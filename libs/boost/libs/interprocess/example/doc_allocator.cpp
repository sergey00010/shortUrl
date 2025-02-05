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
//[doc_allocator
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <cassert>
//<-
#include "../test/get_process_id_name.hpp"
//->

using namespace boost::interprocess;

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

   //Create an allocator that allocates ints from the managed segment
   allocator<int, managed_shared_memory::segment_manager>
      allocator_instance(segment.get_segment_manager());

   //Copy constructed allocator is equal
   allocator<int, managed_shared_memory::segment_manager>
      allocator_instance2(allocator_instance);
   assert(allocator_instance2 == allocator_instance);

   //Allocate and deallocate memory for 100 ints
   allocator_instance2.deallocate(allocator_instance.allocate(100), 100);

   return 0;
}
//]

