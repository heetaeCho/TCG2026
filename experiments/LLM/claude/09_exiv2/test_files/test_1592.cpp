#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need access to the SonyMakerNote class from the internal namespace
// Since the class is defined in sonymn_int.cpp, we need to include the appropriate header
// or recreate the minimal interface for testing purposes.
// Based on the provided code, we'll include the internal header.
#include "sonymn_int.hpp"

namespace {

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_1592 : public ::testing::Test {
protected:
    SonyMakerNote sonyNote;
    std::ostringstream os;
};

// Test: When value count is not 2, should print raw value in parentheses
TEST_F(SonyMakerNoteTest_1592, PrintWBShiftABGM_WrongCount_SingleValue_1592) {
    Exiv2::ValueType<int32_t> value;
    value.value_.push_back(5);
    
    sonyNote.printWBShiftABGM(os, value, nullptr);
    EXPECT_EQ(os.str(), "(5)");
}

// Test: When value count is 0, should print raw value in parentheses
TEST_F(SonyMakerNoteTest_1592, PrintWBShiftABGM_EmptyValue_1592) {
    Exiv2::ValueType<int32_t> value;
    
    sonyNote.printWBShiftABGM(os, value, nullptr);
    EXPECT_EQ(os.str(), "()");
}

// Test: When value count is 3 (more than 2), should print raw value in parentheses
TEST_F(SonyMakerNoteTest_1592, PrintWBShiftABGM_ThreeValues_1592) {
    Exiv2::ValueType<int32_t> value;
    value.value_.push_back(1);
    value.value_.push_back(2);
    value.value_.push_back(3);
    
    sonyNote.printWBShiftABGM(os, value, nullptr);
    EXPECT_EQ(os.str(), "(1 2 3)");
}

// Test: When type is not signedLong, should print raw value in parentheses
TEST_F(SonyMakerNoteTest_1592, PrintWBShiftABGM_WrongType_1592) {
    Exiv2::ValueType<uint32_t> value;
    value.value_.push_back(5);
    value.value_.push_back(3);
    
    sonyNote.printWBShiftABGM(os, value, nullptr);
    EXPECT_EQ(os.str(), "(5 3)");
}

// Test: Both values are zero
TEST_F(SonyMakerNoteTest_1592, PrintWBShiftABGM_BothZero_1592) {
    Exiv2::ValueType<int32_t> value;
    value.value_.push_back(0);
    value.value_.push_back(0);
    
    sonyNote.printWBShiftABGM(os, value, nullptr);
    EXPECT_EQ(os.str(), "A/B: 0, G/M: 0");
}

// Test: v0 negative (A direction), v1 zero
TEST_F(SonyMakerNoteTest_1592, PrintWBShiftABGM_NegativeV0_ZeroV1_1592) {
    Exiv2::ValueType<int32_t> value;
    value.value_.push_back(-3);
    value.value_.push_back(0);
    
    sonyNote.printWBShiftABGM(os, value, nullptr);
    EXPECT_EQ(os.str(), "A/B: A3, G/M: 0");
}

// Test: v0 positive (B direction), v1 zero
TEST_F(SonyMakerNoteTest_1592, PrintWBShiftABGM_PositiveV0_ZeroV1_1592) {
    Exiv2::ValueType<int32_t> value;
    value.value_.push_back(5);
    value.value_.push_back(0);
    
    sonyNote.printWBShiftABGM(os, value, nullptr);
    EXPECT_EQ(os.str(), "A/B: B5, G/M: 0");
}

// Test: v0 zero, v1 negative (G direction)
TEST_F(SonyMakerNoteTest_1592, PrintWBShiftABGM_ZeroV0_NegativeV1_1592) {
    Exiv2::ValueType<int32_t> value;
    value.value_.push_back(0);
    value.value_.push_back(-2);
    
    sonyNote.printWBShiftABGM(os, value, nullptr);
    EXPECT_EQ(os.str(), "A/B: 0, G/M: G2");
}

// Test: v0 zero, v1 positive (M direction)
TEST_F(SonyMakerNoteTest_1592, PrintWBShiftABGM_ZeroV0_PositiveV1_1592) {
    Exiv2::ValueType<int32_t> value;
    value.value_.push_back(0);
    value.value_.push_back(4);
    
    sonyNote.printWBShiftABGM(os, value, nullptr);
    EXPECT_EQ(os.str(), "A/B: 0, G/M: M4");
}

// Test: v0 negative, v1 negative (A and G)
TEST_F(SonyMakerNoteTest_1592, PrintWBShiftABGM_NegativeV0_NegativeV1_1592) {
    Exiv2::ValueType<int32_t> value;
    value.value_.push_back(-1);
    value.value_.push_back(-7);
    
    sonyNote.printWBShiftABGM(os, value, nullptr);
    EXPECT_EQ(os.str(), "A/B: A1, G/M: G7");
}

// Test: v0 positive, v1 positive (B and M)
TEST_F(SonyMakerNoteTest_1592, PrintWBShiftABGM_PositiveV0_PositiveV1_1592) {
    Exiv2::ValueType<int32_t> value;
    value.value_.push_back(2);
    value.value_.push_back(3);
    
    sonyNote.printWBShiftABGM(os, value, nullptr);
    EXPECT_EQ(os.str(), "A/B: B2, G/M: M3");
}

// Test: v0 negative, v1 positive (A and M)
TEST_F(SonyMakerNoteTest_1592, PrintWBShiftABGM_NegativeV0_PositiveV1_1592) {
    Exiv2::ValueType<int32_t> value;
    value.value_.push_back(-4);
    value.value_.push_back(6);
    
    sonyNote.printWBShiftABGM(os, value, nullptr);
    EXPECT_EQ(os.str(), "A/B: A4, G/M: M6");
}

// Test: v0 positive, v1 negative (B and G)
TEST_F(SonyMakerNoteTest_1592, PrintWBShiftABGM_PositiveV0_NegativeV1_1592) {
    Exiv2::ValueType<int32_t> value;
    value.value_.push_back(8);
    value.value_.push_back(-9);
    
    sonyNote.printWBShiftABGM(os, value, nullptr);
    EXPECT_EQ(os.str(), "A/B: B8, G/M: G9");
}

// Test: Large values
TEST_F(SonyMakerNoteTest_1592, PrintWBShiftABGM_LargeValues_1592) {
    Exiv2::ValueType<int32_t> value;
    value.value_.push_back(-100);
    value.value_.push_back(200);
    
    sonyNote.printWBShiftABGM(os, value, nullptr);
    EXPECT_EQ(os.str(), "A/B: A100, G/M: M200");
}

// Test: v0 = 1, v1 = 1 (minimum positive values)
TEST_F(SonyMakerNoteTest_1592, PrintWBShiftABGM_MinimumPositive_1592) {
    Exiv2::ValueType<int32_t> value;
    value.value_.push_back(1);
    value.value_.push_back(1);
    
    sonyNote.printWBShiftABGM(os, value, nullptr);
    EXPECT_EQ(os.str(), "A/B: B1, G/M: M1");
}

// Test: v0 = -1, v1 = -1 (minimum negative values)
TEST_F(SonyMakerNoteTest_1592, PrintWBShiftABGM_MinimumNegative_1592) {
    Exiv2::ValueType<int32_t> value;
    value.value_.push_back(-1);
    value.value_.push_back(-1);
    
    sonyNote.printWBShiftABGM(os, value, nullptr);
    EXPECT_EQ(os.str(), "A/B: A1, G/M: G1");
}

// Test: Return value is reference to same stream
TEST_F(SonyMakerNoteTest_1592, PrintWBShiftABGM_ReturnsSameStream_1592) {
    Exiv2::ValueType<int32_t> value;
    value.value_.push_back(0);
    value.value_.push_back(0);
    
    std::ostream& result = sonyNote.printWBShiftABGM(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test: Return value is reference to same stream for error case
TEST_F(SonyMakerNoteTest_1592, PrintWBShiftABGM_ReturnsSameStreamOnError_1592) {
    Exiv2::ValueType<int32_t> value;
    value.value_.push_back(5);
    
    std::ostream& result = sonyNote.printWBShiftABGM(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test: ExifData pointer is nullptr (should work fine as it's unused)
TEST_F(SonyMakerNoteTest_1592, PrintWBShiftABGM_NullExifData_1592) {
    Exiv2::ValueType<int32_t> value;
    value.value_.push_back(3);
    value.value_.push_back(-5);
    
    sonyNote.printWBShiftABGM(os, value, nullptr);
    EXPECT_EQ(os.str(), "A/B: B3, G/M: G5");
}

} // namespace
