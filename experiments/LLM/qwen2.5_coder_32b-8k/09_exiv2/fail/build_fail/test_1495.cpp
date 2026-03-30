#include <gtest/gtest.h>

#include "makernote_int.hpp"



using namespace Exiv2::Internal;



class SigmaMnHeaderTest_1495 : public ::testing::Test {

protected:

    SigmaMnHeader header;

};



TEST_F(SigmaMnHeaderTest_1495, IfdOffsetDefaultValue_1495) {

    EXPECT_EQ(header.ifdOffset(), 0U);

}



TEST_F(SigmaMnHeaderTest_1495, ReadReturnsFalseOnNullData_1495) {

    const byte* pData = nullptr;

    size_t size = 10;

    ByteOrder byteOrder = littleEndian;



    EXPECT_FALSE(header.read(pData, size, byteOrder));

}



TEST_F(SigmaMnHeaderTest_1495, ReadReturnsFalseOnZeroSize_1495) {

    const byte pData[1] = {0};

    size_t size = 0;

    ByteOrder byteOrder = littleEndian;



    EXPECT_FALSE(header.read(pData, size, byteOrder));

}



TEST_F(SigmaMnHeaderTest_1495, SizeReturnsExpectedValue_1495) {

    EXPECT_EQ(header.size(), SigmaMnHeader::sizeOfSignature());

}



TEST_F(SigmaMnHeaderTest_1495, WriteReturnsZeroOnNullIoWrapper_1495) {

    IoWrapper* ioWrapper = nullptr;

    ByteOrder byteOrder = littleEndian;



    EXPECT_EQ(header.write(*ioWrapper, byteOrder), 0U);

}
