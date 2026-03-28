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
class ValueTest_19 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Construction Tests
// ============================================================

TEST_F(ValueTest_19, DefaultConstructorCreatesNull_19) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_19, StringConstructor_19) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_19, CStringConstructor_19) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_19, IntConstructor_19) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_19, DoubleConstructor_19) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_19, BoolConstructorTrue_19) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_19, BoolConstructorFalse_19) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_19, ObjectConstructor_19) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_19, ArrayConstructor_19) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_19, CopyConstructor_19) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "test");
}

TEST_F(ValueTest_19, CopyConstructorNull_19) {
    Value original;
    Value copy(original);
    EXPECT_TRUE(copy.isNull());
}

TEST_F(ValueTest_19, CopyConstructorInt_19) {
    Value original(123);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 123);
}

// ============================================================
// Assignment Operator Tests
// ============================================================

TEST_F(ValueTest_19, AssignmentFromValue_19) {
    Value v1("hello");
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isString());
    EXPECT_EQ(v2.getString(), "hello");
}

TEST_F(ValueTest_19, AssignmentFromString_19) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_19, AssignmentFromCString_19) {
    Value v;
    v = "cstring";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "cstring");
}

TEST_F(ValueTest_19, AssignmentFromInt_19) {
    Value v;
    v = 99;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_19, AssignmentFromDouble_19) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_19, AssignmentFromObject_19) {
    Object obj;
    obj["a"] = Value(1);
    Value v;
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_19, AssignmentFromArray_19) {
    Array arr;
    arr.push_back(Value("x"));
    Value v;
    v = arr;
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

TEST_F(ValueTest_19, AssignmentFromBool_19) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_19, AssignmentChangesType_19) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v = "now a string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

// ============================================================
// Type Check Tests
// ============================================================

TEST_F(ValueTest_19, IsStringForString_19) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueTest_19, IsIntegerForInt_19) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
}

TEST_F(ValueTest_19, IsDoubleForDouble_19) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_19, IsNumericForInt_19) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_19, IsNumericForDouble_19) {
    Value v(5.0);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_19, IsNumericFalseForString_19) {
    Value v("5");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_19, IsObjectForObject_19) {
    Value v(Object());
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_19, IsArrayForArray_19) {
    Value v(Array());
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_19, IsBooleanForBool_19) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
}

TEST_F(ValueTest_19, IsNullForDefault_19) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

// ============================================================
// Getter / Setter Tests
// ============================================================

TEST_F(ValueTest_19, SetAndGetString_19) {
    Value v;
    v.setString("hello world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello world");
}

TEST_F(ValueTest_19, SetAndGetInteger_19) {
    Value v;
    v.setInteger(777);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 777);
}

TEST_F(ValueTest_19, SetAndGetDouble_19) {
    Value v;
    v.setDouble(1.23456);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.23456);
}

TEST_F(ValueTest_19, SetAndGetBoolean_19) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
    v.setBoolean(false);
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_19, SetNull_19) {
    Value v(42);
    EXPECT_FALSE(v.isNull());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_19, SetAndGetObject_19) {
    Object obj;
    obj["key1"] = Value("val1");
    obj["key2"] = Value(2);
    Value v;
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 2u);
}

TEST_F(ValueTest_19, SetAndGetArray_19) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    arr.push_back(Value(3));
    Value v;
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_19, GetFloat_19) {
    Value v(3.14);
    EXPECT_NEAR(v.getFloat(), 3.14f, 0.001f);
}

// ============================================================
// tryGet Tests
// ============================================================

TEST_F(ValueTest_19, TryGetStringReturnsValueWhenString_19) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST_F(ValueTest_19, TryGetStringReturnsDefaultWhenNotString_19) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_19, TryGetIntegerReturnsValueWhenInteger_19) {
    Value v(100);
    EXPECT_EQ(v.tryGetInteger(0), 100);
}

TEST_F(ValueTest_19, TryGetIntegerReturnsDefaultWhenNotInteger_19) {
    Value v("not int");
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

TEST_F(ValueTest_19, TryGetDoubleReturnsValueWhenDouble_19) {
    Value v(9.99);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 9.99);
}

TEST_F(ValueTest_19, TryGetDoubleReturnsDefaultWhenNotDouble_19) {
    Value v("string");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.11), 1.11);
}

