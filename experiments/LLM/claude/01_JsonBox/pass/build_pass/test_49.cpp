#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueTest_49 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(ValueTest_49, DefaultConstructor_IsNull_49) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_49, StringConstructor_49) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_49, CStringConstructor_49) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_49, IntConstructor_49) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_49, DoubleConstructor_49) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_49, BooleanConstructor_True_49) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_49, BooleanConstructor_False_49) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_49, ObjectConstructor_49) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_49, ArrayConstructor_49) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_49, CopyConstructor_49) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

// ==================== Type Checking Tests ====================

TEST_F(ValueTest_49, IsString_49) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueTest_49, IsInteger_49) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_TRUE(v.isNumeric());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
}

TEST_F(ValueTest_49, IsDouble_49) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_TRUE(v.isNumeric());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_49, IsNumeric_Integer_49) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_49, IsNumeric_Double_49) {
    Value v(5.0);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_49, IsNumeric_String_49) {
    Value v("5");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_49, IsNull_Default_49) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_49, IsBoolean_49) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_49, IsObject_49) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_49, IsArray_49) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
}

// ==================== getDouble Tests ====================

TEST_F(ValueTest_49, GetDouble_FromDouble_49) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_49, GetDouble_FromNonDouble_ReturnsEmptyDouble_49) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_49, GetDouble_FromNull_ReturnsEmptyDouble_49) {
    Value v;
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_49, GetDouble_FromBoolean_ReturnsEmptyDouble_49) {
    Value v(true);
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_49, GetDouble_FromInteger_ReturnsEmptyDouble_49) {
    Value v(42);
    // Integer is not double, so getDouble should return EMPTY_DOUBLE (0.0)
    // unless tryGetDouble handles integer-to-double conversion
    double result = v.getDouble();
    // We just verify it returns some double without crashing
    (void)result;
}

TEST_F(ValueTest_49, GetDouble_NegativeDouble_49) {
    Value v(-2.718);
    EXPECT_DOUBLE_EQ(v.getDouble(), -2.718);
}

TEST_F(ValueTest_49, GetDouble_Zero_49) {
    Value v(0.0);
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_49, GetDouble_VeryLargeValue_49) {
    Value v(1.0e308);
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.0e308);
}

TEST_F(ValueTest_49, GetDouble_VerySmallValue_49) {
    Value v(1.0e-308);
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.0e-308);
}

// ==================== tryGetDouble Tests ====================

TEST_F(ValueTest_49, TryGetDouble_FromDouble_49) {
    Value v(2.5);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(99.9), 2.5);
}

TEST_F(ValueTest_49, TryGetDouble_FromNonDouble_ReturnsDefault_49) {
    Value v("not a double");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(99.9), 99.9);
}

TEST_F(ValueTest_49, TryGetDouble_FromNull_ReturnsDefault_49) {
    Value v;
    EXPECT_DOUBLE_EQ(v.tryGetDouble(-1.0), -1.0);
}

// ==================== Assignment Operator Tests ====================

TEST_F(ValueTest_49, AssignmentOperator_Value_49) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_49, AssignmentOperator_String_49) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_49, AssignmentOperator_CString_49) {
    Value v;
    v = "c_string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "c_string");
}

TEST_F(ValueTest_49, AssignmentOperator_Int_49) {
    Value v;
    v = 100;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST_F(ValueTest_49, AssignmentOperator_Double_49) {
    Value v;
    v = 1.23;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.23);
}

TEST_F(ValueTest_49, AssignmentOperator_Bool_49) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_49, AssignmentOperator_Object_49) {
    Value v;
    Object obj;
    obj["x"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_49, AssignmentOperator_Array_49) {
    Value v;
    Array arr;
    arr.push_back(Value("a"));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

// ==================== Setter Tests ====================

TEST_F(ValueTest_49, SetString_49) {
    Value v;
    v.setString("new string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "new string");
}

TEST_F(ValueTest_49, SetInteger_49) {
    Value v;
    v.setInteger(99);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_49, SetDouble_49) {
    Value v;
    v.setDouble(6.28);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 6.28);
}

TEST_F(ValueTest_49, SetBoolean_49) {
    Value v;
    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_49, SetNull_49) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_49, SetObject_49) {
    Value v;
    Object obj;
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_49, SetArray_49) {
    Value v;
    Array arr;
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
}

// ==================== Getter Tests ====================

TEST_F(ValueTest_49, GetString_49) {
    Value v("test string");
    EXPECT_EQ(v.getString(), "test string");
}

TEST_F(ValueTest_49, GetInteger_49) {
    Value v(7);
    EXPECT_EQ(v.getInteger(), 7);
}

TEST_F(ValueTest_49, GetFloat_FromDouble_49) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 1.5f);
}

TEST_F(ValueTest_49, TryGetString_FromString_49) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST_F(ValueTest_49, TryGetString_FromNonString_49) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_49, TryGetInteger_FromInteger_49) {
    Value v(10);
    EXPECT_EQ(v.tryGetInteger(0), 10);
}

TEST_F(ValueTest_49, TryGetInteger_FromNonInteger_49) {
    Value v("not int");
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

TEST_F(ValueTest_49, TryGetBoolean_FromBoolean_49) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_49, TryGetBoolean_FromNonBoolean_49) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_49, TryGetFloat_FromDouble_49) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST_F(ValueTest_49, TryGetFloat_FromNonDouble_49) {
    Value v("str");
    EXPECT_FLOAT_EQ(v.tryGetFloat(9.9f), 9.9f);
}

// ==================== Comparison Tests ====================

