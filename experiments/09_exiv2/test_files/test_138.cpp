#include <gtest/gtest.h>

#include "exiv2/value.hpp"



namespace {



class GetValueTest_138 : public ::testing::Test {

protected:

    uint16_t result;

};



TEST_F(GetValueTest_138, BigEndianNormalOperation_138) {

    const byte buf[] = {0x12, 0x34};

    result = Exiv2::getValue(buf, bigEndian);

    EXPECT_EQ(result, 0x1234);

}



TEST_F(GetValueTest_138, LittleEndianNormalOperation_138) {

    const byte buf[] = {0x34, 0x12};

    result = Exiv2::getValue(buf, littleEndian);

    EXPECT_EQ(result, 0x1234);

}



TEST_F(GetValueTest_138, BigEndianBoundaryCondition_138) {

    const byte buf[] = {0x00, 0x00};

    result = Exiv2::getValue(buf, bigEndian);

    EXPECT_EQ(result, 0x0000);



    const byte maxBuf[] = {0xFF, 0xFF};

    result = Exiv2::getValue(maxBuf, bigEndian);

    EXPECT_EQ(result, 0xFFFF);

}



TEST_F(GetValueTest_138, LittleEndianBoundaryCondition_138) {

    const byte buf[] = {0x00, 0x00};

    result = Exiv2::getValue(buf, littleEndian);

    EXPECT_EQ(result, 0x0000);



    const byte maxBuf[] = {0xFF, 0xFF};

    result = Exiv2::getValue(maxBuf, littleEndian);

    EXPECT_EQ(result, 0xFFFF);

}



} // namespace
