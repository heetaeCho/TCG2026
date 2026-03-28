#include <gtest/gtest.h>

#include "glomap/controllers/option_manager.h"
#include "glomap/controllers/global_mapper.h"
#include "glomap/estimators/relpose_estimation.h"

namespace {

class OptionManagerTest_41 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Construct OptionManager without automatically adding project options.
    option_manager_ =
        std::make_unique<glomap::OptionManager>(/*add_project_options=*/false);

    // Ensure mapper is a valid shared_ptr so that AddRelativePoseEstimationOptions
    // can safely access mapper->opt_relpose...
    mapper_ = std::make_shared<glomap::GlobalMapperOptions>();
    option_manager_->mapper = mapper_;
  }

  std::unique_ptr<glomap::OptionManager> option_manager_;
  std::shared_ptr<glomap::GlobalMapperOptions> mapper_;
};

// Normal operation: After registering relative pose estimation options,
// parsing the corresponding command-line flag should update the underlying
// max_epipolar_error value.
TEST_F(OptionManagerTest_41, ParsesMaxEpipolarErrorOption_41) {
  ASSERT_NE(option_manager_->mapper, nullptr);

  // Set an initial value to verify it is changed by Parse.
  mapper_->opt_relpose.ransac_options.max_epipolar_error = 1.0;

  // Register the relative pose estimation option.
  option_manager_->AddRelativePoseEstimationOptions();

  // Prepare command-line arguments that set the option.
  int argc = 2;
  char arg0[] = "program";
  char arg1[] = "--RelPoseEstimation.max_epipolar_error=0.5";
  char* argv[] = {arg0, arg1};

  // Parse should succeed and update the underlying option.
  option_manager_->Parse(argc, argv);

  EXPECT_DOUBLE_EQ(
      mapper_->opt_relpose.ransac_options.max_epipolar_error, 0.5);
}

// Boundary / idempotency behavior: Calling AddRelativePoseEstimationOptions
// multiple times should be safe (no exceptions) and still allow parsing the
// option from the command line.
TEST_F(OptionManagerTest_41, MultipleCallsAreSafeAndParseStillWorks_41) {
  ASSERT_NE(option_manager_->mapper, nullptr);

  // Set a distinct initial value.
  mapper_->opt_relpose.ransac_options.max_epipolar_error = 2.0;

  // Call AddRelativePoseEstimationOptions multiple times; the method
  // is expected to be idempotent from the caller's perspective.
  option_manager_->AddRelativePoseEstimationOptions();
  option_manager_->AddRelativePoseEstimationOptions();

  int argc = 2;
  char arg0[] = "program";
  char arg1[] = "--RelPoseEstimation.max_epipolar_error=3.5";
  char* argv[] = {arg0, arg1};

  // Parsing after multiple registrations should not throw.
  EXPECT_NO_THROW(option_manager_->Parse(argc, argv));

  // The parsed value should be reflected in the underlying option.
  EXPECT_DOUBLE_EQ(
      mapper_->opt_relpose.ransac_options.max_epipolar_error, 3.5);
}

}  // namespace
