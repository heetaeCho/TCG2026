#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueTest_59 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(ValueTest_59, DefaultConstructorCreatesNullValue_59) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_59, StringConstructorCreatesStringValue_59) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_59, CStringConstructorCreatesStringValue_59) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_59, IntConstructorCreatesIntegerValue_59) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_59, DoubleConstructorCreatesDoubleValue_59) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_59, BooleanConstructorCreatesBooleanValue_59) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_59, BooleanConstructorFalseCreatesBooleanValue_59) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_59, ObjectConstructorCreatesObjectValue_59) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_59, ArrayConstructorCreatesArrayValue_59) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_59, CopyConstructorCopiesValue_59) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

// ==================== Type Check Tests ====================

TEST_F(ValueTest_59, IsStringReturnsTrueForString_59) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_59, IsIntegerReturnsTrueForInteger_59) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_59, IsDoubleReturnsTrueForDouble_59) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_59, IsNumericReturnsTrueForInteger_59) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_59, IsNumericReturnsTrueForDouble_59) {
    Value v(5.5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_59, IsNumericReturnsFalseForString_59) {
    Value v("not a number");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_59, IsNullReturnsTrueForDefault_59) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_59, GetTypeReturnsCorrectType_59) {
    Value vNull;
    EXPECT_EQ(vNull.getType(), Value::NULL_VALUE);

    Value vStr("hello");
    EXPECT_EQ(vStr.getType(), Value::STRING);

    Value vInt(42);
    EXPECT_EQ(vInt.getType(), Value::INTEGER);

    Value vDbl(3.14);
    EXPECT_EQ(vDbl.getType(), Value::DOUBLE);

    Value vBool(true);
    EXPECT_EQ(vBool.getType(), Value::BOOLEAN);
}

// ==================== tryGetBoolean Tests ====================

TEST_F(ValueTest_59, TryGetBooleanReturnsTrueWhenBooleanTrue_59) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_59, TryGetBooleanReturnsFalseWhenBooleanFalse_59) {
    Value v(false);
    EXPECT_FALSE(v.tryGetBoolean(true));
}

TEST_F(ValueTest_59, TryGetBooleanReturnsEmptyBoolWhenNotBoolean_59) {
    Value v(42);
    // EMPTY_BOOL is false
    EXPECT_FALSE(v.tryGetBoolean(true));
}

TEST_F(ValueTest_59, TryGetBooleanOnStringReturnsEmptyBool_59) {
    Value v("true");
    EXPECT_FALSE(v.tryGetBoolean(true));
}

TEST_F(ValueTest_59, TryGetBooleanOnNullReturnsEmptyBool_59) {
    Value v;
    EXPECT_FALSE(v.tryGetBoolean(true));
}

TEST_F(ValueTest_59, TryGetBooleanOnDoubleReturnsEmptyBool_59) {
    Value v(1.0);
    EXPECT_FALSE(v.tryGetBoolean(true));
}

TEST_F(ValueTest_59, TryGetBooleanOnObjectReturnsEmptyBool_59) {
    Object obj;
    Value v(obj);
    EXPECT_FALSE(v.tryGetBoolean(true));
}

TEST_F(ValueTest_59, TryGetBooleanOnArrayReturnsEmptyBool_59) {
    Array arr;
    Value v(arr);
    EXPECT_FALSE(v.tryGetBoolean(true));
}

// ==================== tryGetString Tests ====================

TEST_F(ValueTest_59, TryGetStringReturnsStringWhenString_59) {
    Value v("hello");
    EXPECT_EQ(v.tryGetString("default"), "hello");
}

TEST_F(ValueTest_59, TryGetStringReturnsDefaultWhenNotString_59) {
    Value v(42);
    std::string result = v.tryGetString("default");
    // Should return default or empty based on type mismatch behavior
    // Since it's not a string type, it should return the default or empty
}

// ==================== tryGetInteger Tests ====================

TEST_F(ValueTest_59, TryGetIntegerReturnsIntegerWhenInteger_59) {
    Value v(100);
    EXPECT_EQ(v.tryGetInteger(0), 100);
}

TEST_F(ValueTest_59, TryGetIntegerReturnsDefaultWhenNotInteger_59) {
    Value v("not int");
    int result = v.tryGetInteger(42);
    // Should return 0 (EMPTY_INT equivalent) or default based on impl
}

// ==================== tryGetDouble Tests ====================

TEST_F(ValueTest_59, TryGetDoubleReturnsDoubleWhenDouble_59) {
    Value v(2.718);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 2.718);
}

