#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

// ==================== Construction Tests ====================

TEST(ValueTest_14, DefaultConstructor_IsNull_14) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST(ValueTest_14, StringConstructor_14) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueTest_14, CStringConstructor_14) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST(ValueTest_14, IntConstructor_14) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueTest_14, DoubleConstructor_14) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST(ValueTest_14, BooleanConstructorTrue_14) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_14, BooleanConstructorFalse_14) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueTest_14, ObjectConstructor_14) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST(ValueTest_14, ArrayConstructor_14) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST(ValueTest_14, CopyConstructor_14) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

TEST(ValueTest_14, CopyConstructorString_14) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "test");
}

TEST(ValueTest_14, CopyConstructorNull_14) {
    Value original;
    Value copy(original);
    EXPECT_TRUE(copy.isNull());
}

// ==================== Assignment Operator Tests ====================

TEST(ValueTest_14, AssignmentFromValue_14) {
    Value v;
    Value src(100);
    v = src;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST(ValueTest_14, AssignmentFromString_14) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST(ValueTest_14, AssignmentFromCString_14) {
    Value v;
    v = "cstring";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "cstring");
}

TEST(ValueTest_14, AssignmentFromInt_14) {
    Value v;
    v = 55;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 55);
}

TEST(ValueTest_14, AssignmentFromDouble_14) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST(ValueTest_14, AssignmentFromObject_14) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST(ValueTest_14, AssignmentFromArray_14) {
    Value v;
    Array arr;
    arr.push_back(Value("item"));
    v = arr;
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

TEST(ValueTest_14, AssignmentFromBool_14) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_14, ReassignmentChangesType_14) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v = std::string("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

// ==================== Type Checking Tests ====================

TEST(ValueTest_14, IsStringable_String_14) {
    Value v("test");
    EXPECT_TRUE(v.isStringable());
}

TEST(ValueTest_14, IsStringable_Int_14) {
    Value v(42);
    EXPECT_TRUE(v.isStringable());
}

TEST(ValueTest_14, IsStringable_Double_14) {
    Value v(3.14);
    EXPECT_TRUE(v.isStringable());
}

TEST(ValueTest_14, IsStringable_Null_14) {
    Value v;
    EXPECT_FALSE(v.isStringable());
}

TEST(ValueTest_14, IsNumeric_Int_14) {
    Value v(10);
    EXPECT_TRUE(v.isNumeric());
}

TEST(ValueTest_14, IsNumeric_Double_14) {
    Value v(10.5);
    EXPECT_TRUE(v.isNumeric());
}

TEST(ValueTest_14, IsNumeric_String_14) {
    Value v("not a number");
    EXPECT_FALSE(v.isNumeric());
}

TEST(ValueTest_14, IsNotString_WhenInt_14) {
    Value v(42);
    EXPECT_FALSE(v.isString());
}

TEST(ValueTest_14, IsNotInt_WhenString_14) {
    Value v("hello");
    EXPECT_FALSE(v.isInteger());
}

TEST(ValueTest_14, IsNotDouble_WhenBool_14) {
    Value v(true);
    EXPECT_FALSE(v.isDouble());
}

TEST(ValueTest_14, IsNotObject_WhenArray_14) {
    Array arr;
    Value v(arr);
    EXPECT_FALSE(v.isObject());
}

TEST(ValueTest_14, IsNotArray_WhenObject_14) {
    Object obj;
    Value v(obj);
    EXPECT_FALSE(v.isArray());
}

TEST(ValueTest_14, IsNotBoolean_WhenNull_14) {
    Value v;
    EXPECT_FALSE(v.isBoolean());
}

// ==================== Getter/Setter Tests ====================

TEST(ValueTest_14, SetAndGetString_14) {
    Value v;
    v.setString("test string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test string");
}

TEST(ValueTest_14, SetAndGetInteger_14) {
    Value v;
    v.setInteger(999);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 999);
}

TEST(ValueTest_14, SetAndGetDouble_14) {
    Value v;
    v.setDouble(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.5);
}

