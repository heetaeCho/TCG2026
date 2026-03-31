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
class ValueTest_16 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Default Constructor Tests
// ============================================================
TEST_F(ValueTest_16, DefaultConstructorCreatesNull_16) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

// ============================================================
// String Constructor and Accessor Tests
// ============================================================
TEST_F(ValueTest_16, StringConstructor_16) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_16, CStringConstructor_16) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_16, EmptyStringConstructor_16) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

// ============================================================
// Integer Constructor and Accessor Tests
// ============================================================
TEST_F(ValueTest_16, IntConstructor_16) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_16, IntConstructorNegative_16) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST_F(ValueTest_16, IntConstructorZero_16) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

// ============================================================
// Double Constructor and Accessor Tests
// ============================================================
TEST_F(ValueTest_16, DoubleConstructor_16) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_16, DoubleConstructorNegative_16) {
    Value v(-2.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -2.5);
}

TEST_F(ValueTest_16, DoubleConstructorZero_16) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

// ============================================================
// Boolean Constructor and Accessor Tests
// ============================================================
TEST_F(ValueTest_16, BoolConstructorTrue_16) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_16, BoolConstructorFalse_16) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

// ============================================================
// Object Constructor and Accessor Tests
// ============================================================
TEST_F(ValueTest_16, ObjectConstructor_16) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
    EXPECT_EQ(v.getObject().at("key").getString(), "value");
}

TEST_F(ValueTest_16, EmptyObjectConstructor_16) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

// ============================================================
// Array Constructor and Accessor Tests
// ============================================================
TEST_F(ValueTest_16, ArrayConstructor_16) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    arr.push_back(Value(3));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
    EXPECT_EQ(v.getArray()[0].getInteger(), 1);
    EXPECT_EQ(v.getArray()[2].getInteger(), 3);
}

TEST_F(ValueTest_16, EmptyArrayConstructor_16) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

// ============================================================
// Copy Constructor Tests
// ============================================================
TEST_F(ValueTest_16, CopyConstructorString_16) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "test");
}

TEST_F(ValueTest_16, CopyConstructorInt_16) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

TEST_F(ValueTest_16, CopyConstructorNull_16) {
    Value original;
    Value copy(original);
    EXPECT_TRUE(copy.isNull());
}

// ============================================================
// Assignment Operator Tests
// ============================================================
TEST_F(ValueTest_16, AssignmentFromValue_16) {
    Value v1("hello");
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isString());
    EXPECT_EQ(v2.getString(), "hello");
}

TEST_F(ValueTest_16, AssignmentFromString_16) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_16, AssignmentFromCString_16) {
    Value v;
    v = "cstring";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "cstring");
}

TEST_F(ValueTest_16, AssignmentFromInt_16) {
    Value v;
    v = 99;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_16, AssignmentFromDouble_16) {
    Value v;
    v = 1.618;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.618);
}

TEST_F(ValueTest_16, AssignmentFromBool_16) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_16, AssignmentFromObject_16) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().at("a").getInteger(), 1);
}

TEST_F(ValueTest_16, AssignmentFromArray_16) {
    Value v;
    Array arr;
    arr.push_back(Value("elem"));
    v = arr;
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray()[0].getString(), "elem");
}

// ============================================================
// Type Change via Assignment Tests
// ============================================================
TEST_F(ValueTest_16, TypeChangeFromIntToString_16) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v = std::string("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST_F(ValueTest_16, TypeChangeFromStringToInt_16) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    v = 10;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 10);
}

TEST_F(ValueTest_16, TypeChangeFromNullToBool_16) {
    Value v;
    EXPECT_TRUE(v.isNull());
    v = false;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

// ============================================================
// Setter Tests
// ============================================================
TEST_F(ValueTest_16, SetString_16) {
    Value v;
    v.setString("set_string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "set_string");
}

TEST_F(ValueTest_16, SetInteger_16) {
    Value v;
    v.setInteger(123);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

TEST_F(ValueTest_16, SetDouble_16) {
    Value v;
    v.setDouble(9.81);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 9.81);
}

TEST_F(ValueTest_16, SetBoolean_16) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_16, SetObject_16) {
    Value v;
    Object obj;
    obj["x"] = Value(42);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_16, SetArray_16) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_16, SetNull_16) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

