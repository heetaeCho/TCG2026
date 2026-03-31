#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sys/stat.h>
#include <unistd.h>

// Declaration of the function under test
int ParseCgroupV1(std::string& path);

class ParseCgroupV1Test_153 : public ::testing::Test {
protected:
  std::string tmpdir_;

  void SetUp() override {
    char tmpl[] = "/tmp/cgroup_test_XXXXXX";
    char* dir = mkdtemp(tmpl);
    ASSERT_NE(dir, nullptr);
    tmpdir_ = dir;
  }

  void TearDown() override {
    // Clean up files
    unlink((tmpdir_ + "/cpu.cfs_quota_us").c_str());
    unlink((tmpdir_ + "/cpu.cfs_period_us").c_str());
    rmdir(tmpdir_.c_str());
  }

  void writeFile(const std::string& filename, const std::string& content) {
    std::ofstream ofs(filename);
    ofs << content;
    ofs.close();
  }
};

TEST_F(ParseCgroupV1Test_153, NormalQuotaAndPeriod_153) {
  writeFile(tmpdir_ + "/cpu.cfs_quota_us", "200000");
  writeFile(tmpdir_ + "/cpu.cfs_period_us", "100000");
  int result = ParseCgroupV1(tmpdir_);
  EXPECT_EQ(result, 2);
}

TEST_F(ParseCgroupV1Test_153, QuotaIsMinusOne_153) {
  writeFile(tmpdir_ + "/cpu.cfs_quota_us", "-1");
  writeFile(tmpdir_ + "/cpu.cfs_period_us", "100000");
  int result = ParseCgroupV1(tmpdir_);
  EXPECT_EQ(result, -1);
}

TEST_F(ParseCgroupV1Test_153, QuotaFileMissing_153) {
  // Don't create quota file, only period
  writeFile(tmpdir_ + "/cpu.cfs_period_us", "100000");
  int result = ParseCgroupV1(tmpdir_);
  EXPECT_EQ(result, -1);
}

TEST_F(ParseCgroupV1Test_153, PeriodFileMissing_153) {
  writeFile(tmpdir_ + "/cpu.cfs_quota_us", "200000");
  // Don't create period file
  int result = ParseCgroupV1(tmpdir_);
  EXPECT_EQ(result, -1);
}

TEST_F(ParseCgroupV1Test_153, PeriodIsZero_153) {
  writeFile(tmpdir_ + "/cpu.cfs_quota_us", "200000");
  writeFile(tmpdir_ + "/cpu.cfs_period_us", "0");
  int result = ParseCgroupV1(tmpdir_);
  EXPECT_EQ(result, -1);
}

TEST_F(ParseCgroupV1Test_153, BothFilesMissing_153) {
  int result = ParseCgroupV1(tmpdir_);
  EXPECT_EQ(result, -1);
}

TEST_F(ParseCgroupV1Test_153, QuotaLessThanPeriod_153) {
  writeFile(tmpdir_ + "/cpu.cfs_quota_us", "50000");
  writeFile(tmpdir_ + "/cpu.cfs_period_us", "100000");
  int result = ParseCgroupV1(tmpdir_);
  // 50000 / 100000 = 0 (integer division)
  EXPECT_EQ(result, 0);
}

TEST_F(ParseCgroupV1Test_153, QuotaEqualsPeriod_153) {
  writeFile(tmpdir_ + "/cpu.cfs_quota_us", "100000");
  writeFile(tmpdir_ + "/cpu.cfs_period_us", "100000");
  int result = ParseCgroupV1(tmpdir_);
  EXPECT_EQ(result, 1);
}

TEST_F(ParseCgroupV1Test_153, LargeQuota_153) {
  writeFile(tmpdir_ + "/cpu.cfs_quota_us", "800000");
  writeFile(tmpdir_ + "/cpu.cfs_period_us", "100000");
  int result = ParseCgroupV1(tmpdir_);
  EXPECT_EQ(result, 8);
}

TEST_F(ParseCgroupV1Test_153, NonExistentPath_153) {
  std::string bad_path = "/tmp/nonexistent_cgroup_path_xyz_153";
  int result = ParseCgroupV1(bad_path);
  EXPECT_EQ(result, -1);
}

TEST_F(ParseCgroupV1Test_153, QuotaFileEmpty_153) {
  writeFile(tmpdir_ + "/cpu.cfs_quota_us", "");
  writeFile(tmpdir_ + "/cpu.cfs_period_us", "100000");
  int result = ParseCgroupV1(tmpdir_);
  EXPECT_EQ(result, -1);
}

TEST_F(ParseCgroupV1Test_153, PeriodFileEmpty_153) {
  writeFile(tmpdir_ + "/cpu.cfs_quota_us", "200000");
  writeFile(tmpdir_ + "/cpu.cfs_period_us", "");
  int result = ParseCgroupV1(tmpdir_);
  EXPECT_EQ(result, -1);
}

TEST_F(ParseCgroupV1Test_153, IntegerDivisionTruncation_153) {
  writeFile(tmpdir_ + "/cpu.cfs_quota_us", "350000");
  writeFile(tmpdir_ + "/cpu.cfs_period_us", "100000");
  int result = ParseCgroupV1(tmpdir_);
  // 350000 / 100000 = 3 (integer division)
  EXPECT_EQ(result, 3);
}
