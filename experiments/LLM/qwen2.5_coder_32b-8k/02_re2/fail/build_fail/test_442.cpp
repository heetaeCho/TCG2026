#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "dfa.h"



namespace re2 {



class DFA_Test_442 : public ::testing::Test {

protected:

    Workq workq;



    DFA_Test_442() : workq(10, 5) {} // Example initialization

};



TEST_F(DFA_Test_442, Maxmark_ReturnsCorrectValue_442) {

    EXPECT_EQ(workq.maxmark(), 5);

}



TEST_F(DFA_Test_442, Size_InitSizeIsZero_442) {

    EXPECT_EQ(workq.size(), 0);

}



TEST_F(DFA_Test_442, Insert_IncreasesSize_442) {

    workq.insert(1);

    EXPECT_EQ(workq.size(), 1);

}



TEST_F(DFA_Test_442, InsertNew_IncreasesSize_442) {

    workq.insert_new(1);

    EXPECT_EQ(workq.size(), 1);

}



TEST_F(DFA_Test_442, Clear_ResetsSizeToZero_442) {

    workq.insert(1);

    workq.clear();

    EXPECT_EQ(workq.size(), 0);

}



TEST_F(DFA_Test_442, Mark_IncrementsNextmark_442) {

    int initial_nextmark = workq.maxmark() + workq.size();

    workq.mark();

    EXPECT_EQ(workq.nextmark_, initial_nextmark + 1);

}



TEST_F(DFA_Test_442, IsMark_ReturnsTrueForMarkedIndex_442) {

    workq.insert(1);

    workq.mark();

    EXPECT_TRUE(workq.is_mark(1));

}



TEST_F(DFA_Test_442, IsMark_ReturnsFalseForUnmarkedIndex_442) {

    workq.insert(1);

    EXPECT_FALSE(workq.is_mark(1));

}



TEST_F(DFA_Test_442, Insert_OutOfBoundsDoesNotIncreaseSize_442) {

    workq.insert(workq.n_ + workq.maxmark() + 1);

    EXPECT_EQ(workq.size(), 0);

}



TEST_F(DFA_Test_442, InsertNew_OutOfBoundsThrowsNoException_442) {

    workq.insert_new(workq.n_ + workq.maxmark() + 1);

    EXPECT_EQ(workq.size(), 0);

}



} // namespace re2
