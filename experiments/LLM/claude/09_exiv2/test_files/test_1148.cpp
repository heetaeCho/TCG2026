#include <gtest/gtest.h>
#include <exiv2/types.hpp>

using namespace Exiv2;

// Test normal operation with little-endian byte order
TEST(Ur2DataTest_1148, NormalOperationLittleEndian_1148) {
    byte buf[8] = {0};
    URational val(0x12345678, 0xAABBCCDD);
    size_t result = ur2Data(buf, val, littleEndian);
    EXPECT_EQ(result, 8u);

    // Verify first component (numerator) in little-endian
    EXPECT_EQ(buf[0], 0x78);
    EXPECT_EQ(buf[1], 0x56);
    EXPECT_EQ(buf[2], 0x34);
    EXPECT_EQ(buf[3], 0x12);

    // Verify second component (denominator) in little-endian
    EXPECT_EQ(buf[4], 0xDD);
    EXPECT_EQ(buf[5], 0xCC);
    EXPECT_EQ(buf[6], 0xBB);
    EXPECT_EQ(buf[7], 0xAA);
}

// Test normal operation with big-endian byte order
TEST(Ur2DataTest_1148, NormalOperationBigEndian_1148) {
    byte buf[8] = {0};
    URational val(0x12345678, 0xAABBCCDD);
    size_t result = ur2Data(buf, val, bigEndian);
    EXPECT_EQ(result, 8u);

    // Verify first component (numerator) in big-endian
    EXPECT_EQ(buf[0], 0x12);
    EXPECT_EQ(buf[1], 0x34);
    EXPECT_EQ(buf[2], 0x56);
    EXPECT_EQ(buf[3], 0x78);

    // Verify second component (denominator) in big-endian
    EXPECT_EQ(buf[4], 0xAA);
    EXPECT_EQ(buf[5], 0xBB);
    EXPECT_EQ(buf[6], 0xCC);
    EXPECT_EQ(buf[7], 0xDD);
}

// Test with zero values
TEST(Ur2DataTest_1148, ZeroValues_1148) {
    byte buf[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    URational val(0, 0);
    size_t result = ur2Data(buf, val, littleEndian);
    EXPECT_EQ(result, 8u);

    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(buf[i], 0x00);
    }
}

// Test with maximum uint32 values
TEST(Ur2DataTest_1148, MaxUint32Values_1148) {
    byte buf[8] = {0};
    URational val(0xFFFFFFFF, 0xFFFFFFFF);
    size_t result = ur2Data(buf, val, bigEndian);
    EXPECT_EQ(result, 8u);

    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(buf[i], 0xFF);
    }
}

// Test with numerator zero, denominator non-zero
TEST(Ur2DataTest_1148, NumeratorZeroDenominatorNonZero_1148) {
    byte buf[8] = {0};
    URational val(0, 1);
    size_t result = ur2Data(buf, val, bigEndian);
    EXPECT_EQ(result, 8u);

    // Numerator should be 0
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x00);

    // Denominator should be 1
    EXPECT_EQ(buf[4], 0x00);
    EXPECT_EQ(buf[5], 0x00);
    EXPECT_EQ(buf[6], 0x00);
    EXPECT_EQ(buf[7], 0x01);
}

// Test with numerator non-zero, denominator zero
TEST(Ur2DataTest_1148, NumeratorNonZeroDenominatorZero_1148) {
    byte buf[8] = {0};
    URational val(1, 0);
    size_t result = ur2Data(buf, val, littleEndian);
    EXPECT_EQ(result, 8u);

    // Numerator should be 1 in little-endian
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x00);

    // Denominator should be 0
    EXPECT_EQ(buf[4], 0x00);
    EXPECT_EQ(buf[5], 0x00);
    EXPECT_EQ(buf[6], 0x00);
    EXPECT_EQ(buf[7], 0x00);
}

// Test return value is always 8
TEST(Ur2DataTest_1148, ReturnValueAlways8_1148) {
    byte buf[8] = {0};

    URational val1(1, 1);
    EXPECT_EQ(ur2Data(buf, val1, littleEndian), 8u);
    EXPECT_EQ(ur2Data(buf, val1, bigEndian), 8u);

    URational val2(0xFFFFFFFF, 0xFFFFFFFF);
    EXPECT_EQ(ur2Data(buf, val2, littleEndian), 8u);
    EXPECT_EQ(ur2Data(buf, val2, bigEndian), 8u);

    URational val3(0, 0);
    EXPECT_EQ(ur2Data(buf, val3, littleEndian), 8u);
    EXPECT_EQ(ur2Data(buf, val3, bigEndian), 8u);
}

// Test with value 1/1 big-endian
TEST(Ur2DataTest_1148, OneOverOneBigEndian_1148) {
    byte buf[8] = {0};
    URational val(1, 1);
    size_t result = ur2Data(buf, val, bigEndian);
    EXPECT_EQ(result, 8u);

    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x00);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x01);
    EXPECT_EQ(buf[4], 0x00);
    EXPECT_EQ(buf[5], 0x00);
    EXPECT_EQ(buf[6], 0x00);
    EXPECT_EQ(buf[7], 0x01);
}

// Test with asymmetric values to ensure numerator and denominator are in correct positions
TEST(Ur2DataTest_1148, AsymmetricValuesCorrectOrder_1148) {
    byte buf[8] = {0};
    URational val(0x00000001, 0x00000002);
    size_t result = ur2Data(buf, val, bigEndian);
    EXPECT_EQ(result, 8u);

    // First 4 bytes should be numerator (1)
    EXPECT_EQ(buf[3], 0x01);
    // Last 4 bytes should be denominator (2)
    EXPECT_EQ(buf[7], 0x02);
}

// Test consistency: write then read back should give same values
TEST(Ur2DataTest_1148, WriteReadConsistencyBigEndian_1148) {
    byte buf[8] = {0};
    URational original(12345, 67890);
    ur2Data(buf, original, bigEndian);

    URational readBack = getURational(buf, bigEndian);
    EXPECT_EQ(readBack.first, original.first);
    EXPECT_EQ(readBack.second, original.second);
}

// Test consistency: write then read back with little-endian
TEST(Ur2DataTest_1148, WriteReadConsistencyLittleEndian_1148) {
    byte buf[8] = {0};
    URational original(0xDEADBEEF, 0xCAFEBABE);
    ur2Data(buf, original, littleEndian);

    URational readBack = getURational(buf, littleEndian);
    EXPECT_EQ(readBack.first, original.first);
    EXPECT_EQ(readBack.second, original.second);
}

// Test that endianness actually changes the output
TEST(Ur2DataTest_1148, EndiannessDifference_1148) {
    byte bufLE[8] = {0};
    byte bufBE[8] = {0};
    URational val(0x01020304, 0x05060708);

    ur2Data(bufLE, val, littleEndian);
    ur2Data(bufBE, val, bigEndian);

    // The buffers should differ (since the value is not palindromic in bytes)
    bool different = false;
    for (int i = 0; i < 8; ++i) {
        if (bufLE[i] != bufBE[i]) {
            different = true;
            break;
        }
    }
    EXPECT_TRUE(different);
}
