// File: Value_isDouble_test_36.cpp
#include <gtest/gtest.h>
#include <limits>
#include <map>
#include <string>
#include <vector>

#include "JsonBox/Value.h"

using namespace JsonBox;

TEST(ValueIsDoubleTest_36, ReturnsTrueForDoubleConstructor_36) {
    Value v(3.14159);
    EXPECT_TRUE(v.isDouble());
}

TEST(ValueIsDoubleTest_36, ReturnsTrueAfterSetDouble_36) {
    Value v(0);           // start non-double
    v.setDouble(2.5);     // change to double
    EXPECT_TRUE(v.isDouble());
}

TEST(ValueIsDoubleTest_36, ReturnsTrueAfterAssignDouble_36) {
    Value v(std::string("x"));
    v = 1.23;
    EXPECT_TRUE(v.isDouble());
}

TEST(ValueIsDoubleTest_36, ReturnsFalseForDefaultNull_36) {
    Value v;
    EXPECT_FALSE(v.isDouble());
}

TEST(ValueIsDoubleTest_36, ReturnsFalseForStringConstructor_36) {
    Value v(std::string("hello"));
    EXPECT_FALSE(v.isDouble());
}

TEST(ValueIsDoubleTest_36, ReturnsFalseForCStringConstructor_36) {
    Value v("hello");
    EXPECT_FALSE(v.isDouble());
}

TEST(ValueIsDoubleTest_36, ReturnsFalseForIntegerConstructor_36) {
    Value v(42);
    EXPECT_FALSE(v.isDouble());
}

TEST(ValueIsDoubleTest_36, ReturnsFalseForObjectConstructor_36) {
    JsonBox::Object obj;
    obj["k"] = Value(1);
    Value v(obj);
    EXPECT_FALSE(v.isDouble());
}

TEST(ValueIsDoubleTest_36, ReturnsFalseForArrayConstructor_36) {
    JsonBox::Array arr;
    arr.push_back(Value(true));
    Value v(arr);
    EXPECT_FALSE(v.isDouble());
}

TEST(ValueIsDoubleTest_36, ReturnsFalseForBooleanConstructor_36) {
    Value v(true);
    EXPECT_FALSE(v.isDouble());
}

TEST(ValueIsDoubleTest_36, ReturnsFalseAfterSetNull_36) {
    Value v(9.0);
    ASSERT_TRUE(v.isDouble()); // sanity check
    v.setNull();
    EXPECT_FALSE(v.isDouble());
}

TEST(ValueIsDoubleTest_36, PreservedThroughCopyConstructor_36) {
    Value original(0.5);
    ASSERT_TRUE(original.isDouble());
    Value copy(original);
    EXPECT_TRUE(copy.isDouble());
}

TEST(ValueIsDoubleTest_36, HandlesNaNAndInfinityAsDouble_36) {
    const double nan = std::numeric_limits<double>::quiet_NaN();
    const double inf = std::numeric_limits<double>::infinity();

    Value v_nan(nan);
    Value v_inf(inf);

    EXPECT_TRUE(v_nan.isDouble());
    EXPECT_TRUE(v_inf.isDouble());
}

TEST(ValueIsDoubleTest_36, TypeSwitchingViaAssignment_36) {
    Value v(10);      // integer
    EXPECT_FALSE(v.isDouble());

    v = 3.0;          // switch to double
    EXPECT_TRUE(v.isDouble());

    v = 7;            // back to integer
    EXPECT_FALSE(v.isDouble());

    v = "str";        // string
    EXPECT_FALSE(v.isDouble());
}
