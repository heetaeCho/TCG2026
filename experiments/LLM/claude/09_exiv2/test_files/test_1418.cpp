#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// We need access to the internal function and tag details
namespace Exiv2 {
namespace Internal {
std::ostream& print0xa409(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class Print0xa409Test_1418 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test normal operation: value 0 should print "Normal"
TEST_F(Print0xa409Test_1418, ValueZeroPrintsNormal_1418) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("0");
    Exiv2::Internal::print0xa409(os, value, nullptr);
    EXPECT_EQ(os.str(), "Normal");
}

// Test normal operation: value 1 should print "Low"
TEST_F(Print0xa409Test_1418, ValueOnePrintsLow_1418) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("1");
    Exiv2::Internal::print0xa409(os, value, nullptr);
    EXPECT_EQ(os.str(), "Low");
}

// Test normal operation: value 2 should print "High"
TEST_F(Print0xa409Test_1418, ValueTwoPrintsHigh_1418) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("2");
    Exiv2::Internal::print0xa409(os, value, nullptr);
    EXPECT_EQ(os.str(), "High");
}

// Test boundary: value just outside the known range (3) should print something (likely the numeric value)
TEST_F(Print0xa409Test_1418, ValueThreeOutOfRange_1418) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("3");
    Exiv2::Internal::print0xa409(os, value, nullptr);
    std::string result = os.str();
    // Unknown values typically print as "(3)"
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "Normal");
    EXPECT_NE(result, "Low");
    EXPECT_NE(result, "High");
}

// Test with a large unknown value
TEST_F(Print0xa409Test_1418, LargeUnknownValue_1418) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("65535");
    Exiv2::Internal::print0xa409(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "Normal");
    EXPECT_NE(result, "Low");
    EXPECT_NE(result, "High");
}

// Test that the function returns the same ostream reference
TEST_F(Print0xa409Test_1418, ReturnsSameOstream_1418) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("0");
    std::ostream& returned = Exiv2::Internal::print0xa409(os, value, nullptr);
    EXPECT_EQ(&returned, &os);
}

// Test with non-null ExifData pointer (should still work for known values)
TEST_F(Print0xa409Test_1418, WithExifDataNormal_1418) {
    Exiv2::ExifData exifData;
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("0");
    Exiv2::Internal::print0xa409(os, value, &exifData);
    EXPECT_EQ(os.str(), "Normal");
}

// Test with non-null ExifData pointer for value 1
TEST_F(Print0xa409Test_1418, WithExifDataLow_1418) {
    Exiv2::ExifData exifData;
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("1");
    Exiv2::Internal::print0xa409(os, value, &exifData);
    EXPECT_EQ(os.str(), "Low");
}

// Test with non-null ExifData pointer for value 2
TEST_F(Print0xa409Test_1418, WithExifDataHigh_1418) {
    Exiv2::ExifData exifData;
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("2");
    Exiv2::Internal::print0xa409(os, value, &exifData);
    EXPECT_EQ(os.str(), "High");
}

// Test with signed long value type for known saturation value
TEST_F(Print0xa409Test_1418, SignedLongValueNormal_1418) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("0");
    Exiv2::Internal::print0xa409(os, value, nullptr);
    EXPECT_EQ(os.str(), "Normal");
}

// Test with signed long value type for value 2
TEST_F(Print0xa409Test_1418, SignedLongValueHigh_1418) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("2");
    Exiv2::Internal::print0xa409(os, value, nullptr);
    EXPECT_EQ(os.str(), "High");
}

// Test that consecutive calls append to the stream
TEST_F(Print0xa409Test_1418, ConsecutiveCallsAppend_1418) {
    Exiv2::ValueType<uint16_t> value0(Exiv2::unsignedShort);
    value0.read("0");
    Exiv2::Internal::print0xa409(os, value0, nullptr);
    
    Exiv2::ValueType<uint16_t> value1(Exiv2::unsignedShort);
    value1.read("1");
    Exiv2::Internal::print0xa409(os, value1, nullptr);
    
    std::string result = os.str();
    EXPECT_EQ(result, "NormalLow");
}
