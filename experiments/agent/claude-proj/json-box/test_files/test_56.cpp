#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueTest_56 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(ValueTest_56, DefaultConstructorCreatesNullValue_56) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_56, StringConstructorCreatesStringValue_56) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_56, CStringConstructorCreatesStringValue_56) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_56, IntConstructorCreatesIntegerValue_56) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_56, DoubleConstructorCreatesDoubleValue_56) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_56, BoolConstructorCreatesBooleanValue_56) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_56, BoolConstructorFalse_56) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_56, ArrayConstructorCreatesArrayValue_56) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_56, ObjectConstructorCreatesObjectValue_56) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_56, CopyConstructor_56) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

// ==================== Type Checking Tests ====================

TEST_F(ValueTest_56, IsStringReturnsTrueForString_56) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_56, IsIntegerReturnsTrueForInt_56) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
}

TEST_F(ValueTest_56, IsDoubleReturnsTrueForDouble_56) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_56, IsNumericForInteger_56) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_56, IsNumericForDouble_56) {
    Value v(5.5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_56, IsNumericFalseForString_56) {
    Value v("hello");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_56, IsNullForDefaultConstructed_56) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_56, GetTypeReturnsCorrectType_56) {
    EXPECT_EQ(Value().getType(), Value::NULL_VALUE);
    EXPECT_EQ(Value("str").getType(), Value::STRING);
    EXPECT_EQ(Value(1).getType(), Value::INTEGER);
    EXPECT_EQ(Value(1.0).getType(), Value::DOUBLE);
    EXPECT_EQ(Value(true).getType(), Value::BOOLEAN);
    EXPECT_EQ(Value(Array()).getType(), Value::ARRAY);
    EXPECT_EQ(Value(Object()).getType(), Value::OBJECT);
}

// ==================== getArray Tests ====================

TEST_F(ValueTest_56, GetArrayReturnsEmptyArrayForNonArrayType_56) {
    Value v;
    const Array& arr = v.getArray();
    EXPECT_TRUE(arr.empty());
}

TEST_F(ValueTest_56, GetArrayReturnsEmptyArrayForStringType_56) {
    Value v("hello");
    const Array& arr = v.getArray();
    EXPECT_TRUE(arr.empty());
}

TEST_F(ValueTest_56, GetArrayReturnsEmptyArrayForIntegerType_56) {
    Value v(42);
    const Array& arr = v.getArray();
    EXPECT_TRUE(arr.empty());
}

TEST_F(ValueTest_56, GetArrayReturnsEmptyArrayForDoubleType_56) {
    Value v(3.14);
    const Array& arr = v.getArray();
    EXPECT_TRUE(arr.empty());
}

TEST_F(ValueTest_56, GetArrayReturnsEmptyArrayForBooleanType_56) {
    Value v(true);
    const Array& arr = v.getArray();
    EXPECT_TRUE(arr.empty());
}

TEST_F(ValueTest_56, GetArrayReturnsEmptyArrayForObjectType_56) {
    Value v(Object());
    const Array& arr = v.getArray();
    EXPECT_TRUE(arr.empty());
}

TEST_F(ValueTest_56, GetArrayReturnsActualArrayForArrayType_56) {
    Array inputArr;
    inputArr.push_back(Value(1));
    inputArr.push_back(Value("two"));
    inputArr.push_back(Value(3.0));
    Value v(inputArr);
    const Array& arr = v.getArray();
    EXPECT_EQ(arr.size(), 3u);
    EXPECT_EQ(arr[0].getInteger(), 1);
    EXPECT_EQ(arr[1].getString(), "two");
    EXPECT_DOUBLE_EQ(arr[2].getDouble(), 3.0);
}

TEST_F(ValueTest_56, GetArrayReturnsEmptyArrayWhenSetToEmptyArray_56) {
    Value v(Array());
    const Array& arr = v.getArray();
    EXPECT_TRUE(arr.empty());
}

TEST_F(ValueTest_56, GetArrayAfterSetArray_56) {
    Value v;
    Array newArr;
    newArr.push_back(Value(100));
    v.setArray(newArr);
    const Array& arr = v.getArray();
    EXPECT_EQ(arr.size(), 1u);
    EXPECT_EQ(arr[0].getInteger(), 100);
}

// ==================== Assignment Operator Tests ====================

TEST_F(ValueTest_56, AssignmentFromValue_56) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_56, AssignmentFromString_56) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_56, AssignmentFromCString_56) {
    Value v;
    v = "c-string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "c-string");
}

TEST_F(ValueTest_56, AssignmentFromInt_56) {
    Value v;
    v = 99;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_56, AssignmentFromDouble_56) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_56, AssignmentFromObject_56) {
    Value v;
    Object obj;
    obj["name"] = Value("test");
    v = obj;
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_56, AssignmentFromArray_56) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

TEST_F(ValueTest_56, AssignmentFromBool_56) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

