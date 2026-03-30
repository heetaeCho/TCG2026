// TEST_ID 801
// File: annotmarkup_isinreplyto_801_test.cc

#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "poppler/Annot.h"
#include "poppler/GlobalParams.h"
#include "poppler/PDFDoc.h"
#include "poppler/Page.h"

// Poppler uses a global GlobalParams*
extern GlobalParams *globalParams;

namespace {

class AnnotMarkupTest_801 : public ::testing::Test {
protected:
  void SetUp() override {
    if (!globalParams) {
      globalParams = new GlobalParams();
      ownsGlobalParams_ = true;
    }
  }

  void TearDown() override {
    if (ownsGlobalParams_) {
      delete globalParams;
      globalParams = nullptr;
      ownsGlobalParams_ = false;
    }
  }

  static std::string BuildPdfWithTwoTextAnnots(bool includeIrt, bool irtIsNull = false) {
    // Object numbers:
    // 1: Catalog
    // 2: Pages
    // 3: Page
    // 4: Contents (empty)
    // 5: Annot 1 (Text)
    // 6: Annot 2 (Text) optionally /IRT 5 0 R
    std::vector<std::string> objs;
    objs.reserve(6);

    objs.push_back("<< /Type /Catalog /Pages 2 0 R >>");

    objs.push_back("<< /Type /Pages /Count 1 /Kids [3 0 R] >>");

    objs.push_back("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
                  "   /Contents 4 0 R\n"
                  "   /Annots [5 0 R 6 0 R]\n"
                  ">>");

    objs.push_back("<< /Length 0 >>\nstream\n\nendstream");

    objs.push_back("<< /Type /Annot /Subtype /Text /Rect [10 10 20 20]\n"
                  "   /Contents (A)\n"
                  ">>");

    {
      std::ostringstream a2;
      a2 << "<< /Type /Annot /Subtype /Text /Rect [30 30 40 40]\n"
            "   /Contents (B)\n";
      if (includeIrt) {
        if (irtIsNull) {
          a2 << "   /IRT null\n";
        } else {
          a2 << "   /IRT 5 0 R\n";
        }
      }
      a2 << ">>";
      objs.push_back(a2.str());
    }

    std::ostringstream pdf;
    pdf << "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n";

    // Write objects and record offsets.
    std::vector<long> offsets;
    offsets.resize(objs.size() + 1);
    offsets[0] = 0;

    for (size_t i = 0; i < objs.size(); ++i) {
      offsets[i + 1] = static_cast<long>(pdf.tellp());
      const int objNum = static_cast<int>(i + 1);
      pdf << objNum << " 0 obj\n" << objs[i] << "\nendobj\n";
    }

    const long xrefPos = static_cast<long>(pdf.tellp());
    const int size = static_cast<int>(objs.size()) + 1;

    pdf << "xref\n0 " << size << "\n";
    pdf << "0000000000 65535 f \n";
    for (int i = 1; i < size; ++i) {
      pdf << std::setw(10) << std::setfill('0') << offsets[i] << " 00000 n \n";
    }

    pdf << "trailer\n"
           "<< /Size "
        << size << " /Root 1 0 R >>\n";
    pdf << "startxref\n" << xrefPos << "\n%%EOF\n";

    return pdf.str();
  }

  static std::string WriteTempPdf(const std::string &bytes) {
    // Use a deterministic-ish filename per process; overwrite is fine for tests.
    std::ostringstream path;
    path << "/tmp/poppler_annotmarkup_801_" << ::getpid() << ".pdf";
    const std::string p = path.str();

    std::ofstream out(p, std::ios::binary | std::ios::trunc);
    out.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
    out.close();
    return p;
  }

  static std::unique_ptr<PDFDoc> OpenDocOrFail(const std::string &path) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(path.c_str()));
    EXPECT_TRUE(doc);
    EXPECT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isEncrypted());
    return doc;
  }

  static std::pair<AnnotMarkup *, AnnotMarkup *> GetTwoMarkupAnnotsOrFail(PDFDoc &doc) {
    Page *page = doc.getPage(1);
    EXPECT_NE(page, nullptr);

    Annots *annots = page->getAnnots();
    EXPECT_NE(annots, nullptr);

    AnnotMarkup *first = nullptr;
    AnnotMarkup *second = nullptr;

    const int n = annots->getNumAnnots();
    EXPECT_GE(n, 2);

    // Find first two annotations that are (or derive from) AnnotMarkup.
    for (int i = 0; i < n; ++i) {
      Annot *a = annots->getAnnot(i);
      if (!a) continue;
      auto *m = dynamic_cast<AnnotMarkup *>(a);
      if (!m) continue;
      if (!first) first = m;
      else if (!second) {
        second = m;
        break;
      }
    }

    EXPECT_NE(first, nullptr);
    EXPECT_NE(second, nullptr);
    return {first, second};
  }

private:
  bool ownsGlobalParams_ = false;
};

TEST_F(AnnotMarkupTest_801, IsInReplyTo_FalseWhenNoIrt_801) {
  const std::string pdfBytes = BuildPdfWithTwoTextAnnots(/*includeIrt=*/false);
  const std::string path = WriteTempPdf(pdfBytes);

  auto doc = OpenDocOrFail(path);
  auto [a1, a2] = GetTwoMarkupAnnotsOrFail(*doc);

  EXPECT_FALSE(a1->isInReplyTo());
  EXPECT_FALSE(a2->isInReplyTo());

  std::remove(path.c_str());
}

TEST_F(AnnotMarkupTest_801, IsInReplyTo_TrueWhenIrtIsPresent_801) {
  const std::string pdfBytes = BuildPdfWithTwoTextAnnots(/*includeIrt=*/true, /*irtIsNull=*/false);
  const std::string path = WriteTempPdf(pdfBytes);

  auto doc = OpenDocOrFail(path);
  auto [a1, a2] = GetTwoMarkupAnnotsOrFail(*doc);

  // First annotation has no /IRT; second points to first.
  EXPECT_FALSE(a1->isInReplyTo());
  EXPECT_TRUE(a2->isInReplyTo());

  std::remove(path.c_str());
}

TEST_F(AnnotMarkupTest_801, IsInReplyTo_FalseWhenIrtIsNull_801) {
  const std::string pdfBytes = BuildPdfWithTwoTextAnnots(/*includeIrt=*/true, /*irtIsNull=*/true);
  const std::string path = WriteTempPdf(pdfBytes);

  auto doc = OpenDocOrFail(path);
  auto [a1, a2] = GetTwoMarkupAnnotsOrFail(*doc);

  // Boundary-ish: /IRT exists but is null in the PDF.
  EXPECT_FALSE(a1->isInReplyTo());
  EXPECT_FALSE(a2->isInReplyTo());

  std::remove(path.c_str());
}

} // namespace