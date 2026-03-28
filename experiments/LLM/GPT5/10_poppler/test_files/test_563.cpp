// TEST_ID: 563
// File: gfxstate_copy_tests_563.cpp

#include <gtest/gtest.h>

#include <array>
#include <cmath>
#include <cstring>
#include <memory>

#if __has_include("poppler/GfxState.h")
#include "poppler/GfxState.h"
#else
#include "GfxState.h"
#endif

// Try to pull in PDFRectangle if it's not already available via GfxState.h.
#if __has_include("poppler/PDFDoc.h")
#include "poppler/PDFDoc.h"
#elif __has_include("PDFDoc.h")
#include "PDFDoc.h"
#elif __has_include("poppler/Page.h")
#include "poppler/Page.h"
#elif __has_include("Page.h")
#include "Page.h"
#endif

namespace {

static PDFRectangle MakePageBox() {
  // Poppler commonly supports aggregate init for PDFRectangle.
  // If PDFRectangle isn't an aggregate, this still typically works via a matching ctor.
  return PDFRectangle{0.0, 0.0, 612.0, 792.0};
}

static std::unique_ptr<GfxState> MakeState(double hDPI = 72.0,
                                           double vDPI = 72.0,
                                           int rotate = 0,
                                           bool upsideDown = false) {
  static PDFRectangle box = MakePageBox();
  return std::unique_ptr<GfxState>(new GfxState(hDPI, vDPI, &box, rotate, upsideDown));
}

static void ExpectArrayNear(const std::array<double, 6> &a,
                            const std::array<double, 6> &b,
                            double eps = 1e-12) {
  for (size_t i = 0; i < a.size(); ++i) {
    EXPECT_NEAR(a[i], b[i], eps) << "index=" << i;
  }
}

class GfxStateCopyTest_563 : public ::testing::Test {};

} // namespace

TEST_F(GfxStateCopyTest_563, CopyReturnsNewObjectPointer_563) {
  auto st = MakeState();
  ASSERT_NE(st, nullptr);

  std::unique_ptr<GfxState> copy(st->copy());
  ASSERT_NE(copy, nullptr);
  EXPECT_NE(copy.get(), st.get());
}

