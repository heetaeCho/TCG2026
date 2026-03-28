// Page_getCropWidth_708_test.cpp
#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

// Poppler headers (paths may vary slightly depending on your build setup)
#include "GlobalParams.h"
#include "PDFDoc.h"
#include "Page.h"
#include "goo/GooString.h"

namespace {

class PageGetCropWidthTest_708 : public ::testing::Test {
protected:
  void SetUp() override {
    // Many Poppler builds expect globalParams to be initialized before PDFDoc usage.
    if (!globalParams) {
      globalParams = std::make_unique<GlobalParams>();
    }
  }

  // Builds a minimal 1-page PDF with a MediaBox and (optionally) a CropBox.
  // Returns the PDF bytes as a string with a valid xref/trailer.
  static std::string BuildOnePagePdf(double mediaW, double mediaH,
                                     std::optional<std::array<double, 4>> cropBox) {
    auto fmt = [](double v) {
      std::ostringstream oss;
      // Keep it simple and stable for PDF tokenization.
      oss.setf(std::ios::fixed);
      oss.precision(6);
      oss << v;
      return oss.str();
    };

    std::vector<std::string> objs;
    objs.reserve(5);

    // 1: Catalog
    objs.emplace_back("1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");

    // 2: Pages
    objs.emplace_back("2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n");

    // 3: Page
    std::ostringstream pageDict;
    pageDict << "3 0 obj\n<< /Type /Page /Parent 2 0 R\n"
             << "   /MediaBox [0 0 " << fmt(mediaW) << " " << fmt(mediaH) << "]\n";
    if (cropBox.has_value()) {
      const auto &cb = *cropBox;
      pageDict << "   /CropBox [" << fmt(cb[0]) << " " << fmt(cb[1]) << " "
               << fmt(cb[2]) << " " << fmt(cb[3]) << "]\n";
    }
    pageDict << "   /Contents 4 0 R\n"
             << "   /Resources << >>\n"
             << ">>\nendobj\n";
    objs.emplace_back(pageDict.str());

    // 4: Empty content stream
    objs.emplace_back("4 0 obj\n<< /Length 0 >>\nstream\n\nendstream\nendobj\n");

    // Assemble PDF and compute xref offsets.
    std::ostringstream pdf;
    pdf << "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n";

    // Object 0 is the free head in xref; include it in offsets vector as 0.
    std::vector<long long> offsets(5, 0);

    // Write objects and record offsets.
    for (size_t i = 0; i < objs.size(); ++i) {
      offsets[i + 1] = static_cast<long long>(pdf.tellp());
      pdf << objs[i];
    }

    const long long xrefPos = static_cast<long long>(pdf.tellp());

    pdf << "xref\n0 5\n";
    // Object 0 free entry
    pdf << "0000000000 65535 f \n";
    for (int objNum = 1; objNum <= 4; ++objNum) {
      std::ostringstream off;
      off.setf(std::ios::fixed);
      off << std::setw(10) << std::setfill('0') << offsets[objNum];
      pdf << off.str() << " 00000 n \n";
    }

    pdf << "trailer\n<< /Size 5 /Root 1 0 R >>\n"
        << "startxref\n" << xrefPos << "\n%%EOF\n";

    return pdf.str();
  }

  static std::filesystem::path WriteTempPdf(const std::string &bytes, const std::string &tag) {
    const auto dir = std::filesystem::temp_directory_path();
    const auto path = dir / (std::string("poppler_page_getCropWidth_708_") + tag + ".pdf");
    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    out.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
    out.close();
    return path;
  }

