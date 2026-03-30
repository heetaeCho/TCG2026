#include <gtest/gtest.h>

#include "makernote_int.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2::Internal;



class Nikon2MnHeaderTest_2188 : public ::testing::Test {

protected:

    Nikon2MnHeader nikon2MnHeader;

};



TEST_F(Nikon2MnHeaderTest_2188, ReadValidData_2188) {

    byte data[] = {0x4E, 0x6B, 0x01, 0x00};

    size_t size = sizeof(data);

    ByteOrder byteOrder = littleEndian;

    EXPECT_TRUE(nikon2MnHeader.read(data, size, byteOrder));

}



TEST_F(Nikon2MnHeaderTest_2188, ReadInvalidData_2188) {

    byte data[] = {0x00, 0x00, 0x00, 0x00};

    size_t size = sizeof(data);

    ByteOrder byteOrder = littleEndian;

    EXPECT_FALSE(nikon2MnHeader.read(data, size, byteOrder));

}



TEST_F(Nikon2MnHeaderTest_2188, ReadInsufficientData_2188) {

    byte data[] = {0x4E, 0x6B};

    size_t size = sizeof(data);

    ByteOrder byteOrder = littleEndian;

    EXPECT_FALSE(nikon2MnHeader.read(data, size, byteOrder));

}



TEST_F(Nikon2MnHeaderTest_2188, SizeOfSignature_2188) {

    EXPECT_EQ(Nikon2MnHeader::sizeOfSignature(), 4);

}



TEST_F(Nikon2MnHeaderTest_2188, SetByteOrder_2188) {

    ByteOrder byteOrder = littleEndian;

    nikon2MnHeader.setByteOrder(byteOrder);

    EXPECT_EQ(nikon2MnHeader.byteOrder(), byteOrder);

}



TEST_F(Nikon2MnHeaderTest_2188, IfdOffset_Default_2188) {

    EXPECT_EQ(nikon2MnHeader.ifdOffset(), 0);

}



TEST_F(Nikon2MnHeaderTest_2188, BaseOffset_Default_2188) {

    size_t mnOffset = 10;

    EXPECT_EQ(nikon2MnHeader.baseOffset(mnOffset), mnOffset);

}
