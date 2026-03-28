// File: Value_getString_test_42.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueGetStringTest_42 : public ::testing::Test {};

// [Normal] Returns the stored std::string
TEST_F(ValueGetStringTest_42, ReturnsStoredString_42) {
    Value v(std::string("hello"));
    EXPECT_EQ(std::string("hello"), v.getString());
}

// [Normal] Returns the stored C-string
TEST_F(ValueGetStringTest_42, CStringConstructor_42) {
    Value v("world");
    EXPECT_EQ(std::string("world"), v.getString());
}

// [Boundary] Returns empty for an explicitly empty string value (should not alter content)
TEST_F(ValueGetStringTest_42, EmptyStringRemainsEmpty_42) {
    Value v(std::string());
    EXPECT_TRUE(v.getString().empty());
}

// [Boundary] Large and Unicode string round-trips unchanged
TEST_F(ValueGetStringTest_42, LargeAndUnicodeString_42) {
    std::string big(10000, 'x'); // large payload
    std::string unicode = u8"한글🙂"; // UTF-8 content
    std::string combined = big + unicode;

    Value v(combined);
    EXPECT_EQ(combined, v.getString());
}

// [Exceptional/Type Mismatch Observable Behavior] For null, getString() yields an empty string
TEST_F(ValueGetStringTest_42, NullValueReturnsEmpty_42) {
    Value v; // default-constructed -> null
    EXPECT_TRUE(v.getString().empty());
}

// [Exceptional/Type Mismatch Observable Behavior] For integer, getString() yields an empty string
TEST_F(ValueGetStringTest_42, IntegerValueReturnsEmpty_42) {
    Value v(123);
    EXPECT_TRUE(v.getString().empty());
}

// [Exceptional/Type Mismatch Observable Behavior] For double, getString() yields an empty string
TEST_F(ValueGetStringTest_42, DoubleValueReturnsEmpty_42) {
    Value v(3.14);
    EXPECT_TRUE(v.getString().empty());
}

// [Exceptional/Type Mismatch Observable Behavior] For boolean, getString() yields an empty string
TEST_F(ValueGetStringTest_42, BooleanValueReturnsEmpty_42) {
    Value v(true);
    EXPECT_TRUE(v.getString().empty());
}

// [Exceptional/Type Mismatch Observable Behavior] For object, getString() yields an empty string
TEST_F(ValueGetStringTest_42, ObjectValueReturnsEmpty_42) {
    Object o;
    o["k"] = Value(1);
    Value v(o);
    EXPECT_TRUE(v.getString().empty());
}

// [Exceptional/Type Mismatch Observable Behavior] For array, getString() yields an empty string
TEST_F(ValueGetStringTest_42, ArrayValueReturnsEmpty_42) {
    Array a;
    a.push_back(Value(1));
    Value v(a);
    EXPECT_TRUE(v.getString().empty());
}

// [Stability] Reference returned by getString() is stable across multiple calls for string values
TEST_F(ValueGetStringTest_42, ConsistentReferenceAcrossCalls_String_42) {
    Value v("abc");
    auto* p1 = &v.getString();
    auto* p2 = &v.getString();
    EXPECT_EQ(p1, p2);
    EXPECT_EQ(std::string("abc"), *p1);
}

// [Stability] Reference returned by getString() is stable across multiple calls for non-string values
TEST_F(ValueGetStringTest_42, ConsistentReferenceAcrossCalls_NonString_42) {
    Value v(42); // non-string
    auto* p1 = &v.getString();
    auto* p2 = &v.getString();
    EXPECT_EQ(p1, p2);
    EXPECT_TRUE(p1->empty());
}
