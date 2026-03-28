#include "gtest/gtest.h"
#include "util/pcre.h"
#include <string>

namespace re2 {

class PCRETest_199 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(PCRETest_199, ConstructFromCString_199) {
  PCRE re("hello");
  EXPECT_EQ(re.pattern(), "hello");
}

TEST_F(PCRETest_199, ConstructFromStdString_199) {
  std::string pattern = "world";
  PCRE re(pattern);
  EXPECT_EQ(re.pattern(), "world");
}

TEST_F(PCRETest_199, ConstructEmptyPattern_199) {
  PCRE re("");
  EXPECT_EQ(re.pattern(), "");
}

// ==================== DoMatch Tests ====================

TEST_F(PCRETest_199, DoMatchSimpleMatch_199) {
  PCRE re("hello");
  bool result = re.DoMatch("hello world", PCRE::UNANCHORED, nullptr, nullptr, 0);
  EXPECT_TRUE(result);
}

TEST_F(PCRETest_199, DoMatchNoMatch_199) {
  PCRE re("goodbye");
  bool result = re.DoMatch("hello world", PCRE::UNANCHORED, nullptr, nullptr, 0);
  EXPECT_FALSE(result);
}

TEST_F(PCRETest_199, DoMatchAnchored_199) {
  PCRE re("hello");
  bool result = re.DoMatch("hello world", PCRE::ANCHOR_START, nullptr, nullptr, 0);
  EXPECT_TRUE(result);
}

TEST_F(PCRETest_199, DoMatchAnchoredNoMatch_199) {
  PCRE re("world");
  bool result = re.DoMatch("hello world", PCRE::ANCHOR_START, nullptr, nullptr, 0);
  EXPECT_FALSE(result);
}

TEST_F(PCRETest_199, DoMatchFullAnchor_199) {
  PCRE re("hello world");
  bool result = re.DoMatch("hello world", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0);
  EXPECT_TRUE(result);
}

TEST_F(PCRETest_199, DoMatchFullAnchorNoMatch_199) {
  PCRE re("hello");
  bool result = re.DoMatch("hello world", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0);
  EXPECT_FALSE(result);
}

TEST_F(PCRETest_199, DoMatchEmptyText_199) {
  PCRE re(".*");
  bool result = re.DoMatch("", PCRE::UNANCHORED, nullptr, nullptr, 0);
  EXPECT_TRUE(result);
}

TEST_F(PCRETest_199, DoMatchEmptyPattern_199) {
  PCRE re("");
  bool result = re.DoMatch("hello", PCRE::UNANCHORED, nullptr, nullptr, 0);
  EXPECT_TRUE(result);
}

TEST_F(PCRETest_199, DoMatchWithConsumed_199) {
  PCRE re("(\\w+)");
  size_t consumed = 0;
  bool result = re.DoMatch("hello world", PCRE::ANCHOR_START, &consumed, nullptr, 0);
  EXPECT_TRUE(result);
  EXPECT_EQ(consumed, 5u);
}

TEST_F(PCRETest_199, DoMatchWithStringCapture_199) {
  PCRE re("(\\w+)");
  std::string captured;
  PCRE::Arg arg(&captured);
  const PCRE::Arg* args[] = {&arg};
  bool result = re.DoMatch("hello world", PCRE::UNANCHORED, nullptr, args, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(captured, "hello");
}

TEST_F(PCRETest_199, DoMatchWithIntCapture_199) {
  PCRE re("(\\d+)");
  int captured = 0;
  PCRE::Arg arg(&captured);
  const PCRE::Arg* args[] = {&arg};
  bool result = re.DoMatch("abc 123 def", PCRE::UNANCHORED, nullptr, args, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(captured, 123);
}

TEST_F(PCRETest_199, DoMatchWithMultipleCaptures_199) {
  PCRE re("(\\w+)\\s+(\\d+)");
  std::string word;
  int number = 0;
  PCRE::Arg arg1(&word);
  PCRE::Arg arg2(&number);
  const PCRE::Arg* args[] = {&arg1, &arg2};
  bool result = re.DoMatch("hello 42", PCRE::UNANCHORED, nullptr, args, 2);
  EXPECT_TRUE(result);
  EXPECT_EQ(word, "hello");
  EXPECT_EQ(number, 42);
}

TEST_F(PCRETest_199, DoMatchZeroArgs_199) {
  PCRE re("(\\w+)");
  bool result = re.DoMatch("hello", PCRE::UNANCHORED, nullptr, nullptr, 0);
  EXPECT_TRUE(result);
}

// ==================== NumberOfCapturingGroups Tests ====================

TEST_F(PCRETest_199, NumberOfCapturingGroupsNone_199) {
  PCRE re("hello");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST_F(PCRETest_199, NumberOfCapturingGroupsOne_199) {
  PCRE re("(hello)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST_F(PCRETest_199, NumberOfCapturingGroupsMultiple_199) {
  PCRE re("(\\w+)\\s+(\\d+)\\s+(\\w+)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

// ==================== Replace Tests ====================

TEST_F(PCRETest_199, ReplaceSimple_199) {
  std::string str = "hello world";
  PCRE re("world");
  bool result = PCRE::Replace(&str, re, "there");
  EXPECT_TRUE(result);
  EXPECT_EQ(str, "hello there");
}

TEST_F(PCRETest_199, ReplaceNoMatch_199) {
  std::string str = "hello world";
  PCRE re("goodbye");
  bool result = PCRE::Replace(&str, re, "there");
  EXPECT_FALSE(result);
  EXPECT_EQ(str, "hello world");
}

TEST_F(PCRETest_199, ReplaceWithCapture_199) {
  std::string str = "hello world";
  PCRE re("(\\w+) (\\w+)");
  bool result = PCRE::Replace(&str, re, "\\2 \\1");
  EXPECT_TRUE(result);
  EXPECT_EQ(str, "world hello");
}

TEST_F(PCRETest_199, ReplaceEmptyString_199) {
  std::string str = "";
  PCRE re(".*");
  bool result = PCRE::Replace(&str, re, "replaced");
  EXPECT_TRUE(result);
  EXPECT_EQ(str, "replaced");
}

// ==================== GlobalReplace Tests ====================

TEST_F(PCRETest_199, GlobalReplaceMultipleMatches_199) {
  std::string str = "aaa bbb aaa";
  PCRE re("aaa");
  int count = PCRE::GlobalReplace(&str, re, "ccc");
  EXPECT_EQ(count, 2);
  EXPECT_EQ(str, "ccc bbb ccc");
}

TEST_F(PCRETest_199, GlobalReplaceNoMatch_199) {
  std::string str = "hello world";
  PCRE re("xyz");
  int count = PCRE::GlobalReplace(&str, re, "abc");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(str, "hello world");
}

TEST_F(PCRETest_199, GlobalReplaceSingleMatch_199) {
  std::string str = "hello world";
  PCRE re("world");
  int count = PCRE::GlobalReplace(&str, re, "there");
  EXPECT_EQ(count, 1);
  EXPECT_EQ(str, "hello there");
}

// ==================== Extract Tests ====================

TEST_F(PCRETest_199, ExtractSimple_199) {
  std::string out;
  PCRE re("(\\w+)@(\\w+)");
  bool result = PCRE::Extract("user@host", re, "\\1 at \\2", &out);
  EXPECT_TRUE(result);
  EXPECT_EQ(out, "user at host");
}

TEST_F(PCRETest_199, ExtractNoMatch_199) {
  std::string out;
  PCRE re("(\\d+)");
  bool result = PCRE::Extract("no numbers here", re, "\\1", &out);
  EXPECT_FALSE(result);
}

// ==================== QuoteMeta Tests ====================

TEST_F(PCRETest_199, QuoteMetaNoSpecialChars_199) {
  std::string result = PCRE::QuoteMeta("hello");
  EXPECT_EQ(result, "hello");
}

TEST_F(PCRETest_199, QuoteMetaWithSpecialChars_199) {
  std::string result = PCRE::QuoteMeta("a.b*c+d?e");
  // Each special char should be escaped with backslash
  PCRE re(result);
  bool match = re.DoMatch("a.b*c+d?e", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0);
  EXPECT_TRUE(match);
}

TEST_F(PCRETest_199, QuoteMetaEmptyString_199) {
  std::string result = PCRE::QuoteMeta("");
  EXPECT_EQ(result, "");
}

TEST_F(PCRETest_199, QuoteMetaDotStar_199) {
  std::string result = PCRE::QuoteMeta(".*");
  // The quoted version should NOT match arbitrary strings
  PCRE re(result);
  bool match = re.DoMatch("anything", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0);
  EXPECT_FALSE(match);
  // But it should match literal ".*"
  match = re.DoMatch(".*", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0);
  EXPECT_TRUE(match);
}

// ==================== CheckRewriteString Tests ====================

TEST_F(PCRETest_199, CheckRewriteStringValid_199) {
  PCRE re("(\\w+) (\\w+)");
  std::string error;
  bool result = re.CheckRewriteString("\\1-\\2", &error);
  EXPECT_TRUE(result);
}

TEST_F(PCRETest_199, CheckRewriteStringInvalidBackref_199) {
  PCRE re("(\\w+)");
  std::string error;
  bool result = re.CheckRewriteString("\\2", &error);
  EXPECT_FALSE(result);
  EXPECT_FALSE(error.empty());
}

TEST_F(PCRETest_199, CheckRewriteStringNoBackrefs_199) {
  PCRE re("hello");
  std::string error;
  bool result = re.CheckRewriteString("replacement", &error);
  EXPECT_TRUE(result);
}

// ==================== HitLimit and ClearHitLimit Tests ====================

TEST_F(PCRETest_199, HitLimitInitiallyFalse_199) {
  PCRE re("hello");
  EXPECT_FALSE(re.HitLimit());
}

TEST_F(PCRETest_199, ClearHitLimitNoError_199) {
  PCRE re("hello");
  re.ClearHitLimit();
  EXPECT_FALSE(re.HitLimit());
}

// ==================== Pattern and Error Tests ====================

TEST_F(PCRETest_199, PatternReturnsOriginal_199) {
  PCRE re("test pattern (\\d+)");
  EXPECT_EQ(re.pattern(), "test pattern (\\d+)");
}

TEST_F(PCRETest_199, ErrorEmptyForValidPattern_199) {
  PCRE re("valid");
  EXPECT_TRUE(re.error().empty());
}

// ==================== Arg Tests ====================

TEST_F(PCRETest_199, ArgDefaultConstructor_199) {
  PCRE::Arg arg;
  // Default constructed Arg should parse null (accept anything)
  bool result = arg.Parse("test", 4);
  EXPECT_TRUE(result);
}

TEST_F(PCRETest_199, ArgParseString_199) {
  std::string value;
  PCRE::Arg arg(&value);
  bool result = arg.Parse("hello", 5);
  EXPECT_TRUE(result);
  EXPECT_EQ(value, "hello");
}

TEST_F(PCRETest_199, ArgParseInt_199) {
  int value = 0;
  PCRE::Arg arg(&value);
  bool result = arg.Parse("42", 2);
  EXPECT_TRUE(result);
  EXPECT_EQ(value, 42);
}

TEST_F(PCRETest_199, ArgParseIntNegative_199) {
  int value = 0;
  PCRE::Arg arg(&value);
  bool result = arg.Parse("-123", 4);
  EXPECT_TRUE(result);
  EXPECT_EQ(value, -123);
}

TEST_F(PCRETest_199, ArgParseDouble_199) {
  double value = 0.0;
  PCRE::Arg arg(&value);
  bool result = arg.Parse("3.14", 4);
  EXPECT_TRUE(result);
  EXPECT_DOUBLE_EQ(value, 3.14);
}

TEST_F(PCRETest_199, ArgParseFloat_199) {
  float value = 0.0f;
  PCRE::Arg arg(&value);
  bool result = arg.Parse("2.5", 3);
  EXPECT_TRUE(result);
  EXPECT_FLOAT_EQ(value, 2.5f);
}

TEST_F(PCRETest_199, ArgParseChar_199) {
  char value = '\0';
  PCRE::Arg arg(&value);
  bool result = arg.Parse("A", 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(value, 'A');
}

TEST_F(PCRETest_199, ArgParseIntInvalid_199) {
  int value = 0;
  PCRE::Arg arg(&value);
  bool result = arg.Parse("not_a_number", 12);
  EXPECT_FALSE(result);
}

TEST_F(PCRETest_199, ArgParseEmptyString_199) {
  std::string value;
  PCRE::Arg arg(&value);
  bool result = arg.Parse("", 0);
  EXPECT_TRUE(result);
  EXPECT_EQ(value, "");
}

TEST_F(PCRETest_199, ArgParseStringView_199) {
  absl::string_view value;
  PCRE::Arg arg(&value);
  const char* str = "hello";
  bool result = arg.Parse(str, 5);
  EXPECT_TRUE(result);
  EXPECT_EQ(value, "hello");
}

// ==================== Complex Pattern Tests ====================

TEST_F(PCRETest_199, DoMatchComplexPattern_199) {
  PCRE re("(\\d{4})-(\\d{2})-(\\d{2})");
  std::string year, month, day;
  PCRE::Arg arg1(&year);
  PCRE::Arg arg2(&month);
  PCRE::Arg arg3(&day);
  const PCRE::Arg* args[] = {&arg1, &arg2, &arg3};
  bool result = re.DoMatch("2023-12-25", PCRE::ANCHOR_BOTH, nullptr, args, 3);
  EXPECT_TRUE(result);
  EXPECT_EQ(year, "2023");
  EXPECT_EQ(month, "12");
  EXPECT_EQ(day, "25");
}

TEST_F(PCRETest_199, DoMatchPartialConsumption_199) {
  PCRE re("(\\d+)");
  size_t consumed = 0;
  int number = 0;
  PCRE::Arg arg(&number);
  const PCRE::Arg* args[] = {&arg};
  bool result = re.DoMatch("123abc", PCRE::ANCHOR_START, &consumed, args, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(number, 123);
  EXPECT_EQ(consumed, 3u);
}

TEST_F(PCRETest_199, DoMatchUnanchoredFindsSubstring_199) {
  PCRE re("(\\d+)");
  int number = 0;
  PCRE::Arg arg(&number);
  const PCRE::Arg* args[] = {&arg};
  bool result = re.DoMatch("abc123def", PCRE::UNANCHORED, nullptr, args, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(number, 123);
}

// ==================== Boundary Tests ====================

TEST_F(PCRETest_199, DoMatchSingleCharacter_199) {
  PCRE re("a");
  bool result = re.DoMatch("a", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0);
  EXPECT_TRUE(result);
}

TEST_F(PCRETest_199, DoMatchSingleCharacterNoMatch_199) {
  PCRE re("a");
  bool result = re.DoMatch("b", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0);
  EXPECT_FALSE(result);
}

TEST_F(PCRETest_199, GlobalReplaceEmptyPattern_199) {
  std::string str = "abc";
  PCRE re("");
  int count = PCRE::GlobalReplace(&str, re, "x");
  // Empty pattern matches at every position
  EXPECT_GT(count, 0);
}

TEST_F(PCRETest_199, ReplaceFirstOccurrenceOnly_199) {
  std::string str = "aaa";
  PCRE re("a");
  bool result = PCRE::Replace(&str, re, "b");
  EXPECT_TRUE(result);
  EXPECT_EQ(str, "baa");
}

}  // namespace re2