// ==================== Setter Tests ====================

TEST_F(ValueTest_56, SetStringChangesType_56) {
    Value v(42);
    v.setString("now a string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
}

TEST_F(ValueTest_56, SetIntegerChangesType_56) {
    Value v("hello");
    v.setInteger(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 10);
}

TEST_F(ValueTest_56, SetDoubleChangesType_56) {
    Value v;
    v.setDouble(1.23);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.23);
}

TEST_F(ValueTest_56, SetBooleanChangesType_56) {
    Value v(42);
    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_56, SetNullChangesType_56) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_56, SetObjectChangesType_56) {
    Value v(42);
    Object obj;
    obj["x"] = Value(1);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_56, SetArrayChangesType_56) {
    Value v(42);
    Array arr;
    arr.push_back(Value("elem"));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

// ==================== Getter Tests ====================

TEST_F(ValueTest_56, GetStringReturnsCorrectValue_56) {
    Value v("test string");
    EXPECT_EQ(v.getString(), "test string");
}

TEST_F(ValueTest_56, GetIntegerReturnsCorrectValue_56) {
    Value v(123);
    EXPECT_EQ(v.getInteger(), 123);
}

TEST_F(ValueTest_56, GetDoubleReturnsCorrectValue_56) {
    Value v(9.99);
    EXPECT_DOUBLE_EQ(v.getDouble(), 9.99);
}

TEST_F(ValueTest_56, GetFloatReturnsCorrectValue_56) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 1.5f);
}

TEST_F(ValueTest_56, GetBooleanReturnsCorrectValue_56) {
    Value v(true);
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_56, GetObjectReturnsCorrectValue_56) {
    Object obj;
    obj["a"] = Value(1);
    obj["b"] = Value(2);
    Value v(obj);
    const Object& result = v.getObject();
    EXPECT_EQ(result.size(), 2u);
}

// ==================== Try-Get Tests ====================

TEST_F(ValueTest_56, TryGetStringReturnsValueWhenString_56) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST_F(ValueTest_56, TryGetStringReturnsDefaultWhenNotString_56) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_56, TryGetIntegerReturnsValueWhenInteger_56) {
    Value v(77);
    EXPECT_EQ(v.tryGetInteger(0), 77);
}

TEST_F(ValueTest_56, TryGetIntegerReturnsDefaultWhenNotInteger_56) {
    Value v("not int");
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

TEST_F(ValueTest_56, TryGetDoubleReturnsValueWhenDouble_56) {
    Value v(2.5);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 2.5);
}

TEST_F(ValueTest_56, TryGetDoubleReturnsDefaultWhenNotDouble_56) {
    Value v("not double");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(9.9), 9.9);
}

TEST_F(ValueTest_56, TryGetFloatReturnsValueWhenDouble_56) {
    Value v(1.25);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 1.25f);
}

TEST_F(ValueTest_56, TryGetFloatReturnsDefaultWhenNotDouble_56) {
    Value v("not float");
    EXPECT_FLOAT_EQ(v.tryGetFloat(5.5f), 5.5f);
}

TEST_F(ValueTest_56, TryGetBooleanReturnsValueWhenBoolean_56) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_56, TryGetBooleanReturnsDefaultWhenNotBoolean_56) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ==================== Comparison Operator Tests ====================

TEST_F(ValueTest_56, EqualityOperatorSameValues_56) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_56, EqualityOperatorDifferentValues_56) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_56, InequalityOperator_56) {
    Value v1(42);
    Value v2(43);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_56, LessThanOperator_56) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_56, LessThanOrEqualOperator_56) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_56, GreaterThanOperator_56) {
    Value v1(2);
    Value v2(1);
    EXPECT_TRUE(v1 > v2);
}

TEST_F(ValueTest_56, GreaterThanOrEqualOperator_56) {
    Value v1(2);
    Value v2(2);
    EXPECT_TRUE(v1 >= v2);
}

TEST_F(ValueTest_56, EqualityDifferentTypes_56) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

// ==================== Subscript Operator Tests ====================

TEST_F(ValueTest_56, SubscriptWithStringKeyOnObject_56) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    Value& result = v["key"];
    EXPECT_EQ(result.getString(), "value");
}

TEST_F(ValueTest_56, SubscriptWithCStringKeyOnObject_56) {
    Object obj;
    obj["key2"] = Value(99);
    Value v(obj);
    Value& result = v["key2"];
    EXPECT_EQ(result.getInteger(), 99);
}

TEST_F(ValueTest_56, SubscriptWithIndexOnArray_56) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[static_cast<size_t>(0)].getInteger(), 10);
    EXPECT_EQ(v[static_cast<size_t>(1)].getInteger(), 20);
    EXPECT_EQ(v[static_cast<size_t>(2)].getInteger(), 30);
}

// ==================== Load and Write Tests ====================

