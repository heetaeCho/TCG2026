#include <gtest/gtest.h>
#include <limits>
#include <cstdint>
#include "GooCheckedOps.h"

// Test checkedAssign with int target type - normal values
TEST(CheckedAssignTest_2, NormalIntValue_2) {
    int z = 0;
    bool overflow = checkedAssign<int>(42LL, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, 42);
}

TEST(CheckedAssignTest_2, ZeroValue_2) {
    int z = -1;
    bool overflow = checkedAssign<int>(0LL, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, 0);
}

TEST(CheckedAssignTest_2, NegativeIntValue_2) {
    int z = 0;
    bool overflow = checkedAssign<int>(-100LL, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, -100);
}

// Boundary: max of int
TEST(CheckedAssignTest_2, IntMaxBoundary_2) {
    int z = 0;
    long long maxInt = static_cast<long long>(std::numeric_limits<int>::max());
    
    bool overflow = checkedAssign<int>(maxInt, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, std::numeric_limits<int>::max());
}

// Boundary: max of int + 1 (overflow)
TEST(CheckedAssignTest_2, IntMaxPlusOneOverflow_2) {
    int z = 0;
    long long overMax = static_cast<long long>(std::numeric_limits<int>::max()) + 1LL;
    
    bool overflow = checkedAssign<int>(overMax, &z);
    EXPECT_TRUE(overflow);
}

// Boundary: min of int
TEST(CheckedAssignTest_2, IntMinBoundary_2) {
    int z = 0;
    long long minInt = static_cast<long long>(std::numeric_limits<int>::min());
    
    bool overflow = checkedAssign<int>(minInt, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, std::numeric_limits<int>::min());
}

// Boundary: min of int - 1 (underflow)
TEST(CheckedAssignTest_2, IntMinMinusOneUnderflow_2) {
    int z = 0;
    long long underMin = static_cast<long long>(std::numeric_limits<int>::min()) - 1LL;
    
    bool overflow = checkedAssign<int>(underMin, &z);
    EXPECT_TRUE(overflow);
}

// Test with short target type - normal value
TEST(CheckedAssignTest_2, NormalShortValue_2) {
    short z = 0;
    bool overflow = checkedAssign<short>(100LL, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, 100);
}

// Test with short - max boundary
TEST(CheckedAssignTest_2, ShortMaxBoundary_2) {
    short z = 0;
    long long maxShort = static_cast<long long>(std::numeric_limits<short>::max());
    
    bool overflow = checkedAssign<short>(maxShort, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, std::numeric_limits<short>::max());
}

// Test with short - overflow
TEST(CheckedAssignTest_2, ShortMaxPlusOneOverflow_2) {
    short z = 0;
    long long overMax = static_cast<long long>(std::numeric_limits<short>::max()) + 1LL;
    
    bool overflow = checkedAssign<short>(overMax, &z);
    EXPECT_TRUE(overflow);
}

// Test with short - min boundary
TEST(CheckedAssignTest_2, ShortMinBoundary_2) {
    short z = 0;
    long long minShort = static_cast<long long>(std::numeric_limits<short>::min());
    
    bool overflow = checkedAssign<short>(minShort, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, std::numeric_limits<short>::min());
}

// Test with short - underflow
TEST(CheckedAssignTest_2, ShortMinMinusOneUnderflow_2) {
    short z = 0;
    long long underMin = static_cast<long long>(std::numeric_limits<short>::min()) - 1LL;
    
    bool overflow = checkedAssign<short>(underMin, &z);
    EXPECT_TRUE(overflow);
}

// Test with char (signed char) target type
TEST(CheckedAssignTest_2, NormalCharValue_2) {
    signed char z = 0;
    bool overflow = checkedAssign<signed char>(50LL, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, 50);
}

TEST(CheckedAssignTest_2, CharMaxBoundary_2) {
    signed char z = 0;
    long long maxChar = static_cast<long long>(std::numeric_limits<signed char>::max());
    
    bool overflow = checkedAssign<signed char>(maxChar, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, std::numeric_limits<signed char>::max());
}

TEST(CheckedAssignTest_2, CharOverflow_2) {
    signed char z = 0;
    long long overMax = static_cast<long long>(std::numeric_limits<signed char>::max()) + 1LL;
    
    bool overflow = checkedAssign<signed char>(overMax, &z);
    EXPECT_TRUE(overflow);
}

