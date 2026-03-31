#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "JsonBox/Value.h"

using namespace JsonBox;

// ============================================================
// Test fixture
// ============================================================
class ValueTest_60 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Constructor tests
// ============================================================

TEST_F(ValueTest_60, DefaultConstructorCreatesNull_60) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_60, StringConstructor_60) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_60, CStringConstructor_60) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_60, IntConstructor_60) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_60, DoubleConstructor_60) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_60, BooleanConstructorTrue_60) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_60, BooleanConstructorFalse_60) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_60, ObjectConstructor_60) {
    Object obj;
    obj["key"] = Value(123);
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_60, ArrayConstructor_60) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_60, CopyConstructor_60) {
    Value original(std::string("copy me"));
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "copy me");
}

// ============================================================
// setBoolean tests (the function in focus)
// ============================================================

TEST_F(ValueTest_60, SetBooleanOnBooleanValue_60) {
    Value v(true);
    EXPECT_TRUE(v.getBoolean());
    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_60, SetBooleanOnBooleanValueTrueToTrue_60) {
    Value v(true);
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_60, SetBooleanOnBooleanValueFalseToFalse_60) {
    Value v(false);
    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_60, SetBooleanOnNullValue_60) {
    Value v;
    EXPECT_TRUE(v.isNull());
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_60, SetBooleanOnStringValue_60) {
    Value v(std::string("test"));
    EXPECT_TRUE(v.isString());
    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_60, SetBooleanOnIntegerValue_60) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_60, SetBooleanOnDoubleValue_60) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_60, SetBooleanOnObjectValue_60) {
    Object obj;
    obj["x"] = Value(1);
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_60, SetBooleanOnArrayValue_60) {
    Array arr;
    arr.push_back(Value(1));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_60, SetBooleanMultipleTimes_60) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.getBoolean());
    v.setBoolean(false);
    EXPECT_FALSE(v.getBoolean());
    v.setBoolean(true);
    EXPECT_TRUE(v.getBoolean());
}

// ============================================================
// Type checking tests
// ============================================================

TEST_F(ValueTest_60, IsStringOnString_60) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueTest_60, IsIntegerOnInteger_60) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_60, IsDoubleOnDouble_60) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_60, IsNumericOnInteger_60) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_60, IsNumericOnDouble_60) {
    Value v(5.5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_60, IsNumericOnString_60) {
    Value v(std::string("5"));
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_60, GetTypeString_60) {
    Value v(std::string("s"));
    EXPECT_EQ(v.getType(), Value::STRING);
}

TEST_F(ValueTest_60, GetTypeInteger_60) {
    Value v(1);
    EXPECT_EQ(v.getType(), Value::INTEGER);
}

TEST_F(ValueTest_60, GetTypeDouble_60) {
    Value v(1.0);
    EXPECT_EQ(v.getType(), Value::DOUBLE);
}

TEST_F(ValueTest_60, GetTypeBoolean_60) {
    Value v(true);
    EXPECT_EQ(v.getType(), Value::BOOLEAN);
}

TEST_F(ValueTest_60, GetTypeNull_60) {
    Value v;
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_60, GetTypeObject_60) {
    Object obj;
    Value v(obj);
    EXPECT_EQ(v.getType(), Value::OBJECT);
}

TEST_F(ValueTest_60, GetTypeArray_60) {
    Array arr;
    Value v(arr);
    EXPECT_EQ(v.getType(), Value::ARRAY);
}

// ============================================================
// Setter tests
// ============================================================

TEST_F(ValueTest_60, SetString_60) {
    Value v;
    v.setString("new string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "new string");
}

TEST_F(ValueTest_60, SetStringOnExistingString_60) {
    Value v(std::string("old"));
    v.setString("new");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "new");
}

TEST_F(ValueTest_60, SetInteger_60) {
    Value v;
    v.setInteger(99);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_60, SetIntegerOnExistingInteger_60) {
    Value v(10);
    v.setInteger(20);
    EXPECT_EQ(v.getInteger(), 20);
}

TEST_F(ValueTest_60, SetDouble_60) {
    Value v;
    v.setDouble(2.718);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_60, SetObject_60) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_60, SetArray_60) {
    Value v;
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_60, SetNull_60) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_60, SetNullOnNull_60) {
    Value v;
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

// ============================================================
// Assignment operator tests
// ============================================================

TEST_F(ValueTest_60, AssignmentFromValue_60) {
    Value v1(std::string("hello"));
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isString());
    EXPECT_EQ(v2.getString(), "hello");
}

TEST_F(ValueTest_60, AssignmentFromString_60) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_60, AssignmentFromCString_60) {
    Value v;
    v = "c-string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "c-string");
}

