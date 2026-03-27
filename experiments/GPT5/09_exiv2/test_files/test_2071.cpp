// =================================================================================================
// TEST_ID 2071
// Unit tests for UTF8_to_UTF32Nat (UnicodeConversions.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>
#include <algorithm>

// Include the public header(s) that declare UTF8Unit/UTF32Unit and the conversion entry points.
// Adjust include path to match your build.
// NOTE: The function under test is static in UnicodeConversions.cpp. In this test suite we include
// the .cpp directly to legally reach the static symbol without re-implementing logic.
#include "TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp"

#ifndef TEST_ID
#define TEST_ID 2071
#endif

namespace {

using Byte = unsigned char;

// Helper to make UTF8Unit buffers without assuming UTF8Unit == char.
static std::vector<UTF8Unit> MakeUTF8(const std::vector<uint8_t>& bytes) {
  std::vector<UTF8Unit> out;
  out.reserve(bytes.size());
  for (uint8_t b : bytes) out.push_back(static_cast<UTF8Unit>(b));
  return out;
}

static void Call_UTF8_to_UTF32Nat(const std::vector<UTF8Unit>& in,
                                 size_t utf32Len,
                                 std::vector<UTF32Unit>* out,
                                 size_t* utf8Read,
                                 size_t* utf32Written) {
  ASSERT_NE(out, nullptr);
  out->assign(utf32Len, static_cast<UTF32Unit>(0xDEADBEEF));

  *utf8Read = 0;
  *utf32Written = 0;

  UTF8_to_UTF32Nat(in.data(),
                   in.size(),
                   out->data(),
                   out->size(),
                   utf8Read,
                   utf32Written);
}

}  // namespace

class UTF8ToUTF32NatTest_2071 : public ::testing::Test {};

TEST_F(UTF8ToUTF32NatTest_2071, ConvertsPureASCII_AllCopiedAndCountsMatch_2071) {
  const auto in = MakeUTF8({'H','e','l','l','o',' ','1','2','3','!'});
  std::vector<UTF32Unit> out;
  size_t utf8Read = 0, utf32Written = 0;

  Call_UTF8_to_UTF32Nat(in, /*utf32Len*/ in.size(), &out, &utf8Read, &utf32Written);

  EXPECT_EQ(utf8Read, in.size());
  EXPECT_EQ(utf32Written, in.size());

  for (size_t i = 0; i < in.size(); ++i) {
    EXPECT_EQ(static_cast<uint32_t>(out[i]), static_cast<uint32_t>(static_cast<uint8_t>(in[i])))
        << "Mismatch at index " << i;
  }
}

TEST_F(UTF8ToUTF32NatTest_2071, StopsWhenUTF32BufferTooSmall_ForASCIIOnly_2071) {
  const auto in = MakeUTF8({'A','B','C','D','E'});
  std::vector<UTF32Unit> out;
  size_t utf8Read = 0, utf32Written = 0;

  Call_UTF8_to_UTF32Nat(in, /*utf32Len*/ 3, &out, &utf8Read, &utf32Written);

  // For pure ASCII, we can observe deterministic truncation: one UTF-8 byte -> one UTF-32 unit.
  EXPECT_EQ(utf32Written, 3u);
  EXPECT_EQ(utf8Read, 3u);
  EXPECT_EQ(static_cast<uint32_t>(out[0]), static_cast<uint32_t>('A'));
  EXPECT_EQ(static_cast<uint32_t>(out[1]), static_cast<uint32_t>('B'));
  EXPECT_EQ(static_cast<uint32_t>(out[2]), static_cast<uint32_t>('C'));
}

TEST_F(UTF8ToUTF32NatTest_2071, ZeroLengthInput_WritesNothing_2071) {
  const std::vector<UTF8Unit> in;  // empty
  std::vector<UTF32Unit> out;
  size_t utf8Read = 123, utf32Written = 456;

  Call_UTF8_to_UTF32Nat(in, /*utf32Len*/ 4, &out, &utf8Read, &utf32Written);

  EXPECT_EQ(utf8Read, 0u);
  EXPECT_EQ(utf32Written, 0u);
}

TEST_F(UTF8ToUTF32NatTest_2071, ZeroLengthOutput_WritesNothing_2071) {
  const auto in = MakeUTF8({'x','y','z'});
  std::vector<UTF32Unit> out;
  size_t utf8Read = 111, utf32Written = 222;

  Call_UTF8_to_UTF32Nat(in, /*utf32Len*/ 0, &out, &utf8Read, &utf32Written);

  EXPECT_EQ(out.size(), 0u);
  EXPECT_EQ(utf8Read, 0u);
  EXPECT_EQ(utf32Written, 0u);
}

