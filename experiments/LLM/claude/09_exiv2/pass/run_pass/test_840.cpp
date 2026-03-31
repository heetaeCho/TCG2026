#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cstdint>
#include <string>
#include <limits>

class XmpTextValueTest_840 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test normal positive integer conversion
TEST_F(XmpTextValueTest_840, ToUint32_NormalPositiveInteger_840) {
    Exiv2::XmpTextValue value;
    value.read("12345");
    EXPECT_EQ(value.toUint32(0), static_cast<uint32_t>(12345));
}

// Test zero value
TEST_F(XmpTextValueTest_840, ToUint32_Zero_840) {
    Exiv2::XmpTextValue value;
    value.read("0");
    EXPECT_EQ(value.toUint32(0), static_cast<uint32_t>(0));
}

// Test value of 1
TEST_F(XmpTextValueTest_840, ToUint32_One_840) {
    Exiv2::XmpTextValue value;
    value.read("1");
    EXPECT_EQ(value.toUint32(0), static_cast<uint32_t>(1));
}

// Test maximum uint32 value
TEST_F(XmpTextValueTest_840, ToUint32_MaxUint32_840) {
    Exiv2::XmpTextValue value;
    value.read("4294967295");
    EXPECT_EQ(value.toUint32(0), std::numeric_limits<uint32_t>::max());
}

// Test large number within uint32 range
TEST_F(XmpTextValueTest_840, ToUint32_LargeNumber_840) {
    Exiv2::XmpTextValue value;
    value.read("1000000000");
    EXPECT_EQ(value.toUint32(0), static_cast<uint32_t>(1000000000));
}

// Test with n parameter being non-zero (should be ignored per interface)
TEST_F(XmpTextValueTest_840, ToUint32_NonZeroNParameter_840) {
    Exiv2::XmpTextValue value;
    value.read("42");
    EXPECT_EQ(value.toUint32(5), static_cast<uint32_t>(42));
}

// Test empty string
TEST_F(XmpTextValueTest_840, ToUint32_EmptyString_840) {
    Exiv2::XmpTextValue value;
    value.read("");
    // Empty string should not parse to a valid uint32; result may be 0 or undefined
    // We just verify it doesn't crash
    value.toUint32(0);
}

// Test non-numeric string
TEST_F(XmpTextValueTest_840, ToUint32_NonNumericString_840) {
    Exiv2::XmpTextValue value;
    value.read("abc");
    // Non-numeric should return 0 or some default, we verify no crash
    value.toUint32(0);
}

// Test string with leading whitespace
TEST_F(XmpTextValueTest_840, ToUint32_LeadingWhitespace_840) {
    Exiv2::XmpTextValue value;
    value.read("  123");
    // May or may not trim; just verify no crash
    value.toUint32(0);
}

// Test string with trailing whitespace
TEST_F(XmpTextValueTest_840, ToUint32_TrailingWhitespace_840) {
    Exiv2::XmpTextValue value;
    value.read("123  ");
    value.toUint32(0);
}

// Test negative number string
TEST_F(XmpTextValueTest_840, ToUint32_NegativeNumber_840) {
    Exiv2::XmpTextValue value;
    value.read("-1");
    // Negative number for uint32 - behavior depends on implementation
    value.toUint32(0);
}

// Test floating point string
TEST_F(XmpTextValueTest_840, ToUint32_FloatingPoint_840) {
    Exiv2::XmpTextValue value;
    value.read("3.14");
    // Float for uint32 parse - verify no crash
    value.toUint32(0);
}

// Test with various n values to confirm parameter is truly ignored
TEST_F(XmpTextValueTest_840, ToUint32_VariousNValues_840) {
    Exiv2::XmpTextValue value;
    value.read("999");
    uint32_t result0 = value.toUint32(0);
    uint32_t result1 = value.toUint32(1);
    uint32_t result100 = value.toUint32(100);
    EXPECT_EQ(result0, result1);
    EXPECT_EQ(result1, result100);
}

// Test boundary: value just below max uint32
TEST_F(XmpTextValueTest_840, ToUint32_JustBelowMax_840) {
    Exiv2::XmpTextValue value;
    value.read("4294967294");
    EXPECT_EQ(value.toUint32(0), static_cast<uint32_t>(4294967294U));
}

// Test reading and converting multiple times
TEST_F(XmpTextValueTest_840, ToUint32_ReadMultipleTimes_840) {
    Exiv2::XmpTextValue value;
    value.read("100");
    EXPECT_EQ(value.toUint32(0), static_cast<uint32_t>(100));
    value.read("200");
    EXPECT_EQ(value.toUint32(0), static_cast<uint32_t>(200));
}

// Test with string containing only zeros
TEST_F(XmpTextValueTest_840, ToUint32_MultipleZeros_840) {
    Exiv2::XmpTextValue value;
    value.read("0000");
    EXPECT_EQ(value.toUint32(0), static_cast<uint32_t>(0));
}

// Test with leading zeros
TEST_F(XmpTextValueTest_840, ToUint32_LeadingZeros_840) {
    Exiv2::XmpTextValue value;
    value.read("007");
    EXPECT_EQ(value.toUint32(0), static_cast<uint32_t>(7));
}
