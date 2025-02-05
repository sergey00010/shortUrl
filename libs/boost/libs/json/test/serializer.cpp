//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

// Test that header file is self-contained.
#include <boost/json/serializer.hpp>

#include <boost/describe/class.hpp>
#include <boost/describe/enum.hpp>
#include <boost/json/detail/stack.hpp>
#include <boost/json/serialize.hpp>
#include <boost/json/null_resource.hpp>
#include <boost/json/parse.hpp>
#include <iostream>
#include <map>
#include <vector>
#include <limits.h>

#ifndef BOOST_NO_CXX17_HDR_FILESYSTEM
#include <filesystem>
#endif // BOOST_NO_CXX17_HDR_FILESYSTEM

#include "parse-vectors.hpp"
#include "test.hpp"
#include "test_suite.hpp"

namespace boost {
namespace json {
namespace serializer_test_ns {

struct my_struct
{
    std::string s;
    int n;
    double d;
};
BOOST_DESCRIBE_STRUCT(my_struct, (), (s, n, d));

enum class my_enum
{
    option_one,
    option_two,
    option_three,
    option_four,
};
BOOST_DESCRIBE_ENUM(my_enum, option_one, option_two, option_three);

} // namespace serializer_test_ns

BOOST_STATIC_ASSERT( std::is_nothrow_destructible<serializer>::value );

class serializer_test
{
public:
    //------------------------------------------------------

    // From the javadoc

    void print( std::ostream& os, value const& jv)
    {
        serializer sr;
        sr.reset( &jv );
        while( ! sr.done() )
        {
            char buf[ 4000 ];
            os << sr.read( buf );
        }
    }

    //------------------------------------------------------

    ::test_suite::log_type log;

    void
    grind_one(
        string_view s,
        value const& jv,
        string_view name = {})
    {
        {
            system::error_code ec;
            auto const s1 = serialize(jv);
            auto const jv2 = parse(s1, ec);
            if(! BOOST_TEST(equal(jv, jv2)))
            {
                if(name.empty())
                    log <<
                        " " << s << "\n"
                        " " << s1 <<
                        std::endl;
                else
                    log << name << ":\n"
                        " " << s << "\n"
                        " " << s1 <<
                        std::endl;
            }
        }

        // large buffer
        {
            system::error_code ec;
            serializer sr;
            sr.reset(&jv);
            string js;
            js.reserve(4096);
            js.grow(sr.read(
                js.data(), js.capacity()).size());

            auto const s1 = serialize(jv);
            auto const jv2 = parse(s1, ec);
            BOOST_TEST(equal(jv, jv2));
        }
    }

    template<class T>
    void
    grind_one(string_view s, T const& t, string_view name = {})
    {
        {
            auto const s1 = serialize(t);
            if( !BOOST_TEST(s == s1) )
            {
                if(name.empty())
                    log <<
                        " " << s << "\n"
                        " " << s1 <<
                        std::endl;
                else
                    log << name << ":\n"
                        " " << s << "\n"
                        " " << s1 <<
                        std::endl;
            }
        }

        // large buffer
        {
            serializer sr;
            sr.reset(&t);
            string js;
            js.reserve(4096);
            js.grow(sr.read(
                js.data(), js.capacity()).size());

            auto const s1 = serialize(t);
            BOOST_TEST( s == s1 );
        }
    }

    template<class T>
    void
    grind(
        string_view s0,
        T const& t,
        string_view name = {})
    {
        grind_one(s0, t, name);

        auto const s1 = serialize(t);
        for(std::size_t i = 1;
            i < s1.size(); ++i)
        {
            serializer sr;
            sr.reset(&t);
            string s2;
            s2.reserve(s1.size());
            s2.grow(sr.read(
                s2.data(), i).size());
            auto const dump =
            [&]
            {
                if(name.empty())
                    log <<
                        " " << s0 << "\n"
                        " " << s1 << "\n"
                        " " << s2 << std::endl;
                else
                    log << name << ":\n"
                        " " << s0 << "\n"
                        " " << s1 << "\n"
                        " " << s2 << std::endl;
            };
            if(! BOOST_TEST(
                s2.size() == i))
            {
                dump();
                break;
            }
            s2.grow(sr.read(
                s2.data() + i,
                s1.size() - i).size());
            if(! BOOST_TEST(
                s2.size() == s1.size()))
            {
                dump();
                break;
            }
            if(! BOOST_TEST(s2 == s1))
            {
                dump();
                break;
            }
        }
        {
            string s2;
            s2.reserve( s1.size() );
            serializer sr;
            sr.reset(&t);
            for(std::size_t i = 0; i < s1.size(); ++i)
            {
                BOOST_TEST( sr.read(s2.data() + i, 1).size() == 1 );
                s2.grow(1);
            }
            BOOST_TEST(s2 == s1);
        }
    }

