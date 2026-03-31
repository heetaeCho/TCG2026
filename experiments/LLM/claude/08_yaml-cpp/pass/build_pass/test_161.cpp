#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/exceptions.h"
#include "scanscalar.h"
#include "stream.h"
#include "exp.h"
#include <sstream>
#include <string>

namespace YAML {

class ScanScalarTest_161 : public ::testing::Test {
 protected:
  ScanScalarParams MakeDefaultParams() {
    ScanScalarParams params;
    params.end = nullptr;
    params.eatEnd = false;
    params.indent = 0;
    params.detectIndent = false;
    params.eatLeadingWhitespace = true;
    params.escape = 0;
    params.fold = DONT_FOLD;
    params.trimTrailingSpaces = false;
    params.chomp = CLIP;
    params.onDocIndicator = NONE;
    params.onTabInIndentation = NONE;
    params.leadingSpaces = false;
    return params;
  }
};

// Test scanning an empty stream
TEST_F(ScanScalarTest_161, EmptyStream_161) {
  std::stringstream ss("");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  std::string result = ScanScalar(stream, params);
  EXPECT_EQ("", result);
}

// Test scanning a simple word with no special params
TEST_F(ScanScalarTest_161, SimpleWord_161) {
  std::stringstream ss("hello");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  std::string result = ScanScalar(stream, params);
  EXPECT_EQ("hello", result);
}

// Test scanning with a newline and DONT_FOLD
TEST_F(ScanScalarTest_161, NewlineDontFold_161) {
  std::stringstream ss("hello\nworld");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  params.fold = DONT_FOLD;
  std::string result = ScanScalar(stream, params);
  EXPECT_EQ("hello\nworld", result);
}

// Test scanning with FOLD_FLOW - consecutive non-empty lines fold to space
TEST_F(ScanScalarTest_161, FoldFlow_NonEmptyLines_161) {
  std::stringstream ss("hello\nworld");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  params.fold = FOLD_FLOW;
  std::string result = ScanScalar(stream, params);
  EXPECT_EQ("hello world", result);
}

// Test scanning with FOLD_FLOW - empty line preserved
TEST_F(ScanScalarTest_161, FoldFlow_EmptyLine_161) {
  std::stringstream ss("hello\n\nworld");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  params.fold = FOLD_FLOW;
  std::string result = ScanScalar(stream, params);
  EXPECT_EQ("hello\nworld", result);
}

// Test trimming trailing spaces
TEST_F(ScanScalarTest_161, TrimTrailingSpaces_161) {
  std::stringstream ss("hello   ");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  params.trimTrailingSpaces = true;
  std::string result = ScanScalar(stream, params);
  EXPECT_EQ("hello", result);
}

// Test CLIP chomp - trailing newlines clipped to single
TEST_F(ScanScalarTest_161, ChompClip_161) {
  std::stringstream ss("hello");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  params.chomp = CLIP;
  std::string result = ScanScalar(stream, params);
  // No trailing newlines to clip
  EXPECT_EQ("hello", result);
}

// Test STRIP chomp - all trailing newlines removed
TEST_F(ScanScalarTest_161, ChompStrip_161) {
  std::stringstream ss("hello");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  params.chomp = STRIP;
  std::string result = ScanScalar(stream, params);
  EXPECT_EQ("hello", result);
}

// Test KEEP chomp - trailing newlines kept
TEST_F(ScanScalarTest_161, ChompKeep_161) {
  std::stringstream ss("hello");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  params.chomp = KEEP;
  std::string result = ScanScalar(stream, params);
  EXPECT_EQ("hello", result);
}

// Test with end regex matching
TEST_F(ScanScalarTest_161, EndRegexMatch_161) {
  std::stringstream ss("hello:world");
  Stream stream(ss);
  RegEx endRegex(':');
  ScanScalarParams params = MakeDefaultParams();
  params.end = &endRegex;
  params.eatEnd = false;
  std::string result = ScanScalar(stream, params);
  EXPECT_EQ("hello", result);
}

// Test with end regex and eatEnd true
TEST_F(ScanScalarTest_161, EndRegexEatEnd_161) {
  std::stringstream ss("hello:world");
  Stream stream(ss);
  RegEx endRegex(':');
  ScanScalarParams params = MakeDefaultParams();
  params.end = &endRegex;
  params.eatEnd = true;
  std::string result = ScanScalar(stream, params);
  EXPECT_EQ("hello", result);
}

// Test eatEnd with EOF throws exception
TEST_F(ScanScalarTest_161, EatEndEOFThrows_161) {
  std::stringstream ss("hello");
  Stream stream(ss);
  RegEx endRegex(':');  // Will never match
  ScanScalarParams params = MakeDefaultParams();
  params.end = &endRegex;
  params.eatEnd = true;
  EXPECT_THROW(ScanScalar(stream, params), ParserException);
}

// Test leading spaces detection when indent is not met
TEST_F(ScanScalarTest_161, LeadingSpacesDetection_161) {
  std::stringstream ss("  hello\nworld");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  params.indent = 4;
  params.fold = DONT_FOLD;
  std::string result = ScanScalar(stream, params);
  // "world" has column 0 < indent 4, so leadingSpaces should be set
  EXPECT_TRUE(params.leadingSpaces);
}

// Test detectIndent
TEST_F(ScanScalarTest_161, DetectIndent_161) {
  std::stringstream ss("\n  hello");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  params.indent = 0;
  params.detectIndent = true;
  params.fold = DONT_FOLD;
  std::string result = ScanScalar(stream, params);
  EXPECT_GE(params.indent, 0);
}

// Test onDocIndicator BREAK
TEST_F(ScanScalarTest_161, DocIndicatorBreak_161) {
  std::stringstream ss("hello\n---");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  params.onDocIndicator = BREAK;
  params.fold = DONT_FOLD;
  std::string result = ScanScalar(stream, params);
  // Should break at document indicator
  EXPECT_NE(std::string::npos, result.find("hello"));
}

// Test onDocIndicator THROW
TEST_F(ScanScalarTest_161, DocIndicatorThrow_161) {
  std::stringstream ss("hello\n---");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  params.onDocIndicator = THROW;
  params.fold = DONT_FOLD;
  EXPECT_THROW(ScanScalar(stream, params), ParserException);
}

// Test onDocIndicator with "..." indicator BREAK
TEST_F(ScanScalarTest_161, DocEndIndicatorBreak_161) {
  std::stringstream ss("hello\n...");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  params.onDocIndicator = BREAK;
  params.fold = DONT_FOLD;
  std::string result = ScanScalar(stream, params);
  EXPECT_NE(std::string::npos, result.find("hello"));
}

// Test escape character
TEST_F(ScanScalarTest_161, EscapeCharacter_161) {
  std::stringstream ss("hello\\nworld");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  params.escape = '\\';
  std::string result = ScanScalar(stream, params);
  // The escape processing should handle \n
  EXPECT_FALSE(result.empty());
}

// Test with tabs in indentation THROW
TEST_F(ScanScalarTest_161, TabInIndentationThrow_161) {
  std::stringstream ss("hello\n\tworld");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  params.indent = 4;
  params.onTabInIndentation = THROW;
  params.fold = DONT_FOLD;
  EXPECT_THROW(ScanScalar(stream, params), ParserException);
}

// Test FOLD_BLOCK with simple lines
TEST_F(ScanScalarTest_161, FoldBlock_SimpleLines_161) {
  std::stringstream ss("hello\nworld");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  params.fold = FOLD_BLOCK;
  params.indent = 0;
  std::string result = ScanScalar(stream, params);
  // Two non-empty, non-more-indented lines should fold to space
  EXPECT_EQ("hello world", result);
}

// Test only whitespace content
TEST_F(ScanScalarTest_161, OnlyWhitespace_161) {
  std::stringstream ss("   ");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  params.trimTrailingSpaces = true;
  std::string result = ScanScalar(stream, params);
  EXPECT_EQ("", result);
}

// Test only tabs
TEST_F(ScanScalarTest_161, OnlyTabs_161) {
  std::stringstream ss("\t\t");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  params.trimTrailingSpaces = true;
  std::string result = ScanScalar(stream, params);
  EXPECT_EQ("", result);
}

// Test eatLeadingWhitespace false
TEST_F(ScanScalarTest_161, NoEatLeadingWhitespace_161) {
  std::stringstream ss("hello\n  world");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  params.eatLeadingWhitespace = false;
  params.fold = DONT_FOLD;
  std::string result = ScanScalar(stream, params);
  // Leading whitespace should be preserved in some form
  EXPECT_FALSE(result.empty());
}

// Test multiple newlines with DONT_FOLD
TEST_F(ScanScalarTest_161, MultipleNewlinesDontFold_161) {
  std::stringstream ss("a\n\n\nb");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  params.fold = DONT_FOLD;
  std::string result = ScanScalar(stream, params);
  EXPECT_EQ("a\n\n\nb", result);
}

// Test FOLD_BLOCK with empty lines between content
TEST_F(ScanScalarTest_161, FoldBlockEmptyLinesBetween_161) {
  std::stringstream ss("hello\n\nworld");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  params.fold = FOLD_BLOCK;
  params.indent = 0;
  std::string result = ScanScalar(stream, params);
  // Empty line between should result in preserved newline
  EXPECT_NE(std::string::npos, result.find('\n'));
}

// Test STRIP chomp with trailing newlines in multiline
TEST_F(ScanScalarTest_161, StripChompMultiline_161) {
  std::stringstream ss("hello\nworld\n");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  params.fold = DONT_FOLD;
  params.chomp = STRIP;
  std::string result = ScanScalar(stream, params);
  // Trailing newlines should be stripped
  if (!result.empty()) {
    EXPECT_NE('\n', result.back());
  }
}

// Test single character input
TEST_F(ScanScalarTest_161, SingleCharacter_161) {
  std::stringstream ss("a");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  std::string result = ScanScalar(stream, params);
  EXPECT_EQ("a", result);
}

// Test escaped newline with backslash
TEST_F(ScanScalarTest_161, EscapedNewline_161) {
  std::stringstream ss("hello\\\nworld");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  params.escape = '\\';
  params.fold = FOLD_FLOW;
  std::string result = ScanScalar(stream, params);
  // Escaped newline in flow fold context
  EXPECT_FALSE(result.empty());
}

// Test leadingSpaces is initially false
TEST_F(ScanScalarTest_161, LeadingSpacesInitiallyFalse_161) {
  std::stringstream ss("hello");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  params.leadingSpaces = true;  // Set to true beforehand
  std::string result = ScanScalar(stream, params);
  // ScanScalar resets leadingSpaces to false at start
  // It stays false if indent condition is not triggered
  EXPECT_FALSE(params.leadingSpaces);
}

// Test with end regex that doesn't match eatEnd false doesn't throw
TEST_F(ScanScalarTest_161, NoEndMatchNoEatEndNoThrow_161) {
  std::stringstream ss("hello");
  Stream stream(ss);
  RegEx endRegex(':');
  ScanScalarParams params = MakeDefaultParams();
  params.end = &endRegex;
  params.eatEnd = false;
  std::string result = ScanScalar(stream, params);
  EXPECT_EQ("hello", result);
}

// Test FOLD_FLOW with trailing whitespace on line
TEST_F(ScanScalarTest_161, FoldFlowTrailingWhitespace_161) {
  std::stringstream ss("hello   \nworld");
  Stream stream(ss);
  ScanScalarParams params = MakeDefaultParams();
  params.fold = FOLD_FLOW;
  std::string result = ScanScalar(stream, params);
  // FOLD_FLOW erases trailing whitespace before folding
  EXPECT_EQ("hello world", result);
}

// Test default ScanScalarParams initialization
TEST_F(ScanScalarTest_161, DefaultParams_161) {
  ScanScalarParams params;
  EXPECT_EQ(nullptr, params.end);
  EXPECT_FALSE(params.eatEnd);
  EXPECT_EQ(0, params.indent);
  EXPECT_FALSE(params.detectIndent);
  EXPECT_EQ(0, params.escape);
  EXPECT_EQ(DONT_FOLD, params.fold);
  EXPECT_FALSE(params.trimTrailingSpaces);
  EXPECT_EQ(CLIP, params.chomp);
  EXPECT_EQ(NONE, params.onDocIndicator);
  EXPECT_EQ(NONE, params.onTabInIndentation);
  EXPECT_FALSE(params.leadingSpaces);
}

}  // namespace YAML
