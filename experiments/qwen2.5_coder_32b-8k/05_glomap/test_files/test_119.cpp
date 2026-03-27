#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/glomap/glomap/io/colmap_converter.cc"

#include "./TestProjects/glomap/glomap/scene/frame.h"

#include "./TestProjects/glomap/glomap/scene/image.h"

#include "./TestProjects/glomap/glomap/scene/track.h"



using namespace glomap;

using namespace colmap;



class ConvertGlomapToColmapTest_119 : public ::testing::Test {

protected:

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<track_t, Track> tracks;

    colmap::Reconstruction reconstruction;



    void SetUp() override {

        // Setup some basic data for testing

        Camera camera1;

        cameras[1] = camera1;



        Rig rig1;

        rigs[1] = rig1;



        Frame frame1;

        frames[1] = frame1;



        Image image1(1, 1, "image1.jpg");

        images[1] = image1;



        Track track1;

        Observation obs1(1, 0);

        track1.observations.push_back(obs1);

        tracks[1] = track1;

    }

};



TEST_F(ConvertGlomapToColmapTest_119, NormalOperation_119) {

    ConvertGlomapToColmap(rigs, cameras, frames, images, tracks, reconstruction, -1, true);

    EXPECT_EQ(reconstruction.NumCameras(), 1);

    EXPECT_EQ(reconstruction.NumRigs(), 1);

    EXPECT_EQ(reconstruction.NumFrames(), 1);

    EXPECT_EQ(reconstruction.NumImages(), 1);

    EXPECT_EQ(reconstruction.NumPoints3D(), 1);

}



TEST_F(ConvertGlomapToColmapTest_119, BoundaryConditions_EmptyInputs_119) {

    std::unordered_map<rig_t, Rig> empty_rigs;

    std::unordered_map<camera_t, Camera> empty_cameras;

    std::unordered_map<frame_t, Frame> empty_frames;

    std::unordered_map<image_t, Image> empty_images;

    std::unordered_map<track_t, Track> empty_tracks;



    ConvertGlomapToColmap(empty_rigs, empty_cameras, empty_frames, empty_images, empty_tracks, reconstruction, -1, true);

    EXPECT_EQ(reconstruction.NumCameras(), 0);

    EXPECT_EQ(reconstruction.NumRigs(), 0);

    EXPECT_EQ(reconstruction.NumFrames(), 0);

    EXPECT_EQ(reconstruction.NumImages(), 0);

    EXPECT_EQ(reconstruction.NumPoints3D(), 0);

}



TEST_F(ConvertGlomapToColmapTest_119, BoundaryConditions_NoTracks_119) {

    std::unordered_map<track_t, Track> empty_tracks;



    ConvertGlomapToColmap(rigs, cameras, frames, images, empty_tracks, reconstruction, -1, true);

    EXPECT_EQ(reconstruction.NumPoints3D(), 0);

}



TEST_F(ConvertGlomapToColmapTest_119, BoundaryConditions_NoImages_119) {

    std::unordered_map<image_t, Image> empty_images;



    ConvertGlomapToColmap(rigs, cameras, frames, empty_images, tracks, reconstruction, -1, true);

    EXPECT_EQ(reconstruction.NumPoints3D(), 0);

}



TEST_F(ConvertGlomapToColmapTest_119, ExceptionalCases_UnregisteredImages_119) {

    images[1].camera_id = -1; // Make image unregistered

    ConvertGlomapToColmap(rigs, cameras, frames, images, tracks, reconstruction, -1, true);

    EXPECT_EQ(reconstruction.NumPoints3D(), 0);

}



TEST_F(ConvertGlomapToColmapTest_119, ExceptionalCases_ClusterIdMismatch_119) {

    frames[1].cluster_id = 1;

    ConvertGlomapToColmap(rigs, cameras, frames, images, tracks, reconstruction, 2, true);

    EXPECT_EQ(reconstruction.NumFrames(), 0); // Frame should be deregistered

}



TEST_F(ConvertGlomapToColmapTest_119, VerificationOfExternalInteractions_119) {

    ConvertGlomapToColmap(rigs, cameras, frames, images, tracks, reconstruction, -1, true);

    EXPECT_EQ(reconstruction.NumCameras(), 1);

    EXPECT_EQ(reconstruction.NumRigs(), 1);

    EXPECT_EQ(reconstruction.NumFrames(), 1);

    EXPECT_EQ(reconstruction.NumImages(), 1);

    EXPECT_EQ(reconstruction.NumPoints3D(), 1);



    const colmap::Camera& added_camera = reconstruction.Camera(1);

    EXPECT_EQ(added_camera, cameras[1]);



    const colmap::Rig& added_rig = reconstruction.Rig(1);

    EXPECT_EQ(added_rig, rigs[1]);



    const colmap::Frame& added_frame = reconstruction.Frame(1);

    EXPECT_EQ(added_frame, frames[1]);



    const colmap::Image& added_image = reconstruction.Image(1);

    EXPECT_EQ(added_image.Name(), images[1].file_name);



    const colmap::Point3D& added_point = reconstruction.Point3D(1);

    EXPECT_EQ(added_point.xyz, tracks[1].xyz);

}
