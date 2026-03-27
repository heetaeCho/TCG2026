#include <gtest/gtest.h>

#include "GfxState.h"



class GfxTilingPatternTest : public ::testing::Test {

protected:

    std::array<double, 4> bbox = {0.0, 0.0, 100.0, 100.0};

    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    Object resDict;

    Object contentStream;



    std::unique_ptr<GfxTilingPattern> createGfxTilingPattern(int paintType, int tilingType) {

        return std::make_unique<GfxTilingPattern>(paintType, tilingType, bbox, 10.0, 10.0, &resDict, matrix, &contentStream, 1);

    }

};



TEST_F(GfxTilingPatternTest_492, GetPaintType_ReturnsCorrectValue_492) {

    auto pattern = createGfxTilingPattern(1, 1);

    EXPECT_EQ(pattern->getPaintType(), 1);

}



TEST_F(GfxTilingPatternTest_492, GetTilingType_ReturnsCorrectValue_492) {

    auto pattern = createGfxTilingPattern(1, 2);

    EXPECT_EQ(pattern->getTilingType(), 2);

}



TEST_F(GfxTilingPatternTest_492, GetBBox_ReturnsCorrectValues_492) {

    auto pattern = createGfxTilingPattern(1, 1);

    const auto& resultBbox = pattern->getBBox();

    EXPECT_EQ(resultBbox[0], 0.0);

    EXPECT_EQ(resultBbox[1], 0.0);

    EXPECT_EQ(resultBbox[2], 100.0);

    EXPECT_EQ(resultBbox[3], 100.0);

}



TEST_F(GfxTilingPatternTest_492, GetXStep_ReturnsCorrectValue_492) {

    auto pattern = createGfxTilingPattern(1, 1);

    EXPECT_DOUBLE_EQ(pattern->getXStep(), 10.0);

}



TEST_F(GfxTilingPatternTest_492, GetYStep_ReturnsCorrectValue_492) {

    auto pattern = createGfxTilingPattern(1, 1);

    EXPECT_DOUBLE_EQ(pattern->getYStep(), 10.0);

}



TEST_F(GfxTilingPatternTest_492, GetMatrix_ReturnsCorrectValues_492) {

    auto pattern = createGfxTilingPattern(1, 1);

    const auto& resultMatrix = pattern->getMatrix();

    EXPECT_DOUBLE_EQ(resultMatrix[0], 1.0);

    EXPECT_DOUBLE_EQ(resultMatrix[1], 0.0);

    EXPECT_DOUBLE_EQ(resultMatrix[2], 0.0);

    EXPECT_DOUBLE_EQ(resultMatrix[3], 1.0);

    EXPECT_DOUBLE_EQ(resultMatrix[4], 0.0);

    EXPECT_DOUBLE_EQ(resultMatrix[5], 0.0);

}



TEST_F(GfxTilingPatternTest_492, GetResDict_ReturnsValidObject_492) {

    auto pattern = createGfxTilingPattern(1, 1);

    EXPECT_NE(pattern->getResDict(), nullptr);

}



TEST_F(GfxTilingPatternTest_492, GetContentStream_ReturnsValidObject_492) {

    auto pattern = createGfxTilingPattern(1, 1);

    EXPECT_NE(pattern->getContentStream(), nullptr);

}
