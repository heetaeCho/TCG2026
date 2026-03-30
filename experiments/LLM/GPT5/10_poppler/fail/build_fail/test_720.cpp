// Page_getDoc_ut_720.cpp
// Unit tests for poppler::Page (interface: PDFDoc *Page::getDoc())
// TEST_ID: 720

#include <gtest/gtest.h>

#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "poppler/GlobalParams.h"
#include "poppler/PDFDoc.h"
#include "poppler/Page.h"
#include "goo/GooString.h"

// Poppler typically exposes a global GlobalParams*.
extern GlobalParams *globalParams;

namespace {

class PageTest_720 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    if (!globalParams) {
      globalParams = new GlobalParams();
    }
  }

  static void TearDownTestSuite() {
    delete globalParams;
    globalParams = nullptr;
  }

  static std::string BuildSimplePdfBytes(int numPages) {
    // Build a tiny, valid PDF with `numPages` pages and a shared Helvetica font.
    // Note: This is only test data generation; it does not depend on Page internals.
    if (numPages < 1) numPages = 1;

    // Object ids:
    // 1 0: Catalog
    // 2 0: Pages
    // For each page i (1..n):
    //   pageId = 3 + (i-1)*2
    //   contentsId = pageId + 1
    // fontId = 2*n + 3
    const int fontId = 2 * numPages + 3;
    const int maxObjId = fontId;

    std::string pdf;
    pdf.reserve(4096);

    auto append = [&](const std::string &s) { pdf += s; };

    append("%PDF-1.4\n");
    std::vector<size_t> offsets(maxObjId + 1, 0);

    auto beginObj = [&](int objId) {
      offsets[objId] = pdf.size();
      append(std::to_string(objId));
      append(" 0 obj\n");
    };
    auto endObj = [&]() { append("endobj\n"); };

    // 1) Catalog
    beginObj(1);
    append("<< /Type /Catalog /Pages 2 0 R >>\n");
    endObj();

    // 2) Pages tree
    beginObj(2);
    append("<< /Type /Pages /Count ");
    append(std::to_string(numPages));
    append(" /Kids [ ");
    for (int i = 1; i <= numPages; ++i) {
      const int pageId = 3 + (i - 1) * 2;
      append(std::to_string(pageId));
      append(" 0 R ");
    }
    append("] >>\n");
    endObj();

    // Pages + contents
    for (int i = 1; i <= numPages; ++i) {
      const int pageId = 3 + (i - 1) * 2;
      const int contentsId = pageId + 1;

      // Page object
      beginObj(pageId);
      append("<< /Type /Page /Parent 2 0 R ");
      append("/MediaBox [0 0 200 200] ");
      append("/Resources << /Font << /F1 ");
      append(std::to_string(fontId));
      append(" 0 R >> >> ");
      append("/Contents ");
      append(std::to_string(contentsId));
      append(" 0 R ");
      append(">>\n");
      endObj();

      // Contents stream
      const std::string streamText = "BT /F1 12 Tf 10 100 Td (Hello) Tj ET\n";
      beginObj(contentsId);
      append("<< /Length ");
      append(std::to_string(streamText.size()));
      append(" >>\nstream\n");
      append(streamText);
      append("endstream\n");
      endObj();
    }

    // Font object
    beginObj(fontId);
    append("<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n");
    endObj();

    // Xref
    const size_t xrefOffset = pdf.size();
    append("xref\n");
    append("0 ");
    append(std::to_string(maxObjId + 1));
    append("\n");

    // Entry 0 (free)
    append("0000000000 65535 f \n");

    auto fmt10 = [](size_t off) {
      char buf[32];
      std::snprintf(buf, sizeof(buf), "%010zu", off);
      return std::string(buf);
    };

    for (int objId = 1; objId <= maxObjId; ++objId) {
      append(fmt10(offsets[objId]));
      append(" 00000 n \n");
    }

    // Trailer
    append("trailer\n");
    append("<< /Size ");
    append(std::to_string(maxObjId + 1));
    append(" /Root 1 0 R >>\n");
    append("startxref\n");
    append(std::to_string(xrefOffset));
    append("\n%%EOF\n");

    return pdf;
  }

  static std::filesystem::path WriteTempFile(const std::string &bytes,
                                             const std::string &suffix) {
    const auto dir = std::filesystem::temp_directory_path();
    const auto path =
        dir / (std::string("poppler_page_getdoc_720_") + std::to_string(std::rand()) + suffix);
    std::ofstream out(path, std::ios::binary);
    out.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
    out.close();
    return path;
  }

  static std::unique_ptr<PDFDoc> OpenDoc(const std::filesystem::path &path) {
    auto fname = std::make_unique<GooString>(path.string().c_str());
    // Common Poppler ctor: PDFDoc(std::unique_ptr<GooString>, GooString*, GooString*, void*)
    // If your Poppler version differs, adjust accordingly in your tree.
    return std::make_unique<PDFDoc>(std::move(fname), nullptr, nullptr, nullptr);
  }
};

TEST_F(PageTest_720, GetDocReturnsOwningDocPointer_720) {
  const auto pdfBytes = BuildSimplePdfBytes(2);
  const auto pdfPath = WriteTempFile(pdfBytes, ".pdf");

  auto doc = OpenDoc(pdfPath);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());
  ASSERT_EQ(doc->getNumPages(), 2);

  Page *p1 = doc->getPage(1);
  Page *p2 = doc->getPage(2);
  ASSERT_NE(p1, nullptr);
  ASSERT_NE(p2, nullptr);

  // Observable behavior: Page::getDoc returns a PDFDoc*.
  EXPECT_EQ(p1->getDoc(), doc.get());
  EXPECT_EQ(p2->getDoc(), doc.get());
}

TEST_F(PageTest_720, GetDocIsStableAcrossMultipleCalls_720) {
  const auto pdfBytes = BuildSimplePdfBytes(1);
  const auto pdfPath = WriteTempFile(pdfBytes, ".pdf");

  auto doc = OpenDoc(pdfPath);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());
  ASSERT_EQ(doc->getNumPages(), 1);

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  PDFDoc *d1 = page->getDoc();
  PDFDoc *d2 = page->getDoc();
  EXPECT_EQ(d1, d2);
  EXPECT_EQ(d1, doc.get());
}

TEST_F(PageTest_720, GetDocNonNullWhenDocumentIsOk_720) {
  const auto pdfBytes = BuildSimplePdfBytes(1);
  const auto pdfPath = WriteTempFile(pdfBytes, ".pdf");

  auto doc = OpenDoc(pdfPath);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  EXPECT_NE(page->getDoc(), nullptr);
}

TEST_F(PageTest_720, ErrorCase_InvalidPdfYieldsNoUsablePage_720) {
  // Exceptional/error path observable via PDFDoc/Page public APIs:
  // If the document cannot be parsed, a page may be unavailable.
  const auto pdfPath = WriteTempFile(std::string(), ".pdf");

  auto doc = OpenDoc(pdfPath);
  ASSERT_TRUE(doc);

  if (!doc->isOk()) {
    SUCCEED() << "PDFDoc reports not ok for invalid input.";
    return;
  }

  // If some builds still mark it ok, ensure we don't get a valid page.
  Page *page = doc->getPage(1);
  EXPECT_EQ(page, nullptr);
}

} // namespace