#include <gtest/gtest.h>
#include "glomap/controllers/option_manager.h"

namespace glomap {
namespace {

class OptionManagerTest_39 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test construction with project options
TEST_F(OptionManagerTest_39, ConstructWithProjectOptions_39) {
  EXPECT_NO_THROW(OptionManager manager(true));
}

// Test construction without project options
TEST_F(OptionManagerTest_39, ConstructWithoutProjectOptions_39) {
  EXPECT_NO_THROW(OptionManager manager(false));
}

// Test that shared pointers are initialized after construction
TEST_F(OptionManagerTest_39, SharedPointersInitialized_39) {
  OptionManager manager(true);
  EXPECT_NE(manager.database_path, nullptr);
  EXPECT_NE(manager.image_path, nullptr);
  EXPECT_NE(manager.mapper, nullptr);
}

// Test AddAllOptions does not throw
TEST_F(OptionManagerTest_39, AddAllOptionsNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddAllOptions());
}

// Test AddDatabaseOptions does not throw
TEST_F(OptionManagerTest_39, AddDatabaseOptionsNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddDatabaseOptions());
}

// Test AddImageOptions does not throw
TEST_F(OptionManagerTest_39, AddImageOptionsNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddImageOptions());
}

// Test AddGlobalMapperOptions does not throw
TEST_F(OptionManagerTest_39, AddGlobalMapperOptionsNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddGlobalMapperOptions());
}

// Test AddGlobalMapperFullOptions does not throw
TEST_F(OptionManagerTest_39, AddGlobalMapperFullOptionsNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddGlobalMapperFullOptions());
}

// Test AddGlobalMapperResumeOptions does not throw
TEST_F(OptionManagerTest_39, AddGlobalMapperResumeOptionsNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddGlobalMapperResumeOptions());
}

// Test AddGlobalMapperResumeFullOptions does not throw
TEST_F(OptionManagerTest_39, AddGlobalMapperResumeFullOptionsNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddGlobalMapperResumeFullOptions());
}

// Test AddViewGraphCalibrationOptions does not throw
TEST_F(OptionManagerTest_39, AddViewGraphCalibrationOptionsNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddViewGraphCalibrationOptions());
}

// Test AddRelativePoseEstimationOptions does not throw
TEST_F(OptionManagerTest_39, AddRelativePoseEstimationOptionsNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddRelativePoseEstimationOptions());
}

// Test AddRotationEstimatorOptions does not throw
TEST_F(OptionManagerTest_39, AddRotationEstimatorOptionsNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddRotationEstimatorOptions());
}

// Test AddTrackEstablishmentOptions does not throw
TEST_F(OptionManagerTest_39, AddTrackEstablishmentOptionsNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddTrackEstablishmentOptions());
}

// Test AddGlobalPositionerOptions does not throw
TEST_F(OptionManagerTest_39, AddGlobalPositionerOptionsNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddGlobalPositionerOptions());
}

// Test AddBundleAdjusterOptions does not throw
TEST_F(OptionManagerTest_39, AddBundleAdjusterOptionsNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddBundleAdjusterOptions());
}

// Test AddTriangulatorOptions does not throw
TEST_F(OptionManagerTest_39, AddTriangulatorOptionsNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddTriangulatorOptions());
}

// Test AddInlierThresholdOptions does not throw
TEST_F(OptionManagerTest_39, AddInlierThresholdOptionsNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddInlierThresholdOptions());
}

// Test AddGravityRefinerOptions does not throw
TEST_F(OptionManagerTest_39, AddGravityRefinerOptionsNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddGravityRefinerOptions());
}

// Test that calling the same Add method twice does not throw (idempotency)
TEST_F(OptionManagerTest_39, AddDatabaseOptionsTwiceNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddDatabaseOptions());
  EXPECT_NO_THROW(manager.AddDatabaseOptions());
}

TEST_F(OptionManagerTest_39, AddImageOptionsTwiceNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddImageOptions());
  EXPECT_NO_THROW(manager.AddImageOptions());
}

TEST_F(OptionManagerTest_39, AddGlobalMapperOptionsTwiceNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddGlobalMapperOptions());
  EXPECT_NO_THROW(manager.AddGlobalMapperOptions());
}

TEST_F(OptionManagerTest_39, AddViewGraphCalibrationOptionsTwiceNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddViewGraphCalibrationOptions());
  EXPECT_NO_THROW(manager.AddViewGraphCalibrationOptions());
}

