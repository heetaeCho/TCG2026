#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

// ============================================================
// Construction Tests
// ============================================================

TEST(ValueConstructionTest_26, DefaultConstructorCreatesNull_26) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

TEST(ValueConstructionTest_26, StringConstructor_26) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueConstructionTest_26, CStringConstructor_26) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST(ValueConstructionTest_26, IntConstructor_26) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueConstructionTest_26, DoubleConstructor_26) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST(ValueConstructionTest_26, BooleanConstructorTrue_26) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueConstructionTest_26, BooleanConstructorFalse_26) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueConstructionTest_26, ObjectConstructor_26) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST(ValueConstructionTest_26, ArrayConstructor_26) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST(ValueConstructionTest_26, CopyConstructor_26) {
    Value original(123);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 123);
}

TEST(ValueConstructionTest_26, StreamConstructor_26) {
    std::istringstream iss("\"test\"");
    Value v(iss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

// ============================================================
// Type Checking Tests
// ============================================================

TEST(ValueTypeTest_26, IsStringable_26) {
    Value vs("hello");
    EXPECT_TRUE(vs.isStringable());

    Value vi(42);
    EXPECT_TRUE(vi.isStringable());

    Value vd(3.14);
    EXPECT_TRUE(vd.isStringable());

    Value vb(true);
    // Boolean may or may not be stringable depending on implementation
    // but numeric types should be
}

TEST(ValueTypeTest_26, IsNumeric_26) {
    Value vi(42);
    EXPECT_TRUE(vi.isNumeric());
    EXPECT_TRUE(vi.isInteger());
    EXPECT_FALSE(vi.isDouble());

    Value vd(3.14);
    EXPECT_TRUE(vd.isNumeric());
    EXPECT_TRUE(vd.isDouble());
    EXPECT_FALSE(vd.isInteger());
}

TEST(ValueTypeTest_26, NullIsNotOtherTypes_26) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isNumeric());
}

// ============================================================
// Assignment Operator Tests
// ============================================================

TEST(ValueAssignmentTest_26, AssignValue_26) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST(ValueAssignmentTest_26, AssignString_26) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST(ValueAssignmentTest_26, AssignCString_26) {
    Value v;
    v = "cstring";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "cstring");
}

TEST(ValueAssignmentTest_26, AssignInt_26) {
    Value v;
    v = 99;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST(ValueAssignmentTest_26, AssignDouble_26) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST(ValueAssignmentTest_26, AssignObject_26) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST(ValueAssignmentTest_26, AssignArray_26) {
    Value v;
    Array arr;
    arr.push_back(Value("elem"));
    v = arr;
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

TEST(ValueAssignmentTest_26, AssignBool_26) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueAssignmentTest_26, ReassignChangesType_26) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v = "now a string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

// ============================================================
// Setter/Getter Tests
// ============================================================

TEST(ValueSetterGetterTest_26, SetAndGetString_26) {
    Value v;
    v.setString("test");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

TEST(ValueSetterGetterTest_26, SetAndGetInteger_26) {
    Value v;
    v.setInteger(100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST(ValueSetterGetterTest_26, SetAndGetDouble_26) {
    Value v;
    v.setDouble(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.5);
}

TEST(ValueSetterGetterTest_26, SetAndGetBoolean_26) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueSetterGetterTest_26, SetNull_26) {
    Value v(42);
    EXPECT_FALSE(v.isNull());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST(ValueSetterGetterTest_26, SetAndGetObject_26) {
    Value v;
    Object obj;
    obj["x"] = Value(10);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().at("x").getInteger(), 10);
}

TEST(ValueSetterGetterTest_26, SetAndGetArray_26) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    arr.push_back(Value(3));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST(ValueSetterGetterTest_26, GetFloat_26) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 2.5f);
}

TEST(ValueSetterGetterTest_26, GetToString_26) {
    Value v(42);
    std::string s = v.getToString();
    EXPECT_EQ(s, "42");
}

// ============================================================
// TryGet Tests (with defaults)
// ============================================================

TEST(ValueTryGetTest_26, TryGetStringWhenString_26) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST(ValueTryGetTest_26, TryGetStringWhenNotString_26) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST(ValueTryGetTest_26, TryGetIntegerWhenInteger_26) {
    Value v(99);
    EXPECT_EQ(v.tryGetInteger(0), 99);
}

TEST(ValueTryGetTest_26, TryGetIntegerWhenNotInteger_26) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

TEST(ValueTryGetTest_26, TryGetDoubleWhenDouble_26) {
    Value v(1.23);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 1.23);
}

