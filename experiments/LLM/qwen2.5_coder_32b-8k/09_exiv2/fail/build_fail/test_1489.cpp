#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/makernote_int.hpp"



using namespace Exiv2::Internal;

using namespace testing;



class SamsungMnHeaderTest_1489 : public Test {

protected:

    SamsungMnHeader header;

};



TEST_F(SamsungMnHeaderTest_1489, SizeReturnsZero_1489) {

    EXPECT_EQ(header.size(), 0);

}



TEST_F(SamsungMnHeaderTest_1489, ReadFunctionExists_1489) {

    const byte* pData = nullptr;

    size_t size = 0;

    ByteOrder byteOrder = littleEndian;

    EXPECT_FALSE(header.read(pData, size, byteOrder));

}



TEST_F(SamsungMnHeaderTest_1489, WriteFunctionExists_1489) {

    Mock<IoWrapper> mockIoWrapper;

    ByteOrder byteOrder = littleEndian;

    EXPECT_EQ(header.write(mockIoWrapper, byteOrder), 0);

}



TEST_F(SamsungMnHeaderTest_1489, BaseOffsetReturnsZero_1489) {

    size_t mnOffset = 0;

    EXPECT_EQ(header.baseOffset(mnOffset), 0);

}
