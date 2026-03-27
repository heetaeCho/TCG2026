// TEST_ID = 212
//
// Unit tests for ASCIIHexEncoder (Stream.h)
//
// Constraints honored:
// - Treat implementation as black box (only observable behavior via public interface).
// - No private/internal state access.
// - No re-implementation of logic beyond calling the interface.
// - No unnecessary mocks (no external collaborators in this interface).

#include <gtest/gtest.h>

// Include the header under test.
#include "Stream.h"

// If Stream.h is in a namespace in your codebase (e.g., poppler), adjust accordingly.
// These tests assume ASCIIHexEncoder is accessible as-is.

class ASCIIHexEncoderTest_212 : public ::testing::Test {
protected:
  ASCIIHexEncoder encoder;
};

TEST_F(ASCIIHexEncoderTest_212, IsBinaryDefaultArgumentReturnsFalse_212) {
  // Exercise: call with default argument (no parameter).
  EXPECT_FALSE(encoder.isBinary());
}

TEST_F(ASCIIHexEncoderTest_212, IsBinaryExplicitTrueReturnsFalse_212) {
  // Exercise: call with explicit last=true.
  EXPECT_FALSE(encoder.isBinary(true));
}

TEST_F(ASCIIHexEncoderTest_212, IsBinaryExplicitFalseReturnsFalse_212) {
  // Exercise: call with explicit last=false (boundary variation for bool input).
  EXPECT_FALSE(encoder.isBinary(false));
}

// Boundary-ish coverage: repeated calls should be stable/consistent via public API.
TEST_F(ASCIIHexEncoderTest_212, IsBinaryRepeatedCallsRemainFalse_212) {
  EXPECT_FALSE(encoder.isBinary());
  EXPECT_FALSE(encoder.isBinary(true));
  EXPECT_FALSE(encoder.isBinary(false));
  EXPECT_FALSE(encoder.isBinary());  // again
}