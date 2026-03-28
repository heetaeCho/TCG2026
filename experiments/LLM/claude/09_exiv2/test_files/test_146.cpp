#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <cstring>
#include <cmath>
#include <limits>

namespace {

using namespace Exiv2;

// Test normal operation: converting a positive double to data in little-endian byte order
TEST(ToDataDoubleTest_146, PositiveDoubleLittleEndian_146) {
    byte buf[8];
    std::memset(buf, 0, sizeof(buf));
    double value = 3.14;
    size_t result = toData(buf, value, littleEndian);
    EXPECT_EQ(result, 8u);

    // Verify round-trip: read the value back
    double readBack;
    std::memcpy(&readBack, buf, sizeof(double));
    // On a little-endian system this should match directly;
    // we rely on the library's d2Data for correctness
    // Instead, use the library to verify if possible, or just check bytes are non-zero
    // We at minimum check that the function wrote something meaningful
    bool allZero = true;
    for (size_t i = 0; i < 8; ++i) {
        if (buf[i] != 0) {
            allZero = false;
            break;
        }
    }
    EXPECT_FALSE(allZero);
}

// Test normal operation: converting a positive double to data in big-endian byte order
TEST(ToDataDoubleTest_146, PositiveDoubleBigEndian_146) {
    byte buf[8];
    std::memset(buf, 0, sizeof(buf));
    double value = 3.14;
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 8u);

    bool allZero = true;
    for (size_t i = 0; i < 8; ++i) {
        if (buf[i] != 0) {
            allZero = false;
            break;
        }
    }
    EXPECT_FALSE(allZero);
}

// Test that different byte orders produce different byte representations for a non-trivial value
TEST(ToDataDoubleTest_146, DifferentByteOrdersProduceDifferentBytes_146) {
    byte bufLE[8];
    byte bufBE[8];
    std::memset(bufLE, 0, sizeof(bufLE));
    std::memset(bufBE, 0, sizeof(bufBE));

    double value = 1.23456789;
    toData(bufLE, value, littleEndian);
    toData(bufBE, value, bigEndian);

    // The two representations should be byte-reversed relative to each other
    // At minimum, they should differ (unless the machine representation happens to be palindromic, which is extremely unlikely for 1.23456789)
    bool differ = false;
    for (size_t i = 0; i < 8; ++i) {
        if (bufLE[i] != bufBE[i]) {
            differ = true;
            break;
        }
    }
    EXPECT_TRUE(differ);
}

// Test that byte orders are reverses of each other
TEST(ToDataDoubleTest_146, ByteOrdersAreReversed_146) {
    byte bufLE[8];
    byte bufBE[8];
    double value = 2.71828;

    toData(bufLE, value, littleEndian);
    toData(bufBE, value, bigEndian);

    // Big-endian and little-endian should be byte-reversed
    for (size_t i = 0; i < 8; ++i) {
        EXPECT_EQ(bufLE[i], bufBE[7 - i]);
    }
}

// Test boundary: zero value
TEST(ToDataDoubleTest_146, ZeroValue_146) {
    byte buf[8];
    std::memset(buf, 0xFF, sizeof(buf));
    double value = 0.0;
    size_t result = toData(buf, value, littleEndian);
    EXPECT_EQ(result, 8u);

    // IEEE 754: +0.0 is all zero bytes
    for (size_t i = 0; i < 8; ++i) {
        EXPECT_EQ(buf[i], 0u);
    }
}

// Test boundary: negative zero
TEST(ToDataDoubleTest_146, NegativeZero_146) {
    byte buf[8];
    std::memset(buf, 0, sizeof(buf));
    double value = -0.0;
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 8u);

    // Negative zero in IEEE 754 big-endian: sign bit is 1, so first byte should be 0x80
    EXPECT_EQ(buf[0], 0x80);
    for (size_t i = 1; i < 8; ++i) {
        EXPECT_EQ(buf[i], 0u);
    }
}

// Test boundary: negative value
TEST(ToDataDoubleTest_146, NegativeDouble_146) {
    byte bufLE[8];
    byte bufBE[8];
    double value = -42.5;

    toData(bufLE, value, littleEndian);
    toData(bufBE, value, bigEndian);

    // Verify reversibility
    for (size_t i = 0; i < 8; ++i) {
        EXPECT_EQ(bufLE[i], bufBE[7 - i]);
    }
}

// Test boundary: very large double
TEST(ToDataDoubleTest_146, VeryLargeDouble_146) {
    byte buf[8];
    double value = std::numeric_limits<double>::max();
    size_t result = toData(buf, value, littleEndian);
    EXPECT_EQ(result, 8u);
}

