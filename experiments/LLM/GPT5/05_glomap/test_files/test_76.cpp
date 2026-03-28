#include "glomap/processors/image_pair_inliers.h"
#include "glomap/scene/image_pair.h"

#include <gtest/gtest.h>
#include <unordered_map>

namespace glomap {

// Small helper subclass to expose the protected scoring methods for comparison.
class TestableImagePairInliers_76 : public ImagePairInliers {
 public:
  using ImagePairInliers::ImagePairInliers;

  double CallScoreErrorEssential() { return ScoreErrorEssential(); }
  double CallScoreErrorFundamental() { return ScoreErrorFundamental(); }
  double CallScoreErrorHomography() { return ScoreErrorHomography(); }
};

class ImagePairInliersTest_76 : public ::testing::Test {
 protected:
  ImagePairInliersTest_76()
      : image_pair_(1, 2),  // IDs are arbitrary but must be valid
        images_(),
        options_(),
        cameras_() {
    // Provide dummy images for the two image IDs referenced by image_pair_.
    images_.emplace(image_pair_.image_id1, Image());
    images_.emplace(image_pair_.image_id2, Image());
  }

  ImagePair image_pair_;
  std::unordered_map<image_t, Image> images_;
  InlierThresholdOptions options_;
  std::unordered_map<camera_t, Camera> cameras_;
};

// PLANAR config should route to ScoreErrorHomography.
TEST_F(ImagePairInliersTest_76, PlanarConfigUsesHomographyScore_76) {
  image_pair_.config = colmap::TwoViewGeometry::PLANAR;

  TestableImagePairInliers_76 inliers(image_pair_, images_, options_, &cameras_);

  const double expected = inliers.CallScoreErrorHomography();
  const double actual = inliers.ScoreError();

  EXPECT_DOUBLE_EQ(expected, actual);
}

// PANORAMIC config should route to ScoreErrorHomography.
TEST_F(ImagePairInliersTest_76, PanoramicConfigUsesHomographyScore_76) {
  image_pair_.config = colmap::TwoViewGeometry::PANORAMIC;

  TestableImagePairInliers_76 inliers(image_pair_, images_, options_, &cameras_);

  const double expected = inliers.CallScoreErrorHomography();
  const double actual = inliers.ScoreError();

  EXPECT_DOUBLE_EQ(expected, actual);
}

// PLANAR_OR_PANORAMIC config should route to ScoreErrorHomography.
TEST_F(ImagePairInliersTest_76, PlanarOrPanoramicConfigUsesHomographyScore_76) {
  image_pair_.config = colmap::TwoViewGeometry::PLANAR_OR_PANORAMIC;

  TestableImagePairInliers_76 inliers(image_pair_, images_, options_, &cameras_);

  const double expected = inliers.CallScoreErrorHomography();
  const double actual = inliers.ScoreError();

  EXPECT_DOUBLE_EQ(expected, actual);
}

// UNCALIBRATED config should route to ScoreErrorFundamental.
TEST_F(ImagePairInliersTest_76, UncalibratedConfigUsesFundamentalScore_76) {
  image_pair_.config = colmap::TwoViewGeometry::UNCALIBRATED;

  TestableImagePairInliers_76 inliers(image_pair_, images_, options_, &cameras_);

  const double expected = inliers.CallScoreErrorFundamental();
  const double actual = inliers.ScoreError();

  EXPECT_DOUBLE_EQ(expected, actual);
}

// CALIBRATED config should route to ScoreErrorEssential.
TEST_F(ImagePairInliersTest_76, CalibratedConfigUsesEssentialScore_76) {
  image_pair_.config = colmap::TwoViewGeometry::CALIBRATED;

  TestableImagePairInliers_76 inliers(image_pair_, images_, options_, &cameras_);

  const double expected = inliers.CallScoreErrorEssential();
  const double actual = inliers.ScoreError();

  EXPECT_DOUBLE_EQ(expected, actual);
}

// UNDEFINED (or any unsupported) config should return 0.
TEST_F(ImagePairInliersTest_76, UndefinedConfigReturnsZero_76) {
  image_pair_.config = colmap::TwoViewGeometry::UNDEFINED;

  TestableImagePairInliers_76 inliers(image_pair_, images_, options_, &cameras_);

  const double score = inliers.ScoreError();

  EXPECT_DOUBLE_EQ(0.0, score);
}

// Explicitly test an out-of-range / unknown config as a boundary case.
TEST_F(ImagePairInliersTest_76, UnknownConfigReturnsZero_76) {
  image_pair_.config = 9999;  // Value outside the known TwoViewGeometry enum range

  TestableImagePairInliers_76 inliers(image_pair_, images_, options_, &cameras_);

  const double score = inliers.ScoreError();

  EXPECT_DOUBLE_EQ(0.0, score);
}

}  // namespace glomap
