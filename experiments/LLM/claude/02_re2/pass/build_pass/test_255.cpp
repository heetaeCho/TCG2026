#include <gtest/gtest.h>
#include <string>
#include "re2/re2.h"

namespace re2 {
namespace {

// ============================================================
// FindAndConsumeN Tests
// ============================================================

class FindAndConsumeNTest_255 : public ::testing::Test {
 protected:
};

// Test basic FindAndConsumeN with no capture groups
TEST_F(FindAndConsumeNTest_255, BasicMatchNoArgs_255) {
  absl::string_view input("hello world");
  RE2 re("\\w+");
  EXPECT_TRUE(RE2::FindAndConsumeN(&input, re, nullptr, 0));
  // After consuming "hello", the input should have " world" remaining
  // (FindAndConsume is unanchored, so it finds first match and consumes up to end of it)
  EXPECT_EQ(input, " world");
}

// Test FindAndConsumeN consumes successive matches
TEST_F(FindAndConsumeNTest_255, SuccessiveConsumption_255) {
  absl::string_view input("aaa bbb ccc");
  RE2 re("\\w+");

  EXPECT_TRUE(RE2::FindAndConsumeN(&input, re, nullptr, 0));
  EXPECT_EQ(input, " bbb ccc");

  EXPECT_TRUE(RE2::FindAndConsumeN(&input, re, nullptr, 0));
  EXPECT_EQ(input, " ccc");

  EXPECT_TRUE(RE2::FindAndConsumeN(&input, re, nullptr, 0));
  EXPECT_EQ(input, "");

  // No more matches
  EXPECT_FALSE(RE2::FindAndConsumeN(&input, re, nullptr, 0));
}

// Test FindAndConsumeN with a capture group
TEST_F(FindAndConsumeNTest_255, WithCaptureGroup_255) {
  absl::string_view input("abc 123 def 456");
  RE2 re("(\\d+)");
  int value;
  const RE2::Arg arg(&value);
  const RE2::Arg* args[] = {&arg};

  EXPECT_TRUE(RE2::FindAndConsumeN(&input, re, args, 1));
  EXPECT_EQ(value, 123);
  EXPECT_EQ(input, " def 456");

  EXPECT_TRUE(RE2::FindAndConsumeN(&input, re, args, 1));
  EXPECT_EQ(value, 456);
  EXPECT_EQ(input, "");
}

// Test FindAndConsumeN with no match returns false
TEST_F(FindAndConsumeNTest_255, NoMatchReturnsFalse_255) {
  absl::string_view input("hello world");
  RE2 re("\\d+");
  EXPECT_FALSE(RE2::FindAndConsumeN(&input, re, nullptr, 0));
  // Input should remain unchanged on failure
  EXPECT_EQ(input, "hello world");
}

// Test FindAndConsumeN with empty input
TEST_F(FindAndConsumeNTest_255, EmptyInput_255) {
  absl::string_view input("");
  RE2 re("\\w+");
  EXPECT_FALSE(RE2::FindAndConsumeN(&input, re, nullptr, 0));
  EXPECT_EQ(input, "");
}

// Test FindAndConsumeN with empty pattern (matches empty string)
TEST_F(FindAndConsumeNTest_255, EmptyPatternMatchesEmptyString_255) {
  absl::string_view input("abc");
  RE2 re("");
  // Empty pattern matches at position 0, consuming nothing
  // This behavior depends on implementation, but typically it matches
  EXPECT_TRUE(RE2::FindAndConsumeN(&input, re, nullptr, 0));
}

// Test FindAndConsumeN with string capture
TEST_F(FindAndConsumeNTest_255, StringCapture_255) {
  absl::string_view input("key=value; other=stuff");
  RE2 re("(\\w+)=(\\w+)");
  std::string key, val;
  const RE2::Arg arg_key(&key);
  const RE2::Arg arg_val(&val);
  const RE2::Arg* args[] = {&arg_key, &arg_val};

  EXPECT_TRUE(RE2::FindAndConsumeN(&input, re, args, 2));
  EXPECT_EQ(key, "key");
  EXPECT_EQ(val, "value");
  EXPECT_EQ(input, "; other=stuff");

  EXPECT_TRUE(RE2::FindAndConsumeN(&input, re, args, 2));
  EXPECT_EQ(key, "other");
  EXPECT_EQ(val, "stuff");
}

// Test FindAndConsumeN with pattern that matches mid-string (unanchored)
TEST_F(FindAndConsumeNTest_255, UnanchoredMatch_255) {
  absl::string_view input("---abc---");
  RE2 re("([a-z]+)");
  std::string captured;
  const RE2::Arg arg(&captured);
  const RE2::Arg* args[] = {&arg};

  EXPECT_TRUE(RE2::FindAndConsumeN(&input, re, args, 1));
  EXPECT_EQ(captured, "abc");
  // Input should have everything after "abc" consumed (including prefix up to and including match)
  EXPECT_EQ(input, "---");
}

// Test FindAndConsumeN with invalid regex
TEST_F(FindAndConsumeNTest_255, InvalidRegex_255) {
  absl::string_view input("hello");
  RE2 re("(");  // Invalid regex
  EXPECT_FALSE(re.ok());
  EXPECT_FALSE(RE2::FindAndConsumeN(&input, re, nullptr, 0));
}

// ============================================================
// FindAndConsume variadic template tests
// ============================================================

TEST_F(FindAndConsumeNTest_255, FindAndConsumeVariadic_255) {
  absl::string_view input("foo123bar456");
  RE2 re("(\\d+)");
  int val;

  EXPECT_TRUE(RE2::FindAndConsume(&input, re, &val));
  EXPECT_EQ(val, 123);

  EXPECT_TRUE(RE2::FindAndConsume(&input, re, &val));
  EXPECT_EQ(val, 456);

  EXPECT_FALSE(RE2::FindAndConsume(&input, re, &val));
}

// ============================================================
// FullMatchN Tests
// ============================================================

class FullMatchNTest_255 : public ::testing::Test {};

TEST_F(FullMatchNTest_255, BasicFullMatch_255) {
  RE2 re("hello");
  EXPECT_TRUE(RE2::FullMatchN("hello", re, nullptr, 0));
  EXPECT_FALSE(RE2::FullMatchN("hello world", re, nullptr, 0));
}

TEST_F(FullMatchNTest_255, FullMatchWithCapture_255) {
  RE2 re("(\\d+)");
  int val;
  const RE2::Arg arg(&val);
  const RE2::Arg* args[] = {&arg};
  EXPECT_TRUE(RE2::FullMatchN("12345", re, args, 1));
  EXPECT_EQ(val, 12345);
}

TEST_F(FullMatchNTest_255, FullMatchFailsPartial_255) {
  RE2 re("\\d+");
  EXPECT_FALSE(RE2::FullMatchN("abc123", re, nullptr, 0));
}

// ============================================================
// PartialMatchN Tests
// ============================================================

class PartialMatchNTest_255 : public ::testing::Test {};

TEST_F(PartialMatchNTest_255, BasicPartialMatch_255) {
  RE2 re("\\d+");
  EXPECT_TRUE(RE2::PartialMatchN("abc123def", re, nullptr, 0));
  EXPECT_FALSE(RE2::PartialMatchN("abcdef", re, nullptr, 0));
}

TEST_F(PartialMatchNTest_255, PartialMatchWithCapture_255) {
  RE2 re("(\\d+)");
  int val;
  const RE2::Arg arg(&val);
  const RE2::Arg* args[] = {&arg};
  EXPECT_TRUE(RE2::PartialMatchN("abc123def", re, args, 1));
  EXPECT_EQ(val, 123);
}

// ============================================================
// ConsumeN Tests
// ============================================================

class ConsumeNTest_255 : public ::testing::Test {};

TEST_F(ConsumeNTest_255, BasicConsume_255) {
  absl::string_view input("123abc");
  RE2 re("\\d+");
  EXPECT_TRUE(RE2::ConsumeN(&input, re, nullptr, 0));
  EXPECT_EQ(input, "abc");
}

TEST_F(ConsumeNTest_255, ConsumeAnchored_255) {
  absl::string_view input("abc123");
  RE2 re("\\d+");
  // Consume is anchored at start, so this should fail
  EXPECT_FALSE(RE2::ConsumeN(&input, re, nullptr, 0));
  EXPECT_EQ(input, "abc123");
}

TEST_F(ConsumeNTest_255, ConsumeWithCapture_255) {
  absl::string_view input("123abc");
  RE2 re("(\\d+)");
  int val;
  const RE2::Arg arg(&val);
  const RE2::Arg* args[] = {&arg};
  EXPECT_TRUE(RE2::ConsumeN(&input, re, args, 1));
  EXPECT_EQ(val, 123);
  EXPECT_EQ(input, "abc");
}

// ============================================================
// Replace Tests
// ============================================================

class ReplaceTest_255 : public ::testing::Test {};

TEST_F(ReplaceTest_255, BasicReplace_255) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, RE2("world"), "there"));
  EXPECT_EQ(s, "hello there");
}

