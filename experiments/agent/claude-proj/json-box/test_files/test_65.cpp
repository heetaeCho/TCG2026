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
class ValueTest_65 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Default Constructor Tests
// ============================================================
TEST_F(ValueTest_65, DefaultConstructorIsNull_65) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_65, DefaultConstructorTypeIsNullValue_65) {
    Value v;
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

// ============================================================
// String Constructor Tests
// ============================================================
TEST_F(ValueTest_65, StringConstructor_65) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_65, CStringConstructor_65) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_65, EmptyStringConstructor_65) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

// ============================================================
// Integer Constructor Tests
// ============================================================
TEST_F(ValueTest_65, IntConstructor_65) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_65, IntConstructorNegative_65) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST_F(ValueTest_65, IntConstructorZero_65) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

// ============================================================
// Double Constructor Tests
// ============================================================
TEST_F(ValueTest_65, DoubleConstructor_65) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_65, DoubleConstructorNegative_65) {
    Value v(-2.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -2.5);
}

TEST_F(ValueTest_65, DoubleConstructorZero_65) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

// ============================================================
// Boolean Constructor Tests
// ============================================================
TEST_F(ValueTest_65, BoolConstructorTrue_65) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_65, BoolConstructorFalse_65) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

// ============================================================
// Object Constructor Tests
// ============================================================
TEST_F(ValueTest_65, ObjectConstructor_65) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_65, EmptyObjectConstructor_65) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v.getObject().empty());
}

// ============================================================
// Array Constructor Tests
// ============================================================
TEST_F(ValueTest_65, ArrayConstructor_65) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_65, EmptyArrayConstructor_65) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v.getArray().empty());
}

// ============================================================
// Copy Constructor Tests
// ============================================================
TEST_F(ValueTest_65, CopyConstructorString_65) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "test");
}

TEST_F(ValueTest_65, CopyConstructorInt_65) {
    Value original(99);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 99);
}

TEST_F(ValueTest_65, CopyConstructorNull_65) {
    Value original;
    Value copy(original);
    EXPECT_TRUE(copy.isNull());
}

// ============================================================
// Assignment Operator Tests
// ============================================================
TEST_F(ValueTest_65, AssignmentFromValue_65) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_65, AssignmentFromString_65) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_65, AssignmentFromCString_65) {
    Value v;
    v = "cstring";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "cstring");
}

TEST_F(ValueTest_65, AssignmentFromInt_65) {
    Value v;
    v = 77;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 77);
}

TEST_F(ValueTest_65, AssignmentFromDouble_65) {
    Value v;
    v = 1.618;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.618);
}

TEST_F(ValueTest_65, AssignmentFromBool_65) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_65, AssignmentFromObject_65) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_65, AssignmentFromArray_65) {
    Value v;
    Array arr;
    arr.push_back(Value(10));
    v = arr;
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

// ============================================================
// Type Checking Tests
// ============================================================
TEST_F(ValueTest_65, IsStringFalseForInt_65) {
    Value v(10);
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_65, IsIntegerFalseForString_65) {
    Value v("text");
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_65, IsDoubleFalseForInt_65) {
    Value v(5);
    EXPECT_FALSE(v.isDouble());
}

TEST_F(ValueTest_65, IsNumericTrueForInt_65) {
    Value v(10);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_65, IsNumericTrueForDouble_65) {
    Value v(3.14);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_65, IsNumericFalseForString_65) {
    Value v("text");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_65, IsObjectFalseForArray_65) {
    Array arr;
    Value v(arr);
    EXPECT_FALSE(v.isObject());
}

TEST_F(ValueTest_65, IsArrayFalseForObject_65) {
    Object obj;
    Value v(obj);
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueTest_65, IsBooleanFalseForNull_65) {
    Value v;
    EXPECT_FALSE(v.isBoolean());
}

TEST_F(ValueTest_65, IsNullFalseForBoolean_65) {
    Value v(true);
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_65, IsStringableForString_65) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_65, IsStringableForInt_65) {
    Value v(42);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_65, IsStringableForDouble_65) {
    Value v(3.14);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_65, IsStringableForBool_65) {
    Value v(true);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_65, IsStringableForNull_65) {
    Value v;
    EXPECT_TRUE(v.isStringable());
}

