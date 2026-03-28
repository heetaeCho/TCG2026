#include <gtest/gtest.h>
#include "glomap/controllers/option_manager.h"

namespace glomap {
namespace {

class OptionManagerTest_50 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create OptionManager with add_project_options = true
    option_manager_ = std::make_unique<OptionManager>(true);
  }

  std::unique_ptr<OptionManager> option_manager_;
};

// Test that OptionManager can be constructed with project options
TEST_F(OptionManagerTest_50, ConstructWithProjectOptions_50) {
  EXPECT_NE(option_manager_, nullptr);
  EXPECT_NE(option_manager_->database_path, nullptr);
  EXPECT_NE(option_manager_->image_path, nullptr);
  EXPECT_NE(option_manager_->mapper, nullptr);
  EXPECT_NE(option_manager_->gravity_refiner, nullptr);
}

// Test that OptionManager can be constructed without project options
TEST_F(OptionManagerTest_50, ConstructWithoutProjectOptions_50) {
  OptionManager om(false);
  EXPECT_NE(om.database_path, nullptr);
  EXPECT_NE(om.image_path, nullptr);
  EXPECT_NE(om.mapper, nullptr);
  EXPECT_NE(om.gravity_refiner, nullptr);
}

// Test ResetOptions with reset_paths = true clears paths
TEST_F(OptionManagerTest_50, ResetOptionsWithResetPathsTrue_50) {
  *option_manager_->database_path = "/some/database/path.db";
  *option_manager_->image_path = "/some/image/path";

  option_manager_->ResetOptions(true);

  EXPECT_EQ(*option_manager_->database_path, "");
  EXPECT_EQ(*option_manager_->image_path, "");
}

// Test ResetOptions with reset_paths = false does not clear paths
TEST_F(OptionManagerTest_50, ResetOptionsWithResetPathsFalse_50) {
  *option_manager_->database_path = "/some/database/path.db";
  *option_manager_->image_path = "/some/image/path";

  option_manager_->ResetOptions(false);

  EXPECT_EQ(*option_manager_->database_path, "/some/database/path.db");
  EXPECT_EQ(*option_manager_->image_path, "/some/image/path");
}

// Test ResetOptions resets mapper to default GlobalMapperOptions
TEST_F(OptionManagerTest_50, ResetOptionsResetsMapper_50) {
  option_manager_->mapper->num_iteration_bundle_adjustment = 999;
  option_manager_->mapper->skip_preprocessing = true;

  option_manager_->ResetOptions(false);

  GlobalMapperOptions defaults;
  EXPECT_EQ(option_manager_->mapper->num_iteration_bundle_adjustment,
            defaults.num_iteration_bundle_adjustment);
  EXPECT_EQ(option_manager_->mapper->skip_preprocessing,
            defaults.skip_preprocessing);
}

// Test ResetOptions resets gravity_refiner to default GravityRefinerOptions
TEST_F(OptionManagerTest_50, ResetOptionsResetsGravityRefiner_50) {
  option_manager_->gravity_refiner->max_outlier_ratio = 0.99;
  option_manager_->gravity_refiner->max_gravity_error = 100.0;
  option_manager_->gravity_refiner->min_num_neighbors = 999;

  option_manager_->ResetOptions(false);

  GravityRefinerOptions defaults;
  EXPECT_DOUBLE_EQ(option_manager_->gravity_refiner->max_outlier_ratio,
                   defaults.max_outlier_ratio);
  EXPECT_DOUBLE_EQ(option_manager_->gravity_refiner->max_gravity_error,
                   defaults.max_gravity_error);
  EXPECT_EQ(option_manager_->gravity_refiner->min_num_neighbors,
            defaults.min_num_neighbors);
}

