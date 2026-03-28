// File: re2_named_capturing_groups_test.cc
#include <gtest/gtest.h>
#include <thread>
#include <vector>
#include <set>
#include "re2/re2.h"

using re2::RE2;

class RE2_NamedCapturingGroupsTest_250 : public ::testing::Test {};

// 1) No named groups → empty map.
TEST_F(RE2_NamedCapturingGroupsTest_250, ReturnsEmptyWhenNoNamedGroups_250) {
  RE2 re("^(a)(b)(?:c)$");  // only numbered + non-capturing
  const auto& m = re.NamedCapturingGroups();
  EXPECT_TRUE(m.empty());
}

// 2) Named groups → correct name→index mapping (indices start at 1).
TEST_F(RE2_NamedCapturingGroupsTest_250, MapsNamesToIndices_250) {
  RE2 re("^(?P<first>a)(?P<second>b)$");

  const auto& m = re.NamedCapturingGroups();
  ASSERT_EQ(m.size(), 2u);

  // Expect names are present and mapped to capture indices.
  auto it1 = m.find("first");
  auto it2 = m.find("second");
  ASSERT_NE(it1, m.end());
  ASSERT_NE(it2, m.end());

  // The first group in the pattern is index 1, the second is index 2.
  EXPECT_EQ(it1->second, 1);
  EXPECT_EQ(it2->second, 2);
}

// 3) Caching/consistency: subsequent calls return the same reference.
TEST_F(RE2_NamedCapturingGroupsTest_250, ReturnsSameReferenceAcrossCalls_250) {
  RE2 re("(?P<x>a)(?P<y>b)");
  const auto& m1 = re.NamedCapturingGroups();
  const auto& m2 = re.NamedCapturingGroups();

  // Reference identity (addresses should match).
  EXPECT_EQ(&m1, &m2);

  // And contents remain consistent.
  EXPECT_EQ(m1, m2);
}

// 4) Thread safety: many concurrent reads see the same mapping and reference.
TEST_F(RE2_NamedCapturingGroupsTest_250, ThreadSafety_ConcurrentAccess_250) {
  RE2 re("^(?P<alpha>a)(b)(?P<bravo>c)$");
  const size_t kThreads = 16;

  // Launch threads that all grab the reference and record its address and size.
  std::vector<std::thread> threads;
  std::vector<const std::map<std::string,int>*> ptrs(kThreads, nullptr);
  std::vector<size_t> sizes(kThreads, 0);

  for (size_t i = 0; i < kThreads; ++i) {
    threads.emplace_back([&, i] {
      const auto& m = re.NamedCapturingGroups();
      ptrs[i] = &m;
      sizes[i] = m.size();
      // Also verify expected keys/values in each thread.
      auto a = m.find("alpha");
      auto b = m.find("bravo");
      ASSERT_NE(a, m.end());
      ASSERT_NE(b, m.end());
      // Positions: alpha is first capturing group (index 1), (b) is second (index 2),
      // bravo is third (index 3). We only assert named ones we can observe.
      EXPECT_EQ(a->second, 1);
      EXPECT_EQ(b->second, 3);
    });
  }
  for (auto& t : threads) t.join();

  // All threads should see the SAME reference (same address).
  std::set<const std::map<std::string,int>*> uniq(ptrs.begin(), ptrs.end());
  EXPECT_EQ(uniq.size(), 1u);

  // All threads should see the same size (2 named groups).
  for (size_t i = 0; i < kThreads; ++i) {
    EXPECT_EQ(sizes[i], 2u) << "mismatched size at thread " << i;
  }
}

// 5) Different objects with same pattern → equal contents (not relying on identity).
TEST_F(RE2_NamedCapturingGroupsTest_250, EqualContentsForSamePatternDifferentObjects_250) {
  RE2 re1("(?P<k1>a)(?P<k2>b)");
  RE2 re2("(?P<k1>a)(?P<k2>b)");

  const auto& m1 = re1.NamedCapturingGroups();
  const auto& m2 = re2.NamedCapturingGroups();

  EXPECT_EQ(m1, m2);
  // Not asserting address equality here because they are different objects.
}
