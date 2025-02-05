//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2006-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#include <boost/interprocess/detail/workaround.hpp>
#if BOOST_CXX_VERSION >= 201103L
//[doc_multi_index
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/container/string.hpp>

//<-
//Shield against external warnings
#include <boost/interprocess/detail/config_external_begin.hpp>
//->

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>

//<-
#include <boost/interprocess/detail/config_external_end.hpp>
#include "../test/get_process_id_name.hpp"
//->

using namespace boost::interprocess;
namespace bmi = boost::multi_index;

typedef managed_shared_memory::allocator<char>::type              char_allocator;
typedef boost::container::basic_string<char, std::char_traits<char>, char_allocator>shm_string;

//Data to insert in shared memory
struct employee
{
   int         id;
   int         age;
   shm_string  name;
   employee( int id_
           , int age_
           , const char *name_
           , const char_allocator &a)
      : id(id_), age(age_), name(name_, a)
   {}
};

//Tags
struct id{};
struct age{};
struct name{};

// Define a multi_index_container of employees with following indices:
//   - a unique index sorted by employee::int,
//   - a non-unique index sorted by employee::name,
//   - a non-unique index sorted by employee::age.
typedef bmi::multi_index_container<
  employee,
  bmi::indexed_by<
    bmi::ordered_unique
      <bmi::tag<id>,  bmi::member<employee,int,&employee::id> >,
    bmi::ordered_non_unique<
      bmi::tag<name>, bmi::member<employee,shm_string,&employee::name> >,
    bmi::ordered_non_unique
      <bmi::tag<age>, bmi::member<employee,int,&employee::age> > >,
  managed_shared_memory::allocator<employee>::type
> employee_set;

int main ()
{
   //Remove shared memory on construction and destruction
   struct shm_remove
   {
      shm_remove() { shared_memory_object::remove(test::get_process_id_name()); }
      ~shm_remove(){ shared_memory_object::remove(test::get_process_id_name()); }
   } remover;
   //<-
   (void)remover;
   //->

   //Create shared memory
   managed_shared_memory segment(create_only,test::get_process_id_name(), 65536);

   //Construct the multi_index in shared memory
   employee_set *es = segment.construct<employee_set>
      ("My MultiIndex Container")            //Container's name in shared memory
      ( employee_set::ctor_args_list()
      , segment.get_allocator<employee>());  //Ctor parameters

   //Now insert elements
   char_allocator ca(segment.get_allocator<char>());
   es->insert(employee(0,31, "Joe", ca));
   es->insert(employee(1,27, "Robert", ca));
   es->insert(employee(2,40, "John", ca));
   return 0;
}
//]

#else ////#if BOOST_CXX_VERSION >= 201103L

int main()
{
   return 0;
}

#endif   //#if BOOST_CXX_VERSION >= 201103L