// ============================================================
// Type Check Tests (isXxx methods)
// ============================================================
TEST_F(ValueTest_16, IsStringForString_16) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueTest_16, IsIntegerForInteger_16) {
    Value v(5);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_16, IsDoubleForDouble_16) {
    Value v(1.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_16, IsNumericForInteger_16) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_16, IsNumericForDouble_16) {
    Value v(5.0);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_16, IsNumericForString_16) {
    Value v("hello");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_16, IsStringableForString_16) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_16, IsStringableForInteger_16) {
    Value v(42);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_16, IsStringableForDouble_16) {
    Value v(3.14);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_16, IsStringableForNull_16) {
    Value v;
    // Null may or may not be stringable; just test it doesn't crash
    v.isStringable();
}

// ============================================================
// Comparison Operator Tests
// ============================================================
TEST_F(ValueTest_16, EqualityOperatorSameInt_16) {
    Value v1(10);
    Value v2(10);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueTest_16, EqualityOperatorDifferentInt_16) {
    Value v1(10);
    Value v2(20);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_16, EqualityOperatorSameString_16) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_16, EqualityOperatorDifferentString_16) {
    Value v1("abc");
    Value v2("xyz");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_16, EqualityOperatorDifferentTypes_16) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_16, LessThanOperatorInts_16) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_16, LessThanOrEqualOperator_16) {
    Value v1(5);
    Value v2(5);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_16, GreaterThanOperator_16) {
    Value v1(10);
    Value v2(5);
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v2 > v1);
}

TEST_F(ValueTest_16, GreaterThanOrEqualOperator_16) {
    Value v1(5);
    Value v2(5);
    EXPECT_TRUE(v1 >= v2);
}

TEST_F(ValueTest_16, EqualityBooleans_16) {
    Value v1(true);
    Value v2(true);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_16, EqualityNulls_16) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

// ============================================================
// Subscript Operator Tests
// ============================================================
TEST_F(ValueTest_16, SubscriptStringKeyOnObject_16) {
    Object obj;
    obj["name"] = Value("Alice");
    Value v(obj);
    EXPECT_EQ(v["name"].getString(), "Alice");
}

TEST_F(ValueTest_16, SubscriptCStringKeyOnObject_16) {
    Object obj;
    obj["key"] = Value(100);
    Value v(obj);
    EXPECT_EQ(v["key"].getInteger(), 100);
}

TEST_F(ValueTest_16, SubscriptIndexOnArray_16) {
    Array arr;
    arr.push_back(Value("first"));
    arr.push_back(Value("second"));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getString(), "first");
    EXPECT_EQ(v[(size_t)1].getString(), "second");
}

TEST_F(ValueTest_16, SubscriptCreatesNewKeyInObject_16) {
    Object obj;
    Value v(obj);
    v["newkey"] = 42;
    EXPECT_EQ(v["newkey"].getInteger(), 42);
}

// ============================================================
// tryGet Methods Tests
// ============================================================
TEST_F(ValueTest_16, TryGetStringReturnsValueWhenString_16) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST_F(ValueTest_16, TryGetStringReturnsDefaultWhenNotString_16) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_16, TryGetIntegerReturnsValueWhenInteger_16) {
    Value v(7);
    EXPECT_EQ(v.tryGetInteger(0), 7);
}

TEST_F(ValueTest_16, TryGetIntegerReturnsDefaultWhenNotInteger_16) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

TEST_F(ValueTest_16, TryGetDoubleReturnsValueWhenDouble_16) {
    Value v(2.718);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 2.718);
}

TEST_F(ValueTest_16, TryGetDoubleReturnsDefaultWhenNotDouble_16) {
    Value v("text");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(9.9), 9.9);
}

TEST_F(ValueTest_16, TryGetBooleanReturnsValueWhenBoolean_16) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_16, TryGetBooleanReturnsDefaultWhenNotBoolean_16) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_16, TryGetFloatReturnsDefaultWhenNotDouble_16) {
    Value v("text");
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.5f), 1.5f);
}

