#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"



using namespace testing;



class GfxTilingPatternTest : public Test {

protected:

    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    std::array<double, 4> bbox = {0.0, 0.0, 1.0, 1.0};

    Object resDict;

    Object contentStream;

    std::unique_ptr<GfxTilingPattern> pattern;



    void SetUp() override {

        pattern = GfxTilingPattern::parse(nullptr, 42);

        if (!pattern) {

            pattern = std::make_unique<GfxTilingPattern>(1, 1, bbox, 0.5, 0.5, &resDict, matrix, &contentStream, 42);

        }

    }

};



TEST_F(GfxTilingPatternTest_498, GetMatrix_ReturnsCorrectValue_498) {

    EXPECT_EQ(pattern->getMatrix(), matrix);

}



TEST_F(GfxTilingPatternTest_498, GetPaintType_ReturnsDefaultValue_498) {

    EXPECT_EQ(pattern->getPaintType(), 1); // Assuming default paint type is 1 based on the constructor

}



TEST_F(GfxTilingPatternTest_498, GetTilingType_ReturnsDefaultValue_498) {

    EXPECT_EQ(pattern->getTilingType(), 1); // Assuming default tiling type is 1 based on the constructor

}



TEST_F(GfxTilingPatternTest_498, GetBBox_ReturnsCorrectValue_498) {

    EXPECT_EQ(pattern->getBBox(), bbox);

}



TEST_F(GfxTilingPatternTest_498, GetXStep_ReturnsDefaultValue_498) {

    EXPECT_DOUBLE_EQ(pattern->getXStep(), 0.5); // Assuming default xStep is 0.5 based on the constructor

}



TEST_F(GfxTilingPatternTest_498, GetYStep_ReturnsDefaultValue_498) {

    EXPECT_DOUBLE_EQ(pattern->getYStep(), 0.5); // Assuming default yStep is 0.5 based on the constructor

}



TEST_F(GfxTilingPatternTest_498, GetResDict_ReturnsNon-nullPointer_498) {

    EXPECT_NE(pattern->getResDict(), nullptr);

}



TEST_F(GfxTilingPatternTest_498, Copy_ReturnsNewInstanceWithSameMatrix_498) {

    auto copiedPattern = pattern->copy();

    GfxTilingPattern* tilingCopiedPattern = dynamic_cast<GfxTilingPattern*>(copiedPattern.get());

    ASSERT_NE(tilingCopiedPattern, nullptr);

    EXPECT_EQ(tilingCopiedPattern->getMatrix(), matrix);

}
