#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_ref.h"



using namespace YAML::detail;



class NodeRefTest_228 : public ::testing::Test {

protected:

    node_ref node_ref_instance;

    node dummy_node;

    shared_memory_holder dummy_pMemory;

};



TEST_F(NodeRefTest_228, PushBackIncreasesSize_228) {

    size_t initial_size = node_ref_instance.size();

    node_ref_instance.push_back(dummy_node, dummy_pMemory);

    EXPECT_EQ(node_ref_instance.size(), initial_size + 1);

}



TEST_F(NodeRefTest_228, PushBackSameNodeMultipleTimes_228) {

    node_ref_instance.push_back(dummy_node, dummy_pMemory);

    node_ref_instance.push_back(dummy_node, dummy_pMemory);

    EXPECT_EQ(node_ref_instance.size(), 2);

}



TEST_F(NodeRefTest_228, SizeInitiallyZero_228) {

    EXPECT_EQ(node_ref_instance.size(), 0);

}
