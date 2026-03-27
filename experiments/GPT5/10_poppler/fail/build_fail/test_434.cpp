// TEST_ID: 434
#include <gtest/gtest.h>

#include "poppler/GfxState.h"

namespace {

class GfxCalRGBColorSpaceTest_434 : public ::testing::Test {};

TEST_F(GfxCalRGBColorSpaceTest_434, DefaultConstruction_AllowsGetWhiteZ_434) {
  GfxCalRGBColorSpace cs;

  // Observable behavior: callable and returns a double consistently.
  const double z1 = cs.getWhiteZ();
  const double z2 = cs.getWhiteZ();

  EXPECT_EQ(z1, z2);
}

TEST_F(GfxCalRGBColorSpaceTest_434, Copy_ReturnsSameConcreteType_434) {
  GfxCalRGBColorSpace cs;

  std::unique_ptr<GfxColorSpace> copyBase = cs.copy();
  ASSERT_NE(copyBase, nullptr);

  // Observable behavior: copy() should preserve dynamic type for a "copy" operation.
  auto *copyDerived = dynamic_cast<GfxCalRGBColorSpace *>(copyBase.get());
  ASSERT_NE(copyDerived, nullptr);
}

TEST_F(GfxCalRGBColorSpaceTest_434, Copy_PreservesWhiteZValue_434) {
  GfxCalRGBColorSpace cs;

  const double originalZ = cs.getWhiteZ();

  std::unique_ptr<GfxColorSpace> copyBase = cs.copy();
  ASSERT_NE(copyBase, nullptr);

  auto *copyDerived = dynamic_cast<GfxCalRGBColorSpace *>(copyBase.get());
  ASSERT_NE(copyDerived, nullptr);

  const double copiedZ = copyDerived->getWhiteZ();
  EXPECT_EQ(copiedZ, originalZ);
  EXPECT_EQ(copyDerived->getWhiteZ(), copyDerived->getWhiteZ());  // stable across calls
}

}  // namespace