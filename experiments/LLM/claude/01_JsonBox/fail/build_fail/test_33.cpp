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
class ValueTest_33 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Constructor Tests
// ============================================================

TEST_F(ValueTest_33, DefaultConstructorCreatesNull_33) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_33, StringConstructor_33) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_33, CStringConstructor_33) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_33, IntConstructor_33) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_33, DoubleConstructor_33) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_33, BoolConstructorTrue_33) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_33, BoolConstructorFalse_33) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_33, ObjectConstructor_33) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_33, ArrayConstructor_33) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_33, CopyConstructor_33) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "test");
}

TEST_F(ValueTest_33, StreamConstructorValidJson_33) {
    std::istringstream ss("\"hello\"");
    Value v(ss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

// ============================================================
// Type Checking Tests
// ============================================================

TEST_F(ValueTest_33, IsStringReturnsTrueForString_33) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_33, IsIntegerReturnsTrueForInt_33) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_33, IsDoubleReturnsTrueForDouble_33) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_33, IsNumericForInteger_33) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_33, IsNumericForDouble_33) {
    Value v(5.5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_33, IsNumericFalseForString_33) {
    Value v("not a number");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_33, IsObjectReturnsTrueForObject_33) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_33, IsArrayReturnsTrueForArray_33) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_33, IsBooleanReturnsTrueForBool_33) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
}

TEST_F(ValueTest_33, IsNullReturnsTrueForDefault_33) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_33, IsStringableForString_33) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_33, IsStringableForInteger_33) {
    Value v(42);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_33, IsStringableForDouble_33) {
    Value v(3.14);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_33, IsStringableForBoolean_33) {
    Value v(true);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_33, IsStringableForNull_33) {
    Value v;
    EXPECT_TRUE(v.isStringable());
}

// ============================================================
// getType Tests
// ============================================================

TEST_F(ValueTest_33, GetTypeString_33) {
    Value v("str");
    EXPECT_EQ(v.getType(), Value::STRING);
}

TEST_F(ValueTest_33, GetTypeInteger_33) {
    Value v(1);
    EXPECT_EQ(v.getType(), Value::INTEGER);
}

TEST_F(ValueTest_33, GetTypeDouble_33) {
    Value v(1.0);
    EXPECT_EQ(v.getType(), Value::DOUBLE);
}

TEST_F(ValueTest_33, GetTypeObject_33) {
    Value v(Object());
    EXPECT_EQ(v.getType(), Value::OBJECT);
}

TEST_F(ValueTest_33, GetTypeArray_33) {
    Value v(Array());
    EXPECT_EQ(v.getType(), Value::ARRAY);
}

TEST_F(ValueTest_33, GetTypeBoolean_33) {
    Value v(false);
    EXPECT_EQ(v.getType(), Value::BOOLEAN);
}

TEST_F(ValueTest_33, GetTypeNull_33) {
    Value v;
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

// ============================================================
// Assignment Operator Tests
// ============================================================

TEST_F(ValueTest_33, AssignValueToValue_33) {
    Value v1("hello");
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isString());
    EXPECT_EQ(v2.getString(), "hello");
}

TEST_F(ValueTest_33, AssignStringToValue_33) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_33, AssignCStringToValue_33) {
    Value v;
    v = "cstring";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "cstring");
}

TEST_F(ValueTest_33, AssignIntToValue_33) {
    Value v;
    v = 99;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_33, AssignDoubleToValue_33) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_33, AssignObjectToValue_33) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_33, AssignArrayToValue_33) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_33, AssignBoolToValue_33) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

// ============================================================
// Setter Tests
// ============================================================

