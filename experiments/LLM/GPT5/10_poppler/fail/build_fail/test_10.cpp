// File: gmem_gmalloc_checkoverflow_test.cpp
// Unit tests for: inline void *gmalloc_checkoverflow(size_t size) { return gmalloc(size, true); }

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <limits>
#include <new>

#if __has_include("goo/gmem.h")
#include "goo/gmem.h"
#elif __has_include("./TestProjects/poppler/goo/gmem.h")
#include "./TestProjects/poppler/goo/gmem.h"
#else
#include "gmem.h"
#endif

// --- Test seam for external collaborator: gmalloc(size_t, bool) ---
// We do NOT re-implement poppler's logic; we only capture observable interaction.
namespace {
struct GmallocSpy {
  static inline size_t lastSize = 0;
  static inline bool lastCheckOverflow = false;
  static inline int callCount = 0;

  static inline void* nextReturn = reinterpret_cast<void*>(0x1);

  static inline bool shouldThrow = false;
  static inline bool throwBadAlloc = false;

  static void Reset() {
    lastSize = 0;
    lastCheckOverflow = false;
    callCount = 0;
    nextReturn = reinterpret_cast<void*>(0x1);
    shouldThrow = false;
    throwBadAlloc = false;
  }
};
}  // namespace

// Provide a definition for gmalloc that matches the declaration from gmem.h.
// If the signature differs in your codebase, this will fail to compile, which is correct.
void* gmalloc(size_t size, bool checkoverflow) {
  GmallocSpy::callCount++;
  GmallocSpy::lastSize = size;
  GmallocSpy::lastCheckOverflow = checkoverflow;

  if (GmallocSpy::shouldThrow) {
    if (GmallocSpy::throwBadAlloc) {
      throw std::bad_alloc{};
    }
    throw std::runtime_error("gmalloc test exception");
  }
  return GmallocSpy::nextReturn;
}

class GmallocCheckOverflowTest_10 : public ::testing::Test {
 protected:
  void SetUp() override { GmallocSpy::Reset(); }
};

// Normal operation: forwards args and returns exactly what gmalloc returns.
TEST_F(GmallocCheckOverflowTest_10, ForwardsSizeAndSetsOverflowCheckTrue_10) {
  void* expected = reinterpret_cast<void*>(0x1234);
  GmallocSpy::nextReturn = expected;

  void* out = gmalloc_checkoverflow(static_cast<size_t>(42));

  EXPECT_EQ(GmallocSpy::callCount, 1);
  EXPECT_EQ(GmallocSpy::lastSize, static_cast<size_t>(42));
  EXPECT_TRUE(GmallocSpy::lastCheckOverflow);
  EXPECT_EQ(out, expected);
}

// Boundary: size == 0 should still forward and request overflow checking.
TEST_F(GmallocCheckOverflowTest_10, SizeZeroIsForwarded_10) {
  void* expected = reinterpret_cast<void*>(0xBEEF);
  GmallocSpy::nextReturn = expected;

  void* out = gmalloc_checkoverflow(static_cast<size_t>(0));

  EXPECT_EQ(GmallocSpy::callCount, 1);
  EXPECT_EQ(GmallocSpy::lastSize, static_cast<size_t>(0));
  EXPECT_TRUE(GmallocSpy::lastCheckOverflow);
  EXPECT_EQ(out, expected);
}

// Boundary: very large size should still be forwarded as-is (wrapper behavior).
TEST_F(GmallocCheckOverflowTest_10, MaxSizeIsForwarded_10) {
  const size_t kMax = (std::numeric_limits<size_t>::max)();
  void* expected = reinterpret_cast<void*>(0xDEAD);
  GmallocSpy::nextReturn = expected;

  void* out = gmalloc_checkoverflow(kMax);

  EXPECT_EQ(GmallocSpy::callCount, 1);
  EXPECT_EQ(GmallocSpy::lastSize, kMax);
  EXPECT_TRUE(GmallocSpy::lastCheckOverflow);
  EXPECT_EQ(out, expected);
}

// Error/exceptional: if underlying allocator throws, wrapper should not swallow it.
TEST_F(GmallocCheckOverflowTest_10, PropagatesExceptionsFromGmalloc_10) {
  GmallocSpy::shouldThrow = true;
  GmallocSpy::throwBadAlloc = true;

  EXPECT_THROW({ (void)gmalloc_checkoverflow(static_cast<size_t>(16)); }, std::bad_alloc);

  EXPECT_EQ(GmallocSpy::callCount, 1);
  EXPECT_EQ(GmallocSpy::lastSize, static_cast<size_t>(16));
  EXPECT_TRUE(GmallocSpy::lastCheckOverflow);
}