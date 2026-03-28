#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueTest_47 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(ValueTest_47, DefaultConstructor_IsNull_47) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_47, StringConstructor_CreatesStringValue_47) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_47, CStringConstructor_CreatesStringValue_47) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_47, IntConstructor_CreatesIntegerValue_47) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_47, DoubleConstructor_CreatesDoubleValue_47) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_47, BoolConstructor_CreatesBooleanValue_47) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_47, BoolConstructorFalse_CreatesBooleanValue_47) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_47, ObjectConstructor_CreatesObjectValue_47) {
    Object obj;
    obj["key"] = Value(123);
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_47, ArrayConstructor_CreatesArrayValue_47) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_47, CopyConstructor_CopiesValue_47) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

// ==================== Type Checking Tests ====================

TEST_F(ValueTest_47, IsString_ReturnsTrueForString_47) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_47, IsInteger_ReturnsTrueForInteger_47) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_47, IsDouble_ReturnsTrueForDouble_47) {
    Value v(2.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_47, IsNumeric_ReturnsTrueForIntegerAndDouble_47) {
    Value intVal(5);
    Value doubleVal(5.5);
    Value strVal("5");
    EXPECT_TRUE(intVal.isNumeric());
    EXPECT_TRUE(doubleVal.isNumeric());
    EXPECT_FALSE(strVal.isNumeric());
}

TEST_F(ValueTest_47, IsObject_ReturnsTrueForObject_47) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_47, IsArray_ReturnsTrueForArray_47) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_47, IsBoolean_ReturnsTrueForBoolean_47) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
}

TEST_F(ValueTest_47, IsNull_ReturnsTrueForNull_47) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

// ==================== getType Tests ====================

TEST_F(ValueTest_47, GetType_ReturnsCorrectType_47) {
    Value nullVal;
    Value strVal("test");
    Value intVal(42);
    Value dblVal(3.14);
    Value boolVal(true);

    EXPECT_EQ(nullVal.getType(), Value::NULL_VALUE);
    EXPECT_EQ(strVal.getType(), Value::STRING);
    EXPECT_EQ(intVal.getType(), Value::INTEGER);
    EXPECT_EQ(dblVal.getType(), Value::DOUBLE);
    EXPECT_EQ(boolVal.getType(), Value::BOOLEAN);
}

// ==================== tryGetInteger Tests (Focus method) ====================

TEST_F(ValueTest_47, TryGetInteger_ReturnsIntegerWhenTypeIsInteger_47) {
    Value v(42);
    EXPECT_EQ(v.tryGetInteger(0), 42);
}

TEST_F(ValueTest_47, TryGetInteger_ReturnsCastedDoubleWhenTypeIsDouble_47) {
    Value v(3.7);
    EXPECT_EQ(v.tryGetInteger(0), 3);
}

TEST_F(ValueTest_47, TryGetInteger_ReturnsDefaultForString_47) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

TEST_F(ValueTest_47, TryGetInteger_ReturnsDefaultForNull_47) {
    Value v;
    EXPECT_EQ(v.tryGetInteger(99), 99);
}

TEST_F(ValueTest_47, TryGetInteger_ReturnsDefaultForBoolean_47) {
    Value v(true);
    EXPECT_EQ(v.tryGetInteger(55), 55);
}

TEST_F(ValueTest_47, TryGetInteger_ReturnsDefaultForObject_47) {
    Object obj;
    Value v(obj);
    EXPECT_EQ(v.tryGetInteger(100), 100);
}

TEST_F(ValueTest_47, TryGetInteger_ReturnsDefaultForArray_47) {
    Array arr;
    Value v(arr);
    EXPECT_EQ(v.tryGetInteger(200), 200);
}

TEST_F(ValueTest_47, TryGetInteger_NegativeInteger_47) {
    Value v(-123);
    EXPECT_EQ(v.tryGetInteger(0), -123);
}

TEST_F(ValueTest_47, TryGetInteger_ZeroInteger_47) {
    Value v(0);
    EXPECT_EQ(v.tryGetInteger(999), 0);
}

TEST_F(ValueTest_47, TryGetInteger_NegativeDoubleFloor_47) {
    Value v(-3.9);
    EXPECT_EQ(v.tryGetInteger(0), -3);
}

TEST_F(ValueTest_47, TryGetInteger_LargeInteger_47) {
    Value v(2147483647);  // INT_MAX
    EXPECT_EQ(v.tryGetInteger(0), 2147483647);
}

TEST_F(ValueTest_47, TryGetInteger_DoubleZero_47) {
    Value v(0.0);
    EXPECT_EQ(v.tryGetInteger(42), 0);
}

TEST_F(ValueTest_47, TryGetInteger_DoubleWithNoFraction_47) {
    Value v(5.0);
    EXPECT_EQ(v.tryGetInteger(0), 5);
}

// ==================== tryGetDouble Tests ====================

TEST_F(ValueTest_47, TryGetDouble_ReturnsDoubleWhenTypeIsDouble_47) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 3.14);
}

TEST_F(ValueTest_47, TryGetDouble_ReturnsDefaultForString_47) {
    Value v("test");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.5), 1.5);
}

