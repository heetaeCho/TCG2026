#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Forward declaration of the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& print0x000a(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class Print0x000aTest_1388 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test with value '2' which should print "2-dimensional measurement"
TEST_F(Print0x000aTest_1388, TwoDimensionalMeasurement_1388) {
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("2");
    
    Exiv2::Internal::print0x000a(os, *value, nullptr);
    
    EXPECT_NE(os.str().find("2-dimensional measurement"), std::string::npos)
        << "Actual output: " << os.str();
}

// Test with value '3' which should print "3-dimensional measurement"
TEST_F(Print0x000aTest_1388, ThreeDimensionalMeasurement_1388) {
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("3");
    
    Exiv2::Internal::print0x000a(os, *value, nullptr);
    
    EXPECT_NE(os.str().find("3-dimensional measurement"), std::string::npos)
        << "Actual output: " << os.str();
}

// Test with unknown value that is not in the tag details
TEST_F(Print0x000aTest_1388, UnknownValue_1388) {
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("5");
    
    Exiv2::Internal::print0x000a(os, *value, nullptr);
    
    std::string result = os.str();
    // Should not contain known measurement modes
    EXPECT_EQ(result.find("2-dimensional measurement"), std::string::npos);
    EXPECT_EQ(result.find("3-dimensional measurement"), std::string::npos);
    // Should produce some output (likely the raw value or "(5)")
    EXPECT_FALSE(result.empty()) << "Output should not be empty for unknown value";
}

// Test with value '0' - not a recognized mode
TEST_F(Print0x000aTest_1388, ZeroValue_1388) {
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("0");
    
    Exiv2::Internal::print0x000a(os, *value, nullptr);
    
    std::string result = os.str();
    EXPECT_EQ(result.find("2-dimensional measurement"), std::string::npos);
    EXPECT_EQ(result.find("3-dimensional measurement"), std::string::npos);
}

// Test with nullptr metadata - should still work
TEST_F(Print0x000aTest_1388, NullMetadata_1388) {
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("2");
    
    // Should not crash with nullptr metadata
    Exiv2::Internal::print0x000a(os, *value, nullptr);
    
    EXPECT_NE(os.str().find("2-dimensional measurement"), std::string::npos);
}

// Test with valid ExifData metadata
TEST_F(Print0x000aTest_1388, WithExifDataMetadata_1388) {
    Exiv2::ExifData exifData;
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("3");
    
    Exiv2::Internal::print0x000a(os, *value, &exifData);
    
    EXPECT_NE(os.str().find("3-dimensional measurement"), std::string::npos)
        << "Actual output: " << os.str();
}

// Test with value '1' - not a recognized mode
TEST_F(Print0x000aTest_1388, ValueOne_1388) {
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("1");
    
    Exiv2::Internal::print0x000a(os, *value, nullptr);
    
    std::string result = os.str();
    EXPECT_EQ(result.find("2-dimensional measurement"), std::string::npos);
    EXPECT_EQ(result.find("3-dimensional measurement"), std::string::npos);
}

// Test that the function returns the same ostream reference
TEST_F(Print0x000aTest_1388, ReturnsOstreamReference_1388) {
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("2");
    
    std::ostream& result = Exiv2::Internal::print0x000a(os, *value, nullptr);
    
    EXPECT_EQ(&result, &os);
}

// Test with unsigned short value type for '2'
TEST_F(Print0x000aTest_1388, UnsignedShortValue2_1388) {
    auto value = Exiv2::Value::create(Exiv2::unsignedShort);
    value->read("50"); // ASCII '2' = 50
    
    Exiv2::Internal::print0x000a(os, *value, nullptr);
    
    // Output should be produced
    EXPECT_FALSE(os.str().empty());
}

// Test with empty string value
TEST_F(Print0x000aTest_1388, EmptyStringValue_1388) {
    auto value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("");
    
    Exiv2::Internal::print0x000a(os, *value, nullptr);
    
    // Should produce some output without crashing
    // The exact output depends on implementation
}

// Test consecutive calls to ensure stream state is preserved
TEST_F(Print0x000aTest_1388, ConsecutiveCalls_1388) {
    auto value2 = Exiv2::Value::create(Exiv2::asciiString);
    value2->read("2");
    
    auto value3 = Exiv2::Value::create(Exiv2::asciiString);
    value3->read("3");
    
    Exiv2::Internal::print0x000a(os, *value2, nullptr);
    std::string first = os.str();
    
    os.str("");
    Exiv2::Internal::print0x000a(os, *value3, nullptr);
    std::string second = os.str();
    
    EXPECT_NE(first.find("2-dimensional"), std::string::npos);
    EXPECT_NE(second.find("3-dimensional"), std::string::npos);
}
