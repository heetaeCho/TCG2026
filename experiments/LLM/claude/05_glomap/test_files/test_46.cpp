#include <gtest/gtest.h>
#include "glomap/controllers/option_manager.h"

namespace glomap {
namespace {

class OptionManagerTest_46 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create OptionManager with add_project_options = false to avoid
    // automatically adding options we don't want for isolated tests
    option_manager_ = std::make_unique<OptionManager>(false);
  }

  std::unique_ptr<OptionManager> option_manager_;
};

// Test that AddTriangulatorOptions can be called without crashing
TEST_F(OptionManagerTest_46, AddTriangulatorOptionsDoesNotCrash_46) {
  EXPECT_NO_THROW(option_manager_->AddTriangulatorOptions());
}

// Test that calling AddTriangulatorOptions twice is idempotent (guarded by flag)
TEST_F(OptionManagerTest_46, AddTriangulatorOptionsIdempotent_46) {
  EXPECT_NO_THROW(option_manager_->AddTriangulatorOptions());
  EXPECT_NO_THROW(option_manager_->AddTriangulatorOptions());
}

// Test that the mapper shared pointer is valid after construction
TEST_F(OptionManagerTest_46, MapperSharedPtrIsValid_46) {
  ASSERT_NE(option_manager_->mapper, nullptr);
}

// Test that default triangulator option values are set correctly before AddTriangulatorOptions
TEST_F(OptionManagerTest_46, DefaultTriangulatorValues_46) {
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_triangulator.tri_complete_max_reproj_error, 15.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_triangulator.tri_merge_max_reproj_error, 15.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_triangulator.tri_min_angle, 1.0);
  EXPECT_EQ(option_manager_->mapper->opt_triangulator.min_num_matches, 15);
}

// Test that after AddTriangulatorOptions, the default values remain unchanged
TEST_F(OptionManagerTest_46, TriangulatorOptionsDefaultsUnchangedAfterAdd_46) {
  option_manager_->AddTriangulatorOptions();
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_triangulator.tri_complete_max_reproj_error, 15.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_triangulator.tri_merge_max_reproj_error, 15.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_triangulator.tri_min_angle, 1.0);
  EXPECT_EQ(option_manager_->mapper->opt_triangulator.min_num_matches, 15);
}

// Test AddAllOptions includes triangulator options and doesn't crash
TEST_F(OptionManagerTest_46, AddAllOptionsIncludesTriangulator_46) {
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
}

// Test AddAllOptions called twice doesn't crash (all guards should work)
TEST_F(OptionManagerTest_46, AddAllOptionsTwice_46) {
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
}

// Test that Reset works after adding triangulator options
TEST_F(OptionManagerTest_46, ResetAfterAddTriangulatorOptions_46) {
  option_manager_->AddTriangulatorOptions();
  EXPECT_NO_THROW(option_manager_->Reset());
}

// Test that ResetOptions with reset_paths=false works
TEST_F(OptionManagerTest_46, ResetOptionsNoPaths_46) {
  option_manager_->AddTriangulatorOptions();
  EXPECT_NO_THROW(option_manager_->ResetOptions(false));
}

// Test that ResetOptions with reset_paths=true works
TEST_F(OptionManagerTest_46, ResetOptionsWithPaths_46) {
  option_manager_->AddTriangulatorOptions();
  EXPECT_NO_THROW(option_manager_->ResetOptions(true));
}

// Test that after Reset, triangulator options can be re-added
TEST_F(OptionManagerTest_46, ResetThenReaddTriangulatorOptions_46) {
  option_manager_->AddTriangulatorOptions();
  option_manager_->Reset();
  // After reset, the guard flag should be cleared, allowing re-addition
  EXPECT_NO_THROW(option_manager_->AddTriangulatorOptions());
}

// Test AddDatabaseOptions does not crash
TEST_F(OptionManagerTest_46, AddDatabaseOptions_46) {
  EXPECT_NO_THROW(option_manager_->AddDatabaseOptions());
}

// Test AddImageOptions does not crash
TEST_F(OptionManagerTest_46, AddImageOptions_46) {
  EXPECT_NO_THROW(option_manager_->AddImageOptions());
}

// Test AddGlobalMapperOptions does not crash
TEST_F(OptionManagerTest_46, AddGlobalMapperOptions_46) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperOptions());
}

// Test AddViewGraphCalibrationOptions does not crash
TEST_F(OptionManagerTest_46, AddViewGraphCalibrationOptions_46) {
  EXPECT_NO_THROW(option_manager_->AddViewGraphCalibrationOptions());
}

// Test AddRelativePoseEstimationOptions does not crash
TEST_F(OptionManagerTest_46, AddRelativePoseEstimationOptions_46) {
  EXPECT_NO_THROW(option_manager_->AddRelativePoseEstimationOptions());
}

