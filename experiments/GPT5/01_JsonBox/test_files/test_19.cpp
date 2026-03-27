// File: tests/Value_AssignDouble_19_test.cpp

#include <gtest/gtest.h>
#include <limits>
#include <cmath>
#include "JsonBox/Value.h"

using JsonBox::Value;

namespace {

// Normal operation: assigning a double sets numeric/double state and value.
TEST(ValueAssignDoubleTest_19, AssignDouble_SetsDoubleAndNumeric_19) {
    Value v;                 // default-constructed (null per header, but we don't rely on it)
    const double d = 3.141592653589793;
    v = d;

    EXPECT_TRUE(v.isDouble());
    EXPECT_TRUE(v.isNumeric());
    EXPECT_NEAR(v.getDouble(), d, 1e-12);
}

// Overwrite previous type: from string -> double
TEST(ValueAssignDoubleTest_19, AssignDouble_OverwritesPreviousType_19) {
    Value v(std::string("hello"));
    ASSERT_TRUE(v.isString());          // precondition via public API

    v = 2.5;

    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isString());
    EXPECT_NEAR(v.getDouble(), 2.5, 1e-12);
}

// Return value: operator= should return a reference to *this (enables chaining)
TEST(ValueAssignDoubleTest_19, AssignDouble_ReturnsSelfForChaining_19) {
    Value v;

    Value* ret = &(v = 1.0);            // capture returned reference address
    EXPECT_EQ(ret, &v);

    // chaining assignment should leave the object holding the last assigned value
    (v = 1.1) = 2.2;
    EXPECT_TRUE(v.isDouble());
    EXPECT_NEAR(v.getDouble(), 2.2, 1e-12);
}

// Boundary: +inf and -inf should round-trip via getDouble()
TEST(ValueAssignDoubleTest_19, AssignDouble_HandlesInfinity_19) {
    const double pos_inf = std::numeric_limits<double>::infinity();
    const double neg_inf = -std::numeric_limits<double>::infinity();

    Value v;
    v = pos_inf;
    EXPECT_TRUE(v.isDouble());
    EXPECT_TRUE(std::isinf(v.getDouble()));
    EXPECT_FALSE(std::signbit(v.getDouble()));  // positive

    v = neg_inf;
    EXPECT_TRUE(v.isDouble());
    EXPECT_TRUE(std::isinf(v.getDouble()));
    EXPECT_TRUE(std::signbit(v.getDouble()));   // negative
}

// Boundary: NaN should be preserved as NaN (not equal to itself)
TEST(ValueAssignDoubleTest_19, AssignDouble_HandlesNaN_19) {
    const double nanv = std::numeric_limits<double>::quiet_NaN();

    Value v;
    v = nanv;

    EXPECT_TRUE(v.isDouble());
    EXPECT_TRUE(std::isnan(v.getDouble()));
}

// Boundary: signed zero behavior (+0.0 vs -0.0)
TEST(ValueAssignDoubleTest_19, AssignDouble_SignedZero_19) {
    Value v;

    v = 0.0;
    EXPECT_TRUE(v.isDouble());
    EXPECT_EQ(0.0, v.getDouble());
    EXPECT_FALSE(std::signbit(v.getDouble()));  // +0.0

    v = -0.0;
    EXPECT_TRUE(v.isDouble());
    // Value is still zero numerically...
    EXPECT_EQ(0.0, v.getDouble());
    // ...but sign bit should be set for -0.0
    EXPECT_TRUE(std::signbit(v.getDouble()));
}

// Sanity: tryGetDouble returns the assigned value when type is double
TEST(ValueAssignDoubleTest_19, AssignDouble_TryGetDoubleReturnsValue_19) {
    Value v;
    v = 42.75;

    EXPECT_TRUE(v.isDouble());
    EXPECT_NEAR(v.tryGetDouble(-1.0), 42.75, 1e-12);
}

} // namespace
