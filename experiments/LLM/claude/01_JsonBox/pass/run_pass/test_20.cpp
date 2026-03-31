#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueTest_20 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(ValueTest_20, DefaultConstructorCreatesNull_20) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_20, StringConstructor_20) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_20, CStringConstructor_20) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_20, IntConstructor_20) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_20, DoubleConstructor_20) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_20, BooleanConstructorTrue_20) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_20, BooleanConstructorFalse_20) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_20, ObjectConstructor_20) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_20, ArrayConstructor_20) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_20, CopyConstructor_20) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "test");
}

TEST_F(ValueTest_20, CopyConstructorNull_20) {
    Value original;
    Value copy(original);
    EXPECT_TRUE(copy.isNull());
}

TEST_F(ValueTest_20, CopyConstructorInt_20) {
    Value original(99);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 99);
}

// ==================== Assignment Operator Tests ====================

TEST_F(ValueTest_20, AssignmentFromValue_20) {
    Value v1("hello");
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isString());
    EXPECT_EQ(v2.getString(), "hello");
}

TEST_F(ValueTest_20, AssignmentFromString_20) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_20, AssignmentFromCString_20) {
    Value v;
    v = "c_string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "c_string");
}

TEST_F(ValueTest_20, AssignmentFromInt_20) {
    Value v;
    v = 100;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST_F(ValueTest_20, AssignmentFromDouble_20) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_20, AssignmentFromObject_20) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_20, AssignmentFromArray_20) {
    Value v;
    Array arr;
    arr.push_back(Value("x"));
    v = arr;
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

TEST_F(ValueTest_20, AssignmentFromBool_20) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_20, AssignmentChangesType_20) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v = "now a string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

// ==================== Type Checking Tests ====================

TEST_F(ValueTest_20, IsStringOnString_20) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueTest_20, IsIntegerOnInteger_20) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_20, IsDoubleOnDouble_20) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_20, IsNumericOnInteger_20) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_20, IsNumericOnDouble_20) {
    Value v(5.0);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_20, IsNumericOnString_20) {
    Value v("5");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_20, IsObjectOnObject_20) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_20, IsArrayOnArray_20) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_20, IsBooleanOnBoolean_20) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
}

TEST_F(ValueTest_20, IsNullOnNull_20) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

// ==================== Setter Tests ====================

TEST_F(ValueTest_20, SetString_20) {
    Value v;
    v.setString("new_string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "new_string");
}

TEST_F(ValueTest_20, SetInteger_20) {
    Value v;
    v.setInteger(55);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 55);
}

TEST_F(ValueTest_20, SetDouble_20) {
    Value v;
    v.setDouble(9.99);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 9.99);
}

TEST_F(ValueTest_20, SetBoolean_20) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_20, SetNull_20) {
    Value v(42);
    EXPECT_FALSE(v.isNull());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_20, SetObject_20) {
    Value v;
    Object obj;
    obj["key1"] = Value("val1");
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_20, SetArray_20) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    arr.push_back(Value(3));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

// ==================== Try Getters with Default Values ====================

TEST_F(ValueTest_20, TryGetStringReturnsValueWhenString_20) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST_F(ValueTest_20, TryGetStringReturnsDefaultWhenNotString_20) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_20, TryGetIntegerReturnsValueWhenInteger_20) {
    Value v(77);
    EXPECT_EQ(v.tryGetInteger(0), 77);
}

TEST_F(ValueTest_20, TryGetIntegerReturnsDefaultWhenNotInteger_20) {
    Value v("string");
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

TEST_F(ValueTest_20, TryGetDoubleReturnsValueWhenDouble_20) {
    Value v(1.23);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 1.23);
}

TEST_F(ValueTest_20, TryGetDoubleReturnsDefaultWhenNotDouble_20) {
    Value v("string");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(9.9), 9.9);
}

TEST_F(ValueTest_20, TryGetFloatReturnsValueWhenDouble_20) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 1.5f);
}

TEST_F(ValueTest_20, TryGetFloatReturnsDefaultWhenNotDouble_20) {
    Value v("not a number");
    EXPECT_FLOAT_EQ(v.tryGetFloat(3.3f), 3.3f);
}

TEST_F(ValueTest_20, TryGetBooleanReturnsValueWhenBoolean_20) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_20, TryGetBooleanReturnsDefaultWhenNotBoolean_20) {
    Value v(42);
    EXPECT_TRUE(v.tryGetBoolean(true));
}

