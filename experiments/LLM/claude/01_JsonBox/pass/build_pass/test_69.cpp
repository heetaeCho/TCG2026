#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueTest_69 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(ValueTest_69, DefaultConstructorCreatesNull_69) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueTest_69, StringConstructor_69) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_69, CStringConstructor_69) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_69, IntConstructor_69) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_69, DoubleConstructor_69) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_69, BooleanConstructorTrue_69) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_69, BooleanConstructorFalse_69) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_69, ObjectConstructor_69) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_69, ArrayConstructor_69) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_69, CopyConstructor_69) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

TEST_F(ValueTest_69, StreamConstructor_69) {
    std::istringstream ss("\"hello\"");
    Value v(ss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

// ==================== Type Checking Tests ====================

TEST_F(ValueTest_69, IsStringable_69) {
    Value vStr("hello");
    EXPECT_TRUE(vStr.isStringable());

    Value vInt(42);
    // Integers might be stringable depending on implementation
    // We test that isStringable returns a bool without asserting specific value for non-strings
}

TEST_F(ValueTest_69, IsNumericForInteger_69) {
    Value v(42);
    EXPECT_TRUE(v.isNumeric());
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
}

TEST_F(ValueTest_69, IsNumericForDouble_69) {
    Value v(3.14);
    EXPECT_TRUE(v.isNumeric());
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_69, IsNotNumericForString_69) {
    Value v("hello");
    EXPECT_FALSE(v.isNumeric());
}

// ==================== Assignment Operator Tests ====================

TEST_F(ValueTest_69, AssignmentFromValue_69) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_69, AssignmentFromString_69) {
    Value v;
    v = std::string("test");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

TEST_F(ValueTest_69, AssignmentFromCString_69) {
    Value v;
    v = "test";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

TEST_F(ValueTest_69, AssignmentFromInt_69) {
    Value v;
    v = 100;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST_F(ValueTest_69, AssignmentFromDouble_69) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_69, AssignmentFromBool_69) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_69, AssignmentFromObject_69) {
    Value v;
    Object obj;
    obj["x"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_69, AssignmentFromArray_69) {
    Value v;
    Array arr;
    arr.push_back(Value("a"));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

// ==================== Setter Tests ====================

TEST_F(ValueTest_69, SetString_69) {
    Value v;
    v.setString("new string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "new string");
}

TEST_F(ValueTest_69, SetInteger_69) {
    Value v;
    v.setInteger(99);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_69, SetDouble_69) {
    Value v;
    v.setDouble(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.5);
}

TEST_F(ValueTest_69, SetBoolean_69) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_69, SetNull_69) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_69, SetObject_69) {
    Value v;
    Object obj;
    obj["key"] = Value("val");
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_69, SetArray_69) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    arr.push_back(Value(3));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

// ==================== TryGet Tests ====================

TEST_F(ValueTest_69, TryGetStringReturnsValueWhenString_69) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST_F(ValueTest_69, TryGetStringReturnsDefaultWhenNotString_69) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_69, TryGetIntegerReturnsValueWhenInteger_69) {
    Value v(42);
    EXPECT_EQ(v.tryGetInteger(0), 42);
}

TEST_F(ValueTest_69, TryGetIntegerReturnsDefaultWhenNotInteger_69) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(99), 99);
}

TEST_F(ValueTest_69, TryGetDoubleReturnsValueWhenDouble_69) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 3.14);
}

TEST_F(ValueTest_69, TryGetDoubleReturnsDefaultWhenNotDouble_69) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.0), 1.0);
}

TEST_F(ValueTest_69, TryGetFloatReturnsValueWhenDouble_69) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST_F(ValueTest_69, TryGetFloatReturnsDefaultWhenNotDouble_69) {
    Value v("hello");
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.0f), 1.0f);
}

TEST_F(ValueTest_69, TryGetBooleanReturnsValueWhenBoolean_69) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_69, TryGetBooleanReturnsDefaultWhenNotBoolean_69) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ==================== Comparison Operator Tests ====================

TEST_F(ValueTest_69, EqualityOperatorSameValues_69) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueTest_69, EqualityOperatorDifferentValues_69) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_69, EqualityOperatorDifferentTypes_69) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_69, LessThanOperator_69) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_69, LessThanOrEqualOperator_69) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_69, GreaterThanOperator_69) {
    Value v1(2);
    Value v2(1);
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v2 > v1);
}

