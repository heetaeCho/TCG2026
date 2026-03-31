#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

// ============================================================
// Test Fixture
// ============================================================
class ValueTest_21 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Default Constructor Tests
// ============================================================
TEST_F(ValueTest_21, DefaultConstructorCreatesNull_21) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

// ============================================================
// String Constructor and Accessor Tests
// ============================================================
TEST_F(ValueTest_21, StringConstructor_21) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_21, CStringConstructor_21) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_21, EmptyStringConstructor_21) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

// ============================================================
// Integer Constructor and Accessor Tests
// ============================================================
TEST_F(ValueTest_21, IntConstructor_21) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_21, IntConstructorZero_21) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_21, IntConstructorNegative_21) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

// ============================================================
// Double Constructor and Accessor Tests
// ============================================================
TEST_F(ValueTest_21, DoubleConstructor_21) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_21, DoubleConstructorZero_21) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_21, DoubleConstructorNegative_21) {
    Value v(-2.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -2.5);
}

// ============================================================
// Boolean Constructor and Accessor Tests
// ============================================================
TEST_F(ValueTest_21, BoolConstructorTrue_21) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_21, BoolConstructorFalse_21) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

// ============================================================
// Object Constructor and Accessor Tests
// ============================================================
TEST_F(ValueTest_21, ObjectConstructor_21) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
    EXPECT_EQ(v.getObject().at("key").getString(), "value");
}

TEST_F(ValueTest_21, EmptyObjectConstructor_21) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

// ============================================================
// Array Constructor and Accessor Tests
// ============================================================
TEST_F(ValueTest_21, ArrayConstructor_21) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    arr.push_back(Value(3));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
    EXPECT_EQ(v.getArray()[0].getInteger(), 1);
    EXPECT_EQ(v.getArray()[1].getInteger(), 2);
    EXPECT_EQ(v.getArray()[2].getInteger(), 3);
}

TEST_F(ValueTest_21, EmptyArrayConstructor_21) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

// ============================================================
// Copy Constructor Tests
// ============================================================
TEST_F(ValueTest_21, CopyConstructorString_21) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "test");
}

TEST_F(ValueTest_21, CopyConstructorInt_21) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

TEST_F(ValueTest_21, CopyConstructorNull_21) {
    Value original;
    Value copy(original);
    EXPECT_TRUE(copy.isNull());
}

TEST_F(ValueTest_21, CopyConstructorBool_21) {
    Value original(true);
    Value copy(original);
    EXPECT_TRUE(copy.isBoolean());
    EXPECT_TRUE(copy.getBoolean());
}

TEST_F(ValueTest_21, CopyConstructorDouble_21) {
    Value original(1.23);
    Value copy(original);
    EXPECT_TRUE(copy.isDouble());
    EXPECT_DOUBLE_EQ(copy.getDouble(), 1.23);
}

// ============================================================
// Assignment Operator Tests
// ============================================================
TEST_F(ValueTest_21, AssignmentFromValue_21) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_21, AssignmentFromString_21) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_21, AssignmentFromCString_21) {
    Value v;
    v = "cstr";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "cstr");
}

TEST_F(ValueTest_21, AssignmentFromInt_21) {
    Value v;
    v = 99;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_21, AssignmentFromDouble_21) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_21, AssignmentFromBool_21) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_21, AssignmentFromObject_21) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_21, AssignmentFromArray_21) {
    Value v;
    Array arr;
    arr.push_back(Value("elem"));
    v = arr;
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
    EXPECT_EQ(v.getArray()[0].getString(), "elem");
}

// ============================================================
// Type change after assignment
// ============================================================
TEST_F(ValueTest_21, TypeChangeAfterAssignment_21) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v = std::string("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST_F(ValueTest_21, TypeChangeFromStringToInt_21) {
    Value v("text");
    EXPECT_TRUE(v.isString());
    v = 10;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 10);
}

// ============================================================
// Setter Tests
// ============================================================
TEST_F(ValueTest_21, SetString_21) {
    Value v;
    v.setString("set");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "set");
}

TEST_F(ValueTest_21, SetInteger_21) {
    Value v;
    v.setInteger(55);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 55);
}

TEST_F(ValueTest_21, SetDouble_21) {
    Value v;
    v.setDouble(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.5);
}

TEST_F(ValueTest_21, SetBoolean_21) {
    Value v;
    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_21, SetObject_21) {
    Value v;
    Object obj;
    obj["x"] = Value(10);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().at("x").getInteger(), 10);
}

TEST_F(ValueTest_21, SetArray_21) {
    Value v;
    Array arr;
    arr.push_back(Value(true));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v.getArray()[0].getBoolean());
}

