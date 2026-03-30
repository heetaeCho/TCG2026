// File: table/iterator_destructor_cleanup_test.cc

#include <gtest/gtest.h>
#include <vector>
#include <tuple>
#include <string>
#include <algorithm>

#include "leveldb/iterator.h"

using leveldb::Iterator;

// --- Test helpers: a tiny, black-box-friendly callback recorder ---

namespace {
struct Call {
  std::string tag;
  void* arg1;
  void* arg2;
};

static std::vector<Call> g_calls;

extern "C" {

static void SpyA(void* a1, void* a2) {
  g_calls.push_back({"A", a1, a2});
}

static void SpyB(void* a1, void* a2) {
  g_calls.push_back({"B", a1, a2});
}

static void SpyC(void* a1, void* a2) {
  g_calls.push_back({"C", a1, a2});
}

} // extern "C"

struct IteratorCleanupTest_401 : ::testing::Test {
  void SetUp() override { g_calls.clear(); }
  void TearDown() override { g_calls.clear(); }
};

// Utility: find how many calls recorded for a given tag
static int CountTag(const std::string& tag) {
  return static_cast<int>(std::count_if(g_calls.begin(), g_calls.end(),
                                        [&](const Call& c){ return c.tag == tag; }));
}

// Utility: find first call for tag
static const Call* FindFirstByTag(const std::string& tag) {
  auto it = std::find_if(g_calls.begin(), g_calls.end(),
                         [&](const Call& c){ return c.tag == tag; });
  return it == g_calls.end() ? nullptr : &(*it);
}

} // namespace

// --- Tests ---

// No cleanup handlers registered: destructor should not invoke anything.
TEST_F(IteratorCleanupTest_401, NoRegisteredCleanups_NoCallsOnDestruction_401) {
  {
    Iterator it;  // No RegisterCleanup calls.
    // Let it go out of scope to trigger destructor.
  }
  EXPECT_TRUE(g_calls.empty());
}

// Single handler: verify it is called exactly once with the exact args.
TEST_F(IteratorCleanupTest_401, SingleRegisteredCleanup_ReceivesArgsOnDestruction_401) {
  void* p1 = reinterpret_cast<void*>(0x1);
  void* p2 = reinterpret_cast<void*>(0x2);

  {
    Iterator it;
    it.RegisterCleanup(&SpyA, p1, p2);
  } // dtor triggers callbacks

  ASSERT_EQ(g_calls.size(), 1u);
  EXPECT_EQ(CountTag("A"), 1);
  const Call* c = FindFirstByTag("A");
  ASSERT_NE(c, nullptr);
  EXPECT_EQ(c->arg1, p1);
  EXPECT_EQ(c->arg2, p2);
}

// Multiple handlers: all must be invoked once each (order is *not* asserted).
TEST_F(IteratorCleanupTest_401, MultipleRegisteredCleanups_AllCalled_401) {
  void* a1 = reinterpret_cast<void*>(0x11);
  void* a2 = reinterpret_cast<void*>(0x12);
  void* b1 = reinterpret_cast<void*>(0x21);
  void* b2 = reinterpret_cast<void*>(0x22);

  {
    Iterator it;
    it.RegisterCleanup(&SpyA, a1, a2);
    it.RegisterCleanup(&SpyB, b1, b2);
  }

  ASSERT_EQ(g_calls.size(), 2u);
  EXPECT_EQ(CountTag("A"), 1);
  EXPECT_EQ(CountTag("B"), 1);

  const Call* ca = FindFirstByTag("A");
  ASSERT_NE(ca, nullptr);
  EXPECT_EQ(ca->arg1, a1);
  EXPECT_EQ(ca->arg2, a2);

  const Call* cb = FindFirstByTag("B");
  ASSERT_NE(cb, nullptr);
  EXPECT_EQ(cb->arg1, b1);
  EXPECT_EQ(cb->arg2, b2);
}

// Boundary: nullptr arguments should be passed through to the callback unchanged.
TEST_F(IteratorCleanupTest_401, NullArguments_AreForwarded_401) {
  {
    Iterator it;
    it.RegisterCleanup(&SpyC, /*arg1=*/nullptr, /*arg2=*/nullptr);
  }

  ASSERT_EQ(g_calls.size(), 1u);
  const Call* cc = FindFirstByTag("C");
  ASSERT_NE(cc, nullptr);
  EXPECT_EQ(cc->arg1, nullptr);
  EXPECT_EQ(cc->arg2, nullptr);
}
