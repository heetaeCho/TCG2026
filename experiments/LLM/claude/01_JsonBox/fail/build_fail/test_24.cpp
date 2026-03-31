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
class ValueTest_24 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Default Constructor Tests
// ============================================================
TEST_F(ValueTest_24, DefaultConstructorIsNull_24) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_24, DefaultConstructorTypeIsNullValue_24) {
    Value v;
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

// ============================================================
// String Constructor Tests
// ============================================================
TEST_F(ValueTest_24, StringConstructor_24) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_24, CStringConstructor_24) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_24, EmptyStringConstructor_24) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

// ============================================================
// Integer Constructor Tests
// ============================================================
TEST_F(ValueTest_24, IntConstructor_24) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_24, IntConstructorZero_24) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_24, IntConstructorNegative_24) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

// ============================================================
// Double Constructor Tests
// ============================================================
TEST_F(ValueTest_24, DoubleConstructor_24) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_24, DoubleConstructorZero_24) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_24, DoubleConstructorNegative_24) {
    Value v(-2.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -2.5);
}

// ============================================================
// Boolean Constructor Tests
// ============================================================
TEST_F(ValueTest_24, BoolConstructorTrue_24) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_24, BoolConstructorFalse_24) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

// ============================================================
// Object Constructor Tests
// ============================================================
TEST_F(ValueTest_24, ObjectConstructor_24) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_24, EmptyObjectConstructor_24) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v.getObject().empty());
}

// ============================================================
// Array Constructor Tests
// ============================================================
TEST_F(ValueTest_24, ArrayConstructor_24) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_24, EmptyArrayConstructor_24) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v.getArray().empty());
}

// ============================================================
// Copy Constructor Tests
// ============================================================
TEST_F(ValueTest_24, CopyConstructorString_24) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "test");
}

TEST_F(ValueTest_24, CopyConstructorInt_24) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

TEST_F(ValueTest_24, CopyConstructorNull_24) {
    Value original;
    Value copy(original);
    EXPECT_TRUE(copy.isNull());
}

// ============================================================
// Assignment Operator Tests
// ============================================================
TEST_F(ValueTest_24, AssignmentFromValue_24) {
    Value v1(10);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 10);
}

TEST_F(ValueTest_24, AssignmentFromString_24) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_24, AssignmentFromCString_24) {
    Value v;
    v = "cstring";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "cstring");
}

TEST_F(ValueTest_24, AssignmentFromInt_24) {
    Value v;
    v = 99;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_24, AssignmentFromDouble_24) {
    Value v;
    v = 1.5;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.5);
}

TEST_F(ValueTest_24, AssignmentFromBool_24) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_24, AssignmentFromObject_24) {
    Value v;
    Object obj;
    obj["x"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_24, AssignmentFromArray_24) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

// ============================================================
// Type Change via Assignment
// ============================================================
TEST_F(ValueTest_24, TypeChangeIntToString_24) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v = std::string("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST_F(ValueTest_24, TypeChangeStringToNull_24) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

// ============================================================
// Comparison Operator Tests
// ============================================================
TEST_F(ValueTest_24, EqualityOperatorSameInt_24) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_24, EqualityOperatorDifferentInt_24) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_24, InequalityOperator_24) {
    Value v1(42);
    Value v2(43);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_24, InequalityOperatorSameValue_24) {
    Value v1(42);
    Value v2(42);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueTest_24, EqualityDifferentTypes_24) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_24, EqualityNullValues_24) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_24, EqualityBooleans_24) {
    Value v1(true);
    Value v2(true);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_24, EqualityBooleansDifferent_24) {
    Value v1(true);
    Value v2(false);
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_24, EqualityStrings_24) {
    Value v1("hello");
    Value v2("hello");
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_24, EqualityStringsDifferent_24) {
    Value v1("hello");
    Value v2("world");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_24, EqualityDoubles_24) {
    Value v1(3.14);
    Value v2(3.14);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_24, LessThanOperatorInts_24) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_24, LessThanOrEqualOperator_24) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_24, GreaterThanOperatorInts_24) {
    Value v1(5);
    Value v2(3);
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v2 > v1);
}

