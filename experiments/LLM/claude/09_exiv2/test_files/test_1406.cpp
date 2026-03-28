#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need access to the internal function
namespace Exiv2 {
namespace Internal {
std::ostream& print0x920a(std::ostream& os, const Value& value, const ExifData*);
}
}

using namespace Exiv2;
using namespace Exiv2::Internal;

class Print0x920aTest_1406 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test normal rational value with valid denominator
TEST_F(Print0x920aTest_1406, NormalRationalValue_1406) {
    RationalValue value;
    value.value_.push_back({500, 10});  // 50.0 mm
    print0x920a(os, value, nullptr);
    EXPECT_EQ(os.str(), "50.0 mm");
}

// Test rational value where denominator is zero - should output fallback format
TEST_F(Print0x920aTest_1406, ZeroDenominator_1406) {
    RationalValue value;
    value.value_.push_back({500, 0});
    print0x920a(os, value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test rational value that results in a whole number
TEST_F(Print0x920aTest_1406, WholeNumberFocalLength_1406) {
    RationalValue value;
    value.value_.push_back({100, 1});  // 100.0 mm
    print0x920a(os, value, nullptr);
    EXPECT_EQ(os.str(), "100.0 mm");
}

// Test rational value with fractional result
TEST_F(Print0x920aTest_1406, FractionalFocalLength_1406) {
    RationalValue value;
    value.value_.push_back({353, 10});  // 35.3 mm
    print0x920a(os, value, nullptr);
    EXPECT_EQ(os.str(), "35.3 mm");
}

// Test small focal length
TEST_F(Print0x920aTest_1406, SmallFocalLength_1406) {
    RationalValue value;
    value.value_.push_back({28, 10});  // 2.8 mm
    print0x920a(os, value, nullptr);
    EXPECT_EQ(os.str(), "2.8 mm");
}

// Test large focal length
TEST_F(Print0x920aTest_1406, LargeFocalLength_1406) {
    RationalValue value;
    value.value_.push_back({6000, 10});  // 600.0 mm
    print0x920a(os, value, nullptr);
    EXPECT_EQ(os.str(), "600.0 mm");
}

// Test with denominator of 1
TEST_F(Print0x920aTest_1406, DenominatorOne_1406) {
    RationalValue value;
    value.value_.push_back({55, 1});  // 55.0 mm
    print0x920a(os, value, nullptr);
    EXPECT_EQ(os.str(), "55.0 mm");
}

// Test with numerator of 0 and valid denominator
TEST_F(Print0x920aTest_1406, ZeroNumerator_1406) {
    RationalValue value;
    value.value_.push_back({0, 1});  // 0.0 mm
    print0x920a(os, value, nullptr);
    EXPECT_EQ(os.str(), "0.0 mm");
}

// Test with both numerator and denominator zero
TEST_F(Print0x920aTest_1406, BothZero_1406) {
    RationalValue value;
    value.value_.push_back({0, 0});
    print0x920a(os, value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test with negative numerator
TEST_F(Print0x920aTest_1406, NegativeNumerator_1406) {
    RationalValue value;
    value.value_.push_back({-50, 1});
    print0x920a(os, value, nullptr);
    EXPECT_EQ(os.str(), "-50.0 mm");
}

// Test that the function returns the ostream reference
TEST_F(Print0x920aTest_1406, ReturnsOstream_1406) {
    RationalValue value;
    value.value_.push_back({50, 1});
    std::ostream& result = print0x920a(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test returns ostream reference for zero denominator case
TEST_F(Print0x920aTest_1406, ReturnsOstreamZeroDenom_1406) {
    RationalValue value;
    value.value_.push_back({50, 0});
    std::ostream& result = print0x920a(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test with typical camera focal lengths
TEST_F(Print0x920aTest_1406, TypicalFocalLength35mm_1406) {
    RationalValue value;
    value.value_.push_back({350, 10});  // 35.0 mm
    print0x920a(os, value, nullptr);
    EXPECT_EQ(os.str(), "35.0 mm");
}

TEST_F(Print0x920aTest_1406, TypicalFocalLength50mm_1406) {
    RationalValue value;
    value.value_.push_back({5000, 100});  // 50.0 mm
    print0x920a(os, value, nullptr);
    EXPECT_EQ(os.str(), "50.0 mm");
}

// Test with large denominator producing a small value
TEST_F(Print0x920aTest_1406, LargeDenominator_1406) {
    RationalValue value;
    value.value_.push_back({1, 1000});  // 0.001 -> should round to 0.0
    print0x920a(os, value, nullptr);
    EXPECT_EQ(os.str(), "0.0 mm");
}
