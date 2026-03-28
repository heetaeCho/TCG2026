#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/detail/node.h"



using namespace YAML::detail;



class NodeTest_258 : public ::testing::Test {

protected:

    Node keyNode;

    Node valueNode;

    shared_memory_holder pMemory;

};



TEST_F(NodeTest_258, InsertIncreasesSize_258) {

    Node testNode;

    size_t initialSize = testNode.size();

    testNode.insert(keyNode, valueNode, pMemory);

    EXPECT_EQ(testNode.size(), initialSize + 1);

}



TEST_F(NodeTest_258, InsertSetsDependencyForKey_258) {

    Node testNode;

    testNode.insert(keyNode, valueNode, pMemory);

    EXPECT_TRUE(std::find(keyNode.begin(), keyNode.end(), &testNode) != keyNode.end());

}



TEST_F(NodeTest_258, InsertSetsDependencyForValue_258) {

    Node testNode;

    testNode.insert(keyNode, valueNode, pMemory);

    EXPECT_TRUE(std::find(valueNode.begin(), valueNode.end(), &testNode) != valueNode.end());

}



TEST_F(NodeTest_258, InsertWithUndefinedKeyAndValue_258) {

    Node testNode;

    Node undefinedKey;

    Node undefinedValue;

    testNode.insert(undefinedKey, undefinedValue, pMemory);

    EXPECT_EQ(testNode.size(), 1);

}



TEST_F(NodeTest_258, InsertTwiceSameKeyValue_258) {

    Node testNode;

    testNode.insert(keyNode, valueNode, pMemory);

    size_t initialSize = testNode.size();

    testNode.insert(keyNode, valueNode, pMemory);

    EXPECT_EQ(testNode.size(), initialSize); // Assuming no duplicates are allowed

}



TEST_F(NodeTest_258, InsertWithNullMemory_258) {

    Node testNode;

    shared_memory_holder nullMemory = nullptr;

    EXPECT_THROW(testNode.insert(keyNode, valueNode, nullMemory), std::exception); // Assuming an exception is thrown for null memory

}
