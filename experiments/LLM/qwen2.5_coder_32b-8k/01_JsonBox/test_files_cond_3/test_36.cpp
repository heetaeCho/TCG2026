#include <gtest/gtest.h>
#include "JsonBox/Value.h"
using namespace JsonBox;

class ValueTest_36 : public ::testing::Test {
protected:
    ValueTest_36() {}
};

TEST_F(ValueTest_36, IsDouble_ReturnsTrueForDoubleType_36) {
    Value value(1.23);
    EXPECT_TRUE(value.isDouble());
}

TEST_F(ValueTest_36, IsDouble_ReturnsFalseForNonDoubleType_36) {
    Value stringValue("test");
    EXPECT_FALSE(stringValue.isDouble());
    Value intValue(456);
    EXPECT_FALSE(intValue.isDouble());
    Value boolValue(true);
    EXPECT_FALSE(boolValue.isDouble());
    Value nullValue;
    EXPECT_FALSE(nullValue.isDouble());
    JsonBox::Object object;
    Value objectValue(object);
    EXPECT_FALSE(objectValue.isDouble());
    JsonBox::Array array;
    Value arrayValue(array);
    EXPECT_FALSE(arrayValue.isDouble());
}

TEST_F(ValueTest_36, IsDouble_ReturnsFalseForDefaultConstructedValue_36) {
    Value value;
    EXPECT_FALSE(value.isDouble());
}