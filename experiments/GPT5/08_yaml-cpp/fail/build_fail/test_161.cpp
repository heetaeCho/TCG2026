// File: ./TestProjects/yaml-cpp/test/scanscalar_test_161.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "stream.h"
#include "regex_yaml.h"
#include "scanscalar.h"
#include "exceptions.h"

namespace {

class ScanScalarTest_161 : public ::testing::Test {
 protected:
  static YAML::Stream MakeStream(const std::string& text, std::stringstream& backing) {
    backing.str(text);
    backing.clear();
    return YAML::Stream(backing);
  }
};

}  // namespace

TEST_F(ScanScalarTest_161, ReturnsInputUntilEndRegexWithoutEatingEnd_161) {
  std::stringstream ss;
  auto stream = MakeStream("abc!def", ss);

  YAML::ScanScalarParams params;
  YAML::RegEx end('!');
  params.end = &end;
  params.eatEnd = false;

  const std::string out = YAML::ScanScalar(stream, params);
  EXPECT_EQ(out, "abc");

  // Verify terminator was NOT consumed.
  EXPECT_EQ(stream.peek(), '!');
}

TEST_F(ScanScalarTest_161, ConsumesEndRegexWhenEatEndTrue_161) {
  std::stringstream ss;
  auto stream = MakeStream("abc!def", ss);

  YAML::ScanScalarParams params;
  YAML::RegEx end('!');
  params.end = &end;
  params.eatEnd = true;

  const std::string out = YAML::ScanScalar(stream, params);
  EXPECT_EQ(out, "abc");

  // Verify terminator WAS consumed.
  EXPECT_EQ(stream.peek(), 'd');
}

TEST_F(ScanScalarTest_161, DontFoldPreservesLineBreakAsNewline_161) {
  std::stringstream ss;
  auto stream = MakeStream("a\nb!", ss);

  YAML::ScanScalarParams params;
  YAML::RegEx end('!');
  params.end = &end;
  params.eatEnd = true;
  params.fold = YAML::DONT_FOLD;

  const std::string out = YAML::ScanScalar(stream, params);
  EXPECT_EQ(out, std::string("a\nb"));
  EXPECT_EQ(stream.peek(), YAML::Stream::eof());
}

TEST_F(ScanScalarTest_161, FoldFlowFoldsSingleLineBreakIntoSpace_161) {
  std::stringstream ss;
  auto stream = MakeStream("a\nb!", ss);

  YAML::ScanScalarParams params;
  YAML::RegEx end('!');
  params.end = &end;
  params.eatEnd = true;
  params.fold = YAML::FOLD_FLOW;

  const std::string out = YAML::ScanScalar(stream, params);
  EXPECT_EQ(out, "a b");
}

TEST_F(ScanScalarTest_161, TrimTrailingSpacesRemovesSpacesBeforeEnd_161) {
  std::stringstream ss;
  auto stream = MakeStream("abc   \t!", ss);

  YAML::ScanScalarParams params;
  YAML::RegEx end('!');
  params.end = &end;
  params.eatEnd = true;
  params.trimTrailingSpaces = true;

  const std::string out = YAML::ScanScalar(stream, params);
  EXPECT_EQ(out, "abc");
}

TEST_F(ScanScalarTest_161, ChompStripRemovesTrailingNewlines_161) {
  std::stringstream ss;
  auto stream = MakeStream("a\n\n!", ss);

  YAML::ScanScalarParams params;
  YAML::RegEx end('!');
  params.end = &end;
  params.eatEnd = true;
  params.fold = YAML::DONT_FOLD;
  params.chomp = YAML::STRIP;

  const std::string out = YAML::ScanScalar(stream, params);

  // With DONT_FOLD, line breaks are observable as '\n' in output, and STRIP removes trailing '\n'.
  EXPECT_EQ(out, "a");
}

TEST_F(ScanScalarTest_161, LeadingSpacesFlagSetWhenIndentNotMetAfterBreak_161) {
  std::stringstream ss;
  auto stream = MakeStream("a\n b", ss);  // only 1 space indentation

  YAML::ScanScalarParams params;
  params.fold = YAML::DONT_FOLD;
  params.indent = 2;           // require at least 2 columns
  params.detectIndent = false;
  params.eatLeadingWhitespace = true;

  const std::string out = YAML::ScanScalar(stream, params);

  EXPECT_EQ(out, "a\n");
  EXPECT_TRUE(params.leadingSpaces);
}

TEST_F(ScanScalarTest_161, ThrowsOnDocIndicatorWhenConfiguredToThrow_161) {
  std::stringstream ss;
  auto stream = MakeStream("---\nabc", ss);

  YAML::ScanScalarParams params;
  params.onDocIndicator = YAML::THROW;

  try {
    (void)YAML::ScanScalar(stream, params);
    FAIL() << "Expected YAML::ParserException";
  } catch (const YAML::ParserException& e) {
    // Verify the observable error message.
    EXPECT_STREQ(e.msg, YAML::ErrorMsg::DOC_IN_SCALAR);
  }
}

TEST_F(ScanScalarTest_161, ThrowsOnEOFWhenEatEndTrueAndEndNeverFound_161) {
  std::stringstream ss;
  auto stream = MakeStream("abc", ss);

  YAML::ScanScalarParams params;
  YAML::RegEx end('!');
  params.end = &end;
  params.eatEnd = true;

  try {
    (void)YAML::ScanScalar(stream, params);
    FAIL() << "Expected YAML::ParserException";
  } catch (const YAML::ParserException& e) {
    EXPECT_STREQ(e.msg, YAML::ErrorMsg::EOF_IN_SCALAR);
  }
}

TEST_F(ScanScalarTest_161, ThrowsOnTabInIndentationWhenConfiguredToThrow_161) {
  std::stringstream ss;
  auto stream = MakeStream("a\n\tb", ss);

  YAML::ScanScalarParams params;
  params.fold = YAML::DONT_FOLD;
  params.indent = 2;
  params.eatLeadingWhitespace = true;
  params.onTabInIndentation = YAML::THROW;

  try {
    (void)YAML::ScanScalar(stream, params);
    FAIL() << "Expected YAML::ParserException";
  } catch (const YAML::ParserException& e) {
    EXPECT_STREQ(e.msg, YAML::ErrorMsg::TAB_IN_INDENTATION);
  }
}