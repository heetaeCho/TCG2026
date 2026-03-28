// Decrypt_aesReadBlock_1600_test.cc
#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <cstdio>
#include <vector>

// Stream is a dependency of aesReadBlock.
#include "Stream.h"

// Include the implementation file to get access to the internal static function.
// This is a common unit-test technique for testing internal-file static helpers.
#include "Decrypt.cc"

namespace {

class VectorStream final : public Stream {
public:
  explicit VectorStream(std::vector<unsigned char> data)
      : data_(std::move(data)) {}

  int getChar() override {
    ++get_char_calls_;
    if (pos_ >= data_.size()) {
      return EOF;
    }
    return static_cast<int>(data_[pos_++]);
  }

  int getCharCalls() const { return get_char_calls_; }
  size_t pos() const { return pos_; }

private:
  std::vector<unsigned char> data_;
  size_t pos_ = 0;
  int get_char_calls_ = 0;
};

} // namespace

TEST(aesReadBlockTest_1600, FullBlockNoPaddingReturnsTrueAndCopies16Bytes_1600) {
  std::vector<unsigned char> inBytes(16);
  for (int i = 0; i < 16; ++i) inBytes[i] = static_cast<unsigned char>(i);

  VectorStream s(inBytes);
  std::array<unsigned char, 16> out{};
  out.fill(0xAA);

  const bool ok = aesReadBlock(&s, out.data(), /*addPadding=*/false);

  EXPECT_TRUE(ok);
  EXPECT_EQ(s.getCharCalls(), 16);

  for (int i = 0; i < 16; ++i) {
    EXPECT_EQ(out[i], static_cast<unsigned char>(i));
  }
}

TEST(aesReadBlockTest_1600, FullBlockWithPaddingFlagStillReturnsTrueAndCopies16Bytes_1600) {
  std::vector<unsigned char> inBytes(16);
  for (int i = 0; i < 16; ++i) inBytes[i] = static_cast<unsigned char>(0xF0 + i);

  VectorStream s(inBytes);
  std::array<unsigned char, 16> out{};
  out.fill(0x11);

  const bool ok = aesReadBlock(&s, out.data(), /*addPadding=*/true);

  EXPECT_TRUE(ok);
  EXPECT_EQ(s.getCharCalls(), 16);

  for (int i = 0; i < 16; ++i) {
    EXPECT_EQ(out[i], static_cast<unsigned char>(0xF0 + i));
  }
}

TEST(aesReadBlockTest_1600, PartialBlockNoPaddingReturnsFalseAndDoesNotOverwriteRemainder_1600) {
  const std::vector<unsigned char> inBytes = {0x10, 0x11, 0x12, 0x13, 0x14}; // 5 bytes

  VectorStream s(inBytes);
  std::array<unsigned char, 16> out{};
  out.fill(0xCC);

  const bool ok = aesReadBlock(&s, out.data(), /*addPadding=*/false);

  EXPECT_FALSE(ok);
  // Reads 5 bytes + 1 EOF attempt.
  EXPECT_EQ(s.getCharCalls(), 6);

  for (size_t i = 0; i < inBytes.size(); ++i) {
    EXPECT_EQ(out[i], inBytes[i]);
  }
  for (size_t i = inBytes.size(); i < out.size(); ++i) {
    EXPECT_EQ(out[i], 0xCC) << "Byte " << i << " should remain unchanged when no padding is added";
  }
}

TEST(aesReadBlockTest_1600, PartialBlockWithPaddingReturnsFalseAndPadsTo16Bytes_1600) {
  const std::vector<unsigned char> inBytes = {0xA0, 0xA1, 0xA2, 0xA3, 0xA4}; // 5 bytes

  VectorStream s(inBytes);
  std::array<unsigned char, 16> out{};
  out.fill(0x00);

  const bool ok = aesReadBlock(&s, out.data(), /*addPadding=*/true);

  EXPECT_FALSE(ok);
  // Reads 5 bytes + 1 EOF attempt.
  EXPECT_EQ(s.getCharCalls(), 6);

  for (size_t i = 0; i < inBytes.size(); ++i) {
    EXPECT_EQ(out[i], inBytes[i]);
  }

  const unsigned char pad = static_cast<unsigned char>(16 - inBytes.size()); // 11
  for (size_t i = inBytes.size(); i < out.size(); ++i) {
    EXPECT_EQ(out[i], pad) << "Byte " << i << " should be padding";
  }
}

TEST(aesReadBlockTest_1600, EmptyStreamWithPaddingReturnsFalseAndFillsAllWith16_1600) {
  VectorStream s(std::vector<unsigned char>{});
  std::array<unsigned char, 16> out{};
  out.fill(0x77);

  const bool ok = aesReadBlock(&s, out.data(), /*addPadding=*/true);

  EXPECT_FALSE(ok);
  // Immediate EOF on first getChar.
  EXPECT_EQ(s.getCharCalls(), 1);

  for (size_t i = 0; i < out.size(); ++i) {
    EXPECT_EQ(out[i], static_cast<unsigned char>(16));
  }
}

TEST(aesReadBlockTest_1600, FifteenBytesWithPaddingReturnsFalseAndPadsWith1_1600) {
  std::vector<unsigned char> inBytes(15);
  for (int i = 0; i < 15; ++i) inBytes[i] = static_cast<unsigned char>(0x20 + i);

  VectorStream s(inBytes);
  std::array<unsigned char, 16> out{};
  out.fill(0x00);

  const bool ok = aesReadBlock(&s, out.data(), /*addPadding=*/true);

  EXPECT_FALSE(ok);
  // Reads 15 bytes + 1 EOF attempt => 16 calls.
  EXPECT_EQ(s.getCharCalls(), 16);

  for (int i = 0; i < 15; ++i) {
    EXPECT_EQ(out[i], static_cast<unsigned char>(0x20 + i));
  }
  EXPECT_EQ(out[15], static_cast<unsigned char>(1));
}