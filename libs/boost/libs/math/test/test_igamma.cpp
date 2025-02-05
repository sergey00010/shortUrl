//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef SYCL_LANGUAGE_VERSION
#include <pch_light.hpp>
#endif 

#ifdef __clang__
#  pragma clang diagnostic push 
#  pragma clang diagnostic ignored "-Wliteral-range"
#elif defined(__GNUC__)
#  pragma GCC diagnostic push 
#  pragma GCC diagnostic ignored "-Woverflow"
#endif

#include "test_igamma.hpp"

//
// DESCRIPTION:
// ~~~~~~~~~~~~
//
// This file tests the incomplete gamma functions tgamma,
// tgamma_lower, gamma_p and gamma_q. There are two sets of tests, spot
// tests which compare our results with selected values computed
// using the online special function calculator at 
// functions.wolfram.com, while the bulk of the accuracy tests
// use values generated with NTL::RR at 1000-bit precision
// and our generic versions of these functions.
//
// Note that when this file is first run on a new platform many of
// these tests will fail: the default accuracy is 1 epsilon which
// is too tight for most platforms.  In this situation you will 
// need to cast a human eye over the error rates reported and make
// a judgement as to whether they are acceptable.  Either way please
// report the results to the Boost mailing list.  Acceptable rates of
// error are marked up below as a series of regular expressions that
// identify the compiler/stdlib/platform/data-type/test-data/test-function
// along with the maximum expected peek and RMS mean errors for that
// test.
//

