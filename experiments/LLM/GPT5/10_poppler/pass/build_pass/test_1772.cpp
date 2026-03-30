// TEST_ID = 1772
// Unit tests for static helper: isPositive(Object *value)
// File: ./TestProjects/poppler/poppler/StructElement.cc

#include <gtest/gtest.h>

// Include the implementation file to access the TU-local static helper.
// This test is intended to be built as a single translation unit.
#include "StructElement.cc"

namespace {

class IsPositiveTest_1772 : public ::testing::Test {};

// Normal operation: positive integer -> true
TEST_F(IsPositiveTest_1772, PositiveIntegerReturnsTrue_1772)
{
    Object v(1);
    EXPECT_TRUE(isPositive(&v));
}

// Normal operation: positive real -> true
TEST_F(IsPositiveTest_1772, PositiveRealReturnsTrue_1772)
{
    Object v(0.25);
    EXPECT_TRUE(isPositive(&v));
}

// Boundary: zero (int) -> true
TEST_F(IsPositiveTest_1772, ZeroIntegerReturnsTrue_1772)
{
    Object v(0);
    EXPECT_TRUE(isPositive(&v));
}

// Boundary: zero (real) -> true
TEST_F(IsPositiveTest_1772, ZeroRealReturnsTrue_1772)
{
    Object v(0.0);
    EXPECT_TRUE(isPositive(&v));
}

// Boundary: negative values -> false
TEST_F(IsPositiveTest_1772, NegativeNumbersReturnFalse_1772)
{
    Object vi(-1);
    Object vr(-0.0001);
    EXPECT_FALSE(isPositive(&vi));
    EXPECT_FALSE(isPositive(&vr));
}

// Error/exceptional-ish numeric: NaN compares false to >= 0.0 -> expect false
TEST_F(IsPositiveTest_1772, NaNReturnsFalse_1772)
{
    Object v(std::numeric_limits<double>::quiet_NaN());
    ASSERT_TRUE(v.isNum());
    EXPECT_FALSE(isPositive(&v));
}

// Non-numeric types -> false
TEST_F(IsPositiveTest_1772, NonNumericTypesReturnFalse_1772)
{
    Object vb(true);
    Object vs(std::string("123"));
    Object vn = Object::null();
    Object ve = Object::error();
    Object vf = Object::eof();

    EXPECT_FALSE(isPositive(&vb));
    EXPECT_FALSE(isPositive(&vs));
    EXPECT_FALSE(isPositive(&vn));
    EXPECT_FALSE(isPositive(&ve));
    EXPECT_FALSE(isPositive(&vf));
}

} // namespace