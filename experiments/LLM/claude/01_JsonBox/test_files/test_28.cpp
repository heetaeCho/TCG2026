#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

// ==================== Construction Tests ====================

TEST(ValueTest_28, DefaultConstructorCreatesNull_28) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_28, StringConstructor_28) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueTest_28, CStringConstructor_28) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST(ValueTest_28, IntConstructor_28) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueTest_28, DoubleConstructor_28) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST(ValueTest_28, BooleanConstructorTrue_28) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_28, BooleanConstructorFalse_28) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueTest_28, ObjectConstructor_28) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST(ValueTest_28, ArrayConstructor_28) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST(ValueTest_28, CopyConstructor_28) {
    Value original(123);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 123);
}

TEST(ValueTest_28, StreamConstructor_28) {
    std::istringstream input("\"test string\"");
    Value v(input);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test string");
}

// ==================== Type Checking Tests ====================

TEST(ValueTest_28, IsStringReturnsFalseForNonString_28) {
    Value v(42);
    EXPECT_FALSE(v.isString());
}

TEST(ValueTest_28, IsIntegerReturnsFalseForDouble_28) {
    Value v(3.14);
    EXPECT_FALSE(v.isInteger());
}

TEST(ValueTest_28, IsDoubleReturnsFalseForInteger_28) {
    Value v(42);
    EXPECT_FALSE(v.isDouble());
}

TEST(ValueTest_28, IsNumericTrueForInteger_28) {
    Value v(42);
    EXPECT_TRUE(v.isNumeric());
}

TEST(ValueTest_28, IsNumericTrueForDouble_28) {
    Value v(3.14);
    EXPECT_TRUE(v.isNumeric());
}

TEST(ValueTest_28, IsNumericFalseForString_28) {
    Value v("hello");
    EXPECT_FALSE(v.isNumeric());
}

TEST(ValueTest_28, IsObjectReturnsFalseForNull_28) {
    Value v;
    EXPECT_FALSE(v.isObject());
}

TEST(ValueTest_28, IsArrayReturnsFalseForNull_28) {
    Value v;
    EXPECT_FALSE(v.isArray());
}

TEST(ValueTest_28, IsBooleanReturnsFalseForNull_28) {
    Value v;
    EXPECT_FALSE(v.isBoolean());
}

TEST(ValueTest_28, IsNullReturnsFalseForString_28) {
    Value v("hello");
    EXPECT_FALSE(v.isNull());
}

// ==================== Assignment Operator Tests ====================

TEST(ValueTest_28, AssignValueFromValue_28) {
    Value a(42);
    Value b;
    b = a;
    EXPECT_TRUE(b.isInteger());
    EXPECT_EQ(b.getInteger(), 42);
}

TEST(ValueTest_28, AssignStringToValue_28) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST(ValueTest_28, AssignCStringToValue_28) {
    Value v;
    v = "c-string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "c-string");
}

TEST(ValueTest_28, AssignIntToValue_28) {
    Value v;
    v = 99;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST(ValueTest_28, AssignDoubleToValue_28) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST(ValueTest_28, AssignObjectToValue_28) {
    Value v;
    Object obj;
    obj["x"] = Value(10);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST(ValueTest_28, AssignArrayToValue_28) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

TEST(ValueTest_28, AssignBoolToValue_28) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

// ==================== Setter Tests ====================

TEST(ValueTest_28, SetString_28) {
    Value v(42);
    v.setString("changed");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "changed");
}

TEST(ValueTest_28, SetInteger_28) {
    Value v("hello");
    v.setInteger(100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST(ValueTest_28, SetDouble_28) {
    Value v("hello");
    v.setDouble(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.5);
}

TEST(ValueTest_28, SetBoolean_28) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_28, SetNull_28) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_28, SetObject_28) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
}

TEST(ValueTest_28, SetArray_28) {
    Value v;
    Array arr;
    arr.push_back(Value("item"));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
}

// ==================== Getter / TryGet Tests ====================

TEST(ValueTest_28, GetFloat_28) {
    Value v(3.14);
    EXPECT_NEAR(v.getFloat(), 3.14f, 0.001f);
}

TEST(ValueTest_28, TryGetStringReturnsValueWhenString_28) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST(ValueTest_28, TryGetStringReturnsDefaultWhenNotString_28) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST(ValueTest_28, TryGetIntegerReturnsValueWhenInteger_28) {
    Value v(10);
    EXPECT_EQ(v.tryGetInteger(0), 10);
}

TEST(ValueTest_28, TryGetIntegerReturnsDefaultWhenNotInteger_28) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(0), 0);
}

TEST(ValueTest_28, TryGetDoubleReturnsValueWhenDouble_28) {
    Value v(2.5);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 2.5);
}

TEST(ValueTest_28, TryGetDoubleReturnsDefaultWhenNotDouble_28) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.0), 1.0);
}

