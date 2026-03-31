#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

// ===== Construction Tests =====

TEST(ValueConstructionTest_27, DefaultConstructorCreatesNull_27) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

TEST(ValueConstructionTest_27, StringConstructor_27) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueConstructionTest_27, CStringConstructor_27) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST(ValueConstructionTest_27, IntConstructor_27) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueConstructionTest_27, DoubleConstructor_27) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST(ValueConstructionTest_27, BooleanConstructorTrue_27) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueConstructionTest_27, BooleanConstructorFalse_27) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueConstructionTest_27, ObjectConstructor_27) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST(ValueConstructionTest_27, ArrayConstructor_27) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST(ValueConstructionTest_27, CopyConstructor_27) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

TEST(ValueConstructionTest_27, EmptyStringConstructor_27) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

// ===== Type Checking Tests =====

TEST(ValueTypeTest_27, IsStringable_27) {
    Value vStr("hello");
    EXPECT_TRUE(vStr.isStringable());

    Value vInt(42);
    // Integers might be stringable depending on implementation
    // We test that isStringable doesn't crash
    vInt.isStringable();

    Value vNull;
    vNull.isStringable();
}

TEST(ValueTypeTest_27, IsNumericForInt_27) {
    Value v(10);
    EXPECT_TRUE(v.isNumeric());
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
}

TEST(ValueTypeTest_27, IsNumericForDouble_27) {
    Value v(3.14);
    EXPECT_TRUE(v.isNumeric());
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
}

TEST(ValueTypeTest_27, NullIsNotOtherTypes_27) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNumeric());
}

TEST(ValueTypeTest_27, StringIsNotOtherTypes_27) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isNull());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
}

TEST(ValueTypeTest_27, BooleanIsNotOtherTypes_27) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
}

// ===== Assignment Tests =====

TEST(ValueAssignmentTest_27, AssignValue_27) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST(ValueAssignmentTest_27, AssignString_27) {
    Value v;
    v = std::string("hello");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueAssignmentTest_27, AssignCString_27) {
    Value v;
    v = "hello";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueAssignmentTest_27, AssignInt_27) {
    Value v;
    v = 99;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST(ValueAssignmentTest_27, AssignDouble_27) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST(ValueAssignmentTest_27, AssignBool_27) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueAssignmentTest_27, AssignObject_27) {
    Value v;
    Object obj;
    obj["x"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST(ValueAssignmentTest_27, AssignArray_27) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

TEST(ValueAssignmentTest_27, ReassignDifferentType_27) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v = "now a string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

// ===== Setter Tests =====

TEST(ValueSetterTest_27, SetString_27) {
    Value v;
    v.setString("test");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

TEST(ValueSetterTest_27, SetInteger_27) {
    Value v;
    v.setInteger(100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST(ValueSetterTest_27, SetDouble_27) {
    Value v;
    v.setDouble(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.5);
}

TEST(ValueSetterTest_27, SetBoolean_27) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueSetterTest_27, SetNull_27) {
    Value v(42);
    EXPECT_FALSE(v.isNull());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST(ValueSetterTest_27, SetObject_27) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST(ValueSetterTest_27, SetArray_27) {
    Value v;
    Array arr;
    arr.push_back(Value("elem"));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

// ===== Getter Tests =====

TEST(ValueGetterTest_27, GetFloat_27) {
    Value v(3.14);
    EXPECT_NEAR(v.getFloat(), 3.14f, 0.001f);
}

TEST(ValueGetterTest_27, GetToString_27) {
    Value v(42);
    std::string s = v.getToString();
    // For integer, should produce some string representation
    EXPECT_FALSE(s.empty());
}

// ===== TryGet Tests =====

TEST(ValueTryGetTest_27, TryGetStringWhenString_27) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST(ValueTryGetTest_27, TryGetStringWhenNotString_27) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST(ValueTryGetTest_27, TryGetIntegerWhenInteger_27) {
    Value v(42);
    EXPECT_EQ(v.tryGetInteger(0), 42);
}

TEST(ValueTryGetTest_27, TryGetIntegerWhenNotInteger_27) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(99), 99);
}

TEST(ValueTryGetTest_27, TryGetDoubleWhenDouble_27) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 3.14);
}

TEST(ValueTryGetTest_27, TryGetDoubleWhenNotDouble_27) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.0), 1.0);
}

TEST(ValueTryGetTest_27, TryGetFloatWhenDouble_27) {
    Value v(2.5);
    EXPECT_NEAR(v.tryGetFloat(0.0f), 2.5f, 0.001f);
}

TEST(ValueTryGetTest_27, TryGetFloatWhenNotDouble_27) {
    Value v("hello");
    EXPECT_NEAR(v.tryGetFloat(1.0f), 1.0f, 0.001f);
}

TEST(ValueTryGetTest_27, TryGetBooleanWhenBoolean_27) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST(ValueTryGetTest_27, TryGetBooleanWhenNotBoolean_27) {
    Value v(42);
    EXPECT_TRUE(v.tryGetBoolean(true));
}

