// Copyright 2021 Peter Dimov.
// Copyright 2023-2024 Joaquin M Lopez Munoz.
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#define _SILENCE_CXX17_OLD_ALLOCATOR_MEMBERS_DEPRECATION_WARNING
#define _SILENCE_CXX20_CISO646_REMOVED_WARNING

#define BOOST_UNORDERED_ENABLE_STATS

#include <boost/unordered/unordered_flat_map.hpp>
#include <boost/core/detail/splitmix64.hpp>
#include <boost/config.hpp>
#include <unordered_map>
#include <vector>
#include <memory>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <type_traits>

using namespace std::chrono_literals;

static void print_time( std::chrono::steady_clock::time_point & t1, char const* label, std::uint32_t s, std::size_t size )
{
    auto t2 = std::chrono::steady_clock::now();

    std::cout << label << ": " << ( t2 - t1 ) / 1ms << " ms (s=" << s << ", size=" << size << ")\n";

    t1 = t2;
}

constexpr unsigned N = 50'000;
constexpr int K = 10;

static std::vector<std::string> indices1, indices2;

static std::string make_index( unsigned x )
{
    char buffer[ 64 ];
    std::snprintf( buffer, sizeof(buffer), "pfx_%u_sfx", x );

    return buffer;
}

static std::string make_random_index( unsigned x )
{
    char buffer[ 64 ];
    std::snprintf( buffer, sizeof(buffer), "pfx_%0*d_%u_sfx", x % 8 + 1, 0, x );

    return buffer;
}

static void init_indices()
{
    indices1.reserve( N*2+1 );
    indices1.push_back( make_index( 0 ) );

    for( unsigned i = 1; i <= N*2; ++i )
    {
        indices1.push_back( make_index( i ) );
    }

    indices2.reserve( N*2+1 );
    indices2.push_back( make_index( 0 ) );

    {
        boost::detail::splitmix64 rng;

        for( unsigned i = 1; i <= N*2; ++i )
        {
            indices2.push_back( make_random_index( static_cast<std::uint32_t>( rng() ) ) );
        }
    }
}

template<class Map> BOOST_NOINLINE void test_insert( Map& map, std::chrono::steady_clock::time_point & t1 )
{
    for( unsigned i = 1; i <= N; ++i )
    {
        map.insert( { indices1[ i ], i } );
    }

    print_time( t1, "Consecutive insert",  0, map.size() );

    for( unsigned i = 1; i <= N; ++i )
    {
        map.insert( { indices2[ i ], i } );
    }

    print_time( t1, "Random insert",  0, map.size() );

    std::cout << std::endl;
}

template<class Map> BOOST_NOINLINE void test_lookup( Map& map, std::chrono::steady_clock::time_point & t1 )
{
    std::uint32_t s;
    
    s = 0;

    for( int j = 0; j < K; ++j )
    {
        for( unsigned i = 1; i <= N * 2; ++i )
        {
            auto it = map.find( indices1[ i ] );
            if( it != map.end() ) s += it->second;
        }
    }

    print_time( t1, "Consecutive lookup",  s, map.size() );

    s = 0;

    for( int j = 0; j < K; ++j )
    {
        for( unsigned i = 1; i <= N * 2; ++i )
        {
            auto it = map.find( indices2[ i ] );
            if( it != map.end() ) s += it->second;
        }
    }

    print_time( t1, "Random lookup",  s, map.size() );

    std::cout << std::endl;
}

template<class Map> BOOST_NOINLINE void test_iteration( Map& map, std::chrono::steady_clock::time_point & t1 )
{
    auto it = map.begin();

    while( it != map.end() )
    {
        if( it->second & 1 )
        {
            if constexpr( std::is_void_v< decltype( map.erase( it ) ) > )
            {
                map.erase( it++ );
            }
            else
            {
                it = map.erase( it );
            }
        }
        else
        {
            ++it;
        }
    }

    print_time( t1, "Iterate and erase odd elements",  0, map.size() );

    std::cout << std::endl;
}

template<class Map> BOOST_NOINLINE void test_erase( Map& map, std::chrono::steady_clock::time_point & t1 )
{
    for( unsigned i = 1; i <= N; ++i )
    {
        map.erase( indices1[ i ] );
    }

    print_time( t1, "Consecutive erase",  0, map.size() );

    for( unsigned i = 1; i <= N; ++i )
    {
        map.erase( indices2[ i ] );
    }

    print_time( t1, "Random erase",  0, map.size() );

    std::cout << std::endl;
}

//

// All Unordered container use the same struct
using stats = boost::unordered_flat_map<int, int>::stats; 

