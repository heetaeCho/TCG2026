// ============================================================================
// File:        test_MD5Init_2047.cpp
// Description: Unit tests for MD5Init (MD5.cpp) using GoogleTest
// TEST_ID:     2047
// ============================================================================

#include <gtest/gtest.h>

#include "MD5.h"

// MD5Init is implemented in xmpsdk/src/MD5.cpp (C++), but may be linked as C.
// Forward declare without assuming linkage specifics used by the project.
extern void MD5Init(struct MD5_CTX* ctx);

namespace {

class MD5InitTest_2047 : public ::testing::Test {
 protected:
  MD5_CTX ctx_{};
};

TEST_F(MD5InitTest_2047, InitializesBufAndBytesToExpectedConstants_2047) {
  // Act
  MD5Init(&ctx_);

  // Assert (observable behavior via public fields)
  EXPECT_EQ(ctx_.buf[0], 0x67452301u);
  EXPECT_EQ(ctx_.buf[1], 0xefcdab89u);
  EXPECT_EQ(ctx_.buf[2], 0x98badcfeu);
  EXPECT_EQ(ctx_.buf[3], 0x10325476u);

  EXPECT_EQ(ctx_.bytes[0], 0u);
  EXPECT_EQ(ctx_.bytes[1], 0u);
}

TEST_F(MD5InitTest_2047, OverwritesExistingValuesInBufAndBytes_2047) {
  // Arrange: seed with non-default values
  ctx_.buf[0] = 0u;
  ctx_.buf[1] = 1u;
  ctx_.buf[2] = 2u;
  ctx_.buf[3] = 3u;
  ctx_.bytes[0] = 123u;
  ctx_.bytes[1] = 456u;

  // Act
  MD5Init(&ctx_);

  // Assert: must be overwritten to the expected initialization values
  EXPECT_EQ(ctx_.buf[0], 0x67452301u);
  EXPECT_EQ(ctx_.buf[1], 0xefcdab89u);
  EXPECT_EQ(ctx_.buf[2], 0x98badcfeu);
  EXPECT_EQ(ctx_.buf[3], 0x10325476u);

  EXPECT_EQ(ctx_.bytes[0], 0u);
  EXPECT_EQ(ctx_.bytes[1], 0u);
}

TEST_F(MD5InitTest_2047, CanBeCalledRepeatedlyAndRemainsIdempotentForBufAndBytes_2047) {
  // Act
  MD5Init(&ctx_);

  // Mutate (simulate changes between calls) and re-init
  ctx_.buf[0] ^= 0xffffffffu;
  ctx_.bytes[0] = 999u;

  MD5Init(&ctx_);

  // Assert: calling again restores the same expected values
  EXPECT_EQ(ctx_.buf[0], 0x67452301u);
  EXPECT_EQ(ctx_.buf[1], 0xefcdab89u);
  EXPECT_EQ(ctx_.buf[2], 0x98badcfeu);
  EXPECT_EQ(ctx_.buf[3], 0x10325476u);

  EXPECT_EQ(ctx_.bytes[0], 0u);
  EXPECT_EQ(ctx_.bytes[1], 0u);
}

}  // namespace