#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"



using namespace YAML::detail;



class NodeDataTest : public ::testing::Test {

protected:

    node_data data;

};



TEST_F(NodeDataTest_647, SizeIsZeroWhenNotDefined_647) {

    EXPECT_EQ(data.size(), 0);

}



TEST_F(NodeDataTest_647, SizeIsZeroForNullType_647) {

    data.mark_defined();

    data.set_type(NodeType::Null);

    EXPECT_EQ(data.size(), 0);

}



TEST_F(NodeDataTest_647, SizeReflectsSequenceLength_647) {

    shared_memory_holder pMemory;

    node n1, n2;



    data.mark_defined();

    data.set_type(NodeType::Sequence);

    data.push_back(n1, pMemory);

    data.push_back(n2, pMemory);



    EXPECT_EQ(data.size(), 2);

}



TEST_F(NodeDataTest_647, SizeReflectsMapSizeMinusUndefinedPairs_647) {

    shared_memory_holder pMemory;

    node key1, value1, key2, value2;



    data.mark_defined();

    data.set_type(NodeType::Map);

    data.insert(key1, value1, pMemory);

    data.insert(key2, value2, pMemory);



    EXPECT_EQ(data.size(), 2);



    // Simulate undefined pair (this part is not directly observable through the interface)

    // Assuming there's a way to introduce an undefined pair for testing

    // For this example, we'll just assert the expected behavior after introduction

    data.m_undefinedPairs.push_back(kv_pair(key1, value1));

    EXPECT_EQ(data.size(), 1);

}



TEST_F(NodeDataTest_647, BoundaryConditionForEmptySequence_647) {

    data.mark_defined();

    data.set_type(NodeType::Sequence);



    EXPECT_EQ(data.size(), 0);

}



TEST_F(NodeDataTest_647, BoundaryConditionForEmptyMap_647) {

    data.mark_defined();

    data.set_type(NodeType::Map);



    EXPECT_EQ(data.size(), 0);

}
