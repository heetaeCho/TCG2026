// Page_getArtBox_712_test.cpp
#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "poppler/Page.h"

// These headers are commonly available in Poppler builds. If your build already
// includes them via Page.h, extra includes are harmless.
#include "poppler/PDFDoc.h"
#include "poppler/goo/GooString.h"

namespace {

struct RectEndpoints {
  double x1, y1, x2, y2;
};

static bool IsFiniteRect(const PDFRectangle* r) {
  if (!r) return false;
  return std::isfinite(r->x1) && std::isfinite(r->y1) && std::isfinite(r->x2) && std::isfinite(r->y2);
}

static void ExpectRectMatchesEndpointsOrderIndependent(const PDFRectangle* actual,
                                                      const RectEndpoints& expected,
                                                      double eps = 1e-9) {
  ASSERT_NE(actual, nullptr);

  const double axMin = std::min(actual->x1, actual->x2);
  const double axMax = std::max(actual->x1, actual->x2);
  const double ayMin = std::min(actual->y1, actual->y2);
  const double ayMax = std::max(actual->y1, actual->y2);

  const double exMin = std::min(expected.x1, expected.x2);
  const double exMax = std::max(expected.x1, expected.x2);
  const double eyMin = std::min(expected.y1, expected.y2);
  const double eyMax = std::max(expected.y1, expected.y2);

  EXPECT_NEAR(axMin, exMin, eps);
  EXPECT_NEAR(axMax, exMax, eps);
  EXPECT_NEAR(ayMin, eyMin, eps);
  EXPECT_NEAR(ayMax, eyMax, eps);
}

static bool RectEqualsOrderIndependent(const PDFRectangle* a, const PDFRectangle* b, double eps = 1e-9) {
  if (!a || !b) return false;
  const double axMin = std::min(a->x1, a->x2);
  const double axMax = std::max(a->x1, a->x2);
  const double ayMin = std::min(a->y1, a->y2);
  const double ayMax = std::max(a->y1, a->y2);

  const double bxMin = std::min(b->x1, b->x2);
  const double bxMax = std::max(b->x1, b->x2);
  const double byMin = std::min(b->y1, b->y2);
  const double byMax = std::max(b->y1, b->y2);

  return std::abs(axMin - bxMin) <= eps && std::abs(axMax - bxMax) <= eps &&
         std::abs(ayMin - byMin) <= eps && std::abs(ayMax - byMax) <= eps;
}

// Build a tiny single-page PDF with customizable page dictionary entries.
// This is test infrastructure; it does not re-implement any Poppler logic.
static std::string BuildSinglePagePdf(const std::string& pageDictExtras) {
  // Objects are 1-based in this builder.
  // 1: Catalog
  // 2: Pages
  // 3: Page (with extras)
  // 4: Contents (empty stream)
  std::vector<std::string> objs;
  objs.emplace_back("<< /Type /Catalog /Pages 2 0 R >>");
  objs.emplace_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");

  std::string pageObj =
      "<< /Type /Page /Parent 2 0 R "
      "/MediaBox [0 0 200 400] "
      "/Contents 4 0 R ";
  pageObj += pageDictExtras;
  pageObj += ">>";
  objs.emplace_back(pageObj);

  objs.emplace_back("<< /Length 0 >>\nstream\n\nendstream");

  std::string pdf;
  pdf += "%PDF-1.4\n";

  // Track offsets for xref.
  std::vector<std::size_t> offsets;
  offsets.reserve(objs.size() + 1);
  offsets.push_back(0);  // object 0 (free)

  for (std::size_t i = 0; i < objs.size(); ++i) {
    offsets.push_back(pdf.size());
    pdf += std::to_string(i + 1);
    pdf += " 0 obj\n";
    pdf += objs[i];
    pdf += "\nendobj\n";
  }

  const std::size_t xrefOffset = pdf.size();
  pdf += "xref\n";
  pdf += "0 ";
  pdf += std::to_string(objs.size() + 1);
  pdf += "\n";
  // object 0
  pdf += "0000000000 65535 f \n";
  for (std::size_t i = 1; i < offsets.size(); ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010u 00000 n \n", static_cast<unsigned>(offsets[i]));
    pdf += buf;
  }

  pdf += "trailer\n";
  pdf += "<< /Size ";
  pdf += std::to_string(objs.size() + 1);
  pdf += " /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xrefOffset);
  pdf += "\n%%EOF\n";

  return pdf;
}

static std::filesystem::path WriteTempFile(const std::string& content, const std::string& baseName) {
  const auto dir = std::filesystem::temp_directory_path();
  const auto path = dir / (baseName + ".pdf");
  std::ofstream os(path, std::ios::binary | std::ios::trunc);
  os.write(content.data(), static_cast<std::streamsize>(content.size()));
  os.flush();
  return path;
}

// Construct PDFDoc across Poppler API variations (SFINAE / if constexpr).
template <class... Args>
static std::unique_ptr<PDFDoc> TryMakeDoc(Args&&... args) {
  return std::make_unique<PDFDoc>(std::forward<Args>(args)...);
}

static std::unique_ptr<PDFDoc> MakePdfDocFromPath(const std::string& path) {
  // Common signatures across Poppler versions:
  //  - PDFDoc(std::unique_ptr<GooString> fileName, GooString* owner, GooString* user, void* guiData = nullptr)
  //  - PDFDoc(GooString* fileName, GooString* owner, GooString* user, void* guiData = nullptr)
  //  - PDFDoc(std::unique_ptr<GooString> fileName, const std::optional<GooString>& owner, const std::optional<GooString>& user)
  //
  // We attempt a few likely constructs using compile-time checks.
  auto gsUnique = std::make_unique<GooString>(path.c_str());

  if constexpr (std::is_constructible_v<PDFDoc, std::unique_ptr<GooString>, GooString*, GooString*, void*>) {
    return TryMakeDoc(std::move(gsUnique), static_cast<GooString*>(nullptr), static_cast<GooString*>(nullptr),
                      static_cast<void*>(nullptr));
  } else if constexpr (std::is_constructible_v<PDFDoc, std::unique_ptr<GooString>, GooString*, GooString*>) {
    return TryMakeDoc(std::move(gsUnique), static_cast<GooString*>(nullptr), static_cast<GooString*>(nullptr));
  } else {
    // Fallback: raw GooString pointer form.
    // Ownership behavior varies by version; this is used only if the unique_ptr overloads don't exist.
    GooString* raw = new GooString(path.c_str());
    if constexpr (std::is_constructible_v<PDFDoc, GooString*, GooString*, GooString*, void*>) {
      return TryMakeDoc(raw, static_cast<GooString*>(nullptr), static_cast<GooString*>(nullptr), static_cast<void*>(nullptr));
    } else if constexpr (std::is_constructible_v<PDFDoc, GooString*, GooString*, GooString*>) {
      return TryMakeDoc(raw, static_cast<GooString*>(nullptr), static_cast<GooString*>(nullptr));
    } else if constexpr (std::is_constructible_v<PDFDoc, GooString*>) {
      return TryMakeDoc(raw);
    } else {
      // If your Poppler build uses a different constructor, update this helper accordingly.
      delete raw;
      return nullptr;
    }
  }
}

class Page_GetArtBoxTest_712 : public ::testing::Test {
protected:
  static Page* GetFirstPage(PDFDoc* doc) {
    if (!doc) return nullptr;
    // Most Poppler builds provide getPage(int pageNum) with 1-based indexing.
    return doc->getPage(1);
  }
};

}  // namespace

