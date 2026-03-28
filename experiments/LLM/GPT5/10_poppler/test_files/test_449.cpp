// -*- mode: c++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2; -*-
// File: gfxlabcolorspace_getwhitex_unittest_449.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <memory>

#include "poppler/GfxState.h"

namespace {

class GfxLabColorSpaceTest_449 : public ::testing::Test {};

TEST_F(GfxLabColorSpaceTest_449, ConstructionAndGetterDoesNotCrash_449)
{
  GfxLabColorSpace cs;

  // Observable behavior: callable getter returning a double.
  const double x = cs.getWhiteX();
  (void)x;

  // Basic sanity: returned value is a finite double (not NaN/Inf).
  EXPECT_TRUE(std::isfinite(x));
}

TEST_F(GfxLabColorSpaceTest_449, GetterIsStableAcrossCalls_449)
{
  GfxLabColorSpace cs;

  const double x1 = cs.getWhiteX();
  const double x2 = cs.getWhiteX();
  const double x3 = cs.getWhiteX();

  // Getter should be non-mutating/consistent for the same object.
  EXPECT_DOUBLE_EQ(x1, x2);
  EXPECT_DOUBLE_EQ(x2, x3);
}

TEST_F(GfxLabColorSpaceTest_449, GetterWorksOnConstObject_449)
{
  const GfxLabColorSpace cs;

  const double x1 = cs.getWhiteX();
  const double x2 = cs.getWhiteX();

  EXPECT_TRUE(std::isfinite(x1));
  EXPECT_DOUBLE_EQ(x1, x2);
}

TEST_F(GfxLabColorSpaceTest_449, CopyPreservesWhiteX_449)
{
  GfxLabColorSpace cs;
  const double x = cs.getWhiteX();

  std::unique_ptr<GfxColorSpace> copied = cs.copy();
  ASSERT_NE(copied, nullptr);

  // Verify we got a distinct object.
  EXPECT_NE(copied.get(), static_cast<GfxColorSpace *>(&cs));

  // Verify observable behavior is preserved through the public interface.
  // (We avoid assuming *how* copy() is implemented.)
  auto *copiedLab = dynamic_cast<GfxLabColorSpace *>(copied.get());
  ASSERT_NE(copiedLab, nullptr);

  EXPECT_DOUBLE_EQ(copiedLab->getWhiteX(), x);
  EXPECT_TRUE(std::isfinite(copiedLab->getWhiteX()));
}

} // namespace