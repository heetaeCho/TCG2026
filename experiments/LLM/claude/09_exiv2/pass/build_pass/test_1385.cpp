#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>

// We need access to the Internal namespace function
namespace Exiv2 {
namespace Internal {
std::ostream& print0x0006(std::ostream& os, const Value& value, const ExifData*);
}
}

using namespace Exiv2;

class Print0x0006Test_1385 : public ::testing::Test {
protected:
    std::ostringstream os_;
};

// Test with a normal rational value where denominator > 1 (should have 1 decimal place)
TEST_F(Print0x0006Test_1385, NormalRationalDenominatorGreaterThanOne_1385) {
    URationalValue value;
    value.read("35/10");
    Internal::print0x0006(os_, value, nullptr);
    EXPECT_EQ(os_.str(), "3.5 m");
}

// Test with a rational value where denominator == 1 (should have 0 decimal places)
TEST_F(Print0x0006Test_1385, RationalDenominatorEqualsOne_1385) {
    URationalValue value;
    value.read("5/1");
    Internal::print0x0006(os_, value, nullptr);
    EXPECT_EQ(os_.str(), "5 m");
}

// Test with denominator == 0 (should return "(value)" format)
TEST_F(Print0x0006Test_1385, DenominatorZeroReturnsParenthesizedValue_1385) {
    URationalValue value;
    value.read("5/0");
    Internal::print0x0006(os_, value, nullptr);
    std::string result = os_.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test with value 0/1 (zero distance)
TEST_F(Print0x0006Test_1385, ZeroValueDenominatorOne_1385) {
    URationalValue value;
    value.read("0/1");
    Internal::print0x0006(os_, value, nullptr);
    EXPECT_EQ(os_.str(), "0 m");
}

// Test with value 0/10 (zero distance, denominator > 1)
TEST_F(Print0x0006Test_1385, ZeroValueDenominatorGreaterThanOne_1385) {
    URationalValue value;
    value.read("0/10");
    Internal::print0x0006(os_, value, nullptr);
    EXPECT_EQ(os_.str(), "0.0 m");
}

// Test with large rational value
TEST_F(Print0x0006Test_1385, LargeRationalValue_1385) {
    URationalValue value;
    value.read("100000/1");
    Internal::print0x0006(os_, value, nullptr);
    EXPECT_EQ(os_.str(), "100000 m");
}

// Test with small fractional value
TEST_F(Print0x0006Test_1385, SmallFractionalValue_1385) {
    URationalValue value;
    value.read("1/100");
    Internal::print0x0006(os_, value, nullptr);
    EXPECT_EQ(os_.str(), "0.0 m");
}

// Test with denominator = 2
TEST_F(Print0x0006Test_1385, DenominatorEqualsTwo_1385) {
    URationalValue value;
    value.read("5/2");
    Internal::print0x0006(os_, value, nullptr);
    EXPECT_EQ(os_.str(), "2.5 m");
}

// Test that stream flags are restored after the call
TEST_F(Print0x0006Test_1385, StreamFlagsRestoredAfterCall_1385) {
    URationalValue value;
    value.read("35/10");
    
    std::ios::fmtflags flagsBefore = os_.flags();
    Internal::print0x0006(os_, value, nullptr);
    std::ios::fmtflags flagsAfter = os_.flags();
    
    EXPECT_EQ(flagsBefore, flagsAfter);
}

// Test with nullptr ExifData (should work fine)
TEST_F(Print0x0006Test_1385, NullExifDataAccepted_1385) {
    URationalValue value;
    value.read("10/1");
    EXPECT_NO_THROW(Internal::print0x0006(os_, value, nullptr));
    EXPECT_EQ(os_.str(), "10 m");
}

// Test with value 1/1
TEST_F(Print0x0006Test_1385, OneOverOne_1385) {
    URationalValue value;
    value.read("1/1");
    Internal::print0x0006(os_, value, nullptr);
    EXPECT_EQ(os_.str(), "1 m");
}

// Test that " m" suffix is always present for non-zero denominator
TEST_F(Print0x0006Test_1385, SuffixMPresent_1385) {
    URationalValue value;
    value.read("7/3");
    Internal::print0x0006(os_, value, nullptr);
    std::string result = os_.str();
    EXPECT_TRUE(result.size() >= 2);
    EXPECT_EQ(result.substr(result.size() - 2), " m");
}

// Test with denominator 0/0
TEST_F(Print0x0006Test_1385, ZeroOverZero_1385) {
    URationalValue value;
    value.read("0/0");
    Internal::print0x0006(os_, value, nullptr);
    std::string result = os_.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test return value is the same stream
TEST_F(Print0x0006Test_1385, ReturnsSameStream_1385) {
    URationalValue value;
    value.read("10/1");
    std::ostream& returned = Internal::print0x0006(os_, value, nullptr);
    EXPECT_EQ(&returned, &os_);
}

// Test with denominator 0 returns same stream
TEST_F(Print0x0006Test_1385, DenominatorZeroReturnsSameStream_1385) {
    URationalValue value;
    value.read("10/0");
    std::ostream& returned = Internal::print0x0006(os_, value, nullptr);
    EXPECT_EQ(&returned, &os_);
}
