#include <gtest/gtest.h>

#include <gmock/gmock.h>



#include "OutputDev.h"



using namespace testing;



class OutputDevTest : public ::testing::Test {

protected:

    std::unique_ptr<OutputDev> output_dev;



    void SetUp() override {

        output_dev = std::make_unique<OutputDev>();

    }

};



TEST_F(OutputDevTest_1060, UseDrawFormReturnsFalseByDefault_1060) {

    EXPECT_FALSE(output_dev->useDrawForm());

}



TEST_F(OutputDevTest_1060, UpsideDownReturnsFalseByDefault_1060) {

    EXPECT_FALSE(output_dev->upsideDown());

}



TEST_F(OutputDevTest_1060, UseDrawCharReturnsFalseByDefault_1060) {

    EXPECT_FALSE(output_dev->useDrawChar());

}



TEST_F(OutputDevTest_1060, InterpretType3CharsReturnsFalseByDefault_1060) {

    EXPECT_FALSE(output_dev->interpretType3Chars());

}



TEST_F(OutputDevTest_1060, UseTilingPatternFillReturnsFalseByDefault_1060) {

    EXPECT_FALSE(output_dev->useTilingPatternFill());

}



TEST_F(OutputDevTest_1060, UseShadedFillsReturnsFalseForArbitraryType_1060) {

    EXPECT_FALSE(output_dev->useShadedFills(0));

}



TEST_F(OutputDevTest_1060, UseFillColorStopReturnsFalseByDefault_1060) {

    EXPECT_FALSE(output_dev->useFillColorStop());

}



TEST_F(OutputDevTest_1060, NeedNonTextReturnsFalseByDefault_1060) {

    EXPECT_FALSE(output_dev->needNonText());

}



TEST_F(OutputDevTest_1060, NeedCharCountReturnsFalseByDefault_1060) {

    EXPECT_FALSE(output_dev->needCharCount());

}



TEST_F(OutputDevTest_1060, NeedClipToCropBoxReturnsFalseByDefault_1060) {

    EXPECT_FALSE(output_dev->needClipToCropBox());

}



TEST_F(OutputDevTest_1060, SupportJPXtransparencyReturnsFalseByDefault_1060) {

    EXPECT_FALSE(output_dev->supportJPXtransparency());

}



TEST_F(OutputDevTest_1060, GetVectorAntialiasReturnsTrueByDefault_1060) {

    EXPECT_TRUE(output_dev->getVectorAntialias());

}
