#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueTest_41 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(ValueTest_41, DefaultConstructorCreatesNull_41) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_41, StringConstructor_41) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_41, CStringConstructor_41) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_41, IntConstructor_41) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_41, DoubleConstructor_41) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_41, BooleanConstructorTrue_41) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_41, BooleanConstructorFalse_41) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_41, ObjectConstructor_41) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_41, ArrayConstructor_41) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_41, CopyConstructor_41) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

TEST_F(ValueTest_41, StreamConstructor_41) {
    std::istringstream input("\"hello\"");
    Value v(input);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

// ==================== Type Checking Tests ====================

TEST_F(ValueTest_41, IsStringReturnsTrueForString_41) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_41, IsIntegerReturnsTrueForInt_41) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_41, IsDoubleReturnsTrueForDouble_41) {
    Value v(2.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_41, IsNumericForInteger_41) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_41, IsNumericForDouble_41) {
    Value v(5.5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_41, IsNumericFalseForString_41) {
    Value v("hello");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_41, IsObjectReturnsTrueForObject_41) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_41, IsArrayReturnsTrueForArray_41) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_41, IsBooleanReturnsTrueForBool_41) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
}

TEST_F(ValueTest_41, IsNullReturnsTrueForDefault_41) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_41, IsStringableForString_41) {
    Value v("test");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_41, IsStringableForInteger_41) {
    Value v(42);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_41, IsStringableForDouble_41) {
    Value v(3.14);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_41, IsStringableForBoolean_41) {
    Value v(true);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_41, IsStringableForNull_41) {
    Value v;
    EXPECT_TRUE(v.isStringable());
}

// ==================== Getter/Setter Tests ====================

TEST_F(ValueTest_41, SetStringChangesType_41) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setString("changed");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "changed");
}

TEST_F(ValueTest_41, SetIntegerChangesType_41) {
    Value v("hello");
    v.setInteger(99);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_41, SetDoubleChangesType_41) {
    Value v;
    v.setDouble(1.23);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.23);
}

TEST_F(ValueTest_41, SetBooleanChangesType_41) {
    Value v(42);
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_41, SetObjectChangesType_41) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_41, SetArrayChangesType_41) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

TEST_F(ValueTest_41, SetNullClearsValue_41) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_41, GetFloatReturnsFloat_41) {
    Value v(3.14);
    EXPECT_FLOAT_EQ(v.getFloat(), 3.14f);
}

// ==================== Try Getters (Default Values) ====================

TEST_F(ValueTest_41, TryGetStringReturnsValueWhenString_41) {
    Value v("hello");
    EXPECT_EQ(v.tryGetString("default"), "hello");
}

TEST_F(ValueTest_41, TryGetStringReturnsDefaultWhenNotString_41) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_41, TryGetIntegerReturnsValueWhenInteger_41) {
    Value v(42);
    EXPECT_EQ(v.tryGetInteger(0), 42);
}

TEST_F(ValueTest_41, TryGetIntegerReturnsDefaultWhenNotInteger_41) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(0), 0);
}

TEST_F(ValueTest_41, TryGetDoubleReturnsValueWhenDouble_41) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 3.14);
}

TEST_F(ValueTest_41, TryGetDoubleReturnsDefaultWhenNotDouble_41) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 0.0);
}

TEST_F(ValueTest_41, TryGetFloatReturnsValueWhenDouble_41) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST_F(ValueTest_41, TryGetFloatReturnsDefaultWhenNotDouble_41) {
    Value v("hello");
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.0f), 1.0f);
}

TEST_F(ValueTest_41, TryGetBooleanReturnsValueWhenBoolean_41) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_41, TryGetBooleanReturnsDefaultWhenNotBoolean_41) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ==================== Assignment Operator Tests ====================

TEST_F(ValueTest_41, AssignmentFromValue_41) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_41, AssignmentFromString_41) {
    Value v;
    v = std::string("test");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

TEST_F(ValueTest_41, AssignmentFromCString_41) {
    Value v;
    v = "cstring";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "cstring");
}

TEST_F(ValueTest_41, AssignmentFromInt_41) {
    Value v;
    v = 100;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST_F(ValueTest_41, AssignmentFromDouble_41) {
    Value v;
    v = 9.99;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 9.99);
}

TEST_F(ValueTest_41, AssignmentFromObject_41) {
    Value v;
    Object obj;
    obj["key"] = Value("val");
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_41, AssignmentFromArray_41) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_41, AssignmentFromBool_41) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

// ==================== Comparison Operator Tests ====================

