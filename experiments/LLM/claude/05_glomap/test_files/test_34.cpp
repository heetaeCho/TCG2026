#include <gtest/gtest.h>
#include "glomap/controllers/option_manager.h"

namespace glomap {
namespace {

class OptionManagerTest_34 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create OptionManager without project options by default
    option_manager_ = std::make_unique<OptionManager>(false);
  }

  std::unique_ptr<OptionManager> option_manager_;
};

// Test that OptionManager can be constructed with add_project_options = false
TEST_F(OptionManagerTest_34, ConstructWithoutProjectOptions_34) {
  EXPECT_NO_THROW(OptionManager om(false));
}

// Test that OptionManager can be constructed with add_project_options = true
TEST_F(OptionManagerTest_34, ConstructWithProjectOptions_34) {
  EXPECT_NO_THROW(OptionManager om(true));
}

// Test that database_path is initialized (shared_ptr is not null)
TEST_F(OptionManagerTest_34, DatabasePathInitialized_34) {
  EXPECT_NE(option_manager_->database_path, nullptr);
}

// Test that image_path is initialized (shared_ptr is not null)
TEST_F(OptionManagerTest_34, ImagePathInitialized_34) {
  EXPECT_NE(option_manager_->image_path, nullptr);
}

// Test that mapper is initialized (shared_ptr is not null)
TEST_F(OptionManagerTest_34, MapperInitialized_34) {
  EXPECT_NE(option_manager_->mapper, nullptr);
}

// Test that gravity_refiner is initialized
TEST_F(OptionManagerTest_34, GravityRefinerInitialized_34) {
  EXPECT_NE(option_manager_->gravity_refiner, nullptr);
}

// Test AddDatabaseOptions can be called without throwing
TEST_F(OptionManagerTest_34, AddDatabaseOptionsNoThrow_34) {
  EXPECT_NO_THROW(option_manager_->AddDatabaseOptions());
}

// Test AddDatabaseOptions is idempotent (calling it twice should not throw)
TEST_F(OptionManagerTest_34, AddDatabaseOptionsIdempotent_34) {
  EXPECT_NO_THROW(option_manager_->AddDatabaseOptions());
  EXPECT_NO_THROW(option_manager_->AddDatabaseOptions());
}

// Test AddImageOptions can be called without throwing
TEST_F(OptionManagerTest_34, AddImageOptionsNoThrow_34) {
  EXPECT_NO_THROW(option_manager_->AddImageOptions());
}

// Test AddImageOptions is idempotent
TEST_F(OptionManagerTest_34, AddImageOptionsIdempotent_34) {
  EXPECT_NO_THROW(option_manager_->AddImageOptions());
  EXPECT_NO_THROW(option_manager_->AddImageOptions());
}

// Test AddGlobalMapperOptions can be called without throwing
TEST_F(OptionManagerTest_34, AddGlobalMapperOptionsNoThrow_34) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperOptions());
}

// Test AddGlobalMapperOptions is idempotent
TEST_F(OptionManagerTest_34, AddGlobalMapperOptionsIdempotent_34) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperOptions());
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperOptions());
}

// Test AddGlobalMapperFullOptions can be called without throwing
TEST_F(OptionManagerTest_34, AddGlobalMapperFullOptionsNoThrow_34) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperFullOptions());
}

// Test AddGlobalMapperResumeOptions can be called without throwing
TEST_F(OptionManagerTest_34, AddGlobalMapperResumeOptionsNoThrow_34) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperResumeOptions());
}

// Test AddGlobalMapperResumeFullOptions can be called without throwing
TEST_F(OptionManagerTest_34, AddGlobalMapperResumeFullOptionsNoThrow_34) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperResumeFullOptions());
}

// Test AddViewGraphCalibrationOptions can be called without throwing
TEST_F(OptionManagerTest_34, AddViewGraphCalibrationOptionsNoThrow_34) {
  EXPECT_NO_THROW(option_manager_->AddViewGraphCalibrationOptions());
}

