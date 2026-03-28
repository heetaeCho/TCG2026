// File: poppler-form-field-choice-do-spell-check-test_2343.cc

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

extern "C" {
// Function under test (implemented in poppler-form-field.cc)
gboolean poppler_form_field_choice_do_spell_check(PopplerFormField *field);
}

namespace {

static std::string BuildMinimalPdfWithSingleFormField(bool choice_field, int ff_value) {
  // Build a tiny, valid PDF with:
  // - 1 page
  // - 1 widget annotation
  // - 1 form field (either /FT /Ch or /FT /Tx)
  //
  // Objects:
  // 1  Catalog (Root) with /Pages and /AcroForm
  // 2  Pages
  // 3  Page with /Annots [5 0 R] and empty /Contents
  // 4  Contents (empty stream)
  // 5  Widget annotation, /Parent 7 0 R
  // 6  AcroForm with /Fields [7 0 R]
  // 7  Field dictionary (/FT /Ch or /Tx), /Kids [5 0 R], /Ff ff_value

  const char *ft = choice_field ? "/Ch" : "/Tx";

  std::vector<std::string> objs;
  objs.resize(7);

  // 1
  objs[0] =
      "<< /Type /Catalog\n"
      "   /Pages 2 0 R\n"
      "   /AcroForm 6 0 R\n"
      ">>\n";

  // 2
  objs[1] =
      "<< /Type /Pages\n"
      "   /Kids [3 0 R]\n"
      "   /Count 1\n"
      ">>\n";

  // 3
  objs[2] =
      "<< /Type /Page\n"
      "   /Parent 2 0 R\n"
      "   /MediaBox [0 0 200 200]\n"
      "   /Resources << >>\n"
      "   /Contents 4 0 R\n"
      "   /Annots [5 0 R]\n"
      ">>\n";

  // 4 (empty stream)
  objs[3] =
      "<< /Length 0 >>\n"
      "stream\n"
      "\n"
      "endstream\n";

  // 5 (widget)
  // Include /FT as well for robustness (some PDFs repeat /FT on widget, though field dict is authoritative).
  objs[4] =
      "<< /Type /Annot\n"
      "   /Subtype /Widget\n"
      "   /Rect [10 10 100 30]\n"
      "   /FT " +
      std::string(ft) +
      "\n"
      "   /Parent 7 0 R\n"
      "   /P 3 0 R\n"
      ">>\n";

  // 6 (AcroForm)
  objs[5] =
      "<< /Fields [7 0 R] >>\n";

  // 7 (field)
  {
    std::ostringstream oss;
    oss << "<< /FT " << ft << "\n"
        << "   /T (Field1)\n"
        << "   /Ff " << ff_value << "\n"
        << "   /Kids [5 0 R]\n"
        << ">>\n";
    objs[6] = oss.str();
  }

  std::ostringstream pdf;
  pdf << "%PDF-1.4\n";
  std::vector<long> offsets;
  offsets.reserve(objs.size() + 1);
  offsets.push_back(0);  // xref entry for object 0

  for (size_t i = 0; i < objs.size(); ++i) {
    offsets.push_back(static_cast<long>(pdf.tellp()));
    pdf << (i + 1) << " 0 obj\n" << objs[i] << "endobj\n";
  }

  const long xref_offset = static_cast<long>(pdf.tellp());
  pdf << "xref\n";
  pdf << "0 " << (objs.size() + 1) << "\n";
  pdf << "0000000000 65535 f \n";
  for (size_t i = 1; i < offsets.size(); ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld", offsets[i]);
    pdf << buf << " 00000 n \n";
  }

  pdf << "trailer\n";
  pdf << "<< /Size " << (objs.size() + 1) << "\n"
      << "   /Root 1 0 R\n"
      << ">>\n";
  pdf << "startxref\n";
  pdf << xref_offset << "\n";
  pdf << "%%EOF\n";

  return pdf.str();
}

static std::string WriteTempPdfAndGetUri(const std::string &bytes) {
  // Write to a unique temp file and return file:// URI for poppler_document_new_from_file().
  char tmpl[] = "/tmp/poppler_form_field_XXXXXX.pdf";
  int fd = g_mkstemp(tmpl);
  if (fd == -1) {
    return std::string();
  }

  // Close the FD and write via C++ (simple and reliable).
  close(fd);

  std::ofstream ofs(tmpl, std::ios::binary | std::ios::trunc);
  ofs.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
  ofs.close();

  gchar *uri = g_filename_to_uri(tmpl, /*hostname=*/nullptr, /*error=*/nullptr);
  std::string out = uri ? uri : "";
  g_free(uri);
  return out;
}

static PopplerFormField *GetFirstFormFieldFromFirstPage(PopplerDocument *doc) {
  PopplerPage *page = poppler_document_get_page(doc, 0);
  if (!page) {
    return nullptr;
  }

  GList *mappings = poppler_page_get_form_field_mapping(page);
  poppler_page_unref(page);

  if (!mappings) {
    return nullptr;
  }

  auto *mapping = static_cast<PopplerFormFieldMapping *>(mappings->data);
  PopplerFormField *field = mapping ? mapping->field : nullptr;

  // Keep the field alive by ref'ing it; mapping list will be freed.
  if (field) {
    g_object_ref(field);
  }

  poppler_page_free_form_field_mapping(mappings);
  return field;
}

struct DocAndField {
  PopplerDocument *doc = nullptr;
  PopplerFormField *field = nullptr;
  std::string uri;
};

static DocAndField LoadDocAndGetField(bool choice_field, int ff_value) {
  DocAndField out;

  const std::string pdf = BuildMinimalPdfWithSingleFormField(choice_field, ff_value);
  out.uri = WriteTempPdfAndGetUri(pdf);
  if (out.uri.empty()) {
    return out;
  }

  GError *error = nullptr;
  out.doc = poppler_document_new_from_file(out.uri.c_str(), /*password=*/nullptr, &error);
  if (!out.doc) {
    if (error) {
      g_error_free(error);
    }
    return out;
  }

  out.field = GetFirstFormFieldFromFirstPage(out.doc);
  return out;
}

static void Cleanup(DocAndField *d) {
  if (!d) return;
  if (d->field) {
    g_object_unref(d->field);
    d->field = nullptr;
  }
  if (d->doc) {
    g_object_unref(d->doc);
    d->doc = nullptr;
  }
  if (!d->uri.empty()) {
    // Convert URI back to filename to delete the temp file.
    GError *error = nullptr;
    gchar *filename = g_filename_from_uri(d->uri.c_str(), nullptr, &error);
    if (filename) {
      std::remove(filename);
      g_free(filename);
    }
    if (error) {
      g_error_free(error);
    }
  }
}

}  // namespace

