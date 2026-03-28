// File: ValueGetTypeTest_32.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"
#include <map>
#include <vector>
#include <string>
#include <sstream>

using namespace JsonBox;

class ValueGetTypeTest_32 : public ::testing::Test {};

TEST_F(ValueGetTypeTest_32, DefaultIsNull_32) {
    Value v;
    EXPECT_EQ(Value::NULL_VALUE, v.getType());
}

TEST_F(ValueGetTypeTest_32, FromStdStringIsString_32) {
    Value v(std::string("hello"));
    EXPECT_EQ(Value::STRING, v.getType());
}

TEST_F(ValueGetTypeTest_32, FromCStringIsString_32) {
    Value v("world");
    EXPECT_EQ(Value::STRING, v.getType());
}

TEST_F(ValueGetTypeTest_32, FromIntIsInteger_32) {
    Value v(42);
    EXPECT_EQ(Value::INTEGER, v.getType());
}

TEST_F(ValueGetTypeTest_32, FromDoubleIsDouble_32) {
    Value v(3.14);
    EXPECT_EQ(Value::DOUBLE, v.getType());
}

TEST_F(ValueGetTypeTest_32, FromObjectIsObject_32) {
    Object obj;
    obj["k"] = Value(1);
    Value v(obj);
    EXPECT_EQ(Value::OBJECT, v.getType());
}

TEST_F(ValueGetTypeTest_32, FromArrayIsArray_32) {
    Array arr;
    arr.push_back(Value(true));
    Value v(arr);
    EXPECT_EQ(Value::ARRAY, v.getType());
}

TEST_F(ValueGetTypeTest_32, FromBoolIsBoolean_32) {
    Value v(true);
    EXPECT_EQ(Value::BOOLEAN, v.getType());
}

TEST_F(ValueGetTypeTest_32, CopyConstructorPreservesType_32) {
    Value original(123);
    Value copy(original);
    EXPECT_EQ(original.getType(), copy.getType());
    EXPECT_EQ(Value::INTEGER, copy.getType());
}

TEST_F(ValueGetTypeTest_32, AfterSetString_TypeIsString_32) {
    Value v;
    v.setString("x");
    EXPECT_EQ(Value::STRING, v.getType());
}

TEST_F(ValueGetTypeTest_32, AfterSetInteger_TypeIsInteger_32) {
    Value v;
    v.setInteger(-7);
    EXPECT_EQ(Value::INTEGER, v.getType());
}

TEST_F(ValueGetTypeTest_32, AfterSetDouble_TypeIsDouble_32) {
    Value v;
    v.setDouble(2.71828);
    EXPECT_EQ(Value::DOUBLE, v.getType());
}

TEST_F(ValueGetTypeTest_32, AfterSetObject_TypeIsObject_32) {
    Value v;
    Object o; o["a"] = Value(false);
    v.setObject(o);
    EXPECT_EQ(Value::OBJECT, v.getType());
}

TEST_F(ValueGetTypeTest_32, AfterSetArray_TypeIsArray_32) {
    Value v;
    Array a; a.push_back(Value("z"));
    v.setArray(a);
    EXPECT_EQ(Value::ARRAY, v.getType());
}

TEST_F(ValueGetTypeTest_32, AfterSetBoolean_TypeIsBoolean_32) {
    Value v;
    v.setBoolean(true);
    EXPECT_EQ(Value::BOOLEAN, v.getType());
}

TEST_F(ValueGetTypeTest_32, AfterSetNull_TypeIsNull_32) {
    Value v("was string");
    v.setNull();
    EXPECT_EQ(Value::NULL_VALUE, v.getType());
}

TEST_F(ValueGetTypeTest_32, StreamConstructorStartsAsNull_32) {
    std::istringstream is("{\"a\":1}");
    Value v(is);
    // Per provided interface snippet, the stream ctor initializes to NULL_VALUE.
    EXPECT_EQ(Value::NULL_VALUE, v.getType());
}