TEST_F(GfxStateCopyTest_563, CopyPreservesObservableGetters_563) {
  auto st = MakeState(96.0, 110.0, 90, true);
  ASSERT_NE(st, nullptr);

  st->setCTM(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
  st->setLineWidth(2.5);
  st->setFillOpacity(0.25);
  st->setStrokeOpacity(0.75);
  st->setFillOverprint(true);
  st->setStrokeOverprint(false);
  st->setOverprintMode(2);
  st->setFlatness(7);
  st->setMiterLimit(11.0);
  st->setStrokeAdjust(true);
  st->setAlphaIsShape(true);
  st->setTextKnockout(false);
  st->setCharSpace(1.25);
  st->setWordSpace(2.5);
  st->setHorizScaling(0.8);
  st->setLeading(9.0);
  st->setRise(3.0);
  st->setRender(1);
  st->setTextMat(10.0, 0.0, 0.0, 20.0, 30.0, 40.0);

  const char *intent = "RelativeColorimetric";
  st->setRenderingIntent(intent);

  // Create a small path to ensure copy() works with existing path state too.
  st->moveTo(1.0, 2.0);
  st->lineTo(3.0, 4.0);

  std::unique_ptr<GfxState> cp(st->copy(/*copyPath=*/false));
  ASSERT_NE(cp, nullptr);
  EXPECT_NE(cp.get(), st.get());

  EXPECT_DOUBLE_EQ(cp->getHDPI(), st->getHDPI());
  EXPECT_DOUBLE_EQ(cp->getVDPI(), st->getVDPI());
  EXPECT_EQ(cp->getRotate(), st->getRotate());

  ExpectArrayNear(cp->getCTM(), st->getCTM());
  ExpectArrayNear(cp->getTextMat(), st->getTextMat());

  EXPECT_DOUBLE_EQ(cp->getLineWidth(), st->getLineWidth());
  EXPECT_DOUBLE_EQ(cp->getFillOpacity(), st->getFillOpacity());
  EXPECT_DOUBLE_EQ(cp->getStrokeOpacity(), st->getStrokeOpacity());
  EXPECT_EQ(cp->getFillOverprint(), st->getFillOverprint());
  EXPECT_EQ(cp->getStrokeOverprint(), st->getStrokeOverprint());
  EXPECT_EQ(cp->getOverprintMode(), st->getOverprintMode());

  EXPECT_EQ(cp->getFlatness(), st->getFlatness());
  EXPECT_DOUBLE_EQ(cp->getMiterLimit(), st->getMiterLimit());
  EXPECT_EQ(cp->getStrokeAdjust(), st->getStrokeAdjust());
  EXPECT_EQ(cp->getAlphaIsShape(), st->getAlphaIsShape());
  EXPECT_EQ(cp->getTextKnockout(), st->getTextKnockout());

  EXPECT_DOUBLE_EQ(cp->getCharSpace(), st->getCharSpace());
  EXPECT_DOUBLE_EQ(cp->getWordSpace(), st->getWordSpace());
  EXPECT_DOUBLE_EQ(cp->getHorizScaling(), st->getHorizScaling());
  EXPECT_DOUBLE_EQ(cp->getLeading(), st->getLeading());
  EXPECT_DOUBLE_EQ(cp->getRise(), st->getRise());
  EXPECT_EQ(cp->getRender(), st->getRender());

  ASSERT_NE(cp->getRenderingIntent(), nullptr);
  ASSERT_NE(st->getRenderingIntent(), nullptr);
  EXPECT_STREQ(cp->getRenderingIntent(), st->getRenderingIntent());
}

TEST_F(GfxStateCopyTest_563, CopyIsIndependentFromOriginalAfterOriginalMutation_563) {
  auto st = MakeState();
  ASSERT_NE(st, nullptr);

  st->setCTM(1.0, 0.0, 0.0, 1.0, 10.0, 20.0);
  st->setLineWidth(3.0);
  st->setFillOpacity(0.4);
  st->setRenderingIntent("Perceptual");

  std::unique_ptr<GfxState> cp(st->copy());
  ASSERT_NE(cp, nullptr);

  // Mutate original after copy and verify copy remains with the previous observable values.
  st->setCTM(2.0, 0.0, 0.0, 2.0, 100.0, 200.0);
  st->setLineWidth(9.5);
  st->setFillOpacity(0.9);
  st->setRenderingIntent("Saturation");

  // Copy should still have the old values.
  ExpectArrayNear(cp->getCTM(), std::array<double, 6>{1.0, 0.0, 0.0, 1.0, 10.0, 20.0});
  EXPECT_DOUBLE_EQ(cp->getLineWidth(), 3.0);
  EXPECT_DOUBLE_EQ(cp->getFillOpacity(), 0.4);
  ASSERT_NE(cp->getRenderingIntent(), nullptr);
  EXPECT_STREQ(cp->getRenderingIntent(), "Perceptual");
}

TEST_F(GfxStateCopyTest_563, CopyIsIndependentFromOriginalAfterCopyMutation_563) {
  auto st = MakeState();
  ASSERT_NE(st, nullptr);

  st->setLineWidth(1.0);
  st->setStrokeOpacity(0.2);

  std::unique_ptr<GfxState> cp(st->copy());
  ASSERT_NE(cp, nullptr);

  // Mutate copy and verify original is unchanged (observable via getters).
  cp->setLineWidth(8.0);
  cp->setStrokeOpacity(0.85);

  EXPECT_DOUBLE_EQ(st->getLineWidth(), 1.0);
  EXPECT_DOUBLE_EQ(st->getStrokeOpacity(), 0.2);
}

TEST_F(GfxStateCopyTest_563, CopyWithCopyPathTrueAndFalseDoesNotCrashAndReturnsDistinctObjects_563) {
  auto st = MakeState();
  ASSERT_NE(st, nullptr);

  // Establish a path state (observable via isPath()).
  st->moveTo(0.0, 0.0);
  st->lineTo(10.0, 10.0);
  const bool origHasPath = st->isPath();

  std::unique_ptr<GfxState> cpFalse(st->copy(false));
  std::unique_ptr<GfxState> cpTrue(st->copy(true));

  ASSERT_NE(cpFalse, nullptr);
  ASSERT_NE(cpTrue, nullptr);

  EXPECT_NE(cpFalse.get(), st.get());
  EXPECT_NE(cpTrue.get(), st.get());
  EXPECT_NE(cpFalse.get(), cpTrue.get());

  // We don't assume what copyPath changes internally; we only validate both copies are valid
  // and maintain a reasonable, observable invariant: the original is unchanged.
  EXPECT_EQ(st->isPath(), origHasPath);
}

TEST_F(GfxStateCopyTest_563, CopyWithCopyPathTrueWhenNoPathStillWorks_563) {
  auto st = MakeState();
  ASSERT_NE(st, nullptr);

  // Ensure no path (as observable).
  st->clearPath();
  const bool origHasPath = st->isPath();

  std::unique_ptr<GfxState> cp(st->copy(true));
  ASSERT_NE(cp, nullptr);
  EXPECT_NE(cp.get(), st.get());

  // Original unchanged.
  EXPECT_EQ(st->isPath(), origHasPath);
}