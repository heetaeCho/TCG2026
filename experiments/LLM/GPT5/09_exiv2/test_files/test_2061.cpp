// =================================================================================================
//  TEST: UnicodeConversions.cpp (FromUTF32Native)
//  TEST_ID: 2061
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#if defined(__has_include)
  #if __has_include("UnicodeConversions.hpp")
    #include "UnicodeConversions.hpp"
  #elif __has_include("UnicodeConversions.h")
    #include "UnicodeConversions.h"
  #elif __has_include("UnicodeConversions.hpp")
    #include "UnicodeConversions.hpp"
  #endif
#endif

// Some builds may require this for error ids like kXMPErr_BadXML, etc.
#if defined(__has_include)
  #if __has_include("XMP_Const.h")
    #include "XMP_Const.h"
  #endif
#endif

// FromUTF32Native is defined as `extern void ...` in UnicodeConversions.cpp.
// Make sure we have a declaration even if the header include above didn't provide it.
#ifndef HAVE_FROM_UTF32_NATIVE_DECL
extern void FromUTF32Native(const UTF32Unit* utf32In, size_t utf32Len, std::string* utf8Str);
#endif

namespace {

// Helper: build UTF32 input as a vector.
static std::vector<UTF32Unit> MakeUTF32(std::initializer_list<uint32_t> cps) {
  std::vector<UTF32Unit> out;
  out.reserve(cps.size());
  for (uint32_t cp : cps) out.push_back(static_cast<UTF32Unit>(cp));
  return out;
}

}  // namespace

// -------------------------------------------------------------------------------------------------
// Normal operation
// -------------------------------------------------------------------------------------------------

TEST(UnicodeConversionsTest_2061, ConvertsAsciiToUtf8_2061) {
  std::string out = "preexisting";
  const auto in = MakeUTF32({0x41, 0x42, 0x43});  // "ABC"

  ASSERT_NO_THROW(FromUTF32Native(in.data(), in.size(), &out));
  EXPECT_EQ(out, "ABC");
}

TEST(UnicodeConversionsTest_2061, ConvertsLatin1NonAsciiToUtf8_2061) {
  // U+00E9 'é' => UTF-8: C3 A9
  std::string out;
  const auto in = MakeUTF32({0x00E9});

  ASSERT_NO_THROW(FromUTF32Native(in.data(), in.size(), &out));
  ASSERT_EQ(out.size(), 2u);
  EXPECT_EQ(static_cast<unsigned char>(out[0]), 0xC3);
  EXPECT_EQ(static_cast<unsigned char>(out[1]), 0xA9);
}

TEST(UnicodeConversionsTest_2061, ConvertsSupplementaryPlaneCodePointToUtf8_2061) {
  // U+1F600 GRINNING FACE => UTF-8: F0 9F 98 80
  std::string out;
  const auto in = MakeUTF32({0x0001F600});

  ASSERT_NO_THROW(FromUTF32Native(in.data(), in.size(), &out));
  ASSERT_EQ(out.size(), 4u);
  EXPECT_EQ(static_cast<unsigned char>(out[0]), 0xF0);
  EXPECT_EQ(static_cast<unsigned char>(out[1]), 0x9F);
  EXPECT_EQ(static_cast<unsigned char>(out[2]), 0x98);
  EXPECT_EQ(static_cast<unsigned char>(out[3]), 0x80);
}

// -------------------------------------------------------------------------------------------------
// Boundary conditions
// -------------------------------------------------------------------------------------------------

TEST(UnicodeConversionsTest_2061, EmptyInputClearsOutput_2061) {
  std::string out = "will be cleared";

  // Passing nullptr with length 0 should be safe (no reads should occur).
  ASSERT_NO_THROW(FromUTF32Native(nullptr, 0, &out));
  EXPECT_TRUE(out.empty());
}

TEST(UnicodeConversionsTest_2061, LargeInputProducesExpectedSize_2061) {
  // Large ASCII input: output length should match input length (ASCII -> 1 byte each).
  const size_t kCount = 20000;
  std::vector<UTF32Unit> in(kCount, static_cast<UTF32Unit>(0x61));  // 'a'
  std::string out;

  ASSERT_NO_THROW(FromUTF32Native(in.data(), in.size(), &out));
  EXPECT_EQ(out.size(), kCount);
  // Spot-check a few positions.
  EXPECT_EQ(out.front(), 'a');
  EXPECT_EQ(out[kCount / 2], 'a');
  EXPECT_EQ(out.back(), 'a');
}

// -------------------------------------------------------------------------------------------------
// Exceptional / error cases (observable via thrown exceptions)
// -------------------------------------------------------------------------------------------------

TEST(UnicodeConversionsTest_2061, InvalidCodePointThrows_2061) {
  // U+110000 is outside Unicode range (max is U+10FFFF).
  std::string out = "unchanged?";
  const auto in = MakeUTF32({0x00110000});

  EXPECT_ANY_THROW(FromUTF32Native(in.data(), in.size(), &out));
}