TEST_F(Page_GetArtBoxTest_712, ReturnsRectangleWhenArtBoxPresent_712) {
  const RectEndpoints art{10, 20, 150, 300};
  const std::string extras =
      "/ArtBox [10 20 150 300] ";

  const auto pdfPath = WriteTempFile(BuildSinglePagePdf(extras), "poppler_page_artbox_present_712");
  auto doc = MakePdfDocFromPath(pdfPath.string());
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  Page* page = GetFirstPage(doc.get());
  ASSERT_NE(page, nullptr);

  const PDFRectangle* r1 = page->getArtBox();
  const PDFRectangle* r2 = page->getArtBox();

  ASSERT_TRUE(IsFiniteRect(r1));
  EXPECT_EQ(r1, r2) << "Pointer should be stable across repeated calls (observable behavior).";
  ExpectRectMatchesEndpointsOrderIndependent(r1, art);
}

TEST_F(Page_GetArtBoxTest_712, AcceptsNegativeAndReversedEndpoints_712) {
  // Boundary-ish values: negatives + reversed coordinates.
  const RectEndpoints art{-50, 400, -10, 100};  // reversed y-order (400 -> 100)
  const std::string extras =
      "/ArtBox [-50 400 -10 100] ";

  const auto pdfPath = WriteTempFile(BuildSinglePagePdf(extras), "poppler_page_artbox_negative_reversed_712");
  auto doc = MakePdfDocFromPath(pdfPath.string());
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  Page* page = GetFirstPage(doc.get());
  ASSERT_NE(page, nullptr);

  const PDFRectangle* r = page->getArtBox();
  ASSERT_TRUE(IsFiniteRect(r));

  // Compare order-independently to avoid assuming whether Poppler normalizes endpoints.
  ExpectRectMatchesEndpointsOrderIndependent(r, art);
}