// ============================================================
// Setter Tests
// ============================================================
TEST_F(ValueTest_65, SetString_65) {
    Value v;
    v.setString("new value");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "new value");
}

TEST_F(ValueTest_65, SetInteger_65) {
    Value v;
    v.setInteger(123);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

TEST_F(ValueTest_65, SetDouble_65) {
    Value v;
    v.setDouble(2.718);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_65, SetBoolean_65) {
    Value v;
    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_65, SetObject_65) {
    Value v;
    Object obj;
    obj["x"] = Value(10);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_65, SetArray_65) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_65, SetNull_65) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_65, SetNullFromString_65) {
    Value v("hello");
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

// ============================================================
// Type Transition Tests
// ============================================================
TEST_F(ValueTest_65, TransitionIntToString_65) {
    Value v(42);
    v.setString("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST_F(ValueTest_65, TransitionStringToInt_65) {
    Value v("text");
    v.setInteger(100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

// ============================================================
// tryGet Tests (default value on type mismatch)
// ============================================================
TEST_F(ValueTest_65, TryGetStringReturnsValueWhenString_65) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST_F(ValueTest_65, TryGetStringReturnsDefaultWhenNotString_65) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_65, TryGetIntegerReturnsValueWhenInt_65) {
    Value v(10);
    EXPECT_EQ(v.tryGetInteger(99), 10);
}

TEST_F(ValueTest_65, TryGetIntegerReturnsDefaultWhenNotInt_65) {
    Value v("text");
    EXPECT_EQ(v.tryGetInteger(99), 99);
}

TEST_F(ValueTest_65, TryGetDoubleReturnsValueWhenDouble_65) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 3.14);
}

TEST_F(ValueTest_65, TryGetDoubleReturnsDefaultWhenNotDouble_65) {
    Value v("text");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.0), 1.0);
}

TEST_F(ValueTest_65, TryGetFloatReturnsValueWhenDouble_65) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST_F(ValueTest_65, TryGetFloatReturnsDefaultWhenNotDouble_65) {
    Value v("text");
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.5f), 1.5f);
}

TEST_F(ValueTest_65, TryGetBooleanReturnsValueWhenBool_65) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_65, TryGetBooleanReturnsDefaultWhenNotBool_65) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ============================================================
// getToString Tests
// ============================================================
TEST_F(ValueTest_65, GetToStringForString_65) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

TEST_F(ValueTest_65, GetToStringForNull_65) {
    Value v;
    std::string result = v.getToString();
    // Should return some string representation of null
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_65, GetToStringForBoolTrue_65) {
    Value v(true);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_65, GetToStringForInt_65) {
    Value v(42);
    std::string result = v.getToString();
    EXPECT_EQ(result, "42");
}

// ============================================================
// getFloat Tests
// ============================================================
TEST_F(ValueTest_65, GetFloat_65) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 2.5f);
}

// ============================================================
// Operator[] Tests
// ============================================================
TEST_F(ValueTest_65, ObjectSubscriptStringKey_65) {
    Object obj;
    obj["key"] = Value(42);
    Value v(obj);
    EXPECT_TRUE(v["key"].isInteger());
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST_F(ValueTest_65, ObjectSubscriptCStringKey_65) {
    Object obj;
    obj["name"] = Value("John");
    Value v(obj);
    EXPECT_EQ(v["name"].getString(), "John");
}

TEST_F(ValueTest_65, ArraySubscriptIndex_65) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

TEST_F(ValueTest_65, ObjectSubscriptCreatesEntry_65) {
    Object obj;
    Value v(obj);
    v["newkey"] = Value(100);
    EXPECT_TRUE(v["newkey"].isInteger());
    EXPECT_EQ(v["newkey"].getInteger(), 100);
}

// ============================================================
// Comparison Operator Tests
// ============================================================
TEST_F(ValueTest_65, EqualityOperatorSameInts_65) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_65, EqualityOperatorDifferentInts_65) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_65, InequalityOperator_65) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_65, InequalityOperatorSameValues_65) {
    Value v1("same");
    Value v2("same");
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueTest_65, LessThanOperatorInts_65) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_65, LessThanOrEqualOperator_65) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_65, GreaterThanOperator_65) {
    Value v1(5);
    Value v2(3);
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v2 > v1);
}

