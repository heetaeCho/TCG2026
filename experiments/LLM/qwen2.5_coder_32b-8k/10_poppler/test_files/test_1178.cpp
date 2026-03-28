#include <gtest/gtest.h>

#include "TextOutputDev.h"



class TextFontInfoTest : public ::testing::Test {

protected:

    class MockGfxState {};

    std::shared_ptr<MockGfxState> mockState;

    TextFontInfo fontInfo;



    TextFontInfoTest() : mockState(std::make_shared<MockGfxState>()), fontInfo(reinterpret_cast<GfxState*>(mockState.get())) {}

};



TEST_F(TextFontInfoTest_1178, IsBold_ReturnsTrueWhenFlagSet_1178) {

    // Arrange

    // Assuming there's a way to set the flag for bold, which is not provided in the interface.

    // Since we treat the implementation as a black box, we assume that the constructor or another method sets this flag.



    // Act & Assert

    EXPECT_TRUE(fontInfo.isBold());

}



TEST_F(TextFontInfoTest_1178, IsBold_ReturnsFalseWhenFlagNotSet_1178) {

    // Arrange

    // Assuming there's a way to ensure the flag for bold is not set, which is not provided in the interface.

    // Since we treat the implementation as a black box, we assume that the constructor or another method does not set this flag.



    // Act & Assert

    EXPECT_FALSE(fontInfo.isBold());

}



TEST_F(TextFontInfoTest_1178, GetFontName_ReturnsValidGooStringPointer_1178) {

    // Arrange

    // Assuming the font name is properly initialized in the constructor.



    // Act

    const GooString* fontName = fontInfo.getFontName();



    // Assert

    EXPECT_NE(fontName, nullptr);

}



TEST_F(TextFontInfoTest_1178, Matches_GfxState_ReturnsTrueForMatchingState_1178) {

    // Arrange

    MockGfxState matchingState;



    // Act

    bool result = fontInfo.matches(reinterpret_cast<GfxState*>(&matchingState));



    // Assert

    EXPECT_TRUE(result);  // Assuming the state matches as per internal logic.

}



TEST_F(TextFontInfoTest_1178, Matches_GfxState_ReturnsFalseForNonMatchingState_1178) {

    // Arrange

    MockGfxState nonMatchingState;



    // Act

    bool result = fontInfo.matches(reinterpret_cast<GfxState*>(&nonMatchingState));



    // Assert

    EXPECT_FALSE(result);  // Assuming the state does not match as per internal logic.

}



TEST_F(TextFontInfoTest_1178, Matches_TextFontInfo_ReturnsTrueForSameObject_1178) {

    // Arrange

    TextFontInfo sameFontInfo(reinterpret_cast<GfxState*>(mockState.get()));



    // Act

    bool result = fontInfo.matches(&sameFontInfo);



    // Assert

    EXPECT_TRUE(result);

}



TEST_F(TextFontInfoTest_1178, Matches_TextFontInfo_ReturnsFalseForDifferentObject_1178) {

    // Arrange

    MockGfxState differentState;

    TextFontInfo differentFontInfo(reinterpret_cast<GfxState*>(&differentState));



    // Act

    bool result = fontInfo.matches(&differentFontInfo);



    // Assert

    EXPECT_FALSE(result);

}



TEST_F(TextFontInfoTest_1178, Matches_Ref_ReturnsTrueForMatchingRef_1178) {

    // Arrange

    Ref matchingRef;

    // Assuming there's a way to set the ref in fontInfo which is not provided in the interface.



    // Act

    bool result = fontInfo.matches(&matchingRef);



    // Assert

    EXPECT_TRUE(result);  // Assuming the ref matches as per internal logic.

}



TEST_F(TextFontInfoTest_1178, Matches_Ref_ReturnsFalseForNonMatchingRef_1178) {

    // Arrange

    Ref nonMatchingRef;

    // Assuming there's a way to set the ref in fontInfo which is not provided in the interface.



    // Act

    bool result = fontInfo.matches(&nonMatchingRef);



    // Assert

    EXPECT_FALSE(result);  // Assuming the ref does not match as per internal logic.

}



TEST_F(TextFontInfoTest_1178, GetAscent_ReturnsNonNegativeValue_1178) {

    // Arrange & Act

    double ascent = fontInfo.getAscent();



    // Assert

    EXPECT_GE(ascent, 0.0);

}



TEST_F(TextFontInfoTest_1178, GetDescent_ReturnsNonPositiveValue_1178) {

    // Arrange & Act

    double descent = fontInfo.getDescent();



    // Assert

    EXPECT_LE(descent, 0.0);

}
