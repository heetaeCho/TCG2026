#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "JsonBox/Value.h"

using namespace JsonBox;

// Test fixture
class ValueTest_31 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(ValueTest_31, DefaultConstructorCreatesNullValue_31) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_31, StringConstructor_31) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_31, CStringConstructor_31) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_31, IntConstructor_31) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_31, DoubleConstructor_31) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_31, BoolConstructor_31) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_31, BoolConstructorFalse_31) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_31, ArrayConstructor_31) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_31, ObjectConstructor_31) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_31, CopyConstructor_31) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

TEST_F(ValueTest_31, EmptyStringConstructor_31) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

// ==================== Assignment Operator Tests ====================

TEST_F(ValueTest_31, AssignmentFromValue_31) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_31, AssignmentFromString_31) {
    Value v;
    v = std::string("test");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

TEST_F(ValueTest_31, AssignmentFromCString_31) {
    Value v;
    v = "test";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

TEST_F(ValueTest_31, AssignmentFromInt_31) {
    Value v;
    v = 99;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_31, AssignmentFromDouble_31) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_31, AssignmentFromBool_31) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_31, AssignmentFromObject_31) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_31, AssignmentFromArray_31) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

// ==================== Type Check Tests ====================

TEST_F(ValueTest_31, IsStringForStringValue_31) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_31, IsIntegerForIntValue_31) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_31, IsDoubleForDoubleValue_31) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_31, IsNumericForInt_31) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_31, IsNumericForDouble_31) {
    Value v(5.5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_31, IsNotNumericForString_31) {
    Value v("hello");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_31, GetTypeReturnsCorrectType_31) {
    Value vNull;
    EXPECT_EQ(vNull.getType(), Value::NULL_VALUE);

    Value vStr("test");
    EXPECT_EQ(vStr.getType(), Value::STRING);

    Value vInt(1);
    EXPECT_EQ(vInt.getType(), Value::INTEGER);

    Value vDbl(1.0);
    EXPECT_EQ(vDbl.getType(), Value::DOUBLE);

    Value vBool(true);
    EXPECT_EQ(vBool.getType(), Value::BOOLEAN);
}

// ==================== Operator[] (Array index) Tests ====================

TEST_F(ValueTest_31, ArrayIndexOperatorOnNullCreatesArray_31) {
    Value v;
    EXPECT_TRUE(v.isNull());
    v[0] = 42;
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v[0].getInteger(), 42);
}

TEST_F(ValueTest_31, ArrayIndexOperatorResizesIfNeeded_31) {
    Value v;
    v[5] = 100;
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 6u);
    EXPECT_EQ(v[5].getInteger(), 100);
}

TEST_F(ValueTest_31, ArrayIndexOperatorOnNonArrayConvertsToArray_31) {
    Value v(42); // integer
    EXPECT_TRUE(v.isInteger());
    v[0] = "hello";
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v[0].getString(), "hello");
}

TEST_F(ValueTest_31, ArrayIndexOperatorExistingIndex_31) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[0].getInteger(), 10);
    EXPECT_EQ(v[1].getInteger(), 20);
    EXPECT_EQ(v[2].getInteger(), 30);
}

TEST_F(ValueTest_31, ArrayIndexOperatorBeyondSize_31) {
    Array arr;
    arr.push_back(Value(1));
    Value v(arr);
    EXPECT_EQ(v.getArray().size(), 1u);
    v[3] = 99;
    EXPECT_EQ(v.getArray().size(), 4u);
    EXPECT_EQ(v[3].getInteger(), 99);
    // Intermediate elements should be null
    EXPECT_TRUE(v[1].isNull());
    EXPECT_TRUE(v[2].isNull());
}

TEST_F(ValueTest_31, ArrayIndexOperatorZeroOnNull_31) {
    Value v;
    v[0] = "first";
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
    EXPECT_EQ(v[0].getString(), "first");
}

TEST_F(ValueTest_31, ArrayIndexOperatorOnStringConvertsToArray_31) {
    Value v("some string");
    EXPECT_TRUE(v.isString());
    v[0] = 1;
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_31, ArrayIndexOperatorOnBoolConvertsToArray_31) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    v[2] = "test";
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

// ==================== Operator[] (Object key) Tests ====================

