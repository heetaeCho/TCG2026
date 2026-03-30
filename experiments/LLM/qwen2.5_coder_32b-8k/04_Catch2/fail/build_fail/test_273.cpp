#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/catch_tostring.hpp"



using namespace Catch;



TEST(StringMakerUnsignedLongTest_273, ConvertValidValue_ReturnsCorrectString_273) {

    unsigned long value = 123456789;

    std::string result = StringMaker<unsigned long>::convert(value);

    EXPECT_EQ(result, "123456789");

}



TEST(StringMakerUnsignedLongTest_273, ConvertZero_ReturnsCorrectString_273) {

    unsigned long value = 0;

    std::string result = StringMaker<unsigned long>::convert(value);

    EXPECT_EQ(result, "0");

}



TEST(StringMakerUnsignedLongTest_273, ConvertMaxValue_ReturnsCorrectString_273) {

    unsigned long value = ULONG_MAX;

    std::string result = StringMaker<unsigned long>::convert(value);

    EXPECT_EQ(result, std::to_string(ULONG_MAX));

}
