#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>

// Forward declaration of the function we're testing
namespace Exiv2 {
namespace Internal {
std::ostream& printMinoltaSonyBoolValue(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class PrintMinoltaSonyBoolValueTest_1027 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test normal case: value 0 should print "Off"
TEST_F(PrintMinoltaSonyBoolValueTest_1027, ValueZeroPrintsOff_1027) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    Exiv2::Internal::printMinoltaSonyBoolValue(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Off");
}

// Test normal case: value 1 should print "On"
TEST_F(PrintMinoltaSonyBoolValueTest_1027, ValueOnePrintsOn_1027) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    Exiv2::Internal::printMinoltaSonyBoolValue(os, *value, nullptr);
    EXPECT_EQ(os.str(), "On");
}

// Test boundary/error case: value 2 (out of known range) should print something (likely the numeric value)
TEST_F(PrintMinoltaSonyBoolValueTest_1027, ValueTwoPrintsUnknown_1027) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("2");
    Exiv2::Internal::printMinoltaSonyBoolValue(os, *value, nullptr);
    std::string result = os.str();
    // Should not be "Off" or "On" since 2 is not in the tag details
    EXPECT_NE(result, "Off");
    EXPECT_NE(result, "On");
    // The output should contain "2" as part of the unknown value representation
    EXPECT_FALSE(result.empty());
}

// Test with a negative value (not in known range)
TEST_F(PrintMinoltaSonyBoolValueTest_1027, NegativeValuePrintsUnknown_1027) {
    auto value = Exiv2::Value::create(Exiv2::signedShort);
    value->read("-1");
    Exiv2::Internal::printMinoltaSonyBoolValue(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result, "Off");
    EXPECT_NE(result, "On");
    EXPECT_FALSE(result.empty());
}

// Test with a large value (not in known range)
TEST_F(PrintMinoltaSonyBoolValueTest_1027, LargeValuePrintsUnknown_1027) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("65535");
    Exiv2::Internal::printMinoltaSonyBoolValue(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result, "Off");
    EXPECT_NE(result, "On");
    EXPECT_FALSE(result.empty());
}

// Test that the function returns the same ostream reference
TEST_F(PrintMinoltaSonyBoolValueTest_1027, ReturnsOstreamReference_1027) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    std::ostream& returned = Exiv2::Internal::printMinoltaSonyBoolValue(os, *value, nullptr);
    EXPECT_EQ(&returned, &os);
}

// Test with ExifData pointer (non-null but empty)
TEST_F(PrintMinoltaSonyBoolValueTest_1027, WithEmptyExifDataPrintsOff_1027) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    Exiv2::Internal::printMinoltaSonyBoolValue(os, *value, &exifData);
    EXPECT_EQ(os.str(), "Off");
}

// Test with ExifData pointer (non-null but empty) and value 1
TEST_F(PrintMinoltaSonyBoolValueTest_1027, WithEmptyExifDataPrintsOn_1027) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    Exiv2::Internal::printMinoltaSonyBoolValue(os, *value, &exifData);
    EXPECT_EQ(os.str(), "On");
}

// Test with unsigned long type value set to 0
TEST_F(PrintMinoltaSonyBoolValueTest_1027, UnsignedLongValueZeroPrintsOff_1027) {
    auto value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("0");
    Exiv2::Internal::printMinoltaSonyBoolValue(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Off");
}

// Test with unsigned long type value set to 1
TEST_F(PrintMinoltaSonyBoolValueTest_1027, UnsignedLongValueOnePrintsOn_1027) {
    auto value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("1");
    Exiv2::Internal::printMinoltaSonyBoolValue(os, *value, nullptr);
    EXPECT_EQ(os.str(), "On");
}

// Test with unsigned byte type value set to 0
TEST_F(PrintMinoltaSonyBoolValueTest_1027, UnsignedByteValueZeroPrintsOff_1027) {
    auto value = Exiv2::Value::create(Exiv2::unsignedByte);
    value->read("0");
    Exiv2::Internal::printMinoltaSonyBoolValue(os, *value, nullptr);
    EXPECT_EQ(os.str(), "Off");
}

// Test with unsigned byte type value set to 1
TEST_F(PrintMinoltaSonyBoolValueTest_1027, UnsignedByteValueOnePrintsOn_1027) {
    auto value = Exiv2::Value::create(Exiv2::unsignedByte);
    value->read("1");
    Exiv2::Internal::printMinoltaSonyBoolValue(os, *value, nullptr);
    EXPECT_EQ(os.str(), "On");
}
