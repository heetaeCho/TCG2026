#include "re2/re2.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <map>

namespace {

// ===========================================================================
// PartialMatchN Tests
// ===========================================================================

TEST(RE2PartialMatchNTest_253, SimpleMatchNoArgs_253) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatchN("say hello world", re, nullptr, 0));
}

TEST(RE2PartialMatchNTest_253, SimpleMatchFails_253) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(RE2::PartialMatchN("say helo world", re, nullptr, 0));
}

TEST(RE2PartialMatchNTest_253, MatchWithCapture_253) {
  RE2 re("(\\d+)");
  ASSERT_TRUE(re.ok());
  int value = 0;
  RE2::Arg arg(&value);
  const RE2::Arg* args[] = {&arg};
  EXPECT_TRUE(RE2::PartialMatchN("abc 123 def", re, args, 1));
  EXPECT_EQ(value, 123);
}

TEST(RE2PartialMatchNTest_253, MatchWithStringCapture_253) {
  RE2 re("(\\w+)@(\\w+)");
  ASSERT_TRUE(re.ok());
  std::string user, domain;
  RE2::Arg arg1(&user);
  RE2::Arg arg2(&domain);
  const RE2::Arg* args[] = {&arg1, &arg2};
  EXPECT_TRUE(RE2::PartialMatchN("email: user@domain please", re, args, 2));
  EXPECT_EQ(user, "user");
  EXPECT_EQ(domain, "domain");
}

TEST(RE2PartialMatchNTest_253, EmptyText_253) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(RE2::PartialMatchN("", re, nullptr, 0));
}

TEST(RE2PartialMatchNTest_253, EmptyPattern_253) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatchN("anything", re, nullptr, 0));
}

TEST(RE2PartialMatchNTest_253, EmptyTextEmptyPattern_253) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatchN("", re, nullptr, 0));
}

TEST(RE2PartialMatchNTest_253, PartialMatchAtBeginning_253) {
  RE2 re("^hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatchN("hello world", re, nullptr, 0));
  EXPECT_FALSE(RE2::PartialMatchN("say hello", re, nullptr, 0));
}

TEST(RE2PartialMatchNTest_253, PartialMatchAtEnd_253) {
  RE2 re("world$");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatchN("hello world", re, nullptr, 0));
  EXPECT_FALSE(RE2::PartialMatchN("world hello", re, nullptr, 0));
}

// ===========================================================================
// PartialMatch (variadic template) Tests
// ===========================================================================

TEST(RE2PartialMatchTest_253, SimpleMatch_253) {
  EXPECT_TRUE(RE2::PartialMatch("hello world", RE2("hello")));
}

TEST(RE2PartialMatchTest_253, SimpleNoMatch_253) {
  EXPECT_FALSE(RE2::PartialMatch("hello world", RE2("xyz")));
}

TEST(RE2PartialMatchTest_253, CaptureInt_253) {
  int n;
  EXPECT_TRUE(RE2::PartialMatch("x = 42;", RE2("(\\d+)"), &n));
  EXPECT_EQ(n, 42);
}

TEST(RE2PartialMatchTest_253, CaptureString_253) {
  std::string s;
  EXPECT_TRUE(RE2::PartialMatch("hello world", RE2("(\\w+)"), &s));
  EXPECT_EQ(s, "hello");
}

TEST(RE2PartialMatchTest_253, MultipleCaptures_253) {
  int a, b;
  EXPECT_TRUE(RE2::PartialMatch("coords: 10,20", RE2("(\\d+),(\\d+)"), &a, &b));
  EXPECT_EQ(a, 10);
  EXPECT_EQ(b, 20);
}

// ===========================================================================
// FullMatch Tests
// ===========================================================================

TEST(RE2FullMatchTest_253, ExactMatch_253) {
  EXPECT_TRUE(RE2::FullMatch("hello", RE2("hello")));
}

TEST(RE2FullMatchTest_253, ExactMatchFails_253) {
  EXPECT_FALSE(RE2::FullMatch("hello world", RE2("hello")));
}

