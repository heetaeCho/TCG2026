#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

// ============================================================
// Test fixture
// ============================================================
class ValueTest_34 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Construction tests
// ============================================================

TEST_F(ValueTest_34, DefaultConstructorIsNull_34) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_34, StringConstructor_34) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_34, CStringConstructor_34) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_34, IntConstructor_34) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_34, DoubleConstructor_34) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_34, BooleanConstructorTrue_34) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_34, BooleanConstructorFalse_34) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_34, ObjectConstructor_34) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_34, ArrayConstructor_34) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_34, CopyConstructor_34) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "test");
}

// ============================================================
// isStringable tests (the method under focus)
// ============================================================

TEST_F(ValueTest_34, IsStringableForString_34) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_34, IsStringableForInteger_34) {
    Value v(123);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_34, IsStringableForDouble_34) {
    Value v(1.5);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_34, IsStringableForBoolean_34) {
    Value v(true);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_34, IsStringableForNull_34) {
    Value v;
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_34, IsNotStringableForArray_34) {
    Array arr;
    Value v(arr);
    EXPECT_FALSE(v.isStringable());
}

TEST_F(ValueTest_34, IsNotStringableForObject_34) {
    Object obj;
    Value v(obj);
    EXPECT_FALSE(v.isStringable());
}

TEST_F(ValueTest_34, IsNotStringableForNonEmptyArray_34) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value("two"));
    Value v(arr);
    EXPECT_FALSE(v.isStringable());
}

TEST_F(ValueTest_34, IsNotStringableForNonEmptyObject_34) {
    Object obj;
    obj["a"] = Value(1);
    obj["b"] = Value(2);
    Value v(obj);
    EXPECT_FALSE(v.isStringable());
}

// ============================================================
// Type query tests
// ============================================================

TEST_F(ValueTest_34, IsStringTrue_34) {
    Value v("abc");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_34, IsIntegerTrue_34) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_34, IsDoubleTrue_34) {
    Value v(2.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_34, IsNumericForInteger_34) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_34, IsNumericForDouble_34) {
    Value v(5.0);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_34, IsNotNumericForString_34) {
    Value v("5");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_34, IsNotNumericForNull_34) {
    Value v;
    EXPECT_FALSE(v.isNumeric());
}

// ============================================================
// Assignment operator tests
// ============================================================

TEST_F(ValueTest_34, AssignString_34) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_34, AssignCString_34) {
    Value v;
    v = "cstr";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "cstr");
}

TEST_F(ValueTest_34, AssignInt_34) {
    Value v;
    v = 99;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_34, AssignDouble_34) {
    Value v;
    v = 1.23;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.23);
}

TEST_F(ValueTest_34, AssignBool_34) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_34, AssignObject_34) {
    Value v;
    Object obj;
    obj["x"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_34, AssignArray_34) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_34, AssignValueCopy_34) {
    Value src(42);
    Value dst;
    dst = src;
    EXPECT_TRUE(dst.isInteger());
    EXPECT_EQ(dst.getInteger(), 42);
}

// ============================================================
// Setter tests
// ============================================================

TEST_F(ValueTest_34, SetString_34) {
    Value v(123);
    v.setString("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST_F(ValueTest_34, SetInteger_34) {
    Value v("text");
    v.setInteger(7);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 7);
}

TEST_F(ValueTest_34, SetDouble_34) {
    Value v;
    v.setDouble(9.81);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 9.81);
}

TEST_F(ValueTest_34, SetBoolean_34) {
    Value v;
    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_34, SetNull_34) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_34, SetObject_34) {
    Value v;
    Object obj;
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_34, SetArray_34) {
    Value v;
    Array arr;
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
}

// ============================================================
// tryGet tests (default value behavior)
// ============================================================

TEST_F(ValueTest_34, TryGetStringReturnsValueWhenString_34) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST_F(ValueTest_34, TryGetStringReturnsDefaultWhenNotString_34) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_34, TryGetIntegerReturnsValueWhenInteger_34) {
    Value v(10);
    EXPECT_EQ(v.tryGetInteger(0), 10);
}

TEST_F(ValueTest_34, TryGetIntegerReturnsDefaultWhenNotInteger_34) {
    Value v("text");
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

TEST_F(ValueTest_34, TryGetDoubleReturnsValueWhenDouble_34) {
    Value v(2.71);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 2.71);
}

TEST_F(ValueTest_34, TryGetDoubleReturnsDefaultWhenNotDouble_34) {
    Value v("text");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.0), 1.0);
}

TEST_F(ValueTest_34, TryGetFloatReturnsValueWhenDouble_34) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST_F(ValueTest_34, TryGetFloatReturnsDefaultWhenNotDouble_34) {
    Value v("text");
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.0f), 1.0f);
}

TEST_F(ValueTest_34, TryGetBooleanReturnsValueWhenBoolean_34) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_34, TryGetBooleanReturnsDefaultWhenNotBoolean_34) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ============================================================
// Comparison operator tests
// ============================================================

TEST_F(ValueTest_34, EqualityOperator_34) {
    Value a(10);
    Value b(10);
    EXPECT_TRUE(a == b);
}

TEST_F(ValueTest_34, InequalityOperator_34) {
    Value a(10);
    Value b(20);
    EXPECT_TRUE(a != b);
}

