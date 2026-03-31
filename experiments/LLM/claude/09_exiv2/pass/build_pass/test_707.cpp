#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need access to the PanasonicMakerNote class
// Since it's in Internal namespace, we include the relevant header
#include "panasonicmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PanasonicMakerNoteTest_707 : public ::testing::Test {
protected:
    PanasonicMakerNote maker;
    std::ostringstream os;

    // Helper to create a DataValue with two unsigned bytes
    DataValue createUnsignedByteValue(uint8_t b0, uint8_t b1) {
        DataValue val(unsignedByte);
        val.read(reinterpret_cast<const byte*>(&b0), 1, invalidByteOrder);
        val.read(reinterpret_cast<const byte*>(&b1), 1, invalidByteOrder);
        return val;
    }

    // Helper to create a DataValue with one unsigned byte
    DataValue createSingleByteValue(uint8_t b0) {
        DataValue val(unsignedByte);
        val.read(reinterpret_cast<const byte*>(&b0), 1, invalidByteOrder);
        return val;
    }
};

// Test: count < 2 should output raw value
TEST_F(PanasonicMakerNoteTest_707, Print0x000f_CountLessThanTwo_707) {
    DataValue val = createSingleByteValue(5);
    maker.print0x000f(os, val, nullptr);
    // With count < 2, it should just output the value directly
    EXPECT_FALSE(os.str().empty());
}

