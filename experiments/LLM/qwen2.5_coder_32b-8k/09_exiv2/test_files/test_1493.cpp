#include <gtest/gtest.h>

#include "makernote_int.hpp"

#include <gmock/gmock.h>



using namespace Exiv2::Internal;



class SigmaMnHeaderTest : public ::testing::Test {

protected:

    SigmaMnHeader header;

};



TEST_F(SigmaMnHeaderTest, SizeOfSignature_ReturnsCorrectSize_1493) {

    EXPECT_EQ(header.sizeOfSignature(), sizeof(signature1_));

}



TEST_F(SigmaMnHeaderTest, Read_ValidData_ReturnsTrue_1493) {

    byte data[] = {0x01, 0x02, 0x03};

    size_t dataSize = sizeof(data);

    ByteOrder byteOrder = littleEndian;

    EXPECT_TRUE(header.read(data, dataSize, byteOrder));

}



TEST_F(SigmaMnHeaderTest, Read_InvalidData_ReturnsFalse_1493) {

    byte data[] = {0x00, 0x00, 0x00};

    size_t dataSize = sizeof(data);

    ByteOrder byteOrder = littleEndian;

    EXPECT_FALSE(header.read(data, dataSize, byteOrder));

}



TEST_F(SigmaMnHeaderTest, Size_ReturnsNonZero_1493) {

    EXPECT_NE(header.size(), 0u);

}



TEST_F(SigmaMnHeaderTest, IfdOffset_ReturnsExpectedValue_1493) {

    EXPECT_EQ(header.ifdOffset(), 0u); // Assuming ifdOffset returns 0 by default

}



// Mock IoWrapper for testing write function

class MockIoWrapper : public IoWrapper {

public:

    MOCK_METHOD(size_t, write, (const byte* data, size_t size), (override));

};



TEST_F(SigmaMnHeaderTest, Write_ValidData_ReturnsSizeWritten_1493) {

    MockIoWrapper mockIoWrapper;

    ByteOrder byteOrder = littleEndian;



    const size_t expectedSize = 10; // Assuming write returns a non-zero value

    EXPECT_CALL(mockIoWrapper, write(::testing::_, ::testing::_))

        .WillOnce(::testing::Return(expectedSize));



    size_t result = header.write(mockIoWrapper, byteOrder);

    EXPECT_EQ(result, expectedSize);

}



TEST_F(SigmaMnHeaderTest, Write_InvalidData_ReturnsZero_1493) {

    MockIoWrapper mockIoWrapper;

    ByteOrder byteOrder = littleEndian;



    // Assuming write returns 0 when data is invalid

    EXPECT_CALL(mockIoWrapper, write(::testing::_, ::testing::_))

        .WillOnce(::testing::Return(0));



    size_t result = header.write(mockIoWrapper, byteOrder);

    EXPECT_EQ(result, 0u);

}
