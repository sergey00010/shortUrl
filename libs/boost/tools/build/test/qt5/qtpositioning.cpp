// (c) Copyright Juergen Hunold 2012
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE.txt or copy at
// https://www.bfgroup.xyz/b2/LICENSE.txt)

#define BOOST_TEST_MODULE QtPositioning

#include <QGeoCoordinate>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE (defines)
{
    BOOST_CHECK_EQUAL(BOOST_IS_DEFINED(QT_CORE_LIB), true);
    BOOST_CHECK_EQUAL(BOOST_IS_DEFINED(QT_POSITIONING_LIB), true);
}

BOOST_AUTO_TEST_CASE( geo_coordinate )
{
    QGeoCoordinate geocoordinate;

    BOOST_CHECK_EQUAL(geocoordinate.type(), QGeoCoordinate::InvalidCoordinate);
}
