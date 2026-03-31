#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Include internal headers for Nikon3MakerNote
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PrintExternalFlashData1Fl7Test_487 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test: Value with wrong count (not 1) should print raw value in parentheses
TEST_F(PrintExternalFlashData1Fl7Test_487, WrongCount_PrintsRawValue_487) {
    // Create a value with count > 1
    auto value = Value::create(unsignedByte);
    value->read("0 1");
    Nikon3MakerNote::printExternalFlashData1Fl7(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Value with wrong type (not unsignedByte) should print raw value in parentheses
TEST_F(PrintExternalFlashData1Fl7Test_487, WrongType_PrintsRawValue_487) {
    auto value = Value::create(unsignedShort);
    value->read("0");
    Nikon3MakerNote::printExternalFlashData1Fl7(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Value 0x00 - external flash off (bit 0 not set)
TEST_F(PrintExternalFlashData1Fl7Test_487, FlashOff_Value0_487) {
    auto value = Value::create(unsignedByte);
    value->read("0");
    Nikon3MakerNote::printExternalFlashData1Fl7(os, *value, nullptr);
    std::string result = os.str();
    // Should contain "External flash off" or equivalent translation
    EXPECT_NE(result.find("flash off"), std::string::npos);
}

// Test: Value 0x02 - external flash off (bit 0 not set, other bits set)
TEST_F(PrintExternalFlashData1Fl7Test_487, FlashOff_Value2_487) {
    auto value = Value::create(unsignedByte);
    value->read("2");
    Nikon3MakerNote::printExternalFlashData1Fl7(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("flash off"), std::string::npos);
}

// Test: Value 0x01 - external flash on, no zoom override, no adaptors
TEST_F(PrintExternalFlashData1Fl7Test_487, FlashOn_NoZoomOverride_NoAdaptors_487) {
    auto value = Value::create(unsignedByte);
    value->read("1");
    Nikon3MakerNote::printExternalFlashData1Fl7(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("flash on"), std::string::npos);
    EXPECT_NE(result.find("No external flash zoom override"), std::string::npos);
}

// Test: Value 0x81 - external flash on with zoom override (bit 7 + bit 0 set)
TEST_F(PrintExternalFlashData1Fl7Test_487, FlashOn_WithZoomOverride_487) {
    auto value = Value::create(unsignedByte);
    value->read("129"); // 0x81
    Nikon3MakerNote::printExternalFlashData1Fl7(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("flash on"), std::string::npos);
    EXPECT_NE(result.find("External flash zoom override"), std::string::npos);
    // Should NOT contain "No external flash zoom override"
    EXPECT_EQ(result.find("No external flash zoom override"), std::string::npos);
}

// Test: Value 0x05 - external flash on with Bounce Flash adaptor (bit 2 + bit 0)
TEST_F(PrintExternalFlashData1Fl7Test_487, FlashOn_BounceFlashAdaptor_487) {
    auto value = Value::create(unsignedByte);
    value->read("5"); // 0x05 = bit 0 + bit 2
    Nikon3MakerNote::printExternalFlashData1Fl7(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("flash on"), std::string::npos);
    EXPECT_NE(result.find("Bounce Flash adaptor"), std::string::npos);
}

// Test: Value 0x11 - external flash on with Wide Flash adaptor (bit 4 + bit 0)
TEST_F(PrintExternalFlashData1Fl7Test_487, FlashOn_WideFlashAdaptor_487) {
    auto value = Value::create(unsignedByte);
    value->read("17"); // 0x11 = bit 0 + bit 4
    Nikon3MakerNote::printExternalFlashData1Fl7(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("flash on"), std::string::npos);
    EXPECT_NE(result.find("Wide Flash adaptor"), std::string::npos);
}

// Test: Value 0x21 - external flash on with Nikon Diffusion Dome (bit 5 + bit 0)
TEST_F(PrintExternalFlashData1Fl7Test_487, FlashOn_NikonDiffusionDome_487) {
    auto value = Value::create(unsignedByte);
    value->read("33"); // 0x21 = bit 0 + bit 5
    Nikon3MakerNote::printExternalFlashData1Fl7(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("flash on"), std::string::npos);
    EXPECT_NE(result.find("Nikon Diffusion Dome"), std::string::npos);
}

// Test: Value 0x35 - external flash on, multiple adaptors (bit 0 + bit 2 + bit 4 + bit 5)
TEST_F(PrintExternalFlashData1Fl7Test_487, FlashOn_MultipleAdaptors_487) {
    auto value = Value::create(unsignedByte);
    value->read("53"); // 0x35 = 0x01 + 0x04 + 0x10 + 0x20
    Nikon3MakerNote::printExternalFlashData1Fl7(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("flash on"), std::string::npos);
    EXPECT_NE(result.find("Bounce Flash adaptor"), std::string::npos);
    EXPECT_NE(result.find("Wide Flash adaptor"), std::string::npos);
    EXPECT_NE(result.find("Nikon Diffusion Dome"), std::string::npos);
}

// Test: Value 0xB5 - external flash on, zoom override + multiple adaptors
TEST_F(PrintExternalFlashData1Fl7Test_487, FlashOn_ZoomOverrideAndMultipleAdaptors_487) {
    auto value = Value::create(unsignedByte);
    value->read("181"); // 0xB5 = 0x80 + 0x20 + 0x10 + 0x04 + 0x01
    Nikon3MakerNote::printExternalFlashData1Fl7(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("flash on"), std::string::npos);
    EXPECT_NE(result.find("External flash zoom override"), std::string::npos);
    EXPECT_EQ(result.find("No external flash zoom override"), std::string::npos);
}

// Test: Return value is the same ostream reference
TEST_F(PrintExternalFlashData1Fl7Test_487, ReturnsSameOstream_487) {
    auto value = Value::create(unsignedByte);
    value->read("0");
    std::ostream& ret = Nikon3MakerNote::printExternalFlashData1Fl7(os, *value, nullptr);
    EXPECT_EQ(&ret, &os);
}

// Test: Passing nullptr for metadata still works
TEST_F(PrintExternalFlashData1Fl7Test_487, NullMetadata_FlashOff_487) {
    auto value = Value::create(unsignedByte);
    value->read("0");
    Nikon3MakerNote::printExternalFlashData1Fl7(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: Passing nullptr for metadata with flash on
TEST_F(PrintExternalFlashData1Fl7Test_487, NullMetadata_FlashOn_487) {
    auto value = Value::create(unsignedByte);
    value->read("1");
    Nikon3MakerNote::printExternalFlashData1Fl7(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("flash on"), std::string::npos);
}

// Test: Value 0x80 - bit 7 set but bit 0 not set = flash off
TEST_F(PrintExternalFlashData1Fl7Test_487, FlashOff_ZoomOverrideBitButFlashOff_487) {
    auto value = Value::create(unsignedByte);
    value->read("128"); // 0x80
    Nikon3MakerNote::printExternalFlashData1Fl7(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("flash off"), std::string::npos);
}

// Test: Value with ExifData passed (non-null metadata)
TEST_F(PrintExternalFlashData1Fl7Test_487, WithExifData_FlashOn_487) {
    ExifData exifData;
    auto value = Value::create(unsignedByte);
    value->read("1");
    Nikon3MakerNote::printExternalFlashData1Fl7(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_NE(result.find("flash on"), std::string::npos);
}

// Test: signedByte type should be treated as wrong type
TEST_F(PrintExternalFlashData1Fl7Test_487, WrongType_SignedByte_487) {
    auto value = Value::create(signedByte);
    value->read("1");
    Nikon3MakerNote::printExternalFlashData1Fl7(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: unsignedLong type should be treated as wrong type
TEST_F(PrintExternalFlashData1Fl7Test_487, WrongType_UnsignedLong_487) {
    auto value = Value::create(unsignedLong);
    value->read("1");
    Nikon3MakerNote::printExternalFlashData1Fl7(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Value 0xFF - all bits set, flash on with zoom override
TEST_F(PrintExternalFlashData1Fl7Test_487, AllBitsSet_487) {
    auto value = Value::create(unsignedByte);
    value->read("255"); // 0xFF
    Nikon3MakerNote::printExternalFlashData1Fl7(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("flash on"), std::string::npos);
    EXPECT_NE(result.find("External flash zoom override"), std::string::npos);
}
