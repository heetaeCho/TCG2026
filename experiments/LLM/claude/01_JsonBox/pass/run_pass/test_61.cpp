#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "JsonBox/Value.h"

using namespace JsonBox;

// ===== Construction Tests =====

TEST(ValueTest_61, DefaultConstructor_IsNull_61) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST(ValueTest_61, StringConstructor_61) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
    EXPECT_EQ(v.getType(), Value::STRING);
}

TEST(ValueTest_61, CStringConstructor_61) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST(ValueTest_61, IntConstructor_61) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
    EXPECT_EQ(v.getType(), Value::INTEGER);
}

TEST(ValueTest_61, DoubleConstructor_61) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
    EXPECT_EQ(v.getType(), Value::DOUBLE);
}

TEST(ValueTest_61, BooleanConstructorTrue_61) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
    EXPECT_EQ(v.getType(), Value::BOOLEAN);
}

TEST(ValueTest_61, BooleanConstructorFalse_61) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueTest_61, ObjectConstructor_61) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getType(), Value::OBJECT);
}

TEST(ValueTest_61, ArrayConstructor_61) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getType(), Value::ARRAY);
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST(ValueTest_61, CopyConstructor_61) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "test");
}

TEST(ValueTest_61, CopyConstructorNull_61) {
    Value original;
    Value copy(original);
    EXPECT_TRUE(copy.isNull());
}

TEST(ValueTest_61, CopyConstructorInt_61) {
    Value original(100);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 100);
}

TEST(ValueTest_61, CopyConstructorDouble_61) {
    Value original(2.718);
    Value copy(original);
    EXPECT_TRUE(copy.isDouble());
    EXPECT_DOUBLE_EQ(copy.getDouble(), 2.718);
}

TEST(ValueTest_61, CopyConstructorBoolean_61) {
    Value original(true);
    Value copy(original);
    EXPECT_TRUE(copy.isBoolean());
    EXPECT_TRUE(copy.getBoolean());
}

// ===== Assignment Operator Tests =====

TEST(ValueTest_61, AssignmentFromValue_61) {
    Value v1("hello");
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isString());
    EXPECT_EQ(v2.getString(), "hello");
}

TEST(ValueTest_61, AssignmentFromString_61) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST(ValueTest_61, AssignmentFromCString_61) {
    Value v;
    v = "cstring";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "cstring");
}

TEST(ValueTest_61, AssignmentFromInt_61) {
    Value v;
    v = 99;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST(ValueTest_61, AssignmentFromDouble_61) {
    Value v;
    v = 1.5;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.5);
}

TEST(ValueTest_61, AssignmentFromObject_61) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST(ValueTest_61, AssignmentFromArray_61) {
    Value v;
    Array arr;
    arr.push_back(Value("x"));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

TEST(ValueTest_61, AssignmentFromBool_61) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_61, AssignmentChangesType_61) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v = std::string("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

// ===== Setter Tests =====

TEST(ValueTest_61, SetString_61) {
    Value v;
    v.setString("test");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

TEST(ValueTest_61, SetInteger_61) {
    Value v;
    v.setInteger(77);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 77);
}

TEST(ValueTest_61, SetDouble_61) {
    Value v;
    v.setDouble(6.28);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 6.28);
}

