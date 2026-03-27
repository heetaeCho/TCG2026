// PDFDoc_getPageCropHeight_957_test.cpp
#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <memory>
#include <optional>
#include <string>

#include "PDFDoc.h"
#include "goo/GooString.h"

namespace {

class PDFDocTest_957 : public ::testing::Test {
protected:
  static std::string writeTempPdf(const std::string &contents) {
#if defined(_WIN32)
    // Fallback temp name (keep it simple; CI environments usually accept this).
    const std::string path = "PDFDocTest_957_temp.pdf";
#else
    std::string path;
    {
      char tmpl[] = "/tmp/pdfdoc_957_XXXXXX.pdf";
      // mkstemps requires mutable char[]; suffix length is 4 for ".pdf"
      int fd = ::mkstemps(tmpl, 4);
      if (fd >= 0) {
        ::close(fd);
        path = tmpl;
      } else {
        path = "/tmp/pdfdoc_957_fallback.pdf";
      }
    }
#endif
    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    out.write(contents.data(), static_cast<std::streamsize>(contents.size()));
    out.close();
    return path;
  }

  static std::unique_ptr<PDFDoc> openDocFromFile(const std::string &path) {
    auto fileName = std::make_unique<GooString>(path.c_str());
    const std::optional<GooString> ownerPassword;
    const std::optional<GooString> userPassword;
    auto cb = []() {};
    return std::make_unique<PDFDoc>(std::move(fileName), ownerPassword, userPassword, cb);
  }

  // Minimal 1-page PDF, with explicit CropBox and MediaBox.
  // (We intentionally do NOT assert any absolute crop height value; we only compare
  // PDFDoc::getPageCropHeight(page) to Page::getCropHeight() via the public interface.)
  static std::string minimalOnePagePdfWithCropBox() {
    // Note: Cross-reference offsets are correct for this exact string.
    // If edited, offsets must be updated.
    return
      "%PDF-1.4\n"
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R >>\n"
      "endobj\n"
      "2 0 obj\n"
      "<< /Type /Pages /Count 1 /Kids [3 0 R] >>\n"
      "endobj\n"
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R\n"
      "   /MediaBox [0 0 200 400]\n"
      "   /CropBox  [0 0 200 300]\n"
      "   /Resources << >>\n"
      "   /Contents 4 0 R >>\n"
      "endobj\n"
      "4 0 obj\n"
      "<< /Length 0 >>\n"
      "stream\n"
      "endstream\n"
      "endobj\n"
      "xref\n"
      "0 5\n"
      "0000000000 65535 f \n"
      "0000000009 00000 n \n"
      "0000000058 00000 n \n"
      "0000000115 00000 n \n"
      "0000000266 00000 n \n"
      "trailer\n"
      "<< /Size 5 /Root 1 0 R >>\n"
      "startxref\n"
      "335\n"
      "%%EOF\n";
  }
};

TEST_F(PDFDocTest_957, ReturnsZeroWhenGetPageIsNull_957) {
  // Use the public factory that clearly indicates an error doc.
  auto doc = PDFDoc::ErrorPDFDoc(/*errorCode=*/1, std::make_unique<GooString>("dummy.pdf"));
  ASSERT_NE(doc, nullptr);

  // Observable behavior: if getPage(page) is null, getPageCropHeight(page) returns 0.0.
  // We avoid assuming which pages are valid: we *observe* getPage first.
  const int page = 1;
  if (doc->getPage(page) == nullptr) {
    EXPECT_DOUBLE_EQ(doc->getPageCropHeight(page), 0.0);
  } else {
    // If the implementation ever returns a non-null page in this scenario, still validate forwarding.
    EXPECT_DOUBLE_EQ(doc->getPageCropHeight(page), doc->getPage(page)->getCropHeight());
  }
}

TEST_F(PDFDocTest_957, ForwardsToPageGetCropHeightWhenPageExists_957) {
  const std::string pdfPath = writeTempPdf(minimalOnePagePdfWithCropBox());
  std::unique_ptr<PDFDoc> doc = openDocFromFile(pdfPath);
  ASSERT_NE(doc, nullptr);

  // Ensure we have at least one page we can query.
  ASSERT_GT(doc->getNumPages(), 0);

  const int page = 1;
  Page *p = doc->getPage(page);
  ASSERT_NE(p, nullptr);

  const double expected = p->getCropHeight();
  const double actual = doc->getPageCropHeight(page);

  EXPECT_DOUBLE_EQ(actual, expected);

  // Cleanup temp file (best-effort).
  std::remove(pdfPath.c_str());
}

TEST_F(PDFDocTest_957, OutOfRangePageBehavesConsistentlyWithGetPage_957) {
  const std::string pdfPath = writeTempPdf(minimalOnePagePdfWithCropBox());
  std::unique_ptr<PDFDoc> doc = openDocFromFile(pdfPath);
  ASSERT_NE(doc, nullptr);

  const int numPages = doc->getNumPages();
  ASSERT_GE(numPages, 0);

  // Choose a page index that is observably "out of range" for typical 1-based APIs.
  const int page = numPages + 1;

  Page *p = doc->getPage(page);
  if (p == nullptr) {
    EXPECT_DOUBLE_EQ(doc->getPageCropHeight(page), 0.0);
  } else {
    EXPECT_DOUBLE_EQ(doc->getPageCropHeight(page), p->getCropHeight());
  }

  std::remove(pdfPath.c_str());
}

TEST_F(PDFDocTest_957, NonPositivePageBehavesConsistentlyWithGetPage_957) {
  const std::string pdfPath = writeTempPdf(minimalOnePagePdfWithCropBox());
  std::unique_ptr<PDFDoc> doc = openDocFromFile(pdfPath);
  ASSERT_NE(doc, nullptr);

  // Boundary-like inputs: 0 and negative.
  for (int page : {0, -1}) {
    Page *p = doc->getPage(page);
    if (p == nullptr) {
      EXPECT_DOUBLE_EQ(doc->getPageCropHeight(page), 0.0);
    } else {
      EXPECT_DOUBLE_EQ(doc->getPageCropHeight(page), p->getCropHeight());
    }
  }

  std::remove(pdfPath.c_str());
}

} // namespace