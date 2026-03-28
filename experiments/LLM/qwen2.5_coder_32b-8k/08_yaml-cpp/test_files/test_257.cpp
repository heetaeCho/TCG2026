#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"

#include "yaml-cpp/node/detail/node_ref.h"



using namespace YAML::detail;



class NodeTest_257 : public ::testing::Test {

protected:

    shared_memory_holder pMemory;

    node testNode;

    node inputNode;

};



TEST_F(NodeTest_257, PushBackIncreasesSize_257) {

    size_t initialSize = testNode.size();

    testNode.push_back(inputNode, pMemory);

    EXPECT_EQ(testNode.size(), initialSize + 1);

}



TEST_F(NodeTest_257, PushBackSetsDependency_257) {

    testNode.push_back(inputNode, pMemory);

    EXPECT_TRUE(std::find(inputNode.begin(), inputNode.end(), &testNode) != inputNode.end());

}



TEST_F(NodeTest_257, PushBackUpdatesIndex_257) {

    size_t initialIndex = testNode.size();

    testNode.push_back(inputNode, pMemory);

    EXPECT_EQ(inputNode.m_index, initialIndex);

}



TEST_F(NodeTest_257, PushBackWithDefinedNode_257) {

    inputNode.mark_defined();

    testNode.push_back(inputNode, pMemory);

    EXPECT_TRUE(testNode.get(0, pMemory)->is_defined());

}



TEST_F(NodeTest_257, PushBackMultipleNodes_257) {

    node anotherInputNode;

    size_t initialSize = testNode.size();

    testNode.push_back(inputNode, pMemory);

    testNode.push_back(anotherInputNode, pMemory);

    EXPECT_EQ(testNode.size(), initialSize + 2);

}



TEST_F(NodeTest_257, PushBackBoundaryCondition_257) {

    // Assuming a practical boundary condition, e.g., maximum size before reallocation

    for (size_t i = 0; i < 1000; ++i) {

        node newNode;

        testNode.push_back(newNode, pMemory);

    }

    EXPECT_EQ(testNode.size(), 1000);

}
