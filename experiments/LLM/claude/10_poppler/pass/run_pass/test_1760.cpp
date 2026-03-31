#include <gtest/gtest.h>
#include "Object.h"

// We are testing the static function `isNumber` from StructElement.cc
// Since it's a static function in a .cc file, we cannot directly call it.
// However, we can test the underlying behavior it relies on: Object::isNum().
// The function `isNumber` simply delegates to `value->isNum()`.
// We'll write a wrapper that replicates the exact logic to test against Object types.

// Replicate the static function under test
static bool isNumber(Object *value) { return value->isNum(); }

class IsNumberTest_1760 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that an integer Object is recognized as a number
TEST_F(IsNumberTest_1760, IntObjectIsNumber_1760) {
    Object obj(42);
    EXPECT_TRUE(isNumber(&obj));
}

// Test that a real/double Object is recognized as a number
TEST_F(IsNumberTest_1760, RealObjectIsNumber_1760) {
    Object obj(3.14);
    EXPECT_TRUE(isNumber(&obj));
}

// Test that a zero integer is recognized as a number
TEST_F(IsNumberTest_1760, ZeroIntIsNumber_1760) {
    Object obj(0);
    EXPECT_TRUE(isNumber(&obj));
}

// Test that a zero double is recognized as a number
TEST_F(IsNumberTest_1760, ZeroRealIsNumber_1760) {
    Object obj(0.0);
    EXPECT_TRUE(isNumber(&obj));
}

// Test that a negative integer is recognized as a number
TEST_F(IsNumberTest_1760, NegativeIntIsNumber_1760) {
    Object obj(-100);
    EXPECT_TRUE(isNumber(&obj));
}

// Test that a negative double is recognized as a number
TEST_F(IsNumberTest_1760, NegativeRealIsNumber_1760) {
    Object obj(-2.718);
    EXPECT_TRUE(isNumber(&obj));
}

// Test that a very large double is recognized as a number
TEST_F(IsNumberTest_1760, LargeRealIsNumber_1760) {
    Object obj(1e308);
    EXPECT_TRUE(isNumber(&obj));
}

// Test that a very small double is recognized as a number
TEST_F(IsNumberTest_1760, SmallRealIsNumber_1760) {
    Object obj(1e-308);
    EXPECT_TRUE(isNumber(&obj));
}

// Test that a boolean Object is NOT a number
TEST_F(IsNumberTest_1760, BoolObjectIsNotNumber_1760) {
    Object obj(true);
    EXPECT_FALSE(isNumber(&obj));
}

// Test that a null Object is NOT a number
TEST_F(IsNumberTest_1760, NullObjectIsNotNumber_1760) {
    Object obj = Object::null();
    EXPECT_FALSE(isNumber(&obj));
}

// Test that a default-constructed (none) Object is NOT a number
TEST_F(IsNumberTest_1760, NoneObjectIsNotNumber_1760) {
    Object obj;
    EXPECT_FALSE(isNumber(&obj));
}

// Test that an error Object is NOT a number
TEST_F(IsNumberTest_1760, ErrorObjectIsNotNumber_1760) {
    Object obj = Object::error();
    EXPECT_FALSE(isNumber(&obj));
}

// Test that an EOF Object is NOT a number
TEST_F(IsNumberTest_1760, EofObjectIsNotNumber_1760) {
    Object obj = Object::eof();
    EXPECT_FALSE(isNumber(&obj));
}

// Test that a string Object is NOT a number
TEST_F(IsNumberTest_1760, StringObjectIsNotNumber_1760) {
    Object obj(std::string("hello"));
    EXPECT_FALSE(isNumber(&obj));
}

// Test that a name Object is NOT a number
TEST_F(IsNumberTest_1760, NameObjectIsNotNumber_1760) {
    Object obj(objName, "SomeName");
    EXPECT_FALSE(isNumber(&obj));
}

// Test that an int64 Object is recognized as a number (isNum typically covers int, real, and int64)
TEST_F(IsNumberTest_1760, Int64ObjectIsNumber_1760) {
    Object obj(static_cast<long long>(9223372036854775807LL));
    EXPECT_TRUE(isNumber(&obj));
}

// Test that a negative int64 Object is recognized as a number
TEST_F(IsNumberTest_1760, NegativeInt64ObjectIsNumber_1760) {
    Object obj(static_cast<long long>(-9223372036854775807LL));
    EXPECT_TRUE(isNumber(&obj));
}

// Test MAX_INT boundary
TEST_F(IsNumberTest_1760, MaxIntIsNumber_1760) {
    Object obj(std::numeric_limits<int>::max());
    EXPECT_TRUE(isNumber(&obj));
}

// Test MIN_INT boundary
TEST_F(IsNumberTest_1760, MinIntIsNumber_1760) {
    Object obj(std::numeric_limits<int>::min());
    EXPECT_TRUE(isNumber(&obj));
}

// Test that a false boolean is NOT a number
TEST_F(IsNumberTest_1760, FalseBoolObjectIsNotNumber_1760) {
    Object obj(false);
    EXPECT_FALSE(isNumber(&obj));
}