    //------------------------------------------------------

    void
    testNull()
    {
        check("null");
    }

    void
    testBoolean()
    {
        check("true");
        check("false");
    }

    void
    testString()
    {
        check("\"\"");
        check("\"x\"");
        check("\"xyz\"");
        check("\"x z\"");

        // escapes
        check("\"\\\"\"");  // double quote
        check("\"\\\\\"");  // backslash
        check("\"\\b\"");   // backspace
        check("\"\\f\"");   // formfeed
        check("\"\\n\"");   // newline
        check("\"\\r\"");   // carriage return
        check("\"\\t\"");   // horizontal tab

        // control characters
        check("\"\\u0000\"");
        check("\"\\u0001\"");
        check("\"\\u0002\"");
        check("\"\\u0003\"");
        check("\"\\u0004\"");
        check("\"\\u0005\"");
        check("\"\\u0006\"");
        check("\"\\u0007\"");
        check("\"\\u0008\"");
        check("\"\\u0009\"");
        check("\"\\u000a\"");
        check("\"\\u000b\"");
        check("\"\\u000c\"");
        check("\"\\u000d\"");
        check("\"\\u000e\"");
        check("\"\\u000f\"");
        check("\"\\u0010\"");
        check("\"\\u0011\"");
        check("\"\\u0012\"");
        check("\"\\u0013\"");
        check("\"\\u0014\"");
        check("\"\\u0015\"");
        check("\"\\u0016\"");
        check("\"\\u0017\"");
        check("\"\\u0018\"");
        check("\"\\u0019\"");
        check("\"\\u0020\"");
        check("\"\\u0021\"");
    }

    void
    testNumber()
    {
        // VFALCO These don't perfectly round-trip,
        // because the representations are not exact.
        // The test needs to do a better job of comparison.

        check("-999999999999999999999");
        check("-100000000000000000009");
        check("-10000000000000000000");
        //check("-9223372036854775809");
        check("-9223372036854775808");
        check("-9223372036854775807");
        check("-999999999999999999");
        check("-99999999999999999");
        check("-9999999999999999");
        check("-999999999999999");
        check("-99999999999999");
        check("-9999999999999");
        check("-999999999999");
        check("-99999999999");
        check("-9999999999");
        check("-999999999");
        check("-99999999");
        check("-9999999");
        check("-999999");
        check("-99999");
        check("-9999");
        check("-999");
        check("-99");
        check("-9");
        check("-0");
        check("-0.0");
        check( "0");
        check( "9");
        check( "99");
        check( "999");
        check( "9999");
        check( "99999");
        check( "999999");
        check( "9999999");
        check( "99999999");
        check( "999999999");
        check( "9999999999");
        check( "99999999999");
        check( "999999999999");
        check( "9999999999999");
        check( "99999999999999");
        check( "999999999999999");
        check( "9999999999999999");
        check( "99999999999999999");
        check( "999999999999999999");
        check( "9223372036854775807");
        check( "9223372036854775808");
        check( "9999999999999999999");
        check( "18446744073709551615");
        //check( "18446744073709551616");
        check( "99999999999999999999");
        check( "999999999999999999999");
        check( "1000000000000000000000");
        check( "9999999999999999999999");
        check( "99999999999999999999999");

        //check("-0.9999999999999999999999");
        check("-0.9999999999999999");
        //check("-0.9007199254740991");
        //check("-0.999999999999999");
        //check("-0.99999999999999");
        //check("-0.9999999999999");
        //check("-0.999999999999");
        //check("-0.99999999999");
        //check("-0.9999999999");
        //check("-0.999999999");
        //check("-0.99999999");
        //check("-0.9999999");
        //check("-0.999999");
        //check("-0.99999");
        //check("-0.9999");
        //check("-0.8125");
        //check("-0.999");
        //check("-0.99");
        check("-1.0");
        check("-0.9");
        check("-0.0");
        check( "0.0");
        check( "0.9");
        //check( "0.99");
        //check( "0.999");
        //check( "0.8125");
        //check( "0.9999");
        //check( "0.99999");
        //check( "0.999999");
        //check( "0.9999999");
        //check( "0.99999999");
        //check( "0.999999999");
        //check( "0.9999999999");
        //check( "0.99999999999");
        //check( "0.999999999999");
        //check( "0.9999999999999");
        //check( "0.99999999999999");
        //check( "0.999999999999999");
        //check( "0.9007199254740991");
        check( "0.9999999999999999");
        //check( "0.9999999999999999999999");
        //check( "0.999999999999999999999999999");

        check("-1e308");
        check("-1e-308");
        //check("-9999e300");
        //check("-999e100");
        //check("-99e10");
        check("-9e1");
        check( "9e1");
        //check( "99e10");
        //check( "999e100");
        //check( "9999e300");
        check( "999999999999999999.0");
        check( "999999999999999999999.0");
        check( "999999999999999999999e5");
        check( "999999999999999999999.0e5");

        check("-1e-1");
        check("-1e0");
        check("-1e1");
        check( "0e0");
        check( "1e0");
        check( "1e10");
    }

