// File: util_parse_cpu_from_cgroup_test_155.cc

#include <gtest/gtest.h>

#include <map>
#include <string>

// ---------------------------------------------------------------------
// Test seam for the collaborators used by ParseCPUFromCGroup()
// ---------------------------------------------------------------------

// Minimal stand-in type for the value of the subsystem map.
// We never inspect its internals in these tests.
struct TestCGroupSubSys_155 {};

// Shared aliases to match the observable interface of the function
// under test and its collaborators (as seen from the snippet).
using TestSubsystemMap_155 = std::map<std::string, TestCGroupSubSys_155>;
using TestCGroupMap_155    = std::map<std::string, std::string>;

// Stub state controlled from tests.
namespace {

TestSubsystemMap_155 g_subsystems_to_return_155;
TestCGroupMap_155    g_cgroups_to_return_155;

int         g_v1_result_155 = -1;
int         g_v2_result_155 = -1;
std::string g_last_v1_path_155;
std::string g_last_v2_path_155;

bool g_parse_self_cgroup_called_155  = false;
bool g_parse_mount_info_called_155   = false;

}  // namespace

// These are *test doubles* for the real functions. In the actual
// codebase, ParseCPUFromCGroup will be linked against the real
// implementations. Here, for unit-testing, we replace them with
// controllable stubs that expose only observable behavior.

TestSubsystemMap_155 ParseSelfCGroup() {
  g_parse_self_cgroup_called_155 = true;
  return g_subsystems_to_return_155;
}

TestCGroupMap_155 ParseMountInfo(TestSubsystemMap_155& subsystems) {
  g_parse_mount_info_called_155 = true;
  // We don't assert anything about |subsystems| content, only that the
  // function is invoked; ParseCPUFromCGroup treats it as an opaque map.
  (void)subsystems;
  return g_cgroups_to_return_155;
}

int ParseCgroupV1(std::string& path) {
  g_last_v1_path_155 = path;
  return g_v1_result_155;
}

int ParseCgroupV2(std::string& path) {
  g_last_v2_path_155 = path;
  return g_v2_result_155;
}

// ---------------------------------------------------------------------
// Function under test (from the given snippet).
// In the real project this lives in util.cc; here we treat it as the
// system under test and do not alter its logic.
// ---------------------------------------------------------------------

int ParseCPUFromCGroup() {
  auto subsystems = ParseSelfCGroup();
  auto cgroups = ParseMountInfo(subsystems);

  const auto cgroup2 = cgroups.find("cgroup2");
  if (cgroup2 != cgroups.end()) {
    return ParseCgroupV2(cgroup2->second);
  }

  const auto cpu = cgroups.find("cpu");
  if (cpu != cgroups.end()) {
    return ParseCgroupV1(cpu->second);
  }

  return -1;
}

// ---------------------------------------------------------------------
// Test fixture
// ---------------------------------------------------------------------

class ParseCPUFromCGroupTest_155 : public ::testing::Test {
 protected:
  void SetUp() override { ResetStubs_155(); }

  void TearDown() override { ResetStubs_155(); }

  void ResetStubs_155() {
    g_subsystems_to_return_155.clear();
    g_cgroups_to_return_155.clear();

    g_v1_result_155 = -1;
    g_v2_result_155 = -1;

    g_last_v1_path_155.clear();
    g_last_v2_path_155.clear();

    g_parse_self_cgroup_called_155 = false;
    g_parse_mount_info_called_155  = false;
  }
};

// ---------------------------------------------------------------------
// Tests
// ---------------------------------------------------------------------