TEST(ValueTest_61, SetBoolean_61) {
    Value v;
    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueTest_61, SetNull_61) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setNull();
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST(ValueTest_61, SetObject_61) {
    Value v;
    Object obj;
    obj["key"] = Value("val");
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST(ValueTest_61, SetArray_61) {
    Value v;
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

// ===== Type Check Tests =====

TEST(ValueTest_61, IsStringable_ForString_61) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST(ValueTest_61, IsStringable_ForInt_61) {
    Value v(42);
    EXPECT_TRUE(v.isStringable());
}

TEST(ValueTest_61, IsStringable_ForDouble_61) {
    Value v(3.14);
    EXPECT_TRUE(v.isStringable());
}

TEST(ValueTest_61, IsNumeric_ForInt_61) {
    Value v(42);
    EXPECT_TRUE(v.isNumeric());
}

TEST(ValueTest_61, IsNumeric_ForDouble_61) {
    Value v(3.14);
    EXPECT_TRUE(v.isNumeric());
}

TEST(ValueTest_61, IsNumeric_ForString_61) {
    Value v("hello");
    EXPECT_FALSE(v.isNumeric());
}

TEST(ValueTest_61, IsNull_ForDefault_61) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_61, IsString_ForNonString_61) {
    Value v(42);
    EXPECT_FALSE(v.isString());
}

TEST(ValueTest_61, IsInteger_ForNonInt_61) {
    Value v("hello");
    EXPECT_FALSE(v.isInteger());
}

TEST(ValueTest_61, IsDouble_ForNonDouble_61) {
    Value v(42);
    EXPECT_FALSE(v.isDouble());
}

TEST(ValueTest_61, IsObject_ForNonObject_61) {
    Value v(42);
    EXPECT_FALSE(v.isObject());
}

TEST(ValueTest_61, IsArray_ForNonArray_61) {
    Value v(42);
    EXPECT_FALSE(v.isArray());
}

TEST(ValueTest_61, IsBoolean_ForNonBoolean_61) {
    Value v(42);
    EXPECT_FALSE(v.isBoolean());
}

TEST(ValueTest_61, IsNull_ForNonNull_61) {
    Value v(42);
    EXPECT_FALSE(v.isNull());
}

// ===== TryGet Tests =====

TEST(ValueTest_61, TryGetString_WhenString_61) {
    Value v("hello");
    EXPECT_EQ(v.tryGetString("default"), "hello");
}

TEST(ValueTest_61, TryGetString_WhenNotString_61) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST(ValueTest_61, TryGetInteger_WhenInteger_61) {
    Value v(42);
    EXPECT_EQ(v.tryGetInteger(0), 42);
}

TEST(ValueTest_61, TryGetInteger_WhenNotInteger_61) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

TEST(ValueTest_61, TryGetDouble_WhenDouble_61) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 3.14);
}

TEST(ValueTest_61, TryGetDouble_WhenNotDouble_61) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(9.99), 9.99);
}

TEST(ValueTest_61, TryGetFloat_WhenDouble_61) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST(ValueTest_61, TryGetFloat_WhenNotDouble_61) {
    Value v("hello");
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.0f), 1.0f);
}

TEST(ValueTest_61, TryGetBoolean_WhenBoolean_61) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST(ValueTest_61, TryGetBoolean_WhenNotBoolean_61) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ===== GetToString Tests =====

TEST(ValueTest_61, GetToString_FromString_61) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

TEST(ValueTest_61, GetToString_FromInt_61) {
    Value v(42);
    std::string result = v.getToString();
    EXPECT_EQ(result, "42");
}

TEST(ValueTest_61, GetToString_FromDouble_61) {
    Value v(3.5);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

// ===== GetFloat Tests =====

TEST(ValueTest_61, GetFloat_61) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 2.5f);
}

// ===== Comparison Operators =====

TEST(ValueTest_61, EqualityOperator_SameValue_61) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueTest_61, EqualityOperator_DifferentValue_61) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
}

TEST(ValueTest_61, InequalityOperator_61) {
    Value v1(42);
    Value v2(43);
    EXPECT_TRUE(v1 != v2);
}

TEST(ValueTest_61, LessThanOperator_61) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
}

TEST(ValueTest_61, LessThanOrEqualOperator_61) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST(ValueTest_61, GreaterThanOperator_61) {
    Value v1(2);
    Value v2(1);
    EXPECT_TRUE(v1 > v2);
}

TEST(ValueTest_61, GreaterThanOrEqualOperator_61) {
    Value v1(2);
    Value v2(2);
    EXPECT_TRUE(v1 >= v2);
}