TEST(ValueTest_28, TryGetFloatReturnsValueWhenDouble_28) {
    Value v(2.5);
    EXPECT_NEAR(v.tryGetFloat(0.0f), 2.5f, 0.001f);
}

TEST(ValueTest_28, TryGetFloatReturnsDefaultWhenNotNumeric_28) {
    Value v("hello");
    EXPECT_NEAR(v.tryGetFloat(1.0f), 1.0f, 0.001f);
}

TEST(ValueTest_28, TryGetBooleanReturnsValueWhenBoolean_28) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST(ValueTest_28, TryGetBooleanReturnsDefaultWhenNotBoolean_28) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ==================== Comparison Operator Tests ====================

TEST(ValueTest_28, EqualityOfSameIntegers_28) {
    Value a(5);
    Value b(5);
    EXPECT_TRUE(a == b);
}

TEST(ValueTest_28, EqualityOfDifferentIntegers_28) {
    Value a(5);
    Value b(10);
    EXPECT_FALSE(a == b);
}

TEST(ValueTest_28, InequalityOfDifferentIntegers_28) {
    Value a(5);
    Value b(10);
    EXPECT_TRUE(a != b);
}

TEST(ValueTest_28, InequalityOfSameIntegers_28) {
    Value a(5);
    Value b(5);
    EXPECT_FALSE(a != b);
}

TEST(ValueTest_28, LessThanIntegers_28) {
    Value a(3);
    Value b(10);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(ValueTest_28, LessThanOrEqualIntegers_28) {
    Value a(3);
    Value b(3);
    Value c(5);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a <= c);
    EXPECT_FALSE(c <= a);
}

TEST(ValueTest_28, GreaterThanIntegers_28) {
    Value a(10);
    Value b(3);
    EXPECT_TRUE(a > b);
    EXPECT_FALSE(b > a);
}

TEST(ValueTest_28, GreaterThanOrEqualIntegers_28) {
    Value a(10);
    Value b(10);
    Value c(3);
    EXPECT_TRUE(a >= b);
    EXPECT_TRUE(a >= c);
    EXPECT_FALSE(c >= a);
}

TEST(ValueTest_28, EqualityOfSameStrings_28) {
    Value a("hello");
    Value b("hello");
    EXPECT_TRUE(a == b);
}

TEST(ValueTest_28, EqualityOfDifferentStrings_28) {
    Value a("hello");
    Value b("world");
    EXPECT_FALSE(a == b);
}

TEST(ValueTest_28, EqualityOfSameBooleans_28) {
    Value a(true);
    Value b(true);
    EXPECT_TRUE(a == b);
}

TEST(ValueTest_28, EqualityOfDifferentBooleans_28) {
    Value a(true);
    Value b(false);
    EXPECT_FALSE(a == b);
}

TEST(ValueTest_28, EqualityOfNullValues_28) {
    Value a;
    Value b;
    EXPECT_TRUE(a == b);
}

TEST(ValueTest_28, EqualityOfDifferentTypes_28) {
    Value a(42);
    Value b("42");
    EXPECT_FALSE(a == b);
}

TEST(ValueTest_28, GreaterThanOrEqualSameValue_28) {
    Value a(5);
    Value b(5);
    EXPECT_TRUE(a >= b);
}

TEST(ValueTest_28, GreaterThanOrEqualGreaterValue_28) {
    Value a(10);
    Value b(5);
    EXPECT_TRUE(a >= b);
}

TEST(ValueTest_28, GreaterThanOrEqualLesserValue_28) {
    Value a(3);
    Value b(5);
    EXPECT_FALSE(a >= b);
}

// ==================== Subscript Operator Tests ====================

TEST(ValueTest_28, SubscriptStringKey_28) {
    Value v;
    Object obj;
    obj["key"] = Value(42);
    v.setObject(obj);
    EXPECT_TRUE(v["key"].isInteger());
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST(ValueTest_28, SubscriptCStringKey_28) {
    Value v;
    Object obj;
    obj["key"] = Value("val");
    v.setObject(obj);
    EXPECT_TRUE(v["key"].isString());
    EXPECT_EQ(v["key"].getString(), "val");
}

TEST(ValueTest_28, SubscriptArrayIndex_28) {
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

// ==================== Load / Parse Tests ====================

TEST(ValueTest_28, LoadFromStringInteger_28) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueTest_28, LoadFromStringString_28) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueTest_28, LoadFromStringBoolean_28) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_28, LoadFromStringNull_28) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_28, LoadFromStringDouble_28) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_NEAR(v.getDouble(), 3.14, 0.001);
}

TEST(ValueTest_28, LoadFromStringObject_28) {
    Value v;
    v.loadFromString("{\"key\": 123}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getInteger(), 123);
}

TEST(ValueTest_28, LoadFromStringArray_28) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST(ValueTest_28, LoadFromStream_28) {
    std::istringstream iss("{\"a\": true}");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["a"].getBoolean());
}

// ==================== Write / Serialize Tests ====================

TEST(ValueTest_28, WriteToStreamInteger_28) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_FALSE(oss.str().empty());
    EXPECT_NE(oss.str().find("42"), std::string::npos);
}