TEST_F(ReplaceTest_255, ReplaceNoMatch_255) {
  std::string s = "hello world";
  EXPECT_FALSE(RE2::Replace(&s, RE2("xyz"), "there"));
  EXPECT_EQ(s, "hello world");
}

TEST_F(ReplaceTest_255, ReplaceWithBackreference_255) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, RE2("(\\w+)"), "[\\1]"));
  EXPECT_EQ(s, "[hello] world");
}

// ============================================================
// GlobalReplace Tests
// ============================================================

class GlobalReplaceTest_255 : public ::testing::Test {};

TEST_F(GlobalReplaceTest_255, BasicGlobalReplace_255) {
  std::string s = "aaa bbb aaa";
  int count = RE2::GlobalReplace(&s, RE2("aaa"), "ccc");
  EXPECT_EQ(count, 2);
  EXPECT_EQ(s, "ccc bbb ccc");
}

TEST_F(GlobalReplaceTest_255, GlobalReplaceNoMatch_255) {
  std::string s = "hello";
  int count = RE2::GlobalReplace(&s, RE2("xyz"), "abc");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(s, "hello");
}

// ============================================================
// Extract Tests
// ============================================================

class ExtractTest_255 : public ::testing::Test {};

TEST_F(ExtractTest_255, BasicExtract_255) {
  std::string out;
  EXPECT_TRUE(RE2::Extract("boris@kremlin.ru", RE2("(.*)@([^.]*)"), "\\2!\\1", &out));
  EXPECT_EQ(out, "kremlin!boris");
}

