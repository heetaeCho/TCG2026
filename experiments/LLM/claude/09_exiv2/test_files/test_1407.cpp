#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Forward declaration of the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& print0xa001(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class Print0xa001Test_1407 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test that value 1 prints "sRGB"
TEST_F(Print0xa001Test_1407, ValueOne_PrintsSRGB_1407) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("1");
    Exiv2::Internal::print0xa001(oss, value, nullptr);
    EXPECT_NE(oss.str().find("sRGB"), std::string::npos);
}

// Test that value 2 prints "Adobe RGB"
TEST_F(Print0xa001Test_1407, ValueTwo_PrintsAdobeRGB_1407) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("2");
    Exiv2::Internal::print0xa001(oss, value, nullptr);
    EXPECT_NE(oss.str().find("Adobe RGB"), std::string::npos);
}

// Test that value 65535 prints "Uncalibrated"
TEST_F(Print0xa001Test_1407, Value65535_PrintsUncalibrated_1407) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("65535");
    Exiv2::Internal::print0xa001(oss, value, nullptr);
    EXPECT_NE(oss.str().find("Uncalibrated"), std::string::npos);
}

// Test that an unknown value (not in the tag details) prints the numeric value
TEST_F(Print0xa001Test_1407, UnknownValue_PrintsNumeric_1407) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("42");
    Exiv2::Internal::print0xa001(oss, value, nullptr);
    std::string result = oss.str();
    // Should not match any known tag string
    EXPECT_EQ(result.find("sRGB"), std::string::npos);
    EXPECT_EQ(result.find("Adobe RGB"), std::string::npos);
    EXPECT_EQ(result.find("Uncalibrated"), std::string::npos);
    // Should contain the numeric value somewhere
    EXPECT_NE(result.find("42"), std::string::npos);
}

// Test that value 0 is not a known tag
TEST_F(Print0xa001Test_1407, ValueZero_PrintsUnknown_1407) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("0");
    Exiv2::Internal::print0xa001(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_EQ(result.find("sRGB"), std::string::npos);
    EXPECT_EQ(result.find("Adobe RGB"), std::string::npos);
    EXPECT_EQ(result.find("Uncalibrated"), std::string::npos);
}

// Test that the function returns a reference to the same ostream
TEST_F(Print0xa001Test_1407, ReturnsOstreamReference_1407) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("1");
    std::ostream& result = Exiv2::Internal::print0xa001(oss, value, nullptr);
    EXPECT_EQ(&result, &oss);
}

// Test with metadata pointer being non-null (should still work for known values)
TEST_F(Print0xa001Test_1407, WithNonNullMetadata_PrintsSRGB_1407) {
    Exiv2::ExifData exifData;
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("1");
    Exiv2::Internal::print0xa001(oss, value, &exifData);
    EXPECT_NE(oss.str().find("sRGB"), std::string::npos);
}

// Test with a large unknown value
TEST_F(Print0xa001Test_1407, LargeUnknownValue_PrintsNumeric_1407) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("1000");
    Exiv2::Internal::print0xa001(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_EQ(result.find("sRGB"), std::string::npos);
    EXPECT_EQ(result.find("Adobe RGB"), std::string::npos);
    EXPECT_EQ(result.find("Uncalibrated"), std::string::npos);
}

// Test boundary: value 65534 (one less than Uncalibrated)
TEST_F(Print0xa001Test_1407, Value65534_IsUnknown_1407) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("65534");
    Exiv2::Internal::print0xa001(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_EQ(result.find("Uncalibrated"), std::string::npos);
}

// Test boundary: value 3 (one more than Adobe RGB)
TEST_F(Print0xa001Test_1407, ValueThree_IsUnknown_1407) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("3");
    Exiv2::Internal::print0xa001(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_EQ(result.find("sRGB"), std::string::npos);
    EXPECT_EQ(result.find("Adobe RGB"), std::string::npos);
    EXPECT_EQ(result.find("Uncalibrated"), std::string::npos);
}
