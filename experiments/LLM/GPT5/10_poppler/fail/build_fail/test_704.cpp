// PageGetCropBoxTest_704.cpp
// Unit tests for Page::getCropBox()
// TEST_ID: 704

#include <gtest/gtest.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "poppler/PDFDoc.h"
#include "poppler/Catalog.h"
#include "poppler/Page.h"
#include "poppler/PDFRectangle.h"
#include "poppler/goo/GooString.h"

namespace {

// Writes a minimal 1-page PDF to `path`.
// - Always sets /MediaBox
// - Optionally sets /CropBox
//
// This is test data generation (not implementation logic of poppler).
static void writeMinimalPdf1Page(const std::string &path,
                                const PDFRectangle &mediaBox,
                                const std::optional<PDFRectangle> &cropBox) {
  // Helper to format a PDF rectangle array: [x1 y1 x2 y2]
  auto rectArray = [](const PDFRectangle &r) {
    std::ostringstream oss;
    oss << "[" << r.x1 << " " << r.y1 << " " << r.x2 << " " << r.y2 << "]";
    return oss.str();
  };

  std::vector<std::string> objs;
  objs.reserve(5);

  // 1 0 obj: Catalog
  objs.push_back("1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");

  // 2 0 obj: Pages
  objs.push_back("2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n");

  // 3 0 obj: Page with MediaBox and optional CropBox
  {
    std::ostringstream page;
    page << "3 0 obj\n<< /Type /Page /Parent 2 0 R "
         << "/MediaBox " << rectArray(mediaBox) << " ";
    if (cropBox.has_value()) {
      page << "/CropBox " << rectArray(*cropBox) << " ";
    }
    page << "/Contents 4 0 R >>\nendobj\n";
    objs.push_back(page.str());
  }

  // 4 0 obj: Empty content stream
  objs.push_back("4 0 obj\n<< /Length 0 >>\nstream\n\nendstream\nendobj\n");

  // Build full PDF and compute xref offsets.
  std::ostringstream pdf;
  pdf << "%PDF-1.4\n";
  std::vector<long> offsets;
  offsets.reserve(objs.size() + 1);
  offsets.push_back(0); // object 0 is special

  for (const auto &obj : objs) {
    offsets.push_back(static_cast<long>(pdf.tellp()));
    pdf << obj;
  }

  const long xrefPos = static_cast<long>(pdf.tellp());
  pdf << "xref\n";
  pdf << "0 " << (objs.size() + 1) << "\n";
  pdf << "0000000000 65535 f \n";
  for (size_t i = 1; i < offsets.size(); ++i) {
    char buf[64];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    pdf << buf;
  }
  pdf << "trailer\n";
  pdf << "<< /Size " << (objs.size() + 1) << " /Root 1 0 R >>\n";
  pdf << "startxref\n";
  pdf << xrefPos << "\n";
  pdf << "%%EOF\n";

  std::ofstream out(path, std::ios::binary);
  ASSERT_TRUE(out.good()) << "Failed to open output PDF path: " << path;
  const std::string bytes = pdf.str();
  out.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
  out.close();
  ASSERT_TRUE(out.good()) << "Failed writing PDF bytes to: " << path;
}

static std::string makeTempPath(const char *suffix) {
#if defined(_WIN32)
  // Basic fallback for environments that still expose TMP; keep simple.
  const char *tmp = std::getenv("TEMP");
  if (!tmp) tmp = std::getenv("TMP");
  if (!tmp) tmp = ".";
  std::ostringstream oss;
  oss << tmp << "\\poppler_page_getcropbox_704_" << std::rand() << suffix;
  return oss.str();
#else
  const char *tmp = std::getenv("TMPDIR");
  if (!tmp) tmp = "/tmp";
  std::ostringstream oss;
  oss << tmp << "/poppler_page_getcropbox_704_" << std::rand() << suffix;
  return oss.str();
#endif
}

static Page *loadFirstPageOrFail(PDFDoc &doc) {
  EXPECT_TRUE(doc.isOk());
  Catalog *cat = doc.getCatalog();
  EXPECT_NE(cat, nullptr);
  Page *page = cat ? cat->getPage(1) : nullptr;
  EXPECT_NE(page, nullptr);
  return page;
}

static void expectRectEq(const PDFRectangle *r,
                         double x1, double y1, double x2, double y2) {
  ASSERT_NE(r, nullptr);
  EXPECT_DOUBLE_EQ(r->x1, x1);
  EXPECT_DOUBLE_EQ(r->y1, y1);
  EXPECT_DOUBLE_EQ(r->x2, x2);
  EXPECT_DOUBLE_EQ(r->y2, y2);
}

} // namespace

