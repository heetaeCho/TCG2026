#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

// ============================================================
// Test Fixture
// ============================================================
class ValueTest_32 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Constructor Tests
// ============================================================

TEST_F(ValueTest_32, DefaultConstructorCreatesNullValue_32) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_32, StringConstructorCreatesStringValue_32) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
    EXPECT_EQ(v.getType(), Value::STRING);
}

TEST_F(ValueTest_32, CStringConstructorCreatesStringValue_32) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_32, IntConstructorCreatesIntegerValue_32) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
    EXPECT_EQ(v.getType(), Value::INTEGER);
}

TEST_F(ValueTest_32, DoubleConstructorCreatesDoubleValue_32) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
    EXPECT_EQ(v.getType(), Value::DOUBLE);
}

TEST_F(ValueTest_32, BooleanConstructorCreatesBooleanValue_32) {
    Value vTrue(true);
    EXPECT_TRUE(vTrue.isBoolean());
    EXPECT_TRUE(vTrue.getBoolean());

    Value vFalse(false);
    EXPECT_TRUE(vFalse.isBoolean());
    EXPECT_FALSE(vFalse.getBoolean());
}

TEST_F(ValueTest_32, ObjectConstructorCreatesObjectValue_32) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getType(), Value::OBJECT);
}

TEST_F(ValueTest_32, ArrayConstructorCreatesArrayValue_32) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getType(), Value::ARRAY);
}

TEST_F(ValueTest_32, CopyConstructorCopiesValue_32) {
    Value original(123);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 123);
}

TEST_F(ValueTest_32, StreamConstructorParsesJson_32) {
    std::istringstream iss("\"hello\"");
    Value v(iss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

// ============================================================
// Type Checking Tests
// ============================================================

TEST_F(ValueTest_32, IsStringReturnsTrueForString_32) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueTest_32, IsIntegerReturnsTrueForInteger_32) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_32, IsDoubleReturnsTrueForDouble_32) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_32, IsNumericReturnsTrueForIntegerAndDouble_32) {
    Value vInt(5);
    Value vDouble(5.5);
    Value vStr("hello");
    EXPECT_TRUE(vInt.isNumeric());
    EXPECT_TRUE(vDouble.isNumeric());
    EXPECT_FALSE(vStr.isNumeric());
}

TEST_F(ValueTest_32, IsBooleanReturnsTrueForBoolean_32) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_32, IsNullReturnsTrueForDefault_32) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_32, IsObjectReturnsTrueForObject_32) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueTest_32, IsArrayReturnsTrueForArray_32) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_FALSE(v.isObject());
}

TEST_F(ValueTest_32, IsStringableForStringAndNumericAndBool_32) {
    Value vStr("test");
    Value vInt(42);
    Value vDouble(3.14);
    Value vBool(true);
    Value vNull;
    EXPECT_TRUE(vStr.isStringable());
    EXPECT_TRUE(vInt.isStringable());
    EXPECT_TRUE(vDouble.isStringable());
    EXPECT_TRUE(vBool.isStringable());
    // Null may or may not be stringable depending on implementation
}

// ============================================================
// Getter / Setter Tests
// ============================================================

TEST_F(ValueTest_32, SetAndGetString_32) {
    Value v;
    v.setString("newValue");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "newValue");
}

TEST_F(ValueTest_32, SetAndGetInteger_32) {
    Value v;
    v.setInteger(99);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_32, SetAndGetDouble_32) {
    Value v;
    v.setDouble(2.718);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_32, SetAndGetBoolean_32) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
    v.setBoolean(false);
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_32, SetAndGetObject_32) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    const Object& retrieved = v.getObject();
    EXPECT_EQ(retrieved.size(), 1u);
    EXPECT_TRUE(retrieved.find("a") != retrieved.end());
}

TEST_F(ValueTest_32, SetAndGetArray_32) {
    Value v;
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    const Array& retrieved = v.getArray();
    EXPECT_EQ(retrieved.size(), 2u);
}

TEST_F(ValueTest_32, SetNull_32) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_32, GetFloatFromDouble_32) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 1.5f);
}

// ============================================================
// tryGet Tests (with defaults)
// ============================================================

TEST_F(ValueTest_32, TryGetStringReturnsValueWhenString_32) {
    Value v("hello");
    EXPECT_EQ(v.tryGetString("default"), "hello");
}

TEST_F(ValueTest_32, TryGetStringReturnsDefaultWhenNotString_32) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_32, TryGetIntegerReturnsValueWhenInteger_32) {
    Value v(100);
    EXPECT_EQ(v.tryGetInteger(-1), 100);
}

TEST_F(ValueTest_32, TryGetIntegerReturnsDefaultWhenNotInteger_32) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

TEST_F(ValueTest_32, TryGetDoubleReturnsValueWhenDouble_32) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 3.14);
}

TEST_F(ValueTest_32, TryGetDoubleReturnsDefaultWhenNotDouble_32) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 0.0);
}

TEST_F(ValueTest_32, TryGetFloatReturnsValueWhenDouble_32) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST_F(ValueTest_32, TryGetFloatReturnsDefaultWhenNotDouble_32) {
    Value v("nope");
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.0f), 1.0f);
}

