#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

// =============================================
// Construction Tests
// =============================================

TEST(ValueConstructorTest_22, DefaultConstructorCreatesNull_22) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST(ValueConstructorTest_22, StringConstructor_22) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueConstructorTest_22, CStringConstructor_22) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST(ValueConstructorTest_22, IntConstructor_22) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueConstructorTest_22, IntConstructorZero_22) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST(ValueConstructorTest_22, IntConstructorNegative_22) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST(ValueConstructorTest_22, DoubleConstructor_22) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST(ValueConstructorTest_22, DoubleConstructorZero_22) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST(ValueConstructorTest_22, BooleanConstructorTrue_22) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueConstructorTest_22, BooleanConstructorFalse_22) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueConstructorTest_22, ObjectConstructor_22) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST(ValueConstructorTest_22, ArrayConstructor_22) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST(ValueConstructorTest_22, CopyConstructor_22) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

TEST(ValueConstructorTest_22, EmptyStringConstructor_22) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST(ValueConstructorTest_22, StreamConstructorValidJson_22) {
    std::istringstream ss("42");
    Value v(ss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

// =============================================
// Type Check Tests
// =============================================

TEST(ValueTypeCheckTest_22, IsStringable_22) {
    Value vStr("hello");
    EXPECT_TRUE(vStr.isStringable());

    Value vInt(42);
    // Integers may or may not be stringable depending on implementation
    // but we can at least call it
    vInt.isStringable();

    Value vNull;
    vNull.isStringable();
}

TEST(ValueTypeCheckTest_22, IsNumericForInt_22) {
    Value v(42);
    EXPECT_TRUE(v.isNumeric());
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
}

TEST(ValueTypeCheckTest_22, IsNumericForDouble_22) {
    Value v(3.14);
    EXPECT_TRUE(v.isNumeric());
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
}

TEST(ValueTypeCheckTest_22, NullIsNotOtherTypes_22) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isNumeric());
}

TEST(ValueTypeCheckTest_22, StringIsNotOtherTypes_22) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isNull());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
}

TEST(ValueTypeCheckTest_22, BooleanIsNotOtherTypes_22) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
}

// =============================================
// Assignment Operator Tests
// =============================================

TEST(ValueAssignmentTest_22, AssignString_22) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST(ValueAssignmentTest_22, AssignCString_22) {
    Value v;
    v = "cstring";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "cstring");
}

TEST(ValueAssignmentTest_22, AssignInt_22) {
    Value v;
    v = 99;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST(ValueAssignmentTest_22, AssignDouble_22) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST(ValueAssignmentTest_22, AssignBoolTrue_22) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueAssignmentTest_22, AssignBoolFalse_22) {
    Value v;
    v = false;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueAssignmentTest_22, AssignObject_22) {
    Value v;
    Object obj;
    obj["x"] = Value(10);
    v = obj;
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST(ValueAssignmentTest_22, AssignArray_22) {
    Value v;
    Array arr;
    arr.push_back(Value("elem"));
    v = arr;
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

TEST(ValueAssignmentTest_22, AssignValueCopy_22) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST(ValueAssignmentTest_22, ReassignDifferentType_22) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v = std::string("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST(ValueAssignmentTest_22, ChainedAssignment_22) {
    Value v1, v2;
    v1 = v2 = 42;
    EXPECT_TRUE(v1.isInteger());
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v1.getInteger(), 42);
    EXPECT_EQ(v2.getInteger(), 42);
}

// =============================================
// Setter/Getter Tests
// =============================================

TEST(ValueSetterGetterTest_22, SetAndGetString_22) {
    Value v;
    v.setString("test");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

TEST(ValueSetterGetterTest_22, SetAndGetInteger_22) {
    Value v;
    v.setInteger(123);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

TEST(ValueSetterGetterTest_22, SetAndGetDouble_22) {
    Value v;
    v.setDouble(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.5);
}

TEST(ValueSetterGetterTest_22, SetAndGetBoolean_22) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
    v.setBoolean(false);
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueSetterGetterTest_22, SetNull_22) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST(ValueSetterGetterTest_22, SetAndGetObject_22) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    obj["b"] = Value(2);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 2u);
}

