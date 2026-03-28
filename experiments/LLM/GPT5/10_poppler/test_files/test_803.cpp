// SPDX-License-Identifier: GPL-2.0-or-later
// File: AnnotMarkup_getSubject_unittest_803.cpp
//
// Unit tests for AnnotMarkup::getSubject()
// Constraints:
// - Treat implementation as black box: only assert on observable behavior via public API.
// - No private-state inspection.
// - GoogleTest only (no external collaborators to mock for this method).

#include <gtest/gtest.h>

#include "poppler/Annot.h"
#include "poppler/goo/GooString.h"

// A small test seam to *set up inputs* for getSubject().
// NOTE: We do NOT validate or depend on internal logic; we only arrange state so that
// getSubject() has something observable to return (the production interface provides
// no setter for subject).
class TestableAnnotMarkup_803 : public AnnotMarkup {
public:
  using AnnotMarkup::AnnotMarkup;

  void setSubjectForTest_803(std::unique_ptr<GooString> s) { subject = std::move(s); }
  void clearSubjectForTest_803() { subject.reset(); }
};

class AnnotMarkupTest_803 : public ::testing::Test {
protected:
  static PDFRectangle makeRect_803() {
    PDFRectangle r;
    r.x1 = 0;
    r.y1 = 0;
    r.x2 = 10;
    r.y2 = 10;
    return r;
  }
};

TEST_F(AnnotMarkupTest_803, GetSubjectReturnsNullWhenCleared_803) {
  PDFRectangle rect = makeRect_803();
  TestableAnnotMarkup_803 annot(/*docA=*/nullptr, &rect);

  annot.clearSubjectForTest_803();

  const GooString *subj = annot.getSubject();
  EXPECT_EQ(subj, nullptr);
}

TEST_F(AnnotMarkupTest_803, GetSubjectReturnsNonNullAfterSet_803) {
  PDFRectangle rect = makeRect_803();
  TestableAnnotMarkup_803 annot(/*docA=*/nullptr, &rect);

  annot.setSubjectForTest_803(std::make_unique<GooString>("Hello"));

  const GooString *subj = annot.getSubject();
  ASSERT_NE(subj, nullptr);
  EXPECT_STREQ(subj->c_str(), "Hello");
}

TEST_F(AnnotMarkupTest_803, GetSubjectWorksOnConstObject_803) {
  PDFRectangle rect = makeRect_803();
  TestableAnnotMarkup_803 annot(/*docA=*/nullptr, &rect);
  annot.setSubjectForTest_803(std::make_unique<GooString>("ConstOK"));

  const AnnotMarkup &cref = annot;
  const GooString *subj = cref.getSubject();

  ASSERT_NE(subj, nullptr);
  EXPECT_STREQ(subj->c_str(), "ConstOK");
}

TEST_F(AnnotMarkupTest_803, GetSubjectPointerIsStableAcrossCalls_803) {
  PDFRectangle rect = makeRect_803();
  TestableAnnotMarkup_803 annot(/*docA=*/nullptr, &rect);
  annot.setSubjectForTest_803(std::make_unique<GooString>("Stable"));

  const GooString *s1 = annot.getSubject();
  const GooString *s2 = annot.getSubject();

  ASSERT_NE(s1, nullptr);
  ASSERT_NE(s2, nullptr);
  EXPECT_EQ(s1, s2);
  EXPECT_STREQ(s1->c_str(), "Stable");
}

TEST_F(AnnotMarkupTest_803, GetSubjectAllowsEmptyString_803) {
  PDFRectangle rect = makeRect_803();
  TestableAnnotMarkup_803 annot(/*docA=*/nullptr, &rect);

  annot.setSubjectForTest_803(std::make_unique<GooString>(""));

  const GooString *subj = annot.getSubject();
  ASSERT_NE(subj, nullptr);
  EXPECT_STREQ(subj->c_str(), "");
}