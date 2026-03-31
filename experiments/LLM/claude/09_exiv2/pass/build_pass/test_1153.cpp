#include <gtest/gtest.h>
#include <cstring>
#include <cstdint>

// Include the necessary headers
#include "exiv2/types.hpp"

namespace Exiv2 {
// Declaration of the function under test
using byte = uint8_t;
size_t d2Data(byte* buf, double d, ByteOrder byteOrder);
}

class D2DataTest_1153 : public ::testing::Test {
protected:
    Exiv2::byte buf[8];

    void SetUp() override {
        std::memset(buf, 0, sizeof(buf));
    }
};

// Test that the function returns 8 for little endian
TEST_F(D2DataTest_1153, ReturnsEightBytesLittleEndian_1153) {
    double val = 1.0;
    size_t result = Exiv2::d2Data(buf, val, Exiv2::littleEndian);
    EXPECT_EQ(result, 8u);
}

// Test that the function returns 8 for big endian
TEST_F(D2DataTest_1153, ReturnsEightBytesBigEndian_1153) {
    double val = 1.0;
    size_t result = Exiv2::d2Data(buf, val, Exiv2::bigEndian);
    EXPECT_EQ(result, 8u);
}

// Test that zero is encoded correctly in little endian
TEST_F(D2DataTest_1153, ZeroLittleEndian_1153) {
    double val = 0.0;
    Exiv2::d2Data(buf, val, Exiv2::littleEndian);
    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(buf[i], 0) << "Byte " << i << " should be 0 for double 0.0 LE";
    }
}

// Test that zero is encoded correctly in big endian
TEST_F(D2DataTest_1153, ZeroBigEndian_1153) {
    double val = 0.0;
    Exiv2::d2Data(buf, val, Exiv2::bigEndian);
    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(buf[i], 0) << "Byte " << i << " should be 0 for double 0.0 BE";
    }
}

// Test encoding 1.0 in little endian
// IEEE 754: 1.0 = 0x3FF0000000000000
TEST_F(D2DataTest_1153, OneLittleEndian_1153) {
    double val = 1.0;
    Exiv2::d2Data(buf, val, Exiv2::littleEndian);
    // LE: least significant byte first
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x00);
    EXPECT_EQ(buf[4], 0x00);
    EXPECT_EQ(buf[5], 0x00);
    EXPECT_EQ(buf[6], 0xF0);
    EXPECT_EQ(buf[7], 0x3F);
}

// Test encoding 1.0 in big endian
TEST_F(D2DataTest_1153, OneBigEndian_1153) {
    double val = 1.0;
    Exiv2::d2Data(buf, val, Exiv2::bigEndian);
    // BE: most significant byte first
    EXPECT_EQ(buf[0], 0x3F);
    EXPECT_EQ(buf[1], 0xF0);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x00);
    EXPECT_EQ(buf[4], 0x00);
    EXPECT_EQ(buf[5], 0x00);
    EXPECT_EQ(buf[6], 0x00);
    EXPECT_EQ(buf[7], 0x00);
}

// Test encoding -1.0 in little endian
// IEEE 754: -1.0 = 0xBFF0000000000000
TEST_F(D2DataTest_1153, NegativeOneLittleEndian_1153) {
    double val = -1.0;
    Exiv2::d2Data(buf, val, Exiv2::littleEndian);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x00);
    EXPECT_EQ(buf[4], 0x00);
    EXPECT_EQ(buf[5], 0x00);
    EXPECT_EQ(buf[6], 0xF0);
    EXPECT_EQ(buf[7], 0xBF);
}

// Test encoding -1.0 in big endian
TEST_F(D2DataTest_1153, NegativeOneBigEndian_1153) {
    double val = -1.0;
    Exiv2::d2Data(buf, val, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0xBF);
    EXPECT_EQ(buf[1], 0xF0);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x00);
    EXPECT_EQ(buf[4], 0x00);
    EXPECT_EQ(buf[5], 0x00);
    EXPECT_EQ(buf[6], 0x00);
    EXPECT_EQ(buf[7], 0x00);
}

// Test that LE and BE are byte-reversed versions of each other
TEST_F(D2DataTest_1153, LEAndBEAreReversed_1153) {
    double val = 3.14159265358979;
    Exiv2::byte bufLE[8], bufBE[8];
    Exiv2::d2Data(bufLE, val, Exiv2::littleEndian);
    Exiv2::d2Data(bufBE, val, Exiv2::bigEndian);

    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(bufLE[i], bufBE[7 - i]) << "Byte " << i << " mismatch in LE/BE reversal";
    }
}

// Test encoding 2.0 in big endian
// IEEE 754: 2.0 = 0x4000000000000000
TEST_F(D2DataTest_1153, TwoBigEndian_1153) {
    double val = 2.0;
    Exiv2::d2Data(buf, val, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0x40);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x00);
    EXPECT_EQ(buf[4], 0x00);
    EXPECT_EQ(buf[5], 0x00);
    EXPECT_EQ(buf[6], 0x00);
    EXPECT_EQ(buf[7], 0x00);
}