TEST(ValueTest_61, EqualityNullValues_61) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueTest_61, EqualityDifferentTypes_61) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

TEST(ValueTest_61, EqualityStrings_61) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueTest_61, EqualityBooleans_61) {
    Value v1(true);
    Value v2(true);
    EXPECT_TRUE(v1 == v2);
}

// ===== Subscript Operators =====

TEST(ValueTest_61, SubscriptOperator_StringKey_61) {
    Value v;
    Object obj;
    obj["name"] = Value("test");
    v.setObject(obj);
    Value& ref = v["name"];
    EXPECT_TRUE(ref.isString());
    EXPECT_EQ(ref.getString(), "test");
}

TEST(ValueTest_61, SubscriptOperator_CStringKey_61) {
    Value v;
    Object obj;
    obj["key"] = Value(123);
    v.setObject(obj);
    Value& ref = v["key"];
    EXPECT_TRUE(ref.isInteger());
    EXPECT_EQ(ref.getInteger(), 123);
}

TEST(ValueTest_61, SubscriptOperator_Index_61) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

TEST(ValueTest_61, SubscriptOperator_CreatesNewKeyInObject_61) {
    Value v;
    Object obj;
    v.setObject(obj);
    v["newkey"] = Value(42);
    EXPECT_EQ(v["newkey"].getInteger(), 42);
}

// ===== Load and Write Tests =====

TEST(ValueTest_61, LoadFromString_SimpleObject_61) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST(ValueTest_61, LoadFromString_SimpleArray_61) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST(ValueTest_61, LoadFromString_Integer_61) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueTest_61, LoadFromString_Double_61) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST(ValueTest_61, LoadFromString_StringValue_61) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueTest_61, LoadFromString_Boolean_61) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_61, LoadFromString_Null_61) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_61, LoadFromStream_61) {
    std::istringstream iss("{\"a\": 1}");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["a"].getInteger(), 1);
}

TEST(ValueTest_61, StreamConstructor_61) {
    std::istringstream iss("{\"b\": 2}");
    Value v(iss);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["b"].getInteger(), 2);
}

TEST(ValueTest_61, WriteToStream_NoIndent_61) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("key"), std::string::npos);
    EXPECT_NE(output.find("value"), std::string::npos);
}

TEST(ValueTest_61, WriteToStream_WithIndent_61) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST(ValueTest_61, WriteToStream_EscapeAll_61) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    std::ostringstream oss;
    v.writeToStream(oss, false, true);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST(ValueTest_61, OutputOperator_61) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

// ===== SetNull After Various Types =====

