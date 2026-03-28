// TEST_ID: 952
// File: pdfdoc_getOptContentConfig_952_test.cpp

#include <gtest/gtest.h>

#include <fstream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "poppler/PDFDoc.h"
#include "poppler/goo/GooString.h"

#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#endif

namespace {

// Builds a small, syntactically valid PDF with a classic xref table.
// `objects[0]` is object 1 0, `objects[1]` is object 2 0, etc.
static std::string BuildPdfWithXref(const std::vector<std::string> &objects) {
  std::ostringstream out;
  out << "%PDF-1.5\n";
  // Some PDFs include a binary comment line; not strictly required, but harmless.
  out << "%\xE2\xE3\xCF\xD3\n";

  std::vector<long long> offsets;
  offsets.reserve(objects.size() + 1);
  offsets.push_back(0); // obj 0 is the free object.

  for (size_t i = 0; i < objects.size(); ++i) {
    // Record byte offset for object (i+1).
    offsets.push_back(static_cast<long long>(out.tellp()));
    out << (i + 1) << " 0 obj\n";
    out << objects[i] << "\n";
    out << "endobj\n";
  }

  const long long xrefOffset = static_cast<long long>(out.tellp());
  const int size = static_cast<int>(objects.size() + 1);

  out << "xref\n";
  out << "0 " << size << "\n";
  out << "0000000000 65535 f \n";
  for (size_t i = 1; i < offsets.size(); ++i) {
    // 10-digit, zero-padded offsets, gen=00000, in-use 'n'
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010lld 00000 n \n", offsets[i]);
    out << buf;
  }

  out << "trailer\n";
  out << "<< /Size " << size << " /Root 1 0 R >>\n";
  out << "startxref\n";
  out << xrefOffset << "\n";
  out << "%%EOF\n";

  return out.str();
}

static std::string WriteTempPdfFile(const std::string &contents, const char *suffix) {
#if __has_include(<filesystem>)
  const fs::path dir = fs::temp_directory_path();
  fs::path path = dir / fs::path(std::string("poppler_pdfdoc_952_") + std::to_string(::getpid()) +
                                 "_" + std::to_string(reinterpret_cast<uintptr_t>(&contents)) + suffix);
  std::ofstream f(path, std::ios::binary);
  f.write(contents.data(), static_cast<std::streamsize>(contents.size()));
  f.close();
  return path.string();
#else
  // Fallback: write to current directory (best effort).
  std::string path = std::string("poppler_pdfdoc_952") + suffix;
  std::ofstream f(path, std::ios::binary);
  f.write(contents.data(), static_cast<std::streamsize>(contents.size()));
  f.close();
  return path;
#endif
}

static std::unique_ptr<PDFDoc> OpenDocFromPath(const std::string &path) {
  auto fileName = std::make_unique<GooString>(path.c_str());
  const std::optional<GooString> none;
  // xrefReconstructedCallback: no-op
  auto cb = []() {};
  return std::make_unique<PDFDoc>(std::move(fileName), none, none, cb);
}

static std::string MakePdfWithOCProperties() {
  std::vector<std::string> objs;

  // 1: Catalog includes OCProperties
  objs.push_back("<< /Type /Catalog /Pages 2 0 R /OCProperties 5 0 R >>");

  // 2: Pages
  objs.push_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");

  // 3: Page
  objs.push_back("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] "
                 "/Contents 4 0 R /Resources << >> >>");

  // 4: Empty content stream
  objs.push_back("<< /Length 0 >>\nstream\n\nendstream");

  // 5: OCProperties
  objs.push_back("<< /OCGs [6 0 R] /D << /Order [6 0 R] /ON [6 0 R] /OFF [] >> >>");

  // 6: OCG
  objs.push_back("<< /Type /OCG /Name (Layer1) >>");

  return BuildPdfWithXref(objs);
}

static std::string MakePdfWithoutOCProperties() {
  std::vector<std::string> objs;

  // 1: Catalog without OCProperties
  objs.push_back("<< /Type /Catalog /Pages 2 0 R >>");

  // 2: Pages
  objs.push_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");

  // 3: Page
  objs.push_back("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] "
                 "/Contents 4 0 R /Resources << >> >>");

  // 4: Empty content stream
  objs.push_back("<< /Length 0 >>\nstream\n\nendstream");

  return BuildPdfWithXref(objs);
}

} // namespace

class PDFDocTest_952 : public ::testing::Test {};

TEST_F(PDFDocTest_952, GetOptContentConfig_ReturnsNonNullWhenOCPropertiesPresent_952) {
  const std::string pdf = MakePdfWithOCProperties();
  const std::string path = WriteTempPdfFile(pdf, "_with_oc.pdf");

  auto doc = OpenDocFromPath(path);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk()) << "Failed to open generated PDF with OCProperties";

  const OCGs *cfg1 = doc->getOptContentConfig();
  EXPECT_NE(cfg1, nullptr);

  // Boundary/consistency: repeated calls should be stable for the lifetime of the document.
  const OCGs *cfg2 = doc->getOptContentConfig();
  EXPECT_EQ(cfg1, cfg2);

  // Verify external interaction (observable delegation): PDFDoc vs Catalog view should match.
  ASSERT_NE(doc->getCatalog(), nullptr);
  EXPECT_EQ(cfg1, doc->getCatalog()->getOptContentConfig());
}

TEST_F(PDFDocTest_952, GetOptContentConfig_ReturnsNullWhenOCPropertiesAbsent_952) {
  const std::string pdf = MakePdfWithoutOCProperties();
  const std::string path = WriteTempPdfFile(pdf, "_no_oc.pdf");

  auto doc = OpenDocFromPath(path);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk()) << "Failed to open generated PDF without OCProperties";

  // Boundary: no OCProperties => no optional content configuration expected via interface.
  const OCGs *cfg = doc->getOptContentConfig();
  EXPECT_EQ(cfg, nullptr);

  // And Catalog should agree (delegation consistency).
  ASSERT_NE(doc->getCatalog(), nullptr);
  EXPECT_EQ(cfg, doc->getCatalog()->getOptContentConfig());
}

TEST_F(PDFDocTest_952, GetOptContentConfig_DoesNotCrashOnValidDocs_952) {
  // This test is intentionally minimal: it asserts the call is safe on valid docs,
  // covering an "exceptional/error" angle without assuming specific internal behavior.
  const std::string pdf = MakePdfWithOCProperties();
  const std::string path = WriteTempPdfFile(pdf, "_with_oc_safety.pdf");

  auto doc = OpenDocFromPath(path);
  ASSERT_NE(doc, nullptr);
  ASSERT_TRUE(doc->isOk());

  EXPECT_NO_FATAL_FAILURE((void)doc->getOptContentConfig());
}