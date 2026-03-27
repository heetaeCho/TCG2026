#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "colmap/image.h"

#include "glomap/scene/image.h"

#include "glomap/io/colmap_converter.cc"



using namespace glomap;

using namespace colmap;



class ColmapConverterTest_118 : public ::testing::Test {

protected:

    Image input_image;

    colmap::Image output_image_colmap;



    void SetUp() override {

        input_image = Image(42, 10, "test_image.png");

        input_image.camera_id = 5;

        input_image.frame_id = 3;

        input_image.features.push_back(Eigen::Vector2d(1.0, 2.0));

        input_image.features.push_back(Eigen::Vector2d(3.0, 4.0));

    }

};



TEST_F(ColmapConverterTest_118, ConvertGlomapToColmapImage_NormalOperation_118) {

    ConvertGlomapToColmapImage(input_image, output_image_colmap, true);

    

    EXPECT_EQ(output_image_colmap.ImageId(), input_image.image_id);

    EXPECT_EQ(output_image_colmap.CameraId(), input_image.camera_id);

    EXPECT_EQ(output_image_colmap.Name(), input_image.file_name);

    EXPECT_EQ(output_image_colmap.FrameId(), input_image.frame_id);

    EXPECT_EQ(output_image_colmap.Points2D().size(), 2);

}



TEST_F(ColmapConverterTest_118, ConvertGlomapToColmapImage_NoPoints_118) {

    ConvertGlomapToColmapImage(input_image, output_image_colmap, false);



    EXPECT_EQ(output_image_colmap.ImageId(), input_image.image_id);

    EXPECT_EQ(output_image_colmap.CameraId(), input_image.camera_id);

    EXPECT_EQ(output_image_colmap.Name(), input_image.file_name);

    EXPECT_EQ(output_image_colmap.FrameId(), input_image.frame_id);

    EXPECT_EQ(output_image_colmap.Points2D().size(), 0);

}



TEST_F(ColmapConverterTest_118, ConvertGlomapToColmapImage_EmptyFeatures_118) {

    input_image.features.clear();

    ConvertGlomapToColmapImage(input_image, output_image_colmap, true);



    EXPECT_EQ(output_image_colmap.ImageId(), input_image.image_id);

    EXPECT_EQ(output_image_colmap.CameraId(), input_image.camera_id);

    EXPECT_EQ(output_image_colmap.Name(), input_image.file_name);

    EXPECT_EQ(output_image_colmap.FrameId(), input_image.frame_id);

    EXPECT_EQ(output_image_colmap.Points2D().size(), 0);

}



TEST_F(ColmapConverterTest_118, ConvertGlomapToColmapImage_DefaultFrameId_118) {

    input_image.frame_id = -1;

    ConvertGlomapToColmapImage(input_image, output_image_colmap, true);



    EXPECT_EQ(output_image_colmap.ImageId(), input_image.image_id);

    EXPECT_EQ(output_image_colmap.CameraId(), input_image.camera_id);

    EXPECT_EQ(output_image_colmap.Name(), input_image.file_name);

    EXPECT_EQ(output_image_colmap.FrameId(), -1);

}



TEST_F(ColmapConverterTest_118, ConvertGlomapToColmapImage_EmptyFileName_118) {

    input_image = Image(42, 10, "");

    ConvertGlomapToColmapImage(input_image, output_image_colmap, true);



    EXPECT_EQ(output_image_colmap.ImageId(), input_image.image_id);

    EXPECT_EQ(output_image_colmap.CameraId(), input_image.camera_id);

    EXPECT_EQ(output_image_colmap.Name(), "");

    EXPECT_EQ(output_image_colmap.FrameId(), input_image.frame_id);

}