class PageGetCropBoxTest_704 : public ::testing::Test {
protected:
  void TearDown() override {
    for (const auto &p : cleanupPaths_) {
      std::remove(p.c_str());
    }
    cleanupPaths_.clear();
  }

  std::string createPdf(const PDFRectangle &media, const std::optional<PDFRectangle> &crop) {
    std::string path = makeTempPath(".pdf");
    cleanupPaths_.push_back(path);
    writeMinimalPdf1Page(path, media, crop);
    return path;
  }

private:
  std::vector<std::string> cleanupPaths_;
};

TEST_F(PageGetCropBoxTest_704, CropBoxPresent_ReturnsCropBoxValues_704) {
  const PDFRectangle media{0, 0, 200, 400};
  const PDFRectangle crop{10, 20, 150, 300};
  const std::string path = createPdf(media, crop);

  GooString filename(path.c_str());
  PDFDoc doc(&filename);
  Page *page = loadFirstPageOrFail(doc);
  ASSERT_NE(page, nullptr);

  const PDFRectangle *got = page->getCropBox();
  expectRectEq(got, 10, 20, 150, 300);
}

TEST_F(PageGetCropBoxTest_704, CropBoxAbsent_ReturnsNonNullAndMatchesMediaBox_704) {
  const PDFRectangle media{0, 0, 612, 792}; // common Letter size in points
  const std::string path = createPdf(media, std::nullopt);

  GooString filename(path.c_str());
  PDFDoc doc(&filename);
  Page *page = loadFirstPageOrFail(doc);
  ASSERT_NE(page, nullptr);

  const PDFRectangle *gotCrop = page->getCropBox();
  ASSERT_NE(gotCrop, nullptr);

  const PDFRectangle *gotMedia = page->getMediaBox();
  ASSERT_NE(gotMedia, nullptr);

  // Observable behavior expectation: when /CropBox is not specified, crop box
  // should not be "missing" and should align with media box.
  EXPECT_DOUBLE_EQ(gotCrop->x1, gotMedia->x1);
  EXPECT_DOUBLE_EQ(gotCrop->y1, gotMedia->y1);
  EXPECT_DOUBLE_EQ(gotCrop->x2, gotMedia->x2);
  EXPECT_DOUBLE_EQ(gotCrop->y2, gotMedia->y2);
}

TEST_F(PageGetCropBoxTest_704, GetCropBox_IsStableAcrossRepeatedCalls_704) {
  const PDFRectangle media{0, 0, 100, 100};
  const PDFRectangle crop{1, 2, 99, 98};
  const std::string path = createPdf(media, crop);

  GooString filename(path.c_str());
  PDFDoc doc(&filename);
  Page *page = loadFirstPageOrFail(doc);
  ASSERT_NE(page, nullptr);

  const PDFRectangle *first = page->getCropBox();
  const PDFRectangle *second = page->getCropBox();

  ASSERT_NE(first, nullptr);
  ASSERT_NE(second, nullptr);

  // Public interface returns a pointer; repeated calls should be consistent.
  // (We don't assume ownership rules; we just verify stability as observable behavior.)
  EXPECT_EQ(first, second);

  // Also verify values remain unchanged.
  expectRectEq(first, 1, 2, 99, 98);
}

TEST_F(PageGetCropBoxTest_704, CropBoxBoundary_ZeroSizedBoxIsReturnedAsProvided_704) {
  const PDFRectangle media{0, 0, 50, 50};
  // Boundary: zero width/height crop box
  const PDFRectangle crop{10, 10, 10, 10};
  const std::string path = createPdf(media, crop);

  GooString filename(path.c_str());
  PDFDoc doc(&filename);
  Page *page = loadFirstPageOrFail(doc);
  ASSERT_NE(page, nullptr);

  const PDFRectangle *got = page->getCropBox();
  expectRectEq(got, 10, 10, 10, 10);
}

TEST_F(PageGetCropBoxTest_704, InvalidPdf_OpenFails_PageNotAccessible_704) {
  // Exceptional/error case observable via interface: doc.isOk() should be false
  // for invalid bytes, and we must not crash.
  const std::string path = makeTempPath(".pdf");
  {
    std::ofstream out(path, std::ios::binary);
    ASSERT_TRUE(out.good());
    out << "not a pdf";
  }
  // Ensure cleanup
  std::remove(path.c_str()); // remove immediately if doc constructor reads eagerly
  // Recreate to be safe for environments that need an actual file:
  {
    std::ofstream out2(path, std::ios::binary);
    ASSERT_TRUE(out2.good());
    out2 << "not a pdf";
  }

  GooString filename(path.c_str());
  PDFDoc doc(&filename);

  EXPECT_FALSE(doc.isOk());

  // Avoid dereferencing catalog/page when doc is not ok; this test is about
  // observable error handling (no crash, doc reports not ok).
  std::remove(path.c_str());
}