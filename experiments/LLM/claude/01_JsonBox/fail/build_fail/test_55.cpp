#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueTest_55 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(ValueTest_55, DefaultConstructor_IsNull_55) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_55, StringConstructor_CreatesStringValue_55) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_55, CStringConstructor_CreatesStringValue_55) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_55, IntConstructor_CreatesIntegerValue_55) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_55, DoubleConstructor_CreatesDoubleValue_55) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_55, BoolConstructor_CreatesBooleanValue_55) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_EQ(v.getBoolean(), true);
}

TEST_F(ValueTest_55, BoolConstructorFalse_CreatesBooleanValue_55) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_EQ(v.getBoolean(), false);
}

TEST_F(ValueTest_55, ObjectConstructor_CreatesObjectValue_55) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_55, ArrayConstructor_CreatesArrayValue_55) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_55, CopyConstructor_CopiesValue_55) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "test");
}

TEST_F(ValueTest_55, CopyConstructorInt_CopiesValue_55) {
    Value original(123);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 123);
}

// ==================== Type Check Tests ====================

TEST_F(ValueTest_55, IsString_ReturnsTrueForString_55) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_55, IsInteger_ReturnsTrueForInteger_55) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_55, IsDouble_ReturnsTrueForDouble_55) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_55, IsNumeric_ReturnsTrueForIntAndDouble_55) {
    Value vi(10);
    Value vd(1.5);
    Value vs("hello");
    EXPECT_TRUE(vi.isNumeric());
    EXPECT_TRUE(vd.isNumeric());
    EXPECT_FALSE(vs.isNumeric());
}

TEST_F(ValueTest_55, IsObject_ReturnsTrueForObject_55) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_55, IsArray_ReturnsTrueForArray_55) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_55, IsBoolean_ReturnsTrueForBoolean_55) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
}

TEST_F(ValueTest_55, IsNull_ReturnsTrueForNull_55) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

// ==================== GetType Tests ====================

TEST_F(ValueTest_55, GetType_ReturnsCorrectType_55) {
    EXPECT_EQ(Value().getType(), Value::NULL_VALUE);
    EXPECT_EQ(Value("str").getType(), Value::STRING);
    EXPECT_EQ(Value(1).getType(), Value::INTEGER);
    EXPECT_EQ(Value(1.0).getType(), Value::DOUBLE);
    EXPECT_EQ(Value(true).getType(), Value::BOOLEAN);
    EXPECT_EQ(Value(Object()).getType(), Value::OBJECT);
    EXPECT_EQ(Value(Array()).getType(), Value::ARRAY);
}

// ==================== Setter Tests ====================

TEST_F(ValueTest_55, SetString_ChangesTypeToString_55) {
    Value v(42);
    v.setString("changed");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "changed");
}

TEST_F(ValueTest_55, SetString_OverwritesExistingString_55) {
    Value v("old");
    v.setString("new");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "new");
}

TEST_F(ValueTest_55, SetInteger_ChangesTypeToInteger_55) {
    Value v("hello");
    v.setInteger(99);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_55, SetDouble_ChangesTypeToDouble_55) {
    Value v;
    v.setDouble(2.718);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_55, SetBoolean_ChangesTypeToBoolean_55) {
    Value v(42);
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_EQ(v.getBoolean(), true);
}

TEST_F(ValueTest_55, SetNull_ChangesTypeToNull_55) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_55, SetObject_FromNull_55) {
    Value v;
    Object obj;
    obj["key1"] = Value("val1");
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_55, SetObject_FromExistingObject_55) {
    Object obj1;
    obj1["a"] = Value(1);
    Value v(obj1);

    Object obj2;
    obj2["b"] = Value(2);
    obj2["c"] = Value(3);
    v.setObject(obj2);

    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 2u);
    EXPECT_TRUE(v.getObject().find("b") != v.getObject().end());
    EXPECT_TRUE(v.getObject().find("c") != v.getObject().end());
    EXPECT_TRUE(v.getObject().find("a") == v.getObject().end());
}