TEST_F(ValueTest_65, GreaterThanOrEqualOperator_65) {
    Value v1(5);
    Value v2(5);
    EXPECT_TRUE(v1 >= v2);
}

TEST_F(ValueTest_65, EqualityDifferentTypes_65) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_65, EqualityBothNull_65) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_65, EqualityStrings_65) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_65, EqualityDoubles_65) {
    Value v1(3.14);
    Value v2(3.14);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_65, EqualityBooleans_65) {
    Value v1(true);
    Value v2(true);
    EXPECT_TRUE(v1 == v2);
}

// ============================================================
// LoadFromString Tests
// ============================================================
TEST_F(ValueTest_65, LoadFromStringInt_65) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_65, LoadFromStringDouble_65) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_65, LoadFromStringString_65) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_65, LoadFromStringTrue_65) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_65, LoadFromStringFalse_65) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_65, LoadFromStringNull_65) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_65, LoadFromStringEmptyObject_65) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v.getObject().empty());
}

TEST_F(ValueTest_65, LoadFromStringEmptyArray_65) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v.getArray().empty());
}

TEST_F(ValueTest_65, LoadFromStringObject_65) {
    Value v;
    v.loadFromString("{\"key\": 42}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST_F(ValueTest_65, LoadFromStringArray_65) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_65, LoadFromStringNestedObject_65) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": true}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_TRUE(v["outer"]["inner"].getBoolean());
}

TEST_F(ValueTest_65, LoadFromStringNegativeInt_65) {
    Value v;
    v.loadFromString("-10");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -10);
}

// ============================================================
// LoadFromStream Tests
// ============================================================
TEST_F(ValueTest_65, LoadFromStreamInt_65) {
    std::istringstream input("100");
    Value v;
    v.loadFromStream(input);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST_F(ValueTest_65, LoadFromStreamObject_65) {
    std::istringstream input("{\"a\": 1}");
    Value v;
    v.loadFromStream(input);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_65, StreamConstructor_65) {
    std::istringstream input("\"test\"");
    Value v(input);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

// ============================================================
// WriteToStream Tests
// ============================================================
TEST_F(ValueTest_65, WriteToStreamNull_65) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "null");
}

TEST_F(ValueTest_65, WriteToStreamInt_65) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "42");
}

TEST_F(ValueTest_65, WriteToStreamDouble_65) {
    Value v(3.14);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string result = oss.str();
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST_F(ValueTest_65, WriteToStreamString_65) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "\"hello\"");
}

TEST_F(ValueTest_65, WriteToStreamBoolTrue_65) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "true");
}

TEST_F(ValueTest_65, WriteToStreamBoolFalse_65) {
    Value v(false);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "false");
}

TEST_F(ValueTest_65, WriteToStreamEmptyObject_65) {
    Value v(Object());
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "{}");
}

TEST_F(ValueTest_65, WriteToStreamEmptyArray_65) {
    Value v(Array());
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "[]");
}

TEST_F(ValueTest_65, WriteToStreamWithIndent_65) {
    Object obj;
    obj["key"] = Value(1);
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string result = oss.str();
    // With indent, the output should contain newlines
    EXPECT_NE(result.find('\n'), std::string::npos);
}

TEST_F(ValueTest_65, WriteToStreamNoIndent_65) {
    Object obj;
    obj["key"] = Value(1);
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string result = oss.str();
    // Without indent, should be compact (no newlines in simple case)
    EXPECT_NE(result.find("\"key\""), std::string::npos);
}