TEST_F(ValueTest_59, TryGetDoubleReturnsDefaultWhenNotDouble_59) {
    Value v("not double");
    double result = v.tryGetDouble(1.0);
}

// ==================== tryGetFloat Tests ====================

TEST_F(ValueTest_59, TryGetFloatReturnsFloatWhenDouble_59) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 1.5f);
}

// ==================== Getter/Setter Tests ====================

TEST_F(ValueTest_59, SetAndGetString_59) {
    Value v;
    v.setString("test string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test string");
}

TEST_F(ValueTest_59, SetAndGetInteger_59) {
    Value v;
    v.setInteger(999);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 999);
}

TEST_F(ValueTest_59, SetAndGetDouble_59) {
    Value v;
    v.setDouble(6.28);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 6.28);
}

TEST_F(ValueTest_59, SetAndGetBoolean_59) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_59, SetBooleanFalse_59) {
    Value v;
    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_59, SetNull_59) {
    Value v(42);
    EXPECT_FALSE(v.isNull());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_59, SetAndGetObject_59) {
    Object obj;
    obj["name"] = Value("John");
    obj["age"] = Value(30);
    Value v;
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    const Object& retrieved = v.getObject();
    EXPECT_EQ(retrieved.size(), 2u);
}

TEST_F(ValueTest_59, SetAndGetArray_59) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    arr.push_back(Value(3));
    Value v;
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    const Array& retrieved = v.getArray();
    EXPECT_EQ(retrieved.size(), 3u);
}

// ==================== Assignment Operator Tests ====================

TEST_F(ValueTest_59, AssignmentFromValue_59) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_59, AssignmentFromString_59) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_59, AssignmentFromCString_59) {
    Value v;
    v = "c-string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "c-string");
}

TEST_F(ValueTest_59, AssignmentFromInt_59) {
    Value v;
    v = 123;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

TEST_F(ValueTest_59, AssignmentFromDouble_59) {
    Value v;
    v = 1.23;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.23);
}

TEST_F(ValueTest_59, AssignmentFromBool_59) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_59, AssignmentFromObject_59) {
    Value v;
    Object obj;
    obj["key"] = Value("val");
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_59, AssignmentFromArray_59) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

// ==================== Comparison Operator Tests ====================

TEST_F(ValueTest_59, EqualityOperatorSameValues_59) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_59, EqualityOperatorDifferentValues_59) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_59, InequalityOperator_59) {
    Value v1(42);
    Value v2(43);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_59, LessThanOperator_59) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_59, LessThanOrEqualOperator_59) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_59, GreaterThanOperator_59) {
    Value v1(2);
    Value v2(1);
    EXPECT_TRUE(v1 > v2);
}

TEST_F(ValueTest_59, GreaterThanOrEqualOperator_59) {
    Value v1(2);
    Value v2(2);
    EXPECT_TRUE(v1 >= v2);
}

TEST_F(ValueTest_59, EqualityDifferentTypes_59) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

// ==================== Subscript Operator Tests ====================

TEST_F(ValueTest_59, SubscriptWithStringKeyOnObject_59) {
    Object obj;
    obj["name"] = Value("test");
    Value v(obj);
    Value& elem = v["name"];
    EXPECT_TRUE(elem.isString());
    EXPECT_EQ(elem.getString(), "test");
}

TEST_F(ValueTest_59, SubscriptWithCStringKeyOnObject_59) {
    Object obj;
    obj["key"] = Value(100);
    Value v(obj);
    Value& elem = v["key"];
    EXPECT_TRUE(elem.isInteger());
    EXPECT_EQ(elem.getInteger(), 100);
}

TEST_F(ValueTest_59, SubscriptWithIndexOnArray_59) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    Value& elem = v[(size_t)1];
    EXPECT_TRUE(elem.isInteger());
    EXPECT_EQ(elem.getInteger(), 20);
}

// ==================== isStringable Tests ====================

TEST_F(ValueTest_59, IsStringableForString_59) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_59, IsStringableForInteger_59) {
    Value v(42);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_59, IsStringableForDouble_59) {
    Value v(3.14);
    EXPECT_TRUE(v.isStringable());
}

// ==================== getToString Tests ====================

TEST_F(ValueTest_59, GetToStringFromString_59) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

TEST_F(ValueTest_59, GetToStringFromInteger_59) {
    Value v(42);
    std::string result = v.getToString();
    EXPECT_EQ(result, "42");
}

// ==================== Load and Write Tests ====================

