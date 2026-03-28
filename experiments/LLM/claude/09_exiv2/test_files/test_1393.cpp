#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// We need access to the internal function and tag details
namespace Exiv2 {
namespace Internal {
std::ostream& print0x0213(std::ostream& os, const Value& value, const ExifData* metadata);
}
}

class Print0x0213Test_1393 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test normal case: value 1 should print "Centered"
TEST_F(Print0x0213Test_1393, ValueOnePrintsCentered_1393) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("1");
    
    Exiv2::Internal::print0x0213(os, value, nullptr);
    
    EXPECT_EQ(os.str(), "Centered");
}

// Test normal case: value 2 should print "Co-sited"
TEST_F(Print0x0213Test_1393, ValueTwoPrintsCoSited_1393) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("2");
    
    Exiv2::Internal::print0x0213(os, value, nullptr);
    
    EXPECT_EQ(os.str(), "Co-sited");
}

// Test boundary: value 0 is not in the tag details, should print something (likely "(0)")
TEST_F(Print0x0213Test_1393, ValueZeroUnknown_1393) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("0");
    
    Exiv2::Internal::print0x0213(os, value, nullptr);
    
    std::string result = os.str();
    // Value 0 is not defined in exifYCbCrPositioning, should not be "Centered" or "Co-sited"
    EXPECT_NE(result, "Centered");
    EXPECT_NE(result, "Co-sited");
    EXPECT_FALSE(result.empty());
}

// Test boundary: value 3 is not in the tag details
TEST_F(Print0x0213Test_1393, ValueThreeUnknown_1393) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("3");
    
    Exiv2::Internal::print0x0213(os, value, nullptr);
    
    std::string result = os.str();
    EXPECT_NE(result, "Centered");
    EXPECT_NE(result, "Co-sited");
    EXPECT_FALSE(result.empty());
}

// Test with nullptr metadata - should still work
TEST_F(Print0x0213Test_1393, NullMetadataWorksWithValidValue_1393) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("1");
    
    Exiv2::Internal::print0x0213(os, value, nullptr);
    
    EXPECT_EQ(os.str(), "Centered");
}

// Test with actual ExifData pointer
TEST_F(Print0x0213Test_1393, WithExifDataPtrValueOne_1393) {
    Exiv2::ExifData exifData;
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("1");
    
    Exiv2::Internal::print0x0213(os, value, &exifData);
    
    EXPECT_EQ(os.str(), "Centered");
}

// Test with actual ExifData pointer for value 2
TEST_F(Print0x0213Test_1393, WithExifDataPtrValueTwo_1393) {
    Exiv2::ExifData exifData;
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("2");
    
    Exiv2::Internal::print0x0213(os, value, &exifData);
    
    EXPECT_EQ(os.str(), "Co-sited");
}

// Test return value is the same ostream reference
TEST_F(Print0x0213Test_1393, ReturnsOstreamReference_1393) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("1");
    
    std::ostream& result = Exiv2::Internal::print0x0213(os, value, nullptr);
    
    EXPECT_EQ(&result, &os);
}

// Test large unknown value
TEST_F(Print0x0213Test_1393, LargeValueUnknown_1393) {
    Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
    value.read("255");
    
    Exiv2::Internal::print0x0213(os, value, nullptr);
    
    std::string result = os.str();
    EXPECT_NE(result, "Centered");
    EXPECT_NE(result, "Co-sited");
    EXPECT_FALSE(result.empty());
}

// Test that the function can be called multiple times on the same stream
TEST_F(Print0x0213Test_1393, MultipleCallsAppendToStream_1393) {
    Exiv2::ValueType<uint16_t> value1(Exiv2::unsignedShort);
    value1.read("1");
    
    Exiv2::ValueType<uint16_t> value2(Exiv2::unsignedShort);
    value2.read("2");
    
    Exiv2::Internal::print0x0213(os, value1, nullptr);
    Exiv2::Internal::print0x0213(os, value2, nullptr);
    
    std::string result = os.str();
    EXPECT_EQ(result, "CenteredCo-sited");
}
