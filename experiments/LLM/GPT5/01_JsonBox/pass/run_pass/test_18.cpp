// File: Value_AssignInt_Test_18.cpp
#include <gtest/gtest.h>
#include <climits>
#include <map>
#include <string>
#include <vector>

#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueAssignIntTest_18 : public ::testing::Test {};

TEST_F(ValueAssignIntTest_18, AssignSetsTypeAndValue_18) {
    Value v("abc");
    ASSERT_TRUE(v.isString());

    v = 123;
    EXPECT_TRUE(v.isInteger());
    EXPECT_TRUE(v.isNumeric());
    EXPECT_EQ(123, v.getInteger());
    EXPECT_EQ(123, v.tryGetInteger(-1));
}

TEST_F(ValueAssignIntTest_18, SupportsNegativeAndZero_18) {
    Value v;

    v = 0;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(0, v.getInteger());

    v = -456;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(-456, v.getInteger());
}

TEST_F(ValueAssignIntTest_18, OverwritesDifferentPreviousTypes_18) {
    Value v;

    // Start as double
    v = 3.14;
    ASSERT_TRUE(v.isDouble());
    v = 10;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(10, v.getInteger());

    // From boolean
    v = true;
    ASSERT_TRUE(v.isBoolean());
    v = 20;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(20, v.getInteger());

    // From object
    Object o; o["k"] = Value(1);
    v = o;
    ASSERT_TRUE(v.isObject());
    v = 30;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(30, v.getInteger());

    // From array
    Array a; a.push_back(Value(2));
    v = a;
    ASSERT_TRUE(v.isArray());
    v = 40;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(40, v.getInteger());

    // From string
    v = std::string("text");
    ASSERT_TRUE(v.isString());
    v = 50;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(50, v.getInteger());
}

TEST_F(ValueAssignIntTest_18, Boundary_INT_MIN_MAX_18) {
    Value v;

    v = INT_MIN;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(INT_MIN, v.getInteger());

    v = INT_MAX;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(INT_MAX, v.getInteger());
}

TEST_F(ValueAssignIntTest_18, ReturnsSelfReference_18) {
    Value v;
    Value& ref = (v = 77);
    EXPECT_EQ(&v, &ref);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(77, v.getInteger());
}

TEST_F(ValueAssignIntTest_18, AllowsChainedAssignments_18) {
    Value v;
    (v = 1) = 2;  // Use the returned Value& to assign again
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(2, v.getInteger());
}
