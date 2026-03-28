// SPDX-License-Identifier: GPL-2.0-or-later
// File: PageTest_701.cpp
//
// Unit tests for poppler::Page (partial interface)
// Focus: Page::isOk() observable behavior via loading real PDFs (black-box).

#include <gtest/gtest.h>

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "poppler/Page.h"

// Use Poppler internals to obtain real Page instances (black-box).
#include "poppler/PDFDoc.h"
#include "poppler/GooString.h"
#include "poppler/GlobalParams.h"

namespace {

std::string MakeMinimalOnePagePdf()
{
  // Build a minimal, structurally valid PDF with correct xref offsets.
  // Objects:
  // 1: Catalog
  // 2: Pages
  // 3: Page
  // 4: Contents (empty stream)
  std::string pdf;
  pdf.reserve(1024);

  auto append = [&](const std::string &s) { pdf += s; };

  append("%PDF-1.4\n");
  append("%\xE2\xE3\xCF\xD3\n"); // binary comment

  std::vector<size_t> offsets(5, 0); // 0..4
  auto add_obj = [&](int objNum, const std::string &body) {
    offsets[objNum] = pdf.size();
    append(std::to_string(objNum));
    append(" 0 obj\n");
    append(body);
    append("\nendobj\n");
  };

  add_obj(1, "<< /Type /Catalog /Pages 2 0 R >>");
  add_obj(2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>");
  add_obj(3, "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>");
  add_obj(4, "<< /Length 0 >>\nstream\n\nendstream");

  const size_t xrefPos = pdf.size();
  append("xref\n");
  append("0 5\n");
  append("0000000000 65535 f \n");

  auto fmt10 = [](size_t n) {
    std::string s = std::to_string(n);
    if (s.size() < 10) s.insert(s.begin(), 10 - s.size(), '0');
    return s;
  };

  for (int i = 1; i <= 4; ++i) {
    append(fmt10(offsets[i]));
    append(" 00000 n \n");
  }

  append("trailer\n");
  append("<< /Size 5 /Root 1 0 R >>\n");
  append("startxref\n");
  append(std::to_string(xrefPos));
  append("\n%%EOF\n");

  return pdf;
}

std::filesystem::path WriteTempFile(const std::string &bytes, const std::string &nameHint)
{
  const auto dir = std::filesystem::temp_directory_path();
  const auto path = dir / (nameHint + "_" + std::to_string(::getpid()) + ".pdf");

  std::ofstream os(path, std::ios::binary | std::ios::trunc);
  os.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
  os.close();

  return path;
}

class PageTest_701 : public ::testing::Test {
protected:
  void SetUp() override
  {
    // Poppler typically relies on a global GlobalParams instance.
    // Create it for the duration of the tests in this fixture.
    if (globalParams == nullptr) {
      globalParams = new GlobalParams();
      ownsGlobalParams_ = true;
    }
  }

  void TearDown() override
  {
    if (ownsGlobalParams_) {
      delete globalParams;
      globalParams = nullptr;
      ownsGlobalParams_ = false;
    }
  }

private:
  bool ownsGlobalParams_ = false;
};

TEST_F(PageTest_701, IsOkTrueForValidLoadedPage_701)
{
  const std::string pdf = MakeMinimalOnePagePdf();
  const auto path = WriteTempFile(pdf, "poppler_page_ok");

  auto fileName = std::make_unique<GooString>(path.string().c_str());
  std::unique_ptr<PDFDoc> doc(new PDFDoc(std::move(fileName)));

  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  // Obtain a real Page from the document and verify Page::isOk() is true.
  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);
  EXPECT_TRUE(page->isOk());

  // Also verify const-correctness from the public interface perspective.
  const Page *cpage = page;
  EXPECT_TRUE(cpage->isOk());

  std::error_code ec;
  std::filesystem::remove(path, ec);
}

TEST_F(PageTest_701, IsOkCallableRepeatedlyAndStableOnSamePage_701)
{
  const std::string pdf = MakeMinimalOnePagePdf();
  const auto path = WriteTempFile(pdf, "poppler_page_stable");

  auto fileName = std::make_unique<GooString>(path.string().c_str());
  std::unique_ptr<PDFDoc> doc(new PDFDoc(std::move(fileName)));

  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  const bool first = page->isOk();
  const bool second = page->isOk();
  const bool third = page->isOk();

  // Black-box expectation: repeated calls should be consistent for an unchanged object.
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);

  std::error_code ec;
  std::filesystem::remove(path, ec);
}

TEST_F(PageTest_701, ValidDocOutOfRangePageDoesNotProvidePageToQuery_701)
{
  const std::string pdf = MakeMinimalOnePagePdf();
  const auto path = WriteTempFile(pdf, "poppler_page_oob");

  auto fileName = std::make_unique<GooString>(path.string().c_str());
  std::unique_ptr<PDFDoc> doc(new PDFDoc(std::move(fileName)));

  ASSERT_TRUE(doc->isOk());

  // Boundary: page index outside valid range should not yield a Page instance.
  // (We avoid dereferencing nullptr; we only assert the observable result.)
  Page *page0 = doc->getPage(0);
  EXPECT_EQ(page0, nullptr);

  Page *page2 = doc->getPage(2);
  EXPECT_EQ(page2, nullptr);

  std::error_code ec;
  std::filesystem::remove(path, ec);
}

TEST_F(PageTest_701, InvalidPdfDocIsNotOkAndNoPageToQuery_701)
{
  // Exceptional/error case: truncated/invalid PDF should fail to load.
  std::string bad = MakeMinimalOnePagePdf();
  if (bad.size() > 20) bad.resize(20); // truncate hard

  const auto path = WriteTempFile(bad, "poppler_page_bad");

  auto fileName = std::make_unique<GooString>(path.string().c_str());
  std::unique_ptr<PDFDoc> doc(new PDFDoc(std::move(fileName)));

  ASSERT_NE(doc, nullptr);
  EXPECT_FALSE(doc->isOk());

  // In error conditions, we only verify we cannot obtain a page to call isOk on.
  Page *page = doc->getPage(1);
  EXPECT_EQ(page, nullptr);

  std::error_code ec;
  std::filesystem::remove(path, ec);
}

} // namespace