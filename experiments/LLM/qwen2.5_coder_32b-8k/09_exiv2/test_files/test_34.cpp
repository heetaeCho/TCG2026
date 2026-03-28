#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/types.hpp"

#include <string>

#include <limits>



using namespace ::testing;



TEST(ToStringTest_34, IntegralType_Conversion_34) {

    int value = 123;

    std::string result = Exiv2::toString(value);

    EXPECT_EQ(result, "123");

}



TEST(ToStringTest_34, ZeroValue_Conversion_34) {

    int zero = 0;

    std::string result = Exiv2::toString(zero);

    EXPECT_EQ(result, "0");

}



TEST(ToStringTest_34, NegativeIntegralType_Conversion_34) {

    int negativeValue = -123;

    std::string result = Exiv2::toString(negativeValue);

    EXPECT_EQ(result, "-123");

}



TEST(ToStringTest_34, MaxIntValue_Conversion_34) {

    int maxValue = std::numeric_limits<int>::max();

    std::string result = Exiv2::toString(maxValue);

    EXPECT_EQ(result, std::to_string(std::numeric_limits<int>::max()));

}



TEST(ToStringTest_34, MinIntValue_Conversion_34) {

    int minValue = std::numeric_limits<int>::min();

    std::string result = Exiv2::toString(minValue);

    EXPECT_EQ(result, std::to_string(std::numeric_limits<int>::min()));

}



TEST(ToStringTest_34, UnsignedIntegralType_Conversion_34) {

    unsigned int value = 123;

    std::string result = Exiv2::toString(value);

    EXPECT_EQ(result, "123");

}



TEST(ToStringTest_34, MaxUnsignedIntValue_Conversion_34) {

    unsigned int maxValue = std::numeric_limits<unsigned int>::max();

    std::string result = Exiv2::toString(maxValue);

    EXPECT_EQ(result, std::to_string(std::numeric_limits<unsigned int>::max()));

}



TEST(ToStringTest_34, LongLongType_Conversion_34) {

    long long value = 123456789012345LL;

    std::string result = Exiv2::toString(value);

    EXPECT_EQ(result, "123456789012345");

}



TEST(ToStringTest_34, MaxLongLongValue_Conversion_34) {

    long long maxValue = std::numeric_limits<long long>::max();

    std::string result = Exiv2::toString(maxValue);

    EXPECT_EQ(result, std::to_string(std::numeric_limits<long long>::max()));

}



TEST(ToStringTest_34, MinLongLongValue_Conversion_34) {

    long long minValue = std::numeric_limits<long long>::min();

    std::string result = Exiv2::toString(minValue);

    EXPECT_EQ(result, std::to_string(std::numeric_limits<long long>::min()));

}



TEST(ToStringTest_34, UnsignedLongLongType_Conversion_34) {

    unsigned long long value = 123456789012345ULL;

    std::string result = Exiv2::toString(value);

    EXPECT_EQ(result, "123456789012345");

}



TEST(ToStringTest_34, MaxUnsignedLongLongValue_Conversion_34) {

    unsigned long long maxValue = std::numeric_limits<unsigned long long>::max();

    std::string result = Exiv2::toString(maxValue);

    EXPECT_EQ(result, std::to_string(std::numeric_limits<unsigned long long>::max()));

}
