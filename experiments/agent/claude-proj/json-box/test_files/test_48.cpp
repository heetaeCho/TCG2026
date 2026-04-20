#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "JsonBox/Value.h"

using namespace JsonBox;

// Test fixture
class ValueTest_48 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Constructor Tests
// ============================================================

TEST_F(ValueTest_48, DefaultConstructor_IsNull_48) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_48, StringConstructor_48) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_48, CStringConstructor_48) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_48, IntConstructor_48) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_48, DoubleConstructor_48) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_48, BoolConstructor_True_48) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_48, BoolConstructor_False_48) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_48, ObjectConstructor_48) {
    Object obj;
    obj["key"] = Value(123);
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_48, ArrayConstructor_48) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_48, CopyConstructor_48) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

// ============================================================
// Type Checking Tests
// ============================================================

TEST_F(ValueTest_48, IsString_48) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_48, IsInteger_48) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_TRUE(v.isNumeric());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
}

TEST_F(ValueTest_48, IsDouble_48) {
    Value v(2.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_TRUE(v.isNumeric());
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_48, IsNumeric_IntegerIsNumeric_48) {
    Value v(5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_48, IsNumeric_DoubleIsNumeric_48) {
    Value v(5.5);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_48, IsNumeric_StringIsNotNumeric_48) {
    Value v("123");
    EXPECT_FALSE(v.isNumeric());
}

TEST_F(ValueTest_48, IsStringable_StringIsStringable_48) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_48, IsNull_NullValue_48) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

// ============================================================
// Setter Tests
// ============================================================

TEST_F(ValueTest_48, SetInteger_OnIntegerValue_48) {
    Value v(10);
    v.setInteger(20);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 20);
}

TEST_F(ValueTest_48, SetInteger_OnNonIntegerValue_48) {
    Value v("hello");
    v.setInteger(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_48, SetInteger_OnNullValue_48) {
    Value v;
    v.setInteger(99);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_48, SetInteger_NegativeValue_48) {
    Value v;
    v.setInteger(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST_F(ValueTest_48, SetInteger_Zero_48) {
    Value v;
    v.setInteger(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_48, SetInteger_MaxInt_48) {
    Value v;
    v.setInteger(INT_MAX);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), INT_MAX);
}

TEST_F(ValueTest_48, SetInteger_MinInt_48) {
    Value v;
    v.setInteger(INT_MIN);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), INT_MIN);
}

TEST_F(ValueTest_48, SetString_48) {
    Value v;
    v.setString("test");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

TEST_F(ValueTest_48, SetString_OnExistingString_48) {
    Value v("old");
    v.setString("new");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "new");
}

TEST_F(ValueTest_48, SetDouble_48) {
    Value v;
    v.setDouble(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.5);
}

TEST_F(ValueTest_48, SetDouble_OnExistingDouble_48) {
    Value v(2.0);
    v.setDouble(3.0);
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.0);
}

TEST_F(ValueTest_48, SetBoolean_48) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_48, SetBoolean_False_48) {
    Value v;
    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_48, SetNull_48) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_48, SetObject_48) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_48, SetArray_48) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    arr.push_back(Value(3));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

// ============================================================
// Getter Tests
// ============================================================

TEST_F(ValueTest_48, GetInteger_48) {
    Value v(55);
    EXPECT_EQ(v.getInteger(), 55);
}

TEST_F(ValueTest_48, GetDouble_48) {
    Value v(9.81);
    EXPECT_DOUBLE_EQ(v.getDouble(), 9.81);
}

TEST_F(ValueTest_48, GetFloat_48) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 1.5f);
}

TEST_F(ValueTest_48, GetString_48) {
    Value v("abc");
    EXPECT_EQ(v.getString(), "abc");
}

TEST_F(ValueTest_48, GetBoolean_48) {
    Value v(true);
    EXPECT_TRUE(v.getBoolean());
}

// ============================================================
// TryGet Tests
// ============================================================

TEST_F(ValueTest_48, TryGetInteger_WhenInteger_48) {
    Value v(42);
    EXPECT_EQ(v.tryGetInteger(0), 42);
}

TEST_F(ValueTest_48, TryGetInteger_WhenNotInteger_48) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(99), 99);
}

TEST_F(ValueTest_48, TryGetDouble_WhenDouble_48) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 3.14);
}

TEST_F(ValueTest_48, TryGetDouble_WhenNotDouble_48) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.0), 1.0);
}

TEST_F(ValueTest_48, TryGetFloat_WhenDouble_48) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST_F(ValueTest_48, TryGetFloat_WhenNotDouble_48) {
    Value v("hello");
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.0f), 1.0f);
}

TEST_F(ValueTest_48, TryGetString_WhenString_48) {
    Value v("abc");
    EXPECT_EQ(v.tryGetString("default"), "abc");
}

