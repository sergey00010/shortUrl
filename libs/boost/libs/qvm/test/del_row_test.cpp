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
#include "test_qvm.hpp"
#include "test_qvm_matrix.hpp"
#include "gold.hpp"

namespace
    {
    template <int Rows,int Cols,int Row>
    void
    test()
        {
        using namespace boost::qvm;
        test_qvm::matrix<M1,Rows,Cols> x(42,1);
        float r1[Rows-1][Cols];
        for( int i=0; i!=Rows-1; ++i )
            for( int j=0; j!=Cols; ++j )
                r1[i][j]=x.a[i+(i>=Row)][j];
        float r2[Rows-1][Cols];
        assign(r2,del_row<Row>(x));
        BOOST_QVM_TEST_EQ(r1,r2);
        del_row<Row>(x) *= 2;
        for( int i=0; i!=Rows-1; ++i )
            for( int j=0; j!=Cols; ++j )
                r1[i][j]=x.a[i+(i>=Row)][j];
        assign(r2,del_row<Row>(x));
        BOOST_QVM_TEST_EQ(r1,r2);
        del_row<Row>(x)+del_row<Row>(x);
        -del_row<Row>(x);
        }
    }

int
main()
    {
    test<2,2,0>();
    test<2,2,1>();

    test<3,3,0>();
    test<3,3,1>();
    test<3,3,2>();

    test<4,4,0>();
    test<4,4,1>();
    test<4,4,2>();
    test<4,4,3>();

    test<5,5,0>();
    test<5,5,1>();
    test<5,5,2>();
    test<5,5,3>();
    test<5,5,4>();
    return boost::report_errors();
    }
