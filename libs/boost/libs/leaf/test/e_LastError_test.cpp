// Copyright 2018-2024 Emil Dotchevski and Reverge Studios, Inc.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef _WIN32

#include <iostream>

int main()
{
    std::cout << "This test requires Windows";
    return 0;
}

#else

#define BOOST_LEAF_CFG_WIN32 1

#ifdef BOOST_LEAF_TEST_SINGLE_HEADER
#   include "leaf.hpp"
#else
#   include <boost/leaf/common.hpp>
#   include <boost/leaf/handle_errors.hpp>
#   include <boost/leaf/result.hpp>
#endif

#if BOOST_LEAF_CFG_STD_STRING
#   include <sstream>
#   include <iostream>
#endif

#include "lightweight_test.hpp"

namespace leaf = boost::leaf;

int main()
{
    SetLastError(ERROR_FILE_NOT_FOUND);
#if BOOST_LEAF_CFG_STD_STRING
    std::ostringstream ss;
    ss << leaf::windows::e_LastError{};
    std::string s = ss.str();
    std::cout << s << std::endl;
#if BOOST_LEAF_CFG_DIAGNOSTICS
    BOOST_TEST_NE(ss.str().find("The system cannot find the file specified"), std::string::npos);
#endif
#endif

    int r = leaf::try_handle_all(
        []() -> leaf::result<int>
        {
            SetLastError(ERROR_FILE_NOT_FOUND);
            struct reset_LastError { ~reset_LastError() {SetLastError(0); } } reset;
            return leaf::new_error( leaf::windows::e_LastError{} );
        },
        []( leaf::windows::e_LastError e )
        {
            BOOST_TEST_EQ(GetLastError(), 0);
            BOOST_TEST_EQ(e.value, ERROR_FILE_NOT_FOUND);
            return 1;
        },
        []
        {
            return 2;
        } );
    BOOST_TEST_EQ(r, 1);
    return boost::report_errors();
}

#endif
