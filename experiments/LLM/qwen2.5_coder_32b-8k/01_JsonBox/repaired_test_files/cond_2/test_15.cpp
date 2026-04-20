#include <gtest/gtest.h>
#include "JsonBox/Value.h"
using namespace JsonBox;

class ValueTest_15 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ValueTest_15, CopyAssignmentSameTypeString_15) {
    Value original("original");
    Value copy;
    copy = original;
    EXPECT_EQ(copy.getType(), Value::STRING);
    EXPECT_STREQ(copy.getString().c_str(), "original");
}

TEST_F(ValueTest_15, CopyAssignmentDifferentTypes_15) {
    Value original(42);
    Value copy("initial");
    copy = original;
    EXPECT_EQ(copy.getType(), Value::INTEGER);
    EXPECT_EQ(copy.getInteger(), 42);
}

TEST_F(ValueTest_15, SelfAssignment_15) {
    Value value(3.14);
    value = value;
    EXPECT_EQ(value.getType(), Value::DOUBLE);
    EXPECT_DOUBLE_EQ(value.getDouble(), 3.14);
}

TEST_F(ValueTest_15, CopyAssignmentBoundaryConditions_15) {
    Value original("");
    Value copy("non-empty");
    copy = original;
    EXPECT_EQ(copy.getType(), Value::STRING);
    EXPECT_STREQ(copy.getString().c_str(), "");
}

TEST_F(ValueTest_15, CopyAssignmentNullValue_15) {
    Value original;
    Value copy(100);
    copy = original;
    EXPECT_EQ(copy.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_15, CopyAssignmentObjectType_15) {
    Object obj = {{"key", Value("value")}};
    Value original(obj);
    Value copy;
    copy = original;
    EXPECT_EQ(copy.getType(), Value::OBJECT);
    EXPECT_STREQ(copy.getObject().at("key").getString().c_str(), "value");
}

TEST_F(ValueTest_15, CopyAssignmentArrayType_15) {
    Array arr = {Value(1), Value(2)};
    Value original(arr);
    Value copy;
    copy = original;
    EXPECT_EQ(copy.getType(), Value::ARRAY);
    EXPECT_EQ(copy.getArray().size(), 2);
    EXPECT_EQ(copy.getArray()[0].getInteger(), 1);
    EXPECT_EQ(copy.getArray()[1].getInteger(), 2);
}

TEST_F(ValueTest_15, CopyAssignmentBooleanType_15) {
    Value original(true);
    Value copy;
    copy = original;
    EXPECT_EQ(copy.getType(), Value::BOOLEAN);
    EXPECT_TRUE(copy.getBoolean());
}