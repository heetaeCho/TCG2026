#include <gtest/gtest.h>

#include "XMPMeta-Parse.cpp"  // Assuming the function is in this file



// Test fixture for CountUTF8 tests

class CountUTF8Test_1971 : public ::testing::Test {

protected:

    XMP_Uns8 buffer[10];



    void SetUp() override {

        memset(buffer, 0, sizeof(buffer));

    }

};



TEST_F(CountUTF8Test_1971, SingleByteCharacter_1971) {

    // Arrange

    buffer[0] = 0x41; // ASCII 'A'



    // Act & Assert

    EXPECT_EQ(CountUTF8(buffer, buffer + 1), 0);

}



TEST_F(CountUTF8Test_1971, ValidTwoByteCharacter_1971) {

    // Arrange

    buffer[0] = 0xC2; // Two-byte UTF-8 start

    buffer[1] = 0x81; // Second byte



    // Act & Assert

    EXPECT_EQ(CountUTF8(buffer, buffer + 2), 2);

}



TEST_F(CountUTF8Test_1971, ValidThreeByteCharacter_1971) {

    // Arrange

    buffer[0] = 0xE1; // Three-byte UTF-8 start

    buffer[1] = 0x81;

    buffer[2] = 0x81;



    // Act & Assert

    EXPECT_EQ(CountUTF8(buffer, buffer + 3), 3);

}



TEST_F(CountUTF8Test_1971, ValidFourByteCharacter_1971) {

    // Arrange

    buffer[0] = 0xF1; // Four-byte UTF-8 start

    buffer[1] = 0x81;

    buffer[2] = 0x81;

    buffer[3] = 0x81;



    // Act & Assert

    EXPECT_EQ(CountUTF8(buffer, buffer + 4), 4);

}



TEST_F(CountUTF8Test_1971, InvalidTwoByteCharacter_1971) {

    // Arrange

    buffer[0] = 0xC2; // Two-byte UTF-8 start

    buffer[1] = 0x7F; // Invalid second byte



    // Act & Assert

    EXPECT_EQ(CountUTF8(buffer, buffer + 2), 0);

}



TEST_F(CountUTF8Test_1971, IncompleteTwoByteCharacter_1971) {

    // Arrange

    buffer[0] = 0xC2; // Two-byte UTF-8 start



    // Act & Assert

    EXPECT_EQ(CountUTF8(buffer, buffer + 1), -2);

}



TEST_F(CountUTF8Test_1971, BufferEndsAtFirstByte_1971) {

    // Arrange

    buffer[0] = 0x41; // ASCII 'A'



    // Act & Assert

    EXPECT_EQ(CountUTF8(buffer, buffer), 0);

}



TEST_F(CountUTF8Test_1971, BufferEndsAtSecondByteOfTwoByteChar_1971) {

    // Arrange

    buffer[0] = 0xC2; // Two-byte UTF-8 start

    buffer[1] = 0x81;



    // Act & Assert

    EXPECT_EQ(CountUTF8(buffer, buffer + 1), -2);

}



TEST_F(CountUTF8Test_1971, BufferEndsAtThirdByteOfThreeByteChar_1971) {

    // Arrange

    buffer[0] = 0xE1; // Three-byte UTF-8 start

    buffer[1] = 0x81;

    buffer[2] = 0x81;



    // Act & Assert

    EXPECT_EQ(CountUTF8(buffer, buffer + 2), -3);

}



TEST_F(CountUTF8Test_1971, BufferEndsAtFourthByteOfFourByteChar_1971) {

    // Arrange

    buffer[0] = 0xF1; // Four-byte UTF-8 start

    buffer[1] = 0x81;

    buffer[2] = 0x81;

    buffer[3] = 0x81;



    // Act & Assert

    EXPECT_EQ(CountUTF8(buffer, buffer + 3), -4);

}



TEST_F(CountUTF8Test_1971, InvalidStartByte_1971) {

    // Arrange

    buffer[0] = 0x7F; // Invalid start byte



    // Act & Assert

    EXPECT_EQ(CountUTF8(buffer, buffer + 1), 0);

}



TEST_F(CountUTF8Test_1971, BufferStartsAtSecondByteOfTwoByteChar_1971) {

    // Arrange

    buffer[0] = 0x81; // Invalid start byte (second byte of a two-byte char)



    // Act & Assert

    EXPECT_EQ(CountUTF8(buffer, buffer + 1), 0);

}
