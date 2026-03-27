#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/makernote_int.cpp"



using namespace Exiv2::Internal;



class SamsungMnHeaderTest_1491 : public ::testing::Test {

protected:

    SamsungMnHeader header;

};



TEST_F(SamsungMnHeaderTest_1491, ReadReturnsTrueForValidInput_1491) {

    const byte data[] = {0x00, 0x01};

    EXPECT_TRUE(header.read(data, sizeof(data), littleEndian));

}



TEST_F(SamsungMnHeaderTest_1491, ReadReturnsTrueForZeroSize_1491) {

    const byte data[] = {0x00, 0x01};

    EXPECT_TRUE(header.read(data, 0, littleEndian));

}



TEST_F(SamsungMnHeaderTest_1491, ReadReturnsTrueForAnyByteOrder_1491) {

    const byte data[] = {0x00, 0x01};

    EXPECT_TRUE(header.read(data, sizeof(data), littleEndian));

    EXPECT_TRUE(header.read(data, sizeof(data), bigEndian));

}



TEST_F(SamsungMnHeaderTest_1491, ReadReturnsTrueForNullPointerAndZeroSize_1491) {

    EXPECT_TRUE(header.read(nullptr, 0, littleEndian));

}
