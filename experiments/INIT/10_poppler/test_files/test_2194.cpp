// TEST_ID: 2194
//
// Unit tests for poppler_document_get_signature_fields()
// File: ./TestProjects/poppler/glib/poppler-document.cc
//
// Notes:
// - Treat implementation as a black box.
// - Tests exercise observable behavior via public Poppler GLib API.
// - We construct minimal in-memory PDFs to control presence/shape of signature fields.

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace {

std::string BuildPdfFromObjects(const std::vector<std::string> &objects) {
  // objects[i] corresponds to object number (i+1) with generation 0.
  std::string pdf;
  pdf.reserve(4096);
  pdf += "%PDF-1.4\n%";
  // Binary marker comment as commonly used in PDFs.
  pdf.push_back(static_cast<char>(0xE2));
  pdf.push_back(static_cast<char>(0xE3));
  pdf.push_back(static_cast<char>(0xCF));
  pdf.push_back(static_cast<char>(0xD3));
  pdf += "\n";

  std::vector<size_t> offsets;
  offsets.reserve(objects.size() + 1);
  offsets.push_back(0); // xref entry 0 (free)

  for (size_t i = 0; i < objects.size(); ++i) {
    offsets.push_back(pdf.size());
    pdf += std::to_string(i + 1);
    pdf += " 0 obj\n";
    pdf += objects[i];
    pdf += "\nendobj\n";
  }

  const size_t xref_offset = pdf.size();
  pdf += "xref\n";
  pdf += "0 ";
  pdf += std::to_string(objects.size() + 1);
  pdf += "\n";
  pdf += "0000000000 65535 f \n";

  for (size_t i = 1; i < offsets.size(); ++i) {
    std::ostringstream line;
    line << std::setw(10) << std::setfill('0') << static_cast<unsigned long long>(offsets[i])
         << " 00000 n \n";
    pdf += line.str();
  }

  pdf += "trailer\n";
  pdf += "<< /Size ";
  pdf += std::to_string(objects.size() + 1);
  pdf += " /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_offset);
  pdf += "\n%%EOF\n";
  return pdf;
}

PopplerDocument *LoadPopplerDocumentFromData(const std::string &pdf_data) {
  GError *error = nullptr;
  PopplerDocument *doc =
      poppler_document_new_from_data(pdf_data.c_str(),
                                     static_cast<int>(pdf_data.size()),
                                     /*password=*/nullptr,
                                     &error);
  if (!doc) {
    if (error) {
      g_error_free(error);
    }
  } else {
    if (error) {
      g_error_free(error);
    }
  }
  return doc;
}

int GListLengthSafe(GList *lst) {
  return lst ? static_cast<int>(g_list_length(lst)) : 0;
}

void FreeFormFieldList(GList *lst) {
  if (!lst) {
    return;
  }
  g_list_free_full(lst, reinterpret_cast<GDestroyNotify>(g_object_unref));
}

} // namespace

class PopplerDocumentGetSignatureFieldsTest_2194 : public ::testing::Test {
protected:
  void TearDown() override {
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
  }

  void Load(const std::string &pdf) {
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
    doc_ = LoadPopplerDocumentFromData(pdf);
    ASSERT_NE(doc_, nullptr);
  }

  PopplerDocument *doc_ = nullptr;
};

TEST_F(PopplerDocumentGetSignatureFieldsTest_2194, ReturnsNullWhenNoAcroForm_2194) {
  // PDF with no /AcroForm -> should have no signature fields.
  // Objects:
  // 1: Catalog
  // 2: Pages
  // 3: Page
  // 4: Empty contents
  std::vector<std::string> objs;
  objs.emplace_back("<< /Type /Catalog /Pages 2 0 R >>");
  objs.emplace_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");
  objs.emplace_back("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 300 300] /Contents 4 0 R >>");
  objs.emplace_back("<< /Length 0 >>\nstream\n\nendstream");

  Load(BuildPdfFromObjects(objs));

  GList *fields = poppler_document_get_signature_fields(doc_);
  EXPECT_EQ(fields, nullptr);
  FreeFormFieldList(fields);
}

TEST_F(PopplerDocumentGetSignatureFieldsTest_2194, ReturnsEmptyWhenSigFieldHasNoWidget_2194) {
  // /AcroForm has a /Sig field, but it has no /Kids widget annotation.
  // poppler_document_get_signature_fields() filters out fields whose getCreateWidget() is nullptr.
  //
  // 1: Catalog (with AcroForm)
  // 2: Pages
  // 3: Page (no Annots)
  // 4: Contents
  // 5: AcroForm (Fields [6 0 R])
  // 6: Signature field dict (no Kids)
  std::vector<std::string> objs;
  objs.emplace_back("<< /Type /Catalog /Pages 2 0 R /AcroForm 5 0 R >>");
  objs.emplace_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");
  objs.emplace_back("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 300 300] /Contents 4 0 R >>");
  objs.emplace_back("<< /Length 0 >>\nstream\n\nendstream");
  objs.emplace_back("<< /Fields [6 0 R] /SigFlags 3 >>");
  objs.emplace_back("<< /FT /Sig /T (SigNoWidget) >>");

  Load(BuildPdfFromObjects(objs));

  GList *fields = poppler_document_get_signature_fields(doc_);
  EXPECT_EQ(GListLengthSafe(fields), 0);
  FreeFormFieldList(fields);
}

