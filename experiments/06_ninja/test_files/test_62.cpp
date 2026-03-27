#include <gtest/gtest.h>

#include "graph.h"



class EdgeTest : public ::testing::Test {

protected:

    Edge edge;

};



TEST_F(EdgeTest_62, IsImplicitOut_NormalOperation_62) {

    edge.outputs_.resize(5);

    edge.implicit_outs_ = 2;



    EXPECT_FALSE(edge.is_implicit_out(0));

    EXPECT_TRUE(edge.is_implicit_out(3));

}



TEST_F(EdgeTest_62, IsImplicitOut_BoundaryCondition_Start_62) {

    edge.outputs_.resize(5);

    edge.implicit_outs_ = 5;



    EXPECT_TRUE(edge.is_implicit_out(0));

}



TEST_F(EdgeTest_62, IsImplicitOut_BoundaryCondition_End_62) {

    edge.outputs_.resize(5);

    edge.implicit_outs_ = 0;



    EXPECT_FALSE(edge.is_implicit_out(4));

}



TEST_F(EdgeTest_62, IsImplicitOut_ExceptionalCase_EmptyOutputs_62) {

    edge.outputs_.clear();

    edge.implicit_outs_ = 1;



    EXPECT_TRUE(edge.is_implicit_out(0));

}



TEST_F(EdgeTest_62, IsImplicitOut_ExceptionalCase_LargeIndex_62) {

    edge.outputs_.resize(5);

    edge.implicit_outs_ = 3;



    EXPECT_TRUE(edge.is_implicit_out(10));

}