    void
    testArray()
    {
        check("[]");
        check("[[]]");
        check("[[],[],[]]");
        check("[[[[[[[[[[]]]]]]]]]]");
        check("[{}]");
        check("[{},{}]");
        check("[1,2,3,4,5]");
        check("[true,false,null]");
    }

    void
    testObject()
    {
        check("{}");
        check("{\"x\":1}");
        check("{\"x\":[]}");
        check("{\"x\":1,\"y\":null}");
    }

    //------------------------------------------------------

    void
    testMembers()
    {
        // serializer()
        {
            serializer sr;

            char buf[32];
            BOOST_TEST(sr.read(buf) == "null");
        }

        // serializer(storage_ptr)
        {
            {
                serializer sr((storage_ptr()));
                char buf[32];
                BOOST_TEST(sr.read(buf) == "null");
            }
            {
                serializer sr(get_null_resource());
                char buf[1];
                BOOST_TEST_THROWS(
                    sr.read(buf),
                    std::bad_alloc);
            }
        }

        // serializer(storage_ptr, unsigned char*, size_t)
        {
            {
                unsigned char temp[256];
                serializer sr(
                    get_null_resource(),
                    temp,
                    sizeof(temp));
                char buf[32];
                BOOST_TEST(sr.read(&buf[0], 1) == "n");
                BOOST_TEST(sr.read(&buf[1], 2) == "ul");
                BOOST_TEST(sr.read(&buf[3], 1) == "l");
                BOOST_TEST(
                    std::memcmp(buf, "null", 4) == 0);
            }
            {
                unsigned char temp[1];
                serializer sr(
                    get_null_resource(),
                    temp,
                    sizeof(temp));
                array ar({1, 2, 3});
                sr.reset(&ar);
                char buf[32];
                BOOST_TEST_THROWS(
                    sr.read(&buf[0], 1),
                    std::bad_alloc);
            }
        }

        // done()
        {
            value jv = 1;
            serializer sr;
            sr.reset(&jv);
            BOOST_TEST(! sr.done());
            char buf[32];
            BOOST_TEST(sr.read(buf) == "1");
            BOOST_TEST(sr.done());
        }

        // read()
        {
            value jv = 1;
            serializer sr;
            sr.reset(&jv);
            char buf[1024];
            auto const s = sr.read(buf);
            BOOST_TEST(sr.done());
            BOOST_TEST(s == "1");
        }

        // checked read()
        {
            serializer sr;
            char buf[100];
            BOOST_TEST(sr.read(buf, 50) == "null");
        }

        // reset(value)
        {
            char buf[100];
            serializer sr;
            value jv = { 1, 2, 3 };
            sr.reset(&jv);
            BOOST_TEST(sr.read(buf) == "[1,2,3]");
        }

        // reset(array)
        {
            char buf[100];
            serializer sr;
            array arr = { 1, 2, 3 };
            sr.reset(&arr);
            BOOST_TEST(sr.read(buf) == "[1,2,3]");
        }

        // reset(object)
        {
            char buf[100];
            serializer sr;
            object obj = { {"k1",1}, {"k2",2} };
            sr.reset(&obj);
            BOOST_TEST(sr.read(buf) == "{\"k1\":1,\"k2\":2}");
        }

        // reset(string)
        {
            char buf[100];
            serializer sr;
            string str = "123";
            sr.reset(&str);
            BOOST_TEST(sr.read(buf) == "\"123\"");
        }
    }

