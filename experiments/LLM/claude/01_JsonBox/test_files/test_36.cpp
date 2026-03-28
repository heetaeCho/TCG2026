#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

// ==================== Construction Tests ====================

TEST(ValueTest_36, DefaultConstructorCreatesNull_36) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
}

TEST(ValueTest_36, StringConstructor_36) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isNull());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueTest_36, CStringConstructor_36) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST(ValueTest_36, IntConstructor_36) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueTest_36, DoubleConstructor_36) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST(ValueTest_36, BooleanConstructorTrue_36) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_36, BooleanConstructorFalse_36) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueTest_36, ObjectConstructor_36) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
}

TEST(ValueTest_36, ArrayConstructor_36) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
}

TEST(ValueTest_36, CopyConstructor_36) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

// ==================== isDouble Tests (the method under focus) ====================

TEST(ValueTest_36, IsDoubleReturnsTrueForDouble_36) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
}

TEST(ValueTest_36, IsDoubleReturnsFalseForInt_36) {
    Value v(1);
    EXPECT_FALSE(v.isDouble());
}

TEST(ValueTest_36, IsDoubleReturnsFalseForString_36) {
    Value v("3.14");
    EXPECT_FALSE(v.isDouble());
}

TEST(ValueTest_36, IsDoubleReturnsFalseForNull_36) {
    Value v;
    EXPECT_FALSE(v.isDouble());
}

TEST(ValueTest_36, IsDoubleReturnsFalseForBoolean_36) {
    Value v(true);
    EXPECT_FALSE(v.isDouble());
}

TEST(ValueTest_36, IsDoubleReturnsFalseForObject_36) {
    Object obj;
    Value v(obj);
    EXPECT_FALSE(v.isDouble());
}

TEST(ValueTest_36, IsDoubleReturnsFalseForArray_36) {
    Array arr;
    Value v(arr);
    EXPECT_FALSE(v.isDouble());
}

TEST(ValueTest_36, IsDoubleAfterSetDouble_36) {
    Value v;
    EXPECT_FALSE(v.isDouble());
    v.setDouble(2.718);
    EXPECT_TRUE(v.isDouble());
}

TEST(ValueTest_36, IsDoubleWithZero_36) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
}

TEST(ValueTest_36, IsDoubleWithNegative_36) {
    Value v(-99.99);
    EXPECT_TRUE(v.isDouble());
}

TEST(ValueTest_36, IsDoubleWithVeryLargeValue_36) {
    Value v(1.0e308);
    EXPECT_TRUE(v.isDouble());
}

TEST(ValueTest_36, IsDoubleWithVerySmallValue_36) {
    Value v(1.0e-308);
    EXPECT_TRUE(v.isDouble());
}

// ==================== Type Checking Tests ====================

TEST(ValueTest_36, IsNumericForInt_36) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST(ValueTest_36, IsNumericForDouble_36) {
    Value v(5.5);
    EXPECT_TRUE(v.isNumeric());
}

TEST(ValueTest_36, IsNumericForString_36) {
    Value v("hello");
    EXPECT_FALSE(v.isNumeric());
}

TEST(ValueTest_36, IsStringForString_36) {
    Value v("test");
    EXPECT_TRUE(v.isString());
}

TEST(ValueTest_36, IsStringableForString_36) {
    Value v("test");
    EXPECT_TRUE(v.isStringable());
}

TEST(ValueTest_36, GetType_36) {
    Value vNull;
    Value vStr("hello");
    Value vInt(10);
    Value vDbl(1.0);
    Value vBool(true);
    Value vObj(Object());
    Value vArr(Array());

    EXPECT_EQ(vNull.getType(), Value::NULL_VALUE);
    EXPECT_EQ(vStr.getType(), Value::STRING);
    EXPECT_EQ(vInt.getType(), Value::INTEGER);
    EXPECT_EQ(vDbl.getType(), Value::DOUBLE);
    EXPECT_EQ(vBool.getType(), Value::BOOLEAN);
    EXPECT_EQ(vObj.getType(), Value::OBJECT);
    EXPECT_EQ(vArr.getType(), Value::ARRAY);
}

// ==================== Assignment Operator Tests ====================

TEST(ValueTest_36, AssignString_36) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST(ValueTest_36, AssignCString_36) {
    Value v;
    v = "cstring";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "cstring");
}

TEST(ValueTest_36, AssignInt_36) {
    Value v;
    v = 100;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST(ValueTest_36, AssignDouble_36) {
    Value v;
    v = 2.5;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.5);
}

