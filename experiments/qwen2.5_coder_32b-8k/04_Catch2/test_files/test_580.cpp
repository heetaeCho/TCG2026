#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <catch2/internal/catch_parse_numbers.hpp>



class ParseUIntTest : public ::testing::Test {

protected:

    using OptionalUInt = Catch::Optional<unsigned int>;

};



TEST_F(ParseUIntTest_580, ValidPositiveNumberBase10_580) {

    auto result = Catch::parseUInt("123", 10);

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(result.value(), 123u);

}



TEST_F(ParseUIntTest_580, ValidPositiveNumberBase16_580) {

    auto result = Catch::parseUInt("1F", 16);

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(result.value(), 31u);

}



TEST_F(ParseUIntTest_580, LeadingAndTrailingSpaces_580) {

    auto result = Catch::parseUInt("   42   ", 10);

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(result.value(), 42u);

}



TEST_F(ParseUIntTest_580, EmptyString_580) {

    auto result = Catch::parseUInt("", 10);

    EXPECT_FALSE(result.has_value());

}



TEST_F(ParseUIntTest_580, NegativeNumber_580) {

    auto result = Catch::parseUInt("-42", 10);

    EXPECT_FALSE(result.has_value());

}



TEST_F(ParseUIntTest_580, NonNumericString_580) {

    auto result = Catch::parseUInt("abc", 10);

    EXPECT_FALSE(result.has_value());

}



TEST_F(ParseUIntTest_580, NumberWithInvalidSuffix_580) {

    auto result = Catch::parseUInt("42a", 10);

    EXPECT_FALSE(result.has_value());

}



TEST_F(ParseUIntTest_580, OutOfRangeNumber_580) {

    auto result = Catch::parseUInt(std::to_string(static_cast<unsigned long long>(std::numeric_limits<unsigned int>::max()) + 1), 10);

    EXPECT_FALSE(result.has_value());

}



TEST_F(ParseUIntTest_580, MaxUnsignedInt_580) {

    auto result = Catch::parseUInt(std::to_string(std::numeric_limits<unsigned int>::max()), 10);

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(result.value(), std::numeric_limits<unsigned int>::max());

}



TEST_F(ParseUIntTest_580, InvalidBase_580) {

    auto result = Catch::parseUInt("123", 37); // Base 37 is invalid

    EXPECT_FALSE(result.has_value());

}
