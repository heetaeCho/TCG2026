#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueTest_37 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(ValueTest_37, DefaultConstructor_IsNull_37) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_37, StringConstructor_IsString_37) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_37, CStringConstructor_IsString_37) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_37, IntConstructor_IsInteger_37) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_37, DoubleConstructor_IsDouble_37) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_37, BoolConstructor_IsBoolean_37) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_37, BoolConstructorFalse_IsBoolean_37) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_37, ObjectConstructor_IsObject_37) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_37, ArrayConstructor_IsArray_37) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_37, CopyConstructor_CopiesCorrectly_37) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

TEST_F(ValueTest_37, StreamConstructor_ParsesJson_37) {
    std::istringstream input("\"hello\"");
    Value v(input);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

// ==================== isNumeric Tests ====================

TEST_F(ValueTest_37, IsNumeric_Integer_ReturnsTrue_37) {
    Value v(10);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_37, IsNumeric_Double_ReturnsTrue_37) {
    Value v(2.5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_37, IsNumeric_String_ReturnsFalse_37) {
    Value v("123");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_37, IsNumeric_Boolean_ReturnsFalse_37) {
    Value v(true);
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_37, IsNumeric_Null_ReturnsFalse_37) {
    Value v;
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_37, IsNumeric_Object_ReturnsFalse_37) {
    Value v(Object());
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_37, IsNumeric_Array_ReturnsFalse_37) {
    Value v(Array());
    EXPECT_FALSE(v.isNumeric());
}

// ==================== Type Query Tests ====================

TEST_F(ValueTest_37, IsString_ForString_ReturnsTrue_37) {
    Value v("test");
    EXPECT_TRUE(v.isString());
}

TEST_F(ValueTest_37, IsString_ForInt_ReturnsFalse_37) {
    Value v(5);
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_37, IsInteger_ForInt_ReturnsTrue_37) {
    Value v(5);
    EXPECT_TRUE(v.isInteger());
}

TEST_F(ValueTest_37, IsInteger_ForDouble_ReturnsFalse_37) {
    Value v(5.0);
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_37, IsDouble_ForDouble_ReturnsTrue_37) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
}

TEST_F(ValueTest_37, IsDouble_ForInt_ReturnsFalse_37) {
    Value v(1);
    EXPECT_FALSE(v.isDouble());
}

TEST_F(ValueTest_37, IsObject_ForObject_ReturnsTrue_37) {
    Value v(Object());
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_37, IsArray_ForArray_ReturnsTrue_37) {
    Value v(Array());
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_37, IsBoolean_ForBool_ReturnsTrue_37) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
}

TEST_F(ValueTest_37, IsNull_ForDefault_ReturnsTrue_37) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_37, IsNull_ForInt_ReturnsFalse_37) {
    Value v(0);
    EXPECT_FALSE(v.isNull());
}

// ==================== getType Tests ====================

TEST_F(ValueTest_37, GetType_String_37) {
    Value v("hello");
    EXPECT_EQ(v.getType(), Value::STRING);
}

TEST_F(ValueTest_37, GetType_Integer_37) {
    Value v(42);
    EXPECT_EQ(v.getType(), Value::INTEGER);
}

TEST_F(ValueTest_37, GetType_Double_37) {
    Value v(3.14);
    EXPECT_EQ(v.getType(), Value::DOUBLE);
}

TEST_F(ValueTest_37, GetType_Object_37) {
    Value v(Object());
    EXPECT_EQ(v.getType(), Value::OBJECT);
}

TEST_F(ValueTest_37, GetType_Array_37) {
    Value v(Array());
    EXPECT_EQ(v.getType(), Value::ARRAY);
}

TEST_F(ValueTest_37, GetType_Boolean_37) {
    Value v(true);
    EXPECT_EQ(v.getType(), Value::BOOLEAN);
}

TEST_F(ValueTest_37, GetType_Null_37) {
    Value v;
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

// ==================== Getter/Setter Tests ====================

TEST_F(ValueTest_37, SetString_ChangesType_37) {
    Value v(42);
    v.setString("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST_F(ValueTest_37, SetInteger_ChangesType_37) {
    Value v("hello");
    v.setInteger(100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST_F(ValueTest_37, SetDouble_ChangesType_37) {
    Value v("hello");
    v.setDouble(9.81);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 9.81);
}

TEST_F(ValueTest_37, SetBoolean_ChangesType_37) {
    Value v(42);
    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_37, SetNull_ChangesType_37) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_37, SetObject_ChangesType_37) {
    Value v(42);
    Object obj;
    obj["key"] = Value("val");
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_37, SetArray_ChangesType_37) {
    Value v(42);
    Array arr;
    arr.push_back(Value(1));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_37, GetFloat_ReturnsCorrectValue_37) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 2.5f);
}

