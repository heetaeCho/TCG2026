#include <gtest/gtest.h>
#include "glomap/controllers/option_manager.h"

namespace glomap {
namespace {

class OptionManagerTest_35 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create OptionManager without project options to keep things simple
    option_manager_ = std::make_unique<OptionManager>(false);
  }

  std::unique_ptr<OptionManager> option_manager_;
};

// Test that OptionManager can be constructed with add_project_options = false
TEST_F(OptionManagerTest_35, ConstructWithoutProjectOptions_35) {
  EXPECT_NO_THROW(OptionManager om(false));
}

// Test that OptionManager can be constructed with add_project_options = true
TEST_F(OptionManagerTest_35, ConstructWithProjectOptions_35) {
  EXPECT_NO_THROW(OptionManager om(true));
}

// Test that shared pointers are initialized after construction
TEST_F(OptionManagerTest_35, SharedPointersInitialized_35) {
  EXPECT_NE(option_manager_->database_path, nullptr);
  EXPECT_NE(option_manager_->image_path, nullptr);
  EXPECT_NE(option_manager_->mapper, nullptr);
}

// Test AddDatabaseOptions can be called without error
TEST_F(OptionManagerTest_35, AddDatabaseOptions_35) {
  EXPECT_NO_THROW(option_manager_->AddDatabaseOptions());
}

// Test AddImageOptions can be called without error
TEST_F(OptionManagerTest_35, AddImageOptions_35) {
  EXPECT_NO_THROW(option_manager_->AddImageOptions());
}

// Test AddImageOptions is idempotent (calling twice should not crash)
TEST_F(OptionManagerTest_35, AddImageOptionsIdempotent_35) {
  EXPECT_NO_THROW(option_manager_->AddImageOptions());
  EXPECT_NO_THROW(option_manager_->AddImageOptions());
}

// Test AddDatabaseOptions is idempotent
TEST_F(OptionManagerTest_35, AddDatabaseOptionsIdempotent_35) {
  EXPECT_NO_THROW(option_manager_->AddDatabaseOptions());
  EXPECT_NO_THROW(option_manager_->AddDatabaseOptions());
}

// Test AddGlobalMapperOptions can be called
TEST_F(OptionManagerTest_35, AddGlobalMapperOptions_35) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperOptions());
}

// Test AddGlobalMapperOptions is idempotent
TEST_F(OptionManagerTest_35, AddGlobalMapperOptionsIdempotent_35) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperOptions());
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperOptions());
}

// Test AddGlobalMapperFullOptions
TEST_F(OptionManagerTest_35, AddGlobalMapperFullOptions_35) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperFullOptions());
}

// Test AddGlobalMapperResumeOptions
TEST_F(OptionManagerTest_35, AddGlobalMapperResumeOptions_35) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperResumeOptions());
}

// Test AddGlobalMapperResumeFullOptions
TEST_F(OptionManagerTest_35, AddGlobalMapperResumeFullOptions_35) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperResumeFullOptions());
}

// Test AddViewGraphCalibrationOptions
TEST_F(OptionManagerTest_35, AddViewGraphCalibrationOptions_35) {
  EXPECT_NO_THROW(option_manager_->AddViewGraphCalibrationOptions());
}

// Test AddRelativePoseEstimationOptions
TEST_F(OptionManagerTest_35, AddRelativePoseEstimationOptions_35) {
  EXPECT_NO_THROW(option_manager_->AddRelativePoseEstimationOptions());
}

// Test AddRotationEstimatorOptions
TEST_F(OptionManagerTest_35, AddRotationEstimatorOptions_35) {
  EXPECT_NO_THROW(option_manager_->AddRotationEstimatorOptions());
}

// Test AddTrackEstablishmentOptions
TEST_F(OptionManagerTest_35, AddTrackEstablishmentOptions_35) {
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
}

// Test AddGlobalPositionerOptions
TEST_F(OptionManagerTest_35, AddGlobalPositionerOptions_35) {
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
}

// Test AddBundleAdjusterOptions
TEST_F(OptionManagerTest_35, AddBundleAdjusterOptions_35) {
  EXPECT_NO_THROW(option_manager_->AddBundleAdjusterOptions());
}

