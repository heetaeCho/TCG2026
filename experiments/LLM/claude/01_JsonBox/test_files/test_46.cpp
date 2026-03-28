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
class ValueTest_46 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Construction Tests
// ============================================================

TEST_F(ValueTest_46, DefaultConstructor_IsNull_46) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_46, StringConstructor_46) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_46, CStringConstructor_46) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_46, IntConstructor_46) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_46, IntConstructorNegative_46) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST_F(ValueTest_46, IntConstructorZero_46) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_46, DoubleConstructor_46) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_46, BooleanConstructorTrue_46) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_46, BooleanConstructorFalse_46) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_46, ObjectConstructor_46) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_46, ArrayConstructor_46) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_46, CopyConstructor_46) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

TEST_F(ValueTest_46, CopyConstructorString_46) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "test");
}

TEST_F(ValueTest_46, CopyConstructorNull_46) {
    Value original;
    Value copy(original);
    EXPECT_TRUE(copy.isNull());
}

// ============================================================
// Type Checking Tests
// ============================================================

TEST_F(ValueTest_46, IsStringForString_46) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueTest_46, IsIntegerForInt_46) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_46, IsDoubleForDouble_46) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_46, IsNumericForInt_46) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_46, IsNumericForDouble_46) {
    Value v(5.5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_46, IsNumericForString_46) {
    Value v("notanumber");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_46, IsStringableForString_46) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_46, IsStringableForInt_46) {
    Value v(42);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_46, IsStringableForDouble_46) {
    Value v(3.14);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_46, IsNullForNull_46) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
}

// ============================================================
// getInteger / tryGetInteger Tests
// ============================================================

TEST_F(ValueTest_46, GetIntegerFromIntValue_46) {
    Value v(99);
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_46, GetIntegerFromNonIntValue_ReturnsDefault_46) {
    Value v("hello");
    // getInteger calls tryGetInteger(EMPTY_INT) which is 0
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_46, TryGetIntegerFromIntValue_46) {
    Value v(55);
    EXPECT_EQ(v.tryGetInteger(-1), 55);
}

TEST_F(ValueTest_46, TryGetIntegerFromNonIntValue_ReturnsDefault_46) {
    Value v("not an int");
    EXPECT_EQ(v.tryGetInteger(999), 999);
}

TEST_F(ValueTest_46, TryGetIntegerFromNull_ReturnsDefault_46) {
    Value v;
    EXPECT_EQ(v.tryGetInteger(42), 42);
}

TEST_F(ValueTest_46, TryGetIntegerFromBool_ReturnsDefault_46) {
    Value v(true);
    EXPECT_EQ(v.tryGetInteger(77), 77);
}

TEST_F(ValueTest_46, TryGetIntegerFromDouble_ReturnsDefault_46) {
    Value v(3.14);
    EXPECT_EQ(v.tryGetInteger(88), 88);
}

TEST_F(ValueTest_46, GetIntegerMaxValue_46) {
    Value v(std::numeric_limits<int>::max());
    EXPECT_EQ(v.getInteger(), std::numeric_limits<int>::max());
}

TEST_F(ValueTest_46, GetIntegerMinValue_46) {
    Value v(std::numeric_limits<int>::min());
    EXPECT_EQ(v.getInteger(), std::numeric_limits<int>::min());
}

// ============================================================
// getString / tryGetString Tests
// ============================================================

TEST_F(ValueTest_46, GetStringFromStringValue_46) {
    Value v("test string");
    EXPECT_EQ(v.getString(), "test string");
}

TEST_F(ValueTest_46, TryGetStringFromStringValue_46) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST_F(ValueTest_46, TryGetStringFromNonStringValue_46) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_46, TryGetStringFromNull_46) {
    Value v;
    EXPECT_EQ(v.tryGetString("fallback"), "fallback");
}

TEST_F(ValueTest_46, GetStringEmpty_46) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

// ============================================================
// getDouble / tryGetDouble / getFloat / tryGetFloat Tests
// ============================================================

TEST_F(ValueTest_46, GetDoubleFromDoubleValue_46) {
    Value v(2.718);
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_46, TryGetDoubleFromNonDouble_46) {
    Value v("string");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.0), 1.0);
}

TEST_F(ValueTest_46, GetFloatFromDoubleValue_46) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 1.5f);
}

TEST_F(ValueTest_46, TryGetFloatFromNonDouble_46) {
    Value v;
    EXPECT_FLOAT_EQ(v.tryGetFloat(2.5f), 2.5f);
}

// ============================================================
// getBoolean / tryGetBoolean Tests
// ============================================================

