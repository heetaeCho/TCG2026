// File: parse_optional_overload_test_41.cc

#include <gtest/gtest.h>
#include "absl/types/optional.h"

// Bring in the header under test after test doubles are available at instantiation time.
namespace re2 { namespace re2_internal {

// ------- Test doubles (external collaborator stubs) -------

// A simple value type to test normal behavior.
struct Dummy {
  int v = -1;
  friend bool operator==(const Dummy& a, const Dummy& b) { return a.v == b.v; }
};

// A move-only type to ensure the overload uses move emplacement path.
struct MoveOnly {
  int v = -1;
  MoveOnly() = default;
  explicit MoveOnly(int x) : v(x) {}
  MoveOnly(const MoveOnly&) = delete;
  MoveOnly& operator=(const MoveOnly&) = delete;
  MoveOnly(MoveOnly&&) = default;
  MoveOnly& operator=(MoveOnly&&) = default;
  friend bool operator==(const MoveOnly& a, const MoveOnly& b) { return a.v == b.v; }
};

// State to control/observe collaborator behavior.
static bool g_parse_should_succeed_dummy = true;
static bool g_parse_should_succeed_moveonly = true;
static size_t g_last_n = 0;
static int g_last_radix = 0;
static const char* g_last_str = nullptr;

// Stub for: bool Parse(const char*, size_t, Dummy*, int)
inline bool Parse(const char* str, size_t n, Dummy* out, int radix) {
  g_last_str = str;
  g_last_n = n;
  g_last_radix = radix;
  if (!g_parse_should_succeed_dummy) return false;
  if (out) out->v = 12345;  // Sentinel value for verification
  return true;
}

// Stub for: bool Parse(const char*, size_t, MoveOnly*, int)
inline bool Parse(const char* /*str*/, size_t /*n*/, MoveOnly* out, int /*radix*/) {
  if (!g_parse_should_succeed_moveonly) return false;
  if (out) *out = MoveOnly(777);  // Set a recognizable value
  return true;
}

}} // namespace re2::re2_internal

#include "./TestProjects/re2/re2/re2.h"  // header under test

using namespace re2::re2_internal;

class ParseOptionalTest_41 : public ::testing::Test {
protected:
  void SetUp() override {
    g_parse_should_succeed_dummy = true;
    g_parse_should_succeed_moveonly = true;
    g_last_n = 0;
    g_last_radix = 0;
    g_last_str = nullptr;
  }
};

// ---------------------- Tests ----------------------

// Null input pointer should return true and leave dest alone when dest==nullptr.
TEST_F(ParseOptionalTest_41, NullStr_NullDest_ReturnsTrue_41) {
  EXPECT_TRUE(Parse<Dummy>(/*str=*/nullptr, /*n=*/0, /*dest=*/nullptr, /*radix=*/10));
}

// Null input pointer should reset dest (if non-null) and return true.
TEST_F(ParseOptionalTest_41, NullStr_ResetsDest_41) {
  absl::optional<Dummy> dest(Dummy{999}); // engaged
  EXPECT_TRUE(Parse<Dummy>(/*str=*/nullptr, /*n=*/5, &dest, /*radix=*/16));
  EXPECT_FALSE(dest.has_value());  // must be reset
}

// On collaborator success: returns true and sets dest to parsed value.
TEST_F(ParseOptionalTest_41, CollaboratorSuccess_SetsDestAndReturnsTrue_41) {
  g_parse_should_succeed_dummy = true;
  absl::optional<Dummy> dest; // disengaged initially
  const char* s = "anything";
  EXPECT_TRUE(Parse<Dummy>(s, /*n=*/3, &dest, /*radix=*/8));
  ASSERT_TRUE(dest.has_value());
  EXPECT_EQ(dest->v, 12345);  // sentinel set by stub
}

// On collaborator success with dest==nullptr: returns true and does not crash.
TEST_F(ParseOptionalTest_41, CollaboratorSuccess_NullDest_ReturnsTrue_41) {
  g_parse_should_succeed_dummy = true;
  const char* s = "ok";
  EXPECT_TRUE(Parse<Dummy>(s, /*n=*/2, /*dest=*/nullptr, /*radix=*/2));
}

// On collaborator failure: returns false and must not modify existing dest.
TEST_F(ParseOptionalTest_41, CollaboratorFailure_DoesNotModifyDestAndReturnsFalse_41) {
  g_parse_should_succeed_dummy = false;  // force failure
  absl::optional<Dummy> dest(Dummy{4242}); // pre-existing value
  const char* s = "fail";
  EXPECT_FALSE(Parse<Dummy>(s, /*n=*/4, &dest, /*radix=*/10));
  ASSERT_TRUE(dest.has_value());          // still engaged
  EXPECT_EQ(dest->v, 4242);               // unchanged
}

// Forwards length and radix to the collaborator (verify via observed globals).
TEST_F(ParseOptionalTest_41, ForwardsLengthAndRadix_41) {
  g_parse_should_succeed_dummy = true;
  absl::optional<Dummy> dest;
  const char* s = "xyz";
  size_t n = 7;
  int radix = 13;
  EXPECT_TRUE(Parse<Dummy>(s, n, &dest, radix));
  EXPECT_EQ(g_last_str, s);
  EXPECT_EQ(g_last_n, n);
  EXPECT_EQ(g_last_radix, radix);
}

// Works with move-only types (ensures move-based emplacement path compiles/works).
TEST_F(ParseOptionalTest_41, MoveOnlyType_Success_Emplaced_41) {
  g_parse_should_succeed_moveonly = true;
  absl::optional<MoveOnly> dest;
  const char* s = "move";
  EXPECT_TRUE(Parse<MoveOnly>(s, /*n=*/1, &dest, /*radix=*/10));
  ASSERT_TRUE(dest.has_value());
  EXPECT_EQ(dest->v, 777);
}

// Move-only + failure: returns false and leaves dest unchanged.
TEST_F(ParseOptionalTest_41, MoveOnlyType_Failure_NoChange_41) {
  g_parse_should_succeed_moveonly = false;
  absl::optional<MoveOnly> dest(MoveOnly(101));
  const char* s = "nope";
  EXPECT_FALSE(Parse<MoveOnly>(s, /*n=*/2, &dest, /*radix=*/10));
  ASSERT_TRUE(dest.has_value());
  EXPECT_EQ(dest->v, 101);
}
