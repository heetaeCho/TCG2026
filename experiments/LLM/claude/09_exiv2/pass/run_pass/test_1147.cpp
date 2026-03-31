#include <gtest/gtest.h>
#include <cstring>
#include "exiv2/types.hpp"

// Declaration of the function under test
namespace Exiv2 {
    typedef uint8_t byte;
    size_t ull2Data(byte* buf, uint64_t l, ByteOrder byteOrder);
}

class Ull2DataTest_1147 : public ::testing::Test {
protected:
    Exiv2::byte buf[8];

    void SetUp() override {
        std::memset(buf, 0, sizeof(buf));
    }
};

// Test that the function returns 8 for little endian
TEST_F(Ull2DataTest_1147, ReturnsEightForLittleEndian_1147) {
    size_t result = Exiv2::ull2Data(buf, 0x0102030405060708ULL, Exiv2::littleEndian);
    EXPECT_EQ(result, 8u);
}

// Test that the function returns 8 for big endian
TEST_F(Ull2DataTest_1147, ReturnsEightForBigEndian_1147) {
    size_t result = Exiv2::ull2Data(buf, 0x0102030405060708ULL, Exiv2::bigEndian);
    EXPECT_EQ(result, 8u);
}

// Test little endian byte order for a known value
TEST_F(Ull2DataTest_1147, LittleEndianCorrectByteOrder_1147) {
    Exiv2::ull2Data(buf, 0x0102030405060708ULL, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0x08);
    EXPECT_EQ(buf[1], 0x07);
    EXPECT_EQ(buf[2], 0x06);
    EXPECT_EQ(buf[3], 0x05);
    EXPECT_EQ(buf[4], 0x04);
    EXPECT_EQ(buf[5], 0x03);
    EXPECT_EQ(buf[6], 0x02);
    EXPECT_EQ(buf[7], 0x01);
}

// Test big endian byte order for a known value
TEST_F(Ull2DataTest_1147, BigEndianCorrectByteOrder_1147) {
    Exiv2::ull2Data(buf, 0x0102030405060708ULL, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
    EXPECT_EQ(buf[2], 0x03);
    EXPECT_EQ(buf[3], 0x04);
    EXPECT_EQ(buf[4], 0x05);
    EXPECT_EQ(buf[5], 0x06);
    EXPECT_EQ(buf[6], 0x07);
    EXPECT_EQ(buf[7], 0x08);
}

// Test with zero value in little endian
TEST_F(Ull2DataTest_1147, ZeroValueLittleEndian_1147) {
    Exiv2::ull2Data(buf, 0ULL, Exiv2::littleEndian);
    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(buf[i], 0x00) << "Byte " << i << " should be 0";
    }
}

// Test with zero value in big endian
TEST_F(Ull2DataTest_1147, ZeroValueBigEndian_1147) {
    Exiv2::ull2Data(buf, 0ULL, Exiv2::bigEndian);
    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(buf[i], 0x00) << "Byte " << i << " should be 0";
    }
}

// Test with max uint64 value in little endian
TEST_F(Ull2DataTest_1147, MaxValueLittleEndian_1147) {
    Exiv2::ull2Data(buf, 0xFFFFFFFFFFFFFFFFULL, Exiv2::littleEndian);
    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(buf[i], 0xFF) << "Byte " << i << " should be 0xFF";
    }
}

// Test with max uint64 value in big endian
TEST_F(Ull2DataTest_1147, MaxValueBigEndian_1147) {
    Exiv2::ull2Data(buf, 0xFFFFFFFFFFFFFFFFULL, Exiv2::bigEndian);
    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(buf[i], 0xFF) << "Byte " << i << " should be 0xFF";
    }
}

// Test with value 1 in little endian
TEST_F(Ull2DataTest_1147, ValueOneLittleEndian_1147) {
    Exiv2::ull2Data(buf, 1ULL, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0x01);
    for (int i = 1; i < 8; i++) {
        EXPECT_EQ(buf[i], 0x00) << "Byte " << i << " should be 0";
    }
}

// Test with value 1 in big endian
TEST_F(Ull2DataTest_1147, ValueOneBigEndian_1147) {
    Exiv2::ull2Data(buf, 1ULL, Exiv2::bigEndian);
    for (int i = 0; i < 7; i++) {
        EXPECT_EQ(buf[i], 0x00) << "Byte " << i << " should be 0";
    }
    EXPECT_EQ(buf[7], 0x01);
}