TEST(ValueTest_28, WriteToStreamString_28) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("hello"), std::string::npos);
}

TEST(ValueTest_28, WriteToStreamBoolean_28) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("true"), std::string::npos);
}

TEST(ValueTest_28, WriteToStreamNull_28) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("null"), std::string::npos);
}

TEST(ValueTest_28, WriteToStreamWithIndent_28) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// ==================== Escape Tests ====================

TEST(ValueTest_28, EscapeMinimumCharacters_28) {
    std::string input = "line1\nline2\ttab";
    std::string escaped = Value::escapeMinimumCharacters(input);
    EXPECT_NE(escaped.find("\\n"), std::string::npos);
    EXPECT_NE(escaped.find("\\t"), std::string::npos);
}

TEST(ValueTest_28, EscapeAllCharacters_28) {
    std::string input = "hello";
    std::string escaped = Value::escapeAllCharacters(input);
    // Each character should be escaped to unicode
    EXPECT_FALSE(escaped.empty());
}

TEST(ValueTest_28, EscapeToUnicode_28) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
    // Should contain \u prefix
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ==================== GetToString Tests ====================

TEST(ValueTest_28, GetToStringFromInteger_28) {
    Value v(42);
    std::string s = v.getToString();
    EXPECT_EQ(s, "42");
}

TEST(ValueTest_28, GetToStringFromString_28) {
    Value v("hello");
    std::string s = v.getToString();
    EXPECT_EQ(s, "hello");
}

TEST(ValueTest_28, GetToStringFromBoolean_28) {
    Value v(true);
    std::string s = v.getToString();
    // Typically "true" or "1"
    EXPECT_FALSE(s.empty());
}

// ==================== IsStringable Tests ====================

TEST(ValueTest_28, IsStringableForString_28) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST(ValueTest_28, IsStringableForInteger_28) {
    Value v(42);
    EXPECT_TRUE(v.isStringable());
}

TEST(ValueTest_28, IsStringableForDouble_28) {
    Value v(3.14);
    EXPECT_TRUE(v.isStringable());
}

TEST(ValueTest_28, IsStringableForNull_28) {
    Value v;
    // Null may or may not be stringable depending on implementation
    // We just call it to ensure it doesn't crash
    v.isStringable();
}

// ==================== Boundary / Edge Cases ====================

TEST(ValueTest_28, EmptyString_28) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST(ValueTest_28, NegativeInteger_28) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST(ValueTest_28, ZeroInteger_28) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST(ValueTest_28, ZeroDouble_28) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST(ValueTest_28, NegativeDouble_28) {
    Value v(-1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -1.5);
}

TEST(ValueTest_28, LargeInteger_28) {
    Value v(2147483647); // INT_MAX
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST(ValueTest_28, EmptyObject_28) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST(ValueTest_28, EmptyArray_28) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST(ValueTest_28, ReassignFromIntToString_28) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v = std::string("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST(ValueTest_28, ReassignFromStringToNull_28) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_28, NestedObjectParsing_28) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": 42}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

TEST(ValueTest_28, NestedArrayParsing_28) {
    Value v;
    v.loadFromString("[[1, 2], [3, 4]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST(ValueTest_28, LoadFromStringEmptyObject_28) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST(ValueTest_28, LoadFromStringEmptyArray_28) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST(ValueTest_28, OperatorStreamOutput_28) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_NE(oss.str().find("42"), std::string::npos);
}

TEST(ValueTest_28, EscapeMinimumCharactersBackslash_28) {
    std::string input = "back\\slash";
    std::string escaped = Value::escapeMinimumCharacters(input);
    EXPECT_NE(escaped.find("\\\\"), std::string::npos);
}

TEST(ValueTest_28, EscapeMinimumCharactersQuote_28) {
    std::string input = "say \"hello\"";
    std::string escaped = Value::escapeMinimumCharacters(input);
    EXPECT_NE(escaped.find("\\\""), std::string::npos);
}

TEST(ValueTest_28, SelfAssignment_28) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueTest_28, ComparisonDifferentTypes_28) {
    Value a(42);
    Value b("hello");
    // They should not be equal
    EXPECT_TRUE(a != b);
}

TEST(ValueTest_28, LoadFromStringNegativeNumber_28) {
    Value v;
    v.loadFromString("-123");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -123);
}

TEST(ValueTest_28, LoadFromStringFalse_28) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueTest_28, LoadFromStringStringWithEscapes_28) {
    Value v;
    v.loadFromString("\"hello\\nworld\"");
    EXPECT_TRUE(v.isString());
    EXPECT_NE(v.getString().find('\n'), std::string::npos);
}

TEST(ValueTest_28, MultipleSubscriptAccess_28) {
    Value v;
    v.loadFromString("{\"a\": {\"b\": {\"c\": 99}}}");
    EXPECT_EQ(v["a"]["b"]["c"].getInteger(), 99);
}
