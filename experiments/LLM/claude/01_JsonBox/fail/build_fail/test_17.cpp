#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

// ============================================================================
// Construction Tests
// ============================================================================

TEST(ValueTest_17, DefaultConstructor_IsNull_17) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST(ValueTest_17, StringConstructor_17) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueTest_17, CStringConstructor_17) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST(ValueTest_17, IntConstructor_17) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueTest_17, DoubleConstructor_17) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST(ValueTest_17, BoolConstructorTrue_17) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_17, BoolConstructorFalse_17) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueTest_17, ObjectConstructor_17) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST(ValueTest_17, ArrayConstructor_17) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST(ValueTest_17, CopyConstructor_17) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "test");
}

TEST(ValueTest_17, CopyConstructorNull_17) {
    Value original;
    Value copy(original);
    EXPECT_TRUE(copy.isNull());
}

TEST(ValueTest_17, CopyConstructorInt_17) {
    Value original(123);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 123);
}

// ============================================================================
// Assignment Operator Tests
// ============================================================================

TEST(ValueTest_17, AssignValue_17) {
    Value v1("hello");
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isString());
    EXPECT_EQ(v2.getString(), "hello");
}

TEST(ValueTest_17, AssignString_17) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST(ValueTest_17, AssignCString_17) {
    Value v;
    v = "c-string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "c-string");
}

TEST(ValueTest_17, AssignInt_17) {
    Value v;
    v = 99;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST(ValueTest_17, AssignDouble_17) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST(ValueTest_17, AssignObject_17) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST(ValueTest_17, AssignArray_17) {
    Value v;
    Array arr;
    arr.push_back(Value("item"));
    v = arr;
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

TEST(ValueTest_17, AssignBool_17) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_17, AssignOverwriteType_17) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v = "now a string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

// ============================================================================
// Type Check Tests
// ============================================================================

TEST(ValueTest_17, IsStringable_ForString_17) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST(ValueTest_17, IsStringable_ForInt_17) {
    Value v(42);
    EXPECT_TRUE(v.isStringable());
}

TEST(ValueTest_17, IsStringable_ForDouble_17) {
    Value v(3.14);
    EXPECT_TRUE(v.isStringable());
}

TEST(ValueTest_17, IsNumeric_ForInt_17) {
    Value v(10);
    EXPECT_TRUE(v.isNumeric());
}

TEST(ValueTest_17, IsNumeric_ForDouble_17) {
    Value v(1.5);
    EXPECT_TRUE(v.isNumeric());
}

TEST(ValueTest_17, IsNumeric_ForString_17) {
    Value v("not a number");
    EXPECT_FALSE(v.isNumeric());
}

TEST(ValueTest_17, IsNull_AfterSetNull_17) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_17, IsString_ForNonString_17) {
    Value v(42);
    EXPECT_FALSE(v.isString());
}

TEST(ValueTest_17, IsInteger_ForNonInt_17) {
    Value v("hello");
    EXPECT_FALSE(v.isInteger());
}

TEST(ValueTest_17, IsDouble_ForNonDouble_17) {
    Value v(42);
    EXPECT_FALSE(v.isDouble());
}

TEST(ValueTest_17, IsObject_ForNonObject_17) {
    Value v(42);
    EXPECT_FALSE(v.isObject());
}

TEST(ValueTest_17, IsArray_ForNonArray_17) {
    Value v(42);
    EXPECT_FALSE(v.isArray());
}

TEST(ValueTest_17, IsBoolean_ForNonBool_17) {
    Value v(42);
    EXPECT_FALSE(v.isBoolean());
}

// ============================================================================
// Setter / Getter Tests
// ============================================================================

TEST(ValueTest_17, SetString_17) {
    Value v;
    v.setString("test");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

TEST(ValueTest_17, SetInteger_17) {
    Value v;
    v.setInteger(100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST(ValueTest_17, SetDouble_17) {
    Value v;
    v.setDouble(1.23);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.23);
}

TEST(ValueTest_17, SetBoolean_17) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_17, SetObject_17) {
    Value v;
    Object obj;
    obj["x"] = Value(10);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
}

TEST(ValueTest_17, SetArray_17) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
}

TEST(ValueTest_17, SetNull_17) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_17, GetFloat_17) {
    Value v(3.14);
    EXPECT_FLOAT_EQ(v.getFloat(), 3.14f);
}

// ============================================================================
// Try Get (with defaults) Tests
// ============================================================================

TEST(ValueTest_17, TryGetString_WhenString_17) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST(ValueTest_17, TryGetString_WhenNotString_17) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST(ValueTest_17, TryGetInteger_WhenInteger_17) {
    Value v(10);
    EXPECT_EQ(v.tryGetInteger(99), 10);
}

TEST(ValueTest_17, TryGetInteger_WhenNotInteger_17) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(99), 99);
}

TEST(ValueTest_17, TryGetDouble_WhenDouble_17) {
    Value v(2.5);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 2.5);
}

TEST(ValueTest_17, TryGetDouble_WhenNotDouble_17) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.0), 1.0);
}