TEST_F(Page_GetArtBoxTest_712, WhenArtBoxMissingReturnsSomeBoxRectangle_712) {
  // No /ArtBox entry at all.
  const auto pdfPath = WriteTempFile(BuildSinglePagePdf(/*pageDictExtras=*/""), "poppler_page_artbox_missing_712");
  auto doc = MakePdfDocFromPath(pdfPath.string());
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  Page* page = GetFirstPage(doc.get());
  ASSERT_NE(page, nullptr);

  const PDFRectangle* art = page->getArtBox();
  ASSERT_TRUE(IsFiniteRect(art));

  // Without assuming Poppler's fallback choice, verify it matches at least one of the other boxes
  // exposed by the public interface.
  const PDFRectangle* media = page->getMediaBox();
  const PDFRectangle* crop = page->getCropBox();
  const PDFRectangle* bleed = page->getBleedBox();
  const PDFRectangle* trim = page->getTrimBox();

  // All of these should be safe to call via the public interface.
  bool matchesAny =
      RectEqualsOrderIndependent(art, media) || RectEqualsOrderIndependent(art, crop) ||
      RectEqualsOrderIndependent(art, bleed) || RectEqualsOrderIndependent(art, trim);

  EXPECT_TRUE(matchesAny)
      << "getArtBox() should return a meaningful rectangle even if /ArtBox is missing; "
         "it should be consistent with at least one other box returned by the public interface.";
}

TEST_F(Page_GetArtBoxTest_712, MalformedArtBoxDoesNotCrashAndReturnsFiniteRect_712) {
  // Exceptional-ish: provide an invalid ArtBox type (string). We don't assume how Poppler recovers;
  // we only assert the call is safe and returns a finite rectangle.
  const std::string extras =
      "/ArtBox (not-an-array) ";

  const auto pdfPath = WriteTempFile(BuildSinglePagePdf(extras), "poppler_page_artbox_malformed_712");
  auto doc = MakePdfDocFromPath(pdfPath.string());
  ASSERT_NE(doc, nullptr);

  // Depending on Poppler strictness, doc may still be OK. If it's not OK, the observable outcome is that
  // we can't reliably retrieve a page; that's acceptable for this error-case test.
  if (!doc->isOk()) {
    SUCCEED() << "Document rejected as invalid (observable behavior).";
    return;
  }

  Page* page = GetFirstPage(doc.get());
  ASSERT_NE(page, nullptr);

  const PDFRectangle* art = page->getArtBox();
  EXPECT_TRUE(IsFiniteRect(art));
}

TEST_F(Page_GetArtBoxTest_712, CorruptPdfResultsInNotOkDocument_712) {
  // Create a clearly corrupt PDF (missing xref/trailer).
  const std::string corrupt = "%PDF-1.4\n1 0 obj\n<<>>\nendobj\n%%EOF\n";

  const auto pdfPath = WriteTempFile(corrupt, "poppler_page_corrupt_712");
  auto doc = MakePdfDocFromPath(pdfPath.string());
  ASSERT_NE(doc, nullptr);

  EXPECT_FALSE(doc->isOk()) << "Corrupt PDF should be reported as not OK (observable behavior).";
  // Do not call into Page APIs if the document is not OK.
}