TEST(ValueTest_14, SetAndGetBoolean_14) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_14, SetNull_14) {
    Value v(42);
    EXPECT_FALSE(v.isNull());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_14, SetAndGetObject_14) {
    Value v;
    Object obj;
    obj["x"] = Value(10);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST(ValueTest_14, SetAndGetArray_14) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    arr.push_back(Value(3));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST(ValueTest_14, GetFloat_14) {
    Value v(3.14);
    EXPECT_FLOAT_EQ(v.getFloat(), 3.14f);
}

// ==================== tryGet Tests ====================

TEST(ValueTest_14, TryGetString_WhenString_14) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST(ValueTest_14, TryGetString_WhenNotString_14) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST(ValueTest_14, TryGetInteger_WhenInteger_14) {
    Value v(42);
    EXPECT_EQ(v.tryGetInteger(0), 42);
}

TEST(ValueTest_14, TryGetInteger_WhenNotInteger_14) {
    Value v("not int");
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

TEST(ValueTest_14, TryGetDouble_WhenDouble_14) {
    Value v(2.5);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 2.5);
}

TEST(ValueTest_14, TryGetDouble_WhenNotDouble_14) {
    Value v("not double");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(9.9), 9.9);
}

TEST(ValueTest_14, TryGetFloat_WhenDouble_14) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST(ValueTest_14, TryGetFloat_WhenNotDouble_14) {
    Value v("not float");
    EXPECT_FLOAT_EQ(v.tryGetFloat(9.9f), 9.9f);
}

TEST(ValueTest_14, TryGetBoolean_WhenBoolean_14) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST(ValueTest_14, TryGetBoolean_WhenNotBoolean_14) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ==================== Comparison Operators ====================

TEST(ValueTest_14, EqualityOperator_SameInt_14) {
    Value a(42);
    Value b(42);
    EXPECT_TRUE(a == b);
}

TEST(ValueTest_14, EqualityOperator_DifferentInt_14) {
    Value a(42);
    Value b(43);
    EXPECT_FALSE(a == b);
}

TEST(ValueTest_14, InequalityOperator_14) {
    Value a(1);
    Value b(2);
    EXPECT_TRUE(a != b);
}

TEST(ValueTest_14, LessThanOperator_14) {
    Value a(1);
    Value b(2);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(ValueTest_14, LessThanOrEqualOperator_14) {
    Value a(1);
    Value b(1);
    EXPECT_TRUE(a <= b);
}

TEST(ValueTest_14, GreaterThanOperator_14) {
    Value a(5);
    Value b(3);
    EXPECT_TRUE(a > b);
}

TEST(ValueTest_14, GreaterThanOrEqualOperator_14) {
    Value a(5);
    Value b(5);
    EXPECT_TRUE(a >= b);
}

TEST(ValueTest_14, EqualityOperator_SameString_14) {
    Value a("hello");
    Value b("hello");
    EXPECT_TRUE(a == b);
}

TEST(ValueTest_14, EqualityOperator_DifferentTypes_14) {
    Value a(42);
    Value b("42");
    EXPECT_FALSE(a == b);
}

TEST(ValueTest_14, EqualityOperator_NullValues_14) {
    Value a;
    Value b;
    EXPECT_TRUE(a == b);
}

TEST(ValueTest_14, EqualityOperator_BoolValues_14) {
    Value a(true);
    Value b(true);
    EXPECT_TRUE(a == b);
    Value c(false);
    EXPECT_FALSE(a == c);
}

// ==================== Subscript Operators ====================

TEST(ValueTest_14, ObjectSubscript_String_14) {
    Value v;
    Object obj;
    obj["key1"] = Value("val1");
    v.setObject(obj);
    Value& ref = v["key1"];
    EXPECT_TRUE(ref.isString());
    EXPECT_EQ(ref.getString(), "val1");
}

TEST(ValueTest_14, ObjectSubscript_CString_14) {
    Value v;
    Object obj;
    obj["key2"] = Value(100);
    v.setObject(obj);
    Value& ref = v["key2"];
    EXPECT_TRUE(ref.isInteger());
    EXPECT_EQ(ref.getInteger(), 100);
}

TEST(ValueTest_14, ArraySubscript_14) {
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

TEST(ValueTest_14, ObjectSubscript_CreatesNewEntry_14) {
    Value v;
    Object obj;
    v.setObject(obj);
    v["newkey"] = Value("newvalue");
    EXPECT_EQ(v["newkey"].getString(), "newvalue");
}

// ==================== getToString Tests ====================

TEST(ValueTest_14, GetToString_FromString_14) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

TEST(ValueTest_14, GetToString_FromInt_14) {
    Value v(42);
    std::string result = v.getToString();
    EXPECT_EQ(result, "42");
}

TEST(ValueTest_14, GetToString_FromDouble_14) {
    Value v(3.5);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

// ==================== Serialization Tests ====================

TEST(ValueTest_14, WriteToStream_NullValue_14) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "null");
}

TEST(ValueTest_14, WriteToStream_IntValue_14) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "42");
}

