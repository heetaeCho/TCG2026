#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

// ============================================================================
// Test fixture
// ============================================================================
class ValueTest_50 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================================
// Construction tests
// ============================================================================

TEST_F(ValueTest_50, DefaultConstructor_IsNull_50) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(Value::NULL_VALUE, v.getType());
}

TEST_F(ValueTest_50, StringConstructor_SetsString_50) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("hello", v.getString());
}

TEST_F(ValueTest_50, CStringConstructor_SetsString_50) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("world", v.getString());
}

TEST_F(ValueTest_50, IntConstructor_SetsInteger_50) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(42, v.getInteger());
}

TEST_F(ValueTest_50, DoubleConstructor_SetsDouble_50) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(3.14, v.getDouble());
}

TEST_F(ValueTest_50, BoolConstructor_SetsBoolean_50) {
    Value vTrue(true);
    EXPECT_TRUE(vTrue.isBoolean());
    EXPECT_TRUE(vTrue.getBoolean());

    Value vFalse(false);
    EXPECT_TRUE(vFalse.isBoolean());
    EXPECT_FALSE(vFalse.getBoolean());
}

TEST_F(ValueTest_50, ObjectConstructor_SetsObject_50) {
    Object obj;
    obj["key"] = Value(123);
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(1u, v.getObject().size());
}

TEST_F(ValueTest_50, ArrayConstructor_SetsArray_50) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(2u, v.getArray().size());
}

TEST_F(ValueTest_50, CopyConstructor_CopiesValue_50) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(42, copy.getInteger());
}

// ============================================================================
// Type checking tests
// ============================================================================

TEST_F(ValueTest_50, IsString_TrueForString_50) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_50, IsInteger_TrueForInt_50) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
}

TEST_F(ValueTest_50, IsDouble_TrueForDouble_50) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_50, IsNumeric_TrueForIntAndDouble_50) {
    Value vi(5);
    EXPECT_TRUE(vi.isNumeric());

    Value vd(5.5);
    EXPECT_TRUE(vd.isNumeric());

    Value vs("not numeric");
    EXPECT_FALSE(vs.isNumeric());
}

TEST_F(ValueTest_50, IsNull_TrueForDefault_50) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

// ============================================================================
// tryGetDouble tests (the focal method)
// ============================================================================

TEST_F(ValueTest_50, TryGetDouble_ReturnsDoubleWhenDouble_50) {
    Value v(2.718);
    EXPECT_DOUBLE_EQ(2.718, v.tryGetDouble(0.0));
}

TEST_F(ValueTest_50, TryGetDouble_ReturnsIntAsDoubleWhenInteger_50) {
    Value v(42);
    EXPECT_DOUBLE_EQ(42.0, v.tryGetDouble(0.0));
}

TEST_F(ValueTest_50, TryGetDouble_ReturnsDefaultForString_50) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(-1.0, v.tryGetDouble(-1.0));
}

TEST_F(ValueTest_50, TryGetDouble_ReturnsDefaultForNull_50) {
    Value v;
    EXPECT_DOUBLE_EQ(99.9, v.tryGetDouble(99.9));
}

TEST_F(ValueTest_50, TryGetDouble_ReturnsDefaultForBoolean_50) {
    Value v(true);
    EXPECT_DOUBLE_EQ(5.5, v.tryGetDouble(5.5));
}

TEST_F(ValueTest_50, TryGetDouble_ReturnsDefaultForObject_50) {
    Object obj;
    Value v(obj);
    EXPECT_DOUBLE_EQ(7.7, v.tryGetDouble(7.7));
}

TEST_F(ValueTest_50, TryGetDouble_ReturnsDefaultForArray_50) {
    Array arr;
    Value v(arr);
    EXPECT_DOUBLE_EQ(3.3, v.tryGetDouble(3.3));
}

TEST_F(ValueTest_50, TryGetDouble_ZeroDouble_50) {
    Value v(0.0);
    EXPECT_DOUBLE_EQ(0.0, v.tryGetDouble(999.0));
}

