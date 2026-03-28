#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

// =============================================================================
// Construction Tests
// =============================================================================

TEST(ValueConstructorTest_18, DefaultConstructorCreatesNull_18) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST(ValueConstructorTest_18, StringConstructor_18) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueConstructorTest_18, CStringConstructor_18) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST(ValueConstructorTest_18, IntConstructor_18) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueConstructorTest_18, IntConstructorNegative_18) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST(ValueConstructorTest_18, IntConstructorZero_18) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST(ValueConstructorTest_18, DoubleConstructor_18) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST(ValueConstructorTest_18, BooleanConstructorTrue_18) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueConstructorTest_18, BooleanConstructorFalse_18) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueConstructorTest_18, ObjectConstructor_18) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST(ValueConstructorTest_18, ArrayConstructor_18) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST(ValueConstructorTest_18, CopyConstructor_18) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

TEST(ValueConstructorTest_18, CopyConstructorString_18) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "test");
}

TEST(ValueConstructorTest_18, StreamConstructor_18) {
    std::istringstream iss("42");
    Value v(iss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

// =============================================================================
// Type Checking Tests
// =============================================================================

TEST(ValueTypeCheckTest_18, IsStringable_18) {
    Value vStr("hello");
    EXPECT_TRUE(vStr.isStringable());

    Value vInt(42);
    // Integer might or might not be stringable; test based on actual behavior
    // but at least string should be stringable
}

TEST(ValueTypeCheckTest_18, IsNumericForInt_18) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
}

TEST(ValueTypeCheckTest_18, IsNumericForDouble_18) {
    Value v(5.0);
    EXPECT_TRUE(v.isNumeric());
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
}

TEST(ValueTypeCheckTest_18, NullIsNotOtherTypes_18) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNumeric());
}

TEST(ValueTypeCheckTest_18, StringIsNotOtherTypes_18) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isNull());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
}

TEST(ValueTypeCheckTest_18, BooleanIsNotOtherTypes_18) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
}

// =============================================================================
// Assignment Operator Tests
// =============================================================================

TEST(ValueAssignmentTest_18, AssignInt_18) {
    Value v;
    v = 10;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 10);
}

TEST(ValueAssignmentTest_18, AssignDouble_18) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST(ValueAssignmentTest_18, AssignString_18) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST(ValueAssignmentTest_18, AssignCString_18) {
    Value v;
    v = "c_string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "c_string");
}

TEST(ValueAssignmentTest_18, AssignBoolean_18) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueAssignmentTest_18, AssignObject_18) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST(ValueAssignmentTest_18, AssignArray_18) {
    Value v;
    Array arr;
    arr.push_back(Value("item"));
    v = arr;
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

TEST(ValueAssignmentTest_18, AssignValue_18) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST(ValueAssignmentTest_18, ReassignChangesType_18) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v = "now a string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

// =============================================================================
// Setter/Getter Tests
// =============================================================================

TEST(ValueSetterGetterTest_18, SetAndGetString_18) {
    Value v;
    v.setString("hello");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueSetterGetterTest_18, SetAndGetInteger_18) {
    Value v;
    v.setInteger(99);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST(ValueSetterGetterTest_18, SetAndGetDouble_18) {
    Value v;
    v.setDouble(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.5);
}

TEST(ValueSetterGetterTest_18, SetAndGetBoolean_18) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueSetterGetterTest_18, SetAndGetObject_18) {
    Value v;
    Object obj;
    obj["x"] = Value(10);
    obj["y"] = Value(20);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 2u);
}

