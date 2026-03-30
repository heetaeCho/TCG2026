#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/impl.h"

#include "yaml-cpp/node/detail/memory.h"



using namespace YAML::detail;



class NodeDataTest_669 : public ::testing::Test {

protected:

    node_data nd;

    memory_holder mem;

};



TEST_F(NodeDataTest_669, GetUndefinedNode_669) {

    EXPECT_EQ(nd.get("key", mem), nullptr);

}



TEST_F(NodeDataTest_669, GetNullNode_669) {

    nd.set_type(NodeType::Null);

    EXPECT_EQ(nd.get("key", mem), nullptr);

}



TEST_F(NodeDataTest_669, GetScalarNodeWithInvalidKey_669) {

    nd.set_type(NodeType::Scalar);

    nd.set_scalar("value");

    EXPECT_THROW(nd.get("key", mem), BadSubscript);

}



TEST_F(NodeDataTest_669, GetMapNodeWithNonExistentKey_669) {

    nd.set_type(NodeType::Map);

    EXPECT_EQ(nd.get("key", mem), nullptr);

}



TEST_F(NodeDataTest_669, GetSequenceNodeWithInvalidIndex_669) {

    nd.set_type(NodeType::Sequence);

    EXPECT_EQ(nd.get(0, mem), nullptr);

}



// Assuming there's a way to insert nodes into the sequence and map

TEST_F(NodeDataTest_669, GetMapNodeWithExistingKey_669) {

    node_data keyNode;

    node_data valueNode;

    nd.set_type(NodeType::Map);

    nd.insert(keyNode, valueNode, mem);

    EXPECT_EQ(nd.get(keyNode, mem), &valueNode);

}



TEST_F(NodeDataTest_669, GetSequenceNodeWithValidIndex_669) {

    node_data nodeToInsert;

    nd.set_type(NodeType::Sequence);

    nd.push_back(nodeToInsert, mem);

    EXPECT_EQ(nd.get(0, mem), &nodeToInsert);

}



// Boundary condition tests

TEST_F(NodeDataTest_669, GetMapNodeWithEmptyKey_669) {

    node_data keyNode;

    node_data valueNode;

    nd.set_type(NodeType::Map);

    nd.insert(keyNode, valueNode, mem);

    EXPECT_EQ(nd.get(node_data(), mem), nullptr); // Assuming an empty node is a valid key

}



TEST_F(NodeDataTest_669, GetSequenceNodeWithMaxIndex_669) {

    node_data nodeToInsert;

    nd.set_type(NodeType::Sequence);

    for (size_t i = 0; i < 100; ++i) { // Assuming sequence can hold up to 100 elements

        nd.push_back(nodeToInsert, mem);

    }

    EXPECT_EQ(nd.get(99, mem), &nodeToInsert);

}



TEST_F(NodeDataTest_669, GetSequenceNodeWithIndexOutOfRange_669) {

    node_data nodeToInsert;

    nd.set_type(NodeType::Sequence);

    nd.push_back(nodeToInsert, mem);

    EXPECT_EQ(nd.get(100, mem), nullptr); // Out of range index

}
