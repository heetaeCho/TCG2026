// File: Value_AssignString_Test_16.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueAssignStringTest_16 : public ::testing::Test {};

// Normal operation: sets type to string and stores value
TEST_F(ValueAssignStringTest_16, AssignString_SetsTypeAndValue_16) {
    Value v(123);                 // start from a non-string type
    std::string s = "hello";
    v = s;

    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

// Boundary: empty string
TEST_F(ValueAssignStringTest_16, AssignEmptyString_16) {
    Value v(true);
    std::string empty;
    v = empty;

    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

// Boundary: special characters should be preserved as assigned (black-box check via getString)
TEST_F(ValueAssignStringTest_16, AssignString_WithSpecialCharacters_16) {
    Value v;
    std::string s = "\"quotes\" \\backslash\nnewline\t tab \r carriage 𝛼";
    v = s;

    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), s);
}

// Return value: operator= returns a reference to *this (enables chaining)
TEST_F(ValueAssignStringTest_16, ChainedAssignment_ReturnsSelfReference_16) {
    Value v("a");
    std::string s = "b";
    Value& ret = (v = s);

    EXPECT_EQ(&ret, &v);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "b");
}

// Copy semantics: assigning from std::string should not alias external buffer
TEST_F(ValueAssignStringTest_16, AssignString_NoAliasAfterSourceMutation_16) {
    Value v;
    std::string src = "original";
    v = src;
    src = "mutated";  // change the source after assignment

    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "original");
}

// Type change from Object to String is observable through type predicates
TEST_F(ValueAssignStringTest_16, AssignOverExistingObject_ChangesTypeToString_16) {
    Object obj;
    obj["k"] = Value(42);
    Value v(obj);  // start as object
    v = std::string("now-string");

    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isObject());
    EXPECT_EQ(v.getString(), "now-string");
}

// Type change from Array to String is observable through type predicates
TEST_F(ValueAssignStringTest_16, AssignOverExistingArray_ChangesTypeToString_16) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);  // start as array
    v = std::string("S");

    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isArray());
    EXPECT_EQ(v.getString(), "S");
}

// Repeated assignments overwrite prior string value
TEST_F(ValueAssignStringTest_16, RepeatedAssignments_OverwriteValue_16) {
    Value v("first");
    v = std::string("second");

    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "second");
}
