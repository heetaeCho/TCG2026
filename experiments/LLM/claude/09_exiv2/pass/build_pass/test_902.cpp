#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// We need access to the Internal namespace
#include "olympusmn_int.hpp"

using namespace Exiv2;

// Helper to create a Value with unsigned byte type containing specific bytes
static std::unique_ptr<Value> makeUnsignedByteValue(const std::vector<byte>& bytes) {
    auto value = Value::create(unsignedByte);
    for (auto b : bytes) {
        // DataBuf with single byte
        value->read(reinterpret_cast<const byte*>(&b), 1, invalidByteOrder);
    }
    return value;
}

class OlympusMakerNoteTest_902 : public ::testing::Test {
protected:
    // We use the static function through ExifTags or we create a helper
    // Since the class is in Internal namespace, we need to access it
    // The function is printEq0x0301 - let's use it via the tag info tables
    // or directly if accessible.
    
    // We'll test by calling the print function indirectly through Exiv2's tag mechanism
    // or by directly instantiating if possible.
    
    std::ostringstream os;
};

// Test: When value has exactly 6 unsigned bytes with {0,0} pattern -> "None"
TEST_F(OlympusMakerNoteTest_902, PrintNoneExtender_902) {
    auto value = Value::create(unsignedByte);
    // 6 bytes: v0=0, v1=X, v2=0, v3=X, v4=X, v5=X
    byte data[] = {0, 0, 0, 0, 0, 0};
    value->read(data, 6, invalidByteOrder);
    
    Internal::OlympusMakerNote mn;
    mn.printEq0x0301(os, *value, nullptr);
    
    EXPECT_EQ(os.str(), "None");
}

// Test: EC-14 1.4x Teleconverter {0, 4}
TEST_F(OlympusMakerNoteTest_902, PrintEC14Teleconverter_902) {
    auto value = Value::create(unsignedByte);
    byte data[] = {0, 0, 4, 0, 0, 0};
    value->read(data, 6, invalidByteOrder);
    
    Internal::OlympusMakerNote mn;
    mn.printEq0x0301(os, *value, nullptr);
    
    EXPECT_EQ(os.str(), "Olympus Zuiko Digital EC-14 1.4x Teleconverter");
}

// Test: EX-25 Extension Tube {0, 8}
TEST_F(OlympusMakerNoteTest_902, PrintEX25ExtensionTube_902) {
    auto value = Value::create(unsignedByte);
    byte data[] = {0, 0, 8, 0, 0, 0};
    value->read(data, 6, invalidByteOrder);
    
    Internal::OlympusMakerNote mn;
    mn.printEq0x0301(os, *value, nullptr);
    
    EXPECT_EQ(os.str(), "Olympus EX-25 Extension Tube");
}

// Test: EC-20 2.0x Teleconverter {0, 16}
TEST_F(OlympusMakerNoteTest_902, PrintEC20Teleconverter_902) {
    auto value = Value::create(unsignedByte);
    byte data[] = {0, 0, 16, 0, 0, 0};
    value->read(data, 6, invalidByteOrder);
    
    Internal::OlympusMakerNote mn;
    mn.printEq0x0301(os, *value, nullptr);
    
    EXPECT_EQ(os.str(), "Olympus Zuiko Digital EC-20 2.0x Teleconverter");
}

// Test: Unknown extender model - should print raw value
TEST_F(OlympusMakerNoteTest_902, PrintUnknownExtender_902) {
    auto value = Value::create(unsignedByte);
    byte data[] = {1, 0, 99, 0, 0, 0};
    value->read(data, 6, invalidByteOrder);
    
    Internal::OlympusMakerNote mn;
    mn.printEq0x0301(os, *value, nullptr);
    
    // Should fall through to os << value (raw representation)
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    // It should not match any known label
    EXPECT_NE(result, "None");
    EXPECT_NE(result, "Olympus Zuiko Digital EC-14 1.4x Teleconverter");
    EXPECT_NE(result, "Olympus EX-25 Extension Tube");
    EXPECT_NE(result, "Olympus Zuiko Digital EC-20 2.0x Teleconverter");
}

