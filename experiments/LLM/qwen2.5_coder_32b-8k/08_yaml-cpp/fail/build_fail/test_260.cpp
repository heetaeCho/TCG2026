#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/detail/node.h"



using namespace YAML::detail;



class NodeTest_260 : public ::testing::Test {

protected:

    Node nodeUnderTest;

    shared_memory_holder pMemory; // Assuming shared_memory_holder is a mockable or testable type

};



TEST_F(NodeTest_260, RemoveExistingKey_260) {

    // Arrange: Insert a key-value pair into the node

    Node keyNode;

    nodeUnderTest.insert(keyNode, Node(), pMemory);



    // Act & Assert: Remove the existing key and check return value

    EXPECT_TRUE(nodeUnderTest.remove(keyNode, pMemory));

}



TEST_F(NodeTest_260, RemoveNonExistingKey_260) {

    // Arrange: No action needed as node is initially empty



    // Act & Assert: Try to remove a non-existing key and check return value

    Node keyNode;

    EXPECT_FALSE(nodeUnderTest.remove(keyNode, pMemory));

}



TEST_F(NodeTest_260, RemoveBoundaryCondition_260) {

    // Arrange: Insert a boundary condition case if any, e.g., empty string as key

    Node keyNode;

    nodeUnderTest.insert(keyNode, Node(), pMemory);



    // Act & Assert: Remove the boundary condition key and check return value

    EXPECT_TRUE(nodeUnderTest.remove(keyNode, pMemory));

}



TEST_F(NodeTest_260, RemoveExceptionalCase_260) {

    // Arrange: Create a scenario where removal might throw an exception, if any observable through interface



    // Act & Assert: Call remove and check for expected behavior

    Node keyNode;

    EXPECT_NO_THROW(nodeUnderTest.remove(keyNode, pMemory));

}



TEST_F(NodeTest_260, RemoveWithSharedMemoryHolder_260) {

    // Arrange: Insert a key-value pair into the node with shared_memory_holder

    Node keyNode;

    nodeUnderTest.insert(keyNode, Node(), pMemory);



    // Act & Assert: Remove the existing key with shared_memory_holder and check return value

    EXPECT_TRUE(nodeUnderTest.remove(keyNode, pMemory));

}
