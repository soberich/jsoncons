// Copyright 2016 Daniel Parker
// Distributed under Boost license

#if defined(_MSC_VER)
#include "windows.h" // test no inadvertant macro expansions
#endif
#include <jsoncons/json.hpp>
#include <jsoncons_ext/ubjson/ubjson.hpp>
#include <sstream>
#include <vector>
#include <utility>
#include <ctime>
#include <limits>
#include <catch/catch.hpp>
#include "test_utilities.hpp"

using namespace jsoncons;
using namespace jsoncons::ubjson;

void check_encode_ubjson(const std::vector<uint8_t>& expected, const std::vector<uint8_t>& result);

TEST_CASE("serialize array to ubjson")
{
    std::vector<uint8_t> v;
    ubjson_buffer_serializer serializer(v);
    serializer.begin_array(3);
    serializer.bool_value(true);
    serializer.bool_value(false);
    serializer.null_value();
    serializer.end_array();
    serializer.flush();

    try
    {
        json result = decode_ubjson<json>(v);
        std::cout << result << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
} 

TEST_CASE("Too many and too few items in UBJSON object or array")
{
    std::error_code ec{};
    std::vector<uint8_t> v;
    ubjson_buffer_serializer serializer(v);

    SECTION("Too many items in array")
    {
        CHECK(serializer.begin_array(3));
        CHECK(serializer.bool_value(true));
        CHECK(serializer.bool_value(false));
        CHECK(serializer.null_value());
        CHECK(serializer.begin_array(2));
        CHECK(serializer.string_value("cat"));
        CHECK(serializer.string_value("feline"));
        CHECK(serializer.end_array());
        REQUIRE_THROWS_WITH(serializer.end_array(), ubjson_error_category_impl().message((int)ubjson_errc::too_many_items).c_str());
        serializer.flush();
    }
    SECTION("Too few items in array")
    {
        CHECK(serializer.begin_array(5));
        CHECK(serializer.bool_value(true));
        CHECK(serializer.bool_value(false));
        CHECK(serializer.null_value());
        CHECK(serializer.begin_array(2));
        CHECK(serializer.string_value("cat"));
        CHECK(serializer.string_value("feline"));
        CHECK(serializer.end_array());
        REQUIRE_THROWS_WITH(serializer.end_array(), ubjson_error_category_impl().message((int)ubjson_errc::too_few_items).c_str());
        serializer.flush();
    }
    SECTION("Too many items in object")
    {
        CHECK(serializer.begin_object(3));
        CHECK(serializer.name("a"));
        CHECK(serializer.bool_value(true));
        CHECK(serializer.name("b"));
        CHECK(serializer.bool_value(false));
        CHECK(serializer.name("c"));
        CHECK(serializer.null_value());
        CHECK(serializer.name("d"));
        CHECK(serializer.begin_array(2));
        CHECK(serializer.string_value("cat"));
        CHECK(serializer.string_value("feline"));
        CHECK(serializer.end_array());
        REQUIRE_THROWS_WITH(serializer.end_object(), ubjson_error_category_impl().message((int)ubjson_errc::too_many_items).c_str());
        serializer.flush();
    }
    SECTION("Too few items in object")
    {
        CHECK(serializer.begin_object(5));
        CHECK(serializer.name("a"));
        CHECK(serializer.bool_value(true));
        CHECK(serializer.name("b"));
        CHECK(serializer.bool_value(false));
        CHECK(serializer.name("c"));
        CHECK(serializer.null_value());
        CHECK(serializer.name("d"));
        CHECK(serializer.begin_array(2));
        CHECK(serializer.string_value("cat"));
        CHECK(serializer.string_value("feline"));
        CHECK(serializer.end_array());
        REQUIRE_THROWS_WITH(serializer.end_object(), ubjson_error_category_impl().message((int)ubjson_errc::too_few_items).c_str());
        serializer.flush();
    }
}
/*
TEST_CASE("serialize to ubjson optimized format")
{
    std::vector<uint8_t> v;
    ubjson_buffer_serializer serializer(v);
    serializer.begin_array(3);
    serializer.int64_value(1);
    serializer.int64_value(-10);
    serializer.int64_value(100);
    serializer.end_array();
    serializer.flush();

    test_equal(v,{'[','$','i','#','U',3,1,0xf6,100});
} 
*/
