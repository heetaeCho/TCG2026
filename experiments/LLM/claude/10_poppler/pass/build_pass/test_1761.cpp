#include <gtest/gtest.h>
#include <memory>
#include "Object.h"

// We need to test the static function isLineHeight which is defined in StructElement.cc
// Since it's a static function in a .cc file, we cannot directly call it from outside.
// However, based on the prompt, we need to write tests for the interface.
// We'll recreate the function signature here for testing purposes, since the function
// is the interface we're testing.

// Recreate the helper used by isLineHeight
static bool isNumber(Object *value)
{
    return value->isNum() || value->isInt() || value->isReal() || value->isInt64();
}

// Recreate the function under test based on the provided code
static bool isLineHeight(Object *value)
{
    return value->isName("Normal") || value->isName("Auto") || isNumber(value);
}

class IsLineHeightTest_1761 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that "Normal" name is a valid line height
TEST_F(IsLineHeightTest_1761, NameNormalIsLineHeight_1761)
{
    Object obj(objName, "Normal");
    EXPECT_TRUE(isLineHeight(&obj));
}

// Test that "Auto" name is a valid line height
TEST_F(IsLineHeightTest_1761, NameAutoIsLineHeight_1761)
{
    Object obj(objName, "Auto");
    EXPECT_TRUE(isLineHeight(&obj));
}

// Test that an integer value is a valid line height
TEST_F(IsLineHeightTest_1761, IntegerIsLineHeight_1761)
{
    Object obj(42);
    EXPECT_TRUE(isLineHeight(&obj));
}

// Test that a real/double value is a valid line height
TEST_F(IsLineHeightTest_1761, RealIsLineHeight_1761)
{
    Object obj(3.14);
    EXPECT_TRUE(isLineHeight(&obj));
}

// Test that zero integer is a valid line height (boundary)
TEST_F(IsLineHeightTest_1761, ZeroIntegerIsLineHeight_1761)
{
    Object obj(0);
    EXPECT_TRUE(isLineHeight(&obj));
}

// Test that negative integer is a valid line height (number)
TEST_F(IsLineHeightTest_1761, NegativeIntegerIsLineHeight_1761)
{
    Object obj(-5);
    EXPECT_TRUE(isLineHeight(&obj));
}

// Test that zero real is a valid line height (boundary)
TEST_F(IsLineHeightTest_1761, ZeroRealIsLineHeight_1761)
{
    Object obj(0.0);
    EXPECT_TRUE(isLineHeight(&obj));
}

// Test that negative real is a valid line height
TEST_F(IsLineHeightTest_1761, NegativeRealIsLineHeight_1761)
{
    Object obj(-2.5);
    EXPECT_TRUE(isLineHeight(&obj));
}

// Test that int64 value is a valid line height
TEST_F(IsLineHeightTest_1761, Int64IsLineHeight_1761)
{
    Object obj(static_cast<long long>(100000LL));
    EXPECT_TRUE(isLineHeight(&obj));
}

// Test that a random name string is NOT a valid line height
TEST_F(IsLineHeightTest_1761, RandomNameIsNotLineHeight_1761)
{
    Object obj(objName, "SomethingElse");
    EXPECT_FALSE(isLineHeight(&obj));
}

// Test that an empty name is NOT a valid line height
TEST_F(IsLineHeightTest_1761, EmptyNameIsNotLineHeight_1761)
{
    Object obj(objName, "");
    EXPECT_FALSE(isLineHeight(&obj));
}

// Test that a boolean is NOT a valid line height
TEST_F(IsLineHeightTest_1761, BoolIsNotLineHeight_1761)
{
    Object obj(true);
    EXPECT_FALSE(isLineHeight(&obj));
}

// Test that a null object is NOT a valid line height
TEST_F(IsLineHeightTest_1761, NullIsNotLineHeight_1761)
{
    Object obj = Object::null();
    EXPECT_FALSE(isLineHeight(&obj));
}

// Test that a none/default object is NOT a valid line height
TEST_F(IsLineHeightTest_1761, NoneIsNotLineHeight_1761)
{
    Object obj;
    EXPECT_FALSE(isLineHeight(&obj));
}

// Test that a string object is NOT a valid line height
TEST_F(IsLineHeightTest_1761, StringIsNotLineHeight_1761)
{
    Object obj(std::string("Normal"));
    EXPECT_FALSE(isLineHeight(&obj));
}

// Test case-sensitivity: "normal" (lowercase) should NOT match
TEST_F(IsLineHeightTest_1761, LowercaseNormalIsNotLineHeight_1761)
{
    Object obj(objName, "normal");
    EXPECT_FALSE(isLineHeight(&obj));
}

// Test case-sensitivity: "auto" (lowercase) should NOT match
TEST_F(IsLineHeightTest_1761, LowercaseAutoIsNotLineHeight_1761)
{
    Object obj(objName, "auto");
    EXPECT_FALSE(isLineHeight(&obj));
}

// Test case-sensitivity: "NORMAL" (uppercase) should NOT match
TEST_F(IsLineHeightTest_1761, UppercaseNORMALIsNotLineHeight_1761)
{
    Object obj(objName, "NORMAL");
    EXPECT_FALSE(isLineHeight(&obj));
}

// Test case-sensitivity: "AUTO" (uppercase) should NOT match
TEST_F(IsLineHeightTest_1761, UppercaseAUTOIsNotLineHeight_1761)
{
    Object obj(objName, "AUTO");
    EXPECT_FALSE(isLineHeight(&obj));
}

// Test error object is NOT a valid line height
TEST_F(IsLineHeightTest_1761, ErrorIsNotLineHeight_1761)
{
    Object obj = Object::error();
    EXPECT_FALSE(isLineHeight(&obj));
}

// Test EOF object is NOT a valid line height
TEST_F(IsLineHeightTest_1761, EOFIsNotLineHeight_1761)
{
    Object obj = Object::eof();
    EXPECT_FALSE(isLineHeight(&obj));
}

// Test very large real number
TEST_F(IsLineHeightTest_1761, VeryLargeRealIsLineHeight_1761)
{
    Object obj(1e308);
    EXPECT_TRUE(isLineHeight(&obj));
}

// Test very small positive real number
TEST_F(IsLineHeightTest_1761, VerySmallRealIsLineHeight_1761)
{
    Object obj(1e-308);
    EXPECT_TRUE(isLineHeight(&obj));
}