// ============================================================
// getFloat Tests
// ============================================================
TEST_F(ValueTest_16, GetFloatFromDouble_16) {
    Value v(3.14);
    EXPECT_NEAR(v.getFloat(), 3.14f, 0.001f);
}

// ============================================================
// getToString Tests
// ============================================================
TEST_F(ValueTest_16, GetToStringFromString_16) {
    Value v("test");
    EXPECT_EQ(v.getToString(), "test");
}

TEST_F(ValueTest_16, GetToStringFromInteger_16) {
    Value v(42);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_16, GetToStringFromDouble_16) {
    Value v(3.14);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

// ============================================================
// loadFromString Tests
// ============================================================
TEST_F(ValueTest_16, LoadFromStringInteger_16) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_16, LoadFromStringString_16) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_16, LoadFromStringBoolTrue_16) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_16, LoadFromStringBoolFalse_16) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_16, LoadFromStringNull_16) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_16, LoadFromStringDouble_16) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_NEAR(v.getDouble(), 3.14, 0.001);
}

TEST_F(ValueTest_16, LoadFromStringObject_16) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST_F(ValueTest_16, LoadFromStringArray_16) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_16, LoadFromStringEmptyObject_16) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_16, LoadFromStringEmptyArray_16) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_16, LoadFromStringNestedObject_16) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": 42}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

// ============================================================
// loadFromStream Tests
// ============================================================
TEST_F(ValueTest_16, LoadFromStream_16) {
    Value v;
    std::istringstream ss("\"stream_test\"");
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "stream_test");
}

TEST_F(ValueTest_16, ConstructFromStream_16) {
    std::istringstream ss("123");
    Value v(ss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

// ============================================================
// writeToStream Tests
// ============================================================
TEST_F(ValueTest_16, WriteToStreamInteger_16) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_FALSE(oss.str().empty());
    EXPECT_NE(oss.str().find("42"), std::string::npos);
}

TEST_F(ValueTest_16, WriteToStreamString_16) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("hello"), std::string::npos);
}

TEST_F(ValueTest_16, WriteToStreamBoolTrue_16) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("true"), std::string::npos);
}

TEST_F(ValueTest_16, WriteToStreamNull_16) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("null"), std::string::npos);
}

TEST_F(ValueTest_16, WriteToStreamWithIndent_16) {
    Object obj;
    obj["key"] = Value(1);
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTest_16, WriteToStreamArray_16) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
}

// ============================================================
// Operator<< Tests
// ============================================================
TEST_F(ValueTest_16, StreamInsertionOperator_16) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

// ============================================================
// Escape Methods Tests
// ============================================================
TEST_F(ValueTest_16, EscapeMinimumCharactersBasic_16) {
    std::string input = "hello";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ(result, "hello");
}

TEST_F(ValueTest_16, EscapeMinimumCharactersWithQuote_16) {
    std::string input = "he\"llo";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_16, EscapeMinimumCharactersWithBackslash_16) {
    std::string input = "back\\slash";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST_F(ValueTest_16, EscapeMinimumCharactersWithNewline_16) {
    std::string input = "line\nbreak";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_16, EscapeMinimumCharactersWithTab_16) {
    std::string input = "tab\there";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_NE(result.find("\\t"), std::string::npos);
}

TEST_F(ValueTest_16, EscapeAllCharactersBasic_16) {
    std::string input = "abc";
    std::string result = Value::escapeAllCharacters(input);
    // All characters should be escaped to unicode
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_16, EscapeToUnicodeChar_16) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result.substr(0, 2), "\\u");
}

TEST_F(ValueTest_16, EscapeMinimumCharactersEmpty_16) {
    std::string result = Value::escapeMinimumCharacters("");
    EXPECT_EQ(result, "");
}

