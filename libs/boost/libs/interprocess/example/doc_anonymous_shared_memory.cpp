//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2006-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//[doc_anonymous_shared_memory
#include <boost/interprocess/anonymous_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>
#include <cstring>

int main ()
{
   using namespace boost::interprocess;
   BOOST_INTERPROCESS_TRY{
      //Create an anonymous shared memory segment with size 1000
      mapped_region region(anonymous_shared_memory(1000));

      //Write all the memory to 1
      std::memset(region.get_address(), 1, region.get_size());

      //The segment is unmapped when "region" goes out of scope
   }
   BOOST_INTERPROCESS_CATCH(interprocess_exception &ex){
      std::cout << ex.what() << std::endl;
      return 1;
   } BOOST_INTERPROCESS_CATCH_END
   return 0;
}
//]

