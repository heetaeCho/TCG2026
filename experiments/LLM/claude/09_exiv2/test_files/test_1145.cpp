#include <gtest/gtest.h>
#include "exiv2/types.hpp"

namespace Exiv2 {
// Declaration of the function under test
using byte = uint8_t;
size_t us2Data(byte* buf, uint16_t s, ByteOrder byteOrder);
}

class Us2DataTest_1145 : public ::testing::Test {
protected:
    Exiv2::byte buf[2];

    void SetUp() override {
        buf[0] = 0;
        buf[1] = 0;
    }
};

// Test return value is always 2
TEST_F(Us2DataTest_1145, ReturnValue_LittleEndian_1145) {
    size_t result = Exiv2::us2Data(buf, 0x1234, Exiv2::littleEndian);
    EXPECT_EQ(result, 2u);
}

TEST_F(Us2DataTest_1145, ReturnValue_BigEndian_1145) {
    size_t result = Exiv2::us2Data(buf, 0x1234, Exiv2::bigEndian);
    EXPECT_EQ(result, 2u);
}

// Test little endian byte ordering
TEST_F(Us2DataTest_1145, LittleEndian_NormalValue_1145) {
    Exiv2::us2Data(buf, 0x1234, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0x34);  // Low byte first
    EXPECT_EQ(buf[1], 0x12);  // High byte second
}

// Test big endian byte ordering
TEST_F(Us2DataTest_1145, BigEndian_NormalValue_1145) {
    Exiv2::us2Data(buf, 0x1234, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0x12);  // High byte first
    EXPECT_EQ(buf[1], 0x34);  // Low byte second
}

// Test with zero value
TEST_F(Us2DataTest_1145, LittleEndian_ZeroValue_1145) {
    Exiv2::us2Data(buf, 0x0000, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
}

TEST_F(Us2DataTest_1145, BigEndian_ZeroValue_1145) {
    Exiv2::us2Data(buf, 0x0000, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
}

// Test with maximum uint16_t value
TEST_F(Us2DataTest_1145, LittleEndian_MaxValue_1145) {
    Exiv2::us2Data(buf, 0xFFFF, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0xFF);
}

TEST_F(Us2DataTest_1145, BigEndian_MaxValue_1145) {
    Exiv2::us2Data(buf, 0xFFFF, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0xFF);
}

// Test with value where only low byte is set
TEST_F(Us2DataTest_1145, LittleEndian_LowByteOnly_1145) {
    Exiv2::us2Data(buf, 0x00AB, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0xAB);
    EXPECT_EQ(buf[1], 0x00);
}

TEST_F(Us2DataTest_1145, BigEndian_LowByteOnly_1145) {
    Exiv2::us2Data(buf, 0x00AB, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0xAB);
}

// Test with value where only high byte is set
TEST_F(Us2DataTest_1145, LittleEndian_HighByteOnly_1145) {
    Exiv2::us2Data(buf, 0xCD00, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0xCD);
}

TEST_F(Us2DataTest_1145, BigEndian_HighByteOnly_1145) {
    Exiv2::us2Data(buf, 0xCD00, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0xCD);
    EXPECT_EQ(buf[1], 0x00);
}

// Test with value 1
TEST_F(Us2DataTest_1145, LittleEndian_ValueOne_1145) {
    Exiv2::us2Data(buf, 0x0001, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x00);
}

TEST_F(Us2DataTest_1145, BigEndian_ValueOne_1145) {
    Exiv2::us2Data(buf, 0x0001, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x01);
}

// Test with value 256 (0x0100)
TEST_F(Us2DataTest_1145, LittleEndian_Value256_1145) {
    Exiv2::us2Data(buf, 0x0100, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x01);
}

TEST_F(Us2DataTest_1145, BigEndian_Value256_1145) {
    Exiv2::us2Data(buf, 0x0100, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x00);
}

// Test that big endian and little endian produce swapped results
TEST_F(Us2DataTest_1145, EndianSwapVerification_1145) {
    Exiv2::byte bufLE[2], bufBE[2];
    Exiv2::us2Data(bufLE, 0xABCD, Exiv2::littleEndian);
    Exiv2::us2Data(bufBE, 0xABCD, Exiv2::bigEndian);
    EXPECT_EQ(bufLE[0], bufBE[1]);
    EXPECT_EQ(bufLE[1], bufBE[0]);
}

// Test with alternating bit patterns
TEST_F(Us2DataTest_1145, LittleEndian_AlternatingBits_1145) {
    Exiv2::us2Data(buf, 0xAAAA, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0xAA);
    EXPECT_EQ(buf[1], 0xAA);
}

TEST_F(Us2DataTest_1145, BigEndian_AlternatingBits_1145) {
    Exiv2::us2Data(buf, 0x5555, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0x55);
    EXPECT_EQ(buf[1], 0x55);
}

// Test boundary: value 255 (0x00FF)
TEST_F(Us2DataTest_1145, LittleEndian_Value255_1145) {
    Exiv2::us2Data(buf, 0x00FF, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0x00);
}

TEST_F(Us2DataTest_1145, BigEndian_Value255_1145) {
    Exiv2::us2Data(buf, 0x00FF, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0xFF);
}

// Test boundary: value 0xFF00
TEST_F(Us2DataTest_1145, LittleEndian_ValueFF00_1145) {
    Exiv2::us2Data(buf, 0xFF00, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0xFF);
}

TEST_F(Us2DataTest_1145, BigEndian_ValueFF00_1145) {
    Exiv2::us2Data(buf, 0xFF00, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0x00);
}
