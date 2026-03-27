#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"

#include <memory>



using namespace std;



class GfxTilingPatternTest : public ::testing::Test {

protected:

    const array<double, 4> bbox = {0.0, 1.0, 2.0, 3.0};

    const array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    Object resDict;

    Object contentStream;



    std::unique_ptr<GfxTilingPattern> pattern;



    void SetUp() override {

        pattern = GfxTilingPattern::parse(nullptr, 1);

    }

};



TEST_F(GfxTilingPatternTest_494, GetBBox_ReturnsCorrectValues_494) {

    EXPECT_EQ(pattern->getBBox(), bbox);

}



TEST_F(GfxTilingPatternTest_494, Parse_ReturnsNonNullPointer_494) {

    ASSERT_NE(pattern.get(), nullptr);

}



// Assuming the following methods are observable and should be tested

TEST_F(GfxTilingPatternTest_494, GetPaintType_ReturnsExpectedValue_494) {

    // Since we don't know the exact return value, we just check if it's accessible

    int paintType = pattern->getPaintType();

    EXPECT_TRUE(paintType == 1 || paintType == 2); // Common values for paint type in tiling patterns

}



TEST_F(GfxTilingPatternTest_494, GetTilingType_ReturnsExpectedValue_494) {

    int tilingType = pattern->getTilingType();

    EXPECT_TRUE(tilingType >= 1 && tilingType <= 3); // Common values for tiling type

}



TEST_F(GfxTilingPatternTest_494, GetXStep_ReturnsNonNegativeValue_494) {

    double xStep = pattern->getXStep();

    EXPECT_GE(xStep, 0.0);

}



TEST_F(GfxTilingPatternTest_494, GetYStep_ReturnsNonNegativeValue_494) {

    double yStep = pattern->getYStep();

    EXPECT_GE(yStep, 0.0);

}



TEST_F(GfxTilingPatternTest_494, GetResDict_ReturnsNonNullPointer_494) {

    Dict* dict = pattern->getResDict();

    ASSERT_NE(dict, nullptr);

}



TEST_F(GfxTilingPatternTest_494, GetMatrix_ReturnsCorrectValues_494) {

    EXPECT_EQ(pattern->getMatrix(), matrix);

}



TEST_F(GfxTilingPatternTest_494, GetContentStream_ReturnsNonNullPointer_494) {

    Object* stream = pattern->getContentStream();

    ASSERT_NE(stream, nullptr);

}
