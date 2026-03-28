#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Include internal headers for Nikon3MakerNote
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PrintExternalFlashData1Fl6Test_485 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test: Value with wrong count (more than 1) should output raw value in parentheses
TEST_F(PrintExternalFlashData1Fl6Test_485, WrongCount_TwoValues_485) {
    auto value = Value::create(unsignedByte);
    value->read("1 2");
    Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: Value with wrong type (not unsignedByte) should output raw value in parentheses
TEST_F(PrintExternalFlashData1Fl6Test_485, WrongType_UnsignedShort_485) {
    auto value = Value::create(unsignedShort);
    value->read("1");
    Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test: Value 0 (bit 0 not set) should output "Did not fire"
TEST_F(PrintExternalFlashData1Fl6Test_485, DidNotFire_Zero_485) {
    auto value = Value::create(unsignedByte);
    value->read("0");
    Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, nullptr);
    std::string result = os.str();
    // "Did not fire" - check that it contains the expected substring
    EXPECT_TRUE(result.find("Did not fire") != std::string::npos || 
                result.find("not fire") != std::string::npos);
}

// Test: Value 2 (even, bit 0 not set) should output "Did not fire"
TEST_F(PrintExternalFlashData1Fl6Test_485, DidNotFire_Even_485) {
    auto value = Value::create(unsignedByte);
    value->read("2");
    Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Did not fire") != std::string::npos ||
                result.find("not fire") != std::string::npos);
}

// Test: Value 1 (bit 0 set, no other bits) should output "Fired" only
TEST_F(PrintExternalFlashData1Fl6Test_485, Fired_OnlyBit0_485) {
    auto value = Value::create(unsignedByte);
    value->read("1");
    Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Fired") != std::string::npos ||
                result.find("fired") != std::string::npos);
}

// Test: Value 5 (bit 0 and bit 2 set) - Fired with Bounce Flash adaptor
TEST_F(PrintExternalFlashData1Fl6Test_485, Fired_BounceFlashAdaptor_485) {
    auto value = Value::create(unsignedByte);
    value->read("5"); // 0x05 = bit 0 (fired) + bit 2 (Bounce Flash adaptor)
    Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Fired") != std::string::npos ||
                result.find("fired") != std::string::npos);
    EXPECT_TRUE(result.find("Bounce") != std::string::npos);
}

// Test: Value 17 (bit 0 and bit 4 set) - Fired with Wide Flash adaptor
TEST_F(PrintExternalFlashData1Fl6Test_485, Fired_WideFlashAdaptor_485) {
    auto value = Value::create(unsignedByte);
    value->read("17"); // 0x11 = bit 0 (fired) + bit 4 (Wide Flash adaptor)
    Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Fired") != std::string::npos ||
                result.find("fired") != std::string::npos);
    EXPECT_TRUE(result.find("Wide") != std::string::npos);
}

// Test: Value 33 (bit 0 and bit 5 set) - Fired with Nikon Diffusion Dome
TEST_F(PrintExternalFlashData1Fl6Test_485, Fired_NikonDiffusionDome_485) {
    auto value = Value::create(unsignedByte);
    value->read("33"); // 0x21 = bit 0 (fired) + bit 5 (Nikon Diffusion Dome)
    Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Fired") != std::string::npos ||
                result.find("fired") != std::string::npos);
    EXPECT_TRUE(result.find("Diffusion") != std::string::npos || 
                result.find("Dome") != std::string::npos);
}

// Test: Value 53 (bit 0, bit 2, bit 4, bit 5) - Fired with multiple adaptors
TEST_F(PrintExternalFlashData1Fl6Test_485, Fired_MultipleAdaptors_485) {
    auto value = Value::create(unsignedByte);
    value->read("53"); // 0x35 = 1 + 4 + 16 + 32
    Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Fired") != std::string::npos ||
                result.find("fired") != std::string::npos);
    EXPECT_TRUE(result.find("Bounce") != std::string::npos);
    EXPECT_TRUE(result.find("Wide") != std::string::npos);
    EXPECT_TRUE(result.find("Diffusion") != std::string::npos || 
                result.find("Dome") != std::string::npos);
}

// Test: Value 4 (bit 2 set but bit 0 not set) - Did not fire even with adaptor bit set
TEST_F(PrintExternalFlashData1Fl6Test_485, DidNotFire_AdaptorBitSet_485) {
    auto value = Value::create(unsignedByte);
    value->read("4"); // bit 2 set but not bit 0
    Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Did not fire") != std::string::npos ||
                result.find("not fire") != std::string::npos);
}

// Test: Null metadata pointer should still work
TEST_F(PrintExternalFlashData1Fl6Test_485, NullMetadata_Fired_485) {
    auto value = Value::create(unsignedByte);
    value->read("1");
    Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: Value with count 0 should output parenthesized value
TEST_F(PrintExternalFlashData1Fl6Test_485, EmptyValue_485) {
    auto value = Value::create(unsignedByte);
    // An empty value has count 0, which != 1
    Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
}

// Test: Value 255 (all bits set) - Fired with all adaptors
TEST_F(PrintExternalFlashData1Fl6Test_485, Fired_AllBitsSet_485) {
    auto value = Value::create(unsignedByte);
    value->read("255"); // 0xFF
    Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Fired") != std::string::npos ||
                result.find("fired") != std::string::npos);
}

// Test: Return value is the same ostream reference
TEST_F(PrintExternalFlashData1Fl6Test_485, ReturnsSameStream_485) {
    auto value = Value::create(unsignedByte);
    value->read("0");
    std::ostream& ret = Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, nullptr);
    EXPECT_EQ(&ret, &os);
}

// Test: Return value is the same ostream reference for fired case
TEST_F(PrintExternalFlashData1Fl6Test_485, ReturnsSameStream_Fired_485) {
    auto value = Value::create(unsignedByte);
    value->read("1");
    std::ostream& ret = Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, nullptr);
    EXPECT_EQ(&ret, &os);
}

// Test: Wrong type signedByte should also produce parenthesized output
TEST_F(PrintExternalFlashData1Fl6Test_485, WrongType_SignedByte_485) {
    auto value = Value::create(signedByte);
    value->read("1");
    Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos);
    EXPECT_TRUE(result.find(")") != std::string::npos);
}

// Test with ExifData (non-null metadata)
TEST_F(PrintExternalFlashData1Fl6Test_485, WithExifData_Fired_485) {
    ExifData exifData;
    auto value = Value::create(unsignedByte);
    value->read("1");
    Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Fired") != std::string::npos ||
                result.find("fired") != std::string::npos);
}

// Test with ExifData (non-null metadata) and did not fire
TEST_F(PrintExternalFlashData1Fl6Test_485, WithExifData_DidNotFire_485) {
    ExifData exifData;
    auto value = Value::create(unsignedByte);
    value->read("0");
    Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, &exifData);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Did not fire") != std::string::npos ||
                result.find("not fire") != std::string::npos);
}

// Test: Value 3 (bit 0 and bit 1 set) - Fired, bit 1 is not in bitmask table
TEST_F(PrintExternalFlashData1Fl6Test_485, Fired_UnknownBit_485) {
    auto value = Value::create(unsignedByte);
    value->read("3"); // 0x03 = bit 0 (fired) + bit 1 (not in adaptor table)
    Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("Fired") != std::string::npos ||
                result.find("fired") != std::string::npos);
}