TEST_F(ValueTest_31, ObjectKeyOperatorOnNullCreatesObject_31) {
    Value v;
    v["key"] = "value";
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST_F(ValueTest_31, ObjectKeyOperatorWithStringKey_31) {
    Value v;
    std::string key = "mykey";
    v[key] = 42;
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v[key].getInteger(), 42);
}

TEST_F(ValueTest_31, ObjectKeyOperatorWithCStringKey_31) {
    Value v;
    v["ckey"] = 3.14;
    EXPECT_TRUE(v.isObject());
    EXPECT_DOUBLE_EQ(v["ckey"].getDouble(), 3.14);
}

TEST_F(ValueTest_31, ObjectKeyOperatorMultipleKeys_31) {
    Value v;
    v["a"] = 1;
    v["b"] = 2;
    v["c"] = 3;
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["a"].getInteger(), 1);
    EXPECT_EQ(v["b"].getInteger(), 2);
    EXPECT_EQ(v["c"].getInteger(), 3);
}

// ==================== Comparison Operator Tests ====================

TEST_F(ValueTest_31, EqualityOperator_31) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_31, InequalityOperator_31) {
    Value v1(42);
    Value v2(43);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_31, LessThanOperator_31) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_31, LessThanOrEqualOperator_31) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_31, GreaterThanOperator_31) {
    Value v1(10);
    Value v2(5);
    EXPECT_TRUE(v1 > v2);
}

TEST_F(ValueTest_31, GreaterThanOrEqualOperator_31) {
    Value v1(10);
    Value v2(10);
    EXPECT_TRUE(v1 >= v2);
}

TEST_F(ValueTest_31, EqualityBetweenDifferentTypes_31) {
    Value v1(42);
    Value v2("42");
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_31, EqualityNullValues_31) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_31, EqualityStringValues_31) {
    Value v1("hello");
    Value v2("hello");
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_31, EqualityBoolValues_31) {
    Value v1(true);
    Value v2(true);
    EXPECT_TRUE(v1 == v2);
    Value v3(false);
    EXPECT_TRUE(v1 != v3);
}

// ==================== Setter/Getter Tests ====================

TEST_F(ValueTest_31, SetStringAndGetString_31) {
    Value v;
    v.setString("test");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

TEST_F(ValueTest_31, SetIntegerAndGetInteger_31) {
    Value v;
    v.setInteger(123);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

TEST_F(ValueTest_31, SetDoubleAndGetDouble_31) {
    Value v;
    v.setDouble(1.23);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.23);
}

TEST_F(ValueTest_31, SetBooleanAndGetBoolean_31) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_31, SetNull_31) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_31, SetObjectAndGetObject_31) {
    Value v;
    Object obj;
    obj["x"] = Value(10);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_31, SetArrayAndGetArray_31) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_31, GetFloat_31) {
    Value v(3.14);
    float f = v.getFloat();
    EXPECT_NEAR(f, 3.14f, 0.001f);
}

// ==================== Try methods ====================

TEST_F(ValueTest_31, TryGetStringReturnsValueIfString_31) {
    Value v("hello");
    EXPECT_EQ(v.tryGetString("default"), "hello");
}

TEST_F(ValueTest_31, TryGetStringReturnsDefaultIfNotString_31) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_31, TryGetIntegerReturnsValueIfInteger_31) {
    Value v(42);
    EXPECT_EQ(v.tryGetInteger(0), 42);
}

TEST_F(ValueTest_31, TryGetIntegerReturnsDefaultIfNotInteger_31) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(99), 99);
}

TEST_F(ValueTest_31, TryGetDoubleReturnsValueIfDouble_31) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 3.14);
}

TEST_F(ValueTest_31, TryGetDoubleReturnsDefaultIfNotDouble_31) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.0), 1.0);
}

TEST_F(ValueTest_31, TryGetBooleanReturnsValueIfBoolean_31) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_31, TryGetBooleanReturnsDefaultIfNotBoolean_31) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_31, TryGetFloatReturnsDefaultIfNotDouble_31) {
    Value v("hello");
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.5f), 1.5f);
}

// ==================== Stringable Tests ====================

TEST_F(ValueTest_31, IsStringableForString_31) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_31, GetToStringForInt_31) {
    Value v(42);
    std::string s = v.getToString();
    EXPECT_FALSE(s.empty());
}

// ==================== Load/Write Tests ====================

