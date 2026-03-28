// =================================================================================================
// UNIT TESTS for ./TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp
// Target: static void CodePoint_to_UTF8_Multi ( UTF32Unit, UTF8Unit*, size_t, size_t* )
// TEST_ID: 2062
// =================================================================================================

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>

// Include the .cpp directly so this TU can see the internal-linkage (static) function.
// This is a common pattern for testing file-scope statics without changing production code.
#include "TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp"

namespace {

class UnicodeConversionsTest_2062 : public ::testing::Test {};

template <size_t N>
static void Fill(std::array<UTF8Unit, N>& buf, UTF8Unit value) {
  for (auto& b : buf) b = value;
}

template <size_t N>
static void ExpectPrefixEq(const std::array<UTF8Unit, N>& buf,
                           const std::initializer_list<uint8_t>& expectedPrefix,
                           size_t prefixLen) {
  ASSERT_EQ(expectedPrefix.size(), prefixLen);
  size_t i = 0;
  for (auto v : expectedPrefix) {
    ASSERT_LT(i, buf.size());
    EXPECT_EQ(static_cast<uint8_t>(buf[i]), v) << "at index " << i;
    ++i;
  }
}

}  // namespace

TEST_F(UnicodeConversionsTest_2062, ConvertsTwoByteBoundary_0080_2062) {
  std::array<UTF8Unit, 8> out{};
  Fill(out, static_cast<UTF8Unit>(0xAA));
  size_t written = 123;

  CodePoint_to_UTF8_Multi(static_cast<UTF32Unit>(0x0080), out.data(), out.size(), &written);

  EXPECT_EQ(written, 2u);
  ExpectPrefixEq(out, {0xC2, 0x80}, 2);
  // Ensure it didn't scribble beyond written bytes.
  for (size_t i = written; i < out.size(); ++i) {
    EXPECT_EQ(static_cast<uint8_t>(out[i]), 0xAA) << "at index " << i;
  }
}

TEST_F(UnicodeConversionsTest_2062, ConvertsOneByteMax_007F_2062) {
  std::array<UTF8Unit, 4> out{};
  Fill(out, static_cast<UTF8Unit>(0xAA));
  size_t written = 0;

  CodePoint_to_UTF8_Multi(static_cast<UTF32Unit>(0x007F), out.data(), out.size(), &written);

  EXPECT_EQ(written, 1u);
  ExpectPrefixEq(out, {0x7F}, 1);
  for (size_t i = written; i < out.size(); ++i) {
    EXPECT_EQ(static_cast<uint8_t>(out[i]), 0xAA) << "at index " << i;
  }
}

TEST_F(UnicodeConversionsTest_2062, ConvertsTwoByteMax_07FF_2062) {
  std::array<UTF8Unit, 4> out{};
  Fill(out, static_cast<UTF8Unit>(0xAA));
  size_t written = 0;

  CodePoint_to_UTF8_Multi(static_cast<UTF32Unit>(0x07FF), out.data(), out.size(), &written);

  EXPECT_EQ(written, 2u);
  ExpectPrefixEq(out, {0xDF, 0xBF}, 2);
  for (size_t i = written; i < out.size(); ++i) {
    EXPECT_EQ(static_cast<uint8_t>(out[i]), 0xAA) << "at index " << i;
  }
}

TEST_F(UnicodeConversionsTest_2062, ConvertsThreeByteBoundary_0800_2062) {
  std::array<UTF8Unit, 8> out{};
  Fill(out, static_cast<UTF8Unit>(0xAA));
  size_t written = 0;

  CodePoint_to_UTF8_Multi(static_cast<UTF32Unit>(0x0800), out.data(), out.size(), &written);

  EXPECT_EQ(written, 3u);
  ExpectPrefixEq(out, {0xE0, 0xA0, 0x80}, 3);
  for (size_t i = written; i < out.size(); ++i) {
    EXPECT_EQ(static_cast<uint8_t>(out[i]), 0xAA) << "at index " << i;
  }
}

TEST_F(UnicodeConversionsTest_2062, ConvertsThreeByteMax_FFFF_2062) {
  std::array<UTF8Unit, 8> out{};
  Fill(out, static_cast<UTF8Unit>(0xAA));
  size_t written = 0;

  CodePoint_to_UTF8_Multi(static_cast<UTF32Unit>(0xFFFF), out.data(), out.size(), &written);

  EXPECT_EQ(written, 3u);
  ExpectPrefixEq(out, {0xEF, 0xBF, 0xBF}, 3);
  for (size_t i = written; i < out.size(); ++i) {
    EXPECT_EQ(static_cast<uint8_t>(out[i]), 0xAA) << "at index " << i;
  }
}

TEST_F(UnicodeConversionsTest_2062, ConvertsFourByteBoundary_10000_2062) {
  std::array<UTF8Unit, 8> out{};
  Fill(out, static_cast<UTF8Unit>(0xAA));
  size_t written = 0;

  CodePoint_to_UTF8_Multi(static_cast<UTF32Unit>(0x10000), out.data(), out.size(), &written);

  EXPECT_EQ(written, 4u);
  ExpectPrefixEq(out, {0xF0, 0x90, 0x80, 0x80}, 4);
  for (size_t i = written; i < out.size(); ++i) {
    EXPECT_EQ(static_cast<uint8_t>(out[i]), 0xAA) << "at index " << i;
  }
}

TEST_F(UnicodeConversionsTest_2062, ConvertsMaxValidCodePoint_10FFFF_2062) {
  std::array<UTF8Unit, 8> out{};
  Fill(out, static_cast<UTF8Unit>(0xAA));
  size_t written = 0;

  CodePoint_to_UTF8_Multi(static_cast<UTF32Unit>(0x10FFFF), out.data(), out.size(), &written);

  EXPECT_EQ(written, 4u);
  ExpectPrefixEq(out, {0xF4, 0x8F, 0xBF, 0xBF}, 4);
  for (size_t i = written; i < out.size(); ++i) {
    EXPECT_EQ(static_cast<uint8_t>(out[i]), 0xAA) << "at index " << i;
  }
}

TEST_F(UnicodeConversionsTest_2062, NotEnoughRoom_WritesZeroAndDoesNotModifyBuffer_2062) {
  // U+0800 needs 3 bytes, provide only 2.
  std::array<UTF8Unit, 2> out{};
  Fill(out, static_cast<UTF8Unit>(0xAA));
  size_t written = 999;

  CodePoint_to_UTF8_Multi(static_cast<UTF32Unit>(0x0800), out.data(), out.size(), &written);

  EXPECT_EQ(written, 0u);
  EXPECT_EQ(static_cast<uint8_t>(out[0]), 0xAA);
  EXPECT_EQ(static_cast<uint8_t>(out[1]), 0xAA);
}

TEST_F(UnicodeConversionsTest_2062, SurrogateCodePoint_Throws_2062) {
  std::array<UTF8Unit, 8> out{};
  Fill(out, static_cast<UTF8Unit>(0xAA));
  size_t written = 0;

  EXPECT_ANY_THROW({
    CodePoint_to_UTF8_Multi(static_cast<UTF32Unit>(0xD800), out.data(), out.size(), &written);
  });
}

TEST_F(UnicodeConversionsTest_2062, OutOfRangeCodePoint_Throws_2062) {
  std::array<UTF8Unit, 8> out{};
  Fill(out, static_cast<UTF8Unit>(0xAA));
  size_t written = 0;

  EXPECT_ANY_THROW({
    CodePoint_to_UTF8_Multi(static_cast<UTF32Unit>(0x110000), out.data(), out.size(), &written);
  });
}