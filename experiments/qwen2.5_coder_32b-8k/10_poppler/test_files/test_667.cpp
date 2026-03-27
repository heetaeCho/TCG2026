#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    double hDPI = 100.0;

    double vDPI = 100.0;

    PDFRectangle pageBox{0, 0, 612, 792};

    int rotate = 0;



    GfxState* state1 = new GfxState(hDPI, vDPI, &pageBox, rotate, false);

    GfxState* state2 = state1->save();

    GfxState* state3 = state2->save();



    ~GfxStateTest() {

        delete state1;

        delete state2;

        delete state3;

    }

};



TEST_F(GfxStateTest, IsParentState_WhenSameState_ReturnsTrue_667) {

    EXPECT_TRUE(state1->isParentState(state1));

}



TEST_F(GfxStateTest, IsParentState_WhenDirectChild_ReturnsTrue_667) {

    EXPECT_TRUE(state2->isParentState(state1));

}



TEST_F(GfxStateTest, IsParentState_WhenIndirectChild_ReturnsTrue_667) {

    EXPECT_TRUE(state3->isParentState(state1));

}



TEST_F(GfxStateTest, IsParentState_WhenDifferentBranch_ReturnsFalse_667) {

    GfxState* unrelatedState = new GfxState(hDPI, vDPI, &pageBox, rotate, false);

    EXPECT_FALSE(unrelatedState->isParentState(state1));

    delete unrelatedState;

}



TEST_F(GfxStateTest, IsParentState_WhenNullPassed_ReturnsFalse_667) {

    EXPECT_FALSE(state1->isParentState(nullptr));

}
