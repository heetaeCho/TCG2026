// TEST_ID: 632
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/ostream_wrapper.h"
#include "yaml-cpp/emitterutils.h"  // Provides YAML::Utils::WriteChar (and StringEscaping)

namespace {

class WriteCharTest_632 : public ::testing::Test {
 protected:
  std::string WriteToString(char ch, YAML::StringEscaping::value style) {
    std::stringstream ss;
    YAML::ostream_wrapper out(ss);
    const bool ok = YAML::Utils::WriteChar(out, ch, style);
    EXPECT_TRUE(ok);
    return ss.str();
  }

  // For code paths that don't depend on escaping style, any value is fine.
  YAML::StringEscaping::value AnyStyle() const {
    return static_cast<YAML::StringEscaping::value>(0);
  }
};

TEST_F(WriteCharTest_632, WritesLowercaseLetterAsIs_632) {
  const std::string s = WriteToString('a', AnyStyle());
  EXPECT_EQ(s, "a");
}

TEST_F(WriteCharTest_632, WritesUppercaseLetterAsIs_632) {
  const std::string s = WriteToString('Z', AnyStyle());
  EXPECT_EQ(s, "Z");
}

TEST_F(WriteCharTest_632, WritesDoubleQuoteAsEscapedSequence_632) {
  const std::string s = WriteToString('\"', AnyStyle());
  EXPECT_EQ(s, "\\\"");
}

TEST_F(WriteCharTest_632, WritesBackslashAsEscapedSequence_632) {
  const std::string s = WriteToString('\\', AnyStyle());
  EXPECT_EQ(s, "\\\\");
}

TEST_F(WriteCharTest_632, WritesTabAsEscapedSequence_632) {
  const std::string s = WriteToString('\t', AnyStyle());
  EXPECT_EQ(s, "\\t");
}

TEST_F(WriteCharTest_632, WritesNewlineAsEscapedSequence_632) {
  const std::string s = WriteToString('\n', AnyStyle());
  EXPECT_EQ(s, "\\n");
}

TEST_F(WriteCharTest_632, WritesBackspaceAsEscapedSequence_632) {
  const std::string s = WriteToString('\b', AnyStyle());
  EXPECT_EQ(s, "\\b");
}

TEST_F(WriteCharTest_632, WritesCarriageReturnAsEscapedSequence_632) {
  const std::string s = WriteToString('\r', AnyStyle());
  EXPECT_EQ(s, "\\r");
}

TEST_F(WriteCharTest_632, WritesFormFeedAsEscapedSequence_632) {
  const std::string s = WriteToString('\f', AnyStyle());
  EXPECT_EQ(s, "\\f");
}

TEST_F(WriteCharTest_632, WritesPrintableNonLetterAsQuotedChar_632) {
  const std::string s = WriteToString('!', AnyStyle());
  EXPECT_EQ(s, "\"!\"");
}

TEST_F(WriteCharTest_632, WritesDigitAsQuotedChar_632) {
  const std::string s = WriteToString('0', AnyStyle());
  EXPECT_EQ(s, "\"0\"");
}

TEST_F(WriteCharTest_632, WritesSpaceAsQuotedChar_632) {
  const std::string s = WriteToString(' ', AnyStyle());
  EXPECT_EQ(s, "\" \"");
}

TEST_F(WriteCharTest_632, WritesBoundaryPrintableTildeAsQuotedChar_632) {
  const std::string s = WriteToString('~', AnyStyle());
  EXPECT_EQ(s, "\"~\"");
}

TEST_F(WriteCharTest_632, WritesNonAsciiOrNonPrintableWrappedInQuotes_632) {
  // 0x7F is outside the 0x20..0x7E printable range.
  const char ch = static_cast<char>(0x7F);

  const std::string s = WriteToString(ch, AnyStyle());

  // Observable behavior via interface: it must write *something* and wrap it in quotes.
  ASSERT_GE(s.size(), 2u);
  EXPECT_EQ(s.front(), '"');
  EXPECT_EQ(s.back(), '"');

  // The escaped content should not be empty for a non-printable input.
  EXPECT_GT(s.size(), 2u);
}

}  // namespace