// Test: Wrong count (not 6) - should print raw value
TEST_F(OlympusMakerNoteTest_902, PrintWrongCount_902) {
    auto value = Value::create(unsignedByte);
    byte data[] = {0, 0, 0, 0};
    value->read(data, 4, invalidByteOrder);
    
    Internal::OlympusMakerNote mn;
    mn.printEq0x0301(os, *value, nullptr);
    
    // With wrong count, should print raw value
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: Wrong type (not unsignedByte) - should print raw value
TEST_F(OlympusMakerNoteTest_902, PrintWrongType_902) {
    auto value = Value::create(unsignedShort);
    // 3 unsigned shorts = 6 bytes worth, but count would be 3
    uint16_t data[] = {0, 0, 0};
    value->read(reinterpret_cast<const byte*>(data), sizeof(data), littleEndian);
    
    Internal::OlympusMakerNote mn;
    mn.printEq0x0301(os, *value, nullptr);
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: Count is 6 but wrong type - should print raw value
TEST_F(OlympusMakerNoteTest_902, PrintCount6WrongType_902) {
    // unsignedShort with 6 elements would need 12 bytes
    auto value = Value::create(unsignedShort);
    uint16_t data[] = {0, 0, 0, 0, 0, 0};
    value->read(reinterpret_cast<const byte*>(data), sizeof(data), littleEndian);
    
    Internal::OlympusMakerNote mn;
    mn.printEq0x0301(os, *value, nullptr);
    
    // count=6 but typeId != unsignedByte, should print raw
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: Boundary - v0 matches but v2 doesn't
TEST_F(OlympusMakerNoteTest_902, PrintPartialMatch_902) {
    auto value = Value::create(unsignedByte);
    byte data[] = {0, 0, 5, 0, 0, 0}; // v0=0, v2=5 -> no match
    value->read(data, 6, invalidByteOrder);
    
    Internal::OlympusMakerNote mn;
    mn.printEq0x0301(os, *value, nullptr);
    
    std::string result = os.str();
    EXPECT_NE(result, "None");
    EXPECT_NE(result, "Olympus Zuiko Digital EC-14 1.4x Teleconverter");
    EXPECT_NE(result, "Olympus EX-25 Extension Tube");
    EXPECT_NE(result, "Olympus Zuiko Digital EC-20 2.0x Teleconverter");
}

// Test: Empty value
TEST_F(OlympusMakerNoteTest_902, PrintEmptyValue_902) {
    auto value = Value::create(unsignedByte);
    // No data read - count should be 0
    
    Internal::OlympusMakerNote mn;
    mn.printEq0x0301(os, *value, nullptr);
    
    // count != 6, should print raw value
    // Even empty, it should not crash
    // Result may be empty string for empty value
}

// Test: Single byte value (count = 1)
TEST_F(OlympusMakerNoteTest_902, PrintSingleByteValue_902) {
    auto value = Value::create(unsignedByte);
    byte data[] = {0};
    value->read(data, 1, invalidByteOrder);
    
    Internal::OlympusMakerNote mn;
    mn.printEq0x0301(os, *value, nullptr);
    
    // count=1 != 6, fallback to raw
    std::string result = os.str();
    // Should not crash, and should produce some output
}

// Test: Verify that non-zero bytes at positions 1,3,4,5 don't affect matching
TEST_F(OlympusMakerNoteTest_902, PrintIgnoresOtherBytes_902) {
    auto value = Value::create(unsignedByte);
    // v0=0 (pos 0), v2=4 (pos 2), other positions have non-zero values
    byte data[] = {0, 255, 4, 128, 64, 32};
    value->read(data, 6, invalidByteOrder);
    
    Internal::OlympusMakerNote mn;
    mn.printEq0x0301(os, *value, nullptr);
    
    EXPECT_EQ(os.str(), "Olympus Zuiko Digital EC-14 1.4x Teleconverter");
}

// Test: All max byte values (255) - unknown model
TEST_F(OlympusMakerNoteTest_902, PrintMaxByteValues_902) {
    auto value = Value::create(unsignedByte);
    byte data[] = {255, 255, 255, 255, 255, 255};
    value->read(data, 6, invalidByteOrder);
    
    Internal::OlympusMakerNote mn;
    mn.printEq0x0301(os, *value, nullptr);
    
    std::string result = os.str();
    // No known model matches 255,255 so should print raw
    EXPECT_NE(result, "None");
    EXPECT_NE(result, "Olympus Zuiko Digital EC-14 1.4x Teleconverter");
}

// Test: ExifData pointer is nullptr - should work fine
TEST_F(OlympusMakerNoteTest_902, PrintWithNullExifData_902) {
    auto value = Value::create(unsignedByte);
    byte data[] = {0, 0, 0, 0, 0, 0};
    value->read(data, 6, invalidByteOrder);
    
    Internal::OlympusMakerNote mn;
    mn.printEq0x0301(os, *value, nullptr);
    
    EXPECT_EQ(os.str(), "None");
}

// Test: 7 bytes (more than 6)
TEST_F(OlympusMakerNoteTest_902, PrintSevenBytes_902) {
    auto value = Value::create(unsignedByte);
    byte data[] = {0, 0, 0, 0, 0, 0, 0};
    value->read(data, 7, invalidByteOrder);
    
    Internal::OlympusMakerNote mn;
    mn.printEq0x0301(os, *value, nullptr);
    
    // count=7 != 6, should print raw
    std::string result = os.str();
    // Should not print "None" since count check fails first
}
