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
class ValueTest_13 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Default Constructor Tests
// ============================================================
TEST_F(ValueTest_13, DefaultConstructor_IsNull_13) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_13, DefaultConstructor_TypeIsNullValue_13) {
    Value v;
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

// ============================================================
// String Constructor Tests
// ============================================================
TEST_F(ValueTest_13, StringConstructor_SetsString_13) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_13, CStringConstructor_SetsString_13) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_13, StringConstructor_EmptyString_13) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

// ============================================================
// Integer Constructor Tests
// ============================================================
TEST_F(ValueTest_13, IntConstructor_SetsInteger_13) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_13, IntConstructor_Zero_13) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_13, IntConstructor_Negative_13) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

// ============================================================
// Double Constructor Tests
// ============================================================
TEST_F(ValueTest_13, DoubleConstructor_SetsDouble_13) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_13, DoubleConstructor_Zero_13) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_13, DoubleConstructor_Negative_13) {
    Value v(-2.718);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -2.718);
}

// ============================================================
// Boolean Constructor Tests
// ============================================================
TEST_F(ValueTest_13, BoolConstructor_True_13) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_13, BoolConstructor_False_13) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

// ============================================================
// Object Constructor Tests
// ============================================================
TEST_F(ValueTest_13, ObjectConstructor_SetsObject_13) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_13, ObjectConstructor_Empty_13) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v.getObject().empty());
}

// ============================================================
// Array Constructor Tests
// ============================================================
TEST_F(ValueTest_13, ArrayConstructor_SetsArray_13) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_13, ArrayConstructor_Empty_13) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v.getArray().empty());
}

// ============================================================
// Copy Constructor Tests
// ============================================================
TEST_F(ValueTest_13, CopyConstructor_CopiesString_13) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "test");
}

TEST_F(ValueTest_13, CopyConstructor_CopiesInteger_13) {
    Value original(99);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 99);
}

TEST_F(ValueTest_13, CopyConstructor_CopiesNull_13) {
    Value original;
    Value copy(original);
    EXPECT_TRUE(copy.isNull());
}

// ============================================================
// Assignment Operator Tests
// ============================================================
TEST_F(ValueTest_13, AssignmentOperator_Value_13) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_13, AssignmentOperator_String_13) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_13, AssignmentOperator_CString_13) {
    Value v;
    v = "cstring";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "cstring");
}

TEST_F(ValueTest_13, AssignmentOperator_Int_13) {
    Value v;
    v = 123;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

TEST_F(ValueTest_13, AssignmentOperator_Double_13) {
    Value v;
    v = 1.5;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.5);
}

TEST_F(ValueTest_13, AssignmentOperator_Object_13) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_13, AssignmentOperator_Array_13) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_13, AssignmentOperator_Bool_13) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

// ============================================================
// Type Check Tests
// ============================================================
TEST_F(ValueTest_13, IsStringable_WhenString_13) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_13, IsNumeric_WhenInteger_13) {
    Value v(10);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_13, IsNumeric_WhenDouble_13) {
    Value v(1.5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_13, IsString_WhenNotString_13) {
    Value v(42);
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_13, IsInteger_WhenNotInteger_13) {
    Value v("hello");
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_13, IsDouble_WhenNotDouble_13) {
    Value v(42);
    EXPECT_FALSE(v.isDouble());
}

TEST_F(ValueTest_13, IsObject_WhenNotObject_13) {
    Value v(42);
    EXPECT_FALSE(v.isObject());
}

TEST_F(ValueTest_13, IsArray_WhenNotArray_13) {
    Value v(42);
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueTest_13, IsBoolean_WhenNotBoolean_13) {
    Value v(42);
    EXPECT_FALSE(v.isBoolean());
}

TEST_F(ValueTest_13, IsNull_WhenNotNull_13) {
    Value v(42);
    EXPECT_FALSE(v.isNull());
}

// ============================================================
// Setter Tests
// ============================================================
TEST_F(ValueTest_13, SetString_ChangesType_13) {
    Value v(42);
    v.setString("changed");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "changed");
}

