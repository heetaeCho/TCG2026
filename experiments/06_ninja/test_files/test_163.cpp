#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "graph.h"

#include "command_collector.h"



using ::testing::ElementsAre;

using ::testing::MockFunction;



class CommandCollectorTest_163 : public ::testing::Test {

protected:

    void SetUp() override {

        node = new Node("test_node", 0);

        edge = new Edge();

        edge->inputs_.push_back(node);

        node->set_in_edge(edge);

    }



    void TearDown() override {

        delete node;

        delete edge;

    }



    Node* node;

    Edge* edge;

};



TEST_F(CommandCollectorTest_163, CollectFrom_AddsNonPhonyEdgeToInEdges_163) {

    CommandCollector collector;

    edge->set_critical_path_weight(10);

    collector.CollectFrom(node);

    EXPECT_THAT(collector.in_edges, ElementsAre(edge));

}



TEST_F(CommandCollectorTest_163, CollectFrom_SkipsVisitedNode_163) {

    CommandCollector collector;

    collector.CollectFrom(node);

    collector.CollectFrom(node);

    EXPECT_EQ(collector.in_edges.size(), 1u);

}



TEST_F(CommandCollectorTest_163, CollectFrom_SkipsVisitedEdge_163) {

    CommandCollector collector;

    edge->set_critical_path_weight(10);

    collector.CollectFrom(node);

    node->set_in_edge(new Edge());

    collector.CollectFrom(node);

    EXPECT_EQ(collector.in_edges.size(), 1u);

}



TEST_F(CommandCollectorTest_163, CollectFrom_DoesNotAddPhonyEdgeToInEdges_163) {

    CommandCollector collector;

    edge->set_critical_path_weight(10);

    edge->set_outputs_ready(true); // Simulate phony edge

    collector.CollectFrom(node);

    EXPECT_TRUE(collector.in_edges.empty());

}



TEST_F(CommandCollectorTest_163, CollectFrom_HandlesNullInEdge_163) {

    CommandCollector collector;

    node->set_in_edge(nullptr);

    collector.CollectFrom(node);

    EXPECT_TRUE(collector.in_edges.empty());

}



TEST_F(CommandCollectorTest_163, CollectFrom_RecurseOnInputs_163) {

    CommandCollector collector;

    Node* input_node = new Node("input_node", 0);

    edge->inputs_.push_back(input_node);

    Edge* input_edge = new Edge();

    input_node->set_in_edge(input_edge);

    collector.CollectFrom(node);

    EXPECT_EQ(collector.visited_edges_.size(), 2u);

    delete input_node;

    delete input_edge;

}
