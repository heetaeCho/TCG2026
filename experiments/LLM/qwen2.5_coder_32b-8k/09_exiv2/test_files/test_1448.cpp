#include <gtest/gtest.h>

#include "makernote_int.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2::Internal;

using namespace testing;



class OMSystemMnHeaderTest_1448 : public Test {

protected:

    OMSystemMnHeader header;

};



TEST_F(OMSystemMnHeaderTest_1448, SizeReturnsZeroInitially_1448) {

    EXPECT_EQ(header.size(), 0);

}



TEST_F(OMSystemMnHeaderTest_1448, ReadWithNullPointerThrowsException_1448) {

    const byte* pData = nullptr;

    size_t size = 10;

    ByteOrder byteOrder = littleEndian;



    EXPECT_THROW(header.read(pData, size, byteOrder), std::exception);

}



TEST_F(OMSystemMnHeaderTest_1448, ReadWithZeroSizeDoesNotThrowException_1448) {

    const byte* pData = nullptr;

    size_t size = 0;

    ByteOrder byteOrder = littleEndian;



    EXPECT_NO_THROW(header.read(pData, size, byteOrder));

}



TEST_F(OMSystemMnHeaderTest_1448, WriteWithNullPointerThrowsException_1448) {

    IoWrapper ioWrapper(nullptr);

    ByteOrder byteOrder = littleEndian;



    EXPECT_THROW(header.write(ioWrapper, byteOrder), std::exception);

}



TEST_F(OMSystemMnHeaderTest_1448, IfdOffsetReturnsZeroInitially_1448) {

    EXPECT_EQ(header.ifdOffset(), 0);

}



TEST_F(OMSystemMnHeaderTest_1448, BaseOffsetWithZeroMnOffsetReturnsZero_1448) {

    size_t mnOffset = 0;

    EXPECT_EQ(header.baseOffset(mnOffset), 0);

}



TEST_F(OMSystemMnHeaderTest_1448, SizeOfSignatureIsPositive_1448) {

    EXPECT_GT(OMSystemMnHeader::sizeOfSignature(), 0);

}
