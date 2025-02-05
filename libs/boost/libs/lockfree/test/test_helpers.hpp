//  Copyright (C) 2011 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_TEST_HELPERS
#define BOOST_LOCKFREE_TEST_HELPERS

#include <boost/test/test_tools.hpp>

#include <array>
#include <atomic>
#include <mutex>
#include <set>

template < typename int_type >
int_type generate_id( void )
{
    static std::atomic< int_type > generator( 0 );
    return ++generator;
}

template < typename int_type, size_t buckets >
class static_hashed_set
{
public:
    int calc_index( int_type id )
    {
        // knuth hash ... does not need to be good, but has to be portable
        size_t factor = size_t( (float)buckets * 1.616f );

        return ( (size_t)id * factor ) % buckets;
    }

    bool insert( int_type const& id )
    {
        std::size_t index = calc_index( id );

        std::lock_guard< std::mutex > lock( ref_mutex[ index ] );

        auto p = data[ index ].insert( id );

        return p.second;
    }

    bool find( int_type const& id )
    {
        std::size_t index = calc_index( id );

        std::lock_guard< std::mutex > lock( ref_mutex[ index ] );

        return data[ index ].find( id ) != data[ index ].end();
    }

    bool erase( int_type const& id )
    {
        std::size_t index = calc_index( id );

        std::lock_guard< std::mutex > lock( ref_mutex[ index ] );

        if ( data[ index ].find( id ) != data[ index ].end() ) {
            data[ index ].erase( id );
            assert( data[ index ].find( id ) == data[ index ].end() );
            return true;
        } else
            return false;
    }

    std::size_t count_nodes( void ) const
    {
        std::size_t ret = 0;
        for ( int i = 0; i != buckets; ++i ) {
            std::lock_guard< std::mutex > lock( ref_mutex[ i ] );
            ret += data[ i ].size();
        }
        return ret;
    }

private:
    std::array< std::set< int_type >, buckets > data;
    mutable std::array< std::mutex, buckets >   ref_mutex;
};

struct test_equal
{
    test_equal( int i ) :
        i( i )
    {}

    void operator()( int arg ) const
    {
        BOOST_TEST_REQUIRE( arg == i );
    }

    int i;
};

struct dummy_functor
{
    void operator()( int /* arg */ ) const
    {}
};


#endif