void expected_results()
{
   //
   // Define the max and mean errors expected for
   // various compilers and platforms.
   //
   const char* largest_type;
#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
   if(boost::math::policies::digits<double, boost::math::policies::policy<> >() == boost::math::policies::digits<long double, boost::math::policies::policy<> >())
   {
      largest_type = "(long\\s+)?double";
   }
   else
   {
      largest_type = "long double";
   }
#else
   largest_type = "(long\\s+)?double";
#endif
   //
   // Linux:
   //
   // These should not really be needed, but on *some* Linux
   // versions these error rates are quite large and appear to
   // be related to the accuracy of powl and expl.  On Itanium
   // or Xeon machines the error rates are much lower than this.
   // Worst cases appear to be AMD64 machines.
   //
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "linux",                          // platform
      largest_type,                     // test type(s)
      "[^|]*medium[^|]*",               // test data group
      "[^|]*", 1300, 200);                 // test function
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      ".*Solaris.*",                    // platform
      "real_concept",                   // test type(s)
      "[^|]*medium[^|]*",               // test data group
      "[^|]*", 1000, 200);              // test function
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "linux",                          // platform
      largest_type,                     // test type(s)
      "[^|]*integer[^|]*",               // test data group
      "[^|]*", 1300, 200);                 // test function
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "linux",                          // platform
      "real_concept",                   // test type(s)
      "[^|]*medium[^|]*",               // test data group
      "[^|]*", 1300, 200);                // test function
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "linux",                          // platform
      "real_concept",                   // test type(s)
      "[^|]*integer[^|]*",               // test data group
      "[^|]*", 600, 200);                // test function

   //
   // Mac OS X:
   // It's not clear why these should be required, but see notes above
   // about Linux.
   //
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "Mac OS",                          // platform
      largest_type,                     // test type(s)
      "[^|]*medium[^|]*",               // test data group
      "[^|]*", 5000, 1000);                 // test function
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "Mac OS",                          // platform
      largest_type,                     // test type(s)
      "[^|]*small[^|]*",               // test data group
      "[^|]*", 80, 40);                 // test function
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "Mac OS",                          // platform
      largest_type,                     // test type(s)
      "[^|]*integer[^|]*",               // test data group
      "[^|]*", 2000, 300);                 // test function
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "Mac OS",                          // platform
      "real_concept",                   // test type(s)
      "[^|]*medium[^|]*",               // test data group
      "[^|]*", 5000, 1000);                // test function
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "Mac OS",                          // platform
      "real_concept",                     // test type(s)
      "[^|]*small[^|]*",               // test data group
      "[^|]*", 75, 15);                 // test function
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "Mac OS",                          // platform
      "real_concept",                   // test type(s)
      "[^|]*integer[^|]*",               // test data group
      "[^|]*", 2000, 300);                // test function
   //
   // HP-UX:
   //
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "HP-UX",                          // platform
      largest_type,                     // test type(s)
      "[^|]*medium[^|]*",               // test data group
      "[^|]*", 500, 50);                 // test function
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "HP-UX",                          // platform
      "real_concept",                   // test type(s)
      "[^|]*medium[^|]*",               // test data group
      "[^|]*", 500, 100);                // test function
   //
   // Sun OS:
   //
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "Sun.*",                          // platform
      largest_type,                     // test type(s)
      "[^|]*medium[^|]*",               // test data group
      "[^|]*", 500, 100);               // test function
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "Sun.*",                          // platform
      largest_type,                     // test type(s)
      "[^|]*integer[^|]*",              // test data group
      "[^|]*", 100, 30);                // test function
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "Sun.*",                          // platform
      "real_concept",                   // test type(s)
      "[^|]*medium[^|]*",               // test data group
      "[^|]*", 500, 100);                // test function
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "Sun.*",                          // platform
      "real_concept",                   // test type(s)
      "[^|]*integer[^|]*",               // test data group
      "[^|]*", 100, 30);                // test function

   //
   // Mac OS X:
   //
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "Mac OS",                          // platform
      largest_type,                     // test type(s)
      "[^|]*medium[^|]*",               // test data group
      "[^|]*", 100, 50);                 // test function

   //
   // Minw:
   //
   add_expected_result(
      "GNU[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "Win32[^|]*",                          // platform
      "real_concept",                   // test type(s)
      "[^|]*medium[^|]*",               // test data group
      "[^|]*", 1300, 200);               // test function
   add_expected_result(
      "GNU[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "Win32[^|]*",                          // platform
      largest_type,                     // test type(s)
      "[^|]*medium[^|]*",               // test data group
      "[^|]*", 700, 200);                 // test function
   add_expected_result(
      "GNU[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "Win32[^|]*",                          // platform
      largest_type,                     // test type(s)
      "[^|]*small[^|]*",                // test data group
      "[^|]*", 100, 50);                  // test function
   add_expected_result(
      "GNU[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "Win32[^|]*",                          // platform
      largest_type,                     // test type(s)
      "[^|]*integer[^|]*",              // test data group
      ".*", 120, 50);                   // test function
   add_expected_result(
      "GNU[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "Win32[^|]*",                          // platform
      "real_concept",                   // test type(s)
      "[^|]*integer[^|]*",              // test data group
      ".*", 100, 50);                    // test function
   //
   // Cygwin:
   //
   add_expected_result(
      "GNU[^|]*",                       // compiler
      "[^|]*",                          // stdlib
      "Cygwin*",                        // platform
      "real_concept",                   // test type(s)
      "[^|]*medium[^|]*",               // test data group
      "[^|]*", 1300, 200);              // test function
   add_expected_result(
      "GNU[^|]*",                       // compiler
      "[^|]*",                          // stdlib
      "Cygwin*",                        // platform
      largest_type,                     // test type(s)
      "[^|]*medium[^|]*",               // test data group
      "[^|]*", 700, 200);               // test function
   add_expected_result(
      "GNU[^|]*",                       // compiler
      "[^|]*",                          // stdlib
      "Cygwin*",                        // platform
      largest_type,                     // test type(s)
      "[^|]*small[^|]*",                // test data group
      "[^|]*", 100, 50);                // test function
   add_expected_result(
      "GNU[^|]*",                       // compiler
      "[^|]*",                          // stdlib
      "Cygwin*",                        // platform
      largest_type,                     // test type(s)
      "[^|]*integer[^|]*",              // test data group
      ".*", 120, 50);                   // test function
   add_expected_result(
      "GNU[^|]*",                       // compiler
      "[^|]*",                          // stdlib
      "Cygwin*",                        // platform
      "real_concept",                   // test type(s)
      "[^|]*integer[^|]*",              // test data group
      ".*", 100, 50);                   // test function

   //
   // Large exponent range causes more extreme test cases to be evaluated:
   //
   if(std::numeric_limits<long double>::max_exponent > std::numeric_limits<double>::max_exponent)
   {
      add_expected_result(
         "[^|]*",                          // compiler
         "[^|]*",                          // stdlib
         "[^|]*",                          // platform
         largest_type,                     // test type(s)
         "[^|]*large[^|]*",                // test data group
         ".*", 40000, 3000);  // test function
   }


   //
   // Catch all cases come last:
   //
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "[^|]*",                          // platform
      largest_type,                     // test type(s)
      "[^|]*medium[^|]*",               // test data group
      "[^|]*", 50, 20);                 // test function
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "[^|]*",                          // platform
      largest_type,                     // test type(s)
      "[^|]*small[^|]*",                // test data group
      "[^|]*", 20, 10);                  // test function
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "[^|]*",                          // platform
      largest_type,                     // test type(s)
      "[^|]*large[^|]*",                // test data group
      "gamma_q", 500, 50);  // test function
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "Cygwin",                         // platform
      largest_type,                     // test type(s)
      "[^|]*large[^|]*",                // test data group
      "gamma_p", 700, 50);  // test function
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "[^|]*",                          // platform
      largest_type,                     // test type(s)
      "[^|]*large[^|]*",                // test data group
      "gamma_p", 350, 50);  // test function
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "[^|]*",                          // platform
      largest_type,                     // test type(s)
      "[^|]*integer[^|]*",              // test data group
      ".*", 20, 10);                    // test function
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "[^|]*",                          // platform
      "real_concept",                   // test type(s)
      "[^|]*medium[^|]*",               // test data group
      "[^|]*", 1500, 400);                // test function
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "[^|]*",                          // platform
      "real_concept",                   // test type(s)
      "[^|]*small[^|]*",                // test data group
      ".*", 100, 20);                  // test function
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "[^|]*",                          // platform
      "real_concept",                   // test type(s)
      "[^|]*large[^|]*",                // test data group
      ".*", 1000000, 100000);        // test function
   add_expected_result(
      "[^|]*",                          // compiler
      "[^|]*",                          // stdlib
      "[^|]*",                          // platform
      "real_concept",                   // test type(s)
      "[^|]*integer[^|]*",              // test data group
      ".*", 200, 40);                    // test function

   //
   // Finish off by printing out the compiler/stdlib/platform names,
   // we do this to make it easier to mark up expected error rates.
   //
   std::cout << "Tests run with " << BOOST_COMPILER << ", " 
      << BOOST_STDLIB << ", " << BOOST_PLATFORM << std::endl;
}

BOOST_AUTO_TEST_CASE( test_main )
{
   expected_results();
   BOOST_MATH_CONTROL_FP;

#ifndef BOOST_MATH_BUGGY_LARGE_FLOAT_CONSTANTS
   test_spots(0.0F);
#endif
   test_spots(0.0);
#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
   test_spots(0.0L);
#ifndef BOOST_MATH_NO_REAL_CONCEPT_TESTS
   test_spots(boost::math::concepts::real_concept(0.1));
#endif
#endif

#ifndef BOOST_MATH_BUGGY_LARGE_FLOAT_CONSTANTS
   test_gamma(0.1F, "float");
#endif
   test_gamma(0.1, "double");
#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
   test_gamma(0.1L, "long double");
#ifndef BOOST_MATH_NO_REAL_CONCEPT_TESTS
#if !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x582))
   test_gamma(boost::math::concepts::real_concept(0.1), "real_concept");
#endif
#endif
#else
   std::cout << "<note>The long double tests have been disabled on this platform "
      "either because the long double overloads of the usual math functions are "
      "not available at all, or because they are too inaccurate for these tests "
      "to pass.</note>" << std::endl;
#endif
   
}



