#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/processors/image_undistorter.h"

#include "glomap/scene/image.h"

#include <unordered_map>



using namespace glomap;

using testing::_;

using testing::Return;



class ImageUndistorterTest : public ::testing::Test {

protected:

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<image_t, Image> images;

};



TEST_F(ImageUndistorterTest_151, NoImages_151) {

    UndistortImages(cameras, images, false);

    EXPECT_TRUE(images.empty());

}



TEST_F(ImageUndistorterTest_151, SingleImageNoPoints_151) {

    Camera camera;

    Image image(0, 0, "image.jpg");

    cameras[0] = camera;

    images[0] = image;



    UndistortImages(cameras, images, false);

    EXPECT_TRUE(images[0].features_undist.empty());

}



TEST_F(ImageUndistorterTest_151, SingleImageAlreadyUndistorted_151) {

    Camera camera;

    Image image(0, 0, "image.jpg");

    image.features.emplace_back(Eigen::Vector2d(1.0, 2.0));

    image.features_undist.emplace_back(Eigen::Vector3d(1.0, 2.0, 1.0));

    cameras[0] = camera;

    images[0] = image;



    UndistortImages(cameras, images, false);

    EXPECT_EQ(images[0].features_undist.size(), 1);

}



TEST_F(ImageUndistorterTest_151, SingleImageWithPointsToUndistort_151) {

    Camera camera;

    Image image(0, 0, "image.jpg");

    image.features.emplace_back(Eigen::Vector2d(1.0, 2.0));

    cameras[0] = camera;

    images[0] = image;



    UndistortImages(cameras, images, false);

    EXPECT_EQ(images[0].features_undist.size(), 1);

}



TEST_F(ImageUndistorterTest_151, MultipleImagesAlreadyUndistorted_151) {

    Camera camera;

    Image image1(0, 0, "image1.jpg");

    Image image2(1, 0, "image2.jpg");

    image1.features.emplace_back(Eigen::Vector2d(1.0, 2.0));

    image1.features_undist.emplace_back(Eigen::Vector3d(1.0, 2.0, 1.0));

    image2.features.emplace_back(Eigen::Vector2d(3.0, 4.0));

    image2.features_undist.emplace_back(Eigen::Vector3d(3.0, 4.0, 1.0));

    cameras[0] = camera;

    images[0] = image1;

    images[1] = image2;



    UndistortImages(cameras, images, false);

    EXPECT_EQ(images[0].features_undist.size(), 1);

    EXPECT_EQ(images[1].features_undist.size(), 1);

}



TEST_F(ImageUndistorterTest_151, MultipleImagesWithPointsToUndistort_151) {

    Camera camera;

    Image image1(0, 0, "image1.jpg");

    Image image2(1, 0, "image2.jpg");

    image1.features.emplace_back(Eigen::Vector2d(1.0, 2.0));

    image2.features.emplace_back(Eigen::Vector2d(3.0, 4.0));

    cameras[0] = camera;

    images[0] = image1;

    images[1] = image2;



    UndistortImages(cameras, images, false);

    EXPECT_EQ(images[0].features_undist.size(), 1);

    EXPECT_EQ(images[1].features_undist.size(), 1);

}



TEST_F(ImageUndistorterTest_151, CleanPointsFlagSet_151) {

    Camera camera;

    Image image(0, 0, "image.jpg");

    image.features.emplace_back(Eigen::Vector2d(1.0, 2.0));

    cameras[0] = camera;

    images[0] = image;



    UndistortImages(cameras, images, true);

    EXPECT_EQ(images[0].features_undist.size(), 1);

}
