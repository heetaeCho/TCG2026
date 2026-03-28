#include <gtest/gtest.h>
#include "glomap/controllers/option_manager.h"

namespace glomap {
namespace {

class OptionManagerTest_42 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create OptionManager with add_project_options = false to avoid
    // automatically adding project options
  }
};

// Test: Construction with project options enabled
TEST_F(OptionManagerTest_42, ConstructWithProjectOptions_42) {
  EXPECT_NO_THROW(OptionManager om(true));
}

// Test: Construction without project options
TEST_F(OptionManagerTest_42, ConstructWithoutProjectOptions_42) {
  EXPECT_NO_THROW(OptionManager om(false));
}

// Test: Shared pointers are initialized after construction
TEST_F(OptionManagerTest_42, SharedPointersInitialized_42) {
  OptionManager om(false);
  EXPECT_NE(om.database_path, nullptr);
  EXPECT_NE(om.image_path, nullptr);
  EXPECT_NE(om.mapper, nullptr);
}

// Test: AddDatabaseOptions does not throw
TEST_F(OptionManagerTest_42, AddDatabaseOptions_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddDatabaseOptions());
}

// Test: AddDatabaseOptions called twice (idempotent)
TEST_F(OptionManagerTest_42, AddDatabaseOptionsIdempotent_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddDatabaseOptions());
  EXPECT_NO_THROW(om.AddDatabaseOptions());
}

// Test: AddImageOptions does not throw
TEST_F(OptionManagerTest_42, AddImageOptions_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddImageOptions());
}

// Test: AddImageOptions called twice (idempotent)
TEST_F(OptionManagerTest_42, AddImageOptionsIdempotent_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddImageOptions());
  EXPECT_NO_THROW(om.AddImageOptions());
}

// Test: AddGlobalMapperOptions does not throw
TEST_F(OptionManagerTest_42, AddGlobalMapperOptions_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddGlobalMapperOptions());
}

// Test: AddGlobalMapperOptions called twice (idempotent)
TEST_F(OptionManagerTest_42, AddGlobalMapperOptionsIdempotent_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddGlobalMapperOptions());
  EXPECT_NO_THROW(om.AddGlobalMapperOptions());
}

// Test: AddGlobalMapperFullOptions does not throw
TEST_F(OptionManagerTest_42, AddGlobalMapperFullOptions_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddGlobalMapperFullOptions());
}

// Test: AddGlobalMapperResumeOptions does not throw
TEST_F(OptionManagerTest_42, AddGlobalMapperResumeOptions_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddGlobalMapperResumeOptions());
}

// Test: AddGlobalMapperResumeFullOptions does not throw
TEST_F(OptionManagerTest_42, AddGlobalMapperResumeFullOptions_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddGlobalMapperResumeFullOptions());
}

// Test: AddViewGraphCalibrationOptions does not throw
TEST_F(OptionManagerTest_42, AddViewGraphCalibrationOptions_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddViewGraphCalibrationOptions());
}

// Test: AddViewGraphCalibrationOptions called twice (idempotent)
TEST_F(OptionManagerTest_42, AddViewGraphCalibrationOptionsIdempotent_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddViewGraphCalibrationOptions());
  EXPECT_NO_THROW(om.AddViewGraphCalibrationOptions());
}

// Test: AddRelativePoseEstimationOptions does not throw
TEST_F(OptionManagerTest_42, AddRelativePoseEstimationOptions_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddRelativePoseEstimationOptions());
}

// Test: AddRelativePoseEstimationOptions called twice (idempotent)
TEST_F(OptionManagerTest_42, AddRelativePoseEstimationOptionsIdempotent_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddRelativePoseEstimationOptions());
  EXPECT_NO_THROW(om.AddRelativePoseEstimationOptions());
}

// Test: AddRotationEstimatorOptions does not throw
TEST_F(OptionManagerTest_42, AddRotationEstimatorOptions_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddRotationEstimatorOptions());
}

// Test: AddRotationEstimatorOptions called twice (idempotent - early return)
TEST_F(OptionManagerTest_42, AddRotationEstimatorOptionsIdempotent_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddRotationEstimatorOptions());
  EXPECT_NO_THROW(om.AddRotationEstimatorOptions());
}

// Test: AddTrackEstablishmentOptions does not throw
TEST_F(OptionManagerTest_42, AddTrackEstablishmentOptions_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddTrackEstablishmentOptions());
}

// Test: AddTrackEstablishmentOptions called twice (idempotent)
TEST_F(OptionManagerTest_42, AddTrackEstablishmentOptionsIdempotent_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddTrackEstablishmentOptions());
  EXPECT_NO_THROW(om.AddTrackEstablishmentOptions());
}

