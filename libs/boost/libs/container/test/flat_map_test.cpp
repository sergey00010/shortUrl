//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2004-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#include <vector>

#include <boost/container/flat_map.hpp>
#include <boost/container/allocator.hpp>
#include <boost/container/detail/container_or_allocator_rebind.hpp>

#include "print_container.hpp"
#include "dummy_test_allocator.hpp"
#include "movable_int.hpp"
#include "flat_map_test.hpp"
#include "propagate_allocator_test.hpp"
#include "container_common_tests.hpp"
#include "emplace_test.hpp"
#include "../../intrusive/test/iterator_test.hpp"
#include "flat_map_test.hpp"

#include <map>
#include <utility>


using namespace boost::container;

class recursive_flat_map
{
   public:
   recursive_flat_map(const recursive_flat_map &c)
      : map_(c.map_)
   {}

   recursive_flat_map & operator =(const recursive_flat_map &c)
   {
      map_= c.map_;
      return *this;
   }

   flat_map<recursive_flat_map, recursive_flat_map> map_;
   flat_map<recursive_flat_map, recursive_flat_map>::iterator it_;
   flat_map<recursive_flat_map, recursive_flat_map>::const_iterator cit_;
   flat_map<recursive_flat_map, recursive_flat_map>::reverse_iterator rit_;
   flat_map<recursive_flat_map, recursive_flat_map>::const_reverse_iterator crit_;

   friend bool operator< (const recursive_flat_map &a, const recursive_flat_map &b)
   {  return a.map_ < b.map_;   }
};


class recursive_flat_multimap
{
public:
   recursive_flat_multimap(const recursive_flat_multimap &c)
      : map_(c.map_)
   {}

   recursive_flat_multimap & operator =(const recursive_flat_multimap &c)
   {
      map_= c.map_;
      return *this;
   }
   flat_multimap<recursive_flat_multimap, recursive_flat_multimap> map_;
   flat_multimap<recursive_flat_multimap, recursive_flat_multimap>::iterator it_;
   flat_multimap<recursive_flat_multimap, recursive_flat_multimap>::const_iterator cit_;
   flat_multimap<recursive_flat_multimap, recursive_flat_multimap>::reverse_iterator rit_;
   flat_multimap<recursive_flat_multimap, recursive_flat_multimap>::const_reverse_iterator crit_;

   friend bool operator< (const recursive_flat_multimap &a, const recursive_flat_multimap &b)
   {  return a.map_ < b.map_;   }
};

template<class C>
void test_move()
{
   //Now test move semantics
   C original;
   C move_ctor(boost::move(original));
   C move_assign;
   move_assign = boost::move(move_ctor);
   move_assign.swap(original);
}


