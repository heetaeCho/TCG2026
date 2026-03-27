#include <gtest/gtest.h>

#include "exiv2/value.hpp"



// Mock class to simulate external collaborators if needed

class MockHandler {

public:

    MOCK_METHOD(void, handleData, (const byte*, size_t), ());

};



// Test fixture for testing the toData function

class ToDataTest_142 : public ::testing::Test {

protected:

    MockHandler mock_handler;

};



// Normal operation test

TEST_F(ToDataTest_142, PutNormalValue_142) {

    int16_t value = 12345;

    byte buffer[sizeof(int16_t)];

    ByteOrder byteOrder = littleEndian; // or bigEndian as appropriate



    size_t bytesWritten = Exiv2::toData(buffer, value, byteOrder);



    EXPECT_EQ(bytesWritten, sizeof(int16_t));

}



// Boundary condition test with minimum value

TEST_F(ToDataTest_142, PutMinValue_142) {

    int16_t minValue = std::numeric_limits<int16_t>::min();

    byte buffer[sizeof(int16_t)];

    ByteOrder byteOrder = littleEndian; // or bigEndian as appropriate



    size_t bytesWritten = Exiv2::toData(buffer, minValue, byteOrder);



    EXPECT_EQ(bytesWritten, sizeof(int16_t));

}



// Boundary condition test with maximum value

TEST_F(ToDataTest_142, PutMaxValue_142) {

    int16_t maxValue = std::numeric_limits<int16_t>::max();

    byte buffer[sizeof(int16_t)];

    ByteOrder byteOrder = littleEndian; // or bigEndian as appropriate



    size_t bytesWritten = Exiv2::toData(buffer, maxValue, byteOrder);



    EXPECT_EQ(bytesWritten, sizeof(int16_t));

}



// Test for buffer overflow scenario (not possible with this function signature, but good practice)

TEST_F(ToDataTest_142, PutInsufficientBuffer_142) {

    int16_t value = 123;

    byte smallBuffer[sizeof(int16_t) - 1];

    ByteOrder byteOrder = littleEndian; // or bigEndian as appropriate



    size_t bytesWritten = Exiv2::toData(smallBuffer, value, byteOrder);



    EXPECT_EQ(bytesWritten, sizeof(int16_t)); // should still return expected size, but behavior of buffer is undefined

}



// Test for different ByteOrder (littleEndian)

TEST_F(ToDataTest_142, PutLittleEndian_142) {

    int16_t value = 0x1234;

    byte buffer[sizeof(int16_t)];

    ByteOrder byteOrder = littleEndian;



    size_t bytesWritten = Exiv2::toData(buffer, value, byteOrder);



    EXPECT_EQ(bytesWritten, sizeof(int16_t));

    EXPECT_EQ(buffer[0], 0x34); // Little Endian: least significant byte first

    EXPECT_EQ(buffer[1], 0x12);

}



// Test for different ByteOrder (bigEndian)

TEST_F(ToDataTest_142, PutBigEndian_142) {

    int16_t value = 0x1234;

    byte buffer[sizeof(int16_t)];

    ByteOrder byteOrder = bigEndian;



    size_t bytesWritten = Exiv2::toData(buffer, value, byteOrder);



    EXPECT_EQ(bytesWritten, sizeof(int16_t));

    EXPECT_EQ(buffer[0], 0x12); // Big Endian: most significant byte first

    EXPECT_EQ(buffer[1], 0x34);

}