// Test: AddGlobalPositionerOptions does not throw
TEST_F(OptionManagerTest_42, AddGlobalPositionerOptions_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddGlobalPositionerOptions());
}

// Test: AddGlobalPositionerOptions called twice (idempotent)
TEST_F(OptionManagerTest_42, AddGlobalPositionerOptionsIdempotent_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddGlobalPositionerOptions());
  EXPECT_NO_THROW(om.AddGlobalPositionerOptions());
}

// Test: AddBundleAdjusterOptions does not throw
TEST_F(OptionManagerTest_42, AddBundleAdjusterOptions_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddBundleAdjusterOptions());
}

// Test: AddBundleAdjusterOptions called twice (idempotent)
TEST_F(OptionManagerTest_42, AddBundleAdjusterOptionsIdempotent_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddBundleAdjusterOptions());
  EXPECT_NO_THROW(om.AddBundleAdjusterOptions());
}

// Test: AddTriangulatorOptions does not throw
TEST_F(OptionManagerTest_42, AddTriangulatorOptions_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddTriangulatorOptions());
}

// Test: AddTriangulatorOptions called twice (idempotent)
TEST_F(OptionManagerTest_42, AddTriangulatorOptionsIdempotent_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddTriangulatorOptions());
  EXPECT_NO_THROW(om.AddTriangulatorOptions());
}

// Test: AddInlierThresholdOptions does not throw
TEST_F(OptionManagerTest_42, AddInlierThresholdOptions_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddInlierThresholdOptions());
}

// Test: AddInlierThresholdOptions called twice (idempotent)
TEST_F(OptionManagerTest_42, AddInlierThresholdOptionsIdempotent_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddInlierThresholdOptions());
  EXPECT_NO_THROW(om.AddInlierThresholdOptions());
}

// Test: AddGravityRefinerOptions does not throw
TEST_F(OptionManagerTest_42, AddGravityRefinerOptions_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddGravityRefinerOptions());
}

// Test: AddGravityRefinerOptions called twice (idempotent)
TEST_F(OptionManagerTest_42, AddGravityRefinerOptionsIdempotent_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddGravityRefinerOptions());
  EXPECT_NO_THROW(om.AddGravityRefinerOptions());
}

// Test: AddAllOptions does not throw
TEST_F(OptionManagerTest_42, AddAllOptions_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddAllOptions());
}

// Test: AddAllOptions called twice (all sub-options idempotent)
TEST_F(OptionManagerTest_42, AddAllOptionsIdempotent_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddAllOptions());
  EXPECT_NO_THROW(om.AddAllOptions());
}

// Test: Reset does not throw
TEST_F(OptionManagerTest_42, Reset_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.Reset());
}

// Test: Reset after adding options
TEST_F(OptionManagerTest_42, ResetAfterAddingOptions_42) {
  OptionManager om(false);
  om.AddAllOptions();
  EXPECT_NO_THROW(om.Reset());
}

// Test: ResetOptions with reset_paths = true
TEST_F(OptionManagerTest_42, ResetOptionsWithPaths_42) {
  OptionManager om(false);
  om.AddAllOptions();
  EXPECT_NO_THROW(om.ResetOptions(true));
}

// Test: ResetOptions with reset_paths = false
TEST_F(OptionManagerTest_42, ResetOptionsWithoutPaths_42) {
  OptionManager om(false);
  om.AddAllOptions();
  EXPECT_NO_THROW(om.ResetOptions(false));
}

// Test: After Reset, options can be re-added
TEST_F(OptionManagerTest_42, ReAddOptionsAfterReset_42) {
  OptionManager om(false);
  om.AddRotationEstimatorOptions();
  om.Reset();
  // After reset, should be able to add again (flag should be cleared)
  EXPECT_NO_THROW(om.AddRotationEstimatorOptions());
}

// Test: After ResetOptions, all individual options can be re-added
TEST_F(OptionManagerTest_42, ReAddAllOptionsAfterResetOptions_42) {
  OptionManager om(false);
  om.AddAllOptions();
  om.ResetOptions(true);
  EXPECT_NO_THROW(om.AddAllOptions());
}

// Test: AddRequiredOption for string type
TEST_F(OptionManagerTest_42, AddRequiredOptionString_42) {
  OptionManager om(false);
  std::string value = "test";
  EXPECT_NO_THROW(om.AddRequiredOption("test_option", &value, "A test option"));
}

// Test: AddDefaultOption for int type
TEST_F(OptionManagerTest_42, AddDefaultOptionInt_42) {
  OptionManager om(false);
  int value = 42;
  EXPECT_NO_THROW(om.AddDefaultOption("test_int_option", &value, "An int option"));
}

