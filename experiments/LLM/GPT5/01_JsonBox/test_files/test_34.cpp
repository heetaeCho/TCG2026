// File: Value_IsStringable_Test_34.cpp
#include <gtest/gtest.h>
#include <map>
#include <string>
#include <vector>
#include "JsonBox/Value.h"

using JsonBox::Value;
using JsonBox::Object;
using JsonBox::Array;

//
// The tests exercise only public APIs and observable behavior.
// No reliance on private state or inferring internal logic.
//

// ---------- Normal operation: primitive types ----------

TEST(ValueIsStringableTest_34, StringReturnsTrue_34) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isStringable());
}

TEST(ValueIsStringableTest_34, IntegerReturnsTrue_34) {
    Value v(42);
    EXPECT_TRUE(v.isStringable());
}

TEST(ValueIsStringableTest_34, DoubleReturnsTrue_34) {
    Value v(3.14);
    EXPECT_TRUE(v.isStringable());
}

TEST(ValueIsStringableTest_34, BooleanReturnsTrue_34) {
    Value v(true);
    EXPECT_TRUE(v.isStringable());
}

TEST(ValueIsStringableTest_34, NullReturnsTrue_34) {
    Value v; // default-constructed (NULL_VALUE)
    EXPECT_TRUE(v.isStringable());
}

// ---------- Containers: should not be stringable ----------

TEST(ValueIsStringableTest_34, ObjectReturnsFalse_34) {
    Object o;
    o["k"] = Value("v");
    Value v(o);
    EXPECT_FALSE(v.isStringable());
}

TEST(ValueIsStringableTest_34, ArrayReturnsFalse_34) {
    Array a;
    a.push_back(Value(1));
    a.push_back(Value("x"));
    Value v(a);
    EXPECT_FALSE(v.isStringable());
}

// ---------- Boundary-ish: empty containers ----------

TEST(ValueIsStringableTest_34, EmptyObjectReturnsFalse_34) {
    Object empty;
    Value v(empty);
    EXPECT_FALSE(v.isStringable());
}

TEST(ValueIsStringableTest_34, EmptyArrayReturnsFalse_34) {
    Array empty;
    Value v(empty);
    EXPECT_FALSE(v.isStringable());
}

// ---------- Copy semantics: observable behavior preserved ----------

TEST(ValueIsStringableTest_34, CopyPreservesStringableForPrimitive_34) {
    Value src(7);
    Value copy(src);
    EXPECT_TRUE(src.isStringable());
    EXPECT_TRUE(copy.isStringable());
}

TEST(ValueIsStringableTest_34, CopyPreservesStringableForContainer_34) {
    Array a; a.push_back(Value("x"));
    Value src(a);
    Value copy(src);
    EXPECT_FALSE(src.isStringable());
    EXPECT_FALSE(copy.isStringable());
}

// ---------- Assignment: observable type change reflected ----------

TEST(ValueIsStringableTest_34, AssignmentFromObjectToStringableBecomesTrue_34) {
    Object o; o["a"] = Value(1);
    Value v(o);                   // not stringable
    v = std::string("now");       // become stringable
    EXPECT_TRUE(v.isStringable());
}

TEST(ValueIsStringableTest_34, AssignmentFromStringToArrayBecomesFalse_34) {
    Value v(std::string("s"));    // stringable
    Array a; a.push_back(Value(false));
    v = a;                        // become non-stringable
    EXPECT_FALSE(v.isStringable());
}
