#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

// ===== Construction Tests =====

TEST(ValueTest_58, DefaultConstructor_IsNull_58) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_58, StringConstructor_58) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueTest_58, CStringConstructor_58) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST(ValueTest_58, IntConstructor_58) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueTest_58, DoubleConstructor_58) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST(ValueTest_58, BooleanTrueConstructor_58) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_58, BooleanFalseConstructor_58) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueTest_58, ObjectConstructor_58) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
}

TEST(ValueTest_58, ArrayConstructor_58) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST(ValueTest_58, CopyConstructor_58) {
    Value original(123);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 123);
}

// ===== Type Checking Tests =====

TEST(ValueTest_58, IsStringOnString_58) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
}

TEST(ValueTest_58, IsIntegerOnInt_58) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_TRUE(v.isNumeric());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
}

TEST(ValueTest_58, IsDoubleOnDouble_58) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_TRUE(v.isNumeric());
    EXPECT_FALSE(v.isInteger());
}

TEST(ValueTest_58, IsNumericOnInteger_58) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST(ValueTest_58, IsNumericOnDouble_58) {
    Value v(5.5);
    EXPECT_TRUE(v.isNumeric());
}

TEST(ValueTest_58, IsNumericOnString_58) {
    Value v("not a number");
    EXPECT_FALSE(v.isNumeric());
}

TEST(ValueTest_58, IsNullOnDefault_58) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
}

// ===== Assignment Operator Tests =====

TEST(ValueTest_58, AssignString_58) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST(ValueTest_58, AssignCString_58) {
    Value v;
    v = "c-string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "c-string");
}

TEST(ValueTest_58, AssignInt_58) {
    Value v;
    v = 99;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST(ValueTest_58, AssignDouble_58) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST(ValueTest_58, AssignBool_58) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_58, AssignObject_58) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST(ValueTest_58, AssignArray_58) {
    Value v;
    Array arr;
    arr.push_back(Value("elem"));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

TEST(ValueTest_58, AssignValueCopy_58) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

// ===== Setter Tests =====

TEST(ValueTest_58, SetString_58) {
    Value v;
    v.setString("hello");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueTest_58, SetInteger_58) {
    Value v;
    v.setInteger(77);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 77);
}

TEST(ValueTest_58, SetDouble_58) {
    Value v;
    v.setDouble(1.23);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.23);
}

TEST(ValueTest_58, SetBoolean_58) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_58, SetBooleanFalse_58) {
    Value v;
    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueTest_58, SetNull_58) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_58, SetObject_58) {
    Value v;
    Object obj;
    obj["key"] = Value("val");
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
}

TEST(ValueTest_58, SetArray_58) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

// ===== tryGet Tests =====

TEST(ValueTest_58, TryGetBooleanOnBoolean_58) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST(ValueTest_58, TryGetBooleanOnNonBoolean_58) {
    Value v(42);
    EXPECT_TRUE(v.tryGetBoolean(true));
    EXPECT_FALSE(v.tryGetBoolean(false));
}

TEST(ValueTest_58, GetBooleanOnNonBoolean_ReturnsDefaultFalse_58) {
    Value v(42);
    // getBoolean calls tryGetBoolean(EMPTY_BOOL) where EMPTY_BOOL is false
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueTest_58, TryGetStringOnString_58) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST(ValueTest_58, TryGetStringOnNonString_58) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST(ValueTest_58, TryGetIntegerOnInteger_58) {
    Value v(100);
    EXPECT_EQ(v.tryGetInteger(-1), 100);
}

TEST(ValueTest_58, TryGetIntegerOnNonInteger_58) {
    Value v("not int");
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

TEST(ValueTest_58, TryGetDoubleOnDouble_58) {
    Value v(9.81);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 9.81);
}

TEST(ValueTest_58, TryGetDoubleOnNonDouble_58) {
    Value v("not double");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 0.0);
}

TEST(ValueTest_58, TryGetFloatOnDouble_58) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST(ValueTest_58, TryGetFloatOnNonDouble_58) {
    Value v("not float");
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.0f), 1.0f);
}

TEST(ValueTest_58, GetFloat_58) {
    Value v(3.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 3.5f);
}

// ===== Comparison Operators =====

