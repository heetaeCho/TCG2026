// HtmlOutputDev_getPageHeight_2713_test.cc
#include <gtest/gtest.h>

#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "poppler/utils/HtmlOutputDev.h"

// Poppler core
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

namespace {

struct MediaBox {
  int llx;
  int lly;
  int urx;
  int ury;
};

std::string BuildMinimalPdf(const std::vector<MediaBox> &pages) {
  // Build a tiny, valid PDF with N empty pages. Each page has a MediaBox.
  // (No streams needed; pages will render blank.)
  //
  // Objects:
  // 1 0 obj: Catalog
  // 2 0 obj: Pages
  // 3..(2+N): Page objects
  //
  // XRef + Trailer.
  std::vector<std::string> objs;

  // Placeholder: we'll fill Kids array after we know page object numbers.
  // Catalog object (1)
  objs.emplace_back(
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R >>\n"
      "endobj\n");

  // Pages object (2) with Kids
  {
    std::ostringstream kids;
    kids << "[ ";
    for (size_t i = 0; i < pages.size(); ++i) {
      const int pageObjNum = 3 + static_cast<int>(i);
      kids << pageObjNum << " 0 R ";
    }
    kids << "]";

    std::ostringstream o;
    o << "2 0 obj\n"
         "<< /Type /Pages /Count "
      << pages.size() << " /Kids " << kids.str() << " >>\n"
      << "endobj\n";
    objs.emplace_back(o.str());
  }

  // Page objects
  for (size_t i = 0; i < pages.size(); ++i) {
    const int pageObjNum = 3 + static_cast<int>(i);
    const auto &mb = pages[i];

    std::ostringstream o;
    o << pageObjNum << " 0 obj\n"
      << "<< /Type /Page /Parent 2 0 R "
      << "/MediaBox [ " << mb.llx << " " << mb.lly << " " << mb.urx << " " << mb.ury
      << " ] "
      // Minimal required Resources dict; empty is ok for a blank page.
      << "/Resources << >> "
      // Content stream omitted; allowed.
      << ">>\n"
      << "endobj\n";
    objs.emplace_back(o.str());
  }

  std::ostringstream pdf;
  pdf << "%PDF-1.4\n";

  // Track offsets for xref (object numbers start at 1, plus object 0 free).
  // offsets[i] corresponds to object i (0..maxObj).
  const int maxObj = 2 + static_cast<int>(pages.size());
  std::vector<long long> offsets(maxObj + 1, 0);

  for (int objNum = 1; objNum <= maxObj; ++objNum) {
    offsets[objNum] = static_cast<long long>(pdf.tellp());
    pdf << objs[static_cast<size_t>(objNum - 1)];
  }

  const long long xrefPos = static_cast<long long>(pdf.tellp());
  pdf << "xref\n";
  pdf << "0 " << (maxObj + 1) << "\n";
  pdf << "0000000000 65535 f \n";
  for (int objNum = 1; objNum <= maxObj; ++objNum) {
    // 10-digit, zero-padded offsets
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010lld", offsets[objNum]);
    pdf << buf << " 00000 n \n";
  }

  pdf << "trailer\n";
  pdf << "<< /Size " << (maxObj + 1) << " /Root 1 0 R >>\n";
  pdf << "startxref\n";
  pdf << xrefPos << "\n";
  pdf << "%%EOF\n";

  return pdf.str();
}

std::filesystem::path WriteTempFile(const std::string &contents,
                                   const std::string &prefix,
                                   const std::string &ext) {
  const auto dir = std::filesystem::temp_directory_path();
  const auto path =
      dir / (prefix + "_" + std::to_string(::getpid()) + "_" + std::to_string(::rand()) + ext);

  std::ofstream ofs(path, std::ios::binary);
  ofs.write(contents.data(), static_cast<std::streamsize>(contents.size()));
  ofs.close();
  return path;
}

std::unique_ptr<PDFDoc> OpenPdf(const std::filesystem::path &pdfPath) {
  auto gs = std::make_unique<GooString>(pdfPath.string().c_str());
  // NOTE: PDFDoc constructor signatures vary slightly by Poppler version;
  // this is the common one used in many Poppler codebases.
  auto doc = std::make_unique<PDFDoc>(std::move(gs));
  if (!doc || !doc->isOk()) {
    return nullptr;
  }
  return doc;
}

class HtmlOutputDevGetPageHeightTest_2713 : public ::testing::Test {
protected:
  void SetUp() override {
    // Poppler typically expects globalParams to be initialized for rendering.
    // Many codebases have it as a global; we simply ensure it's constructed.
    if (!globalParams) {
      globalParams = std::make_unique<GlobalParams>();
    }
  }
};

} // namespace

