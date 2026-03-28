// File: option_manager_add_view_graph_calibration_options_test_40.cc

#include <gtest/gtest.h>

#include "glomap/controllers/option_manager.h"
#include "glomap/controllers/global_mapper.h"

namespace glomap {

class OptionManagerViewGraphCalibrationOptionsTest_40 : public ::testing::Test {
protected:
  void SetUp() override {
    // Construct OptionManager without automatically adding project options.
    option_manager_ = std::make_unique<OptionManager>(false);
    // Ensure mapper exists so that AddViewGraphCalibrationOptions can safely
    // register options that point into opt_vgcalib.
    option_manager_->mapper = std::make_shared<GlobalMapperOptions>();
  }

  std::unique_ptr<OptionManager> option_manager_;
};

// Verifies that calling AddViewGraphCalibrationOptions alone does not
// change the default values in opt_vgcalib before parsing any arguments.
TEST_F(OptionManagerViewGraphCalibrationOptionsTest_40,
       DoesNotModifyDefaultsBeforeParse_40) {
  ASSERT_NE(option_manager_->mapper, nullptr);
  const auto& before = option_manager_->mapper->opt_vgcalib;

  // Record defaults.
  const double default_lower = before.thres_lower_ratio;
  const double default_higher = before.thres_higher_ratio;
  const double default_two_view = before.thres_two_view_error;

  // Act: just register options.
  option_manager_->AddViewGraphCalibrationOptions();

  const auto& after = option_manager_->mapper->opt_vgcalib;

  // Assert: defaults remain unchanged.
  EXPECT_DOUBLE_EQ(after.thres_lower_ratio, default_lower);
  EXPECT_DOUBLE_EQ(after.thres_higher_ratio, default_higher);
  EXPECT_DOUBLE_EQ(after.thres_two_view_error, default_two_view);
}

// Verifies that after AddViewGraphCalibrationOptions, OptionManager::Parse
// can update all related option values from command-line arguments.
TEST_F(OptionManagerViewGraphCalibrationOptionsTest_40,
       RegistersOptionsAndParsesValues_40) {
  ASSERT_NE(option_manager_->mapper, nullptr);
  auto& opts = option_manager_->mapper->opt_vgcalib;

  // Sanity-check that we start from known defaults (from the options struct).
  const double initial_lower = opts.thres_lower_ratio;
  const double initial_higher = opts.thres_higher_ratio;
  const double initial_two_view = opts.thres_two_view_error;

  // Register options.
  option_manager_->AddViewGraphCalibrationOptions();

  // Prepare argv for Parse.
  char arg0[] = "test_binary";
  char arg1[] = "--ViewGraphCalib.thres_lower_ratio=0.2";
  char arg2[] = "--ViewGraphCalib.thres_higher_ratio=5.5";
  char arg3[] = "--ViewGraphCalib.thres_two_view_error=1.25";

  char* argv[] = {arg0, arg1, arg2, arg3};
  const int argc = static_cast<int>(sizeof(argv) / sizeof(argv[0]));

  // Act: parse command-line options.
  option_manager_->Parse(argc, argv);

  // Assert: all three values should be updated from the CLI.
  EXPECT_DOUBLE_EQ(opts.thres_lower_ratio, 0.2);
  EXPECT_DOUBLE_EQ(opts.thres_higher_ratio, 5.5);
  EXPECT_DOUBLE_EQ(opts.thres_two_view_error, 1.25);

  // Ensure that they indeed changed from their initial values (if different).
  // (If any initial value coincidentally equals the new one, this still passes.)
  // These checks guard against Parse being a no-op.
  if (initial_lower != 0.2) {
    EXPECT_NE(opts.thres_lower_ratio, initial_lower);
  }
  if (initial_higher != 5.5) {
    EXPECT_NE(opts.thres_higher_ratio, initial_higher);
  }
  if (initial_two_view != 1.25) {
    EXPECT_NE(opts.thres_two_view_error, initial_two_view);
  }
}

// Verifies that if only a subset of view-graph calibration options are
// provided on the command line, the others keep their defaults.
TEST_F(OptionManagerViewGraphCalibrationOptionsTest_40,
       ParsesPartialArgumentsAndPreservesOtherDefaults_40) {
  ASSERT_NE(option_manager_->mapper, nullptr);
  auto& opts = option_manager_->mapper->opt_vgcalib;

  const double default_lower = opts.thres_lower_ratio;
  const double default_higher = opts.thres_higher_ratio;
  const double default_two_view = opts.thres_two_view_error;

  option_manager_->AddViewGraphCalibrationOptions();

  // Only override thres_two_view_error.
  char arg0[] = "test_binary";
  char arg1[] = "--ViewGraphCalib.thres_two_view_error=3.75";

  char* argv[] = {arg0, arg1};
  const int argc = static_cast<int>(sizeof(argv) / sizeof(argv[0]));

  option_manager_->Parse(argc, argv);

  // Assert: only the provided option changes, others remain defaults.
  EXPECT_DOUBLE_EQ(opts.thres_two_view_error, 3.75);
  EXPECT_DOUBLE_EQ(opts.thres_lower_ratio, default_lower);
  EXPECT_DOUBLE_EQ(opts.thres_higher_ratio, default_higher);

  if (default_two_view != 3.75) {
    EXPECT_NE(opts.thres_two_view_error, default_two_view);
  }
}

// Verifies that calling AddViewGraphCalibrationOptions multiple times is
// safe and does not prevent proper parsing (idempotent registration).
TEST_F(OptionManagerViewGraphCalibrationOptionsTest_40,
       MultipleCallsAreIdempotent_40) {
  ASSERT_NE(option_manager_->mapper, nullptr);
  auto& opts = option_manager_->mapper->opt_vgcalib;

  const double default_lower = opts.thres_lower_ratio;
  const double default_higher = opts.thres_higher_ratio;
  const double default_two_view = opts.thres_two_view_error;

  // Call multiple times; internal implementation should ignore subsequent calls.
  option_manager_->AddViewGraphCalibrationOptions();
  option_manager_->AddViewGraphCalibrationOptions();
  option_manager_->AddViewGraphCalibrationOptions();

  char arg0[] = "test_binary";
  char arg1[] = "--ViewGraphCalib.thres_lower_ratio=0.05";
  char arg2[] = "--ViewGraphCalib.thres_higher_ratio=20.0";

  char* argv[] = {arg0, arg1, arg2};
  const int argc = static_cast<int>(sizeof(argv) / sizeof(argv[0]));

  option_manager_->Parse(argc, argv);

  // Assert: options still parse correctly after multiple registration attempts.
  EXPECT_DOUBLE_EQ(opts.thres_lower_ratio, 0.05);
  EXPECT_DOUBLE_EQ(opts.thres_higher_ratio, 20.0);
  // Unspecified option keeps its default.
  EXPECT_DOUBLE_EQ(opts.thres_two_view_error, default_two_view);

  // Ensure they changed from initial values where appropriate.
  if (default_lower != 0.05) {
    EXPECT_NE(opts.thres_lower_ratio, default_lower);
  }
  if (default_higher != 20.0) {
    EXPECT_NE(opts.thres_higher_ratio, default_higher);
  }
}

}  // namespace glomap
