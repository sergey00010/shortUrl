// Boost.Geometry (aka GGL, Generic Geometry Library)
// QuickBook Example

// Copyright (c) 2011-2024 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//[append
//` Shows usage of Boost.Geometry's append to append a point or a range to a polygon

#include <iostream>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>

BOOST_GEOMETRY_REGISTER_BOOST_TUPLE_CS(cs::cartesian)

int main()
{
    using boost::geometry::append;

    using vector = std::vector<boost::tuple<int, int>>;
    using polygon = boost::geometry::model::polygon<boost::tuple<int, int>>;

    polygon poly;

    // Append a range
    append(poly, vector{{0, 0}, {0, 10}, {11, 11}, {10, 0}}); /*< vector models a range and can therefore be used in boost::geometry::append >*/
    // Append a point (in this case the closing point)
    append(poly, boost::make_tuple(0, 0));

    // Create an interior ring (append does not do this automatically)
    boost::geometry::interior_rings(poly).resize(1);

    // Append a range to the interior ring
    append(poly, vector{{2, 2}, {2, 5}, {6, 6}, {5, 2}}, 0); /*< The last parameter ring_index 0 denotes the first interior ring >*/

    // Append a point to the first interior ring
    append(poly, boost::make_tuple(2, 2), 0);

    std::cout << boost::geometry::dsv(poly) << std::endl;

    return 0;
}

//]


//[append_output
/*`
Output:
[pre
(((0, 0), (0, 10), (11, 11), (10, 0), (0, 0)), ((2, 2), (2, 5), (6, 6), (5, 2), (2, 2)))
]
*/
//]