TEST_F(ValueTest_13, SetInteger_ChangesType_13) {
    Value v("hello");
    v.setInteger(99);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_13, SetDouble_ChangesType_13) {
    Value v("hello");
    v.setDouble(2.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.5);
}

TEST_F(ValueTest_13, SetBoolean_ChangesType_13) {
    Value v(42);
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_13, SetNull_ChangesType_13) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_13, SetObject_ChangesType_13) {
    Value v(42);
    Object obj;
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_13, SetArray_ChangesType_13) {
    Value v(42);
    Array arr;
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
}

// ============================================================
// Getter Tests for Float
// ============================================================
TEST_F(ValueTest_13, GetFloat_ReturnsFloatFromDouble_13) {
    Value v(3.14);
    float f = v.getFloat();
    EXPECT_NEAR(f, 3.14f, 0.001f);
}

// ============================================================
// tryGet Tests
// ============================================================
TEST_F(ValueTest_13, TryGetString_ReturnsValueWhenString_13) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST_F(ValueTest_13, TryGetString_ReturnsDefaultWhenNotString_13) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_13, TryGetInteger_ReturnsValueWhenInteger_13) {
    Value v(42);
    EXPECT_EQ(v.tryGetInteger(0), 42);
}

TEST_F(ValueTest_13, TryGetInteger_ReturnsDefaultWhenNotInteger_13) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(0), 0);
}

TEST_F(ValueTest_13, TryGetDouble_ReturnsValueWhenDouble_13) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 3.14);
}

TEST_F(ValueTest_13, TryGetDouble_ReturnsDefaultWhenNotDouble_13) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 0.0);
}

TEST_F(ValueTest_13, TryGetFloat_ReturnsValueWhenDouble_13) {
    Value v(2.5);
    EXPECT_NEAR(v.tryGetFloat(0.0f), 2.5f, 0.001f);
}

TEST_F(ValueTest_13, TryGetFloat_ReturnsDefaultWhenNotDouble_13) {
    Value v("hello");
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.0f), 1.0f);
}

TEST_F(ValueTest_13, TryGetBoolean_ReturnsValueWhenBoolean_13) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_13, TryGetBoolean_ReturnsDefaultWhenNotBoolean_13) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ============================================================
// Comparison Operator Tests
// ============================================================
TEST_F(ValueTest_13, EqualityOperator_SameIntValues_13) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_13, EqualityOperator_DifferentIntValues_13) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_13, InequalityOperator_DifferentValues_13) {
    Value v1(42);
    Value v2(43);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_13, InequalityOperator_SameValues_13) {
    Value v1(42);
    Value v2(42);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueTest_13, LessThanOperator_Integers_13) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_13, LessThanOrEqualOperator_13) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_13, GreaterThanOperator_13) {
    Value v1(2);
    Value v2(1);
    EXPECT_TRUE(v1 > v2);
}

TEST_F(ValueTest_13, GreaterThanOrEqualOperator_13) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 >= v2);
}

TEST_F(ValueTest_13, EqualityOperator_SameStringValues_13) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_13, EqualityOperator_DifferentTypes_13) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_13, EqualityOperator_BothNull_13) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

// ============================================================
// Subscript Operator Tests
// ============================================================
TEST_F(ValueTest_13, SubscriptOperator_StringKey_OnObject_13) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST_F(ValueTest_13, SubscriptOperator_CStringKey_OnObject_13) {
    Object obj;
    obj["key"] = Value(42);
    Value v(obj);
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST_F(ValueTest_13, SubscriptOperator_Index_OnArray_13) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    Value v(arr);
    EXPECT_EQ(v[static_cast<size_t>(0)].getInteger(), 10);
    EXPECT_EQ(v[static_cast<size_t>(1)].getInteger(), 20);
}

// ============================================================
// escapeToUnicode Tests
// ============================================================
TEST_F(ValueTest_13, EscapeToUnicode_NullChar_13) {
    std::string result = Value::escapeToUnicode('\0');
    EXPECT_EQ(result, "\\u0000");
}

TEST_F(ValueTest_13, EscapeToUnicode_ControlChar_0x01_13) {
    std::string result = Value::escapeToUnicode('\x01');
    EXPECT_EQ(result, "\\u0001");
}

