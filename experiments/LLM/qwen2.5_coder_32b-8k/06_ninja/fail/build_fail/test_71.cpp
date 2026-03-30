#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "graph.h"



class InputsCollectorTest_71 : public ::testing::Test {

protected:

    InputsCollector collector;

};



TEST_F(InputsCollectorTest_71, VisitNodeAddsToInputs_71) {

    Node node1, node2;

    collector.VisitNode(&node1);

    collector.VisitNode(&node2);



    const auto& inputs = collector.inputs();

    EXPECT_EQ(inputs.size(), 2);

    EXPECT_NE(std::find(inputs.begin(), inputs.end(), &node1), inputs.end());

    EXPECT_NE(std::find(inputs.begin(), inputs.end(), &node2), inputs.end());

}



TEST_F(InputsCollectorTest_71, VisitNodeAvoidsDuplicates_71) {

    Node node;

    collector.VisitNode(&node);

    collector.VisitNode(&node);



    const auto& inputs = collector.inputs();

    EXPECT_EQ(inputs.size(), 1);

}



TEST_F(InputsCollectorTest_71, ResetClearsInputs_71) {

    Node node;

    collector.VisitNode(&node);

    collector.Reset();



    const auto& inputs = collector.inputs();

    EXPECT_TRUE(inputs.empty());

}



TEST_F(InputsCollectorTest_71, GetInputsAsStringsReturnsEmpty_71) {

    std::vector<std::string> result = collector.GetInputsAsStrings(false);

    EXPECT_TRUE(result.empty());



    result = collector.GetInputsAsStrings(true);

    EXPECT_TRUE(result.empty());

}



TEST_F(InputsCollectorTest_71, GetInputsAsStringsReturnsVisitedNodes_71) {

    Node node1, node2;

    collector.VisitNode(&node1);

    collector.VisitNode(&node2);



    std::vector<std::string> result = collector.GetInputsAsStrings(false);

    EXPECT_EQ(result.size(), 2);



    // Assuming GetInputsAsStrings returns some string representation of the nodes.

    // The actual content depends on how Node is implemented and what `shell_escape` does.

}



TEST_F(InputsCollectorTest_71, InputsInitiallyEmpty_71) {

    const auto& inputs = collector.inputs();

    EXPECT_TRUE(inputs.empty());

}
