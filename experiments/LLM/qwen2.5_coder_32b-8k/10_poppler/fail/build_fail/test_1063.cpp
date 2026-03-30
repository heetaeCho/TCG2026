#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/OutputDev.h"



class OutputDevTest_1063 : public ::testing::Test {

protected:

    std::unique_ptr<OutputDev> outputDev;



    void SetUp() override {

        outputDev = std::make_unique<OutputDev>();

    }

};



TEST_F(OutputDevTest_1063, NeedClipToCropBox_DefaultBehavior_1063) {

    EXPECT_FALSE(outputDev->needClipToCropBox());

}



// Test for boundary conditions and exceptional/error cases

TEST_F(OutputDevTest_1063, CheckPageSlice_DefaultValues_1063) {

    bool result = outputDev->checkPageSlice(nullptr, 0.0, 0.0, 0, false, false, 0, 0, 0, 0, false);

    EXPECT_FALSE(result);

}



TEST_F(OutputDevTest_1063, CheckPageSlice_NegativeValues_1063) {

    bool result = outputDev->checkPageSlice(nullptr, -1.0, -1.0, -1, true, true, -1, -1, -1, -1, false);

    EXPECT_FALSE(result);

}



TEST_F(OutputDevTest_1063, CheckPageSlice_ZeroWidthHeight_1063) {

    bool result = outputDev->checkPageSlice(nullptr, 0.0, 0.0, 0, true, true, 0, 0, 0, 0, false);

    EXPECT_FALSE(result);

}



// Test for normal operation

TEST_F(OutputDevTest_1063, UseDrawChar_DefaultBehavior_1063) {

    EXPECT_FALSE(outputDev->useDrawChar());

}



TEST_F(OutputDevTest_1063, InterpretType3Chars_DefaultBehavior_1063) {

    EXPECT_FALSE(outputDev->interpretType3Chars());

}



// Test for external interactions (not applicable in this case since no external collaborators are involved)

```


