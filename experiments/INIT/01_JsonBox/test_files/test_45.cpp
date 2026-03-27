// File: Value_setString_tests_45.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"
#include <string>

using JsonBox::Value;

class ValueSetStringTest_45 : public ::testing::Test {};

// Normal: set on NULL -> becomes STRING with correct value
TEST_F(ValueSetStringTest_45, SetOnNull_MakesTypeStringAndStoresValue_45) {
    Value v; // default constructs as NULL per header
    v.setString(std::string("hello"));

    EXPECT_TRUE(v.isString());
    EXPECT_EQ(Value::STRING, v.getType());
    EXPECT_EQ("hello", v.getString());
    // also via tryGetString should return the set value, not the default
    EXPECT_EQ("hello", v.tryGetString("default"));
}

// Normal: overwrite existing STRING should be in-place (same std::string object), new content
TEST_F(ValueSetStringTest_45, OverwriteExistingString_InPlaceAndUpdatesContent_45) {
    Value v(std::string("first"));
    const std::string* before_addr = &v.getString();

    v.setString(std::string("second"));

    EXPECT_TRUE(v.isString());
    EXPECT_EQ(Value::STRING, v.getType());
    EXPECT_EQ("second", v.getString());

    const std::string* after_addr = &v.getString();
    // Same std::string object observed through public reference
    EXPECT_EQ(before_addr, after_addr);
}

// Conversion: from INTEGER to STRING, then further overwrite should be in-place afterwards
TEST_F(ValueSetStringTest_45, ConvertFromIntegerToString_ThenOverwriteInPlace_45) {
    Value v(123); // not a string initially

    v.setString(std::string("one-two-three"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(Value::STRING, v.getType());
    EXPECT_EQ("one-two-three", v.getString());

    // Once it is a STRING, subsequent setString should be in-place
    const std::string* addr1 = &v.getString();
    v.setString(std::string("updated"));
    const std::string* addr2 = &v.getString();

    EXPECT_TRUE(v.isString());
    EXPECT_EQ(Value::STRING, v.getType());
    EXPECT_EQ("updated", v.getString());
    EXPECT_EQ(addr1, addr2);
}

// Boundary: empty string should be accepted and stored
TEST_F(ValueSetStringTest_45, SetEmptyString_StoresEmpty_45) {
    Value v(std::string("init"));
    v.setString(std::string());

    EXPECT_TRUE(v.isString());
    EXPECT_EQ(Value::STRING, v.getType());
    EXPECT_TRUE(v.getString().empty());
    EXPECT_EQ("", v.tryGetString("fallback"));
}

// Unicode/UTF-8 content should be preserved
TEST_F(ValueSetStringTest_45, SetUnicodeString_PreservesContent_45) {
    Value v; // NULL
    const std::string unicode = u8"한글🌟-テスト-✔";
    v.setString(unicode);

    EXPECT_TRUE(v.isString());
    EXPECT_EQ(Value::STRING, v.getType());
    EXPECT_EQ(unicode, v.getString());
    EXPECT_EQ(unicode, v.tryGetString("x"));
}
