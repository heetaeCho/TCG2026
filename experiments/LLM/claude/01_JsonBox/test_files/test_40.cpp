#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueTest_40 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(ValueTest_40, DefaultConstructor_IsNull_40) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_40, StringConstructor_CreatesString_40) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_40, CStringConstructor_CreatesString_40) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_40, IntConstructor_CreatesInteger_40) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_40, DoubleConstructor_CreatesDouble_40) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_40, BoolConstructor_True_CreatesBoolean_40) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_40, BoolConstructor_False_CreatesBoolean_40) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_40, ObjectConstructor_CreatesObject_40) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_40, ArrayConstructor_CreatesArray_40) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_40, CopyConstructor_CopiesValue_40) {
    Value original(123);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 123);
}

TEST_F(ValueTest_40, StreamConstructor_ParsesJson_40) {
    std::istringstream iss("\"hello\"");
    Value v(iss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

// ==================== Type Check Tests ====================

TEST_F(ValueTest_40, IsString_ReturnsTrueForString_40) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueTest_40, IsInteger_ReturnsTrueForInteger_40) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_40, IsDouble_ReturnsTrueForDouble_40) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_40, IsBoolean_ReturnsTrueForBoolean_40) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_40, IsNull_ReturnsTrueForNull_40) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
}

TEST_F(ValueTest_40, IsObject_ReturnsTrueForObject_40) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_40, IsArray_ReturnsTrueForArray_40) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_40, IsNumeric_TrueForInteger_40) {
    Value v(42);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_40, IsNumeric_TrueForDouble_40) {
    Value v(3.14);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_40, IsNumeric_FalseForString_40) {
    Value v("hello");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_40, IsStringable_TrueForString_40) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_40, IsStringable_FalseForObject_40) {
    Object obj;
    Value v(obj);
    EXPECT_FALSE(v.isStringable());
}

// ==================== GetType Tests ====================

TEST_F(ValueTest_40, GetType_ReturnsStringType_40) {
    Value v("test");
    EXPECT_EQ(v.getType(), Value::STRING);
}

TEST_F(ValueTest_40, GetType_ReturnsIntegerType_40) {
    Value v(5);
    EXPECT_EQ(v.getType(), Value::INTEGER);
}

TEST_F(ValueTest_40, GetType_ReturnsDoubleType_40) {
    Value v(2.0);
    EXPECT_EQ(v.getType(), Value::DOUBLE);
}

TEST_F(ValueTest_40, GetType_ReturnsBooleanType_40) {
    Value v(true);
    EXPECT_EQ(v.getType(), Value::BOOLEAN);
}

TEST_F(ValueTest_40, GetType_ReturnsNullType_40) {
    Value v;
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_40, GetType_ReturnsObjectType_40) {
    Value v(Object());
    EXPECT_EQ(v.getType(), Value::OBJECT);
}

TEST_F(ValueTest_40, GetType_ReturnsArrayType_40) {
    Value v(Array());
    EXPECT_EQ(v.getType(), Value::ARRAY);
}

// ==================== Getter Tests ====================

TEST_F(ValueTest_40, GetString_ReturnsCorrectValue_40) {
    Value v("test string");
    EXPECT_EQ(v.getString(), "test string");
}

TEST_F(ValueTest_40, GetInteger_ReturnsCorrectValue_40) {
    Value v(99);
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_40, GetDouble_ReturnsCorrectValue_40) {
    Value v(2.718);
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_40, GetFloat_ReturnsCorrectValue_40) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 1.5f);
}

TEST_F(ValueTest_40, GetBoolean_ReturnsTrue_40) {
    Value v(true);
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_40, GetBoolean_ReturnsFalse_40) {
    Value v(false);
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_40, GetObject_ReturnsCorrectObject_40) {
    Object obj;
    obj["a"] = Value(1);
    obj["b"] = Value(2);
    Value v(obj);
    const Object& result = v.getObject();
    EXPECT_EQ(result.size(), 2u);
    EXPECT_TRUE(result.find("a") != result.end());
    EXPECT_TRUE(result.find("b") != result.end());
}

