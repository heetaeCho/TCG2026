#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueTest_67 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(ValueTest_67, DefaultConstructorCreatesNullValue_67) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_67, StringConstructor_67) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_67, CStringConstructor_67) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_67, IntConstructor_67) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_67, DoubleConstructor_67) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_67, BooleanTrueConstructor_67) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_67, BooleanFalseConstructor_67) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_67, ObjectConstructor_67) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_67, ArrayConstructor_67) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_67, CopyConstructor_67) {
    Value original(123);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 123);
}

TEST_F(ValueTest_67, StreamConstructorValidJson_67) {
    std::istringstream iss("\"hello\"");
    Value v(iss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

// ==================== Type Check Tests ====================

TEST_F(ValueTest_67, IsStringReturnsTrueForString_67) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_67, IsIntegerReturnsTrueForInteger_67) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
}

TEST_F(ValueTest_67, IsDoubleReturnsTrueForDouble_67) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_67, IsNumericForInteger_67) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_67, IsNumericForDouble_67) {
    Value v(5.0);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_67, IsNumericFalseForString_67) {
    Value v("123");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_67, IsObjectReturnsTrueForObject_67) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_67, IsArrayReturnsTrueForArray_67) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_67, IsBooleanReturnsTrueForBoolean_67) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
}

TEST_F(ValueTest_67, IsNullReturnsTrueForNull_67) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

// ==================== Getter Tests ====================

TEST_F(ValueTest_67, GetStringReturnsCorrectValue_67) {
    Value v("test string");
    EXPECT_EQ(v.getString(), "test string");
}

TEST_F(ValueTest_67, GetIntegerReturnsCorrectValue_67) {
    Value v(999);
    EXPECT_EQ(v.getInteger(), 999);
}

TEST_F(ValueTest_67, GetDoubleReturnsCorrectValue_67) {
    Value v(2.718281828);
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718281828);
}

TEST_F(ValueTest_67, GetFloatReturnsCorrectValue_67) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 1.5f);
}

TEST_F(ValueTest_67, GetBooleanReturnsCorrectValue_67) {
    Value v(true);
    EXPECT_TRUE(v.getBoolean());
    Value v2(false);
    EXPECT_FALSE(v2.getBoolean());
}

// ==================== TryGet Tests ====================

TEST_F(ValueTest_67, TryGetStringReturnsValueWhenString_67) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST_F(ValueTest_67, TryGetStringReturnsDefaultWhenNotString_67) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_67, TryGetIntegerReturnsValueWhenInteger_67) {
    Value v(100);
    EXPECT_EQ(v.tryGetInteger(0), 100);
}

TEST_F(ValueTest_67, TryGetIntegerReturnsDefaultWhenNotInteger_67) {
    Value v("not an int");
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

TEST_F(ValueTest_67, TryGetDoubleReturnsValueWhenDouble_67) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 3.14);
}

TEST_F(ValueTest_67, TryGetDoubleReturnsDefaultWhenNotDouble_67) {
    Value v("not a double");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(9.9), 9.9);
}

TEST_F(ValueTest_67, TryGetFloatReturnsValueWhenDouble_67) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST_F(ValueTest_67, TryGetFloatReturnsDefaultWhenNotDouble_67) {
    Value v("nope");
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.0f), 1.0f);
}

TEST_F(ValueTest_67, TryGetBooleanReturnsValueWhenBoolean_67) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_67, TryGetBooleanReturnsDefaultWhenNotBoolean_67) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ==================== Setter Tests ====================

TEST_F(ValueTest_67, SetStringChangesTypeAndValue_67) {
    Value v;
    v.setString("new value");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "new value");
}

TEST_F(ValueTest_67, SetIntegerChangesTypeAndValue_67) {
    Value v;
    v.setInteger(77);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 77);
}

TEST_F(ValueTest_67, SetDoubleChangesTypeAndValue_67) {
    Value v;
    v.setDouble(1.23);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.23);
}

