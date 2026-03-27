// =================================================================================================
// TEST_ID: 2055
// Unit tests for: ToUTF16Native (./TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

// Prefer the real SDK header if available in the build.
// (If the project already includes the declaration/types elsewhere, this include will work.)
#if __has_include("UnicodeConversions.hpp")
  #include "UnicodeConversions.hpp"
#elif __has_include("UnicodeConversions.h")
  #include "UnicodeConversions.h"
#else
  // Fallback: minimal type aliases + function declaration to compile the tests in isolation.
  // These aliases match the common XMP SDK definitions (UTF8Unit as byte, UTF16Unit as 16-bit unit).
  using UTF8Unit  = unsigned char;
  using UTF16Unit = std::uint16_t;
  extern void ToUTF16Native(const UTF8Unit* utf8In, size_t utf8Len, std::string* utf16Str);
#endif

namespace {

class UnicodeConversionsTest_2055 : public ::testing::Test {
protected:
  static bool DetectLittleEndianFromFirstASCII(const std::string& utf16Bytes, unsigned char ascii) {
    // For ASCII X, UTF-16 code unit is 0x00XX. Bytes are:
    //   LE: XX 00
    //   BE: 00 XX
    // If it doesn't match either pattern, default to LE (but tests using ASCII should match).
    if (utf16Bytes.size() < 2) return true;
    const unsigned char b0 = static_cast<unsigned char>(utf16Bytes[0]);
    const unsigned char b1 = static_cast<unsigned char>(utf16Bytes[1]);
    if (b0 == ascii && b1 == 0x00) return true;
    if (b0 == 0x00 && b1 == ascii) return false;
    return true;
  }

  static std::vector<std::uint16_t> DecodeNativeUTF16BytesToUnits(const std::string& utf16Bytes,
                                                                  bool littleEndian) {
    EXPECT_EQ(utf16Bytes.size() % 2u, 0u) << "UTF-16 byte string must have even length";
    std::vector<std::uint16_t> units;
    units.reserve(utf16Bytes.size() / 2);

    for (size_t i = 0; i + 1 < utf16Bytes.size(); i += 2) {
      const unsigned char b0 = static_cast<unsigned char>(utf16Bytes[i]);
      const unsigned char b1 = static_cast<unsigned char>(utf16Bytes[i + 1]);
      std::uint16_t u = 0;
      if (littleEndian) {
        u = static_cast<std::uint16_t>(static_cast<std::uint16_t>(b0) |
                                       (static_cast<std::uint16_t>(b1) << 8));
      } else {
        u = static_cast<std::uint16_t>(static_cast<std::uint16_t>(b1) |
                                       (static_cast<std::uint16_t>(b0) << 8));
      }
      units.push_back(u);
    }
    return units;
  }