TEST_F(ValueTest_33, SetString_33) {
    Value v;
    v.setString("new string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "new string");
}

TEST_F(ValueTest_33, SetInteger_33) {
    Value v;
    v.setInteger(123);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

TEST_F(ValueTest_33, SetDouble_33) {
    Value v;
    v.setDouble(9.81);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 9.81);
}

TEST_F(ValueTest_33, SetObject_33) {
    Value v;
    Object obj;
    obj["x"] = Value(10);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_33, SetArray_33) {
    Value v;
    Array arr;
    arr.push_back(Value("item"));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

TEST_F(ValueTest_33, SetBoolean_33) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_33, SetNull_33) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

// ============================================================
// Getter Tests
// ============================================================

TEST_F(ValueTest_33, GetStringFromString_33) {
    Value v("hello");
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_33, GetIntegerFromInt_33) {
    Value v(42);
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_33, GetDoubleFromDouble_33) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_33, GetFloatFromDouble_33) {
    Value v(3.14);
    EXPECT_FLOAT_EQ(v.getFloat(), 3.14f);
}

TEST_F(ValueTest_33, GetBooleanFromBool_33) {
    Value v(true);
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_33, GetObjectFromObject_33) {
    Object obj;
    obj["key"] = Value("val");
    Value v(obj);
    const Object& retrieved = v.getObject();
    EXPECT_EQ(retrieved.size(), 1u);
    EXPECT_TRUE(retrieved.find("key") != retrieved.end());
}

TEST_F(ValueTest_33, GetArrayFromArray_33) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    arr.push_back(Value(3));
    Value v(arr);
    const Array& retrieved = v.getArray();
    EXPECT_EQ(retrieved.size(), 3u);
}

// ============================================================
// tryGet Tests
// ============================================================

TEST_F(ValueTest_33, TryGetStringReturnsValueWhenString_33) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST_F(ValueTest_33, TryGetStringReturnsDefaultWhenNotString_33) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_33, TryGetIntegerReturnsValueWhenInteger_33) {
    Value v(10);
    EXPECT_EQ(v.tryGetInteger(0), 10);
}

TEST_F(ValueTest_33, TryGetIntegerReturnsDefaultWhenNotInteger_33) {
    Value v("not int");
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

TEST_F(ValueTest_33, TryGetDoubleReturnsValueWhenDouble_33) {
    Value v(2.5);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 2.5);
}

TEST_F(ValueTest_33, TryGetDoubleReturnsDefaultWhenNotDouble_33) {
    Value v("not double");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(9.9), 9.9);
}

TEST_F(ValueTest_33, TryGetFloatReturnsValueWhenDouble_33) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST_F(ValueTest_33, TryGetFloatReturnsDefaultWhenNotDouble_33) {
    Value v("not float");
    EXPECT_FLOAT_EQ(v.tryGetFloat(9.9f), 9.9f);
}

TEST_F(ValueTest_33, TryGetBooleanReturnsValueWhenBoolean_33) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_33, TryGetBooleanReturnsDefaultWhenNotBoolean_33) {
    Value v(42);
    EXPECT_TRUE(v.tryGetBoolean(true));
}

// ============================================================
// getToString Tests
// ============================================================

TEST_F(ValueTest_33, GetToStringFromString_33) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

TEST_F(ValueTest_33, GetToStringFromInteger_33) {
    Value v(42);
    EXPECT_EQ(v.getToString(), "42");
}

TEST_F(ValueTest_33, GetToStringFromNull_33) {
    Value v;
    std::string result = v.getToString();
    // Null should produce some string representation
    EXPECT_FALSE(result.empty() && !v.isNull()); // just ensuring it doesn't crash
}

// ============================================================
// Comparison Operator Tests
// ============================================================

TEST_F(ValueTest_33, EqualityOperator_33) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_33, InequalityOperator_33) {
    Value v1(42);
    Value v2(43);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_33, EqualityStringValues_33) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_33, InequalityDifferentTypes_33) {
    Value v1(42);
    Value v2("42");
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_33, LessThanOperator_33) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_33, LessThanOrEqualOperator_33) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_33, GreaterThanOperator_33) {
    Value v1(3);
    Value v2(2);
    EXPECT_TRUE(v1 > v2);
}

TEST_F(ValueTest_33, GreaterThanOrEqualOperator_33) {
    Value v1(3);
    Value v2(3);
    EXPECT_TRUE(v1 >= v2);
}

// ============================================================
// Subscript Operator Tests
// ============================================================