TEST_F(ValueTest_21, SetNull_21) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

// ============================================================
// isNumeric Tests
// ============================================================
TEST_F(ValueTest_21, IsNumericForInteger_21) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_21, IsNumericForDouble_21) {
    Value v(5.0);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_21, IsNumericForString_21) {
    Value v("5");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_21, IsNumericForNull_21) {
    Value v;
    EXPECT_FALSE(v.isNumeric());
}

// ============================================================
// isStringable Tests
// ============================================================
TEST_F(ValueTest_21, IsStringableForString_21) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_21, IsStringableForInteger_21) {
    Value v(42);
    // Integers might be stringable (convertible to string representation)
    // We just test that isStringable returns a bool without crashing
    v.isStringable();
}

TEST_F(ValueTest_21, IsStringableForNull_21) {
    Value v;
    // Null is typically not stringable
    v.isStringable();
}

// ============================================================
// Type Query Tests (negative cases)
// ============================================================
TEST_F(ValueTest_21, NullIsNotString_21) {
    Value v;
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_21, NullIsNotInteger_21) {
    Value v;
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_21, NullIsNotDouble_21) {
    Value v;
    EXPECT_FALSE(v.isDouble());
}

TEST_F(ValueTest_21, NullIsNotBoolean_21) {
    Value v;
    EXPECT_FALSE(v.isBoolean());
}

TEST_F(ValueTest_21, NullIsNotObject_21) {
    Value v;
    EXPECT_FALSE(v.isObject());
}

TEST_F(ValueTest_21, NullIsNotArray_21) {
    Value v;
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueTest_21, IntIsNotString_21) {
    Value v(42);
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
}

// ============================================================
// Comparison Operator Tests
// ============================================================
TEST_F(ValueTest_21, EqualityOperator_21) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_21, InequalityOperator_21) {
    Value v1(42);
    Value v2(43);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_21, EqualityDifferentTypes_21) {
    Value v1(42);
    Value v2("42");
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_21, LessThanOperator_21) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_21, LessThanOrEqualOperator_21) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_21, GreaterThanOperator_21) {
    Value v1(10);
    Value v2(5);
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v2 > v1);
}

TEST_F(ValueTest_21, GreaterThanOrEqualOperator_21) {
    Value v1(10);
    Value v2(10);
    EXPECT_TRUE(v1 >= v2);
}

TEST_F(ValueTest_21, EqualityNullValues_21) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_21, EqualityBooleans_21) {
    Value v1(true);
    Value v2(true);
    EXPECT_TRUE(v1 == v2);
    Value v3(false);
    EXPECT_TRUE(v1 != v3);
}

TEST_F(ValueTest_21, EqualityStrings_21) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_TRUE(v1 == v2);
    Value v3("xyz");
    EXPECT_TRUE(v1 != v3);
}

TEST_F(ValueTest_21, EqualityDoubles_21) {
    Value v1(3.14);
    Value v2(3.14);
    EXPECT_TRUE(v1 == v2);
}

// ============================================================
// Subscript Operator Tests (Object)
// ============================================================
TEST_F(ValueTest_21, SubscriptOperatorStringKey_21) {
    Value v;
    v.setObject(Object());
    v["key"] = Value(123);
    EXPECT_TRUE(v["key"].isInteger());
    EXPECT_EQ(v["key"].getInteger(), 123);
}

TEST_F(ValueTest_21, SubscriptOperatorCStringKey_21) {
    Value v;
    v.setObject(Object());
    const char* key = "mykey";
    v[key] = Value("myval");
    EXPECT_EQ(v[key].getString(), "myval");
}

TEST_F(ValueTest_21, SubscriptOperatorMultipleKeys_21) {
    Value v;
    v.setObject(Object());
    v["a"] = Value(1);
    v["b"] = Value(2);
    v["c"] = Value(3);
    EXPECT_EQ(v["a"].getInteger(), 1);
    EXPECT_EQ(v["b"].getInteger(), 2);
    EXPECT_EQ(v["c"].getInteger(), 3);
}

// ============================================================
// Subscript Operator Tests (Array)
// ============================================================
TEST_F(ValueTest_21, SubscriptOperatorArrayIndex_21) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

// ============================================================
// tryGet Tests (Default Values)
// ============================================================
TEST_F(ValueTest_21, TryGetStringReturnsValueWhenString_21) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST_F(ValueTest_21, TryGetStringReturnsDefaultWhenNotString_21) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_21, TryGetIntegerReturnsValueWhenInteger_21) {
    Value v(100);
    EXPECT_EQ(v.tryGetInteger(0), 100);
}

