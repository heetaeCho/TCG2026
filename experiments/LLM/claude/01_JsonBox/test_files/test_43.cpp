#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

// =====================================================
// Test Fixture
// =====================================================
class ValueTest_43 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// =====================================================
// Constructor Tests
// =====================================================

TEST_F(ValueTest_43, DefaultConstructorCreatesNullValue_43) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_43, StringConstructor_43) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
    EXPECT_EQ(v.getType(), Value::STRING);
}

TEST_F(ValueTest_43, CStringConstructor_43) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_43, IntConstructor_43) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
    EXPECT_EQ(v.getType(), Value::INTEGER);
}

TEST_F(ValueTest_43, DoubleConstructor_43) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
    EXPECT_EQ(v.getType(), Value::DOUBLE);
}

TEST_F(ValueTest_43, BooleanConstructor_43) {
    Value vTrue(true);
    EXPECT_TRUE(vTrue.isBoolean());
    EXPECT_TRUE(vTrue.getBoolean());

    Value vFalse(false);
    EXPECT_TRUE(vFalse.isBoolean());
    EXPECT_FALSE(vFalse.getBoolean());
}

TEST_F(ValueTest_43, ObjectConstructor_43) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getType(), Value::OBJECT);
}

TEST_F(ValueTest_43, ArrayConstructor_43) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getType(), Value::ARRAY);
}

TEST_F(ValueTest_43, CopyConstructor_43) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "test");
}

TEST_F(ValueTest_43, CopyConstructorInt_43) {
    Value original(123);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 123);
}

TEST_F(ValueTest_43, CopyConstructorNull_43) {
    Value original;
    Value copy(original);
    EXPECT_TRUE(copy.isNull());
}

// =====================================================
// tryGetString Tests (the focus function)
// =====================================================

TEST_F(ValueTest_43, TryGetStringReturnsStringWhenTypeIsString_43) {
    Value v("hello");
    std::string defaultVal = "default";
    EXPECT_EQ(v.tryGetString(defaultVal), "hello");
}

TEST_F(ValueTest_43, TryGetStringReturnsDefaultWhenTypeIsInt_43) {
    Value v(42);
    std::string defaultVal = "default";
    EXPECT_EQ(v.tryGetString(defaultVal), "default");
}

TEST_F(ValueTest_43, TryGetStringReturnsDefaultWhenTypeIsDouble_43) {
    Value v(3.14);
    std::string defaultVal = "fallback";
    EXPECT_EQ(v.tryGetString(defaultVal), "fallback");
}

TEST_F(ValueTest_43, TryGetStringReturnsDefaultWhenTypeIsNull_43) {
    Value v;
    std::string defaultVal = "null_default";
    EXPECT_EQ(v.tryGetString(defaultVal), "null_default");
}

TEST_F(ValueTest_43, TryGetStringReturnsDefaultWhenTypeIsBoolean_43) {
    Value v(true);
    std::string defaultVal = "bool_default";
    EXPECT_EQ(v.tryGetString(defaultVal), "bool_default");
}

TEST_F(ValueTest_43, TryGetStringReturnsDefaultWhenTypeIsObject_43) {
    Object obj;
    Value v(obj);
    std::string defaultVal = "obj_default";
    EXPECT_EQ(v.tryGetString(defaultVal), "obj_default");
}

TEST_F(ValueTest_43, TryGetStringReturnsDefaultWhenTypeIsArray_43) {
    Array arr;
    Value v(arr);
    std::string defaultVal = "arr_default";
    EXPECT_EQ(v.tryGetString(defaultVal), "arr_default");
}

TEST_F(ValueTest_43, TryGetStringEmptyStringValue_43) {
    Value v(std::string(""));
    std::string defaultVal = "default";
    EXPECT_EQ(v.tryGetString(defaultVal), "");
}

TEST_F(ValueTest_43, TryGetStringEmptyDefault_43) {
    Value v(42);
    std::string defaultVal = "";
    EXPECT_EQ(v.tryGetString(defaultVal), "");
}

TEST_F(ValueTest_43, TryGetStringReturnsReferenceToActualString_43) {
    Value v("actual_value");
    std::string defaultVal = "default";
    const std::string &result = v.tryGetString(defaultVal);
    EXPECT_EQ(result, "actual_value");
}

TEST_F(ValueTest_43, TryGetStringReturnsReferenceToDefault_43) {
    Value v(100);
    std::string defaultVal = "my_default";
    const std::string &result = v.tryGetString(defaultVal);
    EXPECT_EQ(&result, &defaultVal);
}

// =====================================================
// Type Checking Tests
// =====================================================

