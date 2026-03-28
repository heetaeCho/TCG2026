// GfxShadingPattern_getMatrix_501_test.cpp
#include <gtest/gtest.h>

#include <array>
#include <memory>

#include "poppler/GfxState.h"
#include "poppler/Object.h"

namespace {

class GfxShadingPatternTest_501 : public ::testing::Test {
protected:
  // Helper: attempt to parse with "obviously invalid" inputs.
  static std::unique_ptr<GfxShadingPattern> TryParseWithNulls(int patternRefNum) {
    Object patObj;
    patObj.initNull();
    return GfxShadingPattern::parse(/*res=*/nullptr, &patObj,
                                    /*out=*/nullptr, /*state=*/nullptr,
                                    patternRefNum);
  }
};

TEST_F(GfxShadingPatternTest_501, ParseWithNullPatternObjectYieldsNullOrNoCrash_501) {
  // Boundary / error-ish: null pattern object.
  // Observable behavior: parse either returns nullptr or a valid object; both are acceptable
  // for this test as long as it does not crash.
  auto pat = TryParseWithNulls(/*patternRefNum=*/1);

  // Most implementations are expected to reject a null object; if not, we still validate
  // we can safely call getMatrix().
  if (!pat) {
    SUCCEED();
    return;
  }

  const auto &m = pat->getMatrix();
  EXPECT_EQ(m.size(), 6u);
}

TEST_F(GfxShadingPatternTest_501, ParseWithVariousPatternRefNumsDoesNotCrash_501) {
  // Boundary conditions for patternRefNum: negative, zero, positive.
  // We intentionally avoid asserting success/failure; only that calls are safe.
  for (int refNum : {-1, 0, 1, 42}) {
    auto pat = TryParseWithNulls(refNum);
    if (pat) {
      const auto &m = pat->getMatrix();
      EXPECT_EQ(m.size(), 6u);
    }
  }
}

TEST_F(GfxShadingPatternTest_501, GetMatrixReturnsStableConstReferenceIfInstanceAvailable_501) {
  // "Normal operation" when an instance can be produced by parse in this build/runtime.
  // If parse cannot create an instance from the minimal inputs, we skip rather than fail.
  auto pat = TryParseWithNulls(/*patternRefNum=*/1);
  if (!pat) {
    GTEST_SKIP() << "Could not obtain a GfxShadingPattern instance via parse() with minimal inputs.";
  }

  const std::array<double, 6> &m1 = pat->getMatrix();
  const std::array<double, 6> &m2 = pat->getMatrix();

  // Observable contract: returns a const reference; repeated calls should reference the same object.
  EXPECT_EQ(&m1, &m2);
  EXPECT_EQ(m1.size(), 6u);

  // Also validate the returned data is self-consistent (copy equals original).
  const auto copy = m1;
  EXPECT_EQ(copy, m2);
}

} // namespace