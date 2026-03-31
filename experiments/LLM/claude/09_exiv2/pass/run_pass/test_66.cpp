#include <gtest/gtest.h>
#include <stdexcept>
#include <limits>
#include <cstdint>

// Include the header under test
#include "safe_op.hpp"

// ============================================================================
// Tests for Safe::add with int type
// ============================================================================

class SafeAddIntTest_66 : public ::testing::Test {};

TEST_F(SafeAddIntTest_66, AddTwoPositiveInts_66) {
    EXPECT_EQ(Safe::add(3, 4), 7);
}

TEST_F(SafeAddIntTest_66, AddTwoNegativeInts_66) {
    EXPECT_EQ(Safe::add(-3, -4), -7);
}

TEST_F(SafeAddIntTest_66, AddPositiveAndNegative_66) {
    EXPECT_EQ(Safe::add(10, -3), 7);
}

TEST_F(SafeAddIntTest_66, AddNegativeAndPositive_66) {
    EXPECT_EQ(Safe::add(-10, 3), -7);
}

TEST_F(SafeAddIntTest_66, AddZeroAndZero_66) {
    EXPECT_EQ(Safe::add(0, 0), 0);
}

TEST_F(SafeAddIntTest_66, AddZeroAndPositive_66) {
    EXPECT_EQ(Safe::add(0, 42), 42);
}

TEST_F(SafeAddIntTest_66, AddPositiveAndZero_66) {
    EXPECT_EQ(Safe::add(42, 0), 42);
}

TEST_F(SafeAddIntTest_66, AddZeroAndNegative_66) {
    EXPECT_EQ(Safe::add(0, -42), -42);
}

TEST_F(SafeAddIntTest_66, AddNegativeAndZero_66) {
    EXPECT_EQ(Safe::add(-42, 0), -42);
}

TEST_F(SafeAddIntTest_66, OverflowMaxPlusOne_66) {
    EXPECT_THROW(Safe::add(std::numeric_limits<int>::max(), 1), std::overflow_error);
}

TEST_F(SafeAddIntTest_66, OverflowMaxPlusMax_66) {
    EXPECT_THROW(Safe::add(std::numeric_limits<int>::max(), std::numeric_limits<int>::max()), std::overflow_error);
}

TEST_F(SafeAddIntTest_66, UnderflowMinMinusOne_66) {
    EXPECT_THROW(Safe::add(std::numeric_limits<int>::min(), -1), std::overflow_error);
}

TEST_F(SafeAddIntTest_66, UnderflowMinMinusMin_66) {
    EXPECT_THROW(Safe::add(std::numeric_limits<int>::min(), std::numeric_limits<int>::min()), std::overflow_error);
}

TEST_F(SafeAddIntTest_66, MaxPlusZeroNoOverflow_66) {
    EXPECT_EQ(Safe::add(std::numeric_limits<int>::max(), 0), std::numeric_limits<int>::max());
}

TEST_F(SafeAddIntTest_66, MinPlusZeroNoOverflow_66) {
    EXPECT_EQ(Safe::add(std::numeric_limits<int>::min(), 0), std::numeric_limits<int>::min());
}

TEST_F(SafeAddIntTest_66, MaxPlusMinNoOverflow_66) {
    EXPECT_EQ(Safe::add(std::numeric_limits<int>::max(), std::numeric_limits<int>::min()), -1);
}

TEST_F(SafeAddIntTest_66, MinPlusMaxNoOverflow_66) {
    EXPECT_EQ(Safe::add(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()), -1);
}

TEST_F(SafeAddIntTest_66, BoundaryMaxMinusOnePlusOne_66) {
    EXPECT_EQ(Safe::add(std::numeric_limits<int>::max() - 1, 1), std::numeric_limits<int>::max());
}

TEST_F(SafeAddIntTest_66, BoundaryMinPlusOnePlusNegOne_66) {
    EXPECT_EQ(Safe::add(std::numeric_limits<int>::min() + 1, -1), std::numeric_limits<int>::min());
}

// ============================================================================
// Tests for Safe::add with long type
// ============================================================================

class SafeAddLongTest_66 : public ::testing::Test {};

TEST_F(SafeAddLongTest_66, AddTwoPositiveLongs_66) {
    EXPECT_EQ(Safe::add(3L, 4L), 7L);
}

TEST_F(SafeAddLongTest_66, OverflowLongMax_66) {
    EXPECT_THROW(Safe::add(std::numeric_limits<long>::max(), 1L), std::overflow_error);
}

TEST_F(SafeAddLongTest_66, UnderflowLongMin_66) {
    EXPECT_THROW(Safe::add(std::numeric_limits<long>::min(), -1L), std::overflow_error);
}

