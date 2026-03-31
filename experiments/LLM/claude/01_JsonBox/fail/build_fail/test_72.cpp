#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueTest_72 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Default Constructor Tests ====================

TEST_F(ValueTest_72, DefaultConstructorCreatesNullValue_72) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

// ==================== String Constructor Tests ====================

TEST_F(ValueTest_72, StringConstructorFromStdString_72) {
    std::string str = "hello";
    Value v(str);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
    EXPECT_EQ(v.getType(), Value::STRING);
}

TEST_F(ValueTest_72, StringConstructorFromCString_72) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_72, StringConstructorEmptyString_72) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

// ==================== Integer Constructor Tests ====================

TEST_F(ValueTest_72, IntConstructorPositive_72) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
    EXPECT_EQ(v.getType(), Value::INTEGER);
}

TEST_F(ValueTest_72, IntConstructorNegative_72) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST_F(ValueTest_72, IntConstructorZero_72) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

// ==================== Double Constructor Tests ====================

TEST_F(ValueTest_72, DoubleConstructor_72) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
    EXPECT_EQ(v.getType(), Value::DOUBLE);
}

TEST_F(ValueTest_72, DoubleConstructorZero_72) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_72, DoubleConstructorNegative_72) {
    Value v(-2.718);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -2.718);
}

// ==================== Boolean Constructor Tests ====================

TEST_F(ValueTest_72, BoolConstructorTrue_72) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_EQ(v.getBoolean(), true);
    EXPECT_EQ(v.getType(), Value::BOOLEAN);
}

TEST_F(ValueTest_72, BoolConstructorFalse_72) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_EQ(v.getBoolean(), false);
}

// ==================== Object Constructor Tests ====================

TEST_F(ValueTest_72, ObjectConstructorEmpty_72) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getType(), Value::OBJECT);
    EXPECT_TRUE(v.getObject().empty());
}

TEST_F(ValueTest_72, ObjectConstructorWithEntries_72) {
    Object obj;
    obj["key1"] = Value(1);
    obj["key2"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 2u);
}

// ==================== Array Constructor Tests ====================

TEST_F(ValueTest_72, ArrayConstructorEmpty_72) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getType(), Value::ARRAY);
    EXPECT_TRUE(v.getArray().empty());
}

TEST_F(ValueTest_72, ArrayConstructorWithElements_72) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value("two"));
    arr.push_back(Value(3.0));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

// ==================== Copy Constructor Tests ====================

TEST_F(ValueTest_72, CopyConstructorString_72) {
    Value original("test string");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "test string");
    EXPECT_EQ(copy.getType(), Value::STRING);
}

TEST_F(ValueTest_72, CopyConstructorInteger_72) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

TEST_F(ValueTest_72, CopyConstructorDouble_72) {
    Value original(3.14);
    Value copy(original);
    EXPECT_TRUE(copy.isDouble());
    EXPECT_DOUBLE_EQ(copy.getDouble(), 3.14);
}

TEST_F(ValueTest_72, CopyConstructorBoolean_72) {
    Value original(true);
    Value copy(original);
    EXPECT_TRUE(copy.isBoolean());
    EXPECT_EQ(copy.getBoolean(), true);
}

TEST_F(ValueTest_72, CopyConstructorNull_72) {
    Value original;
    Value copy(original);
    EXPECT_TRUE(copy.isNull());
}

TEST_F(ValueTest_72, CopyConstructorObject_72) {
    Object obj;
    obj["a"] = Value(1);
    Value original(obj);
    Value copy(original);
    EXPECT_TRUE(copy.isObject());
    EXPECT_EQ(copy.getObject().size(), 1u);
}

TEST_F(ValueTest_72, CopyConstructorArray_72) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value original(arr);
    Value copy(original);
    EXPECT_TRUE(copy.isArray());
    EXPECT_EQ(copy.getArray().size(), 2u);
}

TEST_F(ValueTest_72, CopyConstructorDeepCopyString_72) {
    Value original("original");
    Value copy(original);
    copy.setString("modified");
    EXPECT_EQ(original.getString(), "original");
    EXPECT_EQ(copy.getString(), "modified");
}