TEST_F(ValueTest_56, LoadFromStringSimpleInt_56) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_56, LoadFromStringSimpleString_56) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_56, LoadFromStringBoolean_56) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_56, LoadFromStringNull_56) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_56, LoadFromStringArray_56) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_56, LoadFromStringObject_56) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_56, LoadFromStringDouble_56) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_NEAR(v.getDouble(), 3.14, 0.001);
}

TEST_F(ValueTest_56, LoadFromStream_56) {
    std::istringstream iss("[1, \"two\", true]");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_56, WriteToStream_56) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTest_56, WriteToStreamWithIndent_56) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTest_56, StreamOperator_56) {
    Value v("test");
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

// ==================== Stringable Tests ====================

TEST_F(ValueTest_56, IsStringableForString_56) {
    Value v("test");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_56, IsStringableForInteger_56) {
    Value v(42);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_56, IsStringableForDouble_56) {
    Value v(3.14);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_56, GetToStringForInteger_56) {
    Value v(42);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_56, GetToStringForString_56) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

// ==================== Escape Functions Tests ====================

TEST_F(ValueTest_56, EscapeMinimumCharacters_56) {
    std::string input = "hello\nworld";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_56, EscapeAllCharacters_56) {
    std::string input = "hello\tworld";
    std::string result = Value::escapeAllCharacters(input);
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_56, EscapeToUnicode_56) {
    std::string result = Value::escapeToUnicode('\n');
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result.substr(0, 2), "\\u");
}

// ==================== Boundary / Edge Cases ====================

TEST_F(ValueTest_56, IntegerZero_56) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_56, NegativeInteger_56) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST_F(ValueTest_56, DoubleZero_56) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_56, EmptyString_56) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_56, EmptyArray_56) {
    Value v(Array());
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v.getArray().empty());
}

TEST_F(ValueTest_56, EmptyObject_56) {
    Value v(Object());
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v.getObject().empty());
}

TEST_F(ValueTest_56, LargeArray_56) {
    Array arr;
    for (int i = 0; i < 1000; ++i) {
        arr.push_back(Value(i));
    }
    Value v(arr);
    EXPECT_EQ(v.getArray().size(), 1000u);
    EXPECT_EQ(v.getArray()[0].getInteger(), 0);
    EXPECT_EQ(v.getArray()[999].getInteger(), 999);
}

TEST_F(ValueTest_56, NestedArrays_56) {
    Array inner;
    inner.push_back(Value(1));
    inner.push_back(Value(2));
    Array outer;
    outer.push_back(Value(inner));
    Value v(outer);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
    EXPECT_TRUE(v.getArray()[0].isArray());
    EXPECT_EQ(v.getArray()[0].getArray().size(), 2u);
}

TEST_F(ValueTest_56, NestedObjects_56) {
    Object inner;
    inner["nested_key"] = Value(42);
    Object outer;
    outer["inner"] = Value(inner);
    Value v(outer);
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v.getObject().at("inner").isObject());
    EXPECT_EQ(v.getObject().at("inner").getObject().at("nested_key").getInteger(), 42);
}

TEST_F(ValueTest_56, ReassignTypeMultipleTimes_56) {
    Value v;
    EXPECT_TRUE(v.isNull());
    v = 42;
    EXPECT_TRUE(v.isInteger());
    v = "string";
    EXPECT_TRUE(v.isString());
    v = 3.14;
    EXPECT_TRUE(v.isDouble());
    v = true;
    EXPECT_TRUE(v.isBoolean());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_56, ConstructFromIstream_56) {
    std::istringstream iss("{\"key\": 42}");
    Value v(iss);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_56, LoadFromStringEmptyArray_56) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v.getArray().empty());
}

TEST_F(ValueTest_56, LoadFromStringEmptyObject_56) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v.getObject().empty());
}

TEST_F(ValueTest_56, LoadFromStringNegativeNumber_56) {
    Value v;
    v.loadFromString("-42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST_F(ValueTest_56, LoadFromStringFalse_56) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_56, SelfAssignment_56) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_56, WriteToStreamNullValue_56) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string result = oss.str();
    EXPECT_NE(result.find("null"), std::string::npos);
}

TEST_F(ValueTest_56, WriteToStreamBooleanTrue_56) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string result = oss.str();
    EXPECT_NE(result.find("true"), std::string::npos);
}

TEST_F(ValueTest_56, WriteToStreamBooleanFalse_56) {
    Value v(false);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string result = oss.str();
    EXPECT_NE(result.find("false"), std::string::npos);
}

TEST_F(ValueTest_56, SubscriptCreatesNewKeyInObject_56) {
    Value v(Object());
    v["newKey"] = Value(123);
    EXPECT_EQ(v["newKey"].getInteger(), 123);
}

TEST_F(ValueTest_56, EscapeMinimumCharactersQuote_56) {
    std::string input = "he\"llo";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_56, EscapeMinimumCharactersBackslash_56) {
    std::string input = "he\\llo";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}
