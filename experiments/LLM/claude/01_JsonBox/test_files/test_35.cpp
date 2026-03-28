#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueTest_35 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(ValueTest_35, DefaultConstructorCreatesNull_35) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
}

TEST_F(ValueTest_35, StringConstructor_35) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_35, CStringConstructor_35) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_35, IntConstructor_35) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_35, IntConstructorNegative_35) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST_F(ValueTest_35, IntConstructorZero_35) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_35, DoubleConstructor_35) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_35, DoubleConstructorZero_35) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_35, BooleanConstructorTrue_35) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_35, BooleanConstructorFalse_35) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_35, ObjectConstructor_35) {
    Object obj;
    obj["key"] = Value(123);
    Value v(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_35, ArrayConstructor_35) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_35, CopyConstructor_35) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

TEST_F(ValueTest_35, CopyConstructorString_35) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "test");
}

TEST_F(ValueTest_35, StreamConstructor_35) {
    std::istringstream input("42");
    Value v(input);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_35, StreamConstructorString_35) {
    std::istringstream input("\"hello\"");
    Value v(input);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

// ==================== Type Check Tests ====================

TEST_F(ValueTest_35, IsStringForString_35) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_35, IsIntegerForInt_35) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_35, IsDoubleForDouble_35) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_35, IsNumericForInt_35) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_35, IsNumericForDouble_35) {
    Value v(5.5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_35, IsNumericForString_35) {
    Value v("notanumber");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_35, IsObjectForObject_35) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_35, IsArrayForArray_35) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_35, IsBooleanForBool_35) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
}

TEST_F(ValueTest_35, IsNullForDefault_35) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_35, IsStringableForString_35) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_35, IsStringableForInt_35) {
    Value v(42);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_35, IsStringableForDouble_35) {
    Value v(3.14);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_35, IsStringableForNull_35) {
    Value v;
    // Null might or might not be stringable depending on impl
    // Just call it to ensure it doesn't crash
    v.isStringable();
}

// ==================== getType Tests ====================

TEST_F(ValueTest_35, GetTypeString_35) {
    Value v("test");
    EXPECT_EQ(v.getType(), Value::STRING);
}

TEST_F(ValueTest_35, GetTypeInteger_35) {
    Value v(10);
    EXPECT_EQ(v.getType(), Value::INTEGER);
}

TEST_F(ValueTest_35, GetTypeDouble_35) {
    Value v(1.0);
    EXPECT_EQ(v.getType(), Value::DOUBLE);
}

TEST_F(ValueTest_35, GetTypeObject_35) {
    Object obj;
    Value v(obj);
    EXPECT_EQ(v.getType(), Value::OBJECT);
}

TEST_F(ValueTest_35, GetTypeArray_35) {
    Array arr;
    Value v(arr);
    EXPECT_EQ(v.getType(), Value::ARRAY);
}

TEST_F(ValueTest_35, GetTypeBoolean_35) {
    Value v(true);
    EXPECT_EQ(v.getType(), Value::BOOLEAN);
}

TEST_F(ValueTest_35, GetTypeNull_35) {
    Value v;
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

// ==================== Assignment Operator Tests ====================

TEST_F(ValueTest_35, AssignValueToValue_35) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_35, AssignString_35) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_35, AssignCString_35) {
    Value v;
    v = "cstring";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "cstring");
}

TEST_F(ValueTest_35, AssignInt_35) {
    Value v;
    v = 99;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_35, AssignDouble_35) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_35, AssignObject_35) {
    Value v;
    Object obj;
    obj["x"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_35, AssignArray_35) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_35, AssignBool_35) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_35, AssignChangesType_35) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v = "now a string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

// ==================== Getter/Setter Tests ====================

TEST_F(ValueTest_35, SetAndGetString_35) {
    Value v;
    v.setString("test string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test string");
}

TEST_F(ValueTest_35, SetAndGetInteger_35) {
    Value v;
    v.setInteger(777);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 777);
}

TEST_F(ValueTest_35, SetAndGetDouble_35) {
    Value v;
    v.setDouble(1.23456);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.23456);
}

TEST_F(ValueTest_35, SetAndGetBoolean_35) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
    v.setBoolean(false);
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_35, SetAndGetObject_35) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    obj["b"] = Value("two");
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    const Object& retrieved = v.getObject();
    EXPECT_EQ(retrieved.size(), 2u);
}

TEST_F(ValueTest_35, SetAndGetArray_35) {
    Value v;
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    const Array& retrieved = v.getArray();
    EXPECT_EQ(retrieved.size(), 3u);
}

TEST_F(ValueTest_35, SetNull_35) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_35, GetFloat_35) {
    Value v(3.14);
    float f = v.getFloat();
    EXPECT_NEAR(f, 3.14f, 0.001f);
}

