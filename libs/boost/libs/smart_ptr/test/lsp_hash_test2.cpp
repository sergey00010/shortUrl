// Copyright 2011, 2020 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/smart_ptr/local_shared_ptr.hpp>
#include <boost/core/lightweight_test.hpp>
#include <boost/config.hpp>
#include <functional>

int main()
{
    {
        boost::local_shared_ptr<int> p1, p2( new int );

        BOOST_TEST_EQ( std::hash< boost::local_shared_ptr<int> >()( p1 ), std::hash< int* >()( p1.get() ) );
        BOOST_TEST_EQ( std::hash< boost::local_shared_ptr<int> >()( p2 ), std::hash< int* >()( p2.get() ) );
    }

    {
        boost::local_shared_ptr<int[]> p1, p2( new int[1] );

        BOOST_TEST_EQ( std::hash< boost::local_shared_ptr<int[]> >()( p1 ), std::hash< int* >()( p1.get() ) );
        BOOST_TEST_EQ( std::hash< boost::local_shared_ptr<int[]> >()( p2 ), std::hash< int* >()( p2.get() ) );
    }

    {
        boost::local_shared_ptr<int[1]> p1, p2( new int[1] );

        BOOST_TEST_EQ( std::hash< boost::local_shared_ptr<int[1]> >()( p1 ), std::hash< int* >()( p1.get() ) );
        BOOST_TEST_EQ( std::hash< boost::local_shared_ptr<int[1]> >()( p2 ), std::hash< int* >()( p2.get() ) );
    }

    return boost::report_errors();
}
