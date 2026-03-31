#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Include internal headers for Nikon3MakerNote
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PrintFlashGroupADataFl7Test_494 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test: Null metadata pointer should output "(value)"
TEST_F(PrintFlashGroupADataFl7Test_494, NullMetadataReturnsParenthesizedValue_494) {
    auto value = Value::create(unsignedByte);
    value->read("42");
    
    Nikon3MakerNote::printFlashGroupADataFl7(os, *value, nullptr);
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: Value with wrong type (not unsignedByte) should output "(value)"
TEST_F(PrintFlashGroupADataFl7Test_494, WrongValueTypeReturnsParenthesizedValue_494) {
    auto value = Value::create(unsignedShort);
    value->read("42");
    
    ExifData metadata;
    
    Nikon3MakerNote::printFlashGroupADataFl7(os, *value, &metadata);
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: Value with count != 1 (multiple values) should output "(value)"
TEST_F(PrintFlashGroupADataFl7Test_494, MultipleValuesReturnsParenthesizedValue_494) {
    auto value = Value::create(unsignedByte);
    value->read("42 43");
    
    ExifData metadata;
    
    Nikon3MakerNote::printFlashGroupADataFl7(os, *value, &metadata);
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: Metadata without FlashGroupAControlData key should output "(value)"
TEST_F(PrintFlashGroupADataFl7Test_494, MissingControlDataKeyReturnsParenthesizedValue_494) {
    auto value = Value::create(unsignedByte);
    value->read("42");
    
    ExifData metadata;
    // Don't add FlashGroupAControlData to metadata
    
    Nikon3MakerNote::printFlashGroupADataFl7(os, *value, &metadata);
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: FlashGroupAControlData with mode 0 (lower nibble = 0) should output "n/a"
TEST_F(PrintFlashGroupADataFl7Test_494, ControlDataModeZeroReturnsNA_494) {
    auto value = Value::create(unsignedByte);
    value->read("42");
    
    ExifData metadata;
    {
        auto controlValue = Value::create(unsignedByte);
        controlValue->read("0"); // mode & 0x0F == 0
        metadata.add(ExifKey("Exif.NikonFl7.FlashGroupAControlData"), controlValue.get());
    }
    
    Nikon3MakerNote::printFlashGroupADataFl7(os, *value, &metadata);
    
    std::string result = os.str();
    // Should contain "n/a" (possibly translated)
    EXPECT_FALSE(result.empty());
    // When mode is 0, it returns "n/a" - check it doesn't have parentheses
    EXPECT_EQ(result.find("("), std::string::npos);
}

// Test: FlashGroupAControlData with mode 0x10 (lower nibble still 0) should output "n/a"
TEST_F(PrintFlashGroupADataFl7Test_494, ControlDataHighNibbleOnlyReturnsNA_494) {
    auto value = Value::create(unsignedByte);
    value->read("42");
    
    ExifData metadata;
    {
        auto controlValue = Value::create(unsignedByte);
        controlValue->read("16"); // 0x10 -> mode & 0x0F == 0
        metadata.add(ExifKey("Exif.NikonFl7.FlashGroupAControlData"), controlValue.get());
    }
    
    Nikon3MakerNote::printFlashGroupADataFl7(os, *value, &metadata);
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result.find("("), std::string::npos);
}

// Test: FlashGroupAControlData with non-zero mode should print flash compensation value
TEST_F(PrintFlashGroupADataFl7Test_494, NonZeroModeReturnsFlashCompensation_494) {
    auto value = Value::create(unsignedByte);
    value->read("0");
    
    ExifData metadata;
    {
        auto controlValue = Value::create(unsignedByte);
        controlValue->read("1"); // mode & 0x0F == 1 (non-zero)
        metadata.add(ExifKey("Exif.NikonFl7.FlashGroupAControlData"), controlValue.get());
    }
    
    Nikon3MakerNote::printFlashGroupADataFl7(os, *value, &metadata);
    
    std::string result = os.str();
    // Should produce some output (flash compensation value)
    EXPECT_FALSE(result.empty());
}

// Test: FlashGroupAControlData with mode 3 (manual mode) and value
TEST_F(PrintFlashGroupADataFl7Test_494, ManualModeReturnsFlashCompensation_494) {
    auto value = Value::create(unsignedByte);
    value->read("24");
    
    ExifData metadata;
    {
        auto controlValue = Value::create(unsignedByte);
        controlValue->read("3"); // mode & 0x0F == 3
        metadata.add(ExifKey("Exif.NikonFl7.FlashGroupAControlData"), controlValue.get());
    }
    
    Nikon3MakerNote::printFlashGroupADataFl7(os, *value, &metadata);
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: FlashGroupAControlData with wrong type should output "(value)"
TEST_F(PrintFlashGroupADataFl7Test_494, ControlDataWrongTypeReturnsParenthesizedValue_494) {
    auto value = Value::create(unsignedByte);
    value->read("42");
    
    ExifData metadata;
    {
        auto controlValue = Value::create(unsignedShort);
        controlValue->read("1");
        metadata.add(ExifKey("Exif.NikonFl7.FlashGroupAControlData"), controlValue.get());
    }
    
    Nikon3MakerNote::printFlashGroupADataFl7(os, *value, &metadata);
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: FlashGroupAControlData with multiple values (count != 1) should output "(value)"
TEST_F(PrintFlashGroupADataFl7Test_494, ControlDataMultipleValuesReturnsParenthesizedValue_494) {
    auto value = Value::create(unsignedByte);
    value->read("42");
    
    ExifData metadata;
    {
        auto controlValue = Value::create(unsignedByte);
        controlValue->read("1 2");
        metadata.add(ExifKey("Exif.NikonFl7.FlashGroupAControlData"), controlValue.get());
    }
    
    Nikon3MakerNote::printFlashGroupADataFl7(os, *value, &metadata);
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: Return value is the same ostream reference
TEST_F(PrintFlashGroupADataFl7Test_494, ReturnsOstreamReference_494) {
    auto value = Value::create(unsignedByte);
    value->read("42");
    
    std::ostream& result = Nikon3MakerNote::printFlashGroupADataFl7(os, *value, nullptr);
    
    EXPECT_EQ(&result, &os);
}

// Test: Value 0 with mode 0x0F (all lower bits set)
TEST_F(PrintFlashGroupADataFl7Test_494, AllLowerBitsSetInMode_494) {
    auto value = Value::create(unsignedByte);
    value->read("0");
    
    ExifData metadata;
    {
        auto controlValue = Value::create(unsignedByte);
        controlValue->read("15"); // 0x0F -> mode & 0x0F == 15
        metadata.add(ExifKey("Exif.NikonFl7.FlashGroupAControlData"), controlValue.get());
    }
    
    Nikon3MakerNote::printFlashGroupADataFl7(os, *value, &metadata);
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: Value 255 (max unsigned byte) with non-zero mode
TEST_F(PrintFlashGroupADataFl7Test_494, MaxByteValueWithNonZeroMode_494) {
    auto value = Value::create(unsignedByte);
    value->read("255");
    
    ExifData metadata;
    {
        auto controlValue = Value::create(unsignedByte);
        controlValue->read("1");
        metadata.add(ExifKey("Exif.NikonFl7.FlashGroupAControlData"), controlValue.get());
    }
    
    Nikon3MakerNote::printFlashGroupADataFl7(os, *value, &metadata);
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: Control data value 0xF0 (lower nibble = 0) should return "n/a"
TEST_F(PrintFlashGroupADataFl7Test_494, ControlDataF0ReturnsNA_494) {
    auto value = Value::create(unsignedByte);
    value->read("42");
    
    ExifData metadata;
    {
        auto controlValue = Value::create(unsignedByte);
        controlValue->read("240"); // 0xF0 -> mode & 0x0F == 0
        metadata.add(ExifKey("Exif.NikonFl7.FlashGroupAControlData"), controlValue.get());
    }
    
    Nikon3MakerNote::printFlashGroupADataFl7(os, *value, &metadata);
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result.find("("), std::string::npos);
}

// Test: Empty value (count == 0) should output "(value)"
TEST_F(PrintFlashGroupADataFl7Test_494, EmptyValueReturnsParenthesizedValue_494) {
    auto value = Value::create(unsignedByte);
    // Don't read any data, count should be 0
    
    ExifData metadata;
    
    Nikon3MakerNote::printFlashGroupADataFl7(os, *value, &metadata);
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}
