#include <gtest/gtest.h>
#include "JsonBox/Value.h"
using namespace JsonBox;
class ValueTest_57 : public ::testing::Test {
protected:
    Value value;
};
TEST_F(ValueTest_57, SetArray_SetsArrayType_57) {
    Array newArray = {Value(1), Value(2)};
    value.setArray(newArray);
    EXPECT_EQ(value.getType(), JsonBox::Value::ARRAY);
}
TEST_F(ValueTest_57, SetArray_ReplacesExistingArray_57) {
    Array initialArray = {Value(3), Value(4)};
    Array newArray = {Value(1), Value(2)};
    value.setArray(initialArray);
    value.setArray(newArray);
    EXPECT_EQ(value.getArray(), newArray);
}
TEST_F(ValueTest_57, SetArray_OnNonArrayType_ClearsAndSetsArray_57) {
    value.setString("test");
    Array newArray = {Value(1), Value(2)};
    value.setArray(newArray);
    EXPECT_EQ(value.getType(), JsonBox::Value::ARRAY);
    EXPECT_EQ(value.getArray(), newArray);
}
TEST_F(ValueTest_57, SetArray_OnEmptyArray_SetsArray_57) {
    Array newArray = {};
    value.setArray(newArray);
    EXPECT_EQ(value.getType(), JsonBox::Value::ARRAY);
    EXPECT_TRUE(value.getArray().empty());
}
TEST_F(ValueTest_57, GetArray_ReturnsSetArray_57) {
    Array newArray = {Value(1), Value(2)};
    value.setArray(newArray);
    EXPECT_EQ(value.getArray(), newArray);
}
TEST_F(ValueTest_57, IsArray_ReturnsTrueAfterSettingArray_57) {
    Array newArray = {Value(1), Value(2)};
    value.setArray(newArray);
    EXPECT_TRUE(value.isArray());
}