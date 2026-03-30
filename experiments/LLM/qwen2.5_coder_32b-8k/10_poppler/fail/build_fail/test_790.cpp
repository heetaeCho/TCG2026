#include <gtest/gtest.h>

#include "poppler/Annot.h"



class AnnotTest_790 : public ::testing::Test {

protected:

    std::unique_ptr<Annot> annot;



    void SetUp() override {

        // Assuming a mock PDFDoc and PDFRectangle are available or can be created

        // For the purpose of this test, we will use nullptr as placeholders

        annot = std::make_unique<Annot>(nullptr, static_cast<PDFRectangle*>(nullptr));

    }

};



TEST_F(AnnotTest_790, GetAppearState_Default_ReturnsNullptr_790) {

    EXPECT_EQ(nullptr, annot->getAppearState());

}



TEST_F(AnnotTest_790, SetAppearanceStateAndGetAppearState_NormalOperation_ReturnsCorrectState_790) {

    const char* expectedState = "Normal";

    annot->setAppearanceState(expectedState);

    EXPECT_STREQ(expectedState, annot->getAppearState()->getCString());

}



TEST_F(AnnotTest_790, SetAppearanceStateAndGetAppearState_BoundaryCondition_EmptyString_ReturnsCorrectState_790) {

    const char* expectedState = "";

    annot->setAppearanceState(expectedState);

    EXPECT_STREQ(expectedState, annot->getAppearState()->getCString());

}



TEST_F(AnnotTest_790, SetAppearanceStateAndGetAppearState_BoundaryCondition_LongString_ReturnsCorrectState_790) {

    const char* expectedState = "A very long appearance state string that should be handled correctly by the Annot class";

    annot->setAppearanceState(expectedState);

    EXPECT_STREQ(expectedState, annot->getAppearState()->getCString());

}
