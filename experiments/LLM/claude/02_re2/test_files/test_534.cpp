#include <string>
#include "gtest/gtest.h"
#include "absl/strings/string_view.h"

namespace re2 {
void ConvertLatin1ToUTF8(absl::string_view latin1, std::string* utf);
}

class ConvertLatin1ToUTF8Test_534 : public ::testing::Test {
 protected:
  std::string utf_;
};

TEST_F(ConvertLatin1ToUTF8Test_534, EmptyInput_534) {
  re2::ConvertLatin1ToUTF8("", &utf_);
  EXPECT_EQ("", utf_);
}

TEST_F(ConvertLatin1ToUTF8Test_534, PureAsciiInput_534) {
  re2::ConvertLatin1ToUTF8("Hello, World!", &utf_);
  EXPECT_EQ("Hello, World!", utf_);
}

TEST_F(ConvertLatin1ToUTF8Test_534, SingleAsciiCharacter_534) {
  re2::ConvertLatin1ToUTF8("A", &utf_);
  EXPECT_EQ("A", utf_);
}

TEST_F(ConvertLatin1ToUTF8Test_534, NullCharacterInInput_534) {
  // A string_view containing a NUL byte
  std::string input(1, '\0');
  re2::ConvertLatin1ToUTF8(absl::string_view(input.data(), input.size()), &utf_);
  // NUL character (0x00) in UTF-8 is also a single NUL byte
  EXPECT_EQ(std::string(1, '\0'), utf_);
  EXPECT_EQ(1u, utf_.size());
}

TEST_F(ConvertLatin1ToUTF8Test_534, AsciiMaxBoundary_534) {
  // Character 0x7F is the highest single-byte UTF-8 value
  std::string input(1, '\x7F');
  re2::ConvertLatin1ToUTF8(input, &utf_);
  EXPECT_EQ(std::string(1, '\x7F'), utf_);
  EXPECT_EQ(1u, utf_.size());
}

TEST_F(ConvertLatin1ToUTF8Test_534, Latin1Char0x80_534) {
  // 0x80 is the first character that needs 2-byte UTF-8 encoding
  // U+0080 in UTF-8 is 0xC2 0x80
  std::string input(1, '\x80');
  re2::ConvertLatin1ToUTF8(input, &utf_);
  EXPECT_EQ(std::string("\xC2\x80"), utf_);
  EXPECT_EQ(2u, utf_.size());
}

TEST_F(ConvertLatin1ToUTF8Test_534, Latin1Char0xFF_534) {
  // 0xFF (ÿ) -> U+00FF -> UTF-8: 0xC3 0xBF
  std::string input(1, '\xFF');
  re2::ConvertLatin1ToUTF8(input, &utf_);
  EXPECT_EQ(std::string("\xC3\xBF"), utf_);
  EXPECT_EQ(2u, utf_.size());
}

TEST_F(ConvertLatin1ToUTF8Test_534, Latin1Char0xA9_Copyright_534) {
  // 0xA9 (©) -> U+00A9 -> UTF-8: 0xC2 0xA9
  std::string input(1, '\xA9');
  re2::ConvertLatin1ToUTF8(input, &utf_);
  EXPECT_EQ(std::string("\xC2\xA9"), utf_);
}

TEST_F(ConvertLatin1ToUTF8Test_534, Latin1Char0xE9_Eacute_534) {
  // 0xE9 (é) -> U+00E9 -> UTF-8: 0xC3 0xA9
  std::string input(1, '\xE9');
  re2::ConvertLatin1ToUTF8(input, &utf_);
  EXPECT_EQ(std::string("\xC3\xA9"), utf_);
}

TEST_F(ConvertLatin1ToUTF8Test_534, MixedAsciiAndLatin1_534) {
  // "café" with é = 0xE9
  std::string input = "caf";
  input += '\xE9';
  re2::ConvertLatin1ToUTF8(input, &utf_);
  EXPECT_EQ(std::string("caf\xC3\xA9"), utf_);
}

