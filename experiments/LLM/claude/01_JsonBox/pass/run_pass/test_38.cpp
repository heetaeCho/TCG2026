#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueTest_38 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(ValueTest_38, DefaultConstructorCreatesNull_38) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_38, StringConstructor_38) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_38, CStringConstructor_38) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_38, IntConstructor_38) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_38, DoubleConstructor_38) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_38, BooleanConstructorTrue_38) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_38, BooleanConstructorFalse_38) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_38, ObjectConstructor_38) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_38, ArrayConstructor_38) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_38, CopyConstructor_38) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

TEST_F(ValueTest_38, StreamConstructorValidJson_38) {
    std::istringstream iss("\"hello\"");
    Value v(iss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

// ==================== Type Check Tests ====================

TEST_F(ValueTest_38, IsStringReturnsTrueForString_38) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_38, IsIntegerReturnsTrueForInt_38) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_38, IsDoubleReturnsTrueForDouble_38) {
    Value v(2.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_38, IsObjectReturnsTrueForObject_38) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_38, IsArrayReturnsTrueForArray_38) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_38, IsBooleanReturnsTrueForBool_38) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_38, IsNullReturnsTrueForDefault_38) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
}

TEST_F(ValueTest_38, IsNumericForInteger_38) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_38, IsNumericForDouble_38) {
    Value v(5.5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_38, IsNumericFalseForString_38) {
    Value v("5");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_38, IsStringableForString_38) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_38, IsStringableForInteger_38) {
    Value v(42);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_38, IsStringableForDouble_38) {
    Value v(3.14);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_38, IsStringableForBoolean_38) {
    Value v(true);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_38, IsStringableForNull_38) {
    Value v;
    EXPECT_TRUE(v.isStringable());
}

// ==================== GetType Tests ====================

TEST_F(ValueTest_38, GetTypeString_38) {
    Value v("test");
    EXPECT_EQ(v.getType(), Value::STRING);
}

TEST_F(ValueTest_38, GetTypeInteger_38) {
    Value v(10);
    EXPECT_EQ(v.getType(), Value::INTEGER);
}

TEST_F(ValueTest_38, GetTypeDouble_38) {
    Value v(1.0);
    EXPECT_EQ(v.getType(), Value::DOUBLE);
}

TEST_F(ValueTest_38, GetTypeObject_38) {
    Object obj;
    Value v(obj);
    EXPECT_EQ(v.getType(), Value::OBJECT);
}

TEST_F(ValueTest_38, GetTypeArray_38) {
    Array arr;
    Value v(arr);
    EXPECT_EQ(v.getType(), Value::ARRAY);
}

TEST_F(ValueTest_38, GetTypeBoolean_38) {
    Value v(true);
    EXPECT_EQ(v.getType(), Value::BOOLEAN);
}

TEST_F(ValueTest_38, GetTypeNull_38) {
    Value v;
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

// ==================== Getter/Setter Tests ====================

TEST_F(ValueTest_38, SetAndGetString_38) {
    Value v;
    v.setString("test");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

TEST_F(ValueTest_38, SetAndGetInteger_38) {
    Value v;
    v.setInteger(100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST_F(ValueTest_38, SetAndGetDouble_38) {
    Value v;
    v.setDouble(2.718);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_38, SetAndGetBoolean_38) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_38, SetAndGetObject_38) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_38, SetAndGetArray_38) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    arr.push_back(Value(3));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_38, SetNull_38) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_38, GetFloat_38) {
    Value v(3.14);
    EXPECT_FLOAT_EQ(v.getFloat(), 3.14f);
}

TEST_F(ValueTest_38, GetToStringFromInteger_38) {
    Value v(42);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_38, GetToStringFromString_38) {
    Value v("hello");
    std::string result = v.getToString();
    EXPECT_EQ(result, "hello");
}

// ==================== TryGet Tests ====================

TEST_F(ValueTest_38, TryGetStringReturnsValueWhenString_38) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST_F(ValueTest_38, TryGetStringReturnsDefaultWhenNotString_38) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_38, TryGetIntegerReturnsValueWhenInteger_38) {
    Value v(42);
    EXPECT_EQ(v.tryGetInteger(0), 42);
}

TEST_F(ValueTest_38, TryGetIntegerReturnsDefaultWhenNotInteger_38) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(99), 99);
}

TEST_F(ValueTest_38, TryGetDoubleReturnsValueWhenDouble_38) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 3.14);
}

TEST_F(ValueTest_38, TryGetDoubleReturnsDefaultWhenNotDouble_38) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.0), 1.0);
}

TEST_F(ValueTest_38, TryGetFloatReturnsValueWhenDouble_38) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST_F(ValueTest_38, TryGetFloatReturnsDefaultWhenNotDouble_38) {
    Value v("hello");
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.5f), 1.5f);
}

