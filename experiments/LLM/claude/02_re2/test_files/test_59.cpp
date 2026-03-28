#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <utility>
#include "re2/re2.h"

// Since RE2MatchShim is in re2_python namespace and uses pybind11 types (py::buffer),
// we cannot directly test it without the Python runtime. Instead, we test the
// underlying RE2 functionality that RE2MatchShim relies on, specifically RE2::Match
// and related methods, which constitute the actual testable interface.

namespace {

class RE2MatchTest_59 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test basic construction and pattern retrieval
TEST_F(RE2MatchTest_59, ConstructFromString_59) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("hello", re.pattern());
}

TEST_F(RE2MatchTest_59, ConstructFromStringView_59) {
  absl::string_view sv("world");
  RE2 re(sv);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ("world", re.pattern());
}

TEST_F(RE2MatchTest_59, InvalidPattern_59) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(RE2::NoError, re.error_code());
}

// Test NumberOfCapturingGroups
TEST_F(RE2MatchTest_59, NumberOfCapturingGroupsNoGroups_59) {
  RE2 re("hello");
  EXPECT_EQ(0, re.NumberOfCapturingGroups());
}

TEST_F(RE2MatchTest_59, NumberOfCapturingGroupsOneGroup_59) {
  RE2 re("(hello)");
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

TEST_F(RE2MatchTest_59, NumberOfCapturingGroupsMultipleGroups_59) {
  RE2 re("(a)(b)(c)");
  EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

TEST_F(RE2MatchTest_59, NumberOfCapturingGroupsNestedGroups_59) {
  RE2 re("((a)(b))");
  EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

TEST_F(RE2MatchTest_59, NumberOfCapturingGroupsNonCapturing_59) {
  RE2 re("(?:hello)(world)");
  EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

// Test RE2::Match - simulating the core of RE2MatchShim
TEST_F(RE2MatchTest_59, MatchUnanchoredSuccess_59) {
  RE2 re("(\\w+)@(\\w+)");
  ASSERT_TRUE(re.ok());
  
  std::string text = "test@example";
  int num_groups = re.NumberOfCapturingGroups() + 1;
  EXPECT_EQ(3, num_groups);
  
  std::vector<absl::string_view> groups(num_groups);
  bool matched = re.Match(text, 0, text.size(), RE2::UNANCHORED,
                           groups.data(), groups.size());
  EXPECT_TRUE(matched);
  EXPECT_EQ("test@example", groups[0]);
  EXPECT_EQ("test", groups[1]);
  EXPECT_EQ("example", groups[2]);
}

TEST_F(RE2MatchTest_59, MatchUnanchoredFailure_59) {
  RE2 re("(\\d+)");
  ASSERT_TRUE(re.ok());
  
  std::string text = "no digits here";
  int num_groups = re.NumberOfCapturingGroups() + 1;
  std::vector<absl::string_view> groups(num_groups);
  
  bool matched = re.Match(text, 0, text.size(), RE2::UNANCHORED,
                           groups.data(), groups.size());
  EXPECT_FALSE(matched);
}

TEST_F(RE2MatchTest_59, MatchAnchorStart_59) {
  RE2 re("(hello)");
  ASSERT_TRUE(re.ok());
  
  std::string text = "hello world";
  int num_groups = re.NumberOfCapturingGroups() + 1;
  std::vector<absl::string_view> groups(num_groups);
  
  bool matched = re.Match(text, 0, text.size(), RE2::ANCHOR_START,
                           groups.data(), groups.size());
  EXPECT_TRUE(matched);
  EXPECT_EQ("hello", groups[0]);
  EXPECT_EQ("hello", groups[1]);
}

TEST_F(RE2MatchTest_59, MatchAnchorStartFail_59) {
  RE2 re("(world)");
  ASSERT_TRUE(re.ok());
  
  std::string text = "hello world";
  int num_groups = re.NumberOfCapturingGroups() + 1;
  std::vector<absl::string_view> groups(num_groups);
  
  bool matched = re.Match(text, 0, text.size(), RE2::ANCHOR_START,
                           groups.data(), groups.size());
  EXPECT_FALSE(matched);
}

TEST_F(RE2MatchTest_59, MatchAnchorBoth_59) {
  RE2 re("(hello world)");
  ASSERT_TRUE(re.ok());
  
  std::string text = "hello world";
  int num_groups = re.NumberOfCapturingGroups() + 1;
  std::vector<absl::string_view> groups(num_groups);
  
  bool matched = re.Match(text, 0, text.size(), RE2::ANCHOR_BOTH,
                           groups.data(), groups.size());
  EXPECT_TRUE(matched);
}

TEST_F(RE2MatchTest_59, MatchAnchorBothFail_59) {
  RE2 re("(hello)");
  ASSERT_TRUE(re.ok());
  
  std::string text = "hello world";
  int num_groups = re.NumberOfCapturingGroups() + 1;
  std::vector<absl::string_view> groups(num_groups);
  
  bool matched = re.Match(text, 0, text.size(), RE2::ANCHOR_BOTH,
                           groups.data(), groups.size());
  EXPECT_FALSE(matched);
}

// Test Match with pos and endpos (partial text matching)
TEST_F(RE2MatchTest_59, MatchWithPosOffset_59) {
  RE2 re("(\\d+)");
  ASSERT_TRUE(re.ok());
  
  std::string text = "abc123def";
  int num_groups = re.NumberOfCapturingGroups() + 1;
  std::vector<absl::string_view> groups(num_groups);
  
  bool matched = re.Match(text, 3, text.size(), RE2::UNANCHORED,
                           groups.data(), groups.size());
  EXPECT_TRUE(matched);
  EXPECT_EQ("123", groups[0]);
}

TEST_F(RE2MatchTest_59, MatchWithEndpos_59) {
  RE2 re("(\\d+)");
  ASSERT_TRUE(re.ok());
  
  std::string text = "abc123def456";
  int num_groups = re.NumberOfCapturingGroups() + 1;
  std::vector<absl::string_view> groups(num_groups);
  
  // Only search in "abc12"
  bool matched = re.Match(text, 0, 5, RE2::UNANCHORED,
                           groups.data(), groups.size());
  EXPECT_TRUE(matched);
  EXPECT_EQ("12", groups[0]);
}

TEST_F(RE2MatchTest_59, MatchWithPosAndEndpos_59) {
  RE2 re("(\\w+)");
  ASSERT_TRUE(re.ok());
  
  std::string text = "hello world";
  int num_groups = re.NumberOfCapturingGroups() + 1;
  std::vector<absl::string_view> groups(num_groups);
  
  // Match from pos=6, endpos=11 -> "world"
  bool matched = re.Match(text, 6, 11, RE2::UNANCHORED,
                           groups.data(), groups.size());
  EXPECT_TRUE(matched);
  EXPECT_EQ("world", groups[0]);
}

// Test span computation as done in RE2MatchShim
TEST_F(RE2MatchTest_59, SpanComputation_59) {
  RE2 re("(\\w+)@(\\w+)");
  ASSERT_TRUE(re.ok());
  
  std::string text = "user@host";
  int num_groups = re.NumberOfCapturingGroups() + 1;
  std::vector<absl::string_view> groups(num_groups);
  
  bool matched = re.Match(text, 0, text.size(), RE2::UNANCHORED,
                           groups.data(), groups.size());
  ASSERT_TRUE(matched);
  
  // Compute spans like RE2MatchShim does
  std::vector<std::pair<ssize_t, ssize_t>> spans;
  spans.reserve(num_groups);
  for (const auto& it : groups) {
    if (it.data() == nullptr) {
      spans.emplace_back(-1, -1);
    } else {
      spans.emplace_back(it.data() - text.data(),
                         it.data() - text.data() + it.size());
    }
  }
  
  ASSERT_EQ(3u, spans.size());
  // Group 0: full match "user@host" -> (0, 9)
  EXPECT_EQ(0, spans[0].first);
  EXPECT_EQ(9, spans[0].second);
  // Group 1: "user" -> (0, 4)
  EXPECT_EQ(0, spans[1].first);
  EXPECT_EQ(4, spans[1].second);
  // Group 2: "host" -> (5, 9)
  EXPECT_EQ(5, spans[2].first);
  EXPECT_EQ(9, spans[2].second);
}

// Test span computation for non-matching groups
TEST_F(RE2MatchTest_59, SpanComputationOptionalGroup_59) {
  RE2 re("(a)(b)?(c)");
  ASSERT_TRUE(re.ok());
  
  std::string text = "ac";
  int num_groups = re.NumberOfCapturingGroups() + 1;
  std::vector<absl::string_view> groups(num_groups);
  
  bool matched = re.Match(text, 0, text.size(), RE2::UNANCHORED,
                           groups.data(), groups.size());
  ASSERT_TRUE(matched);
  
  std::vector<std::pair<ssize_t, ssize_t>> spans;
  spans.reserve(num_groups);
  for (const auto& it : groups) {
    if (it.data() == nullptr) {
      spans.emplace_back(-1, -1);
    } else {
      spans.emplace_back(it.data() - text.data(),
                         it.data() - text.data() + it.size());
    }
  }
  
  ASSERT_EQ(4u, spans.size());
  // Group 0: "ac" -> (0, 2)
  EXPECT_EQ(0, spans[0].first);
  EXPECT_EQ(2, spans[0].second);
  // Group 1: "a" -> (0, 1)
  EXPECT_EQ(0, spans[1].first);
  EXPECT_EQ(1, spans[1].second);
  // Group 2: not matched -> (-1, -1)
  EXPECT_EQ(-1, spans[2].first);
  EXPECT_EQ(-1, spans[2].second);
  // Group 3: "c" -> (1, 2)
  EXPECT_EQ(1, spans[3].first);
  EXPECT_EQ(2, spans[3].second);
}

// Test span computation for no match at all
TEST_F(RE2MatchTest_59, SpanComputationNoMatch_59) {
  RE2 re("(x)(y)");
  ASSERT_TRUE(re.ok());
  
  std::string text = "abc";
  int num_groups = re.NumberOfCapturingGroups() + 1;
  std::vector<absl::string_view> groups(num_groups);
  
  bool matched = re.Match(text, 0, text.size(), RE2::UNANCHORED,
                           groups.data(), groups.size());
  EXPECT_FALSE(matched);
  
  // Simulate RE2MatchShim behavior: clear groups on no match
  for (auto& it : groups) {
    it = absl::string_view();
  }
  
  std::vector<std::pair<ssize_t, ssize_t>> spans;
  spans.reserve(num_groups);
  for (const auto& it : groups) {
    if (it.data() == nullptr) {
      spans.emplace_back(-1, -1);
    } else {
      spans.emplace_back(it.data() - text.data(),
                         it.data() - text.data() + it.size());
    }
  }
  
  ASSERT_EQ(3u, spans.size());
  for (const auto& span : spans) {
    EXPECT_EQ(-1, span.first);
    EXPECT_EQ(-1, span.second);
  }
}

// Test empty pattern
TEST_F(RE2MatchTest_59, EmptyPattern_59) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(0, re.NumberOfCapturingGroups());
  
  std::string text = "hello";
  std::vector<absl::string_view> groups(1);
  
  bool matched = re.Match(text, 0, text.size(), RE2::UNANCHORED,
                           groups.data(), groups.size());
  EXPECT_TRUE(matched);
  EXPECT_EQ("", groups[0]);
}

// Test empty text
TEST_F(RE2MatchTest_59, EmptyText_59) {
  RE2 re("(.*)");
  ASSERT_TRUE(re.ok());
  
  std::string text = "";
  int num_groups = re.NumberOfCapturingGroups() + 1;
  std::vector<absl::string_view> groups(num_groups);
  
  bool matched = re.Match(text, 0, text.size(), RE2::UNANCHORED,
                           groups.data(), groups.size());
  EXPECT_TRUE(matched);
  EXPECT_EQ(0u, groups[0].size());
}

// Test empty text with non-matching pattern
TEST_F(RE2MatchTest_59, EmptyTextNoMatch_59) {
  RE2 re("(.+)");
  ASSERT_TRUE(re.ok());
  
  std::string text = "";
  int num_groups = re.NumberOfCapturingGroups() + 1;
  std::vector<absl::string_view> groups(num_groups);
  
  bool matched = re.Match(text, 0, text.size(), RE2::UNANCHORED,
                           groups.data(), groups.size());
  EXPECT_FALSE(matched);
}

// Test pos == endpos boundary
TEST_F(RE2MatchTest_59, PosEqualsEndpos_59) {
  RE2 re("(.*)");
  ASSERT_TRUE(re.ok());
  
  std::string text = "hello";
  int num_groups = re.NumberOfCapturingGroups() + 1;
  std::vector<absl::string_view> groups(num_groups);
  
  bool matched = re.Match(text, 3, 3, RE2::UNANCHORED,
                           groups.data(), groups.size());
  EXPECT_TRUE(matched);  // .* matches empty string
  EXPECT_EQ(0u, groups[0].size());
}

// Test FullMatch
TEST_F(RE2MatchTest_59, FullMatchSimple_59) {
  EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
  EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

// Test PartialMatch
TEST_F(RE2MatchTest_59, PartialMatchSimple_59) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", "hello"));
  EXPECT_FALSE(RE2::PartialMatch("goodbye world", "hello"));
}

// Test FullMatch with capture
TEST_F(RE2MatchTest_59, FullMatchWithCapture_59) {
  std::string captured;
  EXPECT_TRUE(RE2::FullMatch("hello123", "(\\w+)(\\d+)", &captured));
}

// Test Replace
TEST_F(RE2MatchTest_59, ReplaceSimple_59) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, "world", "universe"));
  EXPECT_EQ("hello universe", s);
}

