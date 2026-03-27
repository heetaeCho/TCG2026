#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/processors/image_pair_inliers.h"

#include "glomap/scene/image.h"

#include "glomap/scene/image_pair.h"

#include "glomap/scene/camera.h"



namespace glomap {

    class ImagePairInliersTest : public ::testing::Test {

    protected:

        void SetUp() override {

            // Initialize test data

            image_id1 = 1;

            image_id2 = 2;



            cam2_from_cam1 = Rigid3d();

            cam2_from_cam1.translation << 0.5, 0.5, 0.5;

            cam2_from_cam1.rotation = Eigen::Matrix3d::Identity();



            image_pair = ImagePair(image_id1, image_id2, cam2_from_cam1);



            image1.image_id = image_id1;

            image1.camera_id = 1;

            image1.features_undist = {{0.1, 0.2}, {0.3, 0.4}};



            image2.image_id = image_id2;

            image2.camera_id = 2;

            image2.features_undist = {{-0.1, -0.2}, {-0.3, -0.4}};



            images = {{image_id1, image1}, {image_id2, image2}};



            camera1.Focal = []() { return 1.0; };

            camera2.Focal = []() { return 1.0; };



            cameras = {{camera1.camera_id, camera1}, {camera2.camera_id, camera2}};



            options.max_epipolar_error_E = 1.0;



            image_pair_inliers = std::make_unique<ImagePairInliers>(image_pair, images, options, &cameras);

        }



        int image_id1;

        int image_id2;

        Rigid3d cam2_from_cam1;

        ImagePair image_pair;

        Image image1;

        Image image2;

        Camera camera1;

        Camera camera2;

        std::unordered_map<image_t, Image> images;

        std::unordered_map<camera_t, Camera> cameras;

        InlierThresholdOptions options;

        std::unique_ptr<ImagePairInliers> image_pair_inliers;

    };



    TEST_F(ImagePairInliersTest_77, ScoreErrorEssential_NormalOperation_77) {

        image_pair.matches = Eigen::MatrixXi(2, 2);

        image_pair.matches << 0, 1,

                            1, 0;



        double score = image_pair_inliers->ScoreErrorEssential();

        EXPECT_GE(score, 0.0); // Score should be non-negative

    }



    TEST_F(ImagePairInliersTest_77, ScoreErrorEssential_NoMatches_77) {

        image_pair.matches = Eigen::MatrixXi(0, 2);



        double score = image_pair_inliers->ScoreErrorEssential();

        EXPECT_EQ(score, 0.0); // No matches should result in zero score

    }



    TEST_F(ImagePairInliersTest_77, ScoreErrorEssential_AllMatchesInliers_77) {

        image_pair.matches = Eigen::MatrixXi(2, 2);

        image_pair.matches << 0, 1,

                            1, 0;



        double score = image_pair_inliers->ScoreErrorEssential();

        EXPECT_EQ(image_pair.inliers.size(), 2); // All matches should be inliers

    }



    TEST_F(ImagePairInliersTest_77, ScoreErrorEssential_AllMatchesOutliers_77) {

        image1.features_undist = {{10.0, 10.0}, {20.0, 20.0}};

        image2.features_undist = {{-10.0, -10.0}, {-20.0, -20.0}};



        image_pair.matches = Eigen::MatrixXi(2, 2);

        image_pair.matches << 0, 1,

                            1, 0;



        double score = image_pair_inliers->ScoreErrorEssential();

        EXPECT_EQ(image_pair.inliers.size(), 0); // No matches should be inliers

    }



    TEST_F(ImagePairInliersTest_77, ScoreErrorEssential_BoundaryConditions_77) {

        image1.features_undist = {{0.5, 0.5}, {0.6, 0.6}};

        image2.features_undist = {{-0.5, -0.5}, {-0.6, -0.6}};



        image_pair.matches = Eigen::MatrixXi(2, 2);

        image_pair.matches << 0, 1,

                            1, 0;



        double score = image_pair_inliers->ScoreErrorEssential();

        EXPECT_EQ(score, 0.0); // Matches on boundary should be inliers

    }



    TEST_F(ImagePairInliersTest_77, ScoreErrorEssential_ExceptionalCases_77) {

        // No exceptional cases observable through the interface for this function.

    }

}
