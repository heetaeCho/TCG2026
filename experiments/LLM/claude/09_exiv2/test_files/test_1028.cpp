#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>

// Declaration of the function under test
namespace Exiv2 {
namespace Internal {
std::ostream& printMinoltaSonyBoolInverseValue(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class PrintMinoltaSonyBoolInverseValueTest_1028 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test that value 0 prints "On" (inverse boolean: 0 = On)
TEST_F(PrintMinoltaSonyBoolInverseValueTest_1028, ValueZeroPrintsOn_1028) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("0");
    
    Exiv2::Internal::printMinoltaSonyBoolInverseValue(os, value, nullptr);
    
    EXPECT_EQ("On", os.str());
}

// Test that value 1 prints "Off" (inverse boolean: 1 = Off)
TEST_F(PrintMinoltaSonyBoolInverseValueTest_1028, ValueOnePrintsOff_1028) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("1");
    
    Exiv2::Internal::printMinoltaSonyBoolInverseValue(os, value, nullptr);
    
    EXPECT_EQ("Off", os.str());
}

// Test that an unknown value (not 0 or 1) prints something (likely the raw number or "(n)")
TEST_F(PrintMinoltaSonyBoolInverseValueTest_1028, UnknownValuePrintsRawOrParenthesized_1028) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("2");
    
    Exiv2::Internal::printMinoltaSonyBoolInverseValue(os, value, nullptr);
    
    std::string result = os.str();
    // The result should not be "On" or "Off" since 2 is not in the tag details
    EXPECT_NE("On", result);
    EXPECT_NE("Off", result);
    // It should contain "2" in some form
    EXPECT_NE(std::string::npos, result.find("2"));
}

// Test with a large unknown value
TEST_F(PrintMinoltaSonyBoolInverseValueTest_1028, LargeUnknownValue_1028) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("255");
    
    Exiv2::Internal::printMinoltaSonyBoolInverseValue(os, value, nullptr);
    
    std::string result = os.str();
    EXPECT_NE("On", result);
    EXPECT_NE("Off", result);
}

// Test that the function returns the same ostream reference
TEST_F(PrintMinoltaSonyBoolInverseValueTest_1028, ReturnsSameOstream_1028) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("0");
    
    std::ostream& returnedOs = Exiv2::Internal::printMinoltaSonyBoolInverseValue(os, value, nullptr);
    
    EXPECT_EQ(&os, &returnedOs);
}

// Test with nullptr metadata (should still work)
TEST_F(PrintMinoltaSonyBoolInverseValueTest_1028, NullMetadataHandled_1028) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("1");
    
    // Should not crash with nullptr metadata
    EXPECT_NO_THROW(Exiv2::Internal::printMinoltaSonyBoolInverseValue(os, value, nullptr));
    EXPECT_EQ("Off", os.str());
}

// Test with valid ExifData pointer
TEST_F(PrintMinoltaSonyBoolInverseValueTest_1028, ValidMetadataPointer_1028) {
    Exiv2::ExifData exifData;
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("0");
    
    Exiv2::Internal::printMinoltaSonyBoolInverseValue(os, value, &exifData);
    
    EXPECT_EQ("On", os.str());
}

// Test with signed long value type for value 0
TEST_F(PrintMinoltaSonyBoolInverseValueTest_1028, SignedLongValueZero_1028) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("0");
    
    Exiv2::Internal::printMinoltaSonyBoolInverseValue(os, value, nullptr);
    
    EXPECT_EQ("On", os.str());
}

// Test with signed long value type for value 1
TEST_F(PrintMinoltaSonyBoolInverseValueTest_1028, SignedLongValueOne_1028) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("1");
    
    Exiv2::Internal::printMinoltaSonyBoolInverseValue(os, value, nullptr);
    
    EXPECT_EQ("Off", os.str());
}
