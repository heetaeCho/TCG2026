#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueTest_53 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(ValueTest_53, DefaultConstructorCreatesNullValue_53) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_53, StringConstructor_53) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_53, CStringConstructor_53) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_53, IntConstructor_53) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_53, DoubleConstructor_53) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_53, BooleanConstructorTrue_53) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_53, BooleanConstructorFalse_53) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_53, ObjectConstructor_53) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_53, ArrayConstructor_53) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_53, CopyConstructor_53) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

// ==================== Type Check Tests ====================

TEST_F(ValueTest_53, IsStringReturnsTrueForString_53) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_53, IsIntegerReturnsTrueForInt_53) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
}

TEST_F(ValueTest_53, IsDoubleReturnsTrueForDouble_53) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_53, IsNumericForInteger_53) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_53, IsNumericForDouble_53) {
    Value v(5.5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_53, IsNumericFalseForString_53) {
    Value v("not a number");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_53, IsObjectReturnsTrueForObject_53) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_53, IsArrayReturnsTrueForArray_53) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_53, IsBooleanReturnsTrueForBoolean_53) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
}

TEST_F(ValueTest_53, IsNullReturnsTrueForNull_53) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

// ==================== setDouble Tests (the focus method) ====================

TEST_F(ValueTest_53, SetDoubleOnNullValue_53) {
    Value v;
    EXPECT_TRUE(v.isNull());
    v.setDouble(2.718);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_53, SetDoubleOnExistingDouble_53) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    v.setDouble(2.718);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_53, SetDoubleOnStringValue_53) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    v.setDouble(1.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.0);
}

TEST_F(ValueTest_53, SetDoubleOnIntegerValue_53) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setDouble(42.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 42.5);
}

TEST_F(ValueTest_53, SetDoubleOnBooleanValue_53) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    v.setDouble(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_53, SetDoubleOnObjectValue_53) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    v.setDouble(9.99);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 9.99);
}

TEST_F(ValueTest_53, SetDoubleOnArrayValue_53) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    v.setDouble(-5.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -5.5);
}

TEST_F(ValueTest_53, SetDoubleZero_53) {
    Value v;
    v.setDouble(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_53, SetDoubleNegative_53) {
    Value v;
    v.setDouble(-123.456);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -123.456);
}

TEST_F(ValueTest_53, SetDoubleLargeValue_53) {
    Value v;
    v.setDouble(1.0e308);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.0e308);
}

TEST_F(ValueTest_53, SetDoubleSmallValue_53) {
    Value v;
    v.setDouble(1.0e-308);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.0e-308);
}

TEST_F(ValueTest_53, SetDoubleMultipleTimes_53) {
    Value v;
    v.setDouble(1.0);
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.0);
    v.setDouble(2.0);
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.0);
    v.setDouble(3.0);
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.0);
}

// ==================== Getter/Setter Tests ====================

TEST_F(ValueTest_53, SetAndGetString_53) {
    Value v;
    v.setString("test string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test string");
}

TEST_F(ValueTest_53, SetAndGetInteger_53) {
    Value v;
    v.setInteger(100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST_F(ValueTest_53, SetAndGetBoolean_53) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_53, SetNull_53) {
    Value v(42);
    EXPECT_FALSE(v.isNull());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_53, SetAndGetObject_53) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    obj["b"] = Value(2);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 2u);
}

TEST_F(ValueTest_53, SetAndGetArray_53) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    arr.push_back(Value(3));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_53, GetFloat_53) {
    Value v(3.14);
    EXPECT_FLOAT_EQ(v.getFloat(), 3.14f);
}

// ==================== tryGet Tests ====================

TEST_F(ValueTest_53, TryGetStringReturnsValueWhenString_53) {
    Value v("hello");
    EXPECT_EQ(v.tryGetString("default"), "hello");
}

TEST_F(ValueTest_53, TryGetStringReturnsDefaultWhenNotString_53) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_53, TryGetIntegerReturnsValueWhenInteger_53) {
    Value v(42);
    EXPECT_EQ(v.tryGetInteger(0), 42);
}

