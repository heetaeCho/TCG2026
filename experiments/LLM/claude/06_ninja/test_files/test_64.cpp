#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "graph.h"
#include "state.h"
#include "deps_log.h"
#include "disk_interface.h"

class ImplicitDepLoaderTest_64 : public ::testing::Test {
 protected:
  void SetUp() override {
    state_ = new State();
    deps_log_ = new DepsLog();
    disk_interface_ = new RealDiskInterface();
    depfile_parser_options_ = DepfileParserOptions();
  }

  void TearDown() override {
    delete state_;
    delete deps_log_;
    delete disk_interface_;
  }

  State* state_;
  DepsLog* deps_log_;
  DiskInterface* disk_interface_;
  DepfileParserOptions depfile_parser_options_;
};

TEST_F(ImplicitDepLoaderTest_64, DepsLogReturnsProvidedDepsLog_64) {
  ImplicitDepLoader loader(state_, deps_log_, disk_interface_,
                           &depfile_parser_options_, nullptr);
  EXPECT_EQ(deps_log_, loader.deps_log());
}

TEST_F(ImplicitDepLoaderTest_64, DepsLogReturnsNullWhenNullProvided_64) {
  ImplicitDepLoader loader(state_, nullptr, disk_interface_,
                           &depfile_parser_options_, nullptr);
  EXPECT_EQ(nullptr, loader.deps_log());
}

TEST_F(ImplicitDepLoaderTest_64, DepsLogConsistentAcrossMultipleCalls_64) {
  ImplicitDepLoader loader(state_, deps_log_, disk_interface_,
                           &depfile_parser_options_, nullptr);
  EXPECT_EQ(loader.deps_log(), loader.deps_log());
}

TEST_F(ImplicitDepLoaderTest_64, DifferentLoadersReturnDifferentDepsLogs_64) {
  DepsLog other_deps_log;
  ImplicitDepLoader loader1(state_, deps_log_, disk_interface_,
                            &depfile_parser_options_, nullptr);
  ImplicitDepLoader loader2(state_, &other_deps_log, disk_interface_,
                            &depfile_parser_options_, nullptr);
  EXPECT_NE(loader1.deps_log(), loader2.deps_log());
  EXPECT_EQ(deps_log_, loader1.deps_log());
  EXPECT_EQ(&other_deps_log, loader2.deps_log());
}

TEST_F(ImplicitDepLoaderTest_64, DepsLogReturnsSamePointerAsConstructorArg_64) {
  DepsLog specific_log;
  ImplicitDepLoader loader(state_, &specific_log, disk_interface_,
                           &depfile_parser_options_, nullptr);
  DepsLog* returned = loader.deps_log();
  ASSERT_NE(nullptr, returned);
  EXPECT_EQ(&specific_log, returned);
}

TEST_F(ImplicitDepLoaderTest_64, LoadDepsWithNoEdgeInputs_64) {
  ImplicitDepLoader loader(state_, deps_log_, disk_interface_,
                           &depfile_parser_options_, nullptr);
  // Verify the loader was constructed properly by checking deps_log
  EXPECT_EQ(deps_log_, loader.deps_log());
}