  static std::string MakeUtf8(const std::vector<unsigned char>& bytes) {
    return std::string(reinterpret_cast<const char*>(bytes.data()), bytes.size());
  }
};

// ------------------------------- Normal operation -------------------------------

TEST_F(UnicodeConversionsTest_2055, EmptyInputClearsOutput_2055) {
  std::string out = "preexisting";
  const UTF8Unit* in = reinterpret_cast<const UTF8Unit*>("");
  EXPECT_NO_THROW(ToUTF16Native(in, 0, &out));
  EXPECT_TRUE(out.empty());
}

TEST_F(UnicodeConversionsTest_2055, AsciiConvertsToUtf16Units_2055) {
  const char* ascii = "ABC";
  const auto* in = reinterpret_cast<const UTF8Unit*>(ascii);
  std::string out;

  ASSERT_NO_THROW(ToUTF16Native(in, std::strlen(ascii), &out));
  ASSERT_EQ(out.size(), 3u * 2u);

  const bool little = DetectLittleEndianFromFirstASCII(out, static_cast<unsigned char>('A'));
  const auto units = DecodeNativeUTF16BytesToUnits(out, little);

  ASSERT_EQ(units.size(), 3u);
  EXPECT_EQ(units[0], 0x0041);
  EXPECT_EQ(units[1], 0x0042);
  EXPECT_EQ(units[2], 0x0043);
}

TEST_F(UnicodeConversionsTest_2055, HandlesEmbeddedNullByteWithExplicitLength_2055) {
  // UTF-8 bytes: 'A' 0x00 'B'
  const std::vector<unsigned char> bytes = {0x41, 0x00, 0x42};
  const std::string utf8 = MakeUtf8(bytes);

  const auto* in = reinterpret_cast<const UTF8Unit*>(utf8.data());
  std::string out;

  ASSERT_NO_THROW(ToUTF16Native(in, utf8.size(), &out));
  ASSERT_EQ(out.size(), 3u * 2u);

  const bool little = DetectLittleEndianFromFirstASCII(out, static_cast<unsigned char>('A'));
  const auto units = DecodeNativeUTF16BytesToUnits(out, little);

  ASSERT_EQ(units.size(), 3u);
  EXPECT_EQ(units[0], 0x0041);
  EXPECT_EQ(units[1], 0x0000);
  EXPECT_EQ(units[2], 0x0042);
}

TEST_F(UnicodeConversionsTest_2055, ConvertsBmpMultibyteCharacter_2055) {
  // "café" in UTF-8: 63 61 66 C3 A9
  const std::vector<unsigned char> bytes = {0x63, 0x61, 0x66, 0xC3, 0xA9};
  const std::string utf8 = MakeUtf8(bytes);

  const auto* in = reinterpret_cast<const UTF8Unit*>(utf8.data());
  std::string out;

  ASSERT_NO_THROW(ToUTF16Native(in, utf8.size(), &out));
  ASSERT_EQ(out.size(), 4u * 2u);

  const bool little = DetectLittleEndianFromFirstASCII(out, static_cast<unsigned char>('c'));
  const auto units = DecodeNativeUTF16BytesToUnits(out, little);

  ASSERT_EQ(units.size(), 4u);
  EXPECT_EQ(units[0], 0x0063); // c
  EXPECT_EQ(units[1], 0x0061); // a
  EXPECT_EQ(units[2], 0x0066); // f
  EXPECT_EQ(units[3], 0x00E9); // é
}

TEST_F(UnicodeConversionsTest_2055, ConvertsNonBmpCharacterAsSurrogatePair_2055) {
  // U+1F600 GRINNING FACE 😀 in UTF-8: F0 9F 98 80
  const std::vector<unsigned char> bytes = {0xF0, 0x9F, 0x98, 0x80};
  const std::string utf8 = MakeUtf8(bytes);

  const auto* in = reinterpret_cast<const UTF8Unit*>(utf8.data());
  std::string out;

  ASSERT_NO_THROW(ToUTF16Native(in, utf8.size(), &out));
  ASSERT_EQ(out.size(), 2u * 2u); // surrogate pair => 2 UTF-16 code units

  // Endianness detect is tricky without ASCII; infer by trying both and accept the one that matches.
  const auto unitsLE = DecodeNativeUTF16BytesToUnits(out, /*littleEndian*/ true);
  const auto unitsBE = DecodeNativeUTF16BytesToUnits(out, /*littleEndian*/ false);

  const bool matchesLE = (unitsLE.size() == 2 && unitsLE[0] == 0xD83D && unitsLE[1] == 0xDE00);
  const bool matchesBE = (unitsBE.size() == 2 && unitsBE[0] == 0xD83D && unitsBE[1] == 0xDE00);

  EXPECT_TRUE(matchesLE || matchesBE);
}

// ------------------------------- Boundary conditions -------------------------------

TEST_F(UnicodeConversionsTest_2055, LargeAsciiInputProcessesAcrossInternalChunks_2055) {
  // Input length > internal buffer sizing (implementation uses an internal buffer per call).
  const size_t n = 9000; // > 8k
  std::string utf8(n, 'a');

  const auto* in = reinterpret_cast<const UTF8Unit*>(utf8.data());
  std::string out;

  ASSERT_NO_THROW(ToUTF16Native(in, utf8.size(), &out));
  ASSERT_EQ(out.size(), n * 2u);

  const bool little = DetectLittleEndianFromFirstASCII(out, static_cast<unsigned char>('a'));
  const auto units = DecodeNativeUTF16BytesToUnits(out, little);

  ASSERT_EQ(units.size(), n);
  // Spot-check a few positions to avoid O(n) assertions being too heavy.
  EXPECT_EQ(units.front(), 0x0061);
  EXPECT_EQ(units[n / 2], 0x0061);
  EXPECT_EQ(units.back(), 0x0061);
}

// ------------------------------- Exceptional / error cases -------------------------------

TEST_F(UnicodeConversionsTest_2055, TruncatedMultibyteSequenceThrows_2055) {
  // Incomplete UTF-8 sequence at the end should be observable as an exception.
  // Example: start of 3-byte sequence for '€' (E2 82 AC) but truncated to (E2 82).
  const std::vector<unsigned char> bytes = {0xE2, 0x82};
  const std::string utf8 = MakeUtf8(bytes);

  const auto* in = reinterpret_cast<const UTF8Unit*>(utf8.data());
  std::string out("keep?");

  EXPECT_ANY_THROW(ToUTF16Native(in, utf8.size(), &out));
}

} // namespace