TEST_F(ValueTest_53, TryGetIntegerReturnsDefaultWhenNotInteger_53) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(99), 99);
}

TEST_F(ValueTest_53, TryGetDoubleReturnsValueWhenDouble_53) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 3.14);
}

TEST_F(ValueTest_53, TryGetDoubleReturnsDefaultWhenNotDouble_53) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.23), 1.23);
}

TEST_F(ValueTest_53, TryGetFloatReturnsValueWhenDouble_53) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST_F(ValueTest_53, TryGetFloatReturnsDefaultWhenNotDouble_53) {
    Value v("hello");
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.5f), 1.5f);
}

TEST_F(ValueTest_53, TryGetBooleanReturnsValueWhenBoolean_53) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_53, TryGetBooleanReturnsDefaultWhenNotBoolean_53) {
    Value v(42);
    EXPECT_TRUE(v.tryGetBoolean(true));
}

// ==================== Assignment Operator Tests ====================

TEST_F(ValueTest_53, AssignmentFromValue_53) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_53, AssignmentFromString_53) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_53, AssignmentFromCString_53) {
    Value v;
    v = "c-string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "c-string");
}

TEST_F(ValueTest_53, AssignmentFromInt_53) {
    Value v;
    v = 100;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST_F(ValueTest_53, AssignmentFromDouble_53) {
    Value v;
    v = 2.5;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.5);
}

TEST_F(ValueTest_53, AssignmentFromBool_53) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_53, AssignmentFromObject_53) {
    Value v;
    Object obj;
    obj["key"] = Value("val");
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_53, AssignmentFromArray_53) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

// ==================== Comparison Operator Tests ====================

TEST_F(ValueTest_53, EqualityOperatorSameValues_53) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_53, EqualityOperatorDifferentValues_53) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_53, InequalityOperator_53) {
    Value v1(42);
    Value v2(43);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_53, LessThanOperator_53) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_53, LessThanOrEqualOperator_53) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_53, GreaterThanOperator_53) {
    Value v1(2);
    Value v2(1);
    EXPECT_TRUE(v1 > v2);
}

TEST_F(ValueTest_53, GreaterThanOrEqualOperator_53) {
    Value v1(2);
    Value v2(2);
    EXPECT_TRUE(v1 >= v2);
}

// ==================== Subscript Operator Tests ====================

TEST_F(ValueTest_53, SubscriptWithStringKeyOnObject_53) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    Value& ref = v["key"];
    EXPECT_TRUE(ref.isString());
    EXPECT_EQ(ref.getString(), "value");
}

TEST_F(ValueTest_53, SubscriptWithCStringKeyOnObject_53) {
    Object obj;
    obj["key"] = Value(42);
    Value v(obj);
    Value& ref = v["key"];
    EXPECT_TRUE(ref.isInteger());
    EXPECT_EQ(ref.getInteger(), 42);
}

TEST_F(ValueTest_53, SubscriptWithIndexOnArray_53) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

// ==================== getType Tests ====================

TEST_F(ValueTest_53, GetTypeString_53) {
    Value v("test");
    EXPECT_EQ(v.getType(), Value::STRING);
}

TEST_F(ValueTest_53, GetTypeInteger_53) {
    Value v(1);
    EXPECT_EQ(v.getType(), Value::INTEGER);
}

TEST_F(ValueTest_53, GetTypeDouble_53) {
    Value v(1.0);
    EXPECT_EQ(v.getType(), Value::DOUBLE);
}

TEST_F(ValueTest_53, GetTypeObject_53) {
    Object obj;
    Value v(obj);
    EXPECT_EQ(v.getType(), Value::OBJECT);
}

TEST_F(ValueTest_53, GetTypeArray_53) {
    Array arr;
    Value v(arr);
    EXPECT_EQ(v.getType(), Value::ARRAY);
}