TEST_F(ValueTest_13, EscapeToUnicode_ControlChar_0x1f_13) {
    std::string result = Value::escapeToUnicode('\x1f');
    EXPECT_EQ(result, "\\u001f");
}

TEST_F(ValueTest_13, EscapeToUnicode_Tab_13) {
    std::string result = Value::escapeToUnicode('\t');
    // \t is 0x09
    EXPECT_EQ(result, "\\u0009");
}

TEST_F(ValueTest_13, EscapeToUnicode_Newline_13) {
    std::string result = Value::escapeToUnicode('\n');
    // \n is 0x0a
    EXPECT_EQ(result, "\\u000a");
}

TEST_F(ValueTest_13, EscapeToUnicode_NonControlChar_ReturnsEmpty_13) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_EQ(result, "");
}

TEST_F(ValueTest_13, EscapeToUnicode_SpaceChar_ReturnsEmpty_13) {
    // Space is 0x20, which is beyond 0x1f
    std::string result = Value::escapeToUnicode(' ');
    EXPECT_EQ(result, "");
}

TEST_F(ValueTest_13, EscapeToUnicode_PrintableChar_ReturnsEmpty_13) {
    std::string result = Value::escapeToUnicode('z');
    EXPECT_EQ(result, "");
}

// ============================================================
// escapeMinimumCharacters Tests
// ============================================================
TEST_F(ValueTest_13, EscapeMinimumCharacters_EmptyString_13) {
    std::string result = Value::escapeMinimumCharacters("");
    EXPECT_EQ(result, "");
}

TEST_F(ValueTest_13, EscapeMinimumCharacters_NoSpecialChars_13) {
    std::string result = Value::escapeMinimumCharacters("hello");
    EXPECT_EQ(result, "hello");
}

TEST_F(ValueTest_13, EscapeMinimumCharacters_Backslash_13) {
    std::string result = Value::escapeMinimumCharacters("\\");
    EXPECT_EQ(result, "\\\\");
}

TEST_F(ValueTest_13, EscapeMinimumCharacters_Quote_13) {
    std::string result = Value::escapeMinimumCharacters("\"");
    EXPECT_EQ(result, "\\\"");
}

TEST_F(ValueTest_13, EscapeMinimumCharacters_Newline_13) {
    std::string result = Value::escapeMinimumCharacters("\n");
    EXPECT_EQ(result, "\\n");
}

TEST_F(ValueTest_13, EscapeMinimumCharacters_Tab_13) {
    std::string result = Value::escapeMinimumCharacters("\t");
    EXPECT_EQ(result, "\\t");
}

// ============================================================
// escapeAllCharacters Tests
// ============================================================
TEST_F(ValueTest_13, EscapeAllCharacters_EmptyString_13) {
    std::string result = Value::escapeAllCharacters("");
    EXPECT_EQ(result, "");
}

TEST_F(ValueTest_13, EscapeAllCharacters_NoSpecialChars_13) {
    std::string result = Value::escapeAllCharacters("abc");
    // Should still escape non-ASCII or all special; plain ASCII letters stay
    EXPECT_EQ(result, "abc");
}

// ============================================================
// loadFromString Tests
// ============================================================
TEST_F(ValueTest_13, LoadFromString_Integer_13) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_13, LoadFromString_String_13) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_13, LoadFromString_Boolean_True_13) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_13, LoadFromString_Boolean_False_13) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_13, LoadFromString_Null_13) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_13, LoadFromString_Double_13) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_NEAR(v.getDouble(), 3.14, 0.001);
}

TEST_F(ValueTest_13, LoadFromString_Array_13) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_13, LoadFromString_Object_13) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_13, LoadFromString_NegativeInteger_13) {
    Value v;
    v.loadFromString("-10");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -10);
}

// ============================================================
// loadFromStream Tests
// ============================================================
TEST_F(ValueTest_13, LoadFromStream_Integer_13) {
    std::istringstream iss("42");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_13, LoadFromStream_Object_13) {
    std::istringstream iss("{\"a\": 1}");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isObject());
}