// ==================== Comparison Operators ====================

TEST_F(ValueTest_20, EqualityOperatorSameValues_20) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_20, EqualityOperatorDifferentValues_20) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_20, InequalityOperator_20) {
    Value v1(42);
    Value v2(43);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_20, EqualityOperatorDifferentTypes_20) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_20, LessThanOperator_20) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_20, LessThanOrEqualOperator_20) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_20, GreaterThanOperator_20) {
    Value v1(2);
    Value v2(1);
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v2 > v1);
}

TEST_F(ValueTest_20, GreaterThanOrEqualOperator_20) {
    Value v1(2);
    Value v2(2);
    EXPECT_TRUE(v1 >= v2);
}

TEST_F(ValueTest_20, EqualNullValues_20) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_20, EqualStringValues_20) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_20, EqualBooleanValues_20) {
    Value v1(true);
    Value v2(true);
    EXPECT_TRUE(v1 == v2);
}

// ==================== Index Operators ====================

TEST_F(ValueTest_20, ObjectIndexOperatorString_20) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v["key"].isString());
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST_F(ValueTest_20, ObjectIndexOperatorCString_20) {
    Object obj;
    obj["key"] = Value(123);
    Value v(obj);
    EXPECT_TRUE(v["key"].isInteger());
    EXPECT_EQ(v["key"].getInteger(), 123);
}

TEST_F(ValueTest_20, ArrayIndexOperator_20) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

TEST_F(ValueTest_20, ObjectIndexOperatorCreatesNewEntry_20) {
    Object obj;
    Value v(obj);
    v["newKey"] = Value("newValue");
    EXPECT_TRUE(v["newKey"].isString());
    EXPECT_EQ(v["newKey"].getString(), "newValue");
}

// ==================== Load From String Tests ====================

TEST_F(ValueTest_20, LoadFromStringInteger_20) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_20, LoadFromStringDouble_20) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_20, LoadFromStringString_20) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_20, LoadFromStringBoolean_20) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_20, LoadFromStringFalse_20) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_20, LoadFromStringNull_20) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_20, LoadFromStringObject_20) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST_F(ValueTest_20, LoadFromStringArray_20) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_20, LoadFromStringEmptyObject_20) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_20, LoadFromStringEmptyArray_20) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_20, LoadFromStringNestedObject_20) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": 42}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

// ==================== Load From Stream Tests ====================

TEST_F(ValueTest_20, LoadFromStream_20) {
    Value v;
    std::istringstream ss("{\"name\": \"test\"}");
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["name"].getString(), "test");
}

TEST_F(ValueTest_20, ConstructFromStream_20) {
    std::istringstream ss("123");
    Value v(ss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

// ==================== Write Tests ====================

TEST_F(ValueTest_20, WriteToStreamInteger_20) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "42");
}

TEST_F(ValueTest_20, WriteToStreamString_20) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "\"hello\"");
}

TEST_F(ValueTest_20, WriteToStreamBoolean_20) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "true");
}

TEST_F(ValueTest_20, WriteToStreamBooleanFalse_20) {
    Value v(false);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "false");
}

TEST_F(ValueTest_20, WriteToStreamNull_20) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "null");
}

TEST_F(ValueTest_20, WriteToStreamDouble_20) {
    Value v(3.14);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string result = oss.str();
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST_F(ValueTest_20, WriteToStreamEmptyObject_20) {
    Value v;
    v.loadFromString("{}");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "{}");
}

TEST_F(ValueTest_20, WriteToStreamEmptyArray_20) {
    Value v;
    v.loadFromString("[]");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "[]");
}

// ==================== Escape Functions ====================

TEST_F(ValueTest_20, EscapeMinimumCharactersQuote_20) {
    std::string result = Value::escapeMinimumCharacters("he\"llo");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_20, EscapeMinimumCharactersBackslash_20) {
    std::string result = Value::escapeMinimumCharacters("he\\llo");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST_F(ValueTest_20, EscapeMinimumCharactersNoEscapeNeeded_20) {
    std::string result = Value::escapeMinimumCharacters("hello");
    EXPECT_EQ(result, "hello");
}

TEST_F(ValueTest_20, EscapeAllCharactersBasic_20) {
    std::string result = Value::escapeAllCharacters("hello");
    // All characters should be escaped to unicode
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_20, EscapeToUnicodeCharacter_20) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ==================== Boundary / Edge Cases ====================

TEST_F(ValueTest_20, EmptyStringValue_20) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_20, NegativeInteger_20) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST_F(ValueTest_20, ZeroInteger_20) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_20, ZeroDouble_20) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_20, NegativeDouble_20) {
    Value v(-3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -3.14);
}

