// === UNIT TESTS for CairoOutputDev::setType3RenderType (TEST_ID: 1732) ===
//
// File: CairoOutputDev_setType3RenderType_test_1732.cpp

#include <gtest/gtest.h>

#include <limits>

#include "CairoOutputDev.h"

namespace {

class CairoOutputDevSetType3RenderTypeTest_1732 : public ::testing::Test {
protected:
  CairoOutputDev dev;
};

TEST_F(CairoOutputDevSetType3RenderTypeTest_1732, SetType3RenderType_AcceptsZeroAndOne_1732)
{
  // Normal operation: accepts typical small enum-like values.
  EXPECT_NO_THROW(dev.setType3RenderType(static_cast<Type3RenderType>(0)));
  EXPECT_NO_THROW(dev.setType3RenderType(static_cast<Type3RenderType>(1)));

  // Calling multiple times should be safe (idempotency not asserted; only that it is callable).
  EXPECT_NO_THROW(dev.setType3RenderType(static_cast<Type3RenderType>(0)));
}

TEST_F(CairoOutputDevSetType3RenderTypeTest_1732, SetType3RenderType_AcceptsNegativeValue_1732)
{
  // Boundary / robustness: enum may be signed or accept casted values.
  EXPECT_NO_THROW(dev.setType3RenderType(static_cast<Type3RenderType>(-1)));
}

TEST_F(CairoOutputDevSetType3RenderTypeTest_1732, SetType3RenderType_AcceptsIntMinAndIntMax_1732)
{
  // Boundary conditions: extreme casted values should not crash.
  EXPECT_NO_THROW(dev.setType3RenderType(
      static_cast<Type3RenderType>(std::numeric_limits<int>::min())));
  EXPECT_NO_THROW(dev.setType3RenderType(
      static_cast<Type3RenderType>(std::numeric_limits<int>::max())));
}

TEST_F(CairoOutputDevSetType3RenderTypeTest_1732, SetType3RenderType_RepeatedRapidChanges_1732)
{
  // Normal/robustness: repeated updates should remain callable.
  for (int i = 0; i < 100; ++i) {
    EXPECT_NO_THROW(dev.setType3RenderType(static_cast<Type3RenderType>(i)));
  }
}

} // namespace