#include <gtest/gtest.h>
#include <string>
#include <map>
#include <vector>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueAssignBoolTest_22 : public ::testing::Test {};

// Normal: assign true sets boolean type & value
TEST_F(ValueAssignBoolTest_22, AssignBool_SetsBooleanTrue_22) {
    Value v; // starts null per interface docs
    v = true;

    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
    EXPECT_FALSE(v.isNull());
}

// Normal: assign false sets boolean type & value
TEST_F(ValueAssignBoolTest_22, AssignBool_SetsBooleanFalse_22) {
    Value v;
    v = false;

    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

// Boundary: assigning twice (idempotent with same value)
TEST_F(ValueAssignBoolTest_22, AssignBool_TwiceSameValue_22) {
    Value v;
    v = true;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

// Boundary: chaining and return-by-reference behavior
TEST_F(ValueAssignBoolTest_22, AssignBool_ChainingAndReturnsSelf_22) {
    Value v;

    // Check it returns a reference to self
    Value* ref = &(v = true);
    EXPECT_EQ(ref, &v);
    EXPECT_TRUE(v.getBoolean());

    // Chaining: the final assignment should prevail
    (v = true) = false;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

// Overwrite previous STRING -> BOOLEAN
TEST_F(ValueAssignBoolTest_22, AssignBool_OverwritesString_22) {
    Value v(std::string("hello"));
    ASSERT_TRUE(v.isString()); // precondition through public API

    v = true;

    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
    EXPECT_FALSE(v.isString());
}

// Overwrite previous INTEGER -> BOOLEAN
TEST_F(ValueAssignBoolTest_22, AssignBool_OverwritesInteger_22) {
    Value v(123);
    ASSERT_TRUE(v.isInteger()); // precondition

    v = false;

    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
    EXPECT_FALSE(v.isInteger());
}

// Overwrite previous DOUBLE -> BOOLEAN
TEST_F(ValueAssignBoolTest_22, AssignBool_OverwritesDouble_22) {
    Value v(3.14);
    ASSERT_TRUE(v.isDouble()); // precondition

    v = true;

    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
    EXPECT_FALSE(v.isDouble());
}

// Overwrite previous OBJECT -> BOOLEAN
TEST_F(ValueAssignBoolTest_22, AssignBool_OverwritesObject_22) {
    JsonBox::Object obj;
    obj["k"] = Value(1);
    Value v(obj);
    ASSERT_TRUE(v.isObject()); // precondition

    v = false;

    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
    EXPECT_FALSE(v.isObject());
}

// Overwrite previous ARRAY -> BOOLEAN
TEST_F(ValueAssignBoolTest_22, AssignBool_OverwritesArray_22) {
    JsonBox::Array arr;
    arr.push_back(Value("x"));
    Value v(arr);
    ASSERT_TRUE(v.isArray()); // precondition

    v = true;

    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
    EXPECT_FALSE(v.isArray());
}

// Observable behavior via tryGetBoolean(default)
TEST_F(ValueAssignBoolTest_22, AssignBool_UpdatesTryGetBoolean_22) {
    Value v;
    v = true;
    EXPECT_TRUE(v.tryGetBoolean(false));
    v = false;
    EXPECT_FALSE(v.tryGetBoolean(true));
}
