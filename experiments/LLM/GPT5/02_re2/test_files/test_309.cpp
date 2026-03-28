// File: ./TestProjects/re2/re2/tests/compiler_addsuffixrecursive_test.cc
#include <gtest/gtest.h>
#include "re2/compile.cc"  // or the appropriate header that exposes re2::Compiler API
#include "re2/prog.h"

namespace re2 {

class AddSuffixRecursiveTest_309 : public ::testing::Test {
protected:
  // Fresh compiler per test.
  Compiler c_;
};

// [Normal] Non-overlapping ranges -> expect a *different* root returned (an alt node can be created internally).
TEST_F(AddSuffixRecursiveTest_309, NonOverlappingRangeCreatesAlternative_309) {
  // root covers ' ' (0x20)
  Frag root = c_.ByteRange(0x20, 0x20, /*foldcase=*/false);

  // id represents a suffix for 'A' (0x41), disjoint from root
  // next = 0 (terminal) is acceptable as per typical RE2 graphs.
  int id = c_.UncachedRuneByteSuffix(/*lo=*/0x41, /*hi=*/0x41, /*foldcase=*/false, /*next=*/0);

  // Act
  int result_root = c_.AddSuffixRecursive(root.begin, id);

  // Assert: must be non-zero and (very importantly) allowed to differ from the original root
  // if the compiler had to create an alternate path for the new suffix.
  ASSERT_NE(result_root, 0);
  EXPECT_NE(result_root, static_cast<int>(root.begin));
}

// [Normal] Overlapping ranges -> expect to reuse/extend existing path (often same root comes back).
TEST_F(AddSuffixRecursiveTest_309, OverlappingRangeReusesExisting_309) {
  // root covers 'A' (0x41)
  Frag root = c_.ByteRange(0x41, 0x41, /*foldcase=*/false);

  // id also covers 'A' (0x41) so it overlaps with root.
  int id = c_.UncachedRuneByteSuffix(/*lo=*/0x41, /*hi=*/0x41, /*foldcase=*/false, /*next=*/0);

  int result_root = c_.AddSuffixRecursive(root.begin, id);

  // In an overlapping case, returning the original root is a valid and expected behavior.
  // We don't assert stronger structure since internal layout is a black box.
  ASSERT_NE(result_root, 0);
  EXPECT_EQ(result_root, static_cast<int>(root.begin));
}

// [Boundary] Cached suffix input: ensure the call succeeds (non-zero) regardless of caching.
TEST_F(AddSuffixRecursiveTest_309, AcceptsCachedSuffixId_309) {
  Frag root = c_.ByteRange(0x30, 0x39, /*foldcase=*/false); // '0'..'9'

  // Create a cached suffix node for '5'
  int cached_id = c_.CachedRuneByteSuffix(/*lo=*/0x35, /*hi=*/0x35, /*foldcase=*/false, /*next=*/0);
  ASSERT_TRUE(c_.IsCachedRuneByteSuffix(cached_id));

  int result_root = c_.AddSuffixRecursive(root.begin, cached_id);

  // Observable guarantee we can rely on: the function should succeed and return a valid root id.
  ASSERT_NE(result_root, 0);
}

// [Boundary] Uncached suffix input: ensure the call also succeeds (non-zero).
TEST_F(AddSuffixRecursiveTest_309, AcceptsUncachedSuffixId_309) {
  Frag root = c_.ByteRange(0x61, 0x7A, /*foldcase=*/false); // 'a'..'z'

  // Create an uncached suffix node for 'm'
  int uncached_id = c_.UncachedRuneByteSuffix(/*lo=*/0x6D, /*hi=*/0x6D, /*foldcase=*/false, /*next=*/0);
  ASSERT_FALSE(c_.IsCachedRuneByteSuffix(uncached_id));

  int result_root = c_.AddSuffixRecursive(root.begin, uncached_id);

  ASSERT_NE(result_root, 0);
}

} // namespace re2
