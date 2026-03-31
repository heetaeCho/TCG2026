#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueTest_15 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(ValueTest_15, DefaultConstructorCreatesNull_15) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_15, StringConstructor_15) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
    EXPECT_EQ(v.getType(), Value::STRING);
}

TEST_F(ValueTest_15, CStringConstructor_15) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_15, IntConstructor_15) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
    EXPECT_EQ(v.getType(), Value::INTEGER);
}

TEST_F(ValueTest_15, DoubleConstructor_15) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
    EXPECT_EQ(v.getType(), Value::DOUBLE);
}

TEST_F(ValueTest_15, BoolConstructorTrue_15) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
    EXPECT_EQ(v.getType(), Value::BOOLEAN);
}

TEST_F(ValueTest_15, BoolConstructorFalse_15) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_15, ObjectConstructor_15) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getType(), Value::OBJECT);
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_15, ArrayConstructor_15) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getType(), Value::ARRAY);
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_15, CopyConstructorString_15) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "test");
}

TEST_F(ValueTest_15, CopyConstructorInt_15) {
    Value original(100);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 100);
}

TEST_F(ValueTest_15, CopyConstructorDouble_15) {
    Value original(2.718);
    Value copy(original);
    EXPECT_TRUE(copy.isDouble());
    EXPECT_DOUBLE_EQ(copy.getDouble(), 2.718);
}

TEST_F(ValueTest_15, CopyConstructorBool_15) {
    Value original(true);
    Value copy(original);
    EXPECT_TRUE(copy.isBoolean());
    EXPECT_TRUE(copy.getBoolean());
}

TEST_F(ValueTest_15, CopyConstructorNull_15) {
    Value original;
    Value copy(original);
    EXPECT_TRUE(copy.isNull());
}

TEST_F(ValueTest_15, CopyConstructorObject_15) {
    Object obj;
    obj["a"] = Value(1);
    Value original(obj);
    Value copy(original);
    EXPECT_TRUE(copy.isObject());
    EXPECT_EQ(copy.getObject().size(), 1u);
}

TEST_F(ValueTest_15, CopyConstructorArray_15) {
    Array arr;
    arr.push_back(Value("x"));
    Value original(arr);
    Value copy(original);
    EXPECT_TRUE(copy.isArray());
    EXPECT_EQ(copy.getArray().size(), 1u);
}

// ==================== Assignment Operator Tests ====================

TEST_F(ValueTest_15, AssignValueString_15) {
    Value v(42);
    Value src("assigned");
    v = src;
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_15, AssignValueInt_15) {
    Value v("hello");
    Value src(99);
    v = src;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_15, AssignValueDouble_15) {
    Value v;
    Value src(1.5);
    v = src;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.5);
}

TEST_F(ValueTest_15, AssignValueBool_15) {
    Value v(42);
    Value src(true);
    v = src;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_15, AssignValueNull_15) {
    Value v("non-null");
    Value src;
    v = src;
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_15, AssignValueObject_15) {
    Object obj;
    obj["key"] = Value("val");
    Value v;
    Value src(obj);
    v = src;
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_15, AssignValueArray_15) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    arr.push_back(Value(3));
    Value v;
    Value src(arr);
    v = src;
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_15, SelfAssignment_15) {
    Value v("self");
    v = v;
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "self");
}

TEST_F(ValueTest_15, AssignString_15) {
    Value v;
    v = std::string("test_string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test_string");
}

TEST_F(ValueTest_15, AssignCString_15) {
    Value v(42);
    v = "c_string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "c_string");
}

TEST_F(ValueTest_15, AssignInt_15) {
    Value v;
    v = 123;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

TEST_F(ValueTest_15, AssignDouble_15) {
    Value v;
    v = 9.81;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 9.81);
}

TEST_F(ValueTest_15, AssignObject_15) {
    Value v;
    Object obj;
    obj["x"] = Value(10);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_15, AssignArray_15) {
    Value v;
    Array arr;
    arr.push_back(Value(true));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_15, AssignBool_15) {
    Value v;
    v = false;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

// ==================== Type Check Tests ====================

TEST_F(ValueTest_15, IsStringableForString_15) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_15, IsNumericForInt_15) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_15, IsNumericForDouble_15) {
    Value v(5.0);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_15, IsNotStringForInt_15) {
    Value v(5);
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_15, IsNotIntForString_15) {
    Value v("hello");
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_15, IsNotDoubleForInt_15) {
    Value v(5);
    EXPECT_FALSE(v.isDouble());
}

TEST_F(ValueTest_15, IsNotObjectForArray_15) {
    Array arr;
    Value v(arr);
    EXPECT_FALSE(v.isObject());
}

TEST_F(ValueTest_15, IsNotArrayForObject_15) {
    Object obj;
    Value v(obj);
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueTest_15, IsNotBooleanForNull_15) {
    Value v;
    EXPECT_FALSE(v.isBoolean());
}

