// Boost.Geometry (aka GGL, Generic Geometry Library)
// QuickBook Example

// Copyright (c) 2011-2024 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//[intersects
//` Check if two linestrings intersect each other

#include <iostream>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

int main()
{
    // Calculate the intersects of a cartesian polygon
    using P = boost::geometry::model::d2::point_xy<double>;
    boost::geometry::model::linestring<P> line1, line2;

    boost::geometry::read_wkt("linestring(1 1,2 2)", line1);
    boost::geometry::read_wkt("linestring(2 1,1 2)", line2);

    bool intersects = boost::geometry::intersects(line1, line2);

    std::cout << "Intersects: " << (intersects ? "YES" : "NO") << std::endl;

    return 0;
}

//]


//[intersects_output
/*`
Output:
[pre
Intersects: YES
]
*/
//]