TEST(ValueTryGetTest_26, TryGetDoubleWhenNotDouble_26) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(5.5), 5.5);
}

TEST(ValueTryGetTest_26, TryGetFloatWhenDouble_26) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 1.5f);
}

TEST(ValueTryGetTest_26, TryGetFloatWhenNotDouble_26) {
    Value v("hello");
    EXPECT_FLOAT_EQ(v.tryGetFloat(9.9f), 9.9f);
}

TEST(ValueTryGetTest_26, TryGetBooleanWhenBoolean_26) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST(ValueTryGetTest_26, TryGetBooleanWhenNotBoolean_26) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ============================================================
// Comparison Operator Tests
// ============================================================

TEST(ValueComparisonTest_26, EqualityIntegers_26) {
    Value v1(10);
    Value v2(10);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST(ValueComparisonTest_26, InequalityIntegers_26) {
    Value v1(10);
    Value v2(20);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST(ValueComparisonTest_26, LessThanIntegers_26) {
    Value v1(5);
    Value v2(10);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST(ValueComparisonTest_26, LessThanOrEqualIntegers_26) {
    Value v1(5);
    Value v2(10);
    Value v3(5);
    EXPECT_TRUE(v1 <= v2);
    EXPECT_TRUE(v1 <= v3);
    EXPECT_FALSE(v2 <= v1);
}

TEST(ValueComparisonTest_26, GreaterThanIntegers_26) {
    Value v1(10);
    Value v2(5);
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v2 > v1);
}

TEST(ValueComparisonTest_26, GreaterThanOrEqualIntegers_26) {
    Value v1(10);
    Value v2(5);
    Value v3(10);
    EXPECT_TRUE(v1 >= v2);
    EXPECT_TRUE(v1 >= v3);
    EXPECT_FALSE(v2 >= v1);
}

TEST(ValueComparisonTest_26, EqualityStrings_26) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueComparisonTest_26, InequalityDifferentTypes_26) {
    Value v1(42);
    Value v2("42");
    EXPECT_TRUE(v1 != v2);
}

TEST(ValueComparisonTest_26, EqualityBooleans_26) {
    Value v1(true);
    Value v2(true);
    Value v3(false);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}

TEST(ValueComparisonTest_26, EqualityNulls_26) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueComparisonTest_26, LessThanOrEqualSameValue_26) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 <= v2);
    EXPECT_TRUE(v2 <= v1);
}

TEST(ValueComparisonTest_26, GreaterThanOrEqualSameValue_26) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 >= v2);
    EXPECT_TRUE(v2 >= v1);
}

// ============================================================
// Subscript Operator Tests
// ============================================================

