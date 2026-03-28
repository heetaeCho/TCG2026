// File: option_manager_add_inlier_threshold_options_test_47.cc

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

#include "glomap/controllers/option_manager.h"
#include "glomap/controllers/global_mapper.h"
#include "glomap/types.h"

namespace {

class OptionManagerInlierThresholdOptionsTest_47 : public ::testing::Test {
 protected:
  glomap::OptionManager manager;

  OptionManagerInlierThresholdOptionsTest_47()
      : manager(false) {  // do not auto-add project options
  }

  void SetUp() override {
    // Ensure mapper is initialized so AddInlierThresholdOptions can safely
    // register options using mapper->inlier_thresholds.
    manager.mapper = std::make_shared<glomap::GlobalMapperOptions>();
  }

  // Helper to build argc/argv for Parse.
  void BuildArgv(const std::vector<std::string>& args,
                 int* argc,
                 std::vector<char*>* argv_storage) {
    argv_storage->clear();
    for (const auto& a : args) {
      // const_cast is safe here for typical main-style argv usage in tests.
      argv_storage->push_back(const_cast<char*>(a.c_str()));
    }
    *argc = static_cast<int>(argv_storage->size());
  }
};

// -----------------------------------------------------------------------------
// Test 1: Normal operation.
// Verifies that AddInlierThresholdOptions registers options so that Parse
// correctly updates the underlying mapper->inlier_thresholds values.
// -----------------------------------------------------------------------------
TEST_F(OptionManagerInlierThresholdOptionsTest_47,
       RegistersThresholdOptionsAndParsesValues_47) {
  ASSERT_NE(manager.mapper, nullptr);

  // Call the function under test.
  manager.AddInlierThresholdOptions();

  // Provide custom values via command-line options.
  std::vector<std::string> args = {
      "test_binary",
      "--Thresholds.max_angle_error=2.5",
      "--Thresholds.max_reprojection_error=0.02",
      "--Thresholds.min_triangulation_angle=5.0",
      "--Thresholds.max_epipolar_error_E=1.5",
      "--Thresholds.max_epipolar_error_F=5.0",
      "--Thresholds.max_epipolar_error_H=6.0",
      "--Thresholds.min_inlier_num=100",
      "--Thresholds.min_inlier_ratio=0.5",
      "--Thresholds.max_rotation_error=20.0",
  };

  int argc = 0;
  std::vector<char*> argv;
  BuildArgv(args, &argc, &argv);

  // Parse should propagate values into mapper->inlier_thresholds.
  manager.Parse(argc, argv.data());

  const glomap::InlierThresholdOptions& thr =
      manager.mapper->inlier_thresholds;

  EXPECT_DOUBLE_EQ(thr.max_angle_error, 2.5);
  EXPECT_DOUBLE_EQ(thr.max_reprojection_error, 0.02);
  EXPECT_DOUBLE_EQ(thr.min_triangulation_angle, 5.0);
  EXPECT_DOUBLE_EQ(thr.max_epipolar_error_E, 1.5);
  EXPECT_DOUBLE_EQ(thr.max_epipolar_error_F, 5.0);
  EXPECT_DOUBLE_EQ(thr.max_epipolar_error_H, 6.0);
  EXPECT_DOUBLE_EQ(thr.min_inlier_num, 100.0);
  EXPECT_DOUBLE_EQ(thr.min_inlier_ratio, 0.5);
  EXPECT_DOUBLE_EQ(thr.max_rotation_error, 20.0);
}

// -----------------------------------------------------------------------------
// Test 2: Boundary/edge condition.
// Calling AddInlierThresholdOptions should *not* modify the current values
// by itself; without Parse, thresholds remain unchanged.
// -----------------------------------------------------------------------------
TEST_F(OptionManagerInlierThresholdOptionsTest_47,
       DoesNotModifyThresholdsWithoutParse_47) {
  ASSERT_NE(manager.mapper, nullptr);

  // Store original defaults.
  glomap::InlierThresholdOptions original =
      manager.mapper->inlier_thresholds;

  // Just register options; do not call Parse.
  manager.AddInlierThresholdOptions();

  const glomap::InlierThresholdOptions& thr =
      manager.mapper->inlier_thresholds;

  EXPECT_DOUBLE_EQ(thr.max_angle_error, original.max_angle_error);
  EXPECT_DOUBLE_EQ(thr.max_reprojection_error, original.max_reprojection_error);
  EXPECT_DOUBLE_EQ(thr.min_triangulation_angle,
                   original.min_triangulation_angle);
  EXPECT_DOUBLE_EQ(thr.max_epipolar_error_E, original.max_epipolar_error_E);
  EXPECT_DOUBLE_EQ(thr.max_epipolar_error_F, original.max_epipolar_error_F);
  EXPECT_DOUBLE_EQ(thr.max_epipolar_error_H, original.max_epipolar_error_H);
  EXPECT_DOUBLE_EQ(thr.min_inlier_num, original.min_inlier_num);
  EXPECT_DOUBLE_EQ(thr.min_inlier_ratio, original.min_inlier_ratio);
  EXPECT_DOUBLE_EQ(thr.max_rotation_error, original.max_rotation_error);
}

// -----------------------------------------------------------------------------
// Test 3: Idempotence / multiple calls.
// Calling AddInlierThresholdOptions more than once should be safe and should
// not prevent Parse from working as expected.
// -----------------------------------------------------------------------------
TEST_F(OptionManagerInlierThresholdOptionsTest_47,
       MultipleCallsAreIdempotentForParsing_47) {
  ASSERT_NE(manager.mapper, nullptr);

  // First and second call; second call should effectively be a no-op
  // according to the implementation's guard, but we only check observable
  // behavior via Parse.
  manager.AddInlierThresholdOptions();
  manager.AddInlierThresholdOptions();

  std::vector<std::string> args = {
      "test_binary",
      "--Thresholds.max_angle_error=3.0",
      "--Thresholds.max_reprojection_error=0.03",
  };

  int argc = 0;
  std::vector<char*> argv;
  BuildArgv(args, &argc, &argv);

  manager.Parse(argc, argv.data());

  const glomap::InlierThresholdOptions& thr =
      manager.mapper->inlier_thresholds;

  EXPECT_DOUBLE_EQ(thr.max_angle_error, 3.0);
  EXPECT_DOUBLE_EQ(thr.max_reprojection_error, 0.03);
}

// -----------------------------------------------------------------------------
// Test 4: Exceptional / error case.
// If an invalid (non-numeric) value is provided for a numeric threshold,
// Parse is expected to fail with some std::exception-derived error.
// We don't rely on the exact exception type from the internal implementation.
// -----------------------------------------------------------------------------
TEST_F(OptionManagerInlierThresholdOptionsTest_47,
       ParseThrowsOnInvalidNumericValue_47) {
  ASSERT_NE(manager.mapper, nullptr);

  manager.AddInlierThresholdOptions();

  std::vector<std::string> args = {
      "test_binary",
      "--Thresholds.max_angle_error=not_a_number",
  };

  int argc = 0;
  std::vector<char*> argv;
  BuildArgv(args, &argc, &argv);

  EXPECT_THROW(
      {
        manager.Parse(argc, argv.data());
      },
      std::exception);
}

}  // namespace
