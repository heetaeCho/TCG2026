// File: ValueEqualityTest_23.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueEqualityTest_23 : public ::testing::Test {};

TEST_F(ValueEqualityTest_23, SelfEquality_23) {
    Value v1(42);
    EXPECT_TRUE(v1 == v1);
}

TEST_F(ValueEqualityTest_23, NullValues_Equal_23) {
    Value v1;          // default -> NULL_VALUE
    Value v2;          // default -> NULL_VALUE
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueEqualityTest_23, String_EqualAndNotEqual_23) {
    Value a(std::string("hello"));
    Value b(std::string("hello"));
    Value c(std::string("world"));

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

TEST_F(ValueEqualityTest_23, Integer_EqualAndNotEqual_23) {
    Value a(123);
    Value b(123);
    Value c(124);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

TEST_F(ValueEqualityTest_23, Double_EqualAndNotEqual_23) {
    Value a(3.14159);
    Value b(3.14159);
    Value c(2.71828);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

TEST_F(ValueEqualityTest_23, Boolean_EqualAndNotEqual_23) {
    Value t(true);
    Value t2(true);
    Value f(false);

    EXPECT_TRUE(t == t2);
    EXPECT_FALSE(t == f);
}

TEST_F(ValueEqualityTest_23, Array_EqualAndNotEqual_23) {
    Array arr1{ Value(1), Value(std::string("x")), Value(true) };
    Array arr2{ Value(1), Value(std::string("x")), Value(true) };
    Array arr3{ Value(1), Value(std::string("x")), Value(false) }; // one element differs
    Array arr4{ Value(1), Value(std::string("x")) };               // size differs

    Value a(arr1);
    Value b(arr2);
    Value c(arr3);
    Value d(arr4);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
    EXPECT_FALSE(a == d);
}

TEST_F(ValueEqualityTest_23, Object_EqualAndNotEqual_23) {
    Object o1{
        {"a", Value(1)},
        {"b", Value(std::string("bee"))},
        {"c", Value(false)}
    };
    Object o2 = o1; // same key/value set
    Object o3 = o1; o3["c"] = Value(true);           // one value differs
    Object o4{{"a", Value(1)}, {"b", Value("bee")}}; // missing key

    Value v1(o1), v2(o2), v3(o3), v4(o4);

    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
    EXPECT_FALSE(v1 == v4);
}

TEST_F(ValueEqualityTest_23, DifferentTypes_NotEqual_23) {
    Value vi(1);
    Value vd(1.0);
    Value vs("1");
    Value vb(true);
    Array arr{ Value(1) };
    Object obj{{"k", Value(1)}};

    Value va(arr);
    Value vo(obj);

    EXPECT_FALSE(vi == vd); // integer vs double
    EXPECT_FALSE(vi == vs); // integer vs string
    EXPECT_FALSE(vs == vb); // string vs boolean
    EXPECT_FALSE(va == vo); // array vs object
}

TEST_F(ValueEqualityTest_23, CopyConstructed_EqualToOriginal_23) {
    Object o{{"x", Value(10)}, {"y", Value("yes")}};
    Array  a{ Value(1), Value(2), Value(3) };

    Value s(std::string("copy"));
    Value i(777);
    Value d(4.5);
    Value b(true);
    Value obj(o);
    Value arr(a);

    Value s2(s);
    Value i2(i);
    Value d2(d);
    Value b2(b);
    Value obj2(obj);
    Value arr2(arr);

    EXPECT_TRUE(s == s2);
    EXPECT_TRUE(i == i2);
    EXPECT_TRUE(d == d2);
    EXPECT_TRUE(b == b2);
    EXPECT_TRUE(obj == obj2);
    EXPECT_TRUE(arr == arr2);
}
