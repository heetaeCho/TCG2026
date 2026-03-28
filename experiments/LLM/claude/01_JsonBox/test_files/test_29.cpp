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
class ValueTest_29 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Construction Tests
// ============================================================

TEST_F(ValueTest_29, DefaultConstructor_IsNull_29) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(Value::NULL_VALUE, v.getType());
}

TEST_F(ValueTest_29, StringConstructor_29) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("hello", v.getString());
}

TEST_F(ValueTest_29, CStringConstructor_29) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("world", v.getString());
}

TEST_F(ValueTest_29, IntConstructor_29) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(42, v.getInteger());
}

TEST_F(ValueTest_29, DoubleConstructor_29) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(3.14, v.getDouble());
}

TEST_F(ValueTest_29, BoolConstructorTrue_29) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_29, BoolConstructorFalse_29) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_29, ObjectConstructor_29) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ("value", v.getObject().at("key").getString());
}

TEST_F(ValueTest_29, ArrayConstructor_29) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(2u, v.getArray().size());
}

TEST_F(ValueTest_29, CopyConstructor_29) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ("test", copy.getString());
}

TEST_F(ValueTest_29, CopyConstructorInt_29) {
    Value original(123);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(123, copy.getInteger());
}

TEST_F(ValueTest_29, CopyConstructorNull_29) {
    Value original;
    Value copy(original);
    EXPECT_TRUE(copy.isNull());
}

// ============================================================
// Assignment Operator Tests
// ============================================================

TEST_F(ValueTest_29, AssignmentFromValue_29) {
    Value v1("hello");
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isString());
    EXPECT_EQ("hello", v2.getString());
}

TEST_F(ValueTest_29, AssignmentFromString_29) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("assigned", v.getString());
}

TEST_F(ValueTest_29, AssignmentFromCString_29) {
    Value v;
    v = "cstring";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("cstring", v.getString());
}

TEST_F(ValueTest_29, AssignmentFromInt_29) {
    Value v;
    v = 99;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(99, v.getInteger());
}

TEST_F(ValueTest_29, AssignmentFromDouble_29) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(2.718, v.getDouble());
}

TEST_F(ValueTest_29, AssignmentFromObject_29) {
    Value v;
    Object obj;
    obj["x"] = Value(10);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_29, AssignmentFromArray_29) {
    Value v;
    Array arr;
    arr.push_back(Value("elem"));
    v = arr;
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(1u, v.getArray().size());
}

TEST_F(ValueTest_29, AssignmentFromBool_29) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

// ============================================================
// Operator[] Tests (the focus of the partial implementation)
// ============================================================

TEST_F(ValueTest_29, SubscriptStringOnNull_ConvertsToObject_29) {
    Value v;
    EXPECT_TRUE(v.isNull());
    v["key"] = Value("val");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ("val", v["key"].getString());
}

TEST_F(ValueTest_29, SubscriptStringOnExistingObject_29) {
    Object obj;
    obj["existing"] = Value(42);
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(42, v["existing"].getInteger());
}

TEST_F(ValueTest_29, SubscriptStringCreatesNewKey_29) {
    Value v;
    v["newkey"];
    EXPECT_TRUE(v.isObject());
    // Accessing a non-existent key should create a default entry
    EXPECT_TRUE(v["newkey"].isNull());
}

TEST_F(ValueTest_29, SubscriptCStringOnNull_ConvertsToObject_29) {
    Value v;
    const char* key = "ckey";
    v[key] = Value(100);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(100, v[key].getInteger());
}

TEST_F(ValueTest_29, SubscriptOnIntValue_ConvertsToObject_29) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v["key"] = Value("override");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ("override", v["key"].getString());
}

TEST_F(ValueTest_29, SubscriptOnStringValue_ConvertsToObject_29) {
    Value v("some string");
    EXPECT_TRUE(v.isString());
    v["key"] = Value(1);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_29, SubscriptOnBoolValue_ConvertsToObject_29) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    v["key"] = Value(false);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_29, SubscriptOnDoubleValue_ConvertsToObject_29) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    v["key"] = Value(2.5);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_29, SubscriptOnArrayValue_ConvertsToObject_29) {
    Array arr;
    arr.push_back(Value(1));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    v["key"] = Value("converted");
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_29, SubscriptMultipleKeys_29) {
    Value v;
    v["a"] = Value(1);
    v["b"] = Value(2);
    v["c"] = Value(3);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(1, v["a"].getInteger());
    EXPECT_EQ(2, v["b"].getInteger());
    EXPECT_EQ(3, v["c"].getInteger());
}

