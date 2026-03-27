#include <gtest/gtest.h>

#include "TestProjects/exiv2/src/types.cpp"  // Assuming Rational is defined in this file or included here



namespace Exiv2 {

    struct Rational {

        int first;

        int second;

    };

}



TEST_F(RationalOutputTest_1133, NormalOperation_1133) {

    std::ostringstream oss;

    Exiv2::Rational r{3, 4};

    oss << r;

    EXPECT_EQ(oss.str(), "3/4");

}



TEST_F(RationalOutputTest_1133, ZeroNumerator_1133) {

    std::ostringstream oss;

    Exiv2::Rational r{0, 5};

    oss << r;

    EXPECT_EQ(oss.str(), "0/5");

}



TEST_F(RationalOutputTest_1133, NegativeNumerator_1133) {

    std::ostringstream oss;

    Exiv2::Rational r{-3, 4};

    oss << r;

    EXPECT_EQ(oss.str(), "-3/4");

}



TEST_F(RationalOutputTest_1133, NegativeDenominator_1133) {

    std::ostringstream oss;

    Exiv2::Rational r{3, -4};

    oss << r;

    EXPECT_EQ(oss.str(), "3/-4");

}



TEST_F(RationalOutputTest_1133, ZeroDenominator_1133) {

    std::ostringstream oss;

    Exiv2::Rational r{3, 0};

    oss << r;

    EXPECT_EQ(oss.str(), "3/0");  // Note: This is undefined behavior in math, but testing observable output

}



TEST_F(RationalOutputTest_1133, LargeValues_1133) {

    std::ostringstream oss;

    Exiv2::Rational r{123456789, 987654321};

    oss << r;

    EXPECT_EQ(oss.str(), "123456789/987654321");

}
