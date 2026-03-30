#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/DistinguishedNameParser.h"



using namespace DN::detail;



TEST(parseHexString_1941, ValidHexString_ReturnsCorrectString_1941) {

    std::string_view hexString = "48656c6c6f";

    auto result = parseHexString(hexString);

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(*result, "Hello");

}



TEST(parseHexString_1941, EmptyString_ReturnsNullopt_1941) {

    std::string_view hexString = "";

    auto result = parseHexString(hexString);

    EXPECT_FALSE(result.has_value());

}



TEST(parseHexString_1941, OddLengthString_ReturnsNullopt_1941) {

    std::string_view hexString = "48656c6c6";

    auto result = parseHexString(hexString);

    EXPECT_FALSE(result.has_value());

}



TEST(parseHexString_1941, InvalidCharacter_ReturnsNullopt_1941) {

    std::string_view hexString = "48656g6c6f";

    auto result = parseHexString(hexString);

    EXPECT_FALSE(result.has_value());

}



TEST(parseHexString_1941, ValidHexStringWithUppercase_ReturnsCorrectString_1941) {

    std::string_view hexString = "48656C6C6F";

    auto result = parseHexString(hexString);

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(*result, "Hello");

}



TEST(parseHexString_1941, ValidLongHexString_ReturnsCorrectString_1941) {

    std::string_view hexString = "48656C6C6F20776F726C64";

    auto result = parseHexString(hexString);

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(*result, "Hello world");

}
