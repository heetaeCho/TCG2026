// File: tests/Value_AssignObject_Test_20.cpp

#include <gtest/gtest.h>
#include <map>
#include <string>
#include <vector>
#include "JsonBox/Value.h"

using JsonBox::Value;
using JsonBox::Object;
using JsonBox::Array;

class ValueAssignObjectTest_20 : public ::testing::Test {
protected:
    static Object MakeSimpleObject() {
        Object o;
        o["int"] = Value(42);
        o["str"] = Value(std::string("hello"));
        o["dbl"] = Value(3.5);
        o["bool"] = Value(true);
        return o;
    }

    static Object MakeNestedObject() {
        Object inner;
        inner["x"] = Value(-7);
        inner["y"] = Value(std::string("yy"));

        Array arr;
        arr.push_back(Value(1));
        arr.push_back(Value(2));
        arr.push_back(Value(3));

        Object root;
        root["obj"] = Value(inner);
        root["arr"] = Value(arr);
        root["flag"] = Value(false);
        return root;
    }
};

// Normal operation: assigning a non-empty Object sets type and copies values.
TEST_F(ValueAssignObjectTest_20, AssignObject_SetsTypeAndValue_20) {
    Value v("was string");
    Object src = ValueAssignObjectTest_20::MakeSimpleObject();

    v = src;

    EXPECT_TRUE(v.isObject());
    const Object& got = v.getObject();
    ASSERT_EQ(4u, got.size());

    EXPECT_TRUE(got.at("int").isInteger());
    EXPECT_EQ(42,   got.at("int").getInteger());
    EXPECT_TRUE(got.at("str").isString());
    EXPECT_EQ(std::string("hello"), got.at("str").getString());
    EXPECT_TRUE(got.at("dbl").isDouble());
    EXPECT_DOUBLE_EQ(3.5, got.at("dbl").getDouble());
    EXPECT_TRUE(got.at("bool").isBoolean());
    EXPECT_TRUE(got.at("bool").getBoolean());
}

// Boundary: assigning an empty Object results in an empty object value.
TEST_F(ValueAssignObjectTest_20, AssignEmptyObject_YieldsEmptyObject_20) {
    Value v(123); // start from a different type
    Object empty;

    v = empty;

    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(0u, v.getObject().size());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isNumeric());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

// Overwrite semantics: previous type and contents are replaced.
TEST_F(ValueAssignObjectTest_20, AssignOverwritesPreviousType_20) {
    // Start as array, then overwrite with object
    Array a;
    a.push_back(Value(1));
    a.push_back(Value(2));
    Value v(a);

    Object src = ValueAssignObjectTest_20::MakeSimpleObject();
    v = src;

    EXPECT_TRUE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isNumeric());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
    EXPECT_EQ(4u, v.getObject().size());
}

// Return value: operator= returns *this (reference) and supports chaining.
TEST_F(ValueAssignObjectTest_20, ReturnsSelfReference_AllowsChaining_20) {
    Value v(true);

    Object a;
    a["x"] = Value(1);

    Object b;
    b["y"] = Value(2);

    Value& ret = (v = a);
    EXPECT_EQ(&ret, &v); // must return *this

    // Chaining another Object assignment should still work and leave object 'b' inside v
    (v = a) = b;
    ASSERT_TRUE(v.isObject());
    const Object& got = v.getObject();
    ASSERT_EQ(1u, got.size());
    EXPECT_EQ(2, got.at("y").getInteger());
}

// Copy semantics: assignment must copy, not alias, the source Object.
TEST_F(ValueAssignObjectTest_20, AssignmentCopiesData_NotAliased_20) {
    Object src;
    src["k"] = Value(10);

    Value v;
    v = src;

    // Mutate the source after assignment
    src["k"] = Value(99);
    src["new"] = Value(std::string("added"));

    // v must remain unchanged
    ASSERT_TRUE(v.isObject());
    const Object& got = v.getObject();
    ASSERT_EQ(1u, got.size());          // no "new" key
    EXPECT_EQ(10, got.at("k").getInteger());
}

// Nested structures: nested arrays/objects preserved and readable via accessors.
TEST_F(ValueAssignObjectTest_20, AssignObjectWithNestedStructures_PreservesNested_20) {
    Object nested = ValueAssignObjectTest_20::MakeNestedObject();

    Value v;
    v = nested;

    ASSERT_TRUE(v.isObject());
    const Object& root = v.getObject();

    // Check nested object
    ASSERT_TRUE(root.at("obj").isObject());
    const Object& in = root.at("obj").getObject();
    EXPECT_EQ(-7, in.at("x").getInteger());
    EXPECT_EQ(std::string("yy"), in.at("y").getString());

    // Check nested array
    ASSERT_TRUE(root.at("arr").isArray());
    const Array& arr = root.at("arr").getArray();
    ASSERT_EQ(3u, arr.size());
    EXPECT_EQ(1, arr[0].getInteger());
    EXPECT_EQ(2, arr[1].getInteger());
    EXPECT_EQ(3, arr[2].getInteger());

    // And a simple boolean
    EXPECT_TRUE(root.at("flag").isBoolean());
    EXPECT_FALSE(root.at("flag").getBoolean());
}
