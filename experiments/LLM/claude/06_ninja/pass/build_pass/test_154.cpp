#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>

// Declaration of the function under test
int ParseCgroupV2(std::string& path);

class ParseCgroupV2Test_154 : public ::testing::Test {
protected:
    std::string temp_dir_;

    void SetUp() override {
        // Create a temporary directory for test files
        char tmpl[] = "/tmp/cgroup_test_XXXXXX";
        char* dir = mkdtemp(tmpl);
        ASSERT_NE(dir, nullptr);
        temp_dir_ = std::string(dir);
    }

    void TearDown() override {
        // Clean up the cpu.max file and temp directory
        std::string cpu_max_path = temp_dir_ + "/cpu.max";
        std::remove(cpu_max_path.c_str());
        rmdir(temp_dir_.c_str());
    }

    void WriteCpuMax(const std::string& content) {
        std::string cpu_max_path = temp_dir_ + "/cpu.max";
        std::ofstream ofs(cpu_max_path);
        ASSERT_TRUE(ofs.is_open());
        ofs << content;
        ofs.close();
    }
};

// Test: Normal case with valid quota and period
TEST_F(ParseCgroupV2Test_154, ValidQuotaAndPeriod_154) {
    WriteCpuMax("200000 100000");
    int result = ParseCgroupV2(temp_dir_);
    EXPECT_EQ(result, 2);
}

// Test: Normal case with quota equal to period (1 CPU)
TEST_F(ParseCgroupV2Test_154, QuotaEqualsPeriod_154) {
    WriteCpuMax("100000 100000");
    int result = ParseCgroupV2(temp_dir_);
    EXPECT_EQ(result, 1);
}

// Test: Quota less than period results in 0 (integer division)
TEST_F(ParseCgroupV2Test_154, QuotaLessThanPeriod_154) {
    WriteCpuMax("50000 100000");
    int result = ParseCgroupV2(temp_dir_);
    EXPECT_EQ(result, 0);
}

// Test: Large quota representing multiple CPUs
TEST_F(ParseCgroupV2Test_154, LargeQuotaMultipleCPUs_154) {
    WriteCpuMax("800000 100000");
    int result = ParseCgroupV2(temp_dir_);
    EXPECT_EQ(result, 8);
}

// Test: "max" quota means no limit, should return -1
TEST_F(ParseCgroupV2Test_154, MaxQuotaNoLimit_154) {
    WriteCpuMax("max 100000");
    int result = ParseCgroupV2(temp_dir_);
    EXPECT_EQ(result, -1);
}

// Test: File does not exist, should return -1
TEST_F(ParseCgroupV2Test_154, FileNotFound_154) {
    std::string nonexistent = "/tmp/nonexistent_cgroup_path_xyz_154";
    int result = ParseCgroupV2(nonexistent);
    EXPECT_EQ(result, -1);
}

// Test: Empty file should return -1
TEST_F(ParseCgroupV2Test_154, EmptyFile_154) {
    WriteCpuMax("");
    int result = ParseCgroupV2(temp_dir_);
    EXPECT_EQ(result, -1);
}

// Test: No space in the line should return -1
TEST_F(ParseCgroupV2Test_154, NoSpaceInLine_154) {
    WriteCpuMax("200000");
    int result = ParseCgroupV2(temp_dir_);
    EXPECT_EQ(result, -1);
}

// Test: Invalid quota string (non-numeric)
TEST_F(ParseCgroupV2Test_154, InvalidQuotaNonNumeric_154) {
    WriteCpuMax("abc 100000");
    int result = ParseCgroupV2(temp_dir_);
    EXPECT_EQ(result, -1);
}

// Test: Invalid period string (non-numeric)
TEST_F(ParseCgroupV2Test_154, InvalidPeriodNonNumeric_154) {
    WriteCpuMax("200000 abc");
    int result = ParseCgroupV2(temp_dir_);
    EXPECT_EQ(result, -1);
}

// Test: Zero quota should return -1
TEST_F(ParseCgroupV2Test_154, ZeroQuota_154) {
    WriteCpuMax("0 100000");
    int result = ParseCgroupV2(temp_dir_);
    EXPECT_EQ(result, -1);
}

// Test: Zero period should return -1
TEST_F(ParseCgroupV2Test_154, ZeroPeriod_154) {
    WriteCpuMax("200000 0");
    int result = ParseCgroupV2(temp_dir_);
    EXPECT_EQ(result, -1);
}

// Test: Negative quota should return -1
TEST_F(ParseCgroupV2Test_154, NegativeQuota_154) {
    WriteCpuMax("-100000 100000");
    int result = ParseCgroupV2(temp_dir_);
    EXPECT_EQ(result, -1);
}

// Test: Negative period should return -1
TEST_F(ParseCgroupV2Test_154, NegativePeriod_154) {
    WriteCpuMax("200000 -100000");
    int result = ParseCgroupV2(temp_dir_);
    EXPECT_EQ(result, -1);
}

// Test: Quota with trailing characters should return -1
TEST_F(ParseCgroupV2Test_154, QuotaWithTrailingChars_154) {
    WriteCpuMax("200000abc 100000");
    int result = ParseCgroupV2(temp_dir_);
    EXPECT_EQ(result, -1);
}

// Test: Period with trailing characters should return -1
TEST_F(ParseCgroupV2Test_154, PeriodWithTrailingChars_154) {
    WriteCpuMax("200000 100000abc");
    int result = ParseCgroupV2(temp_dir_);
    EXPECT_EQ(result, -1);
}

// Test: Multiple spaces - only first space is used as delimiter
TEST_F(ParseCgroupV2Test_154, MultipleSpaces_154) {
    // "200000 100000 extra" -> period_str = "100000 extra", strtoll will stop at space
    WriteCpuMax("200000 100000 extra");
    int result = ParseCgroupV2(temp_dir_);
    // period_str = "100000 extra", strtoll parses "100000" but period_end != '\0'
    EXPECT_EQ(result, -1);
}

// Test: Only a newline in the file
TEST_F(ParseCgroupV2Test_154, OnlyNewline_154) {
    WriteCpuMax("\n");
    int result = ParseCgroupV2(temp_dir_);
    EXPECT_EQ(result, -1);
}

// Test: Space at the beginning
TEST_F(ParseCgroupV2Test_154, SpaceAtBeginning_154) {
    // quota_str = "", which strtoll will fail on
    WriteCpuMax(" 200000 100000");
    int result = ParseCgroupV2(temp_dir_);
    EXPECT_EQ(result, -1);
}

// Test: Integer division truncation (e.g., 350000 / 100000 = 3)
TEST_F(ParseCgroupV2Test_154, IntegerDivisionTruncation_154) {
    WriteCpuMax("350000 100000");
    int result = ParseCgroupV2(temp_dir_);
    EXPECT_EQ(result, 3);
}

// Test: Very small quota and period (both 1)
TEST_F(ParseCgroupV2Test_154, SmallQuotaAndPeriod_154) {
    WriteCpuMax("1 1");
    int result = ParseCgroupV2(temp_dir_);
    EXPECT_EQ(result, 1);
}

// Test: Quota is 1 and period is larger
TEST_F(ParseCgroupV2Test_154, QuotaOnePeriodLarger_154) {
    WriteCpuMax("1 100000");
    int result = ParseCgroupV2(temp_dir_);
    EXPECT_EQ(result, 0);
}

// Test: Only space in the file
TEST_F(ParseCgroupV2Test_154, OnlySpace_154) {
    WriteCpuMax(" ");
    int result = ParseCgroupV2(temp_dir_);
    EXPECT_EQ(result, -1);
}
