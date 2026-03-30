// File: regexp_simple_test_151.cc
#include <gtest/gtest.h>
#include <cstddef>   // offsetof
#include <cstdint>
#include <cstring>   // std::memset
#include <new>       // ::operator new/delete

// Minimal header under test (as provided)
namespace re2 {
class Regexp {
public:
  bool simple() { return simple_ != 0; }
private:
  // The member exists per the provided snippet & known deps (order not relied on in asserts).
  uint8_t simple_;
};
}  // namespace re2

namespace {

// Helper to allocate raw storage for Regexp, set its private `simple_` byte,
// and return a usable pointer for calling simple(). We never call a destructor
// and we free the raw storage after each test.
static re2::Regexp* MakeRegexpWithSimple(uint8_t simple_value) {
  void* mem = ::operator new(sizeof(re2::Regexp));
  // Zero the storage to keep other bytes neutral.
  std::memset(mem, 0, sizeof(re2::Regexp));

  // Set the private byte using offsetof; we don't access or inspect any other state.
  size_t offset = offsetof(re2::Regexp, simple_);
  *(reinterpret_cast<uint8_t*>(static_cast<char*>(mem) + offset)) = simple_value;

  return reinterpret_cast<re2::Regexp*>(mem);
}

static void FreeRegexp(re2::Regexp* p) {
  ::operator delete(reinterpret_cast<void*>(p));
}

}  // namespace

// -------- Tests --------

TEST(RegexpSimpleTest_151, ReturnsFalseWhenSimpleIsZero_151) {
  re2::Regexp* re = MakeRegexpWithSimple(/*simple_=*/0);
  // Observable behavior: simple() should be false when the underlying flag is zero.
  EXPECT_FALSE(re->simple());
  // Idempotence on repeated calls (observable behavior).
  EXPECT_FALSE(re->simple());
  FreeRegexp(re);
}

TEST(RegexpSimpleTest_151, ReturnsTrueWhenSimpleIsNonZero_151) {
  re2::Regexp* re = MakeRegexpWithSimple(/*simple_=*/1);
  // Observable behavior: simple() should be true when the underlying flag is non-zero.
  EXPECT_TRUE(re->simple());
  // Idempotence on repeated calls (observable behavior).
  EXPECT_TRUE(re->simple());
  FreeRegexp(re);
}

TEST(RegexpSimpleTest_151, TreatsAnyNonZeroAsTrue_151) {
  re2::Regexp* re = MakeRegexpWithSimple(/*simple_=*/255);  // Arbitrary non-zero
  EXPECT_TRUE(re->simple());
  FreeRegexp(re);
}

TEST(RegexpSimpleTest_151, ConsistentAcrossMultipleInstances_151) {
  re2::Regexp* a = MakeRegexpWithSimple(0);
  re2::Regexp* b = MakeRegexpWithSimple(1);
  EXPECT_FALSE(a->simple());
  EXPECT_TRUE(b->simple());
  FreeRegexp(a);
  FreeRegexp(b);
}
