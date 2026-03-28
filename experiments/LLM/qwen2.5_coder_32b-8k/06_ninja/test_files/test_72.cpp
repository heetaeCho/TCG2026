#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "graph.h"



using ::testing::ElementsAre;

using ::testing::IsEmpty;



class InputsCollectorTest_72 : public ::testing::Test {

protected:

    InputsCollector collector;

};



TEST_F(InputsCollectorTest_72, ResetClearsInputs_72) {

    const Node* node = nullptr; // Assuming a valid node pointer would be provided in actual use

    collector.VisitNode(node);

    EXPECT_FALSE(collector.inputs().empty());

    collector.Reset();

    EXPECT_TRUE(collector.inputs().empty());

}



TEST_F(InputsCollectorTest_72, ResetClearsVisitedNodes_72) {

    const Node* node = nullptr; // Assuming a valid node pointer would be provided in actual use

    collector.VisitNode(node);

    EXPECT_FALSE(collector.GetInputsAsStrings(false).empty());

    collector.Reset();

    EXPECT_TRUE(collector.GetInputsAsStrings(false).empty());

}



TEST_F(InputsCollectorTest_72, VisitNodeAddsInput_72) {

    const Node* node = nullptr; // Assuming a valid node pointer would be provided in actual use

    collector.VisitNode(node);

    EXPECT_EQ(collector.inputs().size(), 1);

}



TEST_F(InputsCollectorTest_72, GetInputsAsStringsReturnsEmptyWhenNoNodesVisited_72) {

    EXPECT_TRUE(collector.GetInputsAsStrings(false).empty());

}



TEST_F(InputsCollectorTest_72, GetInputsAsStringsReturnsNonEmptyAfterVisitNode_72) {

    const Node* node = nullptr; // Assuming a valid node pointer would be provided in actual use

    collector.VisitNode(node);

    EXPECT_FALSE(collector.GetInputsAsStrings(false).empty());

}



TEST_F(InputsCollectorTest_72, GetInputsAsStringsShellEscapeFalse_72) {

    const Node* node = nullptr; // Assuming a valid node pointer would be provided in actual use

    collector.VisitNode(node);

    std::vector<std::string> inputs = collector.GetInputsAsStrings(false);

    EXPECT_FALSE(inputs.empty());

}



TEST_F(InputsCollectorTest_72, GetInputsAsStringsShellEscapeTrue_72) {

    const Node* node = nullptr; // Assuming a valid node pointer would be provided in actual use

    collector.VisitNode(node);

    std::vector<std::string> inputs = collector.GetInputsAsStrings(true);

    EXPECT_FALSE(inputs.empty());

}