TEST_F(ValueTest_67, SetBooleanChangesTypeAndValue_67) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_67, SetObjectChangesTypeAndValue_67) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_67, SetArrayChangesTypeAndValue_67) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

TEST_F(ValueTest_67, SetNullChangesTypeToNull_67) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

// ==================== Assignment Operator Tests ====================

TEST_F(ValueTest_67, AssignmentFromValue_67) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_67, AssignmentFromString_67) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_67, AssignmentFromCString_67) {
    Value v;
    v = "c-string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "c-string");
}

TEST_F(ValueTest_67, AssignmentFromInt_67) {
    Value v;
    v = 55;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 55);
}

TEST_F(ValueTest_67, AssignmentFromDouble_67) {
    Value v;
    v = 6.28;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 6.28);
}

TEST_F(ValueTest_67, AssignmentFromBool_67) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_67, AssignmentFromObject_67) {
    Value v;
    Object obj;
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_67, AssignmentFromArray_67) {
    Value v;
    Array arr;
    v = arr;
    EXPECT_TRUE(v.isArray());
}

// ==================== Comparison Operator Tests ====================

TEST_F(ValueTest_67, EqualityOperatorSameValues_67) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_67, EqualityOperatorDifferentValues_67) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_67, InequalityOperator_67) {
    Value v1(42);
    Value v2(43);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_67, LessThanOperator_67) {
    Value v1(10);
    Value v2(20);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_67, LessThanOrEqualOperator_67) {
    Value v1(10);
    Value v2(10);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_67, GreaterThanOperator_67) {
    Value v1(20);
    Value v2(10);
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v2 > v1);
}

TEST_F(ValueTest_67, GreaterThanOrEqualOperator_67) {
    Value v1(10);
    Value v2(10);
    EXPECT_TRUE(v1 >= v2);
}

// ==================== Subscript Operator Tests ====================

TEST_F(ValueTest_67, SubscriptWithStringKeyOnObject_67) {
    Object obj;
    obj["key"] = Value("val");
    Value v(obj);
    EXPECT_EQ(v["key"].getString(), "val");
}

TEST_F(ValueTest_67, SubscriptWithCStringKeyOnObject_67) {
    Object obj;
    obj["foo"] = Value(123);
    Value v(obj);
    EXPECT_EQ(v["foo"].getInteger(), 123);
}

TEST_F(ValueTest_67, SubscriptWithIndexOnArray_67) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

// ==================== operator<< (Output Stream) Tests ====================

TEST_F(ValueTest_67, StreamOutputString_67) {
    Value v("hello");
    std::ostringstream oss;
    oss << v;
    EXPECT_EQ(oss.str(), "\"hello\"");
}

TEST_F(ValueTest_67, StreamOutputInteger_67) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_EQ(oss.str(), "42");
}

TEST_F(ValueTest_67, StreamOutputNegativeInteger_67) {
    Value v(-100);
    std::ostringstream oss;
    oss << v;
    EXPECT_EQ(oss.str(), "-100");
}

TEST_F(ValueTest_67, StreamOutputZeroInteger_67) {
    Value v(0);
    std::ostringstream oss;
    oss << v;
    EXPECT_EQ(oss.str(), "0");
}

