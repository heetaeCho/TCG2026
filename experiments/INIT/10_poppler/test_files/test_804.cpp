// TEST_ID 804
// File: annotmarkup_getreplyto_test.cpp

#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <memory>
#include <string>
#include <type_traits>

#include "Annot.h"

// Poppler headers (names/paths vary slightly across versions; keep includes minimal)
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"
#include "PDFDocFactory.h"
#include "ErrorCodes.h"
#include "goo/gfile.h"

namespace {

// Creates a tiny, valid one-page PDF on disk and returns its path.
static std::string writeMinimalPdfToTempFile() {
  // Minimal PDF that many parsers accept (1 page, empty content stream).
  static const char kPdf[] =
      "%PDF-1.4\n"
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R >>\n"
      "endobj\n"
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n"
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>\n"
      "endobj\n"
      "4 0 obj\n"
      "<< /Length 0 >>\n"
      "stream\n"
      "\n"
      "endstream\n"
      "endobj\n"
      "xref\n"
      "0 5\n"
      "0000000000 65535 f \n"
      "0000000009 00000 n \n"
      "0000000058 00000 n \n"
      "0000000115 00000 n \n"
      "0000000202 00000 n \n"
      "trailer\n"
      "<< /Size 5 /Root 1 0 R >>\n"
      "startxref\n"
      "0249\n"
      "%%EOF\n";

  // Use a simple temp filename pattern.
  // (Poppler test harnesses often run in a writable temp dir.)
  const std::string path = "poppler_test_minimal_804.pdf";
  std::ofstream os(path, std::ios::binary | std::ios::trunc);
  os.write(kPdf, static_cast<std::streamsize>(sizeof(kPdf) - 1));
  os.close();
  return path;
}

// Helper: create a PDFDoc across Poppler API variations.
static std::unique_ptr<PDFDoc> openPdfDoc(const std::string& path) {
  auto fileName = std::make_unique<GooString>(path.c_str());

  // Prefer factory if available.
#if defined(POPPLER_HAS_PDFDOCFACTORY) || __has_include("PDFDocFactory.h")
  // Some versions use PDFDocFactory::createPDFDoc(std::unique_ptr<GooString>, ...)
  // Some use PDFDocFactory().createPDFDoc(...)
  // Try common patterns via SFINAE.
  {
    // Pattern A: static createPDFDoc
    if constexpr (std::is_same_v<
                      decltype(PDFDocFactory::createPDFDoc(std::move(fileName))),
                      std::unique_ptr<PDFDoc>>) {
      // Not reachable as-is because we moved fileName; keep below patterns instead.
    }
  }
#endif

  // Fallbacks using constructible checks.
  // NOTE: We keep multiple attempts; only one should be viable for the actual Poppler in this repo.
  if constexpr (std::is_constructible_v<PDFDoc, std::unique_ptr<GooString>>) {
    return std::make_unique<PDFDoc>(std::move(fileName));
  }

  if constexpr (std::is_constructible_v<PDFDoc, GooString*>) {
    // Older APIs take raw GooString* and assume ownership varies; use release().
    return std::make_unique<PDFDoc>(fileName.release());
  }

  if constexpr (std::is_constructible_v<PDFDoc, std::unique_ptr<GooString>, GooString*, GooString*>) {
    return std::make_unique<PDFDoc>(std::move(fileName), nullptr, nullptr);
  }

  // As a last resort, try PDFDocFactory if present (runtime construction patterns).
#if __has_include("PDFDocFactory.h")
  {
    PDFDocFactory factory;
    // Common signature: createPDFDoc(std::unique_ptr<GooString>, const std::optional<GooString>&, ...)
    // We attempt the simplest overload by passing only the filename.
    // If the overload doesn't exist, this block will fail to compile; guarded by if constexpr above would be nicer,
    // but the exact factory signatures vary a lot.
    // So we keep the compilation-safe path above as the primary route.
    (void)factory;
  }
#endif

  return nullptr;
}

struct TempFileCleaner {
  explicit TempFileCleaner(std::string p) : path(std::move(p)) {}
  ~TempFileCleaner() { std::remove(path.c_str()); }
  std::string path;
};

}  // namespace

class AnnotMarkupTest_804 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure globalParams exists (many Poppler objects expect it).
    if (!globalParams) {
      globalParams = std::make_unique<GlobalParams>();
    }
  }
};

TEST_F(AnnotMarkupTest_804, GetReplyTo_IsCallableOnConst_804) {
  const std::string pdfPath = writeMinimalPdfToTempFile();
  TempFileCleaner cleaner(pdfPath);

  auto doc = openPdfDoc(pdfPath);
  ASSERT_NE(doc, nullptr);

  PDFRectangle rect(0, 0, 10, 10);
  AnnotMarkup annot(doc.get(), &rect);

  const AnnotMarkup& cref = annot;
  // Behavior under test: method is callable on const object and returns a value.
  (void)cref.getReplyTo();
}

TEST_F(AnnotMarkupTest_804, GetReplyTo_IsStableAcrossRepeatedCalls_804) {
  const std::string pdfPath = writeMinimalPdfToTempFile();
  TempFileCleaner cleaner(pdfPath);

  auto doc = openPdfDoc(pdfPath);
  ASSERT_NE(doc, nullptr);

  PDFRectangle rect(0, 0, 10, 10);
  AnnotMarkup annot(doc.get(), &rect);

  const auto v1 = annot.getReplyTo();
  const auto v2 = annot.getReplyTo();
  const auto v3 = annot.getReplyTo();

  // Observable behavior: repeated calls should be consistent for the same object state.
  EXPECT_EQ(v1, v2);
  EXPECT_EQ(v2, v3);
}

TEST_F(AnnotMarkupTest_804, GetReplyTo_NotAffectedByUnrelatedMutators_804) {
  const std::string pdfPath = writeMinimalPdfToTempFile();
  TempFileCleaner cleaner(pdfPath);

  auto doc = openPdfDoc(pdfPath);
  ASSERT_NE(doc, nullptr);

  PDFRectangle rect(0, 0, 10, 10);
  AnnotMarkup annot(doc.get(), &rect);

  const auto before = annot.getReplyTo();

  // Mutators that are unrelated to "replyTo" conceptually (based on public API names).
  // We do not assume what they do internally; we only observe getReplyTo output.
  annot.setOpacity(0.0);
  annot.setOpacity(1.0);

  const auto after = annot.getReplyTo();
  EXPECT_EQ(before, after);
}

TEST_F(AnnotMarkupTest_804, GetReplyTo_SurvivesBoundaryOpacityValues_804) {
  const std::string pdfPath = writeMinimalPdfToTempFile();
  TempFileCleaner cleaner(pdfPath);

  auto doc = openPdfDoc(pdfPath);
  ASSERT_NE(doc, nullptr);

  PDFRectangle rect(0, 0, 10, 10);
  AnnotMarkup annot(doc.get(), &rect);

  const auto baseline = annot.getReplyTo();

  // Boundary-ish doubles. We are not asserting opacity behavior itself,
  // only that getReplyTo remains observable and consistent.
  annot.setOpacity(-1.0);
  EXPECT_EQ(baseline, annot.getReplyTo());

  annot.setOpacity(0.0);
  EXPECT_EQ(baseline, annot.getReplyTo());

  annot.setOpacity(1.0);
  EXPECT_EQ(baseline, annot.getReplyTo());

  annot.setOpacity(2.0);
  EXPECT_EQ(baseline, annot.getReplyTo());
}