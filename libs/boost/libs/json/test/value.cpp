//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

// Test that header file is self-contained.
#include <boost/json/value.hpp>
#include <iostream>

#include <boost/json/monotonic_resource.hpp>

#include <memory>
#include <string>
#include <vector>

#include "test.hpp"
#include "test_suite.hpp"

namespace boost {
namespace json {

BOOST_STATIC_ASSERT( std::is_nothrow_destructible<value>::value );
BOOST_STATIC_ASSERT( std::is_nothrow_move_constructible<value>::value );

namespace {

template<class T>
static
T max_of()
{
    return (std::numeric_limits<T>::max)();
}

template<class T>
static
T min_of()
{
    return (std::numeric_limits<T>::min)();
}

class throwing_buffer
    : public std::streambuf
{
protected:
    int_type
    underflow() override
    {
        // make sure we don't throw before the parser had the chance to start
        if( !gptr()  )
        {
            setg(buf_, buf_, buf_ + 1);
            return *buf_;
        }

        throw std::invalid_argument("this buffer throws");
    }

private:
    char buf_[1] = {'t'};
};

} // (anon)

class value_test
{
public:
    //BOOST_STATIC_ASSERT(has_value_from<short>::value);

    string_view const str_;

    value_test()
        : str_(
            "abcdefghijklmnopqrstuvwxyz")
    {
        // ensure this string does
        // not fit in the SBO area.
        BOOST_ASSERT(str_.size() >
            string().capacity());
    }

    //------------------------------------------------------

    void
    testSpecial()
    {
        auto dsp = storage_ptr{};
        auto sp = make_shared_resource<unique_resource>();

        // ~value()
        {
            value(object{});
            value(array{});
            value(string{});
            value(std::int64_t(0));
            value(std::uint64_t(0));
            value(double(0));
            value(true);
            value(nullptr);
        }

        // value()
        {
            value jv;
            BOOST_TEST(*jv.storage() == *dsp);
        }

        // value(storage_ptr)
        {
            value jv(sp);
            BOOST_TEST(*jv.storage() == *sp);
        }

        // value(pilfered<value>)
        {
            {
                value jv1(object{});
                value jv2(pilfer(jv1));
                BOOST_TEST(jv2.is_object());
            }
            {
                value jv1(array{});
                value jv2(pilfer(jv1));
                BOOST_TEST(jv2.is_array());
            }
            {
                value jv1(string{});
                value jv2(pilfer(jv1));
                BOOST_TEST(jv2.is_string());
            }
            {
                value jv1(std::int64_t{});
                value jv2(pilfer(jv1));
                BOOST_TEST(jv2.is_int64());
            }
            {
                value jv1(std::uint64_t{});
                value jv2(pilfer(jv1));
                BOOST_TEST(jv2.is_uint64());
            }
            {
                value jv1(double{});
                value jv2(pilfer(jv1));
                BOOST_TEST(jv2.is_double());
            }
            {
                value jv1(true);
                value jv2(pilfer(jv1));
                BOOST_TEST(jv2.is_bool());
            }
            {
                value jv1(nullptr);
                value jv2(pilfer(jv1));
                BOOST_TEST(jv2.is_null());
            }

            // ensure pilfered-from objects
            // are trivially destructible
            {
                value v1(make_shared_resource<
                    monotonic_resource>());
                value v2(pilfer(v1));
                BOOST_TEST(v1.storage().get() ==
                    storage_ptr().get());
            }
        }

        // value(value const&)
        {
            {
                value jv1(object{});
                value jv2(jv1);
                BOOST_TEST(jv2.is_object());
            }
            {
                value jv1(array{});
                value jv2(jv1);
                BOOST_TEST(jv2.is_array());
            }
            {
                value jv1(string{});
                value jv2(jv1);
                BOOST_TEST(jv2.is_string());
            }
            {
                value jv1(std::int64_t{});
                value jv2(jv1);
                BOOST_TEST(jv2.is_int64());
            }
            {
                value jv1(std::uint64_t{});
                value jv2(jv1);
                BOOST_TEST(jv2.is_uint64());
            }
            {
                value jv1(double{});
                value jv2(jv1);
                BOOST_TEST(jv2.is_double());
            }
            {
                value jv1(true);
                value jv2(jv1);
                BOOST_TEST(jv2.is_bool());
            }
            {
                value jv1(nullptr);
                value jv2(jv1);
                BOOST_TEST(jv2.is_null());
            }
        }

        // value(value const&, storage_ptr)
        {
            {
                value jv1(object{});
                value jv2(jv1, sp);
                BOOST_TEST(jv2.is_object());
                BOOST_TEST(*jv2.storage() == *sp);
            }
            {
                value jv1(array{});
                value jv2(jv1, sp);
                BOOST_TEST(jv2.is_array());
                BOOST_TEST(*jv2.storage() == *sp);
            }
            {
                value jv1(string{});
                value jv2(jv1, sp);
                BOOST_TEST(jv2.is_string());
                BOOST_TEST(*jv2.storage() == *sp);
            }
            {
                value jv1(std::int64_t{});
                value jv2(jv1, sp);
                BOOST_TEST(jv2.is_int64());
                BOOST_TEST(*jv2.storage() == *sp);
            }
            {
                value jv1(std::uint64_t{});
                value jv2(jv1, sp);
                BOOST_TEST(jv2.is_uint64());
                BOOST_TEST(*jv2.storage() == *sp);
            }
            {
                value jv1(double{});
                value jv2(jv1, sp);
                BOOST_TEST(jv2.is_double());
                BOOST_TEST(*jv2.storage() == *sp);
            }
            {
                value jv1(true);
                value jv2(jv1, sp);
                BOOST_TEST(jv2.is_bool());
                BOOST_TEST(*jv2.storage() == *sp);
            }
            {
                value jv1(nullptr);
                value jv2(jv1, sp);
                BOOST_TEST(jv2.is_null());
                BOOST_TEST(*jv2.storage() == *sp);
            }
        }

        // value(value&&)
        {
            {
                value jv1(object{});
                value jv2(std::move(jv1));
                BOOST_TEST(jv2.is_object());
            }
            {
                value jv1(array{});
                value jv2(std::move(jv1));
                BOOST_TEST(jv2.is_array());
            }
            {
                value jv1(string{});
                value jv2(std::move(jv1));
                BOOST_TEST(jv2.is_string());
            }
            {
                value jv1(std::int64_t{});
                value jv2(std::move(jv1));
                BOOST_TEST(jv2.is_int64());
            }
            {
                value jv1(std::uint64_t{});
                value jv2(std::move(jv1));
                BOOST_TEST(jv2.is_uint64());
            }
            {
                value jv1(double{});
                value jv2(std::move(jv1));
                BOOST_TEST(jv2.is_double());
            }
            {
                value jv1(true);
                value jv2(std::move(jv1));
                BOOST_TEST(jv2.is_bool());
            }
            {
                value jv1(nullptr);
                value jv2(std::move(jv1));
                BOOST_TEST(jv2.is_null());
            }
        }

        // value(value&&, storage_ptr)
        {
            {
                value jv1(object{});
                value jv2(std::move(jv1), sp);
                BOOST_TEST(jv2.is_object());
            }
            {
                value jv1(array{});
                value jv2(std::move(jv1), sp);
                BOOST_TEST(jv2.is_array());
            }
            {
                value jv1(string{});
                value jv2(std::move(jv1), sp);
                BOOST_TEST(jv2.is_string());
            }
            {
                value jv1(std::int64_t{});
                value jv2(std::move(jv1), sp);
                BOOST_TEST(jv2.is_int64());
            }
            {
                value jv1(std::uint64_t{});
                value jv2(std::move(jv1), sp);
                BOOST_TEST(jv2.is_uint64());
            }
            {
                value jv1(double{});
                value jv2(std::move(jv1), sp);
                BOOST_TEST(jv2.is_double());
            }
            {
                value jv1(true);
                value jv2(std::move(jv1), sp);
                BOOST_TEST(jv2.is_bool());
            }
            {
                value jv1(nullptr);
                value jv2(std::move(jv1), sp);
                BOOST_TEST(jv2.is_null());
            }
        }
    }

    void
    testConversion()
    {
        auto dsp = storage_ptr{};
        auto sp = make_shared_resource<unique_resource>();

        // value(object)
        // value(object, storage_ptr)
        // value(object_kind, storage_ptr)
        {
            {
                auto jv = value(object());
                BOOST_TEST(jv.is_object());
                BOOST_TEST(*jv.storage() == *dsp);
            }
            {
                auto jv = value(object(sp));
                BOOST_TEST(jv.is_object());
                BOOST_TEST(*jv.storage() == *sp);
            }
            {
                auto jv = value(object(), sp);
                BOOST_TEST(jv.is_object());
                BOOST_TEST(*jv.storage() == *sp);
            }
            {
                auto jv = value(object_kind);
                BOOST_TEST(jv.is_object());
                BOOST_TEST(*jv.storage() == *dsp);
            }
            {
                auto jv = value(object_kind, sp);
                BOOST_TEST(jv.is_object());
                BOOST_TEST(*jv.storage() == *sp);
            }
            {
                // verify moved from
                object obj{{"a", 1}, {"b", 2}};
                BOOST_TEST(obj.capacity() > 0);
                value jv(std::move(obj), {});
                BOOST_TEST(obj.capacity() == 0);
            }
        }

        // value(array)
        // value(array, storage_ptr)
        // value(object_kind, storage_ptr)
        {
            {
                auto jv = value(array());
                BOOST_TEST(jv.is_array());
                BOOST_TEST(*jv.storage() == *dsp);
            }
            {
                auto jv = value(array(sp));
                BOOST_TEST(jv.is_array());
                BOOST_TEST(*jv.storage() == *sp);
            }
            {
                auto jv = value(array(), sp);
                BOOST_TEST(jv.is_array());
                BOOST_TEST(*jv.storage() == *sp);
            }
            {
                auto jv = value(array_kind);
                BOOST_TEST(jv.is_array());
                BOOST_TEST(*jv.storage() == *dsp);
            }
            {
                auto jv = value(array_kind, sp);
                BOOST_TEST(jv.is_array());
                BOOST_TEST(*jv.storage() == *sp);
            }
        }

        // value(string)
        // value(string, storage_ptr)
        {
            {
                auto jv = value(string());
                BOOST_TEST(jv.is_string());
                BOOST_TEST(*jv.storage() == *dsp);
            }
            {
                auto jv = value(string(sp));
                BOOST_TEST(jv.is_string());
                BOOST_TEST(*jv.storage() == *sp);
            }
            {
                auto jv = value(string(), sp);
                BOOST_TEST(jv.is_string());
                BOOST_TEST(*jv.storage() == *sp);
            }
        }

        // value(int64)
        // value(int64, storage_ptr)
        {
            {
                auto jv = value(std::int64_t{-65536});
                BOOST_TEST(jv.is_int64());
                BOOST_TEST(*jv.storage() == *dsp);
            }
            {
                auto jv = value(std::int64_t{-65536}, sp);
                BOOST_TEST(jv.is_int64());
                BOOST_TEST(*jv.storage() == *sp);
            }
        }

        // value(uint64)
        // value(uint64, storage_ptr)
        {
            {
                auto jv = value(std::uint64_t{65536});
                BOOST_TEST(jv.is_uint64());
                BOOST_TEST(*jv.storage() == *dsp);
            }
            {
                auto jv = value(std::uint64_t{65536}, sp);
                BOOST_TEST(jv.is_uint64());
                BOOST_TEST(*jv.storage() == *sp);
            }
        }

        // value(double)
        // value(double, storage_ptr)
        {
            {
                auto jv = value(double{3.141});
                BOOST_TEST(jv.is_double());
                BOOST_TEST(*jv.storage() == *dsp);
            }
            {
                auto jv = value(double{3.141}, sp);
                BOOST_TEST(jv.is_double());
                BOOST_TEST(*jv.storage() == *sp);
            }
        }

        // value(bool)
        // value(bool, storage_ptr)
        {
            {
                auto jv = value(true);
                BOOST_TEST(jv.is_bool());
                BOOST_TEST(*jv.storage() == *dsp);
            }
            {
                auto jv = value(true, sp);
                BOOST_TEST(jv.is_bool());
                BOOST_TEST(*jv.storage() == *sp);
            }
        }

        // value(nullptr_t)
        // value(nullptr_t, storage_ptr)
        {
            {
                auto jv = value(nullptr);
                BOOST_TEST(jv.is_null());
                BOOST_TEST(*jv.storage() == *dsp);
            }
            {
                auto jv = value(nullptr, sp);
                BOOST_TEST(jv.is_null());
                BOOST_TEST(*jv.storage() == *sp);
            }
        }

        // value(initializer_list)
        // value(initializer_list, storage_ptr)
        {
            {
                value jv({1, 2, 3});
                BOOST_TEST(jv.is_array());
                BOOST_TEST(*jv.storage() == *dsp);
            }
            {
                value jv({1, 2, 3}, sp);
                BOOST_TEST(jv.is_array());
                BOOST_TEST(*jv.storage() == *sp);
            }
            {
                value jv({{"a",1},{"b",2},{"c",3}});
                BOOST_TEST(jv.is_object());
                BOOST_TEST(*jv.storage() == *dsp);
            }
            {
                value jv({{"a",1},{"b",2},{"c",3}}, sp);
                BOOST_TEST(jv.is_object());
                BOOST_TEST(*jv.storage() == *sp);
            }
        }
    }

