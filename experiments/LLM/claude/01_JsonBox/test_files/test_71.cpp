#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

// ==================== Construction Tests ====================

TEST(ValueTest_71, DefaultConstructor_IsNull_71) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST(ValueTest_71, StringConstructor_71) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueTest_71, CStringConstructor_71) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST(ValueTest_71, IntConstructor_71) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueTest_71, DoubleConstructor_71) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST(ValueTest_71, BoolConstructorTrue_71) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_71, BoolConstructorFalse_71) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueTest_71, ObjectConstructor_71) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST(ValueTest_71, ArrayConstructor_71) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST(ValueTest_71, CopyConstructor_71) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

TEST(ValueTest_71, StreamConstructor_71) {
    std::istringstream ss("\"hello\"");
    Value v(ss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

// ==================== Type Check Tests ====================

TEST(ValueTest_71, IsStringable_ForString_71) {
    Value v("test");
    EXPECT_TRUE(v.isStringable());
}

TEST(ValueTest_71, IsStringable_ForInt_71) {
    Value v(42);
    EXPECT_TRUE(v.isStringable());
}

TEST(ValueTest_71, IsStringable_ForDouble_71) {
    Value v(3.14);
    EXPECT_TRUE(v.isStringable());
}

TEST(ValueTest_71, IsNumeric_ForInt_71) {
    Value v(10);
    EXPECT_TRUE(v.isNumeric());
}

TEST(ValueTest_71, IsNumeric_ForDouble_71) {
    Value v(10.5);
    EXPECT_TRUE(v.isNumeric());
}

TEST(ValueTest_71, IsNumeric_ForString_71) {
    Value v("hello");
    EXPECT_FALSE(v.isNumeric());
}

TEST(ValueTest_71, IsNull_ForNull_71) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
}

// ==================== Assignment Operator Tests ====================

TEST(ValueTest_71, AssignString_71) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST(ValueTest_71, AssignCString_71) {
    Value v;
    v = "cstring";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "cstring");
}

TEST(ValueTest_71, AssignInt_71) {
    Value v;
    v = 99;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST(ValueTest_71, AssignDouble_71) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST(ValueTest_71, AssignBool_71) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_71, AssignObject_71) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST(ValueTest_71, AssignArray_71) {
    Value v;
    Array arr;
    arr.push_back(Value("item"));
    v = arr;
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

TEST(ValueTest_71, AssignValue_71) {
    Value v1(100);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 100);
}

// ==================== Setter/Getter Tests ====================

TEST(ValueTest_71, SetString_71) {
    Value v;
    v.setString("test_set");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test_set");
}

TEST(ValueTest_71, SetInteger_71) {
    Value v;
    v.setInteger(123);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

TEST(ValueTest_71, SetDouble_71) {
    Value v;
    v.setDouble(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.5);
}

TEST(ValueTest_71, SetBoolean_71) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_71, SetNull_71) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_71, SetObject_71) {
    Value v;
    Object obj;
    obj["x"] = Value(10);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST(ValueTest_71, SetArray_71) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    arr.push_back(Value(3));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST(ValueTest_71, GetFloat_71) {
    Value v(3.14);
    EXPECT_FLOAT_EQ(v.getFloat(), 3.14f);
}

// ==================== Try-Get Tests ====================

TEST(ValueTest_71, TryGetString_WhenString_71) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST(ValueTest_71, TryGetString_WhenNotString_71) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST(ValueTest_71, TryGetInteger_WhenInteger_71) {
    Value v(100);
    EXPECT_EQ(v.tryGetInteger(0), 100);
}

TEST(ValueTest_71, TryGetInteger_WhenNotInteger_71) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

TEST(ValueTest_71, TryGetDouble_WhenDouble_71) {
    Value v(2.5);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 2.5);
}

TEST(ValueTest_71, TryGetDouble_WhenNotDouble_71) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(9.9), 9.9);
}

TEST(ValueTest_71, TryGetFloat_WhenDouble_71) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 1.5f);
}

TEST(ValueTest_71, TryGetFloat_WhenNotDouble_71) {
    Value v("hello");
    EXPECT_FLOAT_EQ(v.tryGetFloat(7.7f), 7.7f);
}

TEST(ValueTest_71, TryGetBoolean_WhenBoolean_71) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST(ValueTest_71, TryGetBoolean_WhenNotBoolean_71) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ==================== GetToString Tests ====================

TEST(ValueTest_71, GetToString_FromString_71) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

