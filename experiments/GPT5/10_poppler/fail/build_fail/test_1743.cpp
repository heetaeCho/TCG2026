// TEST_ID: 1743
// File: CairoImageOutputDev_interpretType3Chars_1743_test.cc

#include <gtest/gtest.h>

#include <memory>

#include "CairoOutputDev.h"

namespace {

class CairoImageOutputDevTest_1743 : public ::testing::Test {
protected:
  void SetUp() override { dev = std::make_unique<CairoImageOutputDev>(); }

  std::unique_ptr<CairoImageOutputDev> dev;
};

TEST_F(CairoImageOutputDevTest_1743, InterpretType3CharsReturnsFalse_1743) {
  ASSERT_NE(dev, nullptr);
  EXPECT_FALSE(dev->interpretType3Chars());
}

TEST_F(CairoImageOutputDevTest_1743, InterpretType3CharsIsStableAcrossMultipleCalls_1743) {
  ASSERT_NE(dev, nullptr);

  // Repeated calls should be consistent (black-box observable behavior).
  EXPECT_FALSE(dev->interpretType3Chars());
  EXPECT_FALSE(dev->interpretType3Chars());
  EXPECT_FALSE(dev->interpretType3Chars());
}

TEST_F(CairoImageOutputDevTest_1743, InterpretType3CharsViaBasePointerReturnsFalse_1743) {
  ASSERT_NE(dev, nullptr);

  CairoOutputDev *base = dev.get();
  ASSERT_NE(base, nullptr);

  // Verifies the override is effective through the base interface.
  EXPECT_FALSE(base->interpretType3Chars());
}

} // namespace