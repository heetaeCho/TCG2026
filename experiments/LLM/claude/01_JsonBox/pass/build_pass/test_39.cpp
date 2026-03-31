#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueTest_39 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(ValueTest_39, DefaultConstructorCreatesNull_39) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_39, StringConstructor_39) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_39, CStringConstructor_39) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_39, IntConstructor_39) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_39, DoubleConstructor_39) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_39, BooleanConstructorTrue_39) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_39, BooleanConstructorFalse_39) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_39, ObjectConstructor_39) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_39, ArrayConstructor_39) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_39, CopyConstructor_39) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "test");
}

TEST_F(ValueTest_39, StreamConstructor_39) {
    std::istringstream input("\"hello\"");
    Value v(input);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

// ==================== Type Checking Tests ====================

TEST_F(ValueTest_39, IsStringReturnsTrueForString_39) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_39, IsIntegerReturnsTrueForInt_39) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_39, IsDoubleReturnsTrueForDouble_39) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_39, IsObjectReturnsTrueForObject_39) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueTest_39, IsArrayReturnsTrueForArray_39) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_FALSE(v.isObject());
}

TEST_F(ValueTest_39, IsBooleanReturnsTrueForBool_39) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_39, IsNullReturnsTrueForDefault_39) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
}

TEST_F(ValueTest_39, IsNumericForInteger_39) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_39, IsNumericForDouble_39) {
    Value v(5.0);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_39, IsNumericFalseForString_39) {
    Value v("hello");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_39, IsStringableForString_39) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_39, IsStringableForInteger_39) {
    Value v(42);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_39, IsStringableForDouble_39) {
    Value v(3.14);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_39, IsStringableForBoolean_39) {
    Value v(true);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_39, IsStringableForNull_39) {
    Value v;
    EXPECT_TRUE(v.isStringable());
}

// ==================== GetType Tests ====================

TEST_F(ValueTest_39, GetTypeString_39) {
    Value v("test");
    EXPECT_EQ(v.getType(), Value::STRING);
}

TEST_F(ValueTest_39, GetTypeInteger_39) {
    Value v(42);
    EXPECT_EQ(v.getType(), Value::INTEGER);
}

TEST_F(ValueTest_39, GetTypeDouble_39) {
    Value v(3.14);
    EXPECT_EQ(v.getType(), Value::DOUBLE);
}

TEST_F(ValueTest_39, GetTypeObject_39) {
    Object obj;
    Value v(obj);
    EXPECT_EQ(v.getType(), Value::OBJECT);
}

TEST_F(ValueTest_39, GetTypeArray_39) {
    Array arr;
    Value v(arr);
    EXPECT_EQ(v.getType(), Value::ARRAY);
}

TEST_F(ValueTest_39, GetTypeBoolean_39) {
    Value v(true);
    EXPECT_EQ(v.getType(), Value::BOOLEAN);
}

TEST_F(ValueTest_39, GetTypeNull_39) {
    Value v;
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

// ==================== Getter Tests ====================

TEST_F(ValueTest_39, GetStringReturnsCorrectValue_39) {
    Value v("test string");
    EXPECT_EQ(v.getString(), "test string");
}

TEST_F(ValueTest_39, GetIntegerReturnsCorrectValue_39) {
    Value v(100);
    EXPECT_EQ(v.getInteger(), 100);
}

TEST_F(ValueTest_39, GetDoubleReturnsCorrectValue_39) {
    Value v(2.718);
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_39, GetFloatReturnsCorrectValue_39) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 1.5f);
}

TEST_F(ValueTest_39, GetBooleanReturnsCorrectValue_39) {
    Value v(true);
    EXPECT_TRUE(v.getBoolean());

    Value v2(false);
    EXPECT_FALSE(v2.getBoolean());
}

TEST_F(ValueTest_39, GetObjectReturnsCorrectValue_39) {
    Object obj;
    obj["a"] = Value(1);
    obj["b"] = Value(2);
    Value v(obj);
    const Object& retrieved = v.getObject();
    EXPECT_EQ(retrieved.size(), 2u);
}

TEST_F(ValueTest_39, GetArrayReturnsCorrectValue_39) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    arr.push_back(Value(3));
    Value v(arr);
    const Array& retrieved = v.getArray();
    EXPECT_EQ(retrieved.size(), 3u);
}

