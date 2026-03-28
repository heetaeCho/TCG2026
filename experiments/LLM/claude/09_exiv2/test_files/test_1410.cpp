#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// We need access to the internal function
namespace Exiv2 {
namespace Internal {
std::ostream& print0xa301(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class Print0xa301Test_1410 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test normal case: value = 1 should print "Directly photographed"
TEST_F(Print0xa301Test_1410, ValueOne_PrintsDirectlyPhotographed_1410) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    
    Exiv2::Internal::print0xa301(os, *value, nullptr);
    
    std::string result = os.str();
    EXPECT_NE(result.find("Directly photographed"), std::string::npos)
        << "Expected 'Directly photographed' but got: " << result;
}

// Test unknown value: value = 0 should print something indicating unknown
TEST_F(Print0xa301Test_1410, ValueZero_PrintsUnknownOrValue_1410) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("0");
    
    Exiv2::Internal::print0xa301(os, *value, nullptr);
    
    std::string result = os.str();
    // Value 0 is not in the tag details, so it should not say "Directly photographed"
    EXPECT_EQ(result.find("Directly photographed"), std::string::npos)
        << "Did not expect 'Directly photographed' for value 0, got: " << result;
}

// Test unknown value: value = 2 should not print "Directly photographed"
TEST_F(Print0xa301Test_1410, ValueTwo_PrintsUnknownOrValue_1410) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("2");
    
    Exiv2::Internal::print0xa301(os, *value, nullptr);
    
    std::string result = os.str();
    EXPECT_EQ(result.find("Directly photographed"), std::string::npos)
        << "Did not expect 'Directly photographed' for value 2, got: " << result;
}

// Test with nullptr metadata - should still work for value 1
TEST_F(Print0xa301Test_1410, NullMetadata_ValueOne_StillWorks_1410) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    
    Exiv2::Internal::print0xa301(os, *value, nullptr);
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty()) << "Output should not be empty";
}

// Test with actual ExifData pointer
TEST_F(Print0xa301Test_1410, WithExifData_ValueOne_PrintsDirectlyPhotographed_1410) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    
    Exiv2::Internal::print0xa301(os, *value, &exifData);
    
    std::string result = os.str();
    EXPECT_NE(result.find("Directly photographed"), std::string::npos)
        << "Expected 'Directly photographed' but got: " << result;
}

// Test return value is the same ostream reference
TEST_F(Print0xa301Test_1410, ReturnsOstreamReference_1410) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    
    std::ostream& returned = Exiv2::Internal::print0xa301(os, *value, nullptr);
    
    EXPECT_EQ(&returned, &os) << "Should return the same ostream reference";
}

// Test large unknown value
TEST_F(Print0xa301Test_1410, LargeValue_PrintsUnknown_1410) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("65535");
    
    Exiv2::Internal::print0xa301(os, *value, nullptr);
    
    std::string result = os.str();
    EXPECT_EQ(result.find("Directly photographed"), std::string::npos)
        << "Did not expect 'Directly photographed' for value 65535, got: " << result;
}

// Test negative value (if supported by signed type)
TEST_F(Print0xa301Test_1410, NegativeValue_PrintsUnknown_1410) {
    auto value = Exiv2::Value::create(Exiv2::signedShort);
    value->read("-1");
    
    Exiv2::Internal::print0xa301(os, *value, nullptr);
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty()) << "Output should not be empty even for negative value";
}

// Test that output is non-empty for any valid input
TEST_F(Print0xa301Test_1410, OutputNonEmptyForValidInput_1410) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("1");
    
    Exiv2::Internal::print0xa301(os, *value, nullptr);
    
    EXPECT_FALSE(os.str().empty()) << "Output should not be empty";
}

// Test with unsignedByte type for value 1
TEST_F(Print0xa301Test_1410, UnsignedByteType_ValueOne_1410) {
    auto value = Exiv2::Value::create(Exiv2::unsignedByte);
    value->read("1");
    
    Exiv2::Internal::print0xa301(os, *value, nullptr);
    
    std::string result = os.str();
    EXPECT_NE(result.find("Directly photographed"), std::string::npos)
        << "Expected 'Directly photographed' but got: " << result;
}

// Test with unsignedLong type for value 1
TEST_F(Print0xa301Test_1410, UnsignedLongType_ValueOne_1410) {
    auto value = Exiv2::Value::create(Exiv2::unsignedLong);
    value->read("1");
    
    Exiv2::Internal::print0xa301(os, *value, nullptr);
    
    std::string result = os.str();
    EXPECT_NE(result.find("Directly photographed"), std::string::npos)
        << "Expected 'Directly photographed' but got: " << result;
}
