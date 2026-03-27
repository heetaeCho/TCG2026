#include <gtest/gtest.h>

#include "makernote_int.hpp"



using namespace Exiv2::Internal;



class Olympus2MnHeaderTest_1441 : public ::testing::Test {

protected:

    Olympus2MnHeader header;

};



TEST_F(Olympus2MnHeaderTest_1441, SizeOfSignature_ReturnsCorrectSize_1441) {

    EXPECT_EQ(header.sizeOfSignature(), sizeof(signature_));

}



TEST_F(Olympus2MnHeaderTest_1441, Read_ValidData_ReturnsTrue_1441) {

    byte data[] = {0x01, 0x02, 0x03};

    size_t dataSize = sizeof(data);

    ByteOrder byteOrder = littleEndian;

    EXPECT_TRUE(header.read(data, dataSize, byteOrder));

}



TEST_F(Olympus2MnHeaderTest_1441, Read_NullData_ReturnsFalse_1441) {

    size_t dataSize = 10;

    ByteOrder byteOrder = littleEndian;

    EXPECT_FALSE(header.read(nullptr, dataSize, byteOrder));

}



TEST_F(Olympus2MnHeaderTest_1441, Size_ReturnsNonZeroValue_1441) {

    EXPECT_NE(header.size(), 0);

}



TEST_F(Olympus2MnHeaderTest_1441, IfdOffset_ReturnsNonNegativeValue_1441) {

    EXPECT_GE(header.ifdOffset(), 0);

}



TEST_F(Olympus2MnHeaderTest_1441, BaseOffset_ValidOffset_ReturnsCorrectValue_1441) {

    size_t mnOffset = 10;

    EXPECT_EQ(header.baseOffset(mnOffset), header.ifdOffset() + mnOffset);

}



TEST_F(Olympus2MnHeaderTest_1441, Write_ValidIoWrapper_ReturnsNonZeroValue_1441) {

    IoWrapper ioWrapper;

    ByteOrder byteOrder = littleEndian;

    EXPECT_NE(header.write(ioWrapper, byteOrder), 0);

}