TEST_F(ValueTest_48, TryGetString_WhenNotString_48) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_48, TryGetBoolean_WhenBoolean_48) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_48, TryGetBoolean_WhenNotBoolean_48) {
    Value v(42);
    EXPECT_TRUE(v.tryGetBoolean(true));
}

// ============================================================
// Assignment Operator Tests
// ============================================================

TEST_F(ValueTest_48, AssignmentOperator_Value_48) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_48, AssignmentOperator_String_48) {
    Value v;
    v = std::string("test");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

TEST_F(ValueTest_48, AssignmentOperator_CString_48) {
    Value v;
    v = "test";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

TEST_F(ValueTest_48, AssignmentOperator_Int_48) {
    Value v;
    v = 100;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST_F(ValueTest_48, AssignmentOperator_Double_48) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_48, AssignmentOperator_Bool_48) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_48, AssignmentOperator_Object_48) {
    Value v;
    Object obj;
    obj["x"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_48, AssignmentOperator_Array_48) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

// ============================================================
// Comparison Operator Tests
// ============================================================

TEST_F(ValueTest_48, EqualityOperator_SameInt_48) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueTest_48, EqualityOperator_DifferentInt_48) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_48, EqualityOperator_DifferentTypes_48) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_48, LessThanOperator_Ints_48) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_48, LessThanOrEqual_48) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_48, GreaterThan_48) {
    Value v1(5);
    Value v2(3);
    EXPECT_TRUE(v1 > v2);
}

TEST_F(ValueTest_48, GreaterThanOrEqual_48) {
    Value v1(5);
    Value v2(5);
    EXPECT_TRUE(v1 >= v2);
}

// ============================================================
// Subscript Operator Tests
// ============================================================

TEST_F(ValueTest_48, SubscriptOperator_StringKey_48) {
    Object obj;
    obj["key"] = Value(123);
    Value v(obj);
    EXPECT_EQ(v["key"].getInteger(), 123);
}

TEST_F(ValueTest_48, SubscriptOperator_CStringKey_48) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST_F(ValueTest_48, SubscriptOperator_ArrayIndex_48) {
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
// Load/Write Tests
// ============================================================

TEST_F(ValueTest_48, LoadFromString_Integer_48) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_48, LoadFromString_String_48) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_48, LoadFromString_Boolean_48) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_48, LoadFromString_Null_48) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_48, LoadFromString_Double_48) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_NEAR(v.getDouble(), 3.14, 0.001);
}

TEST_F(ValueTest_48, LoadFromString_Object_48) {
    Value v;
    v.loadFromString("{\"key\": 42}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST_F(ValueTest_48, LoadFromString_Array_48) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_48, LoadFromStream_48) {
    std::istringstream input("42");
    Value v;
    v.loadFromStream(input);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_48, WriteToStream_Integer_48) {
    Value v(42);
    std::ostringstream output;
    v.writeToStream(output, false, false);
    EXPECT_FALSE(output.str().empty());
}

TEST_F(ValueTest_48, WriteToStream_String_48) {
    Value v("hello");
    std::ostringstream output;
    v.writeToStream(output, false, false);
    std::string result = output.str();
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(ValueTest_48, WriteToStream_Object_Indented_48) {
    Object obj;
    obj["key"] = Value(1);
    Value v(obj);
    std::ostringstream output;
    v.writeToStream(output, true, false);
    EXPECT_FALSE(output.str().empty());
}

TEST_F(ValueTest_48, WriteToStream_Null_48) {
    Value v;
    std::ostringstream output;
    v.writeToStream(output, false, false);
    EXPECT_NE(output.str().find("null"), std::string::npos);
}

// ============================================================
// Stream Constructor Test
// ============================================================

TEST_F(ValueTest_48, StreamConstructor_48) {
    std::istringstream input("\"hello\"");
    Value v(input);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

// ============================================================
// Escape Function Tests
// ============================================================

TEST_F(ValueTest_48, EscapeMinimumCharacters_48) {
    std::string result = Value::escapeMinimumCharacters("hello\nworld");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_48, EscapeAllCharacters_48) {
    std::string result = Value::escapeAllCharacters("abc");
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_48, EscapeToUnicode_48) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
}

// ============================================================
// GetToString Tests
// ============================================================

TEST_F(ValueTest_48, GetToString_FromString_48) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

TEST_F(ValueTest_48, GetToString_FromInteger_48) {
    Value v(42);
    std::string str = v.getToString();
    EXPECT_FALSE(str.empty());
}

// ============================================================
// Type Transition Tests
// ============================================================

TEST_F(ValueTest_48, TypeTransition_NullToInt_48) {
    Value v;
    EXPECT_TRUE(v.isNull());
    v.setInteger(5);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 5);
}

TEST_F(ValueTest_48, TypeTransition_IntToString_48) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setString("hello");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_48, TypeTransition_StringToDouble_48) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    v.setDouble(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_48, TypeTransition_DoubleToBoolean_48) {
    Value v(1.5);
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_48, TypeTransition_BooleanToNull_48) {
    Value v(true);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_48, TypeTransition_IntToObject_48) {
    Value v(42);
    Object obj;
    obj["a"] = Value(1);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_48, TypeTransition_IntToArray_48) {
    Value v(42);
    Array arr;
    arr.push_back(Value(1));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
}

