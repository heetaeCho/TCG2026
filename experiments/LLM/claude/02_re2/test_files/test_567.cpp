#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "absl/strings/string_view.h"

namespace re2 {

class SearchOnePassTest_567 : public ::testing::Test {
 protected:
  // Helper to compile a regex to a Prog and check if it's one-pass
  struct ProgHolder {
    Regexp* re;
    Prog* prog;
    
    ProgHolder(const std::string& pattern) : re(nullptr), prog(nullptr) {
      RegexpStatus status;
      re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
      if (re) {
        prog = re->CompileToProg(0);
      }
    }
    
    ~ProgHolder() {
      delete prog;
      if (re) re->Decref();
    }
    
    bool IsValid() const { return prog != nullptr; }
    bool IsOnePass() const { return prog && prog->IsOnePass(); }
  };
};

// Test that unanchored search with non-full match returns false
TEST_F(SearchOnePassTest_567, UnanchoredNonFullMatchReturnsFalse_567) {
  ProgHolder ph("abc");
  ASSERT_TRUE(ph.IsValid());
  if (!ph.IsOnePass()) return;  // Skip if not one-pass

  absl::string_view text("abc");
  absl::string_view match;
  // kAnchored = 1 (anchored), kUnanchored = 0
  // Using kUnanchored with kFirstMatch should fail
  bool result = ph.prog->SearchOnePass(text, text, Prog::kUnanchored,
                                        Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(result);
}

// Test simple anchored full match
TEST_F(SearchOnePassTest_567, SimpleAnchoredFullMatch_567) {
  ProgHolder ph("abc");
  ASSERT_TRUE(ph.IsValid());
  if (!ph.IsOnePass()) return;

  absl::string_view text("abc");
  absl::string_view match;
  bool result = ph.prog->SearchOnePass(text, text, Prog::kAnchored,
                                        Prog::kFullMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, "abc");
}

// Test anchored full match that should fail
TEST_F(SearchOnePassTest_567, AnchoredFullMatchFails_567) {
  ProgHolder ph("abc");
  ASSERT_TRUE(ph.IsValid());
  if (!ph.IsOnePass()) return;

  absl::string_view text("abd");
  absl::string_view match;
  bool result = ph.prog->SearchOnePass(text, text, Prog::kAnchored,
                                        Prog::kFullMatch, &match, 1);
  EXPECT_FALSE(result);
}

// Test with empty text and empty pattern
TEST_F(SearchOnePassTest_567, EmptyPatternEmptyText_567) {
  ProgHolder ph("");
  ASSERT_TRUE(ph.IsValid());
  if (!ph.IsOnePass()) return;

  absl::string_view text("");
  absl::string_view match;
  bool result = ph.prog->SearchOnePass(text, text, Prog::kAnchored,
                                        Prog::kFullMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match.size(), 0);
}

// Test with capture groups
TEST_F(SearchOnePassTest_567, CaptureGroups_567) {
  ProgHolder ph("(a)(b)(c)");
  ASSERT_TRUE(ph.IsValid());
  if (!ph.IsOnePass()) return;

  absl::string_view text("abc");
  absl::string_view match[4];
  bool result = ph.prog->SearchOnePass(text, text, Prog::kAnchored,
                                        Prog::kFullMatch, match, 4);
  EXPECT_TRUE(result);
  EXPECT_EQ(match[0], "abc");
  EXPECT_EQ(match[1], "a");
  EXPECT_EQ(match[2], "b");
  EXPECT_EQ(match[3], "c");
}

// Test nmatch = 0
TEST_F(SearchOnePassTest_567, NmatchZero_567) {
  ProgHolder ph("abc");
  ASSERT_TRUE(ph.IsValid());
  if (!ph.IsOnePass()) return;

  absl::string_view text("abc");
  bool result = ph.prog->SearchOnePass(text, text, Prog::kAnchored,
                                        Prog::kFullMatch, nullptr, 0);
  EXPECT_TRUE(result);
}

// Test partial match failure (text longer than pattern)
TEST_F(SearchOnePassTest_567, FullMatchFailsTextTooLong_567) {
  ProgHolder ph("ab");
  ASSERT_TRUE(ph.IsValid());
  if (!ph.IsOnePass()) return;

  absl::string_view text("abc");
  absl::string_view match;
  bool result = ph.prog->SearchOnePass(text, text, Prog::kAnchored,
                                        Prog::kFullMatch, &match, 1);
  EXPECT_FALSE(result);
}

// Test partial match failure (text shorter than pattern)
TEST_F(SearchOnePassTest_567, FullMatchFailsTextTooShort_567) {
  ProgHolder ph("abcd");
  ASSERT_TRUE(ph.IsValid());
  if (!ph.IsOnePass()) return;

  absl::string_view text("abc");
  absl::string_view match;
  bool result = ph.prog->SearchOnePass(text, text, Prog::kAnchored,
                                        Prog::kFullMatch, &match, 1);
  EXPECT_FALSE(result);
}

// Test with character class
TEST_F(SearchOnePassTest_567, CharacterClass_567) {
  ProgHolder ph("[a-z]+");
  ASSERT_TRUE(ph.IsValid());
  if (!ph.IsOnePass()) return;

  absl::string_view text("hello");
  absl::string_view match;
  bool result = ph.prog->SearchOnePass(text, text, Prog::kAnchored,
                                        Prog::kFullMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, "hello");
}

// Test with alternation
TEST_F(SearchOnePassTest_567, Alternation_567) {
  ProgHolder ph("abc|def");
  ASSERT_TRUE(ph.IsValid());
  if (!ph.IsOnePass()) return;

  absl::string_view text("def");
  absl::string_view match;
  bool result = ph.prog->SearchOnePass(text, text, Prog::kAnchored,
                                        Prog::kFullMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, "def");
}

// Test optional group
TEST_F(SearchOnePassTest_567, OptionalGroup_567) {
  ProgHolder ph("a(b)?c");
  ASSERT_TRUE(ph.IsValid());
  if (!ph.IsOnePass()) return;

  {
    absl::string_view text("abc");
    absl::string_view match[2];
    bool result = ph.prog->SearchOnePass(text, text, Prog::kAnchored,
                                          Prog::kFullMatch, match, 2);
    EXPECT_TRUE(result);
    EXPECT_EQ(match[0], "abc");
    EXPECT_EQ(match[1], "b");
  }

  {
    absl::string_view text("ac");
    absl::string_view match[2];
    bool result = ph.prog->SearchOnePass(text, text, Prog::kAnchored,
                                          Prog::kFullMatch, match, 2);
    EXPECT_TRUE(result);
    EXPECT_EQ(match[0], "ac");
  }
}

// Test anchored first match
TEST_F(SearchOnePassTest_567, AnchoredFirstMatch_567) {
  ProgHolder ph("a+");
  ASSERT_TRUE(ph.IsValid());
  if (!ph.IsOnePass()) return;

  absl::string_view text("aaa");
  absl::string_view match;
  bool result = ph.prog->SearchOnePass(text, text, Prog::kAnchored,
                                        Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(result);
}

// Test context different from text - anchor_start
TEST_F(SearchOnePassTest_567, ContextDifferentFromTextAnchorStart_567) {
  ProgHolder ph("abc");
  ASSERT_TRUE(ph.IsValid());
  if (!ph.IsOnePass()) return;

  // If anchor_start is set and context begins before text, should fail
  if (ph.prog->anchor_start()) {
    std::string full = "xabc";
    absl::string_view context(full);
    absl::string_view text(full.data() + 1, 3);
    absl::string_view match;
    bool result = ph.prog->SearchOnePass(text, context, Prog::kAnchored,
                                          Prog::kFullMatch, &match, 1);
    EXPECT_FALSE(result);
  }
}

// Test through RE2 high-level API to ensure one-pass is exercised
TEST_F(SearchOnePassTest_567, RE2FullMatchSimple_567) {
  RE2 re("(\\d+)-(\\d+)");
  std::string s1, s2;
  EXPECT_TRUE(RE2::FullMatch("123-456", re, &s1, &s2));
  EXPECT_EQ(s1, "123");
  EXPECT_EQ(s2, "456");
}

TEST_F(SearchOnePassTest_567, RE2FullMatchFails_567) {
  RE2 re("(\\d+)-(\\d+)");
  std::string s1, s2;
  EXPECT_FALSE(RE2::FullMatch("123-abc", re, &s1, &s2));
}

// Test with single character
TEST_F(SearchOnePassTest_567, SingleChar_567) {
  ProgHolder ph("a");
  ASSERT_TRUE(ph.IsValid());
  if (!ph.IsOnePass()) return;

  absl::string_view text("a");
  absl::string_view match;
  bool result = ph.prog->SearchOnePass(text, text, Prog::kAnchored,
                                        Prog::kFullMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, "a");
}

// Test nmatch = 1 with capture pattern (captures beyond nmatch ignored)
TEST_F(SearchOnePassTest_567, NmatchLessThanCaptures_567) {
  ProgHolder ph("(a)(b)");
  ASSERT_TRUE(ph.IsValid());
  if (!ph.IsOnePass()) return;

  absl::string_view text("ab");
  absl::string_view match;
  bool result = ph.prog->SearchOnePass(text, text, Prog::kAnchored,
                                        Prog::kFullMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, "ab");
}

// Test with dot matching
TEST_F(SearchOnePassTest_567, DotMatching_567) {
  ProgHolder ph("a.c");
  ASSERT_TRUE(ph.IsValid());
  if (!ph.IsOnePass()) return;

  absl::string_view text("axc");
  absl::string_view match;
  bool result = ph.prog->SearchOnePass(text, text, Prog::kAnchored,
                                        Prog::kFullMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, "axc");
}

// Test empty text with non-empty pattern
TEST_F(SearchOnePassTest_567, EmptyTextNonEmptyPattern_567) {
  ProgHolder ph("a");
  ASSERT_TRUE(ph.IsValid());
  if (!ph.IsOnePass()) return;

  absl::string_view text("");
  absl::string_view match;
  bool result = ph.prog->SearchOnePass(text, text, Prog::kAnchored,
                                        Prog::kFullMatch, &match, 1);
  EXPECT_FALSE(result);
}

}  // namespace re2