TEST_F(ValueTest_40, GetArray_ReturnsCorrectArray_40) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    const Array& result = v.getArray();
    EXPECT_EQ(result.size(), 3u);
}

// ==================== TryGet Tests ====================

TEST_F(ValueTest_40, TryGetString_ReturnsValueWhenString_40) {
    Value v("hello");
    EXPECT_EQ(v.tryGetString("default"), "hello");
}

TEST_F(ValueTest_40, TryGetString_ReturnsDefaultWhenNotString_40) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_40, TryGetInteger_ReturnsValueWhenInteger_40) {
    Value v(77);
    EXPECT_EQ(v.tryGetInteger(0), 77);
}

TEST_F(ValueTest_40, TryGetInteger_ReturnsDefaultWhenNotInteger_40) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

TEST_F(ValueTest_40, TryGetDouble_ReturnsValueWhenDouble_40) {
    Value v(9.81);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 9.81);
}

TEST_F(ValueTest_40, TryGetDouble_ReturnsDefaultWhenNotDouble_40) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.23), 1.23);
}

TEST_F(ValueTest_40, TryGetFloat_ReturnsValueWhenDouble_40) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST_F(ValueTest_40, TryGetFloat_ReturnsDefaultWhenNotDouble_40) {
    Value v("nope");
    EXPECT_FLOAT_EQ(v.tryGetFloat(5.5f), 5.5f);
}

TEST_F(ValueTest_40, TryGetBoolean_ReturnsValueWhenBoolean_40) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_40, TryGetBoolean_ReturnsDefaultWhenNotBoolean_40) {
    Value v(42);
    EXPECT_TRUE(v.tryGetBoolean(true));
}

// ==================== Setter Tests ====================

TEST_F(ValueTest_40, SetString_ChangesValueToString_40) {
    Value v(42);
    v.setString("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST_F(ValueTest_40, SetInteger_ChangesValueToInteger_40) {
    Value v("was string");
    v.setInteger(100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST_F(ValueTest_40, SetDouble_ChangesValueToDouble_40) {
    Value v(true);
    v.setDouble(6.28);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 6.28);
}

TEST_F(ValueTest_40, SetBoolean_ChangesValueToBoolean_40) {
    Value v("was string");
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_40, SetObject_ChangesValueToObject_40) {
    Value v(42);
    Object obj;
    obj["key"] = Value("val");
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_40, SetArray_ChangesValueToArray_40) {
    Value v(42);
    Array arr;
    arr.push_back(Value(1));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

TEST_F(ValueTest_40, SetNull_ChangesValueToNull_40) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

// ==================== Assignment Operator Tests ====================

TEST_F(ValueTest_40, AssignmentOperator_Value_40) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_40, AssignmentOperator_String_40) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_40, AssignmentOperator_CString_40) {
    Value v;
    v = "c-string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "c-string");
}

TEST_F(ValueTest_40, AssignmentOperator_Int_40) {
    Value v;
    v = 55;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 55);
}

TEST_F(ValueTest_40, AssignmentOperator_Double_40) {
    Value v;
    v = 1.41;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.41);
}

TEST_F(ValueTest_40, AssignmentOperator_Bool_40) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_40, AssignmentOperator_Object_40) {
    Value v;
    Object obj;
    obj["x"] = Value(10);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_40, AssignmentOperator_Array_40) {
    Value v;
    Array arr;
    arr.push_back(Value("elem"));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

// ==================== Comparison Operator Tests ====================

TEST_F(ValueTest_40, EqualityOperator_SameValues_40) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_40, EqualityOperator_DifferentValues_40) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_40, EqualityOperator_DifferentTypes_40) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_40, InequalityOperator_DifferentValues_40) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_40, InequalityOperator_SameValues_40) {
    Value v1(1);
    Value v2(1);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueTest_40, LessThanOperator_Integers_40) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_40, LessThanOrEqual_Integers_40) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_40, GreaterThanOperator_Integers_40) {
    Value v1(5);
    Value v2(3);
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v2 > v1);
}

