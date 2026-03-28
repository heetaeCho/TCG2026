#include <gtest/gtest.h>

#include "onepass.cc"



namespace re2 {



class OnePassTest_566 : public ::testing::Test {

protected:

    // Setup and teardown can be added if necessary.

};



TEST_F(OnePassTest_566, IndexToNode_ReturnsCorrectPointerForValidIndex_566) {

    const int statesize = 10;

    uint8_t nodes[statesize * 3]; // Example buffer for 3 nodes

    OneState* node1 = IndexToNode(nodes, statesize, 1);

    EXPECT_EQ(node1, reinterpret_cast<OneState*>(nodes + statesize));

}



TEST_F(OnePassTest_566, IndexToNode_ReturnsCorrectPointerForFirstIndex_566) {

    const int statesize = 10;

    uint8_t nodes[statesize * 3]; // Example buffer for 3 nodes

    OneState* node0 = IndexToNode(nodes, statesize, 0);

    EXPECT_EQ(node0, reinterpret_cast<OneState*>(nodes));

}



TEST_F(OnePassTest_566, IndexToNode_ReturnsCorrectPointerForLastIndex_566) {

    const int statesize = 10;

    uint8_t nodes[statesize * 3]; // Example buffer for 3 nodes

    OneState* node2 = IndexToNode(nodes, statesize, 2);

    EXPECT_EQ(node2, reinterpret_cast<OneState*>(nodes + 2 * statesize));

}



TEST_F(OnePassTest_566, IndexToNode_BoundaryCondition_ZeroStatesize_566) {

    const int statesize = 0;

    uint8_t nodes[1]; // Minimal buffer

    OneState* node0 = IndexToNode(nodes, statesize, 0);

    EXPECT_EQ(node0, reinterpret_cast<OneState*>(nodes));

}



TEST_F(OnePassTest_566, IndexToNode_BoundaryCondition_MaxIndex_566) {

    const int statesize = 1;

    uint8_t nodes[3]; // Example buffer for 3 nodes

    OneState* node2 = IndexToNode(nodes, statesize, 2);

    EXPECT_EQ(node2, reinterpret_cast<OneState*>(nodes + 2));

}



TEST_F(OnePassTest_566, IndexToNode_OutOfBoundsIndex_ShouldNotCrash_566) {

    const int statesize = 10;

    uint8_t nodes[statesize * 3]; // Example buffer for 3 nodes

    OneState* nodeOut = IndexToNode(nodes, statesize, 3); // Out of bounds index

    EXPECT_EQ(nodeOut, reinterpret_cast<OneState*>(nodes + 3 * statesize));

}



} // namespace re2
