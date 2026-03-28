#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueTest_63 : public ::testing::Test {
protected:
    Value value;
};

// =============================================================================
// Default Constructor Tests
// =============================================================================

TEST_F(ValueTest_63, DefaultConstructor_IsNull_63) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_63, DefaultConstructor_TypeIsNullValue_63) {
    Value v;
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

// =============================================================================
// String Constructor and Getter Tests
// =============================================================================

TEST_F(ValueTest_63, StringConstructor_SetsString_63) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_63, CStringConstructor_SetsString_63) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_63, EmptyStringConstructor_63) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

// =============================================================================
// Integer Constructor and Getter Tests
// =============================================================================

TEST_F(ValueTest_63, IntConstructor_SetsInteger_63) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_63, IntConstructor_NegativeValue_63) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST_F(ValueTest_63, IntConstructor_Zero_63) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

// =============================================================================
// Double Constructor and Getter Tests
// =============================================================================

TEST_F(ValueTest_63, DoubleConstructor_SetsDouble_63) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_63, DoubleConstructor_NegativeValue_63) {
    Value v(-2.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -2.5);
}

// =============================================================================
// Boolean Constructor and Getter Tests
// =============================================================================

TEST_F(ValueTest_63, BoolConstructor_True_63) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_63, BoolConstructor_False_63) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

// =============================================================================
// Object Constructor Tests
// =============================================================================

TEST_F(ValueTest_63, ObjectConstructor_SetsObject_63) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

// =============================================================================
// Array Constructor Tests
// =============================================================================

TEST_F(ValueTest_63, ArrayConstructor_SetsArray_63) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

// =============================================================================
// Copy Constructor Tests
// =============================================================================

TEST_F(ValueTest_63, CopyConstructor_String_63) {
    Value v1("test");
    Value v2(v1);
    EXPECT_TRUE(v2.isString());
    EXPECT_EQ(v2.getString(), "test");
}

TEST_F(ValueTest_63, CopyConstructor_Integer_63) {
    Value v1(42);
    Value v2(v1);
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_63, CopyConstructor_Null_63) {
    Value v1;
    Value v2(v1);
    EXPECT_TRUE(v2.isNull());
}

// =============================================================================
// Assignment Operator Tests
// =============================================================================

TEST_F(ValueTest_63, AssignmentOperator_Value_63) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_63, AssignmentOperator_String_63) {
    Value v;
    v = std::string("hello");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_63, AssignmentOperator_CString_63) {
    Value v;
    v = "hello";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_63, AssignmentOperator_Int_63) {
    Value v;
    v = 99;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_63, AssignmentOperator_Double_63) {
    Value v;
    v = 1.5;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.5);
}

TEST_F(ValueTest_63, AssignmentOperator_Bool_63) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_63, AssignmentOperator_Object_63) {
    Value v;
    Object obj;
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_63, AssignmentOperator_Array_63) {
    Value v;
    Array arr;
    v = arr;
    EXPECT_TRUE(v.isArray());
}

// =============================================================================
// Comparison Operator Tests
// =============================================================================

TEST_F(ValueTest_63, EqualityOperator_SameIntegers_63) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_63, EqualityOperator_DifferentIntegers_63) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_63, InequalityOperator_63) {
    Value v1(42);
    Value v2(43);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_63, LessThanOperator_63) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
}

TEST_F(ValueTest_63, LessThanOrEqualOperator_63) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_63, GreaterThanOperator_63) {
    Value v1(2);
    Value v2(1);
    EXPECT_TRUE(v1 > v2);
}

TEST_F(ValueTest_63, GreaterThanOrEqualOperator_63) {
    Value v1(2);
    Value v2(2);
    EXPECT_TRUE(v1 >= v2);
}

// =============================================================================
// Type Checking Tests
// =============================================================================

TEST_F(ValueTest_63, IsStringable_StringType_63) {
    Value v("test");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_63, IsNumeric_Integer_63) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_63, IsNumeric_Double_63) {
    Value v(5.0);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_63, IsNotString_WhenInteger_63) {
    Value v(5);
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_63, IsNotInteger_WhenString_63) {
    Value v("test");
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_63, IsNotDouble_WhenString_63) {
    Value v("test");
    EXPECT_FALSE(v.isDouble());
}

TEST_F(ValueTest_63, IsNotObject_WhenString_63) {
    Value v("test");
    EXPECT_FALSE(v.isObject());
}

TEST_F(ValueTest_63, IsNotArray_WhenString_63) {
    Value v("test");
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueTest_63, IsNotBoolean_WhenString_63) {
    Value v("test");
    EXPECT_FALSE(v.isBoolean());
}

