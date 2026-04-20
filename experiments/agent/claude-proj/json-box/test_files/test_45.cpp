#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

// ============================================================
// Construction Tests
// ============================================================

TEST(ValueConstructorTest_45, DefaultConstructor_45) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST(ValueConstructorTest_45, StringConstructor_45) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueConstructorTest_45, CStringConstructor_45) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST(ValueConstructorTest_45, IntConstructor_45) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueConstructorTest_45, DoubleConstructor_45) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST(ValueConstructorTest_45, BooleanConstructorTrue_45) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueConstructorTest_45, BooleanConstructorFalse_45) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueConstructorTest_45, ObjectConstructor_45) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST(ValueConstructorTest_45, ArrayConstructor_45) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST(ValueConstructorTest_45, CopyConstructor_45) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "test");
}

TEST(ValueConstructorTest_45, CopyConstructorInt_45) {
    Value original(99);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 99);
}

TEST(ValueConstructorTest_45, CopyConstructorNull_45) {
    Value original;
    Value copy(original);
    EXPECT_TRUE(copy.isNull());
}

TEST(ValueConstructorTest_45, StreamConstructor_45) {
    std::istringstream iss("\"hello\"");
    Value v(iss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

// ============================================================
// Type Checking Tests
// ============================================================

TEST(ValueTypeCheckTest_45, IsStringForString_45) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST(ValueTypeCheckTest_45, IsIntegerForInt_45) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isNull());
}

TEST(ValueTypeCheckTest_45, IsDoubleForDouble_45) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
}

TEST(ValueTypeCheckTest_45, IsNumericForInt_45) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST(ValueTypeCheckTest_45, IsNumericForDouble_45) {
    Value v(5.5);
    EXPECT_TRUE(v.isNumeric());
}

TEST(ValueTypeCheckTest_45, IsNumericFalseForString_45) {
    Value v("not a number");
    EXPECT_FALSE(v.isNumeric());
}

TEST(ValueTypeCheckTest_45, IsStringableForString_45) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST(ValueTypeCheckTest_45, GetTypeReturnsCorrectType_45) {
    Value vStr("str");
    EXPECT_EQ(vStr.getType(), Value::STRING);
    
    Value vInt(1);
    EXPECT_EQ(vInt.getType(), Value::INTEGER);
    
    Value vDbl(1.0);
    EXPECT_EQ(vDbl.getType(), Value::DOUBLE);
    
    Value vBool(true);
    EXPECT_EQ(vBool.getType(), Value::BOOLEAN);
    
    Value vNull;
    EXPECT_EQ(vNull.getType(), Value::NULL_VALUE);
}

// ============================================================
// setString Tests (the function under primary focus)
// ============================================================

TEST(ValueSetStringTest_45, SetStringOnNullValue_45) {
    Value v;
    EXPECT_TRUE(v.isNull());
    v.setString("new string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "new string");
}

TEST(ValueSetStringTest_45, SetStringOnExistingString_45) {
    Value v("old");
    EXPECT_EQ(v.getString(), "old");
    v.setString("new");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "new");
}

TEST(ValueSetStringTest_45, SetStringOnIntValue_45) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setString("converted");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "converted");
}

TEST(ValueSetStringTest_45, SetStringOnDoubleValue_45) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    v.setString("pi");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "pi");
}

TEST(ValueSetStringTest_45, SetStringOnBoolValue_45) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    v.setString("true_string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "true_string");
}

TEST(ValueSetStringTest_45, SetStringOnObjectValue_45) {
    Object obj;
    obj["key"] = Value("val");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    v.setString("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST(ValueSetStringTest_45, SetStringOnArrayValue_45) {
    Array arr;
    arr.push_back(Value(1));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    v.setString("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST(ValueSetStringTest_45, SetEmptyString_45) {
    Value v;
    v.setString("");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST(ValueSetStringTest_45, SetStringMultipleTimes_45) {
    Value v;
    v.setString("first");
    EXPECT_EQ(v.getString(), "first");
    v.setString("second");
    EXPECT_EQ(v.getString(), "second");
    v.setString("third");
    EXPECT_EQ(v.getString(), "third");
}

TEST(ValueSetStringTest_45, SetStringWithSpecialCharacters_45) {
    Value v;
    v.setString("hello\nworld\ttab\"quote\\backslash");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello\nworld\ttab\"quote\\backslash");
}

TEST(ValueSetStringTest_45, SetStringWithUnicode_45) {
    Value v;
    std::string unicodeStr = u8"日本語テスト";
    v.setString(unicodeStr);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), unicodeStr);
}

