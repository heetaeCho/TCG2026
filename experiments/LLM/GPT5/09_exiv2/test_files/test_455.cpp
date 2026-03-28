#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <cstdint>
#include "nikonmn_int.hpp" // Adjust this path to the actual header file

using namespace Exiv2::Internal;

// Mock Value class for testing
class MockValue : public Value {
public:
    MOCK_METHOD(int, count, (), (const, override));
    MOCK_METHOD(uint32_t, toUint32, (size_t index), (const, override));
};

// Test fixture for Nikon1MakerNote class
class Nikon1MakerNoteTest : public ::testing::Test {
protected:
    Nikon1MakerNote makerNote;
    MockValue mockValue;
    std::ostringstream os;
    const ExifData* exifData = nullptr; // Assuming the exifData is nullptr for simplicity
};

// Test normal case with valid focus area and focus point
TEST_F(Nikon1MakerNoteTest, PrintFocusAreaAndPointValid_455) {
    // Mock the value to return 2 valid focus area and point
    EXPECT_CALL(mockValue, count()).WillOnce(testing::Return(2));
    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(testing::Return(1)); // Valid focus area
    EXPECT_CALL(mockValue, toUint32(1)).WillOnce(testing::Return(2)); // Valid focus point

    makerNote.print0x0088(os, mockValue, exifData);
    
    // Verify the printed output
    EXPECT_EQ(os.str(), "Valid FocusArea; Valid FocusPoint");
}

// Test invalid focus area
TEST_F(Nikon1MakerNoteTest, PrintFocusAreaInvalid_456) {
    // Mock the value to return 1 valid focus area and invalid focus point
    EXPECT_CALL(mockValue, count()).WillOnce(testing::Return(1));
    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(testing::Return(100)); // Invalid focus area

    makerNote.print0x0088(os, mockValue, exifData);

    // Verify the printed output
    EXPECT_EQ(os.str(), "Invalid value");
}

// Test invalid focus point (larger than the size of known focus points)
TEST_F(Nikon1MakerNoteTest, PrintFocusPointInvalid_457) {
    // Mock the value to return valid focus area and invalid focus point
    EXPECT_CALL(mockValue, count()).WillOnce(testing::Return(2));
    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(testing::Return(1));  // Valid focus area
    EXPECT_CALL(mockValue, toUint32(1)).WillOnce(testing::Return(50)); // Invalid focus point

    makerNote.print0x0088(os, mockValue, exifData);

    // Verify the printed output
    EXPECT_EQ(os.str(), "Valid FocusArea; (Invalid FocusPoint)");
}

// Test with 3 values, testing focus points used
TEST_F(Nikon1MakerNoteTest, PrintFocusPointsUsed_458) {
    // Mock the value to return 4 valid focus points used
    EXPECT_CALL(mockValue, count()).WillOnce(testing::Return(4));
    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(testing::Return(1)); // Focus area
    EXPECT_CALL(mockValue, toUint32(1)).WillOnce(testing::Return(2)); // Focus point
    EXPECT_CALL(mockValue, toUint32(2)).WillOnce(testing::Return(255)); // Focus points used 1
    EXPECT_CALL(mockValue, toUint32(3)).WillOnce(testing::Return(255)); // Focus points used 2

    makerNote.print0x0088(os, mockValue, exifData);

    // Verify the printed output
    EXPECT_EQ(os.str(), "Valid FocusArea; Valid FocusPoint; [Valid FocusPoint Valid FocusPoint Valid FocusPoint Valid FocusPoint]");
}

// Test with less than 3 values (boundary condition)
TEST_F(Nikon1MakerNoteTest, PrintLessThan3Values_459) {
    // Mock the value to return 1 value
    EXPECT_CALL(mockValue, count()).WillOnce(testing::Return(1));
    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(testing::Return(1)); // Valid focus area

    makerNote.print0x0088(os, mockValue, exifData);

    // Verify the printed output
    EXPECT_EQ(os.str(), "Valid FocusArea");
}

// Test edge case with focus points used but no valid values
TEST_F(Nikon1MakerNoteTest, PrintInvalidFocusPointsUsed_460) {
    // Mock the value to return 4 valid but unrecognized focus points used
    EXPECT_CALL(mockValue, count()).WillOnce(testing::Return(4));
    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(testing::Return(1));  // Focus area
    EXPECT_CALL(mockValue, toUint32(1)).WillOnce(testing::Return(3));  // Focus point
    EXPECT_CALL(mockValue, toUint32(2)).WillOnce(testing::Return(0));  // Invalid focus points used 1
    EXPECT_CALL(mockValue, toUint32(3)).WillOnce(testing::Return(0));  // Invalid focus points used 2

    makerNote.print0x0088(os, mockValue, exifData);

    // Verify the printed output
    EXPECT_EQ(os.str(), "(Invalid FocusPoint)");
}