TEST_F(SafeAddLongTest_66, LongMaxPlusZero_66) {
    EXPECT_EQ(Safe::add(std::numeric_limits<long>::max(), 0L), std::numeric_limits<long>::max());
}

// ============================================================================
// Tests for Safe::add with long long type
// ============================================================================

class SafeAddLongLongTest_66 : public ::testing::Test {};

TEST_F(SafeAddLongLongTest_66, AddTwoPositive_66) {
    EXPECT_EQ(Safe::add(100LL, 200LL), 300LL);
}

TEST_F(SafeAddLongLongTest_66, OverflowLongLongMax_66) {
    EXPECT_THROW(Safe::add(std::numeric_limits<long long>::max(), 1LL), std::overflow_error);
}

TEST_F(SafeAddLongLongTest_66, UnderflowLongLongMin_66) {
    EXPECT_THROW(Safe::add(std::numeric_limits<long long>::min(), -1LL), std::overflow_error);
}

TEST_F(SafeAddLongLongTest_66, MaxPlusMinNoOverflow_66) {
    EXPECT_EQ(Safe::add(std::numeric_limits<long long>::max(), std::numeric_limits<long long>::min()), -1LL);
}

// ============================================================================
// Tests for Safe::add with unsigned int type
// ============================================================================

class SafeAddUnsignedTest_66 : public ::testing::Test {};

TEST_F(SafeAddUnsignedTest_66, AddTwoPositive_66) {
    EXPECT_EQ(Safe::add(3u, 4u), 7u);
}

TEST_F(SafeAddUnsignedTest_66, AddZeros_66) {
    EXPECT_EQ(Safe::add(0u, 0u), 0u);
}

TEST_F(SafeAddUnsignedTest_66, OverflowUnsignedMax_66) {
    EXPECT_THROW(Safe::add(std::numeric_limits<unsigned int>::max(), 1u), std::overflow_error);
}

TEST_F(SafeAddUnsignedTest_66, MaxPlusZeroNoOverflow_66) {
    EXPECT_EQ(Safe::add(std::numeric_limits<unsigned int>::max(), 0u), std::numeric_limits<unsigned int>::max());
}

TEST_F(SafeAddUnsignedTest_66, BoundaryMaxMinusOnePlusOne_66) {
    EXPECT_EQ(Safe::add(std::numeric_limits<unsigned int>::max() - 1u, 1u), std::numeric_limits<unsigned int>::max());
}

TEST_F(SafeAddUnsignedTest_66, OverflowMaxPlusMax_66) {
    EXPECT_THROW(Safe::add(std::numeric_limits<unsigned int>::max(), std::numeric_limits<unsigned int>::max()), std::overflow_error);
}

// ============================================================================
// Tests for Safe::add with unsigned long long type
// ============================================================================

class SafeAddULongLongTest_66 : public ::testing::Test {};

TEST_F(SafeAddULongLongTest_66, AddTwoPositive_66) {
    EXPECT_EQ(Safe::add(100ULL, 200ULL), 300ULL);
}

TEST_F(SafeAddULongLongTest_66, OverflowMax_66) {
    EXPECT_THROW(Safe::add(std::numeric_limits<unsigned long long>::max(), 1ULL), std::overflow_error);
}

TEST_F(SafeAddULongLongTest_66, MaxPlusZero_66) {
    EXPECT_EQ(Safe::add(std::numeric_limits<unsigned long long>::max(), 0ULL), std::numeric_limits<unsigned long long>::max());
}

// ============================================================================
// Tests for Safe::add with int8_t (small type, easy to overflow)
// ============================================================================

class SafeAddInt8Test_66 : public ::testing::Test {};

TEST_F(SafeAddInt8Test_66, AddSmallValues_66) {
    EXPECT_EQ(Safe::add<int8_t>(10, 20), static_cast<int8_t>(30));
}

TEST_F(SafeAddInt8Test_66, OverflowInt8Max_66) {
    EXPECT_THROW(Safe::add<int8_t>(127, 1), std::overflow_error);
}

TEST_F(SafeAddInt8Test_66, UnderflowInt8Min_66) {
    EXPECT_THROW(Safe::add<int8_t>(-128, -1), std::overflow_error);
}

TEST_F(SafeAddInt8Test_66, BoundaryNoOverflow_66) {
    EXPECT_EQ(Safe::add<int8_t>(126, 1), static_cast<int8_t>(127));
}

TEST_F(SafeAddInt8Test_66, BoundaryNoUnderflow_66) {
    EXPECT_EQ(Safe::add<int8_t>(-127, -1), static_cast<int8_t>(-128));
}

// ============================================================================
// Tests for Safe::add with uint8_t
// ============================================================================

