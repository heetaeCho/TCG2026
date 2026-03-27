#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "OutputDev.h"



using namespace testing;



class MockGfxState : public GfxState {

public:

    MOCK_METHOD(void, dummy, (), (override));

};



class OutputDevTest_1062 : public ::testing::Test {

protected:

    OutputDev outputDev;

    MockGfxState mockGfxState;

};



TEST_F(OutputDevTest_1062, NeedCharCount_ReturnsFalse_1062) {

    EXPECT_FALSE(outputDev.needCharCount());

}



TEST_F(OutputDevTest_1062, UpsideDown_DefaultBehavior_1062) {

    EXPECT_CALL(mockGfxState, dummy()).Times(0);

    EXPECT_FALSE(outputDev.upsideDown());

}



TEST_F(OutputDevTest_1062, UseDrawChar_DefaultBehavior_1062) {

    EXPECT_CALL(mockGfxState, dummy()).Times(0);

    EXPECT_FALSE(outputDev.useDrawChar());

}



TEST_F(OutputDevTest_1062, InterpretType3Chars_DefaultBehavior_1062) {

    EXPECT_CALL(mockGfxState, dummy()).Times(0);

    EXPECT_FALSE(outputDev.interpretType3Chars());

}



TEST_F(OutputDevTest_1062, UseTilingPatternFill_DefaultBehavior_1062) {

    EXPECT_CALL(mockGfxState, dummy()).Times(0);

    EXPECT_FALSE(outputDev.useTilingPatternFill());

}



TEST_F(OutputDevTest_1062, UseShadedFills_DefaultBehavior_1062) {

    EXPECT_CALL(mockGfxState, dummy()).Times(0);

    EXPECT_FALSE(outputDev.useShadedFills(0));

}



TEST_F(OutputDevTest_1062, UseFillColorStop_DefaultBehavior_1062) {

    EXPECT_CALL(mockGfxState, dummy()).Times(0);

    EXPECT_FALSE(outputDev.useFillColorStop());

}



TEST_F(OutputDevTest_1062, UseDrawForm_DefaultBehavior_1062) {

    EXPECT_CALL(mockGfxState, dummy()).Times(0);

    EXPECT_FALSE(outputDev.useDrawForm());

}



TEST_F(OutputDevTest_1062, NeedNonText_DefaultBehavior_1062) {

    EXPECT_CALL(mockGfxState, dummy()).Times(0);

    EXPECT_FALSE(outputDev.needNonText());

}



TEST_F(OutputDevTest_1062, NeedClipToCropBox_DefaultBehavior_1062) {

    EXPECT_CALL(mockGfxState, dummy()).Times(0);

    EXPECT_FALSE(outputDev.needClipToCropBox());

}



TEST_F(OutputDevTest_1062, SupportJPXtransparency_DefaultBehavior_1062) {

    EXPECT_CALL(mockGfxState, dummy()).Times(0);

    EXPECT_FALSE(outputDev.supportJPXtransparency());

}



TEST_F(OutputDevTest_1062, GetVectorAntialias_DefaultBehavior_1062) {

    EXPECT_CALL(mockGfxState, dummy()).Times(0);

    EXPECT_FALSE(outputDev.getVectorAntialias());

}
