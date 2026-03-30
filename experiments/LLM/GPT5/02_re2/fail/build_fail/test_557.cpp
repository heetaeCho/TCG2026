// File: prefilter_emptystring_test_557.cc
#include <gtest/gtest.h>
#include "re2/prefilter.h"  // Assumes the project exposes Prefilter/Info here

using re2::Prefilter;

//
// Tests for Prefilter::Info::EmptyString()
//

// [Normal] Returns a non-null Info whose `is_exact()` is true and whose `exact()`
// contains exactly the empty string.
TEST(PrefilterInfoTest_557, EmptyStringProducesExactWithEmptyLiteral_557) {
  Prefilter::Info* info = Prefilter::Info::EmptyString();
  ASSERT_NE(info, nullptr);

  // Observable properties via public interface
  EXPECT_TRUE(info->is_exact());

  // Verify the exact set contains the empty string, and (initially) only that.
  auto& s = info->exact();
  // Expect exactly one element
  ASSERT_EQ(s.size(), 1u);
  // And that element is the empty string
  ASSERT_EQ(s.count(std::string("")), 1u);

  delete info;  // Ensure no crash on destruction
}

// [Boundary] Multiple calls return independent instances: mutating one instance’s
// exact() should not affect another’s observable contents.
TEST(PrefilterInfoTest_557, EmptyStringInstancesAreIndependent_557) {
  Prefilter::Info* a = Prefilter::Info::EmptyString();
  Prefilter::Info* b = Prefilter::Info::EmptyString();
  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  // Baseline: both start with exactly { "" }
  ASSERT_TRUE(a->is_exact());
  ASSERT_TRUE(b->is_exact());
  ASSERT_EQ(a->exact().size(), 1u);
  ASSERT_EQ(a->exact().count(std::string("")), 1u);
  ASSERT_EQ(b->exact().size(), 1u);
  ASSERT_EQ(b->exact().count(std::string("")), 1u);

  // Mutate only `a`'s exact() through the public reference.
  a->exact().insert("extra");

  // Observe independence: `b` remains unchanged.
  EXPECT_EQ(b->exact().size(), 1u);
  EXPECT_EQ(b->exact().count(std::string("")), 1u);

  delete a;
  delete b;
}
