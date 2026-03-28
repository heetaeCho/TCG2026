#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/OutputDev.h"



class OutputDevTest : public ::testing::Test {

protected:

    std::unique_ptr<OutputDev> outputDev;



    void SetUp() override {

        outputDev = std::make_unique<OutputDev>();

    }

};



TEST_F(OutputDevTest_1059, UseFillColorStop_ReturnsFalseByDefault_1059) {

    EXPECT_FALSE(outputDev->useFillColorStop());

}



// Since the class does not provide any setters or methods to modify

// the behavior of useFillColorStop, we can only test its default behavior.



TEST_F(OutputDevTest_1059, UpsideDown_ReturnsFalseByDefault_1059) {

    EXPECT_FALSE(outputDev->upsideDown());

}



TEST_F(OutputDevTest_1059, UseDrawChar_ReturnsFalseByDefault_1059) {

    EXPECT_FALSE(outputDev->useDrawChar());

}



TEST_F(OutputDevTest_1059, InterpretType3Chars_ReturnsFalseByDefault_1059) {

    EXPECT_FALSE(outputDev->interpretType3Chars());

}



TEST_F(OutputDevTest_1059, UseTilingPatternFill_ReturnsFalseByDefault_1059) {

    EXPECT_FALSE(outputDev->useTilingPatternFill());

}



TEST_F(OutputDevTest_1059, UseShadedFills_ReturnsFalseByDefault_1059) {

    EXPECT_FALSE(outputDev->useShadedFills(0));

}



TEST_F(OutputDevTest_1059, UseDrawForm_ReturnsFalseByDefault_1059) {

    EXPECT_FALSE(outputDev->useDrawForm());

}



TEST_F(OutputDevTest_1059, NeedNonText_ReturnsFalseByDefault_1059) {

    EXPECT_FALSE(outputDev->needNonText());

}



TEST_F(OutputDevTest_1059, NeedCharCount_ReturnsFalseByDefault_1059) {

    EXPECT_FALSE(outputDev->needCharCount());

}



TEST_F(OutputDevTest_1059, NeedClipToCropBox_ReturnsFalseByDefault_1059) {

    EXPECT_FALSE(outputDev->needClipToCropBox());

}



TEST_F(OutputDevTest_1059, SupportJPXtransparency_ReturnsFalseByDefault_1059) {

    EXPECT_FALSE(outputDev->supportJPXtransparency());

}
