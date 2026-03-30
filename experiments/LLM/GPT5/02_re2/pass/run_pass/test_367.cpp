// File: convert_runes_to_bytes_test.cc
#include <gtest/gtest.h>
#include <string>
#include <vector>

// Forward declarations only; do not include or rely on internals.
namespace re2 {
  using Rune = int;  // RE2 commonly defines Rune as int; used only for test inputs.
  void ConvertRunesToBytes(bool latin1, Rune* runes, int nrunes, std::string* bytes);
}

class ConvertRunesToBytesTest_367 : public ::testing::Test {
protected:
  static std::string MakeLatin1String(const std::vector<int>& vals) {
    std::string s;
    s.reserve(vals.size());
    for (int v : vals) s.push_back(static_cast<char>(v));
    return s;
  }
};

// --- Latin-1 branch ---

TEST_F(ConvertRunesToBytesTest_367, Latin1_BasicCopy_367) {
  // Arrange: values within 0..255 should be copied as single bytes.
  std::vector<re2::Rune> runes = {0x00, 0x41, 0x7F, 0x80, 0xE9, 0xFF};
  std::string out;

  // Act
  re2::ConvertRunesToBytes(/*latin1=*/true, runes.data(),
                           static_cast<int>(runes.size()), &out);

  // Assert
  ASSERT_EQ(out.size(), runes.size());
  EXPECT_EQ(out, ConvertRunesToBytesTest_367::MakeLatin1String(
                     {0x00, 0x41, 0x7F, 0x80, 0xE9, 0xFF}));
}

TEST_F(ConvertRunesToBytesTest_367, Latin1_AllowsNullPointerWhenCountZero_367) {
  // Arrange
  std::string out = "pre-populated";

  // Act: With nrunes == 0, the function should produce an empty string.
  re2::ConvertRunesToBytes(/*latin1=*/true, /*runes=*/nullptr, /*nrunes=*/0, &out);

  // Assert
  EXPECT_TRUE(out.empty());
}

// --- UTF-8 branch (latin1 == false) ---

TEST_F(ConvertRunesToBytesTest_367, Utf8_AsciiOnly_367) {
  // Arrange: ASCII runes should map to identical single-byte UTF-8.
  std::vector<re2::Rune> runes = {'H', 'i', '!', 0};  // includes NUL
  std::string out;

  // Act
  re2::ConvertRunesToBytes(/*latin1=*/false, runes.data(),
                           static_cast<int>(runes.size()), &out);

  // Assert: Expect exact byte-for-byte match.
  std::string expected;
  expected.push_back('H');
  expected.push_back('i');
  expected.push_back('!');
  expected.push_back('\0');
  ASSERT_EQ(out.size(), expected.size());
  EXPECT_EQ(out, expected);
}

TEST_F(ConvertRunesToBytesTest_367, Utf8_MixedCodepoints_367) {
  // Arrange: mix of 1-, 2-, 3-, and 4-byte UTF-8 sequences.
  // 'A' (U+0041), 'é' (U+00E9), '€' (U+20AC), '😀' (U+1F600)
  std::vector<re2::Rune> runes = {0x0041, 0x00E9, 0x20AC, 0x1F600};
  std::string out;

  // Act
  re2::ConvertRunesToBytes(/*latin1=*/false, runes.data(),
                           static_cast<int>(runes.size()), &out);

  // Assert: expected UTF-8 bytes.
  const std::string expected =
      std::string("A") +               // 0x41
      "\xC3\xA9" +                     // é
      "\xE2\x82\xAC" +                 // €
      "\xF0\x9F\x98\x80";              // 😀
  EXPECT_EQ(out, expected);
}

TEST_F(ConvertRunesToBytesTest_367, Utf8_ZeroRunesProducesEmptyString_367) {
  // Arrange
  std::string out = "should be cleared";

  // Act
  re2::ConvertRunesToBytes(/*latin1=*/false, /*runes=*/nullptr, /*nrunes=*/0, &out);

  // Assert
  EXPECT_TRUE(out.empty());
}

TEST_F(ConvertRunesToBytesTest_367, Utf8_InvalidRuneIsHandledGracefully_367) {
  // Arrange: Use a surrogate code point (D800) which is invalid for UTF-8.
  // RE2 encoding helpers typically replace invalid runes with U+FFFD (�).
  std::vector<re2::Rune> runes = {0x0041, 0xD800, 0x0042};
  std::string out;

  // Act
  re2::ConvertRunesToBytes(/*latin1=*/false, runes.data(),
                           static_cast<int>(runes.size()), &out);

  // Assert: Expect "A" + U+FFFD + "B" => "A\xEF\xBF\xBDB".
  // We don't assert *how* the replacement happens internally—only the observable result.
  const std::string expected = std::string("A") + "\xEF\xBF\xBD" + "B";
  EXPECT_EQ(out, expected);
}