    void
    testAssignment()
    {
        auto dsp = storage_ptr{};
        auto sp = make_shared_resource<unique_resource>();

        // operator=(value const&)
        {
            {
                value jv1(object{});
                value jv2;
                jv2 = jv1;
                BOOST_TEST(jv2.is_object());
            }
            {
                value jv1(array{});
                value jv2;
                jv2 = jv1;
                BOOST_TEST(jv2.is_array());
            }
            {
                value jv1(string{});
                value jv2;
                jv2 = jv1;
                BOOST_TEST(jv2.is_string());
            }
            {
                value jv1(std::int64_t{});
                value jv2;
                jv2 = jv1;
                BOOST_TEST(jv2.is_int64());
            }
            {
                value jv1(std::uint64_t{});
                value jv2;
                jv2 = jv1;
                BOOST_TEST(jv2.is_uint64());
            }
            {
                value jv1(double{});
                value jv2;
                jv2 = jv1;
                BOOST_TEST(jv2.is_double());
            }
            {
                value jv1(true);
                value jv2;
                jv2 = jv1;
                BOOST_TEST(jv2.is_bool());
            }
            {
                value jv1(nullptr);
                value jv2;
                jv2 = jv1;
                BOOST_TEST(jv2.is_null());
            }

            fail_loop([&](storage_ptr const sp)
            {
                value jv1({1, 2, 3, 4, 5});
                value jv2(sp);
                jv2 = jv1;
                BOOST_TEST(jv2.as_array().size() == 5);
            });

            fail_loop([&](storage_ptr const sp)
            {
                value jv1({
                    {"a",1},{"b",2},{"c",3}});
                value jv2(sp);
                jv2 = jv1;
                BOOST_TEST(jv2.as_object().size() == 3);
            });

            fail_loop([&](storage_ptr const sp)
            {
                value jv1(str_);
                value jv2(sp);
                jv2 = jv1;
                BOOST_TEST(jv2.as_string() == str_);
            });

            // self-assign
            {
                value jv = { 1, 2, 3 };
                jv = static_cast<value const&>(jv);
                BOOST_TEST(jv == value({1, 2, 3}));
            }

            // copy from child
            {
                value jv = { 1, 2, 3 };
                jv = jv.at(1);
                BOOST_TEST(
                    *jv.if_int64() == 2);
            }
        }

        // operator=(value&&)
        {
            {
                value jv;
                jv = value(object{});
                BOOST_TEST(jv.is_object());
            }
            {
                value jv;
                jv = value(array{});
                BOOST_TEST(jv.is_array());
            }
            {
                value jv;
                jv = value(string{});
                BOOST_TEST(jv.is_string());
            }
            {
                value jv;
                jv = value(std::int64_t{});
                BOOST_TEST(jv.is_int64());
            }
            {
                value jv;
                jv = value(std::uint64_t{});
                BOOST_TEST(jv.is_uint64());
            }
            {
                value jv;
                jv = value(double{});
                BOOST_TEST(jv.is_double());
            }
            {
                value jv;
                jv = value(true);
                BOOST_TEST(jv.is_bool());
            }
            {
                value jv;
                jv = value(nullptr);
                BOOST_TEST(jv.is_null());
            }

            fail_loop([&](storage_ptr const sp)
            {
                value jv(sp);
                jv = value({
                    { {"a",1}, {"b",2u} },
                    { 1, 2 },
                    "hello",
                    1,
                    2u,
                    3.,
                    true,
                    nullptr
                    });
                BOOST_TEST(jv.as_array().size() == 8);
            });

            fail_loop([&](storage_ptr const sp)
            {
                value jv(sp);
                jv = value({
                    { "aa", { {"a",1}, {"b",2u} } },
                    { "bb", { 1, 2 } },
                    { "cc", "hello" },
                    { "dd", 1 },
                    { "ee", 2u },
                    { "ff", 3. },
                    { "gg", true },
                    { "hh", nullptr },
                    });
                BOOST_TEST(jv.as_object().size() == 8);
            });

            fail_loop([&](storage_ptr const sp)
            {
                value jv(sp);
                jv = value(str_);
                BOOST_TEST(jv.as_string() == str_);
            });

            // self-move
            {
                value jv = { 1, 2, 3 };
                value* p = &jv;
                jv = std::move(*p);
                BOOST_TEST(jv == value({1, 2, 3}));
            }

            // move from child
            {
                value jv = { 1, 2, 3 };
                jv = std::move(jv.at(1));
                BOOST_TEST(
                    *jv.if_int64() == 2);
            }
        }

        // operator=(initializer_list)
        {
            value jv;
            jv = {1, 2, 3};
            BOOST_TEST(jv.is_array());
            BOOST_TEST(*jv.storage() == *dsp);
            BOOST_TEST(jv.at(0).as_int64() == 1);
            BOOST_TEST(jv.at(1).as_int64() == 2);
            BOOST_TEST(jv.at(2).as_int64() == 3);
        }

        // operator=(nullptr_t)
        {
            {
                value jv = 1;
                BOOST_TEST(! jv.is_null());
                jv = nullptr;
                BOOST_TEST(jv.is_null());
            }
            {
                value jv = "string";
                BOOST_TEST(! jv.is_null());
                jv = nullptr;
                BOOST_TEST(jv.is_null());
            }
        }

        // operator=(bool)
        {
            {
                value jv = 1;
                BOOST_TEST(! jv.is_bool());
                jv = true;
                BOOST_TEST(jv.is_bool());
            }
            {
                value jv = "string";
                BOOST_TEST(! jv.is_bool());
                jv = true;
                BOOST_TEST(jv.is_bool());
            }
        }

        // operator=(int64)
        {
            {
                value jv = false;
                BOOST_TEST(! jv.is_int64());
                jv = std::int64_t{-65536};
                BOOST_TEST(jv.is_int64());
            }
            {
                value jv = "string";
                BOOST_TEST(! jv.is_int64());
                jv = std::int64_t{-65536};
                BOOST_TEST(jv.is_int64());
            }
        }

        // operator=(uint64)
        {
            {
                value jv = false;
                BOOST_TEST(! jv.is_uint64());
                jv = std::uint64_t{65536};
                BOOST_TEST(jv.is_uint64());
            }
            {
                value jv = "string";
                BOOST_TEST(! jv.is_uint64());
                jv = std::uint64_t{65536};
                BOOST_TEST(jv.is_uint64());
            }
        }

        // operator=(double)
        {
            {
                value jv = false;
                BOOST_TEST(! jv.is_double());
                jv = double{3.141};
                BOOST_TEST(jv.is_double());
            }
            {
                value jv = "string";
                BOOST_TEST(! jv.is_double());
                jv = double{3.141};
                BOOST_TEST(jv.is_double());
            }
        }

        // operator=(string)
        {
            {
                value jv;
                jv = string();
                BOOST_TEST(jv.is_string());
                BOOST_TEST(*jv.storage() == *dsp);
            }
            {
                value jv(sp);
                jv = string();
                BOOST_TEST(jv.is_string());
                BOOST_TEST(*jv.storage() == *sp);
            }
        }

        // operator=(array)
        {
            {
                value jv;
                jv = array();
                BOOST_TEST(jv.is_array());
                BOOST_TEST(*jv.storage() == *dsp);
            }
            {
                value jv(sp);
                jv = array();
                BOOST_TEST(jv.is_array());
                BOOST_TEST(*jv.storage() == *sp);
            }
            {
                value jv(sp);
                array const arr;
                jv = arr;
                BOOST_TEST(jv.is_array());
                BOOST_TEST(*jv.storage() == *sp);
            }
        }

        // operator=(object)
        {
            {
                value jv;
                jv = object();
                BOOST_TEST(*jv.storage() == *dsp);
                BOOST_TEST(jv.is_object());
            }
            {
                value jv(sp);
                jv = object();
                BOOST_TEST(jv.is_object());
                BOOST_TEST(*jv.storage() == *sp);
            }
            {
                value jv(sp);
                object const obj;
                jv = obj;
                BOOST_TEST(jv.is_object());
                BOOST_TEST(*jv.storage() == *sp);
            }
        }
    }

