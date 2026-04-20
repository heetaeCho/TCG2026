#include <gtest/gtest.h>
#include "JsonBox/Value.h"
using namespace JsonBox;

class ValueTest_20 : public ::testing::Test {
protected:
    Value value;
};

TEST_F(ValueTest_20, AssignmentFromObject_NormalOperation_20) {
    Object src = {{"key1", Value("value1")}, {"key2", Value(42)}};
    value = src;
    EXPECT_TRUE(value.isObject());
    EXPECT_EQ(value.getObject().size(), src.size());
    EXPECT_EQ(value.getObject().at("key1").getString(), "value1");
    EXPECT_EQ(value.getObject().at("key2").getInteger(), 42);
}

TEST_F(ValueTest_20, AssignmentFromEmptyObject_NormalOperation_20) {
    Object src = {};
    value = src;
    EXPECT_TRUE(value.isObject());
    EXPECT_EQ(value.getObject().size(), src.size());
}

TEST_F(ValueTest_20, AssignmentFromObject_BoundaryCondition_20) {
    Object src = {{"key", Value("value")}};
    value = src;
    EXPECT_TRUE(value.isObject());
    EXPECT_EQ(value.getObject().size(), 1);
    EXPECT_EQ(value.getObject().at("key").getString(), "value");
}

TEST_F(ValueTest_20, AssignmentFromObject_ErrorCase_20) {
    // No specific error case expected for this operation based on the interface.
    // However, we can test if reassigning works without issues.
    Object src1 = {{"key", Value("value")}};
    value = src1;
    Object src2 = {};
    value = src2;
    EXPECT_TRUE(value.isObject());
    EXPECT_EQ(value.getObject().size(), 0);
}