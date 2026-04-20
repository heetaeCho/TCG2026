#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueTest_23 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Constructor Tests
// ============================================================

TEST_F(ValueTest_23, DefaultConstructor_IsNull_23) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(Value::NULL_VALUE, v.getType());
}

TEST_F(ValueTest_23, StringConstructor_FromStdString_23) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("hello", v.getString());
}

TEST_F(ValueTest_23, StringConstructor_FromCString_23) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("world", v.getString());
}

TEST_F(ValueTest_23, IntConstructor_23) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(42, v.getInteger());
}

TEST_F(ValueTest_23, DoubleConstructor_23) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(3.14, v.getDouble());
}

TEST_F(ValueTest_23, BooleanConstructor_True_23) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_23, BooleanConstructor_False_23) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_23, ObjectConstructor_23) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ("value", v.getObject().at("key").getString());
}

TEST_F(ValueTest_23, ArrayConstructor_23) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(2u, v.getArray().size());
}

TEST_F(ValueTest_23, CopyConstructor_23) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ("test", copy.getString());
}

TEST_F(ValueTest_23, CopyConstructor_Integer_23) {
    Value original(99);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(99, copy.getInteger());
}

TEST_F(ValueTest_23, CopyConstructor_Null_23) {
    Value original;
    Value copy(original);
    EXPECT_TRUE(copy.isNull());
}

// ============================================================
// Assignment Operator Tests
// ============================================================

TEST_F(ValueTest_23, AssignmentFromValue_23) {
    Value v1("hello");
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isString());
    EXPECT_EQ("hello", v2.getString());
}

TEST_F(ValueTest_23, AssignmentFromString_23) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("assigned", v.getString());
}

TEST_F(ValueTest_23, AssignmentFromCString_23) {
    Value v;
    v = "cstring";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("cstring", v.getString());
}

TEST_F(ValueTest_23, AssignmentFromInt_23) {
    Value v;
    v = 123;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(123, v.getInteger());
}

TEST_F(ValueTest_23, AssignmentFromDouble_23) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(2.718, v.getDouble());
}

TEST_F(ValueTest_23, AssignmentFromBool_23) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_23, AssignmentFromObject_23) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_23, AssignmentFromArray_23) {
    Value v;
    Array arr;
    arr.push_back(Value("item"));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

// ============================================================
// Equality Operator Tests
// ============================================================

TEST_F(ValueTest_23, EqualityOperator_SameStringValues_23) {
    Value v1("hello");
    Value v2("hello");
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_23, EqualityOperator_DifferentStringValues_23) {
    Value v1("hello");
    Value v2("world");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_23, EqualityOperator_SameIntValues_23) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_23, EqualityOperator_DifferentIntValues_23) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_23, EqualityOperator_SameDoubleValues_23) {
    Value v1(3.14);
    Value v2(3.14);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_23, EqualityOperator_DifferentDoubleValues_23) {
    Value v1(3.14);
    Value v2(2.71);
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_23, EqualityOperator_SameBoolValues_23) {
    Value v1(true);
    Value v2(true);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_23, EqualityOperator_DifferentBoolValues_23) {
    Value v1(true);
    Value v2(false);
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_23, EqualityOperator_BothNull_23) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_23, EqualityOperator_DifferentTypes_23) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_23, EqualityOperator_IntVsDouble_23) {
    Value v1(42);
    Value v2(42.0);
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_23, EqualityOperator_SelfEquality_23) {
    Value v(42);
    EXPECT_TRUE(v == v);
}

TEST_F(ValueTest_23, EqualityOperator_SameObjectValues_23) {
    Object obj;
    obj["key"] = Value("value");
    Value v1(obj);
    Value v2(obj);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_23, EqualityOperator_DifferentObjectValues_23) {
    Object obj1;
    obj1["key"] = Value("value1");
    Object obj2;
    obj2["key"] = Value("value2");
    Value v1(obj1);
    Value v2(obj2);
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_23, EqualityOperator_SameArrayValues_23) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v1(arr);
    Value v2(arr);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_23, EqualityOperator_DifferentArrayValues_23) {
    Array arr1;
    arr1.push_back(Value(1));
    Array arr2;
    arr2.push_back(Value(2));
    Value v1(arr1);
    Value v2(arr2);
    EXPECT_FALSE(v1 == v2);
}

// ============================================================
// Inequality Operator Tests
// ============================================================

