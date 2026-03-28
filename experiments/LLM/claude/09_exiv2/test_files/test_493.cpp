#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Include the internal header for Nikon3MakerNote
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PrintFlashGroupADataFl6Test_493 : public ::testing::Test {
protected:
    std::ostringstream os;

    // Helper to create an unsignedByte Value with a single byte
    std::unique_ptr<Value> makeUnsignedByte(uint8_t val) {
        auto v = Value::create(unsignedByte);
        byte buf[1] = {val};
        v->read(buf, 1, littleEndian);
        return v;
    }

    // Helper to create an unsignedShort Value with a single value
    std::unique_ptr<Value> makeUnsignedShort(uint16_t val) {
        auto v = Value::create(unsignedShort);
        byte buf[2];
        buf[0] = static_cast<byte>(val & 0xFF);
        buf[1] = static_cast<byte>((val >> 8) & 0xFF);
        v->read(buf, 2, littleEndian);
        return v;
    }

    // Helper to create a multi-byte unsignedByte Value
    std::unique_ptr<Value> makeUnsignedByteMulti(const std::vector<uint8_t>& vals) {
        auto v = Value::create(unsignedByte);
        v->read(vals.data(), vals.size(), littleEndian);
        return v;
    }
};

// Test: null metadata pointer should produce parenthesized output
TEST_F(PrintFlashGroupADataFl6Test_493, NullMetadata_493) {
    auto value = makeUnsignedByte(0x10);
    Nikon3MakerNote::printFlashGroupADataFl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: value with wrong type (not unsignedByte) should produce parenthesized output
TEST_F(PrintFlashGroupADataFl6Test_493, WrongValueType_493) {
    auto value = makeUnsignedShort(0x10);
    ExifData metadata;
    Nikon3MakerNote::printFlashGroupADataFl6(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: value with count != 1 (multiple bytes) should produce parenthesized output
TEST_F(PrintFlashGroupADataFl6Test_493, MultipleValueCount_493) {
    auto value = makeUnsignedByteMulti({0x10, 0x20});
    ExifData metadata;
    Nikon3MakerNote::printFlashGroupADataFl6(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: metadata doesn't contain FlashGroupAControlData key - parenthesized output
TEST_F(PrintFlashGroupADataFl6Test_493, MissingControlDataKey_493) {
    auto value = makeUnsignedByte(0x10);
    ExifData metadata;
    Nikon3MakerNote::printFlashGroupADataFl6(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: FlashGroupAControlData present but with wrong type
TEST_F(PrintFlashGroupADataFl6Test_493, ControlDataWrongType_493) {
    auto value = makeUnsignedByte(0x10);
    ExifData metadata;
    // Add control data with unsignedShort type instead of unsignedByte
    auto controlVal = makeUnsignedShort(0x01);
    metadata.add(ExifKey("Exif.NikonFl6.FlashGroupAControlData"), controlVal.get());
    Nikon3MakerNote::printFlashGroupADataFl6(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: FlashGroupAControlData present with mode == 0 (lower nibble 0) -> "n/a"
TEST_F(PrintFlashGroupADataFl6Test_493, ControlDataModeZero_493) {
    auto value = makeUnsignedByte(0x10);
    ExifData metadata;
    // mode = 0x00 & 0x0F = 0
    auto controlVal = makeUnsignedByte(0x00);
    metadata.add(ExifKey("Exif.NikonFl6.FlashGroupAControlData"), controlVal.get());
    Nikon3MakerNote::printFlashGroupADataFl6(os, *value, &metadata);
    std::string result = os.str();
    // Should output "n/a" (possibly translated)
    EXPECT_FALSE(result.empty());
    // Should not have parentheses
    EXPECT_EQ(result.find("("), std::string::npos);
}

// Test: FlashGroupAControlData present with mode = 0xF0 (lower nibble 0) -> "n/a"
TEST_F(PrintFlashGroupADataFl6Test_493, ControlDataHighNibbleOnly_493) {
    auto value = makeUnsignedByte(0x20);
    ExifData metadata;
    // mode = 0xF0 & 0x0F = 0
    auto controlVal = makeUnsignedByte(0xF0);
    metadata.add(ExifKey("Exif.NikonFl6.FlashGroupAControlData"), controlVal.get());
    Nikon3MakerNote::printFlashGroupADataFl6(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result.find("("), std::string::npos);
}

// Test: FlashGroupAControlData present with non-zero mode -> calls printFlashCompensationValue
TEST_F(PrintFlashGroupADataFl6Test_493, ControlDataNonZeroMode_493) {
    auto value = makeUnsignedByte(0x00);
    ExifData metadata;
    // mode = 0x01 & 0x0F = 1 (non-zero)
    auto controlVal = makeUnsignedByte(0x01);
    metadata.add(ExifKey("Exif.NikonFl6.FlashGroupAControlData"), controlVal.get());
    Nikon3MakerNote::printFlashGroupADataFl6(os, *value, &metadata);
    std::string result = os.str();
    // Should produce some output from printFlashCompensationValue
    EXPECT_FALSE(result.empty());
}

// Test: FlashGroupAControlData with mode = 0x03 (non-zero low nibble)
TEST_F(PrintFlashGroupADataFl6Test_493, ControlDataMode3_493) {
    auto value = makeUnsignedByte(0x06);
    ExifData metadata;
    // mode = 0x03 & 0x0F = 3
    auto controlVal = makeUnsignedByte(0x03);
    metadata.add(ExifKey("Exif.NikonFl6.FlashGroupAControlData"), controlVal.get());
    Nikon3MakerNote::printFlashGroupADataFl6(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: FlashGroupAControlData with mode = 0x0F (max low nibble)
TEST_F(PrintFlashGroupADataFl6Test_493, ControlDataMaxLowNibble_493) {
    auto value = makeUnsignedByte(0xFF);
    ExifData metadata;
    // mode = 0x0F & 0x0F = 0x0F (non-zero)
    auto controlVal = makeUnsignedByte(0x0F);
    metadata.add(ExifKey("Exif.NikonFl6.FlashGroupAControlData"), controlVal.get());
    Nikon3MakerNote::printFlashGroupADataFl6(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: Value 0 with non-zero mode
TEST_F(PrintFlashGroupADataFl6Test_493, ValueZeroWithNonZeroMode_493) {
    auto value = makeUnsignedByte(0x00);
    ExifData metadata;
    auto controlVal = makeUnsignedByte(0x02);
    metadata.add(ExifKey("Exif.NikonFl6.FlashGroupAControlData"), controlVal.get());
    Nikon3MakerNote::printFlashGroupADataFl6(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: Return value is same ostream reference
TEST_F(PrintFlashGroupADataFl6Test_493, ReturnsSameStream_493) {
    auto value = makeUnsignedByte(0x10);
    ExifData metadata;
    std::ostream& ret = Nikon3MakerNote::printFlashGroupADataFl6(os, *value, &metadata);
    EXPECT_EQ(&ret, &os);
}

// Test: Return value is same ostream reference with null metadata
TEST_F(PrintFlashGroupADataFl6Test_493, ReturnsSameStreamNullMetadata_493) {
    auto value = makeUnsignedByte(0x10);
    std::ostream& ret = Nikon3MakerNote::printFlashGroupADataFl6(os, *value, nullptr);
    EXPECT_EQ(&ret, &os);
}

// Test: Control data with multiple values (count != 1) should produce parenthesized
TEST_F(PrintFlashGroupADataFl6Test_493, ControlDataMultipleValues_493) {
    auto value = makeUnsignedByte(0x10);
    ExifData metadata;
    auto controlVal = makeUnsignedByteMulti({0x01, 0x02});
    metadata.add(ExifKey("Exif.NikonFl6.FlashGroupAControlData"), controlVal.get());
    Nikon3MakerNote::printFlashGroupADataFl6(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: Value with byte = 0x80 and mode = 1
TEST_F(PrintFlashGroupADataFl6Test_493, Value0x80WithMode1_493) {
    auto value = makeUnsignedByte(0x80);
    ExifData metadata;
    auto controlVal = makeUnsignedByte(0x01);
    metadata.add(ExifKey("Exif.NikonFl6.FlashGroupAControlData"), controlVal.get());
    Nikon3MakerNote::printFlashGroupADataFl6(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: ControlData = 0x10 means mode = 0x10 & 0x0F = 0 -> n/a
TEST_F(PrintFlashGroupADataFl6Test_493, ControlData0x10MeansMode0_493) {
    auto value = makeUnsignedByte(0x42);
    ExifData metadata;
    auto controlVal = makeUnsignedByte(0x10);
    metadata.add(ExifKey("Exif.NikonFl6.FlashGroupAControlData"), controlVal.get());
    Nikon3MakerNote::printFlashGroupADataFl6(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result.find("("), std::string::npos);
}

// Test: ControlData = 0x15 means mode = 0x15 & 0x0F = 5 (non-zero)
TEST_F(PrintFlashGroupADataFl6Test_493, ControlData0x15MeansMode5_493) {
    auto value = makeUnsignedByte(0x42);
    ExifData metadata;
    auto controlVal = makeUnsignedByte(0x15);
    metadata.add(ExifKey("Exif.NikonFl6.FlashGroupAControlData"), controlVal.get());
    Nikon3MakerNote::printFlashGroupADataFl6(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}