namespace boost{
namespace container {
namespace test{

bool constructor_template_auto_deduction_test()
{

#ifndef BOOST_CONTAINER_NO_CXX17_CTAD
   using namespace boost::container;
   const std::size_t NumElements = 100;
   {
      std::map<int, int> int_map;
      for(std::size_t i = 0; i != NumElements; ++i){
         int_map.insert(std::map<int, int>::value_type(static_cast<int>(i), static_cast<int>(i)));
      }
      std::multimap<int, int> int_mmap;
      for (std::size_t i = 0; i != NumElements; ++i) {
         int_mmap.insert(std::multimap<int, int>::value_type(static_cast<int>(i), static_cast<int>(i)));
      }

      typedef std::less<int> comp_int_t;
      typedef std::allocator<std::pair<int, int> > alloc_pair_int_t;

      //range
      {
         auto fmap = flat_map(int_map.begin(), int_map.end());
         if (!CheckEqualContainers(int_map, fmap))
            return false;
         auto fmmap = flat_multimap(int_mmap.begin(), int_mmap.end());
         if (!CheckEqualContainers(int_mmap, fmmap))
            return false;
      }
      //range+comp
      {
         auto fmap = flat_map(int_map.begin(), int_map.end(), comp_int_t());
         if (!CheckEqualContainers(int_map, fmap))
            return false;
         auto fmmap = flat_multimap(int_mmap.begin(), int_mmap.end(), comp_int_t());
         if (!CheckEqualContainers(int_mmap, fmmap))
            return false;
      }
      //range+comp+alloc
      {
         auto fmap = flat_map(int_map.begin(), int_map.end(), comp_int_t(), alloc_pair_int_t());
         if (!CheckEqualContainers(int_map, fmap))
            return false;
         auto fmmap = flat_multimap(int_mmap.begin(), int_mmap.end(), comp_int_t(), alloc_pair_int_t());
         if (!CheckEqualContainers(int_mmap, fmmap))
            return false;
      }
      //range+alloc
      {
         auto fmap = flat_map(int_map.begin(), int_map.end(), alloc_pair_int_t());
         if (!CheckEqualContainers(int_map, fmap))
            return false;
         auto fmmap = flat_multimap(int_mmap.begin(), int_mmap.end(), alloc_pair_int_t());
         if (!CheckEqualContainers(int_mmap, fmmap))
            return false;
      }

      //ordered_unique_range / ordered_range

      //range
      {
         auto fmap = flat_map(ordered_unique_range, int_map.begin(), int_map.end());
         if(!CheckEqualContainers(int_map, fmap))
            return false;
         auto fmmap = flat_multimap(ordered_range, int_mmap.begin(), int_mmap.end());
         if(!CheckEqualContainers(int_mmap, fmmap))
            return false;
      }
      //range+comp
      {
         auto fmap = flat_map(ordered_unique_range, int_map.begin(), int_map.end(), comp_int_t());
         if (!CheckEqualContainers(int_map, fmap))
            return false;
         auto fmmap = flat_multimap(ordered_range, int_mmap.begin(), int_mmap.end(), comp_int_t());
         if (!CheckEqualContainers(int_mmap, fmmap))
            return false;
      }
      //range+comp+alloc
      {
         auto fmap = flat_map(ordered_unique_range, int_map.begin(), int_map.end(), comp_int_t(), alloc_pair_int_t());
         if (!CheckEqualContainers(int_map, fmap))
            return false;
         auto fmmap = flat_multimap(ordered_range, int_mmap.begin(), int_mmap.end(), comp_int_t(), alloc_pair_int_t());
         if (!CheckEqualContainers(int_mmap, fmmap))
            return false;
      }
      //range+alloc
      {
         auto fmap = flat_map(ordered_unique_range, int_map.begin(), int_map.end(),alloc_pair_int_t());
         if (!CheckEqualContainers(int_map, fmap))
            return false;
         auto fmmap = flat_multimap(ordered_range, int_mmap.begin(), int_mmap.end(),alloc_pair_int_t());
         if (!CheckEqualContainers(int_mmap, fmmap))
            return false;
      }
   }
#endif

   return true;
}

}}}

template<class VoidAllocatorOrContainer>
struct GetMapContainer
{
   template<class ValueType>
   struct apply
   {
      typedef std::pair<ValueType, ValueType> type_t;
      typedef flat_map< ValueType
                 , ValueType
                 , std::less<ValueType>
                 , typename boost::container::dtl::container_or_allocator_rebind<VoidAllocatorOrContainer, type_t>::type
                 > map_type;

      typedef flat_multimap< ValueType
                 , ValueType
                 , std::less<ValueType>
                 , typename boost::container::dtl::container_or_allocator_rebind<VoidAllocatorOrContainer, type_t>::type
                 > multimap_type;
   };
};

//To test default parameters
template<>
struct GetMapContainer<void>
{
   template<class ValueType>
   struct apply
   {
      typedef std::pair<ValueType, ValueType> type_t;
      typedef flat_map< ValueType
         , ValueType
      > map_type;

      typedef flat_multimap< ValueType
         , ValueType
      > multimap_type;
   };
};


struct boost_container_flat_map;
struct boost_container_flat_multimap;

