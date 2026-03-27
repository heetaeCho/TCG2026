#include <gtest/gtest.h>

#include "exiv2/types.hpp"



using namespace Exiv2;



// Test fixture for ul2Data function tests.

class Ul2DataBaseTest : public ::testing::Test {

protected:

    byte buffer[4];

};



// Test normal operation with littleEndian byte order.

TEST_F(Ul2DataBaseTest, LittleEndianNormal_1146) {

    uint32_t value = 0x12345678;

    size_t result = ul2Data(buffer, value, littleEndian);

    EXPECT_EQ(result, 4);

    EXPECT_EQ(buffer[0], static_cast<byte>(0x78));

    EXPECT_EQ(buffer[1], static_cast<byte>(0x56));

    EXPECT_EQ(buffer[2], static_cast<byte>(0x34));

    EXPECT_EQ(buffer[3], static_cast<byte>(0x12));

}



// Test normal operation with bigEndian byte order.

TEST_F(Ul2DataBaseTest, BigEndianNormal_1146) {

    uint32_t value = 0x12345678;

    size_t result = ul2Data(buffer, value, bigEndian);

    EXPECT_EQ(result, 4);

    EXPECT_EQ(buffer[0], static_cast<byte>(0x12));

    EXPECT_EQ(buffer[1], static_cast<byte>(0x34));

    EXPECT_EQ(buffer[2], static_cast<byte>(0x56));

    EXPECT_EQ(buffer[3], static_cast<byte>(0x78));

}



// Test boundary condition with value 0.

TEST_F(Ul2DataBaseTest, ZeroValue_1146) {

    uint32_t value = 0;

    size_t result = ul2Data(buffer, value, littleEndian);

    EXPECT_EQ(result, 4);

    for (int i = 0; i < 4; ++i) {

        EXPECT_EQ(buffer[i], static_cast<byte>(0));

    }

}



// Test boundary condition with maximum uint32_t value.

TEST_F(Ul2DataBaseTest, MaxUint32Value_1146) {

    uint32_t value = UINT32_MAX;

    size_t result = ul2Data(buffer, value, littleEndian);

    EXPECT_EQ(result, 4);

    EXPECT_EQ(buffer[0], static_cast<byte>(0xFF));

    EXPECT_EQ(buffer[1], static_cast<byte>(0xFF));

    EXPECT_EQ(buffer[2], static_cast<byte>(0xFF));

    EXPECT_EQ(buffer[3], static_cast<byte>(0xFF));

}



// Test with invalidByteOrder, expect no change in buffer.

TEST_F(Ul2DataBaseTest, InvalidByteOrder_1146) {

    uint32_t value = 0x12345678;

    size_t result = ul2Data(buffer, value, invalidByteOrder);

    EXPECT_EQ(result, 4);

    for (int i = 0; i < 4; ++i) {

        EXPECT_EQ(buffer[i], static_cast<byte>(0));

    }

}