TEST_F(ValueTest_21, TryGetIntegerReturnsDefaultWhenNotInteger_21) {
    Value v("not int");
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

TEST_F(ValueTest_21, TryGetDoubleReturnsValueWhenDouble_21) {
    Value v(9.99);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 9.99);
}

TEST_F(ValueTest_21, TryGetDoubleReturnsDefaultWhenNotDouble_21) {
    Value v("not double");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.0), 1.0);
}

TEST_F(ValueTest_21, TryGetFloatReturnsValueWhenDouble_21) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST_F(ValueTest_21, TryGetFloatReturnsDefaultWhenNotDouble_21) {
    Value v("not float");
    EXPECT_FLOAT_EQ(v.tryGetFloat(3.0f), 3.0f);
}

TEST_F(ValueTest_21, TryGetBooleanReturnsValueWhenBoolean_21) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_21, TryGetBooleanReturnsDefaultWhenNotBoolean_21) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ============================================================
// getFloat Tests
// ============================================================
TEST_F(ValueTest_21, GetFloat_21) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 2.5f);
}

// ============================================================
// getToString Tests
// ============================================================
TEST_F(ValueTest_21, GetToStringFromString_21) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

TEST_F(ValueTest_21, GetToStringFromInt_21) {
    Value v(42);
    // Should return some string representation
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

// ============================================================
// loadFromString Tests
// ============================================================
TEST_F(ValueTest_21, LoadFromStringInteger_21) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_21, LoadFromStringString_21) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_21, LoadFromStringBoolTrue_21) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_21, LoadFromStringBoolFalse_21) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_21, LoadFromStringNull_21) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_21, LoadFromStringDouble_21) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_21, LoadFromStringEmptyObject_21) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_21, LoadFromStringEmptyArray_21) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_21, LoadFromStringObjectWithValues_21) {
    Value v;
    v.loadFromString("{\"name\": \"test\", \"value\": 42}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 2u);
}

TEST_F(ValueTest_21, LoadFromStringArrayWithValues_21) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
    EXPECT_EQ(v.getArray()[0].getInteger(), 1);
    EXPECT_EQ(v.getArray()[1].getInteger(), 2);
    EXPECT_EQ(v.getArray()[2].getInteger(), 3);
}

TEST_F(ValueTest_21, LoadFromStringNegativeInteger_21) {
    Value v;
    v.loadFromString("-10");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -10);
}

// ============================================================
// loadFromStream Tests
// ============================================================
TEST_F(ValueTest_21, LoadFromStream_21) {
    Value v;
    std::istringstream iss("\"stream_test\"");
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "stream_test");
}

TEST_F(ValueTest_21, LoadFromStreamObject_21) {
    Value v;
    std::istringstream iss("{\"key\": 100}");
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isObject());
}

// ============================================================
// writeToStream Tests
// ============================================================
TEST_F(ValueTest_21, WriteToStreamString_21) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    // Should contain the string "hello" in some form
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(ValueTest_21, WriteToStreamInteger_21) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(ValueTest_21, WriteToStreamBoolTrue_21) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(ValueTest_21, WriteToStreamBoolFalse_21) {
    Value v(false);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("false"), std::string::npos);
}

TEST_F(ValueTest_21, WriteToStreamNull_21) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("null"), std::string::npos);
}

