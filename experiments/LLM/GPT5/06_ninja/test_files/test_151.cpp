// File: ./TestProjects/ninja/src/util_parse_mountinfo_test.cc

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "util.h"  // Assumed to declare ParseMountInfo, CGroupSubSys, etc.

using ::testing::EndsWith;

namespace {

class ParseMountInfoTest_151 : public ::testing::Test {
 protected:
  // Helper: check if /proc/self/mountinfo is available on this system.
  static bool HasMountInfoFile() {
    std::ifstream mountinfo("/proc/self/mountinfo");
    return mountinfo.is_open();
  }

  // Helper: quick & dirty check if there is any cgroup2 mount.
  // This does *not* reimplement MountPoint::parse; it just scans raw text.
  static bool HasCgroup2Mount() {
    std::ifstream mountinfo("/proc/self/mountinfo");
    if (!mountinfo.is_open())
      return false;

    std::string line;
    while (std::getline(mountinfo, line)) {
      if (line.find(" - cgroup2 ") != std::string::npos)
        return true;
    }
    return false;
  }
};

// ---------------------------------------------------------------------------
// Basic behavior
// ---------------------------------------------------------------------------

// When there are no subsystems configured, ParseMountInfo cannot
// produce any mappings regardless of mountinfo contents.
TEST_F(ParseMountInfoTest_151, EmptySubsystems_ReturnsEmpty_151) {
  std::map<std::string, CGroupSubSys> subsystems;
  const auto result = ParseMountInfo(subsystems);
  EXPECT_TRUE(result.empty());
}

// If /proc/self/mountinfo cannot be opened (e.g., non-Linux platform),
// ParseMountInfo is expected to return an empty map.
TEST_F(ParseMountInfoTest_151, MissingMountInfoFile_ReturnsEmpty_151) {
  if (HasMountInfoFile()) {
    GTEST_SKIP() << "/proc/self/mountinfo exists on this system; "
                    "cannot verify missing-file behavior.";
  }

  std::map<std::string, CGroupSubSys> subsystems;
  CGroupSubSys cpu;
  cpu.id = 1;
  cpu.name = "cpu";
  subsystems.emplace("cpu", cpu);

  const auto result = ParseMountInfo(subsystems);
  EXPECT_TRUE(result.empty());
}

// Subsystems that are very unlikely to exist in the mountinfo
// should result in an empty map. This checks that ParseMountInfo
// does not magically create entries not present in the mountinfo.
TEST_F(ParseMountInfoTest_151, NonMatchingSubsystems_ReturnEmpty_151) {
  if (!HasMountInfoFile()) {
    GTEST_SKIP() << "/proc/self/mountinfo is not available; "
                    "system does not support this test.";
  }

  std::map<std::string, CGroupSubSys> subsystems;

  CGroupSubSys bogus;
  bogus.id = 42;
  bogus.name = "this_subsystem_name_should_not_exist_151";
  subsystems.emplace(bogus.name, bogus);

  const auto result = ParseMountInfo(subsystems);

  // On any sane system, this should be empty, because there is no such
  // subsystem in the mountinfo super options.
  EXPECT_TRUE(result.empty());
}

// ---------------------------------------------------------------------------
// cgroup v1 behavior
// ---------------------------------------------------------------------------

// When a known cgroup v1 subsystem (like "cpu") is mounted and we provide
// a matching entry in the subsystems map, ParseMountInfo should return
// a non-empty path for that subsystem.
//
// The test is skipped if the system does not have a v1 "cpu" cgroup mount.
TEST_F(ParseMountInfoTest_151, CgroupV1Subsystem_MappedWhenPresent_151) {
  if (!HasMountInfoFile()) {
    GTEST_SKIP() << "/proc/self/mountinfo is not available; "
                    "system does not support this test.";
  }

  std::map<std::string, CGroupSubSys> subsystems;

  CGroupSubSys cpu;
  cpu.id = 2;          // The exact id is not important for ParseMountInfo.
  cpu.name = "cpu";    // Key and name usually match for v1 subsystems.
  subsystems.emplace("cpu", cpu);

  const auto result = ParseMountInfo(subsystems);
  auto it = result.find("cpu");
  if (it == result.end()) {
    GTEST_SKIP() << "No v1 'cpu' cgroup mount found on this system; "
                    "skipping behavior-check.";
  }

  EXPECT_FALSE(it->second.empty());
  EXPECT_EQ("cpu", it->first);
}

// ---------------------------------------------------------------------------
// cgroup v2 behavior
// ---------------------------------------------------------------------------

// If the cgroup v2 aggregator entry (key == "" and id == 0) is NOT present
// in the subsystems map, ParseMountInfo must *not* insert any "cgroup2"
// entry, even if there are cgroup2 mounts in the system.
TEST_F(ParseMountInfoTest_151, Cgroup2AggregatorMissing_NoCgroup2Entry_151) {
  if (!HasMountInfoFile()) {
    GTEST_SKIP() << "/proc/self/mountinfo is not available; "
                    "system does not support this test.";
  }

  std::map<std::string, CGroupSubSys> subsystems;

  // Some arbitrary subsystem that should not affect cgroup2 behavior.
  CGroupSubSys dummy;
  dummy.id = 1;
  dummy.name = "dummy";
  subsystems.emplace("dummy", dummy);

  const auto result = ParseMountInfo(subsystems);

  // Regardless of whether there are cgroup2 mounts, the function should
  // never create a "cgroup2" entry without an aggregator entry in the map.
  EXPECT_EQ(0u, result.count("cgroup2"));
}

// When the cgroup v2 aggregator entry is present in the subsystems map
// (key == "" and id == 0), and the system has at least one cgroup2 mount,
// ParseMountInfo should produce a "cgroup2" entry with a non-empty path.
TEST_F(ParseMountInfoTest_151, Cgroup2AggregatorPresent_ProducesEntry_151) {
  if (!HasMountInfoFile() || !HasCgroup2Mount()) {
    GTEST_SKIP() << "System does not appear to have a cgroup2 mount; "
                    "skipping cgroup2 behavior test.";
  }

  std::map<std::string, CGroupSubSys> subsystems;

  CGroupSubSys agg;
  agg.id = 0;
  agg.name = "/";   // Root of the cgroup v2 hierarchy.
  subsystems.emplace("", agg);

  const auto result = ParseMountInfo(subsystems);
  auto it = result.find("cgroup2");
  ASSERT_NE(it, result.end()) << "Expected a cgroup2 entry when aggregator is present.";

  EXPECT_FALSE(it->second.empty());
  EXPECT_EQ("cgroup2", it->first);
  // Path should be an absolute path.
  EXPECT_EQ('/', it->second.front());
}

// If the cgroup v2 aggregator entry has a non-root name, ParseMountInfo
// should append that name to the mount point path it discovers for cgroup2.
TEST_F(ParseMountInfoTest_151, Cgroup2Aggregator_WithName_AppendsToPath_151) {
  if (!HasMountInfoFile() || !HasCgroup2Mount()) {
    GTEST_SKIP() << "System does not appear to have a cgroup2 mount; "
                    "skipping cgroup2 behavior test.";
  }

  std::map<std::string, CGroupSubSys> subsystems;

  CGroupSubSys agg;
  agg.id = 0;
  agg.name = "/test_cgroup2_suffix_151";
  subsystems.emplace("", agg);

  const auto result = ParseMountInfo(subsystems);
  auto it = result.find("cgroup2");
  if (it == result.end()) {
    GTEST_SKIP() << "cgroup2 mount not discovered; skipping suffix behavior check.";
  }

  EXPECT_THAT(it->second, EndsWith("/test_cgroup2_suffix_151"));
}

}  // namespace