    void
    testModifiers()
    {
        // emplace
        {
            BOOST_TEST(value().emplace_object().empty());
            BOOST_TEST(value().emplace_array().empty());
            BOOST_TEST(value().emplace_string().empty());
            BOOST_TEST(value().emplace_int64() == 0);
            BOOST_TEST(value().emplace_uint64() == 0);
            BOOST_TEST(value().emplace_double() == 0);
            BOOST_TEST(value().emplace_bool() = true);
            {
                value jv(object_kind);
                jv.emplace_null();
                BOOST_TEST(jv.is_null());
            }
            {
                value jv(array_kind);
                jv.emplace_null();
                BOOST_TEST(jv.is_null());
            }
            {
                value jv(string_kind);
                jv.emplace_null();
                BOOST_TEST(jv.is_null());
            }
            {
                value jv(-1);
                jv.emplace_null();
                BOOST_TEST(jv.is_null());
            }
            {
                value jv(1U);
                jv.emplace_null();
                BOOST_TEST(jv.is_null());
            }
            {
                value jv(1.0);
                jv.emplace_null();
                BOOST_TEST(jv.is_null());
            }
            {
                value jv(false);
                jv.emplace_null();
                BOOST_TEST(jv.is_null());
            }
            {
                value jv;
                jv.emplace_null();
                BOOST_TEST(jv.is_null());
            }
        }

        // swap
        {
            {
                // self-swap
                value jv;
                swap(jv, jv);
            }
            {
                value jv1(1);
                value jv2("abc");
                BOOST_TEST(
                    *jv1.storage() == *jv2.storage());
                swap(jv1, jv2);
                BOOST_TEST(jv1.as_string() == "abc");
                BOOST_TEST(jv2.as_int64() == 1);
            }

            // different storage
            fail_loop([&](storage_ptr const& sp)
            {
                value jv1(1);
                value jv2("abc", sp);
                BOOST_TEST(
                    *jv1.storage() != *jv2.storage());
                swap(jv1, jv2);
                BOOST_TEST(jv1.as_string() == "abc");
                BOOST_TEST(jv2.as_int64() == 1);
            });
        }
    }

    template<typename T>
    using tt = T;

    void
    testExchange()
    {
        // string{}
        {
            BOOST_TEST(value("abc").is_string());
            BOOST_TEST(value(std::string()).is_string());
            BOOST_TEST(value(string_view()).is_string());

            { value jv; BOOST_TEST((jv = "abc").is_string()); }
            { value jv; BOOST_TEST((jv = std::string()).is_string()); }
            { value jv; BOOST_TEST((jv = string_view()).is_string()); }
        }

        // numbers
        {
            BOOST_TEST(value(tt<signed char>{}).is_int64());
            BOOST_TEST(value(tt<short>{}).is_int64());
            BOOST_TEST(value(tt<int>{}).is_int64());
            BOOST_TEST(value(tt<long>{}).is_int64());
            BOOST_TEST(value(tt<long long>{}).is_int64());
            BOOST_TEST(value(tt<unsigned char>{}).is_uint64());
            BOOST_TEST(value(tt<unsigned short>{}).is_uint64());
            BOOST_TEST(value(tt<unsigned int>{}).is_uint64());
            BOOST_TEST(value(tt<unsigned long>{}).is_uint64());
            BOOST_TEST(value(tt<unsigned long long>{}).is_uint64());
            BOOST_TEST(value(tt<float>{}).is_double());
            BOOST_TEST(value(tt<double>{}).is_double());

            { value jv; BOOST_TEST((jv = tt<signed char>{}).is_int64()); }
            { value jv; BOOST_TEST((jv = tt<short>{}).is_int64()); }
            { value jv; BOOST_TEST((jv = tt<int>{}).is_int64()); }
            { value jv; BOOST_TEST((jv = tt<long>{}).is_int64()); }
            { value jv; BOOST_TEST((jv = tt<long long>{}).is_int64()); }
            { value jv; BOOST_TEST((jv = tt<unsigned char>{}).is_uint64()); }
            { value jv; BOOST_TEST((jv = tt<unsigned short>{}).is_uint64()); }
            { value jv; BOOST_TEST((jv = tt<unsigned int>{}).is_uint64()); }
            { value jv; BOOST_TEST((jv = tt<unsigned long>{}).is_uint64()); }
            { value jv; BOOST_TEST((jv = tt<unsigned long long>{}).is_uint64()); }
            { value jv; BOOST_TEST((jv = tt<float>{}).is_double()); }
            { value jv; BOOST_TEST((jv = tt<double>{}).is_double()); }
        }

        // bool
        {
            BOOST_TEST(value(true).is_bool());
            BOOST_TEST(value(false).is_bool());

            { value jv; BOOST_TEST((jv = true).is_bool()); }
            { value jv; BOOST_TEST((jv = false).is_bool()); }
        }

        // nullptr
        {
            BOOST_TEST(value(nullptr).is_null());

            { value jv("x"); BOOST_TEST((jv = nullptr).is_null()); }
        }

        // VFALCO TODO store()
    }

    void
    testObservers()
    {
        value const obj(object{});
        value const arr(array{});
        value const str(string{});
        value const i64(std::int64_t{});
        value const u64(std::uint64_t{});
        value const dub(double{});
        value const boo(true);
        value const nul(nullptr);

        // kind()
        {
            BOOST_TEST(obj.kind() == kind::object);
            BOOST_TEST(arr.kind() == kind::array);
            BOOST_TEST(str.kind() == kind::string);
            BOOST_TEST(i64.kind() == kind::int64);
            BOOST_TEST(u64.kind() == kind::uint64);
            BOOST_TEST(dub.kind() == kind::double_);
            BOOST_TEST(boo.kind() == kind::bool_);
            BOOST_TEST(nul.kind() == kind::null);
        }

        // is_object()
        {
            BOOST_TEST(  obj.is_object());
            BOOST_TEST(! arr.is_object());
            BOOST_TEST(! str.is_object());
            BOOST_TEST(! i64.is_object());
            BOOST_TEST(! u64.is_object());
            BOOST_TEST(! dub.is_object());
            BOOST_TEST(! boo.is_object());
            BOOST_TEST(! nul.is_object());
        }

        // is_array()
        {
            BOOST_TEST(! obj.is_array());
            BOOST_TEST(  arr.is_array());
            BOOST_TEST(! str.is_array());
            BOOST_TEST(! i64.is_array());
            BOOST_TEST(! u64.is_array());
            BOOST_TEST(! dub.is_array());
            BOOST_TEST(! boo.is_array());
            BOOST_TEST(! nul.is_array());
        }

        // is_string()
        {
            BOOST_TEST(! obj.is_string());
            BOOST_TEST(! arr.is_string());
            BOOST_TEST(  str.is_string());
            BOOST_TEST(! i64.is_string());
            BOOST_TEST(! u64.is_string());
            BOOST_TEST(! dub.is_string());
            BOOST_TEST(! boo.is_string());
            BOOST_TEST(! nul.is_string());
        }

        // is_int64()
        {
            BOOST_TEST(! obj.is_int64());
            BOOST_TEST(! arr.is_int64());
            BOOST_TEST(! str.is_int64());
            BOOST_TEST(  i64.is_int64());
            BOOST_TEST(! u64.is_int64());
            BOOST_TEST(! dub.is_int64());
            BOOST_TEST(! boo.is_int64());
            BOOST_TEST(! nul.is_int64());
        }

        // is_uint64()
        {
            BOOST_TEST(! obj.is_uint64());
            BOOST_TEST(! arr.is_uint64());
            BOOST_TEST(! str.is_uint64());
            BOOST_TEST(! i64.is_uint64());
            BOOST_TEST(  u64.is_uint64());
            BOOST_TEST(! dub.is_uint64());
            BOOST_TEST(! boo.is_uint64());
            BOOST_TEST(! nul.is_uint64());
        }

        // is_double()
        {
            BOOST_TEST(! obj.is_double());
            BOOST_TEST(! arr.is_double());
            BOOST_TEST(! str.is_double());
            BOOST_TEST(! i64.is_double());
            BOOST_TEST(! u64.is_double());
            BOOST_TEST(  dub.is_double());
            BOOST_TEST(! boo.is_double());
            BOOST_TEST(! nul.is_double());
        }

        // is_bool()
        {
            BOOST_TEST(! obj.is_bool());
            BOOST_TEST(! arr.is_bool());
            BOOST_TEST(! str.is_bool());
            BOOST_TEST(! i64.is_bool());
            BOOST_TEST(! u64.is_bool());
            BOOST_TEST(! dub.is_bool());
            BOOST_TEST(  boo.is_bool());
            BOOST_TEST(! nul.is_bool());
        }

        // is_null()
        {
            BOOST_TEST(! obj.is_null());
            BOOST_TEST(! arr.is_null());
            BOOST_TEST(! str.is_null());
            BOOST_TEST(! i64.is_null());
            BOOST_TEST(! u64.is_null());
            BOOST_TEST(! dub.is_null());
            BOOST_TEST(! boo.is_null());
            BOOST_TEST(  nul.is_null());
        }

        // is_number()
        {
            BOOST_TEST(! obj.is_number());
            BOOST_TEST(! arr.is_number());
            BOOST_TEST(! str.is_number());
            BOOST_TEST(  i64.is_number());
            BOOST_TEST(  u64.is_number());
            BOOST_TEST(  dub.is_number());
            BOOST_TEST(! boo.is_number());
            BOOST_TEST(! nul.is_number());
        }

        // is_primitive()
        {
            BOOST_TEST(! obj.is_primitive());
            BOOST_TEST(! arr.is_primitive());
            BOOST_TEST(  str.is_primitive());
            BOOST_TEST(  i64.is_primitive());
            BOOST_TEST(  u64.is_primitive());
            BOOST_TEST(  dub.is_primitive());
            BOOST_TEST(  boo.is_primitive());
            BOOST_TEST(  nul.is_primitive());
        }

        // is_structured()
        {
            BOOST_TEST(  obj.is_structured());
            BOOST_TEST(  arr.is_structured());
            BOOST_TEST(! str.is_structured());
            BOOST_TEST(! i64.is_structured());
            BOOST_TEST(! u64.is_structured());
            BOOST_TEST(! dub.is_structured());
            BOOST_TEST(! boo.is_structured());
            BOOST_TEST(! nul.is_structured());
        }
    }

    //------------------------------------------------------
    //
    // Accessors
    //
    //------------------------------------------------------

    void
    testGetStorage()
    {
        auto const sp =
            make_shared_resource<unique_resource>();

        value obj(object{}, sp);
        value arr(array{}, sp);
        value str(string{}, sp);
        value i64(std::int64_t{}, sp);
        value u64(std::uint64_t{}, sp);
        value dub(double{}, sp);
        value boo(true, sp);
        value nul(nullptr, sp);

        // storage()
        {
            BOOST_TEST(*obj.storage() == *sp);
            BOOST_TEST(*arr.storage() == *sp);
            BOOST_TEST(*str.storage() == *sp);
            BOOST_TEST(*i64.storage() == *sp);
            BOOST_TEST(*u64.storage() == *sp);
            BOOST_TEST(*dub.storage() == *sp);
            BOOST_TEST(*boo.storage() == *sp);
            BOOST_TEST(*nul.storage() == *sp);
        }
    }