// ==================== TryGet Tests ====================

TEST_F(ValueTest_39, TryGetStringReturnsValueWhenString_39) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST_F(ValueTest_39, TryGetStringReturnsDefaultWhenNotString_39) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_39, TryGetIntegerReturnsValueWhenInteger_39) {
    Value v(99);
    EXPECT_EQ(v.tryGetInteger(0), 99);
}

TEST_F(ValueTest_39, TryGetIntegerReturnsDefaultWhenNotInteger_39) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(0), 0);
}

TEST_F(ValueTest_39, TryGetDoubleReturnsValueWhenDouble_39) {
    Value v(1.23);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 1.23);
}

TEST_F(ValueTest_39, TryGetDoubleReturnsDefaultWhenNotDouble_39) {
    Value v("test");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(9.99), 9.99);
}

TEST_F(ValueTest_39, TryGetFloatReturnsValueWhenDouble_39) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 1.5f);
}

TEST_F(ValueTest_39, TryGetFloatReturnsDefaultWhenNotDouble_39) {
    Value v("test");
    EXPECT_FLOAT_EQ(v.tryGetFloat(3.0f), 3.0f);
}

TEST_F(ValueTest_39, TryGetBooleanReturnsValueWhenBoolean_39) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_39, TryGetBooleanReturnsDefaultWhenNotBoolean_39) {
    Value v(42);
    EXPECT_TRUE(v.tryGetBoolean(true));
}

// ==================== Setter Tests ====================

TEST_F(ValueTest_39, SetString_39) {
    Value v;
    v.setString("new string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "new string");
}

TEST_F(ValueTest_39, SetInteger_39) {
    Value v;
    v.setInteger(777);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 777);
}

TEST_F(ValueTest_39, SetDouble_39) {
    Value v;
    v.setDouble(6.28);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 6.28);
}

TEST_F(ValueTest_39, SetObject_39) {
    Value v;
    Object obj;
    obj["x"] = Value(1);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_39, SetArray_39) {
    Value v;
    Array arr;
    arr.push_back(Value(10));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

TEST_F(ValueTest_39, SetBoolean_39) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_39, SetNull_39) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

// ==================== Assignment Operator Tests ====================

TEST_F(ValueTest_39, AssignmentFromValue_39) {
    Value v1("hello");
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isString());
    EXPECT_EQ(v2.getString(), "hello");
}

TEST_F(ValueTest_39, AssignmentFromString_39) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_39, AssignmentFromCString_39) {
    Value v;
    v = "c_string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "c_string");
}

TEST_F(ValueTest_39, AssignmentFromInt_39) {
    Value v;
    v = 123;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

TEST_F(ValueTest_39, AssignmentFromDouble_39) {
    Value v;
    v = 9.81;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 9.81);
}

TEST_F(ValueTest_39, AssignmentFromObject_39) {
    Value v;
    Object obj;
    obj["key"] = Value("val");
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_39, AssignmentFromArray_39) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_39, AssignmentFromBool_39) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

// ==================== Comparison Operator Tests ====================

TEST_F(ValueTest_39, EqualityOperatorSameValues_39) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_39, EqualityOperatorDifferentValues_39) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_39, EqualityOperatorDifferentTypes_39) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_39, InequalityOperator_39) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_39, InequalityOperatorSameValues_39) {
    Value v1(1);
    Value v2(1);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueTest_39, LessThanOperator_39) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_39, LessThanOrEqualOperator_39) {
    Value v1(1);
    Value v2(1);
    Value v3(2);
    EXPECT_TRUE(v1 <= v2);
    EXPECT_TRUE(v1 <= v3);
    EXPECT_FALSE(v3 <= v1);
}

TEST_F(ValueTest_39, GreaterThanOperator_39) {
    Value v1(2);
    Value v2(1);
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v2 > v1);
}

TEST_F(ValueTest_39, GreaterThanOrEqualOperator_39) {
    Value v1(2);
    Value v2(2);
    Value v3(1);
    EXPECT_TRUE(v1 >= v2);
    EXPECT_TRUE(v1 >= v3);
    EXPECT_FALSE(v3 >= v1);
}

// ==================== Subscript Operator Tests ====================