TEST_F(ValueTest_67, StreamOutputDouble_67) {
    Value v(3.14);
    std::ostringstream oss;
    oss << v;
    std::string result = oss.str();
    // Should contain "3.14" at minimum
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST_F(ValueTest_67, StreamOutputBooleanTrue_67) {
    Value v(true);
    std::ostringstream oss;
    oss << v;
    EXPECT_EQ(oss.str(), "true");
}

TEST_F(ValueTest_67, StreamOutputBooleanFalse_67) {
    Value v(false);
    std::ostringstream oss;
    oss << v;
    EXPECT_EQ(oss.str(), "false");
}

TEST_F(ValueTest_67, StreamOutputNull_67) {
    Value v;
    std::ostringstream oss;
    oss << v;
    EXPECT_EQ(oss.str(), "null");
}

TEST_F(ValueTest_67, StreamOutputEmptyString_67) {
    Value v(std::string(""));
    std::ostringstream oss;
    oss << v;
    EXPECT_EQ(oss.str(), "\"\"");
}

TEST_F(ValueTest_67, StreamOutputStringWithSpecialChars_67) {
    Value v("line\nnewline");
    std::ostringstream oss;
    oss << v;
    std::string result = oss.str();
    // Should be quoted and have escaped newline
    EXPECT_EQ(result.front(), '"');
    EXPECT_EQ(result.back(), '"');
    // The newline should be escaped, so raw \n should not appear
    EXPECT_EQ(result.find('\n'), std::string::npos);
}

// ==================== loadFromString Tests ====================

TEST_F(ValueTest_67, LoadFromStringInteger_67) {
    Value v;
    v.loadFromString("123");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

TEST_F(ValueTest_67, LoadFromStringString_67) {
    Value v;
    v.loadFromString("\"hello world\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello world");
}

TEST_F(ValueTest_67, LoadFromStringBoolean_67) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_67, LoadFromStringNull_67) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_67, LoadFromStringDouble_67) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_NEAR(v.getDouble(), 3.14, 0.001);
}

TEST_F(ValueTest_67, LoadFromStringArray_67) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_67, LoadFromStringObject_67) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

// ==================== loadFromStream Tests ====================

TEST_F(ValueTest_67, LoadFromStreamInteger_67) {
    std::istringstream iss("456");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 456);
}

TEST_F(ValueTest_67, LoadFromStreamString_67) {
    std::istringstream iss("\"test\"");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

// ==================== writeToStream Tests ====================

TEST_F(ValueTest_67, WriteToStreamNoIndentNoEscapeAll_67) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "42");
}

TEST_F(ValueTest_67, WriteToStreamString_67) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "\"hello\"");
}

TEST_F(ValueTest_67, WriteToStreamWithIndent_67) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string result = oss.str();
    // With indent, expect some whitespace/newlines
    EXPECT_NE(result.find('\n'), std::string::npos);
}

TEST_F(ValueTest_67, WriteToStreamNull_67) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "null");
}

// ==================== escapeMinimumCharacters Tests ====================

TEST_F(ValueTest_67, EscapeMinimumCharactersNoEscape_67) {
    std::string result = Value::escapeMinimumCharacters("hello");
    EXPECT_EQ(result, "hello");
}

TEST_F(ValueTest_67, EscapeMinimumCharactersWithQuote_67) {
    std::string result = Value::escapeMinimumCharacters("he\"llo");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_67, EscapeMinimumCharactersWithNewline_67) {
    std::string result = Value::escapeMinimumCharacters("line1\nline2");
    EXPECT_EQ(result.find('\n'), std::string::npos);
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_67, EscapeMinimumCharactersWithBackslash_67) {
    std::string result = Value::escapeMinimumCharacters("back\\slash");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST_F(ValueTest_67, EscapeMinimumCharactersEmpty_67) {
    std::string result = Value::escapeMinimumCharacters("");
    EXPECT_EQ(result, "");
}

// ==================== escapeAllCharacters Tests ====================

TEST_F(ValueTest_67, EscapeAllCharactersPlainAscii_67) {
    std::string result = Value::escapeAllCharacters("abc");
    // All characters should be escaped to unicode
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

TEST_F(ValueTest_67, EscapeAllCharactersEmpty_67) {
    std::string result = Value::escapeAllCharacters("");
    EXPECT_EQ(result, "");
}

// ==================== escapeToUnicode Tests ====================

TEST_F(ValueTest_67, EscapeToUnicodeCharA_67) {
    std::string result = Value::escapeToUnicode('A');
    // Should produce something like \u0041
    EXPECT_EQ(result.substr(0, 2), "\\u");
    EXPECT_EQ(result.length(), 6u);
}

TEST_F(ValueTest_67, EscapeToUnicodeNullChar_67) {
    std::string result = Value::escapeToUnicode('\0');
    EXPECT_EQ(result.substr(0, 2), "\\u");
    EXPECT_EQ(result.length(), 6u);
}

// ==================== Boundary / Edge Cases ====================

TEST_F(ValueTest_67, IntegerBoundaryMaxInt_67) {
    Value v(INT_MAX);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), INT_MAX);
}

