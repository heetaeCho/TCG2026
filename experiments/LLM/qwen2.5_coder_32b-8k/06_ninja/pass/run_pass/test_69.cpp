#include <gtest/gtest.h>

#include "graph.h"



class EdgePriorityTest_69 : public ::testing::Test {

protected:

    std::unique_ptr<Edge> edge1;

    std::unique_ptr<Edge> edge2;



    void SetUp() override {

        edge1 = std::make_unique<Edge>();

        edge2 = std::make_unique<Edge>();

    }

};



TEST_F(EdgePriorityTest_69, EdgePriorityLess_NormalOperation_69) {

    edge1->set_critical_path_weight(5);

    edge2->set_critical_path_weight(10);



    EdgePriorityLess priority_less;

    EXPECT_TRUE(priority_less(edge1.get(), edge2.get()));

    EXPECT_FALSE(priority_less(edge2.get(), edge1.get()));

}



TEST_F(EdgePriorityTest_69, EdgePriorityLess_BoundaryCondition_SameWeight_69) {

    edge1->set_critical_path_weight(5);

    edge2->set_critical_path_weight(5);



    EdgePriorityLess priority_less;

    EXPECT_FALSE(priority_less(edge1.get(), edge2.get()));

    EXPECT_FALSE(priority_less(edge2.get(), edge1.get()));

}



TEST_F(EdgePriorityTest_69, EdgePriorityGreater_NormalOperation_69) {

    edge1->set_critical_path_weight(5);

    edge2->set_critical_path_weight(10);



    EdgePriorityGreater priority_greater;

    EXPECT_TRUE(priority_greater(edge2.get(), edge1.get()));

    EXPECT_FALSE(priority_greater(edge1.get(), edge2.get()));

}



TEST_F(EdgePriorityTest_69, EdgePriorityGreater_BoundaryCondition_SameWeight_69) {

    edge1->set_critical_path_weight(5);

    edge2->set_critical_path_weight(5);



    EdgePriorityGreater priority_greater;

    EXPECT_FALSE(priority_greater(edge1.get(), edge2.get()));

    EXPECT_FALSE(priority_greater(edge2.get(), edge1.get()));

}
