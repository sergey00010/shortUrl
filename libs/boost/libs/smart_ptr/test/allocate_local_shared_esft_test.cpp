//  allocate_local_shared_esft_test.cpp
//
//  Copyright 2007-2009, 2017 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/smart_ptr/make_local_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/core/lightweight_test.hpp>
#include <boost/config.hpp>
#include <memory>

class X: public boost::enable_shared_from_this<X>
{
private:

    X( X const & );
    X & operator=( X const & );

public:

    static int instances;

    explicit X( int = 0, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0 )
    {
        ++instances;
    }

    ~X()
    {
        --instances;
    }
};

int X::instances = 0;

int main()
{
    BOOST_TEST_EQ( X::instances, 0 );

    {
        boost::shared_ptr< X > px = boost::allocate_local_shared< X >( std::allocator<void>() );
        BOOST_TEST_EQ( X::instances, 1 );

        try
        {
            boost::shared_ptr< X > qx = px->shared_from_this();

            BOOST_TEST_EQ( px, qx );
            BOOST_TEST( !( px < qx ) && !( qx < px ) );

            px.reset();
            BOOST_TEST_EQ( X::instances, 1 );
        }
        catch( boost::bad_weak_ptr const& )
        {
            BOOST_ERROR( "px->shared_from_this() failed" );
        }
    }

    BOOST_TEST_EQ( X::instances, 0 );

    {
        boost::shared_ptr< X > px = boost::allocate_local_shared_noinit< X >( std::allocator<void>() );
        BOOST_TEST_EQ( X::instances, 1 );

        try
        {
            boost::shared_ptr< X > qx = px->shared_from_this();

            BOOST_TEST_EQ( px, qx );
            BOOST_TEST( !( px < qx ) && !( qx < px ) );

            px.reset();
            BOOST_TEST_EQ( X::instances, 1 );
        }
        catch( boost::bad_weak_ptr const& )
        {
            BOOST_ERROR( "px->shared_from_this() failed" );
        }
    }

    BOOST_TEST_EQ( X::instances, 0 );

    {
        boost::shared_ptr< X > px = boost::allocate_local_shared< X >( std::allocator<void>(), 1 );
        BOOST_TEST_EQ( X::instances, 1 );

        try
        {
            boost::shared_ptr< X > qx = px->shared_from_this();

            BOOST_TEST_EQ( px, qx );
            BOOST_TEST( !( px < qx ) && !( qx < px ) );

            px.reset();
            BOOST_TEST_EQ( X::instances, 1 );
        }
        catch( boost::bad_weak_ptr const& )
        {
            BOOST_ERROR( "px->shared_from_this() failed" );
        }
    }

    BOOST_TEST_EQ( X::instances, 0 );

    {
        boost::shared_ptr< X > px = boost::allocate_local_shared< X >( std::allocator<void>(), 1, 2 );
        BOOST_TEST_EQ( X::instances, 1 );

        try
        {
            boost::shared_ptr< X > qx = px->shared_from_this();

            BOOST_TEST_EQ( px, qx );
            BOOST_TEST( !( px < qx ) && !( qx < px ) );

            px.reset();
            BOOST_TEST_EQ( X::instances, 1 );
        }
        catch( boost::bad_weak_ptr const& )
        {
            BOOST_ERROR( "px->shared_from_this() failed" );
        }
    }

    BOOST_TEST_EQ( X::instances, 0 );

    {
        boost::shared_ptr< X > px = boost::allocate_local_shared< X >( std::allocator<void>(), 1, 2, 3 );
        BOOST_TEST_EQ( X::instances, 1 );

        try
        {
            boost::shared_ptr< X > qx = px->shared_from_this();

            BOOST_TEST_EQ( px, qx );
            BOOST_TEST( !( px < qx ) && !( qx < px ) );

            px.reset();
            BOOST_TEST_EQ( X::instances, 1 );
        }
        catch( boost::bad_weak_ptr const& )
        {
            BOOST_ERROR( "px->shared_from_this() failed" );
        }
    }

    BOOST_TEST_EQ( X::instances, 0 );

    {
        boost::shared_ptr< X > px = boost::allocate_local_shared< X >( std::allocator<void>(), 1, 2, 3, 4 );
        BOOST_TEST_EQ( X::instances, 1 );

        try
        {
            boost::shared_ptr< X > qx = px->shared_from_this();

            BOOST_TEST_EQ( px, qx );
            BOOST_TEST( !( px < qx ) && !( qx < px ) );

            px.reset();
            BOOST_TEST_EQ( X::instances, 1 );
        }
        catch( boost::bad_weak_ptr const& )
        {
            BOOST_ERROR( "px->shared_from_this() failed" );
        }
    }

    BOOST_TEST_EQ( X::instances, 0 );

    {
        boost::shared_ptr< X > px = boost::allocate_local_shared< X >( std::allocator<void>(), 1, 2, 3, 4, 5 );
        BOOST_TEST_EQ( X::instances, 1 );

        try
        {
            boost::shared_ptr< X > qx = px->shared_from_this();

            BOOST_TEST_EQ( px, qx );
            BOOST_TEST( !( px < qx ) && !( qx < px ) );

            px.reset();
            BOOST_TEST_EQ( X::instances, 1 );
        }
        catch( boost::bad_weak_ptr const& )
        {
            BOOST_ERROR( "px->shared_from_this() failed" );
        }
    }

    BOOST_TEST_EQ( X::instances, 0 );

    {
        boost::shared_ptr< X > px = boost::allocate_local_shared< X >( std::allocator<void>(), 1, 2, 3, 4, 5, 6 );
        BOOST_TEST_EQ( X::instances, 1 );

        try
        {
            boost::shared_ptr< X > qx = px->shared_from_this();

            BOOST_TEST_EQ( px, qx );
            BOOST_TEST( !( px < qx ) && !( qx < px ) );

            px.reset();
            BOOST_TEST_EQ( X::instances, 1 );
        }
        catch( boost::bad_weak_ptr const& )
        {
            BOOST_ERROR( "px->shared_from_this() failed" );
        }
    }

    BOOST_TEST_EQ( X::instances, 0 );

    {
        boost::shared_ptr< X > px = boost::allocate_local_shared< X >( std::allocator<void>(), 1, 2, 3, 4, 5, 6, 7 );
        BOOST_TEST_EQ( X::instances, 1 );

        try
        {
            boost::shared_ptr< X > qx = px->shared_from_this();

            BOOST_TEST_EQ( px, qx );
            BOOST_TEST( !( px < qx ) && !( qx < px ) );

            px.reset();
            BOOST_TEST_EQ( X::instances, 1 );
        }
        catch( boost::bad_weak_ptr const& )
        {
            BOOST_ERROR( "px->shared_from_this() failed" );
        }
    }

    BOOST_TEST_EQ( X::instances, 0 );

    {
        boost::shared_ptr< X > px = boost::allocate_local_shared< X >( std::allocator<void>(), 1, 2, 3, 4, 5, 6, 7, 8 );
        BOOST_TEST_EQ( X::instances, 1 );

        try
        {
            boost::shared_ptr< X > qx = px->shared_from_this();

            BOOST_TEST_EQ( px, qx );
            BOOST_TEST( !( px < qx ) && !( qx < px ) );

            px.reset();
            BOOST_TEST_EQ( X::instances, 1 );
        }
        catch( boost::bad_weak_ptr const& )
        {
            BOOST_ERROR( "px->shared_from_this() failed" );
        }
    }

    BOOST_TEST_EQ( X::instances, 0 );

    {
        boost::shared_ptr< X > px = boost::allocate_local_shared< X >( std::allocator<void>(), 1, 2, 3, 4, 5, 6, 7, 8, 9 );
        BOOST_TEST_EQ( X::instances, 1 );

        try
        {
            boost::shared_ptr< X > qx = px->shared_from_this();

            BOOST_TEST_EQ( px, qx );
            BOOST_TEST( !( px < qx ) && !( qx < px ) );

            px.reset();
            BOOST_TEST_EQ( X::instances, 1 );
        }
        catch( boost::bad_weak_ptr const& )
        {
            BOOST_ERROR( "px->shared_from_this() failed" );
        }
    }

    BOOST_TEST_EQ( X::instances, 0 );

    return boost::report_errors();
}