class PopplerFormFieldChoiceSpellCheckTest_2343 : public ::testing::Test {};

TEST_F(PopplerFormFieldChoiceSpellCheckTest_2343, ReturnsFalseForNonChoiceField_2343) {
  // Error/exceptional case observable through interface: g_return_val_if_fail returns FALSE when
  // field widget is not a choice widget.
  DocAndField d = LoadDocAndGetField(/*choice_field=*/false, /*ff_value=*/0);
  ASSERT_NE(d.doc, nullptr);
  ASSERT_NE(d.field, nullptr);

  EXPECT_EQ(poppler_form_field_get_field_type(d.field), POPPLER_FORM_FIELD_TEXT);

  EXPECT_FALSE(poppler_form_field_choice_do_spell_check(d.field));

  Cleanup(&d);
}

TEST_F(PopplerFormFieldChoiceSpellCheckTest_2343, ReturnsTrueForChoiceFieldWhenFfZero_2343) {
  // Normal operation: should be callable on a choice field.
  DocAndField d = LoadDocAndGetField(/*choice_field=*/true, /*ff_value=*/0);
  ASSERT_NE(d.doc, nullptr);
  ASSERT_NE(d.field, nullptr);

  EXPECT_EQ(poppler_form_field_get_field_type(d.field), POPPLER_FORM_FIELD_CHOICE);

  // With no flags set, spell-check is expected to be enabled (do spell check).
  EXPECT_TRUE(poppler_form_field_choice_do_spell_check(d.field));

  Cleanup(&d);
}

TEST_F(PopplerFormFieldChoiceSpellCheckTest_2343, BoundaryFlagDoNotSpellCheckReturnsFalse_2343) {
  // Boundary/flag condition: Set a commonly-specified "doNotSpellCheck" bit in /Ff and verify the
  // public helper reports spell-check should not be performed.
  //
  // PDF field flags are bitfields; for many field types, "doNotSpellCheck" is bit 23 (1<<22).
  const int kDoNotSpellCheckBit = 1 << 22;

  DocAndField d = LoadDocAndGetField(/*choice_field=*/true, /*ff_value=*/kDoNotSpellCheckBit);
  ASSERT_NE(d.doc, nullptr);
  ASSERT_NE(d.field, nullptr);

  EXPECT_EQ(poppler_form_field_get_field_type(d.field), POPPLER_FORM_FIELD_CHOICE);

  EXPECT_FALSE(poppler_form_field_choice_do_spell_check(d.field));

  Cleanup(&d);
}

TEST_F(PopplerFormFieldChoiceSpellCheckTest_2343, BoundaryLargeFfValueDoesNotCrash_2343) {
  // Boundary condition: very large /Ff values should still allow the call to complete and return a
  // deterministic boolean (we only assert it returns either TRUE/FALSE without crashing).
  const int kLargeFf = 0x7fffffff;

  DocAndField d = LoadDocAndGetField(/*choice_field=*/true, /*ff_value=*/kLargeFf);
  ASSERT_NE(d.doc, nullptr);
  ASSERT_NE(d.field, nullptr);

  EXPECT_EQ(poppler_form_field_get_field_type(d.field), POPPLER_FORM_FIELD_CHOICE);

  const gboolean result = poppler_form_field_choice_do_spell_check(d.field);
  EXPECT_TRUE(result == TRUE || result == FALSE);

  Cleanup(&d);
}