// Test boundary: very small positive double (denormalized)
TEST(ToDataDoubleTest_146, VerySmallPositiveDouble_146) {
    byte buf[8];
    double value = std::numeric_limits<double>::denorm_min();
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 8u);

    // denorm_min in big-endian: all zeros except the last byte which should be 1
    for (size_t i = 0; i < 7; ++i) {
        EXPECT_EQ(buf[i], 0u);
    }
    EXPECT_EQ(buf[7], 1u);
}

// Test boundary: positive infinity
TEST(ToDataDoubleTest_146, PositiveInfinity_146) {
    byte buf[8];
    double value = std::numeric_limits<double>::infinity();
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 8u);

    // IEEE 754 big-endian infinity: 0x7FF0000000000000
    EXPECT_EQ(buf[0], 0x7F);
    EXPECT_EQ(buf[1], 0xF0);
    for (size_t i = 2; i < 8; ++i) {
        EXPECT_EQ(buf[i], 0u);
    }
}

// Test boundary: negative infinity
TEST(ToDataDoubleTest_146, NegativeInfinity_146) {
    byte buf[8];
    double value = -std::numeric_limits<double>::infinity();
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 8u);

    // IEEE 754 big-endian -infinity: 0xFFF0000000000000
    EXPECT_EQ(buf[0], 0xFF);
    EXPECT_EQ(buf[1], 0xF0);
    for (size_t i = 2; i < 8; ++i) {
        EXPECT_EQ(buf[i], 0u);
    }
}

// Test boundary: NaN
TEST(ToDataDoubleTest_146, NaNValue_146) {
    byte buf[8];
    double value = std::numeric_limits<double>::quiet_NaN();
    size_t result = toData(buf, value, bigEndian);
    EXPECT_EQ(result, 8u);

    // NaN in IEEE 754: exponent all 1s, mantissa non-zero
    // First byte should have 0x7F and second byte should have at least 0xF0
    // The sign bit can be 0 or 1 depending on implementation
    byte exponentBits = (buf[0] & 0x7F);
    EXPECT_EQ(exponentBits, 0x7F);
    EXPECT_TRUE((buf[1] & 0xF0) == 0xF0);
    // Mantissa should be non-zero for NaN
    bool mantissaNonZero = false;
    if ((buf[1] & 0x0F) != 0) mantissaNonZero = true;
    for (size_t i = 2; i < 8 && !mantissaNonZero; ++i) {
        if (buf[i] != 0) mantissaNonZero = true;
    }
    EXPECT_TRUE(mantissaNonZero);
}

// Test: return value is always 8 (sizeof(double))
TEST(ToDataDoubleTest_146, ReturnValueIsEight_146) {
    byte buf[8];
    double value = 1.0;

    size_t resultLE = toData(buf, value, littleEndian);
    EXPECT_EQ(resultLE, 8u);

    size_t resultBE = toData(buf, value, bigEndian);
    EXPECT_EQ(resultBE, 8u);
}

// Test: one (1.0) representation
TEST(ToDataDoubleTest_146, OnePointZeroBigEndian_146) {
    byte buf[8];
    double value = 1.0;
    toData(buf, value, bigEndian);

    // IEEE 754 big-endian 1.0: 0x3FF0000000000000
    EXPECT_EQ(buf[0], 0x3F);
    EXPECT_EQ(buf[1], 0xF0);
    for (size_t i = 2; i < 8; ++i) {
        EXPECT_EQ(buf[i], 0u);
    }
}

// Test: one (1.0) in little-endian
TEST(ToDataDoubleTest_146, OnePointZeroLittleEndian_146) {
    byte buf[8];
    double value = 1.0;
    toData(buf, value, littleEndian);

    // IEEE 754 little-endian 1.0: reversed of 0x3FF0000000000000
    EXPECT_EQ(buf[7], 0x3F);
    EXPECT_EQ(buf[6], 0xF0);
    for (size_t i = 0; i < 6; ++i) {
        EXPECT_EQ(buf[i], 0u);
    }
}

// Test: epsilon value
TEST(ToDataDoubleTest_146, EpsilonValue_146) {
    byte buf[8];
    double value = std::numeric_limits<double>::epsilon();
    size_t result = toData(buf, value, littleEndian);
    EXPECT_EQ(result, 8u);

    // Just verify it's not all zeros (epsilon is a very small positive number, but not zero)
    bool allZero = true;
    for (size_t i = 0; i < 8; ++i) {
        if (buf[i] != 0) {
            allZero = false;
            break;
        }
    }
    EXPECT_FALSE(allZero);
}

}  // namespace