TEST(ValueTest_36, AssignBool_36) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_36, AssignObject_36) {
    Value v;
    Object obj;
    obj["key"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST(ValueTest_36, AssignArray_36) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

TEST(ValueTest_36, AssignValue_36) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

// ==================== Getter/Setter Tests ====================

TEST(ValueTest_36, SetStringAndGet_36) {
    Value v;
    v.setString("test_string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test_string");
}

TEST(ValueTest_36, SetIntegerAndGet_36) {
    Value v;
    v.setInteger(77);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 77);
}

TEST(ValueTest_36, SetDoubleAndGet_36) {
    Value v;
    v.setDouble(9.81);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 9.81);
}

TEST(ValueTest_36, SetBooleanAndGet_36) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_36, SetObjectAndGet_36) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    const Object& retrieved = v.getObject();
    EXPECT_EQ(retrieved.size(), 1u);
}

TEST(ValueTest_36, SetArrayAndGet_36) {
    Value v;
    Array arr;
    arr.push_back(Value("item"));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    const Array& retrieved = v.getArray();
    EXPECT_EQ(retrieved.size(), 1u);
}

TEST(ValueTest_36, SetNull_36) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_36, GetFloat_36) {
    Value v(3.14);
    float f = v.getFloat();
    EXPECT_NEAR(f, 3.14f, 0.001f);
}

// ==================== TryGet Tests ====================

TEST(ValueTest_36, TryGetStringReturnsValueWhenString_36) {
    Value v("hello");
    EXPECT_EQ(v.tryGetString("default"), "hello");
}

TEST(ValueTest_36, TryGetStringReturnsDefaultWhenNotString_36) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST(ValueTest_36, TryGetIntegerReturnsValueWhenInteger_36) {
    Value v(10);
    EXPECT_EQ(v.tryGetInteger(0), 10);
}

TEST(ValueTest_36, TryGetIntegerReturnsDefaultWhenNotInteger_36) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(99), 99);
}

TEST(ValueTest_36, TryGetDoubleReturnsValueWhenDouble_36) {
    Value v(2.5);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 2.5);
}

TEST(ValueTest_36, TryGetDoubleReturnsDefaultWhenNotDouble_36) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.0), 1.0);
}

TEST(ValueTest_36, TryGetFloatReturnsValueWhenDouble_36) {
    Value v(2.5);
    EXPECT_NEAR(v.tryGetFloat(0.0f), 2.5f, 0.001f);
}

TEST(ValueTest_36, TryGetFloatReturnsDefaultWhenNotDouble_36) {
    Value v("hello");
    EXPECT_NEAR(v.tryGetFloat(1.0f), 1.0f, 0.001f);
}

TEST(ValueTest_36, TryGetBooleanReturnsValueWhenBoolean_36) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST(ValueTest_36, TryGetBooleanReturnsDefaultWhenNotBoolean_36) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ==================== Comparison Tests ====================

TEST(ValueTest_36, EqualityOperator_36) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueTest_36, InequalityOperator_36) {
    Value v1(42);
    Value v2(43);
    EXPECT_TRUE(v1 != v2);
}

TEST(ValueTest_36, LessThanOperator_36) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
}

TEST(ValueTest_36, LessThanOrEqualOperator_36) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST(ValueTest_36, GreaterThanOperator_36) {
    Value v1(2);
    Value v2(1);
    EXPECT_TRUE(v1 > v2);
}

TEST(ValueTest_36, GreaterThanOrEqualOperator_36) {
    Value v1(2);
    Value v2(2);
    EXPECT_TRUE(v1 >= v2);
}

TEST(ValueTest_36, EqualityDifferentTypes_36) {
    Value v1(42);
    Value v2("42");
    EXPECT_TRUE(v1 != v2);
}

// ==================== Subscript Operator Tests ====================

TEST(ValueTest_36, ObjectSubscriptWithString_36) {
    Value v(Object());
    v["key"] = Value(123);
    EXPECT_TRUE(v["key"].isInteger());
    EXPECT_EQ(v["key"].getInteger(), 123);
}

TEST(ValueTest_36, ObjectSubscriptWithCString_36) {
    Value v(Object());
    v["name"] = Value("test");
    EXPECT_TRUE(v["name"].isString());
    EXPECT_EQ(v["name"].getString(), "test");
}

TEST(ValueTest_36, ArraySubscriptWithIndex_36) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

// ==================== Load/Write Tests ====================

