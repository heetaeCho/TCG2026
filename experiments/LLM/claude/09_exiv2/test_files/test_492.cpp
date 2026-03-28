#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Include the internal header for Nikon3MakerNote
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteFlashGroupBCControlDataTest_492 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test: When value count is not 1, should output raw value in parentheses
TEST_F(Nikon3MakerNoteFlashGroupBCControlDataTest_492, CountNotOne_OutputsRawValue_492) {
    // Create a value with count > 1 (two unsigned bytes)
    auto value = Value::create(unsignedByte);
    value->read("10 20");
    
    Nikon3MakerNote::printFlashGroupBCControlData(os, *value, nullptr);
    std::string result = os.str();
    
    // Should be wrapped in parentheses since count != 1
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: When value type is not unsignedByte, should output raw value in parentheses
TEST_F(Nikon3MakerNoteFlashGroupBCControlDataTest_492, WrongTypeId_OutputsRawValue_492) {
    auto value = Value::create(unsignedShort);
    value->read("10");
    
    Nikon3MakerNote::printFlashGroupBCControlData(os, *value, nullptr);
    std::string result = os.str();
    
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Value 0x00 means high nibble=0 (Off), low nibble=0 (Off)
TEST_F(Nikon3MakerNoteFlashGroupBCControlDataTest_492, ValueZero_BothOff_492) {
    auto value = Value::create(unsignedByte);
    value->read("0");
    
    Nikon3MakerNote::printFlashGroupBCControlData(os, *value, nullptr);
    std::string result = os.str();
    
    // 0 >> 4 = 0 -> "Off", 0 & 0x0f = 0 -> "Off"
    EXPECT_NE(result.find("Off"), std::string::npos);
    EXPECT_NE(result.find(", "), std::string::npos);
}

// Test: Value 0x12 means high nibble=1 (TTL), low nibble=2 (iTTL)
TEST_F(Nikon3MakerNoteFlashGroupBCControlDataTest_492, Value0x12_TTLAndiTTL_492) {
    auto value = Value::create(unsignedByte);
    // 0x12 = 18 decimal
    value->read("18");
    
    Nikon3MakerNote::printFlashGroupBCControlData(os, *value, nullptr);
    std::string result = os.str();
    
    // high nibble = 1 -> TTL, low nibble = 2 -> iTTL
    EXPECT_NE(result.find("TTL"), std::string::npos);
    EXPECT_NE(result.find("iTTL"), std::string::npos);
    EXPECT_NE(result.find(", "), std::string::npos);
}

// Test: Value 0x36 means high nibble=3 (Auto Aperture), low nibble=6 (Manual)
TEST_F(Nikon3MakerNoteFlashGroupBCControlDataTest_492, Value0x36_AutoApertureAndManual_492) {
    auto value = Value::create(unsignedByte);
    // 0x36 = 54 decimal
    value->read("54");
    
    Nikon3MakerNote::printFlashGroupBCControlData(os, *value, nullptr);
    std::string result = os.str();
    
    EXPECT_NE(result.find("Auto Aperture"), std::string::npos);
    EXPECT_NE(result.find("Manual"), std::string::npos);
    EXPECT_NE(result.find(", "), std::string::npos);
}

// Test: Value 0x45 means high nibble=4 (Automatic), low nibble=5 (GN (distance priority))
TEST_F(Nikon3MakerNoteFlashGroupBCControlDataTest_492, Value0x45_AutomaticAndGN_492) {
    auto value = Value::create(unsignedByte);
    // 0x45 = 69 decimal
    value->read("69");
    
    Nikon3MakerNote::printFlashGroupBCControlData(os, *value, nullptr);
    std::string result = os.str();
    
    EXPECT_NE(result.find("Automatic"), std::string::npos);
    EXPECT_NE(result.find("GN (distance priority)"), std::string::npos);
}

// Test: Value 0x67 means high nibble=6 (Manual), low nibble=7 (Repeating Flash)
TEST_F(Nikon3MakerNoteFlashGroupBCControlDataTest_492, Value0x67_ManualAndRepeatingFlash_492) {
    auto value = Value::create(unsignedByte);
    // 0x67 = 103 decimal
    value->read("103");
    
    Nikon3MakerNote::printFlashGroupBCControlData(os, *value, nullptr);
    std::string result = os.str();
    
    EXPECT_NE(result.find("Manual"), std::string::npos);
    EXPECT_NE(result.find("Repeating Flash"), std::string::npos);
}

// Test: Value 0x77 means high nibble=7 (Repeating Flash), low nibble=7 (Repeating Flash)
TEST_F(Nikon3MakerNoteFlashGroupBCControlDataTest_492, Value0x77_BothRepeatingFlash_492) {
    auto value = Value::create(unsignedByte);
    // 0x77 = 119 decimal
    value->read("119");
    
    Nikon3MakerNote::printFlashGroupBCControlData(os, *value, nullptr);
    std::string result = os.str();
    
    // Both should be "Repeating Flash"
    size_t first = result.find("Repeating Flash");
    EXPECT_NE(first, std::string::npos);
    size_t second = result.find("Repeating Flash", first + 1);
    EXPECT_NE(second, std::string::npos);
}

// Test: Value where high nibble is out of known range (e.g., 0x80 = 128, high nibble=8)
TEST_F(Nikon3MakerNoteFlashGroupBCControlDataTest_492, HighNibbleOutOfRange_492) {
    auto value = Value::create(unsignedByte);
    // 0x80 = 128 decimal, high nibble = 8 (unknown), low nibble = 0 (Off)
    value->read("128");
    
    Nikon3MakerNote::printFlashGroupBCControlData(os, *value, nullptr);
    std::string result = os.str();
    
    // Should still produce output with a comma separator
    EXPECT_NE(result.find(", "), std::string::npos);
}

// Test: Value where low nibble is out of known range (e.g., 0x0F = 15, low nibble=15)
TEST_F(Nikon3MakerNoteFlashGroupBCControlDataTest_492, LowNibbleOutOfRange_492) {
    auto value = Value::create(unsignedByte);
    // 0x0F = 15 decimal, high nibble = 0 (Off), low nibble = 15 (unknown)
    value->read("15");
    
    Nikon3MakerNote::printFlashGroupBCControlData(os, *value, nullptr);
    std::string result = os.str();
    
    EXPECT_NE(result.find(", "), std::string::npos);
}

// Test: Passing nullptr for ExifData should not crash
TEST_F(Nikon3MakerNoteFlashGroupBCControlDataTest_492, NullExifData_NoCrash_492) {
    auto value = Value::create(unsignedByte);
    value->read("0");
    
    EXPECT_NO_THROW(Nikon3MakerNote::printFlashGroupBCControlData(os, *value, nullptr));
}

// Test: With valid ExifData pointer (non-null)
TEST_F(Nikon3MakerNoteFlashGroupBCControlDataTest_492, NonNullExifData_492) {
    ExifData exifData;
    auto value = Value::create(unsignedByte);
    value->read("0");
    
    EXPECT_NO_THROW(Nikon3MakerNote::printFlashGroupBCControlData(os, *value, &exifData));
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: Count of 0 (empty value) should output parenthesized
TEST_F(Nikon3MakerNoteFlashGroupBCControlDataTest_492, EmptyValue_OutputsParenthesized_492) {
    auto value = Value::create(unsignedByte);
    // Don't read anything - count should be 0
    
    Nikon3MakerNote::printFlashGroupBCControlData(os, *value, nullptr);
    std::string result = os.str();
    
    // count() != 1, should output in parentheses
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Value 0x11 means high nibble=1 (TTL), low nibble=1 (TTL) - same mode both
TEST_F(Nikon3MakerNoteFlashGroupBCControlDataTest_492, Value0x11_BothTTL_492) {
    auto value = Value::create(unsignedByte);
    // 0x11 = 17 decimal
    value->read("17");
    
    Nikon3MakerNote::printFlashGroupBCControlData(os, *value, nullptr);
    std::string result = os.str();
    
    // Both should be TTL
    size_t first = result.find("TTL");
    EXPECT_NE(first, std::string::npos);
    // After comma, find second TTL
    size_t comma = result.find(", ");
    EXPECT_NE(comma, std::string::npos);
    size_t second = result.find("TTL", comma);
    EXPECT_NE(second, std::string::npos);
}

// Test: Return value is the same ostream reference
TEST_F(Nikon3MakerNoteFlashGroupBCControlDataTest_492, ReturnsSameOstream_492) {
    auto value = Value::create(unsignedByte);
    value->read("0");
    
    std::ostream& returned = Nikon3MakerNote::printFlashGroupBCControlData(os, *value, nullptr);
    EXPECT_EQ(&returned, &os);
}

// Test: Return value is the same ostream reference for error case
TEST_F(Nikon3MakerNoteFlashGroupBCControlDataTest_492, ReturnsSameOstream_ErrorCase_492) {
    auto value = Value::create(unsignedShort);
    value->read("0");
    
    std::ostream& returned = Nikon3MakerNote::printFlashGroupBCControlData(os, *value, nullptr);
    EXPECT_EQ(&returned, &os);
}

// Test: Value 0xFF (255) - both nibbles are 0xF (15), out of defined range
TEST_F(Nikon3MakerNoteFlashGroupBCControlDataTest_492, Value0xFF_BothNibblesMax_492) {
    auto value = Value::create(unsignedByte);
    value->read("255");
    
    EXPECT_NO_THROW(Nikon3MakerNote::printFlashGroupBCControlData(os, *value, nullptr));
    std::string result = os.str();
    EXPECT_NE(result.find(", "), std::string::npos);
}

// Test: Signed byte type should output parenthesized (not unsignedByte)
TEST_F(Nikon3MakerNoteFlashGroupBCControlDataTest_492, SignedByteType_OutputsParenthesized_492) {
    auto value = Value::create(signedByte);
    value->read("0");
    
    Nikon3MakerNote::printFlashGroupBCControlData(os, *value, nullptr);
    std::string result = os.str();
    
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}
