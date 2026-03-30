#include <gtest/gtest.h>

#include <yaml-cpp/src/fptostring.cpp>



namespace YAML {

    TEST(FpToStringTest_434, DefaultPrecision_434) {

        std::string result = FpToString(123.456L, 0);

        EXPECT_EQ(result, "123.456");

    }



    TEST(FpToStringTest_434, SpecifiedPrecision_434) {

        std::string result = FpToString(123.456789L, 5);

        EXPECT_EQ(result, "123.457");

    }



    TEST(FpToStringTest_434, ZeroValue_434) {

        std::string result = FpToString(0.0L, 2);

        EXPECT_EQ(result, "0.00");

    }



    TEST(FpToStringTest_434, NegativeValue_434) {

        std::string result = FpToString(-123.456L, 3);

        EXPECT_EQ(result, "-123.456");

    }



    TEST(FpToStringTest_434, LargePrecision_434) {

        std::string result = FpToString(123.456789012345L, 15);

        EXPECT_EQ(result, "123.456789012345");

    }



    TEST(FpToStringTest_434, MaxDigitsPrecision_434) {

        std::string result = FpToString(123.456789012345L, std::numeric_limits<long double>::max_digits10);

        EXPECT_TRUE(result.size() <= std::numeric_limits<long double>::max_digits10 + 1); // +1 for decimal point

    }

}
