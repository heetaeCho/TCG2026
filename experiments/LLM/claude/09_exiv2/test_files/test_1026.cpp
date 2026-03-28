#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Forward declaration of the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& printMinoltaSonyColorMode(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class PrintMinoltaSonyColorModeTest_1026 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test: Standard color mode (value 0)
TEST_F(PrintMinoltaSonyColorModeTest_1026, StandardColorMode_1026) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("0");
    Exiv2::Internal::printMinoltaSonyColorMode(oss, value, nullptr);
    EXPECT_EQ("Standard", oss.str());
}

// Test: Vivid Color mode (value 1)
TEST_F(PrintMinoltaSonyColorModeTest_1026, VividColorMode_1026) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("1");
    Exiv2::Internal::printMinoltaSonyColorMode(oss, value, nullptr);
    EXPECT_EQ("Vivid Color", oss.str());
}

// Test: Portrait mode (value 2)
TEST_F(PrintMinoltaSonyColorModeTest_1026, PortraitMode_1026) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("2");
    Exiv2::Internal::printMinoltaSonyColorMode(oss, value, nullptr);
    EXPECT_EQ("Portrait", oss.str());
}

// Test: Landscape mode (value 3)
TEST_F(PrintMinoltaSonyColorModeTest_1026, LandscapeMode_1026) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("3");
    Exiv2::Internal::printMinoltaSonyColorMode(oss, value, nullptr);
    EXPECT_EQ("Landscape", oss.str());
}

// Test: Sunset mode (value 4)
TEST_F(PrintMinoltaSonyColorModeTest_1026, SunsetMode_1026) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("4");
    Exiv2::Internal::printMinoltaSonyColorMode(oss, value, nullptr);
    EXPECT_EQ("Sunset", oss.str());
}

// Test: Night View/Portrait mode (value 5)
TEST_F(PrintMinoltaSonyColorModeTest_1026, NightViewPortraitMode_1026) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("5");
    Exiv2::Internal::printMinoltaSonyColorMode(oss, value, nullptr);
    EXPECT_EQ("Night View/Portrait", oss.str());
}

// Test: Black & White mode (value 6)
TEST_F(PrintMinoltaSonyColorModeTest_1026, BlackAndWhiteMode_1026) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("6");
    Exiv2::Internal::printMinoltaSonyColorMode(oss, value, nullptr);
    EXPECT_EQ("Black & White", oss.str());
}

// Test: AdobeRGB mode (value 7)
TEST_F(PrintMinoltaSonyColorModeTest_1026, AdobeRGBMode_1026) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("7");
    Exiv2::Internal::printMinoltaSonyColorMode(oss, value, nullptr);
    EXPECT_EQ("AdobeRGB", oss.str());
}

// Test: Neutral mode (value 12)
TEST_F(PrintMinoltaSonyColorModeTest_1026, NeutralMode12_1026) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("12");
    Exiv2::Internal::printMinoltaSonyColorMode(oss, value, nullptr);
    EXPECT_EQ("Neutral", oss.str());
}

// Test: Neutral mode (value 100)
TEST_F(PrintMinoltaSonyColorModeTest_1026, NeutralMode100_1026) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("100");
    Exiv2::Internal::printMinoltaSonyColorMode(oss, value, nullptr);
    EXPECT_EQ("Neutral", oss.str());
}

// Test: Clear mode (value 101)
TEST_F(PrintMinoltaSonyColorModeTest_1026, ClearMode_1026) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("101");
    Exiv2::Internal::printMinoltaSonyColorMode(oss, value, nullptr);
    EXPECT_EQ("Clear", oss.str());
}

// Test: Deep mode (value 102)
TEST_F(PrintMinoltaSonyColorModeTest_1026, DeepMode_1026) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("102");
    Exiv2::Internal::printMinoltaSonyColorMode(oss, value, nullptr);
    EXPECT_EQ("Deep", oss.str());
}

// Test: Light mode (value 103)
TEST_F(PrintMinoltaSonyColorModeTest_1026, LightMode_1026) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("103");
    Exiv2::Internal::printMinoltaSonyColorMode(oss, value, nullptr);
    EXPECT_EQ("Light", oss.str());
}