TEST_F(ValueTest_23, InequalityOperator_DifferentValues_23) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_23, InequalityOperator_SameValues_23) {
    Value v1(1);
    Value v2(1);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueTest_23, InequalityOperator_DifferentTypes_23) {
    Value v1(1);
    Value v2("1");
    EXPECT_TRUE(v1 != v2);
}

// ============================================================
// Comparison Operators Tests
// ============================================================

TEST_F(ValueTest_23, LessThanOperator_Integers_23) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_23, LessThanOrEqualOperator_EqualIntegers_23) {
    Value v1(5);
    Value v2(5);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_23, LessThanOrEqualOperator_LessInteger_23) {
    Value v1(3);
    Value v2(5);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_23, GreaterThanOperator_Integers_23) {
    Value v1(10);
    Value v2(5);
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v2 > v1);
}

TEST_F(ValueTest_23, GreaterThanOrEqualOperator_EqualIntegers_23) {
    Value v1(7);
    Value v2(7);
    EXPECT_TRUE(v1 >= v2);
}

// ============================================================
// Type Checking Tests
// ============================================================

TEST_F(ValueTest_23, IsString_True_23) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_23, IsInteger_True_23) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_23, IsDouble_True_23) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_23, IsNumeric_IntegerIsNumeric_23) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_23, IsNumeric_DoubleIsNumeric_23) {
    Value v(5.5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_23, IsNumeric_StringIsNotNumeric_23) {
    Value v("5");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_23, IsObject_True_23) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_23, IsArray_True_23) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_23, IsBoolean_True_23) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
}

TEST_F(ValueTest_23, IsNull_True_23) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

// ============================================================
// Getter / Setter Tests
// ============================================================

TEST_F(ValueTest_23, SetString_23) {
    Value v;
    v.setString("new string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("new string", v.getString());
}

TEST_F(ValueTest_23, SetInteger_23) {
    Value v;
    v.setInteger(999);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(999, v.getInteger());
}

TEST_F(ValueTest_23, SetDouble_23) {
    Value v;
    v.setDouble(1.23);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(1.23, v.getDouble());
}

TEST_F(ValueTest_23, SetBoolean_23) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_23, SetNull_23) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_23, SetObject_23) {
    Value v;
    Object obj;
    obj["x"] = Value(10);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(10, v.getObject().at("x").getInteger());
}

TEST_F(ValueTest_23, SetArray_23) {
    Value v;
    Array arr;
    arr.push_back(Value("a"));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(1u, v.getArray().size());
}

TEST_F(ValueTest_23, GetFloat_23) {
    Value v(3.14);
    float f = v.getFloat();
    EXPECT_NEAR(3.14f, f, 0.001f);
}

// ============================================================
// Try Getters Tests
// ============================================================

TEST_F(ValueTest_23, TryGetString_WhenString_23) {
    Value v("actual");
    EXPECT_EQ("actual", v.tryGetString("default"));
}

TEST_F(ValueTest_23, TryGetString_WhenNotString_23) {
    Value v(42);
    EXPECT_EQ("default", v.tryGetString("default"));
}

TEST_F(ValueTest_23, TryGetInteger_WhenInteger_23) {
    Value v(100);
    EXPECT_EQ(100, v.tryGetInteger(0));
}

TEST_F(ValueTest_23, TryGetInteger_WhenNotInteger_23) {
    Value v("not int");
    EXPECT_EQ(0, v.tryGetInteger(0));
}

TEST_F(ValueTest_23, TryGetDouble_WhenDouble_23) {
    Value v(1.5);
    EXPECT_DOUBLE_EQ(1.5, v.tryGetDouble(0.0));
}

TEST_F(ValueTest_23, TryGetDouble_WhenNotDouble_23) {
    Value v("not double");
    EXPECT_DOUBLE_EQ(0.0, v.tryGetDouble(0.0));
}

TEST_F(ValueTest_23, TryGetFloat_WhenDouble_23) {
    Value v(2.5);
    EXPECT_NEAR(2.5f, v.tryGetFloat(0.0f), 0.001f);
}

TEST_F(ValueTest_23, TryGetFloat_WhenNotDouble_23) {
    Value v("not float");
    EXPECT_NEAR(0.0f, v.tryGetFloat(0.0f), 0.001f);
}

TEST_F(ValueTest_23, TryGetBoolean_WhenBoolean_23) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_23, TryGetBoolean_WhenNotBoolean_23) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ============================================================
// Subscript Operator Tests
// ============================================================