TEST(ValueSetterGetterTest_18, SetAndGetArray_18) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    arr.push_back(Value(3));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST(ValueSetterGetterTest_18, SetNull_18) {
    Value v(42);
    EXPECT_FALSE(v.isNull());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST(ValueSetterGetterTest_18, GetFloat_18) {
    Value v(3.14);
    EXPECT_FLOAT_EQ(v.getFloat(), 3.14f);
}

// =============================================================================
// Try-Get Tests (with defaults)
// =============================================================================

TEST(ValueTryGetTest_18, TryGetStringWhenString_18) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST(ValueTryGetTest_18, TryGetStringWhenNotString_18) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST(ValueTryGetTest_18, TryGetIntegerWhenInteger_18) {
    Value v(100);
    EXPECT_EQ(v.tryGetInteger(0), 100);
}

TEST(ValueTryGetTest_18, TryGetIntegerWhenNotInteger_18) {
    Value v("not an int");
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

TEST(ValueTryGetTest_18, TryGetDoubleWhenDouble_18) {
    Value v(2.5);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 2.5);
}

TEST(ValueTryGetTest_18, TryGetDoubleWhenNotDouble_18) {
    Value v("not a double");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(9.9), 9.9);
}

TEST(ValueTryGetTest_18, TryGetFloatWhenDouble_18) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 1.5f);
}

TEST(ValueTryGetTest_18, TryGetFloatWhenNotDouble_18) {
    Value v("not a float");
    EXPECT_FLOAT_EQ(v.tryGetFloat(7.7f), 7.7f);
}

TEST(ValueTryGetTest_18, TryGetBooleanWhenBoolean_18) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST(ValueTryGetTest_18, TryGetBooleanWhenNotBoolean_18) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// =============================================================================
// Comparison Operator Tests
// =============================================================================

TEST(ValueComparisonTest_18, EqualIntegers_18) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST(ValueComparisonTest_18, NotEqualIntegers_18) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST(ValueComparisonTest_18, LessThanIntegers_18) {
    Value v1(10);
    Value v2(20);
    EXPECT_TRUE(v1 < v2);
    EXPECT_TRUE(v1 <= v2);
    EXPECT_FALSE(v1 > v2);
    EXPECT_FALSE(v1 >= v2);
}

TEST(ValueComparisonTest_18, GreaterThanIntegers_18) {
    Value v1(20);
    Value v2(10);
    EXPECT_TRUE(v1 > v2);
    EXPECT_TRUE(v1 >= v2);
    EXPECT_FALSE(v1 < v2);
    EXPECT_FALSE(v1 <= v2);
}

TEST(ValueComparisonTest_18, EqualStrings_18) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueComparisonTest_18, NotEqualStrings_18) {
    Value v1("abc");
    Value v2("xyz");
    EXPECT_TRUE(v1 != v2);
}

TEST(ValueComparisonTest_18, EqualBooleans_18) {
    Value v1(true);
    Value v2(true);
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueComparisonTest_18, EqualNulls_18) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueComparisonTest_18, LessOrEqualWhenEqual_18) {
    Value v1(5);
    Value v2(5);
    EXPECT_TRUE(v1 <= v2);
    EXPECT_TRUE(v1 >= v2);
}

// =============================================================================
// Subscript Operator Tests
// =============================================================================

TEST(ValueSubscriptTest_18, ObjectSubscriptString_18) {
    Value v;
    Object obj;
    obj["key"] = Value(123);
    v.setObject(obj);
    EXPECT_EQ(v["key"].getInteger(), 123);
}

TEST(ValueSubscriptTest_18, ObjectSubscriptCString_18) {
    Value v;
    Object obj;
    obj["name"] = Value("John");
    v.setObject(obj);
    EXPECT_EQ(v["name"].getString(), "John");
}

TEST(ValueSubscriptTest_18, ArraySubscript_18) {
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

// =============================================================================
// Load / Parse Tests
// =============================================================================

TEST(ValueLoadTest_18, LoadFromStringInteger_18) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueLoadTest_18, LoadFromStringString_18) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueLoadTest_18, LoadFromStringBoolean_18) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueLoadTest_18, LoadFromStringNull_18) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST(ValueLoadTest_18, LoadFromStringDouble_18) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST(ValueLoadTest_18, LoadFromStringArray_18) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST(ValueLoadTest_18, LoadFromStringObject_18) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST(ValueLoadTest_18, LoadFromStringEmptyObject_18) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST(ValueLoadTest_18, LoadFromStringEmptyArray_18) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST(ValueLoadTest_18, LoadFromStream_18) {
    std::istringstream iss("{\"a\": 1}");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isObject());
}

