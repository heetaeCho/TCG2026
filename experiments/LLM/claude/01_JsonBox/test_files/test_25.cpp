#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueTest_25 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(ValueTest_25, DefaultConstructor_IsNull_25) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_25, StringConstructor_FromStdString_25) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_25, StringConstructor_FromCString_25) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_25, IntConstructor_25) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_25, DoubleConstructor_25) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_25, BoolConstructor_True_25) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_25, BoolConstructor_False_25) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_25, ObjectConstructor_25) {
    Object obj;
    obj["key"] = Value(1);
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_25, ArrayConstructor_25) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_25, CopyConstructor_25) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

// ==================== Assignment Operator Tests ====================

TEST_F(ValueTest_25, AssignmentFromValue_25) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_25, AssignmentFromString_25) {
    Value v;
    v = std::string("test");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

TEST_F(ValueTest_25, AssignmentFromCString_25) {
    Value v;
    v = "cstring";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "cstring");
}

TEST_F(ValueTest_25, AssignmentFromInt_25) {
    Value v;
    v = 100;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST_F(ValueTest_25, AssignmentFromDouble_25) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_25, AssignmentFromBool_25) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_25, AssignmentFromObject_25) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_25, AssignmentFromArray_25) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

// ==================== Type Checking Tests ====================

TEST_F(ValueTest_25, IsStringable_ForString_25) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

TEST_F(ValueTest_25, IsNumeric_ForInteger_25) {
    Value v(42);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_25, IsNumeric_ForDouble_25) {
    Value v(3.14);
    EXPECT_TRUE(v.isNumeric());
}

TEST_F(ValueTest_25, IsNull_ForDefault_25) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
}

// ==================== operator< Tests (Primary Focus) ====================

TEST_F(ValueTest_25, LessThan_SameString_NotLessThan_25) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_FALSE(v1 < v2);
}

TEST_F(ValueTest_25, LessThan_StringLess_25) {
    Value v1("abc");
    Value v2("def");
    EXPECT_TRUE(v1 < v2);
}

TEST_F(ValueTest_25, LessThan_StringGreater_25) {
    Value v1("def");
    Value v2("abc");
    EXPECT_FALSE(v1 < v2);
}

TEST_F(ValueTest_25, LessThan_IntegerLess_25) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
}

TEST_F(ValueTest_25, LessThan_IntegerEqual_25) {
    Value v1(5);
    Value v2(5);
    EXPECT_FALSE(v1 < v2);
}

TEST_F(ValueTest_25, LessThan_IntegerGreater_25) {
    Value v1(10);
    Value v2(5);
    EXPECT_FALSE(v1 < v2);
}

TEST_F(ValueTest_25, LessThan_DoubleLess_25) {
    Value v1(1.0);
    Value v2(2.0);
    EXPECT_TRUE(v1 < v2);
}

TEST_F(ValueTest_25, LessThan_DoubleEqual_25) {
    Value v1(3.14);
    Value v2(3.14);
    EXPECT_FALSE(v1 < v2);
}

TEST_F(ValueTest_25, LessThan_DoubleGreater_25) {
    Value v1(5.0);
    Value v2(2.0);
    EXPECT_FALSE(v1 < v2);
}

TEST_F(ValueTest_25, LessThan_BooleanFalseLessThanTrue_25) {
    Value v1(false);
    Value v2(true);
    EXPECT_TRUE(v1 < v2);
}

TEST_F(ValueTest_25, LessThan_BooleanTrueNotLessThanFalse_25) {
    Value v1(true);
    Value v2(false);
    EXPECT_FALSE(v1 < v2);
}

TEST_F(ValueTest_25, LessThan_BooleanEqual_25) {
    Value v1(true);
    Value v2(true);
    EXPECT_FALSE(v1 < v2);
}

TEST_F(ValueTest_25, LessThan_DifferentTypes_ReturnsFalse_25) {
    Value v1(42);
    Value v2("hello");
    EXPECT_FALSE(v1 < v2);
}

TEST_F(ValueTest_25, LessThan_IntAndDouble_DifferentTypes_ReturnsFalse_25) {
    Value v1(1);
    Value v2(2.0);
    EXPECT_FALSE(v1 < v2);
}

