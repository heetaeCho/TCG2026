#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

// ===== Construction Tests =====

TEST(ValueTest_62, DefaultConstructorCreatesNull_62) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST(ValueTest_62, StringConstructor_62) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueTest_62, CStringConstructor_62) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST(ValueTest_62, IntConstructor_62) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueTest_62, DoubleConstructor_62) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST(ValueTest_62, BooleanConstructorTrue_62) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_62, BooleanConstructorFalse_62) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueTest_62, ObjectConstructor_62) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST(ValueTest_62, ArrayConstructor_62) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST(ValueTest_62, CopyConstructor_62) {
    Value original(123);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 123);
}

// ===== Type Checking Tests =====

TEST(ValueTest_62, IsStringForString_62) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
}

TEST(ValueTest_62, IsIntegerForInt_62) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_TRUE(v.isNumeric());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
}

TEST(ValueTest_62, IsDoubleForDouble_62) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_TRUE(v.isNumeric());
    EXPECT_FALSE(v.isInteger());
}

TEST(ValueTest_62, IsNumericForInt_62) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST(ValueTest_62, IsNumericForDouble_62) {
    Value v(5.5);
    EXPECT_TRUE(v.isNumeric());
}

TEST(ValueTest_62, IsNullForDefault_62) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isNumeric());
    EXPECT_FALSE(v.isString());
}

// ===== Assignment Operator Tests =====

TEST(ValueTest_62, AssignmentFromValue_62) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST(ValueTest_62, AssignmentFromString_62) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST(ValueTest_62, AssignmentFromCString_62) {
    Value v;
    v = "cstring";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "cstring");
}

TEST(ValueTest_62, AssignmentFromInt_62) {
    Value v;
    v = 99;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST(ValueTest_62, AssignmentFromDouble_62) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST(ValueTest_62, AssignmentFromBool_62) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_62, AssignmentFromObject_62) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST(ValueTest_62, AssignmentFromArray_62) {
    Value v;
    Array arr;
    arr.push_back(Value("x"));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

// ===== Setter/Getter Tests =====

TEST(ValueTest_62, SetAndGetString_62) {
    Value v;
    v.setString("newstring");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "newstring");
}

TEST(ValueTest_62, SetAndGetInteger_62) {
    Value v;
    v.setInteger(777);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 777);
}

TEST(ValueTest_62, SetAndGetDouble_62) {
    Value v;
    v.setDouble(1.23);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.23);
}

TEST(ValueTest_62, SetAndGetBoolean_62) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
    v.setBoolean(false);
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueTest_62, SetNull_62) {
    Value v(42);
    EXPECT_FALSE(v.isNull());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_62, SetAndGetObject_62) {
    Value v;
    Object obj;
    obj["key1"] = Value("val1");
    obj["key2"] = Value(2);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 2u);
}

TEST(ValueTest_62, SetAndGetArray_62) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    arr.push_back(Value(3));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST(ValueTest_62, GetFloat_62) {
    Value v(3.14);
    EXPECT_FLOAT_EQ(v.getFloat(), 3.14f);
}

// ===== tryGet Tests =====

TEST(ValueTest_62, TryGetStringWhenString_62) {
    Value v("hello");
    EXPECT_EQ(v.tryGetString("default"), "hello");
}

TEST(ValueTest_62, TryGetStringWhenNotString_62) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST(ValueTest_62, TryGetIntegerWhenInteger_62) {
    Value v(10);
    EXPECT_EQ(v.tryGetInteger(99), 10);
}

TEST(ValueTest_62, TryGetIntegerWhenNotInteger_62) {
    Value v("string");
    EXPECT_EQ(v.tryGetInteger(99), 99);
}

TEST(ValueTest_62, TryGetDoubleWhenDouble_62) {
    Value v(5.5);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 5.5);
}

TEST(ValueTest_62, TryGetDoubleWhenNotDouble_62) {
    Value v("string");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.1), 1.1);
}

TEST(ValueTest_62, TryGetFloatWhenDouble_62) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST(ValueTest_62, TryGetFloatWhenNotDouble_62) {
    Value v("string");
    EXPECT_FLOAT_EQ(v.tryGetFloat(7.7f), 7.7f);
}

TEST(ValueTest_62, TryGetBooleanWhenBoolean_62) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST(ValueTest_62, TryGetBooleanWhenNotBoolean_62) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ===== Comparison Operators =====

TEST(ValueTest_62, EqualityOperator_62) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueTest_62, InequalityOperator_62) {
    Value v1(42);
    Value v2(43);
    EXPECT_TRUE(v1 != v2);
}

TEST(ValueTest_62, LessThanOperator_62) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST(ValueTest_62, LessThanOrEqualOperator_62) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST(ValueTest_62, GreaterThanOperator_62) {
    Value v1(10);
    Value v2(5);
    EXPECT_TRUE(v1 > v2);
}

