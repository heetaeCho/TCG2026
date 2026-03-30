#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/dfa.h"



namespace re2 {



class DFA_WorkqTest : public ::testing::Test {

protected:

    Workq workq;

    DFA_WorkqTest() : workq(10, 5) {} // Example initialization

};



TEST_F(DFA_WorkqTest_445, InitialSizeIsCorrect_445) {

    EXPECT_EQ(workq.size(), 0);

}



TEST_F(DFA_WorkqTest_445, InsertIncreasesSize_445) {

    workq.insert(1);

    EXPECT_EQ(workq.size(), 1);

}



TEST_F(DFA_WorkqTest_445, MarkIncreasesSizeByMaxmark_445) {

    int initial_size = workq.size();

    workq.mark();

    EXPECT_EQ(workq.size(), initial_size + workq.maxmark());

}



TEST_F(DFA_WorkqTest_445, ClearResetsSizeToZero_445) {

    workq.insert(1);

    workq.clear();

    EXPECT_EQ(workq.size(), 0);

}



TEST_F(DFA_WorkqTest_445, MaxmarkReturnsCorrectValue_445) {

    EXPECT_EQ(workq.maxmark(), 5); // Based on the constructor parameters

}



TEST_F(DFA_WorkqTest_445, InsertNewIncreasesSize_445) {

    workq.insert_new(1);

    EXPECT_EQ(workq.size(), 1);

}



TEST_F(DFA_WorkqTest_445, InsertSameIdTwiceDoesNotIncreaseSize_445) {

    workq.insert(1);

    workq.insert(1);

    EXPECT_EQ(workq.size(), 1);

}



TEST_F(DFA_WorkqTest_445, MarkSetsLastWasMarkTrue_445) {

    workq.mark();

    EXPECT_TRUE(workq.is_mark(workq.maxmark() - 1));

}



} // namespace re2
