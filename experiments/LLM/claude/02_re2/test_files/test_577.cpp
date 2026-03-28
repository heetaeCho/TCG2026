#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "absl/strings/string_view.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"

namespace re2 {

// Helper function to compile a regex pattern into a Prog
static Prog* CompileProg(const std::string& pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  if (re == nullptr) return nullptr;
  Prog* prog = re->CompileToProg(0);
  re->Decref();
  return prog;
}

class NFASearchTest_577 : public ::testing::Test {
 protected:
  void TearDown() override {
    for (auto* p : progs_) {
      delete p;
    }
    progs_.clear();
  }

  Prog* MakeProg(const std::string& pattern) {
    Prog* prog = CompileProg(pattern);
    if (prog) progs_.push_back(prog);
    return prog;
  }

  std::vector<Prog*> progs_;
};

// Test basic literal match
TEST_F(NFASearchTest_577, SimpleLiteralMatch_577) {
  Prog* prog = MakeProg("hello");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
}

// Test no match
TEST_F(NFASearchTest_577, NoMatch_577) {
  Prog* prog = MakeProg("xyz");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test anchored match at beginning
TEST_F(NFASearchTest_577, AnchoredMatchAtBeginning_577) {
  Prog* prog = MakeProg("hello");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
}

// Test anchored match fails when pattern not at start
TEST_F(NFASearchTest_577, AnchoredMatchFails_577) {
  Prog* prog = MakeProg("world");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test empty string match
TEST_F(NFASearchTest_577, EmptyPatternMatch_577) {
  Prog* prog = MakeProg("");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match.size(), 0);
}

// Test empty text
TEST_F(NFASearchTest_577, EmptyText_577) {
  Prog* prog = MakeProg("");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
}

// Test empty text with non-empty pattern
TEST_F(NFASearchTest_577, EmptyTextNoMatch_577) {
  Prog* prog = MakeProg("a");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test with submatch groups
TEST_F(NFASearchTest_577, SubmatchCapture_577) {
  Prog* prog = MakeProg("(h)(ello)");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  absl::string_view match[3];
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, match, 3);
  EXPECT_TRUE(found);
  EXPECT_EQ(match[0], "hello");
  EXPECT_EQ(match[1], "h");
  EXPECT_EQ(match[2], "ello");
}

// Test with zero submatches
TEST_F(NFASearchTest_577, ZeroSubmatches_577) {
  Prog* prog = MakeProg("hello");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, nullptr, 0);
  EXPECT_TRUE(found);
}

// Test longest match
TEST_F(NFASearchTest_577, LongestMatch_577) {
  Prog* prog = MakeProg("a+");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("aaa");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kLongestMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "aaa");
}

// Test first match (greedy by default but first match mode)
TEST_F(NFASearchTest_577, FirstMatch_577) {
  Prog* prog = MakeProg("a+");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("aaa bbb aaa");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "aaa");
}

// Test regex with alternation
TEST_F(NFASearchTest_577, Alternation_577) {
  Prog* prog = MakeProg("cat|dog");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("I have a dog");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "dog");
}

// Test regex with character class
TEST_F(NFASearchTest_577, CharacterClass_577) {
  Prog* prog = MakeProg("[0-9]+");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("abc 123 def");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "123");
}

// Test with context different from text (text is substring of context)
TEST_F(NFASearchTest_577, ContextContainsText_577) {
  Prog* prog = MakeProg("world");
  ASSERT_NE(prog, nullptr);

  std::string full = "hello world goodbye";
  absl::string_view context(full);
  // text is a substring of context
  absl::string_view text(full.data() + 6, 5);  // "world"
  absl::string_view match;
  bool found = prog->SearchNFA(text, context, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "world");
}

// Test dot matches various characters
TEST_F(NFASearchTest_577, DotMatch_577) {
  Prog* prog = MakeProg("a.c");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("abc");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
}

// Test question mark (optional)
TEST_F(NFASearchTest_577, OptionalMatch_577) {
  Prog* prog = MakeProg("ab?c");
  ASSERT_NE(prog, nullptr);

  absl::string_view text1("abc");
  absl::string_view match1;
  bool found1 = prog->SearchNFA(text1, text1, Prog::kUnanchored,
                                  Prog::kFirstMatch, &match1, 1);
  EXPECT_TRUE(found1);
  EXPECT_EQ(match1, "abc");

  absl::string_view text2("ac");
  absl::string_view match2;
  bool found2 = prog->SearchNFA(text2, text2, Prog::kUnanchored,
                                  Prog::kFirstMatch, &match2, 1);
  EXPECT_TRUE(found2);
  EXPECT_EQ(match2, "ac");
}

// Test repetition
TEST_F(NFASearchTest_577, Repetition_577) {
  Prog* prog = MakeProg("a{3}");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("aaaa");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "aaa");
}

// Test star operator
TEST_F(NFASearchTest_577, StarOperator_577) {
  Prog* prog = MakeProg("ba*");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("baaa");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "baaa");
}

// Test anchor start pattern
TEST_F(NFASearchTest_577, AnchorStartPattern_577) {
  Prog* prog = MakeProg("^hello");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
}

// Test anchor end pattern
TEST_F(NFASearchTest_577, AnchorEndPattern_577) {
  Prog* prog = MakeProg("world$");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "world");
}

// Test multiple matches - first match returned in unanchored mode
TEST_F(NFASearchTest_577, MultipleOccurrencesFirstMatch_577) {
  Prog* prog = MakeProg("ab");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("ab cd ab");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "ab");
  // Should match the first occurrence
  EXPECT_EQ(match.data(), text.data());
}

// Test nested groups
TEST_F(NFASearchTest_577, NestedGroups_577) {
  Prog* prog = MakeProg("((a)(b))");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("ab");
  absl::string_view match[4];
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, match, 4);
  EXPECT_TRUE(found);
  EXPECT_EQ(match[0], "ab");
  EXPECT_EQ(match[1], "ab");
  EXPECT_EQ(match[2], "a");
  EXPECT_EQ(match[3], "b");
}

// Test single character match
TEST_F(NFASearchTest_577, SingleCharMatch_577) {
  Prog* prog = MakeProg("x");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("x");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "x");
}

// Test word boundary-like patterns
TEST_F(NFASearchTest_577, WordPattern_577) {
  Prog* prog = MakeProg("[a-z]+");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("123abc456");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
}

// Test with special characters in text
TEST_F(NFASearchTest_577, SpecialCharactersInText_577) {
  Prog* prog = MakeProg("a\\+b");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("a+b");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "a+b");
}

// Test longest match with alternation
TEST_F(NFASearchTest_577, LongestMatchAlternation_577) {
  Prog* prog = MakeProg("a|aa");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("aa");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kLongestMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "aa");
}

// Test full match of entire string
TEST_F(NFASearchTest_577, FullStringMatch_577) {
  Prog* prog = MakeProg("hello");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
}

// Test with only one submatch requested out of multiple groups
TEST_F(NFASearchTest_577, PartialSubmatchRequest_577) {
  Prog* prog = MakeProg("(a)(b)(c)");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("abc");
  absl::string_view match[2];
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, match, 2);
  EXPECT_TRUE(found);
  EXPECT_EQ(match[0], "abc");
  EXPECT_EQ(match[1], "a");
}

}  // namespace re2