TEST(ValueSetStringTest_45, SetVeryLongString_45) {
    Value v;
    std::string longStr(10000, 'x');
    v.setString(longStr);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), longStr);
    EXPECT_EQ(v.getString().size(), 10000u);
}

// ============================================================
// Assignment Operator Tests
// ============================================================

TEST(ValueAssignmentTest_45, AssignString_45) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST(ValueAssignmentTest_45, AssignCString_45) {
    Value v;
    v = "c_string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "c_string");
}

TEST(ValueAssignmentTest_45, AssignInt_45) {
    Value v;
    v = 100;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST(ValueAssignmentTest_45, AssignDouble_45) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST(ValueAssignmentTest_45, AssignBool_45) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueAssignmentTest_45, AssignObject_45) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST(ValueAssignmentTest_45, AssignArray_45) {
    Value v;
    Array arr;
    arr.push_back(Value("item"));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

TEST(ValueAssignmentTest_45, AssignValue_45) {
    Value v1("source");
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isString());
    EXPECT_EQ(v2.getString(), "source");
}

TEST(ValueAssignmentTest_45, SelfAssignment_45) {
    Value v("self");
    v = v;
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "self");
}

// ============================================================
// Setter Tests
// ============================================================

TEST(ValueSetterTest_45, SetInteger_45) {
    Value v;
    v.setInteger(123);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

TEST(ValueSetterTest_45, SetDouble_45) {
    Value v;
    v.setDouble(9.99);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 9.99);
}

TEST(ValueSetterTest_45, SetBoolean_45) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueSetterTest_45, SetNull_45) {
    Value v("non-null");
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST(ValueSetterTest_45, SetObject_45) {
    Value v;
    Object obj;
    obj["key"] = Value("val");
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST(ValueSetterTest_45, SetArray_45) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST(ValueSetterTest_45, SetIntegerThenString_45) {
    Value v;
    v.setInteger(10);
    EXPECT_TRUE(v.isInteger());
    v.setString("now string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now string");
}

TEST(ValueSetterTest_45, SetNullThenSetString_45) {
    Value v("hello");
    v.setNull();
    EXPECT_TRUE(v.isNull());
    v.setString("back");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "back");
}

// ============================================================
// Getter Tests
// ============================================================

TEST(ValueGetterTest_45, GetInteger_45) {
    Value v(42);
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueGetterTest_45, GetDouble_45) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST(ValueGetterTest_45, GetFloat_45) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 2.5f);
}

TEST(ValueGetterTest_45, GetBoolean_45) {
    Value v(true);
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueGetterTest_45, GetString_45) {
    Value v("test");
    EXPECT_EQ(v.getString(), "test");
}

// ============================================================
// Try Getter Tests (with default values)
// ============================================================

TEST(ValueTryGetterTest_45, TryGetStringWhenString_45) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST(ValueTryGetterTest_45, TryGetStringWhenNotString_45) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST(ValueTryGetterTest_45, TryGetStringWhenNull_45) {
    Value v;
    EXPECT_EQ(v.tryGetString("fallback"), "fallback");
}

TEST(ValueTryGetterTest_45, TryGetIntegerWhenInteger_45) {
    Value v(10);
    EXPECT_EQ(v.tryGetInteger(99), 10);
}

TEST(ValueTryGetterTest_45, TryGetIntegerWhenNotInteger_45) {
    Value v("string");
    EXPECT_EQ(v.tryGetInteger(99), 99);
}

TEST(ValueTryGetterTest_45, TryGetDoubleWhenDouble_45) {
    Value v(1.5);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 1.5);
}

TEST(ValueTryGetterTest_45, TryGetDoubleWhenNotDouble_45) {
    Value v("string");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(9.9), 9.9);
}

TEST(ValueTryGetterTest_45, TryGetFloatWhenDouble_45) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST(ValueTryGetterTest_45, TryGetFloatWhenNotDouble_45) {
    Value v("string");
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.1f), 1.1f);
}

TEST(ValueTryGetterTest_45, TryGetBooleanWhenBoolean_45) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST(ValueTryGetterTest_45, TryGetBooleanWhenNotBoolean_45) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ============================================================
// Comparison Operator Tests
// ============================================================