TEST_F(ValueTest_24, GreaterThanOrEqualOperator_24) {
    Value v1(5);
    Value v2(5);
    EXPECT_TRUE(v1 >= v2);
}

// ============================================================
// Index Operator Tests
// ============================================================
TEST_F(ValueTest_24, ObjectIndexOperatorString_24) {
    Value v;
    Object obj;
    obj["key"] = Value("value");
    v = obj;
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST_F(ValueTest_24, ObjectIndexOperatorCString_24) {
    Value v;
    Object obj;
    obj["key"] = Value(123);
    v = obj;
    EXPECT_EQ(v["key"].getInteger(), 123);
}

TEST_F(ValueTest_24, ArrayIndexOperator_24) {
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
// Type Checking Tests
// ============================================================
TEST_F(ValueTest_24, IsStringTrue_24) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueTest_24, IsIntegerTrue_24) {
    Value v(5);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_24, IsDoubleTrue_24) {
    Value v(1.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_24, IsNumericForInteger_24) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_24, IsNumericForDouble_24) {
    Value v(5.0);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_24, IsNumericForString_24) {
    Value v("hello");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_24, IsObjectTrue_24) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_24, IsArrayTrue_24) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_24, IsBooleanTrue_24) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
}

TEST_F(ValueTest_24, IsNullTrue_24) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

// ============================================================
// Setter Tests
// ============================================================
TEST_F(ValueTest_24, SetString_24) {
    Value v;
    v.setString("new string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "new string");
}

TEST_F(ValueTest_24, SetInteger_24) {
    Value v;
    v.setInteger(777);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 777);
}

TEST_F(ValueTest_24, SetDouble_24) {
    Value v;
    v.setDouble(2.718);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_24, SetBoolean_24) {
    Value v;
    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_24, SetObject_24) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_24, SetArray_24) {
    Value v;
    Array arr;
    arr.push_back(Value("item"));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

TEST_F(ValueTest_24, SetNull_24) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

// ============================================================
// tryGet Tests
// ============================================================
TEST_F(ValueTest_24, TryGetStringWhenIsString_24) {
    Value v("hello");
    EXPECT_EQ(v.tryGetString("default"), "hello");
}

TEST_F(ValueTest_24, TryGetStringWhenNotString_24) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_24, TryGetIntegerWhenIsInteger_24) {
    Value v(99);
    EXPECT_EQ(v.tryGetInteger(0), 99);
}

TEST_F(ValueTest_24, TryGetIntegerWhenNotInteger_24) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

TEST_F(ValueTest_24, TryGetDoubleWhenIsDouble_24) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 3.14);
}

TEST_F(ValueTest_24, TryGetDoubleWhenNotDouble_24) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.0), 1.0);
}

TEST_F(ValueTest_24, TryGetFloatWhenIsDouble_24) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST_F(ValueTest_24, TryGetFloatWhenNotDouble_24) {
    Value v("hello");
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.0f), 1.0f);
}

TEST_F(ValueTest_24, TryGetBooleanWhenIsBoolean_24) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_24, TryGetBooleanWhenNotBoolean_24) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ============================================================
// getFloat Tests
// ============================================================
TEST_F(ValueTest_24, GetFloat_24) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 2.5f);
}

// ============================================================
// isStringable Tests
// ============================================================
TEST_F(ValueTest_24, IsStringableForString_24) {
    Value v("test");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_24, IsStringableForInteger_24) {
    Value v(42);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_24, IsStringableForDouble_24) {
    Value v(1.5);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_24, IsStringableForBoolean_24) {
    Value v(true);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_24, IsStringableForNull_24) {
    Value v;
    EXPECT_TRUE(v.isStringable());
}

// ============================================================
// getToString Tests
// ============================================================
TEST_F(ValueTest_24, GetToStringFromString_24) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

TEST_F(ValueTest_24, GetToStringFromInteger_24) {
    Value v(42);
    std::string result = v.getToString();
    EXPECT_EQ(result, "42");
}

