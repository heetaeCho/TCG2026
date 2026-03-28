#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueTest_54 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ===== Constructor Tests =====

TEST_F(ValueTest_54, DefaultConstructor_IsNull_54) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_54, StringConstructor_54) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_54, CStringConstructor_54) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_54, IntConstructor_54) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_54, DoubleConstructor_54) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_54, BoolConstructor_True_54) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_54, BoolConstructor_False_54) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_54, ObjectConstructor_54) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_54, ArrayConstructor_54) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_54, CopyConstructor_54) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "test");
}

// ===== getObject Tests =====

TEST_F(ValueTest_54, GetObject_WhenObject_ReturnsObject_54) {
    Object obj;
    obj["name"] = Value("Alice");
    obj["age"] = Value(30);
    Value v(obj);
    const Object& result = v.getObject();
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result.at("name").getString(), "Alice");
    EXPECT_EQ(result.at("age").getInteger(), 30);
}

TEST_F(ValueTest_54, GetObject_WhenNull_ReturnsEmptyObject_54) {
    Value v;
    const Object& result = v.getObject();
    EXPECT_TRUE(result.empty());
}

TEST_F(ValueTest_54, GetObject_WhenString_ReturnsEmptyObject_54) {
    Value v("hello");
    const Object& result = v.getObject();
    EXPECT_TRUE(result.empty());
}

TEST_F(ValueTest_54, GetObject_WhenInteger_ReturnsEmptyObject_54) {
    Value v(42);
    const Object& result = v.getObject();
    EXPECT_TRUE(result.empty());
}

TEST_F(ValueTest_54, GetObject_WhenDouble_ReturnsEmptyObject_54) {
    Value v(3.14);
    const Object& result = v.getObject();
    EXPECT_TRUE(result.empty());
}

TEST_F(ValueTest_54, GetObject_WhenBoolean_ReturnsEmptyObject_54) {
    Value v(true);
    const Object& result = v.getObject();
    EXPECT_TRUE(result.empty());
}

TEST_F(ValueTest_54, GetObject_WhenArray_ReturnsEmptyObject_54) {
    Array arr;
    arr.push_back(Value(1));
    Value v(arr);
    const Object& result = v.getObject();
    EXPECT_TRUE(result.empty());
}

TEST_F(ValueTest_54, GetObject_EmptyObject_54) {
    Object emptyObj;
    Value v(emptyObj);
    const Object& result = v.getObject();
    EXPECT_TRUE(result.empty());
    EXPECT_TRUE(v.isObject());
}

// ===== Type checking tests =====

TEST_F(ValueTest_54, IsString_ForStringValue_54) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_54, IsInteger_ForIntValue_54) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_54, IsDouble_ForDoubleValue_54) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_54, IsNumeric_ForIntAndDouble_54) {
    Value intVal(5);
    Value doubleVal(2.5);
    Value strVal("hello");
    EXPECT_TRUE(intVal.isNumeric());
    EXPECT_TRUE(doubleVal.isNumeric());
    EXPECT_FALSE(strVal.isNumeric());
}

TEST_F(ValueTest_54, IsObject_ForObjectValue_54) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_54, IsArray_ForArrayValue_54) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_54, IsBoolean_ForBoolValue_54) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
}

TEST_F(ValueTest_54, IsNull_ForDefaultValue_54) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

// ===== Assignment operator tests =====

TEST_F(ValueTest_54, AssignmentFromValue_54) {
    Value v1("hello");
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isString());
    EXPECT_EQ(v2.getString(), "hello");
}

TEST_F(ValueTest_54, AssignmentFromString_54) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_54, AssignmentFromCString_54) {
    Value v;
    v = "c_string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "c_string");
}

