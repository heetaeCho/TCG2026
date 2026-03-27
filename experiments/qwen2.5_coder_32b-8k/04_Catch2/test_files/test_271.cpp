#include <gtest/gtest.h>

#include "catch_tostring.hpp"

#include "catch_reusable_string_stream.hpp"



namespace Catch {



TEST(StringMakerLongLongTest_271, ConvertPositiveValueBelowHexThreshold_271) {

    long long value = 100;

    std::string result = StringMaker<long long>::convert(value);

    EXPECT_EQ(result, "100");

}



TEST(StringMakerLongLongTest_271, ConvertNegativeValueBelowHexThreshold_271) {

    long long value = -100;

    std::string result = StringMaker<long long>::convert(value);

    EXPECT_EQ(result, "-100");

}



TEST(StringMakerLongLongTest_271, ConvertPositiveValueAtHexThreshold_271) {

    long long value = 255;

    std::string result = StringMaker<long long>::convert(value);

    EXPECT_EQ(result, "255 (0xff)");

}



TEST(StringMakerLongLongTest_271, ConvertNegativeValueAtHexThreshold_271) {

    long long value = -256;

    std::string result = StringMaker<long long>::convert(value);

    EXPECT_EQ(result, "-256");

}



TEST(StringMakerLongLongTest_271, ConvertPositiveValueAboveHexThreshold_271) {

    long long value = 256;

    std::string result = StringMaker<long long>::convert(value);

    EXPECT_EQ(result, "256 (0x100)");

}



TEST(StringMakerLongLongTest_271, ConvertNegativeValueAboveHexThreshold_271) {

    long long value = -257;

    std::string result = StringMaker<long long>::convert(value);

    EXPECT_EQ(result, "-257");

}



} // namespace Catch