TEST_F(ValueTest_60, AssignmentFromInt_60) {
    Value v;
    v = 100;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST_F(ValueTest_60, AssignmentFromDouble_60) {
    Value v;
    v = 1.23;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.23);
}

TEST_F(ValueTest_60, AssignmentFromBool_60) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_60, AssignmentFromObject_60) {
    Value v;
    Object obj;
    obj["key"] = Value("val");
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_60, AssignmentFromArray_60) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

// ============================================================
// Comparison operator tests
// ============================================================

TEST_F(ValueTest_60, EqualityOperatorSameIntegers_60) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueTest_60, EqualityOperatorDifferentIntegers_60) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_60, EqualityOperatorSameStrings_60) {
    Value v1(std::string("abc"));
    Value v2(std::string("abc"));
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_60, EqualityOperatorDifferentTypes_60) {
    Value v1(42);
    Value v2(std::string("42"));
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_60, LessThanOperatorIntegers_60) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_60, LessThanOrEqualOperator_60) {
    Value v1(5);
    Value v2(5);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_60, GreaterThanOperator_60) {
    Value v1(10);
    Value v2(5);
    EXPECT_TRUE(v1 > v2);
}

TEST_F(ValueTest_60, GreaterThanOrEqualOperator_60) {
    Value v1(10);
    Value v2(10);
    EXPECT_TRUE(v1 >= v2);
}

TEST_F(ValueTest_60, EqualityBooleans_60) {
    Value v1(true);
    Value v2(true);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_60, InequalityBooleans_60) {
    Value v1(true);
    Value v2(false);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_60, EqualityNulls_60) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

// ============================================================
// Subscript operator tests
// ============================================================

TEST_F(ValueTest_60, ObjectSubscriptOperator_60) {
    Object obj;
    obj["key"] = Value(42);
    Value v(obj);
    EXPECT_TRUE(v["key"].isInteger());
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST_F(ValueTest_60, ObjectSubscriptCStringOperator_60) {
    Object obj;
    obj["test"] = Value(std::string("value"));
    Value v(obj);
    EXPECT_EQ(v["test"].getString(), "value");
}

TEST_F(ValueTest_60, ArraySubscriptOperator_60) {
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
// tryGet* tests
// ============================================================

TEST_F(ValueTest_60, TryGetStringWhenIsString_60) {
    Value v(std::string("actual"));
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST_F(ValueTest_60, TryGetStringWhenNotString_60) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_60, TryGetIntegerWhenIsInteger_60) {
    Value v(99);
    EXPECT_EQ(v.tryGetInteger(0), 99);
}

TEST_F(ValueTest_60, TryGetIntegerWhenNotInteger_60) {
    Value v(std::string("hi"));
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

TEST_F(ValueTest_60, TryGetDoubleWhenIsDouble_60) {
    Value v(1.5);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 1.5);
}

TEST_F(ValueTest_60, TryGetDoubleWhenNotDouble_60) {
    Value v(std::string("x"));
    EXPECT_DOUBLE_EQ(v.tryGetDouble(9.9), 9.9);
}

TEST_F(ValueTest_60, TryGetFloatWhenIsDouble_60) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST_F(ValueTest_60, TryGetFloatWhenNotDouble_60) {
    Value v;
    EXPECT_FLOAT_EQ(v.tryGetFloat(7.7f), 7.7f);
}

TEST_F(ValueTest_60, TryGetBooleanWhenIsBoolean_60) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_60, TryGetBooleanWhenNotBoolean_60) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ============================================================
// getFloat tests
// ============================================================

TEST_F(ValueTest_60, GetFloat_60) {
    Value v(3.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 3.5f);
}

// ============================================================
// isStringable tests
// ============================================================

TEST_F(ValueTest_60, IsStringableForString_60) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_60, IsStringableForInteger_60) {
    Value v(42);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_60, IsStringableForDouble_60) {
    Value v(1.5);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_60, IsStringableForBoolean_60) {
    Value v(true);
    // Boolean might or might not be stringable depending on implementation
    // We just call it to ensure no crash
    v.isStringable();
}

// ============================================================
// Load from string / stream tests
// ============================================================

TEST_F(ValueTest_60, LoadFromStringInteger_60) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_60, LoadFromStringString_60) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_60, LoadFromStringBoolean_60) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_60, LoadFromStringNull_60) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_60, LoadFromStringObject_60) {
    Value v;
    v.loadFromString("{\"key\": 123}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getInteger(), 123);
}

TEST_F(ValueTest_60, LoadFromStringArray_60) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_60, LoadFromStream_60) {
    std::istringstream iss("\"stream test\"");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "stream test");
}

