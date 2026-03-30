// TEST_ID: 516
//
// Unit tests for GfxFunctionShading::getNFuncs()
// File: ./TestProjects/poppler/poppler/GfxState.h

#include <gtest/gtest.h>

#include <array>
#include <memory>

#include "poppler/GfxState.h"

namespace {

class GfxFunctionShadingTest_516 : public ::testing::Test {
protected:
  static std::array<double, 6> IdentityMatrix() {
    // [ a b c d e f ] = identity
    return {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
  }
};

TEST_F(GfxFunctionShadingTest_516, GetNFuncsZero_516) {
  const auto m = IdentityMatrix();

  // Use the ctor overload that takes an int&& (no need to create Function objects).
  int n = 0;
  GfxFunctionShading shading(0.0, 0.0, 1.0, 1.0, m, std::move(n));

  EXPECT_EQ(shading.getNFuncs(), 0);
}

TEST_F(GfxFunctionShadingTest_516, GetNFuncsOne_516) {
  const auto m = IdentityMatrix();

  int n = 1;
  GfxFunctionShading shading(0.0, 0.0, 10.0, 10.0, m, std::move(n));

  EXPECT_EQ(shading.getNFuncs(), 1);
}

TEST_F(GfxFunctionShadingTest_516, GetNFuncsLargerValue_516) {
  const auto m = IdentityMatrix();

  int n = 128;
  GfxFunctionShading shading(-5.0, -7.0, 5.0, 7.0, m, std::move(n));

  EXPECT_EQ(shading.getNFuncs(), 128);
}

TEST_F(GfxFunctionShadingTest_516, GetNFuncsIsConstCallable_516) {
  const auto m = IdentityMatrix();

  int n = 3;
  const GfxFunctionShading shading(0.0, 0.0, 2.0, 2.0, m, std::move(n));

  EXPECT_EQ(shading.getNFuncs(), 3);
}

TEST_F(GfxFunctionShadingTest_516, CopyConstructorPreservesNFuncs_516) {
  const auto m = IdentityMatrix();

  int n = 7;
  GfxFunctionShading original(0.0, 0.0, 3.0, 3.0, m, std::move(n));

  GfxFunctionShading copied(&original);

  EXPECT_EQ(original.getNFuncs(), 7);
  EXPECT_EQ(copied.getNFuncs(), original.getNFuncs());
}

TEST_F(GfxFunctionShadingTest_516, CopyVirtualPreservesNFuncsAndType_516) {
  const auto m = IdentityMatrix();

  int n = 5;
  GfxFunctionShading original(0.0, 0.0, 4.0, 4.0, m, std::move(n));

  // copy() returns std::unique_ptr<GfxShading> (polymorphic copy)
  std::unique_ptr<GfxShading> baseCopy;
  ASSERT_NO_THROW(baseCopy = original.copy());
  ASSERT_NE(baseCopy, nullptr);

  // Verify we got a GfxFunctionShading back (observable via RTTI) and N funcs matches.
  auto *derivedCopy = dynamic_cast<GfxFunctionShading *>(baseCopy.get());
  ASSERT_NE(derivedCopy, nullptr);

  EXPECT_EQ(derivedCopy->getNFuncs(), original.getNFuncs());
}

TEST_F(GfxFunctionShadingTest_516, NegativeCtorCountDoesNotProduceNegativeGetNFuncs_516) {
  const auto m = IdentityMatrix();

  int n = -1;
  GfxFunctionShading shading(0.0, 0.0, 1.0, 1.0, m, std::move(n));

  // We don't assume how negatives are handled, but the observable count should not be negative.
  EXPECT_GE(shading.getNFuncs(), 0);
}

} // namespace