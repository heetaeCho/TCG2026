#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/yaml-cpp/src/node_data.cpp"



using namespace YAML::detail;

using ::testing::Return;



class NodeMock : public node {

public:

    MOCK_METHOD1(is, bool(const node& key));

};



TEST_F(NodeDataTest_651, GetReturnsNullptrWhenTypeIsNotMap_651) {

    node_data data;

    data.m_type = NodeType::Scalar;  // Set to a non-Map type

    NodeMock mockNode;

    shared_memory_holder memoryHolder;



    EXPECT_EQ(data.get(mockNode, memoryHolder), nullptr);

}



TEST_F(NodeDataTest_651, GetReturnsCorrectNodeWhenKeyFound_651) {

    node_data data;

    data.m_type = NodeType::Map;  // Set to Map type

    NodeMock mockKey;

    NodeMock mockValue;

    shared_memory_holder memoryHolder;



    EXPECT_CALL(mockKey, is(::testing::_)).WillOnce(Return(true));

    data.m_map.push_back({&mockKey, &mockValue});



    EXPECT_EQ(data.get(mockKey, memoryHolder), &mockValue);

}



TEST_F(NodeDataTest_651, GetReturnsNullptrWhenKeyNotFound_651) {

    node_data data;

    data.m_type = NodeType::Map;  // Set to Map type

    NodeMock mockKey1;

    NodeMock mockKey2;

    NodeMock mockValue;

    shared_memory_holder memoryHolder;



    EXPECT_CALL(mockKey1, is(::testing::_)).WillOnce(Return(false));

    EXPECT_CALL(mockKey2, is(::testing::_)).WillOnce(Return(false));

    data.m_map.push_back({&mockKey1, &mockValue});



    EXPECT_EQ(data.get(mockKey2, memoryHolder), nullptr);

}



TEST_F(NodeDataTest_651, GetHandlesEmptyMapCorrectly_651) {

    node_data data;

    data.m_type = NodeType::Map;  // Set to Map type

    NodeMock mockNode;

    shared_memory_holder memoryHolder;



    EXPECT_EQ(data.get(mockNode, memoryHolder), nullptr);

}
