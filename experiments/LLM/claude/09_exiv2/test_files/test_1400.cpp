#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>

using namespace Exiv2;

class Print0x9201Test_1400 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test with a normal positive APEX shutter speed value
TEST_F(Print0x9201Test_1400, NormalPositiveValue_1400) {
    RationalValue value;
    value.read("5/1");
    Internal::print0x9201(os, value, nullptr);
    std::string result = os.str();
    // Should contain " s" suffix
    EXPECT_NE(result.find(" s"), std::string::npos);
    // Should not be in error format with parentheses
    EXPECT_EQ(result.find("("), std::string::npos);
}

// Test with zero denominator - should produce error format
TEST_F(Print0x9201Test_1400, ZeroDenominator_1400) {
    RationalValue value;
    value.read("5/0");
    Internal::print0x9201(os, value, nullptr);
    std::string result = os.str();
    // Should be in parenthesized error format
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test with zero numerator and non-zero denominator
TEST_F(Print0x9201Test_1400, ZeroNumerator_1400) {
    RationalValue value;
    value.read("0/1");
    Internal::print0x9201(os, value, nullptr);
    std::string result = os.str();
    // Should contain " s" suffix (valid rational)
    EXPECT_NE(result.find(" s"), std::string::npos);
}

// Test with negative APEX value (long exposure)
TEST_F(Print0x9201Test_1400, NegativeValue_1400) {
    RationalValue value;
    value.read("-1/1");
    Internal::print0x9201(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find(" s"), std::string::npos);
}

// Test with a typical APEX value like 6/1 (~1/64s)
TEST_F(Print0x9201Test_1400, TypicalApexValue_1400) {
    RationalValue value;
    value.read("6/1");
    Internal::print0x9201(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find(" s"), std::string::npos);
}

// Test with rational value 1/1 (APEX = 1 means 1s exposure)
TEST_F(Print0x9201Test_1400, ApexOneValue_1400) {
    RationalValue value;
    value.read("1/1");
    Internal::print0x9201(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find(" s"), std::string::npos);
}

// Test with large APEX value
TEST_F(Print0x9201Test_1400, LargeApexValue_1400) {
    RationalValue value;
    value.read("15/1");
    Internal::print0x9201(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find(" s"), std::string::npos);
}

// Test with fractional APEX value
TEST_F(Print0x9201Test_1400, FractionalApexValue_1400) {
    RationalValue value;
    value.read("7/2");
    Internal::print0x9201(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find(" s"), std::string::npos);
}

// Test with large negative value
TEST_F(Print0x9201Test_1400, LargeNegativeValue_1400) {
    RationalValue value;
    value.read("-5/1");
    Internal::print0x9201(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find(" s"), std::string::npos);
}

// Test that the function returns the same ostream reference
TEST_F(Print0x9201Test_1400, ReturnsOstreamReference_1400) {
    RationalValue value;
    value.read("3/1");
    std::ostream& returned = Internal::print0x9201(os, value, nullptr);
    EXPECT_EQ(&returned, &os);
}

// Test with denominator of zero produces parenthesized output and returns ostream
TEST_F(Print0x9201Test_1400, ZeroDenominatorReturnsOstream_1400) {
    RationalValue value;
    value.read("0/0");
    std::ostream& returned = Internal::print0x9201(os, value, nullptr);
    EXPECT_EQ(&returned, &os);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test with a non-Rational value type (e.g., using a different value type)
// that might cause value.ok() to return false
TEST_F(Print0x9201Test_1400, StringValueProducesErrorFormat_1400) {
    StringValue value;
    value.read("not_a_rational");
    Internal::print0x9201(os, value, nullptr);
    std::string result = os.str();
    // When toRational fails (ok() returns false or denominator is 0),
    // should produce parenthesized output
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test APEX value that results in exposure time with denominator > 1 (fractional display)
TEST_F(Print0x9201Test_1400, FractionalExposureDisplay_1400) {
    RationalValue value;
    // APEX value of 10/1 should result in a fast shutter speed like 1/1024
    value.read("10/1");
    Internal::print0x9201(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find(" s"), std::string::npos);
    // For high APEX values, expect a fractional display with "/"
    EXPECT_NE(result.find("/"), std::string::npos);
}

// Test APEX value that results in whole number exposure time
TEST_F(Print0x9201Test_1400, WholeNumberExposure_1400) {
    RationalValue value;
    // APEX value of -3/1 should give a long exposure >= 1s
    value.read("-3/1");
    Internal::print0x9201(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find(" s"), std::string::npos);
}
