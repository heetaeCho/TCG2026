#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Initialize with some arbitrary values for DPI and page box

        PDFRectangle pageBox = {0, 0, 100, 200};

        gfxState = std::make_unique<GfxState>(300.0, 300.0, &pageBox, 0, false);

    }



    virtual void TearDown() {

        gfxState.reset();

    }



    std::unique_ptr<GfxState> gfxState;

};



TEST_F(GfxStateTest_568, GetX1_ReturnsCorrectValue_568) {

    double expectedX1 = 0.0; // Assuming initial value based on PDFRectangle

    EXPECT_DOUBLE_EQ(expectedX1, gfxState->getX1());

}



TEST_F(GfxStateTest_568, GetY1_ReturnsCorrectValue_568) {

    double expectedY1 = 0.0; // Assuming initial value based on PDFRectangle

    EXPECT_DOUBLE_EQ(expectedY1, gfxState->getY1());

}



TEST_F(GfxStateTest_568, GetX2_ReturnsCorrectValue_568) {

    double expectedX2 = 100.0; // Assuming initial value based on PDFRectangle

    EXPECT_DOUBLE_EQ(expectedX2, gfxState->getX2());

}



TEST_F(GfxStateTest_568, GetY2_ReturnsCorrectValue_568) {

    double expectedY2 = 200.0; // Assuming initial value based on PDFRectangle

    EXPECT_DOUBLE_EQ(expectedY2, gfxState->getY2());

}



TEST_F(GfxStateTest_568, GetPageWidth_ReturnsCorrectValue_568) {

    double expectedPageWidth = 100.0; // Based on the provided page box

    EXPECT_DOUBLE_EQ(expectedPageWidth, gfxState->getPageWidth());

}



TEST_F(GfxStateTest_568, GetPageHeight_ReturnsCorrectValue_568) {

    double expectedPageHeight = 200.0; // Based on the provided page box

    EXPECT_DOUBLE_EQ(expectedPageHeight, gfxState->getPageHeight());

}



TEST_F(GfxStateTest_568, GetRotate_ReturnsInitialValue_568) {

    int expectedRotate = 0; // Initial value set in SetUp()

    EXPECT_EQ(expectedRotate, gfxState->getRotate());

}



TEST_F(GfxStateTest_568, SetCTM_ModifiesCTMCorrectly_568) {

    double a = 1.0, b = 2.0, c = 3.0, d = 4.0, e = 5.0, f = 6.0;

    gfxState->setCTM(a, b, c, d, e, f);

    const std::array<double, 6>& currentCTM = gfxState->getCTM();

    EXPECT_DOUBLE_EQ(a, currentCTM[0]);

    EXPECT_DOUBLE_EQ(b, currentCTM[1]);

    EXPECT_DOUBLE_EQ(c, currentCTM[2]);

    EXPECT_DOUBLE_EQ(d, currentCTM[3]);

    EXPECT_DOUBLE_EQ(e, currentCTM[4]);

    EXPECT_DOUBLE_EQ(f, currentCTM[5]);

}



TEST_F(GfxStateTest_568, ConcatCTM_ModifiesCTMAfterConcatenation_568) {

    double initialA = 1.0, initialB = 2.0, initialC = 3.0, initialD = 4.0, initialE = 5.0, initialF = 6.0;

    gfxState->setCTM(initialA, initialB, initialC, initialD, initialE, initialF);



    double concatA = 2.0, concatB = 3.0, concatC = 4.0, concatD = 5.0, concatE = 6.0, concatF = 7.0;

    gfxState->concatCTM(concatA, concatB, concatC, concatD, concatE, concatF);



    const std::array<double, 6>& currentCTM = gfxState->getCTM();

    EXPECT_DOUBLE_EQ((initialA * concatA) + (initialC * concatB), currentCTM[0]);

    EXPECT_DOUBLE_EQ((initialB * concatA) + (initialD * concatB), currentCTM[1]);

    EXPECT_DOUBLE_EQ((initialA * concatC) + (initialC * concatD), currentCTM[2]);

    EXPECT_DOUBLE_EQ((initialB * concatC) + (initialD * concatD), currentCTM[3]);

    EXPECT_DOUBLE_EQ((initialA * concatE) + (initialC * concatF) + initialE, currentCTM[4]);

    EXPECT_DOUBLE_EQ((initialB * concatE) + (initialD * concatF) + initialF, currentCTM[5]);

}



TEST_F(GfxStateTest_568, Save_RestoresCorrectStateAfterModification_568) {

    double a = 1.0, b = 2.0, c = 3.0, d = 4.0, e = 5.0, f = 6.0;

    gfxState->setCTM(a, b, c, d, e, f);

    GfxState* savedState = gfxState->save();



    double newA = 2.0, newB = 3.0, newC = 4.0, newD = 5.0, newE = 6.0, newF = 7.0;

    gfxState->setCTM(newA, newB, newC, newD, newE, newF);



    gfxState->restore();



    const std::array<double, 6>& currentCTM = gfxState->getCTM();

    EXPECT_DOUBLE_EQ(a, currentCTM[0]);

    EXPECT_DOUBLE_EQ(b, currentCTM[1]);

    EXPECT_DOUBLE_EQ(c, currentCTM[2]);

    EXPECT_DOUBLE_EQ(d, currentCTM[3]);

    EXPECT_DOUBLE_EQ(e, currentCTM[4]);

    EXPECT_DOUBLE_EQ(f, currentCTM[5]);



    delete savedState;

}
