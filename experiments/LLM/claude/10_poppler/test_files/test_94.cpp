#include <gtest/gtest.h>
#include "Object.h"

// Test getNum() with an int Object
TEST(ObjectGetNumTest_94, IntReturnsDouble_94) {
    Object obj(42);
    ASSERT_TRUE(obj.isInt());
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

// Test getNum() with a negative int
TEST(ObjectGetNumTest_94, NegativeIntReturnsDouble_94) {
    Object obj(-100);
    ASSERT_TRUE(obj.isInt());
    EXPECT_DOUBLE_EQ(obj.getNum(), -100.0);
}

// Test getNum() with zero int
TEST(ObjectGetNumTest_94, ZeroIntReturnsDouble_94) {
    Object obj(0);
    ASSERT_TRUE(obj.isInt());
    EXPECT_DOUBLE_EQ(obj.getNum(), 0.0);
}

// Test getNum() with a real (double) Object
TEST(ObjectGetNumTest_94, RealReturnsDouble_94) {
    Object obj(3.14);
    ASSERT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getNum(), 3.14);
}

// Test getNum() with a negative real
TEST(ObjectGetNumTest_94, NegativeRealReturnsDouble_94) {
    Object obj(-2.718);
    ASSERT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getNum(), -2.718);
}

// Test getNum() with zero real
TEST(ObjectGetNumTest_94, ZeroRealReturnsDouble_94) {
    Object obj(0.0);
    ASSERT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getNum(), 0.0);
}

// Test getNum() with an int64 Object
TEST(ObjectGetNumTest_94, Int64ReturnsDouble_94) {
    long long val = 1234567890123LL;
    Object obj(val);
    ASSERT_TRUE(obj.isInt64());
    EXPECT_DOUBLE_EQ(obj.getNum(), static_cast<double>(val));
}

// Test getNum() with a negative int64
TEST(ObjectGetNumTest_94, NegativeInt64ReturnsDouble_94) {
    long long val = -9876543210LL;
    Object obj(val);
    ASSERT_TRUE(obj.isInt64());
    EXPECT_DOUBLE_EQ(obj.getNum(), static_cast<double>(val));
}

// Test getNum() with zero int64
TEST(ObjectGetNumTest_94, ZeroInt64ReturnsDouble_94) {
    long long val = 0LL;
    Object obj(val);
    // Note: zero int64 might be stored as int depending on implementation
    // but we test the numeric value regardless
    EXPECT_DOUBLE_EQ(obj.getNum(), 0.0);
}

// Test getNum() with large int value
TEST(ObjectGetNumTest_94, MaxIntReturnsDouble_94) {
    int val = 2147483647; // INT_MAX
    Object obj(val);
    ASSERT_TRUE(obj.isInt());
    EXPECT_DOUBLE_EQ(obj.getNum(), static_cast<double>(val));
}

// Test getNum() with minimum int value
TEST(ObjectGetNumTest_94, MinIntReturnsDouble_94) {
    int val = -2147483648; // INT_MIN
    Object obj(val);
    ASSERT_TRUE(obj.isInt());
    EXPECT_DOUBLE_EQ(obj.getNum(), static_cast<double>(val));
}

// Test getNum() with very small real
TEST(ObjectGetNumTest_94, VerySmallRealReturnsDouble_94) {
    Object obj(1e-300);
    ASSERT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getNum(), 1e-300);
}

// Test getNum() with very large real
TEST(ObjectGetNumTest_94, VeryLargeRealReturnsDouble_94) {
    Object obj(1e300);
    ASSERT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getNum(), 1e300);
}

// Test isNum() returns true for int
TEST(ObjectGetNumTest_94, IsNumTrueForInt_94) {
    Object obj(5);
    EXPECT_TRUE(obj.isNum());
}

// Test isNum() returns true for real
TEST(ObjectGetNumTest_94, IsNumTrueForReal_94) {
    Object obj(5.5);
    EXPECT_TRUE(obj.isNum());
}

// Test isNum() returns true for int64
TEST(ObjectGetNumTest_94, IsNumTrueForInt64_94) {
    Object obj(5LL);
    // int64 with small value might be stored as int, but isNum should still be true
    EXPECT_TRUE(obj.isNum());
}

// Test getNum(bool* ok) overload with int
TEST(ObjectGetNumTest_94, GetNumWithOkParamInt_94) {
    Object obj(10);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 10.0);
}

// Test getNum(bool* ok) overload with real
TEST(ObjectGetNumTest_94, GetNumWithOkParamReal_94) {
    Object obj(2.5);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 2.5);
}

// Test getNum(bool* ok) overload with int64
TEST(ObjectGetNumTest_94, GetNumWithOkParamInt64_94) {
    long long v = 9999999999LL;
    Object obj(v);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, static_cast<double>(v));
}

// Test that int Object returns correct value through getInt as well
TEST(ObjectGetNumTest_94, ConsistencyWithGetInt_94) {
    Object obj(77);
    EXPECT_DOUBLE_EQ(obj.getNum(), static_cast<double>(obj.getInt()));
}

// Test that real Object returns correct value through getReal as well
TEST(ObjectGetNumTest_94, ConsistencyWithGetReal_94) {
    Object obj(77.77);
    EXPECT_DOUBLE_EQ(obj.getNum(), obj.getReal());
}

// Test that int64 Object returns correct value through getInt64 as well
TEST(ObjectGetNumTest_94, ConsistencyWithGetInt64_94) {
    long long v = 123456789012345LL;
    Object obj(v);
    EXPECT_DOUBLE_EQ(obj.getNum(), static_cast<double>(obj.getInt64()));
}

// Test getNumWithDefaultValue for numeric types
TEST(ObjectGetNumTest_94, GetNumWithDefaultValueForInt_94) {
    Object obj(42);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 42.0);
}

// Test getNumWithDefaultValue for non-numeric type returns default
TEST(ObjectGetNumTest_94, GetNumWithDefaultValueForNonNum_94) {
    Object obj(true);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

// Test isNum for non-numeric types
TEST(ObjectGetNumTest_94, IsNumFalseForBool_94) {
    Object obj(true);
    EXPECT_FALSE(obj.isNum());
}

TEST(ObjectGetNumTest_94, IsNumFalseForNull_94) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isNum());
}

TEST(ObjectGetNumTest_94, IsNumFalseForError_94) {
    Object obj = Object::error();
    EXPECT_FALSE(obj.isNum());
}