TEST_F(ValueTest_20, LargeInteger_20) {
    Value v(2147483647);  // INT_MAX
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST_F(ValueTest_20, EmptyObjectValue_20) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_20, EmptyArrayValue_20) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_20, OverwriteTypeMultipleTimes_20) {
    Value v;
    EXPECT_TRUE(v.isNull());
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

TEST_F(ValueTest_20, GetFloatFromDouble_20) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 2.5f);
}

// ==================== isStringable Tests ====================

TEST_F(ValueTest_20, IsStringableOnString_20) {
    Value v("test");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_20, IsStringableOnInteger_20) {
    Value v(42);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_20, IsStringableOnDouble_20) {
    Value v(3.14);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_20, IsStringableOnNull_20) {
    Value v;
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_20, IsStringableOnBoolean_20) {
    Value v(true);
    EXPECT_TRUE(v.isStringable());
}

// ==================== getToString Tests ====================

TEST_F(ValueTest_20, GetToStringFromString_20) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

TEST_F(ValueTest_20, GetToStringFromInteger_20) {
    Value v(42);
    EXPECT_EQ(v.getToString(), "42");
}

TEST_F(ValueTest_20, GetToStringFromBoolTrue_20) {
    Value v(true);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_20, GetToStringFromNull_20) {
    Value v;
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

// ==================== Stream Operator ====================

TEST_F(ValueTest_20, StreamOutputOperator_20) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_EQ(oss.str(), "42");
}

TEST_F(ValueTest_20, StreamOutputOperatorString_20) {
    Value v("test");
    std::ostringstream oss;
    oss << v;
    EXPECT_EQ(oss.str(), "\"test\"");
}

// ==================== Complex JSON Tests ====================

TEST_F(ValueTest_20, LoadComplexJson_20) {
    Value v;
    v.loadFromString("{\"name\": \"John\", \"age\": 30, \"active\": true, \"scores\": [100, 200, 300]}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["name"].getString(), "John");
    EXPECT_EQ(v["age"].getInteger(), 30);
    EXPECT_TRUE(v["active"].getBoolean());
    EXPECT_TRUE(v["scores"].isArray());
    EXPECT_EQ(v["scores"].getArray().size(), 3u);
}

TEST_F(ValueTest_20, LoadFromStringNegativeInteger_20) {
    Value v;
    v.loadFromString("-42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST_F(ValueTest_20, LoadFromStringEmptyString_20) {
    Value v;
    v.loadFromString("\"\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_20, RoundTripObjectJson_20) {
    Value v;
    v.loadFromString("{\"a\": 1, \"b\": 2}");
    
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    
    Value v2;
    v2.loadFromString(oss.str());
    EXPECT_TRUE(v2.isObject());
    EXPECT_EQ(v2["a"].getInteger(), 1);
    EXPECT_EQ(v2["b"].getInteger(), 2);
}

TEST_F(ValueTest_20, RoundTripArrayJson_20) {
    Value v;
    v.loadFromString("[1, \"two\", true, null]");
    
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    
    Value v2;
    v2.loadFromString(oss.str());
    EXPECT_TRUE(v2.isArray());
    EXPECT_EQ(v2.getArray().size(), 4u);
}

// ==================== Escaped String Tests ====================

TEST_F(ValueTest_20, LoadFromStringWithEscapedChars_20) {
    Value v;
    v.loadFromString("\"hello\\nworld\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello\nworld");
}

TEST_F(ValueTest_20, LoadFromStringWithEscapedQuote_20) {
    Value v;
    v.loadFromString("\"he\\\"llo\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "he\"llo");
}

TEST_F(ValueTest_20, EscapeMinimumCharactersNewline_20) {
    std::string result = Value::escapeMinimumCharacters("line1\nline2");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_20, EscapeMinimumCharactersTab_20) {
    std::string result = Value::escapeMinimumCharacters("col1\tcol2");
    EXPECT_NE(result.find("\\t"), std::string::npos);
}

TEST_F(ValueTest_20, EscapeMinimumCharactersEmptyString_20) {
    std::string result = Value::escapeMinimumCharacters("");
    EXPECT_EQ(result, "");
}
