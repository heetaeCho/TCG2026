#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueTest_57 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(ValueTest_57, DefaultConstructor_IsNull_57) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_57, StringConstructor_SetsString_57) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_57, CStringConstructor_SetsString_57) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_57, IntConstructor_SetsInteger_57) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_57, DoubleConstructor_SetsDouble_57) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_57, BooleanConstructor_SetsBoolean_57) {
    Value vTrue(true);
    EXPECT_TRUE(vTrue.isBoolean());
    EXPECT_TRUE(vTrue.getBoolean());

    Value vFalse(false);
    EXPECT_TRUE(vFalse.isBoolean());
    EXPECT_FALSE(vFalse.getBoolean());
}

TEST_F(ValueTest_57, ObjectConstructor_SetsObject_57) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_57, ArrayConstructor_SetsArray_57) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_57, CopyConstructor_CopiesValue_57) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

// ==================== Assignment Operator Tests ====================

TEST_F(ValueTest_57, AssignmentFromValue_57) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_57, AssignmentFromString_57) {
    Value v;
    v = std::string("test");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

TEST_F(ValueTest_57, AssignmentFromCString_57) {
    Value v;
    v = "cstring";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "cstring");
}

TEST_F(ValueTest_57, AssignmentFromInt_57) {
    Value v;
    v = 100;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

TEST_F(ValueTest_57, AssignmentFromDouble_57) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_57, AssignmentFromObject_57) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_57, AssignmentFromArray_57) {
    Value v;
    Array arr;
    arr.push_back(Value(10));
    v = arr;
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

TEST_F(ValueTest_57, AssignmentFromBool_57) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

// ==================== Type Checking Tests ====================

TEST_F(ValueTest_57, IsString_OnlyForString_57) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_57, IsInteger_OnlyForInteger_57) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueTest_57, IsNumeric_ForIntAndDouble_57) {
    Value vi(5);
    EXPECT_TRUE(vi.isNumeric());
    Value vd(5.5);
    EXPECT_TRUE(vd.isNumeric());
    Value vs("str");
    EXPECT_FALSE(vs.isNumeric());
}

TEST_F(ValueTest_57, IsStringable_57) {
    Value vs("str");
    EXPECT_TRUE(vs.isStringable());
    // Integer and double might also be stringable
    Value vi(42);
    // We just test that the function is callable; actual behavior depends on implementation
}

// ==================== setArray Tests (Primary Focus) ====================

TEST_F(ValueTest_57, SetArray_OnNullValue_57) {
    Value v;
    EXPECT_TRUE(v.isNull());
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    arr.push_back(Value(3));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_57, SetArray_OnExistingArray_57) {
    Array arr1;
    arr1.push_back(Value(1));
    Value v(arr1);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);

    Array arr2;
    arr2.push_back(Value(10));
    arr2.push_back(Value(20));
    v.setArray(arr2);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
    EXPECT_EQ(v.getArray()[0].getInteger(), 10);
    EXPECT_EQ(v.getArray()[1].getInteger(), 20);
}

TEST_F(ValueTest_57, SetArray_OnStringValue_57) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    Array arr;
    arr.push_back(Value("a"));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

TEST_F(ValueTest_57, SetArray_OnIntegerValue_57) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    Array arr;
    arr.push_back(Value(100));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

TEST_F(ValueTest_57, SetArray_OnDoubleValue_57) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    Array arr;
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_57, SetArray_OnBooleanValue_57) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    Array arr;
    arr.push_back(Value(false));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

