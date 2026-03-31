#include <gtest/gtest.h>
#include <exiv2/types.hpp>
#include <cstring>

using namespace Exiv2;

class GetRationalTest_1142 : public ::testing::Test {
protected:
    byte buf[8];

    void SetUp() override {
        std::memset(buf, 0, sizeof(buf));
    }

    void writeLong(byte* dest, int32_t value, ByteOrder byteOrder) {
        if (byteOrder == littleEndian) {
            dest[0] = static_cast<byte>(value & 0xFF);
            dest[1] = static_cast<byte>((value >> 8) & 0xFF);
            dest[2] = static_cast<byte>((value >> 16) & 0xFF);
            dest[3] = static_cast<byte>((value >> 24) & 0xFF);
        } else {
            dest[0] = static_cast<byte>((value >> 24) & 0xFF);
            dest[1] = static_cast<byte>((value >> 16) & 0xFF);
            dest[2] = static_cast<byte>((value >> 8) & 0xFF);
            dest[3] = static_cast<byte>(value & 0xFF);
        }
    }
};

TEST_F(GetRationalTest_1142, SimplePositiveRational_LittleEndian_1142) {
    writeLong(buf, 1, littleEndian);
    writeLong(buf + 4, 2, littleEndian);

    Rational result = getRational(buf, littleEndian);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 2);
}

TEST_F(GetRationalTest_1142, SimplePositiveRational_BigEndian_1142) {
    writeLong(buf, 1, bigEndian);
    writeLong(buf + 4, 2, bigEndian);

    Rational result = getRational(buf, bigEndian);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 2);
}

TEST_F(GetRationalTest_1142, ZeroNominator_1142) {
    writeLong(buf, 0, littleEndian);
    writeLong(buf + 4, 5, littleEndian);

    Rational result = getRational(buf, littleEndian);
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, 5);
}

TEST_F(GetRationalTest_1142, ZeroDenominator_1142) {
    writeLong(buf, 3, littleEndian);
    writeLong(buf + 4, 0, littleEndian);

    Rational result = getRational(buf, littleEndian);
    EXPECT_EQ(result.first, 3);
    EXPECT_EQ(result.second, 0);
}

TEST_F(GetRationalTest_1142, BothZero_1142) {
    writeLong(buf, 0, bigEndian);
    writeLong(buf + 4, 0, bigEndian);

    Rational result = getRational(buf, bigEndian);
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, 0);
}

TEST_F(GetRationalTest_1142, NegativeNominator_LittleEndian_1142) {
    writeLong(buf, -7, littleEndian);
    writeLong(buf + 4, 3, littleEndian);

    Rational result = getRational(buf, littleEndian);
    EXPECT_EQ(result.first, -7);
    EXPECT_EQ(result.second, 3);
}

TEST_F(GetRationalTest_1142, NegativeDenominator_BigEndian_1142) {
    writeLong(buf, 5, bigEndian);
    writeLong(buf + 4, -10, bigEndian);

    Rational result = getRational(buf, bigEndian);
    EXPECT_EQ(result.first, 5);
    EXPECT_EQ(result.second, -10);
}

TEST_F(GetRationalTest_1142, BothNegative_1142) {
    writeLong(buf, -100, littleEndian);
    writeLong(buf + 4, -200, littleEndian);

    Rational result = getRational(buf, littleEndian);
    EXPECT_EQ(result.first, -100);
    EXPECT_EQ(result.second, -200);
}

TEST_F(GetRationalTest_1142, MaxInt32Values_LittleEndian_1142) {
    int32_t maxVal = std::numeric_limits<int32_t>::max();
    writeLong(buf, maxVal, littleEndian);
    writeLong(buf + 4, maxVal, littleEndian);

    Rational result = getRational(buf, littleEndian);
    EXPECT_EQ(result.first, maxVal);
    EXPECT_EQ(result.second, maxVal);
}

TEST_F(GetRationalTest_1142, MinInt32Values_BigEndian_1142) {
    int32_t minVal = std::numeric_limits<int32_t>::min();
    writeLong(buf, minVal, bigEndian);
    writeLong(buf + 4, minVal, bigEndian);

    Rational result = getRational(buf, bigEndian);
    EXPECT_EQ(result.first, minVal);
    EXPECT_EQ(result.second, minVal);
}

TEST_F(GetRationalTest_1142, MaxNominatorMinDenominator_1142) {
    int32_t maxVal = std::numeric_limits<int32_t>::max();
    int32_t minVal = std::numeric_limits<int32_t>::min();
    writeLong(buf, maxVal, littleEndian);
    writeLong(buf + 4, minVal, littleEndian);

    Rational result = getRational(buf, littleEndian);
    EXPECT_EQ(result.first, maxVal);
    EXPECT_EQ(result.second, minVal);
}

TEST_F(GetRationalTest_1142, OneOverOne_LittleEndian_1142) {
    writeLong(buf, 1, littleEndian);
    writeLong(buf + 4, 1, littleEndian);

    Rational result = getRational(buf, littleEndian);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 1);
}

TEST_F(GetRationalTest_1142, OneOverOne_BigEndian_1142) {
    writeLong(buf, 1, bigEndian);
    writeLong(buf + 4, 1, bigEndian);

    Rational result = getRational(buf, bigEndian);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 1);
}

TEST_F(GetRationalTest_1142, LargePositiveValues_1142) {
    writeLong(buf, 1000000, bigEndian);
    writeLong(buf + 4, 999999, bigEndian);

    Rational result = getRational(buf, bigEndian);
    EXPECT_EQ(result.first, 1000000);
    EXPECT_EQ(result.second, 999999);
}

TEST_F(GetRationalTest_1142, NegativeOneOverPositiveOne_1142) {
    writeLong(buf, -1, littleEndian);
    writeLong(buf + 4, 1, littleEndian);

    Rational result = getRational(buf, littleEndian);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, 1);
}

TEST_F(GetRationalTest_1142, ConsistencyBetweenByteOrders_1142) {
    // Write same values in both byte orders and verify results match
    byte buf_le[8], buf_be[8];
    
    int32_t nom = 42;
    int32_t den = 17;
    
    writeLong(buf_le, nom, littleEndian);
    writeLong(buf_le + 4, den, littleEndian);
    
    writeLong(buf_be, nom, bigEndian);
    writeLong(buf_be + 4, den, bigEndian);
    
    Rational result_le = getRational(buf_le, littleEndian);
    Rational result_be = getRational(buf_be, bigEndian);
    
    EXPECT_EQ(result_le.first, result_be.first);
    EXPECT_EQ(result_le.second, result_be.second);
    EXPECT_EQ(result_le.first, 42);
    EXPECT_EQ(result_le.second, 17);
}
