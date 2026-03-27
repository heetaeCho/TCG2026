// File: version_set_newestfirst_test_147.cc
#include <gtest/gtest.h>
#include <algorithm>
#include <cstdint>
#include <vector>

#include "db/version_edit.h"  // for leveldb::FileMetaData

namespace {

// Small helper to create FileMetaData with a specific number (other fields unused by tests)
static leveldb::FileMetaData* MakeMeta(uint64_t num) {
  auto* m = new leveldb::FileMetaData();
  m->number = num;
  return m;
}

// Ensure all allocated FileMetaData are cleaned up in each test
struct MetaGuard {
  std::vector<leveldb::FileMetaData*> all;
  ~MetaGuard() {
    for (auto* p : all) delete p;
  }
  leveldb::FileMetaData* add(uint64_t n) {
    auto* p = MakeMeta(n);
    all.push_back(p);
    return p;
  }
};

}  // namespace

namespace leveldb {
  // The function under test lives in db/version_set.cc
  // We declare it here to use it as a comparator without relying on any internals.
  extern bool NewestFirst(FileMetaData* a, FileMetaData* b);
}  // namespace leveldb

// Normal operation: first newer than second -> true
TEST(NewestFirstTest_147, ReturnsTrueWhenFirstHasGreaterNumber_147) {
  MetaGuard g;
  auto* a = g.add(20);
  auto* b = g.add(10);

  EXPECT_TRUE(leveldb::NewestFirst(a, b));
}

// Normal operation: first older than second -> false
TEST(NewestFirstTest_147, ReturnsFalseWhenFirstHasSmallerNumber_147) {
  MetaGuard g;
  auto* a = g.add(7);
  auto* b = g.add(42);

  EXPECT_FALSE(leveldb::NewestFirst(a, b));
}

// Boundary condition: equal numbers -> false (strict comparator should not say a < a)
TEST(NewestFirstTest_147, ReturnsFalseWhenNumbersAreEqual_147) {
  MetaGuard g;
  auto* a = g.add(123);
  auto* b = g.add(123);

  EXPECT_FALSE(leveldb::NewestFirst(a, b));
  EXPECT_FALSE(leveldb::NewestFirst(b, a));
}

// Observable effect with std::sort: results ordered by descending number
TEST(NewestFirstTest_147, SortsInDescendingOrderWithStdSort_147) {
  MetaGuard g;
  auto* m1 = g.add(3);
  auto* m2 = g.add(10);
  auto* m3 = g.add(7);

  std::vector<leveldb::FileMetaData*> v = {m1, m2, m3};
  std::sort(v.begin(), v.end(), leveldb::NewestFirst);

  ASSERT_EQ(v.size(), 3u);
  EXPECT_EQ(v[0]->number, 10u);
  EXPECT_EQ(v[1]->number, 7u);
  EXPECT_EQ(v[2]->number, 3u);
}

// Boundary condition: near uint64_t limits
TEST(NewestFirstTest_147, HandlesUint64MaxBoundary_147) {
  MetaGuard g;
  const uint64_t max = std::numeric_limits<uint64_t>::max();
  auto* a = g.add(max);
  auto* b = g.add(max - 1);

  EXPECT_TRUE(leveldb::NewestFirst(a, b));
  EXPECT_FALSE(leveldb::NewestFirst(b, a));
}

// Comparator properties: antisymmetry & transitivity (observable via outcomes)
TEST(NewestFirstTest_147, SatisfiesStrictWeakOrderingAsUsed_147) {
  MetaGuard g;
  auto* a = g.add(30);
  auto* b = g.add(20);
  auto* c = g.add(10);

  // Antisymmetry-like behavior for strict comparator
  EXPECT_TRUE(leveldb::NewestFirst(a, b));
  EXPECT_FALSE(leveldb::NewestFirst(b, a));

  // Transitivity as exercised via sorting
  std::vector<leveldb::FileMetaData*> v = {b, c, a};
  std::sort(v.begin(), v.end(), leveldb::NewestFirst);
  EXPECT_EQ(v[0]->number, 30u);
  EXPECT_EQ(v[1]->number, 20u);
  EXPECT_EQ(v[2]->number, 10u);
}
