// grealloc_test.cpp
// Unit tests for grealloc (./TestProjects/poppler/goo/gmem.h)

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>

// Include the header that defines grealloc/gfree.
#include "TestProjects/poppler/goo/gmem.h"

namespace {

class GreallocTest_11 : public ::testing::Test {};

TEST_F(GreallocTest_11, MallocWhenNullPointer_11) {
  void* p = grealloc(nullptr, 64);
  ASSERT_NE(p, nullptr);

  // Basic usability check: memory is writable.
  std::memset(p, 0xAB, 64);

  gfree(p);
}

TEST_F(GreallocTest_11, ReallocGrowPreservesPrefix_11) {
  constexpr std::size_t kOldSize = 32;
  constexpr std::size_t kNewSize = 128;

  void* p = grealloc(nullptr, kOldSize);
  ASSERT_NE(p, nullptr);

  // Fill with a recognizable pattern.
  std::memset(p, 0x5A, kOldSize);

  void* q = grealloc(p, kNewSize);
  ASSERT_NE(q, nullptr);

  // realloc contract: previous contents preserved up to min(old,new).
  for (std::size_t i = 0; i < kOldSize; ++i) {
    EXPECT_EQ(static_cast<unsigned char*>(q)[i], static_cast<unsigned char>(0x5A));
  }

  gfree(q);
}

TEST_F(GreallocTest_11, ReallocShrinkKeepsPrefix_11) {
  constexpr std::size_t kOldSize = 128;
  constexpr std::size_t kNewSize = 16;

  void* p = grealloc(nullptr, kOldSize);
  ASSERT_NE(p, nullptr);

  std::memset(p, 0xC3, kOldSize);

  void* q = grealloc(p, kNewSize);
  ASSERT_NE(q, nullptr);

  for (std::size_t i = 0; i < kNewSize; ++i) {
    EXPECT_EQ(static_cast<unsigned char*>(q)[i], static_cast<unsigned char>(0xC3));
  }

  gfree(q);
}

TEST_F(GreallocTest_11, SizeZeroFreesAndReturnsNull_11) {
  void* p = grealloc(nullptr, 32);
  ASSERT_NE(p, nullptr);

  void* q = grealloc(p, 0);  // should free and return nullptr
  EXPECT_EQ(q, nullptr);

  // No further use of p/q (freed); test is that it returns nullptr and does not crash.
}

TEST_F(GreallocTest_11, SizeZeroWithNullPointerReturnsNull_11) {
  void* q = grealloc(nullptr, 0);
  EXPECT_EQ(q, nullptr);
}

TEST_F(GreallocTest_11, CheckOverflowTrueReturnsNullOnAllocationFailure_11) {
  // Use a size that should reliably fail.
  const std::size_t huge = std::numeric_limits<std::size_t>::max();
  void* p = grealloc(nullptr, huge, /*checkoverflow=*/true);
  EXPECT_EQ(p, nullptr);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(GreallocTest_11, CheckOverflowFalseAbortsOnAllocationFailure_11) {
  const std::size_t huge = std::numeric_limits<std::size_t>::max();

  // Expect the process to abort; also match the emitted error text.
  ASSERT_DEATH(
      {
        (void)grealloc(nullptr, huge, /*checkoverflow=*/false);
      },
      "Out of memory");
}
#endif

}  // namespace