    void
    testIf()
    {
        value obj(object{});
        value arr(array{});
        value str(string{});
        value i64(std::int64_t{});
        value u64(std::uint64_t{});
        value dub(double{});
        value boo(true);
        value nul(nullptr);

        auto const& cobj(obj);
        auto const& carr(arr);
        auto const& cstr(str);
        auto const& ci64(i64);
        auto const& cu64(u64);
        auto const& cdub(dub);
        auto const& cboo(boo);
        auto const& cnul(nul);

        // if_object()
        {
            BOOST_TEST(obj.if_object() != nullptr);
            BOOST_TEST(arr.if_object() == nullptr);
            BOOST_TEST(str.if_object() == nullptr);
            BOOST_TEST(i64.if_object() == nullptr);
            BOOST_TEST(u64.if_object() == nullptr);
            BOOST_TEST(dub.if_object() == nullptr);
            BOOST_TEST(boo.if_object() == nullptr);
            BOOST_TEST(nul.if_object() == nullptr);
        }

        // if_object() const
        {
            BOOST_TEST(cobj.if_object() != nullptr);
            BOOST_TEST(carr.if_object() == nullptr);
            BOOST_TEST(cstr.if_object() == nullptr);
            BOOST_TEST(ci64.if_object() == nullptr);
            BOOST_TEST(cu64.if_object() == nullptr);
            BOOST_TEST(cdub.if_object() == nullptr);
            BOOST_TEST(cboo.if_object() == nullptr);
            BOOST_TEST(cnul.if_object() == nullptr);
        }

        // if_array()
        {
            BOOST_TEST(obj.if_array() == nullptr);
            BOOST_TEST(arr.if_array() != nullptr);
            BOOST_TEST(str.if_array() == nullptr);
            BOOST_TEST(i64.if_array() == nullptr);
            BOOST_TEST(u64.if_array() == nullptr);
            BOOST_TEST(dub.if_array() == nullptr);
            BOOST_TEST(boo.if_array() == nullptr);
            BOOST_TEST(nul.if_array() == nullptr);
        }

        // if_array() const
        {
            BOOST_TEST(cobj.if_array() == nullptr);
            BOOST_TEST(carr.if_array() != nullptr);
            BOOST_TEST(cstr.if_array() == nullptr);
            BOOST_TEST(ci64.if_array() == nullptr);
            BOOST_TEST(cu64.if_array() == nullptr);
            BOOST_TEST(cdub.if_array() == nullptr);
            BOOST_TEST(cboo.if_array() == nullptr);
            BOOST_TEST(cnul.if_array() == nullptr);
        }

        // if_string()
        {
            BOOST_TEST(obj.if_string() == nullptr);
            BOOST_TEST(arr.if_string() == nullptr);
            BOOST_TEST(str.if_string() != nullptr);
            BOOST_TEST(i64.if_string() == nullptr);
            BOOST_TEST(u64.if_string() == nullptr);
            BOOST_TEST(dub.if_string() == nullptr);
            BOOST_TEST(boo.if_string() == nullptr);
            BOOST_TEST(nul.if_string() == nullptr);
        }

        // if_string() const
        {
            BOOST_TEST(cobj.if_string() == nullptr);
            BOOST_TEST(carr.if_string() == nullptr);
            BOOST_TEST(cstr.if_string() != nullptr);
            BOOST_TEST(ci64.if_string() == nullptr);
            BOOST_TEST(cu64.if_string() == nullptr);
            BOOST_TEST(cdub.if_string() == nullptr);
            BOOST_TEST(cboo.if_string() == nullptr);
            BOOST_TEST(cnul.if_string() == nullptr);
        }

        // if_int64()
        {
            BOOST_TEST(obj.if_int64() == nullptr);
            BOOST_TEST(arr.if_int64() == nullptr);
            BOOST_TEST(str.if_int64() == nullptr);
            BOOST_TEST(i64.if_int64() != nullptr);
            BOOST_TEST(u64.if_int64() == nullptr);
            BOOST_TEST(dub.if_int64() == nullptr);
            BOOST_TEST(boo.if_int64() == nullptr);
            BOOST_TEST(nul.if_int64() == nullptr);
        }

        // if_int64() const
        {
            BOOST_TEST(cobj.if_int64() == nullptr);
            BOOST_TEST(carr.if_int64() == nullptr);
            BOOST_TEST(cstr.if_int64() == nullptr);
            BOOST_TEST(ci64.if_int64() != nullptr);
            BOOST_TEST(cu64.if_int64() == nullptr);
            BOOST_TEST(cdub.if_int64() == nullptr);
            BOOST_TEST(cboo.if_int64() == nullptr);
            BOOST_TEST(cnul.if_int64() == nullptr);
        }

        // if_uint64()
        {
            BOOST_TEST(obj.if_uint64() == nullptr);
            BOOST_TEST(arr.if_uint64() == nullptr);
            BOOST_TEST(str.if_uint64() == nullptr);
            BOOST_TEST(i64.if_uint64() == nullptr);
            BOOST_TEST(u64.if_uint64() != nullptr);
            BOOST_TEST(dub.if_uint64() == nullptr);
            BOOST_TEST(boo.if_uint64() == nullptr);
            BOOST_TEST(nul.if_uint64() == nullptr);
        }

        // if_uint64() const
        {
            BOOST_TEST(cobj.if_uint64() == nullptr);
            BOOST_TEST(carr.if_uint64() == nullptr);
            BOOST_TEST(cstr.if_uint64() == nullptr);
            BOOST_TEST(ci64.if_uint64() == nullptr);
            BOOST_TEST(cu64.if_uint64() != nullptr);
            BOOST_TEST(cdub.if_uint64() == nullptr);
            BOOST_TEST(cboo.if_uint64() == nullptr);
            BOOST_TEST(cnul.if_uint64() == nullptr);
        }

        // if_double()
        {
            BOOST_TEST(obj.if_double() == nullptr);
            BOOST_TEST(arr.if_double() == nullptr);
            BOOST_TEST(str.if_double() == nullptr);
            BOOST_TEST(i64.if_double() == nullptr);
            BOOST_TEST(u64.if_double() == nullptr);
            BOOST_TEST(dub.if_double() != nullptr);
            BOOST_TEST(boo.if_double() == nullptr);
            BOOST_TEST(nul.if_double() == nullptr);
        }

        // if_double() const
        {
            BOOST_TEST(cobj.if_double() == nullptr);
            BOOST_TEST(carr.if_double() == nullptr);
            BOOST_TEST(cstr.if_double() == nullptr);
            BOOST_TEST(ci64.if_double() == nullptr);
            BOOST_TEST(cu64.if_double() == nullptr);
            BOOST_TEST(cdub.if_double() != nullptr);
            BOOST_TEST(cboo.if_double() == nullptr);
            BOOST_TEST(cnul.if_double() == nullptr);
        }

        // if_bool()
        {
            BOOST_TEST(obj.if_bool() == nullptr);
            BOOST_TEST(arr.if_bool() == nullptr);
            BOOST_TEST(str.if_bool() == nullptr);
            BOOST_TEST(i64.if_bool() == nullptr);
            BOOST_TEST(u64.if_bool() == nullptr);
            BOOST_TEST(dub.if_bool() == nullptr);
            BOOST_TEST(boo.if_bool() != nullptr);
            BOOST_TEST(nul.if_bool() == nullptr);
        }

        // if_bool() const
        {
            BOOST_TEST(cobj.if_bool() == nullptr);
            BOOST_TEST(carr.if_bool() == nullptr);
            BOOST_TEST(cstr.if_bool() == nullptr);
            BOOST_TEST(ci64.if_bool() == nullptr);
            BOOST_TEST(cu64.if_bool() == nullptr);
            BOOST_TEST(cdub.if_bool() == nullptr);
            BOOST_TEST(cboo.if_bool() != nullptr);
            BOOST_TEST(cnul.if_bool() == nullptr);
        }
    }

