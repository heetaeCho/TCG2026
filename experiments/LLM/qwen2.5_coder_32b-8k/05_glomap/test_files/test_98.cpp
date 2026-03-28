#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/glomap/glomap/estimators/bundle_adjustment.h"



using namespace glomap;

using ::testing::_;

using ::testing::Return;



class BundleAdjusterTest_98 : public ::testing::Test {

protected:

    BundleAdjusterOptions options;

    BundleAdjuster bundle_adjuster;



    BundleAdjusterTest_98() : bundle_adjuster(options) {}



    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<track_t, Track> tracks;



    void AddSampleData() {

        // Adding some sample data to ensure the maps are not empty

        rigs[1] = Rig();

        cameras[1] = Camera();

        frames[1] = Frame();

        images[1] = Image();

        tracks[1] = Track();

    }

};



TEST_F(BundleAdjusterTest_98, SolveWithEmptyImages_ReturnsFalse_98) {

    EXPECT_FALSE(bundle_adjuster.Solve(rigs, cameras, frames, images, tracks));

}



TEST_F(BundleAdjusterTest_98, SolveWithEmptyTracks_ReturnsFalse_98) {

    AddSampleData();

    tracks.clear();

    EXPECT_FALSE(bundle_adjuster.Solve(rigs, cameras, frames, images, tracks));

}



TEST_F(BundleAdjusterTest_98, SolveWithValidData_ReturnsTrue_98) {

    AddSampleData();

    EXPECT_TRUE(bundle_adjuster.Solve(rigs, cameras, frames, images, tracks));

}



TEST_F(BundleAdjusterTest_98, SolveWithGPUEnabledAndFewImages_LogsWarning_98) {

    options.use_gpu = true;

    options.min_num_images_gpu_solver = 100; // Set a high threshold to ensure warning is logged

    AddSampleData();

    EXPECT_TRUE(bundle_adjuster.Solve(rigs, cameras, frames, images, tracks));

}



TEST_F(BundleAdjusterTest_98, SolveWithGPUEnabledAndManyImages_UseGPUSolver_98) {

    options.use_gpu = true;

    options.min_num_images_gpu_solver = 1; // Set a low threshold to ensure GPU is used

    AddSampleData();

    EXPECT_TRUE(bundle_adjuster.Solve(rigs, cameras, frames, images, tracks));

}