// Test: wrong type (not unsignedByte) should output raw value
TEST_F(PanasonicMakerNoteTest_707, Print0x000f_WrongType_707) {
    UShortValue val;
    val.read("1 2");
    maker.print0x000f(os, val, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test: l0=0, l1=1 -> "Spot mode on or 9 area"
TEST_F(PanasonicMakerNoteTest_707, Print0x000f_SpotModeOnOr9Area_707) {
    DataValue val = createUnsignedByteValue(0, 1);
    maker.print0x000f(os, val, nullptr);
    EXPECT_NE(os.str().find("Spot mode on"), std::string::npos);
}

// Test: l0=0, l1=16 -> "Spot mode off or 3-area (high speed)"
TEST_F(PanasonicMakerNoteTest_707, Print0x000f_SpotModeOff_707) {
    DataValue val = createUnsignedByteValue(0, 16);
    maker.print0x000f(os, val, nullptr);
    EXPECT_NE(os.str().find("Spot mode off"), std::string::npos);
}

// Test: l0=0, l1=23 -> "23-area"
TEST_F(PanasonicMakerNoteTest_707, Print0x000f_23Area_707) {
    DataValue val = createUnsignedByteValue(0, 23);
    maker.print0x000f(os, val, nullptr);
    EXPECT_NE(os.str().find("23-area"), std::string::npos);
}

// Test: l0=0, l1=49 -> "49-area"
TEST_F(PanasonicMakerNoteTest_707, Print0x000f_49Area_707) {
    DataValue val = createUnsignedByteValue(0, 49);
    maker.print0x000f(os, val, nullptr);
    EXPECT_NE(os.str().find("49-area"), std::string::npos);
}

// Test: l0=0, l1=225 -> "225-area"
TEST_F(PanasonicMakerNoteTest_707, Print0x000f_225Area_707) {
    DataValue val = createUnsignedByteValue(0, 225);
    maker.print0x000f(os, val, nullptr);
    EXPECT_NE(os.str().find("225-area"), std::string::npos);
}

// Test: l0=1, l1=0 -> "Spot focusing"
TEST_F(PanasonicMakerNoteTest_707, Print0x000f_SpotFocusing_707) {
    DataValue val = createUnsignedByteValue(1, 0);
    maker.print0x000f(os, val, nullptr);
    EXPECT_NE(os.str().find("Spot focusing"), std::string::npos);
}

// Test: l0=1, l1=1 -> "5-area"
TEST_F(PanasonicMakerNoteTest_707, Print0x000f_5Area_707) {
    DataValue val = createUnsignedByteValue(1, 1);
    maker.print0x000f(os, val, nullptr);
    EXPECT_NE(os.str().find("5-area"), std::string::npos);
}

// Test: l0=16, l1=0 -> "1-area"
TEST_F(PanasonicMakerNoteTest_707, Print0x000f_1Area_707) {
    DataValue val = createUnsignedByteValue(16, 0);
    maker.print0x000f(os, val, nullptr);
    EXPECT_NE(os.str().find("1-area"), std::string::npos);
}

// Test: l0=16, l1=16 -> "1-area (high speed)"
TEST_F(PanasonicMakerNoteTest_707, Print0x000f_1AreaHighSpeed_707) {
    DataValue val = createUnsignedByteValue(16, 16);
    maker.print0x000f(os, val, nullptr);
    EXPECT_NE(os.str().find("1-area (high speed)"), std::string::npos);
}

// Test: l0=32, l1=0 -> "3-area (auto)"
TEST_F(PanasonicMakerNoteTest_707, Print0x000f_3AreaAuto_707) {
    DataValue val = createUnsignedByteValue(32, 0);
    maker.print0x000f(os, val, nullptr);
    EXPECT_NE(os.str().find("3-area (auto)"), std::string::npos);
}

// Test: l0=32, l1=1 -> "3-area (left)"
TEST_F(PanasonicMakerNoteTest_707, Print0x000f_3AreaLeft_707) {
    DataValue val = createUnsignedByteValue(32, 1);
    maker.print0x000f(os, val, nullptr);
    EXPECT_NE(os.str().find("3-area (left)"), std::string::npos);
}

// Test: l0=32, l1=2 -> "3-area (center)"
TEST_F(PanasonicMakerNoteTest_707, Print0x000f_3AreaCenter_707) {
    DataValue val = createUnsignedByteValue(32, 2);
    maker.print0x000f(os, val, nullptr);
    EXPECT_NE(os.str().find("3-area (center)"), std::string::npos);
}

// Test: l0=32, l1=3 -> "3-area (right)"
TEST_F(PanasonicMakerNoteTest_707, Print0x000f_3AreaRight_707) {
    DataValue val = createUnsignedByteValue(32, 3);
    maker.print0x000f(os, val, nullptr);
    EXPECT_NE(os.str().find("3-area (right)"), std::string::npos);
}

// Test: l0=64, l1=0 -> "Face Detect"
TEST_F(PanasonicMakerNoteTest_707, Print0x000f_FaceDetect_707) {
    DataValue val = createUnsignedByteValue(64, 0);
    maker.print0x000f(os, val, nullptr);
    EXPECT_NE(os.str().find("Face Detect"), std::string::npos);
}

// Test: l0=128, l1=0 -> "Spot Focusing 2"
TEST_F(PanasonicMakerNoteTest_707, Print0x000f_SpotFocusing2_707) {
    DataValue val = createUnsignedByteValue(128, 0);
    maker.print0x000f(os, val, nullptr);
    EXPECT_NE(os.str().find("Spot Focusing 2"), std::string::npos);
}

// Test: l0=240, l1=0 -> "Tracking"
TEST_F(PanasonicMakerNoteTest_707, Print0x000f_Tracking_707) {
    DataValue val = createUnsignedByteValue(240, 0);
    maker.print0x000f(os, val, nullptr);
    EXPECT_NE(os.str().find("Tracking"), std::string::npos);
}

// Test: Unknown combination should output raw value
TEST_F(PanasonicMakerNoteTest_707, Print0x000f_UnknownCombination_707) {
    DataValue val = createUnsignedByteValue(99, 99);
    maker.print0x000f(os, val, nullptr);
    // Should output the raw value representation
    EXPECT_FALSE(os.str().empty());
}

// Test: Another unknown combination
TEST_F(PanasonicMakerNoteTest_707, Print0x000f_AnotherUnknownCombination_707) {
    DataValue val = createUnsignedByteValue(255, 255);
    maker.print0x000f(os, val, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test: l0=0, l1=0 is not a defined combination, should fall through to else
TEST_F(PanasonicMakerNoteTest_707, Print0x000f_ZeroZero_707) {
    DataValue val = createUnsignedByteValue(0, 0);
    maker.print0x000f(os, val, nullptr);
    // Should output raw value since (0,0) is not a recognized combination
    EXPECT_FALSE(os.str().empty());
    // Make sure it doesn't match any known string
    EXPECT_EQ(os.str().find("Spot"), std::string::npos);
    EXPECT_EQ(os.str().find("area"), std::string::npos);
    EXPECT_EQ(os.str().find("Face"), std::string::npos);
    EXPECT_EQ(os.str().find("Tracking"), std::string::npos);
}

// Test: Return value is the same ostream reference
TEST_F(PanasonicMakerNoteTest_707, Print0x000f_ReturnsOstream_707) {
    DataValue val = createUnsignedByteValue(0, 1);
    std::ostream& result = maker.print0x000f(os, val, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test: nullptr ExifData is handled (no crash)
TEST_F(PanasonicMakerNoteTest_707, Print0x000f_NullExifData_707) {
    DataValue val = createUnsignedByteValue(64, 0);
    EXPECT_NO_THROW(maker.print0x000f(os, val, nullptr));
    EXPECT_NE(os.str().find("Face Detect"), std::string::npos);
}

// Test: Boundary - l0=0, l1=1 specifically to verify exact match
TEST_F(PanasonicMakerNoteTest_707, Print0x000f_ExactMatch0_1_707) {
    DataValue val = createUnsignedByteValue(0, 1);
    maker.print0x000f(os, val, nullptr);
    // Should contain the spot mode text
    std::string result = os.str();
    EXPECT_NE(result.find("9 area"), std::string::npos);
}

// Test: l0=0, l1=2 is not defined - should output raw
TEST_F(PanasonicMakerNoteTest_707, Print0x000f_Undefined0_2_707) {
    DataValue val = createUnsignedByteValue(0, 2);
    maker.print0x000f(os, val, nullptr);
    std::string result = os.str();
    // Should not match any specific label
    EXPECT_EQ(result.find("Spot"), std::string::npos);
}
