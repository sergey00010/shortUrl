/*=============================================================================
    Copyright (c) 2010 Tim Blechmann

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <boost/heap/pairing_heap.hpp>

#include "common_heap_tests.hpp"
#include "merge_heap_tests.hpp"
#include "mutable_heap_tests.hpp"
#include "stable_heap_tests.hpp"

template < bool stable, bool constant_time_size >
void run_pairing_heap_test( void )
{
    typedef boost::heap::pairing_heap< int,
                                       boost::heap::stable< stable >,
                                       boost::heap::compare< std::less< int > >,
                                       boost::heap::allocator< std::allocator< int > >,
                                       boost::heap::constant_time_size< constant_time_size > >
        pri_queue;

    BOOST_CONCEPT_ASSERT( (boost::heap::MutablePriorityQueue< pri_queue >));
    BOOST_CONCEPT_ASSERT( (boost::heap::MergablePriorityQueue< pri_queue >));

    run_common_heap_tests< pri_queue >();
    run_iterator_heap_tests< pri_queue >();
    run_copyable_heap_tests< pri_queue >();
    run_moveable_heap_tests< pri_queue >();

    run_merge_tests< pri_queue >();

    run_mutable_heap_tests< pri_queue >();

    run_ordered_iterator_tests< pri_queue >();

    if ( stable ) {
        typedef boost::heap::pairing_heap< q_tester,
                                           boost::heap::stable< stable >,
                                           boost::heap::constant_time_size< constant_time_size > >
            stable_pri_queue;
        run_stable_heap_tests< stable_pri_queue >();
    }

    typedef boost::heap::pairing_heap< int,
                                       boost::heap::stable< stable >,
                                       boost::heap::compare< std::less< int > >,
                                       boost::heap::allocator< boost::container::pmr::polymorphic_allocator< int > >,
                                       boost::heap::constant_time_size< constant_time_size > >
        pmr_pri_queue;

    pri_queue_test_stateful_allocator< pmr_pri_queue >();
}

BOOST_AUTO_TEST_CASE( pairing_heap_test )
{
    run_pairing_heap_test< false, false >();
    run_pairing_heap_test< false, true >();
    run_pairing_heap_test< true, false >();
    run_pairing_heap_test< true, true >();

    RUN_EMPLACE_TEST( pairing_heap );
}

BOOST_AUTO_TEST_CASE( pairing_heap_compare_lookup_test )
{
    typedef boost::heap::
        pairing_heap< int, boost::heap::compare< less_with_T >, boost::heap::allocator< std::allocator< int > > >
            pri_queue;
    run_common_heap_tests< pri_queue >();
}


BOOST_AUTO_TEST_CASE( pairing_heap_leak_test )
{
    typedef boost::heap::pairing_heap< boost::shared_ptr< int > > pri_queue;
    run_leak_check_test< pri_queue >();
}
