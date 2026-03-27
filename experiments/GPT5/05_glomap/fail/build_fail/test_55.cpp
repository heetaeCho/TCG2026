#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Return;
using ::testing::_;

namespace glomap {

// ------------ Mock types to simulate external objects ------------
class MockViewGraph {
public:
    MOCK_METHOD(int, KeepLargestConnectedComponents,
                (std::unordered_map<frame_t, Frame>&,
                 std::unordered_map<image_t, Image>&),
                ());
};

class MockDatabase : public colmap::Database {};

// Many containers are required but their contents are irrelevant
static std::unordered_map<rig_t, Rig> rigs_dummy;
static std::unordered_map<camera_t, Camera> cameras_dummy;
static std::unordered_map<frame_t, Frame> frames_dummy;
static std::unordered_map<image_t, Image> images_dummy;
static std::unordered_map<track_t, Track> tracks_dummy;

// ---------------------- Test Fixture -----------------------------
class GlobalMapperTest_55 : public ::testing::Test {
protected:
    GlobalMapper mapper_;
    colmap::Database db_;
    MockViewGraph view_graph_;
};

// =================================================================
// 1. All skip flags enabled → Solve returns true
// =================================================================
TEST_F(GlobalMapperTest_55, Solve_AllStagesSkipped_ReturnsTrue_55) {
    mapper_.options_.skip_preprocessing = true;
    mapper_.options_.skip_view_graph_calibration = true;
    mapper_.options_.skip_relative_pose_estimation = true;
    mapper_.options_.skip_rotation_averaging = true;
    mapper_.options_.skip_track_establishment = true;
    mapper_.options_.skip_global_positioning = true;
    mapper_.options_.skip_bundle_adjustment = true;
    mapper_.options_.skip_retriangulation = true;
    mapper_.options_.skip_pruning = true;

    EXPECT_TRUE(mapper_.Solve(db_, view_graph_,
                              rigs_dummy, cameras_dummy, frames_dummy,
                              images_dummy, tracks_dummy));
}

// =================================================================
// 2. View graph connectivity failure → returns false
// =================================================================
TEST_F(GlobalMapperTest_55, Solve_ConnectivityZero_ReturnsFalse_55) {
    mapper_.options_.skip_preprocessing = true;
    mapper_.options_.skip_view_graph_calibration = true;
    mapper_.options_.skip_rotation_averaging = false;
    mapper_.options_.skip_relative_pose_estimation = true;

    EXPECT_CALL(view_graph_,
                KeepLargestConnectedComponents(_, _))
                .WillOnce(Return(0));   // triggers failure

    EXPECT_FALSE(mapper_.Solve(db_, view_graph_,
                               rigs_dummy, cameras_dummy, frames_dummy,
                               images_dummy, tracks_dummy));
}

// =================================================================
// 3. Global positioning: constraint type != ONLY_POINTS → false
// =================================================================
TEST_F(GlobalMapperTest_55, Solve_GlobalPositioningInvalidConstraint_ReturnsFalse_55) {
    mapper_.options_.skip_preprocessing = true;
    mapper_.options_.skip_view_graph_calibration = true;
    mapper_.options_.skip_rotation_averaging = true;
    mapper_.options_.skip_relative_pose_estimation = true;
    mapper_.options_.skip_track_establishment = true;
    mapper_.options_.skip_bundle_adjustment = true;
    mapper_.options_.skip_retriangulation = true;
    mapper_.options_.skip_pruning = true;

    mapper_.options_.skip_global_positioning = false;
    mapper_.options_.opt_gp.constraint_type =
        GlobalPositionerOptions::ConstraintType::XYZ; // != ONLY_POINTS

    EXPECT_FALSE(mapper_.Solve(db_, view_graph_,
                               rigs_dummy, cameras_dummy, frames_dummy,
                               images_dummy, tracks_dummy));
}

// =================================================================
// 4. Minimal working case → returns true
// =================================================================
TEST_F(GlobalMapperTest_55, Solve_MinimalNormalFlow_ReturnsTrue_55) {
    mapper_.options_.skip_preprocessing = true;
    mapper_.options_.skip_view_graph_calibration = true;
    mapper_.options_.skip_rotation_averaging = true;
    mapper_.options_.skip_track_establishment = true;
    mapper_.options_.skip_global_positioning = true;
    mapper_.options_.skip_bundle_adjustment = true;
    mapper_.options_.skip_retriangulation = true;
    mapper_.options_.skip_pruning = true;

    EXPECT_CALL(view_graph_,
                KeepLargestConnectedComponents(_, _))
                .Times(0);  // no stage requires this

    EXPECT_TRUE(mapper_.Solve(db_, view_graph_,
                              rigs_dummy, cameras_dummy, frames_dummy,
                              images_dummy, tracks_dummy));
}

} // namespace glomap