TEST_F(ValueTest_43, IsStringReturnsTrueForString_43) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_43, IsIntegerReturnsTrueForInt_43) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_43, IsDoubleReturnsTrueForDouble_43) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_43, IsNumericForInteger_43) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_43, IsNumericForDouble_43) {
    Value v(5.0);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_43, IsNumericFalseForString_43) {
    Value v("123");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_43, IsBooleanReturnsTrueForBool_43) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_43, IsNullReturnsTrueForDefault_43) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_43, IsObjectReturnsTrueForObject_43) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_43, IsArrayReturnsTrueForArray_43) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
}

// =====================================================
// Assignment Operator Tests
// =====================================================

TEST_F(ValueTest_43, AssignmentFromString_43) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_43, AssignmentFromCString_43) {
    Value v;
    v = "cstring";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "cstring");
}

TEST_F(ValueTest_43, AssignmentFromInt_43) {
    Value v;
    v = 99;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_43, AssignmentFromDouble_43) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_43, AssignmentFromBool_43) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_43, AssignmentFromObject_43) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_43, AssignmentFromArray_43) {
    Value v;
    Array arr;
    arr.push_back(Value("item"));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_43, AssignmentFromValue_43) {
    Value v1("original");
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isString());
    EXPECT_EQ(v2.getString(), "original");
}

// =====================================================
// Setter/Getter Tests
// =====================================================

TEST_F(ValueTest_43, SetStringChangesType_43) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setString("now_string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now_string");
}

TEST_F(ValueTest_43, SetIntegerChangesType_43) {
    Value v("hello");
    v.setInteger(100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST_F(ValueTest_43, SetDoubleChangesType_43) {
    Value v;
    v.setDouble(1.23);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.23);
}

TEST_F(ValueTest_43, SetBooleanChangesType_43) {
    Value v("str");
    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_43, SetNullChangesType_43) {
    Value v("not null");
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_43, SetObjectChangesType_43) {
    Value v(42);
    Object obj;
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_43, SetArrayChangesType_43) {
    Value v(42);
    Array arr;
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
}

// =====================================================
// tryGet* Methods Tests
// =====================================================

TEST_F(ValueTest_43, TryGetIntegerReturnsValueWhenInteger_43) {
    Value v(55);
    EXPECT_EQ(v.tryGetInteger(0), 55);
}

TEST_F(ValueTest_43, TryGetIntegerReturnsDefaultWhenNotInteger_43) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

TEST_F(ValueTest_43, TryGetDoubleReturnsValueWhenDouble_43) {
    Value v(2.5);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 2.5);
}

TEST_F(ValueTest_43, TryGetDoubleReturnsDefaultWhenNotDouble_43) {
    Value v("str");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(9.9), 9.9);
}

TEST_F(ValueTest_43, TryGetFloatReturnsValueWhenDouble_43) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 1.5f);
}

TEST_F(ValueTest_43, TryGetFloatReturnsDefaultWhenNotDouble_43) {
    Value v(42);
    EXPECT_FLOAT_EQ(v.tryGetFloat(7.7f), 7.7f);
}

TEST_F(ValueTest_43, TryGetBooleanReturnsValueWhenBoolean_43) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_43, TryGetBooleanReturnsDefaultWhenNotBoolean_43) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// =====================================================
// Comparison Operator Tests
// =====================================================

TEST_F(ValueTest_43, EqualityOperatorSameIntValues_43) {
    Value v1(10);
    Value v2(10);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueTest_43, EqualityOperatorDifferentIntValues_43) {
    Value v1(10);
    Value v2(20);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_43, EqualityOperatorSameStringValues_43) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_43, EqualityOperatorDifferentTypes_43) {
    Value v1(10);
    Value v2("10");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_43, LessThanOperatorIntegers_43) {
    Value v1(5);
    Value v2(10);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_43, LessThanOrEqualOperator_43) {
    Value v1(5);
    Value v2(5);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_43, GreaterThanOperator_43) {
    Value v1(20);
    Value v2(10);
    EXPECT_TRUE(v1 > v2);
}

TEST_F(ValueTest_43, GreaterThanOrEqualOperator_43) {
    Value v1(10);
    Value v2(10);
    EXPECT_TRUE(v1 >= v2);
}

// =====================================================
// Subscript Operator Tests
// =====================================================

TEST_F(ValueTest_43, SubscriptOperatorStringKey_43) {
    Object obj;
    obj["key1"] = Value("val1");
    Value v(obj);
    EXPECT_EQ(v["key1"].getString(), "val1");
}

TEST_F(ValueTest_43, SubscriptOperatorCStringKey_43) {
    Object obj;
    obj["mykey"] = Value(42);
    Value v(obj);
    EXPECT_EQ(v["mykey"].getInteger(), 42);
}

TEST_F(ValueTest_43, SubscriptOperatorArrayIndex_43) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

// =====================================================
// getToString / isStringable Tests
// =====================================================