    void
    check(
        string_view s,
        string_view name = {})
    {
        try
        {
            auto const jv = parse(s);
            grind(s, jv, name);
        }
        catch(std::exception const&)
        {
            BOOST_TEST_FAIL();
        }
    }

    template<class T>
    void
    check_udt(
        T const& t,
        string_view s,
        string_view name = {})
    {
        try
        {
            grind(s, t, name);
        }
        catch(std::exception const&)
        {
            BOOST_TEST_FAIL();
        }
    }

    void
    testVectors()
    {
#if 0
        check(
            R"xx({
                "glossary": {
                    "title": "example glossary",
		            "GlossDiv": {
                        "title": "S",
			            "GlossList": {
                            "GlossEntry": {
                                "ID": "SGML",
					            "SortAs": "SGML",
					            "GlossTerm": "Standard Generalized Markup Language",
					            "Acronym": "SGML",
					            "Abbrev": "ISO 8879:1986",
					            "GlossDef": {
                                    "para": "A meta-markup language, used to create markup languages such as DocBook.",
						            "GlossSeeAlso": ["GML", "XML"]
                                },
					            "GlossSee": "markup"
                            }
                        }
                    }
                }
            })xx");
#endif

        parse_vectors const pv;
        for(auto const e : pv)
        {
            if(e.result != 'y')
                continue;
            // skip these failures for now
            if(
                e.name == "number" ||
                e.name == "number_real_exponent" ||
                e.name == "number_real_fraction_exponent" ||
                e.name == "number_simple_real" ||
                e.name == "object_extreme_numbers" ||
                e.name == "pass01"
                )
                continue;
            check(e.text, e.name);
        }
    }

    std::string
    to_ostream(value const& jv)
    {
        std::stringstream ss;
        ss << jv;
        return ss.str();
    }

    void
    testOstream()
    {
        for(string_view js : {
            "{\"1\":{},\"2\":[],\"3\":\"x\",\"4\":1,"
            "\"5\":-1,\"6\":144.0,\"7\":false,\"8\":null}",
            "[1,2,3,4,5]"
            })
        {
            system::error_code ec;
            auto const jv1 = parse(js, ec);
            if(! BOOST_TEST(! ec))
                return;
            auto const jv2 =
                parse(to_ostream(jv1), ec);
            if(! BOOST_TEST(! ec))
                return;
            if(! BOOST_TEST(equal(jv1, jv2)))
                log <<
                    " " << js << "\n"
                    " " << jv1 << "\n"
                    " " << jv2 <<
                    std::endl;
        }
    }

    void
    testNumberRoundTrips()
    {
        // no decimal or exponent parsed as integer
        BOOST_TEST(parse("-0").as_int64() == 0);
        BOOST_TEST(serialize(parse("-0")) == "0");
        BOOST_TEST(parse("-0.0").as_double() == -0);
        BOOST_TEST(serialize(parse("0.0")) == "0E0");
        BOOST_TEST(parse("0.0").as_double() == 0);
        BOOST_TEST(serialize(parse("-0.0")) == "-0E0");
    }

    void
    testStack()
    {
        char const* sample = "sample string";

        detail::stack st;
        BOOST_TEST( st.empty() );

        st.clear();
        BOOST_TEST( st.empty() );

        st.push(1);
        BOOST_TEST( !st.empty() );

        st.push(sample);
        st.push(3.4);

        std::vector<int> v{1, 2, 3, 4, 5};
        st.push(v);

        v.pop_back();
        st.push(v);

        v.pop_back();
        st.push(v);

        {
            std::vector<int> v1;
            st.pop( v1 );

            BOOST_TEST( v == v1 );
        }
        v.push_back(4);
        {
            std::vector<int> v1;
            st.pop( v1 );

            BOOST_TEST( v == v1 );
        }
        v.push_back(5);
        {
            std::vector<int> v1;
            st.pop( v1 );

            BOOST_TEST( v == v1 );
        }
        {
            double d1;
            st.peek( d1 );
            BOOST_TEST( d1 == 3.4 );

            double d2;
            st.pop( d2 );
            BOOST_TEST( d2 == d1 );
            BOOST_TEST( !st.empty() );
        }
        {
            char const* s1;
            st.peek( s1 );
            BOOST_TEST( s1 == sample );

            char const* s2;
            st.pop( s2 );
            BOOST_TEST( s2 == s1 );
            BOOST_TEST( !st.empty() );
        }
        {
            int n1;
            st.peek( n1 );
            BOOST_TEST( n1 == 1 );

            int n2;
            st.pop( n2 );
            BOOST_TEST( n2 == n1 );
            BOOST_TEST( st.empty() );
        }
        BOOST_TEST( st.empty() );

        st.push(1);
        st.push(v);
        st.clear();
        BOOST_TEST( st.empty() );
    }