TEST_F(ValueTest_23, SubscriptOperator_StringKey_23) {
    Value v;
    v.setObject(Object());
    v["key"] = Value(42);
    EXPECT_EQ(42, v["key"].getInteger());
}

TEST_F(ValueTest_23, SubscriptOperator_CStringKey_23) {
    Value v;
    v.setObject(Object());
    const char* key = "mykey";
    v[key] = Value("myval");
    EXPECT_EQ("myval", v[key].getString());
}

TEST_F(ValueTest_23, SubscriptOperator_ArrayIndex_23) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(10, v[(size_t)0].getInteger());
    EXPECT_EQ(20, v[(size_t)1].getInteger());
    EXPECT_EQ(30, v[(size_t)2].getInteger());
}

// ============================================================
// Load and Write Tests
// ============================================================

TEST_F(ValueTest_23, LoadFromString_SimpleInt_23) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(42, v.getInteger());
}

TEST_F(ValueTest_23, LoadFromString_SimpleString_23) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("hello", v.getString());
}

TEST_F(ValueTest_23, LoadFromString_Boolean_True_23) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_23, LoadFromString_Boolean_False_23) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_23, LoadFromString_Null_23) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_23, LoadFromString_Object_23) {
    Value v;
    v.loadFromString("{\"key\": 1}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(1, v["key"].getInteger());
}

TEST_F(ValueTest_23, LoadFromString_Array_23) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(3u, v.getArray().size());
}

TEST_F(ValueTest_23, LoadFromStream_23) {
    std::istringstream iss("\"stream test\"");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("stream test", v.getString());
}

TEST_F(ValueTest_23, WriteToStream_Integer_23) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(std::string::npos, output.find("42"));
}

TEST_F(ValueTest_23, WriteToStream_String_23) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(std::string::npos, output.find("hello"));
}

TEST_F(ValueTest_23, WriteToStream_Object_23) {
    Value v;
    v.loadFromString("{\"a\": 1}");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(std::string::npos, output.find("a"));
}

TEST_F(ValueTest_23, WriteToStream_WithIndent_23) {
    Value v;
    v.loadFromString("{\"a\": 1}");
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// ============================================================
// IsStringable Tests
// ============================================================

TEST_F(ValueTest_23, IsStringable_String_23) {
    Value v("test");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_23, IsStringable_Integer_23) {
    Value v(42);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_23, IsStringable_Double_23) {
    Value v(3.14);
    EXPECT_TRUE(v.isStringable());
}

// ============================================================
// GetToString Tests
// ============================================================

TEST_F(ValueTest_23, GetToString_FromString_23) {
    Value v("test");
    EXPECT_EQ("test", v.getToString());
}

TEST_F(ValueTest_23, GetToString_FromInteger_23) {
    Value v(42);
    std::string result = v.getToString();
    EXPECT_EQ("42", result);
}

// ============================================================
// Escape Functions Tests
// ============================================================

TEST_F(ValueTest_23, EscapeMinimumCharacters_NoSpecial_23) {
    std::string input = "hello";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ("hello", result);
}

TEST_F(ValueTest_23, EscapeMinimumCharacters_WithQuotes_23) {
    std::string input = "he\"llo";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_NE(std::string::npos, result.find("\\\""));
}

TEST_F(ValueTest_23, EscapeMinimumCharacters_WithBackslash_23) {
    std::string input = "he\\llo";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_NE(std::string::npos, result.find("\\\\"));
}

TEST_F(ValueTest_23, EscapeAllCharacters_NoSpecial_23) {
    std::string input = "hello";
    std::string result = Value::escapeAllCharacters(input);
    // All ASCII letters should be escaped to unicode or kept as is
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_23, EscapeToUnicode_23) {
    std::string result = Value::escapeToUnicode('A');
    // Should produce a unicode escape sequence
    EXPECT_FALSE(result.empty());
    EXPECT_NE(std::string::npos, result.find("\\u"));
}

// ============================================================
// Boundary / Edge Case Tests
// ============================================================

TEST_F(ValueTest_23, EmptyString_23) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("", v.getString());
}

TEST_F(ValueTest_23, IntegerZero_23) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(0, v.getInteger());
}

TEST_F(ValueTest_23, IntegerNegative_23) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(-100, v.getInteger());
}

TEST_F(ValueTest_23, DoubleZero_23) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(0.0, v.getDouble());
}

