#include <gtest/gtest.h>
#include <cstdint>
#include <limits>

// Include the header under test
#include "contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox;

// For float: significand_bits = 23, total_bits = 32, carrier_uint = uint32_t
// For double: significand_bits = 52, total_bits = 64, carrier_uint = uint64_t

using uint128 = detail::wuint::uint128;

// Test fixture for dragonbox compute_left_endpoint tests
class DragonboxComputeLeftEndpoint_401 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that uint128 construction and accessors work correctly
TEST_F(DragonboxComputeLeftEndpoint_401, Uint128ConstructionAndAccess_401) {
    uint128 val(0x1234567890ABCDEFull, 0xFEDCBA0987654321ull);
    EXPECT_EQ(val.high(), 0x1234567890ABCDEFull);
    EXPECT_EQ(val.low(), 0xFEDCBA0987654321ull);
}

TEST_F(DragonboxComputeLeftEndpoint_401, Uint128DefaultConstruction_401) {
    uint128 val{};
    // Default constructed - values may be indeterminate, just verify it compiles
    (void)val.high();
    (void)val.low();
}

TEST_F(DragonboxComputeLeftEndpoint_401, Uint128ZeroValues_401) {
    uint128 val(0, 0);
    EXPECT_EQ(val.high(), 0u);
    EXPECT_EQ(val.low(), 0u);
}

TEST_F(DragonboxComputeLeftEndpoint_401, Uint128MaxValues_401) {
    uint128 val(UINT64_MAX, UINT64_MAX);
    EXPECT_EQ(val.high(), UINT64_MAX);
    EXPECT_EQ(val.low(), UINT64_MAX);
}

TEST_F(DragonboxComputeLeftEndpoint_401, Uint128PlusEqualsBasic_401) {
    uint128 val(0, 5);
    val += 10;
    EXPECT_EQ(val.low(), 15u);
    EXPECT_EQ(val.high(), 0u);
}

TEST_F(DragonboxComputeLeftEndpoint_401, Uint128PlusEqualsOverflow_401) {
    uint128 val(0, UINT64_MAX);
    val += 1;
    EXPECT_EQ(val.low(), 0u);
    EXPECT_EQ(val.high(), 1u);
}

TEST_F(DragonboxComputeLeftEndpoint_401, Uint128PlusEqualsZero_401) {
    uint128 val(42, 100);
    val += 0;
    EXPECT_EQ(val.high(), 42u);
    EXPECT_EQ(val.low(), 100u);
}

// Test the main dragonbox conversion for float values
TEST_F(DragonboxComputeLeftEndpoint_401, ToDecimalFloatPositiveNormal_401) {
    float f = 1.0f;
    auto result = to_decimal(f);
    EXPECT_GT(result.significand, 0u);
    EXPECT_FALSE(result.is_negative);
}

TEST_F(DragonboxComputeLeftEndpoint_401, ToDecimalFloatNegative_401) {
    float f = -1.0f;
    auto result = to_decimal(f);
    EXPECT_TRUE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxComputeLeftEndpoint_401, ToDecimalFloatSmallValue_401) {
    float f = 1.175494e-38f; // near smallest normal float
    auto result = to_decimal(f);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxComputeLeftEndpoint_401, ToDecimalDoublePositiveNormal_401) {
    double d = 1.0;
    auto result = to_decimal(d);
    EXPECT_GT(result.significand, 0u);
    EXPECT_FALSE(result.is_negative);
}

TEST_F(DragonboxComputeLeftEndpoint_401, ToDecimalDoubleNegative_401) {
    double d = -3.14;
    auto result = to_decimal(d);
    EXPECT_TRUE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxComputeLeftEndpoint_401, ToDecimalFloatPointFive_401) {
    float f = 0.5f;
    auto result = to_decimal(f);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxComputeLeftEndpoint_401, ToDecimalDoublePointFive_401) {
    double d = 0.5;
    auto result = to_decimal(d);
    EXPECT_FALSE(result.is_negative);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxComputeLeftEndpoint_401, ToDecimalFloatLargeValue_401) {
    float f = 3.402823e+38f; // near max float
    auto result = to_decimal(f);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxComputeLeftEndpoint_401, ToDecimalDoubleLargeValue_401) {
    double d = 1.7976931348623157e+308; // near max double
    auto result = to_decimal(d);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxComputeLeftEndpoint_401, ToDecimalFloatDenormalized_401) {
    float f = 1.4e-45f; // smallest denorm float
    auto result = to_decimal(f);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxComputeLeftEndpoint_401, ToDecimalDoubleDenormalized_401) {
    double d = 5e-324; // smallest denorm double
    auto result = to_decimal(d);
    EXPECT_GT(result.significand, 0u);
}

TEST_F(DragonboxComputeLeftEndpoint_401, ToDecimalFloatConsistency_401) {
    // The same value should produce the same result
    float f = 2.718281828f;
    auto r1 = to_decimal(f);
    auto r2 = to_decimal(f);
    EXPECT_EQ(r1.significand, r2.significand);
    EXPECT_EQ(r1.exponent, r2.exponent);
    EXPECT_EQ(r1.is_negative, r2.is_negative);
}

TEST_F(DragonboxComputeLeftEndpoint_401, ToDecimalDoubleConsistency_401) {
    double d = 3.141592653589793;
    auto r1 = to_decimal(d);
    auto r2 = to_decimal(d);
    EXPECT_EQ(r1.significand, r2.significand);
    EXPECT_EQ(r1.exponent, r2.exponent);
    EXPECT_EQ(r1.is_negative, r2.is_negative);
}

TEST_F(DragonboxComputeLeftEndpoint_401, ToDecimalFloatOne_401) {
    float f = 1.0f;
    auto result = to_decimal(f);
    // 1.0 should be representable as significand * 10^exponent = 1
    // Typically significand=1, exponent=0
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
}

TEST_F(DragonboxComputeLeftEndpoint_401, ToDecimalDoubleOne_401) {
    double d = 1.0;
    auto result = to_decimal(d);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
}

TEST_F(DragonboxComputeLeftEndpoint_401, ToDecimalFloatTen_401) {
    float f = 10.0f;
    auto result = to_decimal(f);
    // 10.0 = 1 * 10^1
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 1);
}

TEST_F(DragonboxComputeLeftEndpoint_401, ToDecimalDoublePointOne_401) {
    double d = 0.1;
    auto result = to_decimal(d);
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, -1);
}

TEST_F(DragonboxComputeLeftEndpoint_401, Uint128PlusEqualsLargeAddition_401) {
    uint128 val(0, UINT64_MAX - 10);
    val += 20;
    EXPECT_EQ(val.low(), 9u);
    EXPECT_EQ(val.high(), 1u);
}

TEST_F(DragonboxComputeLeftEndpoint_401, Uint128HighOnlyValue_401) {
    uint128 val(UINT64_MAX, 0);
    EXPECT_EQ(val.high(), UINT64_MAX);
    EXPECT_EQ(val.low(), 0u);
}

} // namespace
