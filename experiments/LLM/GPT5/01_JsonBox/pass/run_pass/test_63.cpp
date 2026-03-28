// File: tests/Value_LoadFromStream_Test_63.cpp

#include <gtest/gtest.h>
#include <sstream>
#include "JsonBox/Value.h"
#include "JsonBox/Grammar.h"

using namespace JsonBox;

class ValueLoadFromStreamTest_63 : public ::testing::Test {
protected:
    static Value Parse(const std::string &jsonWithPossibleNulls) {
        // Use stringbuf to preserve embedded '\0' if present.
        std::stringbuf sb(jsonWithPossibleNulls);
        std::istream is(&sb);
        Value v;
        v.loadFromStream(is);
        return v;
    }
};

// --- Normal operation ---

TEST_F(ValueLoadFromStreamTest_63, ParsesTrueBoolean_63) {
    Value v = Parse("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueLoadFromStreamTest_63, ParsesFalseBoolean_63) {
    Value v = Parse("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueLoadFromStreamTest_63, ParsesNull_63) {
    Value v = Parse("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueLoadFromStreamTest_63, ParsesEmptyString_63) {
    Value v = Parse("\"\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("", v.getString());
}

TEST_F(ValueLoadFromStreamTest_63, ParsesSimpleString_63) {
    Value v = Parse("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("hello", v.getString());
}

TEST_F(ValueLoadFromStreamTest_63, ParsesIntegerNumber_63) {
    Value v = Parse("123");
    EXPECT_TRUE(v.isNumeric());
    EXPECT_EQ(123, v.getInteger());       // observable via public API
    EXPECT_DOUBLE_EQ(123.0, v.getDouble());
}

TEST_F(ValueLoadFromStreamTest_63, ParsesNegativeDouble_63) {
    Value v = Parse("-3.5");
    EXPECT_TRUE(v.isNumeric());
    EXPECT_DOUBLE_EQ(-3.5, v.getDouble());
}

TEST_F(ValueLoadFromStreamTest_63, ParsesEmptyObject_63) {
    Value v = Parse("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v.getObject().empty());
}

TEST_F(ValueLoadFromStreamTest_63, ParsesEmptyArray_63) {
    Value v = Parse("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v.getArray().empty());
}

// --- Boundary / whitespace handling ---

TEST_F(ValueLoadFromStreamTest_63, SkipsLeadingWhitespace_63) {
    Value v = Parse("  \n\t true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

// --- Exceptional / error cases (observable through interface) ---

TEST_F(ValueLoadFromStreamTest_63, InvalidCharacterThrowsParsingError_63) {
    Value v;
    std::istringstream is("x"); // not a valid JSON starting character
    // Expect a parsing-related exception; JsonParsingError is thrown by implementation.
    EXPECT_THROW(v.loadFromStream(is), std::exception);
}

TEST_F(ValueLoadFromStreamTest_63, InvalidEncodingHeaderThrowsInvalidArgument_63) {
    // According to the function, if the first two bytes are '\0', it throws invalid_argument
    std::string payload;
    payload.push_back('\0');
    payload.push_back('\0');
    payload += "true"; // rest doesn't matter; early check fails

    Value v;
    std::stringbuf sb(payload);
    std::istream is(&sb);
    EXPECT_THROW(v.loadFromStream(is), std::invalid_argument);
}
