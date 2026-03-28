// File: option_manager_reset_test_49.cc

#include <gtest/gtest.h>

#include "glomap/controllers/option_manager.h"

namespace glomap {

class OptionManagerTest_49 : public ::testing::Test {
 protected:
  // One instance constructed with project options enabled.
  OptionManager manager_with_project_{true};

  // One instance constructed with project options disabled.
  OptionManager manager_without_project_{false};
};

// ----------------------------------------------------------------------
// Reset on a freshly constructed manager (with project options)
// should be callable without throwing.
// ----------------------------------------------------------------------
TEST_F(OptionManagerTest_49, ResetOnFreshManagerWithProjectDoesNotThrow_49) {
  EXPECT_NO_THROW(manager_with_project_.Reset());
}

// ----------------------------------------------------------------------
// Reset on a freshly constructed manager (without project options)
// should be callable without throwing.
// ----------------------------------------------------------------------
TEST_F(OptionManagerTest_49, ResetOnFreshManagerWithoutProjectDoesNotThrow_49) {
  EXPECT_NO_THROW(manager_without_project_.Reset());
}

// ----------------------------------------------------------------------
// Calling Reset after adding various options should not throw.
// This checks that Reset can safely be used after typical setup.
// ----------------------------------------------------------------------
TEST_F(OptionManagerTest_49, ResetAfterAddingOptionsDoesNotThrow_49) {
  // We treat all these calls as black-box interactions.
  // The goal is only to ensure that Reset can be called afterward.
  EXPECT_NO_THROW(manager_with_project_.AddDatabaseOptions());
  EXPECT_NO_THROW(manager_with_project_.AddImageOptions());
  EXPECT_NO_THROW(manager_with_project_.AddGlobalMapperOptions());
  EXPECT_NO_THROW(manager_with_project_.AddTrackEstablishmentOptions());
  EXPECT_NO_THROW(manager_with_project_.AddGlobalPositionerOptions());
  EXPECT_NO_THROW(manager_with_project_.AddBundleAdjusterOptions());
  EXPECT_NO_THROW(manager_with_project_.AddTriangulatorOptions());
  EXPECT_NO_THROW(manager_with_project_.AddInlierThresholdOptions());
  EXPECT_NO_THROW(manager_with_project_.AddGravityRefinerOptions());

  EXPECT_NO_THROW(manager_with_project_.Reset());
}

// ----------------------------------------------------------------------
// Calling Reset multiple times in a row should be safe and not throw.
// This exercises idempotent / repeated usage of Reset.
// ----------------------------------------------------------------------
TEST_F(OptionManagerTest_49, MultipleConsecutiveResetsDoNotThrow_49) {
  EXPECT_NO_THROW(manager_with_project_.Reset());
  EXPECT_NO_THROW(manager_with_project_.Reset());
  EXPECT_NO_THROW(manager_with_project_.Reset());
}

// ----------------------------------------------------------------------
// Reset should also be usable after calling AddAllOptions, which is
// likely to register many sub-option groups. This ensures Reset can
// handle a "fully-configured" manager.
// ----------------------------------------------------------------------
TEST_F(OptionManagerTest_49, ResetAfterAddAllOptionsDoesNotThrow_49) {
  EXPECT_NO_THROW(manager_with_project_.AddAllOptions());
  EXPECT_NO_THROW(manager_with_project_.Reset());
}

}  // namespace glomap
