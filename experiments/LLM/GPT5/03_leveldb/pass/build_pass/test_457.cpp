// File: logging_append_escaped_string_to_test.cc

#include <gtest/gtest.h>
#include <string>

// If your project exposes a header like "util/logging.h", prefer including it.
// Forward-declare here to keep tests based strictly on the provided interface.
namespace leveldb {
  class Slice;
  void AppendEscapedStringTo(std::string* str, const Slice& value);
}

// Minimal include for Slice interface as provided.
#include "leveldb/slice.h"

using leveldb::Slice;
using leveldb::AppendEscapedStringTo;

class AppendEscapedStringToTest_457 : public ::testing::Test {
protected:
  std::string out_;
};

// Printable ASCII (including space ' ' and '~') should pass through unchanged.
TEST_F(AppendEscapedStringToTest_457, PassThroughPrintable_457) {
  const std::string input = "Hello ~ World!";
  AppendEscapedStringTo(&out_, Slice(input));
  EXPECT_EQ(out_, input);
}

// Non-printable bytes (e.g., NUL and TAB) should be hex-escaped as \xNN (lowercase hex).
TEST_F(AppendEscapedStringToTest_457, EscapeNullAndTab_457) {
  const char raw[] = {'A', '\0', 'B', '\t', 'C'};
  const std::string input(raw, sizeof(raw));
  AppendEscapedStringTo(&out_, Slice(input));
  // Expect: 'A' + \x00 + 'B' + \x09 + 'C'
  EXPECT_EQ(out_, std::string("A\\x00B\\x09C"));
}

// Boundary conditions around the printable range:
// 0x1F (ESCAPE), 0x20 (space), 0x7E ('~'), 0x7F (DEL).
TEST_F(AppendEscapedStringToTest_457, EscapeBoundaryChars_457) {
  const char raw[] = {static_cast<char>(0x1F), static_cast<char>(0x20),
                      static_cast<char>(0x7E), static_cast<char>(0x7F)};
  const std::string input(raw, sizeof(raw));
  AppendEscapedStringTo(&out_, Slice(input));
  EXPECT_EQ(out_, std::string("\\x1f ~\\x7f"));
}

// Bytes with high bit set should be treated as unsigned and escaped with 0xff mask.
TEST_F(AppendEscapedStringToTest_457, HighBitBytesEscaped_457) {
  const char raw[] = {static_cast<char>(0x80), static_cast<char>(0xFF),
                      static_cast<char>(0x90)};
  const std::string input(raw, sizeof(raw));
  AppendEscapedStringTo(&out_, Slice(input));
  EXPECT_EQ(out_, std::string("\\x80\\xff\\x90"));
}

// Function should append to an existing string, not overwrite it.
TEST_F(AppendEscapedStringToTest_457, AppendToExistingString_457) {
  out_ = "prefix:";
  const char raw[] = {'A', '\n', 'B'};
  const std::string input(raw, sizeof(raw));
  AppendEscapedStringTo(&out_, Slice(input));
  EXPECT_EQ(out_, std::string("prefix:A\\x0aB"));
}

// Empty slice should not modify the destination string.
TEST_F(AppendEscapedStringToTest_457, EmptySliceNoOp_457) {
  out_ = "keep";
  Slice empty;  // default-constructed Slice per provided interface
  AppendEscapedStringTo(&out_, empty);
  EXPECT_EQ(out_, "keep");
}

// Mixed printable and non-printable content.
TEST_F(AppendEscapedStringToTest_457, MixedContent_457) {
  const char raw[] = {'a','b','c', static_cast<char>(0x01), static_cast<char>(0x02),
                      'X','Y','Z'};
  const std::string input(raw, sizeof(raw));
  AppendEscapedStringTo(&out_, Slice(input));
  EXPECT_EQ(out_, std::string("abc\\x01\\x02XYZ"));
}

// Multiple calls should continue appending correctly and preserve hex format.
TEST_F(AppendEscapedStringToTest_457, RepeatedCallsAccumulate_457) {
  const char first[]  = {'\0', 'A'};       // -> \x00A
  const char second[] = {'B', static_cast<char>(0x7F)}; // -> B\x7f
  AppendEscapedStringTo(&out_, Slice(std::string(first,  sizeof(first))));
  AppendEscapedStringTo(&out_, Slice(std::string(second, sizeof(second))));
  EXPECT_EQ(out_, std::string("\\x00AB\\x7f"));
}
