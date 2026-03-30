// File: option_manager_add_rotation_estimator_options_test_42.cc

#include <gtest/gtest.h>
#include "glomap/controllers/option_manager.h"

namespace glomap {

class OptionManagerTest_42 : public ::testing::Test {
 protected:
  // We don't rely on any internal behavior of the constructor;
  // we just need a valid instance to exercise the public methods.
  OptionManagerTest_42()
      : option_manager_(false) {}  // `add_project_options` = false for tests

  OptionManager option_manager_;
};

// Verifies that a single call to AddRotationEstimatorOptions completes
// successfully without throwing or crashing.
TEST_F(OptionManagerTest_42, AddRotationEstimatorOptions_SingleCallNoThrow_42) {
  EXPECT_NO_THROW(option_manager_.AddRotationEstimatorOptions());
}

// Verifies that AddRotationEstimatorOptions can be called multiple times
// without throwing. This exercises the idempotent guard from the interface
// perspective (repeated calls are allowed and safe).
TEST_F(OptionManagerTest_42, AddRotationEstimatorOptions_MultipleCallsNoThrow_42) {
  EXPECT_NO_THROW(option_manager_.AddRotationEstimatorOptions());
  EXPECT_NO_THROW(option_manager_.AddRotationEstimatorOptions());
}

// Verifies that AddRotationEstimatorOptions can be called, then Reset, and
// called again without observable errors (no exceptions).
TEST_F(OptionManagerTest_42, AddRotationEstimatorOptions_AfterResetNoThrow_42) {
  EXPECT_NO_THROW(option_manager_.AddRotationEstimatorOptions());

  // Reset the manager; we don't assert on internals, only that it remains usable.
  EXPECT_NO_THROW(option_manager_.Reset());

  EXPECT_NO_THROW(option_manager_.AddRotationEstimatorOptions());
}

// Verifies interaction with AddAllOptions: calling AddAllOptions first and then
// AddRotationEstimatorOptions again should still be safe and not throw.
TEST_F(OptionManagerTest_42, AddRotationEstimatorOptions_AfterAddAllOptionsNoThrow_42) {
  EXPECT_NO_THROW(option_manager_.AddAllOptions());
  EXPECT_NO_THROW(option_manager_.AddRotationEstimatorOptions());
}

}  // namespace glomap
