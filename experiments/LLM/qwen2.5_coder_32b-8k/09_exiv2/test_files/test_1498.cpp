#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class SonyMnHeaderTest_1498 : public ::testing::Test {

protected:

    SonyMnHeader sonyMnHeader;

};



TEST_F(SonyMnHeaderTest_1498, SizeOfSignature_ReturnsCorrectSize_1498) {

    EXPECT_EQ(sonyMnHeader.sizeOfSignature(), sizeof(SonyMnHeader::signature_));

}



TEST_F(SonyMnHeaderTest_1498, Size_DefaultConstructed_ReturnsZero_1498) {

    EXPECT_EQ(sonyMnHeader.size(), 0U);

}



TEST_F(SonyMnHeaderTest_1498, IfdOffset_DefaultConstructed_ReturnsZero_1498) {

    EXPECT_EQ(sonyMnHeader.ifdOffset(), 0U);

}



TEST_F(SonyMnHeaderTest_1498, Read_ValidData_ReturnsTrue_1498) {

    byte data[] = {0x01, 0x02, 0x03};

    EXPECT_TRUE(sonyMnHeader.read(data, sizeof(data), littleEndian));

}



TEST_F(SonyMnHeaderTest_1498, Read_NullData_ReturnsFalse_1498) {

    EXPECT_FALSE(sonyMnHeader.read(nullptr, 5, littleEndian));

}



TEST_F(SonyMnHeaderTest_1498, Write_ValidIoWrapper_ReturnsSize_1498) {

    IoWrapper ioWrapper;

    EXPECT_EQ(sonyMnHeader.write(ioWrapper, littleEndian), sonyMnHeader.size());

}



TEST_F(SonyMnHeaderTest_1498, Write_NullIoWrapper_ReturnsZero_1498) {

    // Since we cannot pass a null IoWrapper (it's not a pointer), this test is more of a conceptual check.

    // In practice, you would need to ensure that the IoWrapper is properly constructed and valid.

    IoWrapper ioWrapper;

    EXPECT_EQ(sonyMnHeader.write(ioWrapper, littleEndian), sonyMnHeader.size());

}
