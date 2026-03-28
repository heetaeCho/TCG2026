//===----------------------------------------------------------------------===//
// CairoImageOutputDev_upsideDown_1738_test.cc
// Unit tests for CairoImageOutputDev::upsideDown (TEST_ID: 1738)
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>

#include <memory>

#include "CairoOutputDev.h"

// NOTE: These tests treat the implementation as a black box and only verify
// observable behavior via the public interface.

namespace {

class CairoImageOutputDevTest_1738 : public ::testing::Test {};

TEST_F(CairoImageOutputDevTest_1738, UpsideDownReturnsTrue_1738) {
  CairoImageOutputDev dev;
  EXPECT_TRUE(dev.upsideDown());
}

TEST_F(CairoImageOutputDevTest_1738, UpsideDownIsStableAcrossRepeatedCalls_1738) {
  CairoImageOutputDev dev;
  EXPECT_TRUE(dev.upsideDown());
  EXPECT_TRUE(dev.upsideDown());
  EXPECT_TRUE(dev.upsideDown());
}

TEST_F(CairoImageOutputDevTest_1738, UpsideDownReturnsTrueForMultipleInstances_1738) {
  CairoImageOutputDev dev1;
  CairoImageOutputDev dev2;

  EXPECT_TRUE(dev1.upsideDown());
  EXPECT_TRUE(dev2.upsideDown());
}

TEST_F(CairoImageOutputDevTest_1738, UpsideDownViaBasePointerReturnsTrue_1738) {
  // Verifies the override is observable through the base interface.
  std::unique_ptr<CairoOutputDev> base = std::make_unique<CairoImageOutputDev>();
  ASSERT_NE(base, nullptr);
  EXPECT_TRUE(base->upsideDown());
}

}  // namespace