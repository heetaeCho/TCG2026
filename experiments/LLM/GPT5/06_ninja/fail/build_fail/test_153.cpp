// File: ./TestProjects/ninja/tests/parse_cgroup_v1_test_153.cc

#include "util.h"

#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <string>

class ParseCgroupV1Test_153 : public ::testing::Test {
 protected:
  void SetUp() override {
    path_ = ".";
    CleanupFiles();
  }

  void TearDown() override { CleanupFiles(); }

  void WriteFile(const std::string& filename, const std::string& contents) {
    std::ofstream ofs(filename.c_str(), std::ios::trunc);
    ASSERT_TRUE(ofs.is_open());
    ofs << contents;
  }

  void CleanupFiles() {
    std::remove("./cpu.cfs_quota_us");
    std::remove("./cpu.cfs_period_us");
  }

  std::string path_;
};

// Normal operation: valid quota and period -> integer division result.
TEST_F(ParseCgroupV1Test_153, ValidQuotaAndPeriod_ReturnsIntegerDivision_153) {
  WriteFile("./cpu.cfs_quota_us", "200000\n");
  WriteFile("./cpu.cfs_period_us", "100000\n");

  int result = ParseCgroupV1(path_);

  EXPECT_EQ(2, result);
}

// Boundary: quota smaller than period -> result can be zero.
TEST_F(ParseCgroupV1Test_153, ValidQuotaLessThanPeriod_ReturnsZero_153) {
  WriteFile("./cpu.cfs_quota_us", "50000\n");
  WriteFile("./cpu.cfs_period_us", "100000\n");

  int result = ParseCgroupV1(path_);

  EXPECT_EQ(0, result);
}

// Error case: quota read fails (e.g., missing file) -> returns -1.
TEST_F(ParseCgroupV1Test_153, MissingQuotaFile_ReturnsMinusOne_153) {
  // Ensure quota file is missing; period may or may not exist,
  // but the function should fail before using it.
  std::remove("./cpu.cfs_quota_us");
  WriteFile("./cpu.cfs_period_us", "100000\n");

  int result = ParseCgroupV1(path_);

  EXPECT_EQ(-1, result);
}

// Error case: quota explicitly -1 (unlimited) -> returns -1.
TEST_F(ParseCgroupV1Test_153, QuotaUnlimitedMinusOne_ReturnsMinusOne_153) {
  WriteFile("./cpu.cfs_quota_us", "-1\n");
  WriteFile("./cpu.cfs_period_us", "100000\n");

  int result = ParseCgroupV1(path_);

  EXPECT_EQ(-1, result);
}

// Error case: quota parses OK, but period read fails -> returns -1.
TEST_F(ParseCgroupV1Test_153, MissingPeriodFileAfterValidQuota_ReturnsMinusOne_153) {
  WriteFile("./cpu.cfs_quota_us", "200000\n");
  std::remove("./cpu.cfs_period_us");  // ensure failure for period

  int result = ParseCgroupV1(path_);

  EXPECT_EQ(-1, result);
}

// Error case: period == 0 after successful reads -> returns -1.
TEST_F(ParseCgroupV1Test_153, ZeroPeriodAfterValidQuota_ReturnsMinusOne_153) {
  WriteFile("./cpu.cfs_quota_us", "200000\n");
  WriteFile("./cpu.cfs_period_us", "0\n");

  int result = ParseCgroupV1(path_);

  EXPECT_EQ(-1, result);
}

// Error case: non-numeric quota content -> treated as read/parse failure -> returns -1.
TEST_F(ParseCgroupV1Test_153, NonNumericQuotaContent_ReturnsMinusOne_153) {
  WriteFile("./cpu.cfs_quota_us", "not_a_number\n");
  WriteFile("./cpu.cfs_period_us", "100000\n");

  int result = ParseCgroupV1(path_);

  EXPECT_EQ(-1, result);
}
