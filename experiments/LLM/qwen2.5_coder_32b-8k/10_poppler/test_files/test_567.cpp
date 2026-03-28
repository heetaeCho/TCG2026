#include <gtest/gtest.h>

#include "poppler/GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    void SetUp() override {

        gfxState = std::make_unique<GfxState>(300.0, 300.0, nullptr, 0, false);

    }



    void TearDown() override {

        gfxState.reset();

    }



    std::unique_ptr<GfxState> gfxState;

};



TEST_F(GfxStateTest_567, GetCTM_ReturnsInitializedMatrix_567) {

    Matrix m;

    gfxState->getCTM(&m);

    EXPECT_EQ(m.m[0], 1.0);

    EXPECT_EQ(m.m[1], 0.0);

    EXPECT_EQ(m.m[2], 0.0);

    EXPECT_EQ(m.m[3], 1.0);

    EXPECT_EQ(m.m[4], 0.0);

    EXPECT_EQ(m.m[5], 0.0);

}



TEST_F(GfxStateTest_567, SetCTM_UpdatesMatrix_567) {

    Matrix m;

    gfxState->setCTM(1.2, 2.3, 3.4, 4.5, 5.6, 6.7);

    gfxState->getCTM(&m);

    EXPECT_EQ(m.m[0], 1.2);

    EXPECT_EQ(m.m[1], 2.3);

    EXPECT_EQ(m.m[2], 3.4);

    EXPECT_EQ(m.m[3], 4.5);

    EXPECT_EQ(m.m[4], 5.6);

    EXPECT_EQ(m.m[5], 6.7);

}



TEST_F(GfxStateTest_567, ConcatCTM_ModifiesMatrix_567) {

    Matrix m;

    gfxState->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    gfxState->concatCTM(7.0, 8.0, 9.0, 10.0, 11.0, 12.0);

    gfxState->getCTM(&m);

    EXPECT_EQ(m.m[0], 37.0);   // (1*7 + 2*9)

    EXPECT_EQ(m.m[1], 46.0);   // (1*8 + 2*10)

    EXPECT_EQ(m.m[2], 57.0);   // (3*7 + 4*9)

    EXPECT_EQ(m.m[3], 74.0);   // (3*8 + 4*10)

    EXPECT_EQ(m.m[4], 80.0);   // (5*7 + 6*9 + 11)

    EXPECT_EQ(m.m[5], 102.0);  // (5*8 + 6*10 + 12)

}



TEST_F(GfxStateTest_567, ShiftCTMAndClip_TranslatesMatrix_567) {

    Matrix m;

    gfxState->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    gfxState->shiftCTMAndClip(10.0, 20.0);

    gfxState->getCTM(&m);

    EXPECT_EQ(m.m[0], 1.0);

    EXPECT_EQ(m.m[1], 2.0);

    EXPECT_EQ(m.m[2], 3.0);

    EXPECT_EQ(m.m[3], 4.0);

    EXPECT_EQ(m.m[4], 55.0);   // (5 + 1*10 + 2*20)

    EXPECT_EQ(m.m[5], 86.0);   // (6 + 3*10 + 4*20)

}



TEST_F(GfxStateTest_567, GetHDPI_ReturnsCorrectValue_567) {

    EXPECT_EQ(gfxState->getHDPI(), 300.0);

}



TEST_F(GfxStateTest_567, GetVDPI_ReturnsCorrectValue_567) {

    EXPECT_EQ(gfxState->getVDPI(), 300.0);

}
