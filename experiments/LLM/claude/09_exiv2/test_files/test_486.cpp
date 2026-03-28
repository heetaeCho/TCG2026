#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Include the internal header for Nikon3MakerNote
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PrintExternalFlashData2Fl6Test_486 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test: Value with wrong count (count != 1) should print raw value in parentheses
TEST_F(PrintExternalFlashData2Fl6Test_486, WrongCount_TooMany_486) {
    // Create a value with 2 unsigned bytes
    auto value = Value::create(unsignedByte);
    value->read("128 5");
    ASSERT_EQ(value->count(), 2u);
    
    Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
    std::string result = os.str();
    // Should be wrapped in parentheses since count != 1
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Value with wrong type (not unsignedByte) should print raw value in parentheses
TEST_F(PrintExternalFlashData2Fl6Test_486, WrongType_UnsignedShort_486) {
    auto value = Value::create(unsignedShort);
    value->read("128");
    ASSERT_EQ(value->count(), 1u);
    ASSERT_EQ(value->typeId(), unsignedShort);
    
    Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Value with count 0 should print raw value in parentheses
TEST_F(PrintExternalFlashData2Fl6Test_486, EmptyValue_486) {
    auto value = Value::create(unsignedByte);
    // Empty value, count == 0
    Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: External flash off when bit 7 (0x80) is not set - value 0
TEST_F(PrintExternalFlashData2Fl6Test_486, ExternalFlashOff_Zero_486) {
    auto value = Value::create(unsignedByte);
    value->read("0");
    ASSERT_EQ(value->count(), 1u);
    ASSERT_EQ(value->typeId(), unsignedByte);
    
    Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
    std::string result = os.str();
    // Should contain "External flash off" (or translated equivalent)
    // Bit 7 is 0, so flash is off
    EXPECT_NE(result.find("ff"), std::string::npos);  // "off" or "Off"
}

// Test: External flash off when value is 0x7F (all bits except bit 7)
TEST_F(PrintExternalFlashData2Fl6Test_486, ExternalFlashOff_0x7F_486) {
    auto value = Value::create(unsignedByte);
    value->read("127"); // 0x7F
    ASSERT_EQ(value->count(), 1u);
    
    Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("ff"), std::string::npos);
}

// Test: External flash on with control mode 0 (Off) - value 0x80
TEST_F(PrintExternalFlashData2Fl6Test_486, ExternalFlashOn_ControlModeOff_486) {
    auto value = Value::create(unsignedByte);
    value->read("128"); // 0x80: bit 7 set, lower nibble = 0 -> "Off"
    ASSERT_EQ(value->count(), 1u);
    
    Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
    std::string result = os.str();
    // Should contain "External flash on" and flash control mode for 0
    EXPECT_NE(result.find("n"), std::string::npos); // "on"
}

// Test: External flash on with control mode TTL (1) - value 0x81
TEST_F(PrintExternalFlashData2Fl6Test_486, ExternalFlashOn_TTL_486) {
    auto value = Value::create(unsignedByte);
    value->read("129"); // 0x81: bit 7 set, lower nibble = 1 -> "TTL"
    ASSERT_EQ(value->count(), 1u);
    
    Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("TTL"), std::string::npos);
}

// Test: External flash on with control mode iTTL (2) - value 0x82
TEST_F(PrintExternalFlashData2Fl6Test_486, ExternalFlashOn_iTTL_486) {
    auto value = Value::create(unsignedByte);
    value->read("130"); // 0x82: bit 7 set, lower nibble = 2 -> "iTTL"
    ASSERT_EQ(value->count(), 1u);
    
    Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("iTTL"), std::string::npos);
}

// Test: External flash on with control mode Auto Aperture (3) - value 0x83
TEST_F(PrintExternalFlashData2Fl6Test_486, ExternalFlashOn_AutoAperture_486) {
    auto value = Value::create(unsignedByte);
    value->read("131"); // 0x83
    ASSERT_EQ(value->count(), 1u);
    
    Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("Auto Aperture"), std::string::npos);
}

// Test: External flash on with control mode Automatic (4) - value 0x84
TEST_F(PrintExternalFlashData2Fl6Test_486, ExternalFlashOn_Automatic_486) {
    auto value = Value::create(unsignedByte);
    value->read("132"); // 0x84
    ASSERT_EQ(value->count(), 1u);
    
    Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("Automatic"), std::string::npos);
}

// Test: External flash on with control mode GN (5) - value 0x85
TEST_F(PrintExternalFlashData2Fl6Test_486, ExternalFlashOn_GN_486) {
    auto value = Value::create(unsignedByte);
    value->read("133"); // 0x85
    ASSERT_EQ(value->count(), 1u);
    
    Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("distance priority"), std::string::npos);
}

// Test: External flash on with control mode Manual (6) - value 0x86
TEST_F(PrintExternalFlashData2Fl6Test_486, ExternalFlashOn_Manual_486) {
    auto value = Value::create(unsignedByte);
    value->read("134"); // 0x86
    ASSERT_EQ(value->count(), 1u);
    
    Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("Manual"), std::string::npos);
}

