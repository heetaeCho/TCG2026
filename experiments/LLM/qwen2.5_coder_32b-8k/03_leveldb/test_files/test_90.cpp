#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/skiplist.h"



namespace leveldb {

    class SkipListTest_90 : public ::testing::Test {

    protected:

        Key testKey;

        Node* node;



        void SetUp() override {

            testKey = 42; // Assuming Key is an int for simplicity

            node = new Node(testKey);

        }



        void TearDown() override {

            delete node;

        }

    };



    TEST_F(SkipListTest_90, Next_ReturnsNullForNonExistentLevel_90) {

        EXPECT_EQ(node->Next(0), nullptr);

    }



    TEST_F(SkipListTest_90, SetNextAndGetNext_WorkCorrectly_90) {

        Node* nextNode = new Node(43); // Assuming Key is an int for simplicity

        node->SetNext(0, nextNode);

        EXPECT_EQ(node->Next(0), nextNode);

        delete nextNode;

    }



    TEST_F(SkipListTest_90, NoBarrier_Next_ReturnsNullForNonExistentLevel_90) {

        EXPECT_EQ(node->NoBarrier_Next(0), nullptr);

    }



    TEST_F(SkipListTest_90, NoBarrier_SetNextAndGetNext_WorkCorrectly_90) {

        Node* nextNode = new Node(43); // Assuming Key is an int for simplicity

        node->NoBarrier_SetNext(0, nextNode);

        EXPECT_EQ(node->NoBarrier_Next(0), nextNode);

        delete nextNode;

    }



    TEST_F(SkipListTest_90, Next_AssertFailsForNegativeLevel_90) {

        EXPECT_DEATH(node->Next(-1), ".*assertion.*n >= 0.*");

    }



    TEST_F(SkipListTest_90, NoBarrier_Next_AssertFailsForNegativeLevel_90) {

        EXPECT_DEATH(node->NoBarrier_Next(-1), ".*assertion.*n >= 0.*");

    }

}