TEST_F(HtmlOutputDevGetPageHeightTest_2713, ReturnsNonNegativeBeforeRendering_2713) {
  const std::string pdf = BuildMinimalPdf({MediaBox{0, 0, 612, 792}});
  const auto pdfPath = WriteTempFile(pdf, "poppler_htmloutdev_2713", ".pdf");

  auto doc = OpenPdf(pdfPath);
  ASSERT_NE(doc, nullptr);

  const auto outBase = (std::filesystem::temp_directory_path() / "htmloutdev_2713_out").string();

  HtmlOutputDev dev(doc->getCatalog(),
                    outBase.c_str(),
                    "t", "a", "k", "s", "d",
                    /*rawOrder=*/false,
                    /*firstPage=*/1,
                    /*outline=*/false);

  const int h = dev.getPageHeight();
  EXPECT_GE(h, 0);

  std::error_code ec;
  std::filesystem::remove(pdfPath, ec);
}

TEST_F(HtmlOutputDevGetPageHeightTest_2713, UpdatesToPageHeightAfterDisplayPage_2713) {
  // Letter size in points: 612 x 792
  const std::string pdf = BuildMinimalPdf({MediaBox{0, 0, 612, 792}});
  const auto pdfPath = WriteTempFile(pdf, "poppler_htmloutdev_2713", ".pdf");

  auto doc = OpenPdf(pdfPath);
  ASSERT_NE(doc, nullptr);

  const auto outBase =
      (std::filesystem::temp_directory_path() / "htmloutdev_2713_single").string();

  HtmlOutputDev dev(doc->getCatalog(),
                    outBase.c_str(),
                    "title", "author", "keywords", "subject", "date",
                    /*rawOrder=*/false,
                    /*firstPage=*/1,
                    /*outline=*/false);

  // Render the first page through the OutputDev interface. This should
  // exercise startPage/endPage internally (black-box), making height observable.
  doc->displayPages(&dev,
                    /*firstPage=*/1,
                    /*lastPage=*/1,
                    /*hDPI=*/72.0,
                    /*vDPI=*/72.0,
                    /*rotate=*/0,
                    /*useMediaBox=*/true,
                    /*crop=*/false,
                    /*printing=*/false);

  const int h = dev.getPageHeight();

  // Expect approximately 792 at 72 DPI for a 792-pt tall page.
  // Allow a small tolerance to avoid over-assuming exact rounding behavior.
  EXPECT_GE(h, 791);
  EXPECT_LE(h, 793);

  // Idempotent: repeated calls should match.
  EXPECT_EQ(dev.getPageHeight(), h);

  std::error_code ec;
  std::filesystem::remove(pdfPath, ec);
}

TEST_F(HtmlOutputDevGetPageHeightTest_2713, UsesMaximumHeightAcrossMultiplePages_2713) {
  // Page 1: 612x400, Page 2: 612x792, Page 3: 612x1000
  const std::string pdf =
      BuildMinimalPdf({MediaBox{0, 0, 612, 400}, MediaBox{0, 0, 612, 792}, MediaBox{0, 0, 612, 1000}});
  const auto pdfPath = WriteTempFile(pdf, "poppler_htmloutdev_2713_multi", ".pdf");

  auto doc = OpenPdf(pdfPath);
  ASSERT_NE(doc, nullptr);

  const auto outBase =
      (std::filesystem::temp_directory_path() / "htmloutdev_2713_multi_out").string();

  HtmlOutputDev dev(doc->getCatalog(),
                    outBase.c_str(),
                    "title", "author", "keywords", "subject", "date",
                    /*rawOrder=*/false,
                    /*firstPage=*/1,
                    /*outline=*/false);

  doc->displayPages(&dev,
                    /*firstPage=*/1,
                    /*lastPage=*/3,
                    /*hDPI=*/72.0,
                    /*vDPI=*/72.0,
                    /*rotate=*/0,
                    /*useMediaBox=*/true,
                    /*crop=*/false,
                    /*printing=*/false);

  const int h = dev.getPageHeight();

  // Expect approximately the tallest page: 1000 points at 72 DPI.
  EXPECT_GE(h, 999);
  EXPECT_LE(h, 1001);

  std::error_code ec;
  std::filesystem::remove(pdfPath, ec);
}