// ==================== tryGet Tests ====================

TEST_F(ValueTest_37, TryGetString_WhenString_ReturnsValue_37) {
    Value v("hello");
    EXPECT_EQ(v.tryGetString("default"), "hello");
}

TEST_F(ValueTest_37, TryGetString_WhenNotString_ReturnsDefault_37) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_37, TryGetInteger_WhenInteger_ReturnsValue_37) {
    Value v(42);
    EXPECT_EQ(v.tryGetInteger(0), 42);
}

TEST_F(ValueTest_37, TryGetInteger_WhenNotInteger_ReturnsDefault_37) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(99), 99);
}

TEST_F(ValueTest_37, TryGetDouble_WhenDouble_ReturnsValue_37) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 3.14);
}

TEST_F(ValueTest_37, TryGetDouble_WhenNotDouble_ReturnsDefault_37) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.0), 1.0);
}

TEST_F(ValueTest_37, TryGetFloat_WhenDouble_ReturnsValue_37) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST_F(ValueTest_37, TryGetFloat_WhenNotDouble_ReturnsDefault_37) {
    Value v("hello");
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.5f), 1.5f);
}

TEST_F(ValueTest_37, TryGetBoolean_WhenBoolean_ReturnsValue_37) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_37, TryGetBoolean_WhenNotBoolean_ReturnsDefault_37) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ==================== Assignment Operator Tests ====================

TEST_F(ValueTest_37, AssignmentFromValue_37) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_37, AssignmentFromString_37) {
    Value v(42);
    v = std::string("hello");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_37, AssignmentFromCString_37) {
    Value v(42);
    v = "world";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_37, AssignmentFromInt_37) {
    Value v("hello");
    v = 99;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_37, AssignmentFromDouble_37) {
    Value v("hello");
    v = 1.23;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.23);
}

TEST_F(ValueTest_37, AssignmentFromBool_37) {
    Value v("hello");
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_37, AssignmentFromObject_37) {
    Value v(42);
    Object obj;
    obj["a"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_37, AssignmentFromArray_37) {
    Value v(42);
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

// ==================== Comparison Operator Tests ====================

TEST_F(ValueTest_37, EqualityOperator_SameInt_37) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_37, EqualityOperator_DifferentInt_37) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_37, InequalityOperator_DifferentValues_37) {
    Value v1(42);
    Value v2(43);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_37, InequalityOperator_SameValues_37) {
    Value v1(42);
    Value v2(42);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueTest_37, LessThanOperator_Ints_37) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_37, LessThanOrEqualOperator_37) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_37, GreaterThanOperator_37) {
    Value v1(5);
    Value v2(3);
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v2 > v1);
}

TEST_F(ValueTest_37, GreaterThanOrEqualOperator_37) {
    Value v1(5);
    Value v2(5);
    EXPECT_TRUE(v1 >= v2);
}

TEST_F(ValueTest_37, EqualityOperator_DifferentTypes_37) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

// ==================== Subscript Operator Tests ====================

TEST_F(ValueTest_37, SubscriptString_CreatesObject_37) {
    Value v;
    v["key"] = Value(42);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_37, SubscriptCString_CreatesObject_37) {
    Value v;
    const char* key = "mykey";
    v[key] = Value("value");
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_37, SubscriptIndex_OnArray_37) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

// ==================== isStringable Tests ====================

TEST_F(ValueTest_37, IsStringable_ForString_ReturnsTrue_37) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_37, IsStringable_ForInt_37) {
    Value v(42);
    // Integer might be stringable (can be converted to string)
    // Test based on observed behavior
    bool result = v.isStringable();
    // Just ensure it doesn't crash; exact behavior depends on implementation
    (void)result;
}

// ==================== getToString Tests ====================

TEST_F(ValueTest_37, GetToString_FromString_37) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

TEST_F(ValueTest_37, GetToString_FromInt_37) {
    Value v(42);
    std::string result = v.getToString();
    // Should contain "42" in some form
    EXPECT_FALSE(result.empty());
}

// ==================== Load/Write Tests ====================

TEST_F(ValueTest_37, LoadFromString_Integer_37) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_37, LoadFromString_Double_37) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_37, LoadFromString_String_37) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_37, LoadFromString_Boolean_True_37) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_37, LoadFromString_Boolean_False_37) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_37, LoadFromString_Null_37) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_37, LoadFromString_Object_37) {
    Value v;
    v.loadFromString("{\"key\": 42}");
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_37, LoadFromString_Array_37) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_37, LoadFromStream_37) {
    std::istringstream input("{\"a\": 1}");
    Value v;
    v.loadFromStream(input);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_37, WriteToStream_Integer_37) {
    Value v(42);
    std::ostringstream output;
    v.writeToStream(output, false, false);
    std::string result = output.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("42"), std::string::npos);
}