TEST_F(ValueTest_50, TryGetDouble_NegativeDouble_50) {
    Value v(-123.456);
    EXPECT_DOUBLE_EQ(-123.456, v.tryGetDouble(0.0));
}

TEST_F(ValueTest_50, TryGetDouble_NegativeInteger_50) {
    Value v(-100);
    EXPECT_DOUBLE_EQ(-100.0, v.tryGetDouble(0.0));
}

TEST_F(ValueTest_50, TryGetDouble_ZeroInteger_50) {
    Value v(0);
    EXPECT_DOUBLE_EQ(0.0, v.tryGetDouble(999.0));
}

TEST_F(ValueTest_50, TryGetDouble_LargeInteger_50) {
    Value v(2147483647);  // INT_MAX
    EXPECT_DOUBLE_EQ(2147483647.0, v.tryGetDouble(0.0));
}

TEST_F(ValueTest_50, TryGetDouble_DefaultZero_50) {
    Value v("string");
    EXPECT_DOUBLE_EQ(0.0, v.tryGetDouble(0.0));
}

// ============================================================================
// tryGetInteger tests
// ============================================================================

TEST_F(ValueTest_50, TryGetInteger_ReturnsIntForInt_50) {
    Value v(10);
    EXPECT_EQ(10, v.tryGetInteger(0));
}

TEST_F(ValueTest_50, TryGetInteger_ReturnsDefaultForString_50) {
    Value v("test");
    EXPECT_EQ(-1, v.tryGetInteger(-1));
}

TEST_F(ValueTest_50, TryGetInteger_ReturnsDefaultForNull_50) {
    Value v;
    EXPECT_EQ(42, v.tryGetInteger(42));
}

// ============================================================================
// tryGetString tests
// ============================================================================

TEST_F(ValueTest_50, TryGetString_ReturnsStringForString_50) {
    Value v("hello");
    EXPECT_EQ("hello", v.tryGetString("default"));
}

TEST_F(ValueTest_50, TryGetString_ReturnsDefaultForInt_50) {
    Value v(42);
    EXPECT_EQ("default", v.tryGetString("default"));
}

TEST_F(ValueTest_50, TryGetString_ReturnsDefaultForNull_50) {
    Value v;
    EXPECT_EQ("fallback", v.tryGetString("fallback"));
}

// ============================================================================
// tryGetFloat tests
// ============================================================================

TEST_F(ValueTest_50, TryGetFloat_ReturnsFloatForDouble_50) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(1.5f, v.tryGetFloat(0.0f));
}

TEST_F(ValueTest_50, TryGetFloat_ReturnsDefaultForString_50) {
    Value v("str");
    EXPECT_FLOAT_EQ(9.9f, v.tryGetFloat(9.9f));
}

// ============================================================================
// tryGetBoolean tests
// ============================================================================

TEST_F(ValueTest_50, TryGetBoolean_ReturnsBoolForBool_50) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_50, TryGetBoolean_ReturnsDefaultForInt_50) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ============================================================================
// Assignment operator tests
// ============================================================================

TEST_F(ValueTest_50, AssignmentFromValue_50) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(42, v2.getInteger());
}

TEST_F(ValueTest_50, AssignmentFromString_50) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("assigned", v.getString());
}

TEST_F(ValueTest_50, AssignmentFromCString_50) {
    Value v;
    v = "cstr";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("cstr", v.getString());
}

TEST_F(ValueTest_50, AssignmentFromInt_50) {
    Value v;
    v = 99;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(99, v.getInteger());
}

TEST_F(ValueTest_50, AssignmentFromDouble_50) {
    Value v;
    v = 1.23;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(1.23, v.getDouble());
}

TEST_F(ValueTest_50, AssignmentFromBool_50) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_50, AssignmentFromObject_50) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_50, AssignmentFromArray_50) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

// ============================================================================
// Setter tests
// ============================================================================