TEST_F(ValueTest_31, LoadFromStringSimpleInt_31) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_31, LoadFromStringSimpleString_31) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_31, LoadFromStringBoolTrue_31) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_31, LoadFromStringBoolFalse_31) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_31, LoadFromStringNull_31) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_31, LoadFromStringArray_31) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_31, LoadFromStringObject_31) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_31, LoadFromStreamSimple_31) {
    std::istringstream iss("42");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_31, WriteToStreamSimpleInt_31) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(ValueTest_31, WriteToStreamString_31) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(ValueTest_31, WriteToStreamIndented_31) {
    Value v;
    v["key"] = "value";
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTest_31, StreamInsertionOperator_31) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

// ==================== Escape Tests ====================

TEST_F(ValueTest_31, EscapeMinimumCharacters_31) {
    std::string result = Value::escapeMinimumCharacters("hello\nworld");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_31, EscapeMinimumCharactersNoSpecial_31) {
    std::string result = Value::escapeMinimumCharacters("hello");
    EXPECT_EQ(result, "hello");
}

TEST_F(ValueTest_31, EscapeAllCharactersBasic_31) {
    std::string result = Value::escapeAllCharacters("hello");
    // Should contain escaped unicode for each character
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_31, EscapeToUnicode_31) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
    // Should start with \u
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ==================== Edge Cases ====================

TEST_F(ValueTest_31, IntegerBoundaryNegative_31) {
    Value v(-2147483647);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -2147483647);
}

TEST_F(ValueTest_31, IntegerZero_31) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_31, DoubleZero_31) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_31, DoubleNegative_31) {
    Value v(-1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -1.5);
}

TEST_F(ValueTest_31, ReassignTypesMultipleTimes_31) {
    Value v;
    v = 42;
    EXPECT_TRUE(v.isInteger());
    v = "hello";
    EXPECT_TRUE(v.isString());
    v = 3.14;
    EXPECT_TRUE(v.isDouble());
    v = true;
    EXPECT_TRUE(v.isBoolean());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_31, EmptyArrayConstruction_31) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_31, EmptyObjectConstruction_31) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_31, LoadFromStringDouble_31) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_NEAR(v.getDouble(), 3.14, 0.001);
}

TEST_F(ValueTest_31, LoadFromStringNegativeInt_31) {
    Value v;
    v.loadFromString("-42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST_F(ValueTest_31, NestedObjectViaOperator_31) {
    Value v;
    v["outer"]["inner"] = 42;
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

TEST_F(ValueTest_31, NestedArrayViaOperator_31) {
    Value v;
    v[0][0] = 1;
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v[0].isArray());
    EXPECT_EQ(v[0][0].getInteger(), 1);
}

TEST_F(ValueTest_31, ArrayIndexOperatorOnDoubleConvertsToArray_31) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    v[0] = "element";
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v[0].getString(), "element");
}

TEST_F(ValueTest_31, ArrayIndexOperatorOnObjectConvertsToArray_31) {
    Object obj;
    obj["key"] = Value("val");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    v[0] = 10;
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_31, WriteToStreamBoolean_31) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(ValueTest_31, WriteToStreamNull_31) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("null"), std::string::npos);
}

TEST_F(ValueTest_31, LoadFromStringNestedObject_31) {
    Value v;
    v.loadFromString("{\"a\": {\"b\": 1}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["a"].isObject());
    EXPECT_EQ(v["a"]["b"].getInteger(), 1);
}

TEST_F(ValueTest_31, LoadFromStringNestedArray_31) {
    Value v;
    v.loadFromString("[[1, 2], [3, 4]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
    EXPECT_TRUE(v[0].isArray());
    EXPECT_TRUE(v[1].isArray());
}

TEST_F(ValueTest_31, ConstructFromInputStream_31) {
    std::istringstream iss("\"hello\"");
    Value v(iss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_31, WriteToStreamEscapeAll_31) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, true);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTest_31, SelfAssignment_31) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_31, EscapeMinimumCharactersQuote_31) {
    std::string result = Value::escapeMinimumCharacters("he\"llo");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_31, EscapeMinimumCharactersBackslash_31) {
    std::string result = Value::escapeMinimumCharacters("he\\llo");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST_F(ValueTest_31, EscapeMinimumCharactersTab_31) {
    std::string result = Value::escapeMinimumCharacters("he\tllo");
    EXPECT_NE(result.find("\\t"), std::string::npos);
}