TEST(RE2FullMatchTest_253, FullMatchWithCapture_253) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("42", RE2("(\\d+)"), &n));
  EXPECT_EQ(n, 42);
}

TEST(RE2FullMatchTest_253, EmptyStringEmptyPattern_253) {
  EXPECT_TRUE(RE2::FullMatch("", RE2("")));
}

TEST(RE2FullMatchTest_253, FullMatchNWithArgs_253) {
  RE2 re("(\\d+)-(\\d+)");
  ASSERT_TRUE(re.ok());
  int a = 0, b = 0;
  RE2::Arg arg1(&a);
  RE2::Arg arg2(&b);
  const RE2::Arg* args[] = {&arg1, &arg2};
  EXPECT_TRUE(RE2::FullMatchN("123-456", re, args, 2));
  EXPECT_EQ(a, 123);
  EXPECT_EQ(b, 456);
}

TEST(RE2FullMatchTest_253, FullMatchNNoArgs_253) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatchN("hello", re, nullptr, 0));
  EXPECT_FALSE(RE2::FullMatchN("hello world", re, nullptr, 0));
}

// ===========================================================================
// Consume Tests
// ===========================================================================

TEST(RE2ConsumeTest_253, ConsumeBasic_253) {
  absl::string_view input("one123two456");
  std::string word;
  EXPECT_TRUE(RE2::Consume(&input, RE2("([a-z]+)"), &word));
  EXPECT_EQ(word, "one");
  // input should be advanced past "one"
  EXPECT_EQ(input, "123two456");
}

TEST(RE2ConsumeTest_253, ConsumeNoMatch_253) {
  absl::string_view input("123abc");
  std::string word;
  EXPECT_FALSE(RE2::Consume(&input, RE2("([a-z]+)"), &word));
  EXPECT_EQ(input, "123abc");
}

TEST(RE2ConsumeTest_253, ConsumeNBasic_253) {
  RE2 re("(\\d+)");
  ASSERT_TRUE(re.ok());
  absl::string_view input("42abc");
  int n = 0;
  RE2::Arg arg(&n);
  const RE2::Arg* args[] = {&arg};
  EXPECT_TRUE(RE2::ConsumeN(&input, re, args, 1));
  EXPECT_EQ(n, 42);
  EXPECT_EQ(input, "abc");
}

// ===========================================================================
// FindAndConsume Tests
// ===========================================================================

TEST(RE2FindAndConsumeTest_253, FindAndConsumeBasic_253) {
  absl::string_view input("abc 123 def 456");
  int n;
  EXPECT_TRUE(RE2::FindAndConsume(&input, RE2("(\\d+)"), &n));
  EXPECT_EQ(n, 123);
  EXPECT_TRUE(RE2::FindAndConsume(&input, RE2("(\\d+)"), &n));
  EXPECT_EQ(n, 456);
  EXPECT_FALSE(RE2::FindAndConsume(&input, RE2("(\\d+)"), &n));
}

TEST(RE2FindAndConsumeTest_253, FindAndConsumeNBasic_253) {
  RE2 re("(\\w+)");
  ASSERT_TRUE(re.ok());
  absl::string_view input("  hello  world");
  std::string word;
  RE2::Arg arg(&word);
  const RE2::Arg* args[] = {&arg};
  EXPECT_TRUE(RE2::FindAndConsumeN(&input, re, args, 1));
  EXPECT_EQ(word, "hello");
}

// ===========================================================================
// Replace Tests
// ===========================================================================

TEST(RE2ReplaceTest_253, ReplaceFirst_253) {
  std::string str = "hello world hello";
  EXPECT_TRUE(RE2::Replace(&str, RE2("hello"), "hi"));
  EXPECT_EQ(str, "hi world hello");
}

TEST(RE2ReplaceTest_253, ReplaceNoMatch_253) {
  std::string str = "hello world";
  EXPECT_FALSE(RE2::Replace(&str, RE2("xyz"), "abc"));
  EXPECT_EQ(str, "hello world");
}

