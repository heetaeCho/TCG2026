#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// We need access to the internal function and tag details
namespace Exiv2 {
namespace Internal {
std::ostream& print0x001e(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class Print0x001eTest_1391 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test normal case: value 0 should print "Without correction"
TEST_F(Print0x001eTest_1391, ValueZeroPrintsWithoutCorrection_1391) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    
    Exiv2::Internal::print0x001e(os, *value, nullptr);
    
    EXPECT_NE(std::string::npos, os.str().find("Without correction"));
}

// Test normal case: value 1 should print "Correction applied"
TEST_F(Print0x001eTest_1391, ValueOnePrintsCorrectionApplied_1391) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    
    Exiv2::Internal::print0x001e(os, *value, nullptr);
    
    EXPECT_NE(std::string::npos, os.str().find("Correction applied"));
}

// Test boundary/error case: value 2 (out of defined range) 
TEST_F(Print0x001eTest_1391, ValueTwoUnknown_1391) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("2");
    
    Exiv2::Internal::print0x001e(os, *value, nullptr);
    
    std::string result = os.str();
    // Should not match any known tag description
    EXPECT_EQ(std::string::npos, result.find("Without correction"));
    EXPECT_EQ(std::string::npos, result.find("Correction applied"));
}

// Test with a large out-of-range value
TEST_F(Print0x001eTest_1391, LargeValueUnknown_1391) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("65535");
    
    Exiv2::Internal::print0x001e(os, *value, nullptr);
    
    std::string result = os.str();
    EXPECT_EQ(std::string::npos, result.find("Without correction"));
    EXPECT_EQ(std::string::npos, result.find("Correction applied"));
}

// Test that the function returns the same ostream reference
TEST_F(Print0x001eTest_1391, ReturnsOstreamReference_1391) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    
    std::ostream& returnedOs = Exiv2::Internal::print0x001e(os, *value, nullptr);
    
    EXPECT_EQ(&os, &returnedOs);
}

// Test with ExifData pointer (non-null metadata)
TEST_F(Print0x001eTest_1391, WithNonNullMetadata_1391) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    
    Exiv2::Internal::print0x001e(os, *value, &exifData);
    
    EXPECT_NE(std::string::npos, os.str().find("Without correction"));
}

// Test with ExifData pointer for value 1
TEST_F(Print0x001eTest_1391, WithNonNullMetadataValue1_1391) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    
    Exiv2::Internal::print0x001e(os, *value, &exifData);
    
    EXPECT_NE(std::string::npos, os.str().find("Correction applied"));
}

// Test that output is non-empty for valid values
TEST_F(Print0x001eTest_1391, OutputNonEmptyForValidValue_1391) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    
    Exiv2::Internal::print0x001e(os, *value, nullptr);
    
    EXPECT_FALSE(os.str().empty());
}

// Test that output is non-empty even for unknown values
TEST_F(Print0x001eTest_1391, OutputNonEmptyForUnknownValue_1391) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("99");
    
    Exiv2::Internal::print0x001e(os, *value, nullptr);
    
    EXPECT_FALSE(os.str().empty());
}

// Test with unsignedLong type value set to 0
TEST_F(Print0x001eTest_1391, UnsignedLongValueZero_1391) {
    auto value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("0");
    
    Exiv2::Internal::print0x001e(os, *value, nullptr);
    
    EXPECT_NE(std::string::npos, os.str().find("Without correction"));
}

// Test with unsignedLong type value set to 1
TEST_F(Print0x001eTest_1391, UnsignedLongValueOne_1391) {
    auto value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("1");
    
    Exiv2::Internal::print0x001e(os, *value, nullptr);
    
    EXPECT_NE(std::string::npos, os.str().find("Correction applied"));
}
