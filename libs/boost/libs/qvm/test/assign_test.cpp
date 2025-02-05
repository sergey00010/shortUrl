// Copyright 2008-2024 Emil Dotchevski and Reverge Studios, Inc.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef BOOST_QVM_TEST_SINGLE_HEADER
#   include BOOST_QVM_TEST_SINGLE_HEADER
#else
#   include <boost/qvm/quat_operations.hpp>
#   include <boost/qvm/vec_operations.hpp>
#   include <boost/qvm/mat_operations.hpp>
#endif

#include "test_qvm_matrix.hpp"
#include "test_qvm_quaternion.hpp"
#include "test_qvm_vector.hpp"
#include "gold.hpp"

namespace
    {
    template <int Rows,int Cols>
    void
    test_matrix()
        {
        using namespace boost::qvm::sfinae;
        test_qvm::matrix<M1,Rows,Cols> const x(42,1);
        test_qvm::matrix<M2,Rows,Cols> y(43,1);
        assign(y,x);
        BOOST_QVM_TEST_EQ(x.a,y.a);
        }

    template <int Dim>
    void
    test_vector()
        {
        using namespace boost::qvm::sfinae;
        test_qvm::vector<V1,Dim> const x(42,1);
        test_qvm::vector<V2,Dim> y(43,1);
        assign(y,x);
        BOOST_QVM_TEST_EQ(x.a,y.a);
        }

    void
    test_quaternion()
        {
        using namespace boost::qvm::sfinae;
        test_qvm::quaternion<Q1> const x(42,1);
        test_qvm::quaternion<Q2> y(43,1);
        assign(y,x);
        BOOST_QVM_TEST_EQ(x.a,y.a);
        }
    }

int
main()
    {
    test_matrix<1,2>();
    test_matrix<2,1>();
    test_matrix<2,2>();
    test_matrix<1,3>();
    test_matrix<3,1>();
    test_matrix<3,3>();
    test_matrix<1,4>();
    test_matrix<4,1>();
    test_matrix<4,4>();
    test_matrix<1,5>();
    test_matrix<5,1>();
    test_matrix<5,5>();
    test_vector<2>();
    test_vector<3>();
    test_vector<4>();
    test_vector<5>();
    test_quaternion();
    return boost::report_errors();
    }