TEST(ValueTest_14, WriteToStream_StringValue_14) {
    Value v("test");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "\"test\"");
}

TEST(ValueTest_14, WriteToStream_BoolTrue_14) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "true");
}

TEST(ValueTest_14, WriteToStream_BoolFalse_14) {
    Value v(false);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "false");
}

TEST(ValueTest_14, WriteToStream_EmptyObject_14) {
    Value v;
    Object obj;
    v.setObject(obj);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "{}");
}

TEST(ValueTest_14, WriteToStream_EmptyArray_14) {
    Value v;
    Array arr;
    v.setArray(arr);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "[]");
}

TEST(ValueTest_14, WriteToStream_DoubleValue_14) {
    Value v(3.14);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// ==================== Parsing Tests ====================

TEST(ValueTest_14, LoadFromString_Null_14) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_14, LoadFromString_Integer_14) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueTest_14, LoadFromString_NegativeInteger_14) {
    Value v;
    v.loadFromString("-10");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -10);
}

TEST(ValueTest_14, LoadFromString_Double_14) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST(ValueTest_14, LoadFromString_String_14) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueTest_14, LoadFromString_True_14) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_14, LoadFromString_False_14) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueTest_14, LoadFromString_EmptyObject_14) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST(ValueTest_14, LoadFromString_EmptyArray_14) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST(ValueTest_14, LoadFromString_SimpleObject_14) {
    Value v;
    v.loadFromString("{\"key\":\"value\"}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST(ValueTest_14, LoadFromString_SimpleArray_14) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST(ValueTest_14, LoadFromStream_14) {
    std::istringstream iss("{\"name\":\"test\",\"value\":42}");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isObject());
}

TEST(ValueTest_14, StreamConstructor_14) {
    std::istringstream iss("\"stream test\"");
    Value v(iss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "stream test");
}

// ==================== Nested Structures ====================

TEST(ValueTest_14, NestedObjectArray_14) {
    Value v;
    v.loadFromString("{\"arr\":[1,2,3],\"obj\":{\"a\":1}}");
    EXPECT_TRUE(v.isObject());
    const Object& obj = v.getObject();
    EXPECT_EQ(obj.size(), 2u);
}