TEST_F(ValueTest_72, CopyConstructorDeepCopyInteger_72) {
    Value original(10);
    Value copy(original);
    copy.setInteger(20);
    EXPECT_EQ(original.getInteger(), 10);
    EXPECT_EQ(copy.getInteger(), 20);
}

// ==================== Assignment Operator Tests ====================

TEST_F(ValueTest_72, AssignmentFromValue_72) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_72, AssignmentFromString_72) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_72, AssignmentFromCString_72) {
    Value v;
    v = "c-string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "c-string");
}

TEST_F(ValueTest_72, AssignmentFromInt_72) {
    Value v;
    v = 99;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_72, AssignmentFromDouble_72) {
    Value v;
    v = 1.5;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.5);
}

TEST_F(ValueTest_72, AssignmentFromObject_72) {
    Value v;
    Object obj;
    obj["x"] = Value(10);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_72, AssignmentFromArray_72) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_72, AssignmentFromBool_72) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_EQ(v.getBoolean(), true);
}

TEST_F(ValueTest_72, AssignmentChangesType_72) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v = "now a string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

// ==================== Type Checking Tests ====================

TEST_F(ValueTest_72, IsStringReturnsTrueForString_72) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_72, IsIntegerReturnsTrueForInteger_72) {
    Value v(5);
    EXPECT_FALSE(v.isString());
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_72, IsNumericForInteger_72) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_72, IsNumericForDouble_72) {
    Value v(5.0);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_72, IsNumericForString_72) {
    Value v("hello");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_72, IsStringableForString_72) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

// ==================== Setter Tests ====================

TEST_F(ValueTest_72, SetStringChangesValue_72) {
    Value v;
    v.setString("new value");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "new value");
}

TEST_F(ValueTest_72, SetIntegerChangesValue_72) {
    Value v;
    v.setInteger(123);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

TEST_F(ValueTest_72, SetDoubleChangesValue_72) {
    Value v;
    v.setDouble(9.99);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 9.99);
}

TEST_F(ValueTest_72, SetBooleanChangesValue_72) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_EQ(v.getBoolean(), true);
}

TEST_F(ValueTest_72, SetNullChangesType_72) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_72, SetObjectChangesValue_72) {
    Value v;
    Object obj;
    obj["key"] = Value("val");
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_72, SetArrayChangesValue_72) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

// ==================== Getter Tests ====================

TEST_F(ValueTest_72, GetFloatFromDouble_72) {
    Value v(3.14);
    EXPECT_FLOAT_EQ(v.getFloat(), 3.14f);
}

TEST_F(ValueTest_72, GetToStringFromInteger_72) {
    Value v(42);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_72, GetToStringFromString_72) {
    Value v("hello");
    std::string result = v.getToString();
    EXPECT_EQ(result, "hello");
}

// ==================== TryGet Tests ====================

TEST_F(ValueTest_72, TryGetStringReturnsValueWhenString_72) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST_F(ValueTest_72, TryGetStringReturnsDefaultWhenNotString_72) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_72, TryGetIntegerReturnsValueWhenInteger_72) {
    Value v(10);
    EXPECT_EQ(v.tryGetInteger(0), 10);
}

TEST_F(ValueTest_72, TryGetIntegerReturnsDefaultWhenNotInteger_72) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(42), 42);
}

TEST_F(ValueTest_72, TryGetDoubleReturnsValueWhenDouble_72) {
    Value v(2.5);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 2.5);
}

TEST_F(ValueTest_72, TryGetDoubleReturnsDefaultWhenNotDouble_72) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.0), 1.0);
}

TEST_F(ValueTest_72, TryGetFloatReturnsValueWhenDouble_72) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST_F(ValueTest_72, TryGetFloatReturnsDefaultWhenNotDouble_72) {
    Value v("hello");
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.0f), 1.0f);
}

