#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "graph.h"



using ::testing::Return;



class EdgeTest_60 : public ::testing::Test {

protected:

    Edge edge;

};



TEST_F(EdgeTest_60, IsImplicit_NormalOperation_60) {

    edge.inputs_.resize(5);

    edge.implicit_deps_ = 2;

    edge.order_only_deps_ = 1;



    EXPECT_FALSE(edge.is_implicit(0));

    EXPECT_FALSE(edge.is_implicit(1));

    EXPECT_TRUE(edge.is_implicit(3));

    EXPECT_TRUE(edge.is_implicit(4));

}



TEST_F(EdgeTest_60, IsImplicit_BoundaryCondition_NoInputs_60) {

    edge.inputs_.clear();

    edge.implicit_deps_ = 2;

    edge.order_only_deps_ = 1;



    EXPECT_FALSE(edge.is_implicit(0));

}



TEST_F(EdgeTest_60, IsImplicit_BoundaryCondition_AllInputsOrderOnly_60) {

    edge.inputs_.resize(3);

    edge.implicit_deps_ = 0;

    edge.order_only_deps_ = 3;



    EXPECT_TRUE(edge.is_implicit(0));

    EXPECT_TRUE(edge.is_implicit(1));

    EXPECT_TRUE(edge.is_implicit(2));

}



TEST_F(EdgeTest_60, IsImplicit_BoundaryCondition_AllInputsImplicit_60) {

    edge.inputs_.resize(3);

    edge.implicit_deps_ = 3;

    edge.order_only_deps_ = 0;



    EXPECT_FALSE(edge.is_implicit(0));

    EXPECT_FALSE(edge.is_implicit(1));

    EXPECT_TRUE(edge.is_implicit(2));

}



TEST_F(EdgeTest_60, IsImplicit_BoundaryCondition_AllInputsOrderOnlyAndImplicit_60) {

    edge.inputs_.resize(3);

    edge.implicit_deps_ = 2;

    edge.order_only_deps_ = 2;



    EXPECT_TRUE(edge.is_implicit(1));

    EXPECT_TRUE(edge.is_implicit(2));

}



TEST_F(EdgeTest_60, IsImplicit_Exceptional_IndexOutOfRange_60) {

    edge.inputs_.resize(3);

    edge.implicit_deps_ = 2;

    edge.order_only_deps_ = 1;



    // Assuming out-of-range access does not throw but returns false

    EXPECT_FALSE(edge.is_implicit(5));

}
