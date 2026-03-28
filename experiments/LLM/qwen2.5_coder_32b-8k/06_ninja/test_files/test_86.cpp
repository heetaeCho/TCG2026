#include <gtest/gtest.h>

#include "build.h"



class PlanTest_86 : public ::testing::Test {

protected:

    Builder mockBuilder;

    Plan plan;



    PlanTest_86() : plan(&mockBuilder) {}

};



TEST_F(PlanTest_86, MoreToDo_WithWantedAndCommandEdges_86) {

    // Arrange

    plan.wanted_edges_ = 1;

    plan.command_edges_ = 1;



    // Act & Assert

    EXPECT_TRUE(plan.more_to_do());

}



TEST_F(PlanTest_86, MoreToDo_WithoutWantedEdges_86) {

    // Arrange

    plan.wanted_edges_ = 0;

    plan.command_edges_ = 1;



    // Act & Assert

    EXPECT_FALSE(plan.more_to_do());

}



TEST_F(PlanTest_86, MoreToDo_WithoutCommandEdges_86) {

    // Arrange

    plan.wanted_edges_ = 1;

    plan.command_edges_ = 0;



    // Act & Assert

    EXPECT_FALSE(plan.more_to_do());

}



TEST_F(PlanTest_86, MoreToDo_WithNoEdges_86) {

    // Arrange

    plan.wanted_edges_ = 0;

    plan.command_edges_ = 0;



    // Act & Assert

    EXPECT_FALSE(plan.more_to_do());

}