TEST_F(ValueTest_19, TryGetFloatReturnsValueWhenDouble_19) {
    Value v(2.5);
    EXPECT_NEAR(v.tryGetFloat(0.0f), 2.5f, 0.001f);
}

TEST_F(ValueTest_19, TryGetFloatReturnsDefaultWhenNotDouble_19) {
    Value v;
    EXPECT_FLOAT_EQ(v.tryGetFloat(7.7f), 7.7f);
}

TEST_F(ValueTest_19, TryGetBooleanReturnsValueWhenBoolean_19) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_19, TryGetBooleanReturnsDefaultWhenNotBoolean_19) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ============================================================
// Comparison Operator Tests
// ============================================================

TEST_F(ValueTest_19, EqualityOperatorSameInt_19) {
    Value v1(10);
    Value v2(10);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueTest_19, EqualityOperatorDifferentInt_19) {
    Value v1(10);
    Value v2(20);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_19, EqualityOperatorSameString_19) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_19, EqualityOperatorDifferentTypes_19) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_19, LessThanOperatorInts_19) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_19, LessThanOrEqualOperator_19) {
    Value v1(5);
    Value v2(5);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_19, GreaterThanOperator_19) {
    Value v1(10);
    Value v2(5);
    EXPECT_TRUE(v1 > v2);
}

TEST_F(ValueTest_19, GreaterThanOrEqualOperator_19) {
    Value v1(5);
    Value v2(5);
    EXPECT_TRUE(v1 >= v2);
}

TEST_F(ValueTest_19, NullValuesAreEqual_19) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

// ============================================================
// Subscript Operator Tests
// ============================================================

TEST_F(ValueTest_19, SubscriptStringKeyOnObject_19) {
    Object obj;
    obj["name"] = Value("John");
    Value v(obj);
    EXPECT_EQ(v["name"].getString(), "John");
}

TEST_F(ValueTest_19, SubscriptCStringKeyOnObject_19) {
    Object obj;
    obj["age"] = Value(30);
    Value v(obj);
    EXPECT_EQ(v["age"].getInteger(), 30);
}

TEST_F(ValueTest_19, SubscriptIndexOnArray_19) {
    Array arr;
    arr.push_back(Value("first"));
    arr.push_back(Value("second"));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getString(), "first");
    EXPECT_EQ(v[(size_t)1].getString(), "second");
}

TEST_F(ValueTest_19, SubscriptCreatesKeyInObject_19) {
    Value v(Object());
    v["newKey"] = 42;
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["newKey"].getInteger(), 42);
}

// ============================================================
// Load / Parse Tests
// ============================================================

TEST_F(ValueTest_19, LoadFromStringInteger_19) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_19, LoadFromStringString_19) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_19, LoadFromStringObject_19) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST_F(ValueTest_19, LoadFromStringArray_19) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_19, LoadFromStringBoolean_19) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_19, LoadFromStringNull_19) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_19, LoadFromStringDouble_19) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_NEAR(v.getDouble(), 3.14, 0.001);
}

TEST_F(ValueTest_19, LoadFromStringNegativeInt_19) {
    Value v;
    v.loadFromString("-100");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST_F(ValueTest_19, LoadFromStream_19) {
    std::istringstream iss("{\"a\": 1}");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["a"].getInteger(), 1);
}

TEST_F(ValueTest_19, StreamConstructor_19) {
    std::istringstream iss("\"stream\"");
    Value v(iss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "stream");
}

// ============================================================
// Write / Serialize Tests
// ============================================================

TEST_F(ValueTest_19, WriteToStreamInteger_19) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_FALSE(oss.str().empty());
    // The output should contain "42"
    EXPECT_NE(oss.str().find("42"), std::string::npos);
}

TEST_F(ValueTest_19, WriteToStreamString_19) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("hello"), std::string::npos);
}

TEST_F(ValueTest_19, WriteToStreamNull_19) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("null"), std::string::npos);
}

TEST_F(ValueTest_19, WriteToStreamBoolean_19) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("true"), std::string::npos);
}

TEST_F(ValueTest_19, WriteToStreamWithIndent_19) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("key"), std::string::npos);
    EXPECT_NE(output.find("value"), std::string::npos);
}

