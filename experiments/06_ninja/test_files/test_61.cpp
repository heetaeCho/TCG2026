#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming Edge class is declared in graph.h

#include "graph.h"



class EdgeTest_61 : public ::testing::Test {

protected:

    Edge edge;

};



TEST_F(EdgeTest_61, IsOrderOnly_DefaultCase_61) {

    // By default, order_only_deps_ should be 0 and inputs_ should be empty.

    EXPECT_FALSE(edge.is_order_only(0));

}



TEST_F(EdgeTest_61, IsOrderOnly_IndexWithinBounds_61) {

    edge.inputs_.resize(3); // Adding 3 inputs

    edge.order_only_deps_ = 1; // Setting one of them as order-only



    EXPECT_FALSE(edge.is_order_only(0)); // First input is not order-only

    EXPECT_TRUE(edge.is_order_only(2));  // Last input is order-only

}



TEST_F(EdgeTest_61, IsOrderOnly_IndexOnBoundary_61) {

    edge.inputs_.resize(3); // Adding 3 inputs

    edge.order_only_deps_ = 2; // Setting last two as order-only



    EXPECT_FALSE(edge.is_order_only(0)); // First input is not order-only

    EXPECT_TRUE(edge.is_order_only(1));  // Second input is order-only

    EXPECT_TRUE(edge.is_order_only(2));  // Third input is order-only

}



TEST_F(EdgeTest_61, IsOrderOnly_IndexOutOfRange_61) {

    edge.inputs_.resize(3); // Adding 3 inputs

    edge.order_only_deps_ = 0; // None are order-only



    EXPECT_FALSE(edge.is_order_only(5)); // Out of range should be false

}



TEST_F(EdgeTest_61, IsOrderOnly_AllInputsOrderOnly_61) {

    edge.inputs_.resize(3); // Adding 3 inputs

    edge.order_only_deps_ = 3; // All are order-only



    EXPECT_TRUE(edge.is_order_only(0)); // First input is order-only

    EXPECT_TRUE(edge.is_order_only(1)); // Second input is order-only

    EXPECT_TRUE(edge.is_order_only(2)); // Third input is order-only

}