TEST_F(ValueTest_39, SubscriptWithStringKeyOnObject_39) {
    Object obj;
    obj["name"] = Value("Alice");
    Value v(obj);
    EXPECT_TRUE(v["name"].isString());
    EXPECT_EQ(v["name"].getString(), "Alice");
}

TEST_F(ValueTest_39, SubscriptWithCStringKeyOnObject_39) {
    Object obj;
    obj["age"] = Value(30);
    Value v(obj);
    EXPECT_TRUE(v["age"].isInteger());
    EXPECT_EQ(v["age"].getInteger(), 30);
}

TEST_F(ValueTest_39, SubscriptWithIndexOnArray_39) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

TEST_F(ValueTest_39, SubscriptCreatesNewKeyOnObject_39) {
    Object obj;
    Value v(obj);
    v["newKey"] = Value("newValue");
    EXPECT_TRUE(v["newKey"].isString());
    EXPECT_EQ(v["newKey"].getString(), "newValue");
}

// ==================== Load/Parse Tests ====================

TEST_F(ValueTest_39, LoadFromStringSimpleObject_39) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST_F(ValueTest_39, LoadFromStringSimpleArray_39) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_39, LoadFromStringInteger_39) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_39, LoadFromStringDouble_39) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_39, LoadFromStringBoolean_39) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_39, LoadFromStringNull_39) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_39, LoadFromStringString_39) {
    Value v;
    v.loadFromString("\"hello world\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello world");
}

TEST_F(ValueTest_39, LoadFromStream_39) {
    std::istringstream stream("{\"a\": 1}");
    Value v;
    v.loadFromStream(stream);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["a"].getInteger(), 1);
}

// ==================== Write/Serialize Tests ====================

TEST_F(ValueTest_39, WriteToStreamString_39) {
    Value v("hello");
    std::ostringstream out;
    v.writeToStream(out, false, false);
    std::string output = out.str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(ValueTest_39, WriteToStreamInteger_39) {
    Value v(42);
    std::ostringstream out;
    v.writeToStream(out, false, false);
    std::string output = out.str();
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(ValueTest_39, WriteToStreamNull_39) {
    Value v;
    std::ostringstream out;
    v.writeToStream(out, false, false);
    std::string output = out.str();
    EXPECT_NE(output.find("null"), std::string::npos);
}

TEST_F(ValueTest_39, WriteToStreamBoolean_39) {
    Value v(true);
    std::ostringstream out;
    v.writeToStream(out, false, false);
    std::string output = out.str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(ValueTest_39, WriteToStreamObject_39) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    std::ostringstream out;
    v.writeToStream(out, false, false);
    std::string output = out.str();
    EXPECT_NE(output.find("key"), std::string::npos);
    EXPECT_NE(output.find("value"), std::string::npos);
}

TEST_F(ValueTest_39, WriteToStreamArray_39) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    std::ostringstream out;
    v.writeToStream(out, false, false);
    std::string output = out.str();
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
}

TEST_F(ValueTest_39, WriteToStreamWithIndent_39) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    std::ostringstream out;
    v.writeToStream(out, true, false);
    std::string output = out.str();
    // Indented output should contain newlines or tabs/spaces
    EXPECT_NE(output.find("\n"), std::string::npos);
}

// ==================== Escape Tests ====================

TEST_F(ValueTest_39, EscapeMinimumCharacters_39) {
    std::string result = Value::escapeMinimumCharacters("hello\nworld");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_39, EscapeMinimumCharactersQuotes_39) {
    std::string result = Value::escapeMinimumCharacters("say \"hi\"");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_39, EscapeMinimumCharactersBackslash_39) {
    std::string result = Value::escapeMinimumCharacters("back\\slash");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST_F(ValueTest_39, EscapeAllCharacters_39) {
    std::string result = Value::escapeAllCharacters("a\tb");
    EXPECT_NE(result.find("\\t"), std::string::npos);
}

TEST_F(ValueTest_39, EscapeToUnicode_39) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ==================== Boundary and Edge Cases ====================

TEST_F(ValueTest_39, EmptyStringValue_39) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_39, ZeroIntegerValue_39) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_39, NegativeIntegerValue_39) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST_F(ValueTest_39, ZeroDoubleValue_39) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_39, NegativeDoubleValue_39) {
    Value v(-2.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -2.5);
}

