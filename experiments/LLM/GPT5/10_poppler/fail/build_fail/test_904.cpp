// TEST_ID: 904
// File: formfieldtext_isMultiline_904_test.cc

#include <gtest/gtest.h>

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#if __has_include("poppler/PDFDoc.h")
#  include "poppler/PDFDoc.h"
#  include "poppler/Catalog.h"
#  include "poppler/Form.h"
#  include "poppler/GooString.h"
#elif __has_include("PDFDoc.h")
#  include "PDFDoc.h"
#  include "Catalog.h"
#  include "Form.h"
#  include "GooString.h"
#else
#  include "Form.h"
#endif

namespace {

static std::string WriteTempPdf_904(const std::string &pdfBytes, const char *fileName)
{
#ifdef _WIN32
  const char *tmpDir = std::getenv("TEMP");
  std::string base = tmpDir ? tmpDir : ".";
  std::string path = base + "\\" + fileName;
#else
  const char *tmpDir = std::getenv("TMPDIR");
  std::string base = tmpDir ? tmpDir : "/tmp";
  std::string path = base + "/" + fileName;
#endif

  std::ofstream out(path, std::ios::binary);
  out.write(pdfBytes.data(), static_cast<std::streamsize>(pdfBytes.size()));
  out.close();
  return path;
}

// Minimal, self-contained PDFs for exercising text field flags.
// We keep them tiny but valid enough for poppler to parse.
static std::string MakePdfWithTextFieldFf_904(std::optional<int> ffValue)
{
  // Notes:
  // - /AcroForm with /Fields containing one text field (/FT /Tx)
  // - One page with a widget annotation referencing the field via /Parent
  // - If ffValue is not set, omit /Ff completely.
  //
  // Cross-reference offsets are computed below to avoid relying on hardcoded values.

  auto obj = [](int n, const std::string &body) {
    return std::to_string(n) + " 0 obj\n" + body + "\nendobj\n";
  };

  std::string ffd;
  if (ffValue.has_value()) {
    ffd = "/Ff " + std::to_string(*ffValue) + " ";
  }

  // Objects:
  // 1: Catalog
  // 2: Pages
  // 3: Page
  // 4: AcroForm
  // 5: Field (text)
  // 6: Widget annotation

  std::vector<std::string> objects;
  objects.push_back(obj(1, "<< /Type /Catalog /Pages 2 0 R /AcroForm 4 0 R >>"));
  objects.push_back(obj(2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>"));
  objects.push_back(obj(3, "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Annots [6 0 R] >>"));
  objects.push_back(obj(4, "<< /Fields [5 0 R] >>"));

  // Text field dictionary. Keep it as a terminal field with one kid widget.
  objects.push_back(obj(5, "<< /FT /Tx " + ffd + "/T (t1) /Kids [6 0 R] >>"));

  // Widget annotation pointing back to field as /Parent.
  objects.push_back(obj(6, "<< /Type /Annot /Subtype /Widget /Rect [10 10 190 40] /Parent 5 0 R >>"));

  std::string header = "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n";
  std::string body;
  body.reserve(2048);

  std::vector<long long> offsets;
  offsets.push_back(0); // xref requires entry for object 0

  body += header;

  for (size_t i = 0; i < objects.size(); ++i) {
    offsets.push_back(static_cast<long long>(body.size()));
    body += objects[i];
  }

  long long xrefPos = static_cast<long long>(body.size());
  body += "xref\n0 7\n";
  body += "0000000000 65535 f \n";
  for (size_t i = 1; i < offsets.size(); ++i) {
    char buf[64];
    std::snprintf(buf, sizeof(buf), "%010lld 00000 n \n", offsets[i]);
    body += buf;
  }

  body += "trailer\n<< /Size 7 /Root 1 0 R >>\n";
  body += "startxref\n" + std::to_string(xrefPos) + "\n%%EOF\n";
  return body;
}

static std::unique_ptr<PDFDoc> OpenDoc_904(const std::string &path)
{
  auto gs = std::make_unique<GooString>(path.c_str());
  auto doc = std::make_unique<PDFDoc>(std::move(gs));
  if (!doc || !doc->isOk()) {
    return nullptr;
  }
  return doc;
}

static FormFieldText *GetSingleTextField_904(PDFDoc *doc)
{
  if (!doc) {
    return nullptr;
  }
  Catalog *cat = doc->getCatalog();
  if (!cat) {
    return nullptr;
  }
  Form *form = cat->getForm();
  if (!form) {
    return nullptr;
  }

  // Common poppler Form API patterns:
  // - getNumFields() / getField(i)
  // If your poppler build uses different names, adjust accordingly.
  if (form->getNumFields() < 1) {
    return nullptr;
  }

  FormField *ff = form->getField(0);
  return dynamic_cast<FormFieldText *>(ff);
}

} // namespace

// -----------------------
// Tests (TEST_ID: 904)
// -----------------------

TEST(FormFieldTextTest_904, IsMultiline_DefaultWithoutFfFlag_IsFalse_904)
{
  const std::string pdf = MakePdfWithTextFieldFf_904(std::nullopt);
  const std::string path = WriteTempPdf_904(pdf, "poppler_formfieldtext_noff_904.pdf");

  auto doc = OpenDoc_904(path);
  ASSERT_NE(doc, nullptr);

  FormFieldText *field = GetSingleTextField_904(doc.get());
  ASSERT_NE(field, nullptr);

  EXPECT_FALSE(field->isMultiline());
}

TEST(FormFieldTextTest_904, IsMultiline_WithMultilineFlag_IsTrue_904)
{
  // PDF spec: for text fields, Multiline flag is bit 13 -> 1<<12 = 4096.
  const int kMultiline = 4096;

  const std::string pdf = MakePdfWithTextFieldFf_904(kMultiline);
  const std::string path = WriteTempPdf_904(pdf, "poppler_formfieldtext_multiline_904.pdf");

  auto doc = OpenDoc_904(path);
  ASSERT_NE(doc, nullptr);

  FormFieldText *field = GetSingleTextField_904(doc.get());
  ASSERT_NE(field, nullptr);

  EXPECT_TRUE(field->isMultiline());
}

TEST(FormFieldTextTest_904, IsMultiline_WithOtherFlagOnly_IsFalse_904)
{
  // Use a different text-field flag than multiline (e.g., Password bit 14 -> 1<<13 = 8192).
  // The behavior under test: isMultiline() should reflect multiline, not unrelated bits.
  const int kPassword = 8192;

  const std::string pdf = MakePdfWithTextFieldFf_904(kPassword);
  const std::string path = WriteTempPdf_904(pdf, "poppler_formfieldtext_otherflag_904.pdf");

  auto doc = OpenDoc_904(path);
  ASSERT_NE(doc, nullptr);

  FormFieldText *field = GetSingleTextField_904(doc.get());
  ASSERT_NE(field, nullptr);

  EXPECT_FALSE(field->isMultiline());
}

TEST(FormFieldTextTest_904, IsMultiline_WithMultilinePlusOtherFlag_IsTrue_904)
{
  const int kMultiline = 4096;
  const int kPassword = 8192;

  const std::string pdf = MakePdfWithTextFieldFf_904(kMultiline | kPassword);
  const std::string path = WriteTempPdf_904(pdf, "poppler_formfieldtext_multi_plus_other_904.pdf");

  auto doc = OpenDoc_904(path);
  ASSERT_NE(doc, nullptr);

  FormFieldText *field = GetSingleTextField_904(doc.get());
  ASSERT_NE(field, nullptr);

  EXPECT_TRUE(field->isMultiline());
}

TEST(FormFieldTextTest_904, IsMultiline_AfterSetContent_DoesNotChangeMultiline_904)
{
  const int kMultiline = 4096;

  const std::string pdf = MakePdfWithTextFieldFf_904(kMultiline);
  const std::string path = WriteTempPdf_904(pdf, "poppler_formfieldtext_setcontent_904.pdf");

  auto doc = OpenDoc_904(path);
  ASSERT_NE(doc, nullptr);

  FormFieldText *field = GetSingleTextField_904(doc.get());
  ASSERT_NE(field, nullptr);

  ASSERT_TRUE(field->isMultiline());

  // External interaction through public API: changing content should not affect the multiline flag.
  field->setContent(std::make_unique<GooString>("hello"));
  EXPECT_TRUE(field->isMultiline());

  field->setContent(std::make_unique<GooString>(""));
  EXPECT_TRUE(field->isMultiline());
}

TEST(FormFieldTextTest_904, IsMultiline_ErrorCase_NoFormOrNoFields_HandledGracefully_904)
{
  // Exceptional/edge: a PDF without /AcroForm should yield no Form/fields.
  // Observable behavior: our accessor returns nullptr; test ensures we don't crash.
  const std::string minimalPdf =
      "%PDF-1.4\n"
      "%\xE2\xE3\xCF\xD3\n"
      "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
      "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
      "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] >>\nendobj\n"
      "xref\n0 4\n"
      "0000000000 65535 f \n"
      "0000000015 00000 n \n"
      "0000000064 00000 n \n"
      "0000000121 00000 n \n"
      "trailer\n<< /Size 4 /Root 1 0 R >>\n"
      "startxref\n185\n"
      "%%EOF\n";

  const std::string path = WriteTempPdf_904(minimalPdf, "poppler_formfieldtext_nofrom_904.pdf");
  auto doc = OpenDoc_904(path);
  ASSERT_NE(doc, nullptr);

  FormFieldText *field = GetSingleTextField_904(doc.get());
  EXPECT_EQ(field, nullptr);
}