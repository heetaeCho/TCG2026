// File: tests/ValueLessThanTest_25.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using JsonBox::Value;
using JsonBox::Array;
using JsonBox::Object;

TEST(ValueLessThan_25, SelfCompareIsFalse_25) {
    Value v1(42);
    EXPECT_FALSE(v1 < v1);
}

TEST(ValueLessThan_25, EqualSameTypeIsFalse_25) {
    Value s1(std::string("abc")), s2(std::string("abc"));
    Value i1(10), i2(10);
    Value d1(1.5), d2(1.5);
    Value b1(true), b2(true);

    EXPECT_FALSE(s1 < s2);
    EXPECT_FALSE(i1 < i2);
    EXPECT_FALSE(d1 < d2);
    EXPECT_FALSE(b1 < b2);
}

TEST(ValueLessThan_25, StringOrdering_25) {
    Value a(std::string("abc"));
    Value b(std::string("abd"));
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(ValueLessThan_25, IntegerOrdering_25) {
    Value a(1), b(2);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(ValueLessThan_25, DoubleOrdering_25) {
    Value a(1.0), b(1.1);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(ValueLessThan_25, BooleanOrdering_25) {
    Value f(false), t(true);
    EXPECT_TRUE(f < t);
    EXPECT_FALSE(t < f);
}

TEST(ValueLessThan_25, ArrayLexicographical_25) {
    Array a1; a1.push_back(Value(1)); a1.push_back(Value(2));
    Array a2; a2.push_back(Value(1)); a2.push_back(Value(3));
    Value v1(a1), v2(a2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);

    // Prefix rule: [1] < [1, 0]
    Array a3; a3.push_back(Value(1));
    Array a4; a4.push_back(Value(1)); a4.push_back(Value(0));
    Value v3(a3), v4(a4);
    EXPECT_TRUE(v3 < v4);
    EXPECT_FALSE(v4 < v3);
}

TEST(ValueLessThan_25, ObjectLexicographical_25) {
    Object o1; o1["a"] = Value(1); o1["b"] = Value(2);
    Object o2; o2["a"] = Value(1); o2["b"] = Value(3);
    Value v1(o1), v2(o2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST(ValueLessThan_25, DifferentTypesAlwaysFalse_25) {
    // Same “numeric” value but different types → must be false both ways.
    Value vi(1);
    Value vd(1.0);
    EXPECT_FALSE(vi < vd);
    EXPECT_FALSE(vd < vi);

    // String vs int
    Value vs(std::string("1"));
    EXPECT_FALSE(vs < vi);
    EXPECT_FALSE(vi < vs);

    // Array vs Object
    Value va(Array{Value(1)});
    Object obj; obj["x"] = Value(1);
    Value vo(obj);
    EXPECT_FALSE(va < vo);
    EXPECT_FALSE(vo < va);

    // Boolean vs anything
    Value vb(true);
    EXPECT_FALSE(vb < vs);
    EXPECT_FALSE(vs < vb);
}

TEST(ValueLessThan_25, NullValuesNeverLessThan_25) {
    Value n1; // default-constructed NULL_VALUE
    Value n2;
    EXPECT_FALSE(n1 < n2);
    EXPECT_FALSE(n2 < n1);

    // Null vs any other type is also false both ways.
    Value vi(0);
    EXPECT_FALSE(n1 < vi);
    EXPECT_FALSE(vi < n1);
}