TEST_F(ValueTest_67, IntegerBoundaryMinInt_67) {
    Value v(INT_MIN);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), INT_MIN);
}

TEST_F(ValueTest_67, DoubleZero_67) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_67, EmptyObject_67) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_67, EmptyArray_67) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_67, SetNullFromString_67) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_67, OverwriteTypeByAssignment_67) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v = "now a string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST_F(ValueTest_67, GetTypeForEachType_67) {
    EXPECT_EQ(Value("s").getType(), Value::STRING);
    EXPECT_EQ(Value(1).getType(), Value::INTEGER);
    EXPECT_EQ(Value(1.0).getType(), Value::DOUBLE);
    EXPECT_EQ(Value(Object()).getType(), Value::OBJECT);
    EXPECT_EQ(Value(Array()).getType(), Value::ARRAY);
    EXPECT_EQ(Value(true).getType(), Value::BOOLEAN);
    EXPECT_EQ(Value().getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_67, IsStringableForString_67) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_67, GetToStringForInteger_67) {
    Value v(42);
    std::string s = v.getToString();
    EXPECT_EQ(s, "42");
}

TEST_F(ValueTest_67, GetToStringForString_67) {
    Value v("hello");
    std::string s = v.getToString();
    EXPECT_EQ(s, "hello");
}

TEST_F(ValueTest_67, GetToStringForBoolean_67) {
    Value v(true);
    std::string s = v.getToString();
    EXPECT_EQ(s, "true");
}

TEST_F(ValueTest_67, GetToStringForNull_67) {
    Value v;
    std::string s = v.getToString();
    EXPECT_EQ(s, "null");
}

// ==================== Nested Structure Tests ====================

TEST_F(ValueTest_67, NestedArrayInObject_67) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Object obj;
    obj["array"] = Value(arr);
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["array"].isArray());
    EXPECT_EQ(v["array"].getArray().size(), 2u);
}

TEST_F(ValueTest_67, NestedObjectInArray_67) {
    Object obj;
    obj["key"] = Value("value");
    Array arr;
    arr.push_back(Value(obj));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v[(size_t)0].isObject());
}

TEST_F(ValueTest_67, StreamOutputEmptyObject_67) {
    Object obj;
    Value v(obj);
    std::ostringstream oss;
    oss << v;
    EXPECT_EQ(oss.str(), "{}");
}

TEST_F(ValueTest_67, StreamOutputEmptyArray_67) {
    Array arr;
    Value v(arr);
    std::ostringstream oss;
    oss << v;
    EXPECT_EQ(oss.str(), "[]");
}

// ==================== Self-Assignment ====================

TEST_F(ValueTest_67, SelfAssignment_67) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

// ==================== Comparison of Different Types ====================

TEST_F(ValueTest_67, ComparisonDifferentTypes_67) {
    Value v1(42);
    Value v2("42");
    // Different types should not be equal
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_67, ComparisonBothNull_67) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_67, ComparisonStringValues_67) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_TRUE(v1 == v2);
    Value v3("abd");
    EXPECT_TRUE(v1 < v3);
}

TEST_F(ValueTest_67, StreamOutputStringWithTab_67) {
    Value v("tab\there");
    std::ostringstream oss;
    oss << v;
    std::string result = oss.str();
    // Tab should be escaped
    EXPECT_EQ(result.find('\t'), std::string::npos);
}

TEST_F(ValueTest_67, LoadFromStringNegativeInt_67) {
    Value v;
    v.loadFromString("-42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST_F(ValueTest_67, LoadFromStringFalse_67) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_67, LoadFromStringEmptyObject_67) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_67, LoadFromStringEmptyArray_67) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}
