// File: Value_getInteger_tests_46.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"
#include <limits>

using namespace JsonBox;

class ValueGetIntegerTest_46 : public ::testing::Test {};

// Normal operation: returns the stored integer when the value is constructed with an int.
TEST_F(ValueGetIntegerTest_46, ReturnsStoredPositiveInteger_46) {
    Value v(123);
    EXPECT_EQ(123, v.getInteger());
}

TEST_F(ValueGetIntegerTest_46, ReturnsStoredNegativeInteger_46) {
    Value v(-42);
    EXPECT_EQ(-42, v.getInteger());
}

// Boundary conditions with int limits (constructed via public int constructor).
TEST_F(ValueGetIntegerTest_46, ReturnsIntMin_46) {
    Value v(std::numeric_limits<int>::min());
    EXPECT_EQ(std::numeric_limits<int>::min(), v.getInteger());
}

TEST_F(ValueGetIntegerTest_46, ReturnsIntMax_46) {
    Value v(std::numeric_limits<int>::max());
    EXPECT_EQ(std::numeric_limits<int>::max(), v.getInteger());
}

// Delegation contract: getInteger() must match tryGetInteger(EMPTY_INT) for non-integer types.
// This treats implementation as a black box and checks observable equivalence only.
TEST_F(ValueGetIntegerTest_46, MatchesTryGetIntegerForString_46) {
    Value v(std::string("hello"));
    int expected = v.tryGetInteger(EMPTY_INT);
    EXPECT_EQ(expected, v.getInteger());
}

TEST_F(ValueGetIntegerTest_46, MatchesTryGetIntegerForCString_46) {
    Value v("123");
    int expected = v.tryGetInteger(EMPTY_INT);
    EXPECT_EQ(expected, v.getInteger());
}

TEST_F(ValueGetIntegerTest_46, MatchesTryGetIntegerForDouble_46) {
    Value v(3.75);
    int expected = v.tryGetInteger(EMPTY_INT);
    EXPECT_EQ(expected, v.getInteger());
}

TEST_F(ValueGetIntegerTest_46, MatchesTryGetIntegerForBooleanTrue_46) {
    Value v(true);
    int expected = v.tryGetInteger(EMPTY_INT);
    EXPECT_EQ(expected, v.getInteger());
}

TEST_F(ValueGetIntegerTest_46, MatchesTryGetIntegerForBooleanFalse_46) {
    Value v(false);
    int expected = v.tryGetInteger(EMPTY_INT);
    EXPECT_EQ(expected, v.getInteger());
}

TEST_F(ValueGetIntegerTest_46, MatchesTryGetIntegerForNull_46) {
    Value v; // default constructs to null per interface
    int expected = v.tryGetInteger(EMPTY_INT);
    EXPECT_EQ(expected, v.getInteger());
}

TEST_F(ValueGetIntegerTest_46, MatchesTryGetIntegerForObject_46) {
    Object o; o["k"] = Value(7);
    Value v(o);
    int expected = v.tryGetInteger(EMPTY_INT);
    EXPECT_EQ(expected, v.getInteger());
}

TEST_F(ValueGetIntegerTest_46, MatchesTryGetIntegerForArray_46) {
    Array a; a.push_back(Value(1)); a.push_back(Value(2));
    Value v(a);
    int expected = v.tryGetInteger(EMPTY_INT);
    EXPECT_EQ(expected, v.getInteger());
}

// Ensure calling getInteger() does not mutate the Value's type (observable via getType()).
TEST_F(ValueGetIntegerTest_46, GetIntegerDoesNotChangeType_String_46) {
    Value v(std::string("xyz"));
    Value::Type before = v.getType();
    (void)v.getInteger();
    Value::Type after = v.getType();
    EXPECT_EQ(before, after);
}

TEST_F(ValueGetIntegerTest_46, GetIntegerDoesNotChangeType_Integer_46) {
    Value v(10);
    Value::Type before = v.getType();
    (void)v.getInteger();
    Value::Type after = v.getType();
    EXPECT_EQ(before, after);
}