// ============================================================
// Empty String Tests
// ============================================================

TEST_F(ValueTest_48, EmptyString_48) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_48, SetString_Empty_48) {
    Value v;
    v.setString("");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

// ============================================================
// Empty Object and Array Tests
// ============================================================

TEST_F(ValueTest_48, EmptyObject_48) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_48, EmptyArray_48) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

// ============================================================
// Equality with null
// ============================================================

TEST_F(ValueTest_48, NullEquality_48) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_48, NullInequality_WithInt_48) {
    Value v1;
    Value v2(42);
    EXPECT_TRUE(v1 != v2);
}

// ============================================================
// Self-assignment
// ============================================================

TEST_F(ValueTest_48, SelfAssignment_48) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

// ============================================================
// Complex JSON loading
// ============================================================

TEST_F(ValueTest_48, LoadFromString_NestedObject_48) {
    Value v;
    v.loadFromString("{\"a\": {\"b\": 1}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["a"].isObject());
    EXPECT_EQ(v["a"]["b"].getInteger(), 1);
}

TEST_F(ValueTest_48, LoadFromString_NestedArray_48) {
    Value v;
    v.loadFromString("[[1, 2], [3, 4]]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_48, LoadFromString_NegativeNumber_48) {
    Value v;
    v.loadFromString("-5");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -5);
}

TEST_F(ValueTest_48, LoadFromString_BooleanFalse_48) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

// ============================================================
// Output operator test
// ============================================================

TEST_F(ValueTest_48, StreamOutputOperator_48) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

// ============================================================
// Multiple setInteger calls
// ============================================================

TEST_F(ValueTest_48, SetInteger_MultipleTimes_48) {
    Value v;
    v.setInteger(1);
    EXPECT_EQ(v.getInteger(), 1);
    v.setInteger(2);
    EXPECT_EQ(v.getInteger(), 2);
    v.setInteger(3);
    EXPECT_EQ(v.getInteger(), 3);
}

TEST_F(ValueTest_48, SetInteger_FromDifferentTypes_48) {
    Value v(true);
    v.setInteger(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 10);

    Value v2(3.14);
    v2.setInteger(20);
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 20);

    Object obj;
    Value v3(obj);
    v3.setInteger(30);
    EXPECT_TRUE(v3.isInteger());
    EXPECT_EQ(v3.getInteger(), 30);

    Array arr;
    Value v4(arr);
    v4.setInteger(40);
    EXPECT_TRUE(v4.isInteger());
    EXPECT_EQ(v4.getInteger(), 40);
}

// ============================================================
// getType tests
// ============================================================

TEST_F(ValueTest_48, GetType_AllTypes_48) {
    Value vStr("hello");
    EXPECT_EQ(vStr.getType(), Value::STRING);

    Value vInt(1);
    EXPECT_EQ(vInt.getType(), Value::INTEGER);

    Value vDbl(1.0);
    EXPECT_EQ(vDbl.getType(), Value::DOUBLE);

    Value vBool(true);
    EXPECT_EQ(vBool.getType(), Value::BOOLEAN);

    Value vNull;
    EXPECT_EQ(vNull.getType(), Value::NULL_VALUE);

    Object obj;
    Value vObj(obj);
    EXPECT_EQ(vObj.getType(), Value::OBJECT);

    Array arr;
    Value vArr(arr);
    EXPECT_EQ(vArr.getType(), Value::ARRAY);
}

// ============================================================
// Roundtrip test: write then read
// ============================================================

TEST_F(ValueTest_48, Roundtrip_IntegerWriteRead_48) {
    Value original(42);
    std::ostringstream oss;
    original.writeToStream(oss, false, false);

    Value loaded;
    loaded.loadFromString(oss.str());
    EXPECT_EQ(loaded.getInteger(), 42);
}

TEST_F(ValueTest_48, Roundtrip_StringWriteRead_48) {
    Value original("hello world");
    std::ostringstream oss;
    original.writeToStream(oss, false, false);

    Value loaded;
    loaded.loadFromString(oss.str());
    EXPECT_EQ(loaded.getString(), "hello world");
}

TEST_F(ValueTest_48, Roundtrip_ObjectWriteRead_48) {
    Object obj;
    obj["name"] = Value("test");
    obj["value"] = Value(42);
    Value original(obj);

    std::ostringstream oss;
    original.writeToStream(oss, false, false);

    Value loaded;
    loaded.loadFromString(oss.str());
    EXPECT_TRUE(loaded.isObject());
    EXPECT_EQ(loaded["name"].getString(), "test");
    EXPECT_EQ(loaded["value"].getInteger(), 42);
}