TEST_F(ValueTest_41, EqualityOperator_41) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_41, InequalityOperator_41) {
    Value v1(42);
    Value v2(43);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_41, EqualityDifferentTypes_41) {
    Value v1(42);
    Value v2("42");
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_41, LessThanOperator_41) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_41, LessThanOrEqualOperator_41) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_41, GreaterThanOperator_41) {
    Value v1(2);
    Value v2(1);
    EXPECT_TRUE(v1 > v2);
}

TEST_F(ValueTest_41, GreaterThanOrEqualOperator_41) {
    Value v1(2);
    Value v2(2);
    EXPECT_TRUE(v1 >= v2);
}

TEST_F(ValueTest_41, EqualNullValues_41) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_41, EqualStringValues_41) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_41, EqualBoolValues_41) {
    Value v1(true);
    Value v2(true);
    EXPECT_TRUE(v1 == v2);
}

// ==================== Subscript Operator Tests ====================

TEST_F(ValueTest_41, SubscriptWithStringKeyOnObject_41) {
    Object obj;
    obj["key"] = Value(42);
    Value v(obj);
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST_F(ValueTest_41, SubscriptWithCStringKeyOnObject_41) {
    Object obj;
    obj["name"] = Value("test");
    Value v(obj);
    EXPECT_EQ(v["name"].getString(), "test");
}

TEST_F(ValueTest_41, SubscriptWithIndexOnArray_41) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    Value v(arr);
    EXPECT_EQ(v[static_cast<size_t>(0)].getInteger(), 10);
    EXPECT_EQ(v[static_cast<size_t>(1)].getInteger(), 20);
}

TEST_F(ValueTest_41, SubscriptCreatesNewKeyInObject_41) {
    Object obj;
    Value v(obj);
    v["newKey"] = Value(123);
    EXPECT_EQ(v["newKey"].getInteger(), 123);
}

// ==================== GetToString Tests ====================

TEST_F(ValueTest_41, GetToStringForString_41) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

TEST_F(ValueTest_41, GetToStringForInteger_41) {
    Value v(42);
    std::string result = v.getToString();
    EXPECT_EQ(result, "42");
}

TEST_F(ValueTest_41, GetToStringForNull_41) {
    Value v;
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty() && !v.isNull()); // just verify it doesn't crash
}

TEST_F(ValueTest_41, GetToStringForBoolean_41) {
    Value v(true);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

// ==================== Load/Parse Tests ====================

TEST_F(ValueTest_41, LoadFromStringInteger_41) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_41, LoadFromStringString_41) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_41, LoadFromStringBoolean_41) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_41, LoadFromStringNull_41) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_41, LoadFromStringArray_41) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_41, LoadFromStringObject_41) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_41, LoadFromStringDouble_41) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_41, LoadFromStreamInteger_41) {
    std::istringstream input("42");
    Value v;
    v.loadFromStream(input);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_41, LoadFromStreamObject_41) {
    std::istringstream input("{\"a\": 1, \"b\": 2}");
    Value v;
    v.loadFromStream(input);
    EXPECT_TRUE(v.isObject());
}

// ==================== Write Tests ====================

TEST_F(ValueTest_41, WriteToStreamInteger_41) {
    Value v(42);
    std::ostringstream output;
    v.writeToStream(output, false, false);
    EXPECT_FALSE(output.str().empty());
    EXPECT_NE(output.str().find("42"), std::string::npos);
}

TEST_F(ValueTest_41, WriteToStreamString_41) {
    Value v("hello");
    std::ostringstream output;
    v.writeToStream(output, false, false);
    EXPECT_NE(output.str().find("hello"), std::string::npos);
}

TEST_F(ValueTest_41, WriteToStreamNull_41) {
    Value v;
    std::ostringstream output;
    v.writeToStream(output, false, false);
    EXPECT_NE(output.str().find("null"), std::string::npos);
}

TEST_F(ValueTest_41, WriteToStreamBoolean_41) {
    Value v(true);
    std::ostringstream output;
    v.writeToStream(output, false, false);
    EXPECT_NE(output.str().find("true"), std::string::npos);
}

TEST_F(ValueTest_41, WriteToStreamArray_41) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    std::ostringstream output;
    v.writeToStream(output, false, false);
    std::string result = output.str();
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("2"), std::string::npos);
}

TEST_F(ValueTest_41, WriteToStreamObject_41) {
    Object obj;
    obj["key"] = Value("val");
    Value v(obj);
    std::ostringstream output;
    v.writeToStream(output, false, false);
    std::string result = output.str();
    EXPECT_NE(result.find("key"), std::string::npos);
    EXPECT_NE(result.find("val"), std::string::npos);
}

