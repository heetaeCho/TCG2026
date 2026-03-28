#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

using namespace Exiv2;

class Print0x829aTest_1395 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test with empty value (count == 0)
TEST_F(Print0x829aTest_1395, EmptyValueReturnsEmptyStream_1395) {
    URationalValue value;
    // count() == 0, should return os without printing anything
    Internal::print0x829a(os, value, nullptr);
    EXPECT_EQ(os.str(), "");
}

// Test with non-unsignedRational type - should print parenthesized value
TEST_F(Print0x829aTest_1395, NonRationalTypePrintsParenthesized_1395) {
    UShortValue value;
    value.read("42");
    Internal::print0x829a(os, value, nullptr);
    EXPECT_EQ(os.str(), "(42)");
}

// Test with t.first == 0 (zero numerator)
TEST_F(Print0x829aTest_1395, ZeroNumeratorPrintsParenthesized_1395) {
    URationalValue value;
    value.read("0/1");
    Internal::print0x829a(os, value, nullptr);
    EXPECT_EQ(os.str(), "(0/1)");
}

// Test with t.second == 0 (zero denominator)
TEST_F(Print0x829aTest_1395, ZeroDenominatorPrintsParenthesized_1395) {
    URationalValue value;
    value.read("1/0");
    Internal::print0x829a(os, value, nullptr);
    EXPECT_EQ(os.str(), "(1/0)");
}

// Test with both numerator and denominator zero
TEST_F(Print0x829aTest_1395, BothZeroPrintsParenthesized_1395) {
    URationalValue value;
    value.read("0/0");
    Internal::print0x829a(os, value, nullptr);
    EXPECT_EQ(os.str(), "(0/0)");
}

// Test with t.second == t.first (equal, e.g., 1/1 -> "1 s")
TEST_F(Print0x829aTest_1395, EqualNumeratorDenominatorPrintsOneSecond_1395) {
    URationalValue value;
    value.read("1/1");
    Internal::print0x829a(os, value, nullptr);
    EXPECT_EQ(os.str(), "1 s");
}

// Test with equal but larger values (e.g., 5/5 -> "1 s")
TEST_F(Print0x829aTest_1395, EqualLargerValuesPrintsOneSecond_1395) {
    URationalValue value;
    value.read("5/5");
    Internal::print0x829a(os, value, nullptr);
    EXPECT_EQ(os.str(), "1 s");
}

// Test with t.second % t.first == 0 (e.g., 1/250 -> "1/250 s")
TEST_F(Print0x829aTest_1395, DenominatorDivisibleByNumeratorPrintsSimplified_1395) {
    URationalValue value;
    value.read("1/250");
    Internal::print0x829a(os, value, nullptr);
    EXPECT_EQ(os.str(), "1/250 s");
}

// Test with reducible fraction where denominator is divisible by numerator (e.g., 2/500 -> "1/250 s")
TEST_F(Print0x829aTest_1395, ReducibleFractionSimplifies_1395) {
    URationalValue value;
    value.read("2/500");
    Internal::print0x829a(os, value, nullptr);
    EXPECT_EQ(os.str(), "1/250 s");
}

// Test with fraction that doesn't simplify cleanly (e.g., 3/10 -> float output)
TEST_F(Print0x829aTest_1395, NonDivisibleFractionPrintsFloat_1395) {
    URationalValue value;
    value.read("3/10");
    Internal::print0x829a(os, value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("s") != std::string::npos);
    EXPECT_TRUE(result.find("0.3") != std::string::npos);
}

// Test with typical exposure time 1/125
TEST_F(Print0x829aTest_1395, TypicalExposure125_1395) {
    URationalValue value;
    value.read("1/125");
    Internal::print0x829a(os, value, nullptr);
    EXPECT_EQ(os.str(), "1/125 s");
}

// Test with typical exposure time 1/60
TEST_F(Print0x829aTest_1395, TypicalExposure60_1395) {
    URationalValue value;
    value.read("1/60");
    Internal::print0x829a(os, value, nullptr);
    EXPECT_EQ(os.str(), "1/60 s");
}

// Test with numerator > 1 and denominator not divisible (e.g., 2/3)
TEST_F(Print0x829aTest_1395, FractionGreaterThanZeroLessThanOnePrintsFloat_1395) {
    URationalValue value;
    value.read("2/3");
    Internal::print0x829a(os, value, nullptr);
    std::string result = os.str();
    // Should contain "s" and a float representation of 2/3
    EXPECT_TRUE(result.find("s") != std::string::npos);
}

// Test with long exposure time (e.g., 30/1 -> denominator % numerator != 0 because 1%30!=0, 
// but actually second==first is false, second%first = 1%30 != 0, so it goes to float)
// Wait: 30/1 => t.first=30, t.second=1. t.second != t.first. t.second % t.first = 1%30 = 1 != 0.
// So it prints float: 30/1 = 30.0 s
TEST_F(Print0x829aTest_1395, LongExposure30Seconds_1395) {
    URationalValue value;
    value.read("30/1");
    Internal::print0x829a(os, value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("30") != std::string::npos);
    EXPECT_TRUE(result.find("s") != std::string::npos);
}

// Test with 10/1 - float path since 1 % 10 != 0
TEST_F(Print0x829aTest_1395, TenSecondsExposure_1395) {
    URationalValue value;
    value.read("10/1");
    Internal::print0x829a(os, value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("10") != std::string::npos);
    EXPECT_TRUE(result.find("s") != std::string::npos);
}

// Test with 1/1000 (common fast shutter speed)
TEST_F(Print0x829aTest_1395, FastShutterSpeed1000_1395) {
    URationalValue value;
    value.read("1/1000");
    Internal::print0x829a(os, value, nullptr);
    EXPECT_EQ(os.str(), "1/1000 s");
}

// Test with 1/8000 (very fast shutter speed)
TEST_F(Print0x829aTest_1395, VeryFastShutterSpeed8000_1395) {
    URationalValue value;
    value.read("1/8000");
    Internal::print0x829a(os, value, nullptr);
    EXPECT_EQ(os.str(), "1/8000 s");
}

// Test with 10/5 - t.second != t.first, t.second % t.first = 5%10 = 5 != 0, so float path
// 10/5 = 2.0
TEST_F(Print0x829aTest_1395, TenOverFivePrintsFloat_1395) {
    URationalValue value;
    value.read("10/5");
    Internal::print0x829a(os, value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("2") != std::string::npos);
    EXPECT_TRUE(result.find("s") != std::string::npos);
}

// Test nullptr ExifData parameter is accepted
TEST_F(Print0x829aTest_1395, NullExifDataAccepted_1395) {
    URationalValue value;
    value.read("1/100");
    EXPECT_NO_THROW(Internal::print0x829a(os, value, nullptr));
    EXPECT_EQ(os.str(), "1/100 s");
}