TEST_F(UTF8ToUTF32NatTest_2071, ConvertsLeadingASCIIThenAttemptsMultiByte_ObservedCounts_2071) {
  // "A" + U+00A9 (©) + "B"
  // UTF-8 bytes: 41 C2 A9 42
  const auto in = MakeUTF8({0x41, 0xC2, 0xA9, 0x42});
  std::vector<UTF32Unit> out;
  size_t utf8Read = 0, utf32Written = 0;

  Call_UTF8_to_UTF32Nat(in, /*utf32Len*/ 8, &out, &utf8Read, &utf32Written);

  // Observable behavior: should read at least the first ASCII byte and write at least 1 UTF-32 unit.
  EXPECT_GE(utf8Read, 1u);
  EXPECT_GE(utf32Written, 1u);
  EXPECT_EQ(static_cast<uint32_t>(out[0]), static_cast<uint32_t>('A'));

  // If it successfully converts ©, utf32Written should be >= 2 and utf8Read should be >= 3.
  // We avoid asserting exact code point value to not infer internal logic; we only assert
  // monotonicity and bounds consistent with consuming bytes/units.
  EXPECT_LE(utf8Read, in.size());
  EXPECT_LE(utf32Written, out.size());
}

TEST_F(UTF8ToUTF32NatTest_2071, OutputBufferLimitWithMultiByte_DoesNotOverrunAndCountsBounded_2071) {
  // Two multi-byte characters (e.g., ©©) plus ASCII tail.
  const auto in = MakeUTF8({0xC2, 0xA9, 0xC2, 0xA9, 0x21});  // © © !
  std::vector<UTF32Unit> out;
  size_t utf8Read = 0, utf32Written = 0;

  Call_UTF8_to_UTF32Nat(in, /*utf32Len*/ 1, &out, &utf8Read, &utf32Written);

  // With only 1 UTF-32 slot, it can write at most 1 code point.
  EXPECT_EQ(utf32Written, 1u);
  EXPECT_LE(utf8Read, in.size());
  // It must have read at least 1 byte if it wrote a character.
  EXPECT_GE(utf8Read, 1u);
}

TEST_F(UTF8ToUTF32NatTest_2071, IncompleteMultiByteAtEnd_ReadsUpToBoundary_2071) {
  // Lead byte of a 2-byte sequence (C2) without the continuation byte.
  const auto in = MakeUTF8({0x41, 0xC2});  // 'A' + incomplete
  std::vector<UTF32Unit> out;
  size_t utf8Read = 0, utf32Written = 0;

  Call_UTF8_to_UTF32Nat(in, /*utf32Len*/ 8, &out, &utf8Read, &utf32Written);

  // Observable: it should at least convert the leading ASCII 'A'.
  EXPECT_GE(utf8Read, 1u);
  EXPECT_GE(utf32Written, 1u);
  EXPECT_EQ(static_cast<uint32_t>(out[0]), static_cast<uint32_t>('A'));

  // And it must not claim to have read past input.
  EXPECT_LE(utf8Read, in.size());
}

TEST_F(UTF8ToUTF32NatTest_2071, InvalidUTF8Sequence_DoesNotReadPastInputAndCountsConsistent_2071) {
  // Overlong/invalid style bytes: 0xC0 0xAF is an invalid encoding in UTF-8 (commonly used as a test).
  // We do NOT assume how it's handled (replacement, stop, etc.), only that it doesn't overrun
  // and updates lengths consistently.
  const auto in = MakeUTF8({0x41, 0xC0, 0xAF, 0x42});
  std::vector<UTF32Unit> out;
  size_t utf8Read = 0, utf32Written = 0;

  Call_UTF8_to_UTF32Nat(in, /*utf32Len*/ 8, &out, &utf8Read, &utf32Written);

  EXPECT_LE(utf8Read, in.size());
  EXPECT_LE(utf32Written, out.size());
  // It should still have converted the initial 'A' in any reasonable observable behavior.
  EXPECT_GE(utf8Read, 1u);
  EXPECT_GE(utf32Written, 1u);
  EXPECT_EQ(static_cast<uint32_t>(out[0]), static_cast<uint32_t>('A'));
}

TEST_F(UTF8ToUTF32NatTest_2071, PreservesPreviouslyWrittenWhenStopsEarly_WrittenPrefixMatches_2071) {
  // ASCII prefix should be copied verbatim even if later bytes cause an early stop.
  const auto in = MakeUTF8({'P','r','e','f','i','x',' ', 0xC2});  // incomplete at end
  std::vector<UTF32Unit> out;
  size_t utf8Read = 0, utf32Written = 0;

  Call_UTF8_to_UTF32Nat(in, /*utf32Len*/ 16, &out, &utf8Read, &utf32Written);

  const std::vector<uint8_t> expectedPrefixBytes = {'P','r','e','f','i','x',' '};
  ASSERT_GE(utf32Written, expectedPrefixBytes.size());

  for (size_t i = 0; i < expectedPrefixBytes.size(); ++i) {
    EXPECT_EQ(static_cast<uint32_t>(out[i]), static_cast<uint32_t>(expectedPrefixBytes[i]))
        << "Prefix mismatch at index " << i;
  }
}