TEST_F(ValueTest_55, SetObject_FromString_55) {
    Value v("hello");
    Object obj;
    obj["x"] = Value(10);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_55, SetObject_EmptyObject_55) {
    Value v(42);
    Object obj;
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_55, SetArray_FromNull_55) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

TEST_F(ValueTest_55, SetArray_EmptyArray_55) {
    Value v(42);
    Array arr;
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

// ==================== Assignment Operator Tests ====================

TEST_F(ValueTest_55, AssignmentOperator_Value_55) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_55, AssignmentOperator_String_55) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_55, AssignmentOperator_CString_55) {
    Value v;
    v = "cstring";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "cstring");
}

TEST_F(ValueTest_55, AssignmentOperator_Int_55) {
    Value v;
    v = 100;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST_F(ValueTest_55, AssignmentOperator_Double_55) {
    Value v;
    v = 9.99;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 9.99);
}

TEST_F(ValueTest_55, AssignmentOperator_Object_55) {
    Value v;
    Object obj;
    obj["k"] = Value("v");
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_55, AssignmentOperator_Array_55) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueTest_55, AssignmentOperator_Bool_55) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_EQ(v.getBoolean(), true);
}

// ==================== Comparison Operator Tests ====================

TEST_F(ValueTest_55, EqualityOperator_SameValues_55) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueTest_55, EqualityOperator_DifferentValues_55) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_55, EqualityOperator_DifferentTypes_55) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_55, LessThanOperator_Integers_55) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_55, LessThanOrEqualOperator_55) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_55, GreaterThanOperator_55) {
    Value v1(3);
    Value v2(2);
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v2 > v1);
}

TEST_F(ValueTest_55, GreaterThanOrEqualOperator_55) {
    Value v1(3);
    Value v2(3);
    EXPECT_TRUE(v1 >= v2);
}

// ==================== Subscript Operator Tests ====================

TEST_F(ValueTest_55, SubscriptOperator_StringKey_55) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST_F(ValueTest_55, SubscriptOperator_CStringKey_55) {
    Object obj;
    obj["key"] = Value(42);
    Value v(obj);
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST_F(ValueTest_55, SubscriptOperator_ArrayIndex_55) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

// ==================== Getter Tests ====================

TEST_F(ValueTest_55, GetString_ReturnsCorrectString_55) {
    Value v("test string");
    EXPECT_EQ(v.getString(), "test string");
}

TEST_F(ValueTest_55, GetInteger_ReturnsCorrectInt_55) {
    Value v(999);
    EXPECT_EQ(v.getInteger(), 999);
}

TEST_F(ValueTest_55, GetDouble_ReturnsCorrectDouble_55) {
    Value v(1.23456);
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.23456);
}

TEST_F(ValueTest_55, GetFloat_ReturnsCorrectFloat_55) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 1.5f);
}

TEST_F(ValueTest_55, GetBoolean_ReturnsCorrectBool_55) {
    Value v(true);
    EXPECT_TRUE(v.getBoolean());
    Value v2(false);
    EXPECT_FALSE(v2.getBoolean());
}

TEST_F(ValueTest_55, GetObject_ReturnsCorrectObject_55) {
    Object obj;
    obj["a"] = Value(1);
    obj["b"] = Value(2);
    Value v(obj);
    const Object& retrieved = v.getObject();
    EXPECT_EQ(retrieved.size(), 2u);
}

TEST_F(ValueTest_55, GetArray_ReturnsCorrectArray_55) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    arr.push_back(Value(3));
    Value v(arr);
    const Array& retrieved = v.getArray();
    EXPECT_EQ(retrieved.size(), 3u);
}

// ==================== TryGet Tests ====================

TEST_F(ValueTest_55, TryGetString_ReturnsValueWhenString_55) {
    Value v("hello");
    EXPECT_EQ(v.tryGetString("default"), "hello");
}

TEST_F(ValueTest_55, TryGetString_ReturnsDefaultWhenNotString_55) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_55, TryGetInteger_ReturnsValueWhenInteger_55) {
    Value v(42);
    EXPECT_EQ(v.tryGetInteger(0), 42);
}

TEST_F(ValueTest_55, TryGetInteger_ReturnsDefaultWhenNotInteger_55) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(0), 0);
}

