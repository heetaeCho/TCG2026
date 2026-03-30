// Page_getLastModified_714_test.cpp
// Unit tests for Page::getLastModified()
// TEST_ID: 714

#include <gtest/gtest.h>

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <optional>
#include <sstream>
#include <string>

#include "poppler/Page.h"
#include "poppler/PDFDoc.h"
#include "poppler/GlobalParams.h"
#include "goo/GooString.h"

// Poppler typically uses a global GlobalParams*.
extern GlobalParams *globalParams;

namespace {

std::string BuildMinimalPdfOnePage(std::optional<std::string> lastModifiedLiteral) {
  // Build a minimal PDF with:
  // 1 0 obj Catalog
  // 2 0 obj Pages
  // 3 0 obj Page (optionally includes /LastModified ( ... ))
  // 4 0 obj Contents (empty)
  //
  // We generate a correct xref with computed byte offsets.

  std::ostringstream out;
  out << "%PDF-1.4\n";

  struct ObjRec {
    int num;
    std::string body;
    long offset = 0;
  };

  std::vector<ObjRec> objs;
  objs.push_back({1, "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"});
  objs.push_back({2, "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"});

  {
    std::ostringstream page;
    page << "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] "
         << "/Contents 4 0 R";
    if (lastModifiedLiteral.has_value()) {
      // Literal string form ( ... ) as expected in many PDFs.
      page << " /LastModified (" << *lastModifiedLiteral << ")";
    }
    page << " >>\nendobj\n";
    objs.push_back({3, page.str()});
  }

  // Empty content stream.
  objs.push_back({4, "4 0 obj\n<< /Length 0 >>\nstream\n\nendstream\nendobj\n"});

  // Write objects while tracking offsets.
  for (auto &o : objs) {
    o.offset = static_cast<long>(out.tellp());
    out << o.body;
  }

  const long xrefOffset = static_cast<long>(out.tellp());
  out << "xref\n";
  out << "0 " << (objs.back().num + 1) << "\n";
  // Object 0 (free)
  out << "0000000000 65535 f \n";
  // Objects 1..N
  for (const auto &o : objs) {
    // 10-digit, zero-padded offsets.
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld", o.offset);
    out << buf << " 00000 n \n";
  }

  out << "trailer\n";
  out << "<< /Size " << (objs.back().num + 1) << " /Root 1 0 R >>\n";
  out << "startxref\n";
  out << xrefOffset << "\n";
  out << "%%EOF\n";

  return out.str();
}

std::filesystem::path WriteTempFile(const std::string &bytes, const std::string &nameHint) {
  auto dir = std::filesystem::temp_directory_path();
  auto path = dir / nameHint;
  std::ofstream ofs(path, std::ios::binary | std::ios::trunc);
  ofs.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
  ofs.close();
  return path;
}

std::unique_ptr<PDFDoc> OpenPdfDocFromFile(const std::filesystem::path &path) {
  auto gs = std::make_unique<GooString>(path.u8string().c_str());
  // PDFDoc has multiple constructors across Poppler versions. This one is common:
  // PDFDoc(std::unique_ptr<GooString> fileName, const std::optional<GooString>& ownerPassword, ...)
  // But not all builds expose std::optional. A broadly compatible option is the legacy signature:
  // PDFDoc(GooString *fileName, GooString *ownerPassword, GooString *userPassword)
  //
  // We try the legacy constructor form (most common in older embedded copies).
  return std::make_unique<PDFDoc>(gs.release(), nullptr, nullptr);
}

}  // namespace

class PageGetLastModifiedTest_714 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    if (!globalParams) {
      // Empty config; sufficient for basic parsing in most Poppler builds.
      globalParams = new GlobalParams(nullptr);
    }
  }

  static void TearDownTestSuite() {
    delete globalParams;
    globalParams = nullptr;
  }
};

TEST_F(PageGetLastModifiedTest_714, ReturnsExactLastModifiedStringWhenPresent_714) {
  const std::string expected = "D:20260101000000Z";
  const auto pdfBytes = BuildMinimalPdfOnePage(expected);
  const auto pdfPath = WriteTempFile(pdfBytes, "poppler_page_lastmodified_present_714.pdf");

  auto doc = OpenPdfDocFromFile(pdfPath);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  const GooString *lm = page->getLastModified();
  ASSERT_NE(lm, nullptr);

  // Compare content.
  EXPECT_STREQ(lm->c_str(), expected.c_str());

  // Cleanup temp file.
  std::error_code ec;
  std::filesystem::remove(pdfPath, ec);
}

TEST_F(PageGetLastModifiedTest_714, ReturnsNullWhenLastModifiedIsMissing_714) {
  const auto pdfBytes = BuildMinimalPdfOnePage(std::nullopt);
  const auto pdfPath = WriteTempFile(pdfBytes, "poppler_page_lastmodified_missing_714.pdf");

  auto doc = OpenPdfDocFromFile(pdfPath);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  const GooString *lm = page->getLastModified();
  EXPECT_EQ(lm, nullptr);

  std::error_code ec;
  std::filesystem::remove(pdfPath, ec);
}

TEST_F(PageGetLastModifiedTest_714, RepeatedCallsAreStableForPresentValue_714) {
  const std::string expected = "D:20260215010101Z";
  const auto pdfBytes = BuildMinimalPdfOnePage(expected);
  const auto pdfPath = WriteTempFile(pdfBytes, "poppler_page_lastmodified_stable_714.pdf");

  auto doc = OpenPdfDocFromFile(pdfPath);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  const GooString *lm1 = page->getLastModified();
  const GooString *lm2 = page->getLastModified();

  ASSERT_NE(lm1, nullptr);
  ASSERT_NE(lm2, nullptr);

  // Observable behavior: both calls report the same textual value.
  EXPECT_STREQ(lm1->c_str(), expected.c_str());
  EXPECT_STREQ(lm2->c_str(), expected.c_str());

  // Additionally, if implementation returns a persistent pointer, this may also hold;
  // it’s safe to check as an *observable* property (pointer equality) without relying on internals.
  EXPECT_EQ(lm1, lm2);

  std::error_code ec;
  std::filesystem::remove(pdfPath, ec);
}

TEST_F(PageGetLastModifiedTest_714, InvalidPdfMakesDocNotOk_714) {
  const std::string notPdf = "this is not a pdf";
  const auto badPath = WriteTempFile(notPdf, "poppler_page_lastmodified_invalid_714.pdf");

  auto doc = OpenPdfDocFromFile(badPath);
  ASSERT_NE(doc, nullptr);

  // Observable error case: parsing fails.
  EXPECT_FALSE(doc->isOk());

  std::error_code ec;
  std::filesystem::remove(badPath, ec);
}