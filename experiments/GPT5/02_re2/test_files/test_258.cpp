// File: re2_extract_test_258.cc

#include <gtest/gtest.h>
#include <string>
#include "re2/re2.h"           // public interface
#include "absl/strings/string_view.h"

using re2::RE2;

class RE2_ExtractTest_258 : public ::testing::Test {};

// [Normal] Success: clears *out and writes rewritten result
TEST_F(RE2_ExtractTest_258, ClearsOutAndWritesOnSuccess_258) {
  RE2 helper("(unused)");
  RE2 re("(\\w+)-(\\w+)");          // two capturing groups

  std::string out = "should be cleared";
  const absl::string_view text = "foo-bar";
  const absl::string_view rewrite = "\\2_\\1";  // swap order

  const bool ok = helper.Extract(text, re, rewrite, &out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out, "bar_foo");        // verifies rewrite result and that previous content was cleared
}

// [Boundary] Minimal submatches (no captures in pattern, no backrefs in rewrite)
TEST_F(RE2_ExtractTest_258, NoCapturesAndNoBackrefs_ProducesLiteral_258) {
  RE2 helper("(unused)");
  RE2 re("abc");                    // no capturing groups

  std::string out = "old";
  const absl::string_view text = "zzz abc z";
  const absl::string_view rewrite = "X";        // literal replacement; MaxSubmatch == 0

  const bool ok = helper.Extract(text, re, rewrite, &out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out, "X");
}

// [Error] Rewrite references more groups than pattern provides -> early false, *out unchanged
TEST_F(RE2_ExtractTest_258, RewriteRequiresMoreGroupsThanPattern_ReturnsFalse_258) {
  RE2 helper("(unused)");
  RE2 re("(a)");                    // one capturing group

  std::string out = "unchanged";
  const absl::string_view text = "a";
  const absl::string_view rewrite = "\\2";      // asks for group 2; exceeds 1 + NumberOfCapturingGroups()

  const bool ok = helper.Extract(text, re, rewrite, &out);

  EXPECT_FALSE(ok);
  EXPECT_EQ(out, "unchanged");      // verify no clearing/rewriting happened
}

// [Error] Rewrite requires more vec slots than available (nvec > kVecSize) -> early false, *out unchanged
TEST_F(RE2_ExtractTest_258, RewriteExceedsInternalVecCapacity_ReturnsFalse_258) {
  RE2 helper("(unused)");
  RE2 re("(.*)");                   // pattern content doesn't matter for this check

  std::string out = "keep-me";
  // Use a very large backref index to ensure 1 + MaxSubmatch(rewrite) > kVecSize.
  // Typical kVecSize is modest; \1000 safely exceeds it without relying on internals.
  const absl::string_view text = "whatever";
  const absl::string_view rewrite = "\\1000";

  const bool ok = helper.Extract(text, re, rewrite, &out);

  EXPECT_FALSE(ok);
  EXPECT_EQ(out, "keep-me");
}

// [Error] Pattern does not match text -> returns false, *out unchanged
TEST_F(RE2_ExtractTest_258, NoMatch_ReturnsFalseAndLeavesOutUntouched_258) {
  RE2 helper("(unused)");
  RE2 re("(\\d+)");                 // expects digits

  std::string out = "stay";
  const absl::string_view text = "abc";         // no digits => no match
  const absl::string_view rewrite = "\\1";

  const bool ok = helper.Extract(text, re, rewrite, &out);

  EXPECT_FALSE(ok);
  EXPECT_EQ(out, "stay");
}
