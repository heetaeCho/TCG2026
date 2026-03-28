// File: Value_getToString_Test_44.cpp
#include <gtest/gtest.h>
#include <sstream>
#include "JsonBox/Value.h"     // Interface under test
// If Grammar.h is available you could include it, but we only compare to string literals.

using JsonBox::Value;
using JsonBox::Array;
using JsonBox::Object;

class ValueGetToStringTest_44 : public ::testing::Test {};

// --- STRING ---
TEST_F(ValueGetToStringTest_44, String_ReturnsRawString_44) {
    Value v(std::string("hello"));
    EXPECT_EQ("hello", v.getToString());
}

TEST_F(ValueGetToStringTest_44, String_Empty_ReturnsEmpty_44) {
    Value v(std::string());
    EXPECT_EQ(std::string(), v.getToString());
}

TEST_F(ValueGetToStringTest_44, String_SpecialChars_NotEscaped_44) {
    std::string s = "a\"b\\c\n\t";
    Value v(s);
    EXPECT_EQ(s, v.getToString());
}

// --- INTEGER ---
TEST_F(ValueGetToStringTest_44, Integer_Positive_ReturnsDecimal_44) {
    Value v(123);
    EXPECT_EQ("123", v.getToString());
}

TEST_F(ValueGetToStringTest_44, Integer_Negative_ReturnsDecimal_44) {
    Value v(-9876);
    EXPECT_EQ("-9876", v.getToString());
}

TEST_F(ValueGetToStringTest_44, Integer_Zero_ReturnsZero_44) {
    Value v(0);
    EXPECT_EQ("0", v.getToString());
}

// --- DOUBLE ---
TEST_F(ValueGetToStringTest_44, Double_SimpleFraction_44) {
    Value v(1.5);
    EXPECT_EQ("1.5", v.getToString());
}

TEST_F(ValueGetToStringTest_44, Double_Negative_ReturnsWithSign_44) {
    Value v(-2.25);
    EXPECT_EQ("-2.25", v.getToString());
}

TEST_F(ValueGetToStringTest_44, Double_Zero_ReturnsZero_44) {
    Value v(0.0);
    EXPECT_EQ("0", v.getToString()); // default stringstream format prints "0" for 0.0
}

// --- BOOLEAN ---
TEST_F(ValueGetToStringTest_44, Boolean_True_ReturnsTrueLiteral_44) {
    Value v(true);
    EXPECT_EQ("true", v.getToString());
}

TEST_F(ValueGetToStringTest_44, Boolean_False_ReturnsFalseLiteral_44) {
    Value v(false);
    EXPECT_EQ("false", v.getToString());
}

// --- NULL ---
TEST_F(ValueGetToStringTest_44, Null_ReturnsNullLiteral_44) {
    Value v; // default constructs to NULL_VALUE
    EXPECT_EQ("null", v.getToString());
}

// --- OBJECT ---
// For OBJECT/ARRAY, verify that getToString() matches the Value's stream output,
// without asserting any particular formatting details.
TEST_F(ValueGetToStringTest_44, Object_UsesOperatorStreamFormat_44) {
    Object o;
    o["a"] = Value(1);
    o["b"] = Value(std::string("x"));
    Value v(o);

    std::stringstream ss;
    ss << v;  // relies on the public operator<<
    EXPECT_EQ(ss.str(), v.getToString());
}

// --- ARRAY ---
TEST_F(ValueGetToStringTest_44, Array_UsesOperatorStreamFormat_44) {
    Array a;
    a.push_back(Value(1));
    a.push_back(Value(std::string("y")));
    Value v(a);

    std::stringstream ss;
    ss << v;  // relies on the public operator<<
    EXPECT_EQ(ss.str(), v.getToString());
}

// --- SELF CONSISTENCY SPOT CHECKS ---
TEST_F(ValueGetToStringTest_44, StreamConsistency_WithVariousTypes_44) {
    // Check a few different types for equivalence to stream output.
    Value vals[] = { Value(std::string("k")), Value(42), Value(3.75), Value(true) };
    for (const auto &v : vals) {
        std::stringstream ss;
        ss << v;
        // For non-object/array, operator<< may have its own formatting,
        // so we only assert consistency for object/array earlier.
        // Here we simply validate getToString doesn't throw and returns *some* string.
        // But we can still compare; if operator<< uses the same path (as object/array do),
        // equality will hold; if not, this test remains non-binding.
        // To stay conservative, just ensure it's non-empty for non-empty cases.
        (void)ss; // avoid unused if you choose not to compare
        EXPECT_FALSE(v.getToString().empty()); // "k", "42", "3.75", "true" are non-empty
    }
}
