#include <gtest/gtest.h>
#include <memory>
#include "Object.h"

// We're testing the static function `isTextString` which checks if an Object is a string.
// Since it's a static function in StructElement.cc, we replicate its logic for testing purposes.
// However, per constraints, we test based on the interface of Object::isString().

// The function under test:
static bool isTextString(Object *value) { return value->isString(); }

class IsTextStringTest_1774 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a string Object is recognized as a text string
TEST_F(IsTextStringTest_1774, StringObjectReturnsTrue_1774) {
    Object obj(std::make_unique<GooString>("hello"));
    EXPECT_TRUE(isTextString(&obj));
}

// Test that an empty string Object is still recognized as a text string
TEST_F(IsTextStringTest_1774, EmptyStringObjectReturnsTrue_1774) {
    Object obj(std::make_unique<GooString>(""));
    EXPECT_TRUE(isTextString(&obj));
}

// Test that a string Object constructed from std::string is recognized
TEST_F(IsTextStringTest_1774, StdStringObjectReturnsTrue_1774) {
    std::string s = "test string";
    Object obj(std::move(s));
    EXPECT_TRUE(isTextString(&obj));
}

// Test that a null Object is NOT a text string
TEST_F(IsTextStringTest_1774, NullObjectReturnsFalse_1774) {
    Object obj = Object::null();
    EXPECT_FALSE(isTextString(&obj));
}

// Test that a boolean Object is NOT a text string
TEST_F(IsTextStringTest_1774, BoolObjectReturnsFalse_1774) {
    Object obj(true);
    EXPECT_FALSE(isTextString(&obj));
}

// Test that an integer Object is NOT a text string
TEST_F(IsTextStringTest_1774, IntObjectReturnsFalse_1774) {
    Object obj(42);
    EXPECT_FALSE(isTextString(&obj));
}

// Test that a real/double Object is NOT a text string
TEST_F(IsTextStringTest_1774, RealObjectReturnsFalse_1774) {
    Object obj(3.14);
    EXPECT_FALSE(isTextString(&obj));
}

// Test that a default-constructed (none) Object is NOT a text string
TEST_F(IsTextStringTest_1774, NoneObjectReturnsFalse_1774) {
    Object obj;
    EXPECT_FALSE(isTextString(&obj));
}

// Test that an error Object is NOT a text string
TEST_F(IsTextStringTest_1774, ErrorObjectReturnsFalse_1774) {
    Object obj = Object::error();
    EXPECT_FALSE(isTextString(&obj));
}

// Test that an EOF Object is NOT a text string
TEST_F(IsTextStringTest_1774, EofObjectReturnsFalse_1774) {
    Object obj = Object::eof();
    EXPECT_FALSE(isTextString(&obj));
}

// Test that an int64 Object is NOT a text string
TEST_F(IsTextStringTest_1774, Int64ObjectReturnsFalse_1774) {
    Object obj(static_cast<long long>(123456789LL));
    EXPECT_FALSE(isTextString(&obj));
}

// Test that a name Object is NOT a text string
TEST_F(IsTextStringTest_1774, NameObjectReturnsFalse_1774) {
    Object obj(objName, "SomeName");
    EXPECT_FALSE(isTextString(&obj));
}

// Test that a hex string Object is NOT identified as a regular text string
// (isString() should return false for hex strings, which use objHexString type)
TEST_F(IsTextStringTest_1774, HexStringObjectReturnsFalse_1774) {
    Object obj(objHexString, "48656C6C6F");
    EXPECT_FALSE(isTextString(&obj));
}

// Test with a string containing special characters
TEST_F(IsTextStringTest_1774, SpecialCharStringReturnsTrue_1774) {
    Object obj(std::make_unique<GooString>("hello\nworld\t!@#$%^&*()"));
    EXPECT_TRUE(isTextString(&obj));
}

// Test with a string containing unicode-like content
TEST_F(IsTextStringTest_1774, UnicodeStringReturnsTrue_1774) {
    Object obj(std::make_unique<GooString>("\xFE\xFF\x00\x48\x00\x65"));
    EXPECT_TRUE(isTextString(&obj));
}
