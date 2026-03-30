#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/skiplist.h"



namespace leveldb {



class SkipListTest_91 : public ::testing::Test {

protected:

    Key key1 = 42;

    Key key2 = 43;

    Node* node1;

    Node* node2;



    void SetUp() override {

        node1 = new Node(key1);

        node2 = new Node(key2);

    }



    void TearDown() override {

        delete node1;

        delete node2;

    }

};



TEST_F(SkipListTest_91, SetNextValidIndex_91) {

    node1->SetNext(0, node2);

    EXPECT_EQ(node1->Next(0), node2);

}



TEST_F(SkipListTest_91, SetNextMultipleIndices_91) {

    node1->SetNext(0, node2);

    node1->SetNext(1, nullptr);

    EXPECT_EQ(node1->Next(0), node2);

    EXPECT_EQ(node1->Next(1), nullptr);

}



TEST_F(SkipListTest_91, SetNextBoundaryCondition_91) {

    // Assuming there's a predefined maximum level for the SkipList

    const int max_level = 3; // Hypothetical value, replace with actual if known

    node1->SetNext(max_level - 1, node2);

    EXPECT_EQ(node1->Next(max_level - 1), node2);

}



TEST_F(SkipListTest_91, SetNextInvalidIndex_91) {

    ASSERT_DEATH({ node1->SetNext(-1, node2); }, "");

}



TEST_F(SkipListTest_91, NoBarrierSetNextValidIndex_91) {

    node1->NoBarrier_SetNext(0, node2);

    EXPECT_EQ(node1->NoBarrier_Next(0), node2);

}



}  // namespace leveldb
