#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>

// Forward declaration of the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& printMinoltaSonyDynamicRangeOptimizerMode(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class PrintMinoltaSonyDynamicRangeOptimizerModeTest_1031 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test known tag value: 0 -> "Off"
TEST_F(PrintMinoltaSonyDynamicRangeOptimizerModeTest_1031, ValueOff_1031) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("0");
    Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "Off");
}

// Test known tag value: 1 -> "Standard"
TEST_F(PrintMinoltaSonyDynamicRangeOptimizerModeTest_1031, ValueStandard_1031) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("1");
    Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "Standard");
}

// Test known tag value: 2 -> "Advanced Auto"
TEST_F(PrintMinoltaSonyDynamicRangeOptimizerModeTest_1031, ValueAdvancedAuto_1031) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("2");
    Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "Advanced Auto");
}

// Test known tag value: 3 -> "Advanced Level"
TEST_F(PrintMinoltaSonyDynamicRangeOptimizerModeTest_1031, ValueAdvancedLevel_1031) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("3");
    Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "Advanced Level");
}

// Test known tag value: 4097 -> "Auto"
TEST_F(PrintMinoltaSonyDynamicRangeOptimizerModeTest_1031, ValueAuto_1031) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("4097");
    Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "Auto");
}

// Test unknown tag value: should print something (typically "(n)")
TEST_F(PrintMinoltaSonyDynamicRangeOptimizerModeTest_1031, UnknownValue_1031) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("999");
    Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(oss, value, nullptr);
    std::string result = oss.str();
    // Should not be empty; for unknown values EXV_PRINT_TAG typically prints "(n)"
    EXPECT_FALSE(result.empty());
    // It should not match any known label
    EXPECT_NE(result, "Off");
    EXPECT_NE(result, "Standard");
    EXPECT_NE(result, "Advanced Auto");
    EXPECT_NE(result, "Advanced Level");
    EXPECT_NE(result, "Auto");
}

// Test negative unknown value
TEST_F(PrintMinoltaSonyDynamicRangeOptimizerModeTest_1031, NegativeUnknownValue_1031) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("-1");
    Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "Off");
    EXPECT_NE(result, "Standard");
    EXPECT_NE(result, "Advanced Auto");
    EXPECT_NE(result, "Advanced Level");
    EXPECT_NE(result, "Auto");
}

// Test with non-null metadata pointer
TEST_F(PrintMinoltaSonyDynamicRangeOptimizerModeTest_1031, WithMetadata_1031) {
    Exiv2::ExifData exifData;
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("1");
    Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(oss, value, &exifData);
    EXPECT_EQ(oss.str(), "Standard");
}

// Test boundary: value just above the last sequential entry (4)
TEST_F(PrintMinoltaSonyDynamicRangeOptimizerModeTest_1031, BoundaryValueFour_1031) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("4");
    Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(oss, value, nullptr);
    std::string result = oss.str();
    // 4 is not in the known tag details, so should be unknown
    EXPECT_NE(result, "Off");
    EXPECT_NE(result, "Standard");
    EXPECT_NE(result, "Advanced Auto");
    EXPECT_NE(result, "Advanced Level");
    EXPECT_NE(result, "Auto");
}

// Test boundary: value 4096 (one less than 4097 "Auto")
TEST_F(PrintMinoltaSonyDynamicRangeOptimizerModeTest_1031, BoundaryValue4096_1031) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("4096");
    Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_NE(result, "Auto");
}

// Test boundary: value 4098 (one more than 4097 "Auto")
TEST_F(PrintMinoltaSonyDynamicRangeOptimizerModeTest_1031, BoundaryValue4098_1031) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("4098");
    Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_NE(result, "Auto");
}

// Test that the function returns the same ostream reference
TEST_F(PrintMinoltaSonyDynamicRangeOptimizerModeTest_1031, ReturnsOstreamReference_1031) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("0");
    std::ostream& result = Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(oss, value, nullptr);
    EXPECT_EQ(&result, &oss);
}

// Test large unknown value
TEST_F(PrintMinoltaSonyDynamicRangeOptimizerModeTest_1031, LargeUnknownValue_1031) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("100000");
    Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// Test using unsigned short value type
TEST_F(PrintMinoltaSonyDynamicRangeOptimizerModeTest_1031, UnsignedShortValueType_1031) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("1");
    Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "Standard");
}
