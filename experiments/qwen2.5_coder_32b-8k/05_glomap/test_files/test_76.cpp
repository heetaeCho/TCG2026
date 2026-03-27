#include <gtest/gtest.h>

#include "glomap/processors/image_pair_inliers.h"

#include "glomap/scene/image_pair.h"



namespace glomap {

namespace {



class ImagePairInliersTest : public ::testing::Test {

protected:

    std::unordered_map<image_t, Image> images;

    InlierThresholdOptions options;

    const std::unordered_map<camera_t, Camera>* cameras = nullptr;

    ImagePair image_pair;



    void SetUp() override {

        // Initialize necessary data for tests

        image_pair.config = colmap::TwoViewGeometry::UNDEFINED;  // Default configuration

    }

};



TEST_F(ImagePairInliersTest_76, ScoreErrorPlanarConfig_76) {

    image_pair.config = colmap::TwoViewGeometry::PLANAR;

    ImagePairInliers inliers(image_pair, images, options, cameras);

    EXPECT_DOUBLE_EQ(inliers.ScoreError(), inliers.ScoreErrorHomography());

}



TEST_F(ImagePairInliersTest_76, ScoreErrorPanoramicConfig_76) {

    image_pair.config = colmap::TwoViewGeometry::PANORAMIC;

    ImagePairInliers inliers(image_pair, images, options, cameras);

    EXPECT_DOUBLE_EQ(inliers.ScoreError(), inliers.ScoreErrorHomography());

}



TEST_F(ImagePairInliersTest_76, ScoreErrorPlanarOrPanoramicConfig_76) {

    image_pair.config = colmap::TwoViewGeometry::PLANAR_OR_PANORAMIC;

    ImagePairInliers inliers(image_pair, images, options, cameras);

    EXPECT_DOUBLE_EQ(inliers.ScoreError(), inliers.ScoreErrorHomography());

}



TEST_F(ImagePairInliersTest_76, ScoreErrorUncalibratedConfig_76) {

    image_pair.config = colmap::TwoViewGeometry::UNCALIBRATED;

    ImagePairInliers inliers(image_pair, images, options, cameras);

    EXPECT_DOUBLE_EQ(inliers.ScoreError(), inliers.ScoreErrorFundamental());

}



TEST_F(ImagePairInliersTest_76, ScoreErrorCalibratedConfig_76) {

    image_pair.config = colmap::TwoViewGeometry::CALIBRATED;

    ImagePairInliers inliers(image_pair, images, options, cameras);

    EXPECT_DOUBLE_EQ(inliers.ScoreError(), inliers.ScoreErrorEssential());

}



TEST_F(ImagePairInliersTest_76, ScoreErrorUndefinedConfig_76) {

    image_pair.config = colmap::TwoViewGeometry::UNDEFINED;

    ImagePairInliers inliers(image_pair, images, options, cameras);

    EXPECT_DOUBLE_EQ(inliers.ScoreError(), 0.0);

}



}  // namespace

}  // namespace glomap
