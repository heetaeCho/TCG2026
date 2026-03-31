#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need access to the internal function
namespace Exiv2 {
namespace Internal {
std::ostream& print0x829d(std::ostream& os, const Value& value, const ExifData*);
}
}

using namespace Exiv2;

class Print0x829dTest_1396 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test normal F-number like F2.8 (fnumber = 28/10)
TEST_F(Print0x829dTest_1396, NormalFNumber_F2_8_1396) {
    URationalValue value;
    value.value_.push_back({28, 10});
    Exiv2::Internal::print0x829d(os, value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("F") == 0) << "Expected output starting with 'F', got: " << result;
    EXPECT_NE(result.find("2.8"), std::string::npos) << "Expected '2.8' in output, got: " << result;
}

// Test F-number where second is 0 (should print raw value in parentheses)
TEST_F(Print0x829dTest_1396, ZeroDenominator_1396) {
    URationalValue value;
    value.value_.push_back({28, 0});
    Exiv2::Internal::print0x829d(os, value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(') << "Expected output starting with '(', got: " << result;
    EXPECT_EQ(result.back(), ')') << "Expected output ending with ')', got: " << result;
}

// Test F-number F1 (fnumber = 1/1)
TEST_F(Print0x829dTest_1396, FNumberOne_1396) {
    URationalValue value;
    value.value_.push_back({1, 1});
    Exiv2::Internal::print0x829d(os, value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.substr(0, 1), "F") << "Expected output starting with 'F', got: " << result;
}

// Test F-number F4 (fnumber = 4/1)
TEST_F(Print0x829dTest_1396, FNumberFour_1396) {
    URationalValue value;
    value.value_.push_back({4, 1});
    Exiv2::Internal::print0x829d(os, value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("F") == 0) << "Expected output starting with 'F', got: " << result;
    EXPECT_NE(result.find("4"), std::string::npos) << "Expected '4' in output, got: " << result;
}

// Test F-number F5.6 (fnumber = 56/10)
TEST_F(Print0x829dTest_1396, FNumber_F5_6_1396) {
    URationalValue value;
    value.value_.push_back({56, 10});
    Exiv2::Internal::print0x829d(os, value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("F") == 0) << "Expected output starting with 'F', got: " << result;
    EXPECT_NE(result.find("5.6"), std::string::npos) << "Expected '5.6' in output, got: " << result;
}

// Test F-number F22 (fnumber = 22/1)
TEST_F(Print0x829dTest_1396, FNumber_F22_1396) {
    URationalValue value;
    value.value_.push_back({22, 1});
    Exiv2::Internal::print0x829d(os, value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("F") == 0) << "Expected output starting with 'F', got: " << result;
    EXPECT_NE(result.find("22"), std::string::npos) << "Expected '22' in output, got: " << result;
}

// Test with large values
TEST_F(Print0x829dTest_1396, LargeNumeratorDenominator_1396) {
    URationalValue value;
    value.value_.push_back({280000, 100000});
    Exiv2::Internal::print0x829d(os, value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("F") == 0) << "Expected output starting with 'F', got: " << result;
    EXPECT_NE(result.find("2.8"), std::string::npos) << "Expected '2.8' in output, got: " << result;
}

// Test with zero numerator and non-zero denominator
TEST_F(Print0x829dTest_1396, ZeroNumerator_1396) {
    URationalValue value;
    value.value_.push_back({0, 1});
    Exiv2::Internal::print0x829d(os, value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("F") == 0) << "Expected output starting with 'F', got: " << result;
    EXPECT_NE(result.find("0"), std::string::npos) << "Expected '0' in output, got: " << result;
}

// Test with both zero numerator and denominator
TEST_F(Print0x829dTest_1396, BothZero_1396) {
    URationalValue value;
    value.value_.push_back({0, 0});
    Exiv2::Internal::print0x829d(os, value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(') << "Expected output starting with '(', got: " << result;
    EXPECT_EQ(result.back(), ')') << "Expected output ending with ')', got: " << result;
}

// Test with nullptr ExifData (should still work)
TEST_F(Print0x829dTest_1396, NullExifData_1396) {
    URationalValue value;
    value.value_.push_back({50, 10});
    Exiv2::Internal::print0x829d(os, value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("F") == 0) << "Expected output starting with 'F', got: " << result;
    EXPECT_NE(result.find("5"), std::string::npos) << "Expected '5' in output, got: " << result;
}

// Test that the function returns a reference to the same ostream
TEST_F(Print0x829dTest_1396, ReturnsOstream_1396) {
    URationalValue value;
    value.value_.push_back({28, 10});
    std::ostream& returned = Exiv2::Internal::print0x829d(os, value, nullptr);
    EXPECT_EQ(&returned, &os);
}

// Test returns ostream reference when denominator is zero
TEST_F(Print0x829dTest_1396, ReturnsOstreamZeroDenom_1396) {
    URationalValue value;
    value.value_.push_back({28, 0});
    std::ostream& returned = Exiv2::Internal::print0x829d(os, value, nullptr);
    EXPECT_EQ(&returned, &os);
}

// Test F1.4 (common aperture)
TEST_F(Print0x829dTest_1396, FNumber_F1_4_1396) {
    URationalValue value;
    value.value_.push_back({14, 10});
    Exiv2::Internal::print0x829d(os, value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("F") == 0) << "Expected output starting with 'F', got: " << result;
    EXPECT_NE(result.find("1.4"), std::string::npos) << "Expected '1.4' in output, got: " << result;
}

// Test F8
TEST_F(Print0x829dTest_1396, FNumber_F8_1396) {
    URationalValue value;
    value.value_.push_back({8, 1});
    Exiv2::Internal::print0x829d(os, value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("F") == 0) << "Expected output starting with 'F', got: " << result;
    EXPECT_NE(result.find("8"), std::string::npos) << "Expected '8' in output, got: " << result;
}

// Test F11
TEST_F(Print0x829dTest_1396, FNumber_F11_1396) {
    URationalValue value;
    value.value_.push_back({11, 1});
    Exiv2::Internal::print0x829d(os, value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("F") == 0) << "Expected output starting with 'F', got: " << result;
    EXPECT_NE(result.find("11"), std::string::npos) << "Expected '11' in output, got: " << result;
}