TEST_F(ValueTest_39, EmptyObjectValue_39) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_39, EmptyArrayValue_39) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_39, SetNullResetsType_39) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    v.setNull();
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_39, OverwriteTypeWithSetter_39) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setString("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST_F(ValueTest_39, GetToStringFromString_39) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

TEST_F(ValueTest_39, GetToStringFromInteger_39) {
    Value v(42);
    std::string result = v.getToString();
    EXPECT_EQ(result, "42");
}

TEST_F(ValueTest_39, GetToStringFromBoolean_39) {
    Value v(true);
    std::string result = v.getToString();
    // Could be "true" or "1"
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_39, GetToStringFromNull_39) {
    Value v;
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

// ==================== Nested Structure Tests ====================

TEST_F(ValueTest_39, NestedObjectParsing_39) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": 42}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

TEST_F(ValueTest_39, NestedArrayParsing_39) {
    Value v;
    v.loadFromString("[[1, 2], [3, 4]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_39, MixedNestedStructure_39) {
    Value v;
    v.loadFromString("{\"arr\": [1, \"two\", true, null]}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["arr"].isArray());
    const Array& arr = v["arr"].getArray();
    EXPECT_EQ(arr.size(), 4u);
}

// ==================== Round-Trip Test ====================

TEST_F(ValueTest_39, WriteAndReadBackObject_39) {
    Object obj;
    obj["name"] = Value("test");
    obj["count"] = Value(5);
    obj["flag"] = Value(true);
    Value original(obj);

    std::ostringstream out;
    original.writeToStream(out, false, false);
    std::string json = out.str();

    Value parsed;
    parsed.loadFromString(json);
    EXPECT_TRUE(parsed.isObject());
    EXPECT_EQ(parsed["name"].getString(), "test");
    EXPECT_EQ(parsed["count"].getInteger(), 5);
    EXPECT_TRUE(parsed["flag"].getBoolean());
}

TEST_F(ValueTest_39, WriteAndReadBackArray_39) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value("two"));
    arr.push_back(Value(false));
    Value original(arr);

    std::ostringstream out;
    original.writeToStream(out, false, false);
    std::string json = out.str();

    Value parsed;
    parsed.loadFromString(json);
    EXPECT_TRUE(parsed.isArray());
    EXPECT_EQ(parsed.getArray().size(), 3u);
}

// ==================== Equality between types ====================

TEST_F(ValueTest_39, NullValuesAreEqual_39) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_39, StringValuesEquality_39) {
    Value v1("abc");
    Value v2("abc");
    Value v3("xyz");
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}

TEST_F(ValueTest_39, BooleanValuesEquality_39) {
    Value t1(true);
    Value t2(true);
    Value f1(false);
    EXPECT_TRUE(t1 == t2);
    EXPECT_FALSE(t1 == f1);
}

TEST_F(ValueTest_39, StreamOperator_39) {
    Value v("test");
    std::ostringstream out;
    out << v;
    std::string output = out.str();
    EXPECT_NE(output.find("test"), std::string::npos);
}

// ==================== Self Assignment ====================

TEST_F(ValueTest_39, SelfAssignment_39) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

// ==================== Large Values ====================

TEST_F(ValueTest_39, LargeArray_39) {
    Array arr;
    for (int i = 0; i < 1000; ++i) {
        arr.push_back(Value(i));
    }
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1000u);
}

TEST_F(ValueTest_39, LargeObject_39) {
    Object obj;
    for (int i = 0; i < 100; ++i) {
        obj["key" + std::to_string(i)] = Value(i);
    }
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 100u);
}

// ==================== Special String Content ====================

TEST_F(ValueTest_39, StringWithSpecialCharacters_39) {
    Value v("line1\nline2\ttab");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "line1\nline2\ttab");
}

TEST_F(ValueTest_39, StringWithUnicodeEscape_39) {
    Value v;
    v.loadFromString("\"hello\\u0041world\"");
    EXPECT_TRUE(v.isString());
    // \\u0041 is 'A'
    EXPECT_NE(v.getString().find("A"), std::string::npos);
}

TEST_F(ValueTest_39, LoadFromStringFalseBoolean_39) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_39, NegativeNumberParsing_39) {
    Value v;
    v.loadFromString("-42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST_F(ValueTest_39, NegativeDoubleParsing_39) {
    Value v;
    v.loadFromString("-3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -3.14);
}
