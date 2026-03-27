// File: ./TestProjects/yaml-cpp/test/exp_escape_test.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "stream.h"                 // YAML::Stream
#include "yaml-cpp/exceptions.h"    // YAML::ParserException, YAML::ErrorMsg

// Forward declaration (in case there isn't a public header for exp.cpp)
namespace YAML {
namespace Exp {
std::string Escape(Stream& in);
}  // namespace Exp
}  // namespace YAML

namespace {

struct StreamHolder_168 {
  std::stringstream input;
  YAML::Stream stream;

  explicit StreamHolder_168(const std::string& s)
      : input(s), stream(input) {}
};

static std::string ByteStr_168(unsigned int b) {
  return std::string(1, static_cast<char>(static_cast<unsigned char>(b)));
}

}  // namespace

class EscapeTest_168 : public ::testing::Test {};

// Normal operation: special-case two single-quotes -> "'"
TEST_F(EscapeTest_168, ReturnsSingleQuoteWhenTwoSingleQuotes_168) {
  StreamHolder_168 h("''Z");

  const std::string out = YAML::Exp::Escape(h.stream);
  EXPECT_EQ(out, std::string("'"));

  // Observable external effect: stream advanced by two chars
  EXPECT_EQ(h.stream.get(), 'Z');
}

// Normal operation: common escapes
TEST_F(EscapeTest_168, ReturnsNewlineForN_168) {
  StreamHolder_168 h("\\nX");

  const std::string out = YAML::Exp::Escape(h.stream);
  EXPECT_EQ(out, std::string(1, '\x0A'));
  EXPECT_EQ(h.stream.get(), 'X');
}

TEST_F(EscapeTest_168, ReturnsTabForT_168) {
  StreamHolder_168 h("\\tY");

  const std::string out = YAML::Exp::Escape(h.stream);
  EXPECT_EQ(out, std::string(1, '\x09'));
  EXPECT_EQ(h.stream.get(), 'Y');
}

TEST_F(EscapeTest_168, ReturnsTabForLiteralTabChar_168) {
  // Second character is an actual tab.
  StreamHolder_168 h(std::string("\\") + std::string(1, '\t') + "Q");

  const std::string out = YAML::Exp::Escape(h.stream);
  EXPECT_EQ(out, std::string(1, '\x09'));
  EXPECT_EQ(h.stream.get(), 'Q');
}

TEST_F(EscapeTest_168, ReturnsBackslashForBackslash_168) {
  StreamHolder_168 h("\\\\R");

  const std::string out = YAML::Exp::Escape(h.stream);
  EXPECT_EQ(out, std::string("\\"));
  EXPECT_EQ(h.stream.get(), 'R');
}

TEST_F(EscapeTest_168, ReturnsDoubleQuoteForQuote_168) {
  StreamHolder_168 h("\\\"A");

  const std::string out = YAML::Exp::Escape(h.stream);
  EXPECT_EQ(out, std::string("\""));
  EXPECT_EQ(h.stream.get(), 'A');
}

TEST_F(EscapeTest_168, ReturnsSlashForSlash_168) {
  StreamHolder_168 h("\\/B");

  const std::string out = YAML::Exp::Escape(h.stream);
  EXPECT_EQ(out, std::string("/"));
  EXPECT_EQ(h.stream.get(), 'B');
}

TEST_F(EscapeTest_168, ReturnsSpaceForSpace_168) {
  StreamHolder_168 h("\\ C");

  const std::string out = YAML::Exp::Escape(h.stream);
  EXPECT_EQ(out, std::string(" "));
  EXPECT_EQ(h.stream.get(), 'C');
}

// Boundary/behavioral edge: first character is ignored except for "''"
TEST_F(EscapeTest_168, EscapePrefixCharIsIgnoredExceptDoubleSingleQuote_168) {
  // First char is 'A' (not backslash); second char is 'n' -> should still map to newline.
  StreamHolder_168 h("AnZ");

  const std::string out = YAML::Exp::Escape(h.stream);
  EXPECT_EQ(out, std::string(1, '\x0A'));
  EXPECT_EQ(h.stream.get(), 'Z');
}

// Normal operation: less-common escapes with explicit bytes / UTF-8 sequences
TEST_F(EscapeTest_168, ReturnsNELForN_168) {
  StreamHolder_168 h("\\NZ");

  const std::string out = YAML::Exp::Escape(h.stream);
  EXPECT_EQ(out, ByteStr_168(0x85));
  EXPECT_EQ(h.stream.get(), 'Z');
}

TEST_F(EscapeTest_168, ReturnsNBSPForUnderscore_168) {
  StreamHolder_168 h("\\_Z");

  const std::string out = YAML::Exp::Escape(h.stream);
  EXPECT_EQ(out, ByteStr_168(0xA0));
  EXPECT_EQ(h.stream.get(), 'Z');
}

TEST_F(EscapeTest_168, ReturnsUnicodeLineSeparatorForL_168) {
  StreamHolder_168 h("\\LZ");

  const std::string out = YAML::Exp::Escape(h.stream);
  EXPECT_EQ(out, std::string("\xE2\x80\xA8"));
  EXPECT_EQ(h.stream.get(), 'Z');
}

TEST_F(EscapeTest_168, ReturnsUnicodeParagraphSeparatorForP_168) {
  StreamHolder_168 h("\\PZ");

  const std::string out = YAML::Exp::Escape(h.stream);
  EXPECT_EQ(out, std::string("\xE2\x80\xA9"));
  EXPECT_EQ(h.stream.get(), 'Z');
}

// Exceptional/error cases: unknown escape character
TEST_F(EscapeTest_168, ThrowsParserExceptionOnInvalidEscape_168) {
  StreamHolder_168 h("\\q");

  EXPECT_THROW((void)YAML::Exp::Escape(h.stream), YAML::ParserException);
}

TEST_F(EscapeTest_168, InvalidEscapeExceptionMessageContainsCharacter_168) {
  StreamHolder_168 h("\\q");

  try {
    (void)YAML::Exp::Escape(h.stream);
    FAIL() << "Expected YAML::ParserException";
  } catch (const YAML::ParserException& e) {
    const std::string msg = e.what();
    // Must at least include the library-provided prefix + the offending character.
    EXPECT_NE(msg.find(YAML::ErrorMsg::INVALID_ESCAPE), std::string::npos);
    EXPECT_NE(msg.find("q"), std::string::npos);
  }
}