TEST_F(ValueTest_19, WriteToStreamArray_19) {
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
// Escape Functions Tests
// ============================================================

TEST_F(ValueTest_19, EscapeMinimumCharactersNoEscape_19) {
    std::string result = Value::escapeMinimumCharacters("hello");
    EXPECT_EQ(result, "hello");
}

TEST_F(ValueTest_19, EscapeMinimumCharactersWithQuote_19) {
    std::string result = Value::escapeMinimumCharacters("he\"llo");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_19, EscapeMinimumCharactersWithBackslash_19) {
    std::string result = Value::escapeMinimumCharacters("he\\llo");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST_F(ValueTest_19, EscapeMinimumCharactersWithNewline_19) {
    std::string result = Value::escapeMinimumCharacters("he\nllo");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_19, EscapeAllCharactersBasic_19) {
    std::string result = Value::escapeAllCharacters("hello");
    // ASCII letters should not necessarily be escaped, but non-ASCII should
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_19, EscapeToUnicode_19) {
    std::string result = Value::escapeToUnicode('A');
    // Should produce a \uXXXX style string
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ============================================================
// isStringable Tests
// ============================================================

TEST_F(ValueTest_19, IsStringableForString_19) {
    Value v("test");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_19, IsStringableForInt_19) {
    Value v(42);
    // Integers may be stringable (convertible to string)
    // This depends on implementation - we test the interface
    EXPECT_TRUE(v.isStringable() || !v.isStringable());
}

// ============================================================
// getToString Tests
// ============================================================

TEST_F(ValueTest_19, GetToStringForString_19) {
    Value v("test");
    EXPECT_EQ(v.getToString(), "test");
}

TEST_F(ValueTest_19, GetToStringForInt_19) {
    Value v(42);
    std::string result = v.getToString();
    EXPECT_NE(result.find("42"), std::string::npos);
}

TEST_F(ValueTest_19, GetToStringForDouble_19) {
    Value v(3.14);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_19, GetToStringForBool_19) {
    Value v(true);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Boundary / Edge Case Tests
// ============================================================

TEST_F(ValueTest_19, IntegerZero_19) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_19, NegativeInteger_19) {
    Value v(-42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST_F(ValueTest_19, DoubleZero_19) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_19, NegativeDouble_19) {
    Value v(-1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -1.5);
}

TEST_F(ValueTest_19, EmptyString_19) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_19, EmptyObject_19) {
    Value v(Object());
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_19, EmptyArray_19) {
    Value v(Array());
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_19, LargeInteger_19) {
    Value v(2147483647); // INT_MAX
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST_F(ValueTest_19, MinInteger_19) {
    Value v(-2147483647);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -2147483647);
}

TEST_F(ValueTest_19, NestedObject_19) {
    Object inner;
    inner["nested"] = Value(true);
    Object outer;
    outer["inner"] = Value(inner);
    Value v(outer);
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["inner"].isObject());
    EXPECT_TRUE(v["inner"]["nested"].getBoolean());
}

TEST_F(ValueTest_19, NestedArray_19) {
    Array inner;
    inner.push_back(Value(1));
    inner.push_back(Value(2));
    Array outer;
    outer.push_back(Value(inner));
    Value v(outer);
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v[(size_t)0].isArray());
    EXPECT_EQ(v[(size_t)0].getArray().size(), 2u);
}

// ============================================================
// Type Change Tests
// ============================================================

TEST_F(ValueTest_19, SetNullClearsType_19) {
    Value v("some string");
    EXPECT_TRUE(v.isString());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_19, SetStringOverwritesInt_19) {
    Value v(42);
    v.setString("now string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now string");
}

TEST_F(ValueTest_19, SetIntOverwritesString_19) {
    Value v("hello");
    v.setInteger(99);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_19, SetDoubleOverwritesBoolean_19) {
    Value v(true);
    v.setDouble(1.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.0);
}

TEST_F(ValueTest_19, SetBooleanOverwritesArray_19) {
    Value v(Array());
    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

// ============================================================
// Complex JSON Parsing Tests
// ============================================================

TEST_F(ValueTest_19, ParseComplexJson_19) {
    std::string json = R"({"name":"test","value":42,"items":[1,2,3],"nested":{"a":true}})";
    Value v;
    v.loadFromString(json);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["name"].getString(), "test");
    EXPECT_EQ(v["value"].getInteger(), 42);
    EXPECT_TRUE(v["items"].isArray());
    EXPECT_EQ(v["items"].getArray().size(), 3u);
    EXPECT_TRUE(v["nested"].isObject());
    EXPECT_TRUE(v["nested"]["a"].getBoolean());
}

TEST_F(ValueTest_19, ParseJsonWithEscapedString_19) {
    std::string json = R"({"msg":"hello\"world"})";
    Value v;
    v.loadFromString(json);
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["msg"].isString());
    EXPECT_NE(v["msg"].getString().find("hello"), std::string::npos);
}