TEST_F(OptionManagerTest_39, AddRelativePoseEstimationOptionsTwiceNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddRelativePoseEstimationOptions());
  EXPECT_NO_THROW(manager.AddRelativePoseEstimationOptions());
}

TEST_F(OptionManagerTest_39, AddRotationEstimatorOptionsTwiceNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddRotationEstimatorOptions());
  EXPECT_NO_THROW(manager.AddRotationEstimatorOptions());
}

TEST_F(OptionManagerTest_39, AddTrackEstablishmentOptionsTwiceNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddTrackEstablishmentOptions());
  EXPECT_NO_THROW(manager.AddTrackEstablishmentOptions());
}

TEST_F(OptionManagerTest_39, AddGlobalPositionerOptionsTwiceNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddGlobalPositionerOptions());
  EXPECT_NO_THROW(manager.AddGlobalPositionerOptions());
}

TEST_F(OptionManagerTest_39, AddBundleAdjusterOptionsTwiceNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddBundleAdjusterOptions());
  EXPECT_NO_THROW(manager.AddBundleAdjusterOptions());
}

TEST_F(OptionManagerTest_39, AddTriangulatorOptionsTwiceNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddTriangulatorOptions());
  EXPECT_NO_THROW(manager.AddTriangulatorOptions());
}

TEST_F(OptionManagerTest_39, AddInlierThresholdOptionsTwiceNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddInlierThresholdOptions());
  EXPECT_NO_THROW(manager.AddInlierThresholdOptions());
}

TEST_F(OptionManagerTest_39, AddGravityRefinerOptionsTwiceNoThrow_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddGravityRefinerOptions());
  EXPECT_NO_THROW(manager.AddGravityRefinerOptions());
}

// Test Reset does not throw
TEST_F(OptionManagerTest_39, ResetNoThrow_39) {
  OptionManager manager(false);
  manager.AddAllOptions();
  EXPECT_NO_THROW(manager.Reset());
}

// Test ResetOptions with reset_paths true
TEST_F(OptionManagerTest_39, ResetOptionsWithPaths_39) {
  OptionManager manager(true);
  manager.AddAllOptions();
  EXPECT_NO_THROW(manager.ResetOptions(true));
}

// Test ResetOptions with reset_paths false
TEST_F(OptionManagerTest_39, ResetOptionsWithoutPaths_39) {
  OptionManager manager(true);
  manager.AddAllOptions();
  EXPECT_NO_THROW(manager.ResetOptions(false));
}

// Test that shared pointers remain valid after Reset
TEST_F(OptionManagerTest_39, SharedPointersValidAfterReset_39) {
  OptionManager manager(true);
  manager.AddAllOptions();
  manager.Reset();
  EXPECT_NE(manager.database_path, nullptr);
  EXPECT_NE(manager.image_path, nullptr);
  EXPECT_NE(manager.mapper, nullptr);
}

// Test AddRequiredOption with a string type
TEST_F(OptionManagerTest_39, AddRequiredOptionString_39) {
  OptionManager manager(false);
  std::string value;
  EXPECT_NO_THROW(
      manager.AddRequiredOption("test_string_option", &value, "A test option"));
}

// Test AddDefaultOption with an int type
TEST_F(OptionManagerTest_39, AddDefaultOptionInt_39) {
  OptionManager manager(false);
  int value = 42;
  EXPECT_NO_THROW(
      manager.AddDefaultOption("test_int_option", &value, "A test int option"));
}

// Test AddDefaultOption with a double type
TEST_F(OptionManagerTest_39, AddDefaultOptionDouble_39) {
  OptionManager manager(false);
  double value = 3.14;
  EXPECT_NO_THROW(manager.AddDefaultOption("test_double_option", &value,
                                            "A test double option"));
}

// Test AddDefaultOption with a bool type
TEST_F(OptionManagerTest_39, AddDefaultOptionBool_39) {
  OptionManager manager(false);
  bool value = true;
  EXPECT_NO_THROW(manager.AddDefaultOption("test_bool_option", &value,
                                            "A test bool option"));
}

// Test Parse with minimal arguments (just program name)
TEST_F(OptionManagerTest_39, ParseMinimalArgs_39) {
  OptionManager manager(false);
  const char* argv[] = {"test_program"};
  int argc = 1;
  EXPECT_NO_THROW(manager.Parse(argc, const_cast<char**>(argv)));
}

