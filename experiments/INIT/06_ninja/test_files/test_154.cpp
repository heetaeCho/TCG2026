// File: ./TestProjects/ninja/src/util_cgroup_v2_test.cc

#include "gtest/gtest.h"
#include "util.h"

#include <fstream>
#include <string>
#include <cstdio>

class ParseCgroupV2Test_154 : public ::testing::Test {
protected:
  std::string dir_;

  void SetUp() override {
    dir_ = ::testing::TempDir();
    RemoveCpuMax();
  }

  std::string CpuMaxPath() const {
    std::string path = dir_;
    if (!path.empty() && path.back() != '/' && path.back() != '\\') {
#ifdef _WIN32
      path.push_back('\\');
#else
      path.push_back('/');
#endif
    }
    path += "cpu.max";
    return path;
  }

  void WriteCpuMax(const std::string& line) {
    std::ofstream ofs(CpuMaxPath().c_str(), std::ios::trunc);
    ASSERT_TRUE(ofs.is_open());
    ofs << line;
  }

  void RemoveCpuMax() {
    std::remove(CpuMaxPath().c_str());
  }
};

// Normal operation: valid quota and period => integer division result.
TEST_F(ParseCgroupV2Test_154, ValidQuotaAndPeriod_ReturnsIntegerRatio_154) {
  WriteCpuMax("100000 10000");  // 100000 / 10000 = 10

  int result = ParseCgroupV2(dir_);

  EXPECT_EQ(10, result);
}

// Error: cpu.max file does not exist.
TEST_F(ParseCgroupV2Test_154, MissingCpuMaxFile_ReturnsMinusOne_154) {
  RemoveCpuMax();

  int result = ParseCgroupV2(dir_);

  EXPECT_EQ(-1, result);
}

// Error: cpu.max file is empty.
TEST_F(ParseCgroupV2Test_154, EmptyCpuMaxFile_ReturnsMinusOne_154) {
  WriteCpuMax("");

  int result = ParseCgroupV2(dir_);

  EXPECT_EQ(-1, result);
}

// Error: line without space separator.
TEST_F(ParseCgroupV2Test_154, NoSpaceSeparatorInLine_ReturnsMinusOne_154) {
  WriteCpuMax("100000");  // Missing period value

  int result = ParseCgroupV2(dir_);

  EXPECT_EQ(-1, result);
}

// Error: quota set to "max" means no CPU limit.
TEST_F(ParseCgroupV2Test_154, MaxQuotaMeansNoLimit_ReturnsMinusOne_154) {
  WriteCpuMax("max 10000");

  int result = ParseCgroupV2(dir_);

  EXPECT_EQ(-1, result);
}

// Error: non-numeric quota.
TEST_F(ParseCgroupV2Test_154, NonNumericQuota_ReturnsMinusOne_154) {
  WriteCpuMax("notanumber 10000");

  int result = ParseCgroupV2(dir_);

  EXPECT_EQ(-1, result);
}

// Error: non-numeric period.
TEST_F(ParseCgroupV2Test_154, NonNumericPeriod_ReturnsMinusOne_154) {
  WriteCpuMax("100000 notanumber");

  int result = ParseCgroupV2(dir_);

  EXPECT_EQ(-1, result);
}

// Boundary: non-positive quota (0 or negative) should fail.
TEST_F(ParseCgroupV2Test_154, NonPositiveQuota_ReturnsMinusOne_154) {
  WriteCpuMax("0 10000");
  EXPECT_EQ(-1, ParseCgroupV2(dir_));

  WriteCpuMax("-100 10000");
  EXPECT_EQ(-1, ParseCgroupV2(dir_));
}

// Boundary: non-positive period (0 or negative) should fail.
TEST_F(ParseCgroupV2Test_154, NonPositivePeriod_ReturnsMinusOne_154) {
  WriteCpuMax("100000 0");
  EXPECT_EQ(-1, ParseCgroupV2(dir_));

  WriteCpuMax("100000 -100");
  EXPECT_EQ(-1, ParseCgroupV2(dir_));
}
