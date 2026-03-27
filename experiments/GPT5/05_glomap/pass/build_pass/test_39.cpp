// File: option_manager_add_global_mapper_resume_full_options_test_39.cc

#include <gtest/gtest.h>

#include "glomap/controllers/option_manager.h"

namespace glomap {

class OptionManagerTest_39 : public ::testing::Test {
 protected:
  // Two variants to cover both constructor paths.
  OptionManager manager_without_project_options_{false};
  OptionManager manager_with_project_options_{true};
};

//------------------------------------------------------------------------------
// Normal operation: single call should succeed without throwing.
//------------------------------------------------------------------------------
TEST_F(OptionManagerTest_39,
       AddGlobalMapperResumeFullOptionsDoesNotThrow_39) {
  EXPECT_NO_THROW(manager_without_project_options_.AddGlobalMapperResumeFullOptions());
}

//------------------------------------------------------------------------------
// Boundary / robustness: multiple calls should be safe (no crashes/throws).
// This also implicitly checks that repeated registration of related options
// does not lead to observable failures at this level.
//------------------------------------------------------------------------------
TEST_F(OptionManagerTest_39,
       AddGlobalMapperResumeFullOptionsMultipleCallsSafe_39) {
  EXPECT_NO_THROW({
    manager_without_project_options_.AddGlobalMapperResumeFullOptions();
    manager_without_project_options_.AddGlobalMapperResumeFullOptions();
  });
}

//------------------------------------------------------------------------------
// Integration with Parse: using only these options, parsing a minimal argv
// should not throw (constructor without project options).
//------------------------------------------------------------------------------
TEST_F(OptionManagerTest_39,
       AddGlobalMapperResumeFullOptionsIntegratesWithParseWithoutProjectOptions_39) {
  manager_without_project_options_.AddGlobalMapperResumeFullOptions();

  const char* argv[] = {"program_name"};
  const int argc = 1;

  EXPECT_NO_THROW(manager_without_project_options_.Parse(argc,
                                                         const_cast<char**>(argv)));
}

//------------------------------------------------------------------------------
// Integration with Parse: when project options are enabled via constructor,
// adding these options and then parsing should still behave normally.
//------------------------------------------------------------------------------
TEST_F(OptionManagerTest_39,
       AddGlobalMapperResumeFullOptionsIntegratesWithParseWithProjectOptions_39) {
  manager_with_project_options_.AddGlobalMapperResumeFullOptions();

  const char* argv[] = {"program_name"};
  const int argc = 1;

  EXPECT_NO_THROW(manager_with_project_options_.Parse(argc,
                                                      const_cast<char**>(argv)));
}

}  // namespace glomap
