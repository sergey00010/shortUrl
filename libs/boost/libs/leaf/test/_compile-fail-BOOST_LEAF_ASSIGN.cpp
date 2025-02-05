// Copyright 2018-2024 Emil Dotchevski and Reverge Studios, Inc.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/leaf/error.hpp>

namespace leaf = boost::leaf;

template <class T>
struct my_result
{
    my_result( T );
    my_result( std::error_code );
    T value() const;
    std::error_code error();
    explicit operator bool() const;
};

my_result<int> f();

my_result<int> g()
{
    int a;
    BOOST_LEAF_ASSIGN(a, f());
    return a;
}
