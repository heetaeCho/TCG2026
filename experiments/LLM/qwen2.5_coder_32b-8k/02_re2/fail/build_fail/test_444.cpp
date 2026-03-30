#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/dfa.h"



using namespace re2;



class WorkqTest : public ::testing::Test {

protected:

    Workq workq;

    

    WorkqTest() : workq(10, 5) {}

};



TEST_F(WorkqTest_444, MarkSetsLastWasMarkFalse_444) {

    workq.mark();

    EXPECT_FALSE(workq.last_was_mark_);

}



TEST_F(WorkqTest_444, MarkDoesNotInsertIfAlreadyMarked_444) {

    int initial_size = workq.size();

    workq.mark();

    EXPECT_EQ(initial_size, workq.size());

}



TEST_F(WorkqTest_444, InsertIncreasesSize_444) {

    int initial_size = workq.size();

    workq.insert(5);

    EXPECT_GT(workq.size(), initial_size);

}



TEST_F(WorkqTest_444, InsertNewIncreasesSizeIfNotPresent_444) {

    int initial_size = workq.size();

    workq.insert_new(3);

    EXPECT_GT(workq.size(), initial_size);

}



TEST_F(WorkqTest_444, InsertNewDoesNotIncreaseSizeIfPresent_444) {

    workq.insert_new(7);

    int initial_size = workq.size();

    workq.insert_new(7);

    EXPECT_EQ(initial_size, workq.size());

}



TEST_F(WorkqTest_444, ClearResetsAllStates_444) {

    workq.insert(2);

    workq.mark();

    workq.clear();

    EXPECT_EQ(workq.size(), 0);

    EXPECT_TRUE(workq.last_was_mark_);

}



TEST_F(WorkqTest_444, IsMarkReturnsTrueForMarkedElement_444) {

    workq.mark();

    EXPECT_TRUE(workq.is_mark(workq.nextmark_));

}



TEST_F(WorkqTest_444, MaxmarkReturnsCorrectValue_444) {

    EXPECT_EQ(workq.maxmark(), 5);

}