TEST(ValueSetterGetterTest_22, SetAndGetArray_22) {
    Value v;
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST(ValueSetterGetterTest_22, GetFloat_22) {
    Value v(3.14);
    float f = v.getFloat();
    EXPECT_NEAR(f, 3.14f, 0.001f);
}

// =============================================
// Try-Get Tests (with defaults)
// =============================================

TEST(ValueTryGetTest_22, TryGetStringWhenString_22) {
    Value v("hello");
    EXPECT_EQ(v.tryGetString("default"), "hello");
}

TEST(ValueTryGetTest_22, TryGetStringWhenNotString_22) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST(ValueTryGetTest_22, TryGetIntegerWhenInteger_22) {
    Value v(42);
    EXPECT_EQ(v.tryGetInteger(0), 42);
}

TEST(ValueTryGetTest_22, TryGetIntegerWhenNotInteger_22) {
    Value v("not an int");
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

TEST(ValueTryGetTest_22, TryGetDoubleWhenDouble_22) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 3.14);
}

TEST(ValueTryGetTest_22, TryGetDoubleWhenNotDouble_22) {
    Value v("string");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(9.9), 9.9);
}

TEST(ValueTryGetTest_22, TryGetFloatWhenDouble_22) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST(ValueTryGetTest_22, TryGetFloatWhenNotDouble_22) {
    Value v("string");
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.1f), 1.1f);
}

TEST(ValueTryGetTest_22, TryGetBooleanWhenBoolean_22) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST(ValueTryGetTest_22, TryGetBooleanWhenNotBoolean_22) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

TEST(ValueTryGetTest_22, TryGetStringOnNull_22) {
    Value v;
    EXPECT_EQ(v.tryGetString("fallback"), "fallback");
}

TEST(ValueTryGetTest_22, TryGetIntegerOnNull_22) {
    Value v;
    EXPECT_EQ(v.tryGetInteger(55), 55);
}

TEST(ValueTryGetTest_22, TryGetBooleanOnNull_22) {
    Value v;
    EXPECT_TRUE(v.tryGetBoolean(true));
}

// =============================================
// Comparison Operator Tests
// =============================================

TEST(ValueComparisonTest_22, EqualityOfSameIntegers_22) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST(ValueComparisonTest_22, InequalityOfDifferentIntegers_22) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST(ValueComparisonTest_22, EqualityOfSameStrings_22) {
    Value v1("hello");
    Value v2("hello");
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueComparisonTest_22, InequalityOfDifferentStrings_22) {
    Value v1("hello");
    Value v2("world");
    EXPECT_TRUE(v1 != v2);
}

TEST(ValueComparisonTest_22, EqualityOfSameBooleans_22) {
    Value v1(true);
    Value v2(true);
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueComparisonTest_22, EqualityOfNulls_22) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueComparisonTest_22, InequalityOfDifferentTypes_22) {
    Value vInt(42);
    Value vStr("42");
    EXPECT_TRUE(vInt != vStr);
}

TEST(ValueComparisonTest_22, LessThanIntegers_22) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST(ValueComparisonTest_22, LessThanOrEqualIntegers_22) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST(ValueComparisonTest_22, GreaterThanIntegers_22) {
    Value v1(5);
    Value v2(3);
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v2 > v1);
}

TEST(ValueComparisonTest_22, GreaterThanOrEqualIntegers_22) {
    Value v1(5);
    Value v2(5);
    EXPECT_TRUE(v1 >= v2);
}

TEST(ValueComparisonTest_22, EqualityOfDoubles_22) {
    Value v1(3.14);
    Value v2(3.14);
    EXPECT_TRUE(v1 == v2);
}

// =============================================
// Subscript Operator Tests
// =============================================

TEST(ValueSubscriptTest_22, ObjectSubscriptString_22) {
    Value v;
    Object obj;
    obj["key"] = Value(42);
    v.setObject(obj);
    EXPECT_TRUE(v["key"].isInteger());
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST(ValueSubscriptTest_22, ObjectSubscriptCString_22) {
    Value v;
    Object obj;
    obj["mykey"] = Value("myval");
    v.setObject(obj);
    EXPECT_TRUE(v["mykey"].isString());
    EXPECT_EQ(v["mykey"].getString(), "myval");
}

TEST(ValueSubscriptTest_22, ArraySubscript_22) {
    Value v;
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    v.setArray(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

TEST(ValueSubscriptTest_22, ObjectSubscriptCreatesEntry_22) {
    Value v;
    Object obj;
    v.setObject(obj);
    // Accessing a non-existent key should create it (like std::map)
    Value &ref = v["newkey"];
    EXPECT_TRUE(ref.isNull());
}

// =============================================
// Load/Parse Tests
// =============================================

TEST(ValueLoadTest_22, LoadFromStringInteger_22) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueLoadTest_22, LoadFromStringDouble_22) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST(ValueLoadTest_22, LoadFromStringString_22) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueLoadTest_22, LoadFromStringBoolTrue_22) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueLoadTest_22, LoadFromStringBoolFalse_22) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueLoadTest_22, LoadFromStringNull_22) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST(ValueLoadTest_22, LoadFromStringObject_22) {
    Value v;
    v.loadFromString("{\"key\": 123}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getInteger(), 123);
}

TEST(ValueLoadTest_22, LoadFromStringArray_22) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST(ValueLoadTest_22, LoadFromStringEmptyObject_22) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v.getObject().empty());
}