TEST_F(ValueTest_25, LessThan_SelfComparison_ReturnsFalse_25) {
    Value v(42);
    EXPECT_FALSE(v < v);
}

TEST_F(ValueTest_25, LessThan_NullValues_ReturnsFalse_25) {
    Value v1;
    Value v2;
    EXPECT_FALSE(v1 < v2);
}

TEST_F(ValueTest_25, LessThan_NullAndInt_ReturnsFalse_25) {
    Value v1;
    Value v2(42);
    EXPECT_FALSE(v1 < v2);
}

TEST_F(ValueTest_25, LessThan_ArrayLess_25) {
    Array arr1;
    arr1.push_back(Value(1));
    Array arr2;
    arr2.push_back(Value(1));
    arr2.push_back(Value(2));
    Value v1(arr1);
    Value v2(arr2);
    EXPECT_TRUE(v1 < v2);
}

TEST_F(ValueTest_25, LessThan_ArrayEqual_25) {
    Array arr1;
    arr1.push_back(Value(1));
    Array arr2;
    arr2.push_back(Value(1));
    Value v1(arr1);
    Value v2(arr2);
    EXPECT_FALSE(v1 < v2);
}

TEST_F(ValueTest_25, LessThan_ObjectComparison_25) {
    Object obj1;
    obj1["a"] = Value(1);
    Object obj2;
    obj2["a"] = Value(1);
    obj2["b"] = Value(2);
    Value v1(obj1);
    Value v2(obj2);
    EXPECT_TRUE(v1 < v2);
}

// ==================== Other Comparison Operator Tests ====================

TEST_F(ValueTest_25, Equality_SameIntValues_25) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_25, Equality_DifferentIntValues_25) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_25, Inequality_DifferentValues_25) {
    Value v1(42);
    Value v2(43);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_25, LessThanOrEqual_Equal_25) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_25, LessThanOrEqual_Less_25) {
    Value v1(41);
    Value v2(42);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_25, LessThanOrEqual_Greater_25) {
    Value v1(43);
    Value v2(42);
    EXPECT_FALSE(v1 <= v2);
}

TEST_F(ValueTest_25, GreaterThan_25) {
    Value v1(43);
    Value v2(42);
    EXPECT_TRUE(v1 > v2);
}

TEST_F(ValueTest_25, GreaterThanOrEqual_Equal_25) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 >= v2);
}

TEST_F(ValueTest_25, GreaterThanOrEqual_Greater_25) {
    Value v1(43);
    Value v2(42);
    EXPECT_TRUE(v1 >= v2);
}

// ==================== Getter/Setter Tests ====================

TEST_F(ValueTest_25, SetString_25) {
    Value v;
    v.setString("new_value");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "new_value");
}

TEST_F(ValueTest_25, SetInteger_25) {
    Value v;
    v.setInteger(99);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_25, SetDouble_25) {
    Value v;
    v.setDouble(1.23);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.23);
}

TEST_F(ValueTest_25, SetBoolean_25) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_25, SetNull_25) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_25, SetObject_25) {
    Value v;
    Object obj;
    obj["x"] = Value(10);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_25, SetArray_25) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    arr.push_back(Value(3));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

// ==================== Try Get Tests ====================

TEST_F(ValueTest_25, TryGetString_WhenString_25) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST_F(ValueTest_25, TryGetString_WhenNotString_25) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_25, TryGetInteger_WhenInteger_25) {
    Value v(42);
    EXPECT_EQ(v.tryGetInteger(0), 42);
}

TEST_F(ValueTest_25, TryGetInteger_WhenNotInteger_25) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(99), 99);
}

TEST_F(ValueTest_25, TryGetDouble_WhenDouble_25) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 3.14);
}

TEST_F(ValueTest_25, TryGetDouble_WhenNotDouble_25) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.0), 1.0);
}

TEST_F(ValueTest_25, TryGetBoolean_WhenBoolean_25) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_25, TryGetBoolean_WhenNotBoolean_25) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_25, TryGetFloat_WhenDouble_25) {
    Value v(3.14);
    EXPECT_NEAR(v.tryGetFloat(0.0f), 3.14f, 0.001f);
}

// ==================== Index Operator Tests ====================

