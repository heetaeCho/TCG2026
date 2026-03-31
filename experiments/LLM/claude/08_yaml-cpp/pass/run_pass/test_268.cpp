#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// Test ID: 268

// Test bit_cast with same-size integer types
TEST(BitCastTest_268, IntToUint_268) {
    int32_t source = 42;
    auto result = YAML::jkj::dragonbox::detail::bit_cast<uint32_t>(source);
    static_assert(sizeof(int32_t) == sizeof(uint32_t), "Size mismatch");
    EXPECT_EQ(result, static_cast<uint32_t>(42));
}

TEST(BitCastTest_268, NegativeIntToUint_268) {
    int32_t source = -1;
    auto result = YAML::jkj::dragonbox::detail::bit_cast<uint32_t>(source);
    EXPECT_EQ(result, 0xFFFFFFFFu);
}

TEST(BitCastTest_268, UintToInt_268) {
    uint32_t source = 0xFFFFFFFFu;
    auto result = YAML::jkj::dragonbox::detail::bit_cast<int32_t>(source);
    EXPECT_EQ(result, -1);
}

TEST(BitCastTest_268, FloatToUint32_268) {
    float source = 1.0f;
    auto result = YAML::jkj::dragonbox::detail::bit_cast<uint32_t>(source);
    // IEEE 754: 1.0f = 0x3F800000
    EXPECT_EQ(result, 0x3F800000u);
}

TEST(BitCastTest_268, Uint32ToFloat_268) {
    uint32_t source = 0x3F800000u;
    auto result = YAML::jkj::dragonbox::detail::bit_cast<float>(source);
    EXPECT_FLOAT_EQ(result, 1.0f);
}

TEST(BitCastTest_268, DoubleToUint64_268) {
    double source = 1.0;
    auto result = YAML::jkj::dragonbox::detail::bit_cast<uint64_t>(source);
    // IEEE 754: 1.0 = 0x3FF0000000000000
    EXPECT_EQ(result, 0x3FF0000000000000ull);
}

TEST(BitCastTest_268, Uint64ToDouble_268) {
    uint64_t source = 0x3FF0000000000000ull;
    auto result = YAML::jkj::dragonbox::detail::bit_cast<double>(source);
    EXPECT_DOUBLE_EQ(result, 1.0);
}

TEST(BitCastTest_268, FloatZero_268) {
    float source = 0.0f;
    auto result = YAML::jkj::dragonbox::detail::bit_cast<uint32_t>(source);
    EXPECT_EQ(result, 0u);
}

TEST(BitCastTest_268, FloatNegativeZero_268) {
    float source = -0.0f;
    auto result = YAML::jkj::dragonbox::detail::bit_cast<uint32_t>(source);
    EXPECT_EQ(result, 0x80000000u);
}

TEST(BitCastTest_268, DoubleZero_268) {
    double source = 0.0;
    auto result = YAML::jkj::dragonbox::detail::bit_cast<uint64_t>(source);
    EXPECT_EQ(result, 0ull);
}

TEST(BitCastTest_268, DoubleNegativeZero_268) {
    double source = -0.0;
    auto result = YAML::jkj::dragonbox::detail::bit_cast<uint64_t>(source);
    EXPECT_EQ(result, 0x8000000000000000ull);
}

TEST(BitCastTest_268, RoundTripFloat_268) {
    float original = 3.14159f;
    auto intermediate = YAML::jkj::dragonbox::detail::bit_cast<uint32_t>(original);
    auto result = YAML::jkj::dragonbox::detail::bit_cast<float>(intermediate);
    EXPECT_FLOAT_EQ(result, original);
}

TEST(BitCastTest_268, RoundTripDouble_268) {
    double original = 3.141592653589793;
    auto intermediate = YAML::jkj::dragonbox::detail::bit_cast<uint64_t>(original);
    auto result = YAML::jkj::dragonbox::detail::bit_cast<double>(intermediate);
    EXPECT_DOUBLE_EQ(result, original);
}

