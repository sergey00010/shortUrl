
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#if !defined(_M_IX86)

#include <boost/config/pragma_message.hpp>
BOOST_PRAGMA_MESSAGE("Test skipped because _M_IX86 is not defined")

#elif defined(__clang__)

// Clang-cl 32 bit supports __stdcall, but BOOST_FT_CC_STDCALL isn't defined so the test errors out

#include <boost/config/pragma_message.hpp>
BOOST_PRAGMA_MESSAGE("Test skipped because _M_IX86 is defined, but __clang__ is also defined")

#else

#define BOOST_FT_AUTODETECT_CALLING_CONVENTIONS

#include <boost/mpl/assert.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/function_types/function_type.hpp>
#include <boost/function_types/function_pointer.hpp>
#include <boost/function_types/function_reference.hpp>
#include <boost/function_types/is_callable_builtin.hpp>

#ifndef BOOST_FT_CC_STDCALL
#   error "test not supported with this compiler/platform"
#endif

namespace ft = boost::function_types;
namespace mpl = boost::mpl;

typedef ft::stdcall_cc cc;


BOOST_MPL_ASSERT((
  ft::is_callable_builtin< 
    ft::function_type<mpl::vector<void,int>, cc>::type 
  >
));

BOOST_MPL_ASSERT((
  ft::is_callable_builtin<
    ft::function_pointer<mpl::vector<void,int>, cc>::type 
  >
));

BOOST_MPL_ASSERT((
  ft::is_callable_builtin<
    ft::function_reference<mpl::vector<void,int>, cc>::type 
  >
));

#endif