TEST_F(ValueTest_25, IndexOperator_StringKey_25) {
    Value v;
    Object obj;
    obj["key1"] = Value(10);
    v.setObject(obj);
    Value &ref = v["key1"];
    EXPECT_EQ(ref.getInteger(), 10);
}

TEST_F(ValueTest_25, IndexOperator_CStringKey_25) {
    Value v;
    Object obj;
    obj["key2"] = Value("val");
    v.setObject(obj);
    Value &ref = v["key2"];
    EXPECT_EQ(ref.getString(), "val");
}

TEST_F(ValueTest_25, IndexOperator_ArrayIndex_25) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

// ==================== Serialization / Deserialization Tests ====================

TEST_F(ValueTest_25, LoadFromString_Integer_25) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_25, LoadFromString_String_25) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_25, LoadFromString_Boolean_25) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_25, LoadFromString_Null_25) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_25, LoadFromString_Array_25) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_25, LoadFromString_Object_25) {
    Value v;
    v.loadFromString("{\"key\": 42}");
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_25, LoadFromStream_25) {
    std::istringstream iss("123");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

TEST_F(ValueTest_25, WriteToStream_Integer_25) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_FALSE(oss.str().empty());
}

TEST_F(ValueTest_25, WriteToStream_String_25) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(ValueTest_25, ConstructFromStream_25) {
    std::istringstream iss("\"stream_value\"");
    Value v(iss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "stream_value");
}

// ==================== Boundary / Edge Cases ====================

TEST_F(ValueTest_25, LessThan_NegativeIntegers_25) {
    Value v1(-10);
    Value v2(-5);
    EXPECT_TRUE(v1 < v2);
}

TEST_F(ValueTest_25, LessThan_ZeroIntegers_25) {
    Value v1(0);
    Value v2(0);
    EXPECT_FALSE(v1 < v2);
}

TEST_F(ValueTest_25, LessThan_EmptyStrings_25) {
    Value v1(std::string(""));
    Value v2(std::string(""));
    EXPECT_FALSE(v1 < v2);
}

TEST_F(ValueTest_25, LessThan_EmptyStringVsNonEmpty_25) {
    Value v1(std::string(""));
    Value v2(std::string("a"));
    EXPECT_TRUE(v1 < v2);
}

TEST_F(ValueTest_25, LessThan_EmptyArrays_25) {
    Array arr1, arr2;
    Value v1(arr1);
    Value v2(arr2);
    EXPECT_FALSE(v1 < v2);
}

TEST_F(ValueTest_25, LessThan_EmptyObjects_25) {
    Object obj1, obj2;
    Value v1(obj1);
    Value v2(obj2);
    EXPECT_FALSE(v1 < v2);
}

TEST_F(ValueTest_25, GetFloat_25) {
    Value v(2.5);
    EXPECT_NEAR(v.getFloat(), 2.5f, 0.001f);
}

TEST_F(ValueTest_25, EmptyStringConstructor_25) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_25, IntegerZero_25) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_25, DoubleZero_25) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_25, ReassignDifferentTypes_25) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v = "now a string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
    v = true;
    EXPECT_TRUE(v.isBoolean());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_25, LessThan_NegativeDouble_25) {
    Value v1(-1.5);
    Value v2(0.5);
    EXPECT_TRUE(v1 < v2);
}

TEST_F(ValueTest_25, EscapeMinimumCharacters_25) {
    std::string result = Value::escapeMinimumCharacters("hello\nworld");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_25, GetToString_Integer_25) {
    Value v(42);
    std::string s = v.getToString();
    EXPECT_FALSE(s.empty());
}

TEST_F(ValueTest_25, LessThan_LargeIntegers_25) {
    Value v1(2147483646);
    Value v2(2147483647);
    EXPECT_TRUE(v1 < v2);
}

TEST_F(ValueTest_25, LessThan_StringAndBool_DifferentTypes_25) {
    Value v1("abc");
    Value v2(true);
    EXPECT_FALSE(v1 < v2);
}

TEST_F(ValueTest_25, LessThan_BoolAndNull_DifferentTypes_25) {
    Value v1(false);
    Value v2;
    EXPECT_FALSE(v1 < v2);
}
