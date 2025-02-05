// allocate_shared_alloc11_test.cpp
//
// allocate_shared with a minimal C++11 allocator
//
// Copyright 2007-2009, 2014 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/core/lightweight_test.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/config.hpp>
#include <cstddef>

template< class T > class cxx11_allocator
{
public:

    typedef T value_type;

    cxx11_allocator()
    {
    }

    template< class Y > cxx11_allocator( cxx11_allocator<Y> const & )
    {
    }

    T * allocate( std::size_t n )
    {
        return static_cast< T* >( ::operator new( n * sizeof( T ) ) );
    }

    void deallocate( T * p, std::size_t n )
    {
        ::operator delete( p );
    }
};

class X
{
private:

    X( X const & );
    X & operator=( X const & );

    void * operator new( std::size_t n )
    {
        BOOST_ERROR( "private X::new called" );
        return ::operator new( n );
    }

    void operator delete( void * p )
    {
        BOOST_ERROR( "private X::delete called" );
        ::operator delete( p );
    }

public:

    static int instances;

    int v;

    explicit X( int a1 = 0, int a2 = 0, int a3 = 0, int a4 = 0, int a5 = 0, int a6 = 0, int a7 = 0, int a8 = 0, int a9 = 0 ): v( a1+a2+a3+a4+a5+a6+a7+a8+a9 )
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
    {
        boost::shared_ptr< int > pi = boost::allocate_shared< int >( cxx11_allocator<int>() );

        BOOST_TEST( pi.get() != 0 );
        BOOST_TEST( *pi == 0 );
    }

    {
        boost::shared_ptr< int > pi = boost::allocate_shared< int >( cxx11_allocator<int>(), 5 );

        BOOST_TEST( pi.get() != 0 );
        BOOST_TEST( *pi == 5 );
    }

    BOOST_TEST( X::instances == 0 );

    {
        boost::shared_ptr< X > pi = boost::allocate_shared< X >( cxx11_allocator<void>() );
        boost::weak_ptr<X> wp( pi );

        BOOST_TEST( X::instances == 1 );
        BOOST_TEST( pi.get() != 0 );
        BOOST_TEST( pi->v == 0 );

        pi.reset();

        BOOST_TEST( X::instances == 0 );
    }

    {
        boost::shared_ptr< X > pi = boost::allocate_shared< X >( cxx11_allocator<void>(), 1 );
        boost::weak_ptr<X> wp( pi );

        BOOST_TEST( X::instances == 1 );
        BOOST_TEST( pi.get() != 0 );
        BOOST_TEST( pi->v == 1 );

        pi.reset();

        BOOST_TEST( X::instances == 0 );
    }

    {
        boost::shared_ptr< X > pi = boost::allocate_shared< X >( cxx11_allocator<void>(), 1, 2 );
        boost::weak_ptr<X> wp( pi );

        BOOST_TEST( X::instances == 1 );
        BOOST_TEST( pi.get() != 0 );
        BOOST_TEST( pi->v == 1+2 );

        pi.reset();

        BOOST_TEST( X::instances == 0 );
    }

    {
        boost::shared_ptr< X > pi = boost::allocate_shared< X >( cxx11_allocator<void>(), 1, 2, 3 );
        boost::weak_ptr<X> wp( pi );

        BOOST_TEST( X::instances == 1 );
        BOOST_TEST( pi.get() != 0 );
        BOOST_TEST( pi->v == 1+2+3 );

        pi.reset();

        BOOST_TEST( X::instances == 0 );
    }

    {
        boost::shared_ptr< X > pi = boost::allocate_shared< X >( cxx11_allocator<void>(), 1, 2, 3, 4 );
        boost::weak_ptr<X> wp( pi );

        BOOST_TEST( X::instances == 1 );
        BOOST_TEST( pi.get() != 0 );
        BOOST_TEST( pi->v == 1+2+3+4 );

        pi.reset();

        BOOST_TEST( X::instances == 0 );
    }

    {
        boost::shared_ptr< X > pi = boost::allocate_shared< X >( cxx11_allocator<void>(), 1, 2, 3, 4, 5 );
        boost::weak_ptr<X> wp( pi );

        BOOST_TEST( X::instances == 1 );
        BOOST_TEST( pi.get() != 0 );
        BOOST_TEST( pi->v == 1+2+3+4+5 );

        pi.reset();

        BOOST_TEST( X::instances == 0 );
    }

    {
        boost::shared_ptr< X > pi = boost::allocate_shared< X >( cxx11_allocator<void>(), 1, 2, 3, 4, 5, 6 );
        boost::weak_ptr<X> wp( pi );

        BOOST_TEST( X::instances == 1 );
        BOOST_TEST( pi.get() != 0 );
        BOOST_TEST( pi->v == 1+2+3+4+5+6 );

        pi.reset();

        BOOST_TEST( X::instances == 0 );
    }

    {
        boost::shared_ptr< X > pi = boost::allocate_shared< X >( cxx11_allocator<void>(), 1, 2, 3, 4, 5, 6, 7 );
        boost::weak_ptr<X> wp( pi );

        BOOST_TEST( X::instances == 1 );
        BOOST_TEST( pi.get() != 0 );
        BOOST_TEST( pi->v == 1+2+3+4+5+6+7 );

        pi.reset();

        BOOST_TEST( X::instances == 0 );
    }

    {
        boost::shared_ptr< X > pi = boost::allocate_shared< X >( cxx11_allocator<void>(), 1, 2, 3, 4, 5, 6, 7, 8 );
        boost::weak_ptr<X> wp( pi );

        BOOST_TEST( X::instances == 1 );
        BOOST_TEST( pi.get() != 0 );
        BOOST_TEST( pi->v == 1+2+3+4+5+6+7+8 );

        pi.reset();

        BOOST_TEST( X::instances == 0 );
    }

    {
        boost::shared_ptr< X > pi = boost::allocate_shared< X >( cxx11_allocator<void>(), 1, 2, 3, 4, 5, 6, 7, 8, 9 );
        boost::weak_ptr<X> wp( pi );

        BOOST_TEST( X::instances == 1 );
        BOOST_TEST( pi.get() != 0 );
        BOOST_TEST( pi->v == 1+2+3+4+5+6+7+8+9 );

        pi.reset();

        BOOST_TEST( X::instances == 0 );
    }

    return boost::report_errors();
}
