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
class ValueTest_30 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Construction Tests
// ============================================================

TEST_F(ValueTest_30, DefaultConstructorCreatesNull_30) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_30, StringConstructor_30) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_30, CStringConstructor_30) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_30, IntConstructor_30) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_30, DoubleConstructor_30) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_30, BoolConstructorTrue_30) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_30, BoolConstructorFalse_30) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_30, ObjectConstructor_30) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_30, ArrayConstructor_30) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_30, CopyConstructor_30) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "test");
}

TEST_F(ValueTest_30, StreamConstructorValidJson_30) {
    std::istringstream iss("\"hello\"");
    Value v(iss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

// ============================================================
// Type Check Tests
// ============================================================

TEST_F(ValueTest_30, IsStringForString_30) {
    Value v("abc");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueTest_30, IsIntegerForInt_30) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_TRUE(v.isNumeric());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
}

TEST_F(ValueTest_30, IsDoubleForDouble_30) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_TRUE(v.isNumeric());
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_30, IsNumericForInt_30) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_30, IsNumericForDouble_30) {
    Value v(5.0);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_30, IsNotNumericForString_30) {
    Value v("123");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_30, IsStringableForString_30) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_30, IsStringableForInteger_30) {
    Value v(42);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_30, IsStringableForDouble_30) {
    Value v(3.14);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_30, IsStringableForBoolean_30) {
    Value v(true);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_30, IsStringableForNull_30) {
    Value v;
    EXPECT_TRUE(v.isStringable());
}

// ============================================================
// Assignment Operator Tests
// ============================================================

TEST_F(ValueTest_30, AssignmentFromValue_30) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_30, AssignmentFromString_30) {
    Value v;
    v = std::string("test");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

TEST_F(ValueTest_30, AssignmentFromCString_30) {
    Value v;
    v = "test";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

TEST_F(ValueTest_30, AssignmentFromInt_30) {
    Value v;
    v = 99;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_30, AssignmentFromDouble_30) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_30, AssignmentFromBool_30) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_30, AssignmentFromObject_30) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_30, AssignmentFromArray_30) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_30, AssignmentChangesType_30) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v = "now a string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

// ============================================================
// Getter / Setter Tests
// ============================================================

TEST_F(ValueTest_30, SetAndGetString_30) {
    Value v;
    v.setString("foobar");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "foobar");
}

TEST_F(ValueTest_30, SetAndGetInteger_30) {
    Value v;
    v.setInteger(123);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

TEST_F(ValueTest_30, SetAndGetDouble_30) {
    Value v;
    v.setDouble(9.81);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 9.81);
}

TEST_F(ValueTest_30, GetFloat_30) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 1.5f);
}

TEST_F(ValueTest_30, SetAndGetBoolean_30) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
    v.setBoolean(false);
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_30, SetAndGetObject_30) {
    Value v;
    Object obj;
    obj["x"] = Value(10);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_30, SetAndGetArray_30) {
    Value v;
    Array arr;
    arr.push_back(Value("elem"));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

TEST_F(ValueTest_30, SetNull_30) {
    Value v(42);
    EXPECT_FALSE(v.isNull());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

// ============================================================
// tryGet Tests
// ============================================================

TEST_F(ValueTest_30, TryGetStringReturnsValueWhenString_30) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST_F(ValueTest_30, TryGetStringReturnsDefaultWhenNotString_30) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_30, TryGetIntegerReturnsValueWhenInteger_30) {
    Value v(77);
    EXPECT_EQ(v.tryGetInteger(0), 77);
}

TEST_F(ValueTest_30, TryGetIntegerReturnsDefaultWhenNotInteger_30) {
    Value v("not an int");
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

TEST_F(ValueTest_30, TryGetDoubleReturnsValueWhenDouble_30) {
    Value v(2.5);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 2.5);
}

TEST_F(ValueTest_30, TryGetDoubleReturnsDefaultWhenNotDouble_30) {
    Value v("not a double");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(9.9), 9.9);
}

TEST_F(ValueTest_30, TryGetFloatReturnsValueWhenDouble_30) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST_F(ValueTest_30, TryGetFloatReturnsDefaultWhenNotDouble_30) {
    Value v("not a float");
    EXPECT_FLOAT_EQ(v.tryGetFloat(9.9f), 9.9f);
}

