// File: Value_IsInteger_Test_35.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"
#include <map>
#include <vector>
#include <string>

using JsonBox::Value;
using JsonBox::Array;
using JsonBox::Object;

class ValueIsIntegerTest_35 : public ::testing::Test {};

// Default/null construction should not be integer.
TEST_F(ValueIsIntegerTest_35, DefaultIsNotInteger_35) {
    Value v;
    EXPECT_FALSE(v.isInteger());
}

// Integer constructor should be integer (regardless of numeric value).
TEST_F(ValueIsIntegerTest_35, IntCtorIsInteger_35) {
    EXPECT_TRUE(Value(0).isInteger());
    EXPECT_TRUE(Value(-42).isInteger());
    EXPECT_TRUE(Value(123456).isInteger());
}

// Non-integer numeric constructor: double should not be integer.
TEST_F(ValueIsIntegerTest_35, DoubleCtorIsNotInteger_35) {
    EXPECT_FALSE(Value(0.0).isInteger());
    EXPECT_FALSE(Value(3.14).isInteger());
    EXPECT_FALSE(Value(-2.5).isInteger());
}

// String constructors should not be integer.
TEST_F(ValueIsIntegerTest_35, StringCtorIsNotInteger_35) {
    EXPECT_FALSE(Value(std::string("123")).isInteger());
    EXPECT_FALSE(Value("456").isInteger());
    EXPECT_FALSE(Value("not a number").isInteger());
}

// Boolean constructor should not be integer.
TEST_F(ValueIsIntegerTest_35, BoolCtorIsNotInteger_35) {
    EXPECT_FALSE(Value(true).isInteger());
    EXPECT_FALSE(Value(false).isInteger());
}

// Object constructor should not be integer.
TEST_F(ValueIsIntegerTest_35, ObjectCtorIsNotInteger_35) {
    Object o;
    o["a"] = Value(1);
    o["b"] = Value("str");
    Value v(o);
    EXPECT_FALSE(v.isInteger());
}

// Array constructor should not be integer.
TEST_F(ValueIsIntegerTest_35, ArrayCtorIsNotInteger_35) {
    Array a;
    a.push_back(Value(1));
    a.push_back(Value(2.0));
    Value v(a);
    EXPECT_FALSE(v.isInteger());
}

// Copy constructor preserves "integer-ness".
TEST_F(ValueIsIntegerTest_35, CopyCtorPreservesInteger_35) {
    Value vi(99);
    Value copy_i(vi);
    EXPECT_TRUE(copy_i.isInteger());

    Value vd(1.5);
    Value copy_d(vd);
    EXPECT_FALSE(copy_d.isInteger());
}

// Assignment to int results in integer.
TEST_F(ValueIsIntegerTest_35, AssignmentToIntSetsInteger_35) {
    Value v("was string");
    EXPECT_FALSE(v.isInteger());
    v = 7;
    EXPECT_TRUE(v.isInteger());
}

// setInteger makes it integer regardless of previous type.
TEST_F(ValueIsIntegerTest_35, SetIntegerSetsTypeToInteger_35) {
    Value v(false);
    EXPECT_FALSE(v.isInteger());
    v.setInteger(-100);
    EXPECT_TRUE(v.isInteger());
}

// Changing to a non-integer numeric type stops being integer.
TEST_F(ValueIsIntegerTest_35, SetDoubleClearsInteger_35) {
    Value v(10);
    ASSERT_TRUE(v.isInteger());
    v.setDouble(10.0);
    EXPECT_FALSE(v.isInteger());
}

// Explicitly setting to null should not be integer.
TEST_F(ValueIsIntegerTest_35, SetNullIsNotInteger_35) {
    Value v(1);
    ASSERT_TRUE(v.isInteger());
    v.setNull();
    EXPECT_FALSE(v.isInteger());
}