// Normal case: both cgroup v1 and v2 entries exist.
// Observable behavior: v2 is preferred and v1 is never called.
TEST_F(ParseCPUFromCGroupTest_155, PreferCgroupV2WhenPresent_155) {
  // Arrange
  g_cgroups_to_return_155["cgroup2"] = "/sys/fs/cgroup/unified";
  g_cgroups_to_return_155["cpu"]     = "/sys/fs/cgroup/cpu";

  g_v2_result_155 = 4;  // e.g. 4 CPUs available
  g_v1_result_155 = 2;  // would be ignored if v2 is preferred

  // Act
  int result = ParseCPUFromCGroup();

  // Assert
  EXPECT_TRUE(g_parse_self_cgroup_called_155);
  EXPECT_TRUE(g_parse_mount_info_called_155);

  EXPECT_EQ(4, result);
  EXPECT_EQ("/sys/fs/cgroup/unified", g_last_v2_path_155);

  // Ensure v1 was not called at all.
  EXPECT_TRUE(g_last_v1_path_155.empty());
}

// Normal case: only a v1 "cpu" entry exists.
// Observable behavior: v1 is used and its result is returned.
TEST_F(ParseCPUFromCGroupTest_155, UseCgroupV1WhenOnlyCpuPresent_155) {
  // Arrange: no cgroup2 entry, only v1 "cpu".
  g_cgroups_to_return_155["cpu"] = "/sys/fs/cgroup/cpu";
  g_v1_result_155 = 8;

  // Act
  int result = ParseCPUFromCGroup();

  // Assert
  EXPECT_TRUE(g_parse_self_cgroup_called_155);
  EXPECT_TRUE(g_parse_mount_info_called_155);

  EXPECT_EQ(8, result);
  EXPECT_EQ("/sys/fs/cgroup/cpu", g_last_v1_path_155);

  // Ensure v2 was not called.
  EXPECT_TRUE(g_last_v2_path_155.empty());
}

// Error / boundary case: neither cgroup2 nor cpu entries exist.
// Observable behavior: function returns -1 to signal "no cgroup info".
TEST_F(ParseCPUFromCGroupTest_155, ReturnMinusOneWhenNoRelevantEntries_155) {
  // Arrange: empty cgroups map.
  // (values for v1/v2 stubs should not matter, they must not be used)
  g_cgroups_to_return_155.clear();
  g_v1_result_155 = 42;
  g_v2_result_155 = 42;

  // Act
  int result = ParseCPUFromCGroup();

  // Assert
  EXPECT_TRUE(g_parse_self_cgroup_called_155);
  EXPECT_TRUE(g_parse_mount_info_called_155);

  EXPECT_EQ(-1, result);  // no relevant entries -> -1
  EXPECT_TRUE(g_last_v1_path_155.empty());
  EXPECT_TRUE(g_last_v2_path_155.empty());
}

// Error propagation: cgroup v2 is present but its parser reports an error
// (e.g., invalid cpu.max content). The error value should be propagated.
TEST_F(ParseCPUFromCGroupTest_155, PropagateErrorFromCgroupV2_155) {
  // Arrange
  g_cgroups_to_return_155["cgroup2"] = "/sys/fs/cgroup/unified";
  g_v2_result_155 = -1;  // simulate failure in ParseCgroupV2

  // Act
  int result = ParseCPUFromCGroup();

  // Assert
  EXPECT_EQ(-1, result);
  EXPECT_EQ("/sys/fs/cgroup/unified", g_last_v2_path_155);
  EXPECT_TRUE(g_last_v1_path_155.empty());  // v1 must not be called
}

// Error propagation: only v1 "cpu" entry exists, but ParseCgroupV1
// reports an error. The error value should be returned.
TEST_F(ParseCPUFromCGroupTest_155, PropagateErrorFromCgroupV1_155) {
  // Arrange
  g_cgroups_to_return_155["cpu"] = "/sys/fs/cgroup/cpu";
  g_v1_result_155 = -1;  // simulate failure in ParseCgroupV1

  // Act
  int result = ParseCPUFromCGroup();

  // Assert
  EXPECT_EQ(-1, result);
  EXPECT_EQ("/sys/fs/cgroup/cpu", g_last_v1_path_155);
  EXPECT_TRUE(g_last_v2_path_155.empty());
}
