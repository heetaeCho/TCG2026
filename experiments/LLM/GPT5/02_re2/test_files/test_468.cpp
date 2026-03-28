// File: ./TestProjects/re2/re2/prefilter_tree_hash_test_468.cc

#include "re2/prefilter_tree.h"
#include "re2/prefilter.h"

#include <gtest/gtest.h>
#include <unordered_set>
#include <unordered_map>

// If ABSL_DCHECK expands to a debug assertion/LOG(FATAL), we can use death tests.
#include "absl/base/attributes.h"  // for ABSL_DCHECK (included indirectly by prefilter_tree.h in most setups)
#include "absl/base/config.h"

namespace re2 {

class PrefilterHashTest_468 : public ::testing::Test {};

TEST_F(PrefilterHashTest_468, ConsistentForSamePointer_468) {
  // Construct a Prefilter with some Op value; we do not assume any specific semantics.
  Prefilter p(static_cast<Prefilter::Op>(0));

  PrefilterTree::PrefilterHash hasher;
  const Prefilter* ptr = &p;

  size_t h1 = hasher(ptr);
  size_t h2 = hasher(ptr);

  // Hashing the same pointer (same underlying object) should be consistent.
  EXPECT_EQ(h1, h2);
}

TEST_F(PrefilterHashTest_468, WorksInUnorderedSetWithPointerEquality_468) {
  Prefilter a(static_cast<Prefilter::Op>(0));
  Prefilter b(static_cast<Prefilter::Op>(1));  // Different object; no assumptions about internal equality.

  std::unordered_set<const Prefilter*, PrefilterTree::PrefilterHash> set;
  set.insert(&a);
  set.insert(&b);

  // Distinct pointers should be tracked as distinct keys regardless of their hash values.
  EXPECT_EQ(set.count(&a), 1u);
  EXPECT_EQ(set.count(&b), 1u);
  EXPECT_EQ(set.size(), 2u);
}

TEST_F(PrefilterHashTest_468, WorksInUnorderedMapLookup_468) {
  Prefilter p(static_cast<Prefilter::Op>(0));
  std::unordered_map<const Prefilter*, int, PrefilterTree::PrefilterHash> map;

  map[&p] = 1234;

  // Lookup by the same pointer should succeed.
  auto it = map.find(&p);
  ASSERT_NE(it, map.end());
  EXPECT_EQ(it->second, 1234);
}

#ifndef NDEBUG
// In debug builds, ABSL_DCHECK(a != NULL) is expected to fire.
// We use a death test to verify the observable behavior (program terminates).
TEST_F(PrefilterHashTest_468, DCHECKsOnNullptrInDebug_468) {
  PrefilterTree::PrefilterHash hasher;
  const Prefilter* null_ptr = nullptr;

  // Death test: expect the process to terminate when hashing nullptr.
  // We don't assert on the exact message, just that it dies.
#if GTEST_HAS_DEATH_TEST
  EXPECT_DEATH({ (void)hasher(null_ptr); }, "");
#else
  GTEST_SKIP() << "Death tests not supported on this platform/config.";
#endif
}
#else
// In release builds, ABSL_DCHECK may be compiled out. We cannot rely on any
// specific observable behavior, so we document and skip.
TEST_F(PrefilterHashTest_468, SkipNullptrCheckInRelease_468) {
  GTEST_SKIP() << "ABSL_DCHECK is disabled in release; nullptr behavior is undefined/not asserted.";
}
#endif

}  // namespace re2
