// File: ./TestProjects/ninja/tests/parse_self_cgroup_test_152.cc

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "util.h"  // Declares ParseSelfCGroup() and CGroupSubSys

using std::map;
using std::string;
using std::vector;

class ParseSelfCGroupTest_152 : public ::testing::Test {};

// This test focuses on the core contract of ParseSelfCGroup:
// every key in the returned map must be one of the subsystem
// names stored inside the associated CGroupSubSys instance.
TEST_F(ParseSelfCGroupTest_152, KeysMatchOneOfSubsystems_152) {
  map<string, CGroupSubSys> result = ParseSelfCGroup();

  for (const auto& entry : result) {
    const string& key = entry.first;
    const CGroupSubSys& subsys = entry.second;

    // subsystems vector should not be empty for any mapped entry
    EXPECT_FALSE(subsys.subsystems.empty())
        << "CGroupSubSys for key '" << key << "' has no subsystems";

    // The map key should be one of the subsystem names
    bool found = false;
    for (const auto& name : subsys.subsystems) {
      if (name == key) {
        found = true;
        break;
      }
    }
    EXPECT_TRUE(found) << "Key '" << key
                       << "' was not found in its CGroupSubSys.subsystems";
  }
}

// This test checks that ParseSelfCGroup can be called multiple times and that
// the overall mapping (at least in terms of size and keys) is consistent
// between calls, assuming /proc/self/cgroup does not change during the test.
TEST_F(ParseSelfCGroupTest_152, ConsecutiveCallsProduceConsistentKeys_152) {
  map<string, CGroupSubSys> first = ParseSelfCGroup();
  map<string, CGroupSubSys> second = ParseSelfCGroup();

  // The number of entries should be stable between two immediate calls.
  EXPECT_EQ(first.size(), second.size());

  // Every key from the first result should also be present in the second.
  for (const auto& entry : first) {
    const string& key = entry.first;
    auto it = second.find(key);
    EXPECT_NE(it, second.end()) << "Key '" << key
                                << "' from first call is missing in second call";
  }
}

// This test verifies basic sanity properties of the returned CGroupSubSys
// objects: if any entry exists, its "name" field must not be empty, and its
// subsystem list should not contain empty strings.
TEST_F(ParseSelfCGroupTest_152, ReturnedEntriesHaveSaneFields_152) {
  map<string, CGroupSubSys> result = ParseSelfCGroup();

  for (const auto& entry : result) {
    const string& key = entry.first;
    const CGroupSubSys& subsys = entry.second;

    // If we have an entry for a subsystem, its name should be non-empty.
    EXPECT_FALSE(subsys.name.empty())
        << "CGroupSubSys name is empty for key '" << key << "'";

    // All subsystem strings should be non-empty.
    for (const auto& s : subsys.subsystems) {
      EXPECT_FALSE(s.empty())
          << "Empty subsystem string found for key '" << key << "'";
    }
  }
}
