#include <gtest/gtest.h>

#include "re2/compile.h"



namespace re2 {



class PatchListTest_285 : public ::testing::Test {

protected:

    uint32_t p1 = 10;

    uint32_t p2 = 20;

};



TEST_F(PatchListTest_285, MkInitialization_285) {

    PatchList pl = PatchList::Mk(p1);

    EXPECT_EQ(pl.head, p1);

    EXPECT_EQ(pl.tail, p1);

}



TEST_F(PatchListTest_285, AppendNonEmptyLists_285) {

    PatchList l1 = PatchList::Mk(p1);

    PatchList l2 = PatchList::Mk(p2);

    PatchList result = PatchList::Append(nullptr, l1, l2);

    EXPECT_EQ(result.head, p1);

    EXPECT_EQ(result.tail, p2);

}



TEST_F(PatchListTest_285, AppendEmptyFirstList_285) {

    PatchList l1 = PatchList{0, 0}; // Assuming {0, 0} represents an empty list

    PatchList l2 = PatchList::Mk(p2);

    PatchList result = PatchList::Append(nullptr, l1, l2);

    EXPECT_EQ(result.head, p2);

    EXPECT_EQ(result.tail, p2);

}



TEST_F(PatchListTest_285, AppendEmptySecondList_285) {

    PatchList l1 = PatchList::Mk(p1);

    PatchList l2 = PatchList{0, 0}; // Assuming {0, 0} represents an empty list

    PatchList result = PatchList::Append(nullptr, l1, l2);

    EXPECT_EQ(result.head, p1);

    EXPECT_EQ(result.tail, p1);

}



TEST_F(PatchListTest_285, AppendBothEmptyLists_285) {

    PatchList l1 = PatchList{0, 0}; // Assuming {0, 0} represents an empty list

    PatchList l2 = PatchList{0, 0}; // Assuming {0, 0} represents an empty list

    PatchList result = PatchList::Append(nullptr, l1, l2);

    EXPECT_EQ(result.head, 0);

    EXPECT_EQ(result.tail, 0);

}



} // namespace re2
