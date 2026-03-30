// File: re2_options_max_mem_test_12.cpp
#include <gtest/gtest.h>
#include <cstdint>
#include <limits>
#include "re2/re2.h"

using re2::RE2;

class RE2OptionsTest_12 : public ::testing::Test {
protected:
  RE2::Options opts_;
};

// Verifies that after setting max_mem, the getter returns the same value.
// Covers normal operation across a variety of reasonable positive values.
TEST_F(RE2OptionsTest_12, SetAndGet_MaxMemVariousValues_12) {
  const int64_t values[] = {
      0,                    // boundary: zero
      1,                    // small positive
      1024,                 // 1 KiB
      (1LL << 20),          // 1 MiB
      (1LL << 30),          // 1 GiB
      (1LL << 40)           // large but still within int64_t
  };

  for (int64_t v : values) {
    SCOPED_TRACE(::testing::Message() << "value=" << v);
    opts_.set_max_mem(v);
    EXPECT_EQ(v, opts_.max_mem());
  }
}

// Verifies the getter works via a const-qualified access path (observable behavior),
// and repeated calls are consistent (idempotent read).
TEST_F(RE2OptionsTest_12, ConstGetterConsistency_12) {
  const int64_t set_value = (1LL << 20);
  opts_.set_max_mem(set_value);

  const RE2::Options& const_ref = opts_;
  EXPECT_EQ(set_value, const_ref.max_mem());
  EXPECT_EQ(const_ref.max_mem(), const_ref.max_mem());  // same value on repeated calls
}

// Verifies copy semantics via the public Copy(const Options& src) API:
// - After copying, destination reports the same observable value via max_mem().
// - Subsequent changes in dest do not affect src (independence).
TEST_F(RE2OptionsTest_12, CopyPreservesAndIsIndependent_12) {
  RE2::Options src;
  RE2::Options dst;

  const int64_t src_value = (1LL << 30);
  const int64_t dst_initial = 1024;

  dst.set_max_mem(dst_initial);
  src.set_max_mem(src_value);

  // Copy from src -> dst using the public API.
  dst.Copy(src);

  // Observable behavior: dst now reflects src's value.
  EXPECT_EQ(src_value, dst.max_mem());
  EXPECT_EQ(src_value, src.max_mem());

  // Independence check: mutate dst, src should remain unchanged.
  const int64_t dst_new = (1LL << 20);
  dst.set_max_mem(dst_new);

  EXPECT_EQ(dst_new, dst.max_mem());
  EXPECT_EQ(src_value, src.max_mem());
}

// (Optional) Large boundary sanity check: setting near the upper range that is still reasonable.
// Avoids assuming clamping rules; just checks observable round-trip via the public API.
TEST_F(RE2OptionsTest_12, LargeValueRoundTrip_12) {
  // Use a large value that avoids overflow and is commonly representable.
  const int64_t big = std::numeric_limits<int64_t>::max() / 4;
  opts_.set_max_mem(big);
  EXPECT_EQ(big, opts_.max_mem());
}
