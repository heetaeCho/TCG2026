// File: Value_IsArray_Test_39.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using JsonBox::Value;
using JsonBox::Array;
using JsonBox::Object;

class ValueIsArrayTest_39 : public ::testing::Test {};

// --- Normal operation ---

TEST_F(ValueIsArrayTest_39, ReturnsTrueForArrayConstructor_39) {
    Array arr; // empty array
    Value v(arr);
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueIsArrayTest_39, ReturnsFalseForStringConstructor_39) {
    Value v(std::string("hello"));
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueIsArrayTest_39, ReturnsFalseForCStringConstructor_39) {
    Value v("hello");
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueIsArrayTest_39, ReturnsFalseForIntegerConstructor_39) {
    Value v(123);
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueIsArrayTest_39, ReturnsFalseForDoubleConstructor_39) {
    Value v(3.14);
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueIsArrayTest_39, ReturnsFalseForBooleanConstructor_39) {
    Value v(true);
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueIsArrayTest_39, ReturnsFalseForObjectConstructor_39) {
    Object o;
    Value v(o);
    EXPECT_FALSE(v.isArray());
}

// --- Boundary conditions ---

TEST_F(ValueIsArrayTest_39, DefaultConstructedIsNotArray_39) {
    Value v;
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueIsArrayTest_39, StreamConstructedIsNotArray_39) {
    std::istringstream in("[]"); // implementation is a black box; ctor should not be array by itself
    Value v(in);
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueIsArrayTest_39, NonEmptyArrayStillReportsArray_39) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
}

// --- Copy / assignment semantics ---

TEST_F(ValueIsArrayTest_39, CopyConstructorPreservesArrayType_39) {
    Value src(Array{});   // array
    Value copy(src);
    EXPECT_TRUE(src.isArray());
    EXPECT_TRUE(copy.isArray());
}

TEST_F(ValueIsArrayTest_39, CopyAssignmentPreservesArrayType_39) {
    Value src(Array{});   // array
    Value dst("not array");
    dst = src;
    EXPECT_TRUE(dst.isArray());
}

TEST_F(ValueIsArrayTest_39, AssignArrayFromNonArrayChangesTypeToArray_39) {
    Value v(42);
    EXPECT_FALSE(v.isArray());
    v = Array{};
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueIsArrayTest_39, AssignNonArrayFromArrayChangesTypeToNonArray_39) {
    Value v(Array{});
    ASSERT_TRUE(v.isArray());
    v = 0; // integer
    EXPECT_FALSE(v.isArray());
}

// --- Mutators / setters ---

TEST_F(ValueIsArrayTest_39, SetArrayChangesTypeToArray_39) {
    Value v(false);
    ASSERT_FALSE(v.isArray());
    v.setArray(Array{});
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueIsArrayTest_39, SetStringFromArrayChangesTypeToNonArray_39) {
    Value v(Array{});
    ASSERT_TRUE(v.isArray());
    v.setString("x");
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueIsArrayTest_39, SetNullFromArrayChangesTypeToNonArray_39) {
    Value v(Array{});
    ASSERT_TRUE(v.isArray());
    v.setNull();
    EXPECT_FALSE(v.isArray());
}