// Test: Night View mode (value 104)
TEST_F(PrintMinoltaSonyColorModeTest_1026, NightViewMode_1026) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("104");
    Exiv2::Internal::printMinoltaSonyColorMode(oss, value, nullptr);
    EXPECT_EQ("Night View", oss.str());
}

// Test: Autumn Leaves mode (value 105)
TEST_F(PrintMinoltaSonyColorModeTest_1026, AutumnLeavesMode_1026) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("105");
    Exiv2::Internal::printMinoltaSonyColorMode(oss, value, nullptr);
    EXPECT_EQ("Autumn Leaves", oss.str());
}

// Test: Unknown value (value 8, not in the table)
TEST_F(PrintMinoltaSonyColorModeTest_1026, UnknownValue8_1026) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("8");
    Exiv2::Internal::printMinoltaSonyColorMode(oss, value, nullptr);
    // Unknown values typically print as "(8)"
    EXPECT_EQ("(8)", oss.str());
}

// Test: Unknown value (value -1, negative)
TEST_F(PrintMinoltaSonyColorModeTest_1026, UnknownNegativeValue_1026) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("-1");
    Exiv2::Internal::printMinoltaSonyColorMode(oss, value, nullptr);
    // Negative values should be unknown
    std::string result = oss.str();
    EXPECT_NE(std::string::npos, result.find("-1"));
}

// Test: Unknown value (value 999, large number not in table)
TEST_F(PrintMinoltaSonyColorModeTest_1026, UnknownLargeValue_1026) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("999");
    Exiv2::Internal::printMinoltaSonyColorMode(oss, value, nullptr);
    EXPECT_EQ("(999)", oss.str());
}

// Test: Unknown value in gap (value 10, between 7 and 12)
TEST_F(PrintMinoltaSonyColorModeTest_1026, UnknownGapValue10_1026) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("10");
    Exiv2::Internal::printMinoltaSonyColorMode(oss, value, nullptr);
    EXPECT_EQ("(10)", oss.str());
}

// Test: Unknown value in gap (value 50, between 12 and 100)
TEST_F(PrintMinoltaSonyColorModeTest_1026, UnknownGapValue50_1026) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("50");
    Exiv2::Internal::printMinoltaSonyColorMode(oss, value, nullptr);
    EXPECT_EQ("(50)", oss.str());
}

// Test: Unknown value just after last entry (value 106)
TEST_F(PrintMinoltaSonyColorModeTest_1026, UnknownValueJustAfterLast_1026) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("106");
    Exiv2::Internal::printMinoltaSonyColorMode(oss, value, nullptr);
    EXPECT_EQ("(106)", oss.str());
}

// Test: With non-null metadata pointer (should still work for known values)
TEST_F(PrintMinoltaSonyColorModeTest_1026, WithMetadataPointer_1026) {
    Exiv2::ExifData exifData;
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("0");
    Exiv2::Internal::printMinoltaSonyColorMode(oss, value, &exifData);
    EXPECT_EQ("Standard", oss.str());
}

// Test: Value 11 (between 7 and 12, gap)
TEST_F(PrintMinoltaSonyColorModeTest_1026, UnknownGapValue11_1026) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("11");
    Exiv2::Internal::printMinoltaSonyColorMode(oss, value, nullptr);
    EXPECT_EQ("(11)", oss.str());
}

// Test: Value 99 (just before 100)
TEST_F(PrintMinoltaSonyColorModeTest_1026, UnknownValue99_1026) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("99");
    Exiv2::Internal::printMinoltaSonyColorMode(oss, value, nullptr);
    EXPECT_EQ("(99)", oss.str());
}

// Test: Return value is the same stream
TEST_F(PrintMinoltaSonyColorModeTest_1026, ReturnsSameStream_1026) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("0");
    std::ostream& result = Exiv2::Internal::printMinoltaSonyColorMode(oss, value, nullptr);
    EXPECT_EQ(&oss, &result);
}

// Test: Using unsigned short value type
TEST_F(PrintMinoltaSonyColorModeTest_1026, UnsignedShortValueType_1026) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("3");
    Exiv2::Internal::printMinoltaSonyColorMode(oss, value, nullptr);
    EXPECT_EQ("Landscape", oss.str());
}
