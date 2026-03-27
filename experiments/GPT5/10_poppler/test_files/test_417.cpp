// TEST_ID: 417
#include <gtest/gtest.h>

#include <cmath>
#include <memory>

#include "GfxState.h"

namespace {

class GfxCalGrayColorSpaceTest_417 : public ::testing::Test {
protected:
  static void ExpectFinite(double v) { EXPECT_TRUE(std::isfinite(v)); }
};

TEST_F(GfxCalGrayColorSpaceTest_417, DefaultConstruction_ReturnsFiniteWhiteZ_417)
{
  GfxCalGrayColorSpace cs;
  const double z = cs.getWhiteZ();
  ExpectFinite(z);
}

TEST_F(GfxCalGrayColorSpaceTest_417, ConstObject_CallWorksAndReturnsFinite_417)
{
  const GfxCalGrayColorSpace cs;
  const double z = cs.getWhiteZ();
  ExpectFinite(z);
}

TEST_F(GfxCalGrayColorSpaceTest_417, MultipleCalls_ReturnSameValue_417)
{
  GfxCalGrayColorSpace cs;

  const double z1 = cs.getWhiteZ();
  const double z2 = cs.getWhiteZ();
  const double z3 = cs.getWhiteZ();

  // Observable behavior: getter should be stable across repeated calls.
  EXPECT_DOUBLE_EQ(z1, z2);
  EXPECT_DOUBLE_EQ(z2, z3);
}

TEST_F(GfxCalGrayColorSpaceTest_417, Copy_PreservesWhiteZ_417)
{
  GfxCalGrayColorSpace cs;
  const double originalZ = cs.getWhiteZ();

  // copy() is part of the public interface (via GfxColorSpace).
  std::unique_ptr<GfxColorSpace> baseCopy = cs.copy();
  ASSERT_NE(baseCopy, nullptr);

  // Ensure the dynamic type is preserved for a CalGray color space copy.
  auto *copy = dynamic_cast<GfxCalGrayColorSpace *>(baseCopy.get());
  ASSERT_NE(copy, nullptr);

  EXPECT_DOUBLE_EQ(copy->getWhiteZ(), originalZ);
}

} // namespace