// Test GlobalReplace
TEST_F(RE2MatchTest_59, GlobalReplaceSimple_59) {
  std::string s = "aaa";
  int count = RE2::GlobalReplace(&s, "a", "bb");
  EXPECT_EQ(3, count);
  EXPECT_EQ("bbbbbb", s);
}

// Test Extract
TEST_F(RE2MatchTest_59, ExtractSimple_59) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremvax.ru", "(\\w+)@([\\w.]+)",
                            "\\2!\\1", &out));
  EXPECT_EQ("kremvax.ru!boris", out);
}

// Test QuoteMeta
TEST_F(RE2MatchTest_59, QuoteMeta_59) {
  std::string quoted = RE2::QuoteMeta("hello.world*foo");
  EXPECT_TRUE(RE2::FullMatch("hello.world*foo", quoted));
  EXPECT_FALSE(RE2::FullMatch("helloxworldxfoo", quoted));
}

// Test named capturing groups
TEST_F(RE2MatchTest_59, NamedCapturingGroups_59) {
  RE2 re("(?P<name>\\w+)@(?P<domain>\\w+)");
  ASSERT_TRUE(re.ok());
  
  const auto& named = re.NamedCapturingGroups();
  EXPECT_EQ(2u, named.size());
  EXPECT_EQ(1, named.at("name"));
  EXPECT_EQ(2, named.at("domain"));
}