TEST_F(ValueTest_69, GreaterThanOrEqualOperator_69) {
    Value v1(2);
    Value v2(2);
    EXPECT_TRUE(v1 >= v2);
}

// ==================== Subscript Operator Tests ====================

TEST_F(ValueTest_69, SubscriptOperatorStringKey_69) {
    Value v;
    Object obj;
    obj["key"] = Value("value");
    v.setObject(obj);
    EXPECT_TRUE(v["key"].isString());
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST_F(ValueTest_69, SubscriptOperatorCStringKey_69) {
    Value v;
    Object obj;
    obj["key"] = Value(42);
    v.setObject(obj);
    EXPECT_TRUE(v["key"].isInteger());
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST_F(ValueTest_69, SubscriptOperatorArrayIndex_69) {
    Value v;
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    v.setArray(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

// ==================== Load and Write Tests ====================

TEST_F(ValueTest_69, LoadFromString_69) {
    Value v;
    v.loadFromString("{\"name\": \"test\", \"value\": 42}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["name"].isString());
    EXPECT_EQ(v["name"].getString(), "test");
    EXPECT_TRUE(v["value"].isInteger());
    EXPECT_EQ(v["value"].getInteger(), 42);
}

TEST_F(ValueTest_69, LoadFromStringArray_69) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_69, LoadFromStringNull_69) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_69, LoadFromStringBoolean_69) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_69, LoadFromStringFalse_69) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_69, LoadFromStream_69) {
    std::istringstream ss("{\"a\": 1}");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_69, WriteToStream_69) {
    Value v(42);
    std::ostringstream os;
    v.writeToStream(os, false, false);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(ValueTest_69, WriteToStreamString_69) {
    Value v("hello");
    std::ostringstream os;
    v.writeToStream(os, false, false);
    std::string output = os.str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(ValueTest_69, WriteToStreamIndented_69) {
    Value v;
    v.loadFromString("{\"a\": 1, \"b\": 2}");
    std::ostringstream os;
    v.writeToStream(os, true, false);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTest_69, WriteToStreamNull_69) {
    Value v;
    std::ostringstream os;
    v.writeToStream(os, false, false);
    std::string output = os.str();
    EXPECT_NE(output.find("null"), std::string::npos);
}

TEST_F(ValueTest_69, WriteToStreamBoolean_69) {
    Value v(true);
    std::ostringstream os;
    v.writeToStream(os, false, false);
    std::string output = os.str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

// ==================== Stream Operator Tests ====================

TEST_F(ValueTest_69, StreamOperatorValue_69) {
    Value v(42);
    std::ostringstream os;
    os << v;
    EXPECT_FALSE(os.str().empty());
}

TEST_F(ValueTest_69, StreamOperatorEmptyObject_69) {
    Object obj;
    std::ostringstream os;
    os << obj;
    std::string output = os.str();
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
}

TEST_F(ValueTest_69, StreamOperatorNonEmptyObject_69) {
    Object obj;
    obj["key"] = Value("value");
    std::ostringstream os;
    os << obj;
    std::string output = os.str();
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
    EXPECT_NE(output.find("key"), std::string::npos);
    EXPECT_NE(output.find("value"), std::string::npos);
}

TEST_F(ValueTest_69, StreamOperatorObjectMultipleKeys_69) {
    Object obj;
    obj["a"] = Value(1);
    obj["b"] = Value(2);
    std::ostringstream os;
    os << obj;
    std::string output = os.str();
    EXPECT_NE(output.find(","), std::string::npos);
}

// ==================== Escape Function Tests ====================

TEST_F(ValueTest_69, EscapeMinimumCharactersNoEscape_69) {
    std::string result = Value::escapeMinimumCharacters("hello");
    EXPECT_EQ(result, "hello");
}

TEST_F(ValueTest_69, EscapeMinimumCharactersWithQuote_69) {
    std::string result = Value::escapeMinimumCharacters("he\"llo");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_69, EscapeMinimumCharactersWithBackslash_69) {
    std::string result = Value::escapeMinimumCharacters("he\\llo");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST_F(ValueTest_69, EscapeMinimumCharactersWithNewline_69) {
    std::string result = Value::escapeMinimumCharacters("he\nllo");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_69, EscapeMinimumCharactersWithTab_69) {
    std::string result = Value::escapeMinimumCharacters("he\tllo");
    EXPECT_NE(result.find("\\t"), std::string::npos);
}

TEST_F(ValueTest_69, EscapeMinimumCharactersEmptyString_69) {
    std::string result = Value::escapeMinimumCharacters("");
    EXPECT_EQ(result, "");
}

TEST_F(ValueTest_69, EscapeAllCharactersNoEscape_69) {
    std::string result = Value::escapeAllCharacters("abc");
    // Basic ASCII should pass through or be escaped to unicode
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_69, EscapeToUnicode_69) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
    // Unicode escape should start with \u
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ==================== Type Change Tests ====================

TEST_F(ValueTest_69, ChangeTypeFromIntToString_69) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setString("hello");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_69, ChangeTypeFromStringToNull_69) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    v.setNull();
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_69, ChangeTypeFromNullToObject_69) {
    Value v;
    EXPECT_TRUE(v.isNull());
    Object obj;
    obj["x"] = Value(1);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
}

// ==================== Boundary Tests ====================

TEST_F(ValueTest_69, IntegerZero_69) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_69, NegativeInteger_69) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST_F(ValueTest_69, DoubleZero_69) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_69, NegativeDouble_69) {
    Value v(-3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -3.14);
}

TEST_F(ValueTest_69, EmptyString_69) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_69, EmptyObject_69) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_69, EmptyArray_69) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_69, GetToStringFromInt_69) {
    Value v(42);
    std::string s = v.getToString();
    EXPECT_FALSE(s.empty());
}

