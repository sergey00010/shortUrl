/* Example of Outcome used with C APIs
(C) 2024 Niall Douglas <http://www.nedproductions.biz/> (4 commits)


Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

// This header in Experimental Outcome is pure C, it provides a suite of C helper macros
#include "../../../include/boost/outcome/experimental/result.h"

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//! [preamble]
// Declare to C a Result with a happy value of intptr_t
BOOST_OUTCOME_C_DECLARE_RESULT_SYSTEM(result_int, intptr_t)

// Save oneself typing out BOOST_OUTCOME_C_RESULT_SYSTEM(result_int) all the time
typedef BOOST_OUTCOME_C_RESULT_SYSTEM(result_int) result;

// Our custom C enum
enum c_enum
{
  c_enum_not_found,
  c_enum_bad_argument
};

// Make a custom status code domain for this C enum
BOOST_OUTCOME_C_DECLARE_RESULT_SYSTEM_FROM_ENUM(result_int,                                // The C Result type declared above
                                    c_enum,                                    // The C enum we wish to wrap
                                    "{74ceb994-7622-3a21-07f0-b016aa705585}",  // Unique UUID for this domain
                                    // Mappings of C enum values to textual description and semantic equivalances to generic codes
                                    {c_enum::c_enum_not_found, "item not found", {errc::no_such_file_or_directory}},
                                    {c_enum::c_enum_bad_argument, "invoked wrong", {errc::invalid_argument}})

// Make helper macros
#define SUCCESS(v) BOOST_OUTCOME_C_MAKE_RESULT_SYSTEM_SUCCESS(result_int, (v))
#define FAILURE(v) BOOST_OUTCOME_C_MAKE_RESULT_SYSTEM_FROM_ENUM(result_int, c_enum, (v))
//! [preamble]

//! [using]
result positive_only(int x)
{
  if(x < 0)
  {
    return FAILURE(c_enum_bad_argument);
  }
  return SUCCESS(x);
}

bool test(int x)
{
  result r = positive_only(x);
  if(BOOST_OUTCOME_C_RESULT_HAS_ERROR(r))
  {
    if(outcome_status_code_equal_generic(&r.error, EINVAL))
    {
      fprintf(stderr, "Positive numbers only!\n");
      return false;
    }
  }
  return true;
}
//! [using]

//! [try]
result test2(int x)
{
  BOOST_OUTCOME_C_RESULT_SYSTEM_TRY(int v,                                        // what to set to value if successful
                        fprintf(stderr, "Positive numbers only!\n"),  // what cleanup to run if unsuccessful
                        positive_only(x));
  return SUCCESS(v + 1);
}
//! [try]

int main(void)
{
  if(!test(0))
    abort();
  if(test(-1))
    abort();
  return 0;
}
