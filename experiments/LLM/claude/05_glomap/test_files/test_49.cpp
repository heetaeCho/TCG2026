#include <gtest/gtest.h>
#include "glomap/controllers/option_manager.h"

namespace glomap {
namespace {

class OptionManagerTest_49 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create OptionManager with add_project_options = false to avoid
    // automatically adding project options
    option_manager_ = std::make_unique<OptionManager>(false);
  }

  std::unique_ptr<OptionManager> option_manager_;
};

// Test that OptionManager can be constructed with project options enabled
TEST_F(OptionManagerTest_49, ConstructWithProjectOptions_49) {
  EXPECT_NO_THROW(OptionManager om(true));
}

// Test that OptionManager can be constructed without project options
TEST_F(OptionManagerTest_49, ConstructWithoutProjectOptions_49) {
  EXPECT_NO_THROW(OptionManager om(false));
}

// Test that shared pointers are initialized after construction
TEST_F(OptionManagerTest_49, SharedPointersInitialized_49) {
  OptionManager om(false);
  EXPECT_NE(om.database_path, nullptr);
  EXPECT_NE(om.image_path, nullptr);
  EXPECT_NE(om.mapper, nullptr);
  EXPECT_NE(om.gravity_refiner, nullptr);
}

// Test Reset does not crash and can be called multiple times
TEST_F(OptionManagerTest_49, ResetDoesNotCrash_49) {
  EXPECT_NO_THROW(option_manager_->Reset());
}

// Test Reset can be called multiple times without issues
TEST_F(OptionManagerTest_49, ResetMultipleTimes_49) {
  EXPECT_NO_THROW(option_manager_->Reset());
  EXPECT_NO_THROW(option_manager_->Reset());
  EXPECT_NO_THROW(option_manager_->Reset());
}

// Test AddAllOptions does not crash
TEST_F(OptionManagerTest_49, AddAllOptionsDoesNotCrash_49) {
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
}

// Test AddDatabaseOptions does not crash
TEST_F(OptionManagerTest_49, AddDatabaseOptionsDoesNotCrash_49) {
  EXPECT_NO_THROW(option_manager_->AddDatabaseOptions());
}

// Test AddImageOptions does not crash
TEST_F(OptionManagerTest_49, AddImageOptionsDoesNotCrash_49) {
  EXPECT_NO_THROW(option_manager_->AddImageOptions());
}

// Test AddGlobalMapperOptions does not crash
TEST_F(OptionManagerTest_49, AddGlobalMapperOptionsDoesNotCrash_49) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperOptions());
}

// Test AddGlobalMapperFullOptions does not crash
TEST_F(OptionManagerTest_49, AddGlobalMapperFullOptionsDoesNotCrash_49) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperFullOptions());
}

// Test AddGlobalMapperResumeOptions does not crash
TEST_F(OptionManagerTest_49, AddGlobalMapperResumeOptionsDoesNotCrash_49) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperResumeOptions());
}

// Test AddGlobalMapperResumeFullOptions does not crash
TEST_F(OptionManagerTest_49, AddGlobalMapperResumeFullOptionsDoesNotCrash_49) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperResumeFullOptions());
}

// Test AddViewGraphCalibrationOptions does not crash
TEST_F(OptionManagerTest_49, AddViewGraphCalibrationOptionsDoesNotCrash_49) {
  EXPECT_NO_THROW(option_manager_->AddViewGraphCalibrationOptions());
}

// Test AddRelativePoseEstimationOptions does not crash
TEST_F(OptionManagerTest_49, AddRelativePoseEstimationOptionsDoesNotCrash_49) {
  EXPECT_NO_THROW(option_manager_->AddRelativePoseEstimationOptions());
}

// Test AddRotationEstimatorOptions does not crash
TEST_F(OptionManagerTest_49, AddRotationEstimatorOptionsDoesNotCrash_49) {
  EXPECT_NO_THROW(option_manager_->AddRotationEstimatorOptions());
}

// Test AddTrackEstablishmentOptions does not crash
TEST_F(OptionManagerTest_49, AddTrackEstablishmentOptionsDoesNotCrash_49) {
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
}

// Test AddGlobalPositionerOptions does not crash
TEST_F(OptionManagerTest_49, AddGlobalPositionerOptionsDoesNotCrash_49) {
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
}