// Test: AddDefaultOption for double type
TEST_F(OptionManagerTest_42, AddDefaultOptionDouble_42) {
  OptionManager om(false);
  double value = 3.14;
  EXPECT_NO_THROW(om.AddDefaultOption("test_double_option", &value, "A double option"));
}

// Test: AddDefaultOption for bool type
TEST_F(OptionManagerTest_42, AddDefaultOptionBool_42) {
  OptionManager om(false);
  bool value = true;
  EXPECT_NO_THROW(om.AddDefaultOption("test_bool_option", &value, "A bool option"));
}

// Test: Parse with no arguments (just program name)
TEST_F(OptionManagerTest_42, ParseNoArguments_42) {
  OptionManager om(false);
  char arg0[] = "test_program";
  char* argv[] = {arg0};
  int argc = 1;
  EXPECT_NO_THROW(om.Parse(argc, argv));
}

// Test: Parse with database path option
TEST_F(OptionManagerTest_42, ParseWithDatabasePath_42) {
  OptionManager om(false);
  om.AddDatabaseOptions();
  char arg0[] = "test_program";
  char arg1[] = "--database_path";
  char arg2[] = "/tmp/test.db";
  char* argv[] = {arg0, arg1, arg2};
  int argc = 3;
  EXPECT_NO_THROW(om.Parse(argc, argv));
  EXPECT_EQ(*om.database_path, "/tmp/test.db");
}

// Test: Parse with image path option
TEST_F(OptionManagerTest_42, ParseWithImagePath_42) {
  OptionManager om(false);
  om.AddImageOptions();
  char arg0[] = "test_program";
  char arg1[] = "--image_path";
  char arg2[] = "/tmp/images";
  char* argv[] = {arg0, arg1, arg2};
  int argc = 3;
  EXPECT_NO_THROW(om.Parse(argc, argv));
  EXPECT_EQ(*om.image_path, "/tmp/images");
}

// Test: gravity_refiner shared pointer is initialized
TEST_F(OptionManagerTest_42, GravityRefinerInitialized_42) {
  OptionManager om(false);
  EXPECT_NE(om.gravity_refiner, nullptr);
}

// Test: AddGlobalMapperFullOptions adds all required sub-options
TEST_F(OptionManagerTest_42, AddGlobalMapperFullOptionsThenIdempotent_42) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddGlobalMapperFullOptions());
  // Calling individual sub-options should be idempotent (already added)
  EXPECT_NO_THROW(om.AddGlobalMapperOptions());
  EXPECT_NO_THROW(om.AddViewGraphCalibrationOptions());
  EXPECT_NO_THROW(om.AddRelativePoseEstimationOptions());
  EXPECT_NO_THROW(om.AddRotationEstimatorOptions());
  EXPECT_NO_THROW(om.AddTrackEstablishmentOptions());
  EXPECT_NO_THROW(om.AddGlobalPositionerOptions());
  EXPECT_NO_THROW(om.AddBundleAdjusterOptions());
  EXPECT_NO_THROW(om.AddTriangulatorOptions());
  EXPECT_NO_THROW(om.AddInlierThresholdOptions());
}

// Test: AddRequiredOption for string, then parse
TEST_F(OptionManagerTest_42, AddRequiredOptionAndParse_42) {
  OptionManager om(false);
  std::string value;
  om.AddRequiredOption("custom_option", &value, "Custom required option");
  char arg0[] = "test_program";
  char arg1[] = "--custom_option";
  char arg2[] = "hello_world";
  char* argv[] = {arg0, arg1, arg2};
  int argc = 3;
  EXPECT_NO_THROW(om.Parse(argc, argv));
  EXPECT_EQ(value, "hello_world");
}

// Test: AddDefaultOption for int, then parse with default
TEST_F(OptionManagerTest_42, AddDefaultOptionIntKeepsDefault_42) {
  OptionManager om(false);
  int value = 99;
  om.AddDefaultOption("my_int", &value, "An integer option");
  char arg0[] = "test_program";
  char* argv[] = {arg0};
  int argc = 1;
  EXPECT_NO_THROW(om.Parse(argc, argv));
  EXPECT_EQ(value, 99);
}

// Test: AddDefaultOption for int, then parse with override
TEST_F(OptionManagerTest_42, AddDefaultOptionIntOverride_42) {
  OptionManager om(false);
  int value = 99;
  om.AddDefaultOption("my_int", &value, "An integer option");
  char arg0[] = "test_program";
  char arg1[] = "--my_int";
  char arg2[] = "42";
  char* argv[] = {arg0, arg1, arg2};
  int argc = 3;
  EXPECT_NO_THROW(om.Parse(argc, argv));
  EXPECT_EQ(value, 42);
}

}  // namespace
}  // namespace glomap
