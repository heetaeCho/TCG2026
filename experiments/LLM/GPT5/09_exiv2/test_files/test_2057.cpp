// =================================================================================================
// TEST_ID: 2057
// Unit tests for: ToUTF32Native (./TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

// Prefer including the real SDK header(s) that declare UTF8Unit/UTF32Unit and ToUTF32Native.
// In many XMP SDK layouts, the conversion APIs are declared in a header alongside the .cpp.
// If your build already exports ToUTF32Native via some other public header, include that instead.
#if __has_include("UnicodeConversions.hpp")
#include "UnicodeConversions.hpp"
#elif __has_include("UnicodeConversions.h")
#include "UnicodeConversions.h"
#elif __has_include("XMP_UnicodeConversions.hpp")
#include "XMP_UnicodeConversions.hpp"
#elif __has_include("XMP_UnicodeConversions.h")
#include "XMP_UnicodeConversions.h"
#else
// Fallback forward declarations (only for compilation in case headers are not directly includable
// from the test target). If your environment provides the proper headers, this block is unused.
using UTF8Unit = unsigned char;
using UTF32Unit = uint32_t;
extern void ToUTF32Native(const UTF8Unit* utf8In, size_t utf8Len, std::string* utf32Str);
#endif

class UnicodeConversionsTest_2057 : public ::testing::Test {
protected:
  static std::vector<uint32_t> AsNativeU32(const std::string& utf32Bytes) {
    std::vector<uint32_t> out;
    if (utf32Bytes.empty()) return out;

    // Output is a byte string where each UTF-32 code unit occupies 4 bytes.
    EXPECT_EQ(utf32Bytes.size() % 4, 0u) << "UTF-32 byte string must be multiple of 4 bytes";
    const size_t count = utf32Bytes.size() / 4;
    out.resize(count);

    for (size_t i = 0; i < count; ++i) {
      uint32_t u = 0;
      std::memcpy(&u, utf32Bytes.data() + i * 4, 4);
      out[i] = u;
    }
    return out;
  }
};

TEST_F(UnicodeConversionsTest_2057, EmptyInputProducesEmptyOutput_2057) {
  std::string out("non-empty-initial");
  const UTF8Unit* in = reinterpret_cast<const UTF8Unit*>("");
  ToUTF32Native(in, 0, &out);

  EXPECT_TRUE(out.empty());
}

TEST_F(UnicodeConversionsTest_2057, AsciiConvertsToExpectedCodePoints_2057) {
  const std::string in = "ABCxyz012";
  std::string out;

  ToUTF32Native(reinterpret_cast<const UTF8Unit*>(in.data()), in.size(), &out);

  // Each ASCII byte becomes a single UTF-32 code unit -> 4 bytes each.
  ASSERT_EQ(out.size(), in.size() * 4);

  const auto u32 = AsNativeU32(out);
  ASSERT_EQ(u32.size(), in.size());

  for (size_t i = 0; i < in.size(); ++i) {
    EXPECT_EQ(u32[i], static_cast<uint32_t>(static_cast<unsigned char>(in[i])))
        << "Mismatch at index " << i;
  }
}

TEST_F(UnicodeConversionsTest_2057, Utf8MultibyteConvertsToExpectedCodePoints_2057) {
  // "A" + "¢" (U+00A2) + "€" (U+20AC) + "😀" (U+1F600) + "Z"
  const std::string in =
      std::string("A") +
      std::string("\xC2\xA2") +
      std::string("\xE2\x82\xAC") +
      std::string("\xF0\x9F\x98\x80") +
      std::string("Z");

  std::string out;
  ToUTF32Native(reinterpret_cast<const UTF8Unit*>(in.data()), in.size(), &out);

  const auto u32 = AsNativeU32(out);
  ASSERT_EQ(u32.size(), 5u);

  EXPECT_EQ(u32[0], 0x00000041u);  // 'A'
  EXPECT_EQ(u32[1], 0x000000A2u);  // '¢'
  EXPECT_EQ(u32[2], 0x000020ACu);  // '€'
  EXPECT_EQ(u32[3], 0x0001F600u);  // '😀'
  EXPECT_EQ(u32[4], 0x0000005Au);  // 'Z'
}

TEST_F(UnicodeConversionsTest_2057, LargeAsciiInputProducesExpectedSizedOutput_2057) {
  // Large enough to require internal looping/chunking.
  const size_t kLen = 10000;
  std::string in(kLen, 'b');
  std::string out;

  ToUTF32Native(reinterpret_cast<const UTF8Unit*>(in.data()), in.size(), &out);

  ASSERT_EQ(out.size(), in.size() * 4);

  // Spot-check a few positions (beginning, middle, end) without relying on internals.
  const auto u32 = AsNativeU32(out);
  ASSERT_EQ(u32.size(), kLen);

  EXPECT_EQ(u32.front(), static_cast<uint32_t>('b'));
  EXPECT_EQ(u32[kLen / 2], static_cast<uint32_t>('b'));
  EXPECT_EQ(u32.back(), static_cast<uint32_t>('b'));
}

TEST_F(UnicodeConversionsTest_2057, MultibyteAcrossLikelyChunkBoundaryRemainsCorrect_2057) {
  // Craft input near a typical chunk boundary so a multi-byte sequence might straddle processing.
  // (We don't assume the exact chunk size; we only validate observable correctness.)
  std::string in(4095, 'a');          // many ASCII
  in += std::string("\xE2\x82\xAC");  // '€' (3 bytes)
  in += std::string(10, 'c');

  std::string out;
  ToUTF32Native(reinterpret_cast<const UTF8Unit*>(in.data()), in.size(), &out);

  const auto u32 = AsNativeU32(out);
  ASSERT_EQ(u32.size(), 4095u + 1u + 10u);

  EXPECT_EQ(u32[0], static_cast<uint32_t>('a'));
  EXPECT_EQ(u32[4094], static_cast<uint32_t>('a'));
  EXPECT_EQ(u32[4095], 0x000020ACu);  // '€'
  EXPECT_EQ(u32.back(), static_cast<uint32_t>('c'));
}

TEST_F(UnicodeConversionsTest_2057, TruncatedUtf8AtEndThrows_2057) {
  // Start of a 3-byte sequence (E2 82 AC) but omit last byte to make it incomplete.
  const std::string in = std::string("X") + std::string("\xE2\x82");

  std::string out;
  EXPECT_ANY_THROW({
    ToUTF32Native(reinterpret_cast<const UTF8Unit*>(in.data()), in.size(), &out);
  });
}

TEST_F(UnicodeConversionsTest_2057, LoneContinuationByteThrows_2057) {
  // 0x80 is a continuation byte; on its own it's invalid UTF-8.
  const std::string in = std::string("A") + std::string("\x80") + std::string("B");

  std::string out;
  EXPECT_ANY_THROW({
    ToUTF32Native(reinterpret_cast<const UTF8Unit*>(in.data()), in.size(), &out);
  });
}