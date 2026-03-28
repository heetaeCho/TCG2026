#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need access to the internal function
namespace Exiv2 {
namespace Internal {
std::ostream& print0x9202(std::ostream& os, const Value& value, const ExifData*);
}
}

using namespace Exiv2;
using namespace Exiv2::Internal;

class Print0x9202Test_1401 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test with empty value (count == 0)
TEST_F(Print0x9202Test_1401, EmptyValueReturnsParenthesizedValue_1401) {
    URationalValue value;
    // No values added, count should be 0
    print0x9202(os, value, nullptr);
    std::string result = os.str();
    // Should output "(" followed by value followed by ")"
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test with rational having zero denominator
TEST_F(Print0x9202Test_1401, ZeroDenominatorReturnsParenthesizedValue_1401) {
    URationalValue value;
    value.value_.push_back({5, 0});
    print0x9202(os, value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test with a valid rational value representing a typical aperture
// ApertureValue of 5.0 (APEX) corresponds to fnumber ~ F5.6
TEST_F(Print0x9202Test_1401, ValidApertureValueOutputsFNumber_1401) {
    URationalValue value;
    value.value_.push_back({5, 1}); // Aperture value 5.0
    print0x9202(os, value, nullptr);
    std::string result = os.str();
    // Should start with "F"
    EXPECT_EQ(result[0], 'F');
    // Should not be parenthesized
    EXPECT_NE(result.front(), '(');
}

// Test with aperture value of 0 (fnumber should be 1.0)
// ApertureValue 0 => fnumber = 2^(0/2) = 1.0
TEST_F(Print0x9202Test_1401, ApertureValueZeroOutputsF1_1401) {
    URationalValue value;
    value.value_.push_back({0, 1}); // Aperture value 0.0
    print0x9202(os, value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result[0], 'F');
    EXPECT_NE(result.find("1"), std::string::npos);
}

// Test with aperture value of 2 (APEX) => fnumber = 2^(2/2) = 2.0
TEST_F(Print0x9202Test_1401, ApertureValue2OutputsF2_1401) {
    URationalValue value;
    value.value_.push_back({2, 1}); // Aperture value 2.0
    print0x9202(os, value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result[0], 'F');
    EXPECT_NE(result.find("2"), std::string::npos);
}

// Test with aperture value of 1 (APEX) => fnumber = 2^(1/2) = sqrt(2) ~ 1.4
TEST_F(Print0x9202Test_1401, ApertureValue1OutputsFnumber_1401) {
    URationalValue value;
    value.value_.push_back({1, 1}); // Aperture value 1.0
    print0x9202(os, value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result[0], 'F');
    EXPECT_NE(result.find("1.4"), std::string::npos);
}

// Test with a fractional rational aperture value
TEST_F(Print0x9202Test_1401, FractionalApertureValue_1401) {
    URationalValue value;
    value.value_.push_back({7, 2}); // Aperture value 3.5
    print0x9202(os, value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result[0], 'F');
}

// Test with nullptr ExifData (should still work)
TEST_F(Print0x9202Test_1401, NullExifDataWorks_1401) {
    URationalValue value;
    value.value_.push_back({4, 1}); // Aperture value 4.0 => fnumber = 4.0
    print0x9202(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result[0], 'F');
}

// Test that output stream is returned correctly for chaining
TEST_F(Print0x9202Test_1401, ReturnsOutputStream_1401) {
    URationalValue value;
    value.value_.push_back({3, 1});
    std::ostream& returned = print0x9202(os, value, nullptr);
    EXPECT_EQ(&returned, &os);
}

// Test that output stream is returned correctly for empty value case
TEST_F(Print0x9202Test_1401, ReturnsOutputStreamForEmptyValue_1401) {
    URationalValue value;
    std::ostream& returned = print0x9202(os, value, nullptr);
    EXPECT_EQ(&returned, &os);
}

// Test with a large aperture value
TEST_F(Print0x9202Test_1401, LargeApertureValue_1401) {
    URationalValue value;
    value.value_.push_back({14, 1}); // Large aperture value
    print0x9202(os, value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result[0], 'F');
}

// Test with denominator of 1 (simple integer ratio)
TEST_F(Print0x9202Test_1401, IntegerRationalValue_1401) {
    URationalValue value;
    value.value_.push_back({8, 1}); // Aperture value 8.0 => fnumber = 2^4 = 16
    print0x9202(os, value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result[0], 'F');
    // fnumber for aperture 8 = 2^(8/2) = 2^4 = 16
    EXPECT_NE(result.find("16"), std::string::npos);
}