TEST_F(ValueTest_63, IsNotNull_WhenString_63) {
    Value v("test");
    EXPECT_FALSE(v.isNull());
}

// =============================================================================
// Setter Tests
// =============================================================================

TEST_F(ValueTest_63, SetString_ChangesType_63) {
    Value v(42);
    v.setString("new");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "new");
}

TEST_F(ValueTest_63, SetInteger_ChangesType_63) {
    Value v("hello");
    v.setInteger(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 10);
}

TEST_F(ValueTest_63, SetDouble_ChangesType_63) {
    Value v("hello");
    v.setDouble(2.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.5);
}

TEST_F(ValueTest_63, SetBoolean_ChangesType_63) {
    Value v("hello");
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_63, SetObject_ChangesType_63) {
    Value v("hello");
    v.setObject(Object());
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_63, SetArray_ChangesType_63) {
    Value v("hello");
    v.setArray(Array());
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_63, SetNull_ChangesType_63) {
    Value v("hello");
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

// =============================================================================
// tryGet Tests
// =============================================================================

TEST_F(ValueTest_63, TryGetString_ReturnsValue_WhenString_63) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST_F(ValueTest_63, TryGetString_ReturnsDefault_WhenNotString_63) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_63, TryGetInteger_ReturnsValue_WhenInteger_63) {
    Value v(42);
    EXPECT_EQ(v.tryGetInteger(0), 42);
}

TEST_F(ValueTest_63, TryGetInteger_ReturnsDefault_WhenNotInteger_63) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(99), 99);
}

TEST_F(ValueTest_63, TryGetDouble_ReturnsValue_WhenDouble_63) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 3.14);
}

TEST_F(ValueTest_63, TryGetDouble_ReturnsDefault_WhenNotDouble_63) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.0), 1.0);
}

TEST_F(ValueTest_63, TryGetFloat_ReturnsValue_WhenDouble_63) {
    Value v(3.14);
    EXPECT_NEAR(v.tryGetFloat(0.0f), 3.14f, 0.01f);
}

TEST_F(ValueTest_63, TryGetFloat_ReturnsDefault_WhenNotDouble_63) {
    Value v("hello");
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.0f), 1.0f);
}

TEST_F(ValueTest_63, TryGetBoolean_ReturnsValue_WhenBoolean_63) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_63, TryGetBoolean_ReturnsDefault_WhenNotBoolean_63) {
    Value v("hello");
    EXPECT_TRUE(v.tryGetBoolean(true));
}

// =============================================================================
// loadFromStream Tests
// =============================================================================

TEST_F(ValueTest_63, LoadFromStream_ParsesString_63) {
    std::istringstream ss("\"hello world\"");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello world");
}

TEST_F(ValueTest_63, LoadFromStream_ParsesEmptyString_63) {
    std::istringstream ss("\"\"");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_63, LoadFromStream_ParsesInteger_63) {
    std::istringstream ss("42");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_63, LoadFromStream_ParsesNegativeInteger_63) {
    std::istringstream ss("-7");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -7);
}

TEST_F(ValueTest_63, LoadFromStream_ParsesDouble_63) {
    std::istringstream ss("3.14");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_63, LoadFromStream_ParsesNull_63) {
    std::istringstream ss("null");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_63, LoadFromStream_ParsesTrue_63) {
    std::istringstream ss("true");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_63, LoadFromStream_ParsesFalse_63) {
    std::istringstream ss("false");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_63, LoadFromStream_ParsesEmptyObject_63) {
    std::istringstream ss("{}");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_63, LoadFromStream_ParsesObjectWithEntry_63) {
    std::istringstream ss("{\"key\": 42}");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_63, LoadFromStream_ParsesEmptyArray_63) {
    std::istringstream ss("[]");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_63, LoadFromStream_ParsesArrayWithElements_63) {
    std::istringstream ss("[1, 2, 3]");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_63, LoadFromStream_WhitespaceBeforeValue_63) {
    std::istringstream ss("   42");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_63, LoadFromStream_InvalidCharacter_ThrowsException_63) {
    std::istringstream ss("@");
    Value v;
    EXPECT_THROW(v.loadFromStream(ss), std::exception);
}

TEST_F(ValueTest_63, LoadFromStream_InvalidNull_ThrowsException_63) {
    std::istringstream ss("nulx");
    Value v;
    EXPECT_THROW(v.loadFromStream(ss), std::exception);
}

// =============================================================================
// loadFromString Tests
// =============================================================================

TEST_F(ValueTest_63, LoadFromString_ParsesString_63) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_63, LoadFromString_ParsesInteger_63) {
    Value v;
    v.loadFromString("123");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

TEST_F(ValueTest_63, LoadFromString_ParsesNull_63) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_63, LoadFromString_ParsesTrue_63) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_63, LoadFromString_ParsesFalse_63) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

