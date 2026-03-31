#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <cstring>
#include <cmath>
#include <limits>

namespace {

using namespace Exiv2;

// Helper to convert data back to float for verification
float dataToFloat(const byte* buf, ByteOrder byteOrder) {
    float result;
    uint32_t val;
    if (byteOrder == littleEndian) {
        val = static_cast<uint32_t>(buf[0])
            | (static_cast<uint32_t>(buf[1]) << 8)
            | (static_cast<uint32_t>(buf[2]) << 16)
            | (static_cast<uint32_t>(buf[3]) << 24);
    } else {
        val = (static_cast<uint32_t>(buf[0]) << 24)
            | (static_cast<uint32_t>(buf[1]) << 16)
            | (static_cast<uint32_t>(buf[2]) << 8)
            | static_cast<uint32_t>(buf[3]);
    }
    std::memcpy(&result, &val, sizeof(float));
    return result;
}

class ToDataFloatTest_145 : public ::testing::Test {
protected:
    byte buf[8];

    void SetUp() override {
        std::memset(buf, 0, sizeof(buf));
    }
};

TEST_F(ToDataFloatTest_145, ZeroValueLittleEndian_145) {
    float input = 0.0f;
    size_t result = toData(buf, input, littleEndian);
    EXPECT_EQ(result, 4u);
    float recovered = dataToFloat(buf, littleEndian);
    EXPECT_FLOAT_EQ(recovered, 0.0f);
}

TEST_F(ToDataFloatTest_145, ZeroValueBigEndian_145) {
    float input = 0.0f;
    size_t result = toData(buf, input, bigEndian);
    EXPECT_EQ(result, 4u);
    float recovered = dataToFloat(buf, bigEndian);
    EXPECT_FLOAT_EQ(recovered, 0.0f);
}

TEST_F(ToDataFloatTest_145, PositiveValueLittleEndian_145) {
    float input = 3.14f;
    size_t result = toData(buf, input, littleEndian);
    EXPECT_EQ(result, 4u);
    float recovered = dataToFloat(buf, littleEndian);
    EXPECT_FLOAT_EQ(recovered, 3.14f);
}

TEST_F(ToDataFloatTest_145, PositiveValueBigEndian_145) {
    float input = 3.14f;
    size_t result = toData(buf, input, bigEndian);
    EXPECT_EQ(result, 4u);
    float recovered = dataToFloat(buf, bigEndian);
    EXPECT_FLOAT_EQ(recovered, 3.14f);
}

TEST_F(ToDataFloatTest_145, NegativeValueLittleEndian_145) {
    float input = -42.5f;
    size_t result = toData(buf, input, littleEndian);
    EXPECT_EQ(result, 4u);
    float recovered = dataToFloat(buf, littleEndian);
    EXPECT_FLOAT_EQ(recovered, -42.5f);
}

TEST_F(ToDataFloatTest_145, NegativeValueBigEndian_145) {
    float input = -42.5f;
    size_t result = toData(buf, input, bigEndian);
    EXPECT_EQ(result, 4u);
    float recovered = dataToFloat(buf, bigEndian);
    EXPECT_FLOAT_EQ(recovered, -42.5f);
}

TEST_F(ToDataFloatTest_145, OnePointZeroLittleEndian_145) {
    float input = 1.0f;
    size_t result = toData(buf, input, littleEndian);
    EXPECT_EQ(result, 4u);
    float recovered = dataToFloat(buf, littleEndian);
    EXPECT_FLOAT_EQ(recovered, 1.0f);
}

TEST_F(ToDataFloatTest_145, OnePointZeroBigEndian_145) {
    float input = 1.0f;
    size_t result = toData(buf, input, bigEndian);
    EXPECT_EQ(result, 4u);
    float recovered = dataToFloat(buf, bigEndian);
    EXPECT_FLOAT_EQ(recovered, 1.0f);
}

TEST_F(ToDataFloatTest_145, NegativeOneLittleEndian_145) {
    float input = -1.0f;
    size_t result = toData(buf, input, littleEndian);
    EXPECT_EQ(result, 4u);
    float recovered = dataToFloat(buf, littleEndian);
    EXPECT_FLOAT_EQ(recovered, -1.0f);
}

TEST_F(ToDataFloatTest_145, MaxFloatLittleEndian_145) {
    float input = std::numeric_limits<float>::max();
    size_t result = toData(buf, input, littleEndian);
    EXPECT_EQ(result, 4u);
    float recovered = dataToFloat(buf, littleEndian);
    EXPECT_FLOAT_EQ(recovered, std::numeric_limits<float>::max());
}

TEST_F(ToDataFloatTest_145, MaxFloatBigEndian_145) {
    float input = std::numeric_limits<float>::max();
    size_t result = toData(buf, input, bigEndian);
    EXPECT_EQ(result, 4u);
    float recovered = dataToFloat(buf, bigEndian);
    EXPECT_FLOAT_EQ(recovered, std::numeric_limits<float>::max());
}

TEST_F(ToDataFloatTest_145, MinFloatLittleEndian_145) {
    float input = std::numeric_limits<float>::min();
    size_t result = toData(buf, input, littleEndian);
    EXPECT_EQ(result, 4u);
    float recovered = dataToFloat(buf, littleEndian);
    EXPECT_FLOAT_EQ(recovered, std::numeric_limits<float>::min());
}

TEST_F(ToDataFloatTest_145, MinFloatBigEndian_145) {
    float input = std::numeric_limits<float>::min();
    size_t result = toData(buf, input, bigEndian);
    EXPECT_EQ(result, 4u);
    float recovered = dataToFloat(buf, bigEndian);
    EXPECT_FLOAT_EQ(recovered, std::numeric_limits<float>::min());
}

TEST_F(ToDataFloatTest_145, LowestFloatLittleEndian_145) {
    float input = std::numeric_limits<float>::lowest();
    size_t result = toData(buf, input, littleEndian);
    EXPECT_EQ(result, 4u);
    float recovered = dataToFloat(buf, littleEndian);
    EXPECT_FLOAT_EQ(recovered, std::numeric_limits<float>::lowest());
}

TEST_F(ToDataFloatTest_145, DenormalizedValueLittleEndian_145) {
    float input = std::numeric_limits<float>::denorm_min();
    size_t result = toData(buf, input, littleEndian);
    EXPECT_EQ(result, 4u);
    float recovered = dataToFloat(buf, littleEndian);
    EXPECT_FLOAT_EQ(recovered, std::numeric_limits<float>::denorm_min());
}

TEST_F(ToDataFloatTest_145, InfinityLittleEndian_145) {
    float input = std::numeric_limits<float>::infinity();
    size_t result = toData(buf, input, littleEndian);
    EXPECT_EQ(result, 4u);
    float recovered = dataToFloat(buf, littleEndian);
    EXPECT_TRUE(std::isinf(recovered));
    EXPECT_GT(recovered, 0.0f);
}

TEST_F(ToDataFloatTest_145, NegativeInfinityBigEndian_145) {
    float input = -std::numeric_limits<float>::infinity();
    size_t result = toData(buf, input, bigEndian);
    EXPECT_EQ(result, 4u);
    float recovered = dataToFloat(buf, bigEndian);
    EXPECT_TRUE(std::isinf(recovered));
    EXPECT_LT(recovered, 0.0f);
}

TEST_F(ToDataFloatTest_145, NaNLittleEndian_145) {
    float input = std::numeric_limits<float>::quiet_NaN();
    size_t result = toData(buf, input, littleEndian);
    EXPECT_EQ(result, 4u);
    float recovered = dataToFloat(buf, littleEndian);
    EXPECT_TRUE(std::isnan(recovered));
}

TEST_F(ToDataFloatTest_145, NaNBigEndian_145) {
    float input = std::numeric_limits<float>::quiet_NaN();
    size_t result = toData(buf, input, bigEndian);
    EXPECT_EQ(result, 4u);
    float recovered = dataToFloat(buf, bigEndian);
    EXPECT_TRUE(std::isnan(recovered));
}

TEST_F(ToDataFloatTest_145, ReturnValueIsFourBytes_145) {
    float input = 123.456f;
    size_t resultLE = toData(buf, input, littleEndian);
    EXPECT_EQ(resultLE, 4u);
    size_t resultBE = toData(buf, input, bigEndian);
    EXPECT_EQ(resultBE, 4u);
}

TEST_F(ToDataFloatTest_145, DifferentByteOrdersProduceDifferentBytes_145) {
    float input = 1.5f;
    byte bufLE[4] = {};
    byte bufBE[4] = {};
    toData(bufLE, input, littleEndian);
    toData(bufBE, input, bigEndian);
    // For most non-zero values, LE and BE representations differ
    bool same = (std::memcmp(bufLE, bufBE, 4) == 0);
    EXPECT_FALSE(same);
}

TEST_F(ToDataFloatTest_145, ByteOrderReversal_145) {
    float input = 2.718f;
    byte bufLE[4] = {};
    byte bufBE[4] = {};
    toData(bufLE, input, littleEndian);
    toData(bufBE, input, bigEndian);
    // LE and BE should be byte-reversed versions of each other
    EXPECT_EQ(bufLE[0], bufBE[3]);
    EXPECT_EQ(bufLE[1], bufBE[2]);
    EXPECT_EQ(bufLE[2], bufBE[1]);
    EXPECT_EQ(bufLE[3], bufBE[0]);
}

TEST_F(ToDataFloatTest_145, SmallPositiveValueLittleEndian_145) {
    float input = 1.0e-30f;
    size_t result = toData(buf, input, littleEndian);
    EXPECT_EQ(result, 4u);
    float recovered = dataToFloat(buf, littleEndian);
    EXPECT_FLOAT_EQ(recovered, 1.0e-30f);
}

TEST_F(ToDataFloatTest_145, LargePositiveValueBigEndian_145) {
    float input = 1.0e30f;
    size_t result = toData(buf, input, bigEndian);
    EXPECT_EQ(result, 4u);
    float recovered = dataToFloat(buf, bigEndian);
    EXPECT_FLOAT_EQ(recovered, 1.0e30f);
}

TEST_F(ToDataFloatTest_145, NegativeZeroLittleEndian_145) {
    float input = -0.0f;
    size_t result = toData(buf, input, littleEndian);
    EXPECT_EQ(result, 4u);
    float recovered = dataToFloat(buf, littleEndian);
    EXPECT_FLOAT_EQ(recovered, 0.0f);
    // Check that the sign bit is preserved
    EXPECT_TRUE(std::signbit(recovered));
}

TEST_F(ToDataFloatTest_145, NegativeZeroBigEndian_145) {
    float input = -0.0f;
    size_t result = toData(buf, input, bigEndian);
    EXPECT_EQ(result, 4u);
    float recovered = dataToFloat(buf, bigEndian);
    EXPECT_FLOAT_EQ(recovered, 0.0f);
    EXPECT_TRUE(std::signbit(recovered));
}

TEST_F(ToDataFloatTest_145, EpsilonLittleEndian_145) {
    float input = std::numeric_limits<float>::epsilon();
    size_t result = toData(buf, input, littleEndian);
    EXPECT_EQ(result, 4u);
    float recovered = dataToFloat(buf, littleEndian);
    EXPECT_FLOAT_EQ(recovered, std::numeric_limits<float>::epsilon());
}

}  // namespace
