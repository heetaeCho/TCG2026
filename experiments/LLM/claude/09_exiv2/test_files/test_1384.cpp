#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// We need access to the internal function and tag details
namespace Exiv2 {
namespace Internal {
std::ostream& print0x0005(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class Print0x0005Test_1384 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test normal case: value 0 should print "Above sea level"
TEST_F(Print0x0005Test_1384, AboveSeaLevel_1384) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedByte);
    value->read("0");
    
    Exiv2::Internal::print0x0005(os, *value, nullptr);
    
    EXPECT_NE(std::string::npos, os.str().find("Above sea level"));
}

// Test normal case: value 1 should print "Below sea level"
TEST_F(Print0x0005Test_1384, BelowSeaLevel_1384) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedByte);
    value->read("1");
    
    Exiv2::Internal::print0x0005(os, *value, nullptr);
    
    EXPECT_NE(std::string::npos, os.str().find("Below sea level"));
}

// Test boundary/error case: value 2 (out of range for the tag details)
TEST_F(Print0x0005Test_1384, OutOfRangeValue_1384) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedByte);
    value->read("2");
    
    Exiv2::Internal::print0x0005(os, *value, nullptr);
    
    std::string result = os.str();
    // Should not contain either known label
    // The EXV_PRINT_TAG typically prints "(n)" for unknown values
    EXPECT_EQ(std::string::npos, result.find("Above sea level"));
    EXPECT_EQ(std::string::npos, result.find("Below sea level"));
    EXPECT_FALSE(result.empty());
}

// Test with nullptr metadata (should still work)
TEST_F(Print0x0005Test_1384, NullMetadata_1384) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedByte);
    value->read("0");
    
    Exiv2::Internal::print0x0005(os, *value, nullptr);
    
    EXPECT_NE(std::string::npos, os.str().find("Above sea level"));
}

// Test with valid ExifData metadata
TEST_F(Print0x0005Test_1384, WithExifData_1384) {
    Exiv2::ExifData exifData;
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedByte);
    value->read("1");
    
    Exiv2::Internal::print0x0005(os, *value, &exifData);
    
    EXPECT_NE(std::string::npos, os.str().find("Below sea level"));
}

// Test that the function returns the same ostream reference
TEST_F(Print0x0005Test_1384, ReturnsOstream_1384) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedByte);
    value->read("0");
    
    std::ostream& result = Exiv2::Internal::print0x0005(os, *value, nullptr);
    
    EXPECT_EQ(&os, &result);
}

// Test with a negative/large value (boundary)
TEST_F(Print0x0005Test_1384, LargeValue_1384) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("255");
    
    Exiv2::Internal::print0x0005(os, *value, nullptr);
    
    std::string result = os.str();
    // Unknown value, should not match known labels
    EXPECT_EQ(std::string::npos, result.find("Above sea level"));
    EXPECT_EQ(std::string::npos, result.find("Below sea level"));
    EXPECT_FALSE(result.empty());
}

// Test with signed value type
TEST_F(Print0x0005Test_1384, SignedValueTypeZero_1384) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::signedShort);
    value->read("0");
    
    Exiv2::Internal::print0x0005(os, *value, nullptr);
    
    EXPECT_NE(std::string::npos, os.str().find("Above sea level"));
}

// Test with signed value type for below sea level
TEST_F(Print0x0005Test_1384, SignedValueTypeOne_1384) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::signedShort);
    value->read("1");
    
    Exiv2::Internal::print0x0005(os, *value, nullptr);
    
    EXPECT_NE(std::string::npos, os.str().find("Below sea level"));
}

// Test chaining: write to stream that already has content
TEST_F(Print0x0005Test_1384, StreamChaining_1384) {
    os << "prefix: ";
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedByte);
    value->read("0");
    
    Exiv2::Internal::print0x0005(os, *value, nullptr);
    
    std::string result = os.str();
    EXPECT_NE(std::string::npos, result.find("prefix: "));
    EXPECT_NE(std::string::npos, result.find("Above sea level"));
}