// Test ResetOptions with reset_paths = true resets everything
TEST_F(OptionManagerTest_50, ResetOptionsWithResetPathsTrueResetsAll_50) {
  *option_manager_->database_path = "/modified/db";
  *option_manager_->image_path = "/modified/img";
  option_manager_->mapper->num_iteration_bundle_adjustment = 42;
  option_manager_->gravity_refiner->max_outlier_ratio = 0.1;

  option_manager_->ResetOptions(true);

  EXPECT_EQ(*option_manager_->database_path, "");
  EXPECT_EQ(*option_manager_->image_path, "");
  GlobalMapperOptions mapper_defaults;
  EXPECT_EQ(option_manager_->mapper->num_iteration_bundle_adjustment,
            mapper_defaults.num_iteration_bundle_adjustment);
  GravityRefinerOptions gravity_defaults;
  EXPECT_DOUBLE_EQ(option_manager_->gravity_refiner->max_outlier_ratio,
                   gravity_defaults.max_outlier_ratio);
}

// Test that ResetOptions can be called multiple times
TEST_F(OptionManagerTest_50, ResetOptionsCalledMultipleTimes_50) {
  for (int i = 0; i < 5; ++i) {
    *option_manager_->database_path = "test_path";
    option_manager_->ResetOptions(true);
    EXPECT_EQ(*option_manager_->database_path, "");
  }
}

// Test ResetOptions when paths are already empty
TEST_F(OptionManagerTest_50, ResetOptionsWithAlreadyEmptyPaths_50) {
  *option_manager_->database_path = "";
  *option_manager_->image_path = "";

  option_manager_->ResetOptions(true);

  EXPECT_EQ(*option_manager_->database_path, "");
  EXPECT_EQ(*option_manager_->image_path, "");
}

// Test AddDatabaseOptions does not throw
TEST_F(OptionManagerTest_50, AddDatabaseOptionsNoThrow_50) {
  EXPECT_NO_THROW(option_manager_->AddDatabaseOptions());
}

// Test AddImageOptions does not throw
TEST_F(OptionManagerTest_50, AddImageOptionsNoThrow_50) {
  EXPECT_NO_THROW(option_manager_->AddImageOptions());
}

// Test AddGlobalMapperOptions does not throw
TEST_F(OptionManagerTest_50, AddGlobalMapperOptionsNoThrow_50) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperOptions());
}

// Test AddAllOptions does not throw
TEST_F(OptionManagerTest_50, AddAllOptionsNoThrow_50) {
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
}

// Test AddGravityRefinerOptions does not throw
TEST_F(OptionManagerTest_50, AddGravityRefinerOptionsNoThrow_50) {
  EXPECT_NO_THROW(option_manager_->AddGravityRefinerOptions());
}

// Test AddViewGraphCalibrationOptions does not throw
TEST_F(OptionManagerTest_50, AddViewGraphCalibrationOptionsNoThrow_50) {
  EXPECT_NO_THROW(option_manager_->AddViewGraphCalibrationOptions());
}

// Test AddRelativePoseEstimationOptions does not throw
TEST_F(OptionManagerTest_50, AddRelativePoseEstimationOptionsNoThrow_50) {
  EXPECT_NO_THROW(option_manager_->AddRelativePoseEstimationOptions());
}

// Test AddRotationEstimatorOptions does not throw
TEST_F(OptionManagerTest_50, AddRotationEstimatorOptionsNoThrow_50) {
  EXPECT_NO_THROW(option_manager_->AddRotationEstimatorOptions());
}

// Test AddTrackEstablishmentOptions does not throw
TEST_F(OptionManagerTest_50, AddTrackEstablishmentOptionsNoThrow_50) {
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
}

// Test AddGlobalPositionerOptions does not throw
TEST_F(OptionManagerTest_50, AddGlobalPositionerOptionsNoThrow_50) {
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
}

// Test AddBundleAdjusterOptions does not throw
TEST_F(OptionManagerTest_50, AddBundleAdjusterOptionsNoThrow_50) {
  EXPECT_NO_THROW(option_manager_->AddBundleAdjusterOptions());
}

// Test AddTriangulatorOptions does not throw
TEST_F(OptionManagerTest_50, AddTriangulatorOptionsNoThrow_50) {
  EXPECT_NO_THROW(option_manager_->AddTriangulatorOptions());
}