TEST_F(ValueTest_30, TryGetBooleanReturnsValueWhenBoolean_30) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_30, TryGetBooleanReturnsDefaultWhenNotBoolean_30) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ============================================================
// getToString Tests
// ============================================================

TEST_F(ValueTest_30, GetToStringForString_30) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

TEST_F(ValueTest_30, GetToStringForInteger_30) {
    Value v(42);
    std::string result = v.getToString();
    EXPECT_EQ(result, "42");
}

TEST_F(ValueTest_30, GetToStringForBoolean_30) {
    Value vt(true);
    Value vf(false);
    // Just verify it returns something without crashing
    EXPECT_FALSE(vt.getToString().empty());
    EXPECT_FALSE(vf.getToString().empty());
}

TEST_F(ValueTest_30, GetToStringForNull_30) {
    Value v;
    std::string result = v.getToString();
    // Null should produce some string representation
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Comparison Operator Tests
// ============================================================

TEST_F(ValueTest_30, EqualityOperator_30) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_30, InequalityOperator_30) {
    Value v1(42);
    Value v2(43);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_30, LessThanOperator_30) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_30, LessThanOrEqualOperator_30) {
    Value v1(1);
    Value v2(1);
    Value v3(2);
    EXPECT_TRUE(v1 <= v2);
    EXPECT_TRUE(v1 <= v3);
    EXPECT_FALSE(v3 <= v1);
}

TEST_F(ValueTest_30, GreaterThanOperator_30) {
    Value v1(2);
    Value v2(1);
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v2 > v1);
}

TEST_F(ValueTest_30, GreaterThanOrEqualOperator_30) {
    Value v1(2);
    Value v2(2);
    Value v3(1);
    EXPECT_TRUE(v1 >= v2);
    EXPECT_TRUE(v1 >= v3);
    EXPECT_FALSE(v3 >= v1);
}

TEST_F(ValueTest_30, EqualityDifferentTypes_30) {
    Value vi(1);
    Value vs("1");
    EXPECT_TRUE(vi != vs);
}

TEST_F(ValueTest_30, EqualityStringValues_30) {
    Value v1("abc");
    Value v2("abc");
    Value v3("def");
    EXPECT_TRUE(v1 == v2);
    EXPECT_TRUE(v1 != v3);
}

TEST_F(ValueTest_30, EqualityBoolValues_30) {
    Value v1(true);
    Value v2(true);
    Value v3(false);
    EXPECT_TRUE(v1 == v2);
    EXPECT_TRUE(v1 != v3);
}

TEST_F(ValueTest_30, EqualityNullValues_30) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

// ============================================================
// Subscript Operator Tests
// ============================================================

TEST_F(ValueTest_30, SubscriptStringKeyOnObject_30) {
    Object obj;
    obj["name"] = Value("John");
    Value v(obj);
    EXPECT_TRUE(v["name"].isString());
    EXPECT_EQ(v["name"].getString(), "John");
}

TEST_F(ValueTest_30, SubscriptCStringKeyOnObject_30) {
    Object obj;
    obj["key"] = Value(100);
    Value v(obj);
    EXPECT_TRUE(v["key"].isInteger());
    EXPECT_EQ(v["key"].getInteger(), 100);
}

TEST_F(ValueTest_30, SubscriptIndexOnArray_30) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

TEST_F(ValueTest_30, SubscriptStringKeyCreatesObjectIfNull_30) {
    Value v;
    v["newKey"] = 42;
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["newKey"].getInteger(), 42);
}

TEST_F(ValueTest_30, SubscriptCStringKeyCreatesObjectIfNull_30) {
    Value v;
    const char* key = "myKey";
    v[key] = "value";
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v[key].getString(), "value");
}

// ============================================================
// Load / Parse Tests
// ============================================================

