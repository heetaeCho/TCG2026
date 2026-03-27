// SPDX-License-Identifier: GPL-2.0-or-later
// File: annottext_getopen_unittest_806.cpp

#include <gtest/gtest.h>

#include <memory>

#include "Annot.h"  // ./TestProjects/poppler/poppler/Annot.h

namespace {

class AnnotTextTest_806 : public ::testing::Test {
protected:
  // Best-effort minimal constructor helper.
  // Many Poppler annotation ctors take (PDFDoc*, PDFRectangle*). In numerous builds, the
  // doc pointer is stored/used later; these tests only exercise setOpen/getOpen.
  static std::unique_ptr<AnnotText> MakeAnnotText(PDFDoc* doc) {
    auto rect = std::make_unique<PDFRectangle>();
    // Common PDFRectangle field names in Poppler.
    rect->x1 = 0;
    rect->y1 = 0;
    rect->x2 = 10;
    rect->y2 = 10;

    // AnnotText takes a raw pointer to rect; it is generally copied/consumed internally.
    // We keep it alive for the duration of construction to be safe.
    auto annot = std::make_unique<AnnotText>(doc, rect.get());
    return annot;
  }
};

TEST_F(AnnotTextTest_806, SetOpenTrueThenGetOpenReturnsTrue_806) {
  auto annot = MakeAnnotText(nullptr);

  annot->setOpen(true);

  EXPECT_TRUE(annot->getOpen());
}

TEST_F(AnnotTextTest_806, SetOpenFalseThenGetOpenReturnsFalse_806) {
  auto annot = MakeAnnotText(nullptr);

  annot->setOpen(false);

  EXPECT_FALSE(annot->getOpen());
}

TEST_F(AnnotTextTest_806, ToggleOpenMultipleTimesTracksLatestValue_806) {
  auto annot = MakeAnnotText(nullptr);

  annot->setOpen(true);
  EXPECT_TRUE(annot->getOpen());

  annot->setOpen(false);
  EXPECT_FALSE(annot->getOpen());

  annot->setOpen(true);
  EXPECT_TRUE(annot->getOpen());
}

TEST_F(AnnotTextTest_806, SetOpenIdempotentTrueDoesNotFlipState_806) {
  auto annot = MakeAnnotText(nullptr);

  annot->setOpen(true);
  EXPECT_TRUE(annot->getOpen());

  annot->setOpen(true);
  EXPECT_TRUE(annot->getOpen());
}

TEST_F(AnnotTextTest_806, GetOpenWorksOnConstReference_806) {
  auto annot = MakeAnnotText(nullptr);

  annot->setOpen(true);

  const AnnotText& cref = *annot;
  EXPECT_TRUE(cref.getOpen());
}

}  // namespace