TEST_F(ValueTest_54, AssignmentFromInt_54) {
    Value v;
    v = 100;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST_F(ValueTest_54, AssignmentFromDouble_54) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_54, AssignmentFromObject_54) {
    Object obj;
    obj["x"] = Value(1);
    Value v;
    v = obj;
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_54, AssignmentFromArray_54) {
    Array arr;
    arr.push_back(Value(1));
    Value v;
    v = arr;
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

TEST_F(ValueTest_54, AssignmentFromBool_54) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

// ===== Setter tests =====

TEST_F(ValueTest_54, SetString_54) {
    Value v;
    v.setString("new_string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "new_string");
}

TEST_F(ValueTest_54, SetInteger_54) {
    Value v;
    v.setInteger(99);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_54, SetDouble_54) {
    Value v;
    v.setDouble(1.23);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.23);
}

TEST_F(ValueTest_54, SetObject_54) {
    Value v;
    Object obj;
    obj["key"] = Value("val");
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_54, SetArray_54) {
    Value v;
    Array arr;
    arr.push_back(Value(10));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

TEST_F(ValueTest_54, SetBoolean_54) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_54, SetNull_54) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

// ===== Getter with default (try) tests =====

TEST_F(ValueTest_54, TryGetString_WhenString_54) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST_F(ValueTest_54, TryGetString_WhenNotString_54) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_54, TryGetInteger_WhenInteger_54) {
    Value v(7);
    EXPECT_EQ(v.tryGetInteger(0), 7);
}

TEST_F(ValueTest_54, TryGetInteger_WhenNotInteger_54) {
    Value v("text");
    EXPECT_EQ(v.tryGetInteger(-1), -1);
}

TEST_F(ValueTest_54, TryGetDouble_WhenDouble_54) {
    Value v(9.9);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 9.9);
}

TEST_F(ValueTest_54, TryGetDouble_WhenNotDouble_54) {
    Value v("text");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(5.5), 5.5);
}

TEST_F(ValueTest_54, TryGetFloat_WhenDouble_54) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 1.5f);
}

TEST_F(ValueTest_54, TryGetFloat_WhenNotDouble_54) {
    Value v("text");
    EXPECT_FLOAT_EQ(v.tryGetFloat(2.5f), 2.5f);
}

TEST_F(ValueTest_54, TryGetBoolean_WhenBoolean_54) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_54, TryGetBoolean_WhenNotBoolean_54) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ===== Comparison operator tests =====

TEST_F(ValueTest_54, EqualityOperator_SameValues_54) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueTest_54, EqualityOperator_DifferentValues_54) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_54, EqualityOperator_DifferentTypes_54) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_54, LessThanOperator_54) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_54, LessThanOrEqualOperator_54) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_54, GreaterThanOperator_54) {
    Value v1(5);
    Value v2(3);
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v2 > v1);
}

TEST_F(ValueTest_54, GreaterThanOrEqualOperator_54) {
    Value v1(5);
    Value v2(5);
    EXPECT_TRUE(v1 >= v2);
}

// ===== Subscript operator tests =====

TEST_F(ValueTest_54, SubscriptOperator_StringKey_54) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    Value& result = v[std::string("key")];
    EXPECT_TRUE(result.isString());
    EXPECT_EQ(result.getString(), "value");
}

TEST_F(ValueTest_54, SubscriptOperator_CStringKey_54) {
    Object obj;
    obj["key"] = Value(123);
    Value v(obj);
    Value& result = v["key"];
    EXPECT_TRUE(result.isInteger());
    EXPECT_EQ(result.getInteger(), 123);
}

TEST_F(ValueTest_54, SubscriptOperator_ArrayIndex_54) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    Value& result = v[(size_t)1];
    EXPECT_TRUE(result.isInteger());
    EXPECT_EQ(result.getInteger(), 20);
}

// ===== Load from string tests =====

TEST_F(ValueTest_54, LoadFromString_SimpleObject_54) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST_F(ValueTest_54, LoadFromString_SimpleArray_54) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_54, LoadFromString_Integer_54) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_54, LoadFromString_Double_54) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_54, LoadFromString_String_54) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_54, LoadFromString_Boolean_54) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_54, LoadFromString_Null_54) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_54, LoadFromStream_54) {
    std::istringstream stream("{\"a\": 1}");
    Value v;
    v.loadFromStream(stream);
    EXPECT_TRUE(v.isObject());
}

// ===== Write tests =====

TEST_F(ValueTest_54, WriteToStream_54) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTest_54, WriteToStream_Object_54) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("key"), std::string::npos);
    EXPECT_NE(output.find("value"), std::string::npos);
}

TEST_F(ValueTest_54, WriteToStream_WithIndent_54) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("key"), std::string::npos);
}

// ===== getToString tests =====

TEST_F(ValueTest_54, GetToString_FromInteger_54) {
    Value v(42);
    std::string result = v.getToString();
    EXPECT_EQ(result, "42");
}

TEST_F(ValueTest_54, GetToString_FromDouble_54) {
    Value v(3.5);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_54, GetToString_FromString_54) {
    Value v("hello");
    std::string result = v.getToString();
    EXPECT_EQ(result, "hello");
}