// Test: External flash on with control mode Repeating Flash (7) - value 0x87
TEST_F(PrintExternalFlashData2Fl6Test_486, ExternalFlashOn_RepeatingFlash_486) {
    auto value = Value::create(unsignedByte);
    value->read("135"); // 0x87
    ASSERT_EQ(value->count(), 1u);
    
    Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("Repeating Flash"), std::string::npos);
}

// Test: External flash on with unknown control mode (value > 7 in lower nibble)
TEST_F(PrintExternalFlashData2Fl6Test_486, ExternalFlashOn_UnknownControlMode_486) {
    auto value = Value::create(unsignedByte);
    value->read("143"); // 0x8F: bit 7 set, lower nibble = 15 -> unknown
    ASSERT_EQ(value->count(), 1u);
    
    Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
    std::string result = os.str();
    // Should still output something (flash on + unknown mode)
    EXPECT_FALSE(result.empty());
}

// Test: External flash on with higher bits set (0x90 range) - value 0x90 = lower nibble 0
TEST_F(PrintExternalFlashData2Fl6Test_486, ExternalFlashOn_HighBitsSet_486) {
    auto value = Value::create(unsignedByte);
    value->read("144"); // 0x90: bit 7 set, lower nibble = 0
    ASSERT_EQ(value->count(), 1u);
    
    Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
    std::string result = os.str();
    // Flash is on (bit 7 is set)
    EXPECT_FALSE(result.empty());
}

// Test: Value 0xFF - all bits set, lower nibble = 0x0F
TEST_F(PrintExternalFlashData2Fl6Test_486, ExternalFlashOn_AllBitsSet_486) {
    auto value = Value::create(unsignedByte);
    value->read("255"); // 0xFF
    ASSERT_EQ(value->count(), 1u);
    
    Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: External flash off for various values without bit 7
TEST_F(PrintExternalFlashData2Fl6Test_486, ExternalFlashOff_Value1_486) {
    auto value = Value::create(unsignedByte);
    value->read("1"); // 0x01: bit 7 not set
    ASSERT_EQ(value->count(), 1u);
    
    Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("ff"), std::string::npos);
}

// Test: Passing nullptr for metadata should work fine
TEST_F(PrintExternalFlashData2Fl6Test_486, NullMetadata_FlashOn_486) {
    auto value = Value::create(unsignedByte);
    value->read("129"); // 0x81
    ASSERT_EQ(value->count(), 1u);
    
    Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: Return value is the same ostream reference
TEST_F(PrintExternalFlashData2Fl6Test_486, ReturnsSameOstream_486) {
    auto value = Value::create(unsignedByte);
    value->read("128");
    
    std::ostream& returned = Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
    EXPECT_EQ(&returned, &os);
}

// Test: Return value is the same ostream reference for error case
TEST_F(PrintExternalFlashData2Fl6Test_486, ReturnsSameOstream_ErrorCase_486) {
    auto value = Value::create(unsignedShort);
    value->read("128");
    
    std::ostream& returned = Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
    EXPECT_EQ(&returned, &os);
}

// Test: External flash off - return value is the same ostream
TEST_F(PrintExternalFlashData2Fl6Test_486, ReturnsSameOstream_FlashOff_486) {
    auto value = Value::create(unsignedByte);
    value->read("0");
    
    std::ostream& returned = Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
    EXPECT_EQ(&returned, &os);
}

// Test: Value with signedByte type should be treated as wrong type
TEST_F(PrintExternalFlashData2Fl6Test_486, WrongType_SignedByte_486) {
    auto value = Value::create(signedByte);
    value->read("128");
    ASSERT_EQ(value->count(), 1u);
    ASSERT_NE(value->typeId(), unsignedByte);
    
    Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test with ExifData object (non-null metadata)
TEST_F(PrintExternalFlashData2Fl6Test_486, WithExifData_FlashOn_486) {
    ExifData exifData;
    auto value = Value::create(unsignedByte);
    value->read("130"); // 0x82 -> iTTL
    ASSERT_EQ(value->count(), 1u);
    
    Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("iTTL"), std::string::npos);
}

// Test: Masking behavior - only lower 4 bits determine control mode
// 0x86 = 1000 0110 -> lower nibble = 6 -> Manual
TEST_F(PrintExternalFlashData2Fl6Test_486, MaskingLowerNibble_486) {
    auto value = Value::create(unsignedByte);
    value->read("134"); // 0x86
    
    Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("Manual"), std::string::npos);
}

// Test: Value 0xF1 -> bit 7 set, lower nibble = 1 -> TTL
TEST_F(PrintExternalFlashData2Fl6Test_486, HigherBitsIgnored_TTL_486) {
    auto value = Value::create(unsignedByte);
    value->read("241"); // 0xF1: lower nibble = 1
    
    Nikon3MakerNote::printExternalFlashData2Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("TTL"), std::string::npos);
}