// Test AddViewGraphCalibrationOptions is idempotent
TEST_F(OptionManagerTest_34, AddViewGraphCalibrationOptionsIdempotent_34) {
  EXPECT_NO_THROW(option_manager_->AddViewGraphCalibrationOptions());
  EXPECT_NO_THROW(option_manager_->AddViewGraphCalibrationOptions());
}

// Test AddRelativePoseEstimationOptions can be called without throwing
TEST_F(OptionManagerTest_34, AddRelativePoseEstimationOptionsNoThrow_34) {
  EXPECT_NO_THROW(option_manager_->AddRelativePoseEstimationOptions());
}

// Test AddRelativePoseEstimationOptions is idempotent
TEST_F(OptionManagerTest_34, AddRelativePoseEstimationOptionsIdempotent_34) {
  EXPECT_NO_THROW(option_manager_->AddRelativePoseEstimationOptions());
  EXPECT_NO_THROW(option_manager_->AddRelativePoseEstimationOptions());
}

// Test AddRotationEstimatorOptions can be called without throwing
TEST_F(OptionManagerTest_34, AddRotationEstimatorOptionsNoThrow_34) {
  EXPECT_NO_THROW(option_manager_->AddRotationEstimatorOptions());
}

// Test AddRotationEstimatorOptions is idempotent
TEST_F(OptionManagerTest_34, AddRotationEstimatorOptionsIdempotent_34) {
  EXPECT_NO_THROW(option_manager_->AddRotationEstimatorOptions());
  EXPECT_NO_THROW(option_manager_->AddRotationEstimatorOptions());
}

// Test AddTrackEstablishmentOptions can be called without throwing
TEST_F(OptionManagerTest_34, AddTrackEstablishmentOptionsNoThrow_34) {
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
}

// Test AddTrackEstablishmentOptions is idempotent
TEST_F(OptionManagerTest_34, AddTrackEstablishmentOptionsIdempotent_34) {
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
}

// Test AddGlobalPositionerOptions can be called without throwing
TEST_F(OptionManagerTest_34, AddGlobalPositionerOptionsNoThrow_34) {
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
}

// Test AddGlobalPositionerOptions is idempotent
TEST_F(OptionManagerTest_34, AddGlobalPositionerOptionsIdempotent_34) {
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
}

// Test AddBundleAdjusterOptions can be called without throwing
TEST_F(OptionManagerTest_34, AddBundleAdjusterOptionsNoThrow_34) {
  EXPECT_NO_THROW(option_manager_->AddBundleAdjusterOptions());
}

// Test AddBundleAdjusterOptions is idempotent
TEST_F(OptionManagerTest_34, AddBundleAdjusterOptionsIdempotent_34) {
  EXPECT_NO_THROW(option_manager_->AddBundleAdjusterOptions());
  EXPECT_NO_THROW(option_manager_->AddBundleAdjusterOptions());
}

// Test AddTriangulatorOptions can be called without throwing
TEST_F(OptionManagerTest_34, AddTriangulatorOptionsNoThrow_34) {
  EXPECT_NO_THROW(option_manager_->AddTriangulatorOptions());
}

// Test AddTriangulatorOptions is idempotent
TEST_F(OptionManagerTest_34, AddTriangulatorOptionsIdempotent_34) {
  EXPECT_NO_THROW(option_manager_->AddTriangulatorOptions());
  EXPECT_NO_THROW(option_manager_->AddTriangulatorOptions());
}

// Test AddInlierThresholdOptions can be called without throwing
TEST_F(OptionManagerTest_34, AddInlierThresholdOptionsNoThrow_34) {
  EXPECT_NO_THROW(option_manager_->AddInlierThresholdOptions());
}

// Test AddInlierThresholdOptions is idempotent
TEST_F(OptionManagerTest_34, AddInlierThresholdOptionsIdempotent_34) {
  EXPECT_NO_THROW(option_manager_->AddInlierThresholdOptions());
  EXPECT_NO_THROW(option_manager_->AddInlierThresholdOptions());
}

