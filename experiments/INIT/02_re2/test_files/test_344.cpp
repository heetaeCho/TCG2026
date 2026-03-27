// File: regexp_capture_test_344.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"
#include <limits>

namespace {

// Helper alias for flags type; treat as an opaque enum/bitmask.
using PF = re2::Regexp::ParseFlags;

class RegexpCaptureTest_344 : public ::testing::Test {};

TEST(RegexpCaptureTest_344, CreatesNodeAndSetsSubPointer_344) {
  // Arrange: use opaque, non-dereferenced sentinel pointers for `this` and `sub`.
  auto* fake_this = reinterpret_cast<re2::Regexp*>(0x1000);
  auto* sub_ptr   = reinterpret_cast<re2::Regexp*>(0x2000);
  const int cap   = 7;
  const PF flags  = static_cast<PF>(0);

  // Act: call through an instance to be compatible with either static or non-static declarations.
  re2::Regexp* re = fake_this->Capture(sub_ptr, flags, cap);

  // Assert: observable effects via the public interface only.
  ASSERT_NE(re, nullptr) << "Capture() must return a new Regexp instance";
  ASSERT_NE(re->sub(), nullptr) << "sub() must return a valid array after AllocSub(1)";
  EXPECT_EQ(re->sub()[0], sub_ptr) << "Captured node should store the provided sub-expression pointer";

  // Cap should mirror the provided value (cap_ is public in the provided header shards).
  EXPECT_EQ(re->cap_, cap) << "Captured node should report the provided capture index";
}

TEST(RegexpCaptureTest_344, AcceptsNullSubPointer_344) {
  auto* fake_this = reinterpret_cast<re2::Regexp*>(0x3000);
  re2::Regexp* sub_ptr = nullptr;  // boundary condition
  const int cap   = 0;
  const PF flags  = static_cast<PF>(0);

  re2::Regexp* re = fake_this->Capture(sub_ptr, flags, cap);

  ASSERT_NE(re, nullptr);
  ASSERT_NE(re->sub(), nullptr);
  EXPECT_EQ(re->sub()[0], nullptr) << "Capture() should preserve a nullptr sub pointer";
  EXPECT_EQ(re->cap_, cap);
}

TEST(RegexpCaptureTest_344, PreservesLargeAndNegativeCaptureIndex_344) {
  auto* fake_this = reinterpret_cast<re2::Regexp*>(0x4000);

  // Large positive cap
  {
    const int big_cap = std::numeric_limits<int>::max();
    re2::Regexp* re = fake_this->Capture(reinterpret_cast<re2::Regexp*>(0x5000),
                                         static_cast<PF>(0), big_cap);
    ASSERT_NE(re, nullptr);
    EXPECT_EQ(re->cap_, big_cap) << "Capture index should preserve large positive values";
  }

  // Negative cap (if implementation allows; we only observe what's stored)
  {
    const int neg_cap = -123;
    re2::Regexp* re = fake_this->Capture(reinterpret_cast<re2::Regexp*>(0x6000),
                                         static_cast<PF>(0), neg_cap);
    ASSERT_NE(re, nullptr);
    EXPECT_EQ(re->cap_, neg_cap) << "Capture index should preserve negative values if accepted";
  }
}

}  // namespace