// ===== Comparison Tests =====

TEST(ValueComparisonTest_27, EqualityIntSame_27) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST(ValueComparisonTest_27, EqualityIntDifferent_27) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST(ValueComparisonTest_27, EqualityStringSame_27) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueComparisonTest_27, EqualityStringDifferent_27) {
    Value v1("abc");
    Value v2("def");
    EXPECT_FALSE(v1 == v2);
}

TEST(ValueComparisonTest_27, EqualityDifferentTypes_27) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

TEST(ValueComparisonTest_27, EqualityNullValues_27) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueComparisonTest_27, EqualityBooleans_27) {
    Value v1(true);
    Value v2(true);
    Value v3(false);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}

TEST(ValueComparisonTest_27, LessThanIntegers_27) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST(ValueComparisonTest_27, LessThanOrEqualIntegers_27) {
    Value v1(1);
    Value v2(1);
    Value v3(2);
    EXPECT_TRUE(v1 <= v2);
    EXPECT_TRUE(v1 <= v3);
    EXPECT_FALSE(v3 <= v1);
}

TEST(ValueComparisonTest_27, GreaterThanIntegers_27) {
    Value v1(2);
    Value v2(1);
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v2 > v1);
}

TEST(ValueComparisonTest_27, GreaterThanOrEqualIntegers_27) {
    Value v1(2);
    Value v2(2);
    Value v3(1);
    EXPECT_TRUE(v1 >= v2);
    EXPECT_TRUE(v1 >= v3);
    EXPECT_FALSE(v3 >= v1);
}

TEST(ValueComparisonTest_27, GreaterThanIsNegationOfLessOrEqual_27) {
    Value v1(5);
    Value v2(3);
    // operator> is defined as !(*this <= rhs)
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v1 <= v2);
}

TEST(ValueComparisonTest_27, EqualValuesNotGreaterThan_27) {
    Value v1(5);
    Value v2(5);
    EXPECT_FALSE(v1 > v2);
    EXPECT_TRUE(v1 <= v2);
}

TEST(ValueComparisonTest_27, LessThanStrings_27) {
    Value v1("abc");
    Value v2("def");
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST(ValueComparisonTest_27, GreaterThanDoubles_27) {
    Value v1(3.14);
    Value v2(2.71);
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v2 > v1);
}

// ===== Subscript Operator Tests =====

TEST(ValueSubscriptTest_27, ObjectSubscriptByString_27) {
    Value v;
    Object obj;
    obj["key"] = Value(42);
    v.setObject(obj);
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST(ValueSubscriptTest_27, ObjectSubscriptByCString_27) {
    Value v;
    Object obj;
    obj["key"] = Value("value");
    v.setObject(obj);
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST(ValueSubscriptTest_27, ArraySubscriptByIndex_27) {
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

TEST(ValueSubscriptTest_27, ObjectSubscriptCreatesEntry_27) {
    Value v;
    Object obj;
    v.setObject(obj);
    v["newKey"] = Value("newValue");
    EXPECT_EQ(v["newKey"].getString(), "newValue");
}

// ===== Serialization / Deserialization Tests =====

TEST(ValueSerializationTest_27, LoadFromStringSimpleInt_27) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueSerializationTest_27, LoadFromStringSimpleString_27) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueSerializationTest_27, LoadFromStringBoolean_27) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueSerializationTest_27, LoadFromStringNull_27) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST(ValueSerializationTest_27, LoadFromStringDouble_27) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_NEAR(v.getDouble(), 3.14, 0.001);
}

