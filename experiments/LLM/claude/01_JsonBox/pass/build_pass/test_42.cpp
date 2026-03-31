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
class ValueTest_42 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Construction Tests
// ============================================================

TEST_F(ValueTest_42, DefaultConstructorIsNull_42) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_42, StringConstructor_42) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_42, CStringConstructor_42) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_42, IntConstructor_42) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_42, DoubleConstructor_42) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_42, BoolConstructorTrue_42) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_42, BoolConstructorFalse_42) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_42, ObjectConstructor_42) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_42, ArrayConstructor_42) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_42, CopyConstructor_42) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "test");
}

TEST_F(ValueTest_42, CopyConstructorNull_42) {
    Value original;
    Value copy(original);
    EXPECT_TRUE(copy.isNull());
}

TEST_F(ValueTest_42, StreamConstructor_42) {
    std::istringstream iss("\"hello\"");
    Value v(iss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

// ============================================================
// Type Checking Tests
// ============================================================

TEST_F(ValueTest_42, IsStringReturnsTrueForString_42) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueTest_42, IsIntegerReturnsTrueForInt_42) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_42, IsDoubleReturnsTrueForDouble_42) {
    Value v(2.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_42, IsNumericForInteger_42) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_42, IsNumericForDouble_42) {
    Value v(5.5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_42, IsNumericForString_42) {
    Value v("not a number");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_42, IsStringableForString_42) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_42, IsStringableForInteger_42) {
    Value v(42);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_42, IsStringableForDouble_42) {
    Value v(3.14);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_42, IsStringableForBoolean_42) {
    Value v(true);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_42, IsStringableForNull_42) {
    Value v;
    EXPECT_TRUE(v.isStringable());
}

// ============================================================
// getString / tryGetString Tests
// ============================================================

TEST_F(ValueTest_42, GetStringReturnsCorrectValue_42) {
    Value v("test string");
    EXPECT_EQ(v.getString(), "test string");
}

TEST_F(ValueTest_42, GetStringOnNonStringReturnsEmpty_42) {
    Value v(42);
    // getString delegates to tryGetString(EMPTY_STRING)
    // For non-string types, it should return the default (empty string)
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_42, TryGetStringReturnsValueForString_42) {
    Value v("hello");
    std::string def = "default";
    EXPECT_EQ(v.tryGetString(def), "hello");
}

TEST_F(ValueTest_42, TryGetStringReturnsDefaultForNonString_42) {
    Value v(123);
    std::string def = "default";
    EXPECT_EQ(v.tryGetString(def), "default");
}

TEST_F(ValueTest_42, GetStringEmptyString_42) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

// ============================================================
// getToString Tests
// ============================================================

TEST_F(ValueTest_42, GetToStringForString_42) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

TEST_F(ValueTest_42, GetToStringForInteger_42) {
    Value v(42);
    std::string result = v.getToString();
    EXPECT_EQ(result, "42");
}

TEST_F(ValueTest_42, GetToStringForBoolTrue_42) {
    Value v(true);
    std::string result = v.getToString();
    // Typically "true" or "1"
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_42, GetToStringForNull_42) {
    Value v;
    std::string result = v.getToString();
    // Null typically produces "null" or empty
    // Just verify it doesn't crash
    (void)result;
}

// ============================================================
// getInteger / tryGetInteger Tests
// ============================================================

TEST_F(ValueTest_42, GetIntegerReturnsCorrectValue_42) {
    Value v(99);
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_42, GetIntegerNegative_42) {
    Value v(-10);
    EXPECT_EQ(v.getInteger(), -10);
}

TEST_F(ValueTest_42, GetIntegerZero_42) {
    Value v(0);
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_42, TryGetIntegerReturnsValueForInt_42) {
    Value v(50);
    EXPECT_EQ(v.tryGetInteger(0), 50);
}

TEST_F(ValueTest_42, TryGetIntegerReturnsDefaultForNonInt_42) {
    Value v("not an int");
    EXPECT_EQ(v.tryGetInteger(77), 77);
}

// ============================================================
// getDouble / tryGetDouble / getFloat / tryGetFloat Tests
// ============================================================

TEST_F(ValueTest_42, GetDoubleReturnsCorrectValue_42) {
    Value v(2.718);
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_42, TryGetDoubleReturnsDefaultForNonDouble_42) {
    Value v("not a double");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.0), 1.0);
}

TEST_F(ValueTest_42, TryGetDoubleReturnsValueForDouble_42) {
    Value v(9.9);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 9.9);
}

TEST_F(ValueTest_42, GetFloatReturnsCorrectValue_42) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 1.5f);
}

TEST_F(ValueTest_42, TryGetFloatReturnsDefaultForNonDouble_42) {
    Value v("string");
    EXPECT_FLOAT_EQ(v.tryGetFloat(3.0f), 3.0f);
}

// ============================================================
// getBoolean / tryGetBoolean Tests
// ============================================================