TEST(RE2ReplaceTest_253, ReplaceWithBackreference_253) {
  std::string str = "hello world";
  EXPECT_TRUE(RE2::Replace(&str, RE2("(\\w+)"), "[\\1]"));
  EXPECT_EQ(str, "[hello] world");
}

// ===========================================================================
// GlobalReplace Tests
// ===========================================================================

TEST(RE2GlobalReplaceTest_253, GlobalReplaceAll_253) {
  std::string str = "aaa bbb ccc";
  int count = RE2::GlobalReplace(&str, RE2("\\w+"), "X");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(str, "X X X");
}

TEST(RE2GlobalReplaceTest_253, GlobalReplaceNone_253) {
  std::string str = "hello";
  int count = RE2::GlobalReplace(&str, RE2("\\d+"), "X");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(str, "hello");
}

// ===========================================================================
// Extract Tests
// ===========================================================================

TEST(RE2ExtractTest_253, ExtractBasic_253) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@example.com", RE2("(.*)@([^.]*)"), "\\2!\\1", &out));
  EXPECT_EQ(out, "example!boris");
}

TEST(RE2ExtractTest_253, ExtractNoMatch_253) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("no-at-sign", RE2("(.*)@(.*)"), "\\2!\\1", &out));
}

// ===========================================================================
// QuoteMeta Tests
// ===========================================================================

TEST(RE2QuoteMetaTest_253, BasicQuoting_253) {
  std::string quoted = RE2::QuoteMeta("hello.world");
  EXPECT_TRUE(RE2::FullMatch("hello.world", RE2(quoted)));
  EXPECT_FALSE(RE2::FullMatch("helloxworld", RE2(quoted)));
}

TEST(RE2QuoteMetaTest_253, SpecialChars_253) {
  std::string quoted = RE2::QuoteMeta("a+b*c?");
  EXPECT_TRUE(RE2::FullMatch("a+b*c?", RE2(quoted)));
}

TEST(RE2QuoteMetaTest_253, EmptyString_253) {
  std::string quoted = RE2::QuoteMeta("");
  EXPECT_EQ(quoted, "");
}

// ===========================================================================
// RE2 Construction / Status Tests
// ===========================================================================

TEST(RE2ConstructionTest_253, ValidPattern_253) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.error_code(), RE2::NoError);
  EXPECT_EQ(re.pattern(), "hello");
}

TEST(RE2ConstructionTest_253, InvalidPattern_253) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(re.error_code(), RE2::NoError);
  EXPECT_FALSE(re.error().empty());
}

TEST(RE2ConstructionTest_253, FromCString_253) {
  RE2 re("test");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "test");
}

TEST(RE2ConstructionTest_253, FromStdString_253) {
  std::string pat = "test";
  RE2 re(pat);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "test");
}

TEST(RE2ConstructionTest_253, FromStringView_253) {
  absl::string_view sv = "test";
  RE2 re(sv);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "test");
}

// ===========================================================================
// NumberOfCapturingGroups Tests
// ===========================================================================

