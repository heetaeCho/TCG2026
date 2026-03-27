#include <gtest/gtest.h>

#include "re2/compile.cc"



namespace re2 {



class PatchListTest_287 : public ::testing::Test {

protected:

    Prog::Inst inst0;

};



TEST_F(PatchListTest_287, AppendEmptyLists_287) {

    PatchList l1 = {0, 0};

    PatchList l2 = {0, 0};

    PatchList result = PatchList::Append(&inst0, l1, l2);

    EXPECT_EQ(result.head, 0);

    EXPECT_EQ(result.tail, 0);

}



TEST_F(PatchListTest_287, AppendNonEmptyAndEmptyList_287) {

    PatchList l1 = {1, 3};

    PatchList l2 = {0, 0};

    PatchList result = PatchList::Append(&inst0, l1, l2);

    EXPECT_EQ(result.head, 1);

    EXPECT_EQ(result.tail, 3);

}



TEST_F(PatchListTest_287, AppendEmptyAndNonEmptyList_287) {

    PatchList l1 = {0, 0};

    PatchList l2 = {4, 6};

    PatchList result = PatchList::Append(&inst0, l1, l2);

    EXPECT_EQ(result.head, 4);

    EXPECT_EQ(result.tail, 6);

}



TEST_F(PatchListTest_287, AppendTwoNonEmptyLists_OddTail_287) {

    inst0.set_out(9); // Mocking the internal state of Inst for testing

    PatchList l1 = {1, 3}; // Tail is odd, indicating out1_

    PatchList l2 = {4, 6};

    PatchList result = PatchList::Append(&inst0, l1, l2);

    EXPECT_EQ(result.head, 1);

    EXPECT_EQ(result.tail, 6);

    EXPECT_EQ(inst0.out1_, 4); // Verify that out1_ was updated

}



TEST_F(PatchListTest_287, AppendTwoNonEmptyLists_EvenTail_287) {

    inst0.set_out(9); // Mocking the internal state of Inst for testing

    PatchList l1 = {1, 2}; // Tail is even, indicating out

    PatchList l2 = {4, 6};

    PatchList result = PatchList::Append(&inst0, l1, l2);

    EXPECT_EQ(result.head, 1);

    EXPECT_EQ(result.tail, 6);

    EXPECT_EQ(inst0.out(), 4); // Verify that out was updated

}



} // namespace re2