namespace boost { namespace container {   namespace test {

template<>
struct alloc_propagate_base<boost_container_flat_map>
{
   template <class T, class Allocator>
   struct apply
   {
      typedef typename boost::container::allocator_traits<Allocator>::
         template portable_rebind_alloc<std::pair<T, T> >::type TypeAllocator;
      typedef boost::container::flat_map<T, T, std::less<T>, TypeAllocator> type;
   };
};

template<>
struct alloc_propagate_base<boost_container_flat_multimap>
{
   template <class T, class Allocator>
   struct apply
   {
      typedef typename boost::container::allocator_traits<Allocator>::
         template portable_rebind_alloc<std::pair<T, T> >::type TypeAllocator;
      typedef boost::container::flat_multimap<T, T, std::less<T>, TypeAllocator> type;
   };
};

template <class Key, class T, class Compare, class Allocator>
struct get_real_stored_allocator<flat_map<Key, T, Compare, Allocator> >
{
   typedef typename flat_map<Key, T, Compare, Allocator>::impl_stored_allocator_type type;
};

template <class Key, class T, class Compare, class Allocator>
struct get_real_stored_allocator<flat_multimap<Key, T, Compare, Allocator> >
{
   typedef typename flat_multimap<Key, T, Compare, Allocator>::impl_stored_allocator_type type;
};

bool test_heterogeneous_lookups()
{
   BOOST_CONTAINER_STATIC_ASSERT((dtl::is_transparent<less_transparent>::value));
   BOOST_CONTAINER_STATIC_ASSERT(!(dtl::is_transparent<std::less<int> >::value));
   typedef flat_map<int, char, less_transparent> map_t;
   typedef flat_multimap<int, char, less_transparent> mmap_t;
   typedef map_t::value_type value_type;

   map_t map1;
   mmap_t mmap1;

   const map_t &cmap1 = map1;
   const mmap_t &cmmap1 = mmap1;

   if(!map1.insert_or_assign(1, 'a').second)
      return false;
   if( map1.insert_or_assign(1, 'b').second)
      return false;
   if(!map1.insert_or_assign(2, 'c').second)
      return false;
   if( map1.insert_or_assign(2, 'd').second)
      return false;
   if(!map1.insert_or_assign(3, 'e').second)
      return false;

   if(map1.insert_or_assign(1, 'a').second)
      return false;
   if(map1.insert_or_assign(1, 'b').second)
      return false;
   if(map1.insert_or_assign(2, 'c').second)
      return false;
   if(map1.insert_or_assign(2, 'd').second)
      return false;
   if(map1.insert_or_assign(3, 'e').second)
      return false;

   mmap1.insert(value_type(1, 'a'));
   mmap1.insert(value_type(1, 'b'));
   mmap1.insert(value_type(2, 'c'));
   mmap1.insert(value_type(2, 'd'));
   mmap1.insert(value_type(3, 'e'));

   const test::non_copymovable_int find_me(2);

   //find
   if(map1.find(find_me)->second != 'd')
      return false;
   if(cmap1.find(find_me)->second != 'd')
      return false;
   if(mmap1.find(find_me)->second != 'c')
      return false;
   if(cmmap1.find(find_me)->second != 'c')
      return false;

   //count
   if(map1.count(find_me) != 1)
      return false;
   if(cmap1.count(find_me) != 1)
      return false;
   if(mmap1.count(find_me) != 2)
      return false;
   if(cmmap1.count(find_me) != 2)
      return false;

   //contains
   if(!map1.contains(find_me))
      return false;
   if(!cmap1.contains(find_me))
      return false;
   if(!mmap1.contains(find_me))
      return false;
   if(!cmmap1.contains(find_me))
      return false;

   //lower_bound
   if(map1.lower_bound(find_me)->second != 'd')
      return false;
   if(cmap1.lower_bound(find_me)->second != 'd')
      return false;
   if(mmap1.lower_bound(find_me)->second != 'c')
      return false;
   if(cmmap1.lower_bound(find_me)->second != 'c')
      return false;

   //upper_bound
   if(map1.upper_bound(find_me)->second != 'e')
      return false;
   if(cmap1.upper_bound(find_me)->second != 'e')
      return false;
   if(mmap1.upper_bound(find_me)->second != 'e')
      return false;
   if(cmmap1.upper_bound(find_me)->second != 'e')
      return false;

   //equal_range
   if(map1.equal_range(find_me).first->second != 'd')
      return false;
   if(cmap1.equal_range(find_me).second->second != 'e')
      return false;
   if(mmap1.equal_range(find_me).first->second != 'c')
      return false;
   if(cmmap1.equal_range(find_me).second->second != 'e')
      return false;

   //erase
   if (map1.erase(find_me) != 1)
      return false;
   if (map1.erase(find_me) != 0)
      return false;
   if (mmap1.erase(find_me) != 2)
      return false;
   if (mmap1.erase(find_me) != 0)
      return false;
   return true;
}

// An ordered sequence of std:pair is also ordered by std::pair::first.
struct with_lookup_by_first
{
   typedef void is_transparent;
   inline bool operator()(std::pair<int, int> a, std::pair<int, int> b) const
   {
      return a < b;
   }
   inline bool operator()(std::pair<int, int> a, int first) const
   {
      return a.first < first;
   }
   inline bool operator()(int first, std::pair<int, int> b) const
   {
      return first < b.first;
   }
};

bool test_heterogeneous_lookup_by_partial_key()
{
   typedef flat_map<std::pair<int, int>,int, with_lookup_by_first> map_t;

   map_t map1;
   map1[std::pair<int, int>(0, 1)] = 3;
   map1[std::pair<int, int>(0, 2)] = 3;

   std::pair<map_t::iterator, map_t::iterator> const first_0_range = map1.equal_range(0);

   if(2 != (first_0_range.second - first_0_range.first))
      return false;

   if(2 != map1.count(0))
      return false;
   return true;
}

}}}   //namespace boost::container::test

