// pdfinfo_printUrlList_test_2672.cc
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// These globals are referenced by pdfinfo.cc (declared in other utils like pdftoppm.cc).
// In the unit-test build, we provide definitions here.
int firstPage = 1;
int lastPage = 0;

// pdfinfo.cc is a utility with a main(). Rename it away for unit testing.
#define main pdfinfo_main_for_test_2672
// Include the real implementation so we can call the TU-local static printUrlList().
#include "TestProjects/poppler/utils/pdfinfo.cc"
#undef main

#include "TestProjects/poppler/poppler/PDFDoc.h"
#include "TestProjects/poppler/goo/GooString.h"

using ::testing::HasSubstr;

namespace {

// Minimal PDF builder (writes a valid-enough PDF for Poppler to parse link annotations).
// Supports:
//  - N pages
//  - Optional link annotation per page, either URI action or non-URI (GoTo) action.
enum class LinkActionType {
  kNone,
  kUri,
  kGoTo,
};

struct PageLinkSpec {
  LinkActionType type = LinkActionType::kNone;
  std::string uri;  // used when type==kUri
};

static std::string BuildPdfBytes(const std::vector<PageLinkSpec> &pages) {
  // Object numbering plan:
  //  1 0 obj  Catalog
  //  2 0 obj  Pages
  //  3..(2+N) Page objects
  //  Then for each page:
  //    (optional) Annot object
  //    Content stream object
  //  Additionally: a simple Font object used by all pages/resources.
  //
  // We'll assemble objects as strings, compute xref offsets, then write trailer.

  const int n = static_cast<int>(pages.size());

  auto objHeader = [](int objNum) {
    std::ostringstream oss;
    oss << objNum << " 0 obj\n";
    return oss.str();
  };

  std::vector<std::string> objects;
  objects.reserve(2 + n * 3 + 4);

  // 1: Catalog (Root)
  {
    std::ostringstream oss;
    oss << objHeader(1);
    oss << "<< /Type /Catalog /Pages 2 0 R >>\n";
    oss << "endobj\n";
    objects.push_back(oss.str());
  }

  // 2: Pages (Kids filled after page objects exist, but references are known)
  {
    std::ostringstream kids;
    kids << "[ ";
    for (int i = 0; i < n; ++i) {
      kids << (3 + i) << " 0 R ";
    }
    kids << "]";

    std::ostringstream oss;
    oss << objHeader(2);
    oss << "<< /Type /Pages /Count " << n << " /Kids " << kids.str() << " >>\n";
    oss << "endobj\n";
    objects.push_back(oss.str());
  }

  // Font object number (shared)
  const int fontObjNum = 3 + n;  // after all page objects
  {
    std::ostringstream oss;
    oss << objHeader(fontObjNum);
    oss << "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n";
    oss << "endobj\n";
    objects.push_back(oss.str());
  }

  // We'll create page objects next (3..2+n). But we need to know annot/content object numbers.
  // Plan: For each page i:
  //  - pageObjNum = 3+i
  //  - contentObjNum = firstContentObj + i
  //  - annotObjNum (optional) = firstAnnotObj + i (only if link)
  //
  // We'll place objects in the file in this order:
  //  1) Catalog
  //  2) Pages
  //  3) All Page objects
  //  4) Font
  //  5) All Annots (only those needed)
  //  6) All Contents

  const int firstPageObjNum = 3;
  const int firstAnnotObjNum = fontObjNum + 1;                  // right after font
  const int firstContentObjNum = firstAnnotObjNum + n;          // reserve n ids for annots (even if unused)
  const int totalObjCount = (firstContentObjNum + n) - 1;       // last object number
  const int xrefSize = totalObjCount + 1;                       // including object 0

  // 3..2+n : Page objects
  std::vector<std::string> pageObjects;
  pageObjects.reserve(n);

  for (int i = 0; i < n; ++i) {
    const int pageObjNum = firstPageObjNum + i;
    const int annotObjNum = firstAnnotObjNum + i;
    const int contentObjNum = firstContentObjNum + i;

    std::ostringstream oss;
    oss << objHeader(pageObjNum);

    // Resources with a font to keep Poppler happy even if it ignores content.
    oss << "<< /Type /Page /Parent 2 0 R\n";
    oss << "   /MediaBox [0 0 300 300]\n";
    oss << "   /Resources << /Font << /F1 " << fontObjNum << " 0 R >> >>\n";

    if (pages[i].type != LinkActionType::kNone) {
      oss << "   /Annots [ " << annotObjNum << " 0 R ]\n";
    }

    oss << "   /Contents " << contentObjNum << " 0 R\n";
    oss << ">>\n";
    oss << "endobj\n";
    pageObjects.push_back(oss.str());
  }

  // Append page objects after the initial two objects.
  // Note: objects currently holds (1) Catalog, (2) Pages, (font) — we want page objects before font,
  // so we will rebuild in final assembly order below rather than rely on 'objects' order.

  // Annots (reserve n slots; emit a dummy unused object for pages without annots to keep xref coherent)
  std::vector<std::string> annotObjects;
  annotObjects.reserve(n);
  for (int i = 0; i < n; ++i) {
    const int annotObjNum = firstAnnotObjNum + i;

    std::ostringstream oss;
    oss << objHeader(annotObjNum);

    if (pages[i].type == LinkActionType::kUri) {
      // URI action link annotation
      oss << "<< /Type /Annot /Subtype /Link\n";
      oss << "   /Rect [10 10 100 40]\n";
      oss << "   /Border [0 0 0]\n";
      oss << "   /A << /S /URI /URI (" << pages[i].uri << ") >>\n";
      oss << ">>\n";
    } else if (pages[i].type == LinkActionType::kGoTo) {
      // Non-URI action (should not be printed by printUrlList)
      // Use a self-contained destination: go to first page /Fit.
      oss << "<< /Type /Annot /Subtype /Link\n";
      oss << "   /Rect [10 10 100 40]\n";
      oss << "   /Border [0 0 0]\n";
      oss << "   /A << /S /GoTo /D [" << firstPageObjNum << " 0 R /Fit] >>\n";
      oss << ">>\n";
    } else {
      // Dummy unused object (keeps numbering consistent)
      oss << "<< >>\n";
    }

    oss << "endobj\n";
    annotObjects.push_back(oss.str());
  }

  // Contents (simple text stream)
  std::vector<std::string> contentObjects;
  contentObjects.reserve(n);
  for (int i = 0; i < n; ++i) {
    const int contentObjNum = firstContentObjNum + i;
    const std::string streamData = "BT /F1 12 Tf 20 280 Td (Hello) Tj ET\n";

    std::ostringstream oss;
    oss << objHeader(contentObjNum);
    oss << "<< /Length " << streamData.size() << " >>\n";
    oss << "stream\n";
    oss << streamData;
    oss << "endstream\n";
    oss << "endobj\n";
    contentObjects.push_back(oss.str());
  }

  // Assemble full file and compute xref offsets.
  std::ostringstream pdf;
  pdf << "%PDF-1.4\n";

  // object 0 is free
  std::vector<std::uint64_t> offsets(xrefSize, 0);

  auto appendObj = [&](int objNum, const std::string &objText) {
    offsets[objNum] = static_cast<std::uint64_t>(pdf.tellp());
    pdf << objText;
  };

  // Order: Catalog(1), Pages(2), Page objects(3..), Font, Annots, Contents
  appendObj(1, objects[0]);  // Catalog
  appendObj(2, objects[1]);  // Pages

  for (int i = 0; i < n; ++i) {
    appendObj(firstPageObjNum + i, pageObjects[i]);
  }

  appendObj(fontObjNum, objects[2]);  // Font

  for (int i = 0; i < n; ++i) {
    appendObj(firstAnnotObjNum + i, annotObjects[i]);
  }

  for (int i = 0; i < n; ++i) {
    appendObj(firstContentObjNum + i, contentObjects[i]);
  }

  const std::uint64_t xrefPos = static_cast<std::uint64_t>(pdf.tellp());
  pdf << "xref\n";
  pdf << "0 " << xrefSize << "\n";
  pdf << "0000000000 65535 f \n";

  auto fmt10 = [](std::uint64_t v) {
    std::ostringstream oss;
    oss.width(10);
    oss.fill('0');
    oss << v;
    return oss.str();
  };

  for (int objNum = 1; objNum < xrefSize; ++objNum) {
    pdf << fmt10(offsets[objNum]) << " 00000 n \n";
  }

  pdf << "trailer\n";
  pdf << "<< /Size " << xrefSize << " /Root 1 0 R >>\n";
  pdf << "startxref\n";
  pdf << xrefPos << "\n";
  pdf << "%%EOF\n";

  return pdf.str();
}

static std::string WriteTempPdf(const std::string &bytes, const std::string &nameHint) {
  const auto dir = std::filesystem::temp_directory_path();
  const auto path = dir / (nameHint + ".pdf");

  std::ofstream out(path, std::ios::binary | std::ios::trunc);
  out.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
  out.close();

  return path.string();
}

static std::unique_ptr<PDFDoc> OpenPdfDocOrFail(const std::string &path) {
  auto fileName = std::make_unique<GooString>(path.c_str());
  std::unique_ptr<PDFDoc> doc = std::make_unique<PDFDoc>(
      std::move(fileName),
      std::optional<GooString>{},  // ownerPassword
      std::optional<GooString>{},  // userPassword
      []() {}                      // xrefReconstructedCallback
  );
  if (!doc || !doc->isOk()) {
    ADD_FAILURE() << "Failed to open PDFDoc for: " << path
                  << " errorCode=" << (doc ? doc->getErrorCode() : -1);
    return nullptr;
  }
  return doc;
}

class PrintUrlListTest_2672 : public ::testing::Test {
protected:
  void TearDown() override {
    // Reset globals to defaults to avoid cross-test coupling.
    firstPage = 1;
    lastPage = 0;
  }
};

}  // namespace

