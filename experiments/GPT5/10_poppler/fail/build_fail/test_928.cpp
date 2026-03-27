// Form_getNeedAppearances_test_928.cpp
// Unit tests for poppler::Form::getNeedAppearances()
// TEST_ID: 928

#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "Form.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "goo/GooString.h"

// Poppler typically exposes a global pointer named `globalParams`.
extern GlobalParams *globalParams;

namespace {

class GlobalParamsGuard {
public:
  GlobalParamsGuard() : owned_(nullptr), installed_(false) {
    if (!globalParams) {
      owned_ = new GlobalParams();
      globalParams = owned_;
      installed_ = true;
    }
  }

  ~GlobalParamsGuard() {
    // Only delete if we installed it (avoid interfering with a harness that owns it).
    if (installed_) {
      delete owned_;
      owned_ = nullptr;
      globalParams = nullptr;
    }
  }

  GlobalParamsGuard(const GlobalParamsGuard &) = delete;
  GlobalParamsGuard &operator=(const GlobalParamsGuard &) = delete;

private:
  GlobalParams *owned_;
  bool installed_;
};

static std::string MakeTempPath(const std::string &suffix) {
#if defined(_WIN32)
  char tmpPath[L_tmpnam];
  std::tmpnam(tmpPath);
  return std::string(tmpPath) + suffix;
#else
  std::string base = "/tmp/poppler_form_test_928_XXXXXX";
  std::vector<char> buf(base.begin(), base.end());
  buf.push_back('\0');
  int fd = mkstemp(buf.data());
  if (fd >= 0) {
    close(fd);
  }
  return std::string(buf.data()) + suffix;
#endif
}

// Build a tiny, valid PDF with an /AcroForm dictionary that optionally contains /NeedAppearances.
// This is test input construction (not re-implementing Form); we only observe behavior via the public API.
static std::string WriteMinimalPdfWithNeedAppearances(std::optional<bool> needAppearances) {
  const std::string path = MakeTempPath(".pdf");

  // Objects:
  // 1 0 obj: Catalog with /AcroForm 2 0 R
  // 2 0 obj: AcroForm dict, optionally with /NeedAppearances true/false
  //
  // We'll compute xref offsets based on emitted bytes.
  std::ostringstream out;
  out << "%PDF-1.4\n";

  std::vector<long> offsets;
  offsets.reserve(3);
  offsets.push_back(0); // object 0 is the free entry

  auto mark_offset = [&]() -> long {
    // Return current size in bytes.
    return static_cast<long>(out.str().size());
  };

  // Object 1
  offsets.push_back(mark_offset());
  out << "1 0 obj\n"
      << "<< /Type /Catalog /AcroForm 2 0 R >>\n"
      << "endobj\n";

  // Object 2
  offsets.push_back(mark_offset());
  out << "2 0 obj\n"
      << "<< ";
  if (needAppearances.has_value()) {
    out << "/NeedAppearances " << (*needAppearances ? "true" : "false") << " ";
  }
  out << ">>\n"
      << "endobj\n";

  const long xref_offset = static_cast<long>(out.str().size());
  out << "xref\n"
      << "0 3\n"
      << "0000000000 65535 f \n";

  auto fmt10 = [](long v) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld", v);
    return std::string(buf);
  };

  // entries for objects 1 and 2
  out << fmt10(offsets[1]) << " 00000 n \n";
  out << fmt10(offsets[2]) << " 00000 n \n";

  out << "trailer\n"
      << "<< /Size 3 /Root 1 0 R >>\n"
      << "startxref\n"
      << xref_offset << "\n"
      << "%%EOF\n";

  std::ofstream f(path, std::ios::binary);
  f << out.str();
  f.close();

  return path;
}

static std::unique_ptr<PDFDoc> OpenPdfDoc(const std::string &path) {
  auto gs = std::make_unique<GooString>(path.c_str());
  auto doc = std::make_unique<PDFDoc>(std::move(gs));
  // We avoid asserting on internal doc state; tests below gate on "doc seems usable" where needed.
  return doc;
}

} // namespace

class FormTest_928 : public ::testing::Test {
protected:
  // Ensure Poppler global params exist for PDF parsing in environments that require it.
  GlobalParamsGuard gp_;
};

TEST_F(FormTest_928, GetNeedAppearances_StableAcrossMultipleCalls_928) {
  const std::string path = WriteMinimalPdfWithNeedAppearances(true);
  auto doc = OpenPdfDoc(path);

  ASSERT_TRUE(doc != nullptr);

  Form form(doc.get());
  const bool v1 = form.getNeedAppearances();
  const bool v2 = form.getNeedAppearances();
  const bool v3 = form.getNeedAppearances();

  EXPECT_EQ(v1, v2);
  EXPECT_EQ(v2, v3);
}

TEST_F(FormTest_928, GetNeedAppearances_ReflectsTrueInAcroFormNeedAppearances_928) {
  const std::string path = WriteMinimalPdfWithNeedAppearances(true);
  auto doc = OpenPdfDoc(path);

  ASSERT_TRUE(doc != nullptr);

  Form form(doc.get());
  EXPECT_TRUE(form.getNeedAppearances());
}

TEST_F(FormTest_928, GetNeedAppearances_ReflectsFalseInAcroFormNeedAppearances_928) {
  const std::string path = WriteMinimalPdfWithNeedAppearances(false);
  auto doc = OpenPdfDoc(path);

  ASSERT_TRUE(doc != nullptr);

  Form form(doc.get());
  EXPECT_FALSE(form.getNeedAppearances());
}

TEST_F(FormTest_928, GetNeedAppearances_MissingKeyIsDeterministicForSameInput_928) {
  // Boundary-ish: /NeedAppearances omitted.
  const std::string path = WriteMinimalPdfWithNeedAppearances(std::nullopt);
  auto doc = OpenPdfDoc(path);

  ASSERT_TRUE(doc != nullptr);

  Form form(doc.get());
  const bool first = form.getNeedAppearances();
  const bool second = form.getNeedAppearances();

  // We don't assume the default value, only that the public observable result is consistent.
  EXPECT_EQ(first, second);
}

TEST_F(FormTest_928, GetNeedAppearances_TwoFormsFromDifferentDocsAreIndependent_928) {
  const std::string pathTrue = WriteMinimalPdfWithNeedAppearances(true);
  const std::string pathFalse = WriteMinimalPdfWithNeedAppearances(false);

  auto docTrue = OpenPdfDoc(pathTrue);
  auto docFalse = OpenPdfDoc(pathFalse);

  ASSERT_TRUE(docTrue != nullptr);
  ASSERT_TRUE(docFalse != nullptr);

  Form formTrue(docTrue.get());
  Form formFalse(docFalse.get());

  EXPECT_TRUE(formTrue.getNeedAppearances());
  EXPECT_FALSE(formFalse.getNeedAppearances());
}