// Copyright 2008-2024 Emil Dotchevski and Reverge Studios, Inc.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef BOOST_QVM_TEST_SINGLE_HEADER
#   include BOOST_QVM_TEST_SINGLE_HEADER
#else
#   include <boost/qvm/vec_operations.hpp>
#endif

#include "test_qvm_vector.hpp"
#include "gold.hpp"

namespace
    {
    template <int Dim>
    void
    test()
        {
        using namespace boost::qvm::sfinae;

        test_qvm::vector<V1,Dim> const x(42,1);
        float m1=mag_sqr(x);
        float m2=mag_sqr(vref(x));
        float m3=test_qvm::dot<float>(x.a,x.a);
        BOOST_QVM_TEST_CLOSE(m1,m3,0.000001f);
        BOOST_QVM_TEST_CLOSE(m2,m3,0.000001f);
        }
    }

int
main()
    {
    test<2>();
    test<3>();
    test<4>();
    test<5>();
    return boost::report_errors();
    }