// Test that AddAllOptions then calling individual Add methods again is idempotent
TEST_F(OptionManagerTest_39, AddAllThenIndividualIdempotent_39) {
  OptionManager manager(false);
  EXPECT_NO_THROW(manager.AddAllOptions());
  EXPECT_NO_THROW(manager.AddDatabaseOptions());
  EXPECT_NO_THROW(manager.AddImageOptions());
  EXPECT_NO_THROW(manager.AddGlobalMapperOptions());
  EXPECT_NO_THROW(manager.AddGlobalMapperFullOptions());
  EXPECT_NO_THROW(manager.AddGlobalMapperResumeFullOptions());
  EXPECT_NO_THROW(manager.AddViewGraphCalibrationOptions());
  EXPECT_NO_THROW(manager.AddRelativePoseEstimationOptions());
  EXPECT_NO_THROW(manager.AddRotationEstimatorOptions());
  EXPECT_NO_THROW(manager.AddTrackEstablishmentOptions());
  EXPECT_NO_THROW(manager.AddGlobalPositionerOptions());
  EXPECT_NO_THROW(manager.AddBundleAdjusterOptions());
  EXPECT_NO_THROW(manager.AddTriangulatorOptions());
  EXPECT_NO_THROW(manager.AddInlierThresholdOptions());
  EXPECT_NO_THROW(manager.AddGravityRefinerOptions());
}

// Test that gravity_refiner shared pointer is initialized
TEST_F(OptionManagerTest_39, GravityRefinerInitialized_39) {
  OptionManager manager(false);
  EXPECT_NE(manager.gravity_refiner, nullptr);
}

// Test ResetOptions then re-add options
TEST_F(OptionManagerTest_39, ResetOptionsThenReAdd_39) {
  OptionManager manager(false);
  manager.AddAllOptions();
  manager.ResetOptions(true);
  EXPECT_NO_THROW(manager.AddAllOptions());
}

// Test that database_path and image_path are empty strings by default with project options
TEST_F(OptionManagerTest_39, DefaultPathsEmpty_39) {
  OptionManager manager(true);
  EXPECT_NE(manager.database_path, nullptr);
  EXPECT_NE(manager.image_path, nullptr);
  // Paths should be empty or have some default; just check they're accessible
  EXPECT_NO_THROW({ std::string db = *manager.database_path; });
  EXPECT_NO_THROW({ std::string img = *manager.image_path; });
}

// Test AddGlobalMapperResumeFullOptions includes sub-options
// (calling it should not throw and should be callable after individual sub-options)
TEST_F(OptionManagerTest_39, AddGlobalMapperResumeFullOptionsAfterSubOptions_39) {
  OptionManager manager(false);
  manager.AddGlobalMapperResumeOptions();
  manager.AddGlobalPositionerOptions();
  manager.AddBundleAdjusterOptions();
  manager.AddTriangulatorOptions();
  manager.AddInlierThresholdOptions();
  // Calling the composite should still work (idempotent)
  EXPECT_NO_THROW(manager.AddGlobalMapperResumeFullOptions());
}

// Test Parse with a database path argument
TEST_F(OptionManagerTest_39, ParseWithDatabasePath_39) {
  OptionManager manager(false);
  manager.AddDatabaseOptions();
  const char* argv[] = {"test_program", "--database_path", "/tmp/test.db"};
  int argc = 3;
  EXPECT_NO_THROW(manager.Parse(argc, const_cast<char**>(argv)));
  EXPECT_EQ(*manager.database_path, "/tmp/test.db");
}

// Test Parse with an image path argument
TEST_F(OptionManagerTest_39, ParseWithImagePath_39) {
  OptionManager manager(false);
  manager.AddImageOptions();
  const char* argv[] = {"test_program", "--image_path", "/tmp/images"};
  int argc = 3;
  EXPECT_NO_THROW(manager.Parse(argc, const_cast<char**>(argv)));
  EXPECT_EQ(*manager.image_path, "/tmp/images");
}

// Test Reset and then verify we can add and parse again
TEST_F(OptionManagerTest_39, ResetAndReuse_39) {
  OptionManager manager(false);
  manager.AddDatabaseOptions();
  const char* argv1[] = {"test_program", "--database_path", "/tmp/test1.db"};
  manager.Parse(3, const_cast<char**>(argv1));
  EXPECT_EQ(*manager.database_path, "/tmp/test1.db");

  manager.Reset();
  manager.AddDatabaseOptions();
  const char* argv2[] = {"test_program", "--database_path", "/tmp/test2.db"};
  manager.Parse(3, const_cast<char**>(argv2));
  EXPECT_EQ(*manager.database_path, "/tmp/test2.db");
}

}  // namespace
}  // namespace glomap
