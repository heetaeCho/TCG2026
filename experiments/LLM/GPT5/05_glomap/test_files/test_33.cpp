// File: option_manager_addalloptions_test_33.cc

#include <gtest/gtest.h>

#include "glomap/controllers/option_manager.h"

namespace glomap {

class OptionManagerTest_33 : public ::testing::Test {
 protected:
  void SetUp() override {
    manager_with_project_.reset(new OptionManager(/*add_project_options=*/true));
    manager_without_project_.reset(new OptionManager(/*add_project_options=*/false));
  }

  std::unique_ptr<OptionManager> manager_with_project_;
  std::unique_ptr<OptionManager> manager_without_project_;
};

// Verifies that AddAllOptions can be called without throwing for a typical
// OptionManager instance constructed with project options enabled.
TEST_F(OptionManagerTest_33, AddAllOptions_NoThrow_WithProjectOptions_33) {
  ASSERT_NE(manager_with_project_, nullptr);

  EXPECT_NO_THROW({
    manager_with_project_->AddAllOptions();
  });
}

// Verifies that AddAllOptions can be called without throwing for an
// OptionManager instance constructed with project options disabled.
// This covers a different construction mode.
TEST_F(OptionManagerTest_33, AddAllOptions_NoThrow_WithoutProjectOptions_33) {
  ASSERT_NE(manager_without_project_, nullptr);

  EXPECT_NO_THROW({
    manager_without_project_->AddAllOptions();
  });
}

// Verifies that AddAllOptions can be called multiple times on the same
// instance without throwing. This checks that the method is at least
// idempotent with respect to observable failures (crash/throw).
TEST_F(OptionManagerTest_33, AddAllOptions_CalledTwice_NoThrow_33) {
  ASSERT_NE(manager_with_project_, nullptr);

  EXPECT_NO_THROW({
    manager_with_project_->AddAllOptions();
    manager_with_project_->AddAllOptions();
  });
}

// Verifies that AddAllOptions can be safely combined with ResetOptions.
// This exercises interaction between configuration registration and reset.
TEST_F(OptionManagerTest_33, AddAllOptions_ThenResetOptions_NoThrow_33) {
  ASSERT_NE(manager_with_project_, nullptr);

  EXPECT_NO_THROW({
    manager_with_project_->AddAllOptions();
    // reset_paths = true: exercise the branch where paths may be reset.
    manager_with_project_->ResetOptions(/*reset_paths=*/true);
  });

  // After reset, AddAllOptions should still be callable safely.
  EXPECT_NO_THROW({
    manager_with_project_->AddAllOptions();
  });
}

// Verifies that AddAllOptions can be called before parsing command line
// arguments and that Parse can be executed without throwing afterwards.
TEST_F(OptionManagerTest_33, AddAllOptions_BeforeParse_NoThrow_33) {
  ASSERT_NE(manager_with_project_, nullptr);

  // Minimal argc/argv setup for Parse.
  const char* argv[] = {"program_name"};
  int argc = static_cast<int>(sizeof(argv) / sizeof(argv[0]));

  EXPECT_NO_THROW({
    manager_with_project_->AddAllOptions();
    manager_with_project_->Parse(argc, const_cast<char**>(argv));
  });
}

// Verifies that Parse can be called before AddAllOptions and that
// AddAllOptions still does not throw afterward. This checks that the
// order of calls does not cause observable failures.
TEST_F(OptionManagerTest_33, Parse_BeforeAddAllOptions_NoThrow_33) {
  ASSERT_NE(manager_without_project_, nullptr);

  const char* argv[] = {"program_name"};
  int argc = static_cast<int>(sizeof(argv) / sizeof(argv[0]));

  EXPECT_NO_THROW({
    manager_without_project_->Parse(argc, const_cast<char**>(argv));
    manager_without_project_->AddAllOptions();
  });
}

}  // namespace glomap
