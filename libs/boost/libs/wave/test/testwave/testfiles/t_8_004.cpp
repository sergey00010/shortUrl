/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2020 Jeff Trull. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

//O --c++20
//O -Werror

// test using __VA_ARGS__ inside __VA_OPT__
// JET: Wave seems to inject a space after some lparens

#define sizedvec(TYPE, NAME, SIZE, ...) std::vector<TYPE> NAME(SIZE __VA_OPT__(, __VA_ARGS__))

//R #line 20 "t_8_004.cpp"
//R std::vector<int> foo( 12 );
sizedvec(int, foo, 12);

//R #line 24 "t_8_004.cpp"
//R std::vector<double> bar( 3 , 42.0);
sizedvec(double, bar, 3, 42.0);

// test omitting trailing comma when expanding a macro with both variadic and
// non-variadic parameters where no variadic parameters are supplied
// (allowed starting in C++20)
#define MACRO1(x, ...)  x -> __VA_ARGS__
#define MACRO2(x, ...) #x#__VA_ARGS__
#define MACRO3(x, ...) x##__VA_ARGS__

//R #line 34 "t_8_004.cpp"
MACRO1(1,)  //R 1 -> 
MACRO2(1,)  //R "1""" 
MACRO3(1,)  //R 1 
MACRO1(1)   //R 1 -> 
MACRO2(1)   //R "1""" 
MACRO3(1)   //R 1 
