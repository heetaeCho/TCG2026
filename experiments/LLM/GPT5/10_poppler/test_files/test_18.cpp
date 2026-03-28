// File: copyString_test_18.cpp
// Unit tests for inline copyString() in ./TestProjects/poppler/goo/gmem.h

#include <gtest/gtest.h>

#include <cstddef>
#include <cstring>
#include <cstdlib>
#include <string>

// Include the header under test (contains inline copyString).
#include "./TestProjects/poppler/goo/gmem.h"

// --- Test seam for external allocator dependency (gmalloc) ---
// copyString() calls: gmalloc(n + 1, false)
// We provide a test definition of gmalloc to observe parameters and control failures.

namespace {
struct GmallocSpy {
  size_t last_size = 0;
  bool last_flag = true;
  int call_count = 0;

  bool return_null = false;  // force failure
} g_spy;
}  // namespace

extern "C" void* gmalloc(size_t size, bool flag) {
  g_spy.last_size = size;
  g_spy.last_flag = flag;
  g_spy.call_count++;

  if (g_spy.return_null) return nullptr;
  return std::malloc(size);
}

class CopyStringTest_18 : public ::testing::Test {
 protected:
  void SetUp() override {
    g_spy = {};
  }
};

TEST_F(CopyStringTest_18, CopiesExactLengthAndNullTerminates_18) {
  const char* s = "hello";
  const size_t n = 5;

  char* r = copyString(s, n);

  ASSERT_NE(r, nullptr);
  EXPECT_EQ(g_spy.call_count, 1);
  EXPECT_EQ(g_spy.last_size, n + 1);
  EXPECT_FALSE(g_spy.last_flag);  // copyString passes false
  EXPECT_STREQ(r, "hello");
  EXPECT_EQ(r[n], '\0');  // explicit terminator at position n

  std::free(r);
}

TEST_F(CopyStringTest_18, CopiesPrefixWhenNIsShorterThanSource_18) {
  const char* s = "hello";
  const size_t n = 2;

  char* r = copyString(s, n);

  ASSERT_NE(r, nullptr);
  EXPECT_EQ(g_spy.last_size, n + 1);
  EXPECT_FALSE(g_spy.last_flag);
  EXPECT_STREQ(r, "he");
  EXPECT_EQ(r[n], '\0');

  std::free(r);
}

TEST_F(CopyStringTest_18, PadsWithNullsWhenSourceShorterThanN_18) {
  const char* s = "hi";
  const size_t n = 5;

  char* r = copyString(s, n);

  ASSERT_NE(r, nullptr);
  EXPECT_EQ(g_spy.last_size, n + 1);
  EXPECT_FALSE(g_spy.last_flag);

  // "hi" then '\0' padding; and r[n] must be '\0'.
  EXPECT_EQ(r[0], 'h');
  EXPECT_EQ(r[1], 'i');
  EXPECT_EQ(r[2], '\0');
  EXPECT_EQ(r[3], '\0');
  EXPECT_EQ(r[4], '\0');
  EXPECT_EQ(r[5], '\0');

  // As a C-string, it should read as "hi".
  EXPECT_STREQ(r, "hi");

  std::free(r);
}

TEST_F(CopyStringTest_18, HandlesZeroLengthRequest_18) {
  const char* s = "ignored";
  const size_t n = 0;

  char* r = copyString(s, n);

  ASSERT_NE(r, nullptr);
  EXPECT_EQ(g_spy.last_size, 1u);
  EXPECT_FALSE(g_spy.last_flag);
  EXPECT_STREQ(r, "");
  EXPECT_EQ(r[0], '\0');

  std::free(r);
}

TEST_F(CopyStringTest_18, PreservesEmbeddedNullBehaviorOfStrncpy_18) {
  // Source contains an embedded '\0'. strncpy should stop copying visible chars
  // and pad remaining up to n with '\0's.
  const char s[] = {'a', 'b', '\0', 'c', 'd', '\0'};
  const size_t n = 5;

  char* r = copyString(s, n);

  ASSERT_NE(r, nullptr);
  EXPECT_EQ(g_spy.last_size, n + 1);
  EXPECT_FALSE(g_spy.last_flag);

  EXPECT_EQ(r[0], 'a');
  EXPECT_EQ(r[1], 'b');
  EXPECT_EQ(r[2], '\0');
  EXPECT_EQ(r[3], '\0');
  EXPECT_EQ(r[4], '\0');
  EXPECT_EQ(r[5], '\0');  // explicit terminator

  // As a C-string, it should read as "ab".
  EXPECT_STREQ(r, "ab");

  std::free(r);
}

TEST_F(CopyStringTest_18, DeathWhenAllocatorReturnsNull_18) {
  // Observable exceptional case: if gmalloc returns nullptr, copyString
  // dereferences it (r[n] = '\0'), which should crash.
  g_spy.return_null = true;

  const char* s = "x";
  const size_t n = 1;

  ASSERT_DEATH(
      {
        (void)copyString(s, n);
      },
      ".*");
}