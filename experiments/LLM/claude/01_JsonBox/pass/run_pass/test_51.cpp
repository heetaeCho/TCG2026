#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueTest_51 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(ValueTest_51, DefaultConstructorCreatesNull_51) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_51, StringConstructor_51) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_51, CStringConstructor_51) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_51, IntConstructor_51) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_51, DoubleConstructor_51) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_51, BooleanConstructorTrue_51) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_51, BooleanConstructorFalse_51) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_51, ObjectConstructor_51) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_51, ArrayConstructor_51) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_51, CopyConstructor_51) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

TEST_F(ValueTest_51, StreamConstructor_51) {
    std::istringstream input("\"hello\"");
    Value v(input);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

// ==================== Type Check Tests ====================

TEST_F(ValueTest_51, IsStringForString_51) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueTest_51, IsIntegerForInt_51) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_51, IsDoubleForDouble_51) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_51, IsNumericForInt_51) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_51, IsNumericForDouble_51) {
    Value v(5.5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_51, IsNumericForString_51) {
    Value v("not a number");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_51, IsStringableForString_51) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_51, IsStringableForInt_51) {
    Value v(42);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_51, IsStringableForDouble_51) {
    Value v(3.14);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_51, IsStringableForNull_51) {
    Value v;
    // Null may or may not be stringable, just test it doesn't crash
    v.isStringable();
}

// ==================== Getter Tests ====================

TEST_F(ValueTest_51, GetInteger_51) {
    Value v(123);
    EXPECT_EQ(v.getInteger(), 123);
}

TEST_F(ValueTest_51, GetDouble_51) {
    Value v(2.718);
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_51, GetString_51) {
    Value v("json");
    EXPECT_EQ(v.getString(), "json");
}

TEST_F(ValueTest_51, GetBoolean_51) {
    Value v(true);
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_51, GetFloat_51) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 1.5f);
}

TEST_F(ValueTest_51, GetFloatFromNonDouble_51) {
    Value v;
    // getFloat on a null value should return the default (0.0f based on EMPTY_DOUBLE)
    float result = v.getFloat();
    EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST_F(ValueTest_51, GetObject_51) {
    Object obj;
    obj["x"] = Value(1);
    Value v(obj);
    const Object& retrieved = v.getObject();
    EXPECT_EQ(retrieved.size(), 1u);
    EXPECT_TRUE(retrieved.find("x") != retrieved.end());
}

TEST_F(ValueTest_51, GetArray_51) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    arr.push_back(Value(3));
    Value v(arr);
    const Array& retrieved = v.getArray();
    EXPECT_EQ(retrieved.size(), 3u);
}

// ==================== tryGet Tests ====================

TEST_F(ValueTest_51, TryGetStringReturnsValueWhenString_51) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST_F(ValueTest_51, TryGetStringReturnsDefaultWhenNotString_51) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_51, TryGetIntegerReturnsValueWhenInt_51) {
    Value v(99);
    EXPECT_EQ(v.tryGetInteger(0), 99);
}

TEST_F(ValueTest_51, TryGetIntegerReturnsDefaultWhenNotInt_51) {
    Value v("string");
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

TEST_F(ValueTest_51, TryGetDoubleReturnsValueWhenDouble_51) {
    Value v(6.28);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 6.28);
}

TEST_F(ValueTest_51, TryGetDoubleReturnsDefaultWhenNotDouble_51) {
    Value v("not double");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.0), 1.0);
}

TEST_F(ValueTest_51, TryGetFloatReturnsValueWhenDouble_51) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST_F(ValueTest_51, TryGetFloatReturnsDefaultWhenNotDouble_51) {
    Value v("not a float");
    EXPECT_FLOAT_EQ(v.tryGetFloat(9.9f), 9.9f);
}

TEST_F(ValueTest_51, TryGetBooleanReturnsValueWhenBoolean_51) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_51, TryGetBooleanReturnsDefaultWhenNotBoolean_51) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ==================== Setter Tests ====================

TEST_F(ValueTest_51, SetString_51) {
    Value v;
    v.setString("new string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "new string");
}

TEST_F(ValueTest_51, SetInteger_51) {
    Value v;
    v.setInteger(77);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 77);
}

TEST_F(ValueTest_51, SetDouble_51) {
    Value v;
    v.setDouble(1.41);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.41);
}

