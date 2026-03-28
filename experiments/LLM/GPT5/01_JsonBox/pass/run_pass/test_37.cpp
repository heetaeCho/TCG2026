// File: Value_isNumeric_tests_37.cpp
#include <gtest/gtest.h>
#include <map>
#include <vector>
#include <string>
#include <limits>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueIsNumericTest_37 : public ::testing::Test {};

// ---- Normal operation ----

TEST_F(ValueIsNumericTest_37, ReturnsTrueForIntegerConstructor_37) {
    Value v(42);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueIsNumericTest_37, ReturnsTrueForDoubleConstructor_37) {
    Value v(3.14159);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueIsNumericTest_37, ReturnsFalseForStringConstructor_37) {
    Value v(std::string("123"));
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueIsNumericTest_37, ReturnsFalseForCStringConstructor_37) {
    Value v("456");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueIsNumericTest_37, ReturnsFalseForBooleanConstructor_37) {
    Value v(true);
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueIsNumericTest_37, ReturnsFalseForArrayConstructor_37) {
    Array arr; // empty
    Value v(arr);
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueIsNumericTest_37, ReturnsFalseForObjectConstructor_37) {
    Object obj; // empty
    Value v(obj);
    EXPECT_FALSE(v.isNumeric());
}

// ---- Boundary-ish values (still observable only via type) ----

TEST_F(ValueIsNumericTest_37, ReturnsTrueForNegativeInteger_37) {
    Value v(-1);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueIsNumericTest_37, ReturnsTrueForDoubleNaN_37) {
    Value v(std::numeric_limits<double>::quiet_NaN());
    EXPECT_TRUE(v.isNumeric()); // Type is DOUBLE regardless of the numeric payload
}

// ---- Default and stream constructors (non-numeric by default per interface snippet) ----

TEST_F(ValueIsNumericTest_37, ReturnsFalseForDefaultConstructed_37) {
    Value v;
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueIsNumericTest_37, ReturnsFalseForIStreamConstructorInitialState_37) {
    // The provided header shows Value(std::istream&) initializes as NULL_VALUE.
    std::istringstream iss("{}");
    Value v(iss);
    EXPECT_FALSE(v.isNumeric());
}

// ---- Assignment operations change observable type ----

TEST_F(ValueIsNumericTest_37, BecomesNumericAfterAssigningInteger_37) {
    Value v(std::string("x"));
    ASSERT_FALSE(v.isNumeric());
    v = 7;
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueIsNumericTest_37, BecomesNumericAfterAssigningDouble_37) {
    Value v(false);
    ASSERT_FALSE(v.isNumeric());
    v = 2.5;
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueIsNumericTest_37, BecomesNonNumericAfterAssigningBoolean_37) {
    Value v(123);
    ASSERT_TRUE(v.isNumeric());
    v = true;
    EXPECT_FALSE(v.isNumeric());
}

// ---- Copy construction preserves observable type ----

TEST_F(ValueIsNumericTest_37, CopyFromNumericStaysNumeric_37) {
    Value src(10.0);
    Value copy(src);
    EXPECT_TRUE(copy.isNumeric());
}

TEST_F(ValueIsNumericTest_37, CopyFromNonNumericStaysNonNumeric_37) {
    Value src(std::string("not number"));
    Value copy(src);
    EXPECT_FALSE(copy.isNumeric());
}
