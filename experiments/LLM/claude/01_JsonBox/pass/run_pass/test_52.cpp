#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

// Test fixture
class ValueTest_52 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== tryGetFloat tests ====================

TEST_F(ValueTest_52, TryGetFloat_WithDoubleValue_ReturnsFloat_52) {
    Value v(3.14);
    float result = v.tryGetFloat(0.0f);
    EXPECT_FLOAT_EQ(result, 3.14f);
}

TEST_F(ValueTest_52, TryGetFloat_WithIntegerValue_ReturnsFloatCast_52) {
    Value v(42);
    float result = v.tryGetFloat(0.0f);
    EXPECT_FLOAT_EQ(result, 42.0f);
}

TEST_F(ValueTest_52, TryGetFloat_WithStringValue_ReturnsDefault_52) {
    Value v(std::string("hello"));
    float result = v.tryGetFloat(99.5f);
    EXPECT_FLOAT_EQ(result, 99.5f);
}

TEST_F(ValueTest_52, TryGetFloat_WithNullValue_ReturnsDefault_52) {
    Value v;
    float result = v.tryGetFloat(-1.0f);
    EXPECT_FLOAT_EQ(result, -1.0f);
}

TEST_F(ValueTest_52, TryGetFloat_WithBooleanValue_ReturnsDefault_52) {
    Value v(true);
    float result = v.tryGetFloat(7.7f);
    EXPECT_FLOAT_EQ(result, 7.7f);
}

TEST_F(ValueTest_52, TryGetFloat_WithObjectValue_ReturnsDefault_52) {
    Object obj;
    Value v(obj);
    float result = v.tryGetFloat(5.5f);
    EXPECT_FLOAT_EQ(result, 5.5f);
}

TEST_F(ValueTest_52, TryGetFloat_WithArrayValue_ReturnsDefault_52) {
    Array arr;
    Value v(arr);
    float result = v.tryGetFloat(3.3f);
    EXPECT_FLOAT_EQ(result, 3.3f);
}