TEST_F(ValueTest_33, SubscriptStringKeyOnObject_33) {
    Object obj;
    obj["key"] = Value(100);
    Value v(obj);
    EXPECT_TRUE(v["key"].isInteger());
    EXPECT_EQ(v["key"].getInteger(), 100);
}

TEST_F(ValueTest_33, SubscriptCStringKeyOnObject_33) {
    Object obj;
    obj["name"] = Value("test");
    Value v(obj);
    EXPECT_TRUE(v["name"].isString());
    EXPECT_EQ(v["name"].getString(), "test");
}

TEST_F(ValueTest_33, SubscriptIndexOnArray_33) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

TEST_F(ValueTest_33, SubscriptCreatesNewKeyInObject_33) {
    Object obj;
    Value v(obj);
    v["newkey"] = Value(42);
    EXPECT_TRUE(v["newkey"].isInteger());
    EXPECT_EQ(v["newkey"].getInteger(), 42);
}

// ============================================================
// Load/Parse Tests
// ============================================================

TEST_F(ValueTest_33, LoadFromStringInteger_33) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_33, LoadFromStringString_33) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_33, LoadFromStringBoolean_33) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_33, LoadFromStringNull_33) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_33, LoadFromStringArray_33) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_33, LoadFromStringObject_33) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_33, LoadFromStringDouble_33) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_33, LoadFromStringNegativeInteger_33) {
    Value v;
    v.loadFromString("-10");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -10);
}

TEST_F(ValueTest_33, LoadFromStream_33) {
    std::istringstream ss("{\"a\": 1}");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_33, LoadFromStringEmptyObject_33) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_33, LoadFromStringEmptyArray_33) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

// ============================================================
// Write Tests
// ============================================================

TEST_F(ValueTest_33, WriteToStreamString_33) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(ValueTest_33, WriteToStreamInteger_33) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(ValueTest_33, WriteToStreamNull_33) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("null"), std::string::npos);
}

TEST_F(ValueTest_33, WriteToStreamBoolean_33) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(ValueTest_33, WriteToStreamObject_33) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("key"), std::string::npos);
    EXPECT_NE(output.find("value"), std::string::npos);
}

TEST_F(ValueTest_33, WriteToStreamArray_33) {
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

TEST_F(ValueTest_33, WriteToStreamWithIndent_33) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    // Indented output should have some whitespace/newlines
    EXPECT_NE(output.find("\n"), std::string::npos);
}

// ============================================================
// Stream Operator Test
// ============================================================

TEST_F(ValueTest_33, StreamOutputOperator_33) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

// ============================================================
// Escape Function Tests
// ============================================================

TEST_F(ValueTest_33, EscapeMinimumCharacters_33) {
    std::string result = Value::escapeMinimumCharacters("hello\nworld");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_33, EscapeMinimumCharactersQuote_33) {
    std::string result = Value::escapeMinimumCharacters("say \"hi\"");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_33, EscapeMinimumCharactersBackslash_33) {
    std::string result = Value::escapeMinimumCharacters("path\\to");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST_F(ValueTest_33, EscapeAllCharacters_33) {
    std::string result = Value::escapeAllCharacters("A");
    // escapeAllCharacters should escape even normal characters to unicode
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_33, EscapeToUnicode_33) {
    std::string result = Value::escapeToUnicode('A');
    // Should produce a unicode escape like \u0041
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

TEST_F(ValueTest_33, EscapeMinimumCharactersTab_33) {
    std::string result = Value::escapeMinimumCharacters("hello\tworld");
    EXPECT_NE(result.find("\\t"), std::string::npos);
}

// ============================================================
// Boundary / Edge Cases
// ============================================================

TEST_F(ValueTest_33, EmptyStringValue_33) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_33, ZeroIntValue_33) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_33, NegativeIntValue_33) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST_F(ValueTest_33, ZeroDoubleValue_33) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_33, NegativeDoubleValue_33) {
    Value v(-3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -3.14);
}