TEST_F(PopplerDocumentGetSignatureFieldsTest_2194, ReturnsSingleSignatureField_2194) {
  // Minimal signature field with a widget annotation on the page.
  //
  // 1: Catalog (with AcroForm)
  // 2: Pages
  // 3: Page (Annots [7])
  // 4: Contents
  // 5: AcroForm (Fields [6])
  // 6: Signature field dict (Kids [7])
  // 7: Widget annotation (Parent 6, P 3)
  std::vector<std::string> objs;
  objs.emplace_back("<< /Type /Catalog /Pages 2 0 R /AcroForm 5 0 R >>");
  objs.emplace_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");
  objs.emplace_back(
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 300 300] /Contents 4 0 R /Annots [7 0 R] >>");
  objs.emplace_back("<< /Length 0 >>\nstream\n\nendstream");
  objs.emplace_back("<< /Fields [6 0 R] /SigFlags 3 >>");
  objs.emplace_back("<< /FT /Sig /T (Sig1) /Kids [7 0 R] >>");
  objs.emplace_back(
      "<< /Type /Annot /Subtype /Widget /FT /Sig /Parent 6 0 R /Rect [10 10 50 30] /P 3 0 R >>");

  Load(BuildPdfFromObjects(objs));

  GList *fields = poppler_document_get_signature_fields(doc_);
  ASSERT_EQ(GListLengthSafe(fields), 1);

  auto *field = POPPLER_FORM_FIELD(fields->data);
  ASSERT_NE(field, nullptr);

  EXPECT_EQ(poppler_form_field_get_field_type(field), POPPLER_FORM_FIELD_SIGNATURE);

  const char *name = poppler_form_field_get_name(field);
  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name, "Sig1");

  FreeFormFieldList(fields);
}

TEST_F(PopplerDocumentGetSignatureFieldsTest_2194, MultipleSignatureFieldsPreserveOrder_2194) {
  // Two signature fields in AcroForm /Fields array order: SigA then SigB.
  // Implementation prepends then reverses; expected observable order should match original.
  //
  // 1: Catalog (with AcroForm)
  // 2: Pages
  // 3: Page (Annots [7 9])
  // 4: Contents
  // 5: AcroForm (Fields [6 8])
  // 6: Sig field A (Kids [7])
  // 7: Widget A
  // 8: Sig field B (Kids [9])
  // 9: Widget B
  std::vector<std::string> objs;
  objs.emplace_back("<< /Type /Catalog /Pages 2 0 R /AcroForm 5 0 R >>");
  objs.emplace_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");
  objs.emplace_back(
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 300 300] /Contents 4 0 R /Annots [7 0 R 9 0 R] >>");
  objs.emplace_back("<< /Length 0 >>\nstream\n\nendstream");
  objs.emplace_back("<< /Fields [6 0 R 8 0 R] /SigFlags 3 >>");
  objs.emplace_back("<< /FT /Sig /T (SigA) /Kids [7 0 R] >>");
  objs.emplace_back(
      "<< /Type /Annot /Subtype /Widget /FT /Sig /Parent 6 0 R /Rect [10 10 50 30] /P 3 0 R >>");
  objs.emplace_back("<< /FT /Sig /T (SigB) /Kids [9 0 R] >>");
  objs.emplace_back(
      "<< /Type /Annot /Subtype /Widget /FT /Sig /Parent 8 0 R /Rect [10 40 50 60] /P 3 0 R >>");

  Load(BuildPdfFromObjects(objs));

  GList *fields = poppler_document_get_signature_fields(doc_);
  ASSERT_EQ(GListLengthSafe(fields), 2);

  auto *field0 = POPPLER_FORM_FIELD(g_list_nth_data(fields, 0));
  auto *field1 = POPPLER_FORM_FIELD(g_list_nth_data(fields, 1));
  ASSERT_NE(field0, nullptr);
  ASSERT_NE(field1, nullptr);

  EXPECT_EQ(poppler_form_field_get_field_type(field0), POPPLER_FORM_FIELD_SIGNATURE);
  EXPECT_EQ(poppler_form_field_get_field_type(field1), POPPLER_FORM_FIELD_SIGNATURE);

  const char *name0 = poppler_form_field_get_name(field0);
  const char *name1 = poppler_form_field_get_name(field1);
  ASSERT_NE(name0, nullptr);
  ASSERT_NE(name1, nullptr);

  EXPECT_STREQ(name0, "SigA");
  EXPECT_STREQ(name1, "SigB");

  FreeFormFieldList(fields);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(PopplerDocumentGetSignatureFieldsTest_2194, DeathOnNullDocument_2194) {
  // The implementation dereferences `document` unconditionally; passing nullptr is an error case.
  // Observable behavior (in typical builds): process termination (segfault/assert).
  EXPECT_DEATH({ (void)poppler_document_get_signature_fields(nullptr); }, ".*");
}
#endif