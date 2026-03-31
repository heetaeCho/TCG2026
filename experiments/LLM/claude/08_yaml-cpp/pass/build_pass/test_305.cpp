#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

using YAML::jkj::dragonbox::detail::wuint::uint128;

class Uint128PlusEqualsTest_305 : public ::testing::Test {
protected:
};

// Test adding zero to a zero-initialized uint128
TEST_F(Uint128PlusEqualsTest_305, AddZeroToZero_305) {
    uint128 val(0, 0);
    val += 0;
    EXPECT_EQ(val.high(), 0u);
    EXPECT_EQ(val.low(), 0u);
}

// Test adding a small value to zero
TEST_F(Uint128PlusEqualsTest_305, AddSmallValueToZero_305) {
    uint128 val(0, 0);
    val += 42;
    EXPECT_EQ(val.high(), 0u);
    EXPECT_EQ(val.low(), 42u);
}

// Test adding zero to a non-zero value
TEST_F(Uint128PlusEqualsTest_305, AddZeroToNonZero_305) {
    uint128 val(5, 100);
    val += 0;
    EXPECT_EQ(val.high(), 5u);
    EXPECT_EQ(val.low(), 100u);
}

// Test simple addition without carry
TEST_F(Uint128PlusEqualsTest_305, SimpleAdditionNoCarry_305) {
    uint128 val(0, 10);
    val += 20;
    EXPECT_EQ(val.high(), 0u);
    EXPECT_EQ(val.low(), 30u);
}

// Test addition that causes a carry from low to high
TEST_F(Uint128PlusEqualsTest_305, AdditionWithCarry_305) {
    uint128 val(0, UINT64_C(0xFFFFFFFFFFFFFFFF));
    val += 1;
    EXPECT_EQ(val.high(), 1u);
    EXPECT_EQ(val.low(), 0u);
}

// Test addition with carry when high is already non-zero
TEST_F(Uint128PlusEqualsTest_305, AdditionWithCarryNonZeroHigh_305) {
    uint128 val(10, UINT64_C(0xFFFFFFFFFFFFFFFF));
    val += 1;
    EXPECT_EQ(val.high(), 11u);
    EXPECT_EQ(val.low(), 0u);
}

// Test addition with carry adding more than 1
TEST_F(Uint128PlusEqualsTest_305, AdditionWithCarryLargerValue_305) {
    uint128 val(0, UINT64_C(0xFFFFFFFFFFFFFFFF));
    val += 10;
    EXPECT_EQ(val.high(), 1u);
    EXPECT_EQ(val.low(), 9u);
}

// Test adding max uint64 value to zero
TEST_F(Uint128PlusEqualsTest_305, AddMaxUint64ToZero_305) {
    uint128 val(0, 0);
    val += UINT64_C(0xFFFFFFFFFFFFFFFF);
    EXPECT_EQ(val.high(), 0u);
    EXPECT_EQ(val.low(), UINT64_C(0xFFFFFFFFFFFFFFFF));
}

// Test adding max uint64 to max uint64 in low (produces carry)
TEST_F(Uint128PlusEqualsTest_305, AddMaxUint64ToMaxLow_305) {
    uint128 val(0, UINT64_C(0xFFFFFFFFFFFFFFFF));
    val += UINT64_C(0xFFFFFFFFFFFFFFFF);
    EXPECT_EQ(val.high(), 1u);
    EXPECT_EQ(val.low(), UINT64_C(0xFFFFFFFFFFFFFFFE));
}

// Test carry propagation with max high value (overflow of 128-bit wraps high)
TEST_F(Uint128PlusEqualsTest_305, CarryWithMaxHigh_305) {
    uint128 val(UINT64_C(0xFFFFFFFFFFFFFFFF), UINT64_C(0xFFFFFFFFFFFFFFFF));
    val += 1;
    // high wraps around to 0 (overflow behavior)
    EXPECT_EQ(val.high(), 0u);
    EXPECT_EQ(val.low(), 0u);
}

// Test multiple sequential additions without carry
TEST_F(Uint128PlusEqualsTest_305, MultipleAdditionsNoCarry_305) {
    uint128 val(0, 0);
    val += 100;
    val += 200;
    val += 300;
    EXPECT_EQ(val.high(), 0u);
    EXPECT_EQ(val.low(), 600u);
}

// Test multiple additions that eventually cause a carry
TEST_F(Uint128PlusEqualsTest_305, MultipleAdditionsWithEventualCarry_305) {
    uint128 val(0, UINT64_C(0xFFFFFFFFFFFFFFF0));
    val += 8;
    EXPECT_EQ(val.high(), 0u);
    EXPECT_EQ(val.low(), UINT64_C(0xFFFFFFFFFFFFFFF8));
    val += 8;
    EXPECT_EQ(val.high(), 1u);
    EXPECT_EQ(val.low(), 0u);
}

// Test operator+= returns reference to self
TEST_F(Uint128PlusEqualsTest_305, ReturnsSelfReference_305) {
    uint128 val(0, 0);
    uint128& ref = (val += 5);
    EXPECT_EQ(&ref, &val);
    EXPECT_EQ(val.low(), 5u);
}

// Test chaining += operations
TEST_F(Uint128PlusEqualsTest_305, ChainingOperations_305) {
    uint128 val(0, 0);
    (val += 10) += 20;
    EXPECT_EQ(val.high(), 0u);
    EXPECT_EQ(val.low(), 30u);
}

// Test adding 1 to a value just below the carry boundary
TEST_F(Uint128PlusEqualsTest_305, JustBelowCarryBoundary_305) {
    uint128 val(0, UINT64_C(0xFFFFFFFFFFFFFFFE));
    val += 1;
    EXPECT_EQ(val.high(), 0u);
    EXPECT_EQ(val.low(), UINT64_C(0xFFFFFFFFFFFFFFFF));
}

// Test adding 2 to a value at the carry boundary
TEST_F(Uint128PlusEqualsTest_305, ExactlyAtCarryBoundary_305) {
    uint128 val(0, UINT64_C(0xFFFFFFFFFFFFFFFE));
    val += 2;
    EXPECT_EQ(val.high(), 1u);
    EXPECT_EQ(val.low(), 0u);
}

// Test with large high and addition that doesn't touch high
TEST_F(Uint128PlusEqualsTest_305, LargeHighNoCarry_305) {
    uint128 val(UINT64_C(0x123456789ABCDEF0), 5);
    val += 10;
    EXPECT_EQ(val.high(), UINT64_C(0x123456789ABCDEF0));
    EXPECT_EQ(val.low(), 15u);
}

// Test adding a power of 2
TEST_F(Uint128PlusEqualsTest_305, AddPowerOfTwo_305) {
    uint128 val(0, 0);
    val += UINT64_C(0x8000000000000000);
    EXPECT_EQ(val.high(), 0u);
    EXPECT_EQ(val.low(), UINT64_C(0x8000000000000000));
}

// Test carry with power of 2 values
TEST_F(Uint128PlusEqualsTest_305, CarryWithPowerOfTwo_305) {
    uint128 val(0, UINT64_C(0x8000000000000000));
    val += UINT64_C(0x8000000000000000);
    EXPECT_EQ(val.high(), 1u);
    EXPECT_EQ(val.low(), 0u);
}