TEST_F(ValueTest_37, WriteToStream_String_37) {
    Value v("hello");
    std::ostringstream output;
    v.writeToStream(output, false, false);
    std::string result = output.str();
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(ValueTest_37, WriteToStream_WithIndent_37) {
    Value v;
    v.loadFromString("{\"key\": 42}");
    std::ostringstream output;
    v.writeToStream(output, true, false);
    std::string result = output.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_37, WriteToStream_Null_37) {
    Value v;
    std::ostringstream output;
    v.writeToStream(output, false, false);
    std::string result = output.str();
    EXPECT_NE(result.find("null"), std::string::npos);
}

TEST_F(ValueTest_37, WriteToStream_Boolean_37) {
    Value v(true);
    std::ostringstream output;
    v.writeToStream(output, false, false);
    std::string result = output.str();
    EXPECT_NE(result.find("true"), std::string::npos);
}

// ==================== Escape Tests ====================

TEST_F(ValueTest_37, EscapeMinimumCharacters_NoSpecialChars_37) {
    std::string result = Value::escapeMinimumCharacters("hello");
    EXPECT_EQ(result, "hello");
}

TEST_F(ValueTest_37, EscapeMinimumCharacters_WithQuote_37) {
    std::string result = Value::escapeMinimumCharacters("he\"llo");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_37, EscapeMinimumCharacters_WithBackslash_37) {
    std::string result = Value::escapeMinimumCharacters("he\\llo");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST_F(ValueTest_37, EscapeAllCharacters_NoSpecialChars_37) {
    std::string result = Value::escapeAllCharacters("hello");
    // Basic ASCII should remain or be escaped to unicode
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_37, EscapeToUnicode_37) {
    std::string result = Value::escapeToUnicode('A');
    // Should produce a unicode escape sequence like \u0041
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ==================== Boundary/Edge Cases ====================

TEST_F(ValueTest_37, IntConstructor_Zero_37) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_37, IntConstructor_Negative_37) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST_F(ValueTest_37, DoubleConstructor_Zero_37) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_37, DoubleConstructor_Negative_37) {
    Value v(-1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -1.5);
}

TEST_F(ValueTest_37, EmptyString_37) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_37, EmptyObject_37) {
    Value v(Object());
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v.getObject().empty());
}

TEST_F(ValueTest_37, EmptyArray_37) {
    Value v(Array());
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v.getArray().empty());
}

TEST_F(ValueTest_37, LoadFromString_EmptyObject_37) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v.getObject().empty());
}

TEST_F(ValueTest_37, LoadFromString_EmptyArray_37) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v.getArray().empty());
}

TEST_F(ValueTest_37, LoadFromString_NestedObject_37) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": 42}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

TEST_F(ValueTest_37, LoadFromString_NestedArray_37) {
    Value v;
    v.loadFromString("[[1, 2], [3, 4]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_37, OperatorOutput_37) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

TEST_F(ValueTest_37, LoadFromString_NegativeInteger_37) {
    Value v;
    v.loadFromString("-42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST_F(ValueTest_37, LoadFromString_NegativeDouble_37) {
    Value v;
    v.loadFromString("-3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -3.14);
}

TEST_F(ValueTest_37, SetNull_ThenSetInteger_37) {
    Value v;
    EXPECT_TRUE(v.isNull());
    v.setInteger(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 10);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_37, SelfAssignment_37) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_37, ObjectAccess_MultipleKeys_37) {
    Value v;
    v["a"] = Value(1);
    v["b"] = Value(2);
    v["c"] = Value(3);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["a"].getInteger(), 1);
    EXPECT_EQ(v["b"].getInteger(), 2);
    EXPECT_EQ(v["c"].getInteger(), 3);
}

TEST_F(ValueTest_37, LoadFromString_StringWithEscapes_37) {
    Value v;
    v.loadFromString("\"hello\\nworld\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello\nworld");
}

TEST_F(ValueTest_37, LargeInteger_37) {
    Value v(2147483647); // INT_MAX
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST_F(ValueTest_37, WriteToStream_EscapeAll_37) {
    Value v("hello\nworld");
    std::ostringstream output;
    v.writeToStream(output, false, true);
    std::string result = output.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_37, ComparisonBetweenDifferentTypes_37) {
    Value vInt(42);
    Value vStr("hello");
    // Different types - they should not be equal
    EXPECT_TRUE(vInt != vStr);
}
