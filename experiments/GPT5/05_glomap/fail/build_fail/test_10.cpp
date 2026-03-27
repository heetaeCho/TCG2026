// File: bundle_adjustment_test.cc

#include <gtest/gtest.h>
#include <unordered_map>

#include <ceres/ceres.h>

#include "glomap/estimators/bundle_adjustment.h"

using namespace glomap;

// -----------------------------------------------------------------------------
// Test-time stub for ceres::Solve
// Treat ceres as an external collaborator and replace Solve with a stub so that
// we can control Solver::Summary::IsSolutionUsable() and inspect options.
// -----------------------------------------------------------------------------

namespace {

// Global state observed/controlled by the stub.
bool g_solve_called = false;
bool g_force_usable_solution = true;
ceres::Problem* g_last_problem = nullptr;
ceres::Solver::Options g_last_options;

void ResetCeresMock() {
  g_solve_called = false;
  g_force_usable_solution = true;
  g_last_problem = nullptr;
  g_last_options = ceres::Solver::Options();
}

}  // namespace

namespace ceres {

// Stub implementation of ceres::Solve used only in tests.
// It records the arguments and sets the termination_type so that
// Summary::IsSolutionUsable() returns a controlled value.
void Solve(const ceres::Solver::Options& options,
           ceres::Problem* problem,
           ceres::Solver::Summary* summary) {
  g_solve_called = true;
  g_last_problem = problem;
  g_last_options = options;

  if (summary != nullptr) {
    *summary = ceres::Solver::Summary();
    summary->termination_type =
        g_force_usable_solution ? ceres::CONVERGENCE : ceres::FAILURE;
  }
}

}  // namespace ceres

// -----------------------------------------------------------------------------
// Test fixture
// -----------------------------------------------------------------------------

class BundleAdjusterTest_10 : public ::testing::Test {
 protected:
  void SetUp() override { ResetCeresMock(); }
};

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

// images is empty -> early return false, ceres::Solve must NOT be called.
TEST_F(BundleAdjusterTest_10, SolveReturnsFalseWhenImagesEmpty_10) {
  BundleAdjuster adjuster;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;  // empty
  std::unordered_map<track_t, Track> tracks;  // can be empty as well

  const bool result = adjuster.Solve(rigs, cameras, frames, images, tracks);

  EXPECT_FALSE(result);
  EXPECT_FALSE(g_solve_called) << "ceres::Solve should not be called "
                                  "when images are empty.";
}

// images non-empty, tracks empty -> early return false, ceres::Solve not called.
TEST_F(BundleAdjusterTest_10, SolveReturnsFalseWhenTracksEmpty_10) {
  BundleAdjuster adjuster;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;  // empty

  // Ensure at least one image so that the first early-return is bypassed.
  image_t image_id = static_cast<image_t>(0);
  images.emplace(image_id, Image());

  const bool result = adjuster.Solve(rigs, cameras, frames, images, tracks);

  EXPECT_FALSE(result);
  EXPECT_FALSE(g_solve_called) << "ceres::Solve should not be called "
                                  "when tracks are empty.";
}

// Non-empty images and tracks -> ceres::Solve is called, and the return value
// matches Summary::IsSolutionUsable() == true.
TEST_F(BundleAdjusterTest_10,
       SolveCallsCeresSolveAndReturnsTrueWhenSolutionUsable_10) {
  BundleAdjuster adjuster;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  image_t image_id = static_cast<image_t>(0);
  track_t track_id = static_cast<track_t>(0);

  images.emplace(image_id, Image());
  tracks.emplace(track_id, Track());

  // Configure stub to report a "usable" solution.
  g_force_usable_solution = true;

  const bool result = adjuster.Solve(rigs, cameras, frames, images, tracks);

  EXPECT_TRUE(result);
  EXPECT_TRUE(g_solve_called) << "ceres::Solve should be called when both "
                                 "images and tracks are non-empty.";
  EXPECT_NE(g_last_problem, nullptr)
      << "BundleAdjuster should pass a valid ceres::Problem pointer to ceres::Solve.";
  EXPECT_EQ(g_last_options.linear_solver_type, ceres::SPARSE_SCHUR)
      << "Solve must configure linear_solver_type = SPARSE_SCHUR before calling ceres.";
  EXPECT_EQ(g_last_options.preconditioner_type, ceres::CLUSTER_TRIDIAGONAL)
      << "Solve must configure preconditioner_type = CLUSTER_TRIDIAGONAL "
         "before calling ceres.";
}

// Non-empty images and tracks -> ceres::Solve is called, and the return value
// matches Summary::IsSolutionUsable() == false.
TEST_F(BundleAdjusterTest_10,
       SolveCallsCeresSolveAndReturnsFalseWhenSolutionNotUsable_10) {
  BundleAdjuster adjuster;

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<camera_t, Camera> cameras;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<image_t, Image> images;
  std::unordered_map<track_t, Track> tracks;

  image_t image_id = static_cast<image_t>(1);
  track_t track_id = static_cast<track_t>(1);

  images.emplace(image_id, Image());
  tracks.emplace(track_id, Track());

  // Configure stub to report a "non-usable" solution.
  g_force_usable_solution = false;

  const bool result = adjuster.Solve(rigs, cameras, frames, images, tracks);

  EXPECT_FALSE(result);
  EXPECT_TRUE(g_solve_called) << "ceres::Solve should be called when both "
                                 "images and tracks are non-empty.";
  EXPECT_NE(g_last_problem, nullptr)
      << "BundleAdjuster should pass a valid ceres::Problem pointer to ceres::Solve.";
  EXPECT_EQ(g_last_options.linear_solver_type, ceres::SPARSE_SCHUR);
  EXPECT_EQ(g_last_options.preconditioner_type, ceres::CLUSTER_TRIDIAGONAL);
}