int main()
{
   using namespace boost::container::test;

   //Allocator argument container
   {
      flat_map<int, int> map_((flat_map<int, int>::allocator_type()));
      flat_multimap<int, int> multimap_((flat_multimap<int, int>::allocator_type()));
   }
   //Now test move semantics
   {
      test_move<flat_map<recursive_flat_map, recursive_flat_map> >();
      test_move<flat_multimap<recursive_flat_multimap, recursive_flat_multimap> >();
   }
   //Now test nth/index_of
   {
      flat_map<int, int> map;
      flat_multimap<int, int> mmap;

      map.insert(std::pair<int, int>(0, 0));
      map.insert(std::pair<int, int>(1, 0));
      map.insert(std::pair<int, int>(2, 0));
      mmap.insert(std::pair<int, int>(0, 0));
      mmap.insert(std::pair<int, int>(1, 0));
      mmap.insert(std::pair<int, int>(2, 0));
      if(!boost::container::test::test_nth_index_of(map))
         return 1;
      if(!boost::container::test::test_nth_index_of(mmap))
         return 1;
   }

   ////////////////////////////////////
   //    Constructor Template Auto Deduction test
   ////////////////////////////////////
   if(!constructor_template_auto_deduction_test()){
      return 1;
   }

   if (!test_heterogeneous_lookups())
      return 1;

   if (!test_heterogeneous_lookup_by_partial_key())
      return 1;

   ////////////////////////////////////
   //    Testing allocator implementations
   ////////////////////////////////////
   {
      typedef std::map<int, int>                                     MyStdMap;
      typedef std::multimap<int, int>                                MyStdMultiMap;

      if (0 != test::flat_map_test
         < GetMapContainer<void>::apply<int>::map_type
         , MyStdMap
         , GetMapContainer<void>::apply<int>::multimap_type
         , MyStdMultiMap>()) {
         std::cout << "Error in flat_map_test<std::allocator<void> >" << std::endl;
         return 1;
      }

      if (0 != test::flat_map_test
         < GetMapContainer<std::allocator<void> >::apply<int>::map_type
         , MyStdMap
         , GetMapContainer<std::allocator<void> >::apply<int>::multimap_type
         , MyStdMultiMap>()) {
         std::cout << "Error in flat_map_test<std::allocator<void> >" << std::endl;
         return 1;
      }

      if (0 != test::flat_map_test
         < GetMapContainer<void>::apply<int>::map_type
         , MyStdMap
         , GetMapContainer<void>::apply<int>::multimap_type
         , MyStdMultiMap>()) {
         std::cout << "Error in flat_map_test<new_allocator<void> >" << std::endl;
         return 1;
      }

      if (0 != test::flat_map_test
         < GetMapContainer<new_allocator<void> >::apply<int>::map_type
         , MyStdMap
         , GetMapContainer<new_allocator<void> >::apply<int>::multimap_type
         , MyStdMultiMap>()) {
         std::cout << "Error in flat_map_test<new_allocator<void> >" << std::endl;
         return 1;
      }

      if (0 != test::flat_map_test
         < GetMapContainer<new_allocator<void> >::apply<test::movable_int>::map_type
         , MyStdMap
         , GetMapContainer<new_allocator<void> >::apply<test::movable_int>::multimap_type
         , MyStdMultiMap>()) {
         std::cout << "Error in flat_map_test<new_allocator<void> >" << std::endl;
         return 1;
      }

      if (0 != test::flat_map_test
         < GetMapContainer<new_allocator<void> >::apply<test::copyable_int>::map_type
         , MyStdMap
         , GetMapContainer<new_allocator<void> >::apply<test::copyable_int>::multimap_type
         , MyStdMultiMap>()) {
         std::cout << "Error in flat_map_test<new_allocator<void> >" << std::endl;
         return 1;
      }

      if (0 != test::flat_map_test
         < GetMapContainer<new_allocator<void> >::apply<test::movable_and_copyable_int>::map_type
         , MyStdMap
         , GetMapContainer<new_allocator<void> >::apply<test::movable_and_copyable_int>::multimap_type
         , MyStdMultiMap>()) {
         std::cout << "Error in flat_map_test<new_allocator<void> >" << std::endl;
         return 1;
      }
   }

   if(!boost::container::test::test_map_support_for_initialization_list_for<flat_map<int, int> >())
      return 1;

   if (!boost::container::test::test_map_support_for_initialization_list_for<flat_multimap<int, int> >())
      return 1;

   ////////////////////////////////////
   //    Emplace testing
   ////////////////////////////////////
   const test::EmplaceOptions MapOptions = (test::EmplaceOptions)(test::EMPLACE_HINT_PAIR | test::EMPLACE_ASSOC_PAIR);

   if(!boost::container::test::test_emplace<flat_map<test::EmplaceInt, test::EmplaceInt>, MapOptions>())
      return 1;
   if(!boost::container::test::test_emplace<flat_multimap<test::EmplaceInt, test::EmplaceInt>, MapOptions>())
      return 1;

   ////////////////////////////////////
   //    Allocator propagation testing
   ////////////////////////////////////
   if(!boost::container::test::test_propagate_allocator<boost_container_flat_map>())
      return 1;

   if(!boost::container::test::test_propagate_allocator<boost_container_flat_multimap>())
      return 1;

   ////////////////////////////////////
   //    Iterator testing
   ////////////////////////////////////
   {
      typedef boost::container::flat_map<int, int> cont_int;
      cont_int a; a.insert(cont_int::value_type(0, 9)); a.insert(cont_int::value_type(1, 9)); a.insert(cont_int::value_type(2, 9));
      boost::intrusive::test::test_iterator_random< cont_int >(a);
      if(boost::report_errors() != 0) {
         return 1;
      }
   }
   {
      typedef boost::container::flat_multimap<int, int> cont_int;
      cont_int a; a.insert(cont_int::value_type(0, 9)); a.insert(cont_int::value_type(1, 9)); a.insert(cont_int::value_type(2, 9));
      boost::intrusive::test::test_iterator_random< cont_int >(a);
      if(boost::report_errors() != 0) {
         return 1;
      }
   }

   ////////////////////////////////////
   //    has_trivial_destructor_after_move testing
   ////////////////////////////////////
   {
      typedef boost::container::dtl::pair<int, int> value_t;
      typedef boost::container::dtl::select1st<int> key_of_value_t;
      // flat_map, default
      {
         typedef boost::container::new_allocator<value_t> alloc_or_cont_t;
         typedef boost::container::flat_map<int, int> cont;
         typedef boost::container::dtl::flat_tree<value_t, key_of_value_t, std::less<int>, alloc_or_cont_t> tree;
         BOOST_CONTAINER_STATIC_ASSERT_MSG( boost::has_trivial_destructor_after_move<cont>::value ==
                                  boost::has_trivial_destructor_after_move<tree>::value
                                , "has_trivial_destructor_after_move(flat_map, default) test failed");
      }
      // flat_map, vector
      {
         typedef boost::container::vector<value_t> alloc_or_cont_t;
         typedef boost::container::flat_map<int, int, std::less<int>, alloc_or_cont_t> cont;
         typedef boost::container::dtl::flat_tree<value_t, key_of_value_t, std::less<int>, alloc_or_cont_t> tree;
         BOOST_CONTAINER_STATIC_ASSERT_MSG( boost::has_trivial_destructor_after_move<cont>::value ==
                                  boost::has_trivial_destructor_after_move<tree>::value
                                , "has_trivial_destructor_after_move(flat_map, vector) test failed");
      }
      //Old GCCs have problems (compiler bugs) with std::vector and flat_xxx
      #if !defined(BOOST_GCC) || (BOOST_GCC >= 50000)
      // flat_map, std::vector
      {
         typedef std::vector<value_t> alloc_or_cont_t;
         typedef boost::container::flat_map<int, int, std::less<int>, alloc_or_cont_t> cont;
         typedef boost::container::dtl::flat_tree<value_t, key_of_value_t, std::less<int>, alloc_or_cont_t> tree;
         BOOST_CONTAINER_STATIC_ASSERT_MSG( boost::has_trivial_destructor_after_move<cont>::value ==
                                  boost::has_trivial_destructor_after_move<tree>::value
                                , "has_trivial_destructor_after_move(flat_map, std::vector) test failed");
      }
      #endif
      // flat_multimap, default
      {
         typedef boost::container::new_allocator<value_t> alloc_or_cont_t;
         typedef boost::container::flat_multimap<int, int> cont;
         typedef boost::container::dtl::flat_tree<value_t, key_of_value_t, std::less<int>, alloc_or_cont_t> tree;
         BOOST_CONTAINER_STATIC_ASSERT_MSG( boost::has_trivial_destructor_after_move<cont>::value ==
                                  boost::has_trivial_destructor_after_move<tree>::value
                                , "has_trivial_destructor_after_move(flat_multimap, default) test failed");
      }
      // flat_multimap, vector
      {
         typedef boost::container::vector<value_t> alloc_or_cont_t;
         typedef boost::container::flat_multimap<int, int, std::less<int>, alloc_or_cont_t> cont;
         typedef boost::container::dtl::flat_tree<value_t, key_of_value_t, std::less<int>, alloc_or_cont_t> tree;
         BOOST_CONTAINER_STATIC_ASSERT_MSG( boost::has_trivial_destructor_after_move<cont>::value ==
                                  boost::has_trivial_destructor_after_move<tree>::value
                                , "has_trivial_destructor_after_move(flat_multimap, vector) test failed");
      }
      //Old GCCs have problems (compiler bugs) with std::vector and flat_xxx
      #if !defined(BOOST_GCC) || (BOOST_GCC >= 50000)
      // flat_multimap, std::vector
      {
         typedef std::vector<value_t> alloc_or_cont_t;
         typedef boost::container::flat_multimap<int, int, std::less<int>, alloc_or_cont_t> cont;
         typedef boost::container::dtl::flat_tree<value_t, key_of_value_t, std::less<int>, alloc_or_cont_t> tree;
         BOOST_CONTAINER_STATIC_ASSERT_MSG (boost::has_trivial_destructor_after_move<cont>::value ==
                                  boost::has_trivial_destructor_after_move<tree>::value
                                 , "has_trivial_destructor_after_move(flat_multimap, std::vector) test failed");
      }
      #endif
   }

   return 0;
}