// Test AddRotationEstimatorOptions does not crash
TEST_F(OptionManagerTest_46, AddRotationEstimatorOptions_46) {
  EXPECT_NO_THROW(option_manager_->AddRotationEstimatorOptions());
}

// Test AddTrackEstablishmentOptions does not crash
TEST_F(OptionManagerTest_46, AddTrackEstablishmentOptions_46) {
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
}

// Test AddGlobalPositionerOptions does not crash
TEST_F(OptionManagerTest_46, AddGlobalPositionerOptions_46) {
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
}

// Test AddBundleAdjusterOptions does not crash
TEST_F(OptionManagerTest_46, AddBundleAdjusterOptions_46) {
  EXPECT_NO_THROW(option_manager_->AddBundleAdjusterOptions());
}

// Test AddInlierThresholdOptions does not crash
TEST_F(OptionManagerTest_46, AddInlierThresholdOptions_46) {
  EXPECT_NO_THROW(option_manager_->AddInlierThresholdOptions());
}

// Test AddGravityRefinerOptions does not crash
TEST_F(OptionManagerTest_46, AddGravityRefinerOptions_46) {
  EXPECT_NO_THROW(option_manager_->AddGravityRefinerOptions());
}

// Test Parse with minimal arguments after adding triangulator options
TEST_F(OptionManagerTest_46, ParseWithTriangulatorOptions_46) {
  option_manager_->AddTriangulatorOptions();
  const char* argv[] = {"test_program"};
  EXPECT_NO_THROW(option_manager_->Parse(1, const_cast<char**>(argv)));
}

// Test Parse with triangulation option overrides
TEST_F(OptionManagerTest_46, ParseOverrideTriangulationCompleteMaxReprojError_46) {
  option_manager_->AddTriangulatorOptions();
  const char* argv[] = {"test_program",
                         "--Triangulation.complete_max_reproj_error", "20.0"};
  EXPECT_NO_THROW(option_manager_->Parse(3, const_cast<char**>(argv)));
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_triangulator.tri_complete_max_reproj_error, 20.0);
}

// Test Parse with triangulation merge_max_reproj_error override
TEST_F(OptionManagerTest_46, ParseOverrideTriangulationMergeMaxReprojError_46) {
  option_manager_->AddTriangulatorOptions();
  const char* argv[] = {"test_program",
                         "--Triangulation.merge_max_reproj_error", "25.5"};
  EXPECT_NO_THROW(option_manager_->Parse(3, const_cast<char**>(argv)));
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_triangulator.tri_merge_max_reproj_error, 25.5);
}

// Test Parse with triangulation min_angle override
TEST_F(OptionManagerTest_46, ParseOverrideTriangulationMinAngle_46) {
  option_manager_->AddTriangulatorOptions();
  const char* argv[] = {"test_program",
                         "--Triangulation.min_angle", "2.5"};
  EXPECT_NO_THROW(option_manager_->Parse(3, const_cast<char**>(argv)));
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_triangulator.tri_min_angle, 2.5);
}

// Test Parse with triangulation min_num_matches override
TEST_F(OptionManagerTest_46, ParseOverrideTriangulationMinNumMatches_46) {
  option_manager_->AddTriangulatorOptions();
  const char* argv[] = {"test_program",
                         "--Triangulation.min_num_matches", "30"};
  EXPECT_NO_THROW(option_manager_->Parse(3, const_cast<char**>(argv)));
  EXPECT_EQ(option_manager_->mapper->opt_triangulator.min_num_matches, 30);
}

// Test Parse with all triangulation options overridden at once
TEST_F(OptionManagerTest_46, ParseOverrideAllTriangulationOptions_46) {
  option_manager_->AddTriangulatorOptions();
  const char* argv[] = {"test_program",
                         "--Triangulation.complete_max_reproj_error", "10.0",
                         "--Triangulation.merge_max_reproj_error", "12.0",
                         "--Triangulation.min_angle", "3.0",
                         "--Triangulation.min_num_matches", "50"};
  EXPECT_NO_THROW(option_manager_->Parse(9, const_cast<char**>(argv)));
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_triangulator.tri_complete_max_reproj_error, 10.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_triangulator.tri_merge_max_reproj_error, 12.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_triangulator.tri_min_angle, 3.0);
  EXPECT_EQ(option_manager_->mapper->opt_triangulator.min_num_matches, 50);
}

// Test Parse with zero value for min_num_matches (boundary)
TEST_F(OptionManagerTest_46, ParseBoundaryMinNumMatchesZero_46) {
  option_manager_->AddTriangulatorOptions();
  const char* argv[] = {"test_program",
                         "--Triangulation.min_num_matches", "0"};
  EXPECT_NO_THROW(option_manager_->Parse(3, const_cast<char**>(argv)));
  EXPECT_EQ(option_manager_->mapper->opt_triangulator.min_num_matches, 0);
}