TEST_F(ValueTest_53, GetTypeBoolean_53) {
    Value v(false);
    EXPECT_EQ(v.getType(), Value::BOOLEAN);
}

TEST_F(ValueTest_53, GetTypeNull_53) {
    Value v;
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

// ==================== Load/Write Tests ====================

TEST_F(ValueTest_53, LoadFromString_53) {
    Value v;
    v.loadFromString("{\"key\": 42}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST_F(ValueTest_53, LoadFromStream_53) {
    std::istringstream stream("[1, 2, 3]");
    Value v;
    v.loadFromStream(stream);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_53, WriteToStream_53) {
    Value v(42);
    std::ostringstream output;
    v.writeToStream(output, false, false);
    std::string result = output.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_53, LoadFromStringNull_53) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_53, LoadFromStringBoolean_53) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_53, LoadFromStringDouble_53) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble() || v.isInteger());
}

TEST_F(ValueTest_53, LoadFromStringString_53) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

// ==================== Stream Operator Tests ====================

TEST_F(ValueTest_53, StreamOutputOperator_53) {
    Value v("test");
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

// ==================== Escape Tests ====================

TEST_F(ValueTest_53, EscapeMinimumCharacters_53) {
    std::string result = Value::escapeMinimumCharacters("hello\nworld");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_53, EscapeAllCharacters_53) {
    std::string result = Value::escapeAllCharacters("hello");
    // The function should return some representation
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_53, EscapeToUnicode_53) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
}

// ==================== isStringable Tests ====================

TEST_F(ValueTest_53, IsStringableForString_53) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_53, IsStringableForInteger_53) {
    Value v(42);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_53, IsStringableForDouble_53) {
    Value v(3.14);
    EXPECT_TRUE(v.isStringable());
}

// ==================== getToString Tests ====================

TEST_F(ValueTest_53, GetToStringFromString_53) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

TEST_F(ValueTest_53, GetToStringFromInteger_53) {
    Value v(42);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

// ==================== Edge Cases ====================

TEST_F(ValueTest_53, EmptyStringValue_53) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_53, ZeroIntegerValue_53) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_53, NegativeIntegerValue_53) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST_F(ValueTest_53, EmptyObjectValue_53) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_53, EmptyArrayValue_53) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_53, SetDoubleAfterSetInteger_53) {
    Value v;
    v.setInteger(10);
    EXPECT_TRUE(v.isInteger());
    v.setDouble(10.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
    EXPECT_DOUBLE_EQ(v.getDouble(), 10.5);
}

TEST_F(ValueTest_53, SetIntegerAfterSetDouble_53) {
    Value v;
    v.setDouble(10.5);
    EXPECT_TRUE(v.isDouble());
    v.setInteger(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_EQ(v.getInteger(), 10);
}

TEST_F(ValueTest_53, SetStringAfterSetDouble_53) {
    Value v;
    v.setDouble(1.0);
    EXPECT_TRUE(v.isDouble());
    v.setString("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isDouble());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST_F(ValueTest_53, SetNullAfterSetDouble_53) {
    Value v;
    v.setDouble(1.0);
    EXPECT_TRUE(v.isDouble());
    v.setNull();
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isDouble());
}

TEST_F(ValueTest_53, WriteToStreamIndented_53) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    std::ostringstream output;
    v.writeToStream(output, true, false);
    std::string result = output.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_53, WriteToStreamEscapeAll_53) {
    Value v("hello\nworld");
    std::ostringstream output;
    v.writeToStream(output, false, true);
    std::string result = output.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_53, StreamConstructor_53) {
    std::istringstream stream("42");
    Value v(stream);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_53, EqualityBetweenDifferentTypes_53) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_53, SelfAssignment_53) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_53, NullEqualityBothNull_53) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_53, ComplexNestedStructure_53) {
    Value v;
    v.loadFromString("{\"arr\": [1, 2, {\"nested\": true}]}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["arr"].isArray());
    EXPECT_EQ(v["arr"].getArray().size(), 3u);
}