    void
    testToNumber()
    {
#define EQAL(T) BOOST_TEST(jv.to_number<T>() == V)
#define EQUS(T) BOOST_TEST((V >= 0) && jv.to_number<T>() == static_cast<std::uint64_t>(V))
#define EQUF(T) BOOST_TEST(static_cast<float>(V) == static_cast<float>(jv.to_number<T>()))
#define THRO(T) BOOST_TEST_THROWS_WITH_LOCATION(jv.to_number<T>());

        BOOST_TEST_THROWS_WITH_LOCATION(value(nullptr).to_number<int>());
        BOOST_TEST_THROWS_WITH_LOCATION(value(false).to_number<int>());
        BOOST_TEST_THROWS_WITH_LOCATION(value(string_kind).to_number<int>());
        BOOST_TEST_THROWS_WITH_LOCATION(value(array_kind).to_number<int>());
        BOOST_TEST_THROWS_WITH_LOCATION(value(object_kind).to_number<int>());

        BOOST_TEST_THROWS_WITH_LOCATION(value(nullptr).to_number<unsigned>());
        BOOST_TEST_THROWS_WITH_LOCATION(value(false).to_number<unsigned>());
        BOOST_TEST_THROWS_WITH_LOCATION(value(string_kind).to_number<unsigned>());
        BOOST_TEST_THROWS_WITH_LOCATION(value(array_kind).to_number<unsigned>());
        BOOST_TEST_THROWS_WITH_LOCATION(value(object_kind).to_number<unsigned>());

        BOOST_TEST_THROWS_WITH_LOCATION(value(nullptr).to_number<double>());
        BOOST_TEST_THROWS_WITH_LOCATION(value(false).to_number<double>());
        BOOST_TEST_THROWS_WITH_LOCATION(value(string_kind).to_number<double>());
        BOOST_TEST_THROWS_WITH_LOCATION(value(array_kind).to_number<double>());
        BOOST_TEST_THROWS_WITH_LOCATION(value(object_kind).to_number<double>());

        {
            unsigned char V = 0;
            value const jv(V);
            EQAL(std::int8_t);
            EQAL(std::int16_t);
            EQAL(std::int32_t);
            EQAL(std::int64_t);
            EQAL(std::uint8_t);
            EQAL(std::uint16_t);
            EQAL(std::uint32_t);
            EQAL(std::uint64_t);
            EQAL(float);
            EQAL(double);
        }
        {
            auto V = max_of<std::int8_t>();
            value const jv(V);
            EQAL(std::int8_t);
            EQAL(std::int16_t);
            EQAL(std::int32_t);
            EQAL(std::int64_t);
            EQAL(std::uint8_t);
            EQAL(std::uint16_t);
            EQUS(std::uint32_t);
            EQUS(std::uint64_t);
            EQAL(float);
            EQAL(double);
        }
        {
            auto V = max_of<std::int16_t>();
            value const jv(V);
            THRO(std::int8_t);
            EQAL(std::int16_t);
            EQAL(std::int32_t);
            EQAL(std::int64_t);
            THRO(std::uint8_t);
            EQAL(std::uint16_t);
            EQUS(std::uint32_t);
            EQUS(std::uint64_t);
            EQAL(float);
            EQAL(double);
        }
        {
            auto V = max_of<std::int32_t>();
            value const jv(V);
            THRO(std::int8_t);
            THRO(std::int16_t);
            EQAL(std::int32_t);
            EQAL(std::int64_t);
            THRO(std::uint8_t);
            THRO(std::uint16_t);
            EQUS(std::uint32_t);
            EQUS(std::uint64_t);
            EQUF(float);
            EQAL(double);
        }
        {
            auto V = max_of<std::int64_t>();
            value const jv(V);
            THRO(std::int8_t);
            THRO(std::int16_t);
            THRO(std::int32_t);
            EQAL(std::int64_t);
            THRO(std::uint8_t);
            THRO(std::uint16_t);
            THRO(std::uint32_t);
            EQUS(std::uint64_t);
            EQUF(float);
            EQUF(double);
        }
        //---
        {
            auto V = max_of<std::uint8_t>();
            value const jv(V);
            THRO(std::int8_t);
            EQAL(std::int16_t);
            EQAL(std::int32_t);
            EQAL(std::int64_t);
            EQAL(std::uint8_t);
            EQAL(std::uint16_t);
            EQAL(std::uint32_t);
            EQAL(std::uint64_t);
            EQAL(float);
            EQAL(double);
        }
        {
            auto V = max_of<std::uint16_t>();
            value const jv(V);
            THRO(std::int8_t);
            THRO(std::int16_t);
            EQAL(std::int32_t);
            EQAL(std::int64_t);
            THRO(std::uint8_t);
            EQAL(std::uint16_t);
            EQAL(std::uint32_t);
            EQAL(std::uint64_t);
            EQAL(float);
            EQAL(double);
        }
        {
            auto V = max_of<std::uint32_t>();
            value const jv(V);
            THRO(std::int8_t);
            THRO(std::int16_t);
            THRO(std::int32_t);
            EQAL(std::int64_t);
            THRO(std::uint8_t);
            THRO(std::uint16_t);
            EQAL(std::uint32_t);
            EQAL(std::uint64_t);
            EQUF(float);
            EQAL(double);
        }
        {
            auto V = max_of<std::uint64_t>();
            value const jv(V);
            THRO(std::int8_t);
            THRO(std::int16_t);
            THRO(std::int32_t);
            THRO(std::int64_t);
            THRO(std::uint8_t);
            THRO(std::uint16_t);
            THRO(std::uint32_t);
            EQAL(std::uint64_t);
            EQUF(float);
            EQUF(double);
        }
        //---
        {
            auto V = min_of<std::int8_t>();
            value const jv(V);
            EQAL(std::int8_t);
            EQAL(std::int16_t);
            EQAL(std::int32_t);
            EQAL(std::int64_t);
            THRO(std::uint8_t);
            THRO(std::uint16_t);
            THRO(std::uint32_t);
            THRO(std::uint64_t);
            EQAL(float);
            EQAL(double);
        }
        {
            auto V = min_of<std::int16_t>();
            value const jv(V);
            THRO(std::int8_t);
            EQAL(std::int16_t);
            EQAL(std::int32_t);
            EQAL(std::int64_t);
            THRO(std::uint8_t);
            THRO(std::uint16_t);
            THRO(std::uint32_t);
            THRO(std::uint64_t);
            EQAL(float);
            EQAL(double);
        }
        {
            auto V = min_of<std::int32_t>();
            value const jv(V);
            THRO(std::int8_t);
            THRO(std::int16_t);
            EQAL(std::int32_t);
            EQAL(std::int64_t);
            THRO(std::uint8_t);
            THRO(std::uint16_t);
            THRO(std::uint32_t);
            THRO(std::uint64_t);
            EQUF(float);
            EQAL(double);
        }
        {
            auto V = min_of<std::int64_t>();
            value const jv(V);
            THRO(std::int8_t);
            THRO(std::int16_t);
            THRO(std::int32_t);
            EQAL(std::int64_t);
            THRO(std::uint8_t);
            THRO(std::uint16_t);
            THRO(std::uint32_t);
            THRO(std::uint64_t);
            EQUF(float);
            EQUF(double);
        }
        //---
        {
            auto V = double(1.5);
            value const jv(V);
            THRO(std::int8_t);
            THRO(std::int16_t);
            THRO(std::int32_t);
            THRO(std::int64_t);
            THRO(std::uint8_t);
            THRO(std::uint16_t);
            THRO(std::uint32_t);
            THRO(std::uint64_t);
            EQAL(float);
            EQAL(double);
        }
        {
            auto V = double(2.0);
            value const jv(V);
            EQAL(std::int8_t);
            EQAL(std::int16_t);
            EQAL(std::int32_t);
            EQAL(std::int64_t);
            EQAL(std::uint8_t);
            EQAL(std::uint16_t);
            EQAL(std::uint32_t);
            EQAL(std::uint64_t);
            EQAL(float);
            EQAL(double);
        }
        {
            auto V = double(-4.0);
            value const jv(V);
            EQAL(std::int8_t);
            EQAL(std::int16_t);
            EQAL(std::int32_t);
            EQAL(std::int64_t);
            THRO(std::uint8_t);
            THRO(std::uint16_t);
            THRO(std::uint32_t);
            THRO(std::uint64_t);
            EQAL(float);
            EQAL(double);
        }

        {
            system::error_code ec;
            value(nullptr).to_number<double>(ec);
            BOOST_TEST(ec == error::not_number);
            BOOST_TEST(ec.has_location());
        }

        {
            std::error_code ec;
            value(nullptr).to_number<double>(ec);
            BOOST_TEST(error::not_number == ec);
        }

        system::result<int> res = value(1).try_to_number<int>();
        BOOST_TEST( res.value() == 1 );

        BOOST_TEST_THROWS_WITH_LOCATION(
            value(object_kind).try_to_number<double>().value());
    }