TEST_F(ValueTest_46, GetBooleanTrue_46) {
    Value v(true);
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_46, GetBooleanFalse_46) {
    Value v(false);
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_46, TryGetBooleanFromNonBool_46) {
    Value v(42);
    EXPECT_TRUE(v.tryGetBoolean(true));
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ============================================================
// Setter Tests
// ============================================================

TEST_F(ValueTest_46, SetString_46) {
    Value v;
    v.setString("new string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "new string");
}

TEST_F(ValueTest_46, SetInteger_46) {
    Value v;
    v.setInteger(123);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

TEST_F(ValueTest_46, SetDouble_46) {
    Value v;
    v.setDouble(9.81);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 9.81);
}

TEST_F(ValueTest_46, SetBoolean_46) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_46, SetNull_46) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_46, SetObject_46) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_46, SetArray_46) {
    Value v;
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

// ============================================================
// Assignment Operator Tests
// ============================================================

TEST_F(ValueTest_46, AssignmentFromValue_46) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_46, AssignmentFromString_46) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_46, AssignmentFromCString_46) {
    Value v;
    v = "c-string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "c-string");
}

TEST_F(ValueTest_46, AssignmentFromInt_46) {
    Value v;
    v = 777;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 777);
}

TEST_F(ValueTest_46, AssignmentFromDouble_46) {
    Value v;
    v = 6.28;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 6.28);
}

TEST_F(ValueTest_46, AssignmentFromBool_46) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_46, AssignmentFromObject_46) {
    Value v;
    Object obj;
    obj["x"] = Value(10);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_46, AssignmentFromArray_46) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

// ============================================================
// Operator[] Tests
// ============================================================

TEST_F(ValueTest_46, ObjectSubscriptOperatorString_46) {
    Value v;
    Object obj;
    obj["key1"] = Value("val1");
    v.setObject(obj);
    EXPECT_EQ(v["key1"].getString(), "val1");
}

TEST_F(ValueTest_46, ObjectSubscriptOperatorCString_46) {
    Value v;
    Object obj;
    obj["key2"] = Value(42);
    v.setObject(obj);
    EXPECT_EQ(v["key2"].getInteger(), 42);
}

TEST_F(ValueTest_46, ArraySubscriptOperator_46) {
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
// Comparison Operator Tests
// ============================================================

TEST_F(ValueTest_46, EqualityOperator_SameInt_46) {
    Value v1(10);
    Value v2(10);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueTest_46, EqualityOperator_DifferentInt_46) {
    Value v1(10);
    Value v2(20);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_46, EqualityOperator_DifferentTypes_46) {
    Value v1(10);
    Value v2("10");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_46, LessThanOperator_Integers_46) {
    Value v1(5);
    Value v2(10);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_46, LessThanOrEqualOperator_46) {
    Value v1(5);
    Value v2(5);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_46, GreaterThanOperator_46) {
    Value v1(10);
    Value v2(5);
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v2 > v1);
}

TEST_F(ValueTest_46, GreaterThanOrEqualOperator_46) {
    Value v1(10);
    Value v2(10);
    EXPECT_TRUE(v1 >= v2);
}

TEST_F(ValueTest_46, EqualityNullValues_46) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_46, EqualityStrings_46) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_46, EqualityBooleans_46) {
    Value v1(true);
    Value v2(true);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_46, InequalityBooleans_46) {
    Value v1(true);
    Value v2(false);
    EXPECT_TRUE(v1 != v2);
}

// ============================================================
// Type Change Tests
// ============================================================

TEST_F(ValueTest_46, TypeChangeFromIntToString_46) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setString("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST_F(ValueTest_46, TypeChangeFromStringToNull_46) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_46, TypeChangeFromNullToInt_46) {
    Value v;
    EXPECT_TRUE(v.isNull());
    v.setInteger(100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

// ============================================================
// loadFromString / writeToStream Tests
// ============================================================

TEST_F(ValueTest_46, LoadFromStringSimpleInt_46) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_46, LoadFromStringSimpleString_46) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_46, LoadFromStringBoolean_46) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_46, LoadFromStringNull_46) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_46, LoadFromStringObject_46) {
    Value v;
    v.loadFromString("{\"key\": 123}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getInteger(), 123);
}

TEST_F(ValueTest_46, LoadFromStringArray_46) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_46, LoadFromStringDouble_46) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_NEAR(v.getDouble(), 3.14, 0.001);
}

TEST_F(ValueTest_46, LoadFromStringNegativeInt_46) {
    Value v;
    v.loadFromString("-99");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -99);
}

TEST_F(ValueTest_46, WriteToStream_Integer_46) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "42");
}

TEST_F(ValueTest_46, WriteToStream_String_46) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "\"hello\"");
}

TEST_F(ValueTest_46, WriteToStream_Null_46) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "null");
}

TEST_F(ValueTest_46, WriteToStream_Boolean_46) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "true");
}

TEST_F(ValueTest_46, WriteToStream_BooleanFalse_46) {
    Value v(false);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "false");
}

// ============================================================
// loadFromStream Tests
// ============================================================

TEST_F(ValueTest_46, LoadFromStream_46) {
    std::istringstream iss("{\"name\": \"test\"}");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["name"].getString(), "test");
}

