/* Unit testing for outcomes
(C) 2013-2024 Niall Douglas <http://www.nedproductions.biz/> (4 commits)


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

#include <boost/outcome/iostream_support.hpp>
#include <boost/outcome.hpp>
#include <boost/outcome/try.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>

BOOST_OUTCOME_AUTO_TEST_CASE(issues_0064_outcome, "BOOST_OUTCOME_TRY on excepted outcome is propagating a null error rather than just an exception")
{
#ifndef BOOST_NO_EXCEPTIONS
  using namespace BOOST_OUTCOME_V2_NAMESPACE;
  auto f = []() -> outcome<int> {
    auto h = []() -> outcome<int> { return boost::copy_exception(std::runtime_error("hello")); };
    BOOST_OUTCOME_TRY((h()));
    return 0;
  }();
  std::cout << print(f) << std::endl;
  BOOST_CHECK(!f.has_value());
  BOOST_CHECK(!f.has_error());
  BOOST_CHECK(f.has_exception());
#endif
}