// =============================================================================
// Subscript Operator Tests
// =============================================================================

TEST_F(ValueTest_63, SubscriptOperator_StringKey_CreatesObject_63) {
    Value v;
    v.setObject(Object());
    v["key"] = Value(42);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST_F(ValueTest_63, SubscriptOperator_CStringKey_63) {
    Value v;
    v.setObject(Object());
    v["key"] = Value("val");
    EXPECT_EQ(v["key"].getString(), "val");
}

TEST_F(ValueTest_63, SubscriptOperator_Index_63) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
}

// =============================================================================
// writeToStream Tests
// =============================================================================

TEST_F(ValueTest_63, WriteToStream_Integer_63) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(ValueTest_63, WriteToStream_String_63) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(ValueTest_63, WriteToStream_NullValue_63) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("null"), std::string::npos);
}

TEST_F(ValueTest_63, WriteToStream_BoolTrue_63) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(ValueTest_63, WriteToStream_BoolFalse_63) {
    Value v(false);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("false"), std::string::npos);
}

// =============================================================================
// Stream Constructor Test
// =============================================================================

TEST_F(ValueTest_63, StreamConstructor_ParsesValue_63) {
    std::istringstream ss("\"stream constructor\"");
    Value v(ss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "stream constructor");
}

// =============================================================================
// getToString Tests
// =============================================================================

TEST_F(ValueTest_63, GetToString_Integer_63) {
    Value v(42);
    std::string s = v.getToString();
    EXPECT_EQ(s, "42");
}

TEST_F(ValueTest_63, GetToString_String_63) {
    Value v("hello");
    std::string s = v.getToString();
    EXPECT_EQ(s, "hello");
}

// =============================================================================
// getFloat Tests
// =============================================================================

TEST_F(ValueTest_63, GetFloat_ReturnsFloatValue_63) {
    Value v(3.14);
    EXPECT_NEAR(v.getFloat(), 3.14f, 0.01f);
}

// =============================================================================
// Escape Tests
// =============================================================================

TEST_F(ValueTest_63, EscapeMinimumCharacters_QuoteEscaped_63) {
    std::string result = Value::escapeMinimumCharacters("he\"llo");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_63, EscapeMinimumCharacters_BackslashEscaped_63) {
    std::string result = Value::escapeMinimumCharacters("he\\llo");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST_F(ValueTest_63, EscapeToUnicode_ReturnsUnicodeString_63) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
}

// =============================================================================
// Complex JSON parsing tests
// =============================================================================

TEST_F(ValueTest_63, LoadFromStream_NestedObject_63) {
    std::istringstream ss("{\"outer\": {\"inner\": 1}}");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 1);
}

TEST_F(ValueTest_63, LoadFromStream_NestedArray_63) {
    std::istringstream ss("[[1, 2], [3, 4]]");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_63, LoadFromStream_MixedTypes_63) {
    std::istringstream ss("{\"str\": \"hello\", \"num\": 42, \"bool\": true, \"nil\": null}");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["str"].getString(), "hello");
    EXPECT_EQ(v["num"].getInteger(), 42);
    EXPECT_TRUE(v["bool"].getBoolean());
    EXPECT_TRUE(v["nil"].isNull());
}

TEST_F(ValueTest_63, LoadFromStream_Zero_63) {
    std::istringstream ss("0");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_63, LoadFromStream_NegativeDouble_63) {
    std::istringstream ss("-3.14");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -3.14);
}

// =============================================================================
// Output stream operator test
// =============================================================================

TEST_F(ValueTest_63, StreamOutputOperator_63) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_NE(oss.str().find("42"), std::string::npos);
}

// =============================================================================
// Edge: single character stream too short (< 2 chars, null encoding)
// =============================================================================

TEST_F(ValueTest_63, LoadFromStream_EmptyStream_ThrowsOrHandles_63) {
    std::istringstream ss("");
    Value v;
    // An empty stream would have encoding[0] and encoding[1] fail to read
    // This should throw invalid_argument for non-UTF-8
    EXPECT_THROW(v.loadFromStream(ss), std::invalid_argument);
}

TEST_F(ValueTest_63, LoadFromStream_StringWithEscapedCharacters_63) {
    std::istringstream ss("\"hello\\nworld\"");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isString());
}

TEST_F(ValueTest_63, LoadFromStream_LargeNumber_63) {
    std::istringstream ss("999999999");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 999999999);
}

TEST_F(ValueTest_63, WriteToStream_WithIndent_63) {
    Value v;
    v.setObject(Object());
    v["key"] = Value(1);
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTest_63, WriteToStream_EscapeAll_63) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, true);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}