TEST_F(ValueTest_52, TryGetFloat_WithZeroDouble_ReturnsZero_52) {
    Value v(0.0);
    float result = v.tryGetFloat(1.0f);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST_F(ValueTest_52, TryGetFloat_WithZeroInteger_ReturnsZero_52) {
    Value v(0);
    float result = v.tryGetFloat(1.0f);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST_F(ValueTest_52, TryGetFloat_WithNegativeDouble_ReturnsNegativeFloat_52) {
    Value v(-2.5);
    float result = v.tryGetFloat(0.0f);
    EXPECT_FLOAT_EQ(result, -2.5f);
}

TEST_F(ValueTest_52, TryGetFloat_WithNegativeInteger_ReturnsNegativeFloat_52) {
    Value v(-10);
    float result = v.tryGetFloat(0.0f);
    EXPECT_FLOAT_EQ(result, -10.0f);
}

TEST_F(ValueTest_52, TryGetFloat_WithLargeDouble_ReturnsFloat_52) {
    Value v(1.0e30);
    float result = v.tryGetFloat(0.0f);
    EXPECT_FLOAT_EQ(result, static_cast<float>(1.0e30));
}

TEST_F(ValueTest_52, TryGetFloat_WithDefaultZero_52) {
    Value v(std::string("not a number"));
    float result = v.tryGetFloat(0.0f);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

// ==================== Constructor tests ====================

TEST_F(ValueTest_52, DefaultConstructor_IsNull_52) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_52, StringConstructor_IsString_52) {
    Value v(std::string("test"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

TEST_F(ValueTest_52, CStringConstructor_IsString_52) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

TEST_F(ValueTest_52, IntConstructor_IsInteger_52) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_52, DoubleConstructor_IsDouble_52) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_52, BoolConstructor_IsBoolean_52) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_52, ObjectConstructor_IsObject_52) {
    Object obj;
    obj["key"] = Value(1);
    Value v(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_52, ArrayConstructor_IsArray_52) {
    Array arr;
    arr.push_back(Value(1));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
}

// ==================== Copy constructor and assignment ====================

TEST_F(ValueTest_52, CopyConstructor_CopiesValue_52) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

TEST_F(ValueTest_52, AssignmentOperator_CopiesValue_52) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_52, AssignString_52) {
    Value v;
    v = std::string("hello");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_52, AssignCString_52) {
    Value v;
    v = "hello";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_52, AssignInt_52) {
    Value v;
    v = 100;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST_F(ValueTest_52, AssignDouble_52) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_52, AssignBool_52) {
    Value v;
    v = false;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

// ==================== Type checking tests ====================

TEST_F(ValueTest_52, GetType_Integer_52) {
    Value v(5);
    EXPECT_EQ(v.getType(), Value::INTEGER);
}

TEST_F(ValueTest_52, GetType_Double_52) {
    Value v(5.0);
    EXPECT_EQ(v.getType(), Value::DOUBLE);
}

TEST_F(ValueTest_52, GetType_String_52) {
    Value v(std::string("abc"));
    EXPECT_EQ(v.getType(), Value::STRING);
}

TEST_F(ValueTest_52, GetType_Null_52) {
    Value v;
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_52, GetType_Boolean_52) {
    Value v(true);
    EXPECT_EQ(v.getType(), Value::BOOLEAN);
}

TEST_F(ValueTest_52, IsNumeric_Integer_52) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_52, IsNumeric_Double_52) {
    Value v(5.0);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_52, IsNumeric_String_52) {
    Value v(std::string("5"));
    EXPECT_FALSE(v.isNumeric());
}

// ==================== tryGetInteger tests ====================

TEST_F(ValueTest_52, TryGetInteger_WithInteger_ReturnsValue_52) {
    Value v(42);
    EXPECT_EQ(v.tryGetInteger(0), 42);
}

TEST_F(ValueTest_52, TryGetInteger_WithString_ReturnsDefault_52) {
    Value v(std::string("hello"));
    EXPECT_EQ(v.tryGetInteger(99), 99);
}

TEST_F(ValueTest_52, TryGetInteger_WithNull_ReturnsDefault_52) {
    Value v;
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

// ==================== tryGetDouble tests ====================

TEST_F(ValueTest_52, TryGetDouble_WithDouble_ReturnsValue_52) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 3.14);
}

TEST_F(ValueTest_52, TryGetDouble_WithString_ReturnsDefault_52) {
    Value v(std::string("hello"));
    EXPECT_DOUBLE_EQ(v.tryGetDouble(99.9), 99.9);
}

// ==================== tryGetString tests ====================

TEST_F(ValueTest_52, TryGetString_WithString_ReturnsValue_52) {
    Value v(std::string("hello"));
    EXPECT_EQ(v.tryGetString("default"), "hello");
}

TEST_F(ValueTest_52, TryGetString_WithInteger_ReturnsDefault_52) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

// ==================== tryGetBoolean tests ====================

TEST_F(ValueTest_52, TryGetBoolean_WithBoolean_ReturnsValue_52) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_52, TryGetBoolean_WithString_ReturnsDefault_52) {
    Value v(std::string("hello"));
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ==================== Setter tests ====================

TEST_F(ValueTest_52, SetString_ChangesType_52) {
    Value v(42);
    v.setString("changed");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "changed");
}

TEST_F(ValueTest_52, SetInteger_ChangesType_52) {
    Value v(std::string("hello"));
    v.setInteger(100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST_F(ValueTest_52, SetDouble_ChangesType_52) {
    Value v(std::string("hello"));
    v.setDouble(2.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.5);
}

TEST_F(ValueTest_52, SetBoolean_ChangesType_52) {
    Value v(42);
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_52, SetNull_ChangesType_52) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_52, SetObject_ChangesType_52) {
    Value v(42);
    Object obj;
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_52, SetArray_ChangesType_52) {
    Value v(42);
    Array arr;
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
}

// ==================== Comparison operators ====================

TEST_F(ValueTest_52, EqualityOperator_SameIntegers_52) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_52, EqualityOperator_DifferentIntegers_52) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_52, InequalityOperator_DifferentIntegers_52) {
    Value v1(42);
    Value v2(43);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_52, LessThanOperator_Integers_52) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_52, LessThanOrEqualOperator_52) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_52, GreaterThanOperator_52) {
    Value v1(2);
    Value v2(1);
    EXPECT_TRUE(v1 > v2);
}

