#include <gtest/gtest.h>

#include "glomap/controllers/option_manager.h"

namespace {

class OptionManagerTest_37 : public ::testing::Test {
 protected:
  OptionManagerTest_37()
      : manager_with_project_options_(true),
        manager_without_project_options_(false) {}

  // One instance created with project options enabled.
  glomap::OptionManager manager_with_project_options_;
  // One instance created with project options disabled.
  glomap::OptionManager manager_without_project_options_;
};

// Verifies that AddGlobalMapperFullOptions can be called without throwing
// when the OptionManager is constructed without project options.
TEST_F(OptionManagerTest_37, AddGlobalMapperFullOptions_NoThrowWithoutProjectOptions_37) {
  EXPECT_NO_THROW(manager_without_project_options_.AddGlobalMapperFullOptions());
}

// Verifies that AddGlobalMapperFullOptions can be called without throwing
// when the OptionManager is constructed with project options.
TEST_F(OptionManagerTest_37, AddGlobalMapperFullOptions_NoThrowWithProjectOptions_37) {
  EXPECT_NO_THROW(manager_with_project_options_.AddGlobalMapperFullOptions());
}

// Verifies that AddGlobalMapperFullOptions can be called multiple times
// (boundary / repeated use) without throwing.
TEST_F(OptionManagerTest_37, AddGlobalMapperFullOptions_MultipleCallsDoNotThrow_37) {
  EXPECT_NO_THROW({
    manager_without_project_options_.AddGlobalMapperFullOptions();
    manager_without_project_options_.AddGlobalMapperFullOptions();
  });
}

// Verifies that AddGlobalMapperFullOptions can be safely combined with
// individual option-adding functions before and after the call, without errors.
// This indirectly checks that internal delegation does not conflict with
// separate calls to the same underlying methods.
TEST_F(OptionManagerTest_37, AddGlobalMapperFullOptions_ComposesWithOtherOptionCalls_37) {
  EXPECT_NO_THROW({
    manager_without_project_options_.AddGlobalMapperOptions();
    manager_without_project_options_.AddViewGraphCalibrationOptions();
    manager_without_project_options_.AddGlobalMapperFullOptions();
    manager_without_project_options_.AddRelativePoseEstimationOptions();
    manager_without_project_options_.AddRotationEstimatorOptions();
    manager_without_project_options_.AddTrackEstablishmentOptions();
    manager_without_project_options_.AddGlobalPositionerOptions();
    manager_without_project_options_.AddBundleAdjusterOptions();
    manager_without_project_options_.AddTriangulatorOptions();
    manager_without_project_options_.AddInlierThresholdOptions();
  });
}

// Verifies that AddGlobalMapperFullOptions works correctly together with
// Parse and ResetOptions, covering normal usage combined with other public
// APIs and a reset boundary.
TEST_F(OptionManagerTest_37, AddGlobalMapperFullOptions_ParseAndResetIntegration_37) {
  int argc = 1;
  const char* argv_raw[] = {"program"};
  // Parse expects a non-const char**.
  char** argv = const_cast<char**>(argv_raw);

  EXPECT_NO_THROW({
    manager_without_project_options_.AddGlobalMapperFullOptions();
    manager_without_project_options_.Parse(argc, argv);
    manager_without_project_options_.ResetOptions(true);
    manager_without_project_options_.AddGlobalMapperFullOptions();
    manager_without_project_options_.Parse(argc, argv);
  });
}

}  // namespace
