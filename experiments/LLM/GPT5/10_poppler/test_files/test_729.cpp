// Page_hasStandaloneFields_test_729.cpp
#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "poppler/GlobalParams.h"
#include "poppler/PDFDoc.h"
#include "poppler/Page.h"
#include "goo/GooString.h"

namespace {

// In Poppler, globalParams is typically required before creating PDFDoc.
struct GlobalParamsGuard {
  GlobalParamsGuard() {
    if (!globalParams) {
      globalParams = std::make_unique<GlobalParams>();
    }
  }
  ~GlobalParamsGuard() = default;
};

// Writes a minimally valid PDF by generating correct xref offsets.
static std::string BuildPdfWithObjects(const std::vector<std::string> &objects) {
  std::string pdf;
  pdf += "%PDF-1.4\n";

  // Object numbers start at 1.
  std::vector<size_t> offsets;
  offsets.reserve(objects.size() + 1);
  offsets.push_back(0); // obj 0 is the free object; xref entry is special.

  for (size_t i = 0; i < objects.size(); ++i) {
    offsets.push_back(pdf.size());
    pdf += std::to_string(i + 1) + " 0 obj\n";
    pdf += objects[i];
    if (!pdf.empty() && pdf.back() != '\n') {
      pdf += "\n";
    }
    pdf += "endobj\n";
  }

  const size_t xrefPos = pdf.size();
  pdf += "xref\n";
  pdf += "0 " + std::to_string(objects.size() + 1) + "\n";
  pdf += "0000000000 65535 f \n";

  for (size_t i = 1; i < offsets.size(); ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010zu 00000 n \n", offsets[i]);
    pdf += buf;
  }

  pdf += "trailer\n";
  pdf += "<< /Size " + std::to_string(objects.size() + 1) + " /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xrefPos) + "\n";
  pdf += "%%EOF\n";
  return pdf;
}

static std::string WriteTempFile(const std::string &bytes, const char *suffix) {
  // Portable enough for test environments: create a unique file name in the
  // current working directory.
  static int counter = 0;
  const std::string path =
      std::string("poppler_page_test_729_") + std::to_string(++counter) + suffix;

  std::ofstream out(path, std::ios::binary);
  out.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
  out.close();
  return path;
}

static std::unique_ptr<PDFDoc> OpenDocFromPath(const std::string &path) {
  auto fname = std::make_unique<GooString>(path.c_str());
  // Passwords: nullptr means "no password".
  return std::make_unique<PDFDoc>(std::move(fname), nullptr, nullptr);
}

// One blank page, no /AcroForm at all.
static std::string MakePdf_NoAcroForm() {
  // 1: Catalog, 2: Pages, 3: Page, 4: Contents
  std::vector<std::string> objs;
  objs.push_back("<< /Type /Catalog /Pages 2 0 R >>");
  objs.push_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");
  objs.push_back("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>");
  objs.push_back("<< /Length 0 >>\nstream\n\nendstream");
  return BuildPdfWithObjects(objs);
}

// One blank page, /AcroForm with a single field that references the page via /P,
// but intentionally has no widget annotation. This aims to exercise "standalone fields".
static std::string MakePdf_AcroFormStandaloneField() {
  // 1: Catalog, 2: Pages, 3: Page, 4: Contents, 5: AcroForm, 6: Field
  std::vector<std::string> objs;
  objs.push_back("<< /Type /Catalog /Pages 2 0 R /AcroForm 5 0 R >>");
  objs.push_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");
  objs.push_back("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>");
  objs.push_back("<< /Length 0 >>\nstream\n\nendstream");
  objs.push_back("<< /Fields [6 0 R] >>");
  objs.push_back("<< /FT /Tx /T (Standalone) /P 3 0 R >>");
  return BuildPdfWithObjects(objs);
}

class PageHasStandaloneFieldsTest_729 : public ::testing::Test {
 protected:
  GlobalParamsGuard guard_;
};

} // namespace

TEST_F(PageHasStandaloneFieldsTest_729, NoAcroForm_PageReportsNoStandaloneFields_729) {
  const std::string pdfBytes = MakePdf_NoAcroForm();
  const std::string path = WriteTempFile(pdfBytes, ".pdf");

  auto doc = OpenDocFromPath(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  // Observable behavior: should report false when there are no form fields.
  EXPECT_FALSE(page->hasStandaloneFields());

  // Stable across repeated calls.
  EXPECT_FALSE(page->hasStandaloneFields());

  std::remove(path.c_str());
}

TEST_F(PageHasStandaloneFieldsTest_729, AcroFormStandaloneField_CanReportStandaloneFields_729) {
  const std::string pdfBytes = MakePdf_AcroFormStandaloneField();
  const std::string path = WriteTempFile(pdfBytes, ".pdf");

  auto doc = OpenDocFromPath(path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  Page *page = doc->getPage(1);
  ASSERT_NE(page, nullptr);

  // Some Poppler builds may only populate form-related page data lazily.
  // Calling getFormWidgets() is a public, observable operation that can trigger form parsing.
  (void)page->getFormWidgets();

  // If the implementation recognizes /AcroForm fields tied to this page as "standalone",
  // hasStandaloneFields() should report true.
  EXPECT_TRUE(page->hasStandaloneFields());

  // Stable across repeated calls.
  EXPECT_TRUE(page->hasStandaloneFields());

  std::remove(path.c_str());
}

TEST_F(PageHasStandaloneFieldsTest_729, InvalidPdf_DocumentIsNotOk_729) {
  const std::string notPdf = "this is not a pdf";
  const std::string path = WriteTempFile(notPdf, ".pdf");

  auto doc = OpenDocFromPath(path);
  ASSERT_TRUE(doc);

  // Error/exceptional case observable through PDFDoc interface.
  EXPECT_FALSE(doc->isOk());

  std::remove(path.c_str());
}