TEST_F(ValueTest_57, SetArray_OnObjectValue_57) {
    Object obj;
    obj["key"] = Value("val");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_57, SetArray_EmptyArray_57) {
    Value v;
    Array emptyArr;
    v.setArray(emptyArr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_57, SetArray_WithNestedArrays_57) {
    Array innerArr;
    innerArr.push_back(Value(1));
    innerArr.push_back(Value(2));

    Array outerArr;
    outerArr.push_back(Value(innerArr));

    Value v;
    v.setArray(outerArr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
    EXPECT_TRUE(v.getArray()[0].isArray());
    EXPECT_EQ(v.getArray()[0].getArray().size(), 2u);
}

TEST_F(ValueTest_57, SetArray_WithMixedTypes_57) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value("string"));
    arr.push_back(Value(3.14));
    arr.push_back(Value(true));
    arr.push_back(Value());

    Value v;
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 5u);
    EXPECT_TRUE(v.getArray()[0].isInteger());
    EXPECT_TRUE(v.getArray()[1].isString());
    EXPECT_TRUE(v.getArray()[2].isDouble());
    EXPECT_TRUE(v.getArray()[3].isBoolean());
    EXPECT_TRUE(v.getArray()[4].isNull());
}

TEST_F(ValueTest_57, SetArray_MultipleTimes_57) {
    Value v;
    for (int i = 0; i < 5; ++i) {
        Array arr;
        for (int j = 0; j <= i; ++j) {
            arr.push_back(Value(j));
        }
        v.setArray(arr);
        EXPECT_TRUE(v.isArray());
        EXPECT_EQ(v.getArray().size(), static_cast<size_t>(i + 1));
    }
}

TEST_F(ValueTest_57, SetArray_ReplaceWithSmallerArray_57) {
    Array largeArr;
    for (int i = 0; i < 100; ++i) {
        largeArr.push_back(Value(i));
    }
    Value v(largeArr);
    EXPECT_EQ(v.getArray().size(), 100u);

    Array smallArr;
    smallArr.push_back(Value(42));
    v.setArray(smallArr);
    EXPECT_EQ(v.getArray().size(), 1u);
    EXPECT_EQ(v.getArray()[0].getInteger(), 42);
}

// ==================== Getter/Setter Tests ====================

TEST_F(ValueTest_57, SetString_57) {
    Value v;
    v.setString("test");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "test");
}

TEST_F(ValueTest_57, SetInteger_57) {
    Value v;
    v.setInteger(99);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_57, SetDouble_57) {
    Value v;
    v.setDouble(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.5);
}

TEST_F(ValueTest_57, SetBoolean_57) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_57, SetNull_57) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_57, SetObject_57) {
    Value v;
    Object obj;
    obj["x"] = Value(10);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

// ==================== tryGet Tests ====================

TEST_F(ValueTest_57, TryGetString_ReturnsDefault_WhenNotString_57) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_57, TryGetString_ReturnsValue_WhenString_57) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST_F(ValueTest_57, TryGetInteger_ReturnsDefault_WhenNotInt_57) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(99), 99);
}

TEST_F(ValueTest_57, TryGetInteger_ReturnsValue_WhenInt_57) {
    Value v(42);
    EXPECT_EQ(v.tryGetInteger(99), 42);
}

TEST_F(ValueTest_57, TryGetDouble_ReturnsDefault_WhenNotDouble_57) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.0), 1.0);
}

TEST_F(ValueTest_57, TryGetDouble_ReturnsValue_WhenDouble_57) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.0), 3.14);
}

TEST_F(ValueTest_57, TryGetBoolean_ReturnsDefault_WhenNotBool_57) {
    Value v(42);
    EXPECT_EQ(v.tryGetBoolean(true), true);
}

TEST_F(ValueTest_57, TryGetBoolean_ReturnsValue_WhenBool_57) {
    Value v(false);
    EXPECT_EQ(v.tryGetBoolean(true), false);
}

TEST_F(ValueTest_57, GetFloat_57) {
    Value v(3.14);
    EXPECT_FLOAT_EQ(v.getFloat(), 3.14f);
}

TEST_F(ValueTest_57, TryGetFloat_57) {
    Value v("not a float");
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.5f), 1.5f);
}

// ==================== Comparison Operator Tests ====================

TEST_F(ValueTest_57, EqualityOperator_SameValue_57) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueTest_57, EqualityOperator_DifferentValue_57) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_57, EqualityOperator_DifferentTypes_57) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_57, LessThanOperator_57) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_57, LessThanOrEqualOperator_57) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_57, GreaterThanOperator_57) {
    Value v1(2);
    Value v2(1);
    EXPECT_TRUE(v1 > v2);
}