TEST_F(ValueTest_72, TryGetBooleanReturnsValueWhenBoolean_72) {
    Value v(true);
    EXPECT_EQ(v.tryGetBoolean(false), true);
}

TEST_F(ValueTest_72, TryGetBooleanReturnsDefaultWhenNotBoolean_72) {
    Value v(42);
    EXPECT_EQ(v.tryGetBoolean(true), true);
}

// ==================== Operator[] Tests ====================

TEST_F(ValueTest_72, ObjectSubscriptByString_72) {
    Object obj;
    obj["key"] = Value(42);
    Value v(obj);
    EXPECT_TRUE(v["key"].isInteger());
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST_F(ValueTest_72, ObjectSubscriptByCString_72) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v["key"].isString());
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST_F(ValueTest_72, ArraySubscriptByIndex_72) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

// ==================== Comparison Operator Tests ====================

TEST_F(ValueTest_72, EqualityOperatorSameIntegers_72) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueTest_72, EqualityOperatorDifferentIntegers_72) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_72, EqualityOperatorSameStrings_72) {
    Value v1("hello");
    Value v2("hello");
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_72, EqualityOperatorDifferentStrings_72) {
    Value v1("hello");
    Value v2("world");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_72, EqualityOperatorDifferentTypes_72) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_72, LessThanOperator_72) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_72, LessThanOrEqualOperator_72) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_72, GreaterThanOperator_72) {
    Value v1(2);
    Value v2(1);
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v2 > v1);
}

TEST_F(ValueTest_72, GreaterThanOrEqualOperator_72) {
    Value v1(2);
    Value v2(2);
    EXPECT_TRUE(v1 >= v2);
}

TEST_F(ValueTest_72, EqualityNullValues_72) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_72, EqualityBooleans_72) {
    Value v1(true);
    Value v2(true);
    EXPECT_TRUE(v1 == v2);
    Value v3(false);
    EXPECT_FALSE(v1 == v3);
}

// ==================== Load / Write Tests ====================

TEST_F(ValueTest_72, LoadFromStringSimpleObject_72) {
    Value v;
    v.loadFromString("{\"key\": 42}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST_F(ValueTest_72, LoadFromStringSimpleArray_72) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_72, LoadFromStringString_72) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_72, LoadFromStringNumber_72) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_72, LoadFromStringDouble_72) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_72, LoadFromStringBoolTrue_72) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_EQ(v.getBoolean(), true);
}

TEST_F(ValueTest_72, LoadFromStringBoolFalse_72) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_EQ(v.getBoolean(), false);
}

