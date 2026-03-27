// File: ValueCopyConstructorTest_72.cpp

#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using JsonBox::Value;
using JsonBox::Array;
using JsonBox::Object;

class ValueCopyConstructorTest_72 : public ::testing::Test {};

// STRING
TEST(ValueCopyConstructorTest_72, CopyStringDeep_72) {
    Value original(std::string("hello"));
    Value copy(original);

    ASSERT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "hello");

    // Mutate original and ensure copy is unchanged (deep copy behavior)
    original.setString("world");
    EXPECT_EQ(copy.getString(), "hello");
    EXPECT_EQ(original.getString(), "world");
}

TEST(ValueCopyConstructorTest_72, CopyEmptyStringDeep_72) {
    Value original(std::string(""));
    Value copy(original);

    ASSERT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "");

    original.setString("x");
    EXPECT_EQ(copy.getString(), "");
    EXPECT_EQ(original.getString(), "x");
}

// INTEGER
TEST(ValueCopyConstructorTest_72, CopyIntegerDeep_72) {
    Value original(42);
    Value copy(original);

    ASSERT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);

    original.setInteger(-7);
    EXPECT_EQ(copy.getInteger(), 42);
    EXPECT_EQ(original.getInteger(), -7);
}

// DOUBLE
TEST(ValueCopyConstructorTest_72, CopyDoubleDeep_72) {
    Value original(3.14159);
    Value copy(original);

    ASSERT_TRUE(copy.isDouble());
    EXPECT_DOUBLE_EQ(copy.getDouble(), 3.14159);

    original.setDouble(2.71828);
    EXPECT_DOUBLE_EQ(copy.getDouble(), 3.14159);
    EXPECT_DOUBLE_EQ(original.getDouble(), 2.71828);
}

// BOOLEAN
TEST(ValueCopyConstructorTest_72, CopyBooleanTrueDeep_72) {
    Value original(true);
    Value copy(original);

    ASSERT_TRUE(copy.isBoolean());
    EXPECT_TRUE(copy.getBoolean());

    original.setBoolean(false);
    EXPECT_TRUE(copy.getBoolean());
    EXPECT_FALSE(original.getBoolean());
}

TEST(ValueCopyConstructorTest_72, CopyBooleanFalseDeep_72) {
    Value original(false);
    Value copy(original);

    ASSERT_TRUE(copy.isBoolean());
    EXPECT_FALSE(copy.getBoolean());

    original.setBoolean(true);
    EXPECT_FALSE(copy.getBoolean());
    EXPECT_TRUE(original.getBoolean());
}

// OBJECT
TEST(ValueCopyConstructorTest_72, CopyObjectDeep_72) {
    Object o;
    o["a"] = Value(1);
    o["b"] = Value(std::string("x"));

    Value original(o);
    Value copy(original);

    ASSERT_TRUE(copy.isObject());
    ASSERT_EQ(copy.getObject().size(), 2u);
    EXPECT_EQ(copy.getObject().at("a").getInteger(), 1);
    EXPECT_EQ(copy.getObject().at("b").getString(), "x");

    // Mutate original via setObject (observable change)
    o["a"] = Value(99);
    o["c"] = Value(true);
    original.setObject(o);

    // Copy should remain unchanged
    EXPECT_EQ(copy.getObject().size(), 2u);
    EXPECT_EQ(copy.getObject().at("a").getInteger(), 1);
    EXPECT_EQ(copy.getObject().at("b").getString(), "x");

    // Original reflects the new state
    EXPECT_EQ(original.getObject().size(), 3u);
    EXPECT_EQ(original.getObject().at("a").getInteger(), 99);
    EXPECT_TRUE(original.getObject().at("c").getBoolean());
}

TEST(ValueCopyConstructorTest_72, CopyEmptyObjectDeep_72) {
    Object o;
    Value original(o);
    Value copy(original);

    ASSERT_TRUE(copy.isObject());
    EXPECT_EQ(copy.getObject().size(), 0u);

    // Mutate original
    o["k"] = Value("v");
    original.setObject(o);

    EXPECT_EQ(copy.getObject().size(), 0u);
    EXPECT_EQ(original.getObject().size(), 1u);
}

// ARRAY
TEST(ValueCopyConstructorTest_72, CopyArrayDeep_72) {
    Array arr;
    arr.push_back(Value("a"));
    arr.push_back(Value(2));

    Value original(arr);
    Value copy(original);

    ASSERT_TRUE(copy.isArray());
    ASSERT_EQ(copy.getArray().size(), 2u);
    EXPECT_EQ(copy.getArray()[0].getString(), "a");
    EXPECT_EQ(copy.getArray()[1].getInteger(), 2);

    // Mutate original via setArray (observable change)
    arr.push_back(Value(true));
    original.setArray(arr);

    // Copy remains unchanged
    EXPECT_EQ(copy.getArray().size(), 2u);
    EXPECT_EQ(copy.getArray()[0].getString(), "a");
    EXPECT_EQ(copy.getArray()[1].getInteger(), 2);

    // Original reflects new element
    ASSERT_EQ(original.getArray().size(), 3u);
    EXPECT_TRUE(original.getArray()[2].getBoolean());
}

TEST(ValueCopyConstructorTest_72, CopyEmptyArrayDeep_72) {
    Array arr;
    Value original(arr);
    Value copy(original);

    ASSERT_TRUE(copy.isArray());
    EXPECT_EQ(copy.getArray().size(), 0u);

    arr.push_back(Value(1));
    original.setArray(arr);

    EXPECT_EQ(copy.getArray().size(), 0u);
    EXPECT_EQ(original.getArray().size(), 1u);
}

// NULL
TEST(ValueCopyConstructorTest_72, CopyNullDeep_72) {
    Value original; // default is NULL
    Value copy(original);

    ASSERT_TRUE(copy.isNull());

    // Mutate original to another type; copy should remain null
    original.setString("now not null");
    EXPECT_TRUE(copy.isNull());
    ASSERT_TRUE(original.isString());
    EXPECT_EQ(original.getString(), "now not null");
}
