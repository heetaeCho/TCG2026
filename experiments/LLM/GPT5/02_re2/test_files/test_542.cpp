// File: prefilter_info_take_match_test.cc

#include "gtest/gtest.h"
#include "re2/prefilter.h"  // Declares re2::Prefilter and nested Info
// If your build splits the Info declaration elsewhere, include that header instead.

namespace re2 {

class PrefilterInfoTest_542 : public ::testing::Test {};

TEST_F(PrefilterInfoTest_542, DefaultConstructed_ReturnsNull_542) {
  // Given a freshly constructed Info
  Prefilter::Info info;

  // When TakeMatch is called
  Prefilter* first = info.TakeMatch();

  // Then it should be safe and return nullptr (no observable match available)
  EXPECT_EQ(first, nullptr);
}

TEST_F(PrefilterInfoTest_542, CallingTwice_IsIdempotentAndReturnsNull_542) {
  // Given a freshly constructed Info
  Prefilter::Info info;

  // When TakeMatch is called twice
  Prefilter* first = info.TakeMatch();
  Prefilter* second = info.TakeMatch();

  // Then both observable results are nullptr and the second call doesn't crash
  EXPECT_EQ(first, nullptr);
  EXPECT_EQ(second, nullptr);
}

TEST_F(PrefilterInfoTest_542, MultipleCalls_DoNotCrash_542) {
  // Given a freshly constructed Info
  Prefilter::Info info;

  // When TakeMatch is called repeatedly
  for (int i = 0; i < 10; ++i) {
    // Then each observable result is nullptr (no match surfaced)
    EXPECT_EQ(info.TakeMatch(), nullptr);
  }
}

TEST_F(PrefilterInfoTest_542, SeparateInstances_AreIndependent_542) {
  // Given two independent Info instances
  Prefilter::Info a;
  Prefilter::Info b;

  // When TakeMatch is called on both
  Prefilter* am = a.TakeMatch();
  Prefilter* bm = b.TakeMatch();

  // Then each returns its own observable result (both nullptr in default state)
  EXPECT_EQ(am, nullptr);
  EXPECT_EQ(bm, nullptr);
}

}  // namespace re2
