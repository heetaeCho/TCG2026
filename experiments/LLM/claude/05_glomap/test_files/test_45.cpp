#include <gtest/gtest.h>
#include "glomap/controllers/option_manager.h"

namespace glomap {
namespace {

class OptionManagerBundleAdjusterTest_45 : public ::testing::Test {
 protected:
  void SetUp() override {
    // OptionManager constructor with false to avoid adding project options
    option_manager_ = std::make_unique<OptionManager>(false);
  }

  std::unique_ptr<OptionManager> option_manager_;
};

// Test that AddBundleAdjusterOptions can be called without crashing
TEST_F(OptionManagerBundleAdjusterTest_45, AddBundleAdjusterOptionsDoesNotCrash_45) {
  EXPECT_NO_THROW(option_manager_->AddBundleAdjusterOptions());
}

// Test that calling AddBundleAdjusterOptions twice is idempotent (guarded by added_bundle_adjustment_options_)
TEST_F(OptionManagerBundleAdjusterTest_45, AddBundleAdjusterOptionsIdempotent_45) {
  EXPECT_NO_THROW(option_manager_->AddBundleAdjusterOptions());
  EXPECT_NO_THROW(option_manager_->AddBundleAdjusterOptions());
}

// Test that mapper shared_ptr is valid and has default BA options before calling AddBundleAdjusterOptions
TEST_F(OptionManagerBundleAdjusterTest_45, MapperExistsWithDefaults_45) {
  ASSERT_NE(option_manager_->mapper, nullptr);
  // Check default values from BundleAdjusterOptions
  EXPECT_EQ(option_manager_->mapper->opt_ba.optimize_rig_poses, false);
  EXPECT_EQ(option_manager_->mapper->opt_ba.optimize_rotations, true);
  EXPECT_EQ(option_manager_->mapper->opt_ba.optimize_translation, true);
  EXPECT_EQ(option_manager_->mapper->opt_ba.optimize_intrinsics, true);
  EXPECT_EQ(option_manager_->mapper->opt_ba.optimize_principal_point, false);
  EXPECT_EQ(option_manager_->mapper->opt_ba.optimize_points, true);
  EXPECT_EQ(option_manager_->mapper->opt_ba.use_gpu, true);
}

// Test that after adding bundle adjuster options, default values are still consistent
TEST_F(OptionManagerBundleAdjusterTest_45, DefaultValuesAfterAdd_45) {
  option_manager_->AddBundleAdjusterOptions();

  ASSERT_NE(option_manager_->mapper, nullptr);
  // The AddAndRegisterDefaultOption should register the options but keep defaults
  EXPECT_EQ(option_manager_->mapper->opt_ba.optimize_rig_poses, false);
  EXPECT_EQ(option_manager_->mapper->opt_ba.optimize_rotations, true);
  EXPECT_EQ(option_manager_->mapper->opt_ba.optimize_translation, true);
  EXPECT_EQ(option_manager_->mapper->opt_ba.optimize_intrinsics, true);
  EXPECT_EQ(option_manager_->mapper->opt_ba.optimize_principal_point, false);
  EXPECT_EQ(option_manager_->mapper->opt_ba.optimize_points, true);
  EXPECT_EQ(option_manager_->mapper->opt_ba.use_gpu, true);
  EXPECT_EQ(option_manager_->mapper->opt_ba.gpu_index, "-1");
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_ba.thres_loss_function, 0.1);
}

// Test that AddBundleAdjusterOptions is included when AddAllOptions is called
TEST_F(OptionManagerBundleAdjusterTest_45, AddAllOptionsIncludesBundleAdjuster_45) {
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
  // Calling AddBundleAdjusterOptions again should be a no-op (already added by AddAllOptions)
  EXPECT_NO_THROW(option_manager_->AddBundleAdjusterOptions());
}

// Test that Reset followed by AddBundleAdjusterOptions works
TEST_F(OptionManagerBundleAdjusterTest_45, ResetThenAddBundleAdjusterOptions_45) {
  option_manager_->AddBundleAdjusterOptions();
  EXPECT_NO_THROW(option_manager_->Reset());
  // After reset, we should be able to add options again
  EXPECT_NO_THROW(option_manager_->AddBundleAdjusterOptions());
}

// Test that ResetOptions followed by AddBundleAdjusterOptions works
TEST_F(OptionManagerBundleAdjusterTest_45, ResetOptionsThenAddBundleAdjuster_45) {
  option_manager_->AddBundleAdjusterOptions();
  EXPECT_NO_THROW(option_manager_->ResetOptions(false));
  // After ResetOptions, the added flags should be reset, allowing re-adding
  EXPECT_NO_THROW(option_manager_->AddBundleAdjusterOptions());
}

// Test that thres_loss_function default value is correct
TEST_F(OptionManagerBundleAdjusterTest_45, ThresLossFunctionDefault_45) {
  option_manager_->AddBundleAdjusterOptions();
  EXPECT_NEAR(option_manager_->mapper->opt_ba.thres_loss_function, 0.1, 1e-9);
}

// Test that gpu_index default value is "-1"
TEST_F(OptionManagerBundleAdjusterTest_45, GpuIndexDefault_45) {
  option_manager_->AddBundleAdjusterOptions();
  EXPECT_EQ(option_manager_->mapper->opt_ba.gpu_index, "-1");
}

// Test that solver_options has a reasonable default for max_num_iterations
TEST_F(OptionManagerBundleAdjusterTest_45, SolverOptionsMaxNumIterationsDefault_45) {
  option_manager_->AddBundleAdjusterOptions();
  // max_num_iterations should be a positive number by default
  EXPECT_GT(option_manager_->mapper->opt_ba.solver_options.max_num_iterations, 0);
}

// Test with add_project_options = true
TEST(OptionManagerConstructorTest_45, ConstructWithProjectOptions_45) {
  EXPECT_NO_THROW({
    OptionManager om(true);
    om.AddBundleAdjusterOptions();
  });
}

// Test with add_project_options = false
TEST(OptionManagerConstructorTest_45, ConstructWithoutProjectOptions_45) {
  EXPECT_NO_THROW({
    OptionManager om(false);
    om.AddBundleAdjusterOptions();
  });
}

// Test that multiple different Add*Options calls don't interfere with AddBundleAdjusterOptions
TEST_F(OptionManagerBundleAdjusterTest_45, MultipleAddOptionsCalls_45) {
  EXPECT_NO_THROW(option_manager_->AddDatabaseOptions());
  EXPECT_NO_THROW(option_manager_->AddImageOptions());
  EXPECT_NO_THROW(option_manager_->AddBundleAdjusterOptions());
  EXPECT_NO_THROW(option_manager_->AddTriangulatorOptions());

  // Bundle adjuster defaults should still be intact
  EXPECT_EQ(option_manager_->mapper->opt_ba.optimize_rotations, true);
  EXPECT_EQ(option_manager_->mapper->opt_ba.optimize_translation, true);
}

// Test calling AddBundleAdjusterOptions three times to ensure idempotency
TEST_F(OptionManagerBundleAdjusterTest_45, TripleCallIdempotency_45) {
  option_manager_->AddBundleAdjusterOptions();
  option_manager_->AddBundleAdjusterOptions();
  option_manager_->AddBundleAdjusterOptions();

  // Values should remain at defaults
  EXPECT_EQ(option_manager_->mapper->opt_ba.use_gpu, true);
  EXPECT_EQ(option_manager_->mapper->opt_ba.optimize_points, true);
  EXPECT_EQ(option_manager_->mapper->opt_ba.optimize_rig_poses, false);
}

}  // namespace
}  // namespace glomap
