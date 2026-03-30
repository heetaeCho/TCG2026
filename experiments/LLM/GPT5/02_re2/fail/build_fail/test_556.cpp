// File: prefilter_info_anymatch_test_556.cc

#include <gtest/gtest.h>
#include "re2/prefilter.h"

namespace re2 {

class PrefilterInfoTest_556 : public ::testing::Test {};

// Verifies that AnyMatch returns a valid Info, and that a match object can be taken.
TEST_F(PrefilterInfoTest_556, AnyMatch_ReturnsInfoAndMatchNonNull_556) {
  Prefilter::Info* info = Prefilter::Info::AnyMatch();
  ASSERT_NE(info, nullptr) << "AnyMatch() should return a valid Info*";

  Prefilter* match = info->TakeMatch();
  EXPECT_NE(match, nullptr) << "TakeMatch() should return a valid Prefilter* for AnyMatch()";

  // Clean up (ownership is assumed to be the caller’s after TakeMatch()).
  delete match;
  delete info;
}

// Verifies that TakeMatch() is move-like: first call yields the match, subsequent calls yield nullptr.
TEST_F(PrefilterInfoTest_556, AnyMatch_TakeMatchIsMoveOnly_SecondCallNull_556) {
  Prefilter::Info* info = Prefilter::Info::AnyMatch();
  ASSERT_NE(info, nullptr);

  Prefilter* first = info->TakeMatch();
  ASSERT_NE(first, nullptr) << "First TakeMatch() should yield a Prefilter*";

  Prefilter* second = info->TakeMatch();
  EXPECT_EQ(second, nullptr) << "Second TakeMatch() should yield nullptr after the match was taken";

  delete first;
  delete info;
}

// Verifies the observable flag accessor without relying on internal state.
TEST_F(PrefilterInfoTest_556, AnyMatch_IsNotExactByDefault_556) {
  Prefilter::Info* info = Prefilter::Info::AnyMatch();
  ASSERT_NE(info, nullptr);

  // The interface exposes is_exact(); rely only on this accessor.
  EXPECT_FALSE(info->is_exact()) << "AnyMatch() should not be an 'exact' match by default";

  delete info;
}

// Verifies ToString() provides some human-readable description for debugging/logging.
TEST_F(PrefilterInfoTest_556, AnyMatch_ToString_IsNonEmpty_556) {
  Prefilter::Info* info = Prefilter::Info::AnyMatch();
  ASSERT_NE(info, nullptr);

  std::string s = info->ToString();
  // Do not assert specific content; only that something descriptive is returned.
  EXPECT_FALSE(s.empty()) << "ToString() should return a non-empty description";

  delete info;
}

// Verifies independence: separate AnyMatch() calls return distinct Info objects with distinct matches.
TEST_F(PrefilterInfoTest_556, AnyMatch_IndependentInstances_556) {
  Prefilter::Info* a = Prefilter::Info::AnyMatch();
  Prefilter::Info* b = Prefilter::Info::AnyMatch();
  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  EXPECT_NE(a, b) << "Each AnyMatch() call should return a distinct Info object";

  Prefilter* ma = a->TakeMatch();
  Prefilter* mb = b->TakeMatch();
  ASSERT_NE(ma, nullptr);
  ASSERT_NE(mb, nullptr);
  EXPECT_NE(ma, mb) << "Each Info should own a distinct Prefilter match object";

  delete ma;
  delete mb;
  delete a;
  delete b;
}

}  // namespace re2