TEST_F(ValueTest_57, GreaterThanOrEqualOperator_57) {
    Value v1(2);
    Value v2(2);
    EXPECT_TRUE(v1 >= v2);
}

// ==================== Subscript Operator Tests ====================

TEST_F(ValueTest_57, SubscriptOperator_Object_StringKey_57) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST_F(ValueTest_57, SubscriptOperator_Object_CStringKey_57) {
    Object obj;
    obj["key"] = Value(42);
    Value v(obj);
    EXPECT_EQ(v["key"].getInteger(), 42);
}

TEST_F(ValueTest_57, SubscriptOperator_Array_Index_57) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

// ==================== Serialization Tests ====================

TEST_F(ValueTest_57, WriteToStream_Integer_57) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_FALSE(oss.str().empty());
}

TEST_F(ValueTest_57, WriteToStream_String_57) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(ValueTest_57, WriteToStream_Array_57) {
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

TEST_F(ValueTest_57, WriteToStream_Null_57) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("null"), std::string::npos);
}

// ==================== Load From String Tests ====================

TEST_F(ValueTest_57, LoadFromString_Integer_57) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_57, LoadFromString_String_57) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_57, LoadFromString_Array_57) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_57, LoadFromString_Object_57) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_57, LoadFromString_Boolean_57) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_57, LoadFromString_Null_57) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_57, LoadFromString_Double_57) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_57, LoadFromStream_57) {
    std::istringstream iss("[1, 2, 3]");
    Value v;
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

// ==================== Stream Constructor Test ====================

TEST_F(ValueTest_57, StreamConstructor_57) {
    std::istringstream iss("42");
    Value v(iss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

// ==================== Escape Tests ====================

TEST_F(ValueTest_57, EscapeMinimumCharacters_57) {
    std::string result = Value::escapeMinimumCharacters("hello\nworld");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST_F(ValueTest_57, EscapeAllCharacters_57) {
    std::string result = Value::escapeAllCharacters("hello");
    // Should return an escaped version of the string
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_57, EscapeToUnicode_57) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
    // Unicode escape should start with \u
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ==================== OutputOperator Test ====================

TEST_F(ValueTest_57, OutputOperator_57) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

// ==================== Boundary / Edge Cases ====================

TEST_F(ValueTest_57, IntegerBoundary_Zero_57) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_57, IntegerBoundary_Negative_57) {
    Value v(-1);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -1);
}

TEST_F(ValueTest_57, IntegerBoundary_MaxInt_57) {
    Value v(INT_MAX);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), INT_MAX);
}

TEST_F(ValueTest_57, IntegerBoundary_MinInt_57) {
    Value v(INT_MIN);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), INT_MIN);
}

TEST_F(ValueTest_57, EmptyString_57) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_57, EmptyObject_57) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_57, EmptyArray_57) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_57, LargeArray_57) {
    Array arr;
    for (int i = 0; i < 1000; ++i) {
        arr.push_back(Value(i));
    }
    Value v;
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1000u);
    EXPECT_EQ(v.getArray()[0].getInteger(), 0);
    EXPECT_EQ(v.getArray()[999].getInteger(), 999);
}

TEST_F(ValueTest_57, GetToString_FromInt_57) {
    Value v(42);
    std::string s = v.getToString();
    EXPECT_EQ(s, "42");
}

TEST_F(ValueTest_57, GetToString_FromString_57) {
    Value v("hello");
    std::string s = v.getToString();
    EXPECT_EQ(s, "hello");
}

TEST_F(ValueTest_57, TypeTransition_StringToArrayViaSetArray_57) {
    Value v("test string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getType(), Value::STRING);

    Array arr;
    arr.push_back(Value(1));
    v.setArray(arr);

    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getType(), Value::ARRAY);
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_57, TypeTransition_IntToNull_57) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setNull();
    EXPECT_TRUE(v.isNull());
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_57, SelfAssignment_57) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_57, WriteToStream_WithIndent_57) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTest_57, WriteToStream_WithEscapeAll_57) {
    Value v("hello\nworld");
    std::ostringstream oss;
    v.writeToStream(oss, false, true);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}