TEST_F(ValueTest_50, SetString_ChangesType_50) {
    Value v(42);
    v.setString("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("now a string", v.getString());
}

TEST_F(ValueTest_50, SetInteger_ChangesType_50) {
    Value v("was string");
    v.setInteger(100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(100, v.getInteger());
}

TEST_F(ValueTest_50, SetDouble_ChangesType_50) {
    Value v;
    v.setDouble(6.28);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(6.28, v.getDouble());
}

TEST_F(ValueTest_50, SetBoolean_ChangesType_50) {
    Value v(42);
    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_50, SetNull_ChangesType_50) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_50, SetObject_ChangesType_50) {
    Value v(42);
    Object obj;
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_50, SetArray_ChangesType_50) {
    Value v(42);
    Array arr;
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
}

// ============================================================================
// Comparison operator tests
// ============================================================================

TEST_F(ValueTest_50, EqualityOperator_SameInts_50) {
    Value v1(10);
    Value v2(10);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueTest_50, EqualityOperator_DifferentInts_50) {
    Value v1(10);
    Value v2(20);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_50, EqualityOperator_DifferentTypes_50) {
    Value v1(10);
    Value v2("10");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_50, LessThanOperator_Ints_50) {
    Value v1(5);
    Value v2(10);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_50, LessThanOrEqual_Ints_50) {
    Value v1(5);
    Value v2(5);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_50, GreaterThanOperator_Ints_50) {
    Value v1(10);
    Value v2(5);
    EXPECT_TRUE(v1 > v2);
}

TEST_F(ValueTest_50, GreaterThanOrEqual_Ints_50) {
    Value v1(5);
    Value v2(5);
    EXPECT_TRUE(v1 >= v2);
}

// ============================================================================
// Subscript operator tests
// ============================================================================

TEST_F(ValueTest_50, SubscriptByStringKey_ObjectAccess_50) {
    Object obj;
    obj["name"] = Value("test");
    Value v(obj);
    EXPECT_EQ("test", v["name"].getString());
}

TEST_F(ValueTest_50, SubscriptByCStringKey_ObjectAccess_50) {
    Object obj;
    obj["key"] = Value(42);
    Value v(obj);
    EXPECT_EQ(42, v["key"].getInteger());
}

TEST_F(ValueTest_50, SubscriptByIndex_ArrayAccess_50) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    Value v(arr);
    EXPECT_EQ(10, v[(size_t)0].getInteger());
    EXPECT_EQ(20, v[(size_t)1].getInteger());
}

// ============================================================================
// getType tests
// ============================================================================

TEST_F(ValueTest_50, GetType_ReturnsCorrectTypes_50) {
    EXPECT_EQ(Value::STRING, Value("str").getType());
    EXPECT_EQ(Value::INTEGER, Value(1).getType());
    EXPECT_EQ(Value::DOUBLE, Value(1.0).getType());
    EXPECT_EQ(Value::BOOLEAN, Value(true).getType());
    EXPECT_EQ(Value::NULL_VALUE, Value().getType());
    EXPECT_EQ(Value::OBJECT, Value(Object()).getType());
    EXPECT_EQ(Value::ARRAY, Value(Array()).getType());
}

// ============================================================================
// Getter tests
// ============================================================================

TEST_F(ValueTest_50, GetString_ReturnsString_50) {
    Value v("hello");
    EXPECT_EQ("hello", v.getString());
}

TEST_F(ValueTest_50, GetInteger_ReturnsInt_50) {
    Value v(77);
    EXPECT_EQ(77, v.getInteger());
}

TEST_F(ValueTest_50, GetDouble_ReturnsDouble_50) {
    Value v(1.41);
    EXPECT_DOUBLE_EQ(1.41, v.getDouble());
}

TEST_F(ValueTest_50, GetFloat_ReturnsFloat_50) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(2.5f, v.getFloat());
}

TEST_F(ValueTest_50, GetBoolean_ReturnsBool_50) {
    Value v(true);
    EXPECT_TRUE(v.getBoolean());
}

// ============================================================================
// isStringable tests
// ============================================================================

TEST_F(ValueTest_50, IsStringable_TrueForString_50) {
    Value v("test");
    EXPECT_TRUE(v.isStringable());
}

// ============================================================================
// getToString tests
// ============================================================================

