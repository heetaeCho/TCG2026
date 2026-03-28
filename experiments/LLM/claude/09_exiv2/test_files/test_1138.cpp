#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>

// Include the necessary headers
#include "exiv2/types.hpp"

namespace Exiv2 {
// Declaration of the function under test
uint64_t getULongLong(const byte* buf, ByteOrder byteOrder);
}

using Exiv2::byte;
using Exiv2::getULongLong;
using Exiv2::littleEndian;
using Exiv2::bigEndian;

class GetULongLongTest_1138 : public ::testing::Test {
protected:
    byte buf[8];

    void SetUp() override {
        std::memset(buf, 0, sizeof(buf));
    }
};

// Test all zeros in little endian
TEST_F(GetULongLongTest_1138, AllZerosLittleEndian_1138) {
    uint64_t result = getULongLong(buf, littleEndian);
    EXPECT_EQ(result, 0ULL);
}

// Test all zeros in big endian
TEST_F(GetULongLongTest_1138, AllZerosBigEndian_1138) {
    uint64_t result = getULongLong(buf, bigEndian);
    EXPECT_EQ(result, 0ULL);
}

// Test value 1 in little endian (0x01 at buf[0])
TEST_F(GetULongLongTest_1138, ValueOneLittleEndian_1138) {
    buf[0] = 0x01;
    uint64_t result = getULongLong(buf, littleEndian);
    EXPECT_EQ(result, 1ULL);
}

// Test value 1 in big endian (0x01 at buf[7])
TEST_F(GetULongLongTest_1138, ValueOneBigEndian_1138) {
    buf[7] = 0x01;
    uint64_t result = getULongLong(buf, bigEndian);
    EXPECT_EQ(result, 1ULL);
}

// Test maximum value (all 0xFF) in little endian
TEST_F(GetULongLongTest_1138, MaxValueLittleEndian_1138) {
    std::memset(buf, 0xFF, 8);
    uint64_t result = getULongLong(buf, littleEndian);
    EXPECT_EQ(result, 0xFFFFFFFFFFFFFFFFULL);
}

// Test maximum value (all 0xFF) in big endian
TEST_F(GetULongLongTest_1138, MaxValueBigEndian_1138) {
    std::memset(buf, 0xFF, 8);
    uint64_t result = getULongLong(buf, bigEndian);
    EXPECT_EQ(result, 0xFFFFFFFFFFFFFFFFULL);
}

// Test a known value in big endian: 0x0102030405060708
TEST_F(GetULongLongTest_1138, KnownValueBigEndian_1138) {
    buf[0] = 0x01; buf[1] = 0x02; buf[2] = 0x03; buf[3] = 0x04;
    buf[4] = 0x05; buf[5] = 0x06; buf[6] = 0x07; buf[7] = 0x08;
    uint64_t result = getULongLong(buf, bigEndian);
    EXPECT_EQ(result, 0x0102030405060708ULL);
}

// Test the same buffer in little endian should give reversed byte interpretation
TEST_F(GetULongLongTest_1138, KnownValueLittleEndian_1138) {
    buf[0] = 0x01; buf[1] = 0x02; buf[2] = 0x03; buf[3] = 0x04;
    buf[4] = 0x05; buf[5] = 0x06; buf[6] = 0x07; buf[7] = 0x08;
    uint64_t result = getULongLong(buf, littleEndian);
    EXPECT_EQ(result, 0x0807060504030201ULL);
}

// Test only the most significant byte set in big endian
TEST_F(GetULongLongTest_1138, MSBSetBigEndian_1138) {
    buf[0] = 0x80;
    uint64_t result = getULongLong(buf, bigEndian);
    EXPECT_EQ(result, 0x8000000000000000ULL);
}

// Test only the most significant byte set in little endian
TEST_F(GetULongLongTest_1138, MSBSetLittleEndian_1138) {
    buf[7] = 0x80;
    uint64_t result = getULongLong(buf, littleEndian);
    EXPECT_EQ(result, 0x8000000000000000ULL);
}

