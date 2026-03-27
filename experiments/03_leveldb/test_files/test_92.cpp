#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/skiplist.h"



namespace leveldb {



class SkipListNodeTest : public ::testing::Test {

protected:

    SkipListNodeTest() : key1("key1"), node(key1) {}



    const std::string key1;

    Node node;

};



TEST_F(SkipListNodeTest_92, NoBarrier_Next_ReturnsNullForUnsetNext_92) {

    EXPECT_EQ(node.NoBarrier_Next(0), nullptr);

}



TEST_F(SkipListNodeTest_92, NoBarrier_Next_ReturnsSetNode_92) {

    Node nextNode("key2");

    node.NoBarrier_SetNext(0, &nextNode);

    EXPECT_EQ(node.NoBarrier_Next(0), &nextNode);

}



TEST_F(SkipListNodeTest_92, NoBarrier_Next_BoundaryConditionNegativeIndex_92) {

    EXPECT_DEATH({node.NoBarrier_Next(-1);}, "assertion failed");

}



TEST_F(SkipListNodeTest_92, KeyIsProperlyStored_92) {

    EXPECT_EQ(node.key, key1);

}



}  // namespace leveldb