    void
    testAs()
    {
        value obj(object{});
        value arr(array{});
        value str(string{});
        value i64(std::int64_t{});
        value u64(std::uint64_t{});
        value dub(double{});
        value boo(true);
        value nul(nullptr);

        auto const& cobj(obj);
        auto const& carr(arr);
        auto const& cstr(str);
        auto const& ci64(i64);
        auto const& cu64(u64);
        auto const& cdub(dub);
        auto const& cboo(boo);
        auto const& cnul(nul);

        // as_object() &
        {
            object& x = obj.as_object();
            BOOST_TEST_THROWS_WITH_LOCATION( arr.as_object() );
            BOOST_TEST_THROWS_WITH_LOCATION( str.as_object() );
            BOOST_TEST_THROWS_WITH_LOCATION( i64.as_object() );
            BOOST_TEST_THROWS_WITH_LOCATION( u64.as_object() );
            BOOST_TEST_THROWS_WITH_LOCATION( dub.as_object() );
            BOOST_TEST_THROWS_WITH_LOCATION( boo.as_object() );
            BOOST_TEST_THROWS_WITH_LOCATION( nul.as_object() );
            (void)x;
        }

        // as_object() const&
        {
            object const& x = cobj.as_object();
            BOOST_TEST_THROWS_WITH_LOCATION( carr.as_object() );
            BOOST_TEST_THROWS_WITH_LOCATION( cstr.as_object() );
            BOOST_TEST_THROWS_WITH_LOCATION( ci64.as_object() );
            BOOST_TEST_THROWS_WITH_LOCATION( cu64.as_object() );
            BOOST_TEST_THROWS_WITH_LOCATION( cdub.as_object() );
            BOOST_TEST_THROWS_WITH_LOCATION( cboo.as_object() );
            BOOST_TEST_THROWS_WITH_LOCATION( cnul.as_object() );
            (void)x;
        }

        // as_object() &&
        {
            object&& x = std::move(obj).as_object();
            BOOST_TEST_THROWS_WITH_LOCATION( std::move(arr).as_object() );
            BOOST_TEST_THROWS_WITH_LOCATION( std::move(str).as_object() );
            BOOST_TEST_THROWS_WITH_LOCATION( std::move(i64).as_object() );
            BOOST_TEST_THROWS_WITH_LOCATION( std::move(u64).as_object() );
            BOOST_TEST_THROWS_WITH_LOCATION( std::move(dub).as_object() );
            BOOST_TEST_THROWS_WITH_LOCATION( std::move(boo).as_object() );
            BOOST_TEST_THROWS_WITH_LOCATION( std::move(nul).as_object() );
            (void)x;
        }

        // try_as_object()
        {
            object& x = obj.try_as_object().value();
            BOOST_TEST( arr.try_as_object().has_error() );
            BOOST_TEST( str.try_as_object().has_error() );
            BOOST_TEST( i64.try_as_object().has_error() );
            BOOST_TEST( u64.try_as_object().has_error() );
            BOOST_TEST( dub.try_as_object().has_error() );
            BOOST_TEST( boo.try_as_object().has_error() );
            BOOST_TEST( nul.try_as_object().has_error() );
            (void)x;
        }

        // try_as_object() const
        {
#if defined(BOOST_GCC) && BOOST_GCC >= 130000
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wdangling-reference"
#endif
            object const& x = cobj.try_as_object().value();
#if defined(BOOST_GCC)
# pragma GCC diagnostic pop
#endif
            BOOST_TEST( carr.try_as_object().has_error() );
            BOOST_TEST( cstr.try_as_object().has_error() );
            BOOST_TEST( ci64.try_as_object().has_error() );
            BOOST_TEST( cu64.try_as_object().has_error() );
            BOOST_TEST( cdub.try_as_object().has_error() );
            BOOST_TEST( cboo.try_as_object().has_error() );
            BOOST_TEST( cnul.try_as_object().has_error() );
            (void)x;
        }

        // as_array() &
        {
            array& x = arr.as_array();
            BOOST_TEST_THROWS_WITH_LOCATION( obj.as_array() );
            BOOST_TEST_THROWS_WITH_LOCATION( str.as_array() );
            BOOST_TEST_THROWS_WITH_LOCATION( i64.as_array() );
            BOOST_TEST_THROWS_WITH_LOCATION( u64.as_array() );
            BOOST_TEST_THROWS_WITH_LOCATION( dub.as_array() );
            BOOST_TEST_THROWS_WITH_LOCATION( boo.as_array() );
            BOOST_TEST_THROWS_WITH_LOCATION( nul.as_array() );
            (void)x;
        }

        // as_array() const&
        {
            array const& x = carr.as_array();
            BOOST_TEST_THROWS_WITH_LOCATION( cobj.as_array() );
            BOOST_TEST_THROWS_WITH_LOCATION( cstr.as_array() );
            BOOST_TEST_THROWS_WITH_LOCATION( ci64.as_array() );
            BOOST_TEST_THROWS_WITH_LOCATION( cu64.as_array() );
            BOOST_TEST_THROWS_WITH_LOCATION( cdub.as_array() );
            BOOST_TEST_THROWS_WITH_LOCATION( cboo.as_array() );
            BOOST_TEST_THROWS_WITH_LOCATION( cnul.as_array() );
            (void)x;
        }

        // as_array() &&
        {
            BOOST_TEST_THROWS_WITH_LOCATION( std::move(obj).as_array() );
            array&& x = std::move(arr).as_array();
            BOOST_TEST_THROWS_WITH_LOCATION( std::move(str).as_array() );
            BOOST_TEST_THROWS_WITH_LOCATION( std::move(i64).as_array() );
            BOOST_TEST_THROWS_WITH_LOCATION( std::move(u64).as_array() );
            BOOST_TEST_THROWS_WITH_LOCATION( std::move(dub).as_array() );
            BOOST_TEST_THROWS_WITH_LOCATION( std::move(boo).as_array() );
            BOOST_TEST_THROWS_WITH_LOCATION( std::move(nul).as_array() );
            (void)x;
        }

        // try_as_array()
        {
            array& x = arr.try_as_array().value();
            BOOST_TEST( obj.try_as_array().has_error() );
            BOOST_TEST( str.try_as_array().has_error() );
            BOOST_TEST( i64.try_as_array().has_error() );
            BOOST_TEST( u64.try_as_array().has_error() );
            BOOST_TEST( dub.try_as_array().has_error() );
            BOOST_TEST( boo.try_as_array().has_error() );
            BOOST_TEST( nul.try_as_array().has_error() );
            (void)x;
        }

        // try_as_array() const
        {
#if defined(BOOST_GCC) && BOOST_GCC >= 130000
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wdangling-reference"
#endif
            array const& x = carr.try_as_array().value();
#if defined(BOOST_GCC)
# pragma GCC diagnostic pop
#endif
            BOOST_TEST( cobj.try_as_array().has_error() );
            BOOST_TEST( cstr.try_as_array().has_error() );
            BOOST_TEST( ci64.try_as_array().has_error() );
            BOOST_TEST( cu64.try_as_array().has_error() );
            BOOST_TEST( cdub.try_as_array().has_error() );
            BOOST_TEST( cboo.try_as_array().has_error() );
            BOOST_TEST( cnul.try_as_array().has_error() );
            (void)x;
        }

        // as_string() &
        {
            string& x = str.as_string();
            BOOST_TEST_THROWS_WITH_LOCATION( obj.as_string() );
            BOOST_TEST_THROWS_WITH_LOCATION( arr.as_string() );
            BOOST_TEST_THROWS_WITH_LOCATION( i64.as_string() );
            BOOST_TEST_THROWS_WITH_LOCATION( u64.as_string() );
            BOOST_TEST_THROWS_WITH_LOCATION( dub.as_string() );
            BOOST_TEST_THROWS_WITH_LOCATION( boo.as_string() );
            BOOST_TEST_THROWS_WITH_LOCATION( nul.as_string() );
            (void)x;
        }

        // as_string() const&
        {
            string const& x = cstr.as_string();
            BOOST_TEST_THROWS_WITH_LOCATION( cobj.as_string() );
            BOOST_TEST_THROWS_WITH_LOCATION( carr.as_string() );
            BOOST_TEST_THROWS_WITH_LOCATION( ci64.as_string() );
            BOOST_TEST_THROWS_WITH_LOCATION( cu64.as_string() );
            BOOST_TEST_THROWS_WITH_LOCATION( cdub.as_string() );
            BOOST_TEST_THROWS_WITH_LOCATION( cboo.as_string() );
            BOOST_TEST_THROWS_WITH_LOCATION( cnul.as_string() );
            (void)x;
        }

        // as_string() &&
        {
            BOOST_TEST_THROWS_WITH_LOCATION( std::move(obj).as_string() );
            BOOST_TEST_THROWS_WITH_LOCATION( std::move(arr).as_string() );
            string&& x = std::move(str).as_string();
            BOOST_TEST_THROWS_WITH_LOCATION( std::move(i64).as_string() );
            BOOST_TEST_THROWS_WITH_LOCATION( std::move(u64).as_string() );
            BOOST_TEST_THROWS_WITH_LOCATION( std::move(dub).as_string() );
            BOOST_TEST_THROWS_WITH_LOCATION( std::move(boo).as_string() );
            BOOST_TEST_THROWS_WITH_LOCATION( std::move(nul).as_string() );
            (void)x;
        }

        // try_as_string()
        {
            string& x = str.try_as_string().value();
            BOOST_TEST( obj.try_as_string().has_error() );
            BOOST_TEST( arr.try_as_string().has_error() );
            BOOST_TEST( i64.try_as_string().has_error() );
            BOOST_TEST( u64.try_as_string().has_error() );
            BOOST_TEST( dub.try_as_string().has_error() );
            BOOST_TEST( boo.try_as_string().has_error() );
            BOOST_TEST( nul.try_as_string().has_error() );
            (void)x;
        }

        // try_as_string() const
        {
#if defined(BOOST_GCC) && BOOST_GCC >= 130000
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wdangling-reference"
#endif
            string const& x = cstr.try_as_string().value();
#if defined(BOOST_GCC)
# pragma GCC diagnostic pop
#endif
            BOOST_TEST( cobj.try_as_string().has_error() );
            BOOST_TEST( carr.try_as_string().has_error() );
            BOOST_TEST( ci64.try_as_string().has_error() );
            BOOST_TEST( cu64.try_as_string().has_error() );
            BOOST_TEST( cdub.try_as_string().has_error() );
            BOOST_TEST( cboo.try_as_string().has_error() );
            BOOST_TEST( cnul.try_as_string().has_error() );
            (void)x;
        }

        // as_int64()
        {
            std::int64_t& x = i64.as_int64();
            BOOST_TEST_THROWS_WITH_LOCATION( obj.as_int64() );
            BOOST_TEST_THROWS_WITH_LOCATION( arr.as_int64() );
            BOOST_TEST_THROWS_WITH_LOCATION( str.as_int64() );
            BOOST_TEST_THROWS_WITH_LOCATION( u64.as_int64() );
            BOOST_TEST_THROWS_WITH_LOCATION( dub.as_int64() );
            BOOST_TEST_THROWS_WITH_LOCATION( boo.as_int64() );
            BOOST_TEST_THROWS_WITH_LOCATION( nul.as_int64() );
            (void)x;
        }

        // as_int64() const
        {
            std::int64_t const& x = ci64.as_int64();
            BOOST_TEST_THROWS_WITH_LOCATION( cobj.as_int64() );
            BOOST_TEST_THROWS_WITH_LOCATION( carr.as_int64() );
            BOOST_TEST_THROWS_WITH_LOCATION( cstr.as_int64() );
            BOOST_TEST_THROWS_WITH_LOCATION( cu64.as_int64() );
            BOOST_TEST_THROWS_WITH_LOCATION( cdub.as_int64() );
            BOOST_TEST_THROWS_WITH_LOCATION( cboo.as_int64() );
            BOOST_TEST_THROWS_WITH_LOCATION( cnul.as_int64() );
            (void)x;
        }

        // try_as_int64()
        {
            std::int64_t& x = i64.try_as_int64().value();
            BOOST_TEST( obj.try_as_int64().has_error() );
            BOOST_TEST( arr.try_as_int64().has_error() );
            BOOST_TEST( str.try_as_int64().has_error() );
            BOOST_TEST( u64.try_as_int64().has_error() );
            BOOST_TEST( dub.try_as_int64().has_error() );
            BOOST_TEST( boo.try_as_int64().has_error() );
            BOOST_TEST( nul.try_as_int64().has_error() );
            (void)x;
        }

        // as_int64() const
        {
            std::int64_t const& x = ci64.as_int64();
            BOOST_TEST( cobj.try_as_int64().has_error() );
            BOOST_TEST( carr.try_as_int64().has_error() );
            BOOST_TEST( cstr.try_as_int64().has_error() );
            BOOST_TEST( cu64.try_as_int64().has_error() );
            BOOST_TEST( cdub.try_as_int64().has_error() );
            BOOST_TEST( cboo.try_as_int64().has_error() );
            BOOST_TEST( cnul.try_as_int64().has_error() );
            (void)x;
        }

        // as_uint64()
        {
            std::uint64_t& x = u64.as_uint64();
            BOOST_TEST_THROWS_WITH_LOCATION( obj.as_uint64() );
            BOOST_TEST_THROWS_WITH_LOCATION( arr.as_uint64() );
            BOOST_TEST_THROWS_WITH_LOCATION( str.as_uint64() );
            BOOST_TEST_THROWS_WITH_LOCATION( i64.as_uint64() );
            BOOST_TEST_THROWS_WITH_LOCATION( dub.as_uint64() );
            BOOST_TEST_THROWS_WITH_LOCATION( boo.as_uint64() );
            BOOST_TEST_THROWS_WITH_LOCATION( nul.as_uint64() );
            (void)x;
        }

        // as_uint64() const
        {
            std::uint64_t const& x = cu64.as_uint64();
            BOOST_TEST_THROWS_WITH_LOCATION( cobj.as_uint64() );
            BOOST_TEST_THROWS_WITH_LOCATION( carr.as_uint64() );
            BOOST_TEST_THROWS_WITH_LOCATION( cstr.as_uint64() );
            BOOST_TEST_THROWS_WITH_LOCATION( ci64.as_uint64() );
            BOOST_TEST_THROWS_WITH_LOCATION( cdub.as_uint64() );
            BOOST_TEST_THROWS_WITH_LOCATION( cboo.as_uint64() );
            BOOST_TEST_THROWS_WITH_LOCATION( cnul.as_uint64() );
            (void)x;
        }

        // try_as_uint64()
        {
            std::uint64_t& x = u64.try_as_uint64().value();
            BOOST_TEST( obj.try_as_uint64().has_error() );
            BOOST_TEST( arr.try_as_uint64().has_error() );
            BOOST_TEST( str.try_as_uint64().has_error() );
            BOOST_TEST( i64.try_as_uint64().has_error() );
            BOOST_TEST( dub.try_as_uint64().has_error() );
            BOOST_TEST( boo.try_as_uint64().has_error() );
            BOOST_TEST( nul.try_as_uint64().has_error() );
            (void)x;
        }

        // try_as_uint64() const
        {
            std::uint64_t const& x = cu64.try_as_uint64().value();
            BOOST_TEST( cobj.try_as_uint64().has_error() );
            BOOST_TEST( carr.try_as_uint64().has_error() );
            BOOST_TEST( cstr.try_as_uint64().has_error() );
            BOOST_TEST( ci64.try_as_uint64().has_error() );
            BOOST_TEST( cdub.try_as_uint64().has_error() );
            BOOST_TEST( cboo.try_as_uint64().has_error() );
            BOOST_TEST( cnul.try_as_uint64().has_error() );
            (void)x;
        }

        // as_double()
        {
            double& x = dub.as_double();
            BOOST_TEST_THROWS_WITH_LOCATION( obj.as_double() );
            BOOST_TEST_THROWS_WITH_LOCATION( arr.as_double() );
            BOOST_TEST_THROWS_WITH_LOCATION( str.as_double() );
            BOOST_TEST_THROWS_WITH_LOCATION( i64.as_double() );
            BOOST_TEST_THROWS_WITH_LOCATION( u64.as_double() );
            BOOST_TEST_THROWS_WITH_LOCATION( boo.as_double() );
            BOOST_TEST_THROWS_WITH_LOCATION( nul.as_double() );
            (void)x;
        }

        // as_double() const
        {
            double const& x = cdub.as_double();
            BOOST_TEST_THROWS_WITH_LOCATION( cobj.as_double() );
            BOOST_TEST_THROWS_WITH_LOCATION( carr.as_double() );
            BOOST_TEST_THROWS_WITH_LOCATION( cstr.as_double() );
            BOOST_TEST_THROWS_WITH_LOCATION( ci64.as_double() );
            BOOST_TEST_THROWS_WITH_LOCATION( cu64.as_double() );
            BOOST_TEST_THROWS_WITH_LOCATION( cboo.as_double() );
            BOOST_TEST_THROWS_WITH_LOCATION( cnul.as_double() );
            (void)x;
        }

        // try_as_double()
        {
            double& x = dub.try_as_double().value();
            BOOST_TEST( obj.try_as_double().has_error() );
            BOOST_TEST( arr.try_as_double().has_error() );
            BOOST_TEST( str.try_as_double().has_error() );
            BOOST_TEST( i64.try_as_double().has_error() );
            BOOST_TEST( u64.try_as_double().has_error() );
            BOOST_TEST( boo.try_as_double().has_error() );
            BOOST_TEST( nul.try_as_double().has_error() );
            (void)x;
        }

        // try_as_double() const
        {
            double const& x = cdub.try_as_double().value();
            BOOST_TEST( cobj.try_as_double().has_error() );
            BOOST_TEST( carr.try_as_double().has_error() );
            BOOST_TEST( cstr.try_as_double().has_error() );
            BOOST_TEST( ci64.try_as_double().has_error() );
            BOOST_TEST( cu64.try_as_double().has_error() );
            BOOST_TEST( cboo.try_as_double().has_error() );
            BOOST_TEST( cnul.try_as_double().has_error() );
            (void)x;
        }

        // as_bool()
        {
            bool& x = boo.as_bool();
            BOOST_TEST_THROWS_WITH_LOCATION( obj.as_bool() );
            BOOST_TEST_THROWS_WITH_LOCATION( arr.as_bool() );
            BOOST_TEST_THROWS_WITH_LOCATION( str.as_bool() );
            BOOST_TEST_THROWS_WITH_LOCATION( i64.as_bool() );
            BOOST_TEST_THROWS_WITH_LOCATION( u64.as_bool() );
            BOOST_TEST_THROWS_WITH_LOCATION( dub.as_bool() );
            BOOST_TEST_THROWS_WITH_LOCATION( nul.as_bool() );
            (void)x;
        }

        // as_bool() const
        {
            bool const&x = cboo.as_bool();
            BOOST_TEST_THROWS_WITH_LOCATION( cobj.as_bool() );
            BOOST_TEST_THROWS_WITH_LOCATION( carr.as_bool() );
            BOOST_TEST_THROWS_WITH_LOCATION( cstr.as_bool() );
            BOOST_TEST_THROWS_WITH_LOCATION( ci64.as_bool() );
            BOOST_TEST_THROWS_WITH_LOCATION( cu64.as_bool() );
            BOOST_TEST_THROWS_WITH_LOCATION( cdub.as_bool() );
            BOOST_TEST_THROWS_WITH_LOCATION( cnul.as_bool() );
            (void)x;
        }

        // try_as_bool()
        {
            bool& x = boo.try_as_bool().value();
            BOOST_TEST( obj.try_as_bool().has_error() );
            BOOST_TEST( arr.try_as_bool().has_error() );
            BOOST_TEST( str.try_as_bool().has_error() );
            BOOST_TEST( i64.try_as_bool().has_error() );
            BOOST_TEST( u64.try_as_bool().has_error() );
            BOOST_TEST( dub.try_as_bool().has_error() );
            BOOST_TEST( nul.try_as_bool().has_error() );
            (void)x;
        }

        // try_as_bool() const
        {
            bool const&x = cboo.try_as_bool().value();
            BOOST_TEST( cobj.try_as_bool().has_error() );
            BOOST_TEST( carr.try_as_bool().has_error() );
            BOOST_TEST( cstr.try_as_bool().has_error() );
            BOOST_TEST( ci64.try_as_bool().has_error() );
            BOOST_TEST( cu64.try_as_bool().has_error() );
            BOOST_TEST( cdub.try_as_bool().has_error() );
            BOOST_TEST( cnul.try_as_bool().has_error() );
            (void)x;
        }

        // try_as_null
        {
            BOOST_TEST( cnul.try_as_null().value() == nullptr );
            BOOST_TEST_THROWS_WITH_LOCATION( cboo.try_as_null().value() );
        }
    }

