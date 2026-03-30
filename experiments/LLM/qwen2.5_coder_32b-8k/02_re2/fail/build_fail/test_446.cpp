#include <gtest/gtest.h>

#include "re2/dfa.h"



namespace re2 {



class DFAWorkqTest : public ::testing::Test {

protected:

    void SetUp() override {

        workq = new Workq(10, 5);

    }



    void TearDown() override {

        delete workq;

    }



    Workq* workq;

};



TEST_F(DFAWorkqTest_NormalOperation_446, InsertIncreasesSize_446) {

    EXPECT_EQ(workq->size(), 0);

    workq->insert(1);

    EXPECT_EQ(workq->size(), 1);

}



TEST_F(DFAWorkqTest_NormalOperation_446, InsertSameIdDoesNotIncreaseSizeTwice_446) {

    workq->insert(1);

    workq->insert(1);

    EXPECT_EQ(workq->size(), 1);

}



TEST_F(DFAWorkqTest_BoundaryConditions_446, InsertMaxMarkPlusNIdIncreasesSize_446) {

    for (int i = 0; i < 15; ++i) { // n + maxmark

        workq->insert(i);

    }

    EXPECT_EQ(workq->size(), 15);

}



TEST_F(DFAWorkqTest_BoundaryConditions_446, InsertBeyondMaxMarkPlusNIdDoesNotInsert_446) {

    for (int i = 0; i < 20; ++i) { // beyond n + maxmark

        workq->insert(i);

    }

    EXPECT_EQ(workq->size(), 15);

}



TEST_F(DFAWorkqTest_NormalOperation_446, ClearEmptiesQueue_446) {

    workq->insert(1);

    workq->clear();

    EXPECT_EQ(workq->size(), 0);

}



TEST_F(DFAWorkqTest_NormalOperation_446, MarkSetsLastWasMarkToTrue_446) {

    workq->mark();

    EXPECT_TRUE(workq->last_was_mark_);

}



TEST_F(DFAWorkqTest_NormalOperation_446, MaxmarkReturnsCorrectValue_446) {

    EXPECT_EQ(workq->maxmark(), 5);

}



TEST_F(DFAWorkqTest_NormalOperation_446, IsMarkReturnsTrueForMarkedIndex_446) {

    int mark_index = workq->nextmark_;

    workq->insert(mark_index);

    workq->mark();

    EXPECT_TRUE(workq->is_mark(mark_index));

}



TEST_F(DFAWorkqTest_NormalOperation_446, IsMarkReturnsFalseForNonMarkedIndex_446) {

    int non_mark_index = 0;

    workq->insert(non_mark_index);

    EXPECT_FALSE(workq->is_mark(non_mark_index));

}



} // namespace re2