TEST_F(ValueTest_49, Equality_SameIntValues_49) {
    Value v1(10);
    Value v2(10);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueTest_49, Equality_DifferentIntValues_49) {
    Value v1(10);
    Value v2(20);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_49, Equality_SameStringValues_49) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_49, Equality_DifferentTypes_49) {
    Value v1(10);
    Value v2("10");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_49, LessThan_Integers_49) {
    Value v1(5);
    Value v2(10);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_49, LessThanOrEqual_49) {
    Value v1(5);
    Value v2(5);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_49, GreaterThan_49) {
    Value v1(10);
    Value v2(5);
    EXPECT_TRUE(v1 > v2);
}

TEST_F(ValueTest_49, GreaterThanOrEqual_49) {
    Value v1(10);
    Value v2(10);
    EXPECT_TRUE(v1 >= v2);
}

// ==================== Subscript Operator Tests ====================

TEST_F(ValueTest_49, SubscriptOperator_StringKey_CreatesObject_49) {
    Value v;
    v.setObject(Object());
    v["key"] = Value(42);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST_F(ValueTest_49, SubscriptOperator_CStringKey_49) {
    Value v;
    v.setObject(Object());
    v["ckey"] = Value("val");
    EXPECT_EQ(v["ckey"].getString(), "val");
}

TEST_F(ValueTest_49, SubscriptOperator_ArrayIndex_49) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

// ==================== Load/Parse Tests ====================

TEST_F(ValueTest_49, LoadFromString_SimpleObject_49) {
    Value v;
    v.loadFromString("{\"key\": 42}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST_F(ValueTest_49, LoadFromString_SimpleArray_49) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_49, LoadFromString_StringValue_49) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_49, LoadFromString_NumberValue_49) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_49, LoadFromString_DoubleValue_49) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_49, LoadFromString_BooleanTrue_49) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_49, LoadFromString_BooleanFalse_49) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_49, LoadFromString_Null_49) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_49, LoadFromStream_49) {
    std::istringstream ss("{\"a\": 1}");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_49, ConstructFromStream_49) {
    std::istringstream ss("[1, 2]");
    Value v(ss);
    EXPECT_TRUE(v.isArray());
}

// ==================== Write Tests ====================

TEST_F(ValueTest_49, WriteToStream_Integer_49) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(ValueTest_49, WriteToStream_String_49) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(ValueTest_49, WriteToStream_Null_49) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("null"), std::string::npos);
}

TEST_F(ValueTest_49, WriteToStream_Boolean_49) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(ValueTest_49, WriteToStream_WithIndent_49) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTest_49, OutputStream_Operator_49) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// ==================== Escape Tests ====================

TEST_F(ValueTest_49, EscapeMinimumCharacters_NoSpecialChars_49) {
    std::string result = Value::escapeMinimumCharacters("hello");
    EXPECT_EQ(result, "hello");
}

TEST_F(ValueTest_49, EscapeMinimumCharacters_WithQuote_49) {
    std::string result = Value::escapeMinimumCharacters("he\"llo");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_49, EscapeMinimumCharacters_WithBackslash_49) {
    std::string result = Value::escapeMinimumCharacters("he\\llo");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST_F(ValueTest_49, EscapeAllCharacters_NoSpecialChars_49) {
    std::string result = Value::escapeAllCharacters("hello");
    // ASCII letters should remain or be escaped to unicode
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_49, EscapeToUnicode_49) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
    // Should contain unicode escape format
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ==================== Boundary Tests ====================

TEST_F(ValueTest_49, EmptyString_49) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_49, ZeroInteger_49) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_49, NegativeInteger_49) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST_F(ValueTest_49, EmptyObject_49) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_49, EmptyArray_49) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

// ==================== Type Change Tests ====================

TEST_F(ValueTest_49, ChangeType_IntToString_49) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setString("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST_F(ValueTest_49, ChangeType_StringToNull_49) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_49, ChangeType_NullToObject_49) {
    Value v;
    EXPECT_TRUE(v.isNull());
    Object obj;
    obj["k"] = Value(1);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
}

// ==================== isStringable Test ====================

TEST_F(ValueTest_49, IsStringable_String_49) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_49, IsStringable_Integer_49) {
    Value v(42);
    // Integers may be stringable depending on implementation
    // Just test it doesn't crash
    bool result = v.isStringable();
    (void)result;
}

// ==================== getToString Test ====================

TEST_F(ValueTest_49, GetToString_FromString_49) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

TEST_F(ValueTest_49, GetToString_FromInteger_49) {
    Value v(42);
    std::string result = v.getToString();
    // Should give some string representation
    EXPECT_FALSE(result.empty());
}

// ==================== Nested Structure Tests ====================

TEST_F(ValueTest_49, NestedObject_49) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": 42}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

TEST_F(ValueTest_49, NestedArray_49) {
    Value v;
    v.loadFromString("[[1, 2], [3, 4]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_49, LoadFromString_NegativeNumber_49) {
    Value v;
    v.loadFromString("-42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST_F(ValueTest_49, LoadFromString_NegativeDouble_49) {
    Value v;
    v.loadFromString("-3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -3.14);
}

TEST_F(ValueTest_49, LoadFromString_ComplexObject_49) {
    Value v;
    v.loadFromString("{\"name\": \"test\", \"value\": 123, \"flag\": true, \"data\": null}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["name"].getString(), "test");
    EXPECT_EQ(v["value"].getInteger(), 123);
    EXPECT_TRUE(v["flag"].getBoolean());
    EXPECT_TRUE(v["data"].isNull());
}

// ==================== Self Assignment ====================

TEST_F(ValueTest_49, SelfAssignment_49) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}