TEST_F(ConvertLatin1ToUTF8Test_534, AllHighBytesProduceTwoByteUTF8_534) {
  // Every byte from 0x80 to 0xFF should produce exactly 2 UTF-8 bytes
  for (int c = 0x80; c <= 0xFF; c++) {
    std::string input(1, static_cast<char>(c));
    std::string result;
    re2::ConvertLatin1ToUTF8(input, &result);
    EXPECT_EQ(2u, result.size()) << "Failed for byte 0x" << std::hex << c;
  }
}

TEST_F(ConvertLatin1ToUTF8Test_534, AllLowBytesProduceSingleByteUTF8_534) {
  // Every byte from 0x01 to 0x7F should produce exactly 1 UTF-8 byte
  for (int c = 0x01; c <= 0x7F; c++) {
    std::string input(1, static_cast<char>(c));
    std::string result;
    re2::ConvertLatin1ToUTF8(input, &result);
    EXPECT_EQ(1u, result.size()) << "Failed for byte 0x" << std::hex << c;
    EXPECT_EQ(input, result) << "Failed for byte 0x" << std::hex << c;
  }
}

TEST_F(ConvertLatin1ToUTF8Test_534, OutputIsClearedBeforeConversion_534) {
  utf_ = "pre-existing content";
  re2::ConvertLatin1ToUTF8("abc", &utf_);
  EXPECT_EQ("abc", utf_);
}

TEST_F(ConvertLatin1ToUTF8Test_534, MultipleHighBytesSequence_534) {
  // 0xFC 0xFD 0xFE 0xFF: each produces 2-byte UTF-8
  std::string input;
  input += '\xFC';  // U+00FC -> 0xC3 0xBC (ü)
  input += '\xFD';  // U+00FD -> 0xC3 0xBD (ý)
  input += '\xFE';  // U+00FE -> 0xC3 0xBE (þ)
  input += '\xFF';  // U+00FF -> 0xC3 0xBF (ÿ)
  re2::ConvertLatin1ToUTF8(input, &utf_);
  EXPECT_EQ(std::string("\xC3\xBC\xC3\xBD\xC3\xBE\xC3\xBF"), utf_);
  EXPECT_EQ(8u, utf_.size());
}

TEST_F(ConvertLatin1ToUTF8Test_534, LongAsciiString_534) {
  std::string input(1000, 'x');
  re2::ConvertLatin1ToUTF8(input, &utf_);
  EXPECT_EQ(input, utf_);
  EXPECT_EQ(1000u, utf_.size());
}

TEST_F(ConvertLatin1ToUTF8Test_534, LongLatin1String_534) {
  std::string input(1000, '\xE9');
  re2::ConvertLatin1ToUTF8(input, &utf_);
  EXPECT_EQ(2000u, utf_.size());
}

TEST_F(ConvertLatin1ToUTF8Test_534, Latin1Char0xC0_Agrave_534) {
  // 0xC0 (À) -> U+00C0 -> UTF-8: 0xC3 0x80
  std::string input(1, '\xC0');
  re2::ConvertLatin1ToUTF8(input, &utf_);
  EXPECT_EQ(std::string("\xC3\x80"), utf_);
}

TEST_F(ConvertLatin1ToUTF8Test_534, Latin1Char0xBF_InvertedQuestionMark_534) {
  // 0xBF (¿) -> U+00BF -> UTF-8: 0xC2 0xBF
  std::string input(1, '\xBF');
  re2::ConvertLatin1ToUTF8(input, &utf_);
  EXPECT_EQ(std::string("\xC2\xBF"), utf_);
}

TEST_F(ConvertLatin1ToUTF8Test_534, CalledTwiceOutputReset_534) {
  re2::ConvertLatin1ToUTF8("first", &utf_);
  EXPECT_EQ("first", utf_);
  re2::ConvertLatin1ToUTF8("second", &utf_);
  EXPECT_EQ("second", utf_);
}
