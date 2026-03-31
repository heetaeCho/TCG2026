#include <gtest/gtest.h>
#include "Object.h"

// Test fixture for Object::getNum(bool *ok) tests
class ObjectGetNumTest_95 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test getNum with an int Object - normal case
TEST_F(ObjectGetNumTest_95, IntObjectReturnsDoubleValue_95) {
    Object obj(42);
    bool ok = true;
    double result = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(result, 42.0);
}

// Test getNum with a negative int Object
TEST_F(ObjectGetNumTest_95, NegativeIntObjectReturnsDoubleValue_95) {
    Object obj(-100);
    bool ok = true;
    double result = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(result, -100.0);
}

// Test getNum with int value of zero
TEST_F(ObjectGetNumTest_95, ZeroIntObjectReturnsZero_95) {
    Object obj(0);
    bool ok = true;
    double result = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test getNum with a real (double) Object - normal case
TEST_F(ObjectGetNumTest_95, RealObjectReturnsDoubleValue_95) {
    Object obj(3.14);
    bool ok = true;
    double result = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(result, 3.14);
}

// Test getNum with a negative real Object
TEST_F(ObjectGetNumTest_95, NegativeRealObjectReturnsDoubleValue_95) {
    Object obj(-2.718);
    bool ok = true;
    double result = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(result, -2.718);
}

// Test getNum with real value of zero
TEST_F(ObjectGetNumTest_95, ZeroRealObjectReturnsZero_95) {
    Object obj(0.0);
    bool ok = true;
    double result = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test getNum with an int64 Object - normal case
TEST_F(ObjectGetNumTest_95, Int64ObjectReturnsDoubleValue_95) {
    long long val = 1234567890123LL;
    Object obj(val);
    bool ok = true;
    double result = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(result, (double)val);
}

// Test getNum with a negative int64 Object
TEST_F(ObjectGetNumTest_95, NegativeInt64ObjectReturnsDoubleValue_95) {
    long long val = -9876543210LL;
    Object obj(val);
    bool ok = true;
    double result = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(result, (double)val);
}

// Test getNum with int64 value of zero
TEST_F(ObjectGetNumTest_95, ZeroInt64ObjectReturnsZero_95) {
    long long val = 0LL;
    Object obj(val);
    bool ok = true;
    double result = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test getNum with a bool Object - should set ok to false
TEST_F(ObjectGetNumTest_95, BoolObjectSetsOkFalse_95) {
    Object obj(true);
    bool ok = true;
    double result = obj.getNum(&ok);
    EXPECT_FALSE(ok);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test getNum with a null Object - should set ok to false
TEST_F(ObjectGetNumTest_95, NullObjectSetsOkFalse_95) {
    Object obj = Object::null();
    bool ok = true;
    double result = obj.getNum(&ok);
    EXPECT_FALSE(ok);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test getNum with an error Object - should set ok to false
TEST_F(ObjectGetNumTest_95, ErrorObjectSetsOkFalse_95) {
    Object obj = Object::error();
    bool ok = true;
    double result = obj.getNum(&ok);
    EXPECT_FALSE(ok);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test getNum with an EOF Object - should set ok to false
TEST_F(ObjectGetNumTest_95, EofObjectSetsOkFalse_95) {
    Object obj = Object::eof();
    bool ok = true;
    double result = obj.getNum(&ok);
    EXPECT_FALSE(ok);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test getNum with a name Object - should set ok to false
TEST_F(ObjectGetNumTest_95, NameObjectSetsOkFalse_95) {
    Object obj(objName, "testName");
    bool ok = true;
    double result = obj.getNum(&ok);
    EXPECT_FALSE(ok);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test getNum with a string Object - should set ok to false
TEST_F(ObjectGetNumTest_95, StringObjectSetsOkFalse_95) {
    Object obj(std::string("hello"));
    bool ok = true;
    double result = obj.getNum(&ok);
    EXPECT_FALSE(ok);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test getNum with a cmd Object - should set ok to false
TEST_F(ObjectGetNumTest_95, CmdObjectSetsOkFalse_95) {
    Object obj(objCmd, "someCmd");
    bool ok = true;
    double result = obj.getNum(&ok);
    EXPECT_FALSE(ok);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test getNum with default constructed (none) Object - should set ok to false
TEST_F(ObjectGetNumTest_95, NoneObjectSetsOkFalse_95) {
    Object obj;
    bool ok = true;
    double result = obj.getNum(&ok);
    EXPECT_FALSE(ok);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test getNum with large int value - boundary
TEST_F(ObjectGetNumTest_95, LargeIntValueReturnsCorrectDouble_95) {
    Object obj(2147483647); // INT_MAX
    bool ok = true;
    double result = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(result, 2147483647.0);
}

// Test getNum with minimum int value - boundary
TEST_F(ObjectGetNumTest_95, MinIntValueReturnsCorrectDouble_95) {
    Object obj(-2147483647 - 1); // INT_MIN
    bool ok = true;
    double result = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(result, (double)(-2147483647 - 1));
}

// Test getNum with very small real value
TEST_F(ObjectGetNumTest_95, VerySmallRealReturnsCorrectValue_95) {
    Object obj(1e-300);
    bool ok = true;
    double result = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(result, 1e-300);
}

// Test getNum with very large real value
TEST_F(ObjectGetNumTest_95, VeryLargeRealReturnsCorrectValue_95) {
    Object obj(1e+300);
    bool ok = true;
    double result = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(result, 1e+300);
}

// Test that ok is not modified when the type is valid (int)
TEST_F(ObjectGetNumTest_95, OkNotSetToFalseForValidInt_95) {
    Object obj(7);
    bool ok = true;
    obj.getNum(&ok);
    EXPECT_TRUE(ok);
}

// Test that ok is not modified when the type is valid (real)
TEST_F(ObjectGetNumTest_95, OkNotSetToFalseForValidReal_95) {
    Object obj(7.5);
    bool ok = true;
    obj.getNum(&ok);
    EXPECT_TRUE(ok);
}

// Test that ok is not modified when the type is valid (int64)
TEST_F(ObjectGetNumTest_95, OkNotSetToFalseForValidInt64_95) {
    Object obj(7LL);
    bool ok = true;
    obj.getNum(&ok);
    EXPECT_TRUE(ok);
}

// Test that ok starts false and stays false for invalid type
TEST_F(ObjectGetNumTest_95, OkAlreadyFalseStaysFalseForInvalidType_95) {
    Object obj = Object::null();
    bool ok = false;
    double result = obj.getNum(&ok);
    EXPECT_FALSE(ok);
    EXPECT_DOUBLE_EQ(result, 0.0);
}