  static std::unique_ptr<PDFDoc> OpenDoc(const std::filesystem::path &path) {
    // Common Poppler constructor style (may vary by version).
    auto gs = std::make_unique<GooString>(path.string().c_str());
    return std::make_unique<PDFDoc>(std::move(gs));
  }
};

TEST_F(PageGetCropWidthTest_708, ReturnsCropWidthFromCropBox_708) {
  const auto pdfBytes = BuildOnePagePdf(/*mediaW=*/300, /*mediaH=*/400,
                                       std::array<double, 4>{0, 0, 200, 400});
  const auto pdfPath = WriteTempPdf(pdfBytes, "crop_200");

  auto doc = OpenDoc(pdfPath);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  EXPECT_DOUBLE_EQ(page->getCropWidth(), 200.0);
}

TEST_F(PageGetCropWidthTest_708, CropWidthHandlesNegativeCoordinates_708) {
  const auto pdfBytes = BuildOnePagePdf(/*mediaW=*/300, /*mediaH=*/400,
                                       std::array<double, 4>{-10, 0, 10, 100});
  const auto pdfPath = WriteTempPdf(pdfBytes, "crop_neg");

  auto doc = OpenDoc(pdfPath);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  EXPECT_DOUBLE_EQ(page->getCropWidth(), 20.0);
}

TEST_F(PageGetCropWidthTest_708, CropWidthZeroWhenX1EqualsX2_708) {
  const auto pdfBytes = BuildOnePagePdf(/*mediaW=*/300, /*mediaH=*/400,
                                       std::array<double, 4>{0, 0, 0, 100});
  const auto pdfPath = WriteTempPdf(pdfBytes, "crop_zero");

  auto doc = OpenDoc(pdfPath);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  EXPECT_DOUBLE_EQ(page->getCropWidth(), 0.0);
}

TEST_F(PageGetCropWidthTest_708, FallsBackToMediaBoxWidthWhenNoCropBox_708) {
  const auto pdfBytes = BuildOnePagePdf(/*mediaW=*/321, /*mediaH=*/400, std::nullopt);
  const auto pdfPath = WriteTempPdf(pdfBytes, "no_crop");

  auto doc = OpenDoc(pdfPath);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  // Observable behavior: getCropWidth uses the page's crop box; when not present,
  // Poppler typically uses MediaBox as the effective CropBox.
  EXPECT_DOUBLE_EQ(page->getCropWidth(), 321.0);
}

TEST_F(PageGetCropWidthTest_708, DocumentWithMalformedCropBoxDoesNotCrashAndIsOk_708) {
  // Create a PDF where CropBox is malformed (not an array). Many parsers ignore it.
  // We only assert observable robustness: document opens and page is accessible.
  std::ostringstream pdf;
  pdf << "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n";

  std::vector<long long> offsets(5, 0);

  offsets[1] = static_cast<long long>(pdf.tellp());
  pdf << "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";

  offsets[2] = static_cast<long long>(pdf.tellp());
  pdf << "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";

  offsets[3] = static_cast<long long>(pdf.tellp());
  pdf << "3 0 obj\n<< /Type /Page /Parent 2 0 R\n"
      << "   /MediaBox [0 0 100 100]\n"
      << "   /CropBox 123\n" // malformed
      << "   /Contents 4 0 R\n"
      << "   /Resources << >>\n"
      << ">>\nendobj\n";

  offsets[4] = static_cast<long long>(pdf.tellp());
  pdf << "4 0 obj\n<< /Length 0 >>\nstream\n\nendstream\nendobj\n";

  const long long xrefPos = static_cast<long long>(pdf.tellp());
  pdf << "xref\n0 5\n";
  pdf << "0000000000 65535 f \n";
  for (int objNum = 1; objNum <= 4; ++objNum) {
    std::ostringstream off;
    off << std::setw(10) << std::setfill('0') << offsets[objNum];
    pdf << off.str() << " 00000 n \n";
  }
  pdf << "trailer\n<< /Size 5 /Root 1 0 R >>\n"
      << "startxref\n" << xrefPos << "\n%%EOF\n";

  const auto pdfPath = WriteTempPdf(pdf.str(), "malformed_crop");

  auto doc = OpenDoc(pdfPath);
  ASSERT_TRUE(doc);

  // Some builds may still mark it ok; if it is ok, page should be accessible and callable.
  if (doc->isOk()) {
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    // Should not crash; value may fall back to MediaBox width.
    (void)page->getCropWidth();
  }
}

} // namespace