TEST(ValueTest_71, GetToString_FromInt_71) {
    Value v(42);
    std::string result = v.getToString();
    EXPECT_EQ(result, "42");
}

TEST(ValueTest_71, GetToString_FromDouble_71) {
    Value v(3.5);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

// ==================== Comparison Operator Tests ====================

TEST(ValueTest_71, EqualityOperator_SameInt_71) {
    Value v1(10);
    Value v2(10);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST(ValueTest_71, EqualityOperator_DifferentInt_71) {
    Value v1(10);
    Value v2(20);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST(ValueTest_71, LessThanOperator_Ints_71) {
    Value v1(5);
    Value v2(10);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST(ValueTest_71, LessEqualOperator_71) {
    Value v1(5);
    Value v2(5);
    EXPECT_TRUE(v1 <= v2);
}

TEST(ValueTest_71, GreaterThanOperator_71) {
    Value v1(10);
    Value v2(5);
    EXPECT_TRUE(v1 > v2);
}

TEST(ValueTest_71, GreaterEqualOperator_71) {
    Value v1(10);
    Value v2(10);
    EXPECT_TRUE(v1 >= v2);
}

TEST(ValueTest_71, EqualityOperator_SameString_71) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueTest_71, EqualityOperator_DifferentTypes_71) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

TEST(ValueTest_71, EqualityOperator_NullValues_71) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueTest_71, EqualityOperator_BoolValues_71) {
    Value v1(true);
    Value v2(true);
    EXPECT_TRUE(v1 == v2);
}

// ==================== Subscript Operator Tests ====================

TEST(ValueTest_71, SubscriptString_OnObject_71) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST(ValueTest_71, SubscriptCString_OnObject_71) {
    Object obj;
    obj["name"] = Value("test");
    Value v(obj);
    EXPECT_EQ(v["name"].getString(), "test");
}

TEST(ValueTest_71, SubscriptIndex_OnArray_71) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[static_cast<size_t>(0)].getInteger(), 10);
    EXPECT_EQ(v[static_cast<size_t>(1)].getInteger(), 20);
    EXPECT_EQ(v[static_cast<size_t>(2)].getInteger(), 30);
}

// ==================== Load / Write Tests ====================

TEST(ValueTest_71, LoadFromString_Integer_71) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueTest_71, LoadFromString_Double_71) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST(ValueTest_71, LoadFromString_String_71) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueTest_71, LoadFromString_True_71) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_71, LoadFromString_False_71) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueTest_71, LoadFromString_Null_71) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_71, LoadFromString_EmptyObject_71) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST(ValueTest_71, LoadFromString_EmptyArray_71) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST(ValueTest_71, LoadFromString_Object_71) {
    Value v;
    v.loadFromString("{\"name\":\"test\",\"value\":42}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 2u);
}

TEST(ValueTest_71, LoadFromString_Array_71) {
    Value v;
    v.loadFromString("[1,2,3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST(ValueTest_71, LoadFromStream_71) {
    std::istringstream ss("{\"a\":1}");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isObject());
}

TEST(ValueTest_71, WriteToStream_NoIndent_71) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "42");
}

TEST(ValueTest_71, WriteToStream_String_71) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "\"hello\"");
}

TEST(ValueTest_71, WriteToStream_Null_71) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "null");
}

TEST(ValueTest_71, WriteToStream_Bool_71) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "true");
}

TEST(ValueTest_71, WriteToStream_BoolFalse_71) {
    Value v(false);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "false");
}

TEST(ValueTest_71, WriteToStream_Array_71) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string result = oss.str();
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("2"), std::string::npos);
}

TEST(ValueTest_71, WriteToStream_Object_71) {
    Object obj;
    obj["key"] = Value("val");
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string result = oss.str();
    EXPECT_NE(result.find("key"), std::string::npos);
    EXPECT_NE(result.find("val"), std::string::npos);
}

// ==================== Escape Tests ====================

TEST(ValueTest_71, EscapeMinimumCharacters_71) {
    std::string input = "hello\nworld";
    std::string escaped = Value::escapeMinimumCharacters(input);
    EXPECT_NE(escaped.find("\\n"), std::string::npos);
}

TEST(ValueTest_71, EscapeMinimumCharacters_Backslash_71) {
    std::string input = "back\\slash";
    std::string escaped = Value::escapeMinimumCharacters(input);
    EXPECT_NE(escaped.find("\\\\"), std::string::npos);
}

TEST(ValueTest_71, EscapeMinimumCharacters_Quote_71) {
    std::string input = "say\"hello\"";
    std::string escaped = Value::escapeMinimumCharacters(input);
    EXPECT_NE(escaped.find("\\\""), std::string::npos);
}

