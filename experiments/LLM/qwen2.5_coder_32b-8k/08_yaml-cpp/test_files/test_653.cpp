#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "node_data.cpp"  // Assuming this includes necessary headers



namespace YAML {

namespace detail {



class NodeMock : public node {

public:

    MOCK_METHOD(bool, is, (const node& key), (const override));

};



class SharedMemoryHolderMock : public shared_memory_holder {

public:

    // Add any necessary mocks if shared_memory_holder has virtual functions

};



class NodeDataTest_653 : public ::testing::Test {

protected:

    node_data data;

    std::shared_ptr<NodeMock> key1 = std::make_shared<NodeMock>();

    std::shared_ptr<NodeMock> value1 = std::make_shared<NodeMock>();

    SharedMemoryHolderMock memory;



    void SetUp() override {

        // Setup initial state if necessary

    }

};



TEST_F(NodeDataTest_653, RemoveFromMap_NodeExists_653) {

    YAML::detail::node* keyPtr = key1.get();

    YAML::detail::node* valuePtr = value1.get();



    data.m_type = NodeType::Map;

    data.m_map.push_back({keyPtr, valuePtr});



    EXPECT_CALL(*key1, is(::testing::_)).WillOnce(::testing::Return(true));



    bool result = data.remove(*key1, memory);

    EXPECT_TRUE(result);

    EXPECT_EQ(data.m_map.size(), 0u);

}



TEST_F(NodeDataTest_653, RemoveFromMap_NodeDoesNotExist_653) {

    YAML::detail::node* keyPtr = key1.get();



    data.m_type = NodeType::Map;



    EXPECT_CALL(*key1, is(::testing::_)).WillOnce(::testing::Return(false));



    bool result = data.remove(*key1, memory);

    EXPECT_FALSE(result);

    EXPECT_EQ(data.m_map.size(), 0u);

}



TEST_F(NodeDataTest_653, RemoveFromUndefinedPairs_NodeExists_653) {

    YAML::detail::node* keyPtr = key1.get();

    YAML::detail::node* valuePtr = value1.get();



    data.m_type = NodeType::Map;

    data.m_undefinedPairs.push_back({keyPtr, valuePtr});



    EXPECT_CALL(*key1, is(::testing::_)).WillOnce(::testing::Return(true));



    bool result = data.remove(*key1, memory);

    EXPECT_TRUE(result);

    EXPECT_EQ(data.m_undefinedPairs.size(), 0u);

}



TEST_F(NodeDataTest_653, RemoveFromUndefinedPairs_NodeDoesNotExist_653) {

    YAML::detail::node* keyPtr = key1.get();



    data.m_type = NodeType::Map;



    EXPECT_CALL(*key1, is(::testing::_)).WillOnce(::testing::Return(false));



    bool result = data.remove(*key1, memory);

    EXPECT_FALSE(result);

    EXPECT_EQ(data.m_undefinedPairs.size(), 0u);

}



TEST_F(NodeDataTest_653, RemoveFromMap_NodeExistsInBothCollections_653) {

    YAML::detail::node* keyPtr = key1.get();

    YAML::detail::node* valuePtr = value1.get();



    data.m_type = NodeType::Map;

    data.m_map.push_back({keyPtr, valuePtr});

    data.m_undefinedPairs.push_back({keyPtr, valuePtr});



    EXPECT_CALL(*key1, is(::testing::_)).WillRepeatedly(::testing::Return(true));



    bool result = data.remove(*key1, memory);

    EXPECT_TRUE(result);

    EXPECT_EQ(data.m_map.size(), 0u);

    EXPECT_EQ(data.m_undefinedPairs.size(), 0u);

}



TEST_F(NodeDataTest_653, RemoveFromMap_NotAMap_653) {

    YAML::detail::node* keyPtr = key1.get();



    data.m_type = NodeType::Sequence;  // Not a map



    EXPECT_CALL(*key1, is(::testing::_)).Times(0);  // Should not be called



    bool result = data.remove(*key1, memory);

    EXPECT_FALSE(result);

}



}  // namespace detail

}  // namespace YAML
