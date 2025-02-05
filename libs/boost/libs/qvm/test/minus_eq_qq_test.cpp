// Copyright 2008-2024 Emil Dotchevski and Reverge Studios, Inc.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef BOOST_QVM_TEST_SINGLE_HEADER
#   include BOOST_QVM_TEST_SINGLE_HEADER
#else
#   include <boost/qvm/quat_operations.hpp>
#endif

#include "test_qvm_quaternion.hpp"
#include "gold.hpp"

namespace
    {
    void
    test()
        {
        using namespace boost::qvm::sfinae;
        test_qvm::quaternion<Q1> x(42,2);
            {
            test_qvm::quaternion<Q1> const y(42,1);
            test_qvm::subtract_v(x.b,x.a,y.a);
            x-=y;
            BOOST_QVM_TEST_EQ(x.a,x.b);
            }
            {
            test_qvm::quaternion<Q2> const y(42,1);
            test_qvm::subtract_v(x.b,x.a,y.a);
            x-=y;
            BOOST_QVM_TEST_EQ(x.a,x.b);
            }
        }
    }

int
main()
    {
    test();
    return boost::report_errors();
    }