// ============================================================
// Negative Integer Tests
// ============================================================
TEST_F(ValueTest_16, LoadFromStringNegativeInteger_16) {
    Value v;
    v.loadFromString("-42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST_F(ValueTest_16, LoadFromStringNegativeDouble_16) {
    Value v;
    v.loadFromString("-3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_NEAR(v.getDouble(), -3.14, 0.001);
}

// ============================================================
// Complex JSON Loading
// ============================================================
TEST_F(ValueTest_16, LoadComplexJson_16) {
    Value v;
    v.loadFromString("{\"name\": \"John\", \"age\": 30, \"active\": true, \"scores\": [1, 2, 3], \"address\": null}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["name"].getString(), "John");
    EXPECT_EQ(v["age"].getInteger(), 30);
    EXPECT_TRUE(v["active"].getBoolean());
    EXPECT_TRUE(v["scores"].isArray());
    EXPECT_EQ(v["scores"].getArray().size(), 3u);
    EXPECT_TRUE(v["address"].isNull());
}

// ============================================================
// Round-trip Test (write and read back)
// ============================================================
TEST_F(ValueTest_16, RoundTripStringValue_16) {
    Value original("round trip test");
    std::ostringstream oss;
    original.writeToStream(oss, false, false);
    Value loaded;
    loaded.loadFromString(oss.str());
    EXPECT_TRUE(loaded.isString());
    EXPECT_EQ(loaded.getString(), "round trip test");
}

TEST_F(ValueTest_16, RoundTripObject_16) {
    Object obj;
    obj["key1"] = Value(1);
    obj["key2"] = Value("two");
    Value original(obj);
    std::ostringstream oss;
    original.writeToStream(oss, false, false);
    Value loaded;
    loaded.loadFromString(oss.str());
    EXPECT_TRUE(loaded.isObject());
    EXPECT_EQ(loaded["key1"].getInteger(), 1);
    EXPECT_EQ(loaded["key2"].getString(), "two");
}

TEST_F(ValueTest_16, RoundTripArray_16) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value("text"));
    arr.push_back(Value(true));
    Value original(arr);
    std::ostringstream oss;
    original.writeToStream(oss, false, false);
    Value loaded;
    loaded.loadFromString(oss.str());
    EXPECT_TRUE(loaded.isArray());
    EXPECT_EQ(loaded.getArray().size(), 3u);
}

// ============================================================
// Self-Assignment Test
// ============================================================
TEST_F(ValueTest_16, SelfAssignment_16) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

// ============================================================
// getType Tests
// ============================================================
TEST_F(ValueTest_16, GetTypeNull_16) {
    Value v;
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_16, GetTypeString_16) {
    Value v("s");
    EXPECT_EQ(v.getType(), Value::STRING);
}

TEST_F(ValueTest_16, GetTypeInteger_16) {
    Value v(1);
    EXPECT_EQ(v.getType(), Value::INTEGER);
}

TEST_F(ValueTest_16, GetTypeDouble_16) {
    Value v(1.0);
    EXPECT_EQ(v.getType(), Value::DOUBLE);
}

TEST_F(ValueTest_16, GetTypeObject_16) {
    Value v(Object());
    EXPECT_EQ(v.getType(), Value::OBJECT);
}

TEST_F(ValueTest_16, GetTypeArray_16) {
    Value v(Array());
    EXPECT_EQ(v.getType(), Value::ARRAY);
}

TEST_F(ValueTest_16, GetTypeBoolean_16) {
    Value v(true);
    EXPECT_EQ(v.getType(), Value::BOOLEAN);
}

// ============================================================
// String with special JSON characters
// ============================================================
TEST_F(ValueTest_16, LoadStringWithEscapedCharacters_16) {
    Value v;
    v.loadFromString("\"hello\\nworld\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello\nworld");
}

TEST_F(ValueTest_16, LoadStringWithUnicode_16) {
    Value v;
    v.loadFromString("\"\\u0041\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "A");
}

// ============================================================
// Large number boundary
// ============================================================
TEST_F(ValueTest_16, LargeInteger_16) {
    Value v(2147483647);  // INT_MAX
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST_F(ValueTest_16, NegativeLargeInteger_16) {
    Value v(-2147483647);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -2147483647);
}

// ============================================================
// Write with escapeAll flag
// ============================================================
TEST_F(ValueTest_16, WriteToStreamWithEscapeAll_16) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, true);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    // With escapeAll, ASCII characters should be escaped to unicode
    EXPECT_NE(output.find("\\u"), std::string::npos);
}