TEST_F(ValueTest_33, LargeIntValue_33) {
    Value v(2147483647); // INT_MAX
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST_F(ValueTest_33, EmptyObjectValue_33) {
    Value v(Object());
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_33, EmptyArrayValue_33) {
    Value v(Array());
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

// ============================================================
// Type Change Tests
// ============================================================

TEST_F(ValueTest_33, ChangeTypeFromIntToString_33) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setString("now string");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_EQ(v.getString(), "now string");
}

TEST_F(ValueTest_33, ChangeTypeFromStringToNull_33) {
    Value v("something");
    EXPECT_TRUE(v.isString());
    v.setNull();
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_33, ChangeTypeFromBoolToDouble_33) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    v.setDouble(1.23);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
}

TEST_F(ValueTest_33, ChangeTypeFromNullToArray_33) {
    Value v;
    EXPECT_TRUE(v.isNull());
    Array arr;
    arr.push_back(Value(1));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
}

// ============================================================
// Nested Structure Tests
// ============================================================

TEST_F(ValueTest_33, NestedObjectInArray_33) {
    Object inner;
    inner["key"] = Value("value");
    Array arr;
    arr.push_back(Value(inner));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v.getArray()[0].isObject());
}

TEST_F(ValueTest_33, NestedArrayInObject_33) {
    Array inner;
    inner.push_back(Value(1));
    inner.push_back(Value(2));
    Object obj;
    obj["arr"] = Value(inner);
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v.getObject().at("arr").isArray());
}

TEST_F(ValueTest_33, LoadComplexJsonFromString_33) {
    Value v;
    v.loadFromString("{\"name\": \"test\", \"values\": [1, 2, 3], \"nested\": {\"flag\": true}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["name"].isString());
    EXPECT_EQ(v["name"].getString(), "test");
    EXPECT_TRUE(v["values"].isArray());
    EXPECT_EQ(v["values"].getArray().size(), 3u);
    EXPECT_TRUE(v["nested"].isObject());
    EXPECT_TRUE(v["nested"]["flag"].isBoolean());
    EXPECT_TRUE(v["nested"]["flag"].getBoolean());
}

// ============================================================
// Roundtrip Test
// ============================================================

TEST_F(ValueTest_33, RoundtripSerializeDeserialize_33) {
    Object obj;
    obj["string"] = Value("hello");
    obj["int"] = Value(42);
    obj["double"] = Value(3.14);
    obj["bool"] = Value(true);
    obj["null"] = Value();
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    obj["array"] = Value(arr);
    
    Value original(obj);
    
    std::ostringstream oss;
    original.writeToStream(oss, false, false);
    std::string json = oss.str();
    
    Value parsed;
    parsed.loadFromString(json);
    
    EXPECT_TRUE(parsed.isObject());
    EXPECT_TRUE(parsed["string"].isString());
    EXPECT_EQ(parsed["string"].getString(), "hello");
    EXPECT_TRUE(parsed["int"].isInteger());
    EXPECT_EQ(parsed["int"].getInteger(), 42);
    EXPECT_TRUE(parsed["bool"].isBoolean());
    EXPECT_TRUE(parsed["bool"].getBoolean());
    EXPECT_TRUE(parsed["null"].isNull());
    EXPECT_TRUE(parsed["array"].isArray());
    EXPECT_EQ(parsed["array"].getArray().size(), 2u);
}

// ============================================================
// Self Assignment Test
// ============================================================

TEST_F(ValueTest_33, SelfAssignment_33) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

// ============================================================
// Boolean false special case
// ============================================================

TEST_F(ValueTest_33, LoadFromStringFalse_33) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

// ============================================================
// Whitespace in JSON
// ============================================================

TEST_F(ValueTest_33, LoadFromStringWithWhitespace_33) {
    Value v;
    v.loadFromString("  {  \"key\"  :  \"value\"  }  ");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getString(), "value");
}

// ============================================================
// Equality between different types
// ============================================================

TEST_F(ValueTest_33, EqualityNullValues_33) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_33, EqualityBooleanValues_33) {
    Value v1(true);
    Value v2(true);
    EXPECT_TRUE(v1 == v2);
    Value v3(false);
    EXPECT_TRUE(v1 != v3);
}

TEST_F(ValueTest_33, EqualityDoubleValues_33) {
    Value v1(1.5);
    Value v2(1.5);
    EXPECT_TRUE(v1 == v2);
}