TEST_F(ValueTest_40, GreaterThanOrEqual_Integers_40) {
    Value v1(5);
    Value v2(5);
    EXPECT_TRUE(v1 >= v2);
}

// ==================== Subscript Operator Tests ====================

TEST_F(ValueTest_40, SubscriptOperator_StringKey_CreatesObject_40) {
    Value v;
    v.setObject(Object());
    v["key"] = Value(42);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST_F(ValueTest_40, SubscriptOperator_CStringKey_40) {
    Value v;
    v.setObject(Object());
    v["name"] = Value("test");
    EXPECT_EQ(v["name"].getString(), "test");
}

TEST_F(ValueTest_40, SubscriptOperator_ArrayIndex_40) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

// ==================== LoadFromString Tests ====================

TEST_F(ValueTest_40, LoadFromString_Integer_40) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_40, LoadFromString_String_40) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_40, LoadFromString_Boolean_40) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_40, LoadFromString_Null_40) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_40, LoadFromString_Double_40) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_40, LoadFromString_EmptyObject_40) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_40, LoadFromString_EmptyArray_40) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_40, LoadFromString_Object_40) {
    Value v;
    v.loadFromString("{\"a\": 1, \"b\": 2}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 2u);
}

TEST_F(ValueTest_40, LoadFromString_Array_40) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_40, LoadFromString_NegativeInteger_40) {
    Value v;
    v.loadFromString("-42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST_F(ValueTest_40, LoadFromString_FalseBoolean_40) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

// ==================== LoadFromStream Tests ====================

TEST_F(ValueTest_40, LoadFromStream_Integer_40) {
    std::istringstream iss("100");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST_F(ValueTest_40, LoadFromStream_String_40) {
    std::istringstream iss("\"stream test\"");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "stream test");
}

// ==================== WriteToStream Tests ====================

TEST_F(ValueTest_40, WriteToStream_Integer_40) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_FALSE(oss.str().empty());
    EXPECT_NE(oss.str().find("42"), std::string::npos);
}

TEST_F(ValueTest_40, WriteToStream_String_40) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("hello"), std::string::npos);
}

TEST_F(ValueTest_40, WriteToStream_Boolean_40) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("true"), std::string::npos);
}

TEST_F(ValueTest_40, WriteToStream_Null_40) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("null"), std::string::npos);
}

TEST_F(ValueTest_40, WriteToStream_WithIndent_40) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    EXPECT_FALSE(oss.str().empty());
}

// ==================== GetToString Tests ====================

TEST_F(ValueTest_40, GetToString_FromInteger_40) {
    Value v(42);
    std::string result = v.getToString();
    EXPECT_EQ(result, "42");
}

TEST_F(ValueTest_40, GetToString_FromString_40) {
    Value v("hello");
    std::string result = v.getToString();
    EXPECT_EQ(result, "hello");
}

TEST_F(ValueTest_40, GetToString_FromDouble_40) {
    Value v(3.5);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

// ==================== Escape Function Tests ====================

TEST_F(ValueTest_40, EscapeMinimumCharacters_BasicString_40) {
    std::string result = Value::escapeMinimumCharacters("hello");
    EXPECT_EQ(result, "hello");
}

TEST_F(ValueTest_40, EscapeMinimumCharacters_WithQuotes_40) {
    std::string result = Value::escapeMinimumCharacters("he\"llo");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_40, EscapeMinimumCharacters_WithBackslash_40) {
    std::string result = Value::escapeMinimumCharacters("he\\llo");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST_F(ValueTest_40, EscapeMinimumCharacters_WithNewline_40) {
    std::string result = Value::escapeMinimumCharacters("he\nllo");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_40, EscapeAllCharacters_BasicString_40) {
    std::string result = Value::escapeAllCharacters("hello");
    // All characters should be escaped to unicode
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_40, EscapeToUnicode_CharA_40) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result.substr(0, 2), "\\u");
}