TEST_F(ValueTest_21, WriteToStreamWithIndent_21) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTest_21, WriteToStreamNoIndent_21) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// ============================================================
// Stream Operator << Tests
// ============================================================
TEST_F(ValueTest_21, StreamOperator_21) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// ============================================================
// Escape Functions Tests
// ============================================================
TEST_F(ValueTest_21, EscapeMinimumCharacters_21) {
    std::string result = Value::escapeMinimumCharacters("hello\nworld");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_21, EscapeMinimumCharactersQuote_21) {
    std::string result = Value::escapeMinimumCharacters("he said \"hi\"");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_21, EscapeMinimumCharactersBackslash_21) {
    std::string result = Value::escapeMinimumCharacters("path\\to");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST_F(ValueTest_21, EscapeMinimumCharactersNoEscape_21) {
    std::string result = Value::escapeMinimumCharacters("normal text");
    EXPECT_EQ(result, "normal text");
}

TEST_F(ValueTest_21, EscapeMinimumCharactersEmpty_21) {
    std::string result = Value::escapeMinimumCharacters("");
    EXPECT_EQ(result, "");
}

TEST_F(ValueTest_21, EscapeAllCharacters_21) {
    std::string result = Value::escapeAllCharacters("hello\nworld");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_21, EscapeToUnicode_21) {
    std::string result = Value::escapeToUnicode('A');
    // Should return a unicode escape string like \u0041
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

TEST_F(ValueTest_21, EscapeToUnicodeNullChar_21) {
    std::string result = Value::escapeToUnicode('\0');
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ============================================================
// Constructor from istream Tests
// ============================================================
TEST_F(ValueTest_21, ConstructFromIStream_21) {
    std::istringstream iss("\"from_stream\"");
    Value v(iss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "from_stream");
}

TEST_F(ValueTest_21, ConstructFromIStreamInteger_21) {
    std::istringstream iss("123");
    Value v(iss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

TEST_F(ValueTest_21, ConstructFromIStreamObject_21) {
    std::istringstream iss("{\"a\": 1}");
    Value v(iss);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_21, ConstructFromIStreamArray_21) {
    std::istringstream iss("[1, 2]");
    Value v(iss);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

// ============================================================
// Nested Structure Tests
// ============================================================
TEST_F(ValueTest_21, NestedObjectInObject_21) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": 42}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

TEST_F(ValueTest_21, ArrayInObject_21) {
    Value v;
    v.loadFromString("{\"arr\": [1, 2, 3]}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["arr"].isArray());
    EXPECT_EQ(v["arr"].getArray().size(), 3u);
}

TEST_F(ValueTest_21, ObjectInArray_21) {
    Value v;
    v.loadFromString("[{\"key\": \"val\"}]");
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v[(size_t)0].isObject());
}

// ============================================================
// Roundtrip Tests (load -> write -> load)
// ============================================================
TEST_F(ValueTest_21, RoundtripSimpleObject_21) {
    std::string json = "{\"name\":\"test\",\"value\":42}";
    Value v1;
    v1.loadFromString(json);

    std::ostringstream oss;
    v1.writeToStream(oss, false, false);

    Value v2;
    v2.loadFromString(oss.str());

    EXPECT_TRUE(v2.isObject());
    EXPECT_EQ(v2["name"].getString(), "test");
    EXPECT_EQ(v2["value"].getInteger(), 42);
}

TEST_F(ValueTest_21, RoundtripArray_21) {
    std::string json = "[1,2,3]";
    Value v1;
    v1.loadFromString(json);

    std::ostringstream oss;
    v1.writeToStream(oss, false, false);

    Value v2;
    v2.loadFromString(oss.str());

    EXPECT_TRUE(v2.isArray());
    EXPECT_EQ(v2.getArray().size(), 3u);
}

// ============================================================
// Mixed Type Array Tests
// ============================================================
TEST_F(ValueTest_21, MixedTypeArray_21) {
    Value v;
    v.loadFromString("[1, \"hello\", true, null, 3.14]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 5u);
    EXPECT_TRUE(v[(size_t)0].isInteger());
    EXPECT_TRUE(v[(size_t)1].isString());
    EXPECT_TRUE(v[(size_t)2].isBoolean());
    EXPECT_TRUE(v[(size_t)3].isNull());
    EXPECT_TRUE(v[(size_t)4].isDouble());
}

// ============================================================
// Self-Assignment Test
// ============================================================
TEST_F(ValueTest_21, SelfAssignment_21) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

// ============================================================
// Overwrite Type Tests
// ============================================================
TEST_F(ValueTest_21, OverwriteWithSetNull_21) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_21, OverwriteStringWithInteger_21) {
    Value v("hello");
    v.setInteger(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 10);
}

TEST_F(ValueTest_21, OverwriteIntegerWithBoolean_21) {
    Value v(42);
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_21, OverwriteBooleanWithDouble_21) {
    Value v(true);
    v.setDouble(9.9);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 9.9);
}

// ============================================================
// Escaped String JSON Loading
// ============================================================
TEST_F(ValueTest_21, LoadStringWithEscapedCharacters_21) {
    Value v;
    v.loadFromString("\"hello\\nworld\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello\nworld");
}

TEST_F(ValueTest_21, LoadStringWithEscapedQuote_21) {
    Value v;
    v.loadFromString("\"he said \\\"hi\\\"\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "he said \"hi\"");
}

// ============================================================
// Large Integer Boundary
// ============================================================
TEST_F(ValueTest_21, LargeInteger_21) {
    Value v(2147483647); // INT_MAX
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST_F(ValueTest_21, MinInteger_21) {
    Value v(-2147483647 - 1); // INT_MIN
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -2147483647 - 1);
}

// ============================================================
// Write and read back with escape all
// ============================================================
TEST_F(ValueTest_21, WriteToStreamEscapeAll_21) {
    Value v("test\n\ttab");
    std::ostringstream oss;
    v.writeToStream(oss, false, true);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// ============================================================
// Unicode Escape
// ============================================================
TEST_F(ValueTest_21, LoadStringWithUnicodeEscape_21) {
    Value v;
    v.loadFromString("\"\\u0041\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "A");
}
