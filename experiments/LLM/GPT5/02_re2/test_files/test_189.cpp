// File: pcre_fullmatchfunctor_test_189.cc
#include <gtest/gtest.h>
#include <string>
#include "re2/util/pcre.h"

using re2::PCRE;

class PCRE_FullMatchFunctorTest_189 : public ::testing::Test {
protected:
  PCRE::FullMatchFunctor functor_;
};

// Normal operation: exact full match should succeed.
TEST_F(PCRE_FullMatchFunctorTest_189, FullMatch_ReturnsTrueOnExactMatch_189) {
  PCRE re("abc");
  // Provide many args (no captures in pattern) to ensure extras don't break behavior.
  PCRE::Arg a[16];  // default-constructed
  bool ok = functor_("abc", re,
                     a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7],
                     a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15]);
  EXPECT_TRUE(ok);
}

// Anchoring (ANCHOR_BOTH): partial match should fail.
TEST_F(PCRE_FullMatchFunctorTest_189, FullMatch_ReturnsFalseOnPartialMatch_189) {
  PCRE re("abc");
  PCRE::Arg a[16];
  // "xabc" contains "abc" but not as a full-string match
  bool ok = functor_("xabc", re,
                     a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7],
                     a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15]);
  EXPECT_FALSE(ok);
}

// Captures: verify that capture args are filled on success.
TEST_F(PCRE_FullMatchFunctorTest_189, Captures_FilledOnSuccess_189) {
  PCRE re("(\\w+)-(\\d+)");
  std::string s1, s2;
  PCRE::Arg a_s1(&s1);
  PCRE::Arg a_s2(&s2);
  PCRE::Arg a[14];  // remaining unused args

  bool ok = functor_("foo-123", re,
                     a_s1, a_s2,
                     a[0], a[1], a[2], a[3], a[4], a[5], a[6],
                     a[7], a[8], a[9], a[10], a[11], a[12], a[13]);
  EXPECT_TRUE(ok);
  EXPECT_EQ(s1, "foo");
  EXPECT_EQ(s2, "123");
}

// Extra args: args beyond capture count should be ignored (not modified).
TEST_F(PCRE_FullMatchFunctorTest_189, ExtraArgs_IgnoredBeyondCaptureCount_189) {
  PCRE re("(\\d+)");
  std::string first = "unset";
  std::string extra = "keep";
  PCRE::Arg a_first(&first);
  PCRE::Arg a_extra(&extra);
  PCRE::Arg a[14];

  bool ok = functor_("42", re,
                     a_first, a_extra,
                     a[0], a[1], a[2], a[3], a[4], a[5], a[6],
                     a[7], a[8], a[9], a[10], a[11], a[12], a[13]);
  EXPECT_TRUE(ok);
  EXPECT_EQ(first, "42");
  // Should remain unchanged since only one capturing group exists
  EXPECT_EQ(extra, "keep");
}

// Failure path: on no match, output args should not be populated.
TEST_F(PCRE_FullMatchFunctorTest_189, NoMatch_DoesNotModifyOutputs_189) {
  PCRE re("(\\d+)");
  std::string out = "orig";
  PCRE::Arg a_out(&out);
  PCRE::Arg a[15];

  bool ok = functor_("abc", re,
                     a_out,
                     a[0], a[1], a[2], a[3], a[4], a[5], a[6],
                     a[7], a[8], a[9], a[10], a[11], a[12], a[13], a[14]);
  EXPECT_FALSE(ok);
  EXPECT_EQ(out, "orig");  // remains unchanged on failure
}

// Boundary: handle up to kMaxArgs (16) capture groups without crashing.
TEST_F(PCRE_FullMatchFunctorTest_189, HandlesMaxArgs_SixteenCaptures_189) {
  // 16 single-character capturing groups matching 16 'a's
  PCRE re("(^)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)(a)$");
  // The first (^) group captures empty string; keep it simple and just verify sizes/contents where meaningful.
  std::string caps[16];
  PCRE::Arg args[16] = {
      PCRE::Arg(&caps[0]),  PCRE::Arg(&caps[1]),
      PCRE::Arg(&caps[2]),  PCRE::Arg(&caps[3]),
      PCRE::Arg(&caps[4]),  PCRE::Arg(&caps[5]),
      PCRE::Arg(&caps[6]),  PCRE::Arg(&caps[7]),
      PCRE::Arg(&caps[8]),  PCRE::Arg(&caps[9]),
      PCRE::Arg(&caps[10]), PCRE::Arg(&caps[11]),
      PCRE::Arg(&caps[12]), PCRE::Arg(&caps[13]),
      PCRE::Arg(&caps[14]), PCRE::Arg(&caps[15])
  };

  // Build the 16-char input: empty-start anchor capture + 15 'a's still needs 15 'a's; we’ll provide 15 'a's,
  // but include 16 'a's to keep it simple—pattern uses anchors so string must match exactly 15 a's after start.
  // Adjust to exactly 15 'a's to satisfy the pattern shape we wrote.
  std::string text(15, 'a');

  bool ok = functor_(text, re,
                     args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7],
                     args[8], args[9], args[10], args[11], args[12], args[13], args[14], args[15]);
  EXPECT_TRUE(ok);

  // Verify expected captured values: group 0 is (^) -> empty, groups 1..15 are "a"
  EXPECT_EQ(caps[0], "");      // from (^)
  for (int i = 1; i < 16; ++i) {
    EXPECT_EQ(caps[i], "a");
  }
}
