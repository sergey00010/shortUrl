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

#include <boost/core/lightweight_test.hpp>

#include <boost/config.hpp>

#include <string>

#include <boost/bimap/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>

#include "strong_type.hpp"

int test_bimap_info()
{
    using namespace boost::bimaps;

    typedef bimap< double, unordered_set_of<int>, with_info<std::string> > bm_type;

    bm_type bm;
    const bm_type & cbm = bm;

    // Insertion with info
    bm      .insert( bm_type::      value_type(1.1 ,   1, "one"   ) );
    bm.left .insert( bm_type:: left_value_type(2.2 ,   2, "two"   ) );
    bm.right.insert( bm_type::right_value_type(  3 , 3.3, "three" ) );

    bm.begin()->info = "1";
    BOOST_TEST( bm.right.find(1)->info == "1" );

    bm.left.find(2.2)->info = "2";
    BOOST_TEST( bm.right.find(2)->info == "2" );

    bm.right.find(3)->info = "3";
    BOOST_TEST( bm.right.find(3)->info == "3" );

    // Empty info insert
    bm      .insert( bm_type::      value_type(4.4 ,   4) );
    bm. left.insert( bm_type:: left_value_type(5.5 ,   5) );
    bm.right.insert( bm_type::right_value_type(  6 , 6.6) );

    BOOST_TEST( bm.right.find(4)->info == "" );

    bm.left.info_at(4.4) = "4";
    BOOST_TEST(  bm.right.info_at(4) == "4" );
    BOOST_TEST( cbm.right.info_at(4) == "4" );

    bm.right.info_at(5) = "5";
    BOOST_TEST(  bm.left.info_at(5.5) == "5" );
    BOOST_TEST( cbm.left.info_at(5.5) == "5" );

    return 0;
}


struct left  {};
struct right {};
struct info  {};

int test_tagged_bimap_info()
{
    using namespace boost::bimaps;

    typedef bimap< tagged<int,left>,
                   tagged<int,right>,
                   with_info<tagged<int,info> > > bm_type;

    bm_type bm;
    const bm_type & cbm = bm;

    bm      .insert( bm_type::      value_type(1,1,1) );
    bm.left .insert( bm_type:: left_value_type(2,2,2) );
    bm.right.insert( bm_type::right_value_type(3,3,3) );

    bm.begin()->get<info>() = 10;
    BOOST_TEST( bm.right.find(1)->get<info>() == 10 );
    BOOST_TEST( cbm.right.find(1)->get<info>() == 10 );

    bm.left.find(2)->get<info>() = 20;
    BOOST_TEST( bm.right.find(2)->get<info>() == 20 );
    BOOST_TEST( cbm.right.find(2)->get<info>() == 20 );

    bm.right.find(3)->get<info>() = 30;
    BOOST_TEST( bm.right.find(3)->get<info>() == 30 );
    BOOST_TEST( cbm.right.find(3)->get<info>() == 30 );

    // Empty info insert
    bm      .insert( bm_type::      value_type(4,4) );
    bm. left.insert( bm_type:: left_value_type(5,5) );
    bm.right.insert( bm_type::right_value_type(6,6) );

    bm.left.info_at(4) = 4;
    BOOST_TEST(  bm.right.info_at(4) == 4 );
    BOOST_TEST( cbm.right.info_at(4) == 4 );

    bm.right.info_at(5) = 5;
    BOOST_TEST(  bm.left.info_at(5) == 5 );
    BOOST_TEST( cbm.left.info_at(5) == 5 );

    return 0;
}

void test_heterogeneous_access_bimap_info()
{
    using namespace boost::bimaps;

    typedef bimap
    <
      set_of< int, std::less< strong<int> > >,
      unordered_set_of
      <
        int, boost::hash< strong<int> >, std::equal_to< strong<int> >
      >,
      with_info<int>
    > bm_type;

    bm_type bm;
    bm.insert(bm_type::value_type(1,1,0));

    BOOST_TEST( bm.left.info_at(strong<int>(1)) == 0 );
    BOOST_TEST( bm.right.info_at(strong<int>(1)) == 0 );

    bm.left.info_at(strong<int>(1))=1;
    BOOST_TEST( bm.left.info_at(strong<int>(1)) == 1 );
    BOOST_TEST( bm.right.info_at(strong<int>(1)) == 1 );

    bm.right.info_at(strong<int>(1))=2;
    BOOST_TEST( bm.left.info_at(strong<int>(1)) == 2 );
    BOOST_TEST( bm.right.info_at(strong<int>(1)) == 2 );
}

int main()
{
    test_bimap_info();
    test_tagged_bimap_info();
    test_heterogeneous_access_bimap_info();
    return boost::report_errors();
}