// Test CapturingGroupNames
TEST_F(RE2MatchTest_59, CapturingGroupNames_59) {
  RE2 re("(?P<name>\\w+)@(?P<domain>\\w+)");
  ASSERT_TRUE(re.ok());
  
  const auto& group_names = re.CapturingGroupNames();
  EXPECT_EQ(2u, group_names.size());
  EXPECT_EQ("name", group_names.at(1));
  EXPECT_EQ("domain", group_names.at(2));
}

// Test complex pattern with alternation
TEST_F(RE2MatchTest_59, MatchAlternation_59) {
  RE2 re("(cat|dog)");
  ASSERT_TRUE(re.ok());
  
  std::string text = "I have a dog";
  int num_groups = re.NumberOfCapturingGroups() + 1;
  std::vector<absl::string_view> groups(num_groups);
  
  bool matched = re.Match(text, 0, text.size(), RE2::UNANCHORED,
                           groups.data(), groups.size());
  EXPECT_TRUE(matched);
  EXPECT_EQ("dog", groups[1]);
}

// Test match at beginning of text with pos offset
TEST_F(RE2MatchTest_59, MatchAtPosWithAnchorStart_59) {
  RE2 re("(\\d+)");
  ASSERT_TRUE(re.ok());
  
  std::string text = "abc123";
  int num_groups = re.NumberOfCapturingGroups() + 1;
  std::vector<absl::string_view> groups(num_groups);
  
  // ANCHOR_START with pos=3 should match at position 3
  bool matched = re.Match(text, 3, text.size(), RE2::ANCHOR_START,
                           groups.data(), groups.size());
  EXPECT_TRUE(matched);
  EXPECT_EQ("123", groups[0]);
}