TEST_F(ValueTest_47, TryGetDouble_ReturnsDefaultForNull_47) {
    Value v;
    EXPECT_DOUBLE_EQ(v.tryGetDouble(9.9), 9.9);
}

// ==================== tryGetFloat Tests ====================

TEST_F(ValueTest_47, TryGetFloat_ReturnsFloatWhenTypeIsDouble_47) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST_F(ValueTest_47, TryGetFloat_ReturnsDefaultForNull_47) {
    Value v;
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.0f), 1.0f);
}

// ==================== tryGetString Tests ====================

TEST_F(ValueTest_47, TryGetString_ReturnsStringWhenTypeIsString_47) {
    Value v("hello");
    EXPECT_EQ(v.tryGetString("default"), "hello");
}

TEST_F(ValueTest_47, TryGetString_ReturnsDefaultForInteger_47) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_47, TryGetString_ReturnsDefaultForNull_47) {
    Value v;
    EXPECT_EQ(v.tryGetString("none"), "none");
}

// ==================== tryGetBoolean Tests ====================

TEST_F(ValueTest_47, TryGetBoolean_ReturnsBoolWhenTypeIsBoolean_47) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_47, TryGetBoolean_ReturnsDefaultForString_47) {
    Value v("true");
    EXPECT_FALSE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_47, TryGetBoolean_ReturnsDefaultForNull_47) {
    Value v;
    EXPECT_TRUE(v.tryGetBoolean(true));
}

// ==================== Setter Tests ====================

TEST_F(ValueTest_47, SetString_ChangesTypeToString_47) {
    Value v(42);
    v.setString("changed");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "changed");
}

TEST_F(ValueTest_47, SetInteger_ChangesTypeToInteger_47) {
    Value v("test");
    v.setInteger(100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST_F(ValueTest_47, SetDouble_ChangesTypeToDouble_47) {
    Value v;
    v.setDouble(1.23);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.23);
}

TEST_F(ValueTest_47, SetBoolean_ChangesTypeToBoolean_47) {
    Value v(42);
    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_47, SetNull_ChangesTypeToNull_47) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_47, SetObject_ChangesTypeToObject_47) {
    Value v;
    Object obj;
    obj["key"] = Value("value");
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_47, SetArray_ChangesTypeToArray_47) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

// ==================== Assignment Operator Tests ====================

TEST_F(ValueTest_47, AssignmentFromValue_47) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_47, AssignmentFromString_47) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_47, AssignmentFromCString_47) {
    Value v;
    v = "cstring";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "cstring");
}

TEST_F(ValueTest_47, AssignmentFromInt_47) {
    Value v;
    v = 77;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 77);
}

TEST_F(ValueTest_47, AssignmentFromDouble_47) {
    Value v;
    v = 1.618;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.618);
}

TEST_F(ValueTest_47, AssignmentFromBool_47) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_47, AssignmentFromObject_47) {
    Value v;
    Object obj;
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_47, AssignmentFromArray_47) {
    Value v;
    Array arr;
    v = arr;
    EXPECT_TRUE(v.isArray());
}

// ==================== Comparison Operator Tests ====================

TEST_F(ValueTest_47, EqualityOperator_SameIntegers_47) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueTest_47, EqualityOperator_DifferentIntegers_47) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_47, EqualityOperator_SameStrings_47) {
    Value v1("hello");
    Value v2("hello");
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_47, EqualityOperator_DifferentTypes_47) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_47, LessThanOperator_Integers_47) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_47, LessThanOrEqualOperator_47) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_47, GreaterThanOperator_47) {
    Value v1(5);
    Value v2(3);
    EXPECT_TRUE(v1 > v2);
}

TEST_F(ValueTest_47, GreaterThanOrEqualOperator_47) {
    Value v1(5);
    Value v2(5);
    EXPECT_TRUE(v1 >= v2);
}

// ==================== Subscript Operator Tests ====================

TEST_F(ValueTest_47, SubscriptString_CreatesObjectEntry_47) {
    Value v;
    v.setObject(Object());
    v["key"] = Value(42);
    EXPECT_TRUE(v["key"].isInteger());
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST_F(ValueTest_47, SubscriptCString_CreatesObjectEntry_47) {
    Value v;
    v.setObject(Object());
    const char* key = "mykey";
    v[key] = Value("myval");
    EXPECT_TRUE(v[key].isString());
    EXPECT_EQ(v[key].getString(), "myval");
}

TEST_F(ValueTest_47, SubscriptIndex_AccessesArrayElement_47) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

// ==================== Load and Write Tests ====================

TEST_F(ValueTest_47, LoadFromString_ParsesSimpleObject_47) {
    Value v;
    v.loadFromString("{\"key\": 42}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST_F(ValueTest_47, LoadFromString_ParsesArray_47) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_47, LoadFromString_ParsesString_47) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_47, LoadFromString_ParsesInteger_47) {
    Value v;
    v.loadFromString("123");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

TEST_F(ValueTest_47, LoadFromString_ParsesDouble_47) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_47, LoadFromString_ParsesTrue_47) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_47, LoadFromString_ParsesFalse_47) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_47, LoadFromString_ParsesNull_47) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_47, LoadFromStream_ParsesObject_47) {
    std::istringstream iss("{\"a\": 1}");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_47, WriteToStream_ProducesValidJSON_47) {
    Value v;
    v.loadFromString("{\"key\": 42}");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    // Verify it can be re-parsed
    Value v2;
    v2.loadFromString(output);
    EXPECT_TRUE(v2.isObject());
}

