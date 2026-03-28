// File: page_getmediawidth_unittest_706.cpp
#include <gtest/gtest.h>

#include <memory>

// Poppler headers (as provided by the project)
#include "Page.h"
#include "PDFRectangle.h"

// These are typical Poppler core types used to build dictionaries/objects for PageAttrs.
// If your local Poppler tree exposes them from different headers, adjust includes accordingly.
#include "Object.h"
#include "Dict.h"
#include "Array.h"
#include "XRef.h"

namespace {

class PageGetMediaWidthTest_706 : public ::testing::Test {
protected:
  // Build a Dict with a /MediaBox [x1 y1 x2 y2]
  static std::unique_ptr<Dict> MakeDictWithMediaBox(double x1, double y1, double x2, double y2) {
    // Dict/Array commonly take an XRef* in Poppler; nullptr is usually acceptable for unit tests
    // that don't resolve indirect objects.
    auto dict = std::make_unique<Dict>(static_cast<XRef *>(nullptr));

    auto *arr = new Array(static_cast<XRef *>(nullptr));
    {
      Object o1;
      o1.initReal(x1);
      arr->add(std::move(o1));

      Object o2;
      o2.initReal(y1);
      arr->add(std::move(o2));

      Object o3;
      o3.initReal(x2);
      arr->add(std::move(o3));

      Object o4;
      o4.initReal(y2);
      arr->add(std::move(o4));
    }

    Object mediaBoxObj;
    mediaBoxObj.initArray(arr);
    dict->add("MediaBox", std::move(mediaBoxObj));

    return dict;
  }

  static std::unique_ptr<Dict> MakeDictWithMediaAndCropBoxes(double mx1,
                                                             double my1,
                                                             double mx2,
                                                             double my2,
                                                             double cx1,
                                                             double cy1,
                                                             double cx2,
                                                             double cy2) {
    auto dict = MakeDictWithMediaBox(mx1, my1, mx2, my2);

    auto *cropArr = new Array(static_cast<XRef *>(nullptr));
    {
      Object o1;
      o1.initReal(cx1);
      cropArr->add(std::move(o1));

      Object o2;
      o2.initReal(cy1);
      cropArr->add(std::move(o2));

      Object o3;
      o3.initReal(cx2);
      cropArr->add(std::move(o3));

      Object o4;
      o4.initReal(cy2);
      cropArr->add(std::move(o4));
    }

    Object cropBoxObj;
    cropBoxObj.initArray(cropArr);
    dict->add("CropBox", std::move(cropBoxObj));

    return dict;
  }

  static std::unique_ptr<Page> MakePageWithAttrs(std::unique_ptr<PageAttrs> attrs) {
    // Keep pageDict minimal; getMediaWidth() is expected to use attrs->getMediaBox().
    Object pageDictObj;
    pageDictObj.initDict(new Dict(static_cast<XRef *>(nullptr)));

    Ref ref;
    ref.num = 1;
    ref.gen = 0;

    // PDFDoc is not used by getMediaWidth(). Many Poppler builds tolerate nullptr here in tests.
    PDFDoc *doc = nullptr;

    return std::make_unique<Page>(doc, /*numA=*/1, std::move(pageDictObj), ref, std::move(attrs));
  }

  static std::unique_ptr<Page> MakePageWithMediaBox(double x1, double y1, double x2, double y2) {
    auto dict = MakeDictWithMediaBox(x1, y1, x2, y2);
    auto attrs = std::make_unique<PageAttrs>(/*attrs=*/nullptr, dict.get());
    return MakePageWithAttrs(std::move(attrs));
  }
};

TEST_F(PageGetMediaWidthTest_706, ReturnsDifferenceX2MinusX1_Normal_706) {
  auto page = MakePageWithMediaBox(/*x1=*/10.0, /*y1=*/0.0, /*x2=*/210.0, /*y2=*/300.0);
  EXPECT_DOUBLE_EQ(page->getMediaWidth(), 200.0);
}

TEST_F(PageGetMediaWidthTest_706, ReturnsZeroWhenX1EqualsX2_Boundary_706) {
  auto page = MakePageWithMediaBox(/*x1=*/42.5, /*y1=*/0.0, /*x2=*/42.5, /*y2=*/100.0);
  EXPECT_DOUBLE_EQ(page->getMediaWidth(), 0.0);
}

TEST_F(PageGetMediaWidthTest_706, AllowsNegativeWidthWhenX2LessThanX1_Boundary_706) {
  auto page = MakePageWithMediaBox(/*x1=*/100.0, /*y1=*/0.0, /*x2=*/25.0, /*y2=*/50.0);
  EXPECT_DOUBLE_EQ(page->getMediaWidth(), -75.0);
}

TEST_F(PageGetMediaWidthTest_706, UsesMediaBoxNotCropBox_WhenTheyDiffer_706) {
  auto dict = MakeDictWithMediaAndCropBoxes(
      /*media*/ 0.0, 0.0, 200.0, 200.0,
      /*crop */ 0.0, 0.0, 123.0, 200.0);

  auto attrs = std::make_unique<PageAttrs>(/*attrs=*/nullptr, dict.get());
  auto page = MakePageWithAttrs(std::move(attrs));

  // getMediaWidth() should reflect MediaBox width (200), not CropBox width (123).
  EXPECT_DOUBLE_EQ(page->getMediaWidth(), 200.0);
}

TEST_F(PageGetMediaWidthTest_706, HandlesLargeCoordinateValues_Normal_706) {
  auto page = MakePageWithMediaBox(/*x1=*/-1e9, /*y1=*/0.0, /*x2=*/1e9, /*y2=*/1.0);
  EXPECT_DOUBLE_EQ(page->getMediaWidth(), 2e9);
}

TEST_F(PageGetMediaWidthTest_706, MissingMediaBox_DoesNotCrashAndReturnsFiniteValue_706) {
  // Exceptional-ish case: construct PageAttrs from an empty dict.
  // Exact fallback behavior is implementation-defined; we only assert observable safety.
  auto emptyDict = std::make_unique<Dict>(static_cast<XRef *>(nullptr));
  auto attrs = std::make_unique<PageAttrs>(/*attrs=*/nullptr, emptyDict.get());
  auto page = MakePageWithAttrs(std::move(attrs));

  const double w = page->getMediaWidth();
  EXPECT_TRUE(std::isfinite(w));
}

} // namespace