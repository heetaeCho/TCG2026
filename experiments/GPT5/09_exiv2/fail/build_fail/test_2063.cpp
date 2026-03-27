// TEST_ID: 2063
// Unit tests for CodePoint_to_UTF8
//
// File: ./TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>

// XMP SDK headers (expected to provide UTF8Unit/UTF32Unit + function declarations).
// Adjust include path if your build uses a different include root.
#include "UnicodeConversions.hpp"

namespace {

class UnicodeConversionsTest_2063 : public ::testing::Test {};

static std::vector<UTF8Unit> MakeBuf(size_t n, UTF8Unit fill) {
  return std::vector<UTF8Unit>(n, fill);
}

TEST_F(UnicodeConversionsTest_2063, AsciiZero_WritesSingleByte_2063) {
  auto buf = MakeBuf(4, UTF8Unit(0xAA));
  size_t written = 999;

  CodePoint_to_UTF8(UTF32Unit(0x00), buf.data(), buf.size(), &written);

  ASSERT_EQ(written, size_t{1});
  EXPECT_EQ(buf[0], UTF8Unit(0x00));
  EXPECT_EQ(buf[1], UTF8Unit(0xAA));  // no extra writes expected
  EXPECT_EQ(buf[2], UTF8Unit(0xAA));
  EXPECT_EQ(buf[3], UTF8Unit(0xAA));
}

TEST_F(UnicodeConversionsTest_2063, AsciiMax7F_WritesSingleByte_2063) {
  auto buf = MakeBuf(4, UTF8Unit(0xAA));
  size_t written = 0;

  CodePoint_to_UTF8(UTF32Unit(0x7F), buf.data(), buf.size(), &written);

  ASSERT_EQ(written, size_t{1});
  EXPECT_EQ(buf[0], UTF8Unit(0x7F));
  EXPECT_EQ(buf[1], UTF8Unit(0xAA));
}

TEST_F(UnicodeConversionsTest_2063, Ascii_WithZeroBufferLen_WritesNothing_2063) {
  auto buf = MakeBuf(2, UTF8Unit(0xAA));
  size_t written = 123;

  // Pass utf8Len = 0. Buffer pointer is non-null to satisfy preconditions.
  CodePoint_to_UTF8(UTF32Unit(0x41), buf.data(), 0, &written);

  EXPECT_EQ(written, size_t{0});
  // Should not modify output when length is 0.
  EXPECT_EQ(buf[0], UTF8Unit(0xAA));
  EXPECT_EQ(buf[1], UTF8Unit(0xAA));
}

TEST_F(UnicodeConversionsTest_2063, TwoByteEncoding_U0080_ProducesExpectedUtf8_2063) {
  auto buf = MakeBuf(8, UTF8Unit(0xAA));
  size_t written = 0;

  CodePoint_to_UTF8(UTF32Unit(0x80), buf.data(), buf.size(), &written);

  ASSERT_EQ(written, size_t{2});
  EXPECT_EQ(buf[0], UTF8Unit(0xC2));
  EXPECT_EQ(buf[1], UTF8Unit(0x80));
  EXPECT_EQ(buf[2], UTF8Unit(0xAA));
}

TEST_F(UnicodeConversionsTest_2063, ThreeByteEncoding_EuroSign_U20AC_ProducesExpectedUtf8_2063) {
  auto buf = MakeBuf(8, UTF8Unit(0xAA));
  size_t written = 0;

  CodePoint_to_UTF8(UTF32Unit(0x20AC), buf.data(), buf.size(), &written);

  ASSERT_EQ(written, size_t{3});
  EXPECT_EQ(buf[0], UTF8Unit(0xE2));
  EXPECT_EQ(buf[1], UTF8Unit(0x82));
  EXPECT_EQ(buf[2], UTF8Unit(0xAC));
  EXPECT_EQ(buf[3], UTF8Unit(0xAA));
}

TEST_F(UnicodeConversionsTest_2063, FourByteEncoding_GrinningFace_U1F600_ProducesExpectedUtf8_2063) {
  auto buf = MakeBuf(8, UTF8Unit(0xAA));
  size_t written = 0;

  CodePoint_to_UTF8(UTF32Unit(0x1F600), buf.data(), buf.size(), &written);

  ASSERT_EQ(written, size_t{4});
  EXPECT_EQ(buf[0], UTF8Unit(0xF0));
  EXPECT_EQ(buf[1], UTF8Unit(0x9F));
  EXPECT_EQ(buf[2], UTF8Unit(0x98));
  EXPECT_EQ(buf[3], UTF8Unit(0x80));
  EXPECT_EQ(buf[4], UTF8Unit(0xAA));
}

TEST_F(UnicodeConversionsTest_2063, MultiByte_WithSmallLen_DoesNotWritePastProvidedLen_2063) {
  // Intentionally provide a small utf8Len. We don't assume the function succeeds,
  // but it must not write beyond the provided length.
  auto buf = MakeBuf(8, UTF8Unit(0xAA));
  size_t written = 0;

  const size_t providedLen = 1;  // smaller than needed for U+0080
  CodePoint_to_UTF8(UTF32Unit(0x80), buf.data(), providedLen, &written);

  // Must not claim it wrote more than the provided length.
  EXPECT_LE(written, providedLen);

  // Canary bytes after providedLen must remain unchanged.
  for (size_t i = providedLen; i < buf.size(); ++i) {
    EXPECT_EQ(buf[i], UTF8Unit(0xAA));
  }
}

#if defined(GTEST_HAS_DEATH_TEST) && GTEST_HAS_DEATH_TEST
TEST_F(UnicodeConversionsTest_2063, NullOutputPointer_TriggersAssert_2063) {
  size_t written = 0;
  // Expect an assertion/death due to UC_Assert precondition.
  ASSERT_DEATH_IF_SUPPORTED(
      { CodePoint_to_UTF8(UTF32Unit(0x41), nullptr, 1, &written); }, ".*");
}

TEST_F(UnicodeConversionsTest_2063, NullWrittenPointer_TriggersAssert_2063) {
  auto buf = MakeBuf(2, UTF8Unit(0xAA));
  // Expect an assertion/death due to UC_Assert precondition.
  ASSERT_DEATH_IF_SUPPORTED(
      { CodePoint_to_UTF8(UTF32Unit(0x41), buf.data(), buf.size(), nullptr); }, ".*");
}
#endif  // death tests

}  // namespace