// Test AddBundleAdjusterOptions does not crash
TEST_F(OptionManagerTest_49, AddBundleAdjusterOptionsDoesNotCrash_49) {
  EXPECT_NO_THROW(option_manager_->AddBundleAdjusterOptions());
}

// Test AddTriangulatorOptions does not crash
TEST_F(OptionManagerTest_49, AddTriangulatorOptionsDoesNotCrash_49) {
  EXPECT_NO_THROW(option_manager_->AddTriangulatorOptions());
}

// Test AddInlierThresholdOptions does not crash
TEST_F(OptionManagerTest_49, AddInlierThresholdOptionsDoesNotCrash_49) {
  EXPECT_NO_THROW(option_manager_->AddInlierThresholdOptions());
}

// Test AddGravityRefinerOptions does not crash
TEST_F(OptionManagerTest_49, AddGravityRefinerOptionsDoesNotCrash_49) {
  EXPECT_NO_THROW(option_manager_->AddGravityRefinerOptions());
}

// Test calling Add*Options twice should be idempotent (guarded by added_ flags)
TEST_F(OptionManagerTest_49, AddDatabaseOptionsTwiceIsIdempotent_49) {
  EXPECT_NO_THROW(option_manager_->AddDatabaseOptions());
  EXPECT_NO_THROW(option_manager_->AddDatabaseOptions());
}

TEST_F(OptionManagerTest_49, AddImageOptionsTwiceIsIdempotent_49) {
  EXPECT_NO_THROW(option_manager_->AddImageOptions());
  EXPECT_NO_THROW(option_manager_->AddImageOptions());
}

TEST_F(OptionManagerTest_49, AddGlobalMapperOptionsTwiceIsIdempotent_49) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperOptions());
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperOptions());
}

TEST_F(OptionManagerTest_49, AddViewGraphCalibrationOptionsTwiceIsIdempotent_49) {
  EXPECT_NO_THROW(option_manager_->AddViewGraphCalibrationOptions());
  EXPECT_NO_THROW(option_manager_->AddViewGraphCalibrationOptions());
}

TEST_F(OptionManagerTest_49, AddRotationEstimatorOptionsTwiceIsIdempotent_49) {
  EXPECT_NO_THROW(option_manager_->AddRotationEstimatorOptions());
  EXPECT_NO_THROW(option_manager_->AddRotationEstimatorOptions());
}

TEST_F(OptionManagerTest_49, AddGravityRefinerOptionsTwiceIsIdempotent_49) {
  EXPECT_NO_THROW(option_manager_->AddGravityRefinerOptions());
  EXPECT_NO_THROW(option_manager_->AddGravityRefinerOptions());
}

// Test AddAllOptions then Reset allows re-adding
TEST_F(OptionManagerTest_49, AddAllOptionsThenResetThenAddAgain_49) {
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
  EXPECT_NO_THROW(option_manager_->Reset());
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
}

// Test ResetOptions with reset_paths = true
TEST_F(OptionManagerTest_49, ResetOptionsWithResetPaths_49) {
  EXPECT_NO_THROW(option_manager_->ResetOptions(true));
}

// Test ResetOptions with reset_paths = false
TEST_F(OptionManagerTest_49, ResetOptionsWithoutResetPaths_49) {
  EXPECT_NO_THROW(option_manager_->ResetOptions(false));
}

// Test AddRequiredOption with a string type
TEST_F(OptionManagerTest_49, AddRequiredOptionString_49) {
  std::string value = "test";
  EXPECT_NO_THROW(
      option_manager_->AddRequiredOption("test_option", &value, "A test option"));
}

// Test AddDefaultOption with an int type
TEST_F(OptionManagerTest_49, AddDefaultOptionInt_49) {
  int value = 42;
  EXPECT_NO_THROW(
      option_manager_->AddDefaultOption("test_int_option", &value, "An int option"));
}

// Test AddDefaultOption with a double type
TEST_F(OptionManagerTest_49, AddDefaultOptionDouble_49) {
  double value = 3.14;
  EXPECT_NO_THROW(
      option_manager_->AddDefaultOption("test_double_option", &value, "A double option"));
}

// Test AddDefaultOption with a bool type
TEST_F(OptionManagerTest_49, AddDefaultOptionBool_49) {
  bool value = true;
  EXPECT_NO_THROW(
      option_manager_->AddDefaultOption("test_bool_option", &value, "A bool option"));
}