TEST(ValueTest_62, GreaterThanOrEqualOperator_62) {
    Value v1(10);
    Value v2(10);
    EXPECT_TRUE(v1 >= v2);
}

TEST(ValueTest_62, EqualityDifferentTypes_62) {
    Value v1(42);
    Value v2("42");
    EXPECT_TRUE(v1 != v2);
}

// ===== Index Operators =====

TEST(ValueTest_62, ObjectIndexOperatorByString_62) {
    Value v;
    Object obj;
    obj["name"] = Value("John");
    v.setObject(obj);
    EXPECT_EQ(v["name"].getString(), "John");
}

TEST(ValueTest_62, ObjectIndexOperatorByCString_62) {
    Value v;
    Object obj;
    obj["age"] = Value(30);
    v.setObject(obj);
    EXPECT_EQ(v["age"].getInteger(), 30);
}

TEST(ValueTest_62, ArrayIndexOperator_62) {
    Value v;
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    v.setArray(arr);
    EXPECT_EQ(v[static_cast<size_t>(0)].getInteger(), 10);
    EXPECT_EQ(v[static_cast<size_t>(1)].getInteger(), 20);
    EXPECT_EQ(v[static_cast<size_t>(2)].getInteger(), 30);
}

// ===== loadFromString Tests =====

TEST(ValueTest_62, LoadFromStringNull_62) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_62, LoadFromStringInteger_62) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueTest_62, LoadFromStringNegativeInteger_62) {
    Value v;
    v.loadFromString("-7");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -7);
}

TEST(ValueTest_62, LoadFromStringDouble_62) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST(ValueTest_62, LoadFromStringString_62) {
    Value v;
    v.loadFromString("\"hello world\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello world");
}

TEST(ValueTest_62, LoadFromStringBoolTrue_62) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_62, LoadFromStringBoolFalse_62) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueTest_62, LoadFromStringEmptyObject_62) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST(ValueTest_62, LoadFromStringEmptyArray_62) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST(ValueTest_62, LoadFromStringObject_62) {
    Value v;
    v.loadFromString("{\"key\": \"value\", \"num\": 123}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 2u);
    EXPECT_EQ(v["key"].getString(), "value");
    EXPECT_EQ(v["num"].getInteger(), 123);
}

TEST(ValueTest_62, LoadFromStringArray_62) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST(ValueTest_62, LoadFromStringNestedObject_62) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": 42}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

TEST(ValueTest_62, LoadFromStringNestedArray_62) {
    Value v;
    v.loadFromString("[[1, 2], [3, 4]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
    EXPECT_TRUE(v[static_cast<size_t>(0)].isArray());
}

TEST(ValueTest_62, LoadFromStringZero_62) {
    Value v;
    v.loadFromString("0");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST(ValueTest_62, LoadFromStringEscapedString_62) {
    Value v;
    v.loadFromString("\"hello\\nworld\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello\nworld");
}

// ===== loadFromStream Tests =====

TEST(ValueTest_62, LoadFromStream_62) {
    std::stringstream ss("{\"a\": 1}");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["a"].getInteger(), 1);
}

// ===== writeToStream Tests =====

TEST(ValueTest_62, WriteToStreamInteger_62) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "42");
}

TEST(ValueTest_62, WriteToStreamString_62) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "\"hello\"");
}

TEST(ValueTest_62, WriteToStreamNull_62) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "null");
}

TEST(ValueTest_62, WriteToStreamBoolTrue_62) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "true");
}

TEST(ValueTest_62, WriteToStreamBoolFalse_62) {
    Value v(false);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "false");
}

TEST(ValueTest_62, WriteToStreamDouble_62) {
    Value v(1.5);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string result = oss.str();
    // Should contain "1.5" in some form
    EXPECT_NE(result.find("1.5"), std::string::npos);
}

TEST(ValueTest_62, WriteToStreamEmptyObject_62) {
    Value v;
    Object obj;
    v.setObject(obj);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "{}");
}

TEST(ValueTest_62, WriteToStreamEmptyArray_62) {
    Value v;
    Array arr;
    v.setArray(arr);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "[]");
}

// ===== Roundtrip Tests =====

TEST(ValueTest_62, RoundtripObjectThroughStream_62) {
    Value original;
    original.loadFromString("{\"name\": \"test\", \"value\": 42}");

    std::ostringstream oss;
    original.writeToStream(oss, false, false);

    Value parsed;
    parsed.loadFromString(oss.str());

    EXPECT_TRUE(parsed.isObject());
    EXPECT_EQ(parsed["name"].getString(), "test");
    EXPECT_EQ(parsed["value"].getInteger(), 42);
}

