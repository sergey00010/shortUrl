// Copyright 2008-2024 Emil Dotchevski and Reverge Studios, Inc.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef BOOST_QVM_TEST_SINGLE_HEADER
#   include BOOST_QVM_TEST_SINGLE_HEADER
#else
#   include <boost/qvm/map_mat_mat.hpp>
#   include <boost/qvm/mat_operations.hpp>
#   include <boost/qvm/mat.hpp>
#endif

#include <boost/qvm/mat_traits_array.hpp>
#include "test_qvm_matrix.hpp"
#include "gold.hpp"

namespace
    {
    template <int Rows,int Cols>
    void
    test()
        {
        using namespace boost::qvm;
        test_qvm::matrix<M1,Rows,Cols> x(42,1);
        float r1[Cols][Rows];
        for( int i=0; i!=Rows; ++i )
            for( int j=0; j!=Cols; ++j )
                r1[j][i]=x.a[i][j];
        float r2[Cols][Rows];
        assign(r2,transposed(x));
        BOOST_QVM_TEST_EQ(r1,r2);
        test_qvm::scalar_multiply_m(x.b,x.a,2.0f);
        transposed(x) *= 2;
        BOOST_QVM_TEST_EQ(x.a,x.b);
        transposed(x) + transposed(x);
        -transposed(x);
        }
    }

int
main()
    {
    test<1,2>();
    test<2,1>();
    test<2,2>();
    test<1,3>();
    test<3,1>();
    test<3,3>();
    test<1,4>();
    test<4,1>();
    test<4,4>();
    test<1,5>();
    test<5,1>();
    test<5,5>();
    return boost::report_errors();
    }