TEST_F(ValueTest_23, DoubleNegative_23) {
    Value v(-3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(-3.14, v.getDouble());
}

TEST_F(ValueTest_23, EmptyObject_23) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v.getObject().empty());
}

TEST_F(ValueTest_23, EmptyArray_23) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v.getArray().empty());
}

TEST_F(ValueTest_23, ReassignDifferentTypes_23) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v = std::string("now a string");
    EXPECT_TRUE(v.isString());
    v = 3.14;
    EXPECT_TRUE(v.isDouble());
    v = true;
    EXPECT_TRUE(v.isBoolean());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_23, LoadFromString_Double_23) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_NEAR(3.14, v.getDouble(), 0.001);
}

TEST_F(ValueTest_23, LoadFromString_NegativeInt_23) {
    Value v;
    v.loadFromString("-42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(-42, v.getInteger());
}

TEST_F(ValueTest_23, LoadFromString_NestedObject_23) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": 1}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(1, v["outer"]["inner"].getInteger());
}

TEST_F(ValueTest_23, LoadFromString_NestedArray_23) {
    Value v;
    v.loadFromString("[[1, 2], [3, 4]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(2u, v.getArray().size());
}

TEST_F(ValueTest_23, StreamConstructor_23) {
    std::istringstream iss("\"from stream\"");
    Value v(iss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("from stream", v.getString());
}

TEST_F(ValueTest_23, EqualityOperator_NullVsString_23) {
    Value v1;
    Value v2("test");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_23, EqualityOperator_NullVsBool_23) {
    Value v1;
    Value v2(false);
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_23, OutputStream_23) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

TEST_F(ValueTest_23, LargeInteger_23) {
    Value v(2147483647);  // INT_MAX
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(2147483647, v.getInteger());
}

TEST_F(ValueTest_23, NegativeLargeInteger_23) {
    Value v(-2147483647);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(-2147483647, v.getInteger());
}

TEST_F(ValueTest_23, GetType_String_23) {
    Value v("test");
    EXPECT_EQ(Value::STRING, v.getType());
}

TEST_F(ValueTest_23, GetType_Integer_23) {
    Value v(5);
    EXPECT_EQ(Value::INTEGER, v.getType());
}

TEST_F(ValueTest_23, GetType_Double_23) {
    Value v(5.0);
    EXPECT_EQ(Value::DOUBLE, v.getType());
}

TEST_F(ValueTest_23, GetType_Object_23) {
    Value v(Object());
    EXPECT_EQ(Value::OBJECT, v.getType());
}

TEST_F(ValueTest_23, GetType_Array_23) {
    Value v(Array());
    EXPECT_EQ(Value::ARRAY, v.getType());
}

TEST_F(ValueTest_23, GetType_Boolean_23) {
    Value v(true);
    EXPECT_EQ(Value::BOOLEAN, v.getType());
}

TEST_F(ValueTest_23, GetType_Null_23) {
    Value v;
    EXPECT_EQ(Value::NULL_VALUE, v.getType());
}

TEST_F(ValueTest_23, SelfAssignment_23) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(42, v.getInteger());
}

TEST_F(ValueTest_23, WriteToStream_Null_23) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(std::string::npos, oss.str().find("null"));
}

TEST_F(ValueTest_23, WriteToStream_Boolean_23) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(std::string::npos, oss.str().find("true"));
}

TEST_F(ValueTest_23, WriteToStream_BooleanFalse_23) {
    Value v(false);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(std::string::npos, oss.str().find("false"));
}

TEST_F(ValueTest_23, WriteToStream_Array_23) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(std::string::npos, output.find("1"));
    EXPECT_NE(std::string::npos, output.find("2"));
    EXPECT_NE(std::string::npos, output.find("3"));
}

TEST_F(ValueTest_23, WriteToStream_EscapeAll_23) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, true);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTest_23, LoadFromString_EmptyString_23) {
    Value v;
    v.loadFromString("\"\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("", v.getString());
}

TEST_F(ValueTest_23, LoadFromString_EscapedQuote_23) {
    Value v;
    v.loadFromString("\"he\\\"llo\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("he\"llo", v.getString());
}

TEST_F(ValueTest_23, LoadFromString_EmptyObject_23) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v.getObject().empty());
}

TEST_F(ValueTest_23, LoadFromString_EmptyArray_23) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v.getArray().empty());
}