TEST(ValueLoadTest_22, LoadFromStringEmptyArray_22) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v.getArray().empty());
}

TEST(ValueLoadTest_22, LoadFromStream_22) {
    std::istringstream ss("{\"a\": 1}");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["a"].getInteger(), 1);
}

TEST(ValueLoadTest_22, LoadFromStringNegativeInt_22) {
    Value v;
    v.loadFromString("-7");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -7);
}

TEST(ValueLoadTest_22, LoadFromStringNestedObject_22) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": true}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_TRUE(v["outer"]["inner"].getBoolean());
}

TEST(ValueLoadTest_22, LoadFromStringNestedArray_22) {
    Value v;
    v.loadFromString("[[1, 2], [3, 4]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
    EXPECT_TRUE(v[(size_t)0].isArray());
    EXPECT_TRUE(v[(size_t)1].isArray());
}

// =============================================
// Write/Serialize Tests
// =============================================

TEST(ValueWriteTest_22, WriteIntegerToStream_22) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST(ValueWriteTest_22, WriteStringToStream_22) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST(ValueWriteTest_22, WriteNullToStream_22) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("null"), std::string::npos);
}

TEST(ValueWriteTest_22, WriteBoolTrueToStream_22) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST(ValueWriteTest_22, WriteBoolFalseToStream_22) {
    Value v(false);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("false"), std::string::npos);
}

TEST(ValueWriteTest_22, WriteObjectToStream_22) {
    Value v;
    v.loadFromString("{\"key\": 123}");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("key"), std::string::npos);
    EXPECT_NE(output.find("123"), std::string::npos);
}

TEST(ValueWriteTest_22, WriteArrayToStream_22) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
    EXPECT_NE(output.find("3"), std::string::npos);
}

TEST(ValueWriteTest_22, WriteWithIndent_22) {
    Value v;
    v.loadFromString("{\"key\": 123}");
    std::ostringstream ossIndent;
    v.writeToStream(ossIndent, true, false);
    std::ostringstream ossNoIndent;
    v.writeToStream(ossNoIndent, false, false);
    // Indented output is generally longer
    EXPECT_GE(ossIndent.str().size(), ossNoIndent.str().size());
}

TEST(ValueWriteTest_22, StreamOperator_22) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

// =============================================
// Escape Character Tests
// =============================================

