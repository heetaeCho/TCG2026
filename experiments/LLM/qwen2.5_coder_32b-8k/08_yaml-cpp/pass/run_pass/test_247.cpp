#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"

#include "yaml-cpp/node/detail/node_ref.h"



using namespace YAML::detail;



class NodeTest_247 : public ::testing::Test {

protected:

    node testNode;

    node anotherNode;

};



TEST_F(NodeTest_247, SetDataFromUndefinedNode_247) {

    // Setup

    anotherNode.mark_defined();

    

    // Exercise

    testNode.set_data(anotherNode);

    

    // Verify

    EXPECT_TRUE(testNode.is_defined());

}



TEST_F(NodeTest_247, SetDataFromDefinedNode_247) {

    // Setup

    anotherNode.mark_defined();

    anotherNode.set_scalar("test");

    

    // Exercise

    testNode.set_data(anotherNode);

    

    // Verify

    EXPECT_TRUE(testNode.is_defined());

    EXPECT_EQ(testNode.scalar(), "test");

}



TEST_F(NodeTest_247, SetDataFromSelf_247) {

    // Setup

    testNode.mark_defined();

    testNode.set_scalar("self_test");

    

    // Exercise

    testNode.set_data(testNode);

    

    // Verify

    EXPECT_TRUE(testNode.is_defined());

    EXPECT_EQ(testNode.scalar(), "self_test");

}



TEST_F(NodeTest_247, SetDataFromUndefinedToDefined_247) {

    // Setup

    anotherNode.mark_defined();

    anotherNode.set_scalar("new_value");

    

    // Exercise

    testNode.set_data(anotherNode);

    

    // Verify

    EXPECT_TRUE(testNode.is_defined());

    EXPECT_EQ(testNode.scalar(), "new_value");

}



TEST_F(NodeTest_247, SetDataFromDefinedToUndefined_247) {

    // Setup

    testNode.mark_defined();

    testNode.set_scalar("initial_value");

    anotherNode.set_data(testNode);

    testNode.set_data(node());  // Reset to undefined state

    

    // Exercise

    testNode.set_data(anotherNode);

    

    // Verify

    EXPECT_TRUE(testNode.is_defined());

    EXPECT_EQ(testNode.scalar(), "initial_value");

}