TEST_F(ValueTest_72, LoadFromStringNull_72) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_72, LoadFromStream_72) {
    std::istringstream ss("{\"a\": 1}");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_72, WriteToStreamIndented_72) {
    Value v(42);
    std::ostringstream os;
    v.writeToStream(os, true, false);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_72, WriteToStreamNoIndent_72) {
    Value v(42);
    std::ostringstream os;
    v.writeToStream(os, false, false);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_72, WriteToStreamEscapeAll_72) {
    Value v("hello\nworld");
    std::ostringstream os;
    v.writeToStream(os, false, true);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// ==================== Stream Constructor Tests ====================

TEST_F(ValueTest_72, StreamConstructor_72) {
    std::istringstream ss("\"hello\"");
    Value v(ss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_72, StreamConstructorObject_72) {
    std::istringstream ss("{\"key\": \"value\"}");
    Value v(ss);
    EXPECT_TRUE(v.isObject());
}

// ==================== Output Stream Operator Tests ====================

TEST_F(ValueTest_72, OutputStreamOperator_72) {
    Value v(42);
    std::ostringstream os;
    os << v;
    EXPECT_FALSE(os.str().empty());
}

// ==================== Escape Function Tests ====================

TEST_F(ValueTest_72, EscapeMinimumCharacters_72) {
    std::string result = Value::escapeMinimumCharacters("hello\nworld");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_72, EscapeMinimumCharactersQuote_72) {
    std::string result = Value::escapeMinimumCharacters("say \"hi\"");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_72, EscapeMinimumCharactersNoEscapeNeeded_72) {
    std::string result = Value::escapeMinimumCharacters("hello");
    EXPECT_EQ(result, "hello");
}

TEST_F(ValueTest_72, EscapeAllCharactersBasic_72) {
    std::string result = Value::escapeAllCharacters("a");
    // Should at least produce some output
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_72, EscapeToUnicode_72) {
    std::string result = Value::escapeToUnicode('A');
    // Should produce a unicode escape sequence
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result.substr(0, 2), "\\u");
}

// ==================== Nested Structure Tests ====================

TEST_F(ValueTest_72, NestedObjectInArray_72) {
    Value v;
    v.loadFromString("[{\"a\": 1}, {\"b\": 2}]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
    EXPECT_TRUE(v[(size_t)0].isObject());
    EXPECT_TRUE(v[(size_t)1].isObject());
}

TEST_F(ValueTest_72, NestedArrayInObject_72) {
    Value v;
    v.loadFromString("{\"arr\": [1, 2, 3]}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["arr"].isArray());
    EXPECT_EQ(v["arr"].getArray().size(), 3u);
}

TEST_F(ValueTest_72, DeepNesting_72) {
    Value v;
    v.loadFromString("{\"a\": {\"b\": {\"c\": 42}}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["a"].isObject());
    EXPECT_TRUE(v["a"]["b"].isObject());
    EXPECT_EQ(v["a"]["b"]["c"].getInteger(), 42);
}

// ==================== Boundary Tests ====================

TEST_F(ValueTest_72, LargeInteger_72) {
    Value v(2147483647); // INT_MAX
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST_F(ValueTest_72, NegativeLargeInteger_72) {
    Value v(-2147483648); // INT_MIN
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -2147483648);
}

TEST_F(ValueTest_72, VerySmallDouble_72) {
    Value v(1e-300);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1e-300);
}

TEST_F(ValueTest_72, VeryLargeDouble_72) {
    Value v(1e300);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1e300);
}

// ==================== Roundtrip Tests ====================

TEST_F(ValueTest_72, WriteAndReadRoundtrip_72) {
    Object obj;
    obj["name"] = Value("test");
    obj["value"] = Value(42);
    obj["flag"] = Value(true);
    Value original(obj);

    std::ostringstream os;
    original.writeToStream(os, false, false);
    std::string json = os.str();

    Value parsed;
    parsed.loadFromString(json);
    EXPECT_TRUE(parsed.isObject());
    EXPECT_EQ(parsed["name"].getString(), "test");
    EXPECT_EQ(parsed["value"].getInteger(), 42);
    EXPECT_EQ(parsed["flag"].getBoolean(), true);
}

// ==================== Multiple Assignment Type Changes ====================

TEST_F(ValueTest_72, MultipleTypeChanges_72) {
    Value v;
    EXPECT_TRUE(v.isNull());

    v = 42;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);

    v = "hello";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");

    v = 3.14;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);

    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_EQ(v.getBoolean(), true);

    v.setNull();
    EXPECT_TRUE(v.isNull());
}

// ==================== Subscript Creates Entry Tests ====================

TEST_F(ValueTest_72, ObjectSubscriptCreatesNewEntry_72) {
    Object obj;
    Value v(obj);
    v["newKey"] = Value(100);
    EXPECT_EQ(v["newKey"].getInteger(), 100);
}

// ==================== Load From String With Whitespace ====================

TEST_F(ValueTest_72, LoadFromStringWithWhitespace_72) {
    Value v;
    v.loadFromString("  {  \"key\"  :  42  }  ");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getInteger(), 42);
}

// ==================== Negative Double ====================

TEST_F(ValueTest_72, LoadNegativeDouble_72) {
    Value v;
    v.loadFromString("-3.14");
    EXPECT_TRUE(v.isNumeric());
}

// ==================== Escape Backslash ====================

TEST_F(ValueTest_72, EscapeMinimumCharactersBackslash_72) {
    std::string result = Value::escapeMinimumCharacters("path\\to\\file");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}
