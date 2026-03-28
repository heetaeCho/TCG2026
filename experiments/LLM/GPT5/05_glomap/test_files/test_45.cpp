// File: option_manager_add_bundle_adjuster_options_test_45.cc

#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "glomap/controllers/option_manager.h"
#include "glomap/controllers/global_mapper.h"

namespace glomap {

class OptionManagerTest_45 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Construct OptionManager without automatically adding project options,
    // so tests can control exactly which options are registered.
    option_manager_ = std::make_unique<OptionManager>(false);
    option_manager_->mapper = std::make_shared<GlobalMapperOptions>();
  }

  std::unique_ptr<OptionManager> option_manager_;
};

// Normal operation: verify that bundle adjustment options are registered
// such that Parse() updates the underlying BundleAdjusterOptions fields
// from command-line arguments.
TEST_F(OptionManagerTest_45, ParsesBundleAdjusterOptionsFromCommandLine_45) {
  ASSERT_NE(option_manager_->mapper, nullptr);

  // Ensure known initial values (some already have defaults, but we set them
  // explicitly to make expectations clear and independent of implementation).
  option_manager_->mapper->opt_ba.use_gpu = true;
  option_manager_->mapper->opt_ba.gpu_index = "-1";
  option_manager_->mapper->opt_ba.optimize_rig_poses = false;
  option_manager_->mapper->opt_ba.optimize_rotations = true;
  option_manager_->mapper->opt_ba.optimize_translation = true;
  option_manager_->mapper->opt_ba.optimize_intrinsics = true;
  option_manager_->mapper->opt_ba.optimize_principal_point = false;
  option_manager_->mapper->opt_ba.optimize_points = true;
  option_manager_->mapper->opt_ba.thres_loss_function = 0.1;
  option_manager_->mapper->opt_ba.solver_options.max_num_iterations = 10;

  // Register bundle adjustment options.
  option_manager_->AddBundleAdjusterOptions();

  // Build argv with bundle adjustment flags.
  char arg0[] = "test_app";
  char arg1[] = "--BundleAdjustment.use_gpu=false";
  char arg2[] = "--BundleAdjustment.gpu_index=1";
  char arg3[] = "--BundleAdjustment.optimize_rig_poses=true";
  char arg4[] = "--BundleAdjustment.optimize_rotations=false";
  char arg5[] = "--BundleAdjustment.optimize_translation=false";
  char arg6[] = "--BundleAdjustment.optimize_intrinsics=false";
  char arg7[] = "--BundleAdjustment.optimize_principal_point=true";
  char arg8[] = "--BundleAdjustment.optimize_points=false";
  char arg9[] = "--BundleAdjustment.thres_loss_function=0.5";
  char arg10[] = "--BundleAdjustment.max_num_iterations=50";

  char* argv[] = {
      arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10};
  int argc = static_cast<int>(sizeof(argv) / sizeof(argv[0]));

  // Parse should assign the registered options into mapper->opt_ba.
  option_manager_->Parse(argc, argv);

  EXPECT_FALSE(option_manager_->mapper->opt_ba.use_gpu);
  EXPECT_EQ(option_manager_->mapper->opt_ba.gpu_index, std::string("1"));
  EXPECT_TRUE(option_manager_->mapper->opt_ba.optimize_rig_poses);
  EXPECT_FALSE(option_manager_->mapper->opt_ba.optimize_rotations);
  EXPECT_FALSE(option_manager_->mapper->opt_ba.optimize_translation);
  EXPECT_FALSE(option_manager_->mapper->opt_ba.optimize_intrinsics);
  EXPECT_TRUE(option_manager_->mapper->opt_ba.optimize_principal_point);
  EXPECT_FALSE(option_manager_->mapper->opt_ba.optimize_points);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_ba.thres_loss_function, 0.5);
  EXPECT_EQ(option_manager_->mapper->opt_ba.solver_options.max_num_iterations,
            50);
}

// Boundary / idempotence: calling AddBundleAdjusterOptions multiple times
// should not cause duplicate registration errors or change behavior of Parse().
TEST_F(OptionManagerTest_45, AddBundleAdjusterOptionsIsIdempotent_45) {
  ASSERT_NE(option_manager_->mapper, nullptr);

  // Known initial values.
  option_manager_->mapper->opt_ba.use_gpu = true;
  option_manager_->mapper->opt_ba.gpu_index = "-1";
  option_manager_->mapper->opt_ba.optimize_rig_poses = false;
  option_manager_->mapper->opt_ba.thres_loss_function = 0.1;
  option_manager_->mapper->opt_ba.solver_options.max_num_iterations = 20;

  // Call twice; second call should effectively be a no-op.
  option_manager_->AddBundleAdjusterOptions();
  EXPECT_NO_THROW(option_manager_->AddBundleAdjusterOptions());

  // Provide a subset of options on the command line.
  char arg0[] = "test_app";
  char arg1[] = "--BundleAdjustment.use_gpu=false";
  char arg2[] = "--BundleAdjustment.gpu_index=2";
  char arg3[] = "--BundleAdjustment.max_num_iterations=40";

  char* argv[] = {arg0, arg1, arg2, arg3};
  int argc = static_cast<int>(sizeof(argv) / sizeof(argv[0]));

  EXPECT_NO_THROW(option_manager_->Parse(argc, argv));

  // Values provided via command line should be applied correctly.
  EXPECT_FALSE(option_manager_->mapper->opt_ba.use_gpu);
  EXPECT_EQ(option_manager_->mapper->opt_ba.gpu_index, std::string("2"));
  EXPECT_EQ(option_manager_->mapper->opt_ba.solver_options.max_num_iterations,
            40);

  // Options not specified on the command line should keep their previous values
  // (as determined by the combination of defaults and initial assignments).
  EXPECT_FALSE(option_manager_->mapper->opt_ba.optimize_rig_poses);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_ba.thres_loss_function, 0.1);
}

// Boundary: when no bundle adjustment options are specified on the command line,
// Parse() should leave the BundleAdjusterOptions values unchanged from their
// pre-Parse state (i.e., respect registered defaults).
TEST_F(OptionManagerTest_45, UnspecifiedOptionsKeepExistingValues_45) {
  ASSERT_NE(option_manager_->mapper, nullptr);

  // Set non-default values before registration to act as defaults.
  option_manager_->mapper->opt_ba.use_gpu = false;
  option_manager_->mapper->opt_ba.optimize_points = false;
  option_manager_->mapper->opt_ba.thres_loss_function = 0.25;
  option_manager_->mapper->opt_ba.solver_options.max_num_iterations = 30;

  option_manager_->AddBundleAdjusterOptions();

  // No bundle-adjustment-related flags in argv.
  char arg0[] = "test_app";
  char* argv[] = {arg0};
  int argc = 1;

  option_manager_->Parse(argc, argv);

  // Since nothing was specified on the command line, the values should remain
  // as they were prior to Parse (i.e., existing/default values are preserved).
  EXPECT_FALSE(option_manager_->mapper->opt_ba.use_gpu);
  EXPECT_FALSE(option_manager_->mapper->opt_ba.optimize_points);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_ba.thres_loss_function, 0.25);
  EXPECT_EQ(option_manager_->mapper->opt_ba.solver_options.max_num_iterations,
            30);
}

}  // namespace glomap