TEST(ValueComparisonTest_45, EqualityStrings_45) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST(ValueComparisonTest_45, InequalityStrings_45) {
    Value v1("abc");
    Value v2("xyz");
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST(ValueComparisonTest_45, EqualityIntegers_45) {
    Value v1(10);
    Value v2(10);
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueComparisonTest_45, InequalityIntegers_45) {
    Value v1(10);
    Value v2(20);
    EXPECT_TRUE(v1 != v2);
}

TEST(ValueComparisonTest_45, LessThanIntegers_45) {
    Value v1(5);
    Value v2(10);
    EXPECT_TRUE(v1 < v2);
    EXPECT_TRUE(v1 <= v2);
    EXPECT_FALSE(v1 > v2);
    EXPECT_FALSE(v1 >= v2);
}

TEST(ValueComparisonTest_45, GreaterThanIntegers_45) {
    Value v1(20);
    Value v2(10);
    EXPECT_TRUE(v1 > v2);
    EXPECT_TRUE(v1 >= v2);
    EXPECT_FALSE(v1 < v2);
    EXPECT_FALSE(v1 <= v2);
}

TEST(ValueComparisonTest_45, EqualValuesLessEqual_45) {
    Value v1(5);
    Value v2(5);
    EXPECT_TRUE(v1 <= v2);
    EXPECT_TRUE(v1 >= v2);
}

TEST(ValueComparisonTest_45, DifferentTypeComparison_45) {
    Value vStr("hello");
    Value vInt(42);
    // Different types should not be equal
    EXPECT_TRUE(vStr != vInt);
}

TEST(ValueComparisonTest_45, NullEquality_45) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueComparisonTest_45, BooleanEquality_45) {
    Value v1(true);
    Value v2(true);
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueComparisonTest_45, BooleanInequality_45) {
    Value v1(true);
    Value v2(false);
    EXPECT_TRUE(v1 != v2);
}

// ============================================================
// Subscript Operator Tests
// ============================================================

TEST(ValueSubscriptTest_45, ObjectSubscriptWithString_45) {
    Object obj;
    obj["name"] = Value("John");
    Value v(obj);
    EXPECT_EQ(v["name"].getString(), "John");
}

TEST(ValueSubscriptTest_45, ObjectSubscriptWithCString_45) {
    Object obj;
    obj["key"] = Value(42);
    Value v(obj);
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST(ValueSubscriptTest_45, ArraySubscriptWithIndex_45) {
    Array arr;
    arr.push_back(Value("first"));
    arr.push_back(Value("second"));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getString(), "first");
    EXPECT_EQ(v[(size_t)1].getString(), "second");
}

TEST(ValueSubscriptTest_45, ObjectSubscriptCreatesEntry_45) {
    Object obj;
    Value v(obj);
    v["new_key"] = Value("new_value");
    EXPECT_EQ(v["new_key"].getString(), "new_value");
}

// ============================================================
// Load and Write Tests
// ============================================================

TEST(ValueLoadTest_45, LoadFromString_45) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST(ValueLoadTest_45, LoadFromStringInteger_45) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueLoadTest_45, LoadFromStringDouble_45) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST(ValueLoadTest_45, LoadFromStringBoolean_45) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueLoadTest_45, LoadFromStringNull_45) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST(ValueLoadTest_45, LoadFromStringArray_45) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST(ValueLoadTest_45, LoadFromStream_45) {
    Value v;
    std::istringstream iss("{\"a\": 1}");
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isObject());
}

TEST(ValueWriteTest_45, WriteToStream_45) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    // The output should contain "hello"
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST(ValueWriteTest_45, WriteObjectToStream_45) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("key"), std::string::npos);
    EXPECT_NE(output.find("value"), std::string::npos);
}

TEST(ValueWriteTest_45, WriteToStreamWithIndent_45) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("key"), std::string::npos);
}

// ============================================================
// getToString Tests
// ============================================================

TEST(ValueToStringTest_45, IntegerToString_45) {
    Value v(42);
    std::string s = v.getToString();
    EXPECT_EQ(s, "42");
}

TEST(ValueToStringTest_45, StringToString_45) {
    Value v("hello");
    std::string s = v.getToString();
    EXPECT_EQ(s, "hello");
}

TEST(ValueToStringTest_45, BoolToString_45) {
    Value v(true);
    std::string s = v.getToString();
    EXPECT_FALSE(s.empty());
}

