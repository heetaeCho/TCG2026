// File: test_value_destructor_14.cpp
#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueDestructorTest_14 : public ::testing::Test {};

// Basic scope-based destruction on default value.
TEST_F(ValueDestructorTest_14, DestroyNullValue_NoCrash_14) {
    EXPECT_NO_THROW({
        Value v;
        // No observable side effect expected; ensuring creation is OK.
        // Destructor runs at end of scope.
    });
}

// Destruction after holding a string.
TEST_F(ValueDestructorTest_14, DestroyStringValue_NoCrash_14) {
    EXPECT_NO_THROW({
        Value v(std::string("hello"));
        EXPECT_TRUE(v.isString());
        EXPECT_EQ("hello", v.getString());
        // Destructor runs at end of scope.
    });
}

// Destruction after holding an integer.
TEST_F(ValueDestructorTest_14, DestroyIntegerValue_NoCrash_14) {
    EXPECT_NO_THROW({
        Value v(42);
        EXPECT_TRUE(v.isInteger());
        EXPECT_EQ(42, v.getInteger());
    });
}

// Destruction after holding a double.
TEST_F(ValueDestructorTest_14, DestroyDoubleValue_NoCrash_14) {
    EXPECT_NO_THROW({
        Value v(3.14159);
        EXPECT_TRUE(v.isDouble());
        EXPECT_DOUBLE_EQ(3.14159, v.getDouble());
    });
}

// Destruction after holding a boolean.
TEST_F(ValueDestructorTest_14, DestroyBooleanValue_NoCrash_14) {
    EXPECT_NO_THROW({
        Value v(true);
        EXPECT_TRUE(v.isBoolean());
        EXPECT_TRUE(v.getBoolean());
    });
}

// Destruction after holding an array with heterogeneous items.
TEST_F(ValueDestructorTest_14, DestroyArrayValue_WithNestedValues_14) {
    EXPECT_NO_THROW({
        Array arr;
        arr.push_back(Value(1));
        arr.push_back(Value("x"));
        arr.push_back(Value(false));
        Value v(arr);
        EXPECT_TRUE(v.isArray());
        const Array &got = v.getArray();
        ASSERT_EQ(3u, got.size());
        EXPECT_TRUE(got[0].isInteger());
        EXPECT_TRUE(got[1].isString());
        EXPECT_TRUE(got[2].isBoolean());
    });
}

// Destruction after holding an object/map with nested values.
TEST_F(ValueDestructorTest_14, DestroyObjectValue_WithNestedValues_14) {
    EXPECT_NO_THROW({
        Object obj;
        obj["a"] = Value(10);
        obj["b"] = Value("bee");
        obj["c"] = Value(true);
        Value v(obj);
        EXPECT_TRUE(v.isObject());
        const Object &got = v.getObject();
        ASSERT_EQ(3u, got.size());
        EXPECT_TRUE(got.at("a").isInteger());
        EXPECT_EQ(10, got.at("a").getInteger());
        EXPECT_TRUE(got.at("b").isString());
        EXPECT_EQ("bee", got.at("b").getString());
        EXPECT_TRUE(got.at("c").isBoolean());
        EXPECT_TRUE(got.at("c").getBoolean());
    });
}

// Reassignment to different types should replace the previous content (which implies cleanup).
TEST_F(ValueDestructorTest_14, ReassignDifferentTypes_ReplacesValue_14) {
    Value v("start");
    ASSERT_TRUE(v.isString());
    EXPECT_EQ("start", v.getString());

    EXPECT_NO_THROW(v = 123);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(123, v.getInteger());

    EXPECT_NO_THROW(v = 2.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(2.5, v.getDouble());

    EXPECT_NO_THROW(v = true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());

    Array arr; arr.push_back(Value("z"));
    EXPECT_NO_THROW(v = arr);
    EXPECT_TRUE(v.isArray());
    ASSERT_EQ(1u, v.getArray().size());
    EXPECT_TRUE(v.getArray()[0].isString());
}

// Copy construction and subsequent independent destruction.
TEST_F(ValueDestructorTest_14, CopyConstruct_ThenBothDestruct_NoCrash_14) {
    EXPECT_NO_THROW({
        Value original("copy me");
        Value copy(original);
        // We only verify observable state; both go out of scope independently.
        if (original.isString()) {
            EXPECT_EQ(original.getString(), copy.getString());
        }
    });
}

// Self-assignment should not crash and should preserve observable value.
TEST_F(ValueDestructorTest_14, SelfAssignment_PreservesValue_NoCrash_14) {
    Value v("self");
    EXPECT_NO_THROW(v = v);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("self", v.getString());
}

// Many instances inside a standard container; all destructed at vector destruction.
TEST_F(ValueDestructorTest_14, VectorOfValues_DestructAll_NoCrash_14) {
    EXPECT_NO_THROW({
        std::vector<Value> vec;
        for (int i = 0; i < 100; ++i) vec.emplace_back(i);
        for (int i = 0; i < 100; ++i) {
            ASSERT_TRUE(vec[i].isInteger());
            EXPECT_EQ(i, vec[i].getInteger());
        }
        // vec destruction triggers destructor of all elements.
    });
}

// Large payload stress — ensures no crash on destruction of big string.
TEST_F(ValueDestructorTest_14, LargeStringPayload_Destruction_NoCrash_14) {
    EXPECT_NO_THROW({
        std::string big(1 << 20, 'A'); // ~1MB
        Value v(big);
        ASSERT_TRUE(v.isString());
        EXPECT_EQ(big.size(), v.getString().size());
    });
}

// Construct from an input stream (per interface), then ensure safe destruction.
TEST_F(ValueDestructorTest_14, StreamConstructor_Destruction_NoCrash_14) {
    EXPECT_NO_THROW({
        std::istringstream iss("{\"k\": 1}");
        Value v(iss);
        // We do not assert parsing behavior here; we only require safe lifetime.
    });
}

// Reassign object and array multiple times to ensure prior content is released and replaced.
TEST_F(ValueDestructorTest_14, ReassignContainers_MultipleTimes_NoCrash_14) {
    EXPECT_NO_THROW({
        Value v;
        Object o1; o1["x"] = Value(7);
        v = o1;
        ASSERT_TRUE(v.isObject());
        EXPECT_EQ(1u, v.getObject().size());

        Array a1; a1.push_back(Value("a")); a1.push_back(Value("b"));
        v = a1;
        ASSERT_TRUE(v.isArray());
        EXPECT_EQ(2u, v.getArray().size());

        Object o2; o2["y"] = Value(false);
        v = o2;
        ASSERT_TRUE(v.isObject());
        EXPECT_EQ(1u, v.getObject().size());
        EXPECT_TRUE(v.getObject().at("y").isBoolean());
    });
}
