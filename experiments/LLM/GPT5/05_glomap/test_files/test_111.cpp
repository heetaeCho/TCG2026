// File: global_positioner_convert_results_test_111.cc

#include <gtest/gtest.h>
#include <unordered_map>
#include <optional>

// Path taken from the prompt.
// Adjust include path if your project layout is different.
#include "glomap/estimators/global_positioning.cc"

namespace glomap {

// A simple test fixture for GlobalPositioner::ConvertResults.
class GlobalPositionerTest_111 : public ::testing::Test {
protected:
  GlobalPositioner positioner_;  // default-constructed; we don't touch internals
};

// Helper to set a 3D translation assuming a contiguous data() buffer.
static void SetTranslation3(double* data, double x, double y, double z) {
  data[0] = x;
  data[1] = y;
  data[2] = z;
}

static void ExpectTranslation3Eq(const double* data,
                                 double x, double y, double z) {
  EXPECT_DOUBLE_EQ(data[0], x);
  EXPECT_DOUBLE_EQ(data[1], y);
  EXPECT_DOUBLE_EQ(data[2], z);
}

// -----------------------------------------------------------------------------
// 1) Normal operation on a single frame
//    - rigs map is empty
//    - rig_scales_ is never populated, so operator[] will create a 0 scale
//    - final translation should therefore become zero, regardless of rotation.
// -----------------------------------------------------------------------------
TEST_F(GlobalPositionerTest_111,
       ConvertResults_SetsSingleFrameTranslationToZeroWhenNoRigScale_111) {
  std::unordered_map<rig_t, Rig> rigs;

  std::unordered_map<frame_t, Frame> frames;
  frame_t frame_id = static_cast<frame_t>(1);
  Frame frame;

  // Initialize frame translation to a non-zero value via data()
  auto& pose = frame.RigFromWorld();
  double* t = pose.translation.data();
  SetTranslation3(t, 1.0, 2.0, 3.0);

  frames.emplace(frame_id, frame);

  // Act
  positioner_.ConvertResults(rigs, frames);

  // Assert: because rig_scales_[idx] is default-initialized to 0.0,
  // translation should end up as zero vector.
  auto& updated_pose = frames.at(frame_id).RigFromWorld();
  const double* updated_t = updated_pose.translation.data();
  ExpectTranslation3Eq(updated_t, 0.0, 0.0, 0.0);
}

// -----------------------------------------------------------------------------
// 2) Multiple frames:
//    - Verify that ConvertResults processes all entries in frames.
//    - With an empty rig_scales_ map, all translations should become zero.
// -----------------------------------------------------------------------------
TEST_F(GlobalPositionerTest_111,
       ConvertResults_SetsAllFrameTranslationsToZeroWhenNoRigScale_111) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;

  Frame frame_a;
  Frame frame_b;

  auto& pose_a = frame_a.RigFromWorld();
  auto& pose_b = frame_b.RigFromWorld();

  SetTranslation3(pose_a.translation.data(), 10.0, -5.0, 2.0);
  SetTranslation3(pose_b.translation.data(), -3.0, 4.0, 7.0);

  frames.emplace(static_cast<frame_t>(1), frame_a);
  frames.emplace(static_cast<frame_t>(2), frame_b);

  // Act
  positioner_.ConvertResults(rigs, frames);

  // Assert: both frames should now have zero translation.
  const double* t_a = frames.at(static_cast<frame_t>(1))
                          .RigFromWorld()
                          .translation.data();
  const double* t_b = frames.at(static_cast<frame_t>(2))
                          .RigFromWorld()
                          .translation.data();

  ExpectTranslation3Eq(t_a, 0.0, 0.0, 0.0);
  ExpectTranslation3Eq(t_b, 0.0, 0.0, 0.0);
}

// -----------------------------------------------------------------------------
// 3) Boundary / robustness case:
//    - Empty frames map, non-empty rigs map.
//    - NonRefSensors() contains only sensors with std::nullopt (no value).
//    - This exercises the rig loop but never enters the branch that consults
//      problem_->HasParameterBlock, so we don't depend on problem_ being set.
//    - The main assertion is that this does not throw or crash.
// -----------------------------------------------------------------------------
TEST_F(GlobalPositionerTest_111,
       ConvertResults_HandlesEmptyFramesAndNulloptSensorsWithoutCrash_111) {
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;  // empty

  rig_t rig_id = static_cast<rig_t>(0);
  Rig rig;

  // Get the NonRefSensors() container and add an entry with no value.
  auto& sensors = rig.NonRefSensors();
  sensors.emplace(0, std::nullopt);

  rigs.emplace(rig_id, rig);

  // Just verifying that the call completes without throwing.
  // If problem_ or internal handling were incorrect, this could crash.
  ASSERT_NO_THROW(positioner_.ConvertResults(rigs, frames));
}

}  // namespace glomap
