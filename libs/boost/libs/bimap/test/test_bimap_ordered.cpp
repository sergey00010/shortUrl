// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
// Copyright (c) 2024 Joaquin M Lopez Munoz
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  VC++ 8.0 warns on usage of certain Standard Library and API functions that
//  can be cause buffer overruns or other possible security issues if misused.
//  See https://web.archive.org/web/20071014014301/http://msdn.microsoft.com/msdnmag/issues/05/05/SafeCandC/default.aspx
//  But the wording of the warning is misleading and unsettling, there are no
//  portable alternative functions, and VC++ 8.0's own libraries use the
//  functions in question. So turn off the warnings.
#define _CRT_SECURE_NO_DEPRECATE
#define _SCL_SECURE_NO_DEPRECATE

#include <boost/config.hpp>

#define BOOST_BIMAP_DISABLE_SERIALIZATION

#include <boost/core/lightweight_test.hpp>

// std
#include <set>
#include <map>
#include <string>
#include <functional>

// Set type specifications
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/multiset_of.hpp>

// List type specification
#include <boost/bimap/list_of.hpp>

// bimap container
#include <boost/bimap/bimap.hpp>

#include "strong_type.hpp"
#include "test_bimap.hpp"

struct  left_tag {};
struct right_tag {};

void test_bimap()
{
    using namespace boost::bimaps;

    typedef std::map<int,double> left_data_type;
    left_data_type left_data;
    left_data.insert( left_data_type::value_type(1,0.1) );
    left_data.insert( left_data_type::value_type(2,0.2) );
    left_data.insert( left_data_type::value_type(3,0.3) );
    left_data.insert( left_data_type::value_type(4,0.4) );

    typedef std::map<double,int> right_data_type;
    right_data_type right_data;
    right_data.insert( right_data_type::value_type(0.1,1) );
    right_data.insert( right_data_type::value_type(0.2,2) );
    right_data.insert( right_data_type::value_type(0.3,3) );
    right_data.insert( right_data_type::value_type(0.4,4) );


    //--------------------------------------------------------------------
    {
        typedef bimap< int, double > bm_type;

        std::set< bm_type::value_type > data;
        data.insert( bm_type::value_type(1,0.1) );
        data.insert( bm_type::value_type(2,0.2) );
        data.insert( bm_type::value_type(3,0.3) );
        data.insert( bm_type::value_type(4,0.4) );

        bm_type bm;
        test_set_set_bimap(bm,data,left_data,right_data);
    }
    //--------------------------------------------------------------------


    //--------------------------------------------------------------------
    {
        typedef bimap
        <
            multiset_of< tagged<int, left_tag > >,
            multiset_of< tagged<double, right_tag > >,
            multiset_of_relation< std::less< _relation > >

        > bm_type;

        std::set< bm_type::value_type > data;
        data.insert( bm_type::value_type(1,0.1) );
        data.insert( bm_type::value_type(2,0.2) );
        data.insert( bm_type::value_type(3,0.3) );
        data.insert( bm_type::value_type(4,0.4) );

        bm_type bm;

        test_multiset_multiset_bimap(bm,data,left_data,right_data);
        test_tagged_bimap<left_tag,right_tag>(bm,data);
    }
    //--------------------------------------------------------------------


    //--------------------------------------------------------------------
    {
        typedef bimap<int,double,right_based> bm_type;

        std::set< bm_type::value_type > data;
        data.insert( bm_type::value_type(1,0.1) );
        data.insert( bm_type::value_type(2,0.2) );
        data.insert( bm_type::value_type(3,0.3) );
        data.insert( bm_type::value_type(4,0.4) );

        bm_type bm;

        test_set_set_bimap(bm,data,left_data,right_data);
    }
    //--------------------------------------------------------------------


    //--------------------------------------------------------------------
    {
        typedef bimap
        <
            multiset_of< int, std::greater<int> >, set_of<std::string> ,
            multiset_of_relation< std::greater< _relation > >

        > bimap_type;

        bimap_type b1;

        b1.insert( bimap_type::value_type(1,"one") );

        bimap_type b2( b1 );

        BOOST_TEST(     b1 == b2   );
        BOOST_TEST( ! ( b1 != b2 ) );
        BOOST_TEST(     b1 <= b2   );
        BOOST_TEST(     b1 >= b2   );
        BOOST_TEST( ! ( b1 <  b2 ) );
        BOOST_TEST( ! ( b1 >  b2 ) );

        b1.insert( bimap_type::value_type(2,"two") );

        b2 = b1;
        BOOST_TEST( b2 == b1 );

        b1.insert( bimap_type::value_type(3,"three") );

        b2.left = b1.left;
        BOOST_TEST( b2 == b1 );

        b1.insert( bimap_type::value_type(4,"four") );

        b2.right = b1.right;
        BOOST_TEST( b2 == b1 );

        b1.clear();
        b2.swap(b1);
        BOOST_TEST( b2.empty() && !b1.empty() );

        b1.left.swap( b2.left );
        BOOST_TEST( b1.empty() && !b2.empty() );

        b1.right.swap( b2.right );
        BOOST_TEST( b2.empty() && !b1.empty() );
    }
    //--------------------------------------------------------------------

    {
        typedef bimap
        <
            set_of< int, std::less< strong<int> > >,
            multiset_of< int, std::less< strong<int> > >,
            set_of_relation<>

        > bm_type;

        std::set< bm_type::value_type > data;
        data.insert( bm_type::value_type(1,1) );
        data.insert( bm_type::value_type(2,2) );
        data.insert( bm_type::value_type(3,3) );
        data.insert( bm_type::value_type(4,4) );

        std::map<int,int> sided_data;
        sided_data.emplace(1,1);
        sided_data.emplace(2,2);
        sided_data.emplace(3,3);
        sided_data.emplace(4,4);

        bm_type bm;

        test_basic_bimap(bm,data,sided_data,sided_data);
        test_associative_container(bm,data);
        test_pair_heterogeneous_ordered_associative_container< strong<int> >(
          bm.left,sided_data);
        test_pair_heterogeneous_ordered_associative_container< strong<int> >(
          bm.right,sided_data);
    }
    //--------------------------------------------------------------------
}


int main()
{
    test_bimap();
    return boost::report_errors();
}

