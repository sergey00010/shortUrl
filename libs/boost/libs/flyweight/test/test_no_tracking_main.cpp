/* Boost.Flyweight test of no_tracking.
 *
 * Copyright 2006-2024 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#include <boost/core/lightweight_test.hpp>
#include "test_no_tracking.hpp"

int main()
{
  test_no_tracking();
  return boost::report_errors();
}