TEST_F(ExtractTest_255, ExtractNoMatch_255) {
  std::string out;
  EXPECT_FALSE(RE2::Extract("no-at-sign", RE2("(.*)@(.*)"), "\\1", &out));
}

// ============================================================
// QuoteMeta Tests
// ============================================================

class QuoteMetaTest_255 : public ::testing::Test {};

TEST_F(QuoteMetaTest_255, BasicQuoteMeta_255) {
  EXPECT_EQ(RE2::QuoteMeta("hello"), "hello");
}

TEST_F(QuoteMetaTest_255, SpecialCharacters_255) {
  std::string quoted = RE2::QuoteMeta("a.b+c*d?e[f]g\\h");
  // The quoted string should be usable as a literal pattern
  EXPECT_TRUE(RE2::FullMatch("a.b+c*d?e[f]g\\h", RE2(quoted)));
}

TEST_F(QuoteMetaTest_255, EmptyString_255) {
  EXPECT_EQ(RE2::QuoteMeta(""), "");
}

// ============================================================
// Match Tests
// ============================================================

class MatchTest_255 : public ::testing::Test {};

TEST_F(MatchTest_255, BasicMatch_255) {
  RE2 re("(\\d+)");
  absl::string_view submatch[2];
  EXPECT_TRUE(re.Match("abc123def", 0, 9, RE2::UNANCHORED, submatch, 2));
  EXPECT_EQ(submatch[0], "123");
  EXPECT_EQ(submatch[1], "123");
}

TEST_F(MatchTest_255, AnchoredMatch_255) {
  RE2 re("\\d+");
  EXPECT_FALSE(re.Match("abc123", 0, 6, RE2::ANCHOR_START, nullptr, 0));
  EXPECT_TRUE(re.Match("123abc", 0, 6, RE2::ANCHOR_START, nullptr, 0));
}

TEST_F(MatchTest_255, FullAnchorMatch_255) {
  RE2 re("\\d+");
  EXPECT_FALSE(re.Match("123abc", 0, 6, RE2::ANCHOR_BOTH, nullptr, 0));
  EXPECT_TRUE(re.Match("123", 0, 3, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST_F(MatchTest_255, MatchWithStartPos_255) {
  RE2 re("\\d+");
  absl::string_view submatch[1];
  EXPECT_TRUE(re.Match("abc123def", 3, 9, RE2::UNANCHORED, submatch, 1));
  EXPECT_EQ(submatch[0], "123");
}

// ============================================================
// RE2 Construction and Status Tests
// ============================================================

class RE2ConstructionTest_255 : public ::testing::Test {};

TEST_F(RE2ConstructionTest_255, ValidPattern_255) {
  RE2 re("abc");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "abc");
}

TEST_F(RE2ConstructionTest_255, InvalidPattern_255) {
  RE2 re("(");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(re.error_code(), RE2::NoError);
}

TEST_F(RE2ConstructionTest_255, PatternFromString_255) {
  std::string pattern = "hello.*world";
  RE2 re(pattern);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), pattern);
}