TEST(ValueTest_62, RoundtripArrayThroughStream_62) {
    Value original;
    original.loadFromString("[1, \"two\", true, null]");

    std::ostringstream oss;
    original.writeToStream(oss, false, false);

    Value parsed;
    parsed.loadFromString(oss.str());

    EXPECT_TRUE(parsed.isArray());
    EXPECT_EQ(parsed.getArray().size(), 4u);
}

// ===== Stream Insertion Operator =====

TEST(ValueTest_62, StreamInsertionOperator_62) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// ===== isStringable Tests =====

TEST(ValueTest_62, IsStringableForString_62) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST(ValueTest_62, IsStringableForInteger_62) {
    Value v(42);
    EXPECT_TRUE(v.isStringable());
}

TEST(ValueTest_62, IsStringableForDouble_62) {
    Value v(3.14);
    EXPECT_TRUE(v.isStringable());
}

// ===== getToString Tests =====

TEST(ValueTest_62, GetToStringForString_62) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

TEST(ValueTest_62, GetToStringForInteger_62) {
    Value v(42);
    std::string result = v.getToString();
    EXPECT_EQ(result, "42");
}

// ===== Escape Tests =====

TEST(ValueTest_62, EscapeMinimumCharacters_62) {
    std::string input = "hello\nworld";
    std::string escaped = Value::escapeMinimumCharacters(input);
    EXPECT_NE(escaped.find("\\n"), std::string::npos);
}

TEST(ValueTest_62, EscapeAllCharacters_62) {
    std::string input = "hello\nworld";
    std::string escaped = Value::escapeAllCharacters(input);
    EXPECT_NE(escaped.find("\\n"), std::string::npos);
}

TEST(ValueTest_62, EscapeToUnicode_62) {
    std::string result = Value::escapeToUnicode('A');
    // Should produce a unicode escape like \u0041
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ===== Edge Cases =====

TEST(ValueTest_62, EmptyStringValue_62) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST(ValueTest_62, ZeroInteger_62) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST(ValueTest_62, NegativeInteger_62) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST(ValueTest_62, ZeroDouble_62) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST(ValueTest_62, NegativeDouble_62) {
    Value v(-99.99);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -99.99);
}

TEST(ValueTest_62, LargeInteger_62) {
    Value v(2147483647);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST(ValueTest_62, TypeChangeOnSet_62) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setString("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST(ValueTest_62, TypeChangeOnAssignment_62) {
    Value v("start as string");
    EXPECT_TRUE(v.isString());
    v = 100;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST(ValueTest_62, SetNullClearsValue_62) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isInteger());
}

TEST(ValueTest_62, LoadFromStringWithWhitespace_62) {
    Value v;
    v.loadFromString("   42   ");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueTest_62, LoadFromStringComplexObject_62) {
    Value v;
    v.loadFromString("{\"arr\": [1, 2, {\"nested\": true}], \"str\": \"test\"}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["arr"].isArray());
    EXPECT_EQ(v["arr"].getArray().size(), 3u);
    EXPECT_TRUE(v["str"].isString());
}

TEST(ValueTest_62, ConstructFromIstream_62) {
    std::istringstream iss("{\"key\": 123}");
    Value v(iss);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getInteger(), 123);
}

TEST(ValueTest_62, WriteToStreamWithIndent_62) {
    Value v;
    v.loadFromString("{\"a\": 1}");
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string result = oss.str();
    // With indentation, should have newlines or tabs
    EXPECT_FALSE(result.empty());
}

TEST(ValueTest_62, WriteToStreamEscapeAll_62) {
    Value v("hello\nworld");
    std::ostringstream oss;
    v.writeToStream(oss, false, true);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

TEST(ValueTest_62, SelfAssignment_62) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueTest_62, EmptyObjectOperations_62) {
    Value v;
    Object obj;
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST(ValueTest_62, EmptyArrayOperations_62) {
    Value v;
    Array arr;
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST(ValueTest_62, LoadFromStringExponentialNotation_62) {
    Value v;
    v.loadFromString("1.5e2");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 150.0);
}

TEST(ValueTest_62, LoadFromStringUnicodeEscape_62) {
    Value v;
    v.loadFromString("\"\\u0041\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "A");
}

TEST(ValueTest_62, MultipleAssignmentChangesType_62) {
    Value v;
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

TEST(ValueTest_62, ObjectSubscriptCreatesEntry_62) {
    Value v;
    Object obj;
    v.setObject(obj);
    v["newkey"] = Value(42);
    EXPECT_EQ(v["newkey"].getInteger(), 42);
}

TEST(ValueTest_62, EqualitySameNull_62) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueTest_62, EqualitySameBool_62) {
    Value v1(true);
    Value v2(true);
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueTest_62, EqualitySameString_62) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueTest_62, InequalityDifferentStrings_62) {
    Value v1("abc");
    Value v2("def");
    EXPECT_TRUE(v1 != v2);
}