TEST_F(ValueTest_30, LoadFromStringInteger_30) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_30, LoadFromStringDouble_30) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_30, LoadFromStringString_30) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_30, LoadFromStringBoolTrue_30) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_30, LoadFromStringBoolFalse_30) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_30, LoadFromStringNull_30) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_30, LoadFromStringObject_30) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST_F(ValueTest_30, LoadFromStringArray_30) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_30, LoadFromStream_30) {
    std::istringstream iss("{\"a\": 1}");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["a"].getInteger(), 1);
}

TEST_F(ValueTest_30, LoadFromStringNestedObject_30) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": 42}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

TEST_F(ValueTest_30, LoadFromStringNestedArray_30) {
    Value v;
    v.loadFromString("[[1, 2], [3, 4]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
    EXPECT_TRUE(v[(size_t)0].isArray());
}

TEST_F(ValueTest_30, LoadFromStringNegativeInt_30) {
    Value v;
    v.loadFromString("-5");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -5);
}

TEST_F(ValueTest_30, LoadFromStringNegativeDouble_30) {
    Value v;
    v.loadFromString("-3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -3.14);
}

// ============================================================
// Write / Serialize Tests
// ============================================================

TEST_F(ValueTest_30, WriteToStreamInteger_30) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_FALSE(oss.str().empty());
    EXPECT_NE(oss.str().find("42"), std::string::npos);
}

TEST_F(ValueTest_30, WriteToStreamString_30) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("hello"), std::string::npos);
}

TEST_F(ValueTest_30, WriteToStreamNull_30) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("null"), std::string::npos);
}

TEST_F(ValueTest_30, WriteToStreamBoolTrue_30) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("true"), std::string::npos);
}

TEST_F(ValueTest_30, WriteToStreamBoolFalse_30) {
    Value v(false);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("false"), std::string::npos);
}

TEST_F(ValueTest_30, WriteToStreamObject_30) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("key"), std::string::npos);
    EXPECT_NE(output.find("value"), std::string::npos);
}

TEST_F(ValueTest_30, WriteToStreamArray_30) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
}

TEST_F(ValueTest_30, WriteToStreamIndented_30) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    // Indented output should contain newlines or tabs
    EXPECT_NE(output.find("\n"), std::string::npos);
}

TEST_F(ValueTest_30, StreamOperator_30) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

// ============================================================
// Escape Tests
// ============================================================

TEST_F(ValueTest_30, EscapeMinimumCharacters_30) {
    std::string input = "hello\nworld";
    std::string escaped = Value::escapeMinimumCharacters(input);
    EXPECT_NE(escaped.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_30, EscapeMinimumCharactersQuote_30) {
    std::string input = "say \"hi\"";
    std::string escaped = Value::escapeMinimumCharacters(input);
    EXPECT_NE(escaped.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_30, EscapeMinimumCharactersBackslash_30) {
    std::string input = "back\\slash";
    std::string escaped = Value::escapeMinimumCharacters(input);
    EXPECT_NE(escaped.find("\\\\"), std::string::npos);
}

TEST_F(ValueTest_30, EscapeMinimumCharactersNoEscapeNeeded_30) {
    std::string input = "simple";
    std::string escaped = Value::escapeMinimumCharacters(input);
    EXPECT_EQ(escaped, "simple");
}

TEST_F(ValueTest_30, EscapeAllCharacters_30) {
    std::string input = "hello\nworld";
    std::string escaped = Value::escapeAllCharacters(input);
    EXPECT_NE(escaped.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_30, EscapeToUnicode_30) {
    std::string result = Value::escapeToUnicode('A');
    // Should produce a unicode escape like \u0041
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ============================================================
// Boundary / Edge Case Tests
// ============================================================

TEST_F(ValueTest_30, EmptyStringValue_30) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_30, ZeroIntValue_30) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_30, ZeroDoubleValue_30) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_30, EmptyObject_30) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_30, EmptyArray_30) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_30, NegativeIntValue_30) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST_F(ValueTest_30, LargeIntValue_30) {
    Value v(2147483647);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST_F(ValueTest_30, EmptyJsonObject_30) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_30, EmptyJsonArray_30) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_30, LoadFromStringWithWhitespace_30) {
    Value v;
    v.loadFromString("  \n\t  42  \n\t  ");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_30, OverwriteValueType_30) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setString("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST_F(ValueTest_30, OverwriteStringWithNull_30) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_30, MultipleSubscriptAccesses_30) {
    Value v;
    v.loadFromString("{\"a\": {\"b\": {\"c\": 123}}}");
    EXPECT_EQ(v["a"]["b"]["c"].getInteger(), 123);
}