TEST_F(ValueTest_52, GreaterThanOrEqualOperator_52) {
    Value v1(2);
    Value v2(2);
    EXPECT_TRUE(v1 >= v2);
}

// ==================== Subscript operators ====================

TEST_F(ValueTest_52, SubscriptStringKey_OnObject_52) {
    Object obj;
    obj["key"] = Value(42);
    Value v(obj);
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST_F(ValueTest_52, SubscriptCStringKey_OnObject_52) {
    Object obj;
    obj["key"] = Value(42);
    Value v(obj);
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST_F(ValueTest_52, SubscriptIndex_OnArray_52) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
}

// ==================== getFloat tests ====================

TEST_F(ValueTest_52, GetFloat_WithDouble_52) {
    Value v(3.14);
    float result = v.getFloat();
    EXPECT_FLOAT_EQ(result, 3.14f);
}

// ==================== Load and Write tests ====================

TEST_F(ValueTest_52, LoadFromString_SimpleObject_52) {
    Value v;
    v.loadFromString("{\"key\": 42}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST_F(ValueTest_52, LoadFromString_SimpleArray_52) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_52, LoadFromStream_52) {
    std::istringstream ss("{\"a\": 1}");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_52, WriteToStream_52) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTest_52, StreamConstructor_52) {
    std::istringstream ss("42");
    Value v(ss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

// ==================== getToString tests ====================

TEST_F(ValueTest_52, GetToString_Integer_52) {
    Value v(42);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_52, GetToString_Double_52) {
    Value v(3.14);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

// ==================== isStringable tests ====================

TEST_F(ValueTest_52, IsStringable_String_52) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_52, IsStringable_Integer_52) {
    Value v(42);
    // Integer might be stringable depending on implementation
    // Just ensure it doesn't crash
    v.isStringable();
}

// ==================== Boundary tests for tryGetFloat ====================

TEST_F(ValueTest_52, TryGetFloat_MaxInt_52) {
    Value v(2147483647);  // INT_MAX
    float result = v.tryGetFloat(0.0f);
    EXPECT_FLOAT_EQ(result, static_cast<float>(2147483647));
}

TEST_F(ValueTest_52, TryGetFloat_MinInt_52) {
    Value v(-2147483647);
    float result = v.tryGetFloat(0.0f);
    EXPECT_FLOAT_EQ(result, static_cast<float>(-2147483647));
}

TEST_F(ValueTest_52, TryGetFloat_VerySmallDouble_52) {
    Value v(1.0e-38);
    float result = v.tryGetFloat(0.0f);
    EXPECT_FLOAT_EQ(result, static_cast<float>(1.0e-38));
}

// ==================== Escape function tests ====================

TEST_F(ValueTest_52, EscapeMinimumCharacters_BasicString_52) {
    std::string result = Value::escapeMinimumCharacters("hello");
    EXPECT_EQ(result, "hello");
}

TEST_F(ValueTest_52, EscapeMinimumCharacters_WithQuotes_52) {
    std::string result = Value::escapeMinimumCharacters("he\"llo");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_52, EscapeAllCharacters_BasicString_52) {
    std::string result = Value::escapeAllCharacters("hello");
    // Result should contain escaped unicode for each character
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_52, EscapeToUnicode_52) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
}

// ==================== Output operator test ====================

TEST_F(ValueTest_52, OutputOperator_52) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

// ==================== Mixed type reassignment ====================

TEST_F(ValueTest_52, ReassignFromIntToString_52) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v = std::string("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST_F(ValueTest_52, ReassignFromStringToNull_52) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_52, TryGetFloat_AfterReassignment_52) {
    Value v(42);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 42.0f);
    v = std::string("not a number");
    EXPECT_FLOAT_EQ(v.tryGetFloat(99.0f), 99.0f);
    v = 3.14;
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 3.14f);
}

// ==================== Equality across types ====================

TEST_F(ValueTest_52, EqualityOperator_DifferentTypes_52) {
    Value v1(42);
    Value v2(std::string("42"));
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_52, EqualityOperator_NullValues_52) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}
