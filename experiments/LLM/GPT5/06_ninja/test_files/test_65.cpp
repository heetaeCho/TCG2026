// File: ./TestProjects/ninja/tests/dependency_scan_build_log_test_65.cc

#include "graph.h"
#include "build_log.h"
#include "deps_log.h"

#include "gtest/gtest.h"

// Simple fixture for DependencyScan tests focused on build_log / deps_log.
class DependencyScanTest_65 : public ::testing::Test {};

// Helper to construct a DependencyScan with minimal setup.
// We only care about the BuildLog* and DepsLog* parameters here,
// so the other collaborators can safely be nullptr.
static DependencyScan MakeScan(BuildLog* build_log, DepsLog* deps_log) {
  return DependencyScan(
      /*state=*/nullptr,
      /*build_log=*/build_log,
      /*deps_log=*/deps_log,
      /*disk_interface=*/nullptr,
      /*depfile_parser_options=*/nullptr,
      /*explanations=*/nullptr);
}

// --- build_log() / set_build_log() tests ---

// Normal case: build_log() returns the BuildLog* passed to the constructor.
TEST_F(DependencyScanTest_65, BuildLogInitiallyMatchesConstructorArgument_65) {
  BuildLog build_log;
  DependencyScan scan = MakeScan(&build_log, /*deps_log=*/nullptr);

  EXPECT_EQ(&build_log, scan.build_log());
}

// Normal case: set_build_log() changes what build_log() returns.
TEST_F(DependencyScanTest_65, SetBuildLogUpdatesGetter_65) {
  BuildLog build_log1;
  BuildLog build_log2;

  DependencyScan scan = MakeScan(&build_log1, /*deps_log=*/nullptr);
  ASSERT_EQ(&build_log1, scan.build_log());

  scan.set_build_log(&build_log2);

  EXPECT_EQ(&build_log2, scan.build_log());
}

// Boundary case: set_build_log(nullptr) makes build_log() return nullptr.
TEST_F(DependencyScanTest_65, SetBuildLogToNull_65) {
  BuildLog build_log;

  DependencyScan scan = MakeScan(&build_log, /*deps_log=*/nullptr);
  ASSERT_NE(nullptr, scan.build_log());

  scan.set_build_log(nullptr);

  EXPECT_EQ(nullptr, scan.build_log());
}

// --- deps_log() tests ---

// Normal case: deps_log() returns the DepsLog* passed to the constructor.
TEST_F(DependencyScanTest_65, DepsLogInitiallyMatchesConstructorArgument_65) {
  DepsLog deps_log;
  DependencyScan scan = MakeScan(/*build_log=*/nullptr, &deps_log);

  EXPECT_EQ(&deps_log, scan.deps_log());
}

// Boundary case: constructing with deps_log == nullptr makes deps_log() return nullptr.
TEST_F(DependencyScanTest_65, DepsLogNullWhenConstructedWithNull_65) {
  DependencyScan scan = MakeScan(/*build_log=*/nullptr, /*deps_log=*/nullptr);

  EXPECT_EQ(nullptr, scan.deps_log());
}

// Interaction: changing build_log via set_build_log() must not affect deps_log().
TEST_F(DependencyScanTest_65, SetBuildLogDoesNotAffectDepsLog_65) {
  BuildLog build_log1;
  BuildLog build_log2;
  DepsLog deps_log;

  DependencyScan scan = MakeScan(&build_log1, &deps_log);
  ASSERT_EQ(&build_log1, scan.build_log());
  ASSERT_EQ(&deps_log, scan.deps_log());

  scan.set_build_log(&build_log2);

  EXPECT_EQ(&build_log2, scan.build_log());
  EXPECT_EQ(&deps_log, scan.deps_log());
}
