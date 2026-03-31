#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PrintFlashGroupCDataFl7Test_498 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test: When value count is not 1, should output "(<value>)"
TEST_F(PrintFlashGroupCDataFl7Test_498, ValueCountNotOne_498) {
    ExifData metadata;
    // Create a value with count != 1 (two bytes)
    auto value = Value::create(unsignedByte);
    value->read("10 20");
    
    Nikon3MakerNote::printFlashGroupCDataFl7(os, *value, &metadata);
    std::string result = os.str();
    // Should contain parentheses
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: When value typeId is not unsignedByte, should output "(<value>)"
TEST_F(PrintFlashGroupCDataFl7Test_498, ValueTypeNotUnsignedByte_498) {
    ExifData metadata;
    auto value = Value::create(unsignedShort);
    value->read("10");
    
    Nikon3MakerNote::printFlashGroupCDataFl7(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: When metadata is null, should output "(<value>)"
TEST_F(PrintFlashGroupCDataFl7Test_498, MetadataIsNull_498) {
    auto value = Value::create(unsignedByte);
    value->read("10");
    
    Nikon3MakerNote::printFlashGroupCDataFl7(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: When FlashGroupBCControlData key is not found in metadata, should output "(<value>)"
TEST_F(PrintFlashGroupCDataFl7Test_498, ControlDataKeyNotFound_498) {
    ExifData metadata;
    auto value = Value::create(unsignedByte);
    value->read("10");
    
    Nikon3MakerNote::printFlashGroupCDataFl7(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: When FlashGroupBCControlData exists but has wrong count, should output "(<value>)"
TEST_F(PrintFlashGroupCDataFl7Test_498, ControlDataWrongCount_498) {
    ExifData metadata;
    auto controlValue = Value::create(unsignedByte);
    controlValue->read("10 20");  // count = 2, not 1
    metadata.add(ExifKey("Exif.NikonFl7.FlashGroupBCControlData"), controlValue.get());
    
    auto value = Value::create(unsignedByte);
    value->read("10");
    
    Nikon3MakerNote::printFlashGroupCDataFl7(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: When FlashGroupBCControlData exists but has wrong type, should output "(<value>)"
TEST_F(PrintFlashGroupCDataFl7Test_498, ControlDataWrongType_498) {
    ExifData metadata;
    auto controlValue = Value::create(unsignedShort);
    controlValue->read("10");
    metadata.add(ExifKey("Exif.NikonFl7.FlashGroupBCControlData"), controlValue.get());
    
    auto value = Value::create(unsignedByte);
    value->read("10");
    
    Nikon3MakerNote::printFlashGroupCDataFl7(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: When mode (low nibble of control data) is 0, should output "n/a"
TEST_F(PrintFlashGroupCDataFl7Test_498, ModeIsZero_OutputNA_498) {
    ExifData metadata;
    // Control data with low nibble = 0 (e.g., 0x00, 0x10, 0x20, etc.)
    auto controlValue = Value::create(unsignedByte);
    controlValue->read("0");  // mode = 0 & 0x0F = 0
    metadata.add(ExifKey("Exif.NikonFl7.FlashGroupBCControlData"), controlValue.get());
    
    auto value = Value::create(unsignedByte);
    value->read("10");
    
    Nikon3MakerNote::printFlashGroupCDataFl7(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_NE(result.find("n/a"), std::string::npos);
}

// Test: When mode (low nibble of control data) is 0x10 (low nibble still 0), should output "n/a"
TEST_F(PrintFlashGroupCDataFl7Test_498, ModeHighNibbleSet_LowNibbleZero_498) {
    ExifData metadata;
    auto controlValue = Value::create(unsignedByte);
    controlValue->read("16");  // 0x10 => mode = 0x10 & 0x0F = 0
    metadata.add(ExifKey("Exif.NikonFl7.FlashGroupBCControlData"), controlValue.get());
    
    auto value = Value::create(unsignedByte);
    value->read("10");
    
    Nikon3MakerNote::printFlashGroupCDataFl7(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_NE(result.find("n/a"), std::string::npos);
}

// Test: When mode is non-zero, should call printFlashCompensationValue (output should not contain "n/a" or parentheses)
TEST_F(PrintFlashGroupCDataFl7Test_498, ModeNonZero_PrintsFlashCompensation_498) {
    ExifData metadata;
    auto controlValue = Value::create(unsignedByte);
    controlValue->read("1");  // mode = 1 & 0x0F = 1 (non-zero)
    metadata.add(ExifKey("Exif.NikonFl7.FlashGroupBCControlData"), controlValue.get());
    
    auto value = Value::create(unsignedByte);
    value->read("0");
    
    Nikon3MakerNote::printFlashGroupCDataFl7(os, *value, &metadata);
    std::string result = os.str();
    // Should not be "n/a" or parenthesized
    EXPECT_EQ(result.find("n/a"), std::string::npos);
    EXPECT_EQ(result.find("("), std::string::npos);
}

// Test: Another non-zero mode value
TEST_F(PrintFlashGroupCDataFl7Test_498, ModeNonZero_Mode3_498) {
    ExifData metadata;
    auto controlValue = Value::create(unsignedByte);
    controlValue->read("3");  // mode = 3 & 0x0F = 3
    metadata.add(ExifKey("Exif.NikonFl7.FlashGroupBCControlData"), controlValue.get());
    
    auto value = Value::create(unsignedByte);
    value->read("0");
    
    Nikon3MakerNote::printFlashGroupCDataFl7(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result.find("n/a"), std::string::npos);
    EXPECT_EQ(result.find("("), std::string::npos);
}

// Test: Mode with high nibble set but non-zero low nibble
TEST_F(PrintFlashGroupCDataFl7Test_498, ModeHighAndLowNibbleSet_498) {
    ExifData metadata;
    auto controlValue = Value::create(unsignedByte);
    controlValue->read("33");  // 0x21 => mode = 0x21 & 0x0F = 1
    metadata.add(ExifKey("Exif.NikonFl7.FlashGroupBCControlData"), controlValue.get());
    
    auto value = Value::create(unsignedByte);
    value->read("128");
    
    Nikon3MakerNote::printFlashGroupCDataFl7(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result.find("n/a"), std::string::npos);
    EXPECT_EQ(result.find("("), std::string::npos);
}

// Test: Returns reference to same ostream (null metadata case)
TEST_F(PrintFlashGroupCDataFl7Test_498, ReturnsSameOstream_498) {
    auto value = Value::create(unsignedByte);
    value->read("10");
    
    std::ostream& ret = Nikon3MakerNote::printFlashGroupCDataFl7(os, *value, nullptr);
    EXPECT_EQ(&ret, &os);
}

// Test: Returns reference to same ostream (n/a case)
TEST_F(PrintFlashGroupCDataFl7Test_498, ReturnsSameOstream_NACase_498) {
    ExifData metadata;
    auto controlValue = Value::create(unsignedByte);
    controlValue->read("0");
    metadata.add(ExifKey("Exif.NikonFl7.FlashGroupBCControlData"), controlValue.get());
    
    auto value = Value::create(unsignedByte);
    value->read("10");
    
    std::ostream& ret = Nikon3MakerNote::printFlashGroupCDataFl7(os, *value, &metadata);
    EXPECT_EQ(&ret, &os);
}

// Test: Returns reference to same ostream (flash compensation case)
TEST_F(PrintFlashGroupCDataFl7Test_498, ReturnsSameOstream_CompensationCase_498) {
    ExifData metadata;
    auto controlValue = Value::create(unsignedByte);
    controlValue->read("1");
    metadata.add(ExifKey("Exif.NikonFl7.FlashGroupBCControlData"), controlValue.get());
    
    auto value = Value::create(unsignedByte);
    value->read("0");
    
    std::ostream& ret = Nikon3MakerNote::printFlashGroupCDataFl7(os, *value, &metadata);
    EXPECT_EQ(&ret, &os);
}

// Test: Value with boundary byte value 255
TEST_F(PrintFlashGroupCDataFl7Test_498, MaxByteValue_498) {
    ExifData metadata;
    auto controlValue = Value::create(unsignedByte);
    controlValue->read("255");  // 0xFF => mode = 0xFF & 0x0F = 15 (non-zero)
    metadata.add(ExifKey("Exif.NikonFl7.FlashGroupBCControlData"), controlValue.get());
    
    auto value = Value::create(unsignedByte);
    value->read("255");
    
    Nikon3MakerNote::printFlashGroupCDataFl7(os, *value, &metadata);
    std::string result = os.str();
    // mode is non-zero (15), so should print flash compensation, not n/a
    EXPECT_EQ(result.find("n/a"), std::string::npos);
    EXPECT_EQ(result.find("("), std::string::npos);
}

// Test: Control data 0xF0 => mode = 0, should output "n/a"
TEST_F(PrintFlashGroupCDataFl7Test_498, ControlData0xF0_ModeZero_498) {
    ExifData metadata;
    auto controlValue = Value::create(unsignedByte);
    controlValue->read("240");  // 0xF0 => mode = 0xF0 & 0x0F = 0
    metadata.add(ExifKey("Exif.NikonFl7.FlashGroupBCControlData"), controlValue.get());
    
    auto value = Value::create(unsignedByte);
    value->read("10");
    
    Nikon3MakerNote::printFlashGroupCDataFl7(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_NE(result.find("n/a"), std::string::npos);
}

// Test: Empty ExifData - key not found
TEST_F(PrintFlashGroupCDataFl7Test_498, EmptyExifData_498) {
    ExifData metadata;
    auto value = Value::create(unsignedByte);
    value->read("42");
    
    Nikon3MakerNote::printFlashGroupCDataFl7(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find("42"), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}