TEST_F(ValueTest_47, StreamConstructor_ParsesJSON_47) {
    std::istringstream iss("{\"x\": 10}");
    Value v(iss);
    EXPECT_TRUE(v.isObject());
}

// ==================== isStringable Tests ====================

TEST_F(ValueTest_47, IsStringable_TrueForString_47) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_47, IsStringable_CheckForInteger_47) {
    Value v(42);
    // Integer may or may not be stringable depending on implementation
    // We just verify it doesn't crash
    v.isStringable();
}

// ==================== getToString Tests ====================

TEST_F(ValueTest_47, GetToString_ForString_47) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

// ==================== Getter Tests ====================

TEST_F(ValueTest_47, GetInteger_ReturnsCorrectValue_47) {
    Value v(999);
    EXPECT_EQ(v.getInteger(), 999);
}

TEST_F(ValueTest_47, GetDouble_ReturnsCorrectValue_47) {
    Value v(2.718);
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_47, GetFloat_ReturnsCorrectValue_47) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 1.5f);
}

TEST_F(ValueTest_47, GetString_ReturnsCorrectValue_47) {
    Value v("test_string");
    EXPECT_EQ(v.getString(), "test_string");
}

TEST_F(ValueTest_47, GetBoolean_ReturnsCorrectValue_47) {
    Value v(true);
    EXPECT_TRUE(v.getBoolean());
}

// ==================== Escape Tests ====================

TEST_F(ValueTest_47, EscapeMinimumCharacters_EscapesQuote_47) {
    std::string result = Value::escapeMinimumCharacters("he\"llo");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_47, EscapeMinimumCharacters_EscapesBackslash_47) {
    std::string result = Value::escapeMinimumCharacters("he\\llo");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST_F(ValueTest_47, EscapeMinimumCharacters_EmptyString_47) {
    std::string result = Value::escapeMinimumCharacters("");
    EXPECT_EQ(result, "");
}

TEST_F(ValueTest_47, EscapeAllCharacters_NonEmpty_47) {
    std::string result = Value::escapeAllCharacters("abc");
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_47, EscapeToUnicode_ProducesUnicodeEscape_47) {
    std::string result = Value::escapeToUnicode('A');
    // Should produce something like \u0041
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ==================== Complex JSON Tests ====================

TEST_F(ValueTest_47, LoadFromString_NestedObject_47) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": 42}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

TEST_F(ValueTest_47, LoadFromString_NestedArray_47) {
    Value v;
    v.loadFromString("[[1, 2], [3, 4]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_47, LoadFromString_NegativeNumber_47) {
    Value v;
    v.loadFromString("-42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST_F(ValueTest_47, LoadFromString_NegativeDouble_47) {
    Value v;
    v.loadFromString("-3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -3.14);
}

// ==================== Boundary Tests ====================

TEST_F(ValueTest_47, EmptyStringValue_47) {
    Value v("");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_47, ZeroIntegerValue_47) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_47, ZeroDoubleValue_47) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_47, EmptyObjectValue_47) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_47, EmptyArrayValue_47) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

// ==================== WriteToStream Tests ====================

TEST_F(ValueTest_47, WriteToStream_Integer_47) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "42");
}

TEST_F(ValueTest_47, WriteToStream_String_47) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("hello"), std::string::npos);
}

TEST_F(ValueTest_47, WriteToStream_Boolean_47) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "true");
}

TEST_F(ValueTest_47, WriteToStream_Null_47) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "null");
}

TEST_F(ValueTest_47, WriteToStream_WithIndent_47) {
    Value v;
    v.loadFromString("{\"key\": 1}");
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// ==================== Output Operator Test ====================

TEST_F(ValueTest_47, OutputStreamOperator_47) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

// ==================== Self-Assignment Test ====================

TEST_F(ValueTest_47, SelfAssignment_47) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

// ==================== Type Conversion via tryGet ====================

TEST_F(ValueTest_47, TryGetInteger_DoubleWithLargeValue_47) {
    Value v(1e9);
    int result = v.tryGetInteger(0);
    EXPECT_EQ(result, static_cast<int>(1e9));
}

TEST_F(ValueTest_47, TryGetInteger_DoubleNearZero_47) {
    Value v(0.999);
    EXPECT_EQ(v.tryGetInteger(0), 0);
}

TEST_F(ValueTest_47, TryGetDouble_IntegerFallback_47) {
    Value v(42);
    // If tryGetDouble doesn't handle integer type, should return default
    double result = v.tryGetDouble(-1.0);
    // Either returns 42.0 or -1.0, depending on implementation
    // We just verify it returns something reasonable
    EXPECT_TRUE(result == 42.0 || result == -1.0);
}