struct record
{
    std::string label_;
    long long time_;
    stats stats_;
};

static std::vector<record> records;

template<template<class...> class Map> BOOST_NOINLINE void test( char const* label )
{
    std::cout << label << ":\n\n";

    Map<std::string, std::uint32_t> map;

    auto t0 = std::chrono::steady_clock::now();
    auto t1 = t0;

    test_insert( map, t1 );

    record rec = { label, 0 };

    test_lookup( map, t1 );
    test_iteration( map, t1 );
    test_lookup( map, t1 );
    test_erase( map, t1 );

    auto tN = std::chrono::steady_clock::now();
    std::cout << "Total: " << ( tN - t0 ) / 1ms << " ms\n\n";

    rec.time_ = ( tN - t0 ) / 1ms;
    rec.stats_ = map.get_stats();
    records.push_back( rec );
}

//

template<class K, class V> using boost_unordered_flat_map =
    boost::unordered_flat_map<K, V, boost::hash<K>, std::equal_to<K>>;

// fnv1a_hash

template<int Bits> struct fnv1a_hash_impl;

template<> struct fnv1a_hash_impl<32>
{
    std::size_t operator()( std::string const& s ) const
    {
        std::size_t h = 0x811C9DC5u;

        char const * first = s.data();
        char const * last = first + s.size();

        for( ; first != last; ++first )
        {
            h ^= static_cast<unsigned char>( *first );
            h *= 0x01000193ul;
        }

        return h;
    }
};

template<> struct fnv1a_hash_impl<64>
{
    std::size_t operator()( std::string const& s ) const
    {
        std::size_t h = 0xCBF29CE484222325ull;

        char const * first = s.data();
        char const * last = first + s.size();

        for( ; first != last; ++first )
        {
            h ^= static_cast<unsigned char>( *first );
            h *= 0x00000100000001B3ull;
        }

        return h;
    }
};

struct fnv1a_hash: fnv1a_hash_impl< std::numeric_limits<std::size_t>::digits >
{
    using is_avalanching = std::true_type;
};

template<class K, class V> using boost_unordered_flat_map_fnv1a =
    boost::unordered_flat_map<K, V, fnv1a_hash, std::equal_to<K>>;

// slightly bad hash

struct slightly_bad_hash
{
    using is_avalanching = std::true_type;

    std::size_t operator()( std::string const& s ) const
    {
       std::size_t h = s.size();

       for( auto ch: s )
       {
         h *= 0x811C9DC4u; // multiplicative factor is even!
         h += static_cast<std::size_t>( ch );
       }

       return h;
    }
};

template<class K, class V> using boost_unordered_flat_map_slightly_bad_hash =
    boost::unordered_flat_map<K, V, slightly_bad_hash, std::equal_to<K>>;

// bad hash

struct bad_hash
{
    using is_avalanching = std::true_type;

    std::size_t operator()( std::string const& s ) const
    {
       std::size_t h = s.size();

       for( auto ch: s )
       {
         h *= 31;
         h += static_cast<std::size_t>( ch );
       }

       return h;
    }
};

template<class K, class V> using boost_unordered_flat_map_bad_hash =
    boost::unordered_flat_map<K, V, bad_hash, std::equal_to<K>>;

//

int main()
{
    init_indices();

    test<boost_unordered_flat_map>( "boost::unordered_flat_map" );
    test<boost_unordered_flat_map_fnv1a>( "boost::unordered_flat_map, FNV-1a" );
    test<boost_unordered_flat_map_slightly_bad_hash>( "boost::unordered_flat_map, slightly_bad_hash" );
    test<boost_unordered_flat_map_bad_hash>( "boost::unordered_flat_map, bad_hash" );

    std::cout << "---\n\n";

    for( auto const& x: records )
    {
        std::cout << std::setw( 46 ) << ( x.label_ + ": " ) << std::setw( 5 ) << x.time_ << " ms\n"
                  << std::setw( 46 ) << "insertion: "
                      << "probe length " << x.stats_.insertion.probe_length.average << "\n"
                  << std::setw( 46 ) << "successful lookup: "
                      << "probe length " << x.stats_.successful_lookup.probe_length.average 
                      << ", num comparisons " << x.stats_.successful_lookup.num_comparisons.average << "\n"
                  << std::setw( 46 ) << "unsuccessful lookup: "
                      << "probe length " << x.stats_.unsuccessful_lookup.probe_length.average 
                      << ", num comparisons " << x.stats_.unsuccessful_lookup.num_comparisons.average << "\n\n";
    }
}