TEST(ValueSubscriptTest_26, ObjectSubscriptStringKey_26) {
    Value v;
    Object obj;
    obj["key"] = Value(42);
    v.setObject(obj);
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST(ValueSubscriptTest_26, ObjectSubscriptCStringKey_26) {
    Value v;
    Object obj;
    obj["name"] = Value("John");
    v.setObject(obj);
    EXPECT_EQ(v["name"].getString(), "John");
}

TEST(ValueSubscriptTest_26, ArraySubscriptIndex_26) {
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

// ============================================================
// Load and Write Tests
// ============================================================

TEST(ValueLoadTest_26, LoadFromString_26) {
    Value v;
    v.loadFromString("{\"key\": 42}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST(ValueLoadTest_26, LoadFromStringArray_26) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST(ValueLoadTest_26, LoadFromStringString_26) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueLoadTest_26, LoadFromStringNumber_26) {
    Value v;
    v.loadFromString("123");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

TEST(ValueLoadTest_26, LoadFromStringBoolean_26) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueLoadTest_26, LoadFromStringNull_26) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST(ValueLoadTest_26, LoadFromStream_26) {
    std::istringstream iss("[1, \"two\", true]");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST(ValueWriteTest_26, WriteToStream_26) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST(ValueWriteTest_26, WriteObjectToStream_26) {
    Value v;
    Object obj;
    obj["key"] = Value("value");
    v.setObject(obj);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("key"), std::string::npos);
    EXPECT_NE(output.find("value"), std::string::npos);
}

TEST(ValueWriteTest_26, WriteWithIndent_26) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v.setObject(obj);
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    // Indented output should have newlines or spaces
    EXPECT_NE(output.find("\n"), std::string::npos);
}

// ============================================================
// Escape Functions Tests
// ============================================================

TEST(ValueEscapeTest_26, EscapeMinimumCharacters_26) {
    std::string result = Value::escapeMinimumCharacters("hello\nworld");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST(ValueEscapeTest_26, EscapeMinimumCharactersQuote_26) {
    std::string result = Value::escapeMinimumCharacters("he said \"hi\"");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST(ValueEscapeTest_26, EscapeMinimumCharactersBackslash_26) {
    std::string result = Value::escapeMinimumCharacters("path\\to\\file");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST(ValueEscapeTest_26, EscapeAllCharacters_26) {
    std::string result = Value::escapeAllCharacters("hello\tworld");
    EXPECT_NE(result.find("\\t"), std::string::npos);
}

TEST(ValueEscapeTest_26, EscapeToUnicode_26) {
    std::string result = Value::escapeToUnicode('A');
    // Should produce something like \u0041
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

TEST(ValueEscapeTest_26, EscapeMinimumNoSpecialChars_26) {
    std::string input = "simple";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ(result, "simple");
}

// ============================================================
// Boundary / Edge Cases
// ============================================================

TEST(ValueBoundaryTest_26, EmptyString_26) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST(ValueBoundaryTest_26, ZeroInteger_26) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST(ValueBoundaryTest_26, NegativeInteger_26) {
    Value v(-42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST(ValueBoundaryTest_26, ZeroDouble_26) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST(ValueBoundaryTest_26, NegativeDouble_26) {
    Value v(-3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -3.14);
}

TEST(ValueBoundaryTest_26, EmptyObject_26) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST(ValueBoundaryTest_26, EmptyArray_26) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST(ValueBoundaryTest_26, LargeInteger_26) {
    Value v(2147483647); // INT_MAX
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST(ValueBoundaryTest_26, SmallInteger_26) {
    Value v(-2147483647);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -2147483647);
}

// ============================================================
// Stream Operator Test
// ============================================================

TEST(ValueStreamTest_26, OutputOperator_26) {
    Value v("test");
    std::ostringstream oss;
    oss << v;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("test"), std::string::npos);
}

// ============================================================
// Complex JSON Tests
// ============================================================

TEST(ValueComplexTest_26, NestedObject_26) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": 42}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

TEST(ValueComplexTest_26, NestedArray_26) {
    Value v;
    v.loadFromString("[[1, 2], [3, 4]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
    EXPECT_TRUE(v[(size_t)0].isArray());
    EXPECT_EQ(v[(size_t)0][(size_t)0].getInteger(), 1);
}

TEST(ValueComplexTest_26, MixedObject_26) {
    Value v;
    v.loadFromString("{\"str\": \"hello\", \"num\": 42, \"bool\": true, \"null\": null, \"arr\": [1,2]}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["str"].isString());
    EXPECT_TRUE(v["num"].isInteger());
    EXPECT_TRUE(v["bool"].isBoolean());
    EXPECT_TRUE(v["null"].isNull());
    EXPECT_TRUE(v["arr"].isArray());
}

TEST(ValueComplexTest_26, DoubleFromJson_26) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_NEAR(v.getDouble(), 3.14, 0.001);
}

TEST(ValueComplexTest_26, NegativeNumberFromJson_26) {
    Value v;
    v.loadFromString("-99");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -99);
}

// ============================================================
// Self-assignment / Type Change Tests
// ============================================================

TEST(ValueTypeChangeTest_26, IntToString_26) {
    Value v(42);
    v.setString("now string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now string");
}

TEST(ValueTypeChangeTest_26, StringToNull_26) {
    Value v("something");
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTypeChangeTest_26, BoolToDouble_26) {
    Value v(true);
    v.setDouble(9.99);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 9.99);
}

// ============================================================
// Roundtrip Test
// ============================================================

TEST(ValueRoundtripTest_26, WriteAndReadBack_26) {
    Value original;
    Object obj;
    obj["name"] = Value("test");
    obj["value"] = Value(42);
    obj["flag"] = Value(true);
    original.setObject(obj);

    std::ostringstream oss;
    original.writeToStream(oss, false, false);
    std::string json = oss.str();

    Value parsed;
    parsed.loadFromString(json);
    EXPECT_TRUE(parsed.isObject());
    EXPECT_EQ(parsed["name"].getString(), "test");
    EXPECT_EQ(parsed["value"].getInteger(), 42);
    EXPECT_TRUE(parsed["flag"].getBoolean());
}