TEST_F(ValueTest_38, TryGetBooleanReturnsValueWhenBoolean_38) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_38, TryGetBooleanReturnsDefaultWhenNotBoolean_38) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ==================== Assignment Operator Tests ====================

TEST_F(ValueTest_38, AssignmentFromValue_38) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_38, AssignmentFromString_38) {
    Value v;
    v = std::string("test");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

TEST_F(ValueTest_38, AssignmentFromCString_38) {
    Value v;
    v = "cstring";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "cstring");
}

TEST_F(ValueTest_38, AssignmentFromInt_38) {
    Value v;
    v = 77;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 77);
}

TEST_F(ValueTest_38, AssignmentFromDouble_38) {
    Value v;
    v = 1.23;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.23);
}

TEST_F(ValueTest_38, AssignmentFromObject_38) {
    Value v;
    Object obj;
    obj["key"] = Value("val");
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_38, AssignmentFromArray_38) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_38, AssignmentFromBool_38) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

// ==================== Type Change Tests ====================

TEST_F(ValueTest_38, ChangeTypeFromIntToString_38) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setString("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST_F(ValueTest_38, ChangeTypeFromStringToNull_38) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_38, ChangeTypeFromNullToObject_38) {
    Value v;
    EXPECT_TRUE(v.isNull());
    Object obj;
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
}

// ==================== Comparison Operator Tests ====================

TEST_F(ValueTest_38, EqualityOperator_38) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_38, InequalityOperator_38) {
    Value v1(42);
    Value v2(43);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_38, LessThanOperator_38) {
    Value v1(10);
    Value v2(20);
    EXPECT_TRUE(v1 < v2);
}

TEST_F(ValueTest_38, LessThanOrEqualOperator_38) {
    Value v1(10);
    Value v2(10);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_38, GreaterThanOperator_38) {
    Value v1(20);
    Value v2(10);
    EXPECT_TRUE(v1 > v2);
}

TEST_F(ValueTest_38, GreaterThanOrEqualOperator_38) {
    Value v1(10);
    Value v2(10);
    EXPECT_TRUE(v1 >= v2);
}

TEST_F(ValueTest_38, EqualityDifferentTypes_38) {
    Value v1(42);
    Value v2("42");
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_38, EqualityStrings_38) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_38, EqualityBooleans_38) {
    Value v1(true);
    Value v2(true);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_38, EqualityNulls_38) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

// ==================== Subscript Operator Tests ====================

TEST_F(ValueTest_38, SubscriptByStringKeyOnObject_38) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    Value& ref = v["key"];
    EXPECT_TRUE(ref.isString());
    EXPECT_EQ(ref.getString(), "value");
}

TEST_F(ValueTest_38, SubscriptByCStringKeyOnObject_38) {
    Object obj;
    obj["key"] = Value(123);
    Value v(obj);
    Value& ref = v["key"];
    EXPECT_TRUE(ref.isInteger());
    EXPECT_EQ(ref.getInteger(), 123);
}

TEST_F(ValueTest_38, SubscriptByIndexOnArray_38) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    Value& ref = v[(size_t)1];
    EXPECT_TRUE(ref.isInteger());
    EXPECT_EQ(ref.getInteger(), 20);
}

TEST_F(ValueTest_38, SubscriptCreatesNewKeyInObject_38) {
    Object obj;
    Value v(obj);
    v["newKey"] = Value("newValue");
    EXPECT_TRUE(v["newKey"].isString());
    EXPECT_EQ(v["newKey"].getString(), "newValue");
}

// ==================== Load/Parse Tests ====================

TEST_F(ValueTest_38, LoadFromStringInteger_38) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_38, LoadFromStringString_38) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_38, LoadFromStringBoolean_38) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_38, LoadFromStringNull_38) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_38, LoadFromStringObject_38) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST_F(ValueTest_38, LoadFromStringArray_38) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_38, LoadFromStringDouble_38) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_38, LoadFromStream_38) {
    Value v;
    std::istringstream iss("{\"a\": 1}");
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_38, LoadFromStringNestedObject_38) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": 42}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

TEST_F(ValueTest_38, LoadFromStringNestedArray_38) {
    Value v;
    v.loadFromString("[[1, 2], [3, 4]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

// ==================== Write/Serialize Tests ====================

TEST_F(ValueTest_38, WriteToStreamInteger_38) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_FALSE(oss.str().empty());
    EXPECT_NE(oss.str().find("42"), std::string::npos);
}

TEST_F(ValueTest_38, WriteToStreamString_38) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("hello"), std::string::npos);
}

TEST_F(ValueTest_38, WriteToStreamNull_38) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("null"), std::string::npos);
}

TEST_F(ValueTest_38, WriteToStreamBoolean_38) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("true"), std::string::npos);
}

