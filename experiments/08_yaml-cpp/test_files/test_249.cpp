#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"

#include "yaml-cpp/node/detail/node_ref.h"



using namespace YAML::detail;



class NodeTest_249 : public ::testing::Test {

protected:

    Node nodeUnderTest;

    shared_memory_holder pMemory = nullptr; // Assuming shared_memory_holder can be initialized to nullptr for these tests

};



TEST_F(NodeTest_249, SetType_SetsUndefined_TypeIsUndefined_249) {

    nodeUnderTest.set_type(NodeType::Undefined);

    EXPECT_EQ(nodeUnderTest.type(), NodeType::Undefined);

}



TEST_F(NodeTest_249, SetType_SetsScalar_TypeIsScalar_249) {

    nodeUnderTest.set_type(NodeType::Scalar);

    EXPECT_EQ(nodeUnderTest.type(), NodeType::Scalar);

}



TEST_F(NodeTest_249, SetType_ScalarToMap_TypeChangesToMap_249) {

    nodeUnderTest.set_type(NodeType::Scalar);

    nodeUnderTest.set_type(NodeType::Map);

    EXPECT_EQ(nodeUnderTest.type(), NodeType::Map);

}



TEST_F(NodeTest_249, IsDefined_AfterSetType_ReturnsTrue_249) {

    nodeUnderTest.set_type(NodeType::Scalar);

    EXPECT_TRUE(nodeUnderTest.is_defined());

}



TEST_F(NodeTest_249, SetType_DefaultConstructor_TypeIsUndefined_249) {

    Node defaultNode;

    EXPECT_EQ(defaultNode.type(), NodeType::Undefined);

}



TEST_F(NodeTest_249, SetType_UnsupportedNodeType_NoCrash_249) {

    // Assuming there are no unsupported node types in the enum, but testing boundary conditions

    nodeUnderTest.set_type(static_cast<NodeType::value>(-1));

    // No crash expected, behavior undefined based on implementation details

}



TEST_F(NodeTest_249, SetType_MarkDefinedCalled_TypeIsNotUndefined_249) {

    nodeUnderTest.mark_defined();

    EXPECT_TRUE(nodeUnderTest.is_defined());

}
