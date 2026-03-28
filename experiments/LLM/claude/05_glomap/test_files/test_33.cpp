#include <gtest/gtest.h>
#include "glomap/controllers/option_manager.h"

namespace glomap {
namespace {

class OptionManagerTest_33 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test construction with add_project_options = true
TEST_F(OptionManagerTest_33, ConstructWithProjectOptions_33) {
  EXPECT_NO_THROW(OptionManager om(true));
}

// Test construction with add_project_options = false
TEST_F(OptionManagerTest_33, ConstructWithoutProjectOptions_33) {
  EXPECT_NO_THROW(OptionManager om(false));
}

// Test that shared_ptr members are initialized after construction
TEST_F(OptionManagerTest_33, SharedPtrsInitialized_33) {
  OptionManager om(false);
  EXPECT_NE(om.database_path, nullptr);
  EXPECT_NE(om.image_path, nullptr);
  EXPECT_NE(om.mapper, nullptr);
}

// Test AddAllOptions does not throw
TEST_F(OptionManagerTest_33, AddAllOptionsNoThrow_33) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddAllOptions());
}

// Test AddAllOptions called twice does not throw (idempotent guards)
TEST_F(OptionManagerTest_33, AddAllOptionsTwiceNoThrow_33) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddAllOptions());
  EXPECT_NO_THROW(om.AddAllOptions());
}

// Test AddDatabaseOptions does not throw
TEST_F(OptionManagerTest_33, AddDatabaseOptionsNoThrow_33) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddDatabaseOptions());
}

// Test AddDatabaseOptions called twice (idempotent)
TEST_F(OptionManagerTest_33, AddDatabaseOptionsTwice_33) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddDatabaseOptions());
  EXPECT_NO_THROW(om.AddDatabaseOptions());
}

// Test AddImageOptions does not throw
TEST_F(OptionManagerTest_33, AddImageOptionsNoThrow_33) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddImageOptions());
}

// Test AddImageOptions called twice (idempotent)
TEST_F(OptionManagerTest_33, AddImageOptionsTwice_33) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddImageOptions());
  EXPECT_NO_THROW(om.AddImageOptions());
}

// Test AddGlobalMapperOptions does not throw
TEST_F(OptionManagerTest_33, AddGlobalMapperOptionsNoThrow_33) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddGlobalMapperOptions());
}

// Test AddGlobalMapperFullOptions does not throw
TEST_F(OptionManagerTest_33, AddGlobalMapperFullOptionsNoThrow_33) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddGlobalMapperFullOptions());
}

// Test AddGlobalMapperResumeOptions does not throw
TEST_F(OptionManagerTest_33, AddGlobalMapperResumeOptionsNoThrow_33) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddGlobalMapperResumeOptions());
}

// Test AddGlobalMapperResumeFullOptions does not throw
TEST_F(OptionManagerTest_33, AddGlobalMapperResumeFullOptionsNoThrow_33) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddGlobalMapperResumeFullOptions());
}

// Test AddViewGraphCalibrationOptions does not throw
TEST_F(OptionManagerTest_33, AddViewGraphCalibrationOptionsNoThrow_33) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddViewGraphCalibrationOptions());
}

// Test AddRelativePoseEstimationOptions does not throw
TEST_F(OptionManagerTest_33, AddRelativePoseEstimationOptionsNoThrow_33) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddRelativePoseEstimationOptions());
}

// Test AddRotationEstimatorOptions does not throw
TEST_F(OptionManagerTest_33, AddRotationEstimatorOptionsNoThrow_33) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddRotationEstimatorOptions());
}

// Test AddTrackEstablishmentOptions does not throw
TEST_F(OptionManagerTest_33, AddTrackEstablishmentOptionsNoThrow_33) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddTrackEstablishmentOptions());
}

// Test AddGlobalPositionerOptions does not throw
TEST_F(OptionManagerTest_33, AddGlobalPositionerOptionsNoThrow_33) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddGlobalPositionerOptions());
}

// Test AddBundleAdjusterOptions does not throw
TEST_F(OptionManagerTest_33, AddBundleAdjusterOptionsNoThrow_33) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddBundleAdjusterOptions());
}

// Test AddTriangulatorOptions does not throw
TEST_F(OptionManagerTest_33, AddTriangulatorOptionsNoThrow_33) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddTriangulatorOptions());
}