// Test with value that only occupies the most significant byte in little endian
TEST_F(Ull2DataTest_1147, HighByteLittleEndian_1147) {
    Exiv2::ull2Data(buf, 0xFF00000000000000ULL, Exiv2::littleEndian);
    for (int i = 0; i < 7; i++) {
        EXPECT_EQ(buf[i], 0x00) << "Byte " << i << " should be 0";
    }
    EXPECT_EQ(buf[7], 0xFF);
}

// Test with value that only occupies the most significant byte in big endian
TEST_F(Ull2DataTest_1147, HighByteBigEndian_1147) {
    Exiv2::ull2Data(buf, 0xFF00000000000000ULL, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0xFF);
    for (int i = 1; i < 8; i++) {
        EXPECT_EQ(buf[i], 0x00) << "Byte " << i << " should be 0";
    }
}

// Test with alternating byte pattern in little endian
TEST_F(Ull2DataTest_1147, AlternatingPatternLittleEndian_1147) {
    Exiv2::ull2Data(buf, 0xAA55AA55AA55AA55ULL, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0x55);
    EXPECT_EQ(buf[1], 0xAA);
    EXPECT_EQ(buf[2], 0x55);
    EXPECT_EQ(buf[3], 0xAA);
    EXPECT_EQ(buf[4], 0x55);
    EXPECT_EQ(buf[5], 0xAA);
    EXPECT_EQ(buf[6], 0x55);
    EXPECT_EQ(buf[7], 0xAA);
}

// Test with alternating byte pattern in big endian
TEST_F(Ull2DataTest_1147, AlternatingPatternBigEndian_1147) {
    Exiv2::ull2Data(buf, 0xAA55AA55AA55AA55ULL, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0xAA);
    EXPECT_EQ(buf[1], 0x55);
    EXPECT_EQ(buf[2], 0xAA);
    EXPECT_EQ(buf[3], 0x55);
    EXPECT_EQ(buf[4], 0xAA);
    EXPECT_EQ(buf[5], 0x55);
    EXPECT_EQ(buf[6], 0xAA);
    EXPECT_EQ(buf[7], 0x55);
}

// Test that little endian and big endian produce reversed byte arrays
TEST_F(Ull2DataTest_1147, LittleAndBigEndianAreReversed_1147) {
    Exiv2::byte bufLE[8];
    Exiv2::byte bufBE[8];
    uint64_t val = 0x123456789ABCDEF0ULL;

    Exiv2::ull2Data(bufLE, val, Exiv2::littleEndian);
    Exiv2::ull2Data(bufBE, val, Exiv2::bigEndian);

    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(bufLE[i], bufBE[7 - i]) << "Byte " << i << " mismatch in reversal";
    }
}

// Test with a small value (fits in 2 bytes) in little endian
TEST_F(Ull2DataTest_1147, SmallValueLittleEndian_1147) {
    Exiv2::ull2Data(buf, 0x0100ULL, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x01);
    for (int i = 2; i < 8; i++) {
        EXPECT_EQ(buf[i], 0x00);
    }
}

// Test with a small value (fits in 2 bytes) in big endian
TEST_F(Ull2DataTest_1147, SmallValueBigEndian_1147) {
    Exiv2::ull2Data(buf, 0x0100ULL, Exiv2::bigEndian);
    for (int i = 0; i < 6; i++) {
        EXPECT_EQ(buf[i], 0x00);
    }
    EXPECT_EQ(buf[6], 0x01);
    EXPECT_EQ(buf[7], 0x00);
}

// Test with value 256 (0x100) to check proper byte splitting
TEST_F(Ull2DataTest_1147, Value256LittleEndian_1147) {
    Exiv2::ull2Data(buf, 256ULL, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x01);
    for (int i = 2; i < 8; i++) {
        EXPECT_EQ(buf[i], 0x00);
    }
}

// Test with a 32-bit boundary value
TEST_F(Ull2DataTest_1147, Value32BitBoundaryLittleEndian_1147) {
    Exiv2::ull2Data(buf, 0x00000000FFFFFFFFULL, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0xFF);
    EXPECT_EQ(buf[2], 0xFF);
    EXPECT_EQ(buf[3], 0xFF);
    EXPECT_EQ(buf[4], 0x00);
    EXPECT_EQ(buf[5], 0x00);
    EXPECT_EQ(buf[6], 0x00);
    EXPECT_EQ(buf[7], 0x00);
}

// Test with a 32-bit boundary value in big endian
TEST_F(Ull2DataTest_1147, Value32BitBoundaryBigEndian_1147) {
    Exiv2::ull2Data(buf, 0x00000000FFFFFFFFULL, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x00);
    EXPECT_EQ(buf[4], 0xFF);
    EXPECT_EQ(buf[5], 0xFF);
    EXPECT_EQ(buf[6], 0xFF);
    EXPECT_EQ(buf[7], 0xFF);
}