    void
    testGet()
    {
        value obj(object{});
        value arr(array{});
        value str(string{});
        value i64(std::int64_t{});
        value u64(std::uint64_t{});
        value dub(double{});
        value boo(true);

        auto const& cobj(obj);
        auto const& carr(arr);
        auto const& cstr(str);
        auto const& ci64(i64);
        auto const& cu64(u64);
        auto const& cdub(dub);
        auto const& cboo(boo);

        // get_object() &
        // get_array() &
        // get_string() &
        // get_int64()
        // get_uint64()
        // get_double()
        // get_bool()
        {
            object&         xobj = obj.get_object();
            array&          xarr = arr.get_array();
            string&         xstr = str.get_string();
            std::int64_t&   xi64 = i64.get_int64();
            std::uint64_t&  xu64 = u64.get_uint64();
            double&         xdub = dub.get_double();
            bool&           xboo = boo.get_bool();

            (void)(xobj);
            (void)(xarr);
            (void)(xstr);
            (void)(xi64);
            (void)(xu64);
            (void)(xdub);
            (void)(xboo);
        }

        // get_object() const&
        // get_array() const&
        // get_string() const&
        // get_int64() const
        // get_uint64() const
        // get_double() const
        // get_bool() const
        {
            object const&   xobj = cobj.get_object();
            array const&    xarr = carr.get_array();
            string const&   xstr = cstr.get_string();
            std::int64_t
                const&      xi64 = ci64.get_int64();
            std::uint64_t
                const&      xu64 = cu64.get_uint64();
            double const&   xdub = cdub.get_double();
            bool const&     xboo = cboo.get_bool();

            (void)(xobj);
            (void)(xarr);
            (void)(xstr);
            (void)(xi64);
            (void)(xu64);
            (void)(xdub);
            (void)(xboo);
        }

        // get_object() &&
        // get_array() &&
        // get_string() &&
        {
            object&& xobj = std::move(obj).get_object();
            array&&  xarr = std::move(arr).get_array();
            string&& xstr = std::move(str).get_string();

            (void)(xobj);
            (void)(xarr);
            (void)(xstr);
        }
    }

    void
    testAt()
    {
        // object
        value jvo{{"k1", "value"}, {"k2", nullptr}};
        value const& cjvo = jvo;
        BOOST_TEST( cjvo.at("k1").as_string() == "value" );
        BOOST_TEST( cjvo.try_at("k1")->as_string() == "value" );

        jvo.at("k1") = {1, 2, 3};
        BOOST_TEST( cjvo.at("k1") == array({1, 2, 3}) );
        BOOST_TEST( *cjvo.try_at("k1") == array({1, 2, 3}) );

        auto&& elem1 = std::move(jvo).at("k1");
        BOOST_TEST( &elem1 == &jvo.at("k1") );
        BOOST_TEST( &elem1 == &*jvo.try_at("k1") );

        BOOST_TEST_THROWS_WITH_LOCATION( cjvo.at("null") );
        BOOST_TEST( cjvo.try_at("null").error() == error::out_of_range );

        // array
        value jva{true,2,"3"};
        value const& cjva = jva;
        BOOST_TEST( cjva.at(1).as_int64() == 2 );
        BOOST_TEST( cjva.try_at(1)->as_int64() == 2 );

        jva.at(1) = "item";
        BOOST_TEST( cjva.at(1) == "item" );
        BOOST_TEST( *cjva.try_at(1) == "item" );

        auto&& elem2 = std::move(jva).at(1);
        BOOST_TEST( &elem2 == &jva.at(1) );
        BOOST_TEST( &elem2 == &*jva.try_at(1) );

        BOOST_TEST_THROWS_WITH_LOCATION( value({false,2,false}).at(4) );
        BOOST_TEST_THROWS_WITH_LOCATION( value({false,2,"3"}).at(4) );
        BOOST_TEST_THROWS_WITH_LOCATION( value({false,false}).at(4) );
        BOOST_TEST_THROWS_WITH_LOCATION( value({false,2}).at(4) );
        BOOST_TEST_THROWS_WITH_LOCATION( value({false,2,"3",nullptr}).at(4) );
        BOOST_TEST_THROWS_WITH_LOCATION( value({2,false,"3"}).at(4) );
        BOOST_TEST_THROWS_WITH_LOCATION( value({true,2,"3"}).at(4) );

        BOOST_TEST(
            value({false,2,false}).try_at(4) == error::out_of_range );
        BOOST_TEST(
            value({false,2,"3"}).try_at(4) == error::out_of_range );
        BOOST_TEST(
            value({false,false}).try_at(4) == error::out_of_range );
        BOOST_TEST(
            value({false,2}).try_at(4) == error::out_of_range );
        BOOST_TEST(
            value({false,2,"3",nullptr}).try_at(4) == error::out_of_range );
        BOOST_TEST(
            value({2,false,"3"}).try_at(4) == error::out_of_range );
        BOOST_TEST(
            value({true,2,"3"}).try_at(4) == error::out_of_range );
    }

    //------------------------------------------------------

    void
    testKeyValuePair()
    {
        using kvp = key_value_pair;

        kvp v1("key", "value");
        kvp v2(v1);
        BOOST_TEST(v2.key() == "key");
        BOOST_TEST(
            v2.value().get_string() == "value");
        kvp v3(std::move(v2));
        BOOST_TEST(v3.key() == "key");
        BOOST_TEST(
            v3.value().get_string() == "value");
        BOOST_TEST(std::memcmp(
            v3.key_c_str(), "key\0", 4) == 0);

        BOOST_STATIC_ASSERT(std::tuple_size<key_value_pair>::value == 2);
        BOOST_TEST(get<0>(v3) == "key");
        BOOST_TEST(
            get<1>(v3).get_string() == "value");

        BOOST_STATIC_ASSERT(std::is_same<
            decltype(get<1>(std::declval<kvp>())), json::value&&>::value);

#if __cplusplus >= 201703L || (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)
        auto const [kc, vc] = v1;
        static_assert(std::is_same<decltype(kc), string_view const>::value);
        static_assert(std::is_same<decltype(vc), value const&>::value);
        BOOST_TEST(kc == "key");
        BOOST_TEST(&vc != &v1.value());

        auto& [kr, vr] = v1;
        static_assert(std::is_same<decltype(kr), string_view const>::value);
        static_assert(std::is_same<decltype(vr), value&>::value);
        BOOST_TEST(kr == "key");
        BOOST_TEST(&vr == &v1.value());

        auto const& [kcr, vcr] = v1;
        static_assert(std::is_same<decltype(kcr), string_view const>::value);
        static_assert(std::is_same<decltype(vcr), value const&>::value);
        BOOST_TEST(kcr == "key");
        BOOST_TEST(&vcr == &v1.value());

        const kvp v4("const key", "const value");
        auto& [ckr, cvr] = v4;
        static_assert(std::is_same<decltype(ckr), string_view const>::value);
        static_assert(std::is_same<decltype(cvr), value const&>::value);
        BOOST_TEST(ckr == "const key");
        BOOST_TEST(&cvr == &v4.value());
#endif
    }

