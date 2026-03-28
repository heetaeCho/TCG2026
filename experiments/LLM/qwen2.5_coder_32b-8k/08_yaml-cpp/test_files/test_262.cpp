#include <gtest/gtest.h>

#include <yaml-cpp/node/detail/node.h>



using namespace YAML::detail;



class NodeTest_262 : public ::testing::Test {

protected:

    node_ref ref;

    shared_memory_holder pMemory = nullptr; // Assuming shared_memory_holder can be nullptr for testing purposes

    node keyNode;

};



TEST_F(NodeTest_262, RemoveKey_NormalOperation_262) {

    // Arrange

    ref.insert(keyNode, keyNode, pMemory);

    

    // Act

    bool result = keyNode.remove(keyNode, pMemory);



    // Assert

    EXPECT_TRUE(result);

}



TEST_F(NodeTest_262, RemoveKey_NotFound_262) {

    // Arrange

    // No insertion of keyNode into ref

    

    // Act

    bool result = keyNode.remove(keyNode, pMemory);



    // Assert

    EXPECT_FALSE(result);

}



TEST_F(NodeTest_262, RemoveKey_BoundaryCondition_EmptyNode_262) {

    // Arrange

    node emptyNode;

    

    // Act

    bool result = emptyNode.remove(keyNode, pMemory);



    // Assert

    EXPECT_FALSE(result);

}