TEST(ValueTest_71, EscapeAllCharacters_71) {
    std::string input = "hello\nworld";
    std::string escaped = Value::escapeAllCharacters(input);
    EXPECT_NE(escaped.find("\\n"), std::string::npos);
}

TEST(ValueTest_71, EscapeToUnicode_71) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ==================== Boundary / Edge Cases ====================

TEST(ValueTest_71, IntegerZero_71) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST(ValueTest_71, NegativeInteger_71) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST(ValueTest_71, DoubleZero_71) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST(ValueTest_71, NegativeDouble_71) {
    Value v(-3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -3.14);
}

TEST(ValueTest_71, EmptyString_71) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST(ValueTest_71, EmptyObjectConstruct_71) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST(ValueTest_71, EmptyArrayConstruct_71) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

// ==================== Type Transition Tests ====================

TEST(ValueTest_71, ChangeType_IntToString_71) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setString("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST(ValueTest_71, ChangeType_StringToNull_71) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_71, ChangeType_NullToObject_71) {
    Value v;
    EXPECT_TRUE(v.isNull());
    Object obj;
    obj["k"] = Value(1);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
}

TEST(ValueTest_71, ChangeType_BoolToArray_71) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    Array arr;
    arr.push_back(Value(1));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
}

// ==================== Stream Operator Test ====================

TEST(ValueTest_71, StreamOutputOperator_71) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

// ==================== Nested Structures ====================

TEST(ValueTest_71, NestedObject_71) {
    Value v;
    v.loadFromString("{\"outer\":{\"inner\":42}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

TEST(ValueTest_71, NestedArray_71) {
    Value v;
    v.loadFromString("[[1,2],[3,4]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
    EXPECT_TRUE(v[static_cast<size_t>(0)].isArray());
}

TEST(ValueTest_71, LoadFromString_NegativeNumber_71) {
    Value v;
    v.loadFromString("-42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST(ValueTest_71, LoadFromString_NegativeDouble_71) {
    Value v;
    v.loadFromString("-3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -3.14);
}

TEST(ValueTest_71, LoadFromString_StringWithEscapes_71) {
    Value v;
    v.loadFromString("\"hello\\nworld\"");
    EXPECT_TRUE(v.isString());
    EXPECT_NE(v.getString().find('\n'), std::string::npos);
}

TEST(ValueTest_71, WriteToStreamIndented_71) {
    Object obj;
    obj["a"] = Value(1);
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string result = oss.str();
    // Indented output should contain newlines/tabs
    EXPECT_NE(result.find('\n'), std::string::npos);
}

TEST(ValueTest_71, WriteToStreamEscapeAll_71) {
    Value v("abc");
    std::ostringstream oss;
    v.writeToStream(oss, false, true);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// ==================== Self-assignment ====================

TEST(ValueTest_71, SelfAssignment_71) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

// ==================== Large Integer ====================

TEST(ValueTest_71, LargeInteger_71) {
    Value v(2147483647); // INT_MAX
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST(ValueTest_71, MinInteger_71) {
    Value v(-2147483647);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -2147483647);
}

// ==================== Mixed Array ====================

TEST(ValueTest_71, LoadMixedArray_71) {
    Value v;
    v.loadFromString("[1, \"two\", true, null, 3.14]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 5u);
    EXPECT_TRUE(v[static_cast<size_t>(0)].isInteger());
    EXPECT_TRUE(v[static_cast<size_t>(1)].isString());
    EXPECT_TRUE(v[static_cast<size_t>(2)].isBoolean());
    EXPECT_TRUE(v[static_cast<size_t>(3)].isNull());
    EXPECT_TRUE(v[static_cast<size_t>(4)].isDouble());
}

// ==================== Roundtrip Test ====================

TEST(ValueTest_71, Roundtrip_71) {
    std::string json = "{\"arr\":[1,2,3],\"bool\":true,\"null\":null,\"num\":42,\"str\":\"hello\"}";
    Value v;
    v.loadFromString(json);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    
    Value v2;
    v2.loadFromString(oss.str());
    EXPECT_TRUE(v2.isObject());
    EXPECT_EQ(v2["str"].getString(), "hello");
    EXPECT_EQ(v2["num"].getInteger(), 42);
    EXPECT_TRUE(v2["bool"].getBoolean());
    EXPECT_TRUE(v2["null"].isNull());
    EXPECT_EQ(v2["arr"].getArray().size(), 3u);
}