TEST_F(ValueTest_51, SetBoolean_51) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_51, SetNull_51) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_51, SetObject_51) {
    Value v;
    Object obj;
    obj["key"] = Value("val");
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_51, SetArray_51) {
    Value v;
    Array arr;
    arr.push_back(Value(10));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
}

// ==================== Assignment Operator Tests ====================

TEST_F(ValueTest_51, AssignValue_51) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_51, AssignString_51) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_51, AssignCString_51) {
    Value v;
    v = "c-string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "c-string");
}

TEST_F(ValueTest_51, AssignInt_51) {
    Value v;
    v = 55;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 55);
}

TEST_F(ValueTest_51, AssignDouble_51) {
    Value v;
    v = 9.81;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 9.81);
}

TEST_F(ValueTest_51, AssignBool_51) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_51, AssignObject_51) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_51, AssignArray_51) {
    Value v;
    Array arr;
    arr.push_back(Value("elem"));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

// ==================== Comparison Operator Tests ====================

TEST_F(ValueTest_51, EqualityOperator_51) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_51, InequalityOperator_51) {
    Value v1(42);
    Value v2(43);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_51, LessThanOperator_51) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
}

TEST_F(ValueTest_51, LessThanOrEqualOperator_51) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_51, GreaterThanOperator_51) {
    Value v1(3);
    Value v2(2);
    EXPECT_TRUE(v1 > v2);
}

TEST_F(ValueTest_51, GreaterThanOrEqualOperator_51) {
    Value v1(3);
    Value v2(3);
    EXPECT_TRUE(v1 >= v2);
}

TEST_F(ValueTest_51, EqualityDifferentTypes_51) {
    Value v1(42);
    Value v2("42");
    EXPECT_TRUE(v1 != v2);
}

// ==================== Subscript Operator Tests ====================

TEST_F(ValueTest_51, SubscriptStringKeyOnObject_51) {
    Object obj;
    obj["key"] = Value(100);
    Value v(obj);
    Value& elem = v["key"];
    EXPECT_TRUE(elem.isInteger());
    EXPECT_EQ(elem.getInteger(), 100);
}

TEST_F(ValueTest_51, SubscriptCStringKeyOnObject_51) {
    Object obj;
    obj["foo"] = Value("bar");
    Value v(obj);
    Value& elem = v["foo"];
    EXPECT_TRUE(elem.isString());
    EXPECT_EQ(elem.getString(), "bar");
}

TEST_F(ValueTest_51, SubscriptIndexOnArray_51) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[static_cast<size_t>(0)].getInteger(), 10);
    EXPECT_EQ(v[static_cast<size_t>(1)].getInteger(), 20);
    EXPECT_EQ(v[static_cast<size_t>(2)].getInteger(), 30);
}

// ==================== Load / Write Tests ====================

TEST_F(ValueTest_51, LoadFromString_51) {
    Value v;
    v.loadFromString("{\"name\":\"test\",\"value\":42}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["name"].getString(), "test");
    EXPECT_EQ(v["value"].getInteger(), 42);
}

TEST_F(ValueTest_51, LoadFromStream_51) {
    std::istringstream ss("[1, 2, 3]");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_51, WriteToStream_51) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(ValueTest_51, WriteToStreamString_51) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(ValueTest_51, WriteToStreamIndented_51) {
    Object obj;
    obj["a"] = Value(1);
    obj["b"] = Value(2);
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// ==================== Escape Functions ====================

TEST_F(ValueTest_51, EscapeMinimumCharacters_51) {
    std::string result = Value::escapeMinimumCharacters("hello\nworld");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_51, EscapeMinimumCharactersQuote_51) {
    std::string result = Value::escapeMinimumCharacters("say \"hi\"");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_51, EscapeAllCharacters_51) {
    std::string result = Value::escapeAllCharacters("abc");
    // Should produce some form of escaped output
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_51, EscapeToUnicode_51) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
    // Should contain \u prefix
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ==================== Boundary / Edge Cases ====================

TEST_F(ValueTest_51, EmptyStringValue_51) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_51, ZeroIntValue_51) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_51, NegativeIntValue_51) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST_F(ValueTest_51, ZeroDoubleValue_51) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_51, NegativeDoubleValue_51) {
    Value v(-3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -3.14);
}

TEST_F(ValueTest_51, LargeIntValue_51) {
    Value v(2147483647);  // INT_MAX
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST_F(ValueTest_51, EmptyObjectValue_51) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_51, EmptyArrayValue_51) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_51, GetToStringFromInt_51) {
    Value v(42);
    std::string str = v.getToString();
    EXPECT_NE(str.find("42"), std::string::npos);
}