TEST_F(ValueTest_24, GetToStringFromBoolTrue_24) {
    Value v(true);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_24, GetToStringFromNull_24) {
    Value v;
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Load From String Tests
// ============================================================
TEST_F(ValueTest_24, LoadFromStringInteger_24) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_24, LoadFromStringString_24) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_24, LoadFromStringBoolean_24) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_24, LoadFromStringFalse_24) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_24, LoadFromStringNull_24) {
    Value v(42);
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_24, LoadFromStringDouble_24) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_NEAR(v.getDouble(), 3.14, 0.001);
}

TEST_F(ValueTest_24, LoadFromStringObject_24) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST_F(ValueTest_24, LoadFromStringArray_24) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_24, LoadFromStringEmptyObject_24) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v.getObject().empty());
}

TEST_F(ValueTest_24, LoadFromStringEmptyArray_24) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v.getArray().empty());
}

// ============================================================
// Load From Stream Tests
// ============================================================
TEST_F(ValueTest_24, LoadFromStream_24) {
    Value v;
    std::istringstream ss("{\"name\": \"test\"}");
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["name"].getString(), "test");
}

TEST_F(ValueTest_24, StreamConstructor_24) {
    std::istringstream ss("123");
    Value v(ss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

// ============================================================
// Write to Stream Tests
// ============================================================
TEST_F(ValueTest_24, WriteToStreamInteger_24) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_FALSE(oss.str().empty());
    EXPECT_NE(oss.str().find("42"), std::string::npos);
}

TEST_F(ValueTest_24, WriteToStreamString_24) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("hello"), std::string::npos);
}

TEST_F(ValueTest_24, WriteToStreamNull_24) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("null"), std::string::npos);
}

TEST_F(ValueTest_24, WriteToStreamBoolean_24) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("true"), std::string::npos);
}

TEST_F(ValueTest_24, WriteToStreamObject_24) {
    Object obj;
    obj["key"] = Value("val");
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string result = oss.str();
    EXPECT_NE(result.find("key"), std::string::npos);
    EXPECT_NE(result.find("val"), std::string::npos);
}

TEST_F(ValueTest_24, WriteToStreamArray_24) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string result = oss.str();
    EXPECT_NE(result.find("["), std::string::npos);
    EXPECT_NE(result.find("]"), std::string::npos);
}

TEST_F(ValueTest_24, WriteToStreamWithIndent_24) {
    Object obj;
    obj["key"] = Value("val");
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string result = oss.str();
    // Indented output should have newlines or tabs
    EXPECT_NE(result.find("\n"), std::string::npos);
}

// ============================================================
// ostream operator<< Tests
// ============================================================
TEST_F(ValueTest_24, OstreamOperator_24) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

