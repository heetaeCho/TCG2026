#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"

#include "yaml-cpp/node/detail/node_ref.h"



using namespace YAML::detail;



class NodeTest_261 : public ::testing::Test {

protected:

    NodeTest_261() : testNode(), keyNode(), valueNode() {}



    node testNode;

    node keyNode;

    node valueNode;

};



TEST_F(NodeTest_261, GetReturnsNullptrForNonExistingKey_261) {

    shared_memory_holder pMemory = nullptr; // Assuming null for shared memory holder

    EXPECT_EQ(testNode.get(keyNode, pMemory), nullptr);

}



TEST_F(NodeTest_261, GetReturnsValidPointerAfterInsert_261) {

    shared_memory_holder pMemory = nullptr; // Assuming null for shared memory holder

    testNode.insert(keyNode, valueNode, pMemory);

    EXPECT_NE(testNode.get(keyNode, pMemory), nullptr);

}



TEST_F(NodeTest_261, GetReturnsSamePointerAfterMultipleGets_261) {

    shared_memory_holder pMemory = nullptr; // Assuming null for shared memory holder

    testNode.insert(keyNode, valueNode, pMemory);

    node* firstGetResult = testNode.get(keyNode, pMemory);

    node* secondGetResult = testNode.get(keyNode, pMemory);

    EXPECT_EQ(firstGetResult, secondGetResult);

}



TEST_F(NodeTest_261, GetDoesNotThrowForNonExistingKey_261) {

    shared_memory_holder pMemory = nullptr; // Assuming null for shared memory holder

    EXPECT_NO_THROW(testNode.get(keyNode, pMemory));

}