// Test AddGravityRefinerOptions can be called without throwing
TEST_F(OptionManagerTest_34, AddGravityRefinerOptionsNoThrow_34) {
  EXPECT_NO_THROW(option_manager_->AddGravityRefinerOptions());
}

// Test AddGravityRefinerOptions is idempotent
TEST_F(OptionManagerTest_34, AddGravityRefinerOptionsIdempotent_34) {
  EXPECT_NO_THROW(option_manager_->AddGravityRefinerOptions());
  EXPECT_NO_THROW(option_manager_->AddGravityRefinerOptions());
}

// Test AddAllOptions can be called without throwing
TEST_F(OptionManagerTest_34, AddAllOptionsNoThrow_34) {
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
}

// Test AddAllOptions is idempotent (calling twice should be safe)
TEST_F(OptionManagerTest_34, AddAllOptionsIdempotent_34) {
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
}

// Test Reset can be called without throwing
TEST_F(OptionManagerTest_34, ResetNoThrow_34) {
  EXPECT_NO_THROW(option_manager_->Reset());
}

// Test Reset after adding options
TEST_F(OptionManagerTest_34, ResetAfterAddingOptions_34) {
  option_manager_->AddAllOptions();
  EXPECT_NO_THROW(option_manager_->Reset());
}

// Test that after Reset, options can be re-added
TEST_F(OptionManagerTest_34, ReAddOptionsAfterReset_34) {
  option_manager_->AddDatabaseOptions();
  option_manager_->Reset();
  EXPECT_NO_THROW(option_manager_->AddDatabaseOptions());
}

// Test ResetOptions with reset_paths = true
TEST_F(OptionManagerTest_34, ResetOptionsWithResetPaths_34) {
  option_manager_->AddAllOptions();
  EXPECT_NO_THROW(option_manager_->ResetOptions(true));
}

// Test ResetOptions with reset_paths = false
TEST_F(OptionManagerTest_34, ResetOptionsWithoutResetPaths_34) {
  option_manager_->AddAllOptions();
  EXPECT_NO_THROW(option_manager_->ResetOptions(false));
}

// Test that after ResetOptions with reset_paths=true, paths are reset
TEST_F(OptionManagerTest_34, ResetOptionsResetsPathsWhenTrue_34) {
  *option_manager_->database_path = "/some/path/to/db";
  *option_manager_->image_path = "/some/path/to/images";
  option_manager_->ResetOptions(true);
  EXPECT_TRUE(option_manager_->database_path->empty());
  EXPECT_TRUE(option_manager_->image_path->empty());
}

// Test that after ResetOptions with reset_paths=false, paths are preserved
TEST_F(OptionManagerTest_34, ResetOptionsPreservesPathsWhenFalse_34) {
  *option_manager_->database_path = "/some/path/to/db";
  *option_manager_->image_path = "/some/path/to/images";
  option_manager_->ResetOptions(false);
  EXPECT_EQ(*option_manager_->database_path, "/some/path/to/db");
  EXPECT_EQ(*option_manager_->image_path, "/some/path/to/images");
}

// Test Parse with minimal arguments (just program name)
TEST_F(OptionManagerTest_34, ParseWithNoArguments_34) {
  option_manager_->AddAllOptions();
  const char* argv[] = {"test_program"};
  // Parse with only program name - this may or may not throw depending on required options
  // We just test that it can be called; required options may cause issues
  // Since database_path is required, parsing without it might throw
  // We test the interface call itself
  int argc = 1;
  // Note: This might throw because required options are not provided
  // We test that behavior is consistent
  try {
    option_manager_->Parse(argc, const_cast<char**>(argv));
  } catch (...) {
    // Expected if required options are not provided
  }
}

// Test Parse with database_path argument
TEST_F(OptionManagerTest_34, ParseWithDatabasePath_34) {
  option_manager_->AddDatabaseOptions();
  const char* argv[] = {"test_program", "--database_path", "/tmp/test.db"};
  int argc = 3;
  EXPECT_NO_THROW(option_manager_->Parse(argc, const_cast<char**>(argv)));
  EXPECT_EQ(*option_manager_->database_path, "/tmp/test.db");
}