    void
    testUDT()
    {
        {
            check_udt(nullptr, "null");

            auto np = nullptr;
            check_udt(np, "null");
        }
        {
            bool b = true;
            check_udt(b, "true");

            b = false;
            check_udt(b, "false");
        }
        {
            std::uint64_t u = 1;
            check_udt(u, "1");

            u = (std::numeric_limits<std::int64_t>::max)();
            u += 1;
            check_udt(u, "9223372036854775808");

            std::int64_t i = -1;
            check_udt(i, "-1");

            double d = 3.12;
            check_udt(d, "3.12E0");

#if defined(BOOST_HAS_INT128) && defined(__GLIBCXX_TYPE_INT_N_0)
            boost::int128_type ii =
                (std::numeric_limits<std::uint64_t>::max)();
            ii += 1;
            d = ii;
            check_udt( ii, serialize(value(d)) );

            ii = (std::numeric_limits<std::int64_t>::min)();
            ii -= 1;
            d = ii;
            check_udt( ii, serialize(value(d)) );
#endif
        }
        {
            std::string s = "fairly long string which avoids SBO";
            check_udt(s, "\"fairly long string which avoids SBO\"");
        }
        {
            std::vector<int> v = {1,2,3,4,5};
            check_udt(v, "[1,2,3,4,5]");
        }
        {
            std::map<std::string, int> v = {
                {"a", 1}, {"b", 2}, {"c", 3}, {"d", 4}, {"e", 5}};
            check_udt(v, R"({"a":1,"b":2,"c":3,"d":4,"e":5})");
        }
        {
            check_udt(
                std::tuple<std::string, int, bool>("a string", 12, true),
                R"(["a string",12,true])");
            check_udt(
                std::tuple<std::string, std::pair<int, bool>>(
                    "a string", {12, true}),
                R"(["a string",[12,true]])");
        }
#ifdef BOOST_DESCRIBE_CXX14
        {
            serializer_test_ns::my_struct s{"some string", 1424, 12.4};
            check_udt(s, R"({"s":"some string","n":1424,"d":1.24E1})");
        }
        {
            check_udt(
                serializer_test_ns::my_enum::option_three,
                R"("option_three")");
            check_udt( serializer_test_ns::my_enum(100), "100" );
        }
#endif // BOOST_DESCRIBE_CXX14
#ifndef BOOST_NO_CXX17_HDR_VARIANT
        {
            std::variant<int, std::string, double> v = 112;
            check_udt( v, "112" );

            v = 0.5;
            check_udt( v, "5E-1" );

            v = "this is a string";
            check_udt(v, R"("this is a string")");

            check_udt(std::monostate(), "null");
        }
#endif // BOOST_NO_CXX17_HDR_VARIANT
#ifndef BOOST_NO_CXX17_HDR_OPTIONAL
        {
            std::optional<int> o;
            check_udt( o, "null" );

            o = 2315;
            check_udt( o, "2315" );
        }
#endif // BOOST_NO_CXX17_HDR_OPTIONAL
#ifndef BOOST_NO_CXX17_HDR_FILESYSTEM
        {
            std::filesystem::path p = "from/here";
            check_udt(p, R"("from/here")");

            p = "to/there";
            check_udt(p, R"("to/there")");

            p = "";
            check_udt(p, R"("")");

            p = "c:/";
            check_udt(p, R"("c:/")");

            p = "..";
            check_udt(p, R"("..")");

            p = "../";
            check_udt(p, R"("../")");
        }
#endif // BOOST_NO_CXX17_HDR_FILESYSTEM
    }

    void
    run()
    {
        {
            serializer sr;
            BOOST_ASSERT( sr.read(nullptr, 0).empty() );
        }
        testNull();
        testBoolean();
        testString();
        testNumber();
        testArray();
        testObject();

        testMembers();
        testVectors();
        testOstream();
        testNumberRoundTrips();
        testStack();
        testUDT();
    }
};

TEST_SUITE(serializer_test, "boost.json.serializer");

} // namespace json
} // namespace boost
