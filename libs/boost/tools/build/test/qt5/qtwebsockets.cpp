// (c) Copyright Juergen Hunold 2016
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE.txt or copy at
// https://www.bfgroup.xyz/b2/LICENSE.txt)

#define BOOST_TEST_MODULE QtWebSockets

#include <QtWebSockets>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE (defines)
{
    BOOST_CHECK_EQUAL(BOOST_IS_DEFINED(QT_CORE_LIB), true);
    BOOST_CHECK_EQUAL(BOOST_IS_DEFINED(QT_WEBSOCKETS_LIB), true);
}

BOOST_AUTO_TEST_CASE( websocket )
{
    QWebSocket socket;
    socket.setPauseMode(QAbstractSocket::PauseNever);

    BOOST_TEST(socket.isValid() == false);
}
