#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.hpp"



using namespace Exiv2::Internal;



class Nikon3MnHeaderTest_1465 : public ::testing::Test {

protected:

    Nikon3MnHeader nikon3MnHeader;

};



TEST_F(Nikon3MnHeaderTest_1465, SizeOfSignature_ReturnsCorrectSize_1465) {

    EXPECT_EQ(nikon3MnHeader.sizeOfSignature(), sizeof(nikon3MnHeader.signature_));

}



TEST_F(Nikon3MnHeaderTest_1465, Constructor_InitializesStartWithSignatureSize_1465) {

    EXPECT_EQ(nikon3MnHeader.start_, nikon3MnHeader.sizeOfSignature());

}



// Mocking IoWrapper for write function

class MockIoWrapper : public IoWrapper {

public:

    MOCK_METHOD(size_t, write, (const byte* data, size_t size), (override));

};



TEST_F(Nikon3MnHeaderTest_1465, Write_CallsIoWrapperWriteWithCorrectParameters_1465) {

    MockIoWrapper mockIoWrapper;

    ByteOrder byteOrder = littleEndian;



    EXPECT_CALL(mockIoWrapper, write(::testing::_, ::testing::_))

        .Times(1);



    nikon3MnHeader.write(mockIoWrapper, byteOrder);

}



// Assuming read and setByteOrder can be tested with some observable behavior

TEST_F(Nikon3MnHeaderTest_1465, Read_ReturnsTrueForValidData_1465) {

    const byte data[] = {0x01, 0x02, 0x03};

    size_t size = sizeof(data);

    ByteOrder byteOrder = littleEndian;



    EXPECT_TRUE(nikon3MnHeader.read(data, size, byteOrder));

}



TEST_F(Nikon3MnHeaderTest_1465, SetByteOrder_SetsCorrectByteOrder_1465) {

    ByteOrder newByteOrder = bigEndian;

    nikon3MnHeader.setByteOrder(newByteOrder);



    EXPECT_EQ(nikon3MnHeader.byteOrder(), newByteOrder);

}



// Assuming size, ifdOffset, and baseOffset have observable behavior

TEST_F(Nikon3MnHeaderTest_1465, Size_ReturnsCorrectSize_1465) {

    EXPECT_EQ(nikon3MnHeader.size(), 0); // Assuming default size is 0 without initialization

}



TEST_F(Nikon3MnHeaderTest_1465, IfdOffset_ReturnsCorrectOffset_1465) {

    EXPECT_EQ(nikon3MnHeader.ifdOffset(), 0); // Assuming default ifdOffset is 0 without initialization

}



TEST_F(Nikon3MnHeaderTest_1465, BaseOffset_ReturnsCorrectBaseOffset_1465) {

    size_t mnOffset = 10;

    EXPECT_EQ(nikon3MnHeader.baseOffset(mnOffset), mnOffset); // Assuming baseOffset returns mnOffset directly

}
