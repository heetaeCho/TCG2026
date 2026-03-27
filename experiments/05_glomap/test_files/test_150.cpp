#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/glomap/glomap/processors/reconstruction_normalizer.cc"

#include "./TestProjects/glomap/glomap/scene/image.h"

#include "./TestProjects/glomap/glomap/scene/track.h"



namespace glomap {



using ::testing::ElementsAre;

using ::testing::Eq;



class ReconstructionNormalizerTest_150 : public ::testing::Test {

protected:

    std::unordered_map<rig_t, Rig> rigs_;

    std::unordered_map<camera_t, Camera> cameras_;

    std::unordered_map<frame_t, Frame> frames_;

    std::unordered_map<image_t, Image> images_;

    std::unordered_map<track_t, Track> tracks_;



    void AddImage(image_t img_id, camera_t cam_id, const Eigen::Vector3d& center) {

        images_[img_id] = Image(img_id, cam_id, "dummy_file");

        images_[img_id].frame_ptr = &frames_[0];

        frames_[0].SetPose(Rigid3d(center, Eigen::Quaterniond::Identity()));

    }

};



TEST_F(ReconstructionNormalizerTest_150, NormalizeReconstruction_NoImages_150) {

    colmap::Sim3d tform = NormalizeReconstruction(rigs_, cameras_, frames_, images_, tracks_, false, 1.0, 0.25, 0.75);

    EXPECT_EQ(tform.scale(), 1.0);

}



TEST_F(ReconstructionNormalizerTest_150, NormalizeReconstruction_SingleImage_150) {

    AddImage(1, 1, Eigen::Vector3d(1.0, 2.0, 3.0));

    colmap::Sim3d tform = NormalizeReconstruction(rigs_, cameras_, frames_, images_, tracks_, false, 1.0, 0.25, 0.75);

    EXPECT_EQ(tform.scale(), 1.0);

}



TEST_F(ReconstructionNormalizerTest_150, NormalizeReconstruction_MultipleImages_150) {

    AddImage(1, 1, Eigen::Vector3d(-1.0, -2.0, -3.0));

    AddImage(2, 1, Eigen::Vector3d(1.0, 2.0, 3.0));

    colmap::Sim3d tform = NormalizeReconstruction(rigs_, cameras_, frames_, images_, tracks_, false, 1.0, 0.25, 0.75);

    EXPECT_EQ(tform.scale(), 1.0);

}



TEST_F(ReconstructionNormalizerTest_150, NormalizeReconstruction_FixedScale_150) {

    AddImage(1, 1, Eigen::Vector3d(-1.0, -2.0, -3.0));

    AddImage(2, 1, Eigen::Vector3d(1.0, 2.0, 3.0));

    colmap::Sim3d tform = NormalizeReconstruction(rigs_, cameras_, frames_, images_, tracks_, true, 1.0, 0.25, 0.75);

    EXPECT_EQ(tform.scale(), 1.0);

}



TEST_F(ReconstructionNormalizerTest_150, NormalizeReconstruction_ZeroExtent_150) {

    AddImage(1, 1, Eigen::Vector3d(0.0, 0.0, 0.0));

    colmap::Sim3d tform = NormalizeReconstruction(rigs_, cameras_, frames_, images_, tracks_, false, 1.0, 0.25, 0.75);

    EXPECT_EQ(tform.scale(), 1.0);

}



TEST_F(ReconstructionNormalizerTest_150, NormalizeReconstruction_NonRegisteredImages_150) {

    images_[1] = Image(1, 1, "dummy_file");

    images_[1].frame_ptr = &frames_[0];

    frames_[0].SetPose(Rigid3d(Eigen::Vector3d(1.0, 2.0, 3.0), Eigen::Quaterniond::Identity()));

    colmap::Sim3d tform = NormalizeReconstruction(rigs_, cameras_, frames_, images_, tracks_, false, 1.0, 0.25, 0.75);

    EXPECT_EQ(tform.scale(), 1.0);

}



TEST_F(ReconstructionNormalizerTest_150, NormalizeReconstruction_TracksTransformation_150) {

    AddImage(1, 1, Eigen::Vector3d(-1.0, -2.0, -3.0));

    AddImage(2, 1, Eigen::Vector3d(1.0, 2.0, 3.0));

    tracks_[1] = Track();

    tracks_[1].xyz = Eigen::Vector3d(0.5, 1.0, 1.5);

    colmap::Sim3d tform = NormalizeReconstruction(rigs_, cameras_, frames_, images_, tracks_, false, 1.0, 0.25, 0.75);

    EXPECT_TRUE(tracks_[1].xyz.isApprox(Eigen::Vector3d(0.0, 0.0, 0.0)));

}



TEST_F(ReconstructionNormalizerTest_150, NormalizeReconstruction_PBoundaryConditions_150) {

    AddImage(1, 1, Eigen::Vector3d(-2.0, -4.0, -6.0));

    AddImage(2, 1, Eigen::Vector3d(0.0, 0.0, 0.0));

    AddImage(3, 1, Eigen::Vector3d(2.0, 4.0, 6.0));

    colmap::Sim3d tform = NormalizeReconstruction(rigs_, cameras_, frames_, images_, tracks_, false, 1.0, 0.0, 1.0);

    EXPECT_TRUE(tform.scale() > 0.0);

}



} // namespace glomap