// ============================================================
// Stream Constructor Tests
// ============================================================
TEST_F(ValueTest_13, StreamConstructor_ParsesInt_13) {
    std::istringstream iss("100");
    Value v(iss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

// ============================================================
// writeToStream Tests
// ============================================================
TEST_F(ValueTest_13, WriteToStream_Integer_13) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "42");
}

TEST_F(ValueTest_13, WriteToStream_String_13) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "\"hello\"");
}

TEST_F(ValueTest_13, WriteToStream_BooleanTrue_13) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "true");
}

TEST_F(ValueTest_13, WriteToStream_BooleanFalse_13) {
    Value v(false);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "false");
}

TEST_F(ValueTest_13, WriteToStream_Null_13) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "null");
}

TEST_F(ValueTest_13, WriteToStream_EmptyArray_13) {
    Value v(Array());
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "[]");
}

TEST_F(ValueTest_13, WriteToStream_EmptyObject_13) {
    Value v(Object());
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "{}");
}

// ============================================================
// getToString Tests
// ============================================================
TEST_F(ValueTest_13, GetToString_FromString_13) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

TEST_F(ValueTest_13, GetToString_FromInteger_13) {
    Value v(42);
    EXPECT_EQ(v.getToString(), "42");
}

// ============================================================
// Operator<< Tests
// ============================================================
TEST_F(ValueTest_13, StreamInsertionOperator_13) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    // Should produce some output (at least the value)
    EXPECT_FALSE(oss.str().empty());
}

// ============================================================
// Complex / Nested Structure Tests
// ============================================================
TEST_F(ValueTest_13, NestedObjectAndArray_13) {
    Value v;
    v.loadFromString("{\"arr\": [1, 2, {\"nested\": true}]}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["arr"].isArray());
    EXPECT_EQ(v["arr"].getArray().size(), 3u);
}

TEST_F(ValueTest_13, OverwriteValue_IntToString_13) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v = "now a string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST_F(ValueTest_13, OverwriteValue_StringToNull_13) {
    Value v("hello");
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

// ============================================================
// Boundary: Large numbers
// ============================================================
TEST_F(ValueTest_13, LargeInteger_13) {
    Value v(2147483647); // INT_MAX
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST_F(ValueTest_13, NegativeLargeInteger_13) {
    Value v(-2147483647);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -2147483647);
}

TEST_F(ValueTest_13, VerySmallDouble_13) {
    Value v(1e-300);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1e-300);
}

TEST_F(ValueTest_13, VeryLargeDouble_13) {
    Value v(1e300);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1e300);
}

// ============================================================
// Roundtrip Tests (serialize then parse)
// ============================================================
TEST_F(ValueTest_13, Roundtrip_SimpleObject_13) {
    Value original;
    original.loadFromString("{\"a\": 1, \"b\": \"hello\", \"c\": true, \"d\": null}");
    
    std::ostringstream oss;
    original.writeToStream(oss, false, false);
    
    Value reparsed;
    reparsed.loadFromString(oss.str());
    
    EXPECT_TRUE(reparsed.isObject());
    EXPECT_EQ(reparsed["a"].getInteger(), 1);
    EXPECT_EQ(reparsed["b"].getString(), "hello");
    EXPECT_TRUE(reparsed["c"].getBoolean());
    EXPECT_TRUE(reparsed["d"].isNull());
}

TEST_F(ValueTest_13, Roundtrip_Array_13) {
    Value original;
    original.loadFromString("[1, 2.5, \"three\", false, null]");
    
    std::ostringstream oss;
    original.writeToStream(oss, false, false);
    
    Value reparsed;
    reparsed.loadFromString(oss.str());
    
    EXPECT_TRUE(reparsed.isArray());
    EXPECT_EQ(reparsed.getArray().size(), 5u);
}

// ============================================================
// Object subscript creates entry if not exists
// ============================================================
TEST_F(ValueTest_13, SubscriptOperator_CreatesEntry_13) {
    Object obj;
    Value v(obj);
    v["newkey"] = 42;
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["newkey"].getInteger(), 42);
}
