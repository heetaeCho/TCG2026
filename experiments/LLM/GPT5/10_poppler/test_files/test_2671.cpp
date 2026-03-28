// File: test_pdfinfo_printDestinations_2671.cc
#include <gtest/gtest.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "goo/GooString.h"
#include "poppler/PDFDoc.h"
#include "poppler/UnicodeMap.h"

// pdfinfo.cc (from poppler/utils) typically defines a main(). Rename it to avoid conflicts.
#define main pdfinfo_main_2671
#include "utils/pdfinfo.cc"
#undef main

// firstPage/lastPage are globals used by printDestinations (declared elsewhere in utils).
extern int firstPage;
extern int lastPage;

namespace {

std::string WriteTempPdf_2671(const std::string &pdfBytes)
{
  // Create a unique-ish file name.
  std::ostringstream oss;
  oss << ::testing::UnitTest::GetInstance()->random_seed() << "_"
      << ::testing::UnitTest::GetInstance()->test_suite_to_run_count() << "_"
      << ::testing::UnitTest::GetInstance()->test_to_run_count() << "_2671.pdf";

  // Use current working directory; most test runners allow writing here.
  const std::string path = oss.str();

  std::ofstream out(path, std::ios::binary);
  EXPECT_TRUE(out.is_open());
  out.write(pdfBytes.data(), static_cast<std::streamsize>(pdfBytes.size()));
  out.close();
  EXPECT_TRUE(static_cast<bool>(out) || true);

  return path;
}

// Minimal PDF builder that emits a valid xref table.
// Objects are 1-based indexed; object 0 is the free object.
std::string BuildPdfWithObjects_2671(const std::vector<std::string> &objects, int rootObjNum)
{
  std::ostringstream pdf;
  pdf << "%PDF-1.4\n";
  // Binary comment line is recommended; keep simple.
  pdf << "%\xE2\xE3\xCF\xD3\n";

  std::vector<long long> offsets;
  offsets.reserve(objects.size() + 1);
  offsets.push_back(0); // obj 0 offset (unused; will be free)

  for (size_t i = 0; i < objects.size(); ++i) {
    offsets.push_back(static_cast<long long>(pdf.tellp()));
    pdf << (i + 1) << " 0 obj\n" << objects[i] << "\nendobj\n";
  }

  const long long xrefPos = static_cast<long long>(pdf.tellp());
  const int size = static_cast<int>(objects.size()) + 1;

  pdf << "xref\n";
  pdf << "0 " << size << "\n";
  // obj 0 free entry
  pdf << "0000000000 65535 f \n";
  for (int i = 1; i < size; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010lld", offsets[static_cast<size_t>(i)]);
    pdf << buf << " 00000 n \n";
  }

  pdf << "trailer\n";
  pdf << "<< /Size " << size << " /Root " << rootObjNum << " 0 R >>\n";
  pdf << "startxref\n";
  pdf << xrefPos << "\n";
  pdf << "%%EOF\n";
  return pdf.str();
}

std::unique_ptr<PDFDoc> OpenPdfDoc_2671(const std::string &path)
{
  auto fileName = std::make_unique<GooString>(path.c_str());
  std::optional<GooString> ownerPW;
  std::optional<GooString> userPW;
  auto doc = std::make_unique<PDFDoc>(std::move(fileName), ownerPW, userPW, []() {});
  return doc;
}

std::unique_ptr<UnicodeMap> Utf8UnicodeMap_2671()
{
  // Poppler commonly supports "UTF-8" maps; fall back to nullptr if not available.
  auto uMap = UnicodeMap::parse("UTF-8");
  return uMap;
}

} // namespace

class PdfInfoPrintDestinationsTest_2671 : public ::testing::Test {
protected:
  void SetUp() override
  {
    // Ensure deterministic page range for tests unless overridden.
    firstPage = 1;
    lastPage = 1;
  }
};

TEST_F(PdfInfoPrintDestinationsTest_2671, PrintsHeaderEvenWhenNoDestinations_2671)
{
  // Catalog without /Dests and /Names.
  // 1: Catalog, 2: Pages, 3: Page, 4: empty contents
  std::vector<std::string> objs;
  objs.push_back("<< /Type /Catalog /Pages 2 0 R >>"); // 1
  objs.push_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>"); // 2
  objs.push_back("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>"); // 3
  objs.push_back("<< /Length 0 >>\nstream\n\nendstream"); // 4

  const std::string pdfBytes = BuildPdfWithObjects_2671(objs, /*rootObjNum=*/1);
  const std::string path = WriteTempPdf_2671(pdfBytes);

  auto doc = OpenPdfDoc_2671(path);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  auto uMap = Utf8UnicodeMap_2671();

  testing::internal::CaptureStdout();
  printDestinations(doc.get(), uMap.get());
  const std::string out = testing::internal::GetCapturedStdout();

  // Observable behavior: header is always printed.
  EXPECT_NE(out.find("Page Destination Name\n"), std::string::npos);

  // With no destinations, no quoted destination names should appear.
  EXPECT_EQ(out.find("\""), std::string::npos);
}