TEST_F(ValueTest_51, GetToStringFromDouble_51) {
    Value v(3.14);
    std::string str = v.getToString();
    EXPECT_FALSE(str.empty());
}

TEST_F(ValueTest_51, GetToStringFromString_51) {
    Value v("hello");
    std::string str = v.getToString();
    EXPECT_EQ(str, "hello");
}

TEST_F(ValueTest_51, TypeChangeFromIntToString_51) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setString("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_51, TypeChangeFromStringToNull_51) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    v.setNull();
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_51, SelfAssignment_51) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_51, LoadFromStringNull_51) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_51, LoadFromStringTrue_51) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_51, LoadFromStringFalse_51) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_51, LoadFromStringNumber_51) {
    Value v;
    v.loadFromString("123");
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_51, LoadFromStringFloat_51) {
    Value v;
    v.loadFromString("1.5");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.5);
}

TEST_F(ValueTest_51, LoadFromStringArray_51) {
    Value v;
    v.loadFromString("[\"a\", \"b\", \"c\"]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_51, OutputOperator_51) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

TEST_F(ValueTest_51, NestedObject_51) {
    Value v;
    v.loadFromString("{\"outer\":{\"inner\":42}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

TEST_F(ValueTest_51, NestedArray_51) {
    Value v;
    v.loadFromString("[[1,2],[3,4]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
    EXPECT_TRUE(v[static_cast<size_t>(0)].isArray());
    EXPECT_TRUE(v[static_cast<size_t>(1)].isArray());
}

TEST_F(ValueTest_51, GetFloatFromIntegerValue_51) {
    Value v(5);
    // getFloat calls tryGetFloat; for an integer type it should return default
    float result = v.getFloat();
    EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST_F(ValueTest_51, TryGetFloatFromIntegerReturnsDefault_51) {
    Value v(5);
    float result = v.tryGetFloat(99.0f);
    EXPECT_FLOAT_EQ(result, 99.0f);
}

TEST_F(ValueTest_51, TryGetStringOnNullReturnsDefault_51) {
    Value v;
    EXPECT_EQ(v.tryGetString("fallback"), "fallback");
}

TEST_F(ValueTest_51, TryGetIntegerOnNullReturnsDefault_51) {
    Value v;
    EXPECT_EQ(v.tryGetInteger(999), 999);
}

TEST_F(ValueTest_51, TryGetDoubleOnNullReturnsDefault_51) {
    Value v;
    EXPECT_DOUBLE_EQ(v.tryGetDouble(5.5), 5.5);
}

TEST_F(ValueTest_51, TryGetBooleanOnNullReturnsDefault_51) {
    Value v;
    EXPECT_TRUE(v.tryGetBoolean(true));
    EXPECT_FALSE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_51, SubscriptCreatesNewKeyInObject_51) {
    Object obj;
    Value v(obj);
    v["newkey"] = Value(42);
    EXPECT_EQ(v["newkey"].getInteger(), 42);
}

TEST_F(ValueTest_51, WriteAndReadRoundTrip_51) {
    Object obj;
    obj["name"] = Value("test");
    obj["count"] = Value(5);
    obj["flag"] = Value(true);
    Value original(obj);

    std::ostringstream oss;
    original.writeToStream(oss, false, false);

    Value loaded;
    loaded.loadFromString(oss.str());
    EXPECT_TRUE(loaded.isObject());
    EXPECT_EQ(loaded["name"].getString(), "test");
    EXPECT_EQ(loaded["count"].getInteger(), 5);
    EXPECT_TRUE(loaded["flag"].getBoolean());
}

TEST_F(ValueTest_51, EscapeMinimumCharactersBackslash_51) {
    std::string result = Value::escapeMinimumCharacters("path\\to\\file");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST_F(ValueTest_51, EscapeMinimumCharactersTab_51) {
    std::string result = Value::escapeMinimumCharacters("col1\tcol2");
    EXPECT_NE(result.find("\\t"), std::string::npos);
}

TEST_F(ValueTest_51, VeryLargeDoubleValue_51) {
    Value v(1.0e300);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.0e300);
}

TEST_F(ValueTest_51, VerySmallDoubleValue_51) {
    Value v(1.0e-300);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.0e-300);
}
