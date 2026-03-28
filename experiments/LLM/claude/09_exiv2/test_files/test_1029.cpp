#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Forward declaration of the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& printMinoltaSonyAFAreaMode(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class PrintMinoltaSonyAFAreaModeTest_1029 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test normal case: value 0 should print "Wide"
TEST_F(PrintMinoltaSonyAFAreaModeTest_1029, Value0PrintsWide_1029) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("0");
    Exiv2::Internal::printMinoltaSonyAFAreaMode(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "Wide");
}

// Test normal case: value 1 should print "Local"
TEST_F(PrintMinoltaSonyAFAreaModeTest_1029, Value1PrintsLocal_1029) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("1");
    Exiv2::Internal::printMinoltaSonyAFAreaMode(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "Local");
}

// Test normal case: value 2 should print "Spot"
TEST_F(PrintMinoltaSonyAFAreaModeTest_1029, Value2PrintsSpot_1029) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("2");
    Exiv2::Internal::printMinoltaSonyAFAreaMode(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "Spot");
}

// Test boundary/error case: value 3 is out of range, should print something (likely the numeric value)
TEST_F(PrintMinoltaSonyAFAreaModeTest_1029, Value3OutOfRange_1029) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("3");
    Exiv2::Internal::printMinoltaSonyAFAreaMode(oss, value, nullptr);
    std::string result = oss.str();
    // Out of range values typically print "(3)" or just "3"
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "Wide");
    EXPECT_NE(result, "Local");
    EXPECT_NE(result, "Spot");
}

// Test boundary/error case: large value out of range
TEST_F(PrintMinoltaSonyAFAreaModeTest_1029, LargeValueOutOfRange_1029) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("255");
    Exiv2::Internal::printMinoltaSonyAFAreaMode(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "Wide");
    EXPECT_NE(result, "Local");
    EXPECT_NE(result, "Spot");
}

// Test that the function returns the ostream reference
TEST_F(PrintMinoltaSonyAFAreaModeTest_1029, ReturnsOstreamReference_1029) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("0");
    std::ostream& result = Exiv2::Internal::printMinoltaSonyAFAreaMode(oss, value, nullptr);
    EXPECT_EQ(&result, &oss);
}

// Test with ExifData pointer being non-null (should still work the same)
TEST_F(PrintMinoltaSonyAFAreaModeTest_1029, NonNullMetadata_1029) {
    Exiv2::ExifData exifData;
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("1");
    Exiv2::Internal::printMinoltaSonyAFAreaMode(oss, value, &exifData);
    EXPECT_EQ(oss.str(), "Local");
}

// Test with signed short value type for value 0
TEST_F(PrintMinoltaSonyAFAreaModeTest_1029, SignedShortValue0_1029) {
    Exiv2::ValueType<int16_t> value(Exiv2::signedShort);
    value.read("0");
    Exiv2::Internal::printMinoltaSonyAFAreaMode(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "Wide");
}

// Test with unsigned long value type for value 2
TEST_F(PrintMinoltaSonyAFAreaModeTest_1029, UnsignedLongValue2_1029) {
    Exiv2::ValueType<uint32_t> value(Exiv2::unsignedLong);
    value.read("2");
    Exiv2::Internal::printMinoltaSonyAFAreaMode(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "Spot");
}

// Test negative value (out of range)
TEST_F(PrintMinoltaSonyAFAreaModeTest_1029, NegativeValueOutOfRange_1029) {
    Exiv2::ValueType<int16_t> value(Exiv2::signedShort);
    value.read("-1");
    Exiv2::Internal::printMinoltaSonyAFAreaMode(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "Wide");
    EXPECT_NE(result, "Local");
    EXPECT_NE(result, "Spot");
}
