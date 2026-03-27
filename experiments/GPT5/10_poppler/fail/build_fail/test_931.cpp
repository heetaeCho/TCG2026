// TEST_ID: 931
// File: form_getDefaultAppearance_test_931.cpp

#include <gtest/gtest.h>

#include <fstream>
#include <memory>
#include <string>

#include "poppler/Form.h"
#include "poppler/PDFDoc.h"
#include "poppler/GooString.h"
#include "poppler/GlobalParams.h"

namespace {

// Poppler often expects globalParams to exist.
class GlobalParamsGuard {
public:
  GlobalParamsGuard() {
    // Some builds expose globalParams as a raw pointer, others as a unique_ptr-like.
    // The most common in Poppler is `GlobalParams *globalParams`.
    if (globalParams == nullptr) {
      globalParams = new GlobalParams(nullptr);
      owned_ = true;
    }
  }
  ~GlobalParamsGuard() {
    if (owned_) {
      delete globalParams;
      globalParams = nullptr;
    }
  }

  GlobalParamsGuard(const GlobalParamsGuard&) = delete;
  GlobalParamsGuard& operator=(const GlobalParamsGuard&) = delete;

private:
  bool owned_ = false;
};

static std::string WriteMinimalPdfToTempFile() {
  // Minimal valid PDF structure (enough for many PDF parsers to open).
  // We intentionally avoid asserting anything about contents beyond "opens or not".
  const char kPdf[] =
      "%PDF-1.4\n"
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R >>\n"
      "endobj\n"
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n"
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] >>\n"
      "endobj\n"
      "xref\n"
      "0 4\n"
      "0000000000 65535 f \n"
      "0000000009 00000 n \n"
      "0000000058 00000 n \n"
      "0000000115 00000 n \n"
      "trailer\n"
      "<< /Size 4 /Root 1 0 R >>\n"
      "startxref\n"
      "0000000182\n"
      "%%EOF\n";

  // Use a deterministic-ish filename; test runners typically isolate working dirs.
  const std::string path = "poppler_form_test_931_minimal.pdf";
  std::ofstream out(path, std::ios::binary | std::ios::trunc);
  out.write(kPdf, static_cast<std::streamsize>(sizeof(kPdf) - 1));
  out.close();
  return path;
}

static std::unique_ptr<PDFDoc> CreateDocOrSkip() {
  const std::string path = WriteMinimalPdfToTempFile();
  auto fileName = std::make_unique<GooString>(path.c_str());

  // Common Poppler constructor: PDFDoc(std::unique_ptr<GooString>&& fileNameA, ...).
  // If your Poppler snapshot differs, adjust this constructor call accordingly.
  std::unique_ptr<PDFDoc> doc = std::make_unique<PDFDoc>(std::move(fileName));

  if (!doc || !doc->isOk()) {
    return nullptr;
  }
  return doc;
}

} // namespace

class FormTest_931 : public ::testing::Test {
protected:
  GlobalParamsGuard gp_;
};

TEST_F(FormTest_931, GetDefaultAppearance_IsCallableAndStableAcrossCalls_931) {
  std::unique_ptr<PDFDoc> doc = CreateDocOrSkip();
  if (!doc) {
    GTEST_SKIP() << "Unable to create a valid PDFDoc in this test environment.";
  }

  Form form(doc.get());

  const GooString* p1 = form.getDefaultAppearance();
  const GooString* p2 = form.getDefaultAppearance();
  const GooString* p3 = form.getDefaultAppearance();

  // Observable behavior: repeated calls return a pointer value; it should be stable.
  EXPECT_EQ(p1, p2);
  EXPECT_EQ(p2, p3);
}

TEST_F(FormTest_931, GetDefaultAppearance_ConsistentViaConstReference_931) {
  std::unique_ptr<PDFDoc> doc = CreateDocOrSkip();
  if (!doc) {
    GTEST_SKIP() << "Unable to create a valid PDFDoc in this test environment.";
  }

  Form form(doc.get());
  const Form& cform = form;

  const GooString* p_nonconst = form.getDefaultAppearance();
  const GooString* p_const = cform.getDefaultAppearance();

  EXPECT_EQ(p_nonconst, p_const);
}

TEST_F(FormTest_931, GetDefaultAppearance_AllowsNullReturnWithoutCrashing_931) {
  std::unique_ptr<PDFDoc> doc = CreateDocOrSkip();
  if (!doc) {
    GTEST_SKIP() << "Unable to create a valid PDFDoc in this test environment.";
  }

  Form form(doc.get());

  // We do NOT assume whether default appearance exists for a given document.
  // The observable requirement here is: the getter is safe to call and if it
  // returns nullptr, repeated calls should remain consistent.
  const GooString* p1 = form.getDefaultAppearance();
  const GooString* p2 = form.getDefaultAppearance();

  if (p1 == nullptr) {
    EXPECT_EQ(nullptr, p2);
  } else {
    EXPECT_EQ(p1, p2);
  }
}