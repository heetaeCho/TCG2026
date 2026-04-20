#include <gtest/gtest.h>
#include "JsonBox/Value.h"
#include <limits> // Include limits header for INT_MIN and INT_MAX

using namespace JsonBox;
class ValueTest_18 : public ::testing::Test {
protected:
    Value value;
};
TEST_F(ValueTest_18, AssignInteger_NormalOperation_18) {
    value = 42;
    EXPECT_EQ(value.getInteger(), 42);
}
TEST_F(ValueTest_18, AssignInteger_BoundaryCondition_MinInt_18) {
    value = std::numeric_limits<int>::min();
    EXPECT_EQ(value.getInteger(), std::numeric_limits<int>::min());
}
TEST_F(ValueTest_18, AssignInteger_BoundaryCondition_MaxInt_18) {
    value = std::numeric_limits<int>::max();
    EXPECT_EQ(value.getInteger(), std::numeric_limits<int>::max());
}
TEST_F(ValueTest_18, IsInteger_AfterAssigningInteger_18) {
    value = 42;
    EXPECT_TRUE(value.isInteger());
}
TEST_F(ValueTest_18, IsInteger_DefaultValue_18) {
    EXPECT_FALSE(value.isInteger());
}
TEST_F(ValueTest_18, GetInteger_DefaultValue_18) {
    EXPECT_EQ(value.getInteger(), 0);
}
TEST_F(ValueTest_18, TryGetInteger_DefaultValue_18) {
    int defaultValue = -1;
    EXPECT_EQ(value.tryGetInteger(defaultValue), defaultValue);
}
TEST_F(ValueTest_18, TryGetInteger_AfterAssigningInteger_18) {
    value = 42;
    EXPECT_EQ(value.tryGetInteger(-1), 42);
}