    //------------------------------------------------------

    void
    testStdConstruction()
    {
        {
            value jv(std::string("test"));
        }
    }

    void
    testInitList()
    {
        {
            value jv1{};
            BOOST_TEST( jv1.is_null() );

            value jv2 = {};
            BOOST_TEST( jv2.is_null() );

            value jv3 = value{};
            BOOST_TEST( jv3.is_null() );
        }
        {
            value jv1{1, 2};
            BOOST_TEST(( jv1 == array{1,2} ));

            value jv2 = {1, 2};
            BOOST_TEST(( jv2 == array{1,2} ));

            value jv3 = value{1, 2};
            BOOST_TEST(( jv3 == array{1,2} ));

            value jv4{{1, 2}};
            BOOST_TEST(( jv4 == array{1,2} ));

            value jv5 = {{1, 2}};
            BOOST_TEST(( jv5 == array{1,2} ));

            value jv6 = value{{1, 2}};
            BOOST_TEST(( jv6 == array{1,2} ));
        }
        {
            value jv1{0};
            BOOST_TEST( jv1 == 0 );

            value jv2 = {0};
            BOOST_TEST( jv2 == 0 );

            value jv3 = value{0};
            BOOST_TEST( jv3 == 0 );

            value jv4{{0}};
            BOOST_TEST( jv4 == array{0} );

            value jv5 = {{0}};
            BOOST_TEST( jv5 == array{0} );

            value jv6 = value{{0}};
            BOOST_TEST( jv6 == array{0} );
        }

        check_array(value{0,0,0},               0, 0, 0);
        check_array(value{false,false,false},   false, false, false);
        check_array(value{false,2,false},       false, 2, false);
        check_array(value{false,2,"3"},         false, 2, "3");
        check_array(value{false,false},         false, false);
        check_array(value{false,2},             false, 2);
        check_array(value{false,2,"3",nullptr}, false, 2, "3", nullptr);
        check_array(value{2,false,"3"},         2, false, "3");
        check_array(value{true,2,"3"},          true, 2, "3");

        check_array({0,0,0},               0, 0, 0);
        check_array({false,false,false},   false, false, false);
        check_array({false,2,false},       false, 2, false);
        check_array({false,2,"3"},         false, 2, "3");
        check_array({false,false},         false, false);
        check_array({false,2},             false, 2);
        check_array({false,2,"3",nullptr}, false, 2, "3", nullptr);
        check_array({2,false,"3"},         2, false, "3");
        check_array({true,2,"3"},          true, 2, "3");
    }

    //------------------------------------------------------

    void
    testEquality()
    {
        BOOST_TEST(value(nullptr) == value(nullptr));
        BOOST_TEST(value(nullptr) != value(true));

        BOOST_TEST(value(false) == value(false));
        BOOST_TEST(value(true)  != value(false));
        BOOST_TEST(value(true)  != value(nullptr));

        BOOST_TEST(value( 1) == value( 1));
        BOOST_TEST(value( 1) != value( 2));
        BOOST_TEST(value(-1) == value(-1));
        BOOST_TEST(value(-1) != value(-2));
        BOOST_TEST(value(-1) != value( 2));
        BOOST_TEST(value( 1) == value( 1UL));
        BOOST_TEST(value( 1) != value( 2UL));
        BOOST_TEST(value(-1) != value( 1UL));
        BOOST_TEST(value(-1) != value(nullptr));

        BOOST_TEST(value(1UL) == value( 1UL));
        BOOST_TEST(value(1UL) != value( 2UL));
        BOOST_TEST(value(1UL) == value( 1));
        BOOST_TEST(value(1UL) != value(-1));
        BOOST_TEST(value(1UL) != value(nullptr));

        BOOST_TEST(value(1.5) == value(1.5));
        BOOST_TEST(value(1.5) != value(2.5));
        BOOST_TEST(value(1.5) != value(false));
        BOOST_TEST(value(2.0) != value(2));

        BOOST_TEST(value("abc") == value("abc"));
        BOOST_TEST(value("abc") != value("xyz"));
        BOOST_TEST(value("abc") != value("x"));
        BOOST_TEST(value("abc") != value(nullptr));

        BOOST_TEST(value({1,2,3}) == value({1,2,3}));
        BOOST_TEST(value({1,2,3}) != value({2,3,1}));
        BOOST_TEST(value({1,2,3}) != value({2,3,4}));
        BOOST_TEST(value({1,2,3}) != value(nullptr));
        BOOST_TEST(value({
            {"a",1}, {"b",2}, {"c",3} }) == value({
            {"a",1}, {"b",2}, {"c",3} }));
        BOOST_TEST(value({
            {"a",1}, {"b",2}, {"c",3} }) == value({
            {"c",3}, {"a",1}, {"b",2} }));
        BOOST_TEST(value({
            {"a",1}, {"b",2}, {"c",3} }) != value({
            {"b",1}, {"c",2}, {"d",3} }));
        BOOST_TEST(value({
            {"a",1}, {"b",2}, {"c",3} }) != value({
            {"a",2}, {"b",3}, {"c",4} }));
        BOOST_TEST(value({
            {"a",1}, {"b",2}, {"c",3} }) != value(nullptr));
    }

    void
    testHash()
    {
        BOOST_TEST(check_hash_equal(value(nullptr), value(nullptr)));
        BOOST_TEST(check_hash_equal(value(nullptr), value()));
        BOOST_TEST(check_hash_equal(value(nullptr), value{}));
        BOOST_TEST(expect_hash_not_equal(value(nullptr), value({})));
        BOOST_TEST(expect_hash_not_equal(value(nullptr), value({object()})));
        BOOST_TEST(expect_hash_not_equal(value(nullptr), value(true)));
        BOOST_TEST(expect_hash_not_equal(value(nullptr), value(false)));
        BOOST_TEST(expect_hash_not_equal(value(nullptr), value(0)));
        BOOST_TEST(expect_hash_not_equal(value(nullptr), value(0UL)));
        BOOST_TEST(expect_hash_not_equal(value(nullptr), value(0.0)));
        BOOST_TEST(expect_hash_not_equal(value(nullptr), value("")));

        BOOST_TEST(check_hash_equal(value(true), value(true)));
        BOOST_TEST(check_hash_equal(value(false), value(false)));
        BOOST_TEST(expect_hash_not_equal(value(false), value(true)));
        BOOST_TEST(expect_hash_not_equal(value(false), value(0)));
        BOOST_TEST(expect_hash_not_equal(value(false), value(0UL)));
        BOOST_TEST(expect_hash_not_equal(value(false), value(0.0)));
        BOOST_TEST(expect_hash_not_equal(value(true), value(1)));
        BOOST_TEST(expect_hash_not_equal(value(true), value(1UL)));
        BOOST_TEST(expect_hash_not_equal(value(true), value(1.0)));

        BOOST_TEST(check_hash_equal(value(2021), value(2021UL)));
        BOOST_TEST(expect_hash_not_equal(value(2021U), value(-2021)));
        BOOST_TEST(expect_hash_not_equal(value(2021UL), value(2021.0)));

        BOOST_TEST(expect_hash_not_equal(value({}), value({object()})));
        BOOST_TEST(expect_hash_not_equal(value({}), value("")));
        BOOST_TEST(expect_hash_not_equal(value({object()}), value("")));

        BOOST_TEST(check_hash_equal(
            value({{"a",1}, {"b",2}, {"c",3}}),
            value({{"b",2}, {"c",3}, {"a",1}})));
        BOOST_TEST(expect_hash_not_equal(
            value({{"a",1}, {"b",2}, {"c",3}}),
            value({{"b",2}, {"c",3}})));
        BOOST_TEST(check_hash_equal(
            value({"a", "b", 17}),
            value({"a", "b", 17U})));
        BOOST_TEST(expect_hash_not_equal(
            value({"a", "b", 17}),
            value({17, "a", "b"})));
        BOOST_TEST(expect_hash_not_equal(
            value({"a", "b"}),
            value({{"a", "b"}})));
    }

    void
    testIstream()
    {
        std::istringstream ss(
            R"({ "x": 1
               , "y": 2
               , "z": [77, null, true, "qwerty uiop"]
               }_12)");
        value jv;

        ss >> jv;
        BOOST_TEST( !!ss );
        BOOST_TEST((
            jv == value{
                {"x", 1},
                {"y", 2},
                {"z", {77, nullptr, true, "qwerty uiop"}}} ));

        // check we didn't consume any extra characters
        std::string s;
        std::getline(ss, s);
        BOOST_TEST( s == "_12" );

        ss.clear();
        ss.str("23");
        ss >> jv;
        BOOST_TEST( jv == 23 );

        ss.clear();
        ss.str("");
        ss >> jv;
        BOOST_TEST( jv == 23 );
        BOOST_TEST( ss.rdstate() == (std::ios::failbit | std::ios::eofbit) );

        ss.clear();
        ss.str("nu");
        ss >> jv;
        BOOST_TEST( jv == 23 );
        BOOST_TEST( ss.rdstate() == (std::ios::failbit | std::ios::eofbit) );

        ss.clear();
        ss.str("[1,2,3,4,]");
        ss >> jv;
        BOOST_TEST( jv == 23 );
        BOOST_TEST( ss.rdstate() == std::ios::failbit );

        {
            throwing_buffer buf;
            std::istream is(&buf);
            is >> jv;
            BOOST_TEST( jv == 23 );
            BOOST_TEST( is.rdstate() & std::ios::badbit );
        }
        {
            throwing_buffer buf;
            std::istream is(&buf);
            is.exceptions(std::ios::badbit);
            BOOST_TEST_THROWS( is >> jv, std::invalid_argument );
            BOOST_TEST( jv == 23 );
            BOOST_TEST( is.rdstate() & std::ios::badbit );
        }

        s = "[1,2,3,4, // here goes EOL\n"
            "  [5,6,7, // and another one\n"
            "    [8,9]]]";

        parse_options opts;
        opts.max_depth = 2;
        opts.allow_comments = true;
        ss.clear();
        ss.str(s);
        ss >> opts >> jv;
        BOOST_TEST( ss.rdstate() == std::ios::failbit );

        ss.clear();
        ss.str(s);
        opts.max_depth = 3;
        ss >> opts >> jv;
        BOOST_TEST(( jv == value{1,2,3,4,{5,6,7,{8,9}}} ));

        ss.clear();
        ss.str( "[1,2,3,4,]" ); // trailing comma should fail
        ss >> opts >> jv;
        BOOST_TEST( ss.rdstate() == std::ios::failbit );
    }

    //------------------------------------------------------

    void
    run()
    {
        testSpecial();
        testConversion();
        testAssignment();
        testModifiers();
        testExchange();
        testObservers();
        testGetStorage();
        testIf();
        testToNumber();
        testAs();
        testGet();
        testAt();
        testKeyValuePair();
        testStdConstruction();
        testInitList();
        testEquality();
        testHash();
        testIstream();
    }
};

TEST_SUITE(value_test, "boost.json.value");

} // namespace json
} // namespace boost
