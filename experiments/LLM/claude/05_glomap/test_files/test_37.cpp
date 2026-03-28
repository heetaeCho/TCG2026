#include <gtest/gtest.h>
#include "glomap/controllers/option_manager.h"

namespace glomap {
namespace {

class OptionManagerTest_37 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test construction with project options
TEST_F(OptionManagerTest_37, ConstructWithProjectOptions_37) {
  EXPECT_NO_THROW(OptionManager manager(true));
}

// Test construction without project options
TEST_F(OptionManagerTest_37, ConstructWithoutProjectOptions_37) {
  EXPECT_NO_THROW(OptionManager manager(false));
}

// Test that shared pointers are initialized after construction
TEST_F(OptionManagerTest_37, SharedPointersInitialized_37) {
  OptionManager manager(true);
  EXPECT_NE(manager.mapper, nullptr);
  EXPECT_NE(manager.database_path, nullptr);
  EXPECT_NE(manager.image_path, nullptr);
}

// Test AddDatabaseOptions does not throw
TEST_F(OptionManagerTest_37, AddDatabaseOptions_37) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddDatabaseOptions());
}

// Test AddImageOptions does not throw
TEST_F(OptionManagerTest_37, AddImageOptions_37) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddImageOptions());
}

// Test AddGlobalMapperOptions does not throw
TEST_F(OptionManagerTest_37, AddGlobalMapperOptions_37) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddGlobalMapperOptions());
}

// Test AddGlobalMapperFullOptions does not throw
TEST_F(OptionManagerTest_37, AddGlobalMapperFullOptions_37) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddGlobalMapperFullOptions());
}

// Test AddGlobalMapperResumeOptions does not throw
TEST_F(OptionManagerTest_37, AddGlobalMapperResumeOptions_37) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddGlobalMapperResumeOptions());
}

// Test AddGlobalMapperResumeFullOptions does not throw
TEST_F(OptionManagerTest_37, AddGlobalMapperResumeFullOptions_37) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddGlobalMapperResumeFullOptions());
}

// Test AddViewGraphCalibrationOptions does not throw
TEST_F(OptionManagerTest_37, AddViewGraphCalibrationOptions_37) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddViewGraphCalibrationOptions());
}

// Test AddRelativePoseEstimationOptions does not throw
TEST_F(OptionManagerTest_37, AddRelativePoseEstimationOptions_37) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddRelativePoseEstimationOptions());
}

// Test AddRotationEstimatorOptions does not throw
TEST_F(OptionManagerTest_37, AddRotationEstimatorOptions_37) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddRotationEstimatorOptions());
}

// Test AddTrackEstablishmentOptions does not throw
TEST_F(OptionManagerTest_37, AddTrackEstablishmentOptions_37) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddTrackEstablishmentOptions());
}

// Test AddGlobalPositionerOptions does not throw
TEST_F(OptionManagerTest_37, AddGlobalPositionerOptions_37) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddGlobalPositionerOptions());
}

// Test AddBundleAdjusterOptions does not throw
TEST_F(OptionManagerTest_37, AddBundleAdjusterOptions_37) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddBundleAdjusterOptions());
}

// Test AddTriangulatorOptions does not throw
TEST_F(OptionManagerTest_37, AddTriangulatorOptions_37) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddTriangulatorOptions());
}

// Test AddInlierThresholdOptions does not throw
TEST_F(OptionManagerTest_37, AddInlierThresholdOptions_37) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddInlierThresholdOptions());
}

// Test AddGravityRefinerOptions does not throw
TEST_F(OptionManagerTest_37, AddGravityRefinerOptions_37) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddGravityRefinerOptions());
}

// Test AddAllOptions does not throw
TEST_F(OptionManagerTest_37, AddAllOptions_37) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddAllOptions());
}

// Test calling the same Add method twice (idempotency)
TEST_F(OptionManagerTest_37, AddDatabaseOptionsTwice_37) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddDatabaseOptions());
  EXPECT_NO_THROW(manager.AddDatabaseOptions());
}

// Test calling AddImageOptions twice (idempotency)
TEST_F(OptionManagerTest_37, AddImageOptionsTwice_37) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddImageOptions());
  EXPECT_NO_THROW(manager.AddImageOptions());
}

// Test calling AddGlobalMapperOptions twice (idempotency)
TEST_F(OptionManagerTest_37, AddGlobalMapperOptionsTwice_37) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddGlobalMapperOptions());
  EXPECT_NO_THROW(manager.AddGlobalMapperOptions());
}

// Test calling AddGlobalMapperFullOptions twice (idempotency)
TEST_F(OptionManagerTest_37, AddGlobalMapperFullOptionsTwice_37) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddGlobalMapperFullOptions());
  EXPECT_NO_THROW(manager.AddGlobalMapperFullOptions());
}

// Test Reset does not throw
TEST_F(OptionManagerTest_37, Reset_37) {
  OptionManager manager(false);
  manager.AddAllOptions();
  EXPECT_NO_THROW(manager.Reset());
}

// Test ResetOptions with reset_paths=true
TEST_F(OptionManagerTest_37, ResetOptionsWithPaths_37) {
  OptionManager manager(false);
  manager.AddAllOptions();
  EXPECT_NO_THROW(manager.ResetOptions(true));
}

// Test ResetOptions with reset_paths=false
TEST_F(OptionManagerTest_37, ResetOptionsWithoutPaths_37) {
  OptionManager manager(false);
  manager.AddAllOptions();
  EXPECT_NO_THROW(manager.ResetOptions(false));
}

