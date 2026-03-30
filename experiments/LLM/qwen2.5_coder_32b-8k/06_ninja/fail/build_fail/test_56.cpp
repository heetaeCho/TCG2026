#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "graph.h"

#include "rule.h"



using ::testing::Return;

using ::testing::Eq;



class EdgeTest_56 : public ::testing::Test {

protected:

    Rule mockRule;

    Edge edge;



    void SetUp() override {

        edge.rule_ = &mockRule;

    }

};



TEST_F(EdgeTest_56, RuleReturnsCorrectReference_56) {

    EXPECT_EQ(&edge.rule(), &mockRule);

}



TEST_F(EdgeTest_56, PoolInitiallyNull_56) {

    EXPECT_EQ(edge.pool(), nullptr);

}



TEST_F(EdgeTest_56, AllInputsReadyDefaultFalse_56) {

    EXPECT_FALSE(edge.AllInputsReady());

}



TEST_F(EdgeTest_56, CriticalPathWeightDefaultValueNegativeOne_56) {

    EXPECT_EQ(edge.critical_path_weight(), -1);

}



TEST_F(EdgeTest_56, SetCriticalPathWeightAndGetItBack_56) {

    int64_t weight = 10;

    edge.set_critical_path_weight(weight);

    EXPECT_EQ(edge.critical_path_weight(), weight);

}



TEST_F(EdgeTest_56, OutputsReadyDefaultValueFalse_56) {

    EXPECT_FALSE(edge.outputs_ready());

}



TEST_F(EdgeTest_56, IsPhonyDefaultFalse_56) {

    EXPECT_CALL(mockRule, is_phony()).WillOnce(Return(false));

    EXPECT_FALSE(edge.is_phony());

}



TEST_F(EdgeTest_56, IsPhonyTrueWhenRuleReturnsTrue_56) {

    EXPECT_CALL(mockRule, is_phony()).WillOnce(Return(true));

    EXPECT_TRUE(edge.is_phony());

}



TEST_F(EdgeTest_56, UseConsoleDefaultFalse_56) {

    EXPECT_CALL(mockRule, use_console()).WillOnce(Return(false));

    EXPECT_FALSE(edge.use_console());

}



TEST_F(EdgeTest_56, UseConsoleTrueWhenRuleReturnsTrue_56) {

    EXPECT_CALL(mockRule, use_console()).WillOnce(Return(true));

    EXPECT_TRUE(edge.use_console());

}