// ============================================================
// Escape Function Tests
// ============================================================

TEST(ValueEscapeTest_45, EscapeMinimumCharacters_45) {
    std::string result = Value::escapeMinimumCharacters("hello\nworld");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST(ValueEscapeTest_45, EscapeMinimumCharactersQuote_45) {
    std::string result = Value::escapeMinimumCharacters("say \"hi\"");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST(ValueEscapeTest_45, EscapeMinimumCharactersBackslash_45) {
    std::string result = Value::escapeMinimumCharacters("back\\slash");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST(ValueEscapeTest_45, EscapeMinimumNoChange_45) {
    std::string result = Value::escapeMinimumCharacters("plain text");
    EXPECT_EQ(result, "plain text");
}

TEST(ValueEscapeTest_45, EscapeAllCharacters_45) {
    std::string result = Value::escapeAllCharacters("hello\nworld");
    EXPECT_FALSE(result.empty());
}

TEST(ValueEscapeTest_45, EscapeToUnicode_45) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
    // Should contain \u prefix
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ============================================================
// Boundary / Edge Case Tests
// ============================================================

TEST(ValueBoundaryTest_45, IntegerZero_45) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST(ValueBoundaryTest_45, NegativeInteger_45) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST(ValueBoundaryTest_45, DoubleZero_45) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST(ValueBoundaryTest_45, NegativeDouble_45) {
    Value v(-1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -1.5);
}

TEST(ValueBoundaryTest_45, EmptyObject_45) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST(ValueBoundaryTest_45, EmptyArray_45) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST(ValueBoundaryTest_45, EmptyStringConstructor_45) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST(ValueBoundaryTest_45, NestedObject_45) {
    Object inner;
    inner["inner_key"] = Value("inner_val");
    Object outer;
    outer["nested"] = Value(inner);
    Value v(outer);
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["nested"].isObject());
    EXPECT_EQ(v["nested"]["inner_key"].getString(), "inner_val");
}

TEST(ValueBoundaryTest_45, NestedArray_45) {
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
// Stream operator test
// ============================================================

TEST(ValueStreamTest_45, OutputStreamOperator_45) {
    Value v("stream_test");
    std::ostringstream oss;
    oss << v;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("stream_test"), std::string::npos);
}

// ============================================================
// Type Transition Tests  
// ============================================================

TEST(ValueTransitionTest_45, StringToInt_45) {
    Value v("hello");
    v.setInteger(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueTransitionTest_45, IntToDouble_45) {
    Value v(10);
    v.setDouble(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST(ValueTransitionTest_45, DoubleToBoolean_45) {
    Value v(1.5);
    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueTransitionTest_45, BooleanToNull_45) {
    Value v(true);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTransitionTest_45, NullToObject_45) {
    Value v;
    Object obj;
    obj["x"] = Value(1);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
}

TEST(ValueTransitionTest_45, ObjectToArray_45) {
    Object obj;
    obj["key"] = Value("val");
    Value v(obj);
    Array arr;
    arr.push_back(Value(1));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
}

TEST(ValueTransitionTest_45, ArrayToString_45) {
    Array arr;
    arr.push_back(Value(1));
    Value v(arr);
    v.setString("converted");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "converted");
}

// ============================================================
// Load from complex JSON
// ============================================================

TEST(ValueComplexLoadTest_45, LoadComplexJson_45) {
    Value v;
    v.loadFromString(R"({"name": "test", "age": 30, "active": true, "score": 9.5, "tags": ["a", "b"], "address": null})");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["name"].getString(), "test");
    EXPECT_EQ(v["age"].getInteger(), 30);
    EXPECT_TRUE(v["active"].getBoolean());
    EXPECT_DOUBLE_EQ(v["score"].getDouble(), 9.5);
    EXPECT_TRUE(v["tags"].isArray());
    EXPECT_EQ(v["tags"].getArray().size(), 2u);
    EXPECT_TRUE(v["address"].isNull());
}

TEST(ValueComplexLoadTest_45, LoadNestedJson_45) {
    Value v;
    v.loadFromString(R"({"outer": {"inner": 42}})");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

TEST(ValueComplexLoadTest_45, RoundTripJsonObject_45) {
    Value v;
    v.loadFromString(R"({"key":"value"})");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    
    Value v2;
    v2.loadFromString(oss.str());
    EXPECT_TRUE(v2.isObject());
    EXPECT_EQ(v2["key"].getString(), "value");
}
