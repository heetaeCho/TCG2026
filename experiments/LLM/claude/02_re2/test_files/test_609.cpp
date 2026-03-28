#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "re2/sparse_array.h"
#include "absl/strings/string_view.h"

#include <string>
#include <vector>

namespace re2 {

class NFATest_609 : public ::testing::Test {
 protected:
  // Helper to compile a pattern into a Prog
  Prog* CompilePattern(const std::string& pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    if (re == nullptr) return nullptr;
    Prog* prog = re->CompileToProg(0);
    re->Decref();
    return prog;
  }
};

// Test basic NFA search with a simple literal match
TEST_F(NFATest_609, SimpleLiteralMatch_609) {
  Prog* prog = CompilePattern("hello");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");

  delete prog;
}

// Test NFA search with no match
TEST_F(NFATest_609, NoMatch_609) {
  Prog* prog = CompilePattern("xyz");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);

  delete prog;
}

// Test unanchored NFA search
TEST_F(NFATest_609, UnanchoredSearch_609) {
  Prog* prog = CompilePattern("world");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "world");

  delete prog;
}

// Test NFA search with empty text
TEST_F(NFATest_609, EmptyText_609) {
  Prog* prog = CompilePattern("hello");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);

  delete prog;
}

// Test NFA search with empty pattern (matches empty string)
TEST_F(NFATest_609, EmptyPattern_609) {
  Prog* prog = CompilePattern("");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match.size(), 0);

  delete prog;
}

// Test NFA search with capture groups
TEST_F(NFATest_609, CaptureGroups_609) {
  Prog* prog = CompilePattern("(hel)(lo)");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  absl::string_view match[3];
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, match, 3);
  EXPECT_TRUE(found);
  EXPECT_EQ(match[0], "hello");
  EXPECT_EQ(match[1], "hel");
  EXPECT_EQ(match[2], "lo");

  delete prog;
}

// Test NFA search with longest match
TEST_F(NFATest_609, LongestMatch_609) {
  Prog* prog = CompilePattern("a+");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("aaaaab");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kLongestMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "aaaaa");

  delete prog;
}

// Test NFA search with character class
TEST_F(NFATest_609, CharacterClass_609) {
  Prog* prog = CompilePattern("[a-z]+");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello123");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");

  delete prog;
}

// Test NFA search with alternation
TEST_F(NFATest_609, Alternation_609) {
  Prog* prog = CompilePattern("cat|dog");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("dog");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "dog");

  delete prog;
}

// Test NFA search with dot-star pattern
TEST_F(NFATest_609, DotStar_609) {
  Prog* prog = CompilePattern(".*");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kLongestMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello world");

  delete prog;
}

// Test NFA search with zero submatch (just boolean match)
TEST_F(NFATest_609, ZeroSubmatch_609) {
  Prog* prog = CompilePattern("hello");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, nullptr, 0);
  EXPECT_TRUE(found);

  delete prog;
}

// Test NFA search anchored at start - should not match in middle
TEST_F(NFATest_609, AnchoredNoMatchInMiddle_609) {
  Prog* prog = CompilePattern("world");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);

  delete prog;
}

// Test NFA search with repetition
TEST_F(NFATest_609, Repetition_609) {
  Prog* prog = CompilePattern("ab{2,4}c");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("abbbc");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abbbc");

  delete prog;
}

// Test NFA search with optional group
TEST_F(NFATest_609, OptionalGroup_609) {
  Prog* prog = CompilePattern("colou?r");
  ASSERT_NE(prog, nullptr);

  absl::string_view text1("color");
  absl::string_view match1;
  bool found1 = prog->SearchNFA(text1, text1, Prog::kAnchored,
                                  Prog::kFirstMatch, &match1, 1);
  EXPECT_TRUE(found1);
  EXPECT_EQ(match1, "color");

  absl::string_view text2("colour");
  absl::string_view match2;
  bool found2 = prog->SearchNFA(text2, text2, Prog::kAnchored,
                                  Prog::kFirstMatch, &match2, 1);
  EXPECT_TRUE(found2);
  EXPECT_EQ(match2, "colour");

  delete prog;
}

// Test NFA search with word boundary-like pattern
TEST_F(NFATest_609, WordPattern_609) {
  Prog* prog = CompilePattern("\\w+");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");

  delete prog;
}

// Test NFA search - single character text
TEST_F(NFATest_609, SingleCharText_609) {
  Prog* prog = CompilePattern("a");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("a");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "a");

  delete prog;
}

// Test NFA with nested capture groups
TEST_F(NFATest_609, NestedCaptureGroups_609) {
  Prog* prog = CompilePattern("((a)(b))");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("ab");
  absl::string_view match[4];
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, match, 4);
  EXPECT_TRUE(found);
  EXPECT_EQ(match[0], "ab");
  EXPECT_EQ(match[1], "ab");
  EXPECT_EQ(match[2], "a");
  EXPECT_EQ(match[3], "b");

  delete prog;
}

// Test NFA search with context different from text
TEST_F(NFATest_609, DifferentContext_609) {
  Prog* prog = CompilePattern("world");
  ASSERT_NE(prog, nullptr);

  std::string full("hello world");
  absl::string_view context(full);
  absl::string_view text(full.data() + 6, 5);  // "world"
  absl::string_view match;
  bool found = prog->SearchNFA(text, context, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "world");

  delete prog;
}

// Test NFA search with both empty text and empty pattern
TEST_F(NFATest_609, BothEmpty_609) {
  Prog* prog = CompilePattern("");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match.size(), 0);

  delete prog;
}

// Test NFA with anchor end-of-string
TEST_F(NFATest_609, AnchorEnd_609) {
  Prog* prog = CompilePattern("world$");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "world");

  delete prog;
}

// Test NFA first match vs longest match behavior
TEST_F(NFATest_609, FirstVsLongestMatch_609) {
  Prog* prog = CompilePattern("a*");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("aaaa");
  
  absl::string_view match_first;
  bool found_first = prog->SearchNFA(text, text, Prog::kAnchored,
                                      Prog::kFirstMatch, &match_first, 1);
  EXPECT_TRUE(found_first);

  absl::string_view match_longest;
  bool found_longest = prog->SearchNFA(text, text, Prog::kAnchored,
                                        Prog::kLongestMatch, &match_longest, 1);
  EXPECT_TRUE(found_longest);
  EXPECT_EQ(match_longest, "aaaa");

  delete prog;
}

}  // namespace re2
