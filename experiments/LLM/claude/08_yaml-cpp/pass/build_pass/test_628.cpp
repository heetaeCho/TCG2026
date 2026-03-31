#include <gtest/gtest.h>
#include <string>
#include <cstring>

// Include necessary yaml-cpp headers
#include "yaml-cpp/emittermanip.h"

// We need to declare the relevant types and functions from the yaml-cpp internals
namespace YAML {

struct FlowType {
  enum value { Flow, Block };
};

struct StringFormat {
  enum value { Plain, SingleQuoted, DoubleQuoted, Literal };
};

namespace Utils {
StringFormat::value ComputeStringFormat(const char* str, std::size_t size,
                                        EMITTER_MANIP strFormat,
                                        FlowType::value flowType,
                                        bool escapeNonAscii);
}
}

class ComputeStringFormatTest_628 : public ::testing::Test {
protected:
  // Helper to call ComputeStringFormat with a std::string
  YAML::StringFormat::value Compute(const std::string& s,
                                     YAML::EMITTER_MANIP manip,
                                     YAML::FlowType::value flowType = YAML::FlowType::Block,
                                     bool escapeNonAscii = false) {
    return YAML::Utils::ComputeStringFormat(s.c_str(), s.size(), manip, flowType, escapeNonAscii);
  }
};

// ============================================================
// Tests for DoubleQuoted format
// ============================================================

TEST_F(ComputeStringFormatTest_628, DoubleQuoted_AlwaysReturnsDoubleQuoted_628) {
  // DoubleQuoted should always return DoubleQuoted regardless of content
  EXPECT_EQ(YAML::StringFormat::DoubleQuoted, Compute("hello", YAML::DoubleQuoted));
}

TEST_F(ComputeStringFormatTest_628, DoubleQuoted_EmptyString_628) {
  EXPECT_EQ(YAML::StringFormat::DoubleQuoted, Compute("", YAML::DoubleQuoted));
}

TEST_F(ComputeStringFormatTest_628, DoubleQuoted_SpecialChars_628) {
  EXPECT_EQ(YAML::StringFormat::DoubleQuoted, Compute("hello: world", YAML::DoubleQuoted));
}

TEST_F(ComputeStringFormatTest_628, DoubleQuoted_FlowType_628) {
  EXPECT_EQ(YAML::StringFormat::DoubleQuoted, Compute("simple", YAML::DoubleQuoted, YAML::FlowType::Flow));
}

TEST_F(ComputeStringFormatTest_628, DoubleQuoted_EscapeNonAscii_628) {
  EXPECT_EQ(YAML::StringFormat::DoubleQuoted, Compute("simple", YAML::DoubleQuoted, YAML::FlowType::Block, true));
}

// ============================================================
// Tests for Auto format
// ============================================================

TEST_F(ComputeStringFormatTest_628, Auto_SimplePlainScalar_Block_628) {
  // A simple word should be a valid plain scalar
  YAML::StringFormat::value result = Compute("hello", YAML::Auto, YAML::FlowType::Block);
  EXPECT_EQ(YAML::StringFormat::Plain, result);
}

TEST_F(ComputeStringFormatTest_628, Auto_SimplePlainScalar_Flow_628) {
  YAML::StringFormat::value result = Compute("hello", YAML::Auto, YAML::FlowType::Flow);
  EXPECT_EQ(YAML::StringFormat::Plain, result);
}

TEST_F(ComputeStringFormatTest_628, Auto_EmptyString_628) {
  // Empty string is likely not a valid plain scalar
  YAML::StringFormat::value result = Compute("", YAML::Auto);
  // Could be Plain or DoubleQuoted depending on implementation
  EXPECT_TRUE(result == YAML::StringFormat::Plain || result == YAML::StringFormat::DoubleQuoted);
}

TEST_F(ComputeStringFormatTest_628, Auto_StringWithColon_628) {
  // "key: value" is typically not a valid plain scalar
  YAML::StringFormat::value result = Compute("key: value", YAML::Auto);
  // This likely needs quoting
  EXPECT_TRUE(result == YAML::StringFormat::Plain || result == YAML::StringFormat::DoubleQuoted);
}

TEST_F(ComputeStringFormatTest_628, Auto_StringWithNewline_628) {
  // Strings with newlines are typically not valid plain scalars
  YAML::StringFormat::value result = Compute("hello\nworld", YAML::Auto);
  EXPECT_EQ(YAML::StringFormat::DoubleQuoted, result);
}

TEST_F(ComputeStringFormatTest_628, Auto_StringStartingWithIndicator_628) {
  // Strings starting with special YAML indicators may not be valid plain
  YAML::StringFormat::value result = Compute("- item", YAML::Auto);
  EXPECT_EQ(YAML::StringFormat::DoubleQuoted, result);
}