TEST_F(ValueTest_38, WriteToStreamObject_38) {
    Object obj;
    obj["key"] = Value("val");
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("key"), std::string::npos);
}

TEST_F(ValueTest_38, WriteToStreamArray_38) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string result = oss.str();
    EXPECT_NE(result.find("["), std::string::npos);
    EXPECT_NE(result.find("]"), std::string::npos);
}

TEST_F(ValueTest_38, WriteToStreamWithIndent_38) {
    Object obj;
    obj["key"] = Value("val");
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    EXPECT_NE(oss.str().find("\n"), std::string::npos);
}

// ==================== Static Escape Method Tests ====================

TEST_F(ValueTest_38, EscapeMinimumCharactersBackslash_38) {
    std::string result = Value::escapeMinimumCharacters("hello\\world");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST_F(ValueTest_38, EscapeMinimumCharactersQuote_38) {
    std::string result = Value::escapeMinimumCharacters("hello\"world");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_38, EscapeMinimumCharactersNoSpecial_38) {
    std::string result = Value::escapeMinimumCharacters("hello");
    EXPECT_EQ(result, "hello");
}

TEST_F(ValueTest_38, EscapeAllCharactersBasicAscii_38) {
    std::string result = Value::escapeAllCharacters("hello");
    // All chars should be escaped to unicode
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

TEST_F(ValueTest_38, EscapeToUnicode_38) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ==================== Boundary/Edge Cases ====================

TEST_F(ValueTest_38, EmptyStringValue_38) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_38, ZeroIntegerValue_38) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_38, NegativeIntegerValue_38) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST_F(ValueTest_38, ZeroDoubleValue_38) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_38, NegativeDoubleValue_38) {
    Value v(-1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -1.5);
}

TEST_F(ValueTest_38, EmptyObjectValue_38) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_38, EmptyArrayValue_38) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_38, LoadFromStringEmptyObject_38) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_38, LoadFromStringEmptyArray_38) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_38, LoadFromStringNegativeNumber_38) {
    Value v;
    v.loadFromString("-42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST_F(ValueTest_38, LoadFromStringBooleanFalse_38) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_38, LoadFromStringWithWhitespace_38) {
    Value v;
    v.loadFromString("  42  ");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_38, RoundTripSerialization_38) {
    Value original;
    original.loadFromString("{\"name\": \"test\", \"value\": 42, \"flag\": true, \"nothing\": null}");
    
    std::ostringstream oss;
    original.writeToStream(oss, false, false);
    
    Value reparsed;
    reparsed.loadFromString(oss.str());
    
    EXPECT_TRUE(reparsed.isObject());
    EXPECT_EQ(reparsed["name"].getString(), "test");
    EXPECT_EQ(reparsed["value"].getInteger(), 42);
    EXPECT_TRUE(reparsed["flag"].getBoolean());
    EXPECT_TRUE(reparsed["nothing"].isNull());
}

TEST_F(ValueTest_38, StreamOutputOperator_38) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

TEST_F(ValueTest_38, LargeIntegerValue_38) {
    Value v(2147483647); // INT_MAX
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST_F(ValueTest_38, SubscriptArrayFirstElement_38) {
    Array arr;
    arr.push_back(Value("first"));
    arr.push_back(Value("second"));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getString(), "first");
}

TEST_F(ValueTest_38, SubscriptArrayLastElement_38) {
    Array arr;
    arr.push_back(Value("first"));
    arr.push_back(Value("last"));
    Value v(arr);
    EXPECT_EQ(v[(size_t)1].getString(), "last");
}

TEST_F(ValueTest_38, LoadFromStringEscapedCharacters_38) {
    Value v;
    v.loadFromString("\"hello\\nworld\"");
    EXPECT_TRUE(v.isString());
    EXPECT_NE(v.getString().find('\n'), std::string::npos);
}

TEST_F(ValueTest_38, MultipleSetterCalls_38) {
    Value v;
    v.setString("hello");
    EXPECT_TRUE(v.isString());
    v.setInteger(42);
    EXPECT_TRUE(v.isInteger());
    v.setDouble(3.14);
    EXPECT_TRUE(v.isDouble());
    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_38, SelfAssignment_38) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_38, LoadComplexJson_38) {
    Value v;
    v.loadFromString(R"({
        "string": "hello",
        "integer": 42,
        "double": 3.14,
        "boolean": true,
        "null_val": null,
        "array": [1, 2, 3],
        "object": {"nested": "value"}
    })");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["string"].isString());
    EXPECT_TRUE(v["integer"].isInteger());
    EXPECT_TRUE(v["double"].isDouble());
    EXPECT_TRUE(v["boolean"].isBoolean());
    EXPECT_TRUE(v["null_val"].isNull());
    EXPECT_TRUE(v["array"].isArray());
    EXPECT_TRUE(v["object"].isObject());
}