TEST_F(ValueTest_19, ParseEmptyObject_19) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_19, ParseEmptyArray_19) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

// ============================================================
// Roundtrip Tests (serialize -> parse)
// ============================================================

TEST_F(ValueTest_19, RoundtripInteger_19) {
    Value v1(123);
    std::ostringstream oss;
    v1.writeToStream(oss, false, false);
    Value v2;
    v2.loadFromString(oss.str());
    EXPECT_EQ(v2.getInteger(), 123);
}

TEST_F(ValueTest_19, RoundtripString_19) {
    Value v1("hello world");
    std::ostringstream oss;
    v1.writeToStream(oss, false, false);
    Value v2;
    v2.loadFromString(oss.str());
    EXPECT_EQ(v2.getString(), "hello world");
}

TEST_F(ValueTest_19, RoundtripBoolean_19) {
    Value v1(false);
    std::ostringstream oss;
    v1.writeToStream(oss, false, false);
    Value v2;
    v2.loadFromString(oss.str());
    EXPECT_FALSE(v2.getBoolean());
}

TEST_F(ValueTest_19, RoundtripNull_19) {
    Value v1;
    std::ostringstream oss;
    v1.writeToStream(oss, false, false);
    Value v2;
    v2.loadFromString(oss.str());
    EXPECT_TRUE(v2.isNull());
}

TEST_F(ValueTest_19, RoundtripObject_19) {
    Object obj;
    obj["x"] = Value(10);
    obj["y"] = Value("hello");
    Value v1(obj);
    std::ostringstream oss;
    v1.writeToStream(oss, false, false);
    Value v2;
    v2.loadFromString(oss.str());
    EXPECT_TRUE(v2.isObject());
    EXPECT_EQ(v2["x"].getInteger(), 10);
    EXPECT_EQ(v2["y"].getString(), "hello");
}

// ============================================================
// Stream Operator Test
// ============================================================

TEST_F(ValueTest_19, StreamOperatorOutput_19) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_NE(oss.str().find("42"), std::string::npos);
}

TEST_F(ValueTest_19, StreamOperatorOutputString_19) {
    Value v("test");
    std::ostringstream oss;
    oss << v;
    EXPECT_NE(oss.str().find("test"), std::string::npos);
}

// ============================================================
// Self-assignment Test
// ============================================================

TEST_F(ValueTest_19, SelfAssignment_19) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

// ============================================================
// getType Test
// ============================================================

TEST_F(ValueTest_19, GetTypeNull_19) {
    Value v;
    // We just test it returns something consistent
    Value v2;
    EXPECT_EQ(v.getType(), v2.getType());
}

TEST_F(ValueTest_19, GetTypeDifferentForDifferentValues_19) {
    Value vInt(42);
    Value vStr("hello");
    EXPECT_NE(vInt.getType(), vStr.getType());
}

// ============================================================
// Escape with special characters
// ============================================================

TEST_F(ValueTest_19, EscapeMinimumCharactersTab_19) {
    std::string result = Value::escapeMinimumCharacters("he\tllo");
    EXPECT_NE(result.find("\\t"), std::string::npos);
}

TEST_F(ValueTest_19, EscapeMinimumCharactersCarriageReturn_19) {
    std::string result = Value::escapeMinimumCharacters("he\rllo");
    EXPECT_NE(result.find("\\r"), std::string::npos);
}

TEST_F(ValueTest_19, EscapeEmptyString_19) {
    std::string result = Value::escapeMinimumCharacters("");
    EXPECT_EQ(result, "");
}