TEST_F(PrintUrlListTest_2672, PrintsHeaderEvenWhenNoPages_2672) {
  // Boundary: default lastPage=0 means loop body doesn't run, but header should still print.
  firstPage = 1;
  lastPage = 0;

  // We still need a doc pointer; create a minimal doc with 1 page but do not iterate.
  const auto pdfBytes = BuildPdfBytes({PageLinkSpec{LinkActionType::kNone, ""}});
  const auto pdfPath = WriteTempPdf(pdfBytes, "printUrlList_no_iter_2672");
  auto doc = OpenPdfDocOrFail(pdfPath);
  ASSERT_NE(doc, nullptr);

  testing::internal::CaptureStdout();
  printUrlList(doc.get());
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_THAT(out, HasSubstr("Page Type URL\n"));
  // No page lines expected when lastPage < firstPage.
  EXPECT_EQ(out, std::string("Page Type URL\n"));
}

TEST_F(PrintUrlListTest_2672, PrintsSingleUriLinkAnnotation_2672) {
  firstPage = 1;
  lastPage = 1;

  const std::string kUri = "http://example.com/a";
  const auto pdfBytes = BuildPdfBytes({PageLinkSpec{LinkActionType::kUri, kUri}});
  const auto pdfPath = WriteTempPdf(pdfBytes, "printUrlList_one_uri_2672");
  auto doc = OpenPdfDocOrFail(pdfPath);
  ASSERT_NE(doc, nullptr);

  testing::internal::CaptureStdout();
  printUrlList(doc.get());
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_THAT(out, HasSubstr("Page Type URL\n"));
  // Output format: "%4d Annotation %s\n"
  EXPECT_THAT(out, HasSubstr("   1 Annotation " + kUri + "\n"));
}

