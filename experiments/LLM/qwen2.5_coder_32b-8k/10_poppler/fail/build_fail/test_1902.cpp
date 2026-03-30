#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GlobalParams.cc"

#include "FoFiIdentifier.h"



using ::testing::Return;



class SupportedFontForEmbeddingTest : public ::testing::Test {

protected:

    SupportedFontForEmbeddingTest() = default;

};



TEST_F(SupportedFontForEmbeddingTest, ReturnsFalseForUnsupportedFileExtension_1902) {

    Unicode uChar = 65; // 'A'

    EXPECT_FALSE(supportedFontForEmbedding(uChar, "font.pfa", 0));

}



TEST_F(SupportedFontForEmbeddingTest, ReturnsFalseForInvalidFoFiType_1902) {

    Unicode uChar = 65; // 'A'

    EXPECT_CALL(*mockFoFiIdentifier(), identifyFile("font.ttf")).WillOnce(Return(fofiIdUnknown));



    EXPECT_FALSE(supportedFontForEmbedding(uChar, "font.ttf", 0));

}



TEST_F(SupportedFontForEmbeddingTest, ReturnsFalseWhenLoadFails_1902) {

    Unicode uChar = 65; // 'A'

    EXPECT_CALL(*mockFoFiIdentifier(), identifyFile("font.ttf")).WillOnce(Return(fofiIdTrueType));



    EXPECT_FALSE(supportedFontForEmbedding(uChar, "font.ttf", 0));

}



TEST_F(SupportedFontForEmbeddingTest, ReturnsFalseWhenNoCmapFound_1902) {

    Unicode uChar = 65; // 'A'

    EXPECT_CALL(*mockFoFiIdentifier(), identifyFile("font.ttf")).WillOnce(Return(fofiIdTrueType));



    const std::unique_ptr<FoFiTrueType> mockFFT(new FoFiTrueType());

    EXPECT_CALL(*mockFFT, findCmap(0, 3)).WillOnce(Return(-1));

    EXPECT_CALL(*mockFFT, findCmap(3, 1)).WillOnce(Return(-1));



    EXPECT_FALSE(supportedFontForEmbedding(uChar, "font.ttf", 0));

}



TEST_F(SupportedFontForEmbeddingTest, ReturnsTrueWhenGlyphFound_1902) {

    Unicode uChar = 65; // 'A'

    EXPECT_CALL(*mockFoFiIdentifier(), identifyFile("font.ttf")).WillOnce(Return(fofiIdTrueType));



    const std::unique_ptr<FoFiTrueType> mockFFT(new FoFiTrueType());

    EXPECT_CALL(*mockFFT, findCmap(0, 3)).WillOnce(Return(1));

    EXPECT_CALL(*mockFFT, mapCodeToGID(1, uChar)).WillOnce(Return(1));



    EXPECT_TRUE(supportedFontForEmbedding(uChar, "font.ttf", 0));

}



TEST_F(SupportedFontForEmbeddingTest, ReturnsFalseWhenGlyphNotFound_1902) {

    Unicode uChar = 65; // 'A'

    EXPECT_CALL(*mockFoFiIdentifier(), identifyFile("font.ttf")).WillOnce(Return(fofiIdTrueType));



    const std::unique_ptr<FoFiTrueType> mockFFT(new FoFiTrueType());

    EXPECT_CALL(*mockFFT, findCmap(0, 3)).WillOnce(Return(1));

    EXPECT_CALL(*mockFFT, mapCodeToGID(1, uChar)).WillOnce(Return(0));



    EXPECT_FALSE(supportedFontForEmbedding(uChar, "font.ttf", 0));

}