// ===== isStringable tests =====

TEST_F(ValueTest_54, IsStringable_String_54) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_54, IsStringable_Integer_54) {
    Value v(42);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_54, IsStringable_Double_54) {
    Value v(3.14);
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_54, IsStringable_Object_54) {
    Object obj;
    Value v(obj);
    EXPECT_FALSE(v.isStringable());
}

TEST_F(ValueTest_54, IsStringable_Array_54) {
    Array arr;
    Value v(arr);
    EXPECT_FALSE(v.isStringable());
}

// ===== getFloat tests =====

TEST_F(ValueTest_54, GetFloat_54) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 1.5f);
}

// ===== Escape function tests =====

TEST_F(ValueTest_54, EscapeMinimumCharacters_54) {
    std::string result = Value::escapeMinimumCharacters("hello\nworld");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_54, EscapeMinimumCharacters_Quotes_54) {
    std::string result = Value::escapeMinimumCharacters("he said \"hi\"");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_54, EscapeAllCharacters_54) {
    std::string result = Value::escapeAllCharacters("hello\nworld");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_54, EscapeToUnicode_54) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ===== Boundary / Edge cases =====

TEST_F(ValueTest_54, EmptyString_54) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_54, ZeroInteger_54) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_54, NegativeInteger_54) {
    Value v(-42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST_F(ValueTest_54, ZeroDouble_54) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_54, NegativeDouble_54) {
    Value v(-1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -1.5);
}

TEST_F(ValueTest_54, EmptyObject_54) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v.getObject().empty());
}

TEST_F(ValueTest_54, EmptyArray_54) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v.getArray().empty());
}

TEST_F(ValueTest_54, SetNull_ClearsType_54) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    v.setNull();
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_54, OverwriteType_StringToInt_54) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    v.setInteger(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 10);
}

TEST_F(ValueTest_54, OverwriteType_IntToObject_54) {
    Value v(42);
    Object obj;
    obj["a"] = Value(1);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_54, StreamConstructor_54) {
    std::istringstream stream("{\"key\": 42}");
    Value v(stream);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_54, NestedObject_GetObject_54) {
    Object inner;
    inner["nested_key"] = Value("nested_value");
    Object outer;
    outer["inner"] = Value(inner);
    Value v(outer);
    EXPECT_TRUE(v.isObject());
    const Object& obj = v.getObject();
    EXPECT_EQ(obj.size(), 1u);
    auto it = obj.find("inner");
    EXPECT_NE(it, obj.end());
    EXPECT_TRUE(it->second.isObject());
    EXPECT_EQ(it->second.getObject().at("nested_key").getString(), "nested_value");
}

TEST_F(ValueTest_54, LoadFromString_NestedStructure_54) {
    Value v;
    v.loadFromString("{\"arr\": [1, 2, {\"deep\": true}]}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["arr"].isArray());
    const Array& arr = v["arr"].getArray();
    EXPECT_EQ(arr.size(), 3u);
}

TEST_F(ValueTest_54, OutputStreamOperator_54) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

TEST_F(ValueTest_54, SelfAssignment_54) {
    Value v("test");
    v = v;
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

TEST_F(ValueTest_54, LargeInteger_54) {
    Value v(2147483647); // INT_MAX
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 2147483647);
}

TEST_F(ValueTest_54, NegativeLargeInteger_54) {
    Value v(-2147483647);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -2147483647);
}

TEST_F(ValueTest_54, GetType_ReturnsCorrectEnum_54) {
    Value strVal("hello");
    EXPECT_EQ(strVal.getType(), Value::STRING);

    Value intVal(1);
    EXPECT_EQ(intVal.getType(), Value::INTEGER);

    Value dblVal(1.0);
    EXPECT_EQ(dblVal.getType(), Value::DOUBLE);

    Value objVal(Object());
    EXPECT_EQ(objVal.getType(), Value::OBJECT);

    Value arrVal(Array());
    EXPECT_EQ(arrVal.getType(), Value::ARRAY);

    Value boolVal(true);
    EXPECT_EQ(boolVal.getType(), Value::BOOLEAN);

    Value nullVal;
    EXPECT_EQ(nullVal.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_54, MultipleSubscriptAccess_54) {
    Value v;
    v.loadFromString("{\"a\": {\"b\": {\"c\": 42}}}");
    EXPECT_EQ(v["a"]["b"]["c"].getInteger(), 42);
}