TEST_F(ValueTest_35, GetToStringFromInt_35) {
    Value v(42);
    std::string s = v.getToString();
    EXPECT_EQ(s, "42");
}

TEST_F(ValueTest_35, GetToStringFromString_35) {
    Value v("hello");
    std::string s = v.getToString();
    EXPECT_EQ(s, "hello");
}

// ==================== tryGet Tests ====================

TEST_F(ValueTest_35, TryGetStringWhenString_35) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST_F(ValueTest_35, TryGetStringWhenNotString_35) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_35, TryGetIntegerWhenInteger_35) {
    Value v(100);
    EXPECT_EQ(v.tryGetInteger(0), 100);
}

TEST_F(ValueTest_35, TryGetIntegerWhenNotInteger_35) {
    Value v("not an int");
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

TEST_F(ValueTest_35, TryGetDoubleWhenDouble_35) {
    Value v(9.99);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 9.99);
}

TEST_F(ValueTest_35, TryGetDoubleWhenNotDouble_35) {
    Value v("not a double");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.0), 1.0);
}

TEST_F(ValueTest_35, TryGetFloatWhenDouble_35) {
    Value v(2.5);
    EXPECT_NEAR(v.tryGetFloat(0.0f), 2.5f, 0.001f);
}

TEST_F(ValueTest_35, TryGetFloatWhenNotDouble_35) {
    Value v("not a float");
    EXPECT_NEAR(v.tryGetFloat(7.7f), 7.7f, 0.001f);
}

TEST_F(ValueTest_35, TryGetBooleanWhenBoolean_35) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_35, TryGetBooleanWhenNotBoolean_35) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ==================== Comparison Operator Tests ====================

TEST_F(ValueTest_35, EqualityOperator_35) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_35, InequalityOperator_35) {
    Value v1(42);
    Value v2(43);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_35, EqualityDifferentTypes_35) {
    Value v1(42);
    Value v2("42");
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_35, LessThanOperator_35) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_35, LessThanOrEqualOperator_35) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_35, GreaterThanOperator_35) {
    Value v1(10);
    Value v2(5);
    EXPECT_TRUE(v1 > v2);
}

TEST_F(ValueTest_35, GreaterThanOrEqualOperator_35) {
    Value v1(10);
    Value v2(10);
    EXPECT_TRUE(v1 >= v2);
}

TEST_F(ValueTest_35, EqualStrings_35) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_35, EqualBooleans_35) {
    Value v1(true);
    Value v2(true);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_35, NullEquality_35) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

// ==================== Subscript Operator Tests ====================

TEST_F(ValueTest_35, SubscriptStringKeyOnObject_35) {
    Object obj;
    obj["key"] = Value(42);
    Value v(obj);
    EXPECT_TRUE(v["key"].isInteger());
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST_F(ValueTest_35, SubscriptCStringKeyOnObject_35) {
    Object obj;
    obj["name"] = Value("John");
    Value v(obj);
    const char* key = "name";
    EXPECT_TRUE(v[key].isString());
    EXPECT_EQ(v[key].getString(), "John");
}

TEST_F(ValueTest_35, SubscriptIndexOnArray_35) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

TEST_F(ValueTest_35, SubscriptCreatesNewKeyInObject_35) {
    Object obj;
    Value v(obj);
    v["newkey"] = 42;
    EXPECT_TRUE(v["newkey"].isInteger());
    EXPECT_EQ(v["newkey"].getInteger(), 42);
}

// ==================== Load Tests ====================

TEST_F(ValueTest_35, LoadFromStringInteger_35) {
    Value v;
    v.loadFromString("123");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

TEST_F(ValueTest_35, LoadFromStringString_35) {
    Value v;
    v.loadFromString("\"hello world\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello world");
}

TEST_F(ValueTest_35, LoadFromStringBoolean_35) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_35, LoadFromStringNull_35) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_35, LoadFromStringObject_35) {
    Value v;
    v.loadFromString("{\"key\": 42}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST_F(ValueTest_35, LoadFromStringArray_35) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    const Array& arr = v.getArray();
    EXPECT_EQ(arr.size(), 3u);
}

TEST_F(ValueTest_35, LoadFromStringDouble_35) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_NEAR(v.getDouble(), 3.14, 0.001);
}

TEST_F(ValueTest_35, LoadFromStream_35) {
    std::istringstream input("{\"a\": 1, \"b\": 2}");
    Value v;
    v.loadFromStream(input);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_35, LoadFromStringNegativeInt_35) {
    Value v;
    v.loadFromString("-42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST_F(ValueTest_35, LoadFromStringFalse_35) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

// ==================== Write Tests ====================

TEST_F(ValueTest_35, WriteToStreamInteger_35) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(ValueTest_35, WriteToStreamString_35) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(ValueTest_35, WriteToStreamNull_35) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("null"), std::string::npos);
}

