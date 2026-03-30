#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "reconstruction_normalizer.cc"



namespace glomap {



using ::testing::_;

using ::testing::Eq;



class ReconstructionNormalizerTest_80 : public ::testing::Test {

protected:

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<track_t, Track> tracks;



    colmap::Sim3d NormalizeReconstructionWrapper(bool fixed_scale, double extent, double p0, double p1) {

        return NormalizeReconstruction(rigs, cameras, frames, images, tracks, fixed_scale, extent, p0, p1);

    }

};



TEST_F(ReconstructionNormalizerTest_80, NoImagesProvided_ReturnsIdentityTransform_80) {

    colmap::Sim3d result = NormalizeReconstructionWrapper(false, 1.0, 0.05, 0.95);

    EXPECT_EQ(result.scale(), 1.0);

    EXPECT_TRUE(result.rotation().isApprox(Eigen::Quaterniond::Identity()));

    EXPECT_TRUE(result.translation().isZero());

}



TEST_F(ReconstructionNormalizerTest_80, SingleImageRegistered_ReturnsTransformCenteredOnImage_80) {

    Image image;

    image.SetRegistered(true);

    image.SetCenter(Eigen::Vector3d(1.0, 2.0, 3.0));

    images[0] = image;



    colmap::Sim3d result = NormalizeReconstructionWrapper(false, 1.0, 0.05, 0.95);

    EXPECT_EQ(result.scale(), 1.0);

    EXPECT_TRUE(result.rotation().isApprox(Eigen::Quaterniond::Identity()));

    EXPECT_TRUE(result.translation().isApprox(-Eigen::Vector3d(1.0, 2.0, 3.0)));

}



TEST_F(ReconstructionNormalizerTest_80, MultipleImagesRegistered_ReturnsTransformCenteredOnMedian_80) {

    Image image1, image2;

    image1.SetRegistered(true);

    image1.SetCenter(Eigen::Vector3d(1.0, 2.0, 3.0));

    images[0] = image1;



    image2.SetRegistered(true);

    image2.SetCenter(Eigen::Vector3d(4.0, 5.0, 6.0));

    images[1] = image2;



    colmap::Sim3d result = NormalizeReconstructionWrapper(false, 1.0, 0.5, 0.5);

    EXPECT_EQ(result.scale(), 1.0);

    EXPECT_TRUE(result.rotation().isApprox(Eigen::Quaterniond::Identity()));

    EXPECT_TRUE(result.translation().isApprox(-Eigen::Vector3d(2.5, 3.5, 4.5)));

}



TEST_F(ReconstructionNormalizerTest_80, FixedScale_ReturnsTransformWithoutScaling_80) {

    Image image;

    image.SetRegistered(true);

    image.SetCenter(Eigen::Vector3d(1.0, 2.0, 3.0));

    images[0] = image;



    colmap::Sim3d result = NormalizeReconstructionWrapper(true, 1.0, 0.05, 0.95);

    EXPECT_EQ(result.scale(), 1.0);

}



TEST_F(ReconstructionNormalizerTest_80, NonRegisteredImagesIgnored_ReturnsCorrectTransform_80) {

    Image image1, image2;

    image1.SetRegistered(true);

    image1.SetCenter(Eigen::Vector3d(1.0, 2.0, 3.0));

    images[0] = image1;



    image2.SetRegistered(false);

    image2.SetCenter(Eigen::Vector3d(4.0, 5.0, 6.0));

    images[1] = image2;



    colmap::Sim3d result = NormalizeReconstructionWrapper(false, 1.0, 0.05, 0.95);

    EXPECT_EQ(result.scale(), 1.0);

    EXPECT_TRUE(result.rotation().isApprox(Eigen::Quaterniond::Identity()));

    EXPECT_TRUE(result.translation().isApprox(-Eigen::Vector3d(1.0, 2.0, 3.0)));

}



TEST_F(ReconstructionNormalizerTest_80, SmallExtent_ReturnsLargeScaleTransform_80) {

    Image image;

    image.SetRegistered(true);

    image.SetCenter(Eigen::Vector3d(1.0, 2.0, 3.0));

    images[0] = image;



    colmap::Sim3d result = NormalizeReconstructionWrapper(false, 0.1, 0.05, 0.95);

    EXPECT_GT(result.scale(), 1.0);

}



TEST_F(ReconstructionNormalizerTest_80, LargeExtent_ReturnsSmallScaleTransform_80) {

    Image image;

    image.SetRegistered(true);

    image.SetCenter(Eigen::Vector3d(1.0, 2.0, 3.0));

    images[0] = image;



    colmap::Sim3d result = NormalizeReconstructionWrapper(false, 1000.0, 0.05, 0.95);

    EXPECT_LT(result.scale(), 1.0);

}



TEST_F(ReconstructionNormalizerTest_80, ExtentZero_ReturnsIdentityTransform_80) {

    Image image;

    image.SetRegistered(true);

    image.SetCenter(Eigen::Vector3d(1.0, 2.0, 3.0));

    images[0] = image;



    colmap::Sim3d result = NormalizeReconstructionWrapper(false, 0.0, 0.05, 0.95);

    EXPECT_EQ(result.scale(), 1.0);

}



TEST_F(ReconstructionNormalizerTest_80, ExtentNegative_ReturnsIdentityTransform_80) {

    Image image;

    image.SetRegistered(true);

    image.SetCenter(Eigen::Vector3d(1.0, 2.0, 3.0));

    images[0] = image;



    colmap::Sim3d result = NormalizeReconstructionWrapper(false, -1.0, 0.05, 0.95);

    EXPECT_EQ(result.scale(), 1.0);

}



TEST_F(ReconstructionNormalizerTest_80, P0P1OutsideRange_ReturnsTransformUsingClippedValues_80) {

    Image image;

    image.SetRegistered(true);

    image.SetCenter(Eigen::Vector3d(1.0, 2.0, 3.0));

    images[0] = image;



    colmap::Sim3d result = NormalizeReconstructionWrapper(false, 1.0, -0.5, 1.5);

    EXPECT_EQ(result.scale(), 1.0);

    EXPECT_TRUE(result.rotation().isApprox(Eigen::Quaterniond::Identity()));

    EXPECT_TRUE(result.translation().isApprox(-Eigen::Vector3d(1.0, 2.0, 3.0)));

}



TEST_F(ReconstructionNormalizerTest_80, P0P1Equal_ReturnsTransformUsingSinglePoint_80) {

    Image image;

    image.SetRegistered(true);

    image.SetCenter(Eigen::Vector3d(1.0, 2.0, 3.0));

    images[0] = image;



    colmap::Sim3d result = NormalizeReconstructionWrapper(false, 1.0, 0.5, 0.5);

    EXPECT_EQ(result.scale(), 1.0);

    EXPECT_TRUE(result.rotation().isApprox(Eigen::Quaterniond::Identity()));

    EXPECT_TRUE(result.translation().isApprox(-Eigen::Vector3d(1.0, 2.0, 3.0)));

}



TEST_F(ReconstructionNormalizerTest_80, FramesTransformedAccordingly_80) {

    Image image;

    image.SetRegistered(true);

    image.SetCenter(Eigen::Vector3d(1.0, 2.0, 3.0));

    images[0] = image;



    Frame frame;

    Rigid3d pose(Eigen::Quaterniond::Identity(), Eigen::Vector3d(4.0, 5.0, 6.0));

    frame.SetPose(pose);

    frames[0] = frame;



    colmap::Sim3d result = NormalizeReconstructionWrapper(false, 1.0, 0.05, 0.95);

    EXPECT_TRUE(frames[0].RigFromWorld().translation().isApprox(Eigen::Vector3d(3.0, 3.0, 3.0)));

}



TEST_F(ReconstructionNormalizerTest_80, RigsTransformedAccordingly_80) {

    Image image;

    image.SetRegistered(true);

    image.SetCenter(Eigen::Vector3d(1.0, 2.0, 3.0));

    images[0] = image;



    Rig rig;

    Rigid3d sensor_from_rig(Eigen::Quaterniond::Identity(), Eigen::Vector3d(0.5, 0.5, 0.5));

    rig.SetSensorFromRig(sensor_id_t(0), sensor_from_rig);

    rigs[0] = rig;



    colmap::Sim3d result = NormalizeReconstructionWrapper(false, 1.0, 0.05, 0.95);

    EXPECT_TRUE(rigs[0].NonRefSensors().at(sensor_id_t(0)).value().translation().isApprox(Eigen::Vector3d(-0.5, -0.5, -0.5)));

}



TEST_F(ReconstructionNormalizerTest_80, TracksTransformedAccordingly_80) {

    Image image;

    image.SetRegistered(true);

    image.SetCenter(Eigen::Vector3d(1.0, 2.0, 3.0));

    images[0] = image;



    Track track;

    track.xyz = Eigen::Vector3d(4.0, 5.0, 6.0);

    tracks[0] = track;



    colmap::Sim3d result = NormalizeReconstructionWrapper(false, 1.0, 0.05, 0.95);

    EXPECT_TRUE(tracks[0].xyz.isApprox(Eigen::Vector3d(2.0, 2.0, 2.0)));

}



} // namespace glomap