TEST_F(ValueTest_69, GetToStringFromString_69) {
    Value v("hello");
    std::string s = v.getToString();
    EXPECT_EQ(s, "hello");
}

TEST_F(ValueTest_69, GetFloatFromDouble_69) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 2.5f);
}

// ==================== Complex JSON Tests ====================

TEST_F(ValueTest_69, LoadComplexJson_69) {
    Value v;
    v.loadFromString("{\"array\": [1, 2, 3], \"nested\": {\"key\": \"value\"}, \"bool\": true, \"null\": null}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["array"].isArray());
    EXPECT_EQ(v["array"].getArray().size(), 3u);
    EXPECT_TRUE(v["nested"].isObject());
    EXPECT_TRUE(v["bool"].isBoolean());
    EXPECT_TRUE(v["bool"].getBoolean());
    EXPECT_TRUE(v["null"].isNull());
}

TEST_F(ValueTest_69, RoundTripJsonObject_69) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    std::ostringstream os;
    v.writeToStream(os, false, false);
    std::string output = os.str();
    
    Value v2;
    v2.loadFromString(output);
    EXPECT_TRUE(v2.isObject());
    EXPECT_EQ(v2["key"].getString(), "value");
}

TEST_F(ValueTest_69, NullValueComparisons_69) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueTest_69, StringValueComparisons_69) {
    Value v1("abc");
    Value v2("def");
    EXPECT_TRUE(v1 < v2);
    EXPECT_TRUE(v2 > v1);
    EXPECT_TRUE(v1 <= v2);
    EXPECT_TRUE(v2 >= v1);
}

TEST_F(ValueTest_69, SelfAssignment_69) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_69, WriteToStreamEscapeAll_69) {
    Value v("hello\nworld");
    std::ostringstream os;
    v.writeToStream(os, false, true);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTest_69, LoadFromStringWithWhitespace_69) {
    Value v;
    v.loadFromString("  { \"key\" : \"value\" }  ");
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_69, LoadNumberFromString_69) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_69, LoadDoubleFromString_69) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_69, LoadStringFromString_69) {
    Value v;
    v.loadFromString("\"hello world\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello world");
}

TEST_F(ValueTest_69, NestedArrayAccess_69) {
    Value v;
    v.loadFromString("[[1, 2], [3, 4]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
    EXPECT_TRUE(v[(size_t)0].isArray());
    EXPECT_TRUE(v[(size_t)1].isArray());
}