TEST_F(ValueTest_41, WriteToStreamWithIndent_41) {
    Object obj;
    obj["a"] = Value(1);
    Value v(obj);
    std::ostringstream output;
    v.writeToStream(output, true, false);
    std::string result = output.str();
    // Indented output should have some whitespace/newlines
    EXPECT_NE(result.find("\n"), std::string::npos);
}

// ==================== Escape Tests ====================

TEST_F(ValueTest_41, EscapeMinimumCharacters_41) {
    std::string result = Value::escapeMinimumCharacters("hello\nworld");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_41, EscapeMinimumCharactersQuote_41) {
    std::string result = Value::escapeMinimumCharacters("he\"llo");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_41, EscapeMinimumCharactersBackslash_41) {
    std::string result = Value::escapeMinimumCharacters("he\\llo");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST_F(ValueTest_41, EscapeAllCharacters_41) {
    std::string result = Value::escapeAllCharacters("A");
    // All characters should be escaped to unicode
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

TEST_F(ValueTest_41, EscapeToUnicode_41) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_NE(result.find("\\u"), std::string::npos);
    EXPECT_EQ(result.size(), 6u); // \uXXXX is 6 characters
}

// ==================== Boundary and Edge Cases ====================

TEST_F(ValueTest_41, EmptyStringValue_41) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_41, ZeroIntegerValue_41) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_41, NegativeIntegerValue_41) {
    Value v(-42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST_F(ValueTest_41, ZeroDoubleValue_41) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_41, NegativeDoubleValue_41) {
    Value v(-1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -1.5);
}

TEST_F(ValueTest_41, EmptyObjectValue_41) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_41, EmptyArrayValue_41) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_41, GetTypeReturnsCorrectEnum_41) {
    Value vNull;
    EXPECT_EQ(vNull.getType(), Value::NULL_VALUE);

    Value vStr("hello");
    EXPECT_EQ(vStr.getType(), Value::STRING);

    Value vInt(42);
    EXPECT_EQ(vInt.getType(), Value::INTEGER);

    Value vDbl(3.14);
    EXPECT_EQ(vDbl.getType(), Value::DOUBLE);

    Value vBool(true);
    EXPECT_EQ(vBool.getType(), Value::BOOLEAN);

    Value vObj(Object());
    EXPECT_EQ(vObj.getType(), Value::OBJECT);

    Value vArr(Array());
    EXPECT_EQ(vArr.getType(), Value::ARRAY);
}

TEST_F(ValueTest_41, SelfAssignment_41) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_41, OverwriteTypeMultipleTimes_41) {
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

TEST_F(ValueTest_41, LoadFromStringNestedObject_41) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": 42}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

TEST_F(ValueTest_41, LoadFromStringNestedArray_41) {
    Value v;
    v.loadFromString("[[1, 2], [3, 4]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_41, LoadFromStringFalseBoolean_41) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_41, LoadFromStringNegativeNumber_41) {
    Value v;
    v.loadFromString("-42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST_F(ValueTest_41, OutputStreamOperator_41) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

TEST_F(ValueTest_41, RoundTripJsonString_41) {
    Value original;
    original.loadFromString("{\"name\": \"test\", \"value\": 42}");

    std::ostringstream output;
    original.writeToStream(output, false, false);

    Value reparsed;
    reparsed.loadFromString(output.str());

    EXPECT_TRUE(reparsed.isObject());
    EXPECT_EQ(reparsed["name"].getString(), "test");
    EXPECT_EQ(reparsed["value"].getInteger(), 42);
}

TEST_F(ValueTest_41, LargeIntegerValue_41) {
    Value v(2147483647); // INT_MAX
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST_F(ValueTest_41, MinIntegerValue_41) {
    Value v(-2147483647);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -2147483647);
}

TEST_F(ValueTest_41, WriteToStreamEscapeAll_41) {
    Value v("hello");
    std::ostringstream output;
    v.writeToStream(output, false, true);
    std::string result = output.str();
    // With escapeAll, characters should be unicode escaped
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

TEST_F(ValueTest_41, LoadFromStringWithWhitespace_41) {
    Value v;
    v.loadFromString("  {  \"key\"  :  \"value\"  }  ");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST_F(ValueTest_41, LoadFromStringEmptyObject_41) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_41, LoadFromStringEmptyArray_41) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}
