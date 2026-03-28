#include <gtest/gtest.h>
#include "Object.h"

// Test that getIntOrInt64 returns the correct value when Object holds an int
TEST(ObjectGetIntOrInt64Test_109, ReturnsIntValue_109) {
    Object obj(42);
    ASSERT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

// Test that getIntOrInt64 returns the correct value when Object holds a negative int
TEST(ObjectGetIntOrInt64Test_109, ReturnsNegativeIntValue_109) {
    Object obj(-100);
    ASSERT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getIntOrInt64(), -100LL);
}

// Test that getIntOrInt64 returns zero for int zero
TEST(ObjectGetIntOrInt64Test_109, ReturnsZeroIntValue_109) {
    Object obj(0);
    ASSERT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getIntOrInt64(), 0LL);
}

// Test that getIntOrInt64 returns the correct value when Object holds an int64
TEST(ObjectGetIntOrInt64Test_109, ReturnsInt64Value_109) {
    long long bigVal = 1LL << 40; // Value that doesn't fit in 32-bit int
    Object obj(bigVal);
    ASSERT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getIntOrInt64(), bigVal);
}

// Test that getIntOrInt64 returns the correct value for a negative int64
TEST(ObjectGetIntOrInt64Test_109, ReturnsNegativeInt64Value_109) {
    long long negBigVal = -(1LL << 40);
    Object obj(negBigVal);
    ASSERT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getIntOrInt64(), negBigVal);
}

// Test that getIntOrInt64 returns zero for int64 zero
TEST(ObjectGetIntOrInt64Test_109, ReturnsZeroInt64Value_109) {
    long long zeroVal = 0LL;
    Object obj(zeroVal);
    // Depending on implementation, 0LL might be stored as int or int64
    ASSERT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getIntOrInt64(), 0LL);
}

// Test that isIntOrInt64 returns true for int
TEST(ObjectGetIntOrInt64Test_109, IsIntOrInt64TrueForInt_109) {
    Object obj(7);
    EXPECT_TRUE(obj.isIntOrInt64());
}

// Test that isIntOrInt64 returns true for int64
TEST(ObjectGetIntOrInt64Test_109, IsIntOrInt64TrueForInt64_109) {
    long long val = 1LL << 50;
    Object obj(val);
    EXPECT_TRUE(obj.isIntOrInt64());
}

// Test that isIntOrInt64 returns false for other types
TEST(ObjectGetIntOrInt64Test_109, IsIntOrInt64FalseForReal_109) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// Test that isIntOrInt64 returns false for bool
TEST(ObjectGetIntOrInt64Test_109, IsIntOrInt64FalseForBool_109) {
    Object obj(true);
    EXPECT_FALSE(obj.isIntOrInt64());
}

// Test that isIntOrInt64 returns false for null
TEST(ObjectGetIntOrInt64Test_109, IsIntOrInt64FalseForNull_109) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isIntOrInt64());
}

// Test boundary: INT_MAX as int
TEST(ObjectGetIntOrInt64Test_109, IntMaxBoundary_109) {
    Object obj(INT_MAX);
    ASSERT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getIntOrInt64(), static_cast<long long>(INT_MAX));
}

// Test boundary: INT_MIN as int
TEST(ObjectGetIntOrInt64Test_109, IntMinBoundary_109) {
    Object obj(INT_MIN);
    ASSERT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getIntOrInt64(), static_cast<long long>(INT_MIN));
}

// Test boundary: LLONG_MAX as int64
TEST(ObjectGetIntOrInt64Test_109, Int64MaxBoundary_109) {
    long long maxVal = LLONG_MAX;
    Object obj(maxVal);
    ASSERT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getIntOrInt64(), maxVal);
}

// Test boundary: LLONG_MIN as int64
TEST(ObjectGetIntOrInt64Test_109, Int64MinBoundary_109) {
    long long minVal = LLONG_MIN;
    Object obj(minVal);
    ASSERT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getIntOrInt64(), minVal);
}

// Test that getInt works for an int object
TEST(ObjectGetIntOrInt64Test_109, GetIntConsistentWithGetIntOrInt64ForInt_109) {
    Object obj(123);
    ASSERT_TRUE(obj.isInt());
    EXPECT_EQ(static_cast<long long>(obj.getInt()), obj.getIntOrInt64());
}

// Test that getInt64 works for an int64 object
TEST(ObjectGetIntOrInt64Test_109, GetInt64ConsistentWithGetIntOrInt64ForInt64_109) {
    long long val = 9876543210LL;
    Object obj(val);
    ASSERT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), obj.getIntOrInt64());
}

// Test isInt and isInt64 are mutually exclusive for a large value
TEST(ObjectGetIntOrInt64Test_109, IsIntAndIsInt64MutuallyExclusiveForLargeValue_109) {
    long long val = 1LL << 40;
    Object obj(val);
    // Should be int64, not int
    EXPECT_TRUE(obj.isInt64());
    EXPECT_FALSE(obj.isInt());
    EXPECT_TRUE(obj.isIntOrInt64());
}

// Test isInt and isInt64 for a small value stored as int
TEST(ObjectGetIntOrInt64Test_109, SmallValueIsIntNotInt64_109) {
    Object obj(5);
    EXPECT_TRUE(obj.isInt());
    EXPECT_FALSE(obj.isInt64());
    EXPECT_TRUE(obj.isIntOrInt64());
}