// Test AddInlierThresholdOptions does not throw
TEST_F(OptionManagerTest_50, AddInlierThresholdOptionsNoThrow_50) {
  EXPECT_NO_THROW(option_manager_->AddInlierThresholdOptions());
}

// Test Reset does not throw
TEST_F(OptionManagerTest_50, ResetNoThrow_50) {
  EXPECT_NO_THROW(option_manager_->Reset());
}

// Test that shared_ptr members are valid after construction
TEST_F(OptionManagerTest_50, SharedPtrsAreValid_50) {
  EXPECT_TRUE(option_manager_->database_path.get() != nullptr);
  EXPECT_TRUE(option_manager_->image_path.get() != nullptr);
  EXPECT_TRUE(option_manager_->mapper.get() != nullptr);
  EXPECT_TRUE(option_manager_->gravity_refiner.get() != nullptr);
}

// Test mapper default values after construction
TEST_F(OptionManagerTest_50, MapperDefaultValues_50) {
  GlobalMapperOptions defaults;
  EXPECT_EQ(option_manager_->mapper->num_iteration_bundle_adjustment,
            defaults.num_iteration_bundle_adjustment);
  EXPECT_EQ(option_manager_->mapper->num_iteration_retriangulation,
            defaults.num_iteration_retriangulation);
  EXPECT_EQ(option_manager_->mapper->skip_preprocessing,
            defaults.skip_preprocessing);
}

// Test gravity_refiner default values after construction
TEST_F(OptionManagerTest_50, GravityRefinerDefaultValues_50) {
  GravityRefinerOptions defaults;
  EXPECT_DOUBLE_EQ(option_manager_->gravity_refiner->max_outlier_ratio,
                   defaults.max_outlier_ratio);
  EXPECT_DOUBLE_EQ(option_manager_->gravity_refiner->max_gravity_error,
                   defaults.max_gravity_error);
  EXPECT_EQ(option_manager_->gravity_refiner->min_num_neighbors,
            defaults.min_num_neighbors);
}

// Test AddGlobalMapperFullOptions does not throw
TEST_F(OptionManagerTest_50, AddGlobalMapperFullOptionsNoThrow_50) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperFullOptions());
}

// Test AddGlobalMapperResumeOptions does not throw
TEST_F(OptionManagerTest_50, AddGlobalMapperResumeOptionsNoThrow_50) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperResumeOptions());
}

// Test AddGlobalMapperResumeFullOptions does not throw
TEST_F(OptionManagerTest_50, AddGlobalMapperResumeFullOptionsNoThrow_50) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperResumeFullOptions());
}

// Test that modifying mapper fields persists until reset
TEST_F(OptionManagerTest_50, MapperModificationPersists_50) {
  option_manager_->mapper->skip_bundle_adjustment = true;
  option_manager_->mapper->num_iteration_bundle_adjustment = 10;

  EXPECT_TRUE(option_manager_->mapper->skip_bundle_adjustment);
  EXPECT_EQ(option_manager_->mapper->num_iteration_bundle_adjustment, 10);

  // After reset, should go back to defaults
  option_manager_->ResetOptions(false);
  GlobalMapperOptions defaults;
  EXPECT_EQ(option_manager_->mapper->skip_bundle_adjustment,
            defaults.skip_bundle_adjustment);
  EXPECT_EQ(option_manager_->mapper->num_iteration_bundle_adjustment,
            defaults.num_iteration_bundle_adjustment);
}

// Test that database_path and image_path start empty (or at default)
TEST_F(OptionManagerTest_50, PathsStartEmpty_50) {
  // After construction, paths should be empty or default
  // After reset with reset_paths=true they should definitely be empty
  option_manager_->ResetOptions(true);
  EXPECT_EQ(*option_manager_->database_path, "");
  EXPECT_EQ(*option_manager_->image_path, "");
}

}  // namespace
}  // namespace glomap
