#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// We need access to the Internal namespace function
namespace Exiv2 {
namespace Internal {
std::ostream& printValue(std::ostream& os, const Value& value, const ExifData*);
}
}

class PrintValueTest_1372 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test that printValue outputs a simple string value correctly
TEST_F(PrintValueTest_1372, PrintStringValue_1372) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("Hello World");
    
    Exiv2::Internal::printValue(oss, *value, nullptr);
    
    EXPECT_EQ(oss.str(), "Hello World");
}

// Test that printValue works with a null ExifData pointer
TEST_F(PrintValueTest_1372, NullExifDataPointer_1372) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("Test");
    
    Exiv2::Internal::printValue(oss, *value, nullptr);
    
    EXPECT_EQ(oss.str(), "Test");
}

// Test that printValue works with valid ExifData pointer
TEST_F(PrintValueTest_1372, ValidExifDataPointer_1372) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("TestWithExifData");
    
    Exiv2::ExifData exifData;
    Exiv2::Internal::printValue(oss, *value, &exifData);
    
    EXPECT_EQ(oss.str(), "TestWithExifData");
}

// Test that printValue returns the same ostream reference
TEST_F(PrintValueTest_1372, ReturnsOstreamReference_1372) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("ref test");
    
    std::ostream& result = Exiv2::Internal::printValue(oss, *value, nullptr);
    
    EXPECT_EQ(&result, &oss);
}

// Test with unsigned short value
TEST_F(PrintValueTest_1372, PrintUnsignedShortValue_1372) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("42");
    
    Exiv2::Internal::printValue(oss, *value, nullptr);
    
    EXPECT_EQ(oss.str(), "42");
}

// Test with unsigned long value
TEST_F(PrintValueTest_1372, PrintUnsignedLongValue_1372) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("123456");
    
    Exiv2::Internal::printValue(oss, *value, nullptr);
    
    EXPECT_EQ(oss.str(), "123456");
}

// Test with signed short value
TEST_F(PrintValueTest_1372, PrintSignedShortValue_1372) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::signedShort);
    value->read("-10");
    
    Exiv2::Internal::printValue(oss, *value, nullptr);
    
    EXPECT_EQ(oss.str(), "-10");
}

// Test with signed long value
TEST_F(PrintValueTest_1372, PrintSignedLongValue_1372) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::signedLong);
    value->read("-99999");
    
    Exiv2::Internal::printValue(oss, *value, nullptr);
    
    EXPECT_EQ(oss.str(), "-99999");
}

// Test with unsigned rational value
TEST_F(PrintValueTest_1372, PrintUnsignedRationalValue_1372) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedRational);
    value->read("1/2");
    
    Exiv2::Internal::printValue(oss, *value, nullptr);
    
    EXPECT_EQ(oss.str(), "1/2");
}

// Test with signed rational value
TEST_F(PrintValueTest_1372, PrintSignedRationalValue_1372) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::signedRational);
    value->read("-3/4");
    
    Exiv2::Internal::printValue(oss, *value, nullptr);
    
    EXPECT_EQ(oss.str(), "-3/4");
}

// Test with empty string value
TEST_F(PrintValueTest_1372, PrintEmptyStringValue_1372) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("");
    
    Exiv2::Internal::printValue(oss, *value, nullptr);
    
    EXPECT_EQ(oss.str(), "");
}

// Test chaining - printValue returns ostream so we can chain
TEST_F(PrintValueTest_1372, ChainingOutput_1372) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("chained");
    
    Exiv2::Internal::printValue(oss, *value, nullptr) << " extra";
    
    EXPECT_EQ(oss.str(), "chained extra");
}

// Test with zero value
TEST_F(PrintValueTest_1372, PrintZeroValue_1372) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    
    Exiv2::Internal::printValue(oss, *value, nullptr);
    
    EXPECT_EQ(oss.str(), "0");
}

// Test with multiple values in unsigned short
TEST_F(PrintValueTest_1372, PrintMultipleUnsignedShortValues_1372) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    value->read("2");
    
    Exiv2::Internal::printValue(oss, *value, nullptr);
    
    // The output should contain both values
    EXPECT_FALSE(oss.str().empty());
}

// Test with large number
TEST_F(PrintValueTest_1372, PrintLargeNumber_1372) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("4294967295");
    
    Exiv2::Internal::printValue(oss, *value, nullptr);
    
    EXPECT_EQ(oss.str(), "4294967295");
}

// Test that ExifData parameter is ignored (same output regardless)
TEST_F(PrintValueTest_1372, ExifDataParameterIgnored_1372) {
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("same output");
    
    std::ostringstream oss1, oss2;
    Exiv2::ExifData exifData;
    
    Exiv2::Internal::printValue(oss1, *value, nullptr);
    Exiv2::Internal::printValue(oss2, *value, &exifData);
    
    EXPECT_EQ(oss1.str(), oss2.str());
}
