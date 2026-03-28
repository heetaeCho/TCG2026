#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Include internal headers for Nikon3MakerNote
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PrintFlashGroupCDataFl6Test_497 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test: When value count != 1, should output "(value)"
TEST_F(PrintFlashGroupCDataFl6Test_497, ValueCountNotOne_OutputsParenthesizedValue_497) {
    // Create a value with count > 1
    auto value = Value::create(unsignedByte);
    value->read("10 20");  // Two values, count = 2
    
    ExifData metadata;
    
    Nikon3MakerNote::printFlashGroupCDataFl6(os, *value, &metadata);
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When value typeId is not unsignedByte, should output "(value)"
TEST_F(PrintFlashGroupCDataFl6Test_497, ValueTypeNotUnsignedByte_OutputsParenthesizedValue_497) {
    auto value = Value::create(unsignedShort);
    value->read("10");
    
    ExifData metadata;
    
    Nikon3MakerNote::printFlashGroupCDataFl6(os, *value, &metadata);
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When metadata is null, should output "(value)"
TEST_F(PrintFlashGroupCDataFl6Test_497, NullMetadata_OutputsParenthesizedValue_497) {
    auto value = Value::create(unsignedByte);
    value->read("10");
    
    Nikon3MakerNote::printFlashGroupCDataFl6(os, *value, nullptr);
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When FlashGroupBCControlData key is not found in metadata, should output "(value)"
TEST_F(PrintFlashGroupCDataFl6Test_497, MissingControlDataKey_OutputsParenthesizedValue_497) {
    auto value = Value::create(unsignedByte);
    value->read("10");
    
    ExifData metadata;
    // Don't add FlashGroupBCControlData to metadata
    
    Nikon3MakerNote::printFlashGroupCDataFl6(os, *value, &metadata);
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When FlashGroupBCControlData exists but has wrong count
TEST_F(PrintFlashGroupCDataFl6Test_497, ControlDataWrongCount_OutputsParenthesizedValue_497) {
    auto value = Value::create(unsignedByte);
    value->read("10");
    
    ExifData metadata;
    auto controlValue = Value::create(unsignedByte);
    controlValue->read("5 6");  // count = 2, not 1
    metadata.add(ExifKey("Exif.NikonFl6.FlashGroupBCControlData"), controlValue.get());
    
    Nikon3MakerNote::printFlashGroupCDataFl6(os, *value, &metadata);
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When FlashGroupBCControlData exists but has wrong typeId
TEST_F(PrintFlashGroupCDataFl6Test_497, ControlDataWrongType_OutputsParenthesizedValue_497) {
    auto value = Value::create(unsignedByte);
    value->read("10");
    
    ExifData metadata;
    auto controlValue = Value::create(unsignedShort);
    controlValue->read("5");
    metadata.add(ExifKey("Exif.NikonFl6.FlashGroupBCControlData"), controlValue.get());
    
    Nikon3MakerNote::printFlashGroupCDataFl6(os, *value, &metadata);
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: When mode (lower nibble of control data) is 0, should output "n/a"
TEST_F(PrintFlashGroupCDataFl6Test_497, ModeZero_OutputsNA_497) {
    auto value = Value::create(unsignedByte);
    value->read("10");
    
    ExifData metadata;
    // Set control data to 0x00 so that (0x00 & 0x0F) == 0
    auto controlValue = Value::create(unsignedByte);
    controlValue->read("0");
    metadata.add(ExifKey("Exif.NikonFl6.FlashGroupBCControlData"), controlValue.get());
    
    Nikon3MakerNote::printFlashGroupCDataFl6(os, *value, &metadata);
    
    std::string result = os.str();
    // Should contain "n/a" (possibly localized)
    EXPECT_FALSE(result.empty());
    // Mode is 0, so we expect n/a
    EXPECT_TRUE(result.find("n/a") != std::string::npos || result.find("N/A") != std::string::npos || result.find("(") == std::string::npos);
}

// Test: When mode (lower nibble) is 0x10 (upper nibble set, lower 0), still mode == 0
TEST_F(PrintFlashGroupCDataFl6Test_497, ModeZeroWithUpperBitsSet_OutputsNA_497) {
    auto value = Value::create(unsignedByte);
    value->read("10");
    
    ExifData metadata;
    // 0xF0 & 0x0F == 0, so mode = 0
    auto controlValue = Value::create(unsignedByte);
    controlValue->read("240");  // 0xF0
    metadata.add(ExifKey("Exif.NikonFl6.FlashGroupBCControlData"), controlValue.get());
    
    Nikon3MakerNote::printFlashGroupCDataFl6(os, *value, &metadata);
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    // Mode is 0, expect n/a
}

// Test: When mode is non-zero, should call printFlashCompensationValue and produce some output
TEST_F(PrintFlashGroupCDataFl6Test_497, ModeNonZero_ProducesFlashCompensationOutput_497) {
    auto value = Value::create(unsignedByte);
    value->read("0");
    
    ExifData metadata;
    // Set control data to 1 so that (1 & 0x0F) == 1 (non-zero mode)
    auto controlValue = Value::create(unsignedByte);
    controlValue->read("1");
    metadata.add(ExifKey("Exif.NikonFl6.FlashGroupBCControlData"), controlValue.get());
    
    Nikon3MakerNote::printFlashGroupCDataFl6(os, *value, &metadata);
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    // Should NOT contain parenthesized value format nor n/a
    EXPECT_TRUE(result.find("(") == std::string::npos || result.find("n/a") == std::string::npos);
}

// Test: Mode non-zero with different value
TEST_F(PrintFlashGroupCDataFl6Test_497, ModeNonZeroWithDifferentValue_ProducesOutput_497) {
    auto value = Value::create(unsignedByte);
    value->read("128");
    
    ExifData metadata;
    // Mode = 3 (e.g., control data = 0x03)
    auto controlValue = Value::create(unsignedByte);
    controlValue->read("3");
    metadata.add(ExifKey("Exif.NikonFl6.FlashGroupBCControlData"), controlValue.get());
    
    Nikon3MakerNote::printFlashGroupCDataFl6(os, *value, &metadata);
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: Return value is reference to the same ostream
TEST_F(PrintFlashGroupCDataFl6Test_497, ReturnsSameOstream_497) {
    auto value = Value::create(unsignedByte);
    value->read("10");
    
    std::ostream& returned = Nikon3MakerNote::printFlashGroupCDataFl6(os, *value, nullptr);
    
    EXPECT_EQ(&returned, &os);
}

// Test: Return value is same ostream when metadata is valid but key not found
TEST_F(PrintFlashGroupCDataFl6Test_497, ReturnsSameOstreamWithValidMetadataNoKey_497) {
    auto value = Value::create(unsignedByte);
    value->read("10");
    
    ExifData metadata;
    
    std::ostream& returned = Nikon3MakerNote::printFlashGroupCDataFl6(os, *value, &metadata);
    
    EXPECT_EQ(&returned, &os);
}

// Test: Return value is same ostream when n/a case
TEST_F(PrintFlashGroupCDataFl6Test_497, ReturnsSameOstreamForNA_497) {
    auto value = Value::create(unsignedByte);
    value->read("10");
    
    ExifData metadata;
    auto controlValue = Value::create(unsignedByte);
    controlValue->read("0");
    metadata.add(ExifKey("Exif.NikonFl6.FlashGroupBCControlData"), controlValue.get());
    
    std::ostream& returned = Nikon3MakerNote::printFlashGroupCDataFl6(os, *value, &metadata);
    
    EXPECT_EQ(&returned, &os);
}

// Test: Mode = 0x0F (all lower nibble bits set), non-zero mode
TEST_F(PrintFlashGroupCDataFl6Test_497, ModeAllLowerBitsSet_ProducesCompensationOutput_497) {
    auto value = Value::create(unsignedByte);
    value->read("50");
    
    ExifData metadata;
    // 0xFF & 0x0F == 0x0F = 15
    auto controlValue = Value::create(unsignedByte);
    controlValue->read("255");  // 0xFF
    metadata.add(ExifKey("Exif.NikonFl6.FlashGroupBCControlData"), controlValue.get());
    
    Nikon3MakerNote::printFlashGroupCDataFl6(os, *value, &metadata);
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: Value = 0 with non-zero mode
TEST_F(PrintFlashGroupCDataFl6Test_497, ValueZeroWithNonZeroMode_497) {
    auto value = Value::create(unsignedByte);
    value->read("0");
    
    ExifData metadata;
    auto controlValue = Value::create(unsignedByte);
    controlValue->read("2");
    metadata.add(ExifKey("Exif.NikonFl6.FlashGroupBCControlData"), controlValue.get());
    
    Nikon3MakerNote::printFlashGroupCDataFl6(os, *value, &metadata);
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: Value = 255 (max unsigned byte) with non-zero mode
TEST_F(PrintFlashGroupCDataFl6Test_497, ValueMaxWithNonZeroMode_497) {
    auto value = Value::create(unsignedByte);
    value->read("255");
    
    ExifData metadata;
    auto controlValue = Value::create(unsignedByte);
    controlValue->read("5");
    metadata.add(ExifKey("Exif.NikonFl6.FlashGroupBCControlData"), controlValue.get());
    
    Nikon3MakerNote::printFlashGroupCDataFl6(os, *value, &metadata);
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}
