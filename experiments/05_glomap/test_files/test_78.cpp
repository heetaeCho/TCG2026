#include <gtest/gtest.h>

#include "image_pair_inliers.h"

#include "types.h"

#include "scene/image.h"

#include "scene/image_pair.h"



using namespace glomap;



class ImagePairInliersTest : public ::testing::Test {

protected:

    InlierThresholdOptions options;

    std::unordered_map<image_t, Image> images;

    Image image1;

    Image image2;

    ImagePair image_pair;

    ImagePairInliers inliers_processor;



    void SetUp() override {

        // Initialize image pair and related objects

        image1 = Image(1, 1, "image1.jpg");

        image2 = Image(2, 2, "image2.jpg");



        images[1] = image1;

        images[2] = image2;



        Eigen::Matrix3d F;

        F << 0.0845, -0.1690,  0.0845,

            -0.1690,  0.3381, -0.1690,

             0.0845, -0.1690,  0.0845;



        image_pair = ImagePair(1, 2);

        image_pair.F = F;



        options.max_epipolar_error_F = 4.0;



        inliers_processor = ImagePairInliers(image_pair, images, options);

    }

};



TEST_F(ImagePairInliersTest_78, ScoreErrorFundamental_NoMatches_78) {

    image_pair.matches.resize(0);

    EXPECT_DOUBLE_EQ(inliers_processor.ScoreErrorFundamental(), 16.0); // 4^2 * number of matches (0 in this case)

}



TEST_F(ImagePairInliersTest_78, ScoreErrorFundamental_AllMatchesInlier_78) {

    image_pair.matches.resize(5);

    for (int i = 0; i < 5; ++i) {

        image1.features.push_back(Eigen::Vector2d(i, i));

        image2.features.push_back(Eigen::Vector2d(i * 0.99, i * 0.99)); // close enough to be inliers

    }



    EXPECT_DOUBLE_EQ(inliers_processor.ScoreErrorFundamental(), 0.0);

}



TEST_F(ImagePairInliersTest_78, ScoreErrorFundamental_AllMatchesOutlier_78) {

    image_pair.matches.resize(5);

    for (int i = 0; i < 5; ++i) {

        image1.features.push_back(Eigen::Vector2d(i, i));

        image2.features.push_back(Eigen::Vector2d(i + 5, i + 5)); // far enough to be outliers

    }



    EXPECT_DOUBLE_EQ(inliers_processor.ScoreErrorFundamental(), 80.0); // 4^2 * number of matches (5 in this case)

}



TEST_F(ImagePairInliersTest_78, ScoreErrorFundamental_MixedMatches_78) {

    image_pair.matches.resize(10);

    for (int i = 0; i < 5; ++i) {

        image1.features.push_back(Eigen::Vector2d(i, i));

        image2.features.push_back(Eigen::Vector2d(i * 0.99, i * 0.99)); // close enough to be inliers

    }

    for (int i = 5; i < 10; ++i) {

        image1.features.push_back(Eigen::Vector2d(i, i));

        image2.features.push_back(Eigen::Vector2d(i + 5, i + 5)); // far enough to be outliers

    }



    EXPECT_DOUBLE_EQ(inliers_processor.ScoreErrorFundamental(), 40.0); // 4^2 * number of outliers (5 in this case)

}



TEST_F(ImagePairInliersTest_78, ScoreErrorFundamental_EpipoleOnLine_78) {

    image_pair.F << 0, -1, 0,

                    1,  0, 0,

                    0,  0, 0; // Epipole is on the line x=0



    image_pair.matches.resize(5);

    for (int i = 0; i < 5; ++i) {

        image1.features.push_back(Eigen::Vector2d(i, 0)); // Points on epipolar line

        image2.features.push_back(Eigen::Vector2d(-i, 0));

    }



    EXPECT_DOUBLE_EQ(inliers_processor.ScoreErrorFundamental(), 80.0); // All points are outliers

}



TEST_F(ImagePairInliersTest_78, ScoreErrorFundamental_ZeroThreshold_78) {

    options.max_epipolar_error_F = 0.0;

    inliers_processor = ImagePairInliers(image_pair, images, options);



    image_pair.matches.resize(5);

    for (int i = 0; i < 5; ++i) {

        image1.features.push_back(Eigen::Vector2d(i, i));

        image2.features.push_back(Eigen::Vector2d(i * 0.99, i * 0.99)); // close enough to be inliers

    }



    EXPECT_DOUBLE_EQ(inliers_processor.ScoreErrorFundamental(), 80.0); // All points are outliers due to zero threshold

}