// ============================================================
// Roundtrip Tests
// ============================================================

TEST_F(ValueTest_30, RoundtripIntegerThroughStream_30) {
    Value original(42);
    std::ostringstream oss;
    original.writeToStream(oss, false, false);
    
    Value parsed;
    parsed.loadFromString(oss.str());
    EXPECT_TRUE(parsed.isInteger());
    EXPECT_EQ(parsed.getInteger(), 42);
}

TEST_F(ValueTest_30, RoundtripStringThroughStream_30) {
    Value original("test string");
    std::ostringstream oss;
    original.writeToStream(oss, false, false);
    
    Value parsed;
    parsed.loadFromString(oss.str());
    EXPECT_TRUE(parsed.isString());
    EXPECT_EQ(parsed.getString(), "test string");
}

TEST_F(ValueTest_30, RoundtripObjectThroughStream_30) {
    Object obj;
    obj["x"] = Value(1);
    obj["y"] = Value("two");
    Value original(obj);
    
    std::ostringstream oss;
    original.writeToStream(oss, false, false);
    
    Value parsed;
    parsed.loadFromString(oss.str());
    EXPECT_TRUE(parsed.isObject());
    EXPECT_EQ(parsed["x"].getInteger(), 1);
    EXPECT_EQ(parsed["y"].getString(), "two");
}

TEST_F(ValueTest_30, RoundtripArrayThroughStream_30) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value("two"));
    arr.push_back(Value(true));
    Value original(arr);
    
    std::ostringstream oss;
    original.writeToStream(oss, false, false);
    
    Value parsed;
    parsed.loadFromString(oss.str());
    EXPECT_TRUE(parsed.isArray());
    EXPECT_EQ(parsed.getArray().size(), 3u);
}

TEST_F(ValueTest_30, RoundtripBoolThroughStream_30) {
    Value original(true);
    std::ostringstream oss;
    original.writeToStream(oss, false, false);
    
    Value parsed;
    parsed.loadFromString(oss.str());
    EXPECT_TRUE(parsed.isBoolean());
    EXPECT_TRUE(parsed.getBoolean());
}

TEST_F(ValueTest_30, RoundtripNullThroughStream_30) {
    Value original;
    std::ostringstream oss;
    original.writeToStream(oss, false, false);
    
    Value parsed;
    parsed.loadFromString(oss.str());
    EXPECT_TRUE(parsed.isNull());
}

// ============================================================
// Complex JSON Parsing Tests
// ============================================================

TEST_F(ValueTest_30, ParseComplexJson_30) {
    std::string json = R"({
        "name": "test",
        "value": 42,
        "pi": 3.14,
        "active": true,
        "nothing": null,
        "tags": ["a", "b", "c"],
        "nested": {"x": 1}
    })";
    
    Value v;
    v.loadFromString(json);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["name"].getString(), "test");
    EXPECT_EQ(v["value"].getInteger(), 42);
    EXPECT_DOUBLE_EQ(v["pi"].getDouble(), 3.14);
    EXPECT_TRUE(v["active"].getBoolean());
    EXPECT_TRUE(v["nothing"].isNull());
    EXPECT_TRUE(v["tags"].isArray());
    EXPECT_EQ(v["tags"].getArray().size(), 3u);
    EXPECT_TRUE(v["nested"].isObject());
    EXPECT_EQ(v["nested"]["x"].getInteger(), 1);
}

TEST_F(ValueTest_30, ParseStringWithEscapeSequences_30) {
    Value v;
    v.loadFromString("\"hello\\nworld\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello\nworld");
}

TEST_F(ValueTest_30, ParseStringWithUnicodeEscape_30) {
    Value v;
    v.loadFromString("\"\\u0041\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "A");
}

TEST_F(ValueTest_30, WriteToStreamEscapeAllMode_30) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, true);
    // In escapeAll mode, characters should be unicode-escaped
    EXPECT_FALSE(oss.str().empty());
}