TEST(RE2CapturingGroupsTest_253, NoGroups_253) {
  RE2 re("hello");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST(RE2CapturingGroupsTest_253, OneGroup_253) {
  RE2 re("(hello)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST(RE2CapturingGroupsTest_253, MultipleGroups_253) {
  RE2 re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(RE2CapturingGroupsTest_253, NonCapturingGroup_253) {
  RE2 re("(?:hello)(world)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

// ===========================================================================
// NamedCapturingGroups Tests
// ===========================================================================

TEST(RE2NamedCapturingGroupsTest_253, NoNamedGroups_253) {
  RE2 re("(\\d+)");
  ASSERT_TRUE(re.ok());
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_TRUE(groups.empty());
}

TEST(RE2NamedCapturingGroupsTest_253, WithNamedGroups_253) {
  RE2 re("(?P<year>\\d{4})-(?P<month>\\d{2})");
  ASSERT_TRUE(re.ok());
  const auto& groups = re.NamedCapturingGroups();
  EXPECT_EQ(groups.size(), 2u);
  auto it = groups.find("year");
  ASSERT_NE(it, groups.end());
  EXPECT_EQ(it->second, 1);
  it = groups.find("month");
  ASSERT_NE(it, groups.end());
  EXPECT_EQ(it->second, 2);
}

// ===========================================================================
// CapturingGroupNames Tests
// ===========================================================================

TEST(RE2CapturingGroupNamesTest_253, WithNames_253) {
  RE2 re("(?P<name>\\w+)@(?P<domain>\\w+)");
  ASSERT_TRUE(re.ok());
  const auto& names = re.CapturingGroupNames();
  EXPECT_EQ(names.size(), 2u);
  auto it = names.find(1);
  ASSERT_NE(it, names.end());
  EXPECT_EQ(it->second, "name");
  it = names.find(2);
  ASSERT_NE(it, names.end());
  EXPECT_EQ(it->second, "domain");
}

// ===========================================================================
// Match Tests
// ===========================================================================

TEST(RE2MatchTest_253, UnanchoredMatch_253) {
  RE2 re("\\d+");
  ASSERT_TRUE(re.ok());
  absl::string_view submatch;
  EXPECT_TRUE(re.Match("abc 42 def", 0, 10, RE2::UNANCHORED, &submatch, 1));
  EXPECT_EQ(submatch, "42");
}

TEST(RE2MatchTest_253, AnchoredStart_253) {
  RE2 re("\\d+");
  ASSERT_TRUE(re.ok());
  absl::string_view submatch;
  EXPECT_FALSE(re.Match("abc 42", 0, 6, RE2::ANCHOR_START, &submatch, 1));
  EXPECT_TRUE(re.Match("42 abc", 0, 6, RE2::ANCHOR_START, &submatch, 1));
  EXPECT_EQ(submatch, "42");
}

TEST(RE2MatchTest_253, AnchoredBoth_253) {
  RE2 re("\\d+");
  ASSERT_TRUE(re.ok());
  absl::string_view submatch;
  EXPECT_FALSE(re.Match("42 abc", 0, 6, RE2::ANCHOR_BOTH, &submatch, 1));
  EXPECT_TRUE(re.Match("42", 0, 2, RE2::ANCHOR_BOTH, &submatch, 1));
  EXPECT_EQ(submatch, "42");
}

TEST(RE2MatchTest_253, MatchWithStartpos_253) {
  RE2 re("\\d+");
  ASSERT_TRUE(re.ok());
  absl::string_view text = "abc 42 def";
  absl::string_view submatch;
  EXPECT_TRUE(re.Match(text, 4, 6, RE2::UNANCHORED, &submatch, 1));
  EXPECT_EQ(submatch, "42");
}

TEST(RE2MatchTest_253, NoSubmatch_253) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(re.Match("say hello", 0, 9, RE2::UNANCHORED, nullptr, 0));
  EXPECT_FALSE(re.Match("say hi", 0, 6, RE2::UNANCHORED, nullptr, 0));
}

// ===========================================================================
// PossibleMatchRange Tests
// ===========================================================================

TEST(RE2PossibleMatchRangeTest_253, BasicRange_253) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  std::string min_str, max_str;
  EXPECT_TRUE(re.PossibleMatchRange(&min_str, &max_str, 10));
  EXPECT_LE(min_str, "hello");
  EXPECT_GE(max_str, "hello");
}

// ===========================================================================
// CheckRewriteString Tests
// ===========================================================================

TEST(RE2CheckRewriteStringTest_253, ValidRewrite_253) {
  RE2 re("(\\w+)");
  ASSERT_TRUE(re.ok());
  std::string err;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &err));
}

TEST(RE2CheckRewriteStringTest_253, InvalidRewrite_253) {
  RE2 re("(\\w+)");
  ASSERT_TRUE(re.ok());
  std::string err;
  EXPECT_FALSE(re.CheckRewriteString("\\2", &err));
  EXPECT_FALSE(err.empty());
}

// ===========================================================================
// MaxSubmatch Tests
// ===========================================================================

TEST(RE2MaxSubmatchTest_253, NoBackref_253) {
  EXPECT_EQ(RE2::MaxSubmatch("no backrefs"), 0);
}

TEST(RE2MaxSubmatchTest_253, SingleBackref_253) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1"), 1);
}