TEST(ValueLoadTest_18, LoadFromStringNegativeInt_18) {
    Value v;
    v.loadFromString("-5");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -5);
}

TEST(ValueLoadTest_18, LoadFromStringNestedObject_18) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": 42}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

TEST(ValueLoadTest_18, LoadFromStringNestedArray_18) {
    Value v;
    v.loadFromString("[[1, 2], [3, 4]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
    EXPECT_TRUE(v[(size_t)0].isArray());
    EXPECT_EQ(v[(size_t)0].getArray().size(), 2u);
}

// =============================================================================
// Write / Serialize Tests
// =============================================================================

TEST(ValueWriteTest_18, WriteIntegerToStream_18) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "42");
}

TEST(ValueWriteTest_18, WriteStringToStream_18) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "\"hello\"");
}

TEST(ValueWriteTest_18, WriteBooleanTrueToStream_18) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "true");
}

TEST(ValueWriteTest_18, WriteBooleanFalseToStream_18) {
    Value v(false);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "false");
}

TEST(ValueWriteTest_18, WriteNullToStream_18) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "null");
}

TEST(ValueWriteTest_18, WriteEmptyObjectToStream_18) {
    Value v;
    v.setObject(Object());
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "{}");
}

TEST(ValueWriteTest_18, WriteEmptyArrayToStream_18) {
    Value v;
    v.setArray(Array());
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "[]");
}

TEST(ValueWriteTest_18, WriteDoubleToStream_18) {
    Value v(1.5);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    // Should contain 1.5 in some form
    EXPECT_NE(output.find("1.5"), std::string::npos);
}

TEST(ValueWriteTest_18, StreamOperator_18) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// =============================================================================
// Escape Functions Tests
// =============================================================================

TEST(ValueEscapeTest_18, EscapeMinimumCharacters_18) {
    std::string input = "hello\nworld";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST(ValueEscapeTest_18, EscapeMinimumCharactersQuote_18) {
    std::string input = "say \"hello\"";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST(ValueEscapeTest_18, EscapeMinimumCharactersBackslash_18) {
    std::string input = "back\\slash";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST(ValueEscapeTest_18, EscapeMinimumCharactersNoEscape_18) {
    std::string input = "simple";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ(result, "simple");
}

TEST(ValueEscapeTest_18, EscapeAllCharacters_18) {
    std::string input = "hello\nworld";
    std::string result = Value::escapeAllCharacters(input);
    // Should escape newline
    EXPECT_EQ(result.find('\n'), std::string::npos);
}

TEST(ValueEscapeTest_18, EscapeToUnicode_18) {
    std::string result = Value::escapeToUnicode('A');
    // Should produce a unicode escape like \u0041
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// =============================================================================
// Boundary and Edge Case Tests
// =============================================================================

TEST(ValueBoundaryTest_18, EmptyString_18) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST(ValueBoundaryTest_18, IntMaxValue_18) {
    Value v(INT_MAX);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), INT_MAX);
}

TEST(ValueBoundaryTest_18, IntMinValue_18) {
    Value v(INT_MIN);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), INT_MIN);
}