TEST_F(ValueTest_42, GetBooleanTrue_42) {
    Value v(true);
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_42, GetBooleanFalse_42) {
    Value v(false);
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_42, TryGetBooleanReturnsValueForBool_42) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_42, TryGetBooleanReturnsDefaultForNonBool_42) {
    Value v(42);
    EXPECT_TRUE(v.tryGetBoolean(true));
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ============================================================
// Setter Tests
// ============================================================

TEST_F(ValueTest_42, SetStringChangesType_42) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setString("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST_F(ValueTest_42, SetIntegerChangesType_42) {
    Value v("was a string");
    v.setInteger(100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST_F(ValueTest_42, SetDoubleChangesType_42) {
    Value v(42);
    v.setDouble(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_42, SetBooleanChangesType_42) {
    Value v("was a string");
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_42, SetNullChangesType_42) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_42, SetObjectChangesType_42) {
    Value v(42);
    Object obj;
    obj["a"] = Value(1);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_42, SetArrayChangesType_42) {
    Value v(42);
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    arr.push_back(Value(3));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

// ============================================================
// Assignment Operator Tests
// ============================================================

TEST_F(ValueTest_42, AssignValueFromValue_42) {
    Value v1("hello");
    Value v2(42);
    v2 = v1;
    EXPECT_TRUE(v2.isString());
    EXPECT_EQ(v2.getString(), "hello");
}

TEST_F(ValueTest_42, AssignStringToValue_42) {
    Value v(42);
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_42, AssignCStringToValue_42) {
    Value v(42);
    v = "c-string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "c-string");
}

TEST_F(ValueTest_42, AssignIntToValue_42) {
    Value v("hello");
    v = 123;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

TEST_F(ValueTest_42, AssignDoubleToValue_42) {
    Value v("hello");
    v = 1.5;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.5);
}

TEST_F(ValueTest_42, AssignBoolToValue_42) {
    Value v("hello");
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_42, AssignObjectToValue_42) {
    Value v(42);
    Object obj;
    obj["x"] = Value(10);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_42, AssignArrayToValue_42) {
    Value v(42);
    Array arr;
    arr.push_back(Value("a"));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

// ============================================================
// Comparison Operator Tests
// ============================================================

TEST_F(ValueTest_42, EqualityOperatorSameInts_42) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueTest_42, EqualityOperatorDifferentInts_42) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_42, EqualityOperatorSameStrings_42) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_42, EqualityOperatorDifferentStrings_42) {
    Value v1("abc");
    Value v2("def");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_42, EqualityOperatorDifferentTypes_42) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_42, LessThanOperatorInts_42) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_42, LessThanOrEqualOperator_42) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_42, GreaterThanOperator_42) {
    Value v1(5);
    Value v2(3);
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v2 > v1);
}

TEST_F(ValueTest_42, GreaterThanOrEqualOperator_42) {
    Value v1(5);
    Value v2(5);
    EXPECT_TRUE(v1 >= v2);
}

TEST_F(ValueTest_42, BooleanEquality_42) {
    Value v1(true);
    Value v2(true);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_42, NullEquality_42) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

// ============================================================
// Subscript Operator Tests
// ============================================================

TEST_F(ValueTest_42, SubscriptOperatorStringKeyOnObject_42) {
    Object obj;
    obj["key1"] = Value(100);
    Value v(obj);
    EXPECT_EQ(v["key1"].getInteger(), 100);
}

TEST_F(ValueTest_42, SubscriptOperatorCStringKey_42) {
    Object obj;
    obj["name"] = Value("John");
    Value v(obj);
    EXPECT_EQ(v["name"].getString(), "John");
}

TEST_F(ValueTest_42, SubscriptOperatorIndexOnArray_42) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

TEST_F(ValueTest_42, SubscriptOperatorCreatesKeyIfMissing_42) {
    Object obj;
    Value v(obj);
    v["newKey"] = Value("newValue");
    EXPECT_EQ(v["newKey"].getString(), "newValue");
}

// ============================================================
// Load / Write Tests
// ============================================================

TEST_F(ValueTest_42, LoadFromStringSimpleObject_42) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST_F(ValueTest_42, LoadFromStringSimpleArray_42) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_42, LoadFromStringInteger_42) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_42, LoadFromStringDouble_42) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_42, LoadFromStringBoolTrue_42) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_42, LoadFromStringBoolFalse_42) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_42, LoadFromStringNull_42) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_42, LoadFromStream_42) {
    std::istringstream iss("{\"a\": 1}");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["a"].getInteger(), 1);
}

TEST_F(ValueTest_42, WriteToStreamNoIndent_42) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("42"), std::string::npos);
}

TEST_F(ValueTest_42, WriteToStreamWithIndent_42) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_42, WriteToStreamString_42) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string result = oss.str();
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(ValueTest_42, WriteToStreamNull_42) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string result = oss.str();
    EXPECT_NE(result.find("null"), std::string::npos);
}

TEST_F(ValueTest_42, WriteToStreamBool_42) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string result = oss.str();
    EXPECT_NE(result.find("true"), std::string::npos);
}

// ============================================================
// Static Escape Function Tests
// ============================================================

TEST_F(ValueTest_42, EscapeMinimumCharactersNoEscapeNeeded_42) {
    std::string result = Value::escapeMinimumCharacters("hello");
    EXPECT_EQ(result, "hello");
}

