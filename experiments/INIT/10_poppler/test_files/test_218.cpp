// TEST_ID: 218
//
// Unit tests for ASCII85Encoder (partial interface)
// File under test: ./TestProjects/poppler/poppler/Stream.h
//
// Constraints note:
// - Treat implementation as a black box.
// - Only test observable behavior from the public interface shown.

#include <gtest/gtest.h>

// Include the header under test.
#include "Stream.h"

namespace {

class ASCII85EncoderTest_218 : public ::testing::Test {};

TEST_F(ASCII85EncoderTest_218, IsBinary_DefaultArg_ReturnsFalse_218) {
  ASCII85Encoder enc;
  EXPECT_FALSE(enc.isBinary());
}

TEST_F(ASCII85EncoderTest_218, IsBinary_LastTrue_ReturnsFalse_218) {
  ASCII85Encoder enc;
  EXPECT_FALSE(enc.isBinary(true));
}

TEST_F(ASCII85EncoderTest_218, IsBinary_LastFalse_ReturnsFalse_218) {
  ASCII85Encoder enc;
  EXPECT_FALSE(enc.isBinary(false));
}

TEST_F(ASCII85EncoderTest_218, IsBinary_CalledMultipleTimes_AlwaysFalse_218) {
  ASCII85Encoder enc;

  EXPECT_FALSE(enc.isBinary());
  EXPECT_FALSE(enc.isBinary(true));
  EXPECT_FALSE(enc.isBinary(false));
  EXPECT_FALSE(enc.isBinary(true));
  EXPECT_FALSE(enc.isBinary());
}

}  // namespace