TEST(ValueSerializationTest_27, LoadFromStringObject_27) {
    Value v;
    v.loadFromString("{\"key\": 42}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST(ValueSerializationTest_27, LoadFromStringArray_27) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST(ValueSerializationTest_27, LoadFromStream_27) {
    std::istringstream iss("\"test\"");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

TEST(ValueSerializationTest_27, StreamConstructor_27) {
    std::istringstream iss("42");
    Value v(iss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueSerializationTest_27, WriteToStreamInteger_27) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST(ValueSerializationTest_27, WriteToStreamString_27) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST(ValueSerializationTest_27, WriteToStreamNull_27) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("null"), std::string::npos);
}

TEST(ValueSerializationTest_27, WriteToStreamBoolean_27) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST(ValueSerializationTest_27, WriteToStreamWithIndent_27) {
    Value v;
    v.loadFromString("{\"key\": 42}");
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST(ValueSerializationTest_27, OutputStreamOperator_27) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

// ===== Escape Tests =====

TEST(ValueEscapeTest_27, EscapeMinimumCharacters_27) {
    std::string input = "hello\nworld";
    std::string escaped = Value::escapeMinimumCharacters(input);
    EXPECT_NE(escaped.find("\\n"), std::string::npos);
}

TEST(ValueEscapeTest_27, EscapeMinimumCharactersQuote_27) {
    std::string input = "say \"hi\"";
    std::string escaped = Value::escapeMinimumCharacters(input);
    EXPECT_NE(escaped.find("\\\""), std::string::npos);
}

TEST(ValueEscapeTest_27, EscapeMinimumCharactersBackslash_27) {
    std::string input = "path\\to";
    std::string escaped = Value::escapeMinimumCharacters(input);
    EXPECT_NE(escaped.find("\\\\"), std::string::npos);
}

TEST(ValueEscapeTest_27, EscapeAllCharacters_27) {
    std::string input = "hello\nworld";
    std::string escaped = Value::escapeAllCharacters(input);
    EXPECT_FALSE(escaped.empty());
}

TEST(ValueEscapeTest_27, EscapeToUnicode_27) {
    std::string result = Value::escapeToUnicode('A');
    // Should produce something like \u0041
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

TEST(ValueEscapeTest_27, EscapeEmptyString_27) {
    std::string escaped = Value::escapeMinimumCharacters("");
    EXPECT_EQ(escaped, "");
}

// ===== Boundary / Edge Case Tests =====

TEST(ValueBoundaryTest_27, IntZero_27) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST(ValueBoundaryTest_27, NegativeInt_27) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST(ValueBoundaryTest_27, NegativeDouble_27) {
    Value v(-3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -3.14);
}

TEST(ValueBoundaryTest_27, DoubleZero_27) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST(ValueBoundaryTest_27, EmptyObject_27) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST(ValueBoundaryTest_27, EmptyArray_27) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST(ValueBoundaryTest_27, LoadFromStringEmptyObject_27) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST(ValueBoundaryTest_27, LoadFromStringEmptyArray_27) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST(ValueBoundaryTest_27, NestedObject_27) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": 42}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

TEST(ValueBoundaryTest_27, NestedArray_27) {
    Value v;
    v.loadFromString("[[1, 2], [3, 4]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST(ValueBoundaryTest_27, LargeInteger_27) {
    Value v(2147483647); // INT_MAX
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST(ValueBoundaryTest_27, NegativeLargeInteger_27) {
    Value v(-2147483647);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -2147483647);
}

// ===== Mutation Tests =====

TEST(ValueMutationTest_27, ChangeTypeFromIntToString_27) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setString("now string");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
}

TEST(ValueMutationTest_27, ChangeTypeFromStringToNull_27) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    v.setNull();
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isString());
}

TEST(ValueMutationTest_27, ChangeTypeFromBoolToInt_27) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    v.setInteger(5);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isBoolean());
}

// ===== Self-assignment Test =====

TEST(ValueSelfAssignmentTest_27, SelfAssignment_27) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

// ===== Complex JSON Tests =====

TEST(ValueComplexTest_27, LoadComplexJson_27) {
    std::string json = R"({
        "name": "test",
        "value": 42,
        "pi": 3.14,
        "active": true,
        "nothing": null,
        "tags": ["a", "b"],
        "nested": {"x": 1}
    })";
    Value v;
    v.loadFromString(json);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["name"].getString(), "test");
    EXPECT_EQ(v["value"].getInteger(), 42);
    EXPECT_TRUE(v["active"].getBoolean());
    EXPECT_TRUE(v["nothing"].isNull());
    EXPECT_TRUE(v["tags"].isArray());
    EXPECT_TRUE(v["nested"].isObject());
}

TEST(ValueComplexTest_27, RoundTrip_27) {
    Value v;
    v.loadFromString("{\"key\": 42}");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string serialized = oss.str();

    Value v2;
    v2.loadFromString(serialized);
    EXPECT_TRUE(v2.isObject());
    EXPECT_EQ(v2["key"].getInteger(), 42);
}

TEST(ValueComplexTest_27, LoadFromStringWithWhitespace_27) {
    Value v;
    v.loadFromString("  \n\t  42  ");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueComplexTest_27, WriteToStreamEscapeAll_27) {
    Value v("hello\nworld");
    std::ostringstream oss;
    v.writeToStream(oss, false, true);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST(ValueComplexTest_27, BooleanFalseLoadFromString_27) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueComplexTest_27, NegativeNumberLoadFromString_27) {
    Value v;
    v.loadFromString("-42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST(ValueComplexTest_27, NegativeDoubleLoadFromString_27) {
    Value v;
    v.loadFromString("-3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_NEAR(v.getDouble(), -3.14, 0.001);
}

// ===== GetType Tests =====

TEST(ValueGetTypeTest_27, NullType_27) {
    Value v;
    // We just verify getType doesn't crash and returns a consistent value
    auto t = v.getType();
    Value v2;
    EXPECT_EQ(t, v2.getType());
}

TEST(ValueGetTypeTest_27, DifferentTypesHaveDifferentGetType_27) {
    Value vNull;
    Value vInt(1);
    Value vStr("s");
    Value vBool(true);
    Value vDouble(1.0);

    // Different types should have different type values
    EXPECT_NE(vNull.getType(), vInt.getType());
    EXPECT_NE(vNull.getType(), vStr.getType());
    EXPECT_NE(vInt.getType(), vStr.getType());
    EXPECT_NE(vBool.getType(), vInt.getType());
}