TEST_F(ValueTest_40, EscapeToUnicode_NullChar_40) {
    std::string result = Value::escapeToUnicode('\0');
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result.substr(0, 2), "\\u");
}

// ==================== Boundary and Edge Cases ====================

TEST_F(ValueTest_40, IntegerBoundary_Zero_40) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_40, IntegerBoundary_Negative_40) {
    Value v(-1);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -1);
}

TEST_F(ValueTest_40, IntegerBoundary_MaxInt_40) {
    Value v(INT_MAX);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), INT_MAX);
}

TEST_F(ValueTest_40, IntegerBoundary_MinInt_40) {
    Value v(INT_MIN);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), INT_MIN);
}

TEST_F(ValueTest_40, DoubleBoundary_Zero_40) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_40, DoubleBoundary_NegativeDouble_40) {
    Value v(-1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -1.5);
}

TEST_F(ValueTest_40, EmptyString_40) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_40, EmptyObject_40) {
    Value v(Object());
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_40, EmptyArray_40) {
    Value v(Array());
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

// ==================== SetNull After Various Types ====================

TEST_F(ValueTest_40, SetNull_AfterString_40) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_40, SetNull_AfterObject_40) {
    Object obj;
    obj["k"] = Value(1);
    Value v(obj);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_40, SetNull_AfterArray_40) {
    Array arr;
    arr.push_back(Value(1));
    Value v(arr);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

// ==================== Nested Structures ====================

TEST_F(ValueTest_40, NestedObject_40) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": 42}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

TEST_F(ValueTest_40, NestedArray_40) {
    Value v;
    v.loadFromString("[[1, 2], [3, 4]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_40, MixedNestedStructure_40) {
    Value v;
    v.loadFromString("{\"arr\": [1, \"two\", true, null]}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["arr"].isArray());
    EXPECT_EQ(v["arr"].getArray().size(), 4u);
}

// ==================== StreamOperator Test ====================

TEST_F(ValueTest_40, StreamOperator_OutputsCorrectly_40) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

// ==================== Self Assignment ====================

TEST_F(ValueTest_40, SelfAssignment_40) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

// ==================== Overwrite Type Tests ====================

TEST_F(ValueTest_40, OverwriteStringWithInteger_40) {
    Value v("test");
    v.setInteger(99);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_40, OverwriteIntegerWithBoolean_40) {
    Value v(42);
    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_40, OverwriteBooleanWithDouble_40) {
    Value v(true);
    v.setDouble(2.71828);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.71828);
}

TEST_F(ValueTest_40, OverwriteNullWithObject_40) {
    Value v;
    Object obj;
    obj["x"] = Value(1);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
}

// ==================== Comparison across types ====================

TEST_F(ValueTest_40, EqualityOperator_StringValues_40) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_40, EqualityOperator_StringValuesDifferent_40) {
    Value v1("abc");
    Value v2("xyz");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_40, EqualityOperator_BooleanValues_40) {
    Value v1(true);
    Value v2(true);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_40, EqualityOperator_NullValues_40) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_40, EqualityOperator_DoubleValues_40) {
    Value v1(1.5);
    Value v2(1.5);
    EXPECT_TRUE(v1 == v2);
}

// ==================== Unicode escape test ====================

TEST_F(ValueTest_40, LoadFromString_EscapedCharacters_40) {
    Value v;
    v.loadFromString("\"hello\\nworld\"");
    EXPECT_TRUE(v.isString());
    EXPECT_NE(v.getString().find('\n'), std::string::npos);
}

TEST_F(ValueTest_40, LoadFromString_UnicodeEscape_40) {
    Value v;
    v.loadFromString("\"\\u0041\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "A");
}
