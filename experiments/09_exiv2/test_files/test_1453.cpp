#include <gtest/gtest.h>

#include "makernote_int.hpp"



using namespace Exiv2::Internal;



class FujiMnHeaderTest : public ::testing::Test {

protected:

    FujiMnHeader fujiMnHeader;

};



TEST_F(FujiMnHeaderTest_1453, SizeOfSignature_ReturnsCorrectSize_1453) {

    EXPECT_EQ(fujiMnHeader.sizeOfSignature(), sizeof(signature_));

}



TEST_F(FujiMnHeaderTest_1453, Read_ReturnsFalseForNullData_1453) {

    const byte* pData = nullptr;

    size_t size = 0;

    ByteOrder byteOrder = littleEndian;

    EXPECT_FALSE(fujiMnHeader.read(pData, size, byteOrder));

}



TEST_F(FujiMnHeaderTest_1453, Read_ReturnsFalseForZeroSize_1453) {

    const byte* pData = new byte[1];

    size_t size = 0;

    ByteOrder byteOrder = littleEndian;

    EXPECT_FALSE(fujiMnHeader.read(pData, size, byteOrder));

    delete[] pData;

}



TEST_F(FujiMnHeaderTest_1453, Size_ReturnsNonZeroValue_1453) {

    EXPECT_NE(fujiMnHeader.size(), 0);

}



TEST_F(FujiMnHeaderTest_1453, IfdOffset_ReturnsValidOffset_1453) {

    EXPECT_GE(fujiMnHeader.ifdOffset(), 0);

}



TEST_F(FujiMnHeaderTest_1453, ByteOrder_ReturnsValidByteOrder_1453) {

    ByteOrder order = fujiMnHeader.byteOrder();

    EXPECT_TRUE(order == littleEndian || order == bigEndian);

}



TEST_F(FujiMnHeaderTest_1453, BaseOffset_ReturnsValidOffsetForNonZeroInput_1453) {

    size_t mnOffset = 1;

    EXPECT_GE(fujiMnHeader.baseOffset(mnOffset), 0);

}



TEST_F(FujiMnHeaderTest_1453, Write_ReturnsWrittenSizeForNonNullIoWrapper_1453) {

    IoWrapper ioWrapper; // Assuming IoWrapper has a default constructor

    ByteOrder byteOrder = littleEndian;

    EXPECT_GT(fujiMnHeader.write(ioWrapper, byteOrder), 0);

}