TEST_F(ValueTest_29, SubscriptSizeT_OnArray_29) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(10, v[(size_t)0].getInteger());
    EXPECT_EQ(20, v[(size_t)1].getInteger());
    EXPECT_EQ(30, v[(size_t)2].getInteger());
}

TEST_F(ValueTest_29, SubscriptEmptyKey_29) {
    Value v;
    v[""] = Value("empty key");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ("empty key", v[""].getString());
}

// ============================================================
// Type Checking Tests
// ============================================================

TEST_F(ValueTest_29, IsStringable_ForString_29) {
    Value v("test");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_29, IsNumeric_ForInt_29) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
}

TEST_F(ValueTest_29, IsNumeric_ForDouble_29) {
    Value v(3.14);
    EXPECT_TRUE(v.isNumeric());
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_29, TypeChecks_ForNull_29) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
}

TEST_F(ValueTest_29, TypeChecks_ForObject_29) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_FALSE(v.isNull());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueTest_29, TypeChecks_ForArray_29) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_FALSE(v.isNull());
    EXPECT_FALSE(v.isObject());
}

// ============================================================
// Comparison Operators Tests
// ============================================================

TEST_F(ValueTest_29, EqualityOperator_SameInt_29) {
    Value v1(10);
    Value v2(10);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueTest_29, EqualityOperator_DifferentInt_29) {
    Value v1(10);
    Value v2(20);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_29, EqualityOperator_SameString_29) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_29, EqualityOperator_DifferentString_29) {
    Value v1("abc");
    Value v2("xyz");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_29, EqualityOperator_DifferentTypes_29) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_29, LessThanOperator_Ints_29) {
    Value v1(5);
    Value v2(10);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_29, LessThanOrEqualOperator_29) {
    Value v1(5);
    Value v2(5);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_29, GreaterThanOperator_29) {
    Value v1(10);
    Value v2(5);
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v2 > v1);
}

TEST_F(ValueTest_29, GreaterThanOrEqualOperator_29) {
    Value v1(10);
    Value v2(10);
    EXPECT_TRUE(v1 >= v2);
}

TEST_F(ValueTest_29, NullValuesEqual_29) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_29, BooleanEquality_29) {
    Value v1(true);
    Value v2(true);
    Value v3(false);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}

// ============================================================
// Setters and Getters Tests
// ============================================================

TEST_F(ValueTest_29, SetString_29) {
    Value v;
    v.setString("newval");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("newval", v.getString());
}

TEST_F(ValueTest_29, SetInteger_29) {
    Value v;
    v.setInteger(55);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(55, v.getInteger());
}

TEST_F(ValueTest_29, SetDouble_29) {
    Value v;
    v.setDouble(1.23);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(1.23, v.getDouble());
}

TEST_F(ValueTest_29, SetBoolean_29) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_29, SetNull_29) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_29, SetObject_29) {
    Value v;
    Object obj;
    obj["k"] = Value("v");
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ("v", v.getObject().at("k").getString());
}

TEST_F(ValueTest_29, SetArray_29) {
    Value v;
    Array arr;
    arr.push_back(Value(100));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(1u, v.getArray().size());
    EXPECT_EQ(100, v.getArray()[0].getInteger());
}

// ============================================================
// tryGet Methods Tests
// ============================================================

TEST_F(ValueTest_29, TryGetString_WhenString_29) {
    Value v("actual");
    EXPECT_EQ("actual", v.tryGetString("default"));
}

TEST_F(ValueTest_29, TryGetString_WhenNotString_29) {
    Value v(42);
    EXPECT_EQ("default", v.tryGetString("default"));
}

TEST_F(ValueTest_29, TryGetInteger_WhenInteger_29) {
    Value v(7);
    EXPECT_EQ(7, v.tryGetInteger(0));
}

TEST_F(ValueTest_29, TryGetInteger_WhenNotInteger_29) {
    Value v("not int");
    EXPECT_EQ(-1, v.tryGetInteger(-1));
}

TEST_F(ValueTest_29, TryGetDouble_WhenDouble_29) {
    Value v(2.5);
    EXPECT_DOUBLE_EQ(2.5, v.tryGetDouble(0.0));
}

TEST_F(ValueTest_29, TryGetDouble_WhenNotDouble_29) {
    Value v("not double");
    EXPECT_DOUBLE_EQ(9.9, v.tryGetDouble(9.9));
}

