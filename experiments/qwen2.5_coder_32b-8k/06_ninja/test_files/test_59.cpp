#include <gtest/gtest.h>

#include "TestProjects/ninja/src/graph.h"



class EdgeTest_59 : public ::testing::Test {

protected:

    Edge edge;

};



TEST_F(EdgeTest_59, OutputsReady_DefaultFalse_59) {

    EXPECT_FALSE(edge.outputs_ready());

}



TEST_F(EdgeTest_59, OutputsReady_SetTrue_59) {

    edge.outputs_ready_ = true;  // Directly setting the member variable for testing purposes

    EXPECT_TRUE(edge.outputs_ready());

}



TEST_F(EdgeTest_59, Rule_DefaultNullptr_59) {

    EXPECT_EQ(edge.rule(), nullptr);

}



TEST_F(EdgeTest_59, Pool_DefaultNullptr_59) {

    EXPECT_EQ(edge.pool(), nullptr);

}



TEST_F(EdgeTest_59, CriticalPathWeight_DefaultNegativeOne_59) {

    EXPECT_EQ(edge.critical_path_weight(), -1);

}



TEST_F(EdgeTest_59, CriticalPathWeight_SetValue_59) {

    edge.set_critical_path_weight(42);

    EXPECT_EQ(edge.critical_path_weight(), 42);

}



TEST_F(EdgeTest_59, Inputs_DefaultEmpty_59) {

    EXPECT_TRUE(edge.inputs_.empty());

}



TEST_F(EdgeTest_59, Outputs_DefaultEmpty_59) {

    EXPECT_TRUE(edge.outputs_.empty());

}



TEST_F(EdgeTest_59, Validations_DefaultEmpty_59) {

    EXPECT_TRUE(edge.validations_.empty());

}
