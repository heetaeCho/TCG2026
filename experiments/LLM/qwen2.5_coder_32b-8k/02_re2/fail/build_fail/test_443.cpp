#include <gtest/gtest.h>

#include "dfa.h"

#include "sparse_set.h"



using namespace re2;



class WorkqTest_443 : public ::testing::Test {

protected:

    void SetUp() override {

        workq = new Workq(10, 5);

    }



    void TearDown() override {

        delete workq;

    }



    Workq* workq;

};



TEST_F(WorkqTest_443, ClearEmptiesTheSet_443) {

    workq->insert(1);

    workq->clear();

    EXPECT_EQ(workq->size(), 0);

}



TEST_F(WorkqTest_443, InsertIncreasesSize_443) {

    workq->insert(1);

    EXPECT_EQ(workq->size(), 1);

}



TEST_F(WorkqTest_443, InsertNewIncreasesSize_443) {

    workq->insert_new(2);

    EXPECT_EQ(workq->size(), 1);

}



TEST_F(WorkqTest_443, InsertSameElementDoesNotIncreaseSize_443) {

    workq->insert(1);

    workq->insert(1);

    EXPECT_EQ(workq->size(), 1);

}



TEST_F(WorkqTest_443, MaxmarkReturnsCorrectValue_443) {

    EXPECT_EQ(workq->maxmark(), 5);

}



TEST_F(WorkqTest_443, IsMarkInitialFalse_443) {

    EXPECT_FALSE(workq->is_mark(0));

}



TEST_F(WorkqTest_443, MarkChangesNextmark_443) {

    int initial_nextmark = workq->nextmark_;

    workq->mark();

    EXPECT_NE(initial_nextmark, workq->nextmark_);

}



TEST_F(WorkqTest_443, InsertBeyondMaxSizeThrows_443) {

    for (int i = 0; i < 15; ++i) { // 10 + 5 maxmarks

        workq->insert(i);

    }

    EXPECT_THROW(workq->insert(15), std::exception); // Assuming out-of-bounds throws an exception

}



TEST_F(WorkqTest_443, InsertNewBeyondMaxSizeThrows_443) {

    for (int i = 0; i < 15; ++i) { // 10 + 5 maxmarks

        workq->insert_new(i);

    }

    EXPECT_THROW(workq->insert_new(15), std::exception); // Assuming out-of-bounds throws an exception

}