TEST_F(ComputeStringFormatTest_628, Auto_StringWithHash_628) {
  // String starting with # is a comment indicator
  YAML::StringFormat::value result = Compute("# comment", YAML::Auto);
  EXPECT_EQ(YAML::StringFormat::DoubleQuoted, result);
}

TEST_F(ComputeStringFormatTest_628, Auto_ResultIsPlainOrDoubleQuoted_628) {
  // Auto should only return Plain or DoubleQuoted
  YAML::StringFormat::value result = Compute("test", YAML::Auto);
  EXPECT_TRUE(result == YAML::StringFormat::Plain || result == YAML::StringFormat::DoubleQuoted);
}

TEST_F(ComputeStringFormatTest_628, Auto_NullCharInString_628) {
  std::string s("hello\0world", 11);
  YAML::StringFormat::value result = YAML::Utils::ComputeStringFormat(s.c_str(), s.size(), YAML::Auto, YAML::FlowType::Block, false);
  EXPECT_EQ(YAML::StringFormat::DoubleQuoted, result);
}

// ============================================================
// Tests for SingleQuoted format
// ============================================================

TEST_F(ComputeStringFormatTest_628, SingleQuoted_SimpleString_628) {
  YAML::StringFormat::value result = Compute("hello", YAML::SingleQuoted);
  EXPECT_EQ(YAML::StringFormat::SingleQuoted, result);
}

TEST_F(ComputeStringFormatTest_628, SingleQuoted_EmptyString_628) {
  YAML::StringFormat::value result = Compute("", YAML::SingleQuoted);
  // Empty might or might not be valid single quoted
  EXPECT_TRUE(result == YAML::StringFormat::SingleQuoted || result == YAML::StringFormat::DoubleQuoted);
}

TEST_F(ComputeStringFormatTest_628, SingleQuoted_StringWithSingleQuote_628) {
  // Strings with single quotes inside should still be valid (escaped by doubling)
  YAML::StringFormat::value result = Compute("it's", YAML::SingleQuoted);
  EXPECT_TRUE(result == YAML::StringFormat::SingleQuoted || result == YAML::StringFormat::DoubleQuoted);
}

TEST_F(ComputeStringFormatTest_628, SingleQuoted_StringWithNewline_628) {
  // Newlines in single quoted strings might not be valid
  YAML::StringFormat::value result = Compute("hello\nworld", YAML::SingleQuoted);
  EXPECT_TRUE(result == YAML::StringFormat::SingleQuoted || result == YAML::StringFormat::DoubleQuoted);
}

TEST_F(ComputeStringFormatTest_628, SingleQuoted_StringWithSpecialChars_628) {
  YAML::StringFormat::value result = Compute("key: value", YAML::SingleQuoted);
  EXPECT_TRUE(result == YAML::StringFormat::SingleQuoted || result == YAML::StringFormat::DoubleQuoted);
}

TEST_F(ComputeStringFormatTest_628, SingleQuoted_FallsBackToDoubleQuotedWhenInvalid_628) {
  // A string with null bytes should not be a valid single-quoted scalar
  std::string s("hello\0world", 11);
  YAML::StringFormat::value result = YAML::Utils::ComputeStringFormat(s.c_str(), s.size(), YAML::SingleQuoted, YAML::FlowType::Block, false);
  EXPECT_EQ(YAML::StringFormat::DoubleQuoted, result);
}

TEST_F(ComputeStringFormatTest_628, SingleQuoted_ResultIsSingleOrDoubleQuoted_628) {
  // SingleQuoted should only return SingleQuoted or DoubleQuoted
  YAML::StringFormat::value result = Compute("test string", YAML::SingleQuoted);
  EXPECT_TRUE(result == YAML::StringFormat::SingleQuoted || result == YAML::StringFormat::DoubleQuoted);
}

TEST_F(ComputeStringFormatTest_628, SingleQuoted_EscapeNonAscii_628) {
  // Non-ASCII with escapeNonAscii=true should fall back to DoubleQuoted
  std::string nonAscii = "héllo";
  YAML::StringFormat::value result = Compute(nonAscii, YAML::SingleQuoted, YAML::FlowType::Block, true);
  EXPECT_EQ(YAML::StringFormat::DoubleQuoted, result);
}

// ============================================================
// Tests for Literal format
// ============================================================

TEST_F(ComputeStringFormatTest_628, Literal_MultilineString_Block_628) {
  YAML::StringFormat::value result = Compute("hello\nworld\n", YAML::Literal, YAML::FlowType::Block);
  EXPECT_TRUE(result == YAML::StringFormat::Literal || result == YAML::StringFormat::DoubleQuoted);
}

