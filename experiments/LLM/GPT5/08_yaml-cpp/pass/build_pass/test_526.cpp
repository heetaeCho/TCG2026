// TEST_ID: 526
#include <gtest/gtest.h>

#include <limits>
#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

class EmitterSetPostCommentIndentTest_526 : public ::testing::Test {
 protected:
  static void ExpectConsistentStateAfterCall(YAML::Emitter& out, bool ok) {
    // Observable contract check (without assuming internal rules):
    // - If the call succeeds, emitter should remain "good" and have no error message.
    // - If it fails, either emitter becomes not-good OR it exposes a non-empty error string.
    if (ok) {
      EXPECT_TRUE(out.good());
      EXPECT_TRUE(out.GetLastError().empty());
    } else {
      EXPECT_TRUE(!out.good() || !out.GetLastError().empty());
    }

    // Also ensure basic queries remain usable (no crash / UB observable via interface).
    (void)out.c_str();
    (void)out.size();
  }
};

TEST_F(EmitterSetPostCommentIndentTest_526, SetToZeroIsHandled_526) {
  YAML::Emitter out;
  const bool ok = out.SetPostCommentIndent(static_cast<std::size_t>(0));
  ExpectConsistentStateAfterCall(out, ok);
}

TEST_F(EmitterSetPostCommentIndentTest_526, SetToTypicalSmallValues_526) {
  YAML::Emitter out;

  const bool ok1 = out.SetPostCommentIndent(static_cast<std::size_t>(1));
  ExpectConsistentStateAfterCall(out, ok1);

  const bool ok2 = out.SetPostCommentIndent(static_cast<std::size_t>(2));
  ExpectConsistentStateAfterCall(out, ok2);

  const bool ok4 = out.SetPostCommentIndent(static_cast<std::size_t>(4));
  ExpectConsistentStateAfterCall(out, ok4);
}

TEST_F(EmitterSetPostCommentIndentTest_526, RepeatedCallsDoNotBreakEmitter_526) {
  YAML::Emitter out;

  const bool ok_first = out.SetPostCommentIndent(static_cast<std::size_t>(2));
  ExpectConsistentStateAfterCall(out, ok_first);

  const bool ok_second = out.SetPostCommentIndent(static_cast<std::size_t>(2));
  ExpectConsistentStateAfterCall(out, ok_second);

  const bool ok_third = out.SetPostCommentIndent(static_cast<std::size_t>(3));
  ExpectConsistentStateAfterCall(out, ok_third);
}

TEST_F(EmitterSetPostCommentIndentTest_526, LargeValueIsHandledGracefully_526) {
  YAML::Emitter out;

  const bool ok = out.SetPostCommentIndent(static_cast<std::size_t>(1024));
  ExpectConsistentStateAfterCall(out, ok);

  const bool ok2 = out.SetPostCommentIndent(static_cast<std::size_t>(1u << 20));
  ExpectConsistentStateAfterCall(out, ok2);
}

TEST_F(EmitterSetPostCommentIndentTest_526, MaxSizeTIsHandledGracefully_526) {
  YAML::Emitter out;

  const std::size_t kMax = (std::numeric_limits<std::size_t>::max)();
  const bool ok = out.SetPostCommentIndent(kMax);
  ExpectConsistentStateAfterCall(out, ok);
}

TEST_F(EmitterSetPostCommentIndentTest_526, WorksWhenUsingStreamConstructor_526) {
  std::ostringstream oss;
  YAML::Emitter out(oss);

  const bool ok = out.SetPostCommentIndent(static_cast<std::size_t>(2));
  ExpectConsistentStateAfterCall(out, ok);

  // Stream-backed emitters should still expose output buffer accessors.
  (void)out.c_str();
  (void)out.size();
}

}  // namespace