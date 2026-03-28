#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class OlympusMnHeaderTest_1437 : public ::testing::Test {

protected:

    OlympusMnHeader olympusMnHeader;

};



TEST_F(OlympusMnHeaderTest_1437, SizeInitiallyZero_1437) {

    EXPECT_EQ(olympusMnHeader.size(), 0u);

}



TEST_F(OlympusMnHeaderTest_1437, ReadWithEmptyData_1437) {

    const byte* pData = nullptr;

    size_t size = 0;

    ByteOrder byteOrder = littleEndian;

    EXPECT_FALSE(olympusMnHeader.read(pData, size, byteOrder));

}



TEST_F(OlympusMnHeaderTest_1437, ReadWithNonEmptyData_1437) {

    const byte pData[] = { 0x01, 0x02, 0x03 };

    size_t size = sizeof(pData);

    ByteOrder byteOrder = littleEndian;

    EXPECT_TRUE(olympusMnHeader.read(pData, size, byteOrder));

}



TEST_F(OlympusMnHeaderTest_1437, WriteWithMockIoWrapper_1437) {

    Mock<IoWrapper> mockIoWrapper;

    ByteOrder byteOrder = littleEndian;



    EXPECT_CALL(mockIoWrapper, write(_, _)).Times(1).WillOnce(::testing::Return(sizeof(DataBuf)));



    size_t bytesWritten = olympusMnHeader.write(mockIoWrapper, byteOrder);

    EXPECT_EQ(bytesWritten, sizeof(DataBuf));

}



TEST_F(OlympusMnHeaderTest_1437, SizeOfSignatureIsPositive_1437) {

    EXPECT_GT(OlympusMnHeader::sizeOfSignature(), 0u);

}



TEST_F(OlympusMnHeaderTest_1437, IfdOffsetInitiallyZero_1437) {

    EXPECT_EQ(olympusMnHeader.ifdOffset(), 0u);

}