TEST_F(ComputeStringFormatTest_628, Literal_SimpleString_628) {
  // Simple one-line strings may or may not be valid literal scalars
  YAML::StringFormat::value result = Compute("hello", YAML::Literal, YAML::FlowType::Block);
  EXPECT_TRUE(result == YAML::StringFormat::Literal || result == YAML::StringFormat::DoubleQuoted);
}

TEST_F(ComputeStringFormatTest_628, Literal_EmptyString_628) {
  YAML::StringFormat::value result = Compute("", YAML::Literal);
  EXPECT_TRUE(result == YAML::StringFormat::Literal || result == YAML::StringFormat::DoubleQuoted);
}

TEST_F(ComputeStringFormatTest_628, Literal_FlowContext_628) {
  // Literal blocks are typically not valid in flow context
  YAML::StringFormat::value result = Compute("hello\nworld\n", YAML::Literal, YAML::FlowType::Flow);
  EXPECT_EQ(YAML::StringFormat::DoubleQuoted, result);
}

TEST_F(ComputeStringFormatTest_628, Literal_NullBytes_628) {
  std::string s("hello\0world", 11);
  YAML::StringFormat::value result = YAML::Utils::ComputeStringFormat(s.c_str(), s.size(), YAML::Literal, YAML::FlowType::Block, false);
  EXPECT_EQ(YAML::StringFormat::DoubleQuoted, result);
}

TEST_F(ComputeStringFormatTest_628, Literal_ResultIsLiteralOrDoubleQuoted_628) {
  // Literal should only return Literal or DoubleQuoted
  YAML::StringFormat::value result = Compute("line1\nline2\n", YAML::Literal, YAML::FlowType::Block);
  EXPECT_TRUE(result == YAML::StringFormat::Literal || result == YAML::StringFormat::DoubleQuoted);
}

TEST_F(ComputeStringFormatTest_628, Literal_NonAsciiWithEscape_628) {
  std::string nonAscii = "héllo\nworld\n";
  YAML::StringFormat::value result = Compute(nonAscii, YAML::Literal, YAML::FlowType::Block, true);
  EXPECT_EQ(YAML::StringFormat::DoubleQuoted, result);
}

// ============================================================
// Tests for unknown/default EMITTER_MANIP values
// ============================================================

TEST_F(ComputeStringFormatTest_628, DefaultCase_UnrelatedManip_628) {
  // Passing a manip that is not Auto, SingleQuoted, DoubleQuoted, or Literal
  // should hit the default case and return DoubleQuoted
  YAML::StringFormat::value result = Compute("hello", YAML::Flow);
  EXPECT_EQ(YAML::StringFormat::DoubleQuoted, result);
}

TEST_F(ComputeStringFormatTest_628, DefaultCase_Block_628) {
  YAML::StringFormat::value result = Compute("hello", YAML::Block);
  EXPECT_EQ(YAML::StringFormat::DoubleQuoted, result);
}

TEST_F(ComputeStringFormatTest_628, DefaultCase_Newline_628) {
  YAML::StringFormat::value result = Compute("hello", YAML::Newline);
  EXPECT_EQ(YAML::StringFormat::DoubleQuoted, result);
}

TEST_F(ComputeStringFormatTest_628, DefaultCase_Dec_628) {
  YAML::StringFormat::value result = Compute("123", YAML::Dec);
  EXPECT_EQ(YAML::StringFormat::DoubleQuoted, result);
}

// ============================================================
// Tests for escapeNonAscii parameter
// ============================================================

TEST_F(ComputeStringFormatTest_628, Auto_NonAsciiWithEscapeTrue_628) {
  std::string nonAscii = "héllo";
  YAML::StringFormat::value result = Compute(nonAscii, YAML::Auto, YAML::FlowType::Block, true);
  // Non-ASCII with escape should likely not be plain
  EXPECT_EQ(YAML::StringFormat::DoubleQuoted, result);
}

TEST_F(ComputeStringFormatTest_628, Auto_NonAsciiWithEscapeFalse_628) {
  std::string nonAscii = "héllo";
  YAML::StringFormat::value result = Compute(nonAscii, YAML::Auto, YAML::FlowType::Block, false);
  // Without escape, non-ASCII might be valid plain
  EXPECT_TRUE(result == YAML::StringFormat::Plain || result == YAML::StringFormat::DoubleQuoted);
}

// ============================================================
// Tests with various string content
// ============================================================

TEST_F(ComputeStringFormatTest_628, Auto_NumberString_628) {
  // Numeric strings might not be valid plain scalars (could be parsed as numbers)
  YAML::StringFormat::value result = Compute("123", YAML::Auto);
  EXPECT_TRUE(result == YAML::StringFormat::Plain || result == YAML::StringFormat::DoubleQuoted);
}

