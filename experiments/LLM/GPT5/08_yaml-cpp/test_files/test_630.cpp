// File: ./TestProjects/yaml-cpp/test/emitterutils_write_double_quoted_string_test_630.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstring>
#include <string>

#include "yaml-cpp/ostream_wrapper.h"
#include "yaml-cpp/emitterutils.h"  // Expected to declare YAML::Utils::WriteDoubleQuotedString and YAML::StringEscaping

namespace {

std::string WriteDQString_630(const char* str, std::size_t size,
                             YAML::StringEscaping::value escaping) {
  YAML::ostream_wrapper out;
  const bool ok = YAML::Utils::WriteDoubleQuotedString(out, str, size, escaping);
  EXPECT_TRUE(ok);
  // ostream_wrapper::str() is expected to return a null-terminated buffer.
  return std::string(out.str());
}

std::string WriteDQString_630(const std::string& s, YAML::StringEscaping::value escaping) {
  return WriteDQString_630(s.data(), s.size(), escaping);
}

}  // namespace

class WriteDoubleQuotedStringTest_630 : public ::testing::Test {};

TEST_F(WriteDoubleQuotedStringTest_630, EmptyStringProducesTwoQuotes_630) {
  const std::string out = WriteDQString_630("", YAML::StringEscaping::None);
  EXPECT_EQ(out, "\"\"");
}

TEST_F(WriteDoubleQuotedStringTest_630, NullPointerWithZeroSizeDoesNotCrashAndProducesTwoQuotes_630) {
  // Boundary/robustness: should not need to dereference str when size == 0.
  const std::string out = WriteDQString_630(nullptr, 0, YAML::StringEscaping::None);
  EXPECT_EQ(out, "\"\"");
}

TEST_F(WriteDoubleQuotedStringTest_630, PlainAsciiIsWrappedInDoubleQuotes_630) {
  const std::string out = WriteDQString_630("abcXYZ123", YAML::StringEscaping::None);
  EXPECT_EQ(out, "\"abcXYZ123\"");
}

TEST_F(WriteDoubleQuotedStringTest_630, RespectsExplicitSizeAndDoesNotReadPastIt_630) {
  // Even though the buffer contains more data, size limits what is written.
  const char buf[] = "abcdef";
  const std::string out = WriteDQString_630(buf, 3, YAML::StringEscaping::None);
  EXPECT_EQ(out, "\"abc\"");
}

TEST_F(WriteDoubleQuotedStringTest_630, EscapesDoubleQuoteCharacter_630) {
  const std::string out = WriteDQString_630("a\"b", YAML::StringEscaping::None);
  EXPECT_EQ(out, "\"a\\\"b\"");
}

TEST_F(WriteDoubleQuotedStringTest_630, EscapesBackslashCharacter_630) {
  const std::string out = WriteDQString_630("a\\b", YAML::StringEscaping::None);
  EXPECT_EQ(out, "\"a\\\\b\"");
}

TEST_F(WriteDoubleQuotedStringTest_630, EscapesCommonControlSequencesNewlineTabCarriageReturn_630) {
  const std::string input = std::string("A") + '\n' + "B" + '\t' + "C" + '\r' + "D";
  const std::string out = WriteDQString_630(input, YAML::StringEscaping::None);
  EXPECT_EQ(out, "\"A\\nB\\tC\\rD\"");
}

TEST_F(WriteDoubleQuotedStringTest_630, EscapesBackspaceAndFormFeed_630) {
  const std::string input = std::string("X") + '\b' + "Y" + '\f' + "Z";
  const std::string out = WriteDQString_630(input, YAML::StringEscaping::None);
  EXPECT_EQ(out, "\"X\\bY\\fZ\"");
}

TEST_F(WriteDoubleQuotedStringTest_630, AlwaysStartsAndEndsWithDoubleQuote_630) {
  const std::string out = WriteDQString_630("hello", YAML::StringEscaping::None);
  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.front(), '"');
  EXPECT_EQ(out.back(), '"');
}