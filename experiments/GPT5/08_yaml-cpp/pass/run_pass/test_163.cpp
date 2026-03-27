// File: ./TestProjects/yaml-cpp/test/scantaghandle_test_163.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "exp.h"                 // YAML::Exp::Word(), YAML::Exp::Tag(), YAML::Keys::Tag
#include "stream.h"              // YAML::Stream
#include "yaml-cpp/exceptions.h" // YAML::ParserException
#include "yaml-cpp/mark.h"       // YAML::Mark (for completeness)

#include "scantag.h" // If your project has a header for ScanTagHandle, include it instead.
// If not, include the cpp directly as a last resort:
// #include "../src/scantag.cpp"

namespace {

class ScanTagHandleTest_163 : public ::testing::Test {
 protected:
  // Finds a character that is NOT a "word" char but IS a "tag" char (per YAML::Exp),
  // excluding '!' to avoid early termination logic.
  static char FindTagOnlyChar() {
    for (int c = 33; c <= 126; ++c) {
      const char ch = static_cast<char>(c);
      if (ch == YAML::Keys::Tag) continue;
      if (!YAML::Exp::Word().Matches(ch) && YAML::Exp::Tag().Matches(ch)) {
        return ch;
      }
    }
    return '\0';
  }

  // Finds a character that matches neither Word nor Tag (a "stop" character),
  // excluding '!' to avoid early termination logic.
  static char FindStopChar() {
    for (int c = 0; c <= 127; ++c) {
      const char ch = static_cast<char>(c);
      if (ch == YAML::Keys::Tag) continue;
      if (!YAML::Exp::Word().Matches(ch) && !YAML::Exp::Tag().Matches(ch)) {
        return ch;
      }
    }
    return '\0';
  }

  static YAML::Stream MakeStream(const std::string& s) {
    // Stream takes a std::istream&, so keep the streambuf alive by owning the stringstream.
    // We return a Stream by value is not allowed (deleted move/copy), so construct in-place
    // in each test instead.
    (void)s;
    std::abort();
  }
};

TEST_F(ScanTagHandleTest_163, EmptyInput_ReturnsEmptyAndCanBeHandleTrue_163) {
  std::istringstream input("");
  YAML::Stream in(input);

  bool canBeHandle = false;
  const std::string tag = YAML::ScanTagHandle(in, canBeHandle);

  EXPECT_EQ(tag, "");
  EXPECT_TRUE(canBeHandle);
}

TEST_F(ScanTagHandleTest_163, ImmediateBang_ReturnsEmptyDoesNotConsumeBang_163) {
  std::istringstream input(std::string(1, YAML::Keys::Tag) + "rest");
  YAML::Stream in(input);

  bool canBeHandle = false;
  const std::string tag = YAML::ScanTagHandle(in, canBeHandle);

  EXPECT_EQ(tag, "");
  EXPECT_TRUE(canBeHandle);
  EXPECT_EQ(in.peek(), YAML::Keys::Tag);  // '!' should remain unconsumed
}

TEST_F(ScanTagHandleTest_163, WordThenBang_ReturnsWordAndDoesNotConsumeBang_163) {
  std::istringstream input("abc!rest");
  YAML::Stream in(input);

  bool canBeHandle = false;
  const std::string tag = YAML::ScanTagHandle(in, canBeHandle);

  EXPECT_EQ(tag, "abc");
  EXPECT_TRUE(canBeHandle);
  EXPECT_EQ(in.peek(), YAML::Keys::Tag);  // '!' should remain unconsumed
}

TEST_F(ScanTagHandleTest_163, StopsOnNonWordAndNonTag_MarksCanBeHandleFalseAndDoesNotConsumeStopChar_163) {
  const char stop = FindStopChar();
  ASSERT_NE(stop, '\0') << "Could not find a stop character (neither Word nor Tag).";

  std::string text = "abc";
  text.push_back(stop);
  text += "tail";

  std::istringstream input(text);
  YAML::Stream in(input);

  bool canBeHandle = true; // initial value should be overwritten by ScanTagHandle
  const std::string tag = YAML::ScanTagHandle(in, canBeHandle);

  // We expect it to collect the initial word part and then stop before consuming 'stop'.
  EXPECT_EQ(tag, "abc");
  EXPECT_FALSE(canBeHandle);
  EXPECT_EQ(in.peek(), stop);
}

TEST_F(ScanTagHandleTest_163, LeadingTagOnlyChar_CollectsItAndCanBeHandleFalse_163) {
  const char tagOnly = FindTagOnlyChar();
  const char stop = FindStopChar();
  ASSERT_NE(tagOnly, '\0') << "Could not find a Tag-only character (Tag && !Word).";
  ASSERT_NE(stop, '\0') << "Could not find a stop character (neither Word nor Tag).";

  std::string text;
  text.push_back(tagOnly);
  text.push_back(stop);

  std::istringstream input(text);
  YAML::Stream in(input);

  bool canBeHandle = true;
  const std::string tag = YAML::ScanTagHandle(in, canBeHandle);

  EXPECT_EQ(tag, std::string(1, tagOnly));
  EXPECT_FALSE(canBeHandle);
  EXPECT_EQ(in.peek(), stop);  // stop char should remain unconsumed
}

TEST_F(ScanTagHandleTest_163, TagOnlyThenBang_ThrowsParserException_163) {
  const char tagOnly = FindTagOnlyChar();
  ASSERT_NE(tagOnly, '\0') << "Could not find a Tag-only character (Tag && !Word).";

  std::string text;
  text.push_back(tagOnly);
  text.push_back(YAML::Keys::Tag);  // '!' triggers error when canBeHandle is false

  std::istringstream input(text);
  YAML::Stream in(input);

  bool canBeHandle = true;
  EXPECT_THROW(
      {
        (void)YAML::ScanTagHandle(in, canBeHandle);
      },
      YAML::ParserException);
}

}  // namespace