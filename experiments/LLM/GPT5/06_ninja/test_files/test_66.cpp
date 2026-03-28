// File: ./TestProjects/ninja/tests/dependency_scan_build_log_test_66.cc

#include "gtest/gtest.h"

#include "graph.h"       // DependencyScan
#include "build_log.h"   // BuildLog

// If your project normally needs additional headers for these types
// (State, DepsLog, DiskInterface, DepfileParserOptions, Explanations)
// they should already be pulled in via "graph.h" in the real codebase.

class DependencyScanTest_66 : public ::testing::Test {
protected:
  BuildLog build_log1_;
  BuildLog build_log2_;
};

// Normal operation: constructor should expose the initial BuildLog*
// via build_log().
TEST_F(DependencyScanTest_66, ConstructorSetsInitialBuildLog_66) {
  DependencyScan scan(
      /*state=*/nullptr,
      /*build_log=*/&build_log1_,
      /*deps_log=*/nullptr,
      /*disk_interface=*/nullptr,
      /*depfile_parser_options=*/nullptr,
      /*explanations=*/nullptr);

  EXPECT_EQ(&build_log1_, scan.build_log());
}

// Normal operation: set_build_log should update the BuildLog*
// returned by build_log().
TEST_F(DependencyScanTest_66, SetBuildLogUpdatesReturnedPointer_66) {
  DependencyScan scan(
      /*state=*/nullptr,
      /*build_log=*/&build_log1_,
      /*deps_log=*/nullptr,
      /*disk_interface=*/nullptr,
      /*depfile_parser_options=*/nullptr,
      /*explanations=*/nullptr);

  // Precondition: initially returns the BuildLog* given to the ctor.
  EXPECT_EQ(&build_log1_, scan.build_log());

  // After calling set_build_log, build_log() should reflect the new value.
  scan.set_build_log(&build_log2_);
  EXPECT_EQ(&build_log2_, scan.build_log());
}

// Boundary case: setting the BuildLog* to nullptr should be observable
// through build_log() (if the interface allows nullptr).
TEST_F(DependencyScanTest_66, SetBuildLogToNull_66) {
  DependencyScan scan(
      /*state=*/nullptr,
      /*build_log=*/&build_log1_,
      /*deps_log=*/nullptr,
      /*disk_interface=*/nullptr,
      /*depfile_parser_options=*/nullptr,
      /*explanations=*/nullptr);

  // Ensure we start from a non-null pointer.
  ASSERT_NE(nullptr, scan.build_log());

  // Set to nullptr and verify the observable behavior.
  scan.set_build_log(nullptr);
  EXPECT_EQ(nullptr, scan.build_log());
}
