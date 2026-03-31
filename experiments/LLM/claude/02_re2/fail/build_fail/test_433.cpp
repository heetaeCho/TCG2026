#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "re2/set.h"
#include "absl/strings/string_view.h"

#include <string>
#include <memory>
#include <vector>

namespace re2 {

class DFATest_433 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}

  // Helper to compile a pattern into a Prog
  std::unique_ptr<Regexp> CompileRegexp(const std::string& pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    return std::unique_ptr<Regexp>(re);
  }
};

// Test basic DFA search through RE2 - simple match
TEST_F(DFATest_433, SimpleMatch_433) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("world", re));
}

// Test DFA search with partial match
TEST_F(DFATest_433, PartialMatch_433) {
  RE2 re("ell");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("hello", re));
  EXPECT_FALSE(RE2::PartialMatch("world", re));
}

// Test DFA with empty pattern
TEST_F(DFATest_433, EmptyPattern_433) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_TRUE(RE2::PartialMatch("anything", re));
}

// Test DFA with empty text
TEST_F(DFATest_433, EmptyText_433) {
  RE2 re("a*");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
}

// Test DFA with complex regex
TEST_F(DFATest_433, ComplexPattern_433) {
  RE2 re("(a|b)+c*d?");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abc", re));
  EXPECT_TRUE(RE2::FullMatch("abccd", re));
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_FALSE(RE2::FullMatch("xyz", re));
}

// Test DFA with character classes
TEST_F(DFATest_433, CharacterClass_433) {
  RE2 re("[a-z]+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("HELLO", re));
  EXPECT_FALSE(RE2::FullMatch("hello123", re));
}

// Test DFA with anchored search
TEST_F(DFATest_433, AnchoredSearch_433) {
  RE2 re("^hello$");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("hello world", re));
}

// Test DFA with repetition patterns
TEST_F(DFATest_433, Repetition_433) {
  RE2 re("a{2,4}");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("aa", re));
  EXPECT_TRUE(RE2::FullMatch("aaa", re));
  EXPECT_TRUE(RE2::FullMatch("aaaa", re));
  EXPECT_FALSE(RE2::FullMatch("a", re));
  EXPECT_FALSE(RE2::FullMatch("aaaaa", re));
}

// Test DFA with dot matches
TEST_F(DFATest_433, DotMatch_433) {
  RE2 re("a.c");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abc", re));
  EXPECT_TRUE(RE2::FullMatch("aXc", re));
  EXPECT_FALSE(RE2::FullMatch("ac", re));
}

// Test PossibleMatchRange through RE2
TEST_F(DFATest_433, PossibleMatchRange_433) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  std::string min, max;
  EXPECT_TRUE(re.PossibleMatchRange(&min, &max, 10));
  EXPECT_LE(min, "hello");
  EXPECT_GE(max, "hello");
}

// Test PossibleMatchRange with alternation
TEST_F(DFATest_433, PossibleMatchRangeAlternation_433) {
  RE2 re("abc|xyz");
  ASSERT_TRUE(re.ok());
  std::string min, max;
  EXPECT_TRUE(re.PossibleMatchRange(&min, &max, 10));
  EXPECT_LE(min, "abc");
  EXPECT_GE(max, "xyz");
}

// Test PossibleMatchRange with maxlen boundary
TEST_F(DFATest_433, PossibleMatchRangeMaxLen_433) {
  RE2 re("a.*z");
  ASSERT_TRUE(re.ok());
  std::string min, max;
  EXPECT_TRUE(re.PossibleMatchRange(&min, &max, 1));
}

// Test DFA with very small max_mem through RE2::Options
TEST_F(DFATest_433, SmallMemoryBudget_433) {
  RE2::Options opts;
  opts.set_max_mem(256);
  RE2 re("(a|b|c|d|e)+", opts);
  // Even with small memory, basic matching should work or degrade gracefully
  if (re.ok()) {
    // It should still produce correct results even if DFA falls back
    bool result = RE2::PartialMatch("abcde", re);
    EXPECT_TRUE(result);
  }
}

// Test DFA with large text
TEST_F(DFATest_433, LargeText_433) {
  RE2 re("needle");
  ASSERT_TRUE(re.ok());
  std::string large_text(10000, 'x');
  EXPECT_FALSE(RE2::PartialMatch(large_text, re));
  large_text += "needle";
  EXPECT_TRUE(RE2::PartialMatch(large_text, re));
}

