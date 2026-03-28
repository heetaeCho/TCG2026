// File: grandom_fill_test.cc
#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <cstdint>

// Black-box declaration (implemented in ./TestProjects/poppler/goo/grandom.cc)
void grandom_fill(unsigned char* buff, int size);

class GrandomFillTest_26 : public ::testing::Test {};

TEST_F(GrandomFillTest_26, ZeroSizeWithNullptrDoesNotCrash_26) {
  // For size == 0, the loop should not execute; nullptr should be safe.
  EXPECT_NO_THROW(grandom_fill(nullptr, 0));
}

TEST_F(GrandomFillTest_26, NegativeSizeWithNullptrDoesNotCrash_26) {
  // For size < 0, the loop condition index < size is false initially; no deref.
  EXPECT_NO_THROW(grandom_fill(nullptr, -1));
  EXPECT_NO_THROW(grandom_fill(nullptr, -100));
}

TEST_F(GrandomFillTest_26, ZeroSizeDoesNotModifyBuffer_26) {
  std::array<unsigned char, 16> buf{};
  buf.fill(static_cast<unsigned char>(0xAA));

  grandom_fill(buf.data(), 0);

  for (unsigned char v : buf) {
    EXPECT_EQ(v, static_cast<unsigned char>(0xAA));
  }
}

TEST_F(GrandomFillTest_26, NegativeSizeDoesNotModifyBuffer_26) {
  std::array<unsigned char, 16> buf{};
  buf.fill(static_cast<unsigned char>(0xAA));

  grandom_fill(buf.data(), -5);

  for (unsigned char v : buf) {
    EXPECT_EQ(v, static_cast<unsigned char>(0xAA));
  }
}

TEST_F(GrandomFillTest_26, WritesOnlyWithinRequestedRange_Size1_26) {
  // Arrange a buffer with canaries on both sides of a 1-byte target.
  std::array<unsigned char, 3> buf{};
  buf[0] = static_cast<unsigned char>(0x11);  // left canary
  buf[1] = static_cast<unsigned char>(0x22);  // target
  buf[2] = static_cast<unsigned char>(0x33);  // right canary

  grandom_fill(&buf[1], 1);

  // Canaries must remain untouched.
  EXPECT_EQ(buf[0], static_cast<unsigned char>(0x11));
  EXPECT_EQ(buf[2], static_cast<unsigned char>(0x33));
}

TEST_F(GrandomFillTest_26, WritesOnlyWithinRequestedRange_MiddleSlice_26) {
  // Buffer layout:
  // [canary][  target range  ][canary]
  constexpr std::size_t kTotal = 64;
  constexpr std::size_t kLeftCanarySize = 8;
  constexpr std::size_t kTargetSize = 32;
  constexpr std::size_t kRightCanarySize = kTotal - kLeftCanarySize - kTargetSize;

  static_assert(kRightCanarySize > 0, "Need a right canary region.");

  std::array<unsigned char, kTotal> buf{};
  buf.fill(static_cast<unsigned char>(0xAA));

  unsigned char* target = buf.data() + kLeftCanarySize;
  grandom_fill(target, static_cast<int>(kTargetSize));

  // Verify left canary region unchanged.
  for (std::size_t i = 0; i < kLeftCanarySize; ++i) {
    EXPECT_EQ(buf[i], static_cast<unsigned char>(0xAA)) << "Left canary modified at " << i;
  }
  // Verify right canary region unchanged.
  for (std::size_t i = kLeftCanarySize + kTargetSize; i < kTotal; ++i) {
    EXPECT_EQ(buf[i], static_cast<unsigned char>(0xAA)) << "Right canary modified at " << i;
  }
}

TEST_F(GrandomFillTest_26, SizeZeroDoesNotTouchCanariesWhenPointingInsideBuffer_26) {
  std::array<unsigned char, 10> buf{};
  buf.fill(static_cast<unsigned char>(0xCC));

  // Point inside the buffer but ask to write zero bytes.
  grandom_fill(buf.data() + 5, 0);

  for (unsigned char v : buf) {
    EXPECT_EQ(v, static_cast<unsigned char>(0xCC));
  }
}