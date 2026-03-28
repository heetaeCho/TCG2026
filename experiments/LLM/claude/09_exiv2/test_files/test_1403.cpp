#include <gtest/gtest.h>
#include <sstream>
#include <limits>
#include <exiv2/exiv2.hpp>

using namespace Exiv2;

class Print0x9206Test_1403 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test when the first element of the rational is 0, should print "Unknown"
TEST_F(Print0x9206Test_1403, ZeroNumeratorPrintsUnknown_1403) {
    URationalValue value;
    value.value_.push_back({0, 100});
    
    Internal::print0x9206(os, value, nullptr);
    
    EXPECT_NE(os.str().find("Unknown"), std::string::npos);
}

// Test when the first element equals uint32_t max, should print "Infinity"
TEST_F(Print0x9206Test_1403, MaxUint32NumeratorPrintsInfinity_1403) {
    RationalValue value;
    value.value_.push_back({static_cast<int32_t>(std::numeric_limits<uint32_t>::max()), 1});
    
    Internal::print0x9206(os, value, nullptr);
    
    EXPECT_NE(os.str().find("Infinity"), std::string::npos);
}

// Test normal distance calculation with valid numerator and denominator
TEST_F(Print0x9206Test_1403, ValidDistancePrintsMeters_1403) {
    RationalValue value;
    value.value_.push_back({500, 100});
    
    Internal::print0x9206(os, value, nullptr);
    
    std::string result = os.str();
    EXPECT_NE(result.find("5.00"), std::string::npos);
    EXPECT_NE(result.find("m"), std::string::npos);
}

// Test when denominator is 0 and numerator is non-zero and not max, should print raw value in parens
TEST_F(Print0x9206Test_1403, ZeroDenominatorPrintsRawValue_1403) {
    RationalValue value;
    value.value_.push_back({10, 0});
    
    Internal::print0x9206(os, value, nullptr);
    
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test with numerator = 1, denominator = 1, should print "1.00 m"
TEST_F(Print0x9206Test_1403, OneOverOnePrintsOneMeter_1403) {
    RationalValue value;
    value.value_.push_back({1, 1});
    
    Internal::print0x9206(os, value, nullptr);
    
    std::string result = os.str();
    EXPECT_NE(result.find("1.00"), std::string::npos);
    EXPECT_NE(result.find("m"), std::string::npos);
}

// Test with numerator = 0 and denominator = 0, should still print "Unknown" because first == 0
TEST_F(Print0x9206Test_1403, ZeroOverZeroPrintsUnknown_1403) {
    RationalValue value;
    value.value_.push_back({0, 0});
    
    Internal::print0x9206(os, value, nullptr);
    
    EXPECT_NE(os.str().find("Unknown"), std::string::npos);
}

// Test with a fractional distance, e.g., 1/3
TEST_F(Print0x9206Test_1403, FractionalDistancePrintsCorrectly_1403) {
    RationalValue value;
    value.value_.push_back({1, 3});
    
    Internal::print0x9206(os, value, nullptr);
    
    std::string result = os.str();
    EXPECT_NE(result.find("0.33"), std::string::npos);
    EXPECT_NE(result.find("m"), std::string::npos);
}

// Test with large valid numerator and denominator
TEST_F(Print0x9206Test_1403, LargeValidDistancePrintsMeters_1403) {
    RationalValue value;
    value.value_.push_back({1000000, 1000});
    
    Internal::print0x9206(os, value, nullptr);
    
    std::string result = os.str();
    EXPECT_NE(result.find("1000.00"), std::string::npos);
    EXPECT_NE(result.find("m"), std::string::npos);
}

// Test with negative numerator (not zero, not max)
TEST_F(Print0x9206Test_1403, NegativeNumeratorWithValidDenominator_1403) {
    RationalValue value;
    value.value_.push_back({-5, 1});
    
    Internal::print0x9206(os, value, nullptr);
    
    std::string result = os.str();
    // Should print distance since denominator != 0 and first != 0
    // The cast to uint32_t of -5 is not uint32_t max, so it should print the distance
    EXPECT_NE(result.find("m"), std::string::npos);
}

// Test with numerator = -1 which when cast to uint32_t equals max
TEST_F(Print0x9206Test_1403, NegativeOneCastToMaxPrintsInfinity_1403) {
    RationalValue value;
    value.value_.push_back({-1, 1});
    
    Internal::print0x9206(os, value, nullptr);
    
    // -1 cast to uint32_t is std::numeric_limits<uint32_t>::max()
    EXPECT_NE(os.str().find("Infinity"), std::string::npos);
}

// Test with denominator = 1 to verify simple integer distance
TEST_F(Print0x9206Test_1403, IntegerDistanceDenominatorOne_1403) {
    RationalValue value;
    value.value_.push_back({42, 1});
    
    Internal::print0x9206(os, value, nullptr);
    
    std::string result = os.str();
    EXPECT_NE(result.find("42.00"), std::string::npos);
    EXPECT_NE(result.find("m"), std::string::npos);
}