TEST_F(ValueTest_35, WriteToStreamBoolean_35) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(ValueTest_35, WriteToStreamIndented_35) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("key"), std::string::npos);
    EXPECT_NE(output.find("value"), std::string::npos);
}

// ==================== Escape Tests ====================

TEST_F(ValueTest_35, EscapeMinimumCharacters_35) {
    std::string result = Value::escapeMinimumCharacters("hello\nworld");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_35, EscapeMinimumCharactersQuote_35) {
    std::string result = Value::escapeMinimumCharacters("say \"hi\"");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_35, EscapeMinimumCharactersBackslash_35) {
    std::string result = Value::escapeMinimumCharacters("a\\b");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST_F(ValueTest_35, EscapeMinimumCharactersNoEscape_35) {
    std::string result = Value::escapeMinimumCharacters("hello");
    EXPECT_EQ(result, "hello");
}

TEST_F(ValueTest_35, EscapeAllCharacters_35) {
    std::string result = Value::escapeAllCharacters("hello\nworld");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_35, EscapeToUnicode_35) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ==================== Boundary and Edge Case Tests ====================

TEST_F(ValueTest_35, EmptyString_35) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_35, EmptyObject_35) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_35, EmptyArray_35) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_35, LargeInteger_35) {
    Value v(2147483647); // INT_MAX
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST_F(ValueTest_35, NegativeLargeInteger_35) {
    Value v(-2147483647);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -2147483647);
}

TEST_F(ValueTest_35, VerySmallDouble_35) {
    Value v(0.0000001);
    EXPECT_TRUE(v.isDouble());
    EXPECT_NEAR(v.getDouble(), 0.0000001, 1e-10);
}

TEST_F(ValueTest_35, NegativeDouble_35) {
    Value v(-99.99);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -99.99);
}

TEST_F(ValueTest_35, SetStringOverwritesPreviousType_35) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setString("now string");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_EQ(v.getString(), "now string");
}

TEST_F(ValueTest_35, SetIntegerOverwritesPreviousType_35) {
    Value v("was a string");
    EXPECT_TRUE(v.isString());
    v.setInteger(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_35, SetDoubleOverwritesPreviousType_35) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    v.setDouble(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
}

TEST_F(ValueTest_35, SetNullOverwritesPreviousType_35) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_35, NestedObjectParsing_35) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": 42}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

TEST_F(ValueTest_35, NestedArrayParsing_35) {
    Value v;
    v.loadFromString("[[1, 2], [3, 4]]");
    EXPECT_TRUE(v.isArray());
    const Array& arr = v.getArray();
    EXPECT_EQ(arr.size(), 2u);
    EXPECT_TRUE(arr[0].isArray());
    EXPECT_TRUE(arr[1].isArray());
}

TEST_F(ValueTest_35, MixedTypesInArray_35) {
    Value v;
    v.loadFromString("[1, \"two\", true, null, 3.14]");
    EXPECT_TRUE(v.isArray());
    const Array& arr = v.getArray();
    EXPECT_EQ(arr.size(), 5u);
    EXPECT_TRUE(arr[0].isInteger());
    EXPECT_TRUE(arr[1].isString());
    EXPECT_TRUE(arr[2].isBoolean());
    EXPECT_TRUE(arr[3].isNull());
    EXPECT_TRUE(arr[4].isDouble());
}

TEST_F(ValueTest_35, StreamOutputOperator_35) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_NE(oss.str().find("42"), std::string::npos);
}

TEST_F(ValueTest_35, SelfAssignment_35) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_35, LoadFromStringEmptyObject_35) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_35, LoadFromStringEmptyArray_35) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_35, WriteAndReloadRoundTrip_35) {
    Value original;
    original.loadFromString("{\"name\": \"test\", \"value\": 42, \"flag\": true}");
    
    std::ostringstream oss;
    original.writeToStream(oss, false, false);
    
    Value reloaded;
    reloaded.loadFromString(oss.str());
    
    EXPECT_TRUE(reloaded.isObject());
    EXPECT_EQ(reloaded["name"].getString(), "test");
    EXPECT_EQ(reloaded["value"].getInteger(), 42);
    EXPECT_TRUE(reloaded["flag"].getBoolean());
}

TEST_F(ValueTest_35, EscapedStringInJson_35) {
    Value v;
    v.loadFromString("{\"key\": \"hello\\nworld\"}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["key"].isString());
    EXPECT_NE(v["key"].getString().find('\n'), std::string::npos);
}

TEST_F(ValueTest_35, UnicodeEscapeInJson_35) {
    Value v;
    v.loadFromString("{\"key\": \"\\u0041\"}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getString(), "A");
}