TEST_F(ValueTest_32, TryGetBooleanReturnsValueWhenBoolean_32) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_32, TryGetBooleanReturnsDefaultWhenNotBoolean_32) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ============================================================
// Assignment Operator Tests
// ============================================================

TEST_F(ValueTest_32, AssignmentFromValue_32) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_32, AssignmentFromString_32) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_32, AssignmentFromCString_32) {
    Value v;
    v = "cstring";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "cstring");
}

TEST_F(ValueTest_32, AssignmentFromInt_32) {
    Value v;
    v = 55;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 55);
}

TEST_F(ValueTest_32, AssignmentFromDouble_32) {
    Value v;
    v = 1.23;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.23);
}

TEST_F(ValueTest_32, AssignmentFromBool_32) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_32, AssignmentFromObject_32) {
    Value v;
    Object obj;
    obj["x"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_32, AssignmentFromArray_32) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

// ============================================================
// Comparison Operator Tests
// ============================================================

TEST_F(ValueTest_32, EqualityOperatorSameValues_32) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueTest_32, EqualityOperatorDifferentValues_32) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_32, EqualityOperatorDifferentTypes_32) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_32, LessThanOperator_32) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_32, LessThanOrEqualOperator_32) {
    Value v1(1);
    Value v2(1);
    Value v3(2);
    EXPECT_TRUE(v1 <= v2);
    EXPECT_TRUE(v1 <= v3);
    EXPECT_FALSE(v3 <= v1);
}

TEST_F(ValueTest_32, GreaterThanOperator_32) {
    Value v1(2);
    Value v2(1);
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v2 > v1);
}

TEST_F(ValueTest_32, GreaterThanOrEqualOperator_32) {
    Value v1(2);
    Value v2(2);
    Value v3(1);
    EXPECT_TRUE(v1 >= v2);
    EXPECT_TRUE(v1 >= v3);
    EXPECT_FALSE(v3 >= v1);
}

TEST_F(ValueTest_32, NullValuesAreEqual_32) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_32, StringEqualityComparison_32) {
    Value v1("abc");
    Value v2("abc");
    Value v3("def");
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}

TEST_F(ValueTest_32, BooleanEqualityComparison_32) {
    Value v1(true);
    Value v2(true);
    Value v3(false);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}

// ============================================================
// Subscript Operator Tests
// ============================================================

TEST_F(ValueTest_32, SubscriptByStringKeyOnObject_32) {
    Object obj;
    obj["key1"] = Value(100);
    Value v(obj);
    Value& accessed = v["key1"];
    EXPECT_TRUE(accessed.isInteger());
    EXPECT_EQ(accessed.getInteger(), 100);
}

TEST_F(ValueTest_32, SubscriptByCStringKeyOnObject_32) {
    Object obj;
    obj["key2"] = Value("val");
    Value v(obj);
    Value& accessed = v["key2"];
    EXPECT_TRUE(accessed.isString());
    EXPECT_EQ(accessed.getString(), "val");
}

TEST_F(ValueTest_32, SubscriptByIndexOnArray_32) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

TEST_F(ValueTest_32, SubscriptCreatesNewKeyInObject_32) {
    Object obj;
    Value v(obj);
    v["newKey"] = Value(42);
    EXPECT_TRUE(v["newKey"].isInteger());
    EXPECT_EQ(v["newKey"].getInteger(), 42);
}

// ============================================================
// Serialization / Deserialization Tests
// ============================================================

TEST_F(ValueTest_32, LoadFromStringInteger_32) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_32, LoadFromStringString_32) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_32, LoadFromStringBoolean_32) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_32, LoadFromStringNull_32) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_32, LoadFromStringDouble_32) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_32, LoadFromStringObject_32) {
    Value v;
    v.loadFromString("{\"key\": 1}");
    EXPECT_TRUE(v.isObject());
    const Object& obj = v.getObject();
    EXPECT_TRUE(obj.find("key") != obj.end());
}

TEST_F(ValueTest_32, LoadFromStringArray_32) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    const Array& arr = v.getArray();
    EXPECT_EQ(arr.size(), 3u);
}

TEST_F(ValueTest_32, LoadFromStream_32) {
    std::istringstream iss("{\"a\": true}");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_32, WriteToStream_32) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(ValueTest_32, WriteToStreamString_32) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(ValueTest_32, WriteToStreamIndented_32) {
    Object obj;
    obj["key"] = Value(1);
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTest_32, WriteToStreamEscapeAll_32) {
    Value v("test");
    std::ostringstream oss;
    v.writeToStream(oss, false, true);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTest_32, StreamInsertionOperator_32) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

// ============================================================
// getToString Tests
// ============================================================

TEST_F(ValueTest_32, GetToStringFromString_32) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

TEST_F(ValueTest_32, GetToStringFromInteger_32) {
    Value v(42);
    std::string s = v.getToString();
    EXPECT_FALSE(s.empty());
    EXPECT_NE(s.find("42"), std::string::npos);
}