TEST(ValueEscapeTest_22, EscapeMinimumCharacters_22) {
    std::string result = Value::escapeMinimumCharacters("hello\nworld");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST(ValueEscapeTest_22, EscapeMinimumCharactersNoSpecial_22) {
    std::string result = Value::escapeMinimumCharacters("hello");
    EXPECT_EQ(result, "hello");
}

TEST(ValueEscapeTest_22, EscapeMinimumCharactersQuotes_22) {
    std::string result = Value::escapeMinimumCharacters("he\"llo");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST(ValueEscapeTest_22, EscapeMinimumCharactersBackslash_22) {
    std::string result = Value::escapeMinimumCharacters("he\\llo");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST(ValueEscapeTest_22, EscapeAllCharacters_22) {
    std::string result = Value::escapeAllCharacters("hello\nworld");
    // Should escape the newline
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST(ValueEscapeTest_22, EscapeToUnicode_22) {
    std::string result = Value::escapeToUnicode('A');
    // Should contain unicode escape like \u0041
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

TEST(ValueEscapeTest_22, EscapeMinimumEmptyString_22) {
    std::string result = Value::escapeMinimumCharacters("");
    EXPECT_EQ(result, "");
}

TEST(ValueEscapeTest_22, EscapeAllEmptyString_22) {
    std::string result = Value::escapeAllCharacters("");
    EXPECT_EQ(result, "");
}

// =============================================
// getToString Tests
// =============================================

TEST(ValueGetToStringTest_22, IntToString_22) {
    Value v(42);
    std::string s = v.getToString();
    EXPECT_NE(s.find("42"), std::string::npos);
}

TEST(ValueGetToStringTest_22, StringToString_22) {
    Value v("hello");
    std::string s = v.getToString();
    EXPECT_EQ(s, "hello");
}

TEST(ValueGetToStringTest_22, BoolTrueToString_22) {
    Value v(true);
    std::string s = v.getToString();
    EXPECT_FALSE(s.empty());
}

TEST(ValueGetToStringTest_22, NullToString_22) {
    Value v;
    std::string s = v.getToString();
    // Implementation dependent, but should not crash
    (void)s;
}

// =============================================
// Roundtrip Tests
// =============================================

TEST(ValueRoundtripTest_22, IntegerRoundtrip_22) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    Value v2;
    v2.loadFromString(oss.str());
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST(ValueRoundtripTest_22, StringRoundtrip_22) {
    Value v("hello world");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    Value v2;
    v2.loadFromString(oss.str());
    EXPECT_TRUE(v2.isString());
    EXPECT_EQ(v2.getString(), "hello world");
}

TEST(ValueRoundtripTest_22, ObjectRoundtrip_22) {
    Value v;
    v.loadFromString("{\"name\": \"test\", \"value\": 42}");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    Value v2;
    v2.loadFromString(oss.str());
    EXPECT_TRUE(v2.isObject());
    EXPECT_EQ(v2["name"].getString(), "test");
    EXPECT_EQ(v2["value"].getInteger(), 42);
}

TEST(ValueRoundtripTest_22, ArrayRoundtrip_22) {
    Value v;
    v.loadFromString("[1, \"two\", true, null]");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    Value v2;
    v2.loadFromString(oss.str());
    EXPECT_TRUE(v2.isArray());
    EXPECT_EQ(v2.getArray().size(), 4u);
}

// =============================================
// Boundary / Edge Cases
// =============================================

TEST(ValueBoundaryTest_22, LargeInteger_22) {
    Value v(2147483647); // INT_MAX
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST(ValueBoundaryTest_22, MinInteger_22) {
    Value v(-2147483647 - 1); // INT_MIN
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -2147483647 - 1);
}

TEST(ValueBoundaryTest_22, VerySmallDouble_22) {
    Value v(1e-300);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1e-300);
}

TEST(ValueBoundaryTest_22, VeryLargeDouble_22) {
    Value v(1e300);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1e300);
}

TEST(ValueBoundaryTest_22, EmptyObjectSubscript_22) {
    Value v;
    Object obj;
    v.setObject(obj);
    // Accessing non-existent key creates entry
    Value &ref = v["nonexistent"];
    EXPECT_TRUE(ref.isNull());
}

TEST(ValueBoundaryTest_22, StringWithSpecialChars_22) {
    Value v(std::string("line1\nline2\ttab"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "line1\nline2\ttab");
}

TEST(ValueBoundaryTest_22, MultipleTypeChanges_22) {
    Value v;
    EXPECT_TRUE(v.isNull());
    v = 42;
    EXPECT_TRUE(v.isInteger());
    v = "string";
    EXPECT_TRUE(v.isString());
    v = true;
    EXPECT_TRUE(v.isBoolean());
    v = 3.14;
    EXPECT_TRUE(v.isDouble());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST(ValueBoundaryTest_22, SelfAssignment_22) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueBoundaryTest_22, EmptyArray_22) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v.getArray().empty());
}

TEST(ValueBoundaryTest_22, EmptyObject_22) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v.getObject().empty());
}

// =============================================
// Complex JSON Parsing Tests
// =============================================

TEST(ValueComplexParsingTest_22, ParseStringWithEscapes_22) {
    Value v;
    v.loadFromString("\"hello\\nworld\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello\nworld");
}

TEST(ValueComplexParsingTest_22, ParseStringWithUnicode_22) {
    Value v;
    v.loadFromString("\"\\u0041\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "A");
}

TEST(ValueComplexParsingTest_22, ParseDeepNesting_22) {
    Value v;
    v.loadFromString("{\"a\": {\"b\": {\"c\": 42}}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["a"]["b"]["c"].getInteger(), 42);
}

TEST(ValueComplexParsingTest_22, ParseMixedArray_22) {
    Value v;
    v.loadFromString("[1, \"two\", 3.0, true, false, null, {\"key\": \"val\"}, [1,2]]");
    EXPECT_TRUE(v.isArray());
    const Array &arr = v.getArray();
    EXPECT_EQ(arr.size(), 8u);
}

TEST(ValueComplexParsingTest_22, ParseNegativeDouble_22) {
    Value v;
    v.loadFromString("-3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -3.14);
}

TEST(ValueComplexParsingTest_22, ParseWithWhitespace_22) {
    Value v;
    v.loadFromString("  {  \"key\"  :  42  }  ");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getInteger(), 42);
}
