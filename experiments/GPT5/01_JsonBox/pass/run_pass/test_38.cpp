// File: Value_IsObject_Test_38.cpp

#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using JsonBox::Value;
using JsonBox::Object;
using JsonBox::Array;

//
// All tests follow the rule: both the test suite and the test case name end with _38
//

// Default-constructed Value should not be an object.
TEST(ValueIsObjectTest_38, DefaultConstructed_IsNotObject_38) {
    Value v;
    EXPECT_FALSE(v.isObject());
}

// Constructing from an Object should yield isObject() == true.
TEST(ValueIsObjectTest_38, ConstructedFromObject_IsObject_38) {
    Object o; // empty object is still an object
    Value v(o);
    EXPECT_TRUE(v.isObject());

    // Also try a non-empty object
    o["a"] = Value(1);
    Value v2(o);
    EXPECT_TRUE(v2.isObject());
}

// Constructing from non-object types should yield isObject() == false.
TEST(ValueIsObjectTest_38, ConstructedFromString_IsNotObject_38) {
    Value v(std::string("hello"));
    EXPECT_FALSE(v.isObject());
}

TEST(ValueIsObjectTest_38, ConstructedFromCString_IsNotObject_38) {
    Value v("hello");
    EXPECT_FALSE(v.isObject());
}

TEST(ValueIsObjectTest_38, ConstructedFromInteger_IsNotObject_38) {
    Value v(123);
    EXPECT_FALSE(v.isObject());
}

TEST(ValueIsObjectTest_38, ConstructedFromDouble_IsNotObject_38) {
    Value v(3.14);
    EXPECT_FALSE(v.isObject());
}

TEST(ValueIsObjectTest_38, ConstructedFromArray_IsNotObject_38) {
    Array a;
    a.push_back(Value(1));
    Value v(a);
    EXPECT_FALSE(v.isObject());
}

TEST(ValueIsObjectTest_38, ConstructedFromBoolean_IsNotObject_38) {
    Value v(true);
    EXPECT_FALSE(v.isObject());
}

// setObject should make the value report as an object.
TEST(ValueIsObjectTest_38, SetObject_MakesIsObjectTrue_38) {
    Value v; // not an object initially
    EXPECT_FALSE(v.isObject());

    Object o;
    o["k"] = Value("v");
    v.setObject(o);
    EXPECT_TRUE(v.isObject());
}

// setNull should make it not an object anymore (observable via isObject()).
TEST(ValueIsObjectTest_38, SetNull_MakesIsObjectFalse_38) {
    Object o;
    Value v(o);
    ASSERT_TRUE(v.isObject());

    v.setNull();
    EXPECT_FALSE(v.isObject());
}

// Copy construction should preserve isObject() result.
TEST(ValueIsObjectTest_38, CopyConstructor_PreservesIsObject_38) {
    Value original(Object{});
    ASSERT_TRUE(original.isObject());

    Value copy(original);
    EXPECT_TRUE(copy.isObject());
}

// Assignment from another Value should preserve isObject() according to the source.
TEST(ValueIsObjectTest_38, AssignmentOperator_PreservesIsObject_38) {
    Value src(Object{});
    Value dst;
    ASSERT_TRUE(src.isObject());
    ASSERT_FALSE(dst.isObject());

    dst = src;
    EXPECT_TRUE(dst.isObject());

    // Assign a non-object to dst and verify it flips to false
    Value nonObj(42);
    dst = nonObj;
    EXPECT_FALSE(dst.isObject());
}

// Loading JSON object text should yield isObject() == true (observable parser behavior).
TEST(ValueIsObjectTest_38, LoadFromString_ObjectJson_IsObjectTrue_38) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());

    v.loadFromString("{\"a\":1}");
    EXPECT_TRUE(v.isObject());
}

// Loading non-object JSON should yield isObject() == false (e.g., array, number, string).
TEST(ValueIsObjectTest_38, LoadFromString_NonObjectJson_IsObjectFalse_38) {
    Value v;

    v.loadFromString("[]");
    EXPECT_FALSE(v.isObject());

    v.loadFromString("1");
    EXPECT_FALSE(v.isObject());

    v.loadFromString("\"text\"");
    EXPECT_FALSE(v.isObject());
}
