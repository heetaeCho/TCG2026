#include <gtest/gtest.h>

#include "TestProjects/poppler/goo/GooCheckedOps.h"



class GooCheckedOpsTest_2 : public ::testing::Test {

protected:

    int32_t value;

};



TEST_F(GooCheckedOpsTest_2, CheckedAssign_NormalOperation_2) {

    long long lz = 100;

    bool result = checkedAssign(lz, &value);

    EXPECT_FALSE(result);

    EXPECT_EQ(value, 100);

}



TEST_F(GooCheckedOpsTest_2, CheckedAssign_BoundaryConditionMaxInt32_2) {

    long long lz = std::numeric_limits<int32_t>::max();

    bool result = checkedAssign(lz, &value);

    EXPECT_FALSE(result);

    EXPECT_EQ(value, std::numeric_limits<int32_t>::max());

}



TEST_F(GooCheckedOpsTest_2, CheckedAssign_BoundaryConditionMinInt32_2) {

    long long lz = std::numeric_limits<int32_t>::min();

    bool result = checkedAssign(lz, &value);

    EXPECT_FALSE(result);

    EXPECT_EQ(value, std::numeric_limits<int32_t>::min());

}



TEST_F(GooCheckedOpsTest_2, CheckedAssign_OverflowAboveMaxInt32_2) {

    long long lz = static_cast<long long>(std::numeric_limits<int32_t>::max()) + 1;

    bool result = checkedAssign(lz, &value);

    EXPECT_TRUE(result);

}



TEST_F(GooCheckedOpsTest_2, CheckedAssign_UnderflowBelowMinInt32_2) {

    long long lz = static_cast<long long>(std::numeric_limits<int32_t>::min()) - 1;

    bool result = checkedAssign(lz, &value);

    EXPECT_TRUE(result);

}