// Test AddTriangulatorOptions
TEST_F(OptionManagerTest_35, AddTriangulatorOptions_35) {
  EXPECT_NO_THROW(option_manager_->AddTriangulatorOptions());
}

// Test AddInlierThresholdOptions
TEST_F(OptionManagerTest_35, AddInlierThresholdOptions_35) {
  EXPECT_NO_THROW(option_manager_->AddInlierThresholdOptions());
}

// Test AddGravityRefinerOptions
TEST_F(OptionManagerTest_35, AddGravityRefinerOptions_35) {
  EXPECT_NO_THROW(option_manager_->AddGravityRefinerOptions());
}

// Test AddGravityRefinerOptions is idempotent
TEST_F(OptionManagerTest_35, AddGravityRefinerOptionsIdempotent_35) {
  EXPECT_NO_THROW(option_manager_->AddGravityRefinerOptions());
  EXPECT_NO_THROW(option_manager_->AddGravityRefinerOptions());
}

// Test AddAllOptions adds all options without error
TEST_F(OptionManagerTest_35, AddAllOptions_35) {
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
}

// Test AddAllOptions is idempotent
TEST_F(OptionManagerTest_35, AddAllOptionsIdempotent_35) {
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
}

// Test Reset can be called
TEST_F(OptionManagerTest_35, Reset_35) {
  option_manager_->AddAllOptions();
  EXPECT_NO_THROW(option_manager_->Reset());
}

// Test ResetOptions with reset_paths = true
TEST_F(OptionManagerTest_35, ResetOptionsWithPaths_35) {
  option_manager_->AddAllOptions();
  EXPECT_NO_THROW(option_manager_->ResetOptions(true));
}

// Test ResetOptions with reset_paths = false
TEST_F(OptionManagerTest_35, ResetOptionsWithoutPaths_35) {
  option_manager_->AddAllOptions();
  EXPECT_NO_THROW(option_manager_->ResetOptions(false));
}

// Test that after Reset, options can be re-added
TEST_F(OptionManagerTest_35, ResetThenReAdd_35) {
  option_manager_->AddAllOptions();
  option_manager_->Reset();
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
}

// Test that gravity_refiner shared pointer is valid
TEST_F(OptionManagerTest_35, GravityRefinerInitialized_35) {
  EXPECT_NE(option_manager_->gravity_refiner, nullptr);
}

// Test Parse with minimal arguments (just program name)
TEST_F(OptionManagerTest_35, ParseMinimalArgs_35) {
  // No required options added, so parsing with just program name should work
  char arg0[] = "test_program";
  char* argv[] = {arg0};
  int argc = 1;
  EXPECT_NO_THROW(option_manager_->Parse(argc, argv));
}

// Test AddRequiredOption with a string option
TEST_F(OptionManagerTest_35, AddRequiredOptionString_35) {
  std::string my_option;
  EXPECT_NO_THROW(
      option_manager_->AddRequiredOption("my_option", &my_option, "A test option"));
}

// Test AddDefaultOption with a string option
TEST_F(OptionManagerTest_35, AddDefaultOptionString_35) {
  std::string my_option = "default_val";
  EXPECT_NO_THROW(
      option_manager_->AddDefaultOption("my_default_option", &my_option, "A default test option"));
}

// Test AddRequiredOption with an int option
TEST_F(OptionManagerTest_35, AddRequiredOptionInt_35) {
  int my_int = 0;
  EXPECT_NO_THROW(
      option_manager_->AddRequiredOption("my_int_option", &my_int, "An int option"));
}

// Test AddDefaultOption with an int option
TEST_F(OptionManagerTest_35, AddDefaultOptionInt_35) {
  int my_int = 42;
  EXPECT_NO_THROW(
      option_manager_->AddDefaultOption("my_default_int", &my_int, "A default int option"));
}

// Test AddDefaultOption with a double option
TEST_F(OptionManagerTest_35, AddDefaultOptionDouble_35) {
  double my_double = 3.14;
  EXPECT_NO_THROW(
      option_manager_->AddDefaultOption("my_default_double", &my_double, "A default double option"));
}

