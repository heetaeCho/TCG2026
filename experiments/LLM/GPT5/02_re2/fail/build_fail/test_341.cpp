// File: regexp_concat_test_341.cc
#include "gtest/gtest.h"
#include "re2/regexp.h"

using re2::Regexp;
using re2::RegexpOp;
using re2::kRegexpConcat;

namespace re2 {
// ---- Link-time stub & probes for the private static method ----
// These globals capture the most recent call for verification.
namespace {
bool g_called = false;
RegexpOp g_last_op = static_cast<RegexpOp>(0);
Regexp** g_last_subs = nullptr;
int g_last_nsubs = -1;
Regexp::ParseFlags g_last_flags = static_cast<Regexp::ParseFlags>(0);
bool g_last_can_factor = true;  // initialize to true so tests catch false properly
Regexp* g_return_value = nullptr;

// Definition for the private static method inside Regexp.
// We DO NOT implement internal logic; we only record inputs and
// return a controllable sentinel. This lets us verify observable
// behavior of the public Concat API.
Regexp* Regexp::ConcatOrAlternate(RegexpOp op,
                                  Regexp** subs,
                                  int nsubs,
                                  Regexp::ParseFlags flags,
                                  bool can_factor) {
  g_called = true;
  g_last_op = op;
  g_last_subs = subs;
  g_last_nsubs = nsubs;
  g_last_flags = flags;
  g_last_can_factor = can_factor;
  return g_return_value;
}
}  // namespace
}  // namespace re2

// Simple helpers to create distinct, valid-but-opaque pointers for comparisons.
namespace {
struct Dummy { char x; };
static Dummy d1, d2, d3;
inline Regexp* AsRe( Dummy* p ) { return reinterpret_cast<Regexp*>(p); }
}  // namespace

class RegexpConcatTest_341 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Reset probes before each test
    using namespace re2;
    g_called = false;
    g_last_op = static_cast<RegexpOp>(0);
    g_last_subs = nullptr;
    g_last_nsubs = -1;
    g_last_flags = static_cast<Regexp::ParseFlags>(0);
    g_last_can_factor = true;  // expect false when Concat calls it
    g_return_value = nullptr;
  }
};

// Normal operation: forwards args and returns the inner result.
TEST_F(RegexpConcatTest_341, Concat_ForwardsArgsAndReturnsInnerResult_341) {
  Regexp* subs[2] = { AsRe(&d1), AsRe(&d2) };
  auto flags = static_cast<Regexp::ParseFlags>(0x123);

  // Make the stub return a unique sentinel.
  re2::g_return_value = AsRe(&d3);

  Regexp* out = Regexp::Concat(subs, 2, flags);

  // Returned value must be exactly what the inner call produced.
  EXPECT_EQ(out, re2::g_return_value);

  // Verify a single internal call was made with expected parameters.
  EXPECT_TRUE(re2::g_called);
  EXPECT_EQ(re2::g_last_op, kRegexpConcat);     // must use Concat op
  EXPECT_EQ(re2::g_last_subs, subs);            // same pointer forwarded
  EXPECT_EQ(re2::g_last_nsubs, 2);              // count forwarded
  EXPECT_EQ(re2::g_last_flags, flags);          // flags forwarded
  EXPECT_FALSE(re2::g_last_can_factor);         // Concat must pass can_factor=false
}

// Boundary: nsubs == 0 with nullptr subs should be forwarded unchanged.
TEST_F(RegexpConcatTest_341, Concat_AllowsZeroSubsWithNullPointer_341) {
  Regexp** subs = nullptr;
  auto flags = static_cast<Regexp::ParseFlags>(0);

  re2::g_return_value = AsRe(&d1);

  Regexp* out = Regexp::Concat(subs, 0, flags);

  EXPECT_EQ(out, re2::g_return_value);
  EXPECT_TRUE(re2::g_called);
  EXPECT_EQ(re2::g_last_op, kRegexpConcat);
  EXPECT_EQ(re2::g_last_subs, subs);
  EXPECT_EQ(re2::g_last_nsubs, 0);
  EXPECT_EQ(re2::g_last_flags, flags);
  EXPECT_FALSE(re2::g_last_can_factor);
}

// Boundary: handles larger nsubs counts (no assumptions about internal limits).
TEST_F(RegexpConcatTest_341, Concat_ForwardsLargerSubarray_341) {
  Regexp* subs[5] = { AsRe(&d1), AsRe(&d2), AsRe(&d3), AsRe(&d1), AsRe(&d2) };
  auto flags = static_cast<Regexp::ParseFlags>(0x5A5A);

  re2::g_return_value = AsRe(&d2);

  Regexp* out = Regexp::Concat(subs, 5, flags);

  EXPECT_EQ(out, re2::g_return_value);
  EXPECT_TRUE(re2::g_called);
  EXPECT_EQ(re2::g_last_op, kRegexpConcat);
  EXPECT_EQ(re2::g_last_subs, subs);
  EXPECT_EQ(re2::g_last_nsubs, 5);
  EXPECT_EQ(re2::g_last_flags, flags);
  EXPECT_FALSE(re2::g_last_can_factor);
}