// Test Parse with zero angle (boundary)
TEST_F(OptionManagerTest_46, ParseBoundaryMinAngleZero_46) {
  option_manager_->AddTriangulatorOptions();
  const char* argv[] = {"test_program",
                         "--Triangulation.min_angle", "0.0"};
  EXPECT_NO_THROW(option_manager_->Parse(3, const_cast<char**>(argv)));
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_triangulator.tri_min_angle, 0.0);
}

// Test Parse with negative reprojection error (boundary/edge case)
TEST_F(OptionManagerTest_46, ParseNegativeReprojError_46) {
  option_manager_->AddTriangulatorOptions();
  const char* argv[] = {"test_program",
                         "--Triangulation.complete_max_reproj_error", "-1.0"};
  EXPECT_NO_THROW(option_manager_->Parse(3, const_cast<char**>(argv)));
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_triangulator.tri_complete_max_reproj_error, -1.0);
}

// Test constructing OptionManager with add_project_options=true
TEST(OptionManagerConstructionTest_46, ConstructWithProjectOptions_46) {
  EXPECT_NO_THROW(OptionManager(true));
}

// Test constructing OptionManager with add_project_options=false
TEST(OptionManagerConstructionTest_46, ConstructWithoutProjectOptions_46) {
  EXPECT_NO_THROW(OptionManager(false));
}

// Test AddGlobalMapperFullOptions does not crash
TEST_F(OptionManagerTest_46, AddGlobalMapperFullOptions_46) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperFullOptions());
}

// Test AddGlobalMapperResumeOptions does not crash
TEST_F(OptionManagerTest_46, AddGlobalMapperResumeOptions_46) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperResumeOptions());
}

// Test AddGlobalMapperResumeFullOptions does not crash
TEST_F(OptionManagerTest_46, AddGlobalMapperResumeFullOptions_46) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperResumeFullOptions());
}

// Test that database_path shared pointer is valid
TEST_F(OptionManagerTest_46, DatabasePathSharedPtrValid_46) {
  ASSERT_NE(option_manager_->database_path, nullptr);
}

// Test that image_path shared pointer is valid
TEST_F(OptionManagerTest_46, ImagePathSharedPtrValid_46) {
  ASSERT_NE(option_manager_->image_path, nullptr);
}

// Test that gravity_refiner shared pointer is valid
TEST_F(OptionManagerTest_46, GravityRefinerSharedPtrValid_46) {
  ASSERT_NE(option_manager_->gravity_refiner, nullptr);
}

// Test AddDefaultOption for a custom double option
TEST_F(OptionManagerTest_46, AddDefaultOptionDouble_46) {
  double custom_val = 42.0;
  EXPECT_NO_THROW(option_manager_->AddDefaultOption(
      "Custom.double_option", &custom_val, "A custom double option"));
}

// Test AddDefaultOption for a custom int option
TEST_F(OptionManagerTest_46, AddDefaultOptionInt_46) {
  int custom_val = 7;
  EXPECT_NO_THROW(option_manager_->AddDefaultOption(
      "Custom.int_option", &custom_val, "A custom int option"));
}

// Test AddDefaultOption for a custom string option
TEST_F(OptionManagerTest_46, AddDefaultOptionString_46) {
  std::string custom_val = "hello";
  EXPECT_NO_THROW(option_manager_->AddDefaultOption(
      "Custom.string_option", &custom_val, "A custom string option"));
}

// Test AddRequiredOption for a custom option
TEST_F(OptionManagerTest_46, AddRequiredOptionString_46) {
  std::string custom_val = "required_val";
  EXPECT_NO_THROW(option_manager_->AddRequiredOption(
      "Custom.required_option", &custom_val, "A required option"));
}

// Test that after Reset and re-adding options, Parse still works
TEST_F(OptionManagerTest_46, ResetAndReparseTriangulatorOptions_46) {
  option_manager_->AddTriangulatorOptions();
  option_manager_->Reset();
  option_manager_->AddTriangulatorOptions();
  const char* argv[] = {"test_program",
                         "--Triangulation.min_num_matches", "100"};
  EXPECT_NO_THROW(option_manager_->Parse(3, const_cast<char**>(argv)));
  EXPECT_EQ(option_manager_->mapper->opt_triangulator.min_num_matches, 100);
}

// Test very large values for triangulation options
TEST_F(OptionManagerTest_46, ParseLargeValuesTriangulationOptions_46) {
  option_manager_->AddTriangulatorOptions();
  const char* argv[] = {"test_program",
                         "--Triangulation.complete_max_reproj_error", "1e10",
                         "--Triangulation.min_num_matches", "1000000"};
  EXPECT_NO_THROW(option_manager_->Parse(5, const_cast<char**>(argv)));
  EXPECT_DOUBLE_EQ(option_manager_->mapper->opt_triangulator.tri_complete_max_reproj_error, 1e10);
  EXPECT_EQ(option_manager_->mapper->opt_triangulator.min_num_matches, 1000000);
}

}  // namespace
}  // namespace glomap
