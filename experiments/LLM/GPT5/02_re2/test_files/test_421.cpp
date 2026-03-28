// File: simplify_regexp_test_421.cc
#include <string>

#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "absl/strings/string_view.h"

namespace {

using re2::Regexp;
using re2::RegexpStatus;
using re2::kRegexpSuccess;

using PF = Regexp::ParseFlags;
static constexpr PF kNoFlags = static_cast<PF>(0);

// --- Success cases ---

TEST(RegexpSimplifyTest_421, ReturnsTrueOnValidRegex_421) {
  const std::string src = "a+b";
  std::string dst = "UNTOUCHED";
  bool ok = Regexp::SimplifyRegexp(src, kNoFlags, &dst, /*status=*/nullptr);
  EXPECT_TRUE(ok);
  // Result string should be a valid regexp that can be parsed again.
  RegexpStatus st2;
  Regexp* parsed = Regexp::Parse(dst, kNoFlags, &st2);
  EXPECT_TRUE(st2.ok());
  ASSERT_NE(parsed, nullptr);
  parsed->Decref();
}

TEST(RegexpSimplifyTest_421, LeavesStatusOkOnSuccess_421) {
  const std::string src = "abc|def";
  std::string dst;
  RegexpStatus status;  // default-constructed; should remain success on success
  bool ok = Regexp::SimplifyRegexp(src, kNoFlags, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_TRUE(status.ok());
  // Also ensure the produced string parses.
  RegexpStatus st2;
  Regexp* parsed = Regexp::Parse(dst, kNoFlags, &st2);
  EXPECT_TRUE(st2.ok());
  ASSERT_NE(parsed, nullptr);
  parsed->Decref();
}

TEST(RegexpSimplifyTest_421, HandlesEmptyPattern_421) {
  const std::string src;  // empty
  std::string dst = "ZZZ";
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(src, kNoFlags, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_TRUE(status.ok());
  // The output should itself be parseable (could be empty or a canonical form).
  RegexpStatus st2;
  Regexp* parsed = Regexp::Parse(dst, kNoFlags, &st2);
  EXPECT_TRUE(st2.ok());
  ASSERT_NE(parsed, nullptr);
  parsed->Decref();
}

// --- Parse error cases (propagated from Parse) ---

TEST(RegexpSimplifyTest_421, ReturnsFalseAndKeepsDstOnParseFailure_421) {
  const std::string src = "(";  // intentionally invalid (unmatched paren)
  std::string dst = "SENTINEL";
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp(src, kNoFlags, &dst, &status);
  EXPECT_FALSE(ok);
  // dst should remain unchanged because simplification never ran.
  EXPECT_EQ(dst, "SENTINEL");
  // Status should indicate failure (exact code is up to Parse).
  EXPECT_FALSE(status.ok());
  EXPECT_NE(status.code(), kRegexpSuccess);
}

TEST(RegexpSimplifyTest_421, ReturnsFalseWithNullStatusOnParseFailure_421) {
  const std::string src = "\\";  // intentionally invalid (trailing backslash)
  std::string dst = "KEEP_ME";
  bool ok = Regexp::SimplifyRegexp(src, kNoFlags, &dst, /*status=*/nullptr);
  EXPECT_FALSE(ok);
  // dst should remain unchanged.
  EXPECT_EQ(dst, "KEEP_ME");
}

// --- API robustness ---

TEST(RegexpSimplifyTest_421, WritesOutputBufferOnSuccess_421) {
  const std::string src = "[a-c]{2,3}";
  std::string dst = "BEFORE";
  bool ok = Regexp::SimplifyRegexp(src, kNoFlags, &dst, /*status=*/nullptr);
  EXPECT_TRUE(ok);
  // On success, the function must assign to dst (may or may not differ in content).
  // At minimum, dst should represent a parseable regexp.
  RegexpStatus st2;
  Regexp* parsed = Regexp::Parse(dst, kNoFlags, &st2);
  EXPECT_TRUE(st2.ok());
  ASSERT_NE(parsed, nullptr);
  parsed->Decref();
}

}  // namespace