TEST(RE2MaxSubmatchTest_253, MultipleBackrefs_253) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1 \\3 \\2"), 3);
}

// ===========================================================================
// ProgramSize Tests
// ===========================================================================

TEST(RE2ProgramSizeTest_253, BasicSize_253) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2ProgramSizeTest_253, ReverseProgramSize_253) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

// ===========================================================================
// ProgramFanout Tests
// ===========================================================================

TEST(RE2ProgramFanoutTest_253, BasicFanout_253) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

TEST(RE2ProgramFanoutTest_253, ReverseFanout_253) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// ===========================================================================
// Options Tests
// ===========================================================================

TEST(RE2OptionsTest_253, CaseInsensitive_253) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("Hello", re));
}

// ===========================================================================
// Hex, Octal, CRadix parsing Tests
// ===========================================================================

TEST(RE2HexTest_253, HexParse_253) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("0xff", RE2("(.+)"), RE2::Hex(&value)));
  EXPECT_EQ(value, 255);
}

TEST(RE2OctalTest_253, OctalParse_253) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("077", RE2("(.+)"), RE2::Octal(&value)));
  EXPECT_EQ(value, 63);
}

TEST(RE2CRadixTest_253, CRadixParse_253) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("0x10", RE2("(.+)"), RE2::CRadix(&value)));
  EXPECT_EQ(value, 16);
}

TEST(RE2CRadixTest_253, CRadixDecimal_253) {
  int value;
  EXPECT_TRUE(RE2::FullMatch("42", RE2("(.+)"), RE2::CRadix(&value)));
  EXPECT_EQ(value, 42);
}

// ===========================================================================
// Arg Tests
// ===========================================================================

TEST(RE2ArgTest_253, NullArg_253) {
  RE2::Arg arg(nullptr);
  EXPECT_TRUE(arg.Parse("anything", 8));
}

TEST(RE2ArgTest_253, DefaultArg_253) {
  RE2::Arg arg;
  EXPECT_TRUE(arg.Parse("anything", 8));
}

TEST(RE2ArgTest_253, IntArg_253) {
  int value = 0;
  RE2::Arg arg(&value);
  EXPECT_TRUE(arg.Parse("42", 2));
  EXPECT_EQ(value, 42);
}

TEST(RE2ArgTest_253, StringArg_253) {
  std::string value;
  RE2::Arg arg(&value);
  EXPECT_TRUE(arg.Parse("hello", 5));
  EXPECT_EQ(value, "hello");
}

// ===========================================================================
// Boundary / Edge Cases
// ===========================================================================

TEST(RE2BoundaryTest_253, VeryLongString_253) {
  std::string longstr(10000, 'a');
  longstr += "needle";
  RE2 re("needle");
  EXPECT_TRUE(RE2::PartialMatch(longstr, re));
}

TEST(RE2BoundaryTest_253, SpecialRegexChars_253) {
  std::string quoted = RE2::QuoteMeta("[](){}.*+?|\\^$");
  RE2 re(quoted);
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("[](){}.*+?|\\^$", re));
}

TEST(RE2BoundaryTest_253, UnicodeInText_253) {
  RE2 re("café");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("I like café au lait", re));
}

TEST(RE2BoundaryTest_253, NullBytesInStringView_253) {
  std::string text("abc\0def", 7);
  std::string pat("c\\x00d");
  RE2 re(pat);
  if (re.ok()) {
    // Match behavior with null bytes
    RE2::PartialMatch(absl::string_view(text.data(), text.size()), re);
  }
}

TEST(RE2BoundaryTest_253, Rewrite_253) {
  RE2 re("(\\w+) (\\w+)");
  ASSERT_TRUE(re.ok());
  absl::string_view vec[3];
  vec[0] = "hello world";
  vec[1] = "hello";
  vec[2] = "world";
  std::string out;
  EXPECT_TRUE(re.Rewrite(&out, "\\2 \\1", vec, 3));
  EXPECT_EQ(out, "world hello");
}

}  // namespace
