#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/PreScanOutputDev.h"

#include "GfxState.h"

#include "XRef.h"



using namespace testing;



class MockGfxState : public GfxState {

public:

    MOCK_METHOD0(getColorSpace, GfxColorSpace*());

    MOCK_METHOD0(getFillColor, GfxColor*());

    MOCK_CONST_METHOD0(getOpacity, double());

    MOCK_CONST_METHOD0(getBlendMode, GfxBlendMode());

};



class PreScanOutputDevTest : public Test {

protected:

    MockGfxState mock_state;

    XRef xref;



    PreScanOutputDev output_dev(PSLevel::psLevel1);

};



TEST_F(PreScanOutputDevTest_1656, UseDrawChar_ReturnsTrue_1656) {

    EXPECT_TRUE(output_dev.useDrawChar());

}



TEST_F(PreScanOutputDevTest_1656, UseTilingPatternFill_ReturnsFalseByDefault_1656) {

    EXPECT_FALSE(output_dev.useTilingPatternFill());

}



TEST_F(PreScanOutputDevTest_1656, UseShadedFills_ReturnsFalseForAnyType_1656) {

    EXPECT_FALSE(output_dev.useShadedFills(0));

    EXPECT_FALSE(output_dev.useShadedFills(1));

    EXPECT_FALSE(output_dev.useShadedFills(-1));

}



TEST_F(PreScanOutputDevTest_1656, InterpretType3Chars_ReturnsFalseByDefault_1656) {

    EXPECT_FALSE(output_dev.interpretType3Chars());

}



TEST_F(PreScanOutputDevTest_1656, IsMonochrome_ReturnsFalseByDefault_1656) {

    EXPECT_FALSE(output_dev.isMonochrome());

}



TEST_F(PreScanOutputDevTest_1656, IsGray_ReturnsFalseByDefault_1656) {

    EXPECT_FALSE(output_dev.isGray());

}



TEST_F(PreScanOutputDevTest_1656, UsesTransparency_ReturnsFalseByDefault_1656) {

    EXPECT_FALSE(output_dev.usesTransparency());

}



TEST_F(PreScanOutputDevTest_1656, IsAllGDI_ReturnsFalseByDefault_1656) {

    EXPECT_FALSE(output_dev.isAllGDI());

}



TEST_F(PreScanOutputDevTest_1656, UsesPatternImageMask_ReturnsFalseByDefault_1656) {

    EXPECT_FALSE(output_dev.usesPatternImageMask());

}
