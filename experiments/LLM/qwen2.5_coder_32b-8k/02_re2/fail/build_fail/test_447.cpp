#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "dfa.cc"

#include "sparse_set.h"



using namespace re2;



class DFA_WorkqTest : public ::testing::Test {

protected:

    DFA::Workq workq;

    

    DFA_WorkqTest() : workq(10, 5) {}

};



TEST_F(DFA_WorkqTest_447, InsertNewIncreasesSize_447) {

    int initial_size = workq.size();

    workq.insert_new(3);

    EXPECT_EQ(workq.size(), initial_size + 1);

}



TEST_F(DFA_WorkqTest_447, InsertExistingDoesNotIncreaseSize_447) {

    workq.insert_new(3);

    int size_after_insert = workq.size();

    workq.insert_new(3); // Attempt to insert the same element again

    EXPECT_EQ(workq.size(), size_after_insert);

}



TEST_F(DFA_WorkqTest_447, ClearResetsSizeToZero_447) {

    workq.insert_new(1);

    workq.clear();

    EXPECT_EQ(workq.size(), 0);

}



TEST_F(DFA_WorkqTest_447, MarkIncreasesNextMark_447) {

    int initial_nextmark = workq.maxmark();

    workq.mark();

    EXPECT_EQ(workq.maxmark(), initial_nextmark + 1);

}



TEST_F(DFA_WorkqTest_447, InsertNewAfterClearDoesNotIncreaseMaxmark_447) {

    workq.insert_new(1);

    workq.clear();

    int initial_maxmark = workq.maxmark();

    workq.insert_new(2);

    EXPECT_EQ(workq.maxmark(), initial_maxmark);

}



TEST_F(DFA_WorkqTest_447, IsMarkReturnsTrueForMarkedElements_447) {

    int mark_index = workq.n_;

    workq.mark();

    EXPECT_TRUE(workq.is_mark(mark_index));

}



TEST_F(DFA_WorkqTest_447, IsMarkReturnsFalseForNonMarkedElements_447) {

    workq.insert_new(1);

    EXPECT_FALSE(workq.is_mark(1));

}