TEST(ValueTest_61, SetNull_AfterString_61) {
    Value v("hello");
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_61, SetNull_AfterDouble_61) {
    Value v(3.14);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_61, SetNull_AfterBoolean_61) {
    Value v(true);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_61, SetNull_AfterObject_61) {
    Object obj;
    obj["k"] = Value(1);
    Value v(obj);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_61, SetNull_AfterArray_61) {
    Array arr;
    arr.push_back(Value(1));
    Value v(arr);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_61, SetNull_OnAlreadyNull_61) {
    Value v;
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

// ===== Escape Functions =====

TEST(ValueTest_61, EscapeMinimumCharacters_NoEscapeNeeded_61) {
    std::string result = Value::escapeMinimumCharacters("hello");
    EXPECT_EQ(result, "hello");
}

TEST(ValueTest_61, EscapeMinimumCharacters_WithQuotes_61) {
    std::string result = Value::escapeMinimumCharacters("he\"llo");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST(ValueTest_61, EscapeMinimumCharacters_WithBackslash_61) {
    std::string result = Value::escapeMinimumCharacters("he\\llo");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST(ValueTest_61, EscapeMinimumCharacters_WithNewline_61) {
    std::string result = Value::escapeMinimumCharacters("he\nllo");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST(ValueTest_61, EscapeAllCharacters_NoEscapeNeeded_61) {
    std::string result = Value::escapeAllCharacters("hello");
    // All characters should be escaped to unicode
    EXPECT_FALSE(result.empty());
}

TEST(ValueTest_61, EscapeToUnicode_61) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
    // Should produce a unicode escape sequence like \u0041
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

TEST(ValueTest_61, EscapeMinimumCharacters_EmptyString_61) {
    std::string result = Value::escapeMinimumCharacters("");
    EXPECT_EQ(result, "");
}

// ===== Boundary and Edge Cases =====

TEST(ValueTest_61, IntegerBoundary_Zero_61) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST(ValueTest_61, IntegerBoundary_Negative_61) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST(ValueTest_61, DoubleBoundary_Zero_61) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST(ValueTest_61, DoubleBoundary_Negative_61) {
    Value v(-99.99);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -99.99);
}

TEST(ValueTest_61, EmptyStringValue_61) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST(ValueTest_61, EmptyObject_61) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST(ValueTest_61, EmptyArray_61) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

// ===== Complex JSON =====

TEST(ValueTest_61, LoadFromString_NestedObject_61) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": 42}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

TEST(ValueTest_61, LoadFromString_NestedArray_61) {
    Value v;
    v.loadFromString("[[1, 2], [3, 4]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST(ValueTest_61, LoadFromString_MixedTypes_61) {
    Value v;
    v.loadFromString("{\"str\": \"hello\", \"num\": 42, \"bool\": true, \"null\": null, \"arr\": [1,2]}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["str"].isString());
    EXPECT_TRUE(v["num"].isInteger());
    EXPECT_TRUE(v["bool"].isBoolean());
    EXPECT_TRUE(v["null"].isNull());
    EXPECT_TRUE(v["arr"].isArray());
}

TEST(ValueTest_61, LoadFromString_NegativeNumber_61) {
    Value v;
    v.loadFromString("-42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST(ValueTest_61, LoadFromString_FalseBoolean_61) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

// ===== Reassignment / Type Change =====

TEST(ValueTest_61, ReassignIntToString_61) {
    Value v(42);
    v.setString("now string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now string");
    EXPECT_FALSE(v.isInteger());
}

TEST(ValueTest_61, ReassignStringToObject_61) {
    Value v("hello");
    Object obj;
    obj["k"] = Value(1);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_FALSE(v.isString());
}

TEST(ValueTest_61, ReassignObjectToArray_61) {
    Object obj;
    obj["k"] = Value(1);
    Value v(obj);
    Array arr;
    arr.push_back(Value(10));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_FALSE(v.isObject());
}

// ===== Round-trip (write then read) =====

TEST(ValueTest_61, RoundTrip_Object_61) {
    Value original;
    original.loadFromString("{\"key\": \"value\", \"num\": 42}");

    std::ostringstream oss;
    original.writeToStream(oss, false, false);

    Value parsed;
    parsed.loadFromString(oss.str());

    EXPECT_TRUE(parsed.isObject());
    EXPECT_EQ(parsed["key"].getString(), "value");
    EXPECT_EQ(parsed["num"].getInteger(), 42);
}

TEST(ValueTest_61, RoundTrip_Array_61) {
    Value original;
    original.loadFromString("[1, 2, 3]");

    std::ostringstream oss;
    original.writeToStream(oss, false, false);

    Value parsed;
    parsed.loadFromString(oss.str());

    EXPECT_TRUE(parsed.isArray());
    EXPECT_EQ(parsed.getArray().size(), 3u);
}

// ===== Self-assignment =====

TEST(ValueTest_61, SelfAssignment_61) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

// ===== Large Values =====

TEST(ValueTest_61, LargeArray_61) {
    Array arr;
    for (int i = 0; i < 1000; ++i) {
        arr.push_back(Value(i));
    }
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1000u);
}

TEST(ValueTest_61, LargeString_61) {
    std::string largeStr(10000, 'a');
    Value v(largeStr);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString().size(), 10000u);
}