TEST_F(ValueTest_34, LessThanOperator_34) {
    Value a(5);
    Value b(10);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(ValueTest_34, LessThanOrEqualOperator_34) {
    Value a(5);
    Value b(5);
    EXPECT_TRUE(a <= b);
}

TEST_F(ValueTest_34, GreaterThanOperator_34) {
    Value a(20);
    Value b(10);
    EXPECT_TRUE(a > b);
}

TEST_F(ValueTest_34, GreaterThanOrEqualOperator_34) {
    Value a(10);
    Value b(10);
    EXPECT_TRUE(a >= b);
}

TEST_F(ValueTest_34, EqualityDifferentTypes_34) {
    Value a(10);
    Value b("10");
    EXPECT_TRUE(a != b);
}

// ============================================================
// Subscript operator tests
// ============================================================

TEST_F(ValueTest_34, SubscriptStringKeyOnObject_34) {
    Object obj;
    obj["key"] = Value(42);
    Value v(obj);
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST_F(ValueTest_34, SubscriptCStringKeyOnObject_34) {
    Object obj;
    obj["foo"] = Value("bar");
    Value v(obj);
    EXPECT_EQ(v["foo"].getString(), "bar");
}

TEST_F(ValueTest_34, SubscriptIndexOnArray_34) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

// ============================================================
// getToString tests
// ============================================================

TEST_F(ValueTest_34, GetToStringForString_34) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

TEST_F(ValueTest_34, GetToStringForInteger_34) {
    Value v(42);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_34, GetToStringForDouble_34) {
    Value v(3.14);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_34, GetToStringForBoolean_34) {
    Value v(true);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_34, GetToStringForNull_34) {
    Value v;
    std::string result = v.getToString();
    // Null should still produce some string representation
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Load/Write stream tests
// ============================================================

TEST_F(ValueTest_34, LoadFromStringSimpleInt_34) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_34, LoadFromStringSimpleString_34) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_34, LoadFromStringBoolean_34) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_34, LoadFromStringNull_34) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_34, LoadFromStringArray_34) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_34, LoadFromStringObject_34) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_34, LoadFromStream_34) {
    std::istringstream iss("123");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

TEST_F(ValueTest_34, WriteToStream_34) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(ValueTest_34, WriteToStreamIndented_34) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTest_34, StreamInsertionOperator_34) {
    Value v("test");
    std::ostringstream oss;
    oss << v;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// ============================================================
// ConstructFromStream tests
// ============================================================

TEST_F(ValueTest_34, ConstructFromStream_34) {
    std::istringstream iss("\"from stream\"");
    Value v(iss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "from stream");
}

// ============================================================
// Escape static methods tests
// ============================================================

TEST_F(ValueTest_34, EscapeMinimumCharacters_34) {
    std::string result = Value::escapeMinimumCharacters("line1\nline2");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_34, EscapeMinimumCharactersQuote_34) {
    std::string result = Value::escapeMinimumCharacters("say \"hello\"");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_34, EscapeAllCharacters_34) {
    std::string result = Value::escapeAllCharacters("abc");
    // Each character should be escaped to unicode
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_34, EscapeToUnicode_34) {
    std::string result = Value::escapeToUnicode('A');
    // Should produce a unicode escape sequence like \u0041
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ============================================================
// Boundary / edge cases
// ============================================================

TEST_F(ValueTest_34, EmptyStringValue_34) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_34, ZeroInteger_34) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_34, NegativeInteger_34) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST_F(ValueTest_34, ZeroDouble_34) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_34, NegativeDouble_34) {
    Value v(-3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -3.14);
}

TEST_F(ValueTest_34, EmptyArrayValue_34) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
    EXPECT_FALSE(v.isStringable());
}

TEST_F(ValueTest_34, EmptyObjectValue_34) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
    EXPECT_FALSE(v.isStringable());
}

TEST_F(ValueTest_34, GetFloatFromDouble_34) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 1.5f);
}

TEST_F(ValueTest_34, LoadFromStringDouble_34) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_34, LoadFromStringNegativeNumber_34) {
    Value v;
    v.loadFromString("-42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST_F(ValueTest_34, LoadFromStringFalse_34) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_34, ReassignChangesType_34) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v = "now a string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST_F(ValueTest_34, SetNullFromNonNull_34) {
    Value v("hello");
    EXPECT_FALSE(v.isNull());
    v.setNull();
    EXPECT_TRUE(v.isNull());
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_34, IsStringableAfterTypeChange_34) {
    Value v;
    Array arr;
    v.setArray(arr);
    EXPECT_FALSE(v.isStringable());
    v.setInteger(5);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_34, NestedObjectArray_34) {
    Array arr;
    Object innerObj;
    innerObj["inner"] = Value(true);
    arr.push_back(Value(innerObj));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_FALSE(v.isStringable());
    EXPECT_EQ(v.getArray().size(), 1u);
}

TEST_F(ValueTest_34, WriteAndReadRoundTrip_34) {
    Object obj;
    obj["name"] = Value("test");
    obj["value"] = Value(42);
    obj["flag"] = Value(true);
    Value original(obj);

    std::ostringstream oss;
    original.writeToStream(oss, false, false);

    Value loaded;
    loaded.loadFromString(oss.str());
    EXPECT_TRUE(loaded.isObject());
    EXPECT_EQ(loaded["name"].getString(), "test");
    EXPECT_EQ(loaded["value"].getInteger(), 42);
    EXPECT_TRUE(loaded["flag"].getBoolean());
}