// Test encoding 0.5 in big endian
// IEEE 754: 0.5 = 0x3FE0000000000000
TEST_F(D2DataTest_1153, HalfBigEndian_1153) {
    double val = 0.5;
    Exiv2::d2Data(buf, val, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0x3F);
    EXPECT_EQ(buf[1], 0xE0);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x00);
    EXPECT_EQ(buf[4], 0x00);
    EXPECT_EQ(buf[5], 0x00);
    EXPECT_EQ(buf[6], 0x00);
    EXPECT_EQ(buf[7], 0x00);
}

// Test encoding a very large number
// IEEE 754: 1e300 — just verify round-trip consistency via LE/BE reversal
TEST_F(D2DataTest_1153, VeryLargeNumberLEBEReversal_1153) {
    double val = 1e300;
    Exiv2::byte bufLE[8], bufBE[8];
    Exiv2::d2Data(bufLE, val, Exiv2::littleEndian);
    Exiv2::d2Data(bufBE, val, Exiv2::bigEndian);

    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(bufLE[i], bufBE[7 - i]);
    }
}

// Test encoding a very small (subnormal) number
TEST_F(D2DataTest_1153, VerySmallNumberLEBEReversal_1153) {
    double val = 5e-324; // smallest positive subnormal
    Exiv2::byte bufLE[8], bufBE[8];
    Exiv2::d2Data(bufLE, val, Exiv2::littleEndian);
    Exiv2::d2Data(bufBE, val, Exiv2::bigEndian);

    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(bufLE[i], bufBE[7 - i]);
    }
}

// Test encoding negative zero
// IEEE 754: -0.0 = 0x8000000000000000
TEST_F(D2DataTest_1153, NegativeZeroBigEndian_1153) {
    double val = -0.0;
    Exiv2::d2Data(buf, val, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0x80);
    for (int i = 1; i < 8; ++i) {
        EXPECT_EQ(buf[i], 0x00) << "Byte " << i;
    }
}

// Test encoding infinity in big endian
// IEEE 754: +inf = 0x7FF0000000000000
TEST_F(D2DataTest_1153, PositiveInfinityBigEndian_1153) {
    double val = std::numeric_limits<double>::infinity();
    Exiv2::d2Data(buf, val, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0x7F);
    EXPECT_EQ(buf[1], 0xF0);
    for (int i = 2; i < 8; ++i) {
        EXPECT_EQ(buf[i], 0x00) << "Byte " << i;
    }
}

// Test encoding negative infinity in big endian
// IEEE 754: -inf = 0xFFF0000000000000
TEST_F(D2DataTest_1153, NegativeInfinityBigEndian_1153) {
    double val = -std::numeric_limits<double>::infinity();
    Exiv2::d2Data(buf, val, Exiv2::bigEndian);
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0xF0);
    for (int i = 2; i < 8; ++i) {
        EXPECT_EQ(buf[i], 0x00) << "Byte " << i;
    }
}

// Test encoding NaN — at least verify the exponent bits are all set and mantissa is non-zero
TEST_F(D2DataTest_1153, NaNBigEndian_1153) {
    double val = std::numeric_limits<double>::quiet_NaN();
    Exiv2::d2Data(buf, val, Exiv2::bigEndian);
    // For NaN: exponent = 0x7FF, mantissa != 0
    // buf[0] should have 0x7F and buf[1] should have 0xF_ with at least some mantissa bits set
    EXPECT_EQ(buf[0] & 0x7F, 0x7F);
    EXPECT_EQ(buf[1] & 0xF0, 0xF0);
    // At least one bit in the mantissa should be non-zero
    bool mantissaNonZero = false;
    if (buf[1] & 0x0F) mantissaNonZero = true;
    for (int i = 2; i < 8; ++i) {
        if (buf[i] != 0) mantissaNonZero = true;
    }
    EXPECT_TRUE(mantissaNonZero);
}

// Test a known value: pi
// IEEE 754: pi ≈ 0x400921FB54442D18
TEST_F(D2DataTest_1153, PiBigEndian_1153) {
    double val = 3.14159265358979323846;
    Exiv2::d2Data(buf, val, Exiv2::bigEndian);
    // Check the known representation
    uint64_t expected = 0x400921FB54442D18ULL;
    for (int i = 0; i < 8; ++i) {
        uint8_t expectedByte = static_cast<uint8_t>((expected >> (56 - i * 8)) & 0xFF);
        EXPECT_EQ(buf[i], expectedByte) << "Byte " << i << " mismatch for pi in BE";
    }
}

// Test a known value: pi in little endian
TEST_F(D2DataTest_1153, PiLittleEndian_1153) {
    double val = 3.14159265358979323846;
    Exiv2::d2Data(buf, val, Exiv2::littleEndian);
    uint64_t expected = 0x400921FB54442D18ULL;
    for (int i = 0; i < 8; ++i) {
        uint8_t expectedByte = static_cast<uint8_t>((expected >> (i * 8)) & 0xFF);
        EXPECT_EQ(buf[i], expectedByte) << "Byte " << i << " mismatch for pi in LE";
    }
}