// Test that CheckRewriteString works
TEST_F(RE2MatchTest_59, CheckRewriteString_59) {
  RE2 re("(\\w+)");
  ASSERT_TRUE(re.ok());
  
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\0-\\1", &error));
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
}

// Test MaxSubmatch
TEST_F(RE2MatchTest_59, MaxSubmatch_59) {
  EXPECT_EQ(0, RE2::MaxSubmatch("no groups"));
  EXPECT_EQ(1, RE2::MaxSubmatch("\\1"));
  EXPECT_EQ(3, RE2::MaxSubmatch("\\1 \\2 \\3"));
}

// Test PossibleMatchRange
TEST_F(RE2MatchTest_59, PossibleMatchRange_59) {
  RE2 re("abc.*");
  ASSERT_TRUE(re.ok());
  
  std::string min_str, max_str;
  EXPECT_TRUE(re.PossibleMatchRange(&min_str, &max_str, 10));
  EXPECT_LE(min_str, "abc");
  EXPECT_GE(max_str, "abc");
}

// Test Rewrite
TEST_F(RE2MatchTest_59, Rewrite_59) {
  RE2 re("(\\w+):(\\d+)");
  ASSERT_TRUE(re.ok());
  
  std::string text = "host:8080";
  int num_groups = re.NumberOfCapturingGroups() + 1;
  std::vector<absl::string_view> groups(num_groups);
  
  bool matched = re.Match(text, 0, text.size(), RE2::ANCHOR_BOTH,
                           groups.data(), groups.size());
  ASSERT_TRUE(matched);
  
  std::string out;
  EXPECT_TRUE(re.Rewrite(&out, "\\2-\\1", groups.data(), groups.size()));
  EXPECT_EQ("8080-host", out);
}

