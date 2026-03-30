#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/impl.h"



using namespace YAML::detail;



class NodeDataTest_670 : public ::testing::Test {

protected:

    shared_memory_holder pMemory;

    node_data* data;



    void SetUp() override {

        data = new node_data();

        data->set_type(NodeType::Map);

    }



    void TearDown() override {

        delete data;

    }

};



TEST_F(NodeDataTest_670, RemoveFromEmptyMap_670) {

    EXPECT_FALSE(data->remove("key", pMemory));

}



TEST_F(NodeDataTest_670, RemoveExistingKey_670) {

    node key_node;

    key_node.set_scalar("key");

    node value_node;

    data->insert(key_node, value_node, pMemory);



    EXPECT_TRUE(data->remove("key", pMemory));

    EXPECT_FALSE(data->remove("key", pMemory)); // Key should be removed

}



TEST_F(NodeDataTest_670, RemoveNonExistingKey_670) {

    node key_node;

    key_node.set_scalar("key");

    node value_node;

    data->insert(key_node, value_node, pMemory);



    EXPECT_FALSE(data->remove("non_existing_key", pMemory));

}



TEST_F(NodeDataTest_670, RemoveMultipleKeys_670) {

    node key1_node;

    key1_node.set_scalar("key1");

    node value1_node;

    data->insert(key1_node, value1_node, pMemory);



    node key2_node;

    key2_node.set_scalar("key2");

    node value2_node;

    data->insert(key2_node, value2_node, pMemory);



    EXPECT_TRUE(data->remove("key1", pMemory));

    EXPECT_TRUE(data->remove("key2", pMemory));



    EXPECT_FALSE(data->remove("key1", pMemory)); // Key should be removed

    EXPECT_FALSE(data->remove("key2", pMemory)); // Key should be removed

}



TEST_F(NodeDataTest_670, RemoveBoundaryCondition_670) {

    node key_node;

    key_node.set_scalar("");

    node value_node;

    data->insert(key_node, value_node, pMemory);



    EXPECT_TRUE(data->remove("", pMemory));

    EXPECT_FALSE(data->remove("", pMemory)); // Key should be removed

}



TEST_F(NodeDataTest_670, RemoveSequenceType_670) {

    data->set_type(NodeType::Sequence);

    node key_node;

    key_node.set_scalar("key");

    node value_node;



    EXPECT_FALSE(data->remove(0, pMemory)); // Sequence is empty

}



TEST_F(NodeDataTest_670, RemoveInvalidKeyType_670) {

    data->set_type(NodeType::Map);

    node key_node;

    key_node.set_scalar("key");

    node value_node;

    data->insert(key_node, value_node, pMemory);



    EXPECT_FALSE(data->remove(123, pMemory)); // Invalid key type

}



TEST_F(NodeDataTest_670, RemoveUndefinedPairs_670) {

    node key_node;

    key_node.set_scalar("key");

    data->m_undefinedPairs.push_back({&key_node, nullptr});



    EXPECT_TRUE(data->remove("key", pMemory));

}
