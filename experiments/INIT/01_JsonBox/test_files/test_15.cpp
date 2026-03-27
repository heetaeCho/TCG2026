// File: Value_CopyAssignmentTest_15.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using JsonBox::Value;
using JsonBox::Object;
using JsonBox::Array;

class ValueCopyAssignTest_15 : public ::testing::Test {
protected:
    // Helper to read an object field safely for assertions.
    static int GetObjectInt(const Value& v, const std::string& key, int fallback = INT_MIN) {
        const Object& obj = v.getObject();
        Object::const_iterator it = obj.find(key);
        if (it == obj.end()) return fallback;
        return it->second.getInteger();
    }
};

/* Normal operation: assign STRING -> NULL */
TEST_F(ValueCopyAssignTest_15, CopyAssign_StringCopiesValue_15) {
    Value src(std::string("hello"));
    Value dst; // null

    dst = src;

    EXPECT_TRUE(dst.isString());
    EXPECT_EQ(std::string("hello"), dst.getString());
}

/* Normal operation: assign INTEGER -> NULL */
TEST_F(ValueCopyAssignTest_15, CopyAssign_IntegerCopiesValue_15) {
    Value src(123);
    Value dst;

    dst = src;

    EXPECT_TRUE(dst.isInteger());
    EXPECT_EQ(123, dst.getInteger());
}

/* Normal operation: assign DOUBLE overwrites previous INTEGER */
TEST_F(ValueCopyAssignTest_15, CopyAssign_DifferentTypeOverwrites_15) {
    Value src(3.14159);
    Value dst(42); // start as integer

    dst = src;

    EXPECT_TRUE(dst.isDouble());
    EXPECT_DOUBLE_EQ(3.14159, dst.getDouble());
    EXPECT_FALSE(dst.isInteger());
}

/* Boundary: self-assignment should be a no-op */
TEST_F(ValueCopyAssignTest_15, CopyAssign_SelfAssignment_NoChange_15) {
    Value v(42);
    v = v; // self-assign

    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(42, v.getInteger());
}

/* Boundary: assigning from NULL should make destination NULL */
TEST_F(ValueCopyAssignTest_15, CopyAssign_FromNullResultsInNull_15) {
    Value src;            // null
    Value dst("not null"); // make sure dst had a value

    dst = src;

    EXPECT_TRUE(dst.isNull());
}

/* Object deep copy: mutate source after assignment, destination must not change */
TEST_F(ValueCopyAssignTest_15, CopyAssign_ObjectIsDeepCopied_15) {
    Object o;
    o["a"] = Value(1);
    Value src(o);
    Value dst;

    dst = src;

    // Mutate source after copy
    src["a"].setInteger(2);      // change existing key
    src["b"].setInteger(3);      // add new key

    // Destination should remain with original content
    EXPECT_TRUE(dst.isObject());
    EXPECT_EQ(1, GetObjectInt(dst, "a"));
    EXPECT_EQ(INT_MIN, GetObjectInt(dst, "b", INT_MIN)); // "b" should not exist
}

/* Array deep copy: mutate source elements after assignment, destination must not change */
TEST_F(ValueCopyAssignTest_15, CopyAssign_ArrayIsDeepCopied_15) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value src(arr);
    Value dst;

    dst = src;

    // Mutate source array elements after copy
    ASSERT_TRUE(src.isArray());
    src[0].setInteger(10);
    src[1].setInteger(20);

    // Destination should retain original element values
    ASSERT_TRUE(dst.isArray());
    EXPECT_EQ(1, dst[0].getInteger());
    EXPECT_EQ(2, dst[1].getInteger());
}

/* Boolean copy */
TEST_F(ValueCopyAssignTest_15, CopyAssign_BooleanCopiesValue_15) {
    Value src(true);
    Value dst(false); // ensure different initial state

    dst = src;

    EXPECT_TRUE(dst.isBoolean());
    EXPECT_TRUE(dst.getBoolean());
}

/* Equality observable behavior: equals immediately after copy, not equal after source mutation */
TEST_F(ValueCopyAssignTest_15, CopyAssign_EqualityThenDivergence_15) {
    Object o;
    o["x"] = Value(7);
    Value src(o);
    Value dst;

    dst = src;
    EXPECT_TRUE(dst == src); // immediately equal

    // mutate source after assignment
    src["x"].setInteger(8);

    EXPECT_TRUE(dst != src); // should now differ
}
