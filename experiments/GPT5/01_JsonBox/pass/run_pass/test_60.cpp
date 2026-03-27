// File: tests/Value_SetBoolean_60_Test.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using JsonBox::Value;
using JsonBox::Object;
using JsonBox::Array;

//
// Basic behavior on null/default
//
TEST(ValueSetBooleanTest_60, SetFromDefaultToTrue_60) {
    Value v; // default-constructed (NULL_VALUE per interface docs)
    v.setBoolean(true);

    EXPECT_TRUE(v.isBoolean());
    EXPECT_EQ(Value::Type::BOOLEAN, v.getType());
    EXPECT_TRUE(v.getBoolean());
    // tryGetBoolean should return the stored value, not the default
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST(ValueSetBooleanTest_60, SetFromDefaultToFalse_60) {
    Value v;
    v.setBoolean(false);

    EXPECT_TRUE(v.isBoolean());
    EXPECT_EQ(Value::Type::BOOLEAN, v.getType());
    EXPECT_FALSE(v.getBoolean());
    EXPECT_FALSE(v.tryGetBoolean(true)); // should ignore default and return stored
}

//
// Replacing other types
//
TEST(ValueSetBooleanTest_60, ReplacesIntegerTypeWithBoolean_60) {
    Value v(42);               // start as INTEGER
    ASSERT_TRUE(v.isInteger()); // precondition via public API

    v.setBoolean(false);

    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.getBoolean());
    // After replacement, integer queries should fall back to the provided default
    EXPECT_EQ(99, v.tryGetInteger(99));
}

TEST(ValueSetBooleanTest_60, ReplacesStringTypeWithBoolean_60) {
    Value v(std::string("hello"));
    ASSERT_TRUE(v.isString());

    v.setBoolean(true);

    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.isString());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueSetBooleanTest_60, ReplacesObjectAndArrayTypesWithBoolean_60) {
    // Object -> BOOLEAN
    Object o;
    o["k"] = Value(1);
    Value vo(o);
    ASSERT_TRUE(vo.isObject());

    vo.setBoolean(true);
    EXPECT_TRUE(vo.isBoolean());
    EXPECT_FALSE(vo.isObject());
    EXPECT_TRUE(vo.getBoolean());

    // Array -> BOOLEAN
    Array a;
    a.push_back(Value(3));
    Value va(a);
    ASSERT_TRUE(va.isArray());

    va.setBoolean(false);
    EXPECT_TRUE(va.isBoolean());
    EXPECT_FALSE(va.isArray());
    EXPECT_FALSE(va.getBoolean());
}

//
// Stability and multiple calls
//
TEST(ValueSetBooleanTest_60, ToggleBooleanMultipleTimes_60) {
    Value v(true);
    ASSERT_TRUE(v.isBoolean());
    ASSERT_TRUE(v.getBoolean());

    v.setBoolean(false);
    EXPECT_FALSE(v.getBoolean());
    EXPECT_TRUE(v.isBoolean()); // still a boolean

    v.setBoolean(true);
    EXPECT_TRUE(v.getBoolean());
    EXPECT_TRUE(v.isBoolean());
}

TEST(ValueSetBooleanTest_60, IdempotentWhenSettingSameValue_60) {
    Value v(false);
    ASSERT_TRUE(v.isBoolean());
    ASSERT_FALSE(v.getBoolean());

    v.setBoolean(false); // same value again
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

//
// Interaction with try-get defaults around a type change
//
TEST(ValueSetBooleanTest_60, TryGetBeforeAndAfterSet_60) {
    Value v(7); // not a boolean initially
    // Before setting, tryGetBoolean should return the provided default
    EXPECT_TRUE(v.tryGetBoolean(true));
    EXPECT_FALSE(v.tryGetBoolean(false));

    v.setBoolean(false);
    // After setting, it should return the stored value regardless of default
    EXPECT_FALSE(v.tryGetBoolean(true));
    EXPECT_FALSE(v.tryGetBoolean(false));
}
