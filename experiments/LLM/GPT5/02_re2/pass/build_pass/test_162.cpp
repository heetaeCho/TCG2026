// File: regexp_match_id_test_162.cc
#include <climits>
#include <gtest/gtest.h>
#include "re2/regexp.h"

using namespace re2;

class RegexpMatchIdTest_162 : public ::testing::Test {};

// [Normal] Returns the exact match id supplied via factory.
TEST_F(RegexpMatchIdTest_162, ReturnsGivenId_162) {
  auto* re = Regexp::HaveMatch(/*match_id=*/42, static_cast<Regexp::ParseFlags>(0));
  ASSERT_NE(nullptr, re);
  EXPECT_EQ(42, re->match_id());
  re->Decref();
}

// [Boundary] Works for edge-case ids: 0, negative, and INT_MAX.
TEST_F(RegexpMatchIdTest_162, HandlesEdgeIds_162) {
  const int ids[] = {0, -1, INT_MAX};
  for (int id : ids) {
    auto* re = Regexp::HaveMatch(id, static_cast<Regexp::ParseFlags>(0));
    ASSERT_NE(nullptr, re) << "Failed to create HaveMatch for id " << id;
    EXPECT_EQ(id, re->match_id()) << "Mismatch for id " << id;
    re->Decref();
  }
}

// [Exceptional/Debug-only] Calling match_id() when op_ != kRegexpHaveMatch should DCHECK.
// We verify with a death test in debug builds (ABSL_DCHECK enabled). In release builds,
// ABSL_DCHECK is compiled out, so we just ensure we don't invoke undefined behavior.
TEST_F(RegexpMatchIdTest_162, DCheckFailsWhenNotHaveMatch_162) {
  // Create any non-HaveMatch regexp through the public interface.
  auto* re = Regexp::Parse("a", static_cast<Regexp::ParseFlags>(0), /*status=*/nullptr);
  ASSERT_NE(nullptr, re);

#ifndef NDEBUG
  // In debug builds, ABSL_DCHECK should fire.
  ASSERT_DEATH_IF_SUPPORTED(
      {
        // Child process body
        (void)re->match_id();
      },
      "");  // Message pattern left empty—implementation detail is not asserted.
#else
  // In release builds, ABSL_DCHECK is disabled; do NOT call match_id() here
  // since behavior is not part of the documented interface for non-HaveMatch.
  SUCCEED();
#endif

  re->Decref();
}
