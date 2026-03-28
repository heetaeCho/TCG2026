#include <gtest/gtest.h>

#include <gmock/gmock.h>



namespace Exiv2 {

    using byte = unsigned char;

    enum ByteOrder { littleEndian, bigEndian };

    uint16_t getUShort(const byte* buf, ByteOrder byteOrder);

}



class GetUShortTest : public ::testing::Test {

protected:

    Exiv2::byte buffer[2];

};



TEST_F(GetUShortTest_1136, NormalOperation_LittleEndian_1136) {

    buffer[0] = 0x01;

    buffer[1] = 0x00;

    EXPECT_EQ(Exiv2::getUShort(buffer, Exiv2::littleEndian), 1);

}



TEST_F(GetUShortTest_1136, NormalOperation_BigEndian_1136) {

    buffer[0] = 0x00;

    buffer[1] = 0x01;

    EXPECT_EQ(Exiv2::getUShort(buffer, Exiv2::bigEndian), 1);

}



TEST_F(GetUShortTest_1136, BoundaryCondition_MaxValue_LittleEndian_1136) {

    buffer[0] = 0xFF;

    buffer[1] = 0xFF;

    EXPECT_EQ(Exiv2::getUShort(buffer, Exiv2::littleEndian), 0xFFFF);

}



TEST_F(GetUShortTest_1136, BoundaryCondition_MaxValue_BigEndian_1136) {

    buffer[0] = 0xFF;

    buffer[1] = 0xFF;

    EXPECT_EQ(Exiv2::getUShort(buffer, Exiv2::bigEndian), 0xFFFF);

}



TEST_F(GetUShortTest_1136, BoundaryCondition_ZeroValue_LittleEndian_1136) {

    buffer[0] = 0x00;

    buffer[1] = 0x00;

    EXPECT_EQ(Exiv2::getUShort(buffer, Exiv2::littleEndian), 0);

}



TEST_F(GetUShortTest_1136, BoundaryCondition_ZeroValue_BigEndian_1136) {

    buffer[0] = 0x00;

    buffer[1] = 0x00;

    EXPECT_EQ(Exiv2::getUShort(buffer, Exiv2::bigEndian), 0);

}
