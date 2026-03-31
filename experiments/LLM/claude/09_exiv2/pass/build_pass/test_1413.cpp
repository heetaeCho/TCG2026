#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Forward declaration of the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& print0xa403(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class Print0xa403Test_1413 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test with value 0 -> "Auto"
TEST_F(Print0xa403Test_1413, ValueZeroReturnsAuto_1413) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("0");
    Exiv2::Internal::print0xa403(os, value, nullptr);
    EXPECT_EQ(os.str(), "Auto");
}

// Test with value 1 -> "Manual"
TEST_F(Print0xa403Test_1413, ValueOneReturnsManual_1413) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("1");
    Exiv2::Internal::print0xa403(os, value, nullptr);
    EXPECT_EQ(os.str(), "Manual");
}

// Test with an unknown value (e.g., 2) -> should print something (typically "(2)")
TEST_F(Print0xa403Test_1413, UnknownValuePrintsSomething_1413) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("2");
    Exiv2::Internal::print0xa403(os, value, nullptr);
    std::string result = os.str();
    // Should not be empty, and should not be "Auto" or "Manual"
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "Auto");
    EXPECT_NE(result, "Manual");
}

// Test with a large unknown value
TEST_F(Print0xa403Test_1413, LargeUnknownValue_1413) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("65535");
    Exiv2::Internal::print0xa403(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "Auto");
    EXPECT_NE(result, "Manual");
}

// Test with metadata pointer being non-null (should still work the same)
TEST_F(Print0xa403Test_1413, ValueZeroWithMetadata_1413) {
    Exiv2::ExifData exifData;
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("0");
    Exiv2::Internal::print0xa403(os, value, &exifData);
    EXPECT_EQ(os.str(), "Auto");
}

// Test with metadata pointer being non-null for Manual
TEST_F(Print0xa403Test_1413, ValueOneWithMetadata_1413) {
    Exiv2::ExifData exifData;
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("1");
    Exiv2::Internal::print0xa403(os, value, &exifData);
    EXPECT_EQ(os.str(), "Manual");
}

// Test that the function returns the same ostream reference
TEST_F(Print0xa403Test_1413, ReturnsOstreamReference_1413) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("0");
    std::ostream& result = Exiv2::Internal::print0xa403(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test with signed long value type containing 0
TEST_F(Print0xa403Test_1413, SignedLongValueZero_1413) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("0");
    Exiv2::Internal::print0xa403(os, value, nullptr);
    EXPECT_EQ(os.str(), "Auto");
}

// Test with signed long value type containing 1
TEST_F(Print0xa403Test_1413, SignedLongValueOne_1413) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("1");
    Exiv2::Internal::print0xa403(os, value, nullptr);
    EXPECT_EQ(os.str(), "Manual");
}

// Test boundary: value just above known range
TEST_F(Print0xa403Test_1413, ValueTwoIsUnknown_1413) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("2");
    Exiv2::Internal::print0xa403(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result, "Auto");
    EXPECT_NE(result, "Manual");
}