TEST_F(ValueTest_55, TryGetDouble_ReturnsValueWhenDouble_55) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 3.14);
}

TEST_F(ValueTest_55, TryGetDouble_ReturnsDefaultWhenNotDouble_55) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.0), 1.0);
}

TEST_F(ValueTest_55, TryGetFloat_ReturnsValueWhenDouble_55) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST_F(ValueTest_55, TryGetFloat_ReturnsDefaultWhenNotDouble_55) {
    Value v("hello");
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.0f), 1.0f);
}

TEST_F(ValueTest_55, TryGetBoolean_ReturnsValueWhenBoolean_55) {
    Value v(true);
    EXPECT_EQ(v.tryGetBoolean(false), true);
}

TEST_F(ValueTest_55, TryGetBoolean_ReturnsDefaultWhenNotBoolean_55) {
    Value v(42);
    EXPECT_EQ(v.tryGetBoolean(false), false);
}

// ==================== IsStringable Tests ====================

TEST_F(ValueTest_55, IsStringable_TrueForString_55) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_55, IsStringable_TrueForNumeric_55) {
    Value vi(42);
    Value vd(3.14);
    EXPECT_TRUE(vi.isStringable());
    EXPECT_TRUE(vd.isStringable());
}

TEST_F(ValueTest_55, IsStringable_TrueForBool_55) {
    Value v(true);
    EXPECT_TRUE(v.isStringable());
}

// ==================== getToString Tests ====================

TEST_F(ValueTest_55, GetToString_FromString_55) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

TEST_F(ValueTest_55, GetToString_FromInteger_55) {
    Value v(42);
    EXPECT_EQ(v.getToString(), "42");
}

// ==================== Load / Write Tests ====================

TEST_F(ValueTest_55, LoadFromString_SimpleObject_55) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST_F(ValueTest_55, LoadFromString_SimpleArray_55) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_55, LoadFromString_Integer_55) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_55, LoadFromString_Double_55) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_55, LoadFromString_String_55) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_55, LoadFromString_Boolean_55) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_55, LoadFromString_Null_55) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_55, LoadFromStream_SimpleJSON_55) {
    std::istringstream ss("{\"a\": 1}");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["a"].getInteger(), 1);
}

TEST_F(ValueTest_55, WriteToStream_SimpleValue_55) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTest_55, WriteToStream_Object_55) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("key") != std::string::npos);
    EXPECT_TRUE(output.find("value") != std::string::npos);
}

TEST_F(ValueTest_55, StreamOperator_Output_55) {
    Value v("test");
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

// ==================== Escape Tests ====================

TEST_F(ValueTest_55, EscapeMinimumCharacters_BasicString_55) {
    std::string result = Value::escapeMinimumCharacters("hello");
    EXPECT_EQ(result, "hello");
}

TEST_F(ValueTest_55, EscapeMinimumCharacters_Quotes_55) {
    std::string result = Value::escapeMinimumCharacters("he\"llo");
    EXPECT_TRUE(result.find("\\\"") != std::string::npos);
}

TEST_F(ValueTest_55, EscapeMinimumCharacters_Backslash_55) {
    std::string result = Value::escapeMinimumCharacters("he\\llo");
    EXPECT_TRUE(result.find("\\\\") != std::string::npos);
}

TEST_F(ValueTest_55, EscapeAllCharacters_BasicString_55) {
    std::string result = Value::escapeAllCharacters("hello");
    // Non-ASCII chars would be escaped; basic ASCII should remain or be escaped to unicode
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_55, EscapeToUnicode_ReturnsNonEmpty_55) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
    // Should be something like \u0041
    EXPECT_TRUE(result.find("\\u") != std::string::npos);
}

// ==================== Boundary / Edge Case Tests ====================

TEST_F(ValueTest_55, IntegerBoundary_Zero_55) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_55, IntegerBoundary_Negative_55) {
    Value v(-1);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -1);
}

TEST_F(ValueTest_55, IntegerBoundary_MaxInt_55) {
    Value v(INT_MAX);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), INT_MAX);
}

TEST_F(ValueTest_55, IntegerBoundary_MinInt_55) {
    Value v(INT_MIN);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), INT_MIN);
}

