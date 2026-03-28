#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "glomap/estimators/global_positioning.h"

#include "glomap/scene/view_graph.h"

#include "glomap/scene/track.h"



using namespace glomap;



// Mock classes if needed



class GlobalPositionerTest : public ::testing::Test {

protected:

    GlobalPositionerOptions options;

    GlobalPositioner positioner;



    GlobalPositionerTest() : positioner(options) {}



    ViewGraph CreateSampleViewGraph() {

        ViewGraph view_graph;

        // Populate view_graph with sample data

        return view_graph;

    }



    std::unordered_map<rig_t, Rig> CreateSampleRigs() {

        std::unordered_map<rig_t, Rig> rigs;

        // Populate rigs with sample data

        return rigs;

    }



    std::unordered_map<track_t, Track> CreateSampleTracks() {

        std::unordered_map<track_t, Track> tracks;

        // Populate tracks with sample data

        return tracks;

    }

};



TEST_F(GlobalPositionerTest_104, SetupProblemWithEmptyData_104) {

    ViewGraph view_graph = CreateSampleViewGraph();

    std::unordered_map<rig_t, Rig> rigs = {};

    std::unordered_map<track_t, Track> tracks = {};



    positioner.SetupProblem(view_graph, rigs, tracks);



    // Verify that scales and rig_scales are correctly initialized

    EXPECT_TRUE(positioner.scales_.empty());

    EXPECT_TRUE(positioner.rig_scales_.empty());

}



TEST_F(GlobalPositionerTest_104, SetupProblemWithSampleData_104) {

    ViewGraph view_graph = CreateSampleViewGraph();

    std::unordered_map<rig_t, Rig> rigs = CreateSampleRigs();

    std::unordered_map<track_t, Track> tracks = CreateSampleTracks();



    positioner.SetupProblem(view_graph, rigs, tracks);



    // Verify that scales and rig_scales are correctly initialized

    EXPECT_EQ(positioner.scales_.size(), view_graph.image_pairs.size() + 

        std::accumulate(tracks.begin(), tracks.end(), 0, [](int sum, const std::pair<track_t, Track>& track) {

            return sum + track.second.observations.size();

        }));

    for (const auto& [rig_id, rig] : rigs) {

        EXPECT_EQ(positioner.rig_scales_[rig_id], 1.0);

    }

}



TEST_F(GlobalPositionerTest_104, SetupProblemWithNoTracks_104) {

    ViewGraph view_graph = CreateSampleViewGraph();

    std::unordered_map<rig_t, Rig> rigs = CreateSampleRigs();

    std::unordered_map<track_t, Track> tracks = {};



    positioner.SetupProblem(view_graph, rigs, tracks);



    // Verify that scales and rig_scales are correctly initialized

    EXPECT_EQ(positioner.scales_.size(), view_graph.image_pairs.size());

    for (const auto& [rig_id, rig] : rigs) {

        EXPECT_EQ(positioner.rig_scales_[rig_id], 1.0);

    }

}



TEST_F(GlobalPositionerTest_104, SetupProblemWithNoRigs_104) {

    ViewGraph view_graph = CreateSampleViewGraph();

    std::unordered_map<rig_t, Rig> rigs = {};

    std::unordered_map<track_t, Track> tracks = CreateSampleTracks();



    positioner.SetupProblem(view_graph, rigs, tracks);



    // Verify that scales and rig_scales are correctly initialized

    EXPECT_EQ(positioner.scales_.size(), view_graph.image_pairs.size() + 

        std::accumulate(tracks.begin(), tracks.end(), 0, [](int sum, const std::pair<track_t, Track>& track) {

            return sum + track.second.observations.size();

        }));

    EXPECT_TRUE(positioner.rig_scales_.empty());

}