TEST(ValueTest_17, TryGetFloat_WhenDouble_17) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST(ValueTest_17, TryGetFloat_WhenNotDouble_17) {
    Value v("hello");
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.0f), 1.0f);
}

TEST(ValueTest_17, TryGetBoolean_WhenBoolean_17) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST(ValueTest_17, TryGetBoolean_WhenNotBoolean_17) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ============================================================================
// Comparison Operator Tests
// ============================================================================

TEST(ValueTest_17, EqualityOperator_SameValues_17) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueTest_17, EqualityOperator_DifferentValues_17) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
}

TEST(ValueTest_17, InequalityOperator_17) {
    Value v1(42);
    Value v2(43);
    EXPECT_TRUE(v1 != v2);
}

TEST(ValueTest_17, LessThanOperator_17) {
    Value v1(10);
    Value v2(20);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST(ValueTest_17, LessThanOrEqualOperator_17) {
    Value v1(10);
    Value v2(10);
    EXPECT_TRUE(v1 <= v2);
}

TEST(ValueTest_17, GreaterThanOperator_17) {
    Value v1(20);
    Value v2(10);
    EXPECT_TRUE(v1 > v2);
}

TEST(ValueTest_17, GreaterThanOrEqualOperator_17) {
    Value v1(10);
    Value v2(10);
    EXPECT_TRUE(v1 >= v2);
}

TEST(ValueTest_17, EqualityStrings_17) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueTest_17, EqualityDifferentTypes_17) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

TEST(ValueTest_17, EqualityNulls_17) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueTest_17, EqualityBooleans_17) {
    Value v1(true);
    Value v2(true);
    EXPECT_TRUE(v1 == v2);
}

// ============================================================================
// Subscript Operator Tests
// ============================================================================

TEST(ValueTest_17, SubscriptString_CreatesObject_17) {
    Value v;
    v.setObject(Object());
    v["key"] = Value(42);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST(ValueTest_17, SubscriptCString_17) {
    Value v;
    v.setObject(Object());
    v["name"] = Value("test");
    EXPECT_EQ(v["name"].getString(), "test");
}

TEST(ValueTest_17, SubscriptIndex_17) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

// ============================================================================
// Serialization / Deserialization Tests
// ============================================================================

TEST(ValueTest_17, LoadFromString_Integer_17) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueTest_17, LoadFromString_String_17) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueTest_17, LoadFromString_Boolean_17) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_17, LoadFromString_Null_17) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_17, LoadFromString_Double_17) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST(ValueTest_17, LoadFromString_Object_17) {
    Value v;
    v.loadFromString("{\"key\": 42}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST(ValueTest_17, LoadFromString_Array_17) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST(ValueTest_17, LoadFromStream_17) {
    std::istringstream ss("\"stream test\"");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "stream test");
}

