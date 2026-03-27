// TEST_ID: 488
#include <gtest/gtest.h>

#include <memory>
#include <type_traits>

#if __has_include("poppler/GfxState.h")
#include "poppler/GfxState.h"
#elif __has_include("GfxState.h")
#include "GfxState.h"
#else
#error "Cannot find GfxState.h (tried <poppler/GfxState.h> and <GfxState.h>)"
#endif

namespace {

class GfxPatternColorSpaceTest_488 : public ::testing::Test {};

TEST_F(GfxPatternColorSpaceTest_488, ConstructWithNullUnder_GetUnderNullAndNCompsZero_488) {
  std::unique_ptr<GfxColorSpace> under;
  GfxPatternColorSpace cs(std::move(under));

  EXPECT_EQ(cs.getUnder(), nullptr);
  EXPECT_EQ(cs.getNComps(), 0);
}

TEST_F(GfxPatternColorSpaceTest_488, GetNComps_IsStableAcrossCalls_488) {
  std::unique_ptr<GfxColorSpace> under;
  GfxPatternColorSpace cs(std::move(under));

  const int n1 = cs.getNComps();
  const int n2 = cs.getNComps();
  const int n3 = cs.getNComps();

  EXPECT_EQ(n1, n2);
  EXPECT_EQ(n2, n3);
  EXPECT_EQ(n1, 0);
}

TEST_F(GfxPatternColorSpaceTest_488, Copy_ReturnsNonNullAndPreservesNComps_488) {
  std::unique_ptr<GfxColorSpace> under;
  GfxPatternColorSpace cs(std::move(under));

  auto copied = cs.copy();
  ASSERT_NE(copied, nullptr);

  // Observable behavior through the base interface.
  EXPECT_EQ(copied->getNComps(), 0);
}

TEST_F(GfxPatternColorSpaceTest_488, Copy_CreatesDistinctObjects_488) {
  std::unique_ptr<GfxColorSpace> under;
  GfxPatternColorSpace cs(std::move(under));

  auto c1 = cs.copy();
  auto c2 = cs.copy();

  ASSERT_NE(c1, nullptr);
  ASSERT_NE(c2, nullptr);
  EXPECT_NE(c1.get(), c2.get());

  EXPECT_EQ(c1->getNComps(), 0);
  EXPECT_EQ(c2->getNComps(), 0);
}

}  // namespace