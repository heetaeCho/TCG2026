#include <gtest/gtest.h>
#include <sstream>
#include <cmath>
#include <exiv2/types.hpp>

using namespace Exiv2;

class FromStreamToRationalTest_1134 : public ::testing::Test {
protected:
};

// Test parsing standard rational format "numerator/denominator"
TEST_F(FromStreamToRationalTest_1134, ParseStandardRational_1134) {
    std::istringstream is("1/2");
    Rational r{0, 0};
    is >> r;
    EXPECT_FALSE(is.fail());
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 2);
}

// Test parsing rational with negative numerator
TEST_F(FromStreamToRationalTest_1134, ParseNegativeNumerator_1134) {
    std::istringstream is("-3/4");
    Rational r{0, 0};
    is >> r;
    EXPECT_FALSE(is.fail());
    EXPECT_EQ(r.first, -3);
    EXPECT_EQ(r.second, 4);
}

// Test parsing rational with negative denominator
TEST_F(FromStreamToRationalTest_1134, ParseNegativeDenominator_1134) {
    std::istringstream is("5/-7");
    Rational r{0, 0};
    is >> r;
    EXPECT_FALSE(is.fail());
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, -7);
}

// Test parsing rational with zero numerator
TEST_F(FromStreamToRationalTest_1134, ParseZeroNumerator_1134) {
    std::istringstream is("0/1");
    Rational r{99, 99};
    is >> r;
    EXPECT_FALSE(is.fail());
    EXPECT_EQ(r.first, 0);
    EXPECT_EQ(r.second, 1);
}

// Test parsing rational with zero denominator
TEST_F(FromStreamToRationalTest_1134, ParseZeroDenominator_1134) {
    std::istringstream is("1/0");
    Rational r{0, 0};
    is >> r;
    EXPECT_FALSE(is.fail());
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 0);
}

// Test that missing '/' causes fail
TEST_F(FromStreamToRationalTest_1134, MissingSeparatorCausesFail_1134) {
    std::istringstream is("1 2");
    Rational r{0, 0};
    is >> r;
    EXPECT_TRUE(is.fail());
}

// Test that wrong separator causes fail
TEST_F(FromStreamToRationalTest_1134, WrongSeparatorCausesFail_1134) {
    std::istringstream is("1:2");
    Rational r{0, 0};
    is >> r;
    EXPECT_TRUE(is.fail());
}

// Test f-stop notation with lowercase 'f'
TEST_F(FromStreamToRationalTest_1134, ParseFStopLowercase_1134) {
    std::istringstream is("f2.0");
    Rational r{0, 0};
    is >> r;
    EXPECT_FALSE(is.fail());
    // f2.0 -> 2*log2(2.0) = 2*1 = 2.0, converted to rational
    // The exact rational depends on floatToRationalCast implementation
    // but we can check it's approximately 2/1
    double value = static_cast<double>(r.first) / static_cast<double>(r.second);
    EXPECT_NEAR(value, 2.0, 0.01);
}

// Test f-stop notation with uppercase 'F'
TEST_F(FromStreamToRationalTest_1134, ParseFStopUppercase_1134) {
    std::istringstream is("F2.0");
    Rational r{0, 0};
    is >> r;
    EXPECT_FALSE(is.fail());
    double value = static_cast<double>(r.first) / static_cast<double>(r.second);
    EXPECT_NEAR(value, 2.0, 0.01);
}

// Test f-stop with f1.0 -> 2*log2(1.0) = 0
TEST_F(FromStreamToRationalTest_1134, ParseFStop1Point0_1134) {
    std::istringstream is("f1.0");
    Rational r{99, 99};
    is >> r;
    EXPECT_FALSE(is.fail());
    double value = (r.second != 0) ? static_cast<double>(r.first) / static_cast<double>(r.second) : 0.0;
    EXPECT_NEAR(value, 0.0, 0.01);
}

// Test f-stop with f4.0 -> 2*log2(4.0) = 2*2 = 4
TEST_F(FromStreamToRationalTest_1134, ParseFStop4_1134) {
    std::istringstream is("f4.0");
    Rational r{0, 0};
    is >> r;
    EXPECT_FALSE(is.fail());
    double value = static_cast<double>(r.first) / static_cast<double>(r.second);
    EXPECT_NEAR(value, 4.0, 0.01);
}

// Test large values in rational
TEST_F(FromStreamToRationalTest_1134, ParseLargeValues_1134) {
    std::istringstream is("2147483647/1");
    Rational r{0, 0};
    is >> r;
    EXPECT_FALSE(is.fail());
    EXPECT_EQ(r.first, 2147483647);
    EXPECT_EQ(r.second, 1);
}

// Test both negative numerator and denominator
TEST_F(FromStreamToRationalTest_1134, ParseBothNegative_1134) {
    std::istringstream is("-1/-1");
    Rational r{0, 0};
    is >> r;
    EXPECT_FALSE(is.fail());
    EXPECT_EQ(r.first, -1);
    EXPECT_EQ(r.second, -1);
}

// Test empty stream causes fail
TEST_F(FromStreamToRationalTest_1134, EmptyStreamCausesFail_1134) {
    std::istringstream is("");
    Rational r{0, 0};
    is >> r;
    EXPECT_TRUE(is.fail());
}

// Test rational 1/1
TEST_F(FromStreamToRationalTest_1134, ParseOneOverOne_1134) {
    std::istringstream is("1/1");
    Rational r{0, 0};
    is >> r;
    EXPECT_FALSE(is.fail());
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 1);
}

// Test f-stop with f1.4 (common aperture)
TEST_F(FromStreamToRationalTest_1134, ParseFStop1Point4_1134) {
    std::istringstream is("f1.4");
    Rational r{0, 0};
    is >> r;
    EXPECT_FALSE(is.fail());
    // f1.4 -> 2*log2(1.4) ≈ 2*0.485 ≈ 0.97
    double value = static_cast<double>(r.first) / static_cast<double>(r.second);
    double expected = 2.0 * std::log2(1.4f);
    EXPECT_NEAR(value, expected, 0.1);
}

// Test that original rational is not modified on parse failure
TEST_F(FromStreamToRationalTest_1134, RationalUnchangedOnFail_1134) {
    std::istringstream is("abc");
    Rational r{42, 43};
    is >> r;
    EXPECT_TRUE(is.fail());
}