// ============================================================
// Escape Tests
// ============================================================
TEST_F(ValueTest_65, EscapeMinimumCharacters_65) {
    std::string input = "hello\nworld";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_65, EscapeMinimumCharactersQuote_65) {
    std::string input = "say \"hi\"";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_65, EscapeMinimumCharactersBackslash_65) {
    std::string input = "back\\slash";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST_F(ValueTest_65, EscapeMinimumCharactersNoEscapeNeeded_65) {
    std::string input = "simple";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ(result, "simple");
}

TEST_F(ValueTest_65, EscapeAllCharactersBasic_65) {
    std::string input = "A";
    std::string result = Value::escapeAllCharacters(input);
    // Should escape every character to unicode
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

TEST_F(ValueTest_65, EscapeToUnicodeNullChar_65) {
    std::string result = Value::escapeToUnicode('\0');
    EXPECT_EQ(result, "\\u0000");
}

TEST_F(ValueTest_65, EscapeToUnicodeCharA_65) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_EQ(result, "\\u0041");
}

// ============================================================
// Stream Operator Tests
// ============================================================
TEST_F(ValueTest_65, StreamOutputOperator_65) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_EQ(oss.str(), "42");
}

TEST_F(ValueTest_65, StreamOutputOperatorString_65) {
    Value v("hello");
    std::ostringstream oss;
    oss << v;
    EXPECT_EQ(oss.str(), "\"hello\"");
}

// ============================================================
// Complex JSON Tests
// ============================================================
TEST_F(ValueTest_65, ComplexNestedStructure_65) {
    Value v;
    v.loadFromString("{\"people\": [{\"name\": \"Alice\", \"age\": 30}, {\"name\": \"Bob\", \"age\": 25}]}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["people"].isArray());
    EXPECT_EQ(v["people"].getArray().size(), 2u);
}

TEST_F(ValueTest_65, RoundTripLoadAndWrite_65) {
    std::string json = "{\"a\":1,\"b\":\"hello\",\"c\":true,\"d\":null}";
    Value v;
    v.loadFromString(json);

    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();

    // Reload and verify
    Value v2;
    v2.loadFromString(output);
    EXPECT_TRUE(v2.isObject());
    EXPECT_EQ(v2["a"].getInteger(), 1);
    EXPECT_EQ(v2["b"].getString(), "hello");
    EXPECT_TRUE(v2["c"].getBoolean());
    EXPECT_TRUE(v2["d"].isNull());
}

TEST_F(ValueTest_65, WriteToStreamEscapeAll_65) {
    Value v("test");
    std::ostringstream oss;
    v.writeToStream(oss, false, true);
    std::string result = oss.str();
    // With escapeAll, string characters should be unicode escaped
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ============================================================
// Boundary / Edge Case Tests
// ============================================================
TEST_F(ValueTest_65, LargeInteger_65) {
    Value v(2147483647); // INT_MAX
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST_F(ValueTest_65, MinInteger_65) {
    Value v(-2147483647 - 1); // INT_MIN
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -2147483647 - 1);
}

TEST_F(ValueTest_65, VerySmallDouble_65) {
    Value v(1e-300);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1e-300);
}

TEST_F(ValueTest_65, VeryLargeDouble_65) {
    Value v(1e300);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1e300);
}

TEST_F(ValueTest_65, StringWithSpecialCharacters_65) {
    Value v("tab\there\nnewline\rcarriage");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "tab\there\nnewline\rcarriage");
}

TEST_F(ValueTest_65, OverwriteTypeMultipleTimes_65) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v = "now a string";
    EXPECT_TRUE(v.isString());
    v = 3.14;
    EXPECT_TRUE(v.isDouble());
    v = true;
    EXPECT_TRUE(v.isBoolean());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_65, LoadFromStringArrayOfMixedTypes_65) {
    Value v;
    v.loadFromString("[1, \"two\", 3.0, true, null]");
    EXPECT_TRUE(v.isArray());
    const Array& arr = v.getArray();
    EXPECT_EQ(arr.size(), 5u);
    EXPECT_TRUE(arr[0].isInteger());
    EXPECT_TRUE(arr[1].isString());
    EXPECT_TRUE(arr[2].isDouble());
    EXPECT_TRUE(arr[3].isBoolean());
    EXPECT_TRUE(arr[4].isNull());
}

TEST_F(ValueTest_65, LoadFromStringEscapedString_65) {
    Value v;
    v.loadFromString("\"hello\\nworld\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello\nworld");
}

TEST_F(ValueTest_65, SelfAssignment_65) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}