TEST(ValueTest_58, EqualityOperator_SameIntegers_58) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST(ValueTest_58, EqualityOperator_DifferentIntegers_58) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST(ValueTest_58, EqualityOperator_DifferentTypes_58) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST(ValueTest_58, LessThanOperator_58) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST(ValueTest_58, LessThanOrEqualOperator_58) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST(ValueTest_58, GreaterThanOperator_58) {
    Value v1(5);
    Value v2(3);
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v2 > v1);
}

TEST(ValueTest_58, GreaterThanOrEqualOperator_58) {
    Value v1(5);
    Value v2(5);
    EXPECT_TRUE(v1 >= v2);
}

// ===== Subscript Operator Tests =====

TEST(ValueTest_58, SubscriptStringKey_58) {
    Object obj;
    obj["name"] = Value("test");
    Value v(obj);
    EXPECT_EQ(v["name"].getString(), "test");
}

TEST(ValueTest_58, SubscriptCStringKey_58) {
    Object obj;
    obj["key"] = Value(123);
    Value v(obj);
    EXPECT_EQ(v["key"].getInteger(), 123);
}

TEST(ValueTest_58, SubscriptArrayIndex_58) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

// ===== Load / Parse Tests =====

TEST(ValueTest_58, LoadFromString_Integer_58) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueTest_58, LoadFromString_String_58) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueTest_58, LoadFromString_Boolean_58) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_58, LoadFromString_BooleanFalse_58) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueTest_58, LoadFromString_Null_58) {
    Value v(42);
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_58, LoadFromString_Double_58) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST(ValueTest_58, LoadFromString_Object_58) {
    Value v;
    v.loadFromString("{\"a\": 1, \"b\": 2}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["a"].getInteger(), 1);
    EXPECT_EQ(v["b"].getInteger(), 2);
}

TEST(ValueTest_58, LoadFromString_Array_58) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST(ValueTest_58, LoadFromStream_58) {
    std::istringstream ss("{\"key\": \"value\"}");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST(ValueTest_58, StreamConstructor_58) {
    std::istringstream ss("123");
    Value v(ss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

// ===== Write Tests =====

TEST(ValueTest_58, WriteToStream_Integer_58) {
    Value v(42);
    std::ostringstream ss;
    v.writeToStream(ss, false, false);
    EXPECT_EQ(ss.str(), "42");
}

TEST(ValueTest_58, WriteToStream_String_58) {
    Value v("hello");
    std::ostringstream ss;
    v.writeToStream(ss, false, false);
    EXPECT_EQ(ss.str(), "\"hello\"");
}

TEST(ValueTest_58, WriteToStream_BoolTrue_58) {
    Value v(true);
    std::ostringstream ss;
    v.writeToStream(ss, false, false);
    EXPECT_EQ(ss.str(), "true");
}

TEST(ValueTest_58, WriteToStream_BoolFalse_58) {
    Value v(false);
    std::ostringstream ss;
    v.writeToStream(ss, false, false);
    EXPECT_EQ(ss.str(), "false");
}

TEST(ValueTest_58, WriteToStream_Null_58) {
    Value v;
    std::ostringstream ss;
    v.writeToStream(ss, false, false);
    EXPECT_EQ(ss.str(), "null");
}

TEST(ValueTest_58, WriteToStream_EmptyObject_58) {
    Value v;
    v.setObject(Object());
    std::ostringstream ss;
    v.writeToStream(ss, false, false);
    EXPECT_EQ(ss.str(), "{}");
}

TEST(ValueTest_58, WriteToStream_EmptyArray_58) {
    Value v;
    v.setArray(Array());
    std::ostringstream ss;
    v.writeToStream(ss, false, false);
    EXPECT_EQ(ss.str(), "[]");
}

TEST(ValueTest_58, StreamOutputOperator_58) {
    Value v(42);
    std::ostringstream ss;
    ss << v;
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
}

// ===== Escape Function Tests =====

TEST(ValueTest_58, EscapeMinimumCharacters_NoSpecial_58) {
    std::string result = Value::escapeMinimumCharacters("hello");
    EXPECT_EQ(result, "hello");
}

TEST(ValueTest_58, EscapeMinimumCharacters_WithQuotes_58) {
    std::string result = Value::escapeMinimumCharacters("he\"llo");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST(ValueTest_58, EscapeMinimumCharacters_WithBackslash_58) {
    std::string result = Value::escapeMinimumCharacters("he\\llo");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST(ValueTest_58, EscapeAllCharacters_NoSpecial_58) {
    std::string result = Value::escapeAllCharacters("hello");
    // All characters might be escaped to unicode
    EXPECT_FALSE(result.empty());
}

TEST(ValueTest_58, EscapeToUnicode_58) {
    std::string result = Value::escapeToUnicode('A');
    // Should produce a unicode escape like \u0041
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ===== Boundary / Edge Cases =====

TEST(ValueTest_58, IntegerBoundary_Zero_58) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST(ValueTest_58, IntegerBoundary_Negative_58) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST(ValueTest_58, IntegerBoundary_MaxInt_58) {
    Value v(std::numeric_limits<int>::max());
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), std::numeric_limits<int>::max());
}

TEST(ValueTest_58, IntegerBoundary_MinInt_58) {
    Value v(std::numeric_limits<int>::min());
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), std::numeric_limits<int>::min());
}

TEST(ValueTest_58, EmptyStringValue_58) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST(ValueTest_58, EmptyObject_58) {
    Value v(Object());
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST(ValueTest_58, EmptyArray_58) {
    Value v(Array());
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST(ValueTest_58, DoubleZero_58) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST(ValueTest_58, NegativeDouble_58) {
    Value v(-1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -1.5);
}

// ===== Type Change Tests =====

TEST(ValueTest_58, ChangeTypeFromIntToString_58) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setString("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
}

TEST(ValueTest_58, ChangeTypeFromStringToNull_58) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_58, ChangeTypeFromBoolToInt_58) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    v.setInteger(5);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isBoolean());
}

// ===== isStringable Tests =====

TEST(ValueTest_58, IsStringable_OnString_58) {
    Value v("test");
    EXPECT_TRUE(v.isStringable());
}

TEST(ValueTest_58, IsStringable_OnInteger_58) {
    Value v(42);
    // Integers might be stringable (convertible to string)
    // We just observe the behavior
    bool result = v.isStringable();
    (void)result; // just checking it doesn't crash
}

// ===== getToString Tests =====

TEST(ValueTest_58, GetToString_OnString_58) {
    Value v("test");
    EXPECT_EQ(v.getToString(), "test");
}

TEST(ValueTest_58, GetToString_OnInteger_58) {
    Value v(42);
    std::string s = v.getToString();
    EXPECT_FALSE(s.empty());
}

// ===== Nested Structure Tests =====

TEST(ValueTest_58, NestedObjectInArray_58) {
    Object obj;
    obj["x"] = Value(1);
    Array arr;
    arr.push_back(Value(obj));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v[(size_t)0].isObject());
    EXPECT_EQ(v[(size_t)0]["x"].getInteger(), 1);
}

TEST(ValueTest_58, NestedArrayInObject_58) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    Object obj;
    obj["numbers"] = Value(arr);
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["numbers"].isArray());
    EXPECT_EQ(v["numbers"].getArray().size(), 2u);
}

TEST(ValueTest_58, LoadComplexJson_58) {
    Value v;
    v.loadFromString("{\"name\": \"test\", \"values\": [1, 2.5, true, null, \"str\"]}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["name"].getString(), "test");
    EXPECT_TRUE(v["values"].isArray());
    const Array& arr = v["values"].getArray();
    EXPECT_EQ(arr.size(), 5u);
}

// ===== Self-Assignment Test =====

TEST(ValueTest_58, SelfAssignment_58) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

// ===== Roundtrip Test =====

TEST(ValueTest_58, RoundtripWriteAndParse_58) {
    Value original;
    original.loadFromString("{\"key\": [1, 2, 3], \"flag\": true}");
    
    std::ostringstream ss;
    original.writeToStream(ss, false, false);
    
    Value parsed;
    parsed.loadFromString(ss.str());
    
    EXPECT_TRUE(parsed.isObject());
    EXPECT_TRUE(parsed["flag"].isBoolean());
    EXPECT_TRUE(parsed["flag"].getBoolean());
    EXPECT_TRUE(parsed["key"].isArray());
    EXPECT_EQ(parsed["key"].getArray().size(), 3u);
}
