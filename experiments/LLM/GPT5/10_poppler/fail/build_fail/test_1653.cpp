// FlateEncoderTest_1653.cpp
#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/poppler/poppler/FlateEncoder.h"

class FlateEncoderTest_1653 : public ::testing::Test {
protected:
  FlateEncoder encoder;
};

TEST_F(FlateEncoderTest_1653, IsBinary_DefaultArgument_ReturnsTrue_1653) {
  // Normal operation: call with default argument
  EXPECT_TRUE(encoder.isBinary());
}

TEST_F(FlateEncoderTest_1653, IsBinary_ExplicitTrue_ReturnsTrue_1653) {
  // Normal operation: explicitly pass true
  EXPECT_TRUE(encoder.isBinary(true));
}

TEST_F(FlateEncoderTest_1653, IsBinary_ExplicitFalse_ReturnsTrue_1653) {
  // Boundary/variation: explicitly pass false (should not matter per observable behavior)
  EXPECT_TRUE(encoder.isBinary(false));
}

TEST_F(FlateEncoderTest_1653, IsBinary_ConstObject_CallIsConstAndReturnsTrue_1653) {
  // Verify const-correctness is usable through the public interface
  const FlateEncoder& constEnc = encoder;
  EXPECT_TRUE(constEnc.isBinary());
  EXPECT_TRUE(constEnc.isBinary(false));
}

TEST_F(FlateEncoderTest_1653, IsBinary_RepeatedCalls_AreStable_1653) {
  // Boundary-ish: repeated calls should be stable/consistent
  for (int i = 0; i < 100; ++i) {
    EXPECT_TRUE(encoder.isBinary());
    EXPECT_TRUE(encoder.isBinary(i % 2 == 0));
  }
}