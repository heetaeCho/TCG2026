// =================================================================================================
// TEST_ID: 2058
// Unit tests for FromUTF16 in ./TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "XMP_Const.h"
#include "UnicodeConversions.hpp"  // expects UTF16Unit, FromUTF16

namespace {

// Runtime endianness probe (portable, no UB).
static bool IsHostBigEndian() {
  const uint16_t v = 0x0102;
  const uint8_t* p = reinterpret_cast<const uint8_t*>(&v);
  return (p[0] == 0x01);
}

static UTF16Unit MaybeByteSwap16(UTF16Unit v) {
  const uint16_t u = static_cast<uint16_t>(v);
  const uint16_t swapped = static_cast<uint16_t>((u >> 8) | (u << 8));
  return static_cast<UTF16Unit>(swapped);
}

// Build a UTF16Unit whose *byte order* in memory corresponds to the requested
// (bigEndianInput == true => UTF-16BE byte sequence; false => UTF-16LE byte sequence).
// This makes the tests robust across host endianness.
static UTF16Unit MakeEndianUnit(uint16_t codeUnitValue, bool bigEndianInput) {
  const bool hostBE = IsHostBigEndian();
  UTF16Unit unit = static_cast<UTF16Unit>(codeUnitValue);
  if (hostBE != bigEndianInput) unit = MaybeByteSwap16(unit);
  return unit;
}

static std::vector<UTF16Unit> MakeUtf16Units_ASCII(const char* s, bool bigEndianInput) {
  std::vector<UTF16Unit> out;
  for (const unsigned char* p = reinterpret_cast<const unsigned char*>(s); *p != 0; ++p) {
    out.push_back(MakeEndianUnit(static_cast<uint16_t>(*p), bigEndianInput));
  }
  return out;
}

// U+1F600 (GRINNING FACE) => UTF-16 surrogate pair: D83D DE00
static std::vector<UTF16Unit> MakeUtf16Units_GrinningFace(bool bigEndianInput) {
  std::vector<UTF16Unit> out;
  out.push_back(MakeEndianUnit(0xD83D, bigEndianInput));
  out.push_back(MakeEndianUnit(0xDE00, bigEndianInput));
  return out;
}

// UTF-8 for U+1F600: F0 9F 98 80
static std::string Utf8_GrinningFace() {
  const unsigned char bytes[] = {0xF0, 0x9F, 0x98, 0x80};
  return std::string(reinterpret_cast<const char*>(bytes),
                     reinterpret_cast<const char*>(bytes + sizeof(bytes)));
}

// Some XMP SDK builds throw XMP_Error with GetID(). Keep the check optional.
template <class E>
static auto TryGetId(const E& e, int /*priority*/)
    -> decltype(static_cast<int>(e.GetID()), int()) {
  return static_cast<int>(e.GetID());
}
static int TryGetId(...) { return -1; }

static void ExpectBadXmlIfPossible(const std::exception& e) {
  // Best-effort: if exception has GetID() we verify it.
  const int id = TryGetId(e, 0);
  if (id != -1) {
    EXPECT_EQ(kXMPErr_BadXML, id);
  }
}

}  // namespace

class FromUTF16Test_2058 : public ::testing::Test {};

TEST_F(FromUTF16Test_2058, EmptyInputClearsOutput_2058) {
  std::string out = "preexisting";
  const UTF16Unit* in = nullptr;

  EXPECT_NO_THROW(FromUTF16(in, 0, &out, /*bigEndian*/ false));
  EXPECT_TRUE(out.empty());

  out = "preexisting2";
  EXPECT_NO_THROW(FromUTF16(in, 0, &out, /*bigEndian*/ true));
  EXPECT_TRUE(out.empty());
}

TEST_F(FromUTF16Test_2058, ConvertsAsciiUtf16LEToUtf8_2058) {
  const std::vector<UTF16Unit> in = MakeUtf16Units_ASCII("ABC", /*bigEndianInput*/ false);
  std::string out = "junk";

  ASSERT_FALSE(in.empty());
  EXPECT_NO_THROW(FromUTF16(in.data(), in.size(), &out, /*bigEndian*/ false));
  EXPECT_EQ("ABC", out);
}

