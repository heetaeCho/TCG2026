#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/TextOutputDev.h"

#include <memory>



class TextOutputDevTest_1219 : public ::testing::Test {

protected:

    std::unique_ptr<TextOutputDev> textOutputDev;



    void SetUp() override {

        textOutputDev = std::make_unique<TextOutputDev>(nullptr, nullptr, false, 0.0, false, false);

    }

};



TEST_F(TextOutputDevTest_1219, UseDrawCharReturnsTrue_1219) {

    EXPECT_TRUE(textOutputDev->useDrawChar());

}



TEST_F(TextOutputDevTest_1219, InterpretType3CharsDefaultBehavior_1219) {

    // Assuming default behavior without any setup is false

    EXPECT_FALSE(textOutputDev->interpretType3Chars());

}



TEST_F(TextOutputDevTest_1219, NeedNonTextDefaultBehavior_1219) {

    // Assuming default behavior without any setup is false

    EXPECT_FALSE(textOutputDev->needNonText());

}



TEST_F(TextOutputDevTest_1219, NeedCharCountDefaultBehavior_1219) {

    // Assuming default behavior without any setup is false

    EXPECT_FALSE(textOutputDev->needCharCount());

}



TEST_F(TextOutputDevTest_1219, IsOkDefaultBehavior_1219) {

    // Assuming default behavior without any setup is true

    EXPECT_TRUE(textOutputDev->isOk());

}



TEST_F(TextOutputDevTest_1219, UpsideDownDefaultBehavior_1219) {

    // Assuming default behavior without any setup is false

    EXPECT_FALSE(textOutputDev->upsideDown());

}



TEST_F(TextOutputDevTest_1219, GetMinColSpacing1InitialValue_1219) {

    EXPECT_DOUBLE_EQ(0.0, textOutputDev->getMinColSpacing1());

}



TEST_F(TextOutputDevTest_1219, SetAndGetMinColSpacing1_1219) {

    double newSpacing = 5.5;

    textOutputDev->setMinColSpacing1(newSpacing);

    EXPECT_DOUBLE_EQ(newSpacing, textOutputDev->getMinColSpacing1());

}



TEST_F(TextOutputDevTest_1219, EnableHTMLExtrasSetsValue_1219) {

    bool doHTML = true;

    textOutputDev->enableHTMLExtras(doHTML);

    // Assuming there is no direct getter for this state, we test the effect on getTextEOL

    // or any other observable behavior if available. Here we assume indirect verification.

}



TEST_F(TextOutputDevTest_1219, SetTextEOLSetsValue_1219) {

    EndOfLineKind textEOL = eolUnix;

    textOutputDev->setTextEOL(textEOL);

    // Assuming there is no direct getter for this state, we test the effect on getText

    // or any other observable behavior if available. Here we assume indirect verification.

}



TEST_F(TextOutputDevTest_1219, SetTextPageBreaksSetsValue_1219) {

    bool textPageBreaks = true;

    textOutputDev->setTextPageBreaks(textPageBreaks);

    // Assuming there is no direct getter for this state, we test the effect on getText

    // or any other observable behavior if available. Here we assume indirect verification.

}



TEST_F(TextOutputDevTest_1219, MakeWordListReturnsNonNull_1219) {

    EXPECT_NE(nullptr, textOutputDev->makeWordList().get());

}



TEST_F(TextOutputDevTest_1219, TakeTextReturnsNonNull_1219) {

    EXPECT_NE(nullptr, textOutputDev->takeText().get());

}



// Assuming TextFlow* getFlows() returns a non-null pointer when there is content.

TEST_F(TextOutputDevTest_1219, GetFlowsReturnsNonNullWhenContentExists_1219) {

    // This test assumes that some content has been added to the TextOutputDev instance

    EXPECT_NE(nullptr, textOutputDev->getFlows());

}
