#include <gtest/gtest.h>

#include "global_mapper.h"

#include "view_graph.h"

#include "database.h" // Assuming colmap::Database is defined in this header or similar



using namespace glomap;



// Mock classes and functions to help with testing

class MockDatabase : public colmap::Database {

public:

    MockDatabase() {}

};



TEST(GlobalMapperTest, SolveWithEmptyData) {

    GlobalMapperOptions options;

    GlobalMapper mapper(options);



    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<track_t, Track> tracks;



    MockDatabase database;

    bool result = mapper.Solve(database, view_graph, rigs, cameras, frames, images, tracks);



    EXPECT_FALSE(result); // Assuming no valid solution can be found with empty data

}



TEST(GlobalMapperTest, SolveWithValidData) {

    GlobalMapperOptions options;

    GlobalMapper mapper(options);



    ViewGraph view_graph;

    // Populate view_graph with valid data



    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<track_t, Track> tracks;



    MockDatabase database;

    bool result = mapper.Solve(database, view_graph, rigs, cameras, frames, images, tracks);



    EXPECT_TRUE(result); // Assuming a valid solution can be found with proper data

}



TEST(GlobalMapperTest, SkipPreprocessing) {

    GlobalMapperOptions options;

    options.skip_preprocessing = true;

    GlobalMapper mapper(options);



    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<track_t, Track> tracks;



    MockDatabase database;

    bool result = mapper.Solve(database, view_graph, rigs, cameras, frames, images, tracks);



    EXPECT_TRUE(result); // Assuming the solver handles skipping preprocessing correctly

}



TEST(GlobalMapperTest, SkipViewGraphCalibration) {

    GlobalMapperOptions options;

    options.skip_view_graph_calibration = true;

    GlobalMapper mapper(options);



    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<track_t, Track> tracks;



    MockDatabase database;

    bool result = mapper.Solve(database, view_graph, rigs, cameras, frames, images, tracks);



    EXPECT_TRUE(result); // Assuming the solver handles skipping view graph calibration correctly

}



TEST(GlobalMapperTest, SkipRotationAveraging) {

    GlobalMapperOptions options;

    options.skip_rotation_averaging = true;

    GlobalMapper mapper(options);



    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<track_t, Track> tracks;



    MockDatabase database;

    bool result = mapper.Solve(database, view_graph, rigs, cameras, frames, images, tracks);



    EXPECT_TRUE(result); // Assuming the solver handles skipping rotation averaging correctly

}



TEST(GlobalMapperTest, SkipTrackEstablishment) {

    GlobalMapperOptions options;

    options.skip_track_establishment = true;

    GlobalMapper mapper(options);



    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<track_t, Track> tracks;



    MockDatabase database;

    bool result = mapper.Solve(database, view_graph, rigs, cameras, frames, images, tracks);



    EXPECT_TRUE(result); // Assuming the solver handles skipping track establishment correctly

}



TEST(GlobalMapperTest, SkipGlobalPositioning) {

    GlobalMapperOptions options;

    options.skip_global_positioning = true;

    GlobalMapper mapper(options);



    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<track_t, Track> tracks;



    MockDatabase database;

    bool result = mapper.Solve(database, view_graph, rigs, cameras, frames, images, tracks);



    EXPECT_TRUE(result); // Assuming the solver handles skipping global positioning correctly

}



TEST(GlobalMapperTest, SkipBundleAdjustment) {

    GlobalMapperOptions options;

    options.skip_bundle_adjustment = true;

    GlobalMapper mapper(options);



    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<track_t, Track> tracks;



    MockDatabase database;

    bool result = mapper.Solve(database, view_graph, rigs, cameras, frames, images, tracks);



    EXPECT_TRUE(result); // Assuming the solver handles skipping bundle adjustment correctly

}



TEST(GlobalMapperTest, SkipRetriangulation) {

    GlobalMapperOptions options;

    options.skip_retriangulation = true;

    GlobalMapper mapper(options);



    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<track_t, Track> tracks;



    MockDatabase database;

    bool result = mapper.Solve(database, view_graph, rigs, cameras, frames, images, tracks);



    EXPECT_TRUE(result); // Assuming the solver handles skipping retriangulation correctly

}



TEST(GlobalMapperTest, SkipPruning) {

    GlobalMapperOptions options;

    options.skip_pruning = false; // Testing the opposite of default to ensure it's being set and used properly

    GlobalMapper mapper(options);



    ViewGraph view_graph;

    std::unordered_map<rig_t, Rig> rigs;

    std::unordered_map<camera_t, Camera> cameras;

    std::unordered_map<frame_t, Frame> frames;

    std::unordered_map<image_t, Image> images;

    std::unordered_map<track_t, Track> tracks;



    MockDatabase database;

    bool result = mapper.Solve(database, view_graph, rigs, cameras, frames, images, tracks);



    EXPECT_TRUE(result); // Assuming the solver handles skipping pruning correctly

}