TEST_F(FromUTF16Test_2058, ConvertsAsciiUtf16BEToUtf8_2058) {
  const std::vector<UTF16Unit> in = MakeUtf16Units_ASCII("ABC", /*bigEndianInput*/ true);
  std::string out;

  ASSERT_FALSE(in.empty());
  EXPECT_NO_THROW(FromUTF16(in.data(), in.size(), &out, /*bigEndian*/ true));
  EXPECT_EQ("ABC", out);
}

TEST_F(FromUTF16Test_2058, ConvertsSupplementaryPlaneSurrogatePairLE_2058) {
  const std::vector<UTF16Unit> in = MakeUtf16Units_GrinningFace(/*bigEndianInput*/ false);
  std::string out;

  ASSERT_EQ(in.size(), 2u);
  EXPECT_NO_THROW(FromUTF16(in.data(), in.size(), &out, /*bigEndian*/ false));
  EXPECT_EQ(Utf8_GrinningFace(), out);
}

TEST_F(FromUTF16Test_2058, ConvertsSupplementaryPlaneSurrogatePairBE_2058) {
  const std::vector<UTF16Unit> in = MakeUtf16Units_GrinningFace(/*bigEndianInput*/ true);
  std::string out;

  ASSERT_EQ(in.size(), 2u);
  EXPECT_NO_THROW(FromUTF16(in.data(), in.size(), &out, /*bigEndian*/ true));
  EXPECT_EQ(Utf8_GrinningFace(), out);
}

TEST_F(FromUTF16Test_2058, LargeInputMoreThanInternalChunkProducesCorrectLength_2058) {
  // Exercise multi-iteration behavior without assuming internal details other than observable output.
  // Use ASCII 'a' => 1 UTF-16 unit, 1 UTF-8 byte per character.
  const size_t kCount = (16 * 1024) + 123;  // > 16k to exceed common chunk sizes
  std::vector<UTF16Unit> in;
  in.reserve(kCount);
  for (size_t i = 0; i < kCount; ++i) {
    in.push_back(MakeEndianUnit(static_cast<uint16_t>('a'), /*bigEndianInput*/ false));
  }

  std::string out;
  EXPECT_NO_THROW(FromUTF16(in.data(), in.size(), &out, /*bigEndian*/ false));
  EXPECT_EQ(kCount, out.size());
  EXPECT_EQ(std::string(kCount, 'a'), out);
}

TEST_F(FromUTF16Test_2058, InvalidDanglingHighSurrogateThrows_2058) {
  // A single high surrogate without a following low surrogate is invalid UTF-16.
  std::vector<UTF16Unit> in;
  in.push_back(MakeEndianUnit(0xD83D, /*bigEndianInput*/ false));  // high surrogate
  std::string out;

  try {
    FromUTF16(in.data(), in.size(), &out, /*bigEndian*/ false);
    FAIL() << "Expected an exception for dangling high surrogate";
  } catch (const std::exception& e) {
    // Best-effort: if the exception type exposes an ID, verify kXMPErr_BadXML.
    ExpectBadXmlIfPossible(e);
  } catch (...) {
    // Accept non-std exceptions as well (implementation-defined).
  }
}

TEST_F(FromUTF16Test_2058, MismatchedEndianFlagDoesNotCrashAndIsDeterministic_2058) {
  // We do NOT assume what the output *should* be when the endian flag doesn't match the input;
  // we only assert the function behaves consistently and does not mutate unpredictably.
  const std::vector<UTF16Unit> inBE = MakeUtf16Units_ASCII("ABC", /*bigEndianInput*/ true);

  std::string out1 = "x";
  std::string out2 = "y";

  EXPECT_NO_THROW(FromUTF16(inBE.data(), inBE.size(), &out1, /*bigEndian*/ false));
  EXPECT_NO_THROW(FromUTF16(inBE.data(), inBE.size(), &out2, /*bigEndian*/ false));

  EXPECT_EQ(out1, out2);
  // And it should have cleared the prior contents.
  EXPECT_NE(out1, "x");
  EXPECT_NE(out2, "y");
}