// Test Parse with minimal arguments (just program name)
TEST_F(OptionManagerTest_49, ParseWithMinimalArgs_49) {
  char arg0[] = "test_program";
  char* argv[] = {arg0, nullptr};
  int argc = 1;
  // Parse should not crash with just the program name, assuming no required options
  EXPECT_NO_THROW(option_manager_->Parse(argc, argv));
}

// Test Parse with a registered default option
TEST_F(OptionManagerTest_49, ParseWithDefaultOption_49) {
  int value = 0;
  option_manager_->AddDefaultOption("test_val", &value, "Test value");

  char arg0[] = "test_program";
  char arg1[] = "--test_val=42";
  char* argv[] = {arg0, arg1, nullptr};
  int argc = 2;
  EXPECT_NO_THROW(option_manager_->Parse(argc, argv));
  EXPECT_EQ(value, 42);
}

// Test Parse with a registered string default option
TEST_F(OptionManagerTest_49, ParseWithStringDefaultOption_49) {
  std::string value = "default";
  option_manager_->AddDefaultOption("str_opt", &value, "String option");

  char arg0[] = "test_program";
  char arg1[] = "--str_opt=hello";
  char* argv[] = {arg0, arg1, nullptr};
  int argc = 2;
  EXPECT_NO_THROW(option_manager_->Parse(argc, argv));
  EXPECT_EQ(value, "hello");
}

// Test that shared pointers remain valid after Reset
TEST_F(OptionManagerTest_49, SharedPointersValidAfterReset_49) {
  option_manager_->Reset();
  EXPECT_NE(option_manager_->database_path, nullptr);
  EXPECT_NE(option_manager_->image_path, nullptr);
  EXPECT_NE(option_manager_->mapper, nullptr);
  EXPECT_NE(option_manager_->gravity_refiner, nullptr);
}

// Test that after adding options, then resetting, we can add the same options again
TEST_F(OptionManagerTest_49, ResetClearsAddedFlags_49) {
  option_manager_->AddGlobalMapperOptions();
  option_manager_->AddViewGraphCalibrationOptions();
  option_manager_->AddRelativePoseEstimationOptions();
  option_manager_->AddRotationEstimatorOptions();
  option_manager_->AddTrackEstablishmentOptions();
  option_manager_->AddGlobalPositionerOptions();
  option_manager_->AddBundleAdjusterOptions();
  option_manager_->AddTriangulatorOptions();
  option_manager_->AddInlierThresholdOptions();

  option_manager_->Reset();

  // After reset, adding should work again without issues
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperOptions());
  EXPECT_NO_THROW(option_manager_->AddViewGraphCalibrationOptions());
  EXPECT_NO_THROW(option_manager_->AddRelativePoseEstimationOptions());
  EXPECT_NO_THROW(option_manager_->AddRotationEstimatorOptions());
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
  EXPECT_NO_THROW(option_manager_->AddBundleAdjusterOptions());
  EXPECT_NO_THROW(option_manager_->AddTriangulatorOptions());
  EXPECT_NO_THROW(option_manager_->AddInlierThresholdOptions());
}

// Test Parse with a double option
TEST_F(OptionManagerTest_49, ParseWithDoubleOption_49) {
  double value = 0.0;
  option_manager_->AddDefaultOption("dbl_opt", &value, "Double option");

  char arg0[] = "test_program";
  char arg1[] = "--dbl_opt=2.718";
  char* argv[] = {arg0, arg1, nullptr};
  int argc = 2;
  EXPECT_NO_THROW(option_manager_->Parse(argc, argv));
  EXPECT_DOUBLE_EQ(value, 2.718);
}

// Test AddGlobalMapperFullOptions after Reset
TEST_F(OptionManagerTest_49, AddGlobalMapperFullOptionsAfterReset_49) {
  option_manager_->AddGlobalMapperFullOptions();
  option_manager_->Reset();
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperFullOptions());
}

// Test AddGlobalMapperResumeFullOptions after Reset
TEST_F(OptionManagerTest_49, AddGlobalMapperResumeFullOptionsAfterReset_49) {
  option_manager_->AddGlobalMapperResumeFullOptions();
  option_manager_->Reset();
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperResumeFullOptions());
}

}  // namespace
}  // namespace glomap