TEST_F(ValueTest_60, ConstructFromStream_60) {
    std::istringstream iss("42");
    Value v(iss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

// ============================================================
// Write to stream tests
// ============================================================

TEST_F(ValueTest_60, WriteToStreamString_60) {
    Value v(std::string("hello"));
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string result = oss.str();
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(ValueTest_60, WriteToStreamInteger_60) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string result = oss.str();
    EXPECT_NE(result.find("42"), std::string::npos);
}

TEST_F(ValueTest_60, WriteToStreamBoolean_60) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string result = oss.str();
    EXPECT_NE(result.find("true"), std::string::npos);
}

TEST_F(ValueTest_60, WriteToStreamNull_60) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string result = oss.str();
    EXPECT_NE(result.find("null"), std::string::npos);
}

TEST_F(ValueTest_60, WriteToStreamWithIndent_60) {
    Value v;
    v.loadFromString("{\"a\": 1}");
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_60, OutputOperator_60) {
    Value v(std::string("test"));
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

// ============================================================
// Escape functions tests
// ============================================================

TEST_F(ValueTest_60, EscapeMinimumCharacters_60) {
    std::string input = "hello\nworld";
    std::string escaped = Value::escapeMinimumCharacters(input);
    EXPECT_NE(escaped.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_60, EscapeMinimumCharactersQuote_60) {
    std::string input = "say \"hi\"";
    std::string escaped = Value::escapeMinimumCharacters(input);
    EXPECT_NE(escaped.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_60, EscapeAllCharacters_60) {
    std::string input = "abc";
    std::string escaped = Value::escapeAllCharacters(input);
    // Should contain unicode escapes for each character
    EXPECT_FALSE(escaped.empty());
}

TEST_F(ValueTest_60, EscapeToUnicode_60) {
    std::string escaped = Value::escapeToUnicode('A');
    EXPECT_FALSE(escaped.empty());
    // Should contain \u prefix
    EXPECT_NE(escaped.find("\\u"), std::string::npos);
}

// ============================================================
// Boundary / Edge case tests
// ============================================================

TEST_F(ValueTest_60, EmptyStringValue_60) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_60, ZeroIntegerValue_60) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_60, NegativeIntegerValue_60) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST_F(ValueTest_60, ZeroDoubleValue_60) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_60, NegativeDoubleValue_60) {
    Value v(-99.99);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -99.99);
}

TEST_F(ValueTest_60, EmptyObjectValue_60) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_60, EmptyArrayValue_60) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_60, GetToStringForInteger_60) {
    Value v(42);
    std::string s = v.getToString();
    EXPECT_EQ(s, "42");
}

TEST_F(ValueTest_60, GetToStringForString_60) {
    Value v(std::string("hello"));
    std::string s = v.getToString();
    EXPECT_EQ(s, "hello");
}

TEST_F(ValueTest_60, LoadFromStringDouble_60) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_NEAR(v.getDouble(), 3.14, 0.001);
}

TEST_F(ValueTest_60, LoadFromStringFalse_60) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_60, SetBooleanThenSetNull_60) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_60, SetBooleanThenSetString_60) {
    Value v;
    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    v.setString("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST_F(ValueTest_60, SetBooleanThenSetInteger_60) {
    Value v;
    v.setBoolean(true);
    v.setInteger(55);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 55);
}

TEST_F(ValueTest_60, NestedObjectParsing_60) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": 42}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

TEST_F(ValueTest_60, NestedArrayParsing_60) {
    Value v;
    v.loadFromString("[[1, 2], [3, 4]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_60, LoadFromStringNegativeNumber_60) {
    Value v;
    v.loadFromString("-42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST_F(ValueTest_60, SelfAssignment_60) {
    Value v(std::string("self"));
    v = v;
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "self");
}

TEST_F(ValueTest_60, TypeTransitionChain_60) {
    Value v;
    EXPECT_TRUE(v.isNull());

    v.setString("str");
    EXPECT_TRUE(v.isString());

    v.setInteger(10);
    EXPECT_TRUE(v.isInteger());

    v.setDouble(1.5);
    EXPECT_TRUE(v.isDouble());

    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());

    Object obj;
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());

    Array arr;
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());

    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_60, WriteAndReloadRoundTrip_60) {
    Value original;
    original.loadFromString("{\"name\": \"test\", \"value\": 42, \"flag\": true}");

    std::ostringstream oss;
    original.writeToStream(oss, false, false);

    Value reloaded;
    reloaded.loadFromString(oss.str());

    EXPECT_TRUE(reloaded.isObject());
    EXPECT_EQ(reloaded["name"].getString(), "test");
    EXPECT_EQ(reloaded["value"].getInteger(), 42);
    EXPECT_TRUE(reloaded["flag"].getBoolean());
}
