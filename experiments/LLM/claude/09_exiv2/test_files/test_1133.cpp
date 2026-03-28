#include <gtest/gtest.h>
#include <sstream>
#include <utility>

// Include the necessary headers from exiv2
#include "types.hpp"

// TEST_ID is 1133

namespace {

// Test normal operation with positive numerator and denominator
TEST(RationalOutputTest_1133, PositiveValues_1133) {
    Exiv2::Rational r(1, 2);
    std::ostringstream os;
    os << r;
    EXPECT_EQ(os.str(), "1/2");
}

// Test normal operation with zero numerator
TEST(RationalOutputTest_1133, ZeroNumerator_1133) {
    Exiv2::Rational r(0, 1);
    std::ostringstream os;
    os << r;
    EXPECT_EQ(os.str(), "0/1");
}

// Test with zero denominator
TEST(RationalOutputTest_1133, ZeroDenominator_1133) {
    Exiv2::Rational r(1, 0);
    std::ostringstream os;
    os << r;
    EXPECT_EQ(os.str(), "1/0");
}

// Test with both zero
TEST(RationalOutputTest_1133, BothZero_1133) {
    Exiv2::Rational r(0, 0);
    std::ostringstream os;
    os << r;
    EXPECT_EQ(os.str(), "0/0");
}

// Test with negative numerator
TEST(RationalOutputTest_1133, NegativeNumerator_1133) {
    Exiv2::Rational r(-3, 4);
    std::ostringstream os;
    os << r;
    EXPECT_EQ(os.str(), "-3/4");
}

// Test with negative denominator
TEST(RationalOutputTest_1133, NegativeDenominator_1133) {
    Exiv2::Rational r(3, -4);
    std::ostringstream os;
    os << r;
    EXPECT_EQ(os.str(), "3/-4");
}

// Test with both negative
TEST(RationalOutputTest_1133, BothNegative_1133) {
    Exiv2::Rational r(-5, -7);
    std::ostringstream os;
    os << r;
    EXPECT_EQ(os.str(), "-5/-7");
}

// Test with large values
TEST(RationalOutputTest_1133, LargeValues_1133) {
    Exiv2::Rational r(2147483647, 2147483647);
    std::ostringstream os;
    os << r;
    EXPECT_EQ(os.str(), "2147483647/2147483647");
}

// Test with INT32_MIN values
TEST(RationalOutputTest_1133, MinIntValues_1133) {
    Exiv2::Rational r(-2147483647 - 1, -2147483647 - 1);
    std::ostringstream os;
    os << r;
    // INT32_MIN is -2147483648
    EXPECT_EQ(os.str(), "-2147483648/-2147483648");
}

// Test with value 1/1
TEST(RationalOutputTest_1133, OneOverOne_1133) {
    Exiv2::Rational r(1, 1);
    std::ostringstream os;
    os << r;
    EXPECT_EQ(os.str(), "1/1");
}

// Test that the operator returns the stream reference (chaining)
TEST(RationalOutputTest_1133, StreamChaining_1133) {
    Exiv2::Rational r1(1, 2);
    Exiv2::Rational r2(3, 4);
    std::ostringstream os;
    os << r1 << " " << r2;
    EXPECT_EQ(os.str(), "1/2 3/4");
}

// Test with typical EXIF-like rational values
TEST(RationalOutputTest_1133, TypicalExifValue_1133) {
    // Typical exposure time: 1/125
    Exiv2::Rational r(1, 125);
    std::ostringstream os;
    os << r;
    EXPECT_EQ(os.str(), "1/125");
}

// Test with large numerator and small denominator
TEST(RationalOutputTest_1133, LargeNumeratorSmallDenominator_1133) {
    Exiv2::Rational r(1000000, 1);
    std::ostringstream os;
    os << r;
    EXPECT_EQ(os.str(), "1000000/1");
}

// Test stream state after output (stream should be good)
TEST(RationalOutputTest_1133, StreamStateGood_1133) {
    Exiv2::Rational r(10, 20);
    std::ostringstream os;
    os << r;
    EXPECT_TRUE(os.good());
    EXPECT_EQ(os.str(), "10/20");
}

} // namespace