TEST(ValueTest_17, StreamConstructor_17) {
    std::istringstream ss("123");
    Value v(ss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

TEST(ValueTest_17, WriteToStream_Integer_17) {
    Value v(42);
    std::ostringstream os;
    v.writeToStream(os, false, false);
    EXPECT_EQ(os.str(), "42");
}

TEST(ValueTest_17, WriteToStream_String_17) {
    Value v("hello");
    std::ostringstream os;
    v.writeToStream(os, false, false);
    EXPECT_EQ(os.str(), "\"hello\"");
}

TEST(ValueTest_17, WriteToStream_Boolean_17) {
    Value v(true);
    std::ostringstream os;
    v.writeToStream(os, false, false);
    EXPECT_EQ(os.str(), "true");
}

TEST(ValueTest_17, WriteToStream_Null_17) {
    Value v;
    std::ostringstream os;
    v.writeToStream(os, false, false);
    EXPECT_EQ(os.str(), "null");
}

TEST(ValueTest_17, WriteToStream_BoolFalse_17) {
    Value v(false);
    std::ostringstream os;
    v.writeToStream(os, false, false);
    EXPECT_EQ(os.str(), "false");
}

TEST(ValueTest_17, OutputStreamOperator_17) {
    Value v(42);
    std::ostringstream os;
    os << v;
    // Should produce some output representing the value
    EXPECT_FALSE(os.str().empty());
}

// ============================================================================
// getToString Tests
// ============================================================================

TEST(ValueTest_17, GetToString_FromString_17) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

TEST(ValueTest_17, GetToString_FromInt_17) {
    Value v(42);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

TEST(ValueTest_17, GetToString_FromDouble_17) {
    Value v(3.14);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

// ============================================================================
// Escape Function Tests
// ============================================================================

TEST(ValueTest_17, EscapeMinimumCharacters_NoSpecialChars_17) {
    std::string result = Value::escapeMinimumCharacters("hello");
    EXPECT_EQ(result, "hello");
}

TEST(ValueTest_17, EscapeMinimumCharacters_WithQuote_17) {
    std::string result = Value::escapeMinimumCharacters("he\"llo");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST(ValueTest_17, EscapeMinimumCharacters_WithBackslash_17) {
    std::string result = Value::escapeMinimumCharacters("he\\llo");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST(ValueTest_17, EscapeMinimumCharacters_WithNewline_17) {
    std::string result = Value::escapeMinimumCharacters("he\nllo");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST(ValueTest_17, EscapeMinimumCharacters_EmptyString_17) {
    std::string result = Value::escapeMinimumCharacters("");
    EXPECT_EQ(result, "");
}

TEST(ValueTest_17, EscapeAllCharacters_EmptyString_17) {
    std::string result = Value::escapeAllCharacters("");
    EXPECT_EQ(result, "");
}

TEST(ValueTest_17, EscapeAllCharacters_NoSpecialChars_17) {
    std::string result = Value::escapeAllCharacters("hello");
    // Should still produce output, possibly with unicode escapes
    EXPECT_FALSE(result.empty());
}

TEST(ValueTest_17, EscapeToUnicode_17) {
    std::string result = Value::escapeToUnicode('A');
    // Should produce a unicode escape like \u0041
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ============================================================================
// Boundary / Edge Cases
// ============================================================================

TEST(ValueTest_17, IntegerBoundary_Zero_17) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST(ValueTest_17, IntegerBoundary_Negative_17) {
    Value v(-1);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -1);
}

TEST(ValueTest_17, IntegerBoundary_MaxInt_17) {
    Value v(INT_MAX);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), INT_MAX);
}

TEST(ValueTest_17, IntegerBoundary_MinInt_17) {
    Value v(INT_MIN);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), INT_MIN);
}

TEST(ValueTest_17, DoubleBoundary_Zero_17) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST(ValueTest_17, DoubleBoundary_Negative_17) {
    Value v(-1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -1.5);
}

TEST(ValueTest_17, EmptyString_17) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST(ValueTest_17, EmptyObject_17) {
    Value v(Object());
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST(ValueTest_17, EmptyArray_17) {
    Value v(Array());
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST(ValueTest_17, LoadFromString_EmptyObject_17) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST(ValueTest_17, LoadFromString_EmptyArray_17) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST(ValueTest_17, LoadFromString_NegativeNumber_17) {
    Value v;
    v.loadFromString("-42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST(ValueTest_17, LoadFromString_NestedObject_17) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": 1}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 1);
}

TEST(ValueTest_17, LoadFromString_NestedArray_17) {
    Value v;
    v.loadFromString("[[1, 2], [3, 4]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

// ============================================================================
// Reassignment / Type Change Tests
// ============================================================================

TEST(ValueTest_17, ChangeFromIntToString_17) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setString("now string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now string");
}

TEST(ValueTest_17, ChangeFromStringToNull_17) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_17, ChangeFromBoolToInt_17) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    v.setInteger(55);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 55);
}

TEST(ValueTest_17, ChangeFromDoubleToArray_17) {
    Value v(1.5);
    Array arr;
    arr.push_back(Value(1));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
}

TEST(ValueTest_17, WriteToStreamIndented_17) {
    Value v;
    v.loadFromString("{\"key\": 42}");
    std::ostringstream os;
    v.writeToStream(os, true, false);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    // Indented output should contain newlines or spaces
}

TEST(ValueTest_17, WriteToStreamEscapeAll_17) {
    Value v("hello");
    std::ostringstream os;
    v.writeToStream(os, false, true);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// ============================================================================
// String with escape characters round-trip
// ============================================================================

TEST(ValueTest_17, LoadFromString_EscapedCharacters_17) {
    Value v;
    v.loadFromString("\"hello\\nworld\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello\nworld");
}

TEST(ValueTest_17, LoadFromString_EscapedQuote_17) {
    Value v;
    v.loadFromString("\"hello\\\"world\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello\"world");
}

TEST(ValueTest_17, LoadFromString_FalseBoolean_17) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueTest_17, LoadFromString_NegativeDouble_17) {
    Value v;
    v.loadFromString("-3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -3.14);
}

// ============================================================================
// Complex/Realistic JSON
// ============================================================================

TEST(ValueTest_17, ComplexJson_17) {
    Value v;
    v.loadFromString(R"({"name": "test", "value": 42, "arr": [1, 2, 3], "nested": {"a": true}})");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["name"].getString(), "test");
    EXPECT_EQ(v["value"].getInteger(), 42);
    EXPECT_TRUE(v["arr"].isArray());
    EXPECT_EQ(v["arr"].getArray().size(), 3u);
    EXPECT_TRUE(v["nested"]["a"].getBoolean());
}

TEST(ValueTest_17, RoundTrip_17) {
    Value original;
    original.loadFromString(R"({"key": "value", "num": 123})");
    
    std::ostringstream os;
    original.writeToStream(os, false, false);
    
    Value reloaded;
    reloaded.loadFromString(os.str());
    
    EXPECT_TRUE(reloaded.isObject());
    EXPECT_EQ(reloaded["key"].getString(), "value");
    EXPECT_EQ(reloaded["num"].getInteger(), 123);
}
