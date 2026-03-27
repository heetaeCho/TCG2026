#include <gtest/gtest.h>

#include "catch2/catch_tostring.hpp"



TEST(StringMakerUnsignedIntTest_272, NormalOperation_272) {

    unsigned int value = 42;

    std::string result = Catch::StringMaker<unsigned int>::convert(value);

    EXPECT_EQ(result, "42");

}



TEST(StringMakerUnsignedIntTest_272, BoundaryCondition_MaxValue_272) {

    unsigned int value = UINT_MAX;

    std::string result = Catch::StringMaker<unsigned int>::convert(value);

    EXPECT_EQ(result, "4294967295");

}



TEST(StringMakerUnsignedIntTest_272, BoundaryCondition_Zero_272) {

    unsigned int value = 0;

    std::string result = Catch::StringMaker<unsigned int>::convert(value);

    EXPECT_EQ(result, "0");

}