// Test with zero-width match
TEST_F(RE2MatchTest_59, ZeroWidthMatch_59) {
  RE2 re("^");
  ASSERT_TRUE(re.ok());
  
  std::string text = "hello";
  std::vector<absl::string_view> groups(1);
  
  bool matched = re.Match(text, 0, text.size(), RE2::UNANCHORED,
                           groups.data(), groups.size());
  EXPECT_TRUE(matched);
  EXPECT_EQ(0u, groups[0].size());
}

// Test error_arg on invalid pattern
TEST_F(RE2MatchTest_59, ErrorArg_59) {
  RE2 re("[invalid");
  EXPECT_FALSE(re.ok());
  EXPECT_FALSE(re.error().empty());
}

// Test options
TEST_F(RE2MatchTest_59, MatchCaseInsensitive_59) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  ASSERT_TRUE(re.ok());
  
  std::string text = "HELLO";
  std::vector<absl::string_view> groups(1);
  
  bool matched = re.Match(text, 0, text.size(), RE2::ANCHOR_BOTH,
                           groups.data(), groups.size());
  EXPECT_TRUE(matched);
}

// Test that pattern with many groups works correctly
TEST_F(RE2MatchTest_59, ManyCapturingGroups_59) {
  RE2 re("(a)(b)(c)(d)(e)");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(5, re.NumberOfCapturingGroups());
  
  std::string text = "abcde";
  int num_groups = re.NumberOfCapturingGroups() + 1;
  std::vector<absl::string_view> groups(num_groups);
  
  bool matched = re.Match(text, 0, text.size(), RE2::ANCHOR_BOTH,
                           groups.data(), groups.size());
  ASSERT_TRUE(matched);
  
  EXPECT_EQ("abcde", groups[0]);
  EXPECT_EQ("a", groups[1]);
  EXPECT_EQ("b", groups[2]);
  EXPECT_EQ("c", groups[3]);
  EXPECT_EQ("d", groups[4]);
  EXPECT_EQ("e", groups[5]);
}

// Test Consume
TEST_F(RE2MatchTest_59, ConsumeSimple_59) {
  absl::string_view input("abc123def456");
  std::string word;
  EXPECT_TRUE(RE2::Consume(&input, "(\\w+)", &word));
  EXPECT_EQ("abc123def456", word);
}

// Test FindAndConsume
TEST_F(RE2MatchTest_59, FindAndConsumeSimple_59) {
  absl::string_view input("abc 123 def 456");
  std::string num;
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &num));
  EXPECT_EQ("123", num);
  EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &num));
  EXPECT_EQ("456", num);
  EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &num));
}

}  // namespace