TEST(ValueBoundaryTest_18, DoubleZero_18) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST(ValueBoundaryTest_18, EmptyObjectValue_18) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST(ValueBoundaryTest_18, EmptyArrayValue_18) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST(ValueBoundaryTest_18, SetNullThenReassign_18) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
    v.setInteger(100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST(ValueBoundaryTest_18, MultipleTypeChanges_18) {
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

TEST(ValueBoundaryTest_18, GetToStringForInt_18) {
    Value v(42);
    // getToString should work for stringable types
    if (v.isStringable()) {
        std::string s = v.getToString();
        EXPECT_FALSE(s.empty());
    }
}

TEST(ValueBoundaryTest_18, GetToStringForString_18) {
    Value v("hello");
    std::string s = v.getToString();
    EXPECT_EQ(s, "hello");
}

TEST(ValueBoundaryTest_18, SelfAssignment_18) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

// =============================================================================
// Complex JSON Parsing Tests
// =============================================================================

TEST(ValueComplexTest_18, ParseMixedTypeArray_18) {
    Value v;
    v.loadFromString("[1, \"two\", 3.0, true, null]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 5u);
    EXPECT_TRUE(v[(size_t)0].isInteger());
    EXPECT_TRUE(v[(size_t)1].isString());
    EXPECT_TRUE(v[(size_t)3].isBoolean());
    EXPECT_TRUE(v[(size_t)4].isNull());
}

TEST(ValueComplexTest_18, ParseComplexObject_18) {
    Value v;
    v.loadFromString("{\"name\": \"test\", \"value\": 42, \"active\": true, \"items\": [1, 2, 3]}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["name"].getString(), "test");
    EXPECT_EQ(v["value"].getInteger(), 42);
    EXPECT_TRUE(v["active"].getBoolean());
    EXPECT_TRUE(v["items"].isArray());
    EXPECT_EQ(v["items"].getArray().size(), 3u);
}

TEST(ValueComplexTest_18, RoundTripSerialization_18) {
    Value original;
    original.loadFromString("{\"key\": \"value\"}");
    
    std::ostringstream oss;
    original.writeToStream(oss, false, false);
    
    Value reparsed;
    reparsed.loadFromString(oss.str());
    EXPECT_TRUE(reparsed.isObject());
    EXPECT_EQ(reparsed["key"].getString(), "value");
}

TEST(ValueComplexTest_18, WriteWithIndent_18) {
    Value v;
    v.loadFromString("{\"a\": 1}");
    std::ostringstream ossIndent;
    v.writeToStream(ossIndent, true, false);
    std::ostringstream ossNoIndent;
    v.writeToStream(ossNoIndent, false, false);
    // Indented version should generally be longer
    EXPECT_GE(ossIndent.str().size(), ossNoIndent.str().size());
}

TEST(ValueComplexTest_18, LoadFromStringWithWhitespace_18) {
    Value v;
    v.loadFromString("  { \"key\" : \"value\" }  ");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST(ValueComplexTest_18, EscapeAllInOutput_18) {
    Value v("hello\nworld");
    std::ostringstream ossNormal;
    v.writeToStream(ossNormal, false, false);
    std::ostringstream ossEscapeAll;
    v.writeToStream(ossEscapeAll, false, true);
    // Both should produce valid output
    EXPECT_FALSE(ossNormal.str().empty());
    EXPECT_FALSE(ossEscapeAll.str().empty());
}

// =============================================================================
// Negative Integer Tests  
// =============================================================================

TEST(ValueLoadTest_18, LoadFromStringNegativeDouble_18) {
    Value v;
    v.loadFromString("-3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -3.14);
}

TEST(ValueLoadTest_18, LoadFromStringFalse_18) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueLoadTest_18, LoadFromStringEscapedString_18) {
    Value v;
    v.loadFromString("\"hello\\nworld\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello\nworld");
}

// =============================================================================
// Object key creation via subscript  
// =============================================================================

TEST(ValueSubscriptTest_18, ObjectSubscriptCreatesKey_18) {
    Value v;
    v.setObject(Object());
    v["newkey"] = Value(42);
    EXPECT_EQ(v["newkey"].getInteger(), 42);
}

TEST(ValueSubscriptTest_18, ObjectSubscriptMultipleKeys_18) {
    Value v;
    v.setObject(Object());
    v["a"] = Value(1);
    v["b"] = Value(2);
    v["c"] = Value(3);
    EXPECT_EQ(v.getObject().size(), 3u);
}