TEST(CheckedAssignTest_2, CharMinBoundary_2) {
    signed char z = 0;
    long long minChar = static_cast<long long>(std::numeric_limits<signed char>::min());
    
    bool overflow = checkedAssign<signed char>(minChar, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, std::numeric_limits<signed char>::min());
}

TEST(CheckedAssignTest_2, CharUnderflow_2) {
    signed char z = 0;
    long long underMin = static_cast<long long>(std::numeric_limits<signed char>::min()) - 1LL;
    
    bool overflow = checkedAssign<signed char>(underMin, &z);
    EXPECT_TRUE(overflow);
}

// Test with large long long values
TEST(CheckedAssignTest_2, LargeLongLongOverflowForInt_2) {
    int z = 0;
    bool overflow = checkedAssign<int>(std::numeric_limits<long long>::max(), &z);
    EXPECT_TRUE(overflow);
}

TEST(CheckedAssignTest_2, LargeNegativeLongLongUnderflowForInt_2) {
    int z = 0;
    bool overflow = checkedAssign<int>(std::numeric_limits<long long>::min(), &z);
    EXPECT_TRUE(overflow);
}

// Test that z is not modified on overflow
TEST(CheckedAssignTest_2, ValueUnchangedOnOverflow_2) {
    int z = 12345;
    int original = z;
    bool overflow = checkedAssign<int>(static_cast<long long>(std::numeric_limits<int>::max()) + 1LL, &z);
    EXPECT_TRUE(overflow);
    // z should remain unchanged when overflow occurs
    EXPECT_EQ(z, original);
}

TEST(CheckedAssignTest_2, ValueUnchangedOnUnderflow_2) {
    int z = 12345;
    int original = z;
    bool overflow = checkedAssign<int>(static_cast<long long>(std::numeric_limits<int>::min()) - 1LL, &z);
    EXPECT_TRUE(overflow);
    EXPECT_EQ(z, original);
}

// Test with int32_t
TEST(CheckedAssignTest_2, Int32Normal_2) {
    int32_t z = 0;
    bool overflow = checkedAssign<int32_t>(1000000LL, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, 1000000);
}

TEST(CheckedAssignTest_2, Int32MaxBoundary_2) {
    int32_t z = 0;
    long long maxVal = static_cast<long long>(std::numeric_limits<int32_t>::max());
    bool overflow = checkedAssign<int32_t>(maxVal, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, std::numeric_limits<int32_t>::max());
}

TEST(CheckedAssignTest_2, Int32Overflow_2) {
    int32_t z = 0;
    long long overVal = static_cast<long long>(std::numeric_limits<int32_t>::max()) + 1LL;
    bool overflow = checkedAssign<int32_t>(overVal, &z);
    EXPECT_TRUE(overflow);
}

// Test positive value just within range
TEST(CheckedAssignTest_2, OneWithinRange_2) {
    int z = 0;
    bool overflow = checkedAssign<int>(1LL, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, 1);
}

// Test negative one
TEST(CheckedAssignTest_2, NegativeOneWithinRange_2) {
    int z = 0;
    bool overflow = checkedAssign<int>(-1LL, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, -1);
}

// Test with int16_t explicitly
TEST(CheckedAssignTest_2, Int16Normal_2) {
    int16_t z = 0;
    bool overflow = checkedAssign<int16_t>(32000LL, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, 32000);
}

TEST(CheckedAssignTest_2, Int16MaxOverflow_2) {
    int16_t z = 0;
    bool overflow = checkedAssign<int16_t>(32768LL, &z);
    EXPECT_TRUE(overflow);
}

TEST(CheckedAssignTest_2, Int16MinBoundary_2) {
    int16_t z = 0;
    bool overflow = checkedAssign<int16_t>(-32768LL, &z);
    EXPECT_FALSE(overflow);
    EXPECT_EQ(z, -32768);
}

TEST(CheckedAssignTest_2, Int16MinUnderflow_2) {
    int16_t z = 0;
    bool overflow = checkedAssign<int16_t>(-32769LL, &z);
    EXPECT_TRUE(overflow);
}
