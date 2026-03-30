#include <memory>

#include "gtest/gtest.h"
#include "glomap/controllers/option_manager.h"
#include "glomap/controllers/global_mapper.h"

namespace glomap {

class OptionManagerTest_38 : public ::testing::Test {
 protected:
  OptionManagerTest_38() : manager_(false) {}

  OptionManager manager_;
};

// Verify that AddGlobalMapperResumeOptions sets the expected "resume" flags on
// GlobalMapperOptions and can be called in normal conditions.
TEST_F(OptionManagerTest_38, AddGlobalMapperResumeOptionsSetsResumeFlags_38) {
  auto mapper = std::make_shared<GlobalMapperOptions>();

  // Set non-resume initial values explicitly to make the change observable.
  mapper->skip_preprocessing = false;
  mapper->skip_view_graph_calibration = false;
  mapper->skip_relative_pose_estimation = false;
  mapper->skip_rotation_averaging = false;
  mapper->skip_track_establishment = false;
  mapper->skip_retriangulation = false;

  // Other flags can be arbitrary; they are not directly modified in this method.
  mapper->skip_global_positioning = false;
  mapper->skip_bundle_adjustment = false;
  mapper->skip_pruning = true;

  manager_.mapper = mapper;

  manager_.AddGlobalMapperResumeOptions();

  // Flags that are explicitly set in AddGlobalMapperResumeOptions().
  EXPECT_TRUE(mapper->skip_preprocessing);
  EXPECT_TRUE(mapper->skip_view_graph_calibration);
  EXPECT_TRUE(mapper->skip_relative_pose_estimation);
  EXPECT_TRUE(mapper->skip_rotation_averaging);
  EXPECT_TRUE(mapper->skip_track_establishment);
  EXPECT_TRUE(mapper->skip_retriangulation);
}

// Verify that calling AddGlobalMapperResumeOptions multiple times is safe and
// does not change the externally observable state after the first call.
TEST_F(OptionManagerTest_38, AddGlobalMapperResumeOptionsIsIdempotent_38) {
  auto mapper = std::make_shared<GlobalMapperOptions>();

  // Start from a known state.
  mapper->skip_preprocessing = false;
  mapper->skip_view_graph_calibration = false;
  mapper->skip_relative_pose_estimation = false;
  mapper->skip_rotation_averaging = false;
  mapper->skip_track_establishment = false;
  mapper->skip_retriangulation = false;

  manager_.mapper = mapper;

  // First call should set the resume-related flags.
  manager_.AddGlobalMapperResumeOptions();

  EXPECT_TRUE(mapper->skip_preprocessing);
  EXPECT_TRUE(mapper->skip_view_graph_calibration);
  EXPECT_TRUE(mapper->skip_relative_pose_estimation);
  EXPECT_TRUE(mapper->skip_rotation_averaging);
  EXPECT_TRUE(mapper->skip_track_establishment);
  EXPECT_TRUE(mapper->skip_retriangulation);

  // Call again; according to the implementation this should be a no-op.
  manager_.AddGlobalMapperResumeOptions();

  // State should remain the same as after the first call.
  EXPECT_TRUE(mapper->skip_preprocessing);
  EXPECT_TRUE(mapper->skip_view_graph_calibration);
  EXPECT_TRUE(mapper->skip_relative_pose_estimation);
  EXPECT_TRUE(mapper->skip_rotation_averaging);
  EXPECT_TRUE(mapper->skip_track_establishment);
  EXPECT_TRUE(mapper->skip_retriangulation);
}

}  // namespace glomap