TEST_F(ValueTest_29, TryGetFloat_WhenDouble_29) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(1.5f, v.tryGetFloat(0.0f));
}

TEST_F(ValueTest_29, TryGetFloat_WhenNotDouble_29) {
    Value v("str");
    EXPECT_FLOAT_EQ(3.0f, v.tryGetFloat(3.0f));
}

TEST_F(ValueTest_29, TryGetBoolean_WhenBoolean_29) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_29, TryGetBoolean_WhenNotBoolean_29) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ============================================================
// GetFloat Tests
// ============================================================

TEST_F(ValueTest_29, GetFloat_29) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(1.5f, v.getFloat());
}

// ============================================================
// Load and Write Tests
// ============================================================

TEST_F(ValueTest_29, LoadFromString_SimpleObject_29) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ("value", v["key"].getString());
}

TEST_F(ValueTest_29, LoadFromString_Integer_29) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(42, v.getInteger());
}

TEST_F(ValueTest_29, LoadFromString_Array_29) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(3u, v.getArray().size());
}

TEST_F(ValueTest_29, LoadFromString_String_29) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("hello", v.getString());
}

TEST_F(ValueTest_29, LoadFromString_Boolean_29) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_29, LoadFromString_Null_29) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_29, LoadFromString_Double_29) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(3.14, v.getDouble());
}

TEST_F(ValueTest_29, LoadFromStream_29) {
    Value v;
    std::istringstream iss("{\"a\": 1}");
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(1, v["a"].getInteger());
}

TEST_F(ValueTest_29, WriteToStream_29) {
    Value v;
    v.loadFromString("{\"key\":\"val\"}");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    // The output should contain "key" and "val"
    EXPECT_NE(std::string::npos, output.find("key"));
    EXPECT_NE(std::string::npos, output.find("val"));
}

TEST_F(ValueTest_29, WriteToStream_WithIndent_29) {
    Value v;
    v.loadFromString("{\"key\":\"val\"}");
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    // Indented output should contain newlines/tabs
    EXPECT_NE(std::string::npos, output.find("\n"));
}

TEST_F(ValueTest_29, StreamInsertionOperator_29) {
    Value v("test");
    std::ostringstream oss;
    oss << v;
    std::string output = oss.str();
    EXPECT_NE(std::string::npos, output.find("test"));
}

// ============================================================
// Constructor from istream
// ============================================================

TEST_F(ValueTest_29, StreamConstructor_29) {
    std::istringstream iss("{\"x\": 10}");
    Value v(iss);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(10, v["x"].getInteger());
}

// ============================================================
// getToString Tests
// ============================================================

TEST_F(ValueTest_29, GetToString_FromInt_29) {
    Value v(42);
    std::string s = v.getToString();
    EXPECT_EQ("42", s);
}

TEST_F(ValueTest_29, GetToString_FromString_29) {
    Value v("hello");
    std::string s = v.getToString();
    EXPECT_EQ("hello", s);
}

TEST_F(ValueTest_29, GetToString_FromDouble_29) {
    Value v(1.5);
    std::string s = v.getToString();
    EXPECT_FALSE(s.empty());
}

TEST_F(ValueTest_29, GetToString_FromBool_29) {
    Value v(true);
    std::string s = v.getToString();
    EXPECT_FALSE(s.empty());
}

// ============================================================
// Escape Functions Tests
// ============================================================

TEST_F(ValueTest_29, EscapeMinimumCharacters_NoSpecial_29) {
    std::string result = Value::escapeMinimumCharacters("hello");
    EXPECT_EQ("hello", result);
}

TEST_F(ValueTest_29, EscapeMinimumCharacters_WithQuote_29) {
    std::string result = Value::escapeMinimumCharacters("he\"llo");
    EXPECT_NE(std::string::npos, result.find("\\\""));
}

TEST_F(ValueTest_29, EscapeMinimumCharacters_WithBackslash_29) {
    std::string result = Value::escapeMinimumCharacters("he\\llo");
    EXPECT_NE(std::string::npos, result.find("\\\\"));
}

TEST_F(ValueTest_29, EscapeMinimumCharacters_WithNewline_29) {
    std::string result = Value::escapeMinimumCharacters("he\nllo");
    EXPECT_NE(std::string::npos, result.find("\\n"));
}

