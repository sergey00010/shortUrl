//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2006-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//[doc_anonymous_upgradable_mutexA
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include "doc_upgradable_mutex_shared_data.hpp"
#include <iostream>
#include <cstdio>
//<-
#include "../test/get_process_id_name.hpp"
//->

using namespace boost::interprocess;

int main ()
{
   //Remove shared memory on destruction
   struct shm_remove
   {
      ~shm_remove(){ shared_memory_object::remove(test::get_process_id_name()); }
   } remover;
   //<-
   (void)remover;
   //->

   //Create a shared memory object.
   shared_memory_object shm
      ( create_only                 //only create
      , test::get_process_id_name() //name
      , read_write                  //read-write mode
      );

   //Set size
   shm.truncate(sizeof(shared_data));

   //Map the whole shared memory in this process
   mapped_region region
      (shm                       //What to map
      ,read_write //Map it as read-write
      );

   //Get the address of the mapped region
   void * addr       = region.get_address();

   //Construct the shared structure in memory
   shared_data * data = new (addr) shared_data;

   //Write some logs
   for(int i = 0; i < shared_data::NumItems; ++i){
      //Lock the upgradable_mutex
      scoped_lock<interprocess_upgradable_mutex> lock(data->upgradable_mutex);
      std::sprintf(data->items[(data->current_line++) % shared_data::NumItems]
               ,"%s_%d", "process_a", i);
      if(i == (shared_data::NumItems-1))
         data->end_a = true;
      //Mutex is released here
   }

   //Wait until the other process ends
   while(1){
      scoped_lock<interprocess_upgradable_mutex> lock(data->upgradable_mutex);
      if(data->end_b)
         break;
   }

   return 0;
}
//]