// Test AddInlierThresholdOptions does not throw
TEST_F(OptionManagerTest_33, AddInlierThresholdOptionsNoThrow_33) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddInlierThresholdOptions());
}

// Test AddGravityRefinerOptions does not throw
TEST_F(OptionManagerTest_33, AddGravityRefinerOptionsNoThrow_33) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddGravityRefinerOptions());
}

// Test gravity_refiner shared_ptr is initialized
TEST_F(OptionManagerTest_33, GravityRefinerInitialized_33) {
  OptionManager om(false);
  EXPECT_NE(om.gravity_refiner, nullptr);
}

// Test Reset does not throw
TEST_F(OptionManagerTest_33, ResetNoThrow_33) {
  OptionManager om(false);
  om.AddAllOptions();
  EXPECT_NO_THROW(om.Reset());
}

// Test ResetOptions with reset_paths = true
TEST_F(OptionManagerTest_33, ResetOptionsWithPaths_33) {
  OptionManager om(false);
  om.AddAllOptions();
  EXPECT_NO_THROW(om.ResetOptions(true));
}

// Test ResetOptions with reset_paths = false
TEST_F(OptionManagerTest_33, ResetOptionsWithoutPaths_33) {
  OptionManager om(false);
  om.AddAllOptions();
  EXPECT_NO_THROW(om.ResetOptions(false));
}

// Test Reset then AddAllOptions again
TEST_F(OptionManagerTest_33, ResetThenAddAllOptions_33) {
  OptionManager om(false);
  om.AddAllOptions();
  om.Reset();
  EXPECT_NO_THROW(om.AddAllOptions());
}

// Test AddRequiredOption with a string option
TEST_F(OptionManagerTest_33, AddRequiredOptionString_33) {
  OptionManager om(false);
  std::string value = "test";
  EXPECT_NO_THROW(om.AddRequiredOption("test_option", &value, "A test option"));
}

// Test AddDefaultOption with an int option
TEST_F(OptionManagerTest_33, AddDefaultOptionInt_33) {
  OptionManager om(false);
  int value = 42;
  EXPECT_NO_THROW(om.AddDefaultOption("test_int", &value, "A test int option"));
}

// Test AddDefaultOption with a double option
TEST_F(OptionManagerTest_33, AddDefaultOptionDouble_33) {
  OptionManager om(false);
  double value = 3.14;
  EXPECT_NO_THROW(om.AddDefaultOption("test_double", &value, "A test double option"));
}

// Test AddDefaultOption with a bool option
TEST_F(OptionManagerTest_33, AddDefaultOptionBool_33) {
  OptionManager om(false);
  bool value = true;
  EXPECT_NO_THROW(om.AddDefaultOption("test_bool", &value, "A test bool option"));
}

// Test Parse with help flag (should not crash)
TEST_F(OptionManagerTest_33, ParseWithHelpFlag_33) {
  OptionManager om(false);
  om.AddAllOptions();
  const char* argv[] = {"program", "--help"};
  int argc = 2;
  // Parse with --help may throw or exit; we just verify it's callable
  // This might call exit, so we skip actually calling it in automated tests
  // Instead, test parse with no arguments
  const char* argv_empty[] = {"program"};
  int argc_empty = 1;
  EXPECT_NO_THROW(om.Parse(argc_empty, const_cast<char**>(argv_empty)));
}

// Test Parse with no additional arguments
TEST_F(OptionManagerTest_33, ParseNoArgs_33) {
  OptionManager om(false);
  om.AddDatabaseOptions();
  om.AddImageOptions();
  const char* argv[] = {"program"};
  int argc = 1;
  EXPECT_NO_THROW(om.Parse(argc, const_cast<char**>(argv)));
}

// Test that database_path and image_path are empty strings initially
TEST_F(OptionManagerTest_33, DefaultPathsAreEmpty_33) {
  OptionManager om(false);
  EXPECT_TRUE(om.database_path->empty());
  EXPECT_TRUE(om.image_path->empty());
}

// Test adding individual options then AddAllOptions
TEST_F(OptionManagerTest_33, AddIndividualThenAll_33) {
  OptionManager om(false);
  om.AddDatabaseOptions();
  om.AddImageOptions();
  // AddAllOptions should handle already-added options gracefully
  EXPECT_NO_THROW(om.AddAllOptions());
}