TEST_F(ValueTest_29, EscapeAllCharacters_NoSpecial_29) {
    std::string result = Value::escapeAllCharacters("hello");
    // All characters should be escaped to unicode
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_29, EscapeToUnicode_29) {
    std::string result = Value::escapeToUnicode('A');
    // Should contain \u0041
    EXPECT_NE(std::string::npos, result.find("\\u"));
}

TEST_F(ValueTest_29, EscapeMinimumCharacters_EmptyString_29) {
    std::string result = Value::escapeMinimumCharacters("");
    EXPECT_EQ("", result);
}

// ============================================================
// Edge Cases
// ============================================================

TEST_F(ValueTest_29, NegativeInteger_29) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(-100, v.getInteger());
}

TEST_F(ValueTest_29, ZeroInteger_29) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(0, v.getInteger());
}

TEST_F(ValueTest_29, NegativeDouble_29) {
    Value v(-3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(-3.14, v.getDouble());
}

TEST_F(ValueTest_29, EmptyString_29) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("", v.getString());
}

TEST_F(ValueTest_29, EmptyObject_29) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v.getObject().empty());
}

TEST_F(ValueTest_29, EmptyArray_29) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v.getArray().empty());
}

TEST_F(ValueTest_29, OverwriteType_IntToString_29) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setString("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("now a string", v.getString());
}

TEST_F(ValueTest_29, OverwriteType_StringToInt_29) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    v.setInteger(99);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(99, v.getInteger());
}

TEST_F(ValueTest_29, NestedObject_ViaSubscript_29) {
    Value v;
    v["outer"]["inner"] = Value("deep");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ("deep", v["outer"]["inner"].getString());
}

TEST_F(ValueTest_29, LoadFromString_NestedObject_29) {
    Value v;
    v.loadFromString("{\"a\": {\"b\": 5}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["a"].isObject());
    EXPECT_EQ(5, v["a"]["b"].getInteger());
}

TEST_F(ValueTest_29, LoadFromString_NestedArray_29) {
    Value v;
    v.loadFromString("[[1, 2], [3, 4]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(2u, v.getArray().size());
    EXPECT_TRUE(v.getArray()[0].isArray());
}

TEST_F(ValueTest_29, SelfAssignment_29) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(42, v.getInteger());
}

TEST_F(ValueTest_29, GetType_AllTypes_29) {
    Value vStr("s");
    EXPECT_EQ(Value::STRING, vStr.getType());

    Value vInt(1);
    EXPECT_EQ(Value::INTEGER, vInt.getType());

    Value vDbl(1.0);
    EXPECT_EQ(Value::DOUBLE, vDbl.getType());

    Object obj;
    Value vObj(obj);
    EXPECT_EQ(Value::OBJECT, vObj.getType());

    Array arr;
    Value vArr(arr);
    EXPECT_EQ(Value::ARRAY, vArr.getType());

    Value vBool(true);
    EXPECT_EQ(Value::BOOLEAN, vBool.getType());

    Value vNull;
    EXPECT_EQ(Value::NULL_VALUE, vNull.getType());
}

TEST_F(ValueTest_29, IsStringable_ForNonString_29) {
    Value v(42);
    // isStringable might return true for integer if it can be converted to string
    // We just check it doesn't crash and returns a bool
    bool result = v.isStringable();
    (void)result;
}

TEST_F(ValueTest_29, LoadFromString_NegativeNumber_29) {
    Value v;
    v.loadFromString("-42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(-42, v.getInteger());
}

TEST_F(ValueTest_29, LoadFromString_FalseBoolean_29) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_29, LoadFromString_EmptyObject_29) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v.getObject().empty());
}

TEST_F(ValueTest_29, LoadFromString_EmptyArray_29) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v.getArray().empty());
}

TEST_F(ValueTest_29, MultipleSubscriptOverwrites_29) {
    Value v;
    v["key"] = Value(1);
    EXPECT_EQ(1, v["key"].getInteger());
    v["key"] = Value(2);
    EXPECT_EQ(2, v["key"].getInteger());
}

TEST_F(ValueTest_29, WriteToStream_NullValue_29) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(std::string::npos, output.find("null"));
}

TEST_F(ValueTest_29, WriteToStream_BooleanTrue_29) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(std::string::npos, output.find("true"));
}

TEST_F(ValueTest_29, WriteToStream_BooleanFalse_29) {
    Value v(false);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(std::string::npos, output.find("false"));
}

TEST_F(ValueTest_29, WriteToStream_Integer_29) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(std::string::npos, output.find("42"));
}

TEST_F(ValueTest_29, WriteToStream_EscapeAll_29) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, true);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}