// Test DFA with alternation of many options
TEST_F(DFATest_433, ManyAlternations_433) {
  RE2 re("cat|dog|fish|bird|snake|horse");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("cat", re));
  EXPECT_TRUE(RE2::FullMatch("dog", re));
  EXPECT_TRUE(RE2::FullMatch("fish", re));
  EXPECT_TRUE(RE2::FullMatch("horse", re));
  EXPECT_FALSE(RE2::FullMatch("cow", re));
}

// Test DFA with unicode/byte patterns
TEST_F(DFATest_433, BytePatterns_433) {
  RE2 re("\\x41\\x42\\x43");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("ABC", re));
  EXPECT_FALSE(RE2::FullMatch("abc", re));
}

// Test DFA BuildAllStates through Prog interface
TEST_F(DFATest_433, BuildAllStatesSimple_433) {
  RegexpStatus status;
  std::unique_ptr<Regexp> regexp(Regexp::Parse("ab", Regexp::LikePerl, &status));
  ASSERT_TRUE(regexp != nullptr);
  std::unique_ptr<Prog> prog(regexp->CompileToProg(0));
  ASSERT_TRUE(prog != nullptr);

  int count = 0;
  prog->BuildEntireDFA(Prog::kFirstMatch, [&count](const int*, bool*, int) {
    count++;
  });
  // We just verify it runs without error
  EXPECT_GE(count, 0);
}

// Test DFA with RE2::Set which uses DFA internally
TEST_F(DFATest_433, RE2SetMatch_433) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  ASSERT_EQ(s.Add("foo", nullptr), 0);
  ASSERT_EQ(s.Add("bar", nullptr), 1);
  ASSERT_EQ(s.Add("baz", nullptr), 2);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("foobar", &matches));
  EXPECT_FALSE(matches.empty());
}

// Test DFA with no match on various inputs
TEST_F(DFATest_433, NoMatchVariousInputs_433) {
  RE2 re("^specific$");
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("", re));
  EXPECT_FALSE(RE2::FullMatch("spec", re));
  EXPECT_FALSE(RE2::FullMatch("specific extra", re));
  EXPECT_TRUE(RE2::FullMatch("specific", re));
}

// Test DFA with longest match semantics
TEST_F(DFATest_433, LongestMatch_433) {
  RE2::Options opts;
  opts.set_longest_match(true);
  RE2 re("a+", opts);
  ASSERT_TRUE(re.ok());
  
  absl::string_view match;
  EXPECT_TRUE(RE2::PartialMatch("aaaa", re, &match));
  EXPECT_EQ(match, "aaaa");
}

// Test DFA with single character
TEST_F(DFATest_433, SingleCharMatch_433) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_FALSE(RE2::FullMatch("b", re));
  EXPECT_FALSE(RE2::FullMatch("aa", re));
}

// Test DFA with star pattern
TEST_F(DFATest_433, StarPattern_433) {
  RE2 re("a*");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_TRUE(RE2::FullMatch("aaaaaa", re));
  EXPECT_FALSE(RE2::FullMatch("b", re));
}

// Test DFA with plus pattern
TEST_F(DFATest_433, PlusPattern_433) {
  RE2 re("a+");
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("", re));
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_TRUE(RE2::FullMatch("aaaaaa", re));
}

// Test DFA with optional pattern
TEST_F(DFATest_433, OptionalPattern_433) {
  RE2 re("ab?c");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("ac", re));
  EXPECT_TRUE(RE2::FullMatch("abc", re));
  EXPECT_FALSE(RE2::FullMatch("abbc", re));
}

// Test PossibleMatchRange with zero maxlen
TEST_F(DFATest_433, PossibleMatchRangeZeroMaxLen_433) {
  RE2 re("test");
  ASSERT_TRUE(re.ok());
  std::string min, max;
  // maxlen of 0 should still work or return false gracefully
  bool result = re.PossibleMatchRange(&min, &max, 0);
  // Just verify it doesn't crash; result depends on implementation
  (void)result;
}

// Test concurrent DFA searches (DFA uses caching with mutexes)
TEST_F(DFATest_433, ConcurrentSearches_433) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  
  std::vector<std::thread> threads;
  std::atomic<int> match_count{0};
  
  for (int i = 0; i < 10; i++) {
    threads.emplace_back([&re, &match_count]() {
      for (int j = 0; j < 100; j++) {
        if (RE2::PartialMatch("hello world", re)) {
          match_count++;
        }
      }
    });
  }
  
  for (auto& t : threads) {
    t.join();
  }
  
  EXPECT_EQ(match_count.load(), 1000);
}

}  // namespace re2
