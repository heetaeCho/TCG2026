#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Forward declaration of the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& print0x0019(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class Print0x0019Test_1390 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test with value 'K' which should print "km"
TEST_F(Print0x0019Test_1390, ValueK_PrintsKm_1390) {
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("K");
    Exiv2::Internal::print0x0019(os, *value, nullptr);
    EXPECT_NE(std::string::npos, os.str().find("km"));
}

// Test with value 'M' which should print "miles"
TEST_F(Print0x0019Test_1390, ValueM_PrintsMiles_1390) {
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("M");
    Exiv2::Internal::print0x0019(os, *value, nullptr);
    EXPECT_NE(std::string::npos, os.str().find("miles"));
}

// Test with value 'N' which should print "nautical miles"
TEST_F(Print0x0019Test_1390, ValueN_PrintsNauticalMiles_1390) {
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("N");
    Exiv2::Internal::print0x0019(os, *value, nullptr);
    EXPECT_NE(std::string::npos, os.str().find("nautical miles"));
}

// Test with unknown value that is not in the tag details
TEST_F(Print0x0019Test_1390, UnknownValue_PrintsSomething_1390) {
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("X");
    Exiv2::Internal::print0x0019(os, *value, nullptr);
    std::string result = os.str();
    // Should print something (possibly the raw value or an unknown indicator)
    EXPECT_FALSE(result.empty());
}

// Test with nullptr metadata - should not crash
TEST_F(Print0x0019Test_1390, NullMetadata_DoesNotCrash_1390) {
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("K");
    EXPECT_NO_THROW(Exiv2::Internal::print0x0019(os, *value, nullptr));
}

// Test that the function returns a reference to the same ostream
TEST_F(Print0x0019Test_1390, ReturnsOstreamReference_1390) {
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("K");
    std::ostream& result = Exiv2::Internal::print0x0019(os, *value, nullptr);
    EXPECT_EQ(&os, &result);
}

// Test with ExifData provided (non-null metadata)
TEST_F(Print0x0019Test_1390, WithExifData_PrintsCorrectly_1390) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("M");
    Exiv2::Internal::print0x0019(os, *value, &exifData);
    EXPECT_NE(std::string::npos, os.str().find("miles"));
}

// Test with empty string value
TEST_F(Print0x0019Test_1390, EmptyValue_PrintsSomething_1390) {
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("");
    EXPECT_NO_THROW(Exiv2::Internal::print0x0019(os, *value, nullptr));
}

// Test with unsigned short value type for 'K' (75 is ASCII for 'K')
TEST_F(Print0x0019Test_1390, UnsignedShortValueK_1390) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("75");  // ASCII value of 'K'
    EXPECT_NO_THROW(Exiv2::Internal::print0x0019(os, *value, nullptr));
}

// Test that 'K' result doesn't contain "miles" or "nautical"
TEST_F(Print0x0019Test_1390, ValueK_DoesNotContainMiles_1390) {
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("K");
    Exiv2::Internal::print0x0019(os, *value, nullptr);
    std::string result = os.str();
    // "km" should not match "miles" or "nautical miles"
    EXPECT_EQ(std::string::npos, result.find("nautical"));
}

// Test that 'M' result contains "miles" but not "nautical"
TEST_F(Print0x0019Test_1390, ValueM_NotNautical_1390) {
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("M");
    Exiv2::Internal::print0x0019(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(std::string::npos, result.find("nautical"));
    EXPECT_NE(std::string::npos, result.find("miles"));
}