TEST_F(PrintUrlListTest_2672, PrintsMultiplePagesMultipleUriLinks_2672) {
  firstPage = 1;
  lastPage = 2;

  const std::string kUri1 = "https://example.org/one";
  const std::string kUri2 = "https://example.org/two";

  const auto pdfBytes = BuildPdfBytes({
      PageLinkSpec{LinkActionType::kUri, kUri1},
      PageLinkSpec{LinkActionType::kUri, kUri2},
  });
  const auto pdfPath = WriteTempPdf(pdfBytes, "printUrlList_two_pages_2672");
  auto doc = OpenPdfDocOrFail(pdfPath);
  ASSERT_NE(doc, nullptr);

  testing::internal::CaptureStdout();
  printUrlList(doc.get());
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_THAT(out, HasSubstr("Page Type URL\n"));
  EXPECT_THAT(out, HasSubstr("   1 Annotation " + kUri1 + "\n"));
  EXPECT_THAT(out, HasSubstr("   2 Annotation " + kUri2 + "\n"));
}

TEST_F(PrintUrlListTest_2672, DoesNotPrintNonUriLinkActions_2672) {
  firstPage = 1;
  lastPage = 1;

  // Page has a link annotation, but action is GoTo (non-URI). Should not be printed.
  const auto pdfBytes = BuildPdfBytes({PageLinkSpec{LinkActionType::kGoTo, ""}});
  const auto pdfPath = WriteTempPdf(pdfBytes, "printUrlList_goto_2672");
  auto doc = OpenPdfDocOrFail(pdfPath);
  ASSERT_NE(doc, nullptr);

  testing::internal::CaptureStdout();
  printUrlList(doc.get());
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_EQ(out, std::string("Page Type URL\n"));
}

TEST_F(PrintUrlListTest_2672, NoOutputForReversedPageRange_2672) {
  // Boundary: reversed range should behave like empty iteration (header only).
  firstPage = 2;
  lastPage = 1;

  const auto pdfBytes = BuildPdfBytes({
      PageLinkSpec{LinkActionType::kUri, "http://example.com/should_not_print"},
      PageLinkSpec{LinkActionType::kUri, "http://example.com/should_not_print2"},
  });
  const auto pdfPath = WriteTempPdf(pdfBytes, "printUrlList_reversed_range_2672");
  auto doc = OpenPdfDocOrFail(pdfPath);
  ASSERT_NE(doc, nullptr);

  testing::internal::CaptureStdout();
  printUrlList(doc.get());
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_EQ(out, std::string("Page Type URL\n"));
}