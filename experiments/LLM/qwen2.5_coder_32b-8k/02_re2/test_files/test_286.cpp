#include <gtest/gtest.h>

#include "re2/prog.h"

#include "re2/compile.cc"



using namespace re2;



class PatchListTest_286 : public ::testing::Test {

protected:

    Prog::Inst inst0[10];



    void SetUp() override {

        for (int i = 0; i < 10; ++i) {

            inst0[i].set_out(i);

            inst0[i].out1_ = i + 1;

        }

    }

};



TEST_F(PatchListTest_286, PatchEmptyPatchList_286) {

    PatchList l = PatchList{0, 0};

    uint32_t p = 5;

    PatchList::Patch(inst0, l, p);

    // No change expected since the list is empty

    for (int i = 0; i < 10; ++i) {

        EXPECT_EQ(inst0[i].out(), i);

        EXPECT_EQ(inst0[i].out1_, i + 1);

    }

}



TEST_F(PatchListTest_286, PatchSingleElementPatchListEvenIndex_286) {

    PatchList l = PatchList{2, 2}; // Pointing to inst0[1]

    uint32_t p = 5;

    PatchList::Patch(inst0, l, p);

    EXPECT_EQ(inst0[1].out(), p);

    EXPECT_EQ(inst0[1].out1_, 2);

}



TEST_F(PatchListTest_286, PatchSingleElementPatchListOddIndex_286) {

    PatchList l = PatchList{3, 3}; // Pointing to inst0[1] out1_

    uint32_t p = 5;

    PatchList::Patch(inst0, l, p);

    EXPECT_EQ(inst0[1].out(), 1);

    EXPECT_EQ(inst0[1].out1_, p);

}



TEST_F(PatchListTest_286, PatchMultipleElementsPatchList_286) {

    PatchList l = PatchList{2, 7}; // Pointing to inst0[1] and then inst0[3]

    uint32_t p = 5;

    PatchList::Patch(inst0, l, p);

    EXPECT_EQ(inst0[1].out(), p); // out of inst0[1] is patched

    EXPECT_EQ(inst0[1].out1_, 2); 

    EXPECT_EQ(inst0[3].out1_, p); // out1_ of inst0[3] is patched

    EXPECT_EQ(inst0[3].out(), 4);

}



TEST_F(PatchListTest_286, PatchBoundaryConditionEvenIndex_286) {

    PatchList l = PatchList{18, 18}; // Pointing to the last element's out_

    uint32_t p = 5;

    PatchList::Patch(inst0, l, p);

    EXPECT_EQ(inst0[9].out(), 9);

    EXPECT_EQ(inst0[9].out1_, p);

}



TEST_F(PatchListTest_286, PatchBoundaryConditionOddIndex_286) {

    PatchList l = PatchList{17, 17}; // Pointing to the last element's out

    uint32_t p = 5;

    PatchList::Patch(inst0, l, p);

    EXPECT_EQ(inst0[8].out(), p);

    EXPECT_EQ(inst0[8].out1_, 9);

}



TEST_F(PatchListTest_286, PatchInvalidIndexNoChange_286) {

    PatchList l = PatchList{20, 20}; // Invalid index

    uint32_t p = 5;

    PatchList::Patch(inst0, l, p);

    for (int i = 0; i < 10; ++i) {

        EXPECT_EQ(inst0[i].out(), i);

        EXPECT_EQ(inst0[i].out1_, i + 1);

    }

}