// Test Reset then re-add options
TEST_F(OptionManagerTest_37, ResetThenReaddOptions_37) {
  OptionManager manager(false);
  manager.AddAllOptions();
  manager.Reset();
  EXPECT_NO_THROW(manager.AddAllOptions());
}

// Test AddRequiredOption with a string option
TEST_F(OptionManagerTest_37, AddRequiredOptionString_37) {
  OptionManager manager(false);
  std::string value = "test";
  EXPECT_NO_THROW(
      manager.AddRequiredOption("test_option", &value, "A test option"));
}

// Test AddDefaultOption with an int option
TEST_F(OptionManagerTest_37, AddDefaultOptionInt_37) {
  OptionManager manager(false);
  int value = 42;
  EXPECT_NO_THROW(
      manager.AddDefaultOption("test_int_option", &value, "An int option"));
}

// Test AddDefaultOption with a double option
TEST_F(OptionManagerTest_37, AddDefaultOptionDouble_37) {
  OptionManager manager(false);
  double value = 3.14;
  EXPECT_NO_THROW(
      manager.AddDefaultOption("test_double_option", &value, "A double option"));
}

// Test AddDefaultOption with a bool option
TEST_F(OptionManagerTest_37, AddDefaultOptionBool_37) {
  OptionManager manager(false);
  bool value = true;
  EXPECT_NO_THROW(
      manager.AddDefaultOption("test_bool_option", &value, "A bool option"));
}

// Test that gravity_refiner pointer is initialized
TEST_F(OptionManagerTest_37, GravityRefinerInitialized_37) {
  OptionManager manager(true);
  EXPECT_NE(manager.gravity_refiner, nullptr);
}

// Test Parse with minimal arguments (just program name)
TEST_F(OptionManagerTest_37, ParseMinimalArgs_37) {
  OptionManager manager(false);
  // No required options added, so parse should succeed with just prog name
  char arg0[] = "test_program";
  char* argv[] = {arg0};
  int argc = 1;
  EXPECT_NO_THROW(manager.Parse(argc, argv));
}

// Test AddAllOptions followed by Reset followed by AddAllOptions
TEST_F(OptionManagerTest_37, AddAllResetAddAll_37) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddAllOptions());
  EXPECT_NO_THROW(manager.Reset());
  EXPECT_NO_THROW(manager.AddAllOptions());
}

// Test that after construction with project options, database_path is empty
TEST_F(OptionManagerTest_37, DatabasePathInitiallyEmpty_37) {
  OptionManager manager(true);
  EXPECT_NE(manager.database_path, nullptr);
  EXPECT_TRUE(manager.database_path->empty());
}

// Test that after construction with project options, image_path is empty
TEST_F(OptionManagerTest_37, ImagePathInitiallyEmpty_37) {
  OptionManager manager(true);
  EXPECT_NE(manager.image_path, nullptr);
  EXPECT_TRUE(manager.image_path->empty());
}

// Test AddGlobalMapperFullOptions includes sub-options (no crash after adding all sub-options)
TEST_F(OptionManagerTest_37, AddGlobalMapperFullOptionsIncludesSubOptions_37) {
  OptionManager manager(false);
  // AddGlobalMapperFullOptions internally calls multiple Add methods.
  // After calling it, calling individual adds should be idempotent (no crash).
  manager.AddGlobalMapperFullOptions();
  EXPECT_NO_THROW(manager.AddGlobalMapperOptions());
  EXPECT_NO_THROW(manager.AddViewGraphCalibrationOptions());
  EXPECT_NO_THROW(manager.AddRelativePoseEstimationOptions());
  EXPECT_NO_THROW(manager.AddRotationEstimatorOptions());
  EXPECT_NO_THROW(manager.AddTrackEstablishmentOptions());
  EXPECT_NO_THROW(manager.AddGlobalPositionerOptions());
  EXPECT_NO_THROW(manager.AddBundleAdjusterOptions());
  EXPECT_NO_THROW(manager.AddTriangulatorOptions());
  EXPECT_NO_THROW(manager.AddInlierThresholdOptions());
}

// Test that AddGravityRefinerOptions can be called after AddAllOptions
TEST_F(OptionManagerTest_37, AddGravityRefinerAfterAll_37) {
  OptionManager manager(false);
  manager.AddAllOptions();
  // Gravity refiner might or might not be included in AddAllOptions
  EXPECT_NO_THROW(manager.AddGravityRefinerOptions());
}

// Test ResetOptions preserves paths when reset_paths is false
TEST_F(OptionManagerTest_37, ResetOptionsPreservesPaths_37) {
  OptionManager manager(true);
  manager.AddDatabaseOptions();
  manager.AddImageOptions();
  *manager.database_path = "/some/path/db";
  *manager.image_path = "/some/path/images";
  manager.ResetOptions(false);
  EXPECT_EQ(*manager.database_path, "/some/path/db");
  EXPECT_EQ(*manager.image_path, "/some/path/images");
}

// Test ResetOptions resets paths when reset_paths is true
TEST_F(OptionManagerTest_37, ResetOptionsResetsPaths_37) {
  OptionManager manager(true);
  manager.AddDatabaseOptions();
  manager.AddImageOptions();
  *manager.database_path = "/some/path/db";
  *manager.image_path = "/some/path/images";
  manager.ResetOptions(true);
  EXPECT_TRUE(manager.database_path->empty());
  EXPECT_TRUE(manager.image_path->empty());
}

}  // namespace
}  // namespace glomap