// Test adding all individual add methods one by one
TEST_F(OptionManagerTest_33, AddAllIndividualOptions_33) {
  OptionManager om(false);
  EXPECT_NO_THROW(om.AddDatabaseOptions());
  EXPECT_NO_THROW(om.AddImageOptions());
  EXPECT_NO_THROW(om.AddGlobalMapperOptions());
  EXPECT_NO_THROW(om.AddViewGraphCalibrationOptions());
  EXPECT_NO_THROW(om.AddRelativePoseEstimationOptions());
  EXPECT_NO_THROW(om.AddRotationEstimatorOptions());
  EXPECT_NO_THROW(om.AddTrackEstablishmentOptions());
  EXPECT_NO_THROW(om.AddGlobalPositionerOptions());
  EXPECT_NO_THROW(om.AddBundleAdjusterOptions());
  EXPECT_NO_THROW(om.AddTriangulatorOptions());
  EXPECT_NO_THROW(om.AddInlierThresholdOptions());
  EXPECT_NO_THROW(om.AddGravityRefinerOptions());
}

// Test Parse with a database path argument
TEST_F(OptionManagerTest_33, ParseDatabasePath_33) {
  OptionManager om(false);
  om.AddDatabaseOptions();
  const char* argv[] = {"program", "--database_path", "/tmp/test.db"};
  int argc = 3;
  EXPECT_NO_THROW(om.Parse(argc, const_cast<char**>(argv)));
  EXPECT_EQ(*om.database_path, "/tmp/test.db");
}

// Test Parse with an image path argument
TEST_F(OptionManagerTest_33, ParseImagePath_33) {
  OptionManager om(false);
  om.AddImageOptions();
  const char* argv[] = {"program", "--image_path", "/tmp/images"};
  int argc = 3;
  EXPECT_NO_THROW(om.Parse(argc, const_cast<char**>(argv)));
  EXPECT_EQ(*om.image_path, "/tmp/images");
}

// Test ResetOptions with reset_paths=true resets paths
TEST_F(OptionManagerTest_33, ResetOptionsResetsPathsWhenTrue_33) {
  OptionManager om(false);
  om.AddDatabaseOptions();
  om.AddImageOptions();
  const char* argv[] = {"program", "--database_path", "/tmp/test.db", "--image_path", "/tmp/images"};
  int argc = 5;
  om.Parse(argc, const_cast<char**>(argv));
  EXPECT_EQ(*om.database_path, "/tmp/test.db");
  om.ResetOptions(true);
  EXPECT_TRUE(om.database_path->empty());
  EXPECT_TRUE(om.image_path->empty());
}

// Test ResetOptions with reset_paths=false preserves paths
TEST_F(OptionManagerTest_33, ResetOptionsPreservesPathsWhenFalse_33) {
  OptionManager om(false);
  om.AddDatabaseOptions();
  om.AddImageOptions();
  const char* argv[] = {"program", "--database_path", "/tmp/test.db", "--image_path", "/tmp/images"};
  int argc = 5;
  om.Parse(argc, const_cast<char**>(argv));
  om.ResetOptions(false);
  EXPECT_EQ(*om.database_path, "/tmp/test.db");
  EXPECT_EQ(*om.image_path, "/tmp/images");
}

// Test constructing with project options true
TEST_F(OptionManagerTest_33, ConstructWithProjectOptionsTrue_33) {
  OptionManager om(true);
  EXPECT_NE(om.database_path, nullptr);
  EXPECT_NE(om.image_path, nullptr);
  EXPECT_NE(om.mapper, nullptr);
}

// Test AddDefaultOption with a string
TEST_F(OptionManagerTest_33, AddDefaultOptionString_33) {
  OptionManager om(false);
  std::string value = "default_value";
  EXPECT_NO_THROW(om.AddDefaultOption("my_string_opt", &value, "string help"));
}

// Test AddRequiredOption with an int
TEST_F(OptionManagerTest_33, AddRequiredOptionInt_33) {
  OptionManager om(false);
  int value = 10;
  EXPECT_NO_THROW(om.AddRequiredOption("my_int_opt", &value, "int help"));
}

}  // namespace
}  // namespace glomap