TEST(ValueTest_14, ArrayOfObjects_14) {
    Value v;
    v.loadFromString("[{\"a\":1},{\"b\":2}]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

// ==================== Escape Function Tests ====================

TEST(ValueTest_14, EscapeMinimumCharacters_NoEscape_14) {
    std::string input = "hello world";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ(result, "hello world");
}

TEST(ValueTest_14, EscapeMinimumCharacters_WithSpecialChars_14) {
    std::string input = "hello\nworld";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_NE(result, input);
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST(ValueTest_14, EscapeMinimumCharacters_Backslash_14) {
    std::string input = "back\\slash";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST(ValueTest_14, EscapeMinimumCharacters_Quote_14) {
    std::string input = "say \"hi\"";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST(ValueTest_14, EscapeAllCharacters_14) {
    std::string input = "hello";
    std::string result = Value::escapeAllCharacters(input);
    // All characters should be escaped to unicode
    EXPECT_FALSE(result.empty());
}

TEST(ValueTest_14, EscapeToUnicode_14) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
    // Should contain \u prefix
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ==================== Boundary Tests ====================

TEST(ValueTest_14, IntegerBoundary_Zero_14) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST(ValueTest_14, IntegerBoundary_Negative_14) {
    Value v(-1);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -1);
}

TEST(ValueTest_14, IntegerBoundary_Large_14) {
    Value v(2147483647);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST(ValueTest_14, DoubleBoundary_Zero_14) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST(ValueTest_14, EmptyStringValue_14) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST(ValueTest_14, EmptyObject_14) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST(ValueTest_14, EmptyArray_14) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

// ==================== Serialization Round-Trip Tests ====================

TEST(ValueTest_14, RoundTrip_SimpleObject_14) {
    Value v;
    v.loadFromString("{\"a\":1,\"b\":\"two\",\"c\":true,\"d\":null}");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    Value v2;
    v2.loadFromString(oss.str());
    EXPECT_TRUE(v2.isObject());
    EXPECT_EQ(v2.getObject().size(), 4u);
}

TEST(ValueTest_14, RoundTrip_Array_14) {
    Value v;
    v.loadFromString("[1,2.5,\"three\",true,null]");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    Value v2;
    v2.loadFromString(oss.str());
    EXPECT_TRUE(v2.isArray());
    EXPECT_EQ(v2.getArray().size(), 5u);
}

// ==================== Stream Insertion Operator ====================

TEST(ValueTest_14, StreamInsertionOperator_14) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// ==================== Self Assignment ====================

TEST(ValueTest_14, SelfAssignment_14) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

// ==================== Overwrite Type ====================

TEST(ValueTest_14, OverwriteIntWithString_14) {
    Value v(42);
    v.setString("now string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now string");
    EXPECT_FALSE(v.isInteger());
}

TEST(ValueTest_14, OverwriteStringWithNull_14) {
    Value v("hello");
    v.setNull();
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isString());
}

TEST(ValueTest_14, OverwriteObjectWithArray_14) {
    Object obj;
    obj["key"] = Value(1);
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    Array arr;
    arr.push_back(Value(1));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_FALSE(v.isObject());
}

// ==================== String with special JSON characters ====================

TEST(ValueTest_14, LoadFromString_StringWithEscapes_14) {
    Value v;
    v.loadFromString("\"hello\\nworld\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello\nworld");
}

TEST(ValueTest_14, LoadFromString_StringWithTab_14) {
    Value v;
    v.loadFromString("\"hello\\tworld\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello\tworld");
}

TEST(ValueTest_14, LoadFromString_StringWithUnicode_14) {
    Value v;
    v.loadFromString("\"\\u0041\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "A");
}

// ==================== WriteToStream with indent ====================

TEST(ValueTest_14, WriteToStream_WithIndent_14) {
    Value v;
    v.loadFromString("{\"key\":\"value\"}");
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
    // Indented output should contain newlines
    EXPECT_NE(result.find('\n'), std::string::npos);
}

TEST(ValueTest_14, WriteToStream_WithEscapeAll_14) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, true);
    std::string result = oss.str();
    // With escapeAll, characters should be unicode escaped
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ==================== Large/Complex JSON ====================

TEST(ValueTest_14, LoadFromString_NestedArrays_14) {
    Value v;
    v.loadFromString("[[1,2],[3,[4,5]]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST(ValueTest_14, LoadFromString_MixedTypes_14) {
    Value v;
    v.loadFromString("{\"int\":1,\"double\":1.5,\"string\":\"s\",\"bool\":true,\"null\":null,\"arr\":[],\"obj\":{}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 7u);
}