TEST_F(ValueTest_55, DoubleBoundary_Zero_55) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_55, DoubleBoundary_NegativeValue_55) {
    Value v(-99.99);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -99.99);
}

TEST_F(ValueTest_55, EmptyString_55) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_55, EmptyObject_55) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_55, EmptyArray_55) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_55, SetNull_FromEachType_55) {
    Value vs("str");
    vs.setNull();
    EXPECT_TRUE(vs.isNull());

    Value vi(42);
    vi.setNull();
    EXPECT_TRUE(vi.isNull());

    Value vd(3.14);
    vd.setNull();
    EXPECT_TRUE(vd.isNull());

    Value vb(true);
    vb.setNull();
    EXPECT_TRUE(vb.isNull());

    Value vo(Object());
    vo.setNull();
    EXPECT_TRUE(vo.isNull());

    Value va(Array());
    va.setNull();
    EXPECT_TRUE(va.isNull());
}

// ==================== Multiple Type Transitions ====================

TEST_F(ValueTest_55, TypeTransition_NullToStringToIntToObject_55) {
    Value v;
    EXPECT_TRUE(v.isNull());

    v.setString("hello");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");

    v.setInteger(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);

    Object obj;
    obj["key"] = Value("val");
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_55, TypeTransition_ArrayToDouble_55) {
    Array arr;
    arr.push_back(Value(1));
    Value v(arr);
    EXPECT_TRUE(v.isArray());

    v.setDouble(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.5);
}

// ==================== Nested Structures ====================

TEST_F(ValueTest_55, NestedObject_55) {
    Object inner;
    inner["inner_key"] = Value("inner_value");
    Object outer;
    outer["nested"] = Value(inner);
    Value v(outer);

    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["nested"].isObject());
    EXPECT_EQ(v["nested"]["inner_key"].getString(), "inner_value");
}

TEST_F(ValueTest_55, NestedArray_55) {
    Array inner;
    inner.push_back(Value(1));
    inner.push_back(Value(2));
    Array outer;
    outer.push_back(Value(inner));
    Value v(outer);

    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v[(size_t)0].isArray());
    EXPECT_EQ(v[(size_t)0].getArray().size(), 2u);
}

TEST_F(ValueTest_55, LoadFromString_NestedJSON_55) {
    Value v;
    v.loadFromString("{\"obj\": {\"arr\": [1, 2, 3]}, \"val\": true}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["obj"].isObject());
    EXPECT_TRUE(v["obj"]["arr"].isArray());
    EXPECT_EQ(v["obj"]["arr"].getArray().size(), 3u);
    EXPECT_TRUE(v["val"].isBoolean());
    EXPECT_TRUE(v["val"].getBoolean());
}

// ==================== Self-Assignment ====================

TEST_F(ValueTest_55, SelfAssignment_55) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

// ==================== Equality between different type combinations ====================

TEST_F(ValueTest_55, Equality_NullValues_55) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_55, Equality_BoolValues_55) {
    Value v1(true);
    Value v2(true);
    Value v3(false);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}

TEST_F(ValueTest_55, Equality_StringValues_55) {
    Value v1("hello");
    Value v2("hello");
    Value v3("world");
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}

TEST_F(ValueTest_55, Equality_DoubleValues_55) {
    Value v1(3.14);
    Value v2(3.14);
    Value v3(2.71);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}

// ==================== writeToStream with indent ====================

TEST_F(ValueTest_55, WriteToStream_WithIndent_55) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTest_55, WriteToStream_WithEscapeAll_55) {
    Value v("hello\nworld");
    std::ostringstream oss;
    v.writeToStream(oss, false, true);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// ==================== Stream constructor ====================

TEST_F(ValueTest_55, StreamConstructor_55) {
    std::istringstream ss("{\"key\": 42}");
    Value v(ss);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getInteger(), 42);
}

// ==================== Subscript creating new keys ====================

TEST_F(ValueTest_55, SubscriptOperator_CreatesNewKey_55) {
    Object obj;
    Value v(obj);
    v["newkey"] = Value(42);
    EXPECT_EQ(v["newkey"].getInteger(), 42);
}
