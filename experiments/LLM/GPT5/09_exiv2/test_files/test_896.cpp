#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "olympusmn_int.cpp"  // Include the file with the class definition

using namespace Exiv2::Internal;

class OlympusMakerNoteTest : public ::testing::Test {
protected:
    OlympusMakerNote makerNote;
    std::ostringstream os;
    Value value;
    ExifData exifData;

    void SetUp() override {
        // Set up any required initialization
    }

    void TearDown() override {
        // Clean up if necessary
    }
};

TEST_F(OlympusMakerNoteTest, print0x0527_Off_896) {
    // Arrange
    value.setCount(3);
    value.setTypeId(signedShort);
    value.setToInt64(0, -2);  // First parameter is -2 for "Off"
    value.setToInt64(1, -2);  // Second parameter is -2
    value.setToInt64(2, 1);   // Third parameter is 1
    
    // Act
    makerNote.print0x0527(os, value, &exifData);

    // Assert
    EXPECT_EQ(os.str(), "Off");
}

TEST_F(OlympusMakerNoteTest, print0x0527_Low_896) {
    // Arrange
    value.setCount(3);
    value.setTypeId(signedShort);
    value.setToInt64(0, -1);  // First parameter is -1 for "Low"
    value.setToInt64(1, -2);  // Second parameter is -2
    value.setToInt64(2, 1);   // Third parameter is 1
    
    // Act
    makerNote.print0x0527(os, value, &exifData);

    // Assert
    EXPECT_EQ(os.str(), "Low");
}

TEST_F(OlympusMakerNoteTest, print0x0527_Standard_896) {
    // Arrange
    value.setCount(3);
    value.setTypeId(signedShort);
    value.setToInt64(0, 0);  // First parameter is 0 for "Standard"
    value.setToInt64(1, -2);  // Second parameter is -2
    value.setToInt64(2, 1);   // Third parameter is 1
    
    // Act
    makerNote.print0x0527(os, value, &exifData);

    // Assert
    EXPECT_EQ(os.str(), "Standard");
}

TEST_F(OlympusMakerNoteTest, print0x0527_High_896) {
    // Arrange
    value.setCount(3);
    value.setTypeId(signedShort);
    value.setToInt64(0, 1);  // First parameter is 1 for "High"
    value.setToInt64(1, -2);  // Second parameter is -2
    value.setToInt64(2, 1);   // Third parameter is 1
    
    // Act
    makerNote.print0x0527(os, value, &exifData);

    // Assert
    EXPECT_EQ(os.str(), "High");
}

TEST_F(OlympusMakerNoteTest, print0x0527_InvalidValue_896) {
    // Arrange
    value.setCount(3);
    value.setTypeId(signedShort);
    value.setToInt64(0, 99);  // Invalid value
    value.setToInt64(1, -2);  // Second parameter is -2
    value.setToInt64(2, 1);   // Third parameter is 1
    
    // Act
    makerNote.print0x0527(os, value, &exifData);

    // Assert
    EXPECT_EQ(os.str(), "99");
}

TEST_F(OlympusMakerNoteTest, print0x0527_InvalidCount_896) {
    // Arrange
    value.setCount(2);  // Invalid count (should be 3)
    value.setTypeId(signedShort);
    value.setToInt64(0, -2);  // First parameter is -2 for "Off"
    value.setToInt64(1, -2);  // Second parameter is -2
    
    // Act
    makerNote.print0x0527(os, value, &exifData);

    // Assert
    EXPECT_EQ(os.str(), "");  // Expect empty output due to invalid count
}

TEST_F(OlympusMakerNoteTest, print0x0527_InvalidTypeId_896) {
    // Arrange
    value.setCount(3);
    value.setTypeId(unsignedInt);  // Invalid type ID
    value.setToInt64(0, -2);  // First parameter is -2 for "Off"
    value.setToInt64(1, -2);  // Second parameter is -2
    value.setToInt64(2, 1);   // Third parameter is 1
    
    // Act
    makerNote.print0x0527(os, value, &exifData);

    // Assert
    EXPECT_EQ(os.str(), "");  // Expect empty output due to invalid type
}