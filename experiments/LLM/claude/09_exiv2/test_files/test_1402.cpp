#include <gtest/gtest.h>
#include <sstream>
#include <limits>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

using namespace Exiv2;

// Forward declaration of the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& print0x9204(std::ostream& os, const Value& value, const ExifData*);
}
}

class Print0x9204Test_1402 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test: When bias.first is 0, output should be "0 EV"
TEST_F(Print0x9204Test_1402, ZeroBiasFirst_1402) {
    RationalValue value;
    value.value_.push_back(Rational(0, 1));
    Internal::print0x9204(os, value, nullptr);
    EXPECT_EQ(os.str(), "0 EV");
}

// Test: When bias.first is 0 and bias.second is 0, output should be "0 EV"
TEST_F(Print0x9204Test_1402, ZeroBiasFirstZeroSecond_1402) {
    RationalValue value;
    value.value_.push_back(Rational(0, 0));
    Internal::print0x9204(os, value, nullptr);
    EXPECT_EQ(os.str(), "0 EV");
}

// Test: When bias.first is INT32_MIN, output should be "0 EV"
TEST_F(Print0x9204Test_1402, Int32MinBiasFirst_1402) {
    RationalValue value;
    value.value_.push_back(Rational(std::numeric_limits<int32_t>::min(), 1));
    Internal::print0x9204(os, value, nullptr);
    EXPECT_EQ(os.str(), "0 EV");
}

// Test: When bias.second is 0 (and bias.first != 0 and != INT32_MIN), output raw fraction in parens
TEST_F(Print0x9204Test_1402, NegativeSecond_ZeroDenominator_1402) {
    RationalValue value;
    value.value_.push_back(Rational(1, 0));
    Internal::print0x9204(os, value, nullptr);
    EXPECT_EQ(os.str(), "(1/0)");
}

// Test: When bias.second is negative, output raw fraction in parens
TEST_F(Print0x9204Test_1402, NegativeDenominator_1402) {
    RationalValue value;
    value.value_.push_back(Rational(1, -3));
    Internal::print0x9204(os, value, nullptr);
    EXPECT_EQ(os.str(), "(1/-3)");
}

// Test: Positive bias with denominator 1 -> "+N EV"
TEST_F(Print0x9204Test_1402, PositiveBiasWholeNumber_1402) {
    RationalValue value;
    value.value_.push_back(Rational(2, 1));
    Internal::print0x9204(os, value, nullptr);
    EXPECT_EQ(os.str(), "+2 EV");
}

// Test: Negative bias with denominator 1 -> "-N EV"
TEST_F(Print0x9204Test_1402, NegativeBiasWholeNumber_1402) {
    RationalValue value;
    value.value_.push_back(Rational(-3, 1));
    Internal::print0x9204(os, value, nullptr);
    EXPECT_EQ(os.str(), "-3 EV");
}

// Test: Positive bias with fraction -> "+num/den EV"
TEST_F(Print0x9204Test_1402, PositiveBiasFraction_1402) {
    RationalValue value;
    value.value_.push_back(Rational(1, 3));
    Internal::print0x9204(os, value, nullptr);
    EXPECT_EQ(os.str(), "+1/3 EV");
}

// Test: Negative bias with fraction -> "-num/den EV"
TEST_F(Print0x9204Test_1402, NegativeBiasFraction_1402) {
    RationalValue value;
    value.value_.push_back(Rational(-1, 3));
    Internal::print0x9204(os, value, nullptr);
    EXPECT_EQ(os.str(), "-1/3 EV");
}

// Test: Positive bias that can be reduced -> reduced fraction
TEST_F(Print0x9204Test_1402, PositiveBiasReducibleFraction_1402) {
    RationalValue value;
    value.value_.push_back(Rational(2, 6));
    Internal::print0x9204(os, value, nullptr);
    EXPECT_EQ(os.str(), "+1/3 EV");
}

// Test: Negative bias that can be reduced -> reduced fraction
TEST_F(Print0x9204Test_1402, NegativeBiasReducibleFraction_1402) {
    RationalValue value;
    value.value_.push_back(Rational(-4, 6));
    Internal::print0x9204(os, value, nullptr);
    EXPECT_EQ(os.str(), "-2/3 EV");
}

// Test: Fraction that reduces to a whole number (e.g., 6/3 = 2)
TEST_F(Print0x9204Test_1402, FractionReducesToWholeNumber_1402) {
    RationalValue value;
    value.value_.push_back(Rational(6, 3));
    Internal::print0x9204(os, value, nullptr);
    EXPECT_EQ(os.str(), "+2 EV");
}

// Test: Negative fraction reducing to whole number
TEST_F(Print0x9204Test_1402, NegativeFractionReducesToWholeNumber_1402) {
    RationalValue value;
    value.value_.push_back(Rational(-6, 3));
    Internal::print0x9204(os, value, nullptr);
    EXPECT_EQ(os.str(), "-2 EV");
}

// Test: bias.first = 1, bias.second = 1 -> "+1 EV"
TEST_F(Print0x9204Test_1402, OneOverOne_1402) {
    RationalValue value;
    value.value_.push_back(Rational(1, 1));
    Internal::print0x9204(os, value, nullptr);
    EXPECT_EQ(os.str(), "+1 EV");
}

// Test: Typical camera exposure bias +2/3
TEST_F(Print0x9204Test_1402, TypicalPositiveTwoThirds_1402) {
    RationalValue value;
    value.value_.push_back(Rational(2, 3));
    Internal::print0x9204(os, value, nullptr);
    EXPECT_EQ(os.str(), "+2/3 EV");
}

// Test: Typical camera exposure bias -1/3
TEST_F(Print0x9204Test_1402, TypicalNegativeOneThird_1402) {
    RationalValue value;
    value.value_.push_back(Rational(-1, 3));
    Internal::print0x9204(os, value, nullptr);
    EXPECT_EQ(os.str(), "-1/3 EV");
}

// Test: Large values
TEST_F(Print0x9204Test_1402, LargePositiveValues_1402) {
    RationalValue value;
    value.value_.push_back(Rational(1000000, 3));
    Internal::print0x9204(os, value, nullptr);
    EXPECT_EQ(os.str(), "+1000000/3 EV");
}

// Test: bias.second is negative with non-zero first (not INT32_MIN)
TEST_F(Print0x9204Test_1402, NegativeDenominatorWithNegativeNumerator_1402) {
    RationalValue value;
    value.value_.push_back(Rational(-5, -2));
    Internal::print0x9204(os, value, nullptr);
    EXPECT_EQ(os.str(), "(-5/-2)");
}

// Test: bias.first = 0, bias.second = large value -> "0 EV"
TEST_F(Print0x9204Test_1402, ZeroNumeratorLargeDenominator_1402) {
    RationalValue value;
    value.value_.push_back(Rational(0, 1000000));
    Internal::print0x9204(os, value, nullptr);
    EXPECT_EQ(os.str(), "0 EV");
}

// Test: Return value is the same ostream reference
TEST_F(Print0x9204Test_1402, ReturnsSameOstream_1402) {
    RationalValue value;
    value.value_.push_back(Rational(1, 3));
    std::ostream& result = Internal::print0x9204(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}
