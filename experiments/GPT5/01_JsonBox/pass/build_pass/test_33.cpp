// File: Value_IsString_Test_33.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueIsStringTest_33 : public ::testing::Test {};

// --- Normal operation ---

TEST_F(ValueIsStringTest_33, DefaultIsNotString_33) {
    Value v; // default-constructed
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueIsStringTest_33, StringCtorReturnsTrue_33) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
}

TEST_F(ValueIsStringTest_33, CStringCtorEmptyReturnsTrue_33) {
    Value v(""); // const char* ctor
    EXPECT_TRUE(v.isString());
}

// --- Other types should report false ---

TEST_F(ValueIsStringTest_33, IntegerCtorIsNotString_33) {
    Value v(123);
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueIsStringTest_33, DoubleCtorIsNotString_33) {
    Value v(3.14);
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueIsStringTest_33, BoolCtorIsNotString_33) {
    Value v(true);
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueIsStringTest_33, ObjectCtorIsNotString_33) {
    Object o;
    o["k"] = Value(1);
    Value v(o);
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueIsStringTest_33, ArrayCtorIsNotString_33) {
    Array a;
    a.push_back(Value(1));
    Value v(a);
    EXPECT_FALSE(v.isString());
}

// --- Assignment behavior (observable via isString) ---

TEST_F(ValueIsStringTest_33, AssignFromStringSetsToString_33) {
    Value v(42);              // start non-string
    v = std::string("x");     // assign string
    EXPECT_TRUE(v.isString());
}

TEST_F(ValueIsStringTest_33, AssignFromCStringSetsToString_33) {
    Value v(false);           // start non-string
    v = "abc";                // assign C-string
    EXPECT_TRUE(v.isString());
}

TEST_F(ValueIsStringTest_33, AssignFromNonStringUnsetsString_33) {
    Value v(std::string("was string"));
    v = 7;                    // assign int
    EXPECT_FALSE(v.isString());
}

// --- Copy semantics preserve observable state ---

TEST_F(ValueIsStringTest_33, CopyConstructorPreservesIsString_33) {
    Value original(std::string("hi"));
    Value copy(original);
    EXPECT_TRUE(original.isString());
    EXPECT_EQ(original.isString(), copy.isString());
}