// Test Parse with image_path argument
TEST_F(OptionManagerTest_34, ParseWithImagePath_34) {
  option_manager_->AddImageOptions();
  const char* argv[] = {"test_program", "--image_path", "/tmp/images"};
  int argc = 3;
  EXPECT_NO_THROW(option_manager_->Parse(argc, const_cast<char**>(argv)));
  EXPECT_EQ(*option_manager_->image_path, "/tmp/images");
}

// Test AddRequiredOption with a string type
TEST_F(OptionManagerTest_34, AddRequiredOptionString_34) {
  std::string custom_option;
  EXPECT_NO_THROW(
      option_manager_->AddRequiredOption("custom_string", &custom_option, "A custom string option"));
}

// Test AddDefaultOption with an int type
TEST_F(OptionManagerTest_34, AddDefaultOptionInt_34) {
  int custom_int = 42;
  EXPECT_NO_THROW(
      option_manager_->AddDefaultOption("custom_int", &custom_int, "A custom int option"));
}

// Test AddDefaultOption with a double type
TEST_F(OptionManagerTest_34, AddDefaultOptionDouble_34) {
  double custom_double = 3.14;
  EXPECT_NO_THROW(
      option_manager_->AddDefaultOption("custom_double", &custom_double, "A custom double option"));
}

// Test AddDefaultOption with a bool type
TEST_F(OptionManagerTest_34, AddDefaultOptionBool_34) {
  bool custom_bool = true;
  EXPECT_NO_THROW(
      option_manager_->AddDefaultOption("custom_bool", &custom_bool, "A custom bool option"));
}

// Test that adding individual options then calling AddAllOptions works
TEST_F(OptionManagerTest_34, AddIndividualThenAllOptions_34) {
  option_manager_->AddDatabaseOptions();
  option_manager_->AddImageOptions();
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
}

// Test that after Reset, re-adding all options works
TEST_F(OptionManagerTest_34, ResetThenReAddAll_34) {
  option_manager_->AddAllOptions();
  option_manager_->Reset();
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
}

// Test adding database and image options, then parsing both
TEST_F(OptionManagerTest_34, ParseDatabaseAndImagePaths_34) {
  option_manager_->AddDatabaseOptions();
  option_manager_->AddImageOptions();
  const char* argv[] = {"test_program",
                         "--database_path", "/tmp/test.db",
                         "--image_path", "/tmp/images"};
  int argc = 5;
  EXPECT_NO_THROW(option_manager_->Parse(argc, const_cast<char**>(argv)));
  EXPECT_EQ(*option_manager_->database_path, "/tmp/test.db");
  EXPECT_EQ(*option_manager_->image_path, "/tmp/images");
}

// Test that shared_ptr members remain valid after Reset
TEST_F(OptionManagerTest_34, SharedPtrValidAfterReset_34) {
  auto db_path_ptr = option_manager_->database_path;
  auto img_path_ptr = option_manager_->image_path;
  option_manager_->Reset();
  // After reset, the shared_ptrs in the option_manager should still be valid
  EXPECT_NE(option_manager_->database_path, nullptr);
  EXPECT_NE(option_manager_->image_path, nullptr);
  EXPECT_NE(option_manager_->mapper, nullptr);
  EXPECT_NE(option_manager_->gravity_refiner, nullptr);
}

// Test constructing with project options = true adds database and image options implicitly
TEST_F(OptionManagerTest_34, ConstructWithProjectOptionsAddsPaths_34) {
  OptionManager om(true);
  // With project options, database_path and image_path should be registered
  const char* argv[] = {"test_program",
                         "--database_path", "/tmp/proj.db",
                         "--image_path", "/tmp/proj_images"};
  int argc = 5;
  // This should work if project options include database and image options
  EXPECT_NO_THROW(om.Parse(argc, const_cast<char**>(argv)));
  EXPECT_EQ(*om.database_path, "/tmp/proj.db");
  EXPECT_EQ(*om.image_path, "/tmp/proj_images");
}

}  // namespace
}  // namespace glomap