TEST_F(ValueTest_15, IsNotNullForBool_15) {
    Value v(true);
    EXPECT_FALSE(v.isNull());
}

// ==================== Getter/Setter Tests ====================

TEST_F(ValueTest_15, SetStringChangesType_15) {
    Value v(42);
    v.setString("changed");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "changed");
}

TEST_F(ValueTest_15, SetIntegerChangesType_15) {
    Value v("hello");
    v.setInteger(7);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 7);
}

TEST_F(ValueTest_15, SetDoubleChangesType_15) {
    Value v(42);
    v.setDouble(6.28);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 6.28);
}

TEST_F(ValueTest_15, SetBooleanChangesType_15) {
    Value v("hello");
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_15, SetNullChangesType_15) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_15, SetObjectChangesType_15) {
    Value v;
    Object obj;
    obj["key"] = Value("val");
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_15, SetArrayChangesType_15) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

TEST_F(ValueTest_15, GetFloat_15) {
    Value v(3.14);
    float f = v.getFloat();
    EXPECT_NEAR(f, 3.14f, 0.001f);
}

// ==================== tryGet Tests ====================

TEST_F(ValueTest_15, TryGetStringReturnsValueIfString_15) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST_F(ValueTest_15, TryGetStringReturnsDefaultIfNotString_15) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_15, TryGetIntegerReturnsValueIfInt_15) {
    Value v(10);
    EXPECT_EQ(v.tryGetInteger(0), 10);
}

TEST_F(ValueTest_15, TryGetIntegerReturnsDefaultIfNotInt_15) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(99), 99);
}

TEST_F(ValueTest_15, TryGetDoubleReturnsValueIfDouble_15) {
    Value v(2.5);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 2.5);
}

TEST_F(ValueTest_15, TryGetDoubleReturnsDefaultIfNotDouble_15) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.0), 1.0);
}

TEST_F(ValueTest_15, TryGetBooleanReturnsValueIfBool_15) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_15, TryGetBooleanReturnsDefaultIfNotBool_15) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_15, TryGetFloatReturnsDefaultIfNotDouble_15) {
    Value v("hello");
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.5f), 1.5f);
}

// ==================== Comparison Operator Tests ====================

TEST_F(ValueTest_15, EqualityForSameStrings_15) {
    Value a("test");
    Value b("test");
    EXPECT_TRUE(a == b);
}

TEST_F(ValueTest_15, InequalityForDifferentStrings_15) {
    Value a("test1");
    Value b("test2");
    EXPECT_TRUE(a != b);
}

TEST_F(ValueTest_15, EqualityForSameIntegers_15) {
    Value a(42);
    Value b(42);
    EXPECT_TRUE(a == b);
}

TEST_F(ValueTest_15, InequalityForDifferentIntegers_15) {
    Value a(1);
    Value b(2);
    EXPECT_TRUE(a != b);
}

TEST_F(ValueTest_15, EqualityForSameDoubles_15) {
    Value a(3.14);
    Value b(3.14);
    EXPECT_TRUE(a == b);
}

TEST_F(ValueTest_15, EqualityForSameBooleans_15) {
    Value a(true);
    Value b(true);
    EXPECT_TRUE(a == b);
}

TEST_F(ValueTest_15, InequalityForDifferentTypes_15) {
    Value a(42);
    Value b("42");
    EXPECT_TRUE(a != b);
}

TEST_F(ValueTest_15, EqualityForNulls_15) {
    Value a;
    Value b;
    EXPECT_TRUE(a == b);
}

TEST_F(ValueTest_15, LessThanForIntegers_15) {
    Value a(1);
    Value b(2);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(ValueTest_15, LessThanOrEqualForIntegers_15) {
    Value a(1);
    Value b(1);
    EXPECT_TRUE(a <= b);
}

TEST_F(ValueTest_15, GreaterThanForIntegers_15) {
    Value a(5);
    Value b(3);
    EXPECT_TRUE(a > b);
}

TEST_F(ValueTest_15, GreaterThanOrEqualForIntegers_15) {
    Value a(5);
    Value b(5);
    EXPECT_TRUE(a >= b);
}

// ==================== Subscript Operator Tests ====================

TEST_F(ValueTest_15, SubscriptStringKeyOnObject_15) {
    Object obj;
    obj["key"] = Value(42);
    Value v(obj);
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST_F(ValueTest_15, SubscriptCStringKeyOnObject_15) {
    Object obj;
    obj["name"] = Value("Alice");
    Value v(obj);
    EXPECT_EQ(v["name"].getString(), "Alice");
}

TEST_F(ValueTest_15, SubscriptIndexOnArray_15) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

TEST_F(ValueTest_15, SubscriptCreatesNewKeyInObject_15) {
    Object obj;
    Value v(obj);
    v["newkey"] = Value("newvalue");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["newkey"].getString(), "newvalue");
}

// ==================== Load/Write Tests ====================

TEST_F(ValueTest_15, LoadFromStringSimpleObject_15) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST_F(ValueTest_15, LoadFromStringInteger_15) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_15, LoadFromStringDouble_15) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_15, LoadFromStringBoolTrue_15) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_15, LoadFromStringBoolFalse_15) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_15, LoadFromStringNull_15) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_15, LoadFromStringArray_15) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_15, LoadFromStream_15) {
    std::istringstream iss("{\"a\": 1}");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["a"].getInteger(), 1);
}

