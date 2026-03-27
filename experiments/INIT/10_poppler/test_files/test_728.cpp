// TEST_ID: 728
// File: page_getactions_test_728.cpp

#include <gtest/gtest.h>

#include <fstream>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "poppler/PDFDoc.h"
#include "poppler/GooString.h"
#include "poppler/Page.h"
#include "poppler/Object.h"

namespace {

std::string MakePdfWithSinglePage(bool withAdditionalActions) {
  // Generate a minimal PDF (with correct xref offsets) containing exactly one page.
  // If withAdditionalActions=true, the page dictionary includes an /AA dictionary.

  std::vector<std::string> objs;
  objs.reserve(4);

  // 1: Catalog
  objs.emplace_back(
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R >>\n"
      "endobj\n");

  // 2: Pages
  objs.emplace_back(
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n");

  // 3: Page
  std::string pageDict =
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R";
  if (withAdditionalActions) {
    // Additional Actions dictionary. Keep it simple (and purely syntactic).
    pageDict +=
        " /AA << /O << /S /JavaScript /JS (app.alert\\(hi\\)) >> >>";
  }
  pageDict += " >>\nendobj\n";
  objs.emplace_back(std::move(pageDict));

  // 4: Empty contents stream
  objs.emplace_back(
      "4 0 obj\n"
      "<< /Length 0 >>\n"
      "stream\n"
      "\n"
      "endstream\n"
      "endobj\n");

  std::string out;
  out += "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n"; // binary marker comment

  // Track offsets: xref uses byte offsets from start of file.
  std::vector<long long> offsets;
  offsets.reserve(objs.size() + 1);
  offsets.push_back(0); // object 0 is the free entry

  for (const auto &obj : objs) {
    offsets.push_back(static_cast<long long>(out.size()));
    out += obj;
  }

  const long long xrefPos = static_cast<long long>(out.size());

  // xref table
  out += "xref\n";
  out += "0 5\n";
  out += "0000000000 65535 f \n";
  for (size_t i = 1; i < offsets.size(); ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010lld 00000 n \n", offsets[i]);
    out += buf;
  }

  // trailer
  out += "trailer\n";
  out += "<< /Size 5 /Root 1 0 R >>\n";
  out += "startxref\n";
  out += std::to_string(xrefPos);
  out += "\n%%EOF\n";

  return out;
}

std::filesystem::path WriteTempFile(const std::string &content, const std::string &stem) {
  const auto dir = std::filesystem::temp_directory_path();
  auto path = dir / (stem + ".pdf");

  std::ofstream os(path, std::ios::binary);
  os.write(content.data(), static_cast<std::streamsize>(content.size()));
  os.close();

  return path;
}

std::unique_ptr<PDFDoc> OpenPdfDoc(const std::filesystem::path &path) {
  auto goo = std::make_unique<GooString>(path.string().c_str());
  // Owner/User passwords not needed for these synthetic PDFs.
  auto doc = std::make_unique<PDFDoc>(std::move(goo));
  return doc;
}

} // namespace

class PageGetActionsTest_728 : public ::testing::Test {
protected:
  void TearDown() override {
    // Best-effort cleanup of temp files created by this test suite.
    for (const auto &p : created_) {
      std::error_code ec;
      std::filesystem::remove(p, ec);
    }
    created_.clear();
  }

  std::filesystem::path MakeTempPdf(bool withAdditionalActions, const std::string &stemSuffix) {
    std::string pdf = MakePdfWithSinglePage(withAdditionalActions);
    auto path = WriteTempFile(pdf, "poppler_page_getactions_728_" + stemSuffix);
    created_.push_back(path);
    return path;
  }

private:
  std::vector<std::filesystem::path> created_;
};

TEST_F(PageGetActionsTest_728, EmptyPageHasNoActions_ReturnsNullNoneOrEmptyDict_728) {
  const auto pdfPath = MakeTempPdf(/*withAdditionalActions=*/false, "no_actions");
  auto doc = OpenPdfDoc(pdfPath);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  Object actions = page->getActions();

  // Observable "error-ish" states should not occur for a valid PDF.
  EXPECT_FALSE(actions.isError());
  EXPECT_FALSE(actions.isEOF());

  // Be tolerant: depending on implementation details, "no actions" may appear as
  // null/none, or an empty dict.
  const bool isNullLike = actions.isNull() || actions.isNone();
  const bool isEmptyDict = actions.isDict() && actions.dictGetLength() == 0;
  EXPECT_TRUE(isNullLike || isEmptyDict);
}

TEST_F(PageGetActionsTest_728, PageWithAdditionalActions_ReturnsDictAndIsStableAcrossCalls_728) {
  const auto pdfPath = MakeTempPdf(/*withAdditionalActions=*/true, "with_aa");
  auto doc = OpenPdfDoc(pdfPath);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  Object actions1 = page->getActions();
  Object actions2 = page->getActions();

  // For a page with /AA set, actions should be representable as a dict.
  EXPECT_TRUE(actions1.isDict());
  EXPECT_FALSE(actions1.isError());
  EXPECT_FALSE(actions1.isEOF());

  // Calling twice should be stable w.r.t. observable type.
  EXPECT_EQ(actions1.getType(), actions2.getType());

  // If it's a dict, it should not be empty in this constructed input.
  if (actions1.isDict()) {
    EXPECT_GT(actions1.dictGetLength(), 0);

    // Spot-check a likely key without assuming full semantics.
    // If lookup exists, it should not produce error/EOF.
    Object o = actions1.dictLookup("O", /*recursion=*/0);
    EXPECT_FALSE(o.isError());
    EXPECT_FALSE(o.isEOF());
    // Many implementations store /O as a dictionary, but we avoid over-specifying.
    EXPECT_TRUE(o.isDict() || o.isNull() || o.isNone() || o.isRef() || o.isName());
  }
}

TEST_F(PageGetActionsTest_728, InvalidPdf_DocNotOkAndNoPageAvailable_728) {
  // Minimal "bad" content to exercise an observable failure mode.
  const auto badPath = WriteTempFile("not a pdf\n", "poppler_page_getactions_728_invalid");
  // Track for cleanup via TearDown by pushing into created_ indirectly isn't possible here;
  // just remove inline at end (best effort).
  std::error_code ecRemove;

  auto doc = OpenPdfDoc(badPath);
  ASSERT_NE(doc, nullptr);

  EXPECT_FALSE(doc->isOk());

  // In an invalid doc, asking for page 1 should not yield a usable page pointer.
  Page *page = doc->getPage(1);
  EXPECT_EQ(page, nullptr);

  std::filesystem::remove(badPath, ecRemove);
}