TEST_F(ValueTest_50, GetToString_ForString_50) {
    Value v("hello");
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_50, GetToString_ForInt_50) {
    Value v(42);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

// ============================================================================
// Load / write tests
// ============================================================================

TEST_F(ValueTest_50, LoadFromString_SimpleInt_50) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(42, v.getInteger());
}

TEST_F(ValueTest_50, LoadFromString_SimpleString_50) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("hello", v.getString());
}

TEST_F(ValueTest_50, LoadFromString_Object_50) {
    Value v;
    v.loadFromString("{\"key\": 1}");
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_50, LoadFromString_Array_50) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(3u, v.getArray().size());
}

TEST_F(ValueTest_50, LoadFromString_BoolTrue_50) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_50, LoadFromString_BoolFalse_50) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_50, LoadFromString_Null_50) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_50, LoadFromString_Double_50) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_NEAR(3.14, v.getDouble(), 0.001);
}

TEST_F(ValueTest_50, LoadFromStream_SimpleValue_50) {
    std::istringstream iss("123");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(123, v.getInteger());
}

TEST_F(ValueTest_50, WriteToStream_Produces_Output_50) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_FALSE(oss.str().empty());
}

TEST_F(ValueTest_50, WriteToStream_WithIndent_50) {
    Object obj;
    obj["a"] = Value(1);
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    EXPECT_FALSE(oss.str().empty());
}

TEST_F(ValueTest_50, StreamConstructor_50) {
    std::istringstream iss("\"stream\"");
    Value v(iss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("stream", v.getString());
}

// ============================================================================
// Stream operator<< test
// ============================================================================

TEST_F(ValueTest_50, StreamInsertionOperator_50) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

// ============================================================================
// Escape function tests
// ============================================================================

TEST_F(ValueTest_50, EscapeMinimumCharacters_BasicString_50) {
    std::string result = Value::escapeMinimumCharacters("hello");
    EXPECT_EQ("hello", result);
}

TEST_F(ValueTest_50, EscapeMinimumCharacters_WithQuotes_50) {
    std::string result = Value::escapeMinimumCharacters("he\"llo");
    EXPECT_NE(std::string::npos, result.find("\\\""));
}

TEST_F(ValueTest_50, EscapeAllCharacters_BasicString_50) {
    std::string result = Value::escapeAllCharacters("hello");
    // All characters should be escaped to unicode
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_50, EscapeToUnicode_ReturnsNonEmpty_50) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
}

// ============================================================================
// Boundary / edge cases for tryGetDouble
// ============================================================================

TEST_F(ValueTest_50, TryGetDouble_VeryLargeDouble_50) {
    Value v(1.7976931348623157e+308);
    EXPECT_DOUBLE_EQ(1.7976931348623157e+308, v.tryGetDouble(0.0));
}

TEST_F(ValueTest_50, TryGetDouble_VerySmallDouble_50) {
    Value v(2.2250738585072014e-308);
    EXPECT_DOUBLE_EQ(2.2250738585072014e-308, v.tryGetDouble(0.0));
}

TEST_F(ValueTest_50, TryGetDouble_NegativeDefault_50) {
    Value v;
    EXPECT_DOUBLE_EQ(-999.999, v.tryGetDouble(-999.999));
}

// ============================================================================
// Copy semantics
// ============================================================================

TEST_F(ValueTest_50, CopyAssignment_DoesNotAffectOriginal_50) {
    Value v1(42);
    Value v2 = v1;
    v2 = 100;
    EXPECT_EQ(42, v1.getInteger());
    EXPECT_EQ(100, v2.getInteger());
}

TEST_F(ValueTest_50, CopiedString_Independent_50) {
    Value v1("original");
    Value v2(v1);
    v2.setString("modified");
    EXPECT_EQ("original", v1.getString());
    EXPECT_EQ("modified", v2.getString());
}

// ============================================================================
// Empty string edge case
// ============================================================================

TEST_F(ValueTest_50, EmptyString_50) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("", v.getString());
}

TEST_F(ValueTest_50, EmptyObject_50) {
    Value v(Object());
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(0u, v.getObject().size());
}

TEST_F(ValueTest_50, EmptyArray_50) {
    Value v(Array());
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(0u, v.getArray().size());
}