// ============================================================
// Escape Tests
// ============================================================
TEST_F(ValueTest_24, EscapeMinimumCharacters_24) {
    std::string result = Value::escapeMinimumCharacters("hello\nworld");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_24, EscapeMinimumCharactersQuote_24) {
    std::string result = Value::escapeMinimumCharacters("say \"hi\"");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_24, EscapeMinimumCharactersBackslash_24) {
    std::string result = Value::escapeMinimumCharacters("back\\slash");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST_F(ValueTest_24, EscapeMinimumCharactersNoEscape_24) {
    std::string result = Value::escapeMinimumCharacters("hello");
    EXPECT_EQ(result, "hello");
}

TEST_F(ValueTest_24, EscapeAllCharactersBasic_24) {
    std::string result = Value::escapeAllCharacters("hello");
    // All characters should be escaped to unicode
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_24, EscapeToUnicode_24) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
    // Should contain unicode escape format \u0041
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ============================================================
// Nested Structure Tests
// ============================================================
TEST_F(ValueTest_24, NestedObjectInArray_24) {
    Value v;
    v.loadFromString("[{\"key\": 1}, {\"key\": 2}]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_24, NestedArrayInObject_24) {
    Value v;
    v.loadFromString("{\"arr\": [1, 2, 3]}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["arr"].isArray());
    EXPECT_EQ(v["arr"].getArray().size(), 3u);
}

TEST_F(ValueTest_24, DeepNesting_24) {
    Value v;
    v.loadFromString("{\"a\": {\"b\": {\"c\": 42}}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["a"].isObject());
    EXPECT_TRUE(v["a"]["b"].isObject());
    EXPECT_EQ(v["a"]["b"]["c"].getInteger(), 42);
}

// ============================================================
// Roundtrip Tests (Load -> Write -> Load)
// ============================================================
TEST_F(ValueTest_24, RoundtripSimpleObject_24) {
    std::string json = "{\"key\":\"value\"}";
    Value v1;
    v1.loadFromString(json);
    
    std::ostringstream oss;
    v1.writeToStream(oss, false, false);
    
    Value v2;
    v2.loadFromString(oss.str());
    
    EXPECT_TRUE(v2.isObject());
    EXPECT_EQ(v2["key"].getString(), "value");
}

TEST_F(ValueTest_24, RoundtripArray_24) {
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
// Boundary / Edge Cases
// ============================================================
TEST_F(ValueTest_24, NegativeDouble_24) {
    Value v(-0.0);
    EXPECT_TRUE(v.isDouble());
}

TEST_F(ValueTest_24, LargeInteger_24) {
    Value v(2147483647); // INT_MAX
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST_F(ValueTest_24, NegativeLargeInteger_24) {
    Value v(-2147483648); // INT_MIN
    EXPECT_TRUE(v.isInteger());
}

TEST_F(ValueTest_24, LoadNegativeNumber_24) {
    Value v;
    v.loadFromString("-42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST_F(ValueTest_24, LoadNegativeDouble_24) {
    Value v;
    v.loadFromString("-3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_NEAR(v.getDouble(), -3.14, 0.001);
}

TEST_F(ValueTest_24, LoadStringWithEscapedChars_24) {
    Value v;
    v.loadFromString("\"hello\\nworld\"");
    EXPECT_TRUE(v.isString());
    EXPECT_NE(v.getString().find('\n'), std::string::npos);
}

TEST_F(ValueTest_24, LoadStringWithUnicodeEscape_24) {
    Value v;
    v.loadFromString("\"\\u0041\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "A");
}

// ============================================================
// Multiple Assignments overwriting type
// ============================================================
TEST_F(ValueTest_24, MultipleTypeChanges_24) {
    Value v;
    EXPECT_TRUE(v.isNull());
    
    v = 42;
    EXPECT_TRUE(v.isInteger());
    
    v = "hello";
    EXPECT_TRUE(v.isString());
    
    v = 3.14;
    EXPECT_TRUE(v.isDouble());
    
    v = true;
    EXPECT_TRUE(v.isBoolean());
    
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

// ============================================================
// Object index operator creates entry
// ============================================================
TEST_F(ValueTest_24, ObjectIndexCreatesEntry_24) {
    Value v;
    Object obj;
    v.setObject(obj);
    v["newkey"] = Value(42);
    EXPECT_EQ(v["newkey"].getInteger(), 42);
}

// ============================================================
// Writing with escapeAll
// ============================================================
TEST_F(ValueTest_24, WriteToStreamEscapeAll_24) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, true);
    std::string result = oss.str();
    // With escapeAll, characters should be escaped to unicode
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ============================================================
// Scientific notation in JSON
// ============================================================
TEST_F(ValueTest_24, LoadScientificNotation_24) {
    Value v;
    v.loadFromString("1.5e2");
    EXPECT_TRUE(v.isDouble() || v.isInteger());
    if (v.isDouble()) {
        EXPECT_NEAR(v.getDouble(), 150.0, 0.001);
    }
}

// ============================================================
// Complex JSON
// ============================================================
TEST_F(ValueTest_24, LoadComplexJSON_24) {
    std::string json = R"({
        "name": "test",
        "version": 1,
        "pi": 3.14,
        "active": true,
        "nothing": null,
        "tags": ["a", "b", "c"],
        "nested": {"x": 1}
    })";
    Value v;
    v.loadFromString(json);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["name"].getString(), "test");
    EXPECT_EQ(v["version"].getInteger(), 1);
    EXPECT_NEAR(v["pi"].getDouble(), 3.14, 0.001);
    EXPECT_TRUE(v["active"].getBoolean());
    EXPECT_TRUE(v["nothing"].isNull());
    EXPECT_TRUE(v["tags"].isArray());
    EXPECT_EQ(v["tags"].getArray().size(), 3u);
    EXPECT_TRUE(v["nested"].isObject());
    EXPECT_EQ(v["nested"]["x"].getInteger(), 1);
}
