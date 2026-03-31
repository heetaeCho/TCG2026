#include <gtest/gtest.h>
#include "Object.h"

// Test fixture for Object::getNumWithDefaultValue
class ObjectGetNumWithDefaultValueTest_110 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Integer object returns its integer value as double
TEST_F(ObjectGetNumWithDefaultValueTest_110, IntObjectReturnsIntValue_110) {
    Object obj(42);
    ASSERT_TRUE(obj.isInt());
    double result = obj.getNumWithDefaultValue(99.0);
    EXPECT_DOUBLE_EQ(result, 42.0);
}

// Test: Int64 object returns its int64 value as double
TEST_F(ObjectGetNumWithDefaultValueTest_110, Int64ObjectReturnsInt64Value_110) {
    Object obj(static_cast<long long>(123456789012345LL));
    ASSERT_TRUE(obj.isInt64());
    double result = obj.getNumWithDefaultValue(99.0);
    EXPECT_DOUBLE_EQ(result, 123456789012345.0);
}

// Test: Real (double) object returns its real value
TEST_F(ObjectGetNumWithDefaultValueTest_110, RealObjectReturnsRealValue_110) {
    Object obj(3.14);
    ASSERT_TRUE(obj.isReal());
    double result = obj.getNumWithDefaultValue(99.0);
    EXPECT_DOUBLE_EQ(result, 3.14);
}

// Test: Null object returns default value
TEST_F(ObjectGetNumWithDefaultValueTest_110, NullObjectReturnsDefault_110) {
    Object obj = Object::null();
    ASSERT_TRUE(obj.isNull());
    double result = obj.getNumWithDefaultValue(99.0);
    EXPECT_DOUBLE_EQ(result, 99.0);
}

// Test: Bool object returns default value (not a numeric type)
TEST_F(ObjectGetNumWithDefaultValueTest_110, BoolObjectReturnsDefault_110) {
    Object obj(true);
    ASSERT_TRUE(obj.isBool());
    double result = obj.getNumWithDefaultValue(55.5);
    EXPECT_DOUBLE_EQ(result, 55.5);
}

// Test: Error object returns default value
TEST_F(ObjectGetNumWithDefaultValueTest_110, ErrorObjectReturnsDefault_110) {
    Object obj = Object::error();
    ASSERT_TRUE(obj.isError());
    double result = obj.getNumWithDefaultValue(-1.0);
    EXPECT_DOUBLE_EQ(result, -1.0);
}

// Test: EOF object returns default value
TEST_F(ObjectGetNumWithDefaultValueTest_110, EofObjectReturnsDefault_110) {
    Object obj = Object::eof();
    ASSERT_TRUE(obj.isEOF());
    double result = obj.getNumWithDefaultValue(42.0);
    EXPECT_DOUBLE_EQ(result, 42.0);
}

// Test: None object returns default value
TEST_F(ObjectGetNumWithDefaultValueTest_110, NoneObjectReturnsDefault_110) {
    Object obj;
    ASSERT_TRUE(obj.isNone());
    double result = obj.getNumWithDefaultValue(7.7);
    EXPECT_DOUBLE_EQ(result, 7.7);
}

