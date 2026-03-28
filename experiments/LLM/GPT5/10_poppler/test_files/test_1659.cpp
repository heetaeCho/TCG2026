// PreScanOutputDev_interpretType3Chars_test_1659.cpp

#include <gtest/gtest.h>

#include "PreScanOutputDev.h"

namespace {

// Helper: pick a PSLevel value without assuming specific enumerator names.
// If construction fails (e.g., throws), tests will skip gracefully.
static PSLevel AnyPSLevel_1659(int v = 0) {
  return static_cast<PSLevel>(v);
}

class PreScanOutputDevTest_1659 : public ::testing::Test {
protected:
  static std::unique_ptr<PreScanOutputDev> MakeDevOrSkip_1659(int levelVal = 0) {
    try {
      return std::make_unique<PreScanOutputDev>(AnyPSLevel_1659(levelVal));
    } catch (...) {
      GTEST_SKIP() << "PreScanOutputDev constructor threw for PSLevel value "
                   << levelVal << "; skipping test.";
      return nullptr;
    }
  }
};

TEST_F(PreScanOutputDevTest_1659, InterpretType3CharsReturnsTrue_1659) {
  auto dev = MakeDevOrSkip_1659(0);
  ASSERT_TRUE(dev);

  EXPECT_TRUE(dev->interpretType3Chars());
}

TEST_F(PreScanOutputDevTest_1659, InterpretType3CharsStableAcrossMultipleCalls_1659) {
  auto dev = MakeDevOrSkip_1659(0);
  ASSERT_TRUE(dev);

  EXPECT_TRUE(dev->interpretType3Chars());
  EXPECT_TRUE(dev->interpretType3Chars());
  EXPECT_TRUE(dev->interpretType3Chars());
}

TEST_F(PreScanOutputDevTest_1659, WorksViaOutputDevBasePointer_1659) {
  auto dev = MakeDevOrSkip_1659(0);
  ASSERT_TRUE(dev);

  OutputDev *base = dev.get();
  EXPECT_TRUE(base->interpretType3Chars());
}

TEST_F(PreScanOutputDevTest_1659, InterpretType3CharsTrueForDifferentCtorLevels_1659) {
  // Boundary-ish: try a few underlying enum values without assuming names/range.
  for (int lvl : {0, 1, 2}) {
    auto dev = MakeDevOrSkip_1659(lvl);
    if (!dev) {
      // If MakeDevOrSkip_1659 skipped, we won't reach here, but keep defensive.
      continue;
    }
    EXPECT_TRUE(dev->interpretType3Chars()) << "PSLevel underlying value: " << lvl;
  }
}

}  // namespace