TEST_F(ValueTest_42, EscapeMinimumCharactersWithQuote_42) {
    std::string result = Value::escapeMinimumCharacters("he\"llo");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_42, EscapeMinimumCharactersWithBackslash_42) {
    std::string result = Value::escapeMinimumCharacters("he\\llo");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST_F(ValueTest_42, EscapeMinimumCharactersWithNewline_42) {
    std::string result = Value::escapeMinimumCharacters("he\nllo");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_42, EscapeMinimumCharactersEmptyString_42) {
    std::string result = Value::escapeMinimumCharacters("");
    EXPECT_EQ(result, "");
}

TEST_F(ValueTest_42, EscapeAllCharactersBasic_42) {
    std::string result = Value::escapeAllCharacters("hello");
    // All characters should be escaped to unicode
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_42, EscapeToUnicode_42) {
    std::string result = Value::escapeToUnicode('A');
    // Should produce a unicode escape like \u0041
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ============================================================
// Operator<< Test
// ============================================================

TEST_F(ValueTest_42, StreamInsertionOperator_42) {
    Value v("test");
    std::ostringstream oss;
    oss << v;
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Complex / Nested Structure Tests
// ============================================================

TEST_F(ValueTest_42, NestedObjectAndArray_42) {
    Value v;
    v.loadFromString("{\"arr\": [1, 2, {\"nested\": true}]}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["arr"].isArray());
    EXPECT_EQ(v["arr"].getArray().size(), 3u);
}

TEST_F(ValueTest_42, LoadFromStringWithEscapedCharacters_42) {
    Value v;
    v.loadFromString("{\"key\": \"hello\\nworld\"}");
    EXPECT_TRUE(v.isObject());
    std::string s = v["key"].getString();
    EXPECT_NE(s.find('\n'), std::string::npos);
}

TEST_F(ValueTest_42, RoundTripThroughStream_42) {
    Object obj;
    obj["name"] = Value("test");
    obj["value"] = Value(42);
    obj["flag"] = Value(true);
    Value original(obj);

    std::ostringstream oss;
    original.writeToStream(oss, false, false);

    Value parsed;
    parsed.loadFromString(oss.str());
    EXPECT_TRUE(parsed.isObject());
    EXPECT_EQ(parsed["name"].getString(), "test");
    EXPECT_EQ(parsed["value"].getInteger(), 42);
    EXPECT_TRUE(parsed["flag"].getBoolean());
}

// ============================================================
// Boundary / Edge Case Tests
// ============================================================

TEST_F(ValueTest_42, EmptyObject_42) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_42, EmptyArray_42) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_42, EmptyStringValue_42) {
    Value v;
    v.loadFromString("\"\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_42, LargeInteger_42) {
    Value v(2147483647); // INT_MAX
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST_F(ValueTest_42, NegativeInteger_42) {
    Value v(-2147483647);
    EXPECT_EQ(v.getInteger(), -2147483647);
}

TEST_F(ValueTest_42, ZeroDouble_42) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_42, NegativeDouble_42) {
    Value v(-1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -1.5);
}

TEST_F(ValueTest_42, SetNullThenSetString_42) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
    v.setString("recovered");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "recovered");
}

TEST_F(ValueTest_42, MultipleTypeChanges_42) {
    Value v;
    EXPECT_TRUE(v.isNull());
    v = 42;
    EXPECT_TRUE(v.isInteger());
    v = "string";
    EXPECT_TRUE(v.isString());
    v = 3.14;
    EXPECT_TRUE(v.isDouble());
    v = true;
    EXPECT_TRUE(v.isBoolean());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_42, SelfAssignment_42) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_42, GetObjectReturnsCorrectContents_42) {
    Object obj;
    obj["a"] = Value(1);
    obj["b"] = Value(2);
    Value v(obj);
    const Object& retrieved = v.getObject();
    EXPECT_EQ(retrieved.size(), 2u);
    EXPECT_EQ(retrieved.at("a").getInteger(), 1);
    EXPECT_EQ(retrieved.at("b").getInteger(), 2);
}

TEST_F(ValueTest_42, GetArrayReturnsCorrectContents_42) {
    Array arr;
    arr.push_back(Value("x"));
    arr.push_back(Value("y"));
    Value v(arr);
    const Array& retrieved = v.getArray();
    EXPECT_EQ(retrieved.size(), 2u);
    EXPECT_EQ(retrieved[0].getString(), "x");
    EXPECT_EQ(retrieved[1].getString(), "y");
}

TEST_F(ValueTest_42, WriteEscapeAll_42) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, true);
    std::string result = oss.str();
    // With escapeAll=true, characters should be unicode-escaped
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_42, LoadFromStringWithWhitespace_42) {
    Value v;
    v.loadFromString("  {  \"key\"  :  \"value\"  }  ");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST_F(ValueTest_42, LoadFromStringNegativeNumber_42) {
    Value v;
    v.loadFromString("-42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST_F(ValueTest_42, LoadFromStringScientificNotation_42) {
    Value v;
    v.loadFromString("1.5e2");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 150.0);
}
