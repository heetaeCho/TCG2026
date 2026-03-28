#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// We need access to the internal function and tag details
namespace Exiv2 {
namespace Internal {
std::ostream& print0x0009(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class Print0x0009Test_1387 : public ::testing::Test {
protected:
    std::ostringstream os_;
};

// Test normal case: GPS Status 'A' (Measurement in progress)
TEST_F(Print0x0009Test_1387, StatusA_MeasurementInProgress_1387) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("A");
    
    os_.str("");
    Exiv2::Internal::print0x0009(os_, *value, nullptr);
    
    std::string result = os_.str();
    EXPECT_NE(result.find("Measurement in progress"), std::string::npos)
        << "Expected 'Measurement in progress' but got: " << result;
}

// Test normal case: GPS Status 'V' (Measurement interrupted)
TEST_F(Print0x0009Test_1387, StatusV_MeasurementInterrupted_1387) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("V");
    
    os_.str("");
    Exiv2::Internal::print0x0009(os_, *value, nullptr);
    
    std::string result = os_.str();
    EXPECT_NE(result.find("Measurement interrupted"), std::string::npos)
        << "Expected 'Measurement interrupted' but got: " << result;
}

// Test with integer value for 'A' (ASCII 65)
TEST_F(Print0x0009Test_1387, IntegerValueA_1387) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("65"); // ASCII 'A'
    
    os_.str("");
    Exiv2::Internal::print0x0009(os_, *value, nullptr);
    
    std::string result = os_.str();
    // Should print something - either the translated value or the raw number
    EXPECT_FALSE(result.empty());
}

// Test with integer value for 'V' (ASCII 86)
TEST_F(Print0x0009Test_1387, IntegerValueV_1387) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("86"); // ASCII 'V'
    
    os_.str("");
    Exiv2::Internal::print0x0009(os_, *value, nullptr);
    
    std::string result = os_.str();
    EXPECT_FALSE(result.empty());
}

// Test with unknown/invalid value
TEST_F(Print0x0009Test_1387, UnknownValue_1387) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("X");
    
    os_.str("");
    Exiv2::Internal::print0x0009(os_, *value, nullptr);
    
    std::string result = os_.str();
    // Should produce some output even for unknown values
    EXPECT_FALSE(result.empty());
}

// Test with nullptr metadata
TEST_F(Print0x0009Test_1387, NullMetadata_1387) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("A");
    
    os_.str("");
    // Should not crash with nullptr metadata
    Exiv2::Internal::print0x0009(os_, *value, nullptr);
    
    std::string result = os_.str();
    EXPECT_FALSE(result.empty());
}

// Test with valid ExifData metadata
TEST_F(Print0x0009Test_1387, WithExifData_1387) {
    Exiv2::ExifData exifData;
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("A");
    
    os_.str("");
    Exiv2::Internal::print0x0009(os_, *value, &exifData);
    
    std::string result = os_.str();
    EXPECT_NE(result.find("Measurement in progress"), std::string::npos)
        << "Expected 'Measurement in progress' but got: " << result;
}

// Test that the function returns the same ostream reference
TEST_F(Print0x0009Test_1387, ReturnsOstream_1387) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("A");
    
    std::ostream& returned = Exiv2::Internal::print0x0009(os_, *value, nullptr);
    
    EXPECT_EQ(&returned, &os_);
}

// Test with empty string value
TEST_F(Print0x0009Test_1387, EmptyValue_1387) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("");
    
    os_.str("");
    // Should not crash with empty value
    Exiv2::Internal::print0x0009(os_, *value, nullptr);
    
    // Just verify it doesn't crash; output may vary
}

// Test with unsigned byte type value for 'A'
TEST_F(Print0x0009Test_1387, UnsignedByteValueA_1387) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedByte);
    value->read("65"); // ASCII 'A'
    
    os_.str("");
    Exiv2::Internal::print0x0009(os_, *value, nullptr);
    
    std::string result = os_.str();
    EXPECT_FALSE(result.empty());
}

// Test with a numeric value that doesn't correspond to any known tag
TEST_F(Print0x0009Test_1387, NumericUnknownValue_1387) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("999");
    
    os_.str("");
    Exiv2::Internal::print0x0009(os_, *value, nullptr);
    
    std::string result = os_.str();
    // Should produce some output for unknown numeric values
    EXPECT_FALSE(result.empty());
}

// Test chaining: write to stream that already has content
TEST_F(Print0x0009Test_1387, StreamChaining_1387) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("A");
    
    os_ << "prefix: ";
    Exiv2::Internal::print0x0009(os_, *value, nullptr);
    
    std::string result = os_.str();
    EXPECT_TRUE(result.find("prefix: ") == 0);
    EXPECT_NE(result.find("Measurement in progress"), std::string::npos);
}