TEST_F(RE2ConstructionTest_255, NumberOfCapturingGroups_255) {
  RE2 re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST_F(RE2ConstructionTest_255, NoCapturingGroups_255) {
  RE2 re("abc");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

// ============================================================
// CheckRewriteString Tests
// ============================================================

class CheckRewriteStringTest_255 : public ::testing::Test {};

TEST_F(CheckRewriteStringTest_255, ValidRewrite_255) {
  RE2 re("(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
}

TEST_F(CheckRewriteStringTest_255, InvalidRewriteBackref_255) {
  RE2 re("(\\w+)");
  std::string error;
  // \\2 references a non-existent group
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
}

// ============================================================
// MaxSubmatch Tests
// ============================================================

class MaxSubmatchTest_255 : public ::testing::Test {};

TEST_F(MaxSubmatchTest_255, BasicMaxSubmatch_255) {
  EXPECT_EQ(RE2::MaxSubmatch("\\1 and \\2"), 2);
}

TEST_F(MaxSubmatchTest_255, NoSubmatch_255) {
  EXPECT_EQ(RE2::MaxSubmatch("no backrefs"), 0);
}

TEST_F(MaxSubmatchTest_255, SingleSubmatch_255) {
  EXPECT_EQ(RE2::MaxSubmatch("\\0"), 0);
}

// ============================================================
// PossibleMatchRange Tests
// ============================================================

class PossibleMatchRangeTest_255 : public ::testing::Test {};

TEST_F(PossibleMatchRangeTest_255, BasicRange_255) {
  RE2 re("abc.*");
  std::string min_val, max_val;
  EXPECT_TRUE(re.PossibleMatchRange(&min_val, &max_val, 10));
  EXPECT_LE(min_val, "abc");
}

// ============================================================
// Rewrite Tests
// ============================================================

class RewriteTest_255 : public ::testing::Test {};

TEST_F(RewriteTest_255, BasicRewrite_255) {
  RE2 re("(\\w+)@(\\w+)");
  std::string out;
  absl::string_view vec[3] = {"boris@kremlin", "boris", "kremlin"};
  EXPECT_TRUE(re.Rewrite(&out, "\\2!\\1", vec, 3));
  EXPECT_EQ(out, "kremlin!boris");
}

// ============================================================
// NamedCapturingGroups Tests
// ============================================================

class NamedCapturingGroupsTest_255 : public ::testing::Test {};

TEST_F(NamedCapturingGroupsTest_255, WithNamedGroups_255) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  EXPECT_TRUE(re.ok());
  const auto& named = re.NamedCapturingGroups();
  EXPECT_EQ(named.size(), 2);
  EXPECT_EQ(named.at("first"), 1);
  EXPECT_EQ(named.at("second"), 2);
}

TEST_F(NamedCapturingGroupsTest_255, NoNamedGroups_255) {
  RE2 re("(\\w+) (\\w+)");
  const auto& named = re.NamedCapturingGroups();
  EXPECT_TRUE(named.empty());
}

// ============================================================
// CapturingGroupNames Tests
// ============================================================

class CapturingGroupNamesTest_255 : public ::testing::Test {};

TEST_F(CapturingGroupNamesTest_255, WithNamedGroups_255) {
  RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
  const auto& names = re.CapturingGroupNames();
  EXPECT_EQ(names.size(), 2);
  EXPECT_EQ(names.at(1), "first");
  EXPECT_EQ(names.at(2), "second");
}

// ============================================================
// FullMatch / PartialMatch variadic template tests
// ============================================================

class VariadicMatchTest_255 : public ::testing::Test {};

TEST_F(VariadicMatchTest_255, FullMatchVariadic_255) {
  EXPECT_TRUE(RE2::FullMatch("hello", RE2("hello")));
  EXPECT_FALSE(RE2::FullMatch("hello world", RE2("hello")));
}

TEST_F(VariadicMatchTest_255, FullMatchWithCapture_255) {
  int n;
  EXPECT_TRUE(RE2::FullMatch("12345", RE2("(\\d+)"), &n));
  EXPECT_EQ(n, 12345);
}

TEST_F(VariadicMatchTest_255, PartialMatchVariadic_255) {
  EXPECT_TRUE(RE2::PartialMatch("hello world 123", RE2("\\d+")));
  EXPECT_FALSE(RE2::PartialMatch("hello world", RE2("\\d+")));
}

TEST_F(VariadicMatchTest_255, PartialMatchWithCapture_255) {
  std::string word;
  EXPECT_TRUE(RE2::PartialMatch("hello world", RE2("(\\w+)"), &word));
  EXPECT_EQ(word, "hello");
}

// ============================================================
// Consume variadic template tests
// ============================================================

class ConsumeVariadicTest_255 : public ::testing::Test {};

TEST_F(ConsumeVariadicTest_255, BasicConsume_255) {
  absl::string_view input("123abc456");
  int n;
  EXPECT_TRUE(RE2::Consume(&input, RE2("(\\d+)"), &n));
  EXPECT_EQ(n, 123);
  EXPECT_EQ(input, "abc456");
}

// ============================================================
// Arg Tests
// ============================================================

class ArgTest_255 : public ::testing::Test {};

TEST_F(ArgTest_255, NullArg_255) {
  RE2::Arg arg(nullptr);
  // Parsing with null dest should succeed (DoNothing)
  EXPECT_TRUE(arg.Parse("hello", 5));
}

TEST_F(ArgTest_255, IntArg_255) {
  int val = 0;
  RE2::Arg arg(&val);
  EXPECT_TRUE(arg.Parse("42", 2));
  EXPECT_EQ(val, 42);
}

TEST_F(ArgTest_255, StringArg_255) {
  std::string val;
  RE2::Arg arg(&val);
  EXPECT_TRUE(arg.Parse("hello", 5));
  EXPECT_EQ(val, "hello");
}

// ============================================================
// ProgramSize / ReverseProgramSize Tests
// ============================================================

class ProgramSizeTest_255 : public ::testing::Test {};

TEST_F(ProgramSizeTest_255, BasicProgramSize_255) {
  RE2 re("hello");
  EXPECT_GT(re.ProgramSize(), 0);
}

TEST_F(ProgramSizeTest_255, ReverseProgramSize_255) {
  RE2 re("hello");
  EXPECT_GT(re.ReverseProgramSize(), 0);
}

// ============================================================
// Hex, Octal, CRadix Tests
// ============================================================

class RadixTest_255 : public ::testing::Test {};

TEST_F(RadixTest_255, HexParse_255) {
  int val;
  EXPECT_TRUE(RE2::FullMatch("0xff", RE2("(0x[0-9a-fA-F]+)"), RE2::Hex(&val)));
  EXPECT_EQ(val, 255);
}

TEST_F(RadixTest_255, OctalParse_255) {
  int val;
  EXPECT_TRUE(RE2::FullMatch("0377", RE2("(0[0-7]+)"), RE2::Octal(&val)));
  EXPECT_EQ(val, 255);
}

TEST_F(RadixTest_255, CRadixHex_255) {
  int val;
  EXPECT_TRUE(RE2::FullMatch("0xff", RE2("(0x[0-9a-fA-F]+)"), RE2::CRadix(&val)));
  EXPECT_EQ(val, 255);
}

TEST_F(RadixTest_255, CRadixDecimal_255) {
  int val;
  EXPECT_TRUE(RE2::FullMatch("255", RE2("(\\d+)"), RE2::CRadix(&val)));
  EXPECT_EQ(val, 255);
}

// ============================================================
// Boundary: very long input
// ============================================================

class BoundaryTest_255 : public ::testing::Test {};

TEST_F(BoundaryTest_255, LongInputFindAndConsume_255) {
  std::string long_str(10000, 'a');
  long_str += "123";
  absl::string_view input(long_str);
  int val;
  EXPECT_TRUE(RE2::FindAndConsume(&input, RE2("(\\d+)"), &val));
  EXPECT_EQ(val, 123);
  EXPECT_EQ(input, "");
}

TEST_F(BoundaryTest_255, SingleCharacterInput_255) {
  absl::string_view input("x");
  RE2 re("(.)");
  std::string c;
  EXPECT_TRUE(RE2::FindAndConsume(&input, re, &c));
  EXPECT_EQ(c, "x");
  EXPECT_EQ(input, "");
}

// ============================================================
// Multiple captures with FindAndConsume
// ============================================================

TEST_F(FindAndConsumeNTest_255, MultipleCapturesVariadic_255) {
  absl::string_view input("12-34 56-78");
  int a, b;
  RE2 re("(\\d+)-(\\d+)");

  EXPECT_TRUE(RE2::FindAndConsume(&input, re, &a, &b));
  EXPECT_EQ(a, 12);
  EXPECT_EQ(b, 34);

  EXPECT_TRUE(RE2::FindAndConsume(&input, re, &a, &b));
  EXPECT_EQ(a, 56);
  EXPECT_EQ(b, 78);

  EXPECT_FALSE(RE2::FindAndConsume(&input, re, &a, &b));
}

}  // namespace
}  // namespace re2
