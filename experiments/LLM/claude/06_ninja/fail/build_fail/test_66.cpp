#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "graph.h"
#include "build_log.h"
#include "deps_log.h"
#include "state.h"
#include "disk_interface.h"
#include "test.h"

class DependencyScanSetBuildLogTest_66 : public ::testing::Test {
 protected:
  void SetUp() override {
    state_.Reset();
  }

  State state_;
  VirtualFileSystem fs_;
  DepfileParserOptions depfile_parser_options_;
};

TEST_F(DependencyScanSetBuildLogTest_66, SetBuildLogChangesLog_66) {
  BuildLog log1;
  BuildLog log2;

  DependencyScan scan(&state_, &log1, nullptr, &fs_,
                      &depfile_parser_options_, nullptr);

  // Initially build_log should be log1
  EXPECT_EQ(&log1, scan.build_log());

  // After set_build_log, it should be log2
  scan.set_build_log(&log2);
  EXPECT_EQ(&log2, scan.build_log());
}

TEST_F(DependencyScanSetBuildLogTest_66, SetBuildLogToNull_66) {
  BuildLog log1;

  DependencyScan scan(&state_, &log1, nullptr, &fs_,
                      &depfile_parser_options_, nullptr);

  EXPECT_EQ(&log1, scan.build_log());

  // Set to nullptr
  scan.set_build_log(nullptr);
  EXPECT_EQ(nullptr, scan.build_log());
}

TEST_F(DependencyScanSetBuildLogTest_66, SetBuildLogMultipleTimes_66) {
  BuildLog log1;
  BuildLog log2;
  BuildLog log3;

  DependencyScan scan(&state_, &log1, nullptr, &fs_,
                      &depfile_parser_options_, nullptr);

  EXPECT_EQ(&log1, scan.build_log());

  scan.set_build_log(&log2);
  EXPECT_EQ(&log2, scan.build_log());

  scan.set_build_log(&log3);
  EXPECT_EQ(&log3, scan.build_log());

  scan.set_build_log(&log1);
  EXPECT_EQ(&log1, scan.build_log());
}

TEST_F(DependencyScanSetBuildLogTest_66, SetBuildLogToSameValue_66) {
  BuildLog log1;

  DependencyScan scan(&state_, &log1, nullptr, &fs_,
                      &depfile_parser_options_, nullptr);

  EXPECT_EQ(&log1, scan.build_log());

  // Setting to the same log should still work
  scan.set_build_log(&log1);
  EXPECT_EQ(&log1, scan.build_log());
}

TEST_F(DependencyScanSetBuildLogTest_66, InitialBuildLogMatchesConstructor_66) {
  BuildLog log;

  DependencyScan scan(&state_, &log, nullptr, &fs_,
                      &depfile_parser_options_, nullptr);

  EXPECT_EQ(&log, scan.build_log());
}

TEST_F(DependencyScanSetBuildLogTest_66, InitialBuildLogNullFromConstructor_66) {
  DependencyScan scan(&state_, nullptr, nullptr, &fs_,
                      &depfile_parser_options_, nullptr);

  EXPECT_EQ(nullptr, scan.build_log());

  BuildLog log;
  scan.set_build_log(&log);
  EXPECT_EQ(&log, scan.build_log());
}

TEST_F(DependencyScanSetBuildLogTest_66, SetBuildLogFromNullToValidAndBack_66) {
  DependencyScan scan(&state_, nullptr, nullptr, &fs_,
                      &depfile_parser_options_, nullptr);

  EXPECT_EQ(nullptr, scan.build_log());

  BuildLog log;
  scan.set_build_log(&log);
  EXPECT_EQ(&log, scan.build_log());

  scan.set_build_log(nullptr);
  EXPECT_EQ(nullptr, scan.build_log());
}
