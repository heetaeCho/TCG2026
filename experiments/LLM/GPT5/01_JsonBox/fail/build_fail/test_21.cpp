// File: Value_AssignArray_Test_21.cpp

#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using JsonBox::Value;
using JsonBox::Array;
using JsonBox::Object;

class ValueAssignArrayTest_21 : public ::testing::Test {};

// Normal operation: assigning a non-empty Array sets type to ARRAY and copies elements.
TEST_F(ValueAssignArrayTest_21, AssignFromArray_SetsTypeAndCopiesElements_21) {
    Array src;
    src.push_back(Value(1));
    src.push_back(Value(2));
    src.push_back(Value(3));

    Value v("before");
    v = src;

    EXPECT_TRUE(v.isArray());
    ASSERT_EQ(v.getArray().size(), src.size());
    EXPECT_EQ(v.getArray(), src);  // relies on std::vector<Value>::operator== and Value::operator==
}

// Boundary: assigning an empty Array results in an empty ARRAY value.
TEST_F(ValueAssignArrayTest_21, AssignEmptyArray_ResultsInEmptyArray_21) {
    Array empty;
    Value v(123);
    v = empty;

    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

// Observable deep copy: modifying the source Array after assignment does not affect the assigned Value.
TEST_F(ValueAssignArrayTest_21, Assign_PerformsCopy_NotAliasingSource_21) {
    Array src;
    src.push_back(Value(10));
    src.push_back(Value(20));

    Value v(true);
    v = src;

    // Mutate the source after assignment
    src[0] = Value(999);
    src.push_back(Value(30));

    // v should remain as the original copy
    ASSERT_TRUE(v.isArray());
    const Array& a = v.getArray();
    ASSERT_EQ(a.size(), 2u);
    EXPECT_TRUE(a[0].isInteger());
    EXPECT_EQ(a[0].getInteger(), 10);
    EXPECT_TRUE(a[1].isInteger());
    EXPECT_EQ(a[1].getInteger(), 20);
}

// Type transition: assigning an Array overwrites previous non-array content and type.
TEST_F(ValueAssignArrayTest_21, Assign_OverwritesPreviousType_21) {
    Object obj;
    obj["k"] = Value("v");
    Value v(obj);  // start as OBJECT
    ASSERT_TRUE(v.isObject());

    Array src;
    src.push_back(Value("x"));
    v = src;

    EXPECT_TRUE(v.isArray());
    EXPECT_FALSE(v.isObject());
    ASSERT_EQ(v.getArray().size(), 1u);
    EXPECT_TRUE(v.getArray()[0].isString());
    EXPECT_EQ(v.getArray()[0].getString(), std::string("x"));
}

// Self-assignment style: assigning from the Value's own getArray() should be stable (no change).
TEST_F(ValueAssignArrayTest_21, AssignFromOwnGetArray_IsStable_21) {
    Array initial;
    initial.push_back(Value(1));
    initial.push_back(Value(2));

    Value v(initial);
    const Array& selfRef = v.getArray();  // safe because v is ARRAY
    v = selfRef;

    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray(), initial);
}

// Nested structures: ensure nested arrays/objects are preserved on assignment.
TEST_F(ValueAssignArrayTest_21, Assign_PreservesNestedStructures_21) {
    Array nested;
    nested.push_back(Value(1));

    Array inner;
    inner.push_back(Value(2));
    inner.push_back(Value(3));
    nested.push_back(Value(inner));  // nested array

    Object o;
    o["a"] = Value(4);
    nested.push_back(Value(o));  // object element

    Value v("placeholder");
    v = nested;

    ASSERT_TRUE(v.isArray());
    const Array& a = v.getArray();
    ASSERT_EQ(a.size(), 3u);

    // [0] -> 1
    EXPECT_TRUE(a[0].isInteger());
    EXPECT_EQ(a[0].getInteger(), 1);

    // [1] -> inner array [2,3]
    ASSERT_TRUE(a[1].isArray());
    ASSERT_EQ(a[1].getArray().size(), 2u);
    EXPECT_TRUE(a[1].getArray()[0].isInteger());
    EXPECT_EQ(a[1].getArray()[0].getInteger(), 2);
    EXPECT_TRUE(a[1].getArray()[1].isInteger());
    EXPECT_EQ(a[1].getArray()[1].getInteger(), 3);

    // [2] -> object {"a":4}
    ASSERT_TRUE(a[2].isObject());
    // Access via operator[] to verify presence & value
    Value &objA = a[2]["a"];
    EXPECT_TRUE(objA.isInteger());
    EXPECT_EQ(objA.getInteger(), 4);
}