TEST_F(ValueTest_32, GetToStringFromDouble_32) {
    Value v(3.14);
    std::string s = v.getToString();
    EXPECT_FALSE(s.empty());
}

TEST_F(ValueTest_32, GetToStringFromBoolean_32) {
    Value vTrue(true);
    Value vFalse(false);
    std::string sTrue = vTrue.getToString();
    std::string sFalse = vFalse.getToString();
    EXPECT_FALSE(sTrue.empty());
    EXPECT_FALSE(sFalse.empty());
}

// ============================================================
// Escape Functions Tests
// ============================================================

TEST_F(ValueTest_32, EscapeMinimumCharacters_32) {
    std::string result = Value::escapeMinimumCharacters("hello\nworld");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_32, EscapeMinimumCharactersQuote_32) {
    std::string result = Value::escapeMinimumCharacters("say \"hi\"");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_32, EscapeMinimumCharactersBackslash_32) {
    std::string result = Value::escapeMinimumCharacters("path\\to");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST_F(ValueTest_32, EscapeMinimumCharactersNoEscapeNeeded_32) {
    std::string input = "simple";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ(result, "simple");
}

TEST_F(ValueTest_32, EscapeAllCharacters_32) {
    std::string result = Value::escapeAllCharacters("hello\nworld");
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_32, EscapeToUnicode_32) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
    // Unicode escape format should contain \u
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ============================================================
// Boundary and Edge Case Tests
// ============================================================

TEST_F(ValueTest_32, EmptyStringValue_32) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_32, ZeroIntegerValue_32) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_32, NegativeIntegerValue_32) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST_F(ValueTest_32, ZeroDoubleValue_32) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_32, NegativeDoubleValue_32) {
    Value v(-1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -1.5);
}

TEST_F(ValueTest_32, EmptyObjectValue_32) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_32, EmptyArrayValue_32) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_32, OverwriteTypeWithSetter_32) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setString("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST_F(ValueTest_32, OverwriteStringWithInteger_32) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    v.setInteger(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 10);
}

TEST_F(ValueTest_32, OverwriteWithNull_32) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_32, LoadFromStringEmptyObject_32) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_32, LoadFromStringEmptyArray_32) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_32, LoadFromStringNegativeNumber_32) {
    Value v;
    v.loadFromString("-42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST_F(ValueTest_32, LoadFromStringFalse_32) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_32, NestedObjectParsing_32) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": 42}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_TRUE(v["outer"]["inner"].isInteger());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

TEST_F(ValueTest_32, NestedArrayParsing_32) {
    Value v;
    v.loadFromString("[[1, 2], [3, 4]]");
    EXPECT_TRUE(v.isArray());
    const Array& arr = v.getArray();
    EXPECT_EQ(arr.size(), 2u);
    EXPECT_TRUE(arr[0].isArray());
    EXPECT_TRUE(arr[1].isArray());
}

TEST_F(ValueTest_32, RoundTripJsonSerialization_32) {
    Value original;
    original.loadFromString("{\"name\": \"test\", \"value\": 42, \"flag\": true}");

    std::ostringstream oss;
    original.writeToStream(oss, false, false);
    std::string jsonStr = oss.str();

    Value reparsed;
    reparsed.loadFromString(jsonStr);

    EXPECT_TRUE(reparsed.isObject());
    EXPECT_EQ(reparsed["name"].getString(), "test");
    EXPECT_EQ(reparsed["value"].getInteger(), 42);
    EXPECT_TRUE(reparsed["flag"].getBoolean());
}

TEST_F(ValueTest_32, LargeIntegerValue_32) {
    Value v(2147483647); // INT_MAX
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST_F(ValueTest_32, MinIntegerValue_32) {
    Value v(-2147483647 - 1); // INT_MIN
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -2147483647 - 1);
}

TEST_F(ValueTest_32, SelfAssignment_32) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_32, MultipleTypeChanges_32) {
    Value v;
    EXPECT_TRUE(v.isNull());
    
    v = 42;
    EXPECT_TRUE(v.isInteger());
    
    v = "string";
    EXPECT_TRUE(v.isString());
    
    v = 3.14;
    EXPECT_TRUE(v.isDouble());
    
    v = true;
    EXPECT_TRUE(v.isBoolean());
    
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_32, EscapeMinimumCharactersTab_32) {
    std::string result = Value::escapeMinimumCharacters("tab\there");
    EXPECT_NE(result.find("\\t"), std::string::npos);
}

TEST_F(ValueTest_32, LoadFromStringEscapedString_32) {
    Value v;
    v.loadFromString("\"hello\\nworld\"");
    EXPECT_TRUE(v.isString());
    EXPECT_NE(v.getString().find('\n'), std::string::npos);
}

TEST_F(ValueTest_32, WriteNullToStream_32) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("null"), std::string::npos);
}

TEST_F(ValueTest_32, WriteBooleanTrueToStream_32) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(ValueTest_32, WriteBooleanFalseToStream_32) {
    Value v(false);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("false"), std::string::npos);
}

TEST_F(ValueTest_32, WriteArrayToStream_32) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}
