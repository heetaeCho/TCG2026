#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>

// Include the internal header for Nikon maker note
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon1MakerNoteTest_455 : public ::testing::Test {
protected:
    Nikon1MakerNote maker_;
    std::ostringstream os_;
};

// Test with a single value (count == 1) and valid focus area index 0
TEST_F(Nikon1MakerNoteTest_455, Print0x0088_SingleValue_ValidFocusArea0_455) {
    UShortValue value;
    value.read(reinterpret_cast<const byte*>("\x00\x00"), 2, littleEndian);
    
    maker_.print0x0088(os_, value, nullptr);
    std::string result = os_.str();
    // Should print the focus area name and then "(value)" since count < 3
    EXPECT_FALSE(result.empty());
    // Since count == 1, the else branch at the end fires: "(" << value << ")"
    EXPECT_NE(result.find("("), std::string::npos);
}

// Test with a single value and out-of-range focus area
TEST_F(Nikon1MakerNoteTest_455, Print0x0088_SingleValue_InvalidFocusArea_455) {
    UShortValue value;
    uint16_t val = 255;
    value.read(reinterpret_cast<const byte*>(&val), 2, littleEndian);
    
    maker_.print0x0088(os_, value, nullptr);
    std::string result = os_.str();
    EXPECT_NE(result.find("Invalid value"), std::string::npos);
}

// Test with count >= 2, focus point <= 4
TEST_F(Nikon1MakerNoteTest_455, Print0x0088_TwoValues_ValidFocusPoint_455) {
    UShortValue value;
    uint16_t vals[2] = {0, 2};
    value.read(reinterpret_cast<const byte*>(vals), 4, littleEndian);
    
    maker_.print0x0088(os_, value, nullptr);
    std::string result = os_.str();
    // Should contain "; " separator for the second value
    EXPECT_NE(result.find("; "), std::string::npos);
}

// Test with count >= 2, focus point > 4
TEST_F(Nikon1MakerNoteTest_455, Print0x0088_TwoValues_FocusPointAbove4_455) {
    UShortValue value;
    uint16_t vals[2] = {0, 6};
    value.read(reinterpret_cast<const byte*>(vals), 4, littleEndian);
    
    maker_.print0x0088(os_, value, nullptr);
    std::string result = os_.str();
    EXPECT_NE(result.find("; "), std::string::npos);
}

// Test with count >= 4, non-zero focus points used (bitmask processing)
TEST_F(Nikon1MakerNoteTest_455, Print0x0088_FourValues_FocusPointsUsed_455) {
    UShortValue value;
    uint16_t vals[4] = {0, 0, 3, 1}; // focusPointsUsed1=3 (bits 0,1), focusPointsUsed2=1 (bit 0)
    value.read(reinterpret_cast<const byte*>(vals), 8, littleEndian);
    
    maker_.print0x0088(os_, value, nullptr);
    std::string result = os_.str();
    // Should contain brackets for focus points used
    EXPECT_NE(result.find("["), std::string::npos);
    EXPECT_NE(result.find("]"), std::string::npos);
}

// Test with count >= 4 but focusPointsUsed1 == 0 (no bracket output)
TEST_F(Nikon1MakerNoteTest_455, Print0x0088_FourValues_ZeroFocusPointsUsed1_455) {
    UShortValue value;
    uint16_t vals[4] = {0, 0, 0, 1};
    value.read(reinterpret_cast<const byte*>(vals), 8, littleEndian);
    
    maker_.print0x0088(os_, value, nullptr);
    std::string result = os_.str();
    // focusPointsUsed1 == 0, so the bracket block should not appear
    EXPECT_EQ(result.find("["), std::string::npos);
}

// Test with count >= 4 but focusPointsUsed2 == 0 (no bracket output)
TEST_F(Nikon1MakerNoteTest_455, Print0x0088_FourValues_ZeroFocusPointsUsed2_455) {
    UShortValue value;
    uint16_t vals[4] = {0, 0, 5, 0};
    value.read(reinterpret_cast<const byte*>(vals), 8, littleEndian);
    
    maker_.print0x0088(os_, value, nullptr);
    std::string result = os_.str();
    EXPECT_EQ(result.find("["), std::string::npos);
}

// Test with count >= 4, all bitmask bits set for focusPointsUsed1
TEST_F(Nikon1MakerNoteTest_455, Print0x0088_FourValues_AllBitsSet_455) {
    UShortValue value;
    uint16_t vals[4] = {0, 0, 0xFF, 0x07}; // all bits in used1 and bits 0-2 in used2
    value.read(reinterpret_cast<const byte*>(vals), 8, littleEndian);
    
    maker_.print0x0088(os_, value, nullptr);
    std::string result = os_.str();
    EXPECT_NE(result.find("["), std::string::npos);
    EXPECT_NE(result.find("]"), std::string::npos);
}

// Test with empty value (count == 0)
TEST_F(Nikon1MakerNoteTest_455, Print0x0088_EmptyValue_455) {
    UShortValue value;
    // Don't read any data, count should be 0
    maker_.print0x0088(os_, value, nullptr);
    std::string result = os_.str();
    // count < 1 means nothing from first block, count < 3 means "(value)" at end
    EXPECT_NE(result.find("("), std::string::npos);
}

// Test with count == 3 (exactly 3, focusPointsUsed2 would need index 3 which doesn't exist)
TEST_F(Nikon1MakerNoteTest_455, Print0x0088_ThreeValues_455) {
    UShortValue value;
    uint16_t vals[3] = {0, 1, 5};
    value.read(reinterpret_cast<const byte*>(vals), 6, littleEndian);
    
    maker_.print0x0088(os_, value, nullptr);
    std::string result = os_.str();
    EXPECT_FALSE(result.empty());
}

// Test return value is the same ostream reference
TEST_F(Nikon1MakerNoteTest_455, Print0x0088_ReturnsOstream_455) {
    UShortValue value;
    uint16_t vals[4] = {0, 0, 1, 1};
    value.read(reinterpret_cast<const byte*>(vals), 8, littleEndian);
    
    std::ostream& returned = maker_.print0x0088(os_, value, nullptr);
    EXPECT_EQ(&returned, &os_);
}

// Test focusPoint exactly equal to 4 (boundary for <= 4 check)
TEST_F(Nikon1MakerNoteTest_455, Print0x0088_FocusPointExactly4_455) {
    UShortValue value;
    uint16_t vals[4] = {0, 4, 1, 1};
    value.read(reinterpret_cast<const byte*>(vals), 8, littleEndian);
    
    maker_.print0x0088(os_, value, nullptr);
    std::string result = os_.str();
    // focusPoint 4 is <= 4, so should use nikonFocuspoints[4] directly
    EXPECT_NE(result.find("; "), std::string::npos);
}

// Test focusPoint exactly equal to 5 (boundary for > 4 check)
TEST_F(Nikon1MakerNoteTest_455, Print0x0088_FocusPointExactly5_455) {
    UShortValue value;
    uint16_t vals[4] = {0, 5, 1, 1};
    value.read(reinterpret_cast<const byte*>(vals), 8, littleEndian);
    
    maker_.print0x0088(os_, value, nullptr);
    std::string result = os_.str();
    // focusPoint 5 is > 4, so it goes to else branch
    EXPECT_NE(result.find("; "), std::string::npos);
}
