// =================================================================================================
// TEST_ID: 2083
// Unit tests for UTF32Swp_to_UTF8 (black-box via compiled-in .cpp to access internal-linkage symbol)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>

// Include the implementation file to access the file-scope static function.
// This is a common technique for unit-testing internal-linkage helpers while still treating them
// as a black box (no private state access, no re-implementation).
#include "xmpsdk/src/UnicodeConversions.cpp"

namespace {

// Helper: produce an input UTF32Unit value such that UTF32InSwap(&value_in_input) yields `cp`.
static UTF32Unit MakeUTF32SwappedForInput(UTF32Unit cp) {
  UTF32Unit tmp = cp;
  return UTF32InSwap(&tmp);  // swap once; converter swaps again when reading.
}

static std::vector<UTF32Unit> MakeSwappedInput(std::initializer_list<UTF32Unit> cps) {
  std::vector<UTF32Unit> in;
  in.reserve(cps.size());
  for (UTF32Unit cp : cps) in.push_back(MakeUTF32SwappedForInput(cp));
  return in;
}

static std::vector<uint8_t> ToU8(const UTF8Unit* p, size_t n) {
  std::vector<uint8_t> out;
  out.reserve(n);
  for (size_t i = 0; i < n; ++i) out.push_back(static_cast<uint8_t>(p[i]));
  return out;
}

class UnicodeConversionsTest_2083 : public ::testing::Test {};

}  // namespace

TEST_F(UnicodeConversionsTest_2083, ConvertsASCIIOnly_2083) {
  const auto utf32In = MakeSwappedInput({0x41u, 0x42u, 0x43u});  // "ABC"

  UTF8Unit utf8Out[3] = {};
  size_t utf32Read = 0;
  size_t utf8Written = 0;

  UTF32Swp_to_UTF8(utf32In.data(), utf32In.size(), utf8Out, sizeof(utf8Out), &utf32Read, &utf8Written);

  EXPECT_EQ(utf32Read, 3u);
  EXPECT_EQ(utf8Written, 3u);

  const std::vector<uint8_t> bytes = ToU8(utf8Out, utf8Written);
  EXPECT_EQ(bytes, (std::vector<uint8_t>{0x41u, 0x42u, 0x43u}));
}

TEST_F(UnicodeConversionsTest_2083, ConvertsMixedASCIIAndMultiByte_WhenSpaceSufficient_2083) {
  // 'A' U+0041  -> 41
  // '©' U+00A9  -> C2 A9
  // '€' U+20AC  -> E2 82 AC
  // '😀' U+1F600 -> F0 9F 98 80
  const auto utf32In = MakeSwappedInput({0x41u, 0x00A9u, 0x20ACu, 0x1F600u});

  UTF8Unit utf8Out[10] = {};  // 1 + 2 + 3 + 4
  size_t utf32Read = 0;
  size_t utf8Written = 0;

  UTF32Swp_to_UTF8(utf32In.data(), utf32In.size(), utf8Out, sizeof(utf8Out), &utf32Read, &utf8Written);

  EXPECT_EQ(utf32Read, 4u);
  EXPECT_EQ(utf8Written, 10u);

  const std::vector<uint8_t> bytes = ToU8(utf8Out, utf8Written);
  EXPECT_EQ(bytes, (std::vector<uint8_t>{
                       0x41u,                    // A
                       0xC2u, 0xA9u,              // ©
                       0xE2u, 0x82u, 0xACu,        // €
                       0xF0u, 0x9Fu, 0x98u, 0x80u  // 😀
                   }));
}

TEST_F(UnicodeConversionsTest_2083, StopsBeforeMultiByte_WhenOutputBufferTooSmall_2083) {
  // 'A' fits in 1 byte, '©' requires 2 bytes.
  const auto utf32In = MakeSwappedInput({0x41u, 0x00A9u});

  UTF8Unit utf8Out[1] = {};
  size_t utf32Read = 0;
  size_t utf8Written = 0;

  UTF32Swp_to_UTF8(utf32In.data(), utf32In.size(), utf8Out, sizeof(utf8Out), &utf32Read, &utf8Written);

  // Should have written only the ASCII 'A' and stopped when it couldn't fit '©'.
  EXPECT_EQ(utf32Read, 1u);
  EXPECT_EQ(utf8Written, 1u);

  const std::vector<uint8_t> bytes = ToU8(utf8Out, utf8Written);
  EXPECT_EQ(bytes, (std::vector<uint8_t>{0x41u}));
}

TEST_F(UnicodeConversionsTest_2083, ConvertsUpToExactCapacity_StopsWhenNextCodePointDoesNotFit_2083) {
  // Capacity exactly fits "A©" (3 bytes), but not the next '€' (3 more bytes).
  const auto utf32In = MakeSwappedInput({0x41u, 0x00A9u, 0x20ACu});

  UTF8Unit utf8Out[3] = {};
  size_t utf32Read = 0;
  size_t utf8Written = 0;

  UTF32Swp_to_UTF8(utf32In.data(), utf32In.size(), utf8Out, sizeof(utf8Out), &utf32Read, &utf8Written);

  EXPECT_EQ(utf32Read, 2u);
  EXPECT_EQ(utf8Written, 3u);

  const std::vector<uint8_t> bytes = ToU8(utf8Out, utf8Written);
  EXPECT_EQ(bytes, (std::vector<uint8_t>{0x41u, 0xC2u, 0xA9u}));
}

TEST_F(UnicodeConversionsTest_2083, HandlesZeroInputLength_2083) {
  const auto utf32In = MakeSwappedInput({0x41u});  // data exists but len=0 is the key case

  UTF8Unit utf8Out[4] = {UTF8Unit(0xAA), UTF8Unit(0xBB), UTF8Unit(0xCC), UTF8Unit(0xDD)};
  size_t utf32Read = 123;
  size_t utf8Written = 456;

  UTF32Swp_to_UTF8(utf32In.data(), 0, utf8Out, sizeof(utf8Out), &utf32Read, &utf8Written);

  EXPECT_EQ(utf32Read, 0u);
  EXPECT_EQ(utf8Written, 0u);
}

TEST_F(UnicodeConversionsTest_2083, HandlesZeroOutputCapacity_2083) {
  const auto utf32In = MakeSwappedInput({0x41u, 0x42u});

  UTF8Unit utf8Out[1] = {};
  size_t utf32Read = 999;
  size_t utf8Written = 999;

  UTF32Swp_to_UTF8(utf32In.data(), utf32In.size(), utf8Out, 0, &utf32Read, &utf8Written);

  EXPECT_EQ(utf32Read, 0u);
  EXPECT_EQ(utf8Written, 0u);
}