// Test consistency: big endian and little endian with reversed buffers should give same result
TEST_F(GetULongLongTest_1138, ConsistencyBetweenEndianness_1138) {
    byte buf_be[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    byte buf_le[8] = {0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01};
    
    uint64_t result_be = getULongLong(buf_be, bigEndian);
    uint64_t result_le = getULongLong(buf_le, littleEndian);
    EXPECT_EQ(result_be, result_le);
}

// Test a value that fits in 4 bytes (lower half) in big endian
TEST_F(GetULongLongTest_1138, Lower32BitsBigEndian_1138) {
    buf[4] = 0x00; buf[5] = 0x00; buf[6] = 0x00; buf[7] = 0xFF;
    uint64_t result = getULongLong(buf, bigEndian);
    EXPECT_EQ(result, 0x00000000000000FFULL);
}

// Test a value that fits in 4 bytes (lower half) in little endian
TEST_F(GetULongLongTest_1138, Lower32BitsLittleEndian_1138) {
    buf[0] = 0xFF;
    uint64_t result = getULongLong(buf, littleEndian);
    EXPECT_EQ(result, 0x00000000000000FFULL);
}

// Test upper 32 bits only in big endian
TEST_F(GetULongLongTest_1138, Upper32BitsBigEndian_1138) {
    buf[0] = 0xDE; buf[1] = 0xAD; buf[2] = 0xBE; buf[3] = 0xEF;
    uint64_t result = getULongLong(buf, bigEndian);
    EXPECT_EQ(result, 0xDEADBEEF00000000ULL);
}

// Test upper 32 bits only in little endian
TEST_F(GetULongLongTest_1138, Upper32BitsLittleEndian_1138) {
    buf[4] = 0xEF; buf[5] = 0xBE; buf[6] = 0xAD; buf[7] = 0xDE;
    uint64_t result = getULongLong(buf, littleEndian);
    EXPECT_EQ(result, 0xDEADBEEF00000000ULL);
}

// Test single byte at each position in big endian
TEST_F(GetULongLongTest_1138, SingleBytePositionsBigEndian_1138) {
    for (int i = 0; i < 8; i++) {
        std::memset(buf, 0, 8);
        buf[i] = 0x01;
        uint64_t result = getULongLong(buf, bigEndian);
        uint64_t expected = 1ULL << ((7 - i) * 8);
        EXPECT_EQ(result, expected) << "Failed at position " << i;
    }
}

// Test single byte at each position in little endian
TEST_F(GetULongLongTest_1138, SingleBytePositionsLittleEndian_1138) {
    for (int i = 0; i < 8; i++) {
        std::memset(buf, 0, 8);
        buf[i] = 0x01;
        uint64_t result = getULongLong(buf, littleEndian);
        uint64_t expected = 1ULL << (i * 8);
        EXPECT_EQ(result, expected) << "Failed at position " << i;
    }
}

// Test with alternating byte pattern
TEST_F(GetULongLongTest_1138, AlternatingPatternBigEndian_1138) {
    buf[0] = 0xAA; buf[1] = 0x55; buf[2] = 0xAA; buf[3] = 0x55;
    buf[4] = 0xAA; buf[5] = 0x55; buf[6] = 0xAA; buf[7] = 0x55;
    uint64_t result = getULongLong(buf, bigEndian);
    EXPECT_EQ(result, 0xAA55AA55AA55AA55ULL);
}

TEST_F(GetULongLongTest_1138, AlternatingPatternLittleEndian_1138) {
    buf[0] = 0x55; buf[1] = 0xAA; buf[2] = 0x55; buf[3] = 0xAA;
    buf[4] = 0x55; buf[5] = 0xAA; buf[6] = 0x55; buf[7] = 0xAA;
    uint64_t result = getULongLong(buf, littleEndian);
    EXPECT_EQ(result, 0xAA55AA55AA55AA55ULL);
}