// Test AddDefaultOption with a bool option
TEST_F(OptionManagerTest_35, AddDefaultOptionBool_35) {
  bool my_bool = true;
  EXPECT_NO_THROW(
      option_manager_->AddDefaultOption("my_default_bool", &my_bool, "A default bool option"));
}

// Test Parse with database_path argument after adding database options
TEST_F(OptionManagerTest_35, ParseWithDatabasePath_35) {
  option_manager_->AddDatabaseOptions();
  char arg0[] = "test_program";
  char arg1[] = "--database_path";
  char arg2[] = "/tmp/test.db";
  char* argv[] = {arg0, arg1, arg2};
  int argc = 3;
  EXPECT_NO_THROW(option_manager_->Parse(argc, argv));
  EXPECT_EQ(*option_manager_->database_path, "/tmp/test.db");
}

// Test Parse with image_path argument after adding image options
TEST_F(OptionManagerTest_35, ParseWithImagePath_35) {
  option_manager_->AddImageOptions();
  char arg0[] = "test_program";
  char arg1[] = "--image_path";
  char arg2[] = "/tmp/images";
  char* argv[] = {arg0, arg1, arg2};
  int argc = 3;
  EXPECT_NO_THROW(option_manager_->Parse(argc, argv));
  EXPECT_EQ(*option_manager_->image_path, "/tmp/images");
}

// Test that adding individual options after AddAllOptions doesn't crash
TEST_F(OptionManagerTest_35, AddIndividualAfterAll_35) {
  option_manager_->AddAllOptions();
  EXPECT_NO_THROW(option_manager_->AddDatabaseOptions());
  EXPECT_NO_THROW(option_manager_->AddImageOptions());
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperOptions());
}

// Test calling all Add*Options in sequence
TEST_F(OptionManagerTest_35, AddAllOptionsSequentially_35) {
  EXPECT_NO_THROW(option_manager_->AddDatabaseOptions());
  EXPECT_NO_THROW(option_manager_->AddImageOptions());
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperOptions());
  EXPECT_NO_THROW(option_manager_->AddViewGraphCalibrationOptions());
  EXPECT_NO_THROW(option_manager_->AddRelativePoseEstimationOptions());
  EXPECT_NO_THROW(option_manager_->AddRotationEstimatorOptions());
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
  EXPECT_NO_THROW(option_manager_->AddBundleAdjusterOptions());
  EXPECT_NO_THROW(option_manager_->AddTriangulatorOptions());
  EXPECT_NO_THROW(option_manager_->AddInlierThresholdOptions());
  EXPECT_NO_THROW(option_manager_->AddGravityRefinerOptions());
}

// Test ResetOptions preserves paths when reset_paths is false
TEST_F(OptionManagerTest_35, ResetOptionsPreservesPaths_35) {
  option_manager_->AddDatabaseOptions();
  option_manager_->AddImageOptions();

  char arg0[] = "test_program";
  char arg1[] = "--database_path";
  char arg2[] = "/tmp/test.db";
  char arg3[] = "--image_path";
  char arg4[] = "/tmp/images";
  char* argv[] = {arg0, arg1, arg2, arg3, arg4};
  int argc = 5;
  option_manager_->Parse(argc, argv);

  option_manager_->ResetOptions(false);

  // Paths should be preserved when reset_paths is false
  EXPECT_EQ(*option_manager_->database_path, "/tmp/test.db");
  EXPECT_EQ(*option_manager_->image_path, "/tmp/images");
}

// Test ResetOptions resets paths when reset_paths is true
TEST_F(OptionManagerTest_35, ResetOptionsClearsPaths_35) {
  option_manager_->AddDatabaseOptions();
  option_manager_->AddImageOptions();

  char arg0[] = "test_program";
  char arg1[] = "--database_path";
  char arg2[] = "/tmp/test.db";
  char arg3[] = "--image_path";
  char arg4[] = "/tmp/images";
  char* argv[] = {arg0, arg1, arg2, arg3, arg4};
  int argc = 5;
  option_manager_->Parse(argc, argv);

  option_manager_->ResetOptions(true);

  // Paths should be reset when reset_paths is true
  EXPECT_TRUE(option_manager_->database_path->empty());
  EXPECT_TRUE(option_manager_->image_path->empty());
}

}  // namespace
}  // namespace glomap
