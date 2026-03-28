#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Forward declaration of the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& printMinoltaSonyZoneMatching(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class PrintMinoltaSonyZoneMatchingTest_1037 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test normal case: value 0 should print "ISO Setting Used"
TEST_F(PrintMinoltaSonyZoneMatchingTest_1037, Value0_ISOSettingUsed_1037) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("0");
    Exiv2::Internal::printMinoltaSonyZoneMatching(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "ISO Setting Used");
}

// Test normal case: value 1 should print "High Key"
TEST_F(PrintMinoltaSonyZoneMatchingTest_1037, Value1_HighKey_1037) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("1");
    Exiv2::Internal::printMinoltaSonyZoneMatching(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "High Key");
}

// Test normal case: value 2 should print "Low Key"
TEST_F(PrintMinoltaSonyZoneMatchingTest_1037, Value2_LowKey_1037) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("2");
    Exiv2::Internal::printMinoltaSonyZoneMatching(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "Low Key");
}

// Test boundary/error case: value 3 is out of range - should print unknown/numeric
TEST_F(PrintMinoltaSonyZoneMatchingTest_1037, Value3_OutOfRange_1037) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("3");
    Exiv2::Internal::printMinoltaSonyZoneMatching(oss, value, nullptr);
    std::string result = oss.str();
    // Should not match any known tag description
    EXPECT_NE(result, "ISO Setting Used");
    EXPECT_NE(result, "High Key");
    EXPECT_NE(result, "Low Key");
    // Typically prints "(3)" or "3" for unknown values
    EXPECT_FALSE(result.empty());
}

// Test boundary/error case: large value out of range
TEST_F(PrintMinoltaSonyZoneMatchingTest_1037, LargeValue_OutOfRange_1037) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("65535");
    Exiv2::Internal::printMinoltaSonyZoneMatching(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_NE(result, "ISO Setting Used");
    EXPECT_NE(result, "High Key");
    EXPECT_NE(result, "Low Key");
    EXPECT_FALSE(result.empty());
}

// Test with ExifData pointer being non-null (should still work the same)
TEST_F(PrintMinoltaSonyZoneMatchingTest_1037, WithExifData_Value0_1037) {
    Exiv2::ExifData exifData;
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("0");
    Exiv2::Internal::printMinoltaSonyZoneMatching(oss, value, &exifData);
    EXPECT_EQ(oss.str(), "ISO Setting Used");
}

// Test with ExifData pointer being non-null for value 2
TEST_F(PrintMinoltaSonyZoneMatchingTest_1037, WithExifData_Value2_1037) {
    Exiv2::ExifData exifData;
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("2");
    Exiv2::Internal::printMinoltaSonyZoneMatching(oss, value, &exifData);
    EXPECT_EQ(oss.str(), "Low Key");
}

// Test that the function returns the same ostream reference
TEST_F(PrintMinoltaSonyZoneMatchingTest_1037, ReturnsOstreamReference_1037) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("1");
    std::ostream& result = Exiv2::Internal::printMinoltaSonyZoneMatching(oss, value, nullptr);
    EXPECT_EQ(&result, &oss);
}

// Test with signed long value type
TEST_F(PrintMinoltaSonyZoneMatchingTest_1037, SignedLongValue0_1037) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("0");
    Exiv2::Internal::printMinoltaSonyZoneMatching(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "ISO Setting Used");
}

// Test chaining - write to stream that already has content
TEST_F(PrintMinoltaSonyZoneMatchingTest_1037, StreamChaining_1037) {
    oss << "Prefix: ";
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("1");
    Exiv2::Internal::printMinoltaSonyZoneMatching(oss, value, nullptr);
    EXPECT_EQ(oss.str(), "Prefix: High Key");
}