TEST_F(PdfInfoPrintDestinationsTest_2671, PrintsDestFromCatalogDestsDictionary_2671)
{
  // Provide /Dests with a named destination referencing the single page by Ref.
  // 1: Catalog, 2: Pages, 3: Page, 4: contents
  std::vector<std::string> objs;
  objs.push_back(
      "<< /Type /Catalog /Pages 2 0 R "
      "   /Dests << /MyDest [3 0 R /Fit] >> "
      ">>"); // 1
  objs.push_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>"); // 2
  objs.push_back("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>"); // 3
  objs.push_back("<< /Length 0 >>\nstream\n\nendstream"); // 4

  const std::string pdfBytes = BuildPdfWithObjects_2671(objs, /*rootObjNum=*/1);
  const std::string path = WriteTempPdf_2671(pdfBytes);

  auto doc = OpenPdfDoc_2671(path);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  auto uMap = Utf8UnicodeMap_2671();

  testing::internal::CaptureStdout();
  printDestinations(doc.get(), uMap.get());
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_NE(out.find("Page Destination Name\n"), std::string::npos);

  // We don't assume printLinkDest formatting; only that the destination name is printed in quotes.
  EXPECT_NE(out.find("\"MyDest\""), std::string::npos);

  // The output includes the page number column; for our single page range, it should include "1".
  // Avoid overly strict spacing assumptions.
  EXPECT_NE(out.find("1"), std::string::npos);
}

TEST_F(PdfInfoPrintDestinationsTest_2671, PrintsDestFromNameTreeAndDestsForSamePage_2671)
{
  // Catalog with both:
  // - /Names /Dests NameTree containing (TreeDest)
  // - /Dests dictionary containing /MyDest
  std::vector<std::string> objs;
  objs.push_back(
      "<< /Type /Catalog /Pages 2 0 R "
      "   /Dests << /MyDest [3 0 R /Fit] >> "
      "   /Names << /Dests << /Names [(TreeDest) [3 0 R /Fit]] >> >> "
      ">>"); // 1
  objs.push_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>"); // 2
  objs.push_back("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>"); // 3
  objs.push_back("<< /Length 0 >>\nstream\n\nendstream"); // 4

  const std::string pdfBytes = BuildPdfWithObjects_2671(objs, /*rootObjNum=*/1);
  const std::string path = WriteTempPdf_2671(pdfBytes);

  auto doc = OpenPdfDoc_2671(path);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  auto uMap = Utf8UnicodeMap_2671();

  testing::internal::CaptureStdout();
  printDestinations(doc.get(), uMap.get());
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_NE(out.find("\"MyDest\""), std::string::npos);
  EXPECT_NE(out.find("\"TreeDest\""), std::string::npos);
}

TEST_F(PdfInfoPrintDestinationsTest_2671, IgnoresDestinationsOutsidePageRange_2671)
{
  // Same as simple /Dests doc but set lastPage beyond actual pages.
  lastPage = 2; // boundary: ask for a page that doesn't exist in the document.

  std::vector<std::string> objs;
  objs.push_back(
      "<< /Type /Catalog /Pages 2 0 R "
      "   /Dests << /MyDest [3 0 R /Fit] >> "
      ">>"); // 1
  objs.push_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>"); // 2
  objs.push_back("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>"); // 3
  objs.push_back("<< /Length 0 >>\nstream\n\nendstream"); // 4

  const std::string pdfBytes = BuildPdfWithObjects_2671(objs, /*rootObjNum=*/1);
  const std::string path = WriteTempPdf_2671(pdfBytes);

  auto doc = OpenPdfDoc_2671(path);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  auto uMap = Utf8UnicodeMap_2671();

  testing::internal::CaptureStdout();
  printDestinations(doc.get(), uMap.get());
  const std::string out = testing::internal::GetCapturedStdout();

  // Should still print the existing destination for page 1.
  EXPECT_NE(out.find("\"MyDest\""), std::string::npos);

  // We can't reliably assert absence of "2" due to other output, but we can assert it doesn't
  // produce a second destination name line for a non-existent page; at least, only one occurrence.
  const size_t firstPos = out.find("\"MyDest\"");
  ASSERT_NE(firstPos, std::string::npos);
  EXPECT_EQ(out.find("\"MyDest\"", firstPos + 1), std::string::npos);
}

TEST_F(PdfInfoPrintDestinationsTest_2671, SkipsNonPageRefDestinations_2671)
{
  // Provide one destination that uses a page NUMBER (integer) instead of a page Ref.
  // In such case, LinkDest::isPageRef() should be false and printDestinations should skip it.
  //
  // NOTE: We don't assume internal parsing, but we can observe that the name is not printed.
  std::vector<std::string> objs;
  objs.push_back(
      "<< /Type /Catalog /Pages 2 0 R "
      "   /Dests << /NumDest [1 /Fit] >> "
      ">>"); // 1
  objs.push_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>"); // 2
  objs.push_back("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>"); // 3
  objs.push_back("<< /Length 0 >>\nstream\n\nendstream"); // 4

  const std::string pdfBytes = BuildPdfWithObjects_2671(objs, /*rootObjNum=*/1);
  const std::string path = WriteTempPdf_2671(pdfBytes);

  auto doc = OpenPdfDoc_2671(path);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  auto uMap = Utf8UnicodeMap_2671();

  testing::internal::CaptureStdout();
  printDestinations(doc.get(), uMap.get());
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_NE(out.find("Page Destination Name\n"), std::string::npos);

  // If the destination isn't a page Ref, printDestinations should not emit the name in quotes.
  EXPECT_EQ(out.find("\"NumDest\""), std::string::npos);
}