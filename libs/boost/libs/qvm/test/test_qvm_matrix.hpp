#ifndef BOOST_QVM_TEST_QVM_MATRIX_HPP_INCLUDED
#define BOOST_QVM_TEST_QVM_MATRIX_HPP_INCLUDED

// Copyright 2008-2024 Emil Dotchevski and Reverge Studios, Inc.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if defined(BOOST_QVM_TEST_SINGLE_HEADER) && !defined(BOOST_QVM_TEST_SINGLE_HEADER)
#   define BOOST_QVM_TEST_REF_WRITE_ELEMENT
#endif

#include <boost/qvm/mat_traits_defaults.hpp>
#include <boost/qvm/deduce_mat.hpp>
#include <boost/qvm/assert.hpp>
#include "test_qvm.hpp"

namespace
test_qvm
    {
    template <class Tag,int Rows,int Cols,class T=float>
    struct
    matrix
        {
        T a[Rows][Cols];
        mutable T b[Rows][Cols];

        explicit
        matrix( T start=T(0), T step=T(0) )
            {
            for( int i=0; i!=Rows; ++i )
                for( int j=0; j!=Cols; ++j,start+=step )
                    a[i][j]=b[i][j]=start;
            }
        };

    template <int Rows,int Cols,class Tag1,class T1,class Tag2,class T2>
    void
    dump_ab( matrix<Tag1,Rows,Cols,T1> const & a, matrix<Tag2,Rows,Cols,T2> const & b )
        {
        detail::dump_ab(a.a,b.a);
        }
    }

namespace boost { namespace qvm {

#ifdef BOOST_QVM_TEST_REF_WRITE_ELEMENT

template <class Tag,int Rows,int Cols,class T>
struct
mat_traits< test_qvm::matrix<Tag,Rows,Cols,T> >:
    mat_traits_defaults<test_qvm::matrix<Tag,Rows,Cols,T>,T,Rows,Cols>
    {
    typedef mat_traits_defaults<test_qvm::matrix<Tag,Rows,Cols,T>,T,Rows,Cols> base;

    template <int R,int C>
    static
    T &
    write_element( typename base::mat_type & m )
        {
        BOOST_QVM_STATIC_ASSERT(R>=0);
        BOOST_QVM_STATIC_ASSERT(R<Rows);
        BOOST_QVM_STATIC_ASSERT(C>=0);
        BOOST_QVM_STATIC_ASSERT(C<Cols);
        return m.a[R][C];
        }

    using base::read_element;
    using base::read_element_idx;
    using base::write_element_idx;
    };

#else

template <class Tag,int Rows,int Cols,class T>
struct
mat_traits< test_qvm::matrix<Tag,Rows,Cols,T> >
    {
    typedef test_qvm::matrix<Tag,Rows,Cols,T> this_matrix;
    typedef T scalar_type;
    static int const rows = Rows;
    static int const cols = Cols;

    template <int R,int C>
    static
    void
    write_element( this_matrix & m, T s )
        {
        BOOST_QVM_STATIC_ASSERT(R>=0);
        BOOST_QVM_STATIC_ASSERT(R<Rows);
        BOOST_QVM_STATIC_ASSERT(C>=0);
        BOOST_QVM_STATIC_ASSERT(C<Cols);
        m.a[R][C] = s;
        }

    template <int R,int C>
    static
    T
    read_element( this_matrix const & m )
        {
        BOOST_QVM_STATIC_ASSERT(R>=0);
        BOOST_QVM_STATIC_ASSERT(R<Rows);
        BOOST_QVM_STATIC_ASSERT(C>=0);
        BOOST_QVM_STATIC_ASSERT(C<Cols);
        return m.a[R][C];
        }

    static
    void
    write_element_idx( int r, int c, this_matrix & m, T s )
        {
        BOOST_QVM_ASSERT(r>=0);
        BOOST_QVM_ASSERT(r<Rows);
        BOOST_QVM_ASSERT(c>=0);
        BOOST_QVM_ASSERT(c<Cols);
        m.a[r][c] = s;
        }

    static
    T
    read_element_idx( int r, int c, this_matrix const & m )
        {
        BOOST_QVM_ASSERT(r>=0);
        BOOST_QVM_ASSERT(r<Rows);
        BOOST_QVM_ASSERT(c>=0);
        BOOST_QVM_ASSERT(c<Cols);
        return m.a[r][c];
        }
    };

#endif

template <class Tag,class T,int R1,int C1,int R2,int C2,int Rows,int Cols>
struct
deduce_mat2<test_qvm::matrix<Tag,R1,C1,T>,test_qvm::matrix<Tag,R2,C2,T>,Rows,Cols>
    {
    typedef test_qvm::matrix<Tag,Rows,Cols,T> type;
    };

} }

namespace
    {
    struct M1;
    struct M2;
    struct M3;
    }

#endif