TEST(BitCastTest_268, Int64ToUint64_268) {
    int64_t source = -12345678901234LL;
    auto result = YAML::jkj::dragonbox::detail::bit_cast<uint64_t>(source);
    auto back = YAML::jkj::dragonbox::detail::bit_cast<int64_t>(result);
    EXPECT_EQ(back, source);
}

TEST(BitCastTest_268, ZeroIntToUint_268) {
    int32_t source = 0;
    auto result = YAML::jkj::dragonbox::detail::bit_cast<uint32_t>(source);
    EXPECT_EQ(result, 0u);
}

TEST(BitCastTest_268, MaxIntToUint_268) {
    int32_t source = INT32_MAX;
    auto result = YAML::jkj::dragonbox::detail::bit_cast<uint32_t>(source);
    EXPECT_EQ(result, static_cast<uint32_t>(INT32_MAX));
}

TEST(BitCastTest_268, MinIntToUint_268) {
    int32_t source = INT32_MIN;
    auto result = YAML::jkj::dragonbox::detail::bit_cast<uint32_t>(source);
    EXPECT_EQ(result, 0x80000000u);
}

TEST(BitCastTest_268, FloatInfinity_268) {
    float source = std::numeric_limits<float>::infinity();
    auto result = YAML::jkj::dragonbox::detail::bit_cast<uint32_t>(source);
    EXPECT_EQ(result, 0x7F800000u);
}

TEST(BitCastTest_268, FloatNegativeInfinity_268) {
    float source = -std::numeric_limits<float>::infinity();
    auto result = YAML::jkj::dragonbox::detail::bit_cast<uint32_t>(source);
    EXPECT_EQ(result, 0xFF800000u);
}

TEST(BitCastTest_268, FloatNaN_268) {
    float source = std::numeric_limits<float>::quiet_NaN();
    auto result = YAML::jkj::dragonbox::detail::bit_cast<uint32_t>(source);
    // NaN has exponent bits all 1 and non-zero mantissa
    EXPECT_EQ(result & 0x7F800000u, 0x7F800000u);  // exponent all 1s
    EXPECT_NE(result & 0x007FFFFFu, 0u);            // mantissa non-zero
}

TEST(BitCastTest_268, DoubleInfinity_268) {
    double source = std::numeric_limits<double>::infinity();
    auto result = YAML::jkj::dragonbox::detail::bit_cast<uint64_t>(source);
    EXPECT_EQ(result, 0x7FF0000000000000ull);
}

TEST(BitCastTest_268, CharArrayRoundTrip_268) {
    // Test with a struct of the same size
    struct FourBytes {
        char data[4];
    };
    static_assert(sizeof(FourBytes) == sizeof(uint32_t), "Size mismatch");

    uint32_t source = 0x01020304u;
    auto result = YAML::jkj::dragonbox::detail::bit_cast<FourBytes>(source);
    auto back = YAML::jkj::dragonbox::detail::bit_cast<uint32_t>(result);
    EXPECT_EQ(back, source);
}

TEST(BitCastTest_268, IdentityBitCastUint32_268) {
    uint32_t source = 0xDEADBEEFu;
    auto result = YAML::jkj::dragonbox::detail::bit_cast<uint32_t>(source);
    EXPECT_EQ(result, source);
}

TEST(BitCastTest_268, IdentityBitCastDouble_268) {
    double source = 2.718281828;
    auto result = YAML::jkj::dragonbox::detail::bit_cast<double>(source);
    EXPECT_DOUBLE_EQ(result, source);
}

TEST(BitCastTest_268, SmallestPositiveFloat_268) {
    float source = std::numeric_limits<float>::denorm_min();
    auto result = YAML::jkj::dragonbox::detail::bit_cast<uint32_t>(source);
    EXPECT_EQ(result, 1u);  // smallest denormalized float is 0x00000001
}

TEST(BitCastTest_268, LargestFloat_268) {
    float source = std::numeric_limits<float>::max();
    auto result = YAML::jkj::dragonbox::detail::bit_cast<uint32_t>(source);
    EXPECT_EQ(result, 0x7F7FFFFFu);
}

}  // namespace