TEST_F(ValueTest_15, WriteToStreamAndReadBack_15) {
    Value v;
    v.loadFromString("{\"name\": \"test\", \"value\": 42}");

    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());

    Value v2;
    v2.loadFromString(output);
    EXPECT_TRUE(v2.isObject());
    EXPECT_EQ(v2["name"].getString(), "test");
    EXPECT_EQ(v2["value"].getInteger(), 42);
}

TEST_F(ValueTest_15, WriteToStreamIndented_15) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");

    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    // Indented output should contain newlines/tabs
    EXPECT_NE(output.find('\n'), std::string::npos);
}

TEST_F(ValueTest_15, StreamConstructor_15) {
    std::istringstream iss("\"hello\"");
    Value v(iss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

// ==================== getToString Tests ====================

TEST_F(ValueTest_15, GetToStringForString_15) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

TEST_F(ValueTest_15, GetToStringForInteger_15) {
    Value v(42);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_15, GetToStringForDouble_15) {
    Value v(3.14);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_15, GetToStringForBool_15) {
    Value v(true);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

// ==================== Escape Function Tests ====================

TEST_F(ValueTest_15, EscapeMinimumCharacters_15) {
    std::string input = "hello\nworld";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_15, EscapeMinimumCharactersQuote_15) {
    std::string input = "say \"hello\"";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_15, EscapeAllCharacters_15) {
    std::string input = "hello\nworld";
    std::string result = Value::escapeAllCharacters(input);
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_15, EscapeToUnicode_15) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
    // Should contain \u prefix
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ==================== Boundary / Edge Cases ====================

TEST_F(ValueTest_15, EmptyStringValue_15) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_15, ZeroInteger_15) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_15, NegativeInteger_15) {
    Value v(-42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST_F(ValueTest_15, ZeroDouble_15) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_15, NegativeDouble_15) {
    Value v(-1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -1.5);
}

TEST_F(ValueTest_15, EmptyObject_15) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_15, EmptyArray_15) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_15, LoadFromStringEmptyObject_15) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_15, LoadFromStringEmptyArray_15) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_15, LoadFromStringNestedObject_15) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": 42}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

TEST_F(ValueTest_15, LoadFromStringNestedArray_15) {
    Value v;
    v.loadFromString("[[1, 2], [3, 4]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
    EXPECT_TRUE(v[(size_t)0].isArray());
    EXPECT_TRUE(v[(size_t)1].isArray());
}

TEST_F(ValueTest_15, LoadFromStringWithWhitespace_15) {
    Value v;
    v.loadFromString("  {  \"key\"  :  \"value\"  }  ");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST_F(ValueTest_15, AssignmentChaining_15) {
    Value a, b, c;
    a = b = c = 42;
    EXPECT_EQ(a.getInteger(), 42);
    EXPECT_EQ(b.getInteger(), 42);
    EXPECT_EQ(c.getInteger(), 42);
}

TEST_F(ValueTest_15, OverwriteTypeMultipleTimes_15) {
    Value v;
    v = 42;
    EXPECT_TRUE(v.isInteger());
    v = "hello";
    EXPECT_TRUE(v.isString());
    v = true;
    EXPECT_TRUE(v.isBoolean());
    v = 3.14;
    EXPECT_TRUE(v.isDouble());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_15, LargeInteger_15) {
    Value v(2147483647); // INT_MAX
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST_F(ValueTest_15, MinInteger_15) {
    Value v(-2147483647 - 1); // INT_MIN
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -2147483647 - 1);
}

TEST_F(ValueTest_15, LoadFromStringEscapedString_15) {
    Value v;
    v.loadFromString("\"hello\\nworld\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello\nworld");
}

TEST_F(ValueTest_15, StreamOutputOperator_15) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTest_15, WriteToStreamEscapeAll_15) {
    Value v("hello\nworld");
    std::ostringstream oss;
    v.writeToStream(oss, false, true);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTest_15, CopyConstructorIndependence_15) {
    Value original("original");
    Value copy(original);
    copy = "modified";
    EXPECT_EQ(original.getString(), "original");
    EXPECT_EQ(copy.getString(), "modified");
}

TEST_F(ValueTest_15, AssignmentIndependence_15) {
    Value original(42);
    Value assigned;
    assigned = original;
    assigned = 99;
    EXPECT_EQ(original.getInteger(), 42);
    EXPECT_EQ(assigned.getInteger(), 99);
}