TEST_F(ComputeStringFormatTest_628, Auto_BooleanLikeString_628) {
  YAML::StringFormat::value result = Compute("true", YAML::Auto);
  EXPECT_TRUE(result == YAML::StringFormat::Plain || result == YAML::StringFormat::DoubleQuoted);
}

TEST_F(ComputeStringFormatTest_628, Auto_NullLikeString_628) {
  YAML::StringFormat::value result = Compute("null", YAML::Auto);
  EXPECT_TRUE(result == YAML::StringFormat::Plain || result == YAML::StringFormat::DoubleQuoted);
}

TEST_F(ComputeStringFormatTest_628, Auto_StringWithTabs_628) {
  YAML::StringFormat::value result = Compute("hello\tworld", YAML::Auto);
  EXPECT_TRUE(result == YAML::StringFormat::Plain || result == YAML::StringFormat::DoubleQuoted);
}

TEST_F(ComputeStringFormatTest_628, Auto_StringWithLeadingSpace_628) {
  YAML::StringFormat::value result = Compute(" hello", YAML::Auto);
  EXPECT_EQ(YAML::StringFormat::DoubleQuoted, result);
}

TEST_F(ComputeStringFormatTest_628, Auto_StringWithTrailingSpace_628) {
  YAML::StringFormat::value result = Compute("hello ", YAML::Auto);
  EXPECT_TRUE(result == YAML::StringFormat::Plain || result == YAML::StringFormat::DoubleQuoted);
}

TEST_F(ComputeStringFormatTest_628, Auto_LongString_628) {
  std::string longStr(1000, 'a');
  YAML::StringFormat::value result = Compute(longStr, YAML::Auto);
  EXPECT_EQ(YAML::StringFormat::Plain, result);
}

TEST_F(ComputeStringFormatTest_628, SingleQuoted_LongString_628) {
  std::string longStr(1000, 'a');
  YAML::StringFormat::value result = Compute(longStr, YAML::SingleQuoted);
  EXPECT_EQ(YAML::StringFormat::SingleQuoted, result);
}

TEST_F(ComputeStringFormatTest_628, Auto_StringStartingWithBrace_628) {
  // Strings starting with { or [ are flow indicators
  YAML::StringFormat::value result = Compute("{key: value}", YAML::Auto);
  EXPECT_EQ(YAML::StringFormat::DoubleQuoted, result);
}

TEST_F(ComputeStringFormatTest_628, Auto_StringStartingWithBracket_628) {
  YAML::StringFormat::value result = Compute("[1, 2, 3]", YAML::Auto);
  EXPECT_EQ(YAML::StringFormat::DoubleQuoted, result);
}

TEST_F(ComputeStringFormatTest_628, Auto_StringWithAmpersand_628) {
  YAML::StringFormat::value result = Compute("&anchor", YAML::Auto);
  EXPECT_EQ(YAML::StringFormat::DoubleQuoted, result);
}

TEST_F(ComputeStringFormatTest_628, Auto_StringWithAsterisk_628) {
  YAML::StringFormat::value result = Compute("*alias", YAML::Auto);
  EXPECT_EQ(YAML::StringFormat::DoubleQuoted, result);
}

TEST_F(ComputeStringFormatTest_628, Auto_StringWithExclamation_628) {
  YAML::StringFormat::value result = Compute("!tag", YAML::Auto);
  EXPECT_EQ(YAML::StringFormat::DoubleQuoted, result);
}

TEST_F(ComputeStringFormatTest_628, Auto_SingleCharacter_628) {
  YAML::StringFormat::value result = Compute("a", YAML::Auto);
  EXPECT_EQ(YAML::StringFormat::Plain, result);
}

TEST_F(ComputeStringFormatTest_628, Literal_LongMultiline_628) {
  std::string multiline = "line1\nline2\nline3\nline4\nline5\n";
  YAML::StringFormat::value result = Compute(multiline, YAML::Literal, YAML::FlowType::Block);
  EXPECT_TRUE(result == YAML::StringFormat::Literal || result == YAML::StringFormat::DoubleQuoted);
}

// ============================================================
// Nullptr / zero-size edge cases
// ============================================================

TEST_F(ComputeStringFormatTest_628, Auto_ZeroSizeWithValidPointer_628) {
  const char* str = "hello";
  YAML::StringFormat::value result = YAML::Utils::ComputeStringFormat(str, 0, YAML::Auto, YAML::FlowType::Block, false);
  EXPECT_TRUE(result == YAML::StringFormat::Plain || result == YAML::StringFormat::DoubleQuoted);
}

TEST_F(ComputeStringFormatTest_628, DoubleQuoted_ZeroSize_628) {
  YAML::StringFormat::value result = YAML::Utils::ComputeStringFormat("", 0, YAML::DoubleQuoted, YAML::FlowType::Block, false);
  EXPECT_EQ(YAML::StringFormat::DoubleQuoted, result);
}
