#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/detail/node_ref.h"

#include "yaml-cpp/node/detail/node.h"



using namespace YAML::detail;



class NodeRefTest_232 : public ::testing::Test {

protected:

    shared_memory_holder pMemory = std::make_shared<int>(); // Dummy memory holder

    node keyNode;

    node valueNode;

};



TEST_F(NodeRefTest_232, GetExistingKey_232) {

    node_ref ref;

    ref.insert(keyNode, valueNode, pMemory);



    EXPECT_EQ(ref.get(keyNode, pMemory), &valueNode);

}



TEST_F(NodeRefTest_232, GetNonExistingKey_232) {

    node_ref ref;



    EXPECT_EQ(ref.get(keyNode, pMemory), nullptr);

}



TEST_F(NodeRefTest_232, InsertAndGet_232) {

    node_ref ref;

    ref.insert(keyNode, valueNode, pMemory);



    EXPECT_EQ(ref.get(keyNode, pMemory), &valueNode);

}



TEST_F(NodeRefTest_232, RemoveExistingKey_232) {

    node_ref ref;

    ref.insert(keyNode, valueNode, pMemory);

    bool removed = ref.remove(keyNode, pMemory);



    EXPECT_TRUE(removed);

    EXPECT_EQ(ref.get(keyNode, pMemory), nullptr);

}



TEST_F(NodeRefTest_232, RemoveNonExistingKey_232) {

    node_ref ref;

    bool removed = ref.remove(keyNode, pMemory);



    EXPECT_FALSE(removed);

}



TEST_F(NodeRefTest_232, SizeAfterInsertion_232) {

    node_ref ref;

    EXPECT_EQ(ref.size(), 0);



    ref.insert(keyNode, valueNode, pMemory);

    EXPECT_EQ(ref.size(), 1);

}



TEST_F(NodeRefTest_232, SizeAfterRemoval_232) {

    node_ref ref;

    ref.insert(keyNode, valueNode, pMemory);

    EXPECT_EQ(ref.size(), 1);



    ref.remove(keyNode, pMemory);

    EXPECT_EQ(ref.size(), 0);

}



TEST_F(NodeRefTest_232, SizeBoundaryCondition_232) {

    node_ref ref;



    for (int i = 0; i < 10; ++i) {

        node key, value;

        ref.insert(key, value, pMemory);

    }

    EXPECT_EQ(ref.size(), 10);



    for (int i = 0; i < 5; ++i) {

        node key;

        ref.remove(key, pMemory);

    }

    EXPECT_EQ(ref.size(), 5);

}