TEST_F(ValueTest_46, ConstructFromStream_46) {
    std::istringstream iss("123");
    Value v(iss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

// ============================================================
// Stream insertion operator Tests
// ============================================================

TEST_F(ValueTest_46, StreamInsertionOperator_46) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    // The output should contain "42"
    EXPECT_NE(oss.str().find("42"), std::string::npos);
}

// ============================================================
// getToString Tests
// ============================================================

TEST_F(ValueTest_46, GetToStringFromInt_46) {
    Value v(42);
    std::string result = v.getToString();
    EXPECT_EQ(result, "42");
}

TEST_F(ValueTest_46, GetToStringFromString_46) {
    Value v("hello");
    std::string result = v.getToString();
    EXPECT_EQ(result, "hello");
}

// ============================================================
// Escape function tests
// ============================================================

TEST_F(ValueTest_46, EscapeMinimumCharacters_46) {
    std::string input = "hello\nworld";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_46, EscapeAllCharacters_Basic_46) {
    std::string input = "ab";
    std::string result = Value::escapeAllCharacters(input);
    // Should contain unicode escapes for each character
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_46, EscapeToUnicode_46) {
    std::string result = Value::escapeToUnicode('A');
    // Should produce a unicode escape string like \u0041
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ============================================================
// Complex / Nested JSON Tests
// ============================================================

TEST_F(ValueTest_46, NestedObjectAccess_46) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": 42}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

TEST_F(ValueTest_46, NestedArrayAccess_46) {
    Value v;
    v.loadFromString("[[1, 2], [3, 4]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_46, EmptyObject_46) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_46, EmptyArray_46) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_46, EmptyString_46) {
    Value v;
    v.loadFromString("\"\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

// ============================================================
// Boundary: Large integer values
// ============================================================

TEST_F(ValueTest_46, LargePositiveInteger_46) {
    Value v(2147483647);  // INT_MAX
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST_F(ValueTest_46, LargeNegativeInteger_46) {
    Value v(-2147483647);
    EXPECT_EQ(v.getInteger(), -2147483647);
}

// ============================================================
// getObject / getArray on correct types
// ============================================================

TEST_F(ValueTest_46, GetObjectReturnsCorrectData_46) {
    Object obj;
    obj["a"] = Value(1);
    obj["b"] = Value(2);
    Value v(obj);
    const Object& retrieved = v.getObject();
    EXPECT_EQ(retrieved.size(), 2u);
    EXPECT_EQ(retrieved.at("a").getInteger(), 1);
    EXPECT_EQ(retrieved.at("b").getInteger(), 2);
}

TEST_F(ValueTest_46, GetArrayReturnsCorrectData_46) {
    Array arr;
    arr.push_back(Value("first"));
    arr.push_back(Value("second"));
    Value v(arr);
    const Array& retrieved = v.getArray();
    EXPECT_EQ(retrieved.size(), 2u);
    EXPECT_EQ(retrieved[0].getString(), "first");
    EXPECT_EQ(retrieved[1].getString(), "second");
}

// ============================================================
// Round-trip test: write then read
// ============================================================

TEST_F(ValueTest_46, RoundTripWriteRead_46) {
    Value original;
    Object obj;
    obj["name"] = Value("JsonBox");
    obj["version"] = Value(1);
    obj["active"] = Value(true);
    original.setObject(obj);

    std::ostringstream oss;
    original.writeToStream(oss, false, false);

    Value parsed;
    parsed.loadFromString(oss.str());

    EXPECT_TRUE(parsed.isObject());
    EXPECT_EQ(parsed["name"].getString(), "JsonBox");
    EXPECT_EQ(parsed["version"].getInteger(), 1);
    EXPECT_TRUE(parsed["active"].getBoolean());
}

// ============================================================
// getType Tests
// ============================================================

TEST_F(ValueTest_46, GetTypeNull_46) {
    Value v;
    // Just verify getType() is callable; the enum value for NULL_VALUE
    // We check through isNull
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_46, GetTypeConsistency_46) {
    Value v(42);
    auto t = v.getType();
    v.setString("now string");
    auto t2 = v.getType();
    EXPECT_NE(t, t2);
}

// ============================================================
// Self-assignment
// ============================================================

TEST_F(ValueTest_46, SelfAssignment_46) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

// ============================================================
// Multiple type changes
// ============================================================

TEST_F(ValueTest_46, MultipleTypeChanges_46) {
    Value v;
    EXPECT_TRUE(v.isNull());

    v.setInteger(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 10);

    v.setString("hello");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");

    v.setDouble(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.5);

    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());

    v.setNull();
    EXPECT_TRUE(v.isNull());
}

// ============================================================
// String with special characters
// ============================================================

TEST_F(ValueTest_46, StringWithSpecialCharsRoundTrip_46) {
    Value v;
    v.loadFromString("\"hello\\nworld\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello\nworld");
}

TEST_F(ValueTest_46, StringWithQuotesRoundTrip_46) {
    Value v;
    v.loadFromString("\"hello\\\"world\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello\"world");
}

TEST_F(ValueTest_46, StringWithBackslashRoundTrip_46) {
    Value v;
    v.loadFromString("\"hello\\\\world\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello\\world");
}