TEST_F(ValueTest_43, GetToStringFromString_43) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

TEST_F(ValueTest_43, IsStringableForString_43) {
    Value v("test");
    EXPECT_TRUE(v.isStringable());
}

// =====================================================
// Serialization / Deserialization Tests
// =====================================================

TEST_F(ValueTest_43, LoadFromStringSimpleObject_43) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST_F(ValueTest_43, LoadFromStringSimpleArray_43) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    const Array &arr = v.getArray();
    EXPECT_EQ(arr.size(), 3u);
}

TEST_F(ValueTest_43, LoadFromStringInteger_43) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_43, LoadFromStringDouble_43) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_43, LoadFromStringBoolean_43) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_43, LoadFromStringNull_43) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_43, LoadFromStream_43) {
    std::istringstream ss("{\"x\": 10}");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["x"].getInteger(), 10);
}

TEST_F(ValueTest_43, StreamConstructor_43) {
    std::istringstream ss("{\"name\": \"test\"}");
    Value v(ss);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["name"].getString(), "test");
}

TEST_F(ValueTest_43, WriteToStreamNoIndent_43) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTest_43, WriteToStreamWithIndent_43) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// =====================================================
// Boundary and Edge Cases
// =====================================================

TEST_F(ValueTest_43, IntegerZero_43) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
    EXPECT_EQ(v.tryGetInteger(99), 0);
}

TEST_F(ValueTest_43, NegativeInteger_43) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST_F(ValueTest_43, DoubleZero_43) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_43, EmptyString_43) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_43, EmptyObject_43) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v.getObject().empty());
}

TEST_F(ValueTest_43, EmptyArray_43) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v.getArray().empty());
}

TEST_F(ValueTest_43, LargeNestedObject_43) {
    Value v;
    v.loadFromString("{\"a\": {\"b\": {\"c\": 42}}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["a"]["b"]["c"].getInteger(), 42);
}

TEST_F(ValueTest_43, ArrayWithMixedTypes_43) {
    Value v;
    v.loadFromString("[1, \"two\", true, null, 3.14]");
    EXPECT_TRUE(v.isArray());
    const Array &arr = v.getArray();
    EXPECT_EQ(arr.size(), 5u);
    EXPECT_TRUE(arr[0].isInteger());
    EXPECT_TRUE(arr[1].isString());
    EXPECT_TRUE(arr[2].isBoolean());
    EXPECT_TRUE(arr[3].isNull());
    EXPECT_TRUE(arr[4].isDouble());
}

// =====================================================
// Escape Functions Tests
// =====================================================

TEST_F(ValueTest_43, EscapeMinimumCharactersBasic_43) {
    std::string result = Value::escapeMinimumCharacters("hello");
    EXPECT_EQ(result, "hello");
}

TEST_F(ValueTest_43, EscapeMinimumCharactersWithQuotes_43) {
    std::string result = Value::escapeMinimumCharacters("he\"llo");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_43, EscapeAllCharactersBasic_43) {
    std::string result = Value::escapeAllCharacters("hello");
    // All characters should be escaped to unicode
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_43, EscapeToUnicodeChar_43) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
    // Should contain \u prefix
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// =====================================================
// Reassignment changes type
// =====================================================

TEST_F(ValueTest_43, ReassignFromStringToInt_43) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    v = 42;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_43, ReassignFromIntToNull_43) {
    Value v(99);
    EXPECT_TRUE(v.isInteger());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_43, ReassignMultipleTimes_43) {
    Value v;
    EXPECT_TRUE(v.isNull());
    v = "string";
    EXPECT_TRUE(v.isString());
    v = 42;
    EXPECT_TRUE(v.isInteger());
    v = 3.14;
    EXPECT_TRUE(v.isDouble());
    v = true;
    EXPECT_TRUE(v.isBoolean());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

// =====================================================
// getFloat tests
// =====================================================

TEST_F(ValueTest_43, GetFloatReturnsFloatValue_43) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 2.5f);
}

// =====================================================
// Output stream operator test
// =====================================================

TEST_F(ValueTest_43, OutputStreamOperator_43) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

TEST_F(ValueTest_43, TryGetStringWithSpecialChars_43) {
    Value v(std::string("line1\nline2\ttab"));
    std::string defaultVal = "default";
    EXPECT_EQ(v.tryGetString(defaultVal), "line1\nline2\ttab");
}

TEST_F(ValueTest_43, TryGetStringWithUnicodeContent_43) {
    Value v(std::string("héllo wörld"));
    std::string defaultVal = "default";
    EXPECT_EQ(v.tryGetString(defaultVal), "héllo wörld");
}

TEST_F(ValueTest_43, LoadFromStringWithEscapedCharacters_43) {
    Value v;
    v.loadFromString("\"hello\\nworld\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello\nworld");
}