TEST(ValueTest_36, LoadFromString_36) {
    Value v;
    v.loadFromString("{\"key\": 42}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["key"].isInteger());
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST(ValueTest_36, LoadFromStringArray_36) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST(ValueTest_36, LoadFromStringSimpleString_36) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueTest_36, LoadFromStringNumber_36) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST(ValueTest_36, LoadFromStringBoolean_36) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_36, LoadFromStringNull_36) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_36, LoadFromStream_36) {
    std::istringstream iss("{\"a\": 1}");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isObject());
}

TEST(ValueTest_36, WriteToStream_36) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST(ValueTest_36, WriteToStreamString_36) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST(ValueTest_36, StreamOperator_36) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

// ==================== GetToString Tests ====================

TEST(ValueTest_36, GetToStringFromInt_36) {
    Value v(42);
    std::string s = v.getToString();
    EXPECT_EQ(s, "42");
}

TEST(ValueTest_36, GetToStringFromDouble_36) {
    Value v(3.14);
    std::string s = v.getToString();
    EXPECT_FALSE(s.empty());
}

TEST(ValueTest_36, GetToStringFromString_36) {
    Value v("hello");
    std::string s = v.getToString();
    EXPECT_EQ(s, "hello");
}

// ==================== Escape Tests ====================

TEST(ValueTest_36, EscapeMinimumCharacters_36) {
    std::string result = Value::escapeMinimumCharacters("hello\nworld");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST(ValueTest_36, EscapeMinimumCharactersQuotes_36) {
    std::string result = Value::escapeMinimumCharacters("say \"hi\"");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST(ValueTest_36, EscapeAllCharacters_36) {
    std::string result = Value::escapeAllCharacters("hello");
    EXPECT_FALSE(result.empty());
}

TEST(ValueTest_36, EscapeToUnicode_36) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
    // Unicode escape should contain \\u
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ==================== Type Transition Tests ====================

TEST(ValueTest_36, TransitionFromIntToString_36) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setString("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
}

TEST(ValueTest_36, TransitionFromStringToDouble_36) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    v.setDouble(1.23);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isString());
}

TEST(ValueTest_36, TransitionFromDoubleToNull_36) {
    Value v(1.0);
    EXPECT_TRUE(v.isDouble());
    v.setNull();
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isDouble());
}

TEST(ValueTest_36, TransitionFromNullToBoolean_36) {
    Value v;
    EXPECT_TRUE(v.isNull());
    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

// ==================== Boundary/Edge Cases ====================

TEST(ValueTest_36, EmptyString_36) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST(ValueTest_36, ZeroInteger_36) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST(ValueTest_36, NegativeInteger_36) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST(ValueTest_36, EmptyObject_36) {
    Value v(Object());
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST(ValueTest_36, EmptyArray_36) {
    Value v(Array());
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST(ValueTest_36, NestedObjectValue_36) {
    Value inner(42);
    Object obj;
    obj["inner"] = inner;
    Value outer(obj);
    EXPECT_TRUE(outer.isObject());
    EXPECT_EQ(outer["inner"].getInteger(), 42);
}

TEST(ValueTest_36, NestedArrayValue_36) {
    Array innerArr;
    innerArr.push_back(Value(1));
    innerArr.push_back(Value(2));
    Array outerArr;
    outerArr.push_back(Value(innerArr));
    Value v(outerArr);
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v[(size_t)0].isArray());
}

TEST(ValueTest_36, LoadComplexJson_36) {
    Value v;
    v.loadFromString("{\"name\": \"test\", \"value\": 42, \"nested\": {\"flag\": true}, \"list\": [1, 2, 3]}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["name"].getString(), "test");
    EXPECT_EQ(v["value"].getInteger(), 42);
    EXPECT_TRUE(v["nested"].isObject());
    EXPECT_TRUE(v["nested"]["flag"].getBoolean());
    EXPECT_TRUE(v["list"].isArray());
    EXPECT_EQ(v["list"].getArray().size(), 3u);
}

TEST(ValueTest_36, InputStreamConstructor_36) {
    std::istringstream iss("{\"key\": \"value\"}");
    Value v(iss);
    EXPECT_TRUE(v.isObject());
}

TEST(ValueTest_36, SelfAssignment_36) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueTest_36, WriteToStreamWithIndent_36) {
    Value v;
    v.loadFromString("{\"a\": 1, \"b\": 2}");
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST(ValueTest_36, WriteToStreamWithEscapeAll_36) {
    Value v;
    v.loadFromString("{\"key\": \"hello\"}");
    std::ostringstream oss;
    v.writeToStream(oss, false, true);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}
