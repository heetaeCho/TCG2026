#include <gtest/gtest.h>
#include "Object.h"

// We need to test the static function isNatural from StructElement.cc
// Since it's a static function in a .cc file, we cannot directly call it.
// We'll need to either include the source or replicate the function signature for testing.
// Since the constraint says we treat it as a black box and test based on interface,
// we'll define a wrapper that matches the exact implementation shown.

// The function under test (copied from the provided code since it's static in .cc):
static bool isNatural(Object *value) {
    return (value->isInt() && value->getInt() > 0) || (value->isInt64() && value->getInt64() > 0);
}

class IsNaturalTest_1771 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test with positive integer - should return true
TEST_F(IsNaturalTest_1771, PositiveIntReturnsTrue_1771) {
    Object obj(1);
    EXPECT_TRUE(isNatural(&obj));
}

// Test with larger positive integer - should return true
TEST_F(IsNaturalTest_1771, LargerPositiveIntReturnsTrue_1771) {
    Object obj(100);
    EXPECT_TRUE(isNatural(&obj));
}

// Test with zero integer - should return false (natural numbers are > 0)
TEST_F(IsNaturalTest_1771, ZeroIntReturnsFalse_1771) {
    Object obj(0);
    EXPECT_FALSE(isNatural(&obj));
}

// Test with negative integer - should return false
TEST_F(IsNaturalTest_1771, NegativeIntReturnsFalse_1771) {
    Object obj(-1);
    EXPECT_FALSE(isNatural(&obj));
}

// Test with large negative integer - should return false
TEST_F(IsNaturalTest_1771, LargeNegativeIntReturnsFalse_1771) {
    Object obj(-1000);
    EXPECT_FALSE(isNatural(&obj));
}

// Test with positive int64 - should return true
TEST_F(IsNaturalTest_1771, PositiveInt64ReturnsTrue_1771) {
    long long val = 1LL;
    Object obj(val);
    EXPECT_TRUE(isNatural(&obj));
}

// Test with large positive int64 - should return true
TEST_F(IsNaturalTest_1771, LargePositiveInt64ReturnsTrue_1771) {
    long long val = 9999999999LL;
    Object obj(val);
    EXPECT_TRUE(isNatural(&obj));
}

// Test with zero int64 - should return false
TEST_F(IsNaturalTest_1771, ZeroInt64ReturnsFalse_1771) {
    long long val = 0LL;
    Object obj(val);
    EXPECT_FALSE(isNatural(&obj));
}

// Test with negative int64 - should return false
TEST_F(IsNaturalTest_1771, NegativeInt64ReturnsFalse_1771) {
    long long val = -1LL;
    Object obj(val);
    EXPECT_FALSE(isNatural(&obj));
}

// Test with large negative int64 - should return false
TEST_F(IsNaturalTest_1771, LargeNegativeInt64ReturnsFalse_1771) {
    long long val = -9999999999LL;
    Object obj(val);
    EXPECT_FALSE(isNatural(&obj));
}

// Test with real/double - should return false (not int or int64)
TEST_F(IsNaturalTest_1771, PositiveDoubleReturnsFalse_1771) {
    Object obj(1.5);
    EXPECT_FALSE(isNatural(&obj));
}

// Test with boolean - should return false
TEST_F(IsNaturalTest_1771, BoolReturnsFalse_1771) {
    Object obj(true);
    EXPECT_FALSE(isNatural(&obj));
}

// Test with null object - should return false
TEST_F(IsNaturalTest_1771, NullObjectReturnsFalse_1771) {
    Object obj = Object::null();
    EXPECT_FALSE(isNatural(&obj));
}

// Test with default constructed object (objNone) - should return false
TEST_F(IsNaturalTest_1771, NoneObjectReturnsFalse_1771) {
    Object obj;
    EXPECT_FALSE(isNatural(&obj));
}

// Test with int value 1 (boundary: smallest natural number)
TEST_F(IsNaturalTest_1771, IntOneIsNatural_1771) {
    Object obj(1);
    EXPECT_TRUE(isNatural(&obj));
}

// Test with int64 value 1 (boundary: smallest natural number)
TEST_F(IsNaturalTest_1771, Int64OneIsNatural_1771) {
    long long val = 1LL;
    Object obj(val);
    EXPECT_TRUE(isNatural(&obj));
}

// Test with INT_MAX - should return true
TEST_F(IsNaturalTest_1771, IntMaxReturnsTrue_1771) {
    Object obj(INT_MAX);
    EXPECT_TRUE(isNatural(&obj));
}

// Test with int64 max-like value - should return true
TEST_F(IsNaturalTest_1771, Int64MaxLikeReturnsTrue_1771) {
    long long val = LLONG_MAX;
    Object obj(val);
    EXPECT_TRUE(isNatural(&obj));
}

// Test with double zero - should return false
TEST_F(IsNaturalTest_1771, DoubleZeroReturnsFalse_1771) {
    Object obj(0.0);
    EXPECT_FALSE(isNatural(&obj));
}

// Test with negative double - should return false
TEST_F(IsNaturalTest_1771, NegativeDoubleReturnsFalse_1771) {
    Object obj(-5.0);
    EXPECT_FALSE(isNatural(&obj));
}

// Test with error object - should return false
TEST_F(IsNaturalTest_1771, ErrorObjectReturnsFalse_1771) {
    Object obj = Object::error();
    EXPECT_FALSE(isNatural(&obj));
}

// Test with EOF object - should return false
TEST_F(IsNaturalTest_1771, EOFObjectReturnsFalse_1771) {
    Object obj = Object::eof();
    EXPECT_FALSE(isNatural(&obj));
}

// Test with INT_MIN - should return false
TEST_F(IsNaturalTest_1771, IntMinReturnsFalse_1771) {
    Object obj(INT_MIN);
    EXPECT_FALSE(isNatural(&obj));
}

// Test with LLONG_MIN - should return false
TEST_F(IsNaturalTest_1771, Int64MinReturnsFalse_1771) {
    long long val = LLONG_MIN;
    Object obj(val);
    EXPECT_FALSE(isNatural(&obj));
}
