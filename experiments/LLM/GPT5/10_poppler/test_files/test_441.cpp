// GfxCalRGBColorSpace_getMatrix_441_test.cpp

#include <gtest/gtest.h>

#include <array>
#include <type_traits>
#include <utility>

#include "GfxState.h" // from ./TestProjects/poppler/poppler/GfxState.h

namespace {

class GfxCalRGBColorSpaceTest_441 : public ::testing::Test {};

TEST_F(GfxCalRGBColorSpaceTest_441, ReturnTypeIsConstArrayRef_441) {
  using ReturnT = decltype(std::declval<const GfxCalRGBColorSpace&>().getMatrix());
  static_assert(std::is_same_v<ReturnT, const std::array<double, 9>&>,
                "getMatrix() must return const std::array<double,9>&");
  SUCCEED();
}

TEST_F(GfxCalRGBColorSpaceTest_441, ReturnsStableReferenceAcrossCalls_441) {
  GfxCalRGBColorSpace cs;

  const auto& m1 = cs.getMatrix();
  const auto& m2 = cs.getMatrix();

  EXPECT_EQ(&m1, &m2);
  EXPECT_EQ(m1.data(), m2.data());
}

TEST_F(GfxCalRGBColorSpaceTest_441, MatrixHasNineElements_441) {
  GfxCalRGBColorSpace cs;
  const auto& m = cs.getMatrix();

  EXPECT_EQ(m.size(), 9u);
}

TEST_F(GfxCalRGBColorSpaceTest_441, ElementAddressesMatchAcrossReferences_441) {
  GfxCalRGBColorSpace cs;

  const auto& m1 = cs.getMatrix();
  const auto& m2 = cs.getMatrix();

  // Verifies the returned reference refers to the same underlying storage.
  EXPECT_EQ(&m1[0], &m2[0]);
  EXPECT_EQ(&m1[8], &m2[8]);
}

}  // namespace