class SafeAddUInt8Test_66 : public ::testing::Test {};

TEST_F(SafeAddUInt8Test_66, AddSmallValues_66) {
    EXPECT_EQ(Safe::add<uint8_t>(10, 20), static_cast<uint8_t>(30));
}

TEST_F(SafeAddUInt8Test_66, OverflowUInt8Max_66) {
    EXPECT_THROW(Safe::add<uint8_t>(255, 1), std::overflow_error);
}

TEST_F(SafeAddUInt8Test_66, BoundaryNoOverflow_66) {
    EXPECT_EQ(Safe::add<uint8_t>(254, 1), static_cast<uint8_t>(255));
}

TEST_F(SafeAddUInt8Test_66, AddZeros_66) {
    EXPECT_EQ(Safe::add<uint8_t>(0, 0), static_cast<uint8_t>(0));
}

// ============================================================================
// Tests for Safe::add with int16_t
// ============================================================================

class SafeAddInt16Test_66 : public ::testing::Test {};

TEST_F(SafeAddInt16Test_66, AddNormalValues_66) {
    EXPECT_EQ(Safe::add<int16_t>(1000, 2000), static_cast<int16_t>(3000));
}

TEST_F(SafeAddInt16Test_66, OverflowInt16Max_66) {
    EXPECT_THROW(Safe::add<int16_t>(32767, 1), std::overflow_error);
}

TEST_F(SafeAddInt16Test_66, UnderflowInt16Min_66) {
    EXPECT_THROW(Safe::add<int16_t>(-32768, -1), std::overflow_error);
}

// ============================================================================
// Verify exception message
// ============================================================================

class SafeAddExceptionMessageTest_66 : public ::testing::Test {};

TEST_F(SafeAddExceptionMessageTest_66, OverflowExceptionMessage_66) {
    try {
        Safe::add(std::numeric_limits<int>::max(), 1);
        FAIL() << "Expected std::overflow_error";
    } catch (const std::overflow_error& e) {
        EXPECT_STREQ(e.what(), "Overflow in addition");
    } catch (...) {
        FAIL() << "Expected std::overflow_error, got different exception";
    }
}

TEST_F(SafeAddExceptionMessageTest_66, UnderflowExceptionMessage_66) {
    try {
        Safe::add(std::numeric_limits<int>::min(), -1);
        FAIL() << "Expected std::overflow_error";
    } catch (const std::overflow_error& e) {
        EXPECT_STREQ(e.what(), "Overflow in addition");
    } catch (...) {
        FAIL() << "Expected std::overflow_error, got different exception";
    }
}

// ============================================================================
// Commutativity tests
// ============================================================================

class SafeAddCommutativityTest_66 : public ::testing::Test {};

TEST_F(SafeAddCommutativityTest_66, CommutativeInt_66) {
    EXPECT_EQ(Safe::add(3, 5), Safe::add(5, 3));
}

TEST_F(SafeAddCommutativityTest_66, CommutativeWithNegative_66) {
    EXPECT_EQ(Safe::add(-10, 7), Safe::add(7, -10));
}

TEST_F(SafeAddCommutativityTest_66, CommutativeUnsigned_66) {
    EXPECT_EQ(Safe::add(100u, 200u), Safe::add(200u, 100u));
}

// ============================================================================
// Identity element tests
// ============================================================================

class SafeAddIdentityTest_66 : public ::testing::Test {};

TEST_F(SafeAddIdentityTest_66, IdentityInt_66) {
    for (int val : {-1000, -1, 0, 1, 1000}) {
        EXPECT_EQ(Safe::add(val, 0), val);
        EXPECT_EQ(Safe::add(0, val), val);
    }
}

TEST_F(SafeAddIdentityTest_66, IdentityUnsigned_66) {
    for (unsigned val : {0u, 1u, 1000u}) {
        EXPECT_EQ(Safe::add(val, 0u), val);
        EXPECT_EQ(Safe::add(0u, val), val);
    }
}

// ============================================================================
// Large value no overflow tests
// ============================================================================

class SafeAddLargeValueTest_66 : public ::testing::Test {};

TEST_F(SafeAddLargeValueTest_66, LargePositiveAndLargeNegativeNoOverflow_66) {
    int large_pos = std::numeric_limits<int>::max() / 2;
    int large_neg = -(std::numeric_limits<int>::max() / 2);
    EXPECT_EQ(Safe::add(large_pos, large_neg), 0);
}

TEST_F(SafeAddLargeValueTest_66, TwoLargePositivesOverflow_66) {
    int half_max = std::numeric_limits<int>::max() / 2 + 1;
    EXPECT_THROW(Safe::add(half_max, half_max), std::overflow_error);
}
