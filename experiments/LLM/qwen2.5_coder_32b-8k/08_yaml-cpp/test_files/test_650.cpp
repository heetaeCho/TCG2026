#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"

#include "yaml-cpp/node/detail/node.h"



using namespace YAML::detail;



class NodeDataTest_650 : public ::testing::Test {

protected:

    node_data nd;

    shared_memory_holder pMemory;

    node keyNode;

    node valueNode;



    void SetUp() override {

        // Initialize nodes and memory holder if necessary

    }

};



TEST_F(NodeDataTest_650, InsertIntoUndefinedType_650) {

    nd.set_type(NodeType::Undefined);

    EXPECT_NO_THROW(nd.insert(keyNode, valueNode, pMemory));

    EXPECT_EQ(nd.type(), NodeType::Map);

}



TEST_F(NodeDataTest_650, InsertIntoNullType_650) {

    nd.set_type(NodeType::Null);

    EXPECT_NO_THROW(nd.insert(keyNode, valueNode, pMemory));

    EXPECT_EQ(nd.type(), NodeType::Map);

}



TEST_F(NodeDataTest_650, InsertIntoSequenceType_650) {

    nd.set_type(NodeType::Sequence);

    EXPECT_NO_THROW(nd.insert(keyNode, valueNode, pMemory));

    EXPECT_EQ(nd.type(), NodeType::Map);

}



TEST_F(NodeDataTest_650, InsertIntoScalarTypeThrows_650) {

    nd.set_type(NodeType::Scalar);

    EXPECT_THROW(nd.insert(keyNode, valueNode, pMemory), BadSubscript);

}



TEST_F(NodeDataTest_650, InsertIntoMapTypeNoThrow_650) {

    nd.set_type(NodeType::Map);

    EXPECT_NO_THROW(nd.insert(keyNode, valueNode, pMemory));

}



// Assuming size() reflects the number of elements in the map

TEST_F(NodeDataTest_650, SizeIncreasedAfterInsert_650) {

    nd.set_type(NodeType::Undefined); // Ensures conversion to Map

    std::size_t initialSize = nd.size();

    nd.insert(keyNode, valueNode, pMemory);

    EXPECT_EQ(nd.size(), initialSize + 1);

}
