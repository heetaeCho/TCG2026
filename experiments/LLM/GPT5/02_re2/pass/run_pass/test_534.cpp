// File: convert_latin1_to_utf8_test.cc

#include <gtest/gtest.h>
#include <string>
#include "absl/strings/string_view.h"

// Forward declaration of the interface under test.
namespace re2 {
void ConvertLatin1ToUTF8(absl::string_view latin1, std::string* utf);
}  // namespace re2

namespace {

class ConvertLatin1ToUTF8Test_534 : public ::testing::Test {
 protected:
  std::string out_;
};

// Empty input should produce empty output and clear any existing content.
TEST_F(ConvertLatin1ToUTF8Test_534, EmptyInputClearsOutput_534) {
  out_ = "preexisting";
  re2::ConvertLatin1ToUTF8(absl::string_view{}, &out_);
  EXPECT_TRUE(out_.empty());
}

// Pure ASCII should be unchanged (1:1 bytes in UTF-8).
TEST_F(ConvertLatin1ToUTF8Test_534, AsciiPreserved_534) {
  const std::string in = "Hello, ASCII!";
  re2::ConvertLatin1ToUTF8(in, &out_);
  EXPECT_EQ(out_, in);
}

// Boundary bytes: 0x7F remains single byte; 0x80 becomes two-byte UTF-8 (C2 80).
TEST_F(ConvertLatin1ToUTF8Test_534, BoundaryBytes_7F_and_80_534) {
  const std::string in("\x7F\x80", 2);
  re2::ConvertLatin1ToUTF8(in, &out_);

  std::string expected;
  expected.push_back('\x7F');       // U+007F -> 0x7F
  expected.push_back('\xC2');       // U+0080 -> 0xC2 0x80
  expected.push_back('\x80');

  ASSERT_EQ(out_.size(), expected.size());
  EXPECT_EQ(out_, expected);
}

// Extended Latin-1 bytes should map to corresponding two-byte UTF-8 sequences.
// 0xA3 (U+00A3 '£') -> C2 A3
// 0xC7 (U+00C7 'Ç') -> C3 87
// 0xFF (U+00FF 'ÿ') -> C3 BF
TEST_F(ConvertLatin1ToUTF8Test_534, ExtendedLatin1Examples_534) {
  const std::string in("\xA3\xC7\xFF", 3);
  re2::ConvertLatin1ToUTF8(in, &out_);

  std::string expected;
  expected.append("\xC2\xA3", 2);
  expected.append("\xC3\x87", 2);
  expected.append("\xC3\xBF", 2);

  ASSERT_EQ(out_.size(), expected.size());
  EXPECT_EQ(out_, expected);
}

// Embedded NUL should be preserved; output length must account for NUL byte.
TEST_F(ConvertLatin1ToUTF8Test_534, EmbeddedNullByte_534) {
  const std::string in(std::string("\x00A", 2));  // {0x00, 'A'}
  re2::ConvertLatin1ToUTF8(in, &out_);

  std::string expected("\x00A", 2);  // U+0000 -> 0x00; 'A' -> 0x41
  ASSERT_EQ(out_.size(), expected.size());
  EXPECT_EQ(out_, expected);
}

// Mixed ASCII + extended bytes; verifies correct sequence and that output was cleared first.
TEST_F(ConvertLatin1ToUTF8Test_534, MixedAsciiAndExtended_AndClearsFirst_534) {
  out_ = "junk_should_be_cleared";
  const std::string in("A\xA3\xC7\xFFZ", 5);  // 'A', £, Ç, ÿ, 'Z'
  re2::ConvertLatin1ToUTF8(in, &out_);

  std::string expected;
  expected.push_back('A');                 // 0x41
  expected.append("\xC2\xA3", 2);          // £
  expected.append("\xC3\x87", 2);          // Ç
  expected.append("\xC3\xBF", 2);          // ÿ
  expected.push_back('Z');                 // 0x5A

  ASSERT_EQ(out_.size(), expected.size());
  EXPECT_EQ(out_, expected);
}

// Large input sanity: many copies of a multibyte Latin-1 char should produce
// twice the number of bytes (since each becomes 2-byte UTF-8).
TEST_F(ConvertLatin1ToUTF8Test_534, LargeInput_RepeatedMultibyteChar_534) {
  const size_t n = 1000;
  std::string in(n, '\xFF');  // 0xFF (ÿ)
  re2::ConvertLatin1ToUTF8(in, &out_);

  // Expect n copies of C3 BF.
  std::string expected;
  expected.reserve(n * 2);
  for (size_t i = 0; i < n; ++i) {
    expected.push_back('\xC3');
    expected.push_back('\xBF');
  }

  ASSERT_EQ(out_.size(), expected.size());
  EXPECT_EQ(out_, expected);
}

}  // namespace
