#include <gtest/gtest.h>

#include "GfxState.h"



class GfxTilingPatternTest_495 : public ::testing::Test {

protected:

    std::unique_ptr<GfxTilingPattern> pattern;



    void SetUp() override {

        // Since we cannot re-implement or infer the internal logic,

        // we assume a valid instance is created for testing purposes.

        // This setup is a placeholder and should be replaced with actual

        // object creation if possible, e.g., using factory methods.

        std::array<double, 4> bbox = {0.0, 0.0, 10.0, 10.0};

        std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

        Object resDict;

        Object contentStream;



        pattern = std::make_unique<GfxTilingPattern>(

            1, // paintTypeA

            2, // tilingTypeA

            bbox,

            5.0, // xStepA

            5.0, // yStepA

            &resDict,

            matrix,

            &contentStream,

            495  // patternRefNumA

        );

    }

};



TEST_F(GfxTilingPatternTest_495, GetXStep_ReturnsCorrectValue_495) {

    EXPECT_DOUBLE_EQ(pattern->getXStep(), 5.0);

}



TEST_F(GfxTilingPatternTest_495, GetYStep_ReturnsCorrectValue_495) {

    EXPECT_DOUBLE_EQ(pattern->getYStep(), 5.0);

}



TEST_F(GfxTilingPatternTest_495, GetBBox_ReturnsCorrectValues_495) {

    const auto& bbox = pattern->getBBox();

    EXPECT_DOUBLE_EQ(bbox[0], 0.0);

    EXPECT_DOUBLE_EQ(bbox[1], 0.0);

    EXPECT_DOUBLE_EQ(bbox[2], 10.0);

    EXPECT_DOUBLE_EQ(bbox[3], 10.0);

}



TEST_F(GfxTilingPatternTest_495, GetMatrix_ReturnsCorrectValues_495) {

    const auto& matrix = pattern->getMatrix();

    EXPECT_DOUBLE_EQ(matrix[0], 1.0);

    EXPECT_DOUBLE_EQ(matrix[1], 0.0);

    EXPECT_DOUBLE_EQ(matrix[2], 0.0);

    EXPECT_DOUBLE_EQ(matrix[3], 1.0);

    EXPECT_DOUBLE_EQ(matrix[4], 0.0);

    EXPECT_DOUBLE_EQ(matrix[5], 0.0);

}



TEST_F(GfxTilingPatternTest_495, GetPaintType_ReturnsCorrectValue_495) {

    EXPECT_EQ(pattern->getPaintType(), 1);

}



TEST_F(GfxTilingPatternTest_495, GetTilingType_ReturnsCorrectValue_495) {

    EXPECT_EQ(pattern->getTilingType(), 2);

}