// Test: Integer zero returns 0.0 (not default)
TEST_F(ObjectGetNumWithDefaultValueTest_110, IntZeroReturnsZero_110) {
    Object obj(0);
    ASSERT_TRUE(obj.isInt());
    double result = obj.getNumWithDefaultValue(100.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test: Negative integer returns correct negative value
TEST_F(ObjectGetNumWithDefaultValueTest_110, NegativeIntReturnsNegativeValue_110) {
    Object obj(-42);
    ASSERT_TRUE(obj.isInt());
    double result = obj.getNumWithDefaultValue(0.0);
    EXPECT_DOUBLE_EQ(result, -42.0);
}

// Test: Real zero returns 0.0 (not default)
TEST_F(ObjectGetNumWithDefaultValueTest_110, RealZeroReturnsZero_110) {
    Object obj(0.0);
    ASSERT_TRUE(obj.isReal());
    double result = obj.getNumWithDefaultValue(100.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test: Negative real returns correct negative value
TEST_F(ObjectGetNumWithDefaultValueTest_110, NegativeRealReturnsNegativeValue_110) {
    Object obj(-2.718);
    ASSERT_TRUE(obj.isReal());
    double result = obj.getNumWithDefaultValue(0.0);
    EXPECT_DOUBLE_EQ(result, -2.718);
}

// Test: Int64 zero returns 0.0 (not default)
TEST_F(ObjectGetNumWithDefaultValueTest_110, Int64ZeroReturnsZero_110) {
    Object obj(static_cast<long long>(0));
    ASSERT_TRUE(obj.isInt64());
    double result = obj.getNumWithDefaultValue(100.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test: Negative Int64 returns correct negative value
TEST_F(ObjectGetNumWithDefaultValueTest_110, NegativeInt64ReturnsNegativeValue_110) {
    Object obj(static_cast<long long>(-999999999999LL));
    ASSERT_TRUE(obj.isInt64());
    double result = obj.getNumWithDefaultValue(0.0);
    EXPECT_DOUBLE_EQ(result, -999999999999.0);
}

// Test: Very large real value is returned correctly
TEST_F(ObjectGetNumWithDefaultValueTest_110, VeryLargeRealReturnsCorrectValue_110) {
    Object obj(1.0e308);
    ASSERT_TRUE(obj.isReal());
    double result = obj.getNumWithDefaultValue(0.0);
    EXPECT_DOUBLE_EQ(result, 1.0e308);
}

// Test: Very small real value (near zero) is returned correctly
TEST_F(ObjectGetNumWithDefaultValueTest_110, VerySmallRealReturnsCorrectValue_110) {
    Object obj(1.0e-300);
    ASSERT_TRUE(obj.isReal());
    double result = obj.getNumWithDefaultValue(0.0);
    EXPECT_DOUBLE_EQ(result, 1.0e-300);
}

// Test: Default value of 0.0 is returned for non-numeric type
TEST_F(ObjectGetNumWithDefaultValueTest_110, DefaultValueZeroReturnedForNonNumeric_110) {
    Object obj = Object::null();
    double result = obj.getNumWithDefaultValue(0.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test: Default value of negative number is returned for non-numeric type
TEST_F(ObjectGetNumWithDefaultValueTest_110, NegativeDefaultValueReturned_110) {
    Object obj = Object::null();
    double result = obj.getNumWithDefaultValue(-999.999);
    EXPECT_DOUBLE_EQ(result, -999.999);
}

// Test: String object returns default value
TEST_F(ObjectGetNumWithDefaultValueTest_110, StringObjectReturnsDefault_110) {
    Object obj(std::string("hello"));
    ASSERT_TRUE(obj.isString());
    double result = obj.getNumWithDefaultValue(12.34);
    EXPECT_DOUBLE_EQ(result, 12.34);
}

// Test: Name object returns default value
TEST_F(ObjectGetNumWithDefaultValueTest_110, NameObjectReturnsDefault_110) {
    Object obj(objName, "someName");
    ASSERT_TRUE(obj.isName());
    double result = obj.getNumWithDefaultValue(56.78);
    EXPECT_DOUBLE_EQ(result, 56.78);
}

// Test: Cmd object returns default value
TEST_F(ObjectGetNumWithDefaultValueTest_110, CmdObjectReturnsDefault_110) {
    Object obj(objCmd, "someCmd");
    ASSERT_TRUE(obj.isCmd());
    double result = obj.getNumWithDefaultValue(11.11);
    EXPECT_DOUBLE_EQ(result, 11.11);
}

// Test: INT_MAX as integer
TEST_F(ObjectGetNumWithDefaultValueTest_110, IntMaxReturnsCorrectValue_110) {
    Object obj(INT_MAX);
    ASSERT_TRUE(obj.isInt());
    double result = obj.getNumWithDefaultValue(0.0);
    EXPECT_DOUBLE_EQ(result, static_cast<double>(INT_MAX));
}

// Test: INT_MIN as integer
TEST_F(ObjectGetNumWithDefaultValueTest_110, IntMinReturnsCorrectValue_110) {
    Object obj(INT_MIN);
    ASSERT_TRUE(obj.isInt());
    double result = obj.getNumWithDefaultValue(0.0);
    EXPECT_DOUBLE_EQ(result, static_cast<double>(INT_MIN));
}