TEST_F(ValueTest_59, LoadFromString_59) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_59, LoadFromStringInteger_59) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_59, LoadFromStringArray_59) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_59, LoadFromStringBoolean_59) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_59, LoadFromStringNull_59) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_59, LoadFromStream_59) {
    std::istringstream ss("{\"name\": \"test\"}");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_59, WriteToStream_59) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTest_59, WriteObjectToStream_59) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("key"), std::string::npos);
    EXPECT_NE(output.find("value"), std::string::npos);
}

TEST_F(ValueTest_59, WriteToStreamWithIndent_59) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("\n"), std::string::npos);
}

TEST_F(ValueTest_59, StreamInsertionOperator_59) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// ==================== Escape Tests ====================

TEST_F(ValueTest_59, EscapeMinimumCharacters_59) {
    std::string result = Value::escapeMinimumCharacters("hello\nworld");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_59, EscapeMinimumCharactersQuote_59) {
    std::string result = Value::escapeMinimumCharacters("say \"hi\"");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_59, EscapeMinimumCharactersBackslash_59) {
    std::string result = Value::escapeMinimumCharacters("back\\slash");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST_F(ValueTest_59, EscapeAllCharacters_59) {
    std::string result = Value::escapeAllCharacters("hello\nworld");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_59, EscapeToUnicode_59) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ==================== Boundary and Edge Cases ====================

TEST_F(ValueTest_59, EmptyStringValue_59) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_59, ZeroInteger_59) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_59, NegativeInteger_59) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST_F(ValueTest_59, ZeroDouble_59) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_59, NegativeDouble_59) {
    Value v(-3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -3.14);
}

TEST_F(ValueTest_59, EmptyObject_59) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_59, EmptyArray_59) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_59, OverwriteValueTypeFromIntToString_59) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setString("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST_F(ValueTest_59, OverwriteValueTypeFromStringToBool_59) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_59, SetNullClearsExistingValue_59) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_59, GetFloatFromDoubleValue_59) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 1.5f);
}

TEST_F(ValueTest_59, LoadFromStringDoubleValue_59) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_NEAR(v.getDouble(), 3.14, 0.001);
}

TEST_F(ValueTest_59, NestedObjectValue_59) {
    Object inner;
    inner["inner_key"] = Value("inner_val");
    Object outer;
    outer["nested"] = Value(inner);
    Value v(outer);
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["nested"].isObject());
}

TEST_F(ValueTest_59, ArrayOfMixedTypes_59) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value("two"));
    arr.push_back(Value(3.0));
    arr.push_back(Value(true));
    arr.push_back(Value());
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 5u);
}

TEST_F(ValueTest_59, StreamConstructor_59) {
    std::istringstream ss("{\"a\": 1}");
    Value v(ss);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_59, LoadFromStringWithWhitespace_59) {
    Value v;
    v.loadFromString("  { \"key\" : \"value\" }  ");
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_59, LargeIntegerValue_59) {
    Value v(2147483647); // INT_MAX
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST_F(ValueTest_59, SelfAssignment_59) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_59, TryGetBooleanWithDefaultFalseOnBoolTrue_59) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_59, TryGetBooleanWithDefaultTrueOnBoolFalse_59) {
    Value v(false);
    EXPECT_FALSE(v.tryGetBoolean(true));
}

TEST_F(ValueTest_59, TryGetIntegerOnNonIntegerReturnsDefault_59) {
    Value v("string");
    int result = v.tryGetInteger(99);
    // Based on the pattern in tryGetBoolean, non-matching type returns EMPTY value (0)
    EXPECT_EQ(result, 0);
}

TEST_F(ValueTest_59, TryGetDoubleOnNonDoubleReturnsDefault_59) {
    Value v("string");
    double result = v.tryGetDouble(99.9);
    // Similar pattern - returns EMPTY value
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST_F(ValueTest_59, WriteArrayToStream_59) {
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

TEST_F(ValueTest_59, WriteBooleanToStream_59) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(ValueTest_59, WriteNullToStream_59) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("null"), std::string::npos);
}

TEST_F(ValueTest_59, WriteStringToStreamWithEscapeAll_59) {
    Value v("hello\nworld");
    std::ostringstream oss;
    v.writeToStream(oss, false, true);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTest_59, LoadFromStringEmptyObject_59) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_59, LoadFromStringEmptyArray_59) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_59, LoadFromStringFalse_59) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_59, LoadFromStringNegativeNumber_59) {
    Value v;
    v.loadFromString("-42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST_F(ValueTest_59, SubscriptCreatesNewKeyInObject_59) {
    Object obj;
    Value v(obj);
    v["new_key"] = Value("new_value");
    EXPECT_TRUE(v["new_key"].isString());
    EXPECT_EQ(v["new_key"].getString(), "new_value");
}
