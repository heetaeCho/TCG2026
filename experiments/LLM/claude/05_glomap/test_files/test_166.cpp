#include <gtest/gtest.h>
#include "glomap/controllers/option_manager.h"

namespace glomap {
namespace {

class OptionManagerTest_166 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test basic construction with add_project_options = true
TEST_F(OptionManagerTest_166, ConstructWithProjectOptions_166) {
  OptionManager manager(true);
  EXPECT_NE(manager.database_path, nullptr);
  EXPECT_NE(manager.image_path, nullptr);
  EXPECT_NE(manager.mapper, nullptr);
  EXPECT_NE(manager.gravity_refiner, nullptr);
}

// Test basic construction with add_project_options = false
TEST_F(OptionManagerTest_166, ConstructWithoutProjectOptions_166) {
  OptionManager manager(false);
  EXPECT_NE(manager.database_path, nullptr);
  EXPECT_NE(manager.image_path, nullptr);
  EXPECT_NE(manager.mapper, nullptr);
  EXPECT_NE(manager.gravity_refiner, nullptr);
}

// Test that shared pointers are initialized to empty strings
TEST_F(OptionManagerTest_166, DefaultPathsAreEmpty_166) {
  OptionManager manager(false);
  EXPECT_TRUE(manager.database_path->empty());
  EXPECT_TRUE(manager.image_path->empty());
}

// Test Reset
TEST_F(OptionManagerTest_166, ResetResetsState_166) {
  OptionManager manager(false);
  *manager.database_path = "/some/path";
  manager.Reset();
  // After reset, shared pointers should still be valid
  EXPECT_NE(manager.database_path, nullptr);
  EXPECT_NE(manager.image_path, nullptr);
  EXPECT_NE(manager.mapper, nullptr);
  EXPECT_NE(manager.gravity_refiner, nullptr);
}

// Test ResetOptions with reset_paths = true
TEST_F(OptionManagerTest_166, ResetOptionsWithResetPaths_166) {
  OptionManager manager(false);
  *manager.database_path = "/some/db/path";
  *manager.image_path = "/some/image/path";
  manager.ResetOptions(true);
  EXPECT_NE(manager.database_path, nullptr);
  EXPECT_NE(manager.image_path, nullptr);
}

// Test ResetOptions with reset_paths = false
TEST_F(OptionManagerTest_166, ResetOptionsWithoutResetPaths_166) {
  OptionManager manager(false);
  *manager.database_path = "/some/db/path";
  *manager.image_path = "/some/image/path";
  manager.ResetOptions(false);
  EXPECT_NE(manager.database_path, nullptr);
  EXPECT_NE(manager.image_path, nullptr);
}

// Test AddDatabaseOptions does not crash
TEST_F(OptionManagerTest_166, AddDatabaseOptions_166) {
  OptionManager manager(false);
  EXPECT_NO_FATAL_FAILURE(manager.AddDatabaseOptions());
}

// Test AddImageOptions does not crash
TEST_F(OptionManagerTest_166, AddImageOptions_166) {
  OptionManager manager(false);
  EXPECT_NO_FATAL_FAILURE(manager.AddImageOptions());
}

// Test AddGlobalMapperOptions does not crash
TEST_F(OptionManagerTest_166, AddGlobalMapperOptions_166) {
  OptionManager manager(false);
  EXPECT_NO_FATAL_FAILURE(manager.AddGlobalMapperOptions());
}

// Test AddGlobalMapperFullOptions does not crash
TEST_F(OptionManagerTest_166, AddGlobalMapperFullOptions_166) {
  OptionManager manager(false);
  EXPECT_NO_FATAL_FAILURE(manager.AddGlobalMapperFullOptions());
}

// Test AddGlobalMapperResumeOptions does not crash
TEST_F(OptionManagerTest_166, AddGlobalMapperResumeOptions_166) {
  OptionManager manager(false);
  EXPECT_NO_FATAL_FAILURE(manager.AddGlobalMapperResumeOptions());
}

// Test AddGlobalMapperResumeFullOptions does not crash
TEST_F(OptionManagerTest_166, AddGlobalMapperResumeFullOptions_166) {
  OptionManager manager(false);
  EXPECT_NO_FATAL_FAILURE(manager.AddGlobalMapperResumeFullOptions());
}

// Test AddViewGraphCalibrationOptions does not crash
TEST_F(OptionManagerTest_166, AddViewGraphCalibrationOptions_166) {
  OptionManager manager(false);
  EXPECT_NO_FATAL_FAILURE(manager.AddViewGraphCalibrationOptions());
}

// Test AddRelativePoseEstimationOptions does not crash
TEST_F(OptionManagerTest_166, AddRelativePoseEstimationOptions_166) {
  OptionManager manager(false);
  EXPECT_NO_FATAL_FAILURE(manager.AddRelativePoseEstimationOptions());
}

// Test AddRotationEstimatorOptions does not crash
TEST_F(OptionManagerTest_166, AddRotationEstimatorOptions_166) {
  OptionManager manager(false);
  EXPECT_NO_FATAL_FAILURE(manager.AddRotationEstimatorOptions());
}

// Test AddTrackEstablishmentOptions does not crash
TEST_F(OptionManagerTest_166, AddTrackEstablishmentOptions_166) {
  OptionManager manager(false);
  EXPECT_NO_FATAL_FAILURE(manager.AddTrackEstablishmentOptions());
}

// Test AddGlobalPositionerOptions does not crash
TEST_F(OptionManagerTest_166, AddGlobalPositionerOptions_166) {
  OptionManager manager(false);
  EXPECT_NO_FATAL_FAILURE(manager.AddGlobalPositionerOptions());
}

// Test AddBundleAdjusterOptions does not crash
TEST_F(OptionManagerTest_166, AddBundleAdjusterOptions_166) {
  OptionManager manager(false);
  EXPECT_NO_FATAL_FAILURE(manager.AddBundleAdjusterOptions());
}

// Test AddTriangulatorOptions does not crash
TEST_F(OptionManagerTest_166, AddTriangulatorOptions_166) {
  OptionManager manager(false);
  EXPECT_NO_FATAL_FAILURE(manager.AddTriangulatorOptions());
}

// Test AddInlierThresholdOptions does not crash
TEST_F(OptionManagerTest_166, AddInlierThresholdOptions_166) {
  OptionManager manager(false);
  EXPECT_NO_FATAL_FAILURE(manager.AddInlierThresholdOptions());
}

// Test AddGravityRefinerOptions does not crash
TEST_F(OptionManagerTest_166, AddGravityRefinerOptions_166) {
  OptionManager manager(false);
  EXPECT_NO_FATAL_FAILURE(manager.AddGravityRefinerOptions());
}

// Test AddAllOptions does not crash
TEST_F(OptionManagerTest_166, AddAllOptions_166) {
  OptionManager manager(false);
  EXPECT_NO_FATAL_FAILURE(manager.AddAllOptions());
}

// Test calling AddDatabaseOptions twice should not crash (idempotent guard)
TEST_F(OptionManagerTest_166, AddDatabaseOptionsTwice_166) {
  OptionManager manager(false);
  EXPECT_NO_FATAL_FAILURE(manager.AddDatabaseOptions());
  // Second call: the internal guard (added_database_options_) should prevent duplicate add
  EXPECT_NO_FATAL_FAILURE(manager.AddDatabaseOptions());
}

// Test calling AddImageOptions twice
TEST_F(OptionManagerTest_166, AddImageOptionsTwice_166) {
  OptionManager manager(false);
  EXPECT_NO_FATAL_FAILURE(manager.AddImageOptions());
  EXPECT_NO_FATAL_FAILURE(manager.AddImageOptions());
}

// Test Parse with help flag
TEST_F(OptionManagerTest_166, ParseWithHelpFlag_166) {
  OptionManager manager(false);
  manager.AddDatabaseOptions();
  manager.AddImageOptions();
  // Parse with --help should trigger help (may call exit, so we just test basic args)
  // We test with no arguments to ensure it doesn't crash
  const char* argv[] = {"test_program"};
  EXPECT_NO_FATAL_FAILURE(manager.Parse(1, const_cast<char**>(argv)));
}

// Test AddRequiredOption with a string option
TEST_F(OptionManagerTest_166, AddRequiredOptionString_166) {
  OptionManager manager(false);
  std::string my_option = "default_value";
  EXPECT_NO_FATAL_FAILURE(
      manager.AddRequiredOption("my_string_opt", &my_option, "A string option"));
}

// Test AddDefaultOption with an int option
TEST_F(OptionManagerTest_166, AddDefaultOptionInt_166) {
  OptionManager manager(false);
  int my_int = 42;
  EXPECT_NO_FATAL_FAILURE(
      manager.AddDefaultOption("my_int_opt", &my_int, "An int option"));
}

// Test AddDefaultOption with a double option
TEST_F(OptionManagerTest_166, AddDefaultOptionDouble_166) {
  OptionManager manager(false);
  double my_double = 3.14;
  EXPECT_NO_FATAL_FAILURE(
      manager.AddDefaultOption("my_double_opt", &my_double, "A double option"));
}

// Test AddDefaultOption with a bool option
TEST_F(OptionManagerTest_166, AddDefaultOptionBool_166) {
  OptionManager manager(false);
  bool my_bool = true;
  EXPECT_NO_FATAL_FAILURE(
      manager.AddDefaultOption("my_bool_opt", &my_bool, "A bool option"));
}

// Test Parse with custom options
TEST_F(OptionManagerTest_166, ParseWithCustomDefaultOption_166) {
  OptionManager manager(false);
  int my_int = 10;
  manager.AddDefaultOption("my_int", &my_int, "An integer option");
  const char* argv[] = {"test_program", "--my_int", "99"};
  EXPECT_NO_FATAL_FAILURE(manager.Parse(3, const_cast<char**>(argv)));
  EXPECT_EQ(my_int, 99);
}

// Test Parse with database path option
TEST_F(OptionManagerTest_166, ParseDatabasePath_166) {
  OptionManager manager(false);
  manager.AddDatabaseOptions();
  const char* argv[] = {"test_program", "--database_path", "/tmp/test.db"};
  EXPECT_NO_FATAL_FAILURE(manager.Parse(3, const_cast<char**>(argv)));
  EXPECT_EQ(*manager.database_path, "/tmp/test.db");
}

// Test Parse with image path option
TEST_F(OptionManagerTest_166, ParseImagePath_166) {
  OptionManager manager(false);
  manager.AddImageOptions();
  const char* argv[] = {"test_program", "--image_path", "/tmp/images"};
  EXPECT_NO_FATAL_FAILURE(manager.Parse(3, const_cast<char**>(argv)));
  EXPECT_EQ(*manager.image_path, "/tmp/images");
}

// Test that mapper shared pointer is valid after construction
TEST_F(OptionManagerTest_166, MapperSharedPtrValid_166) {
  OptionManager manager(false);
  EXPECT_NE(manager.mapper.get(), nullptr);
}

// Test that gravity_refiner shared pointer is valid after construction
TEST_F(OptionManagerTest_166, GravityRefinerSharedPtrValid_166) {
  OptionManager manager(false);
  EXPECT_NE(manager.gravity_refiner.get(), nullptr);
}

// Test that calling Reset followed by AddAllOptions works
TEST_F(OptionManagerTest_166, ResetThenAddAllOptions_166) {
  OptionManager manager(false);
  manager.Reset();
  EXPECT_NO_FATAL_FAILURE(manager.AddAllOptions());
}

// Test multiple resets
TEST_F(OptionManagerTest_166, MultipleResets_166) {
  OptionManager manager(false);
  EXPECT_NO_FATAL_FAILURE(manager.Reset());
  EXPECT_NO_FATAL_FAILURE(manager.Reset());
  EXPECT_NO_FATAL_FAILURE(manager.Reset());
  EXPECT_NE(manager.database_path, nullptr);
  EXPECT_NE(manager.mapper, nullptr);
}

// Test Parse with no arguments (just program name)
TEST_F(OptionManagerTest_166, ParseNoArguments_166) {
  OptionManager manager(false);
  const char* argv[] = {"test_program"};
  EXPECT_NO_FATAL_FAILURE(manager.Parse(1, const_cast<char**>(argv)));
}

// Test AddRequiredOption with double
TEST_F(OptionManagerTest_166, AddRequiredOptionDouble_166) {
  OptionManager manager(false);
  double val = 1.5;
  EXPECT_NO_FATAL_FAILURE(
      manager.AddRequiredOption("req_double", &val, "Required double"));
}

// Test Parse with string default option
TEST_F(OptionManagerTest_166, ParseStringDefaultOption_166) {
  OptionManager manager(false);
  std::string my_str = "initial";
  manager.AddDefaultOption("my_str", &my_str, "A string option");
  const char* argv[] = {"test_program", "--my_str", "updated"};
  EXPECT_NO_FATAL_FAILURE(manager.Parse(3, const_cast<char**>(argv)));
  EXPECT_EQ(my_str, "updated");
}

}  // namespace
}  // namespace glomap
