#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Forward declaration of the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& print0x9207(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class Print0x9207Test_1404 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test metering mode "Unknown" (value 0)
TEST_F(Print0x9207Test_1404, MeteringModeUnknown_1404) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    Exiv2::Internal::print0x9207(oss, *value, nullptr);
    EXPECT_EQ(oss.str(), "Unknown");
}

// Test metering mode "Average" (value 1)
TEST_F(Print0x9207Test_1404, MeteringModeAverage_1404) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    Exiv2::Internal::print0x9207(oss, *value, nullptr);
    EXPECT_EQ(oss.str(), "Average");
}

// Test metering mode "Center weighted average" (value 2)
TEST_F(Print0x9207Test_1404, MeteringModeCenterWeightedAverage_1404) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("2");
    Exiv2::Internal::print0x9207(oss, *value, nullptr);
    EXPECT_EQ(oss.str(), "Center weighted average");
}

// Test metering mode "Spot" (value 3)
TEST_F(Print0x9207Test_1404, MeteringModeSpot_1404) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("3");
    Exiv2::Internal::print0x9207(oss, *value, nullptr);
    EXPECT_EQ(oss.str(), "Spot");
}

// Test metering mode "Multi-spot" (value 4)
TEST_F(Print0x9207Test_1404, MeteringModeMultiSpot_1404) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("4");
    Exiv2::Internal::print0x9207(oss, *value, nullptr);
    EXPECT_EQ(oss.str(), "Multi-spot");
}

// Test metering mode "Multi-segment" (value 5)
TEST_F(Print0x9207Test_1404, MeteringModeMultiSegment_1404) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("5");
    Exiv2::Internal::print0x9207(oss, *value, nullptr);
    EXPECT_EQ(oss.str(), "Multi-segment");
}

// Test metering mode "Partial" (value 6)
TEST_F(Print0x9207Test_1404, MeteringModePartial_1404) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("6");
    Exiv2::Internal::print0x9207(oss, *value, nullptr);
    EXPECT_EQ(oss.str(), "Partial");
}

// Test metering mode "Other" (value 255)
TEST_F(Print0x9207Test_1404, MeteringModeOther_1404) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("255");
    Exiv2::Internal::print0x9207(oss, *value, nullptr);
    EXPECT_EQ(oss.str(), "Other");
}

// Test with an undefined/unknown value (value 7, not in the tag details)
TEST_F(Print0x9207Test_1404, MeteringModeUndefinedValue_1404) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("7");
    Exiv2::Internal::print0x9207(oss, *value, nullptr);
    // For unknown values, EXV_PRINT_TAG typically prints "(7)"
    EXPECT_EQ(oss.str(), "(7)");
}

// Test with another undefined value (value 100)
TEST_F(Print0x9207Test_1404, MeteringModeUndefinedValue100_1404) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("100");
    Exiv2::Internal::print0x9207(oss, *value, nullptr);
    EXPECT_EQ(oss.str(), "(100)");
}

// Test with value 254 (not in the table, between 6 and 255)
TEST_F(Print0x9207Test_1404, MeteringModeUndefinedValue254_1404) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("254");
    Exiv2::Internal::print0x9207(oss, *value, nullptr);
    EXPECT_EQ(oss.str(), "(254)");
}

// Test with metadata pointer being non-null (should still work the same)
TEST_F(Print0x9207Test_1404, MeteringModeWithMetadata_1404) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("3");
    Exiv2::Internal::print0x9207(oss, *value, &exifData);
    EXPECT_EQ(oss.str(), "Spot");
}

// Test that the function returns the same ostream reference
TEST_F(Print0x9207Test_1404, ReturnsOstreamReference_1404) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    std::ostream& result = Exiv2::Internal::print0x9207(oss, *value, nullptr);
    EXPECT_EQ(&result, &oss);
}

// Test with a negative-like value (large unsigned short value, e.g., 65535)
TEST_F(Print0x9207Test_1404, MeteringModeLargeValue_1404) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("65535");
    Exiv2::Internal::print0x9207(oss, *value, nullptr);
    // 65535 is not in the table, so it should print the numeric value
    EXPECT_EQ(oss.str(), "(65535)");
}

// Test using unsignedLong type value
TEST_F(Print0x9207Test_1404, MeteringModeWithUnsignedLongType_1404) {
    auto value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("2");
    Exiv2::Internal::print0x9207(oss, *value, nullptr);
    EXPECT_EQ(oss.str(), "Center weighted average");
}
