// File: poppler-form-field-text-do-spell-check-test-2336.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <cstdlib>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace {

struct GObjectUnrefDeleter {
  void operator()(gpointer p) const {
    if (p) g_object_unref(p);
  }
};

using ScopedGObject = std::unique_ptr<void, GObjectUnrefDeleter>;

static std::string BuildPdfFromObjects(const std::vector<std::string>& obj_bodies) {
  // obj_bodies is 1-based: obj_bodies[0] is object #1 body content.
  std::string out;
  out += "%PDF-1.4\n";
  out += "%\xE2\xE3\xCF\xD3\n";  // binary comment

  std::vector<long> offsets;
  offsets.resize(obj_bodies.size() + 1, 0);  // index 0 reserved for obj 0

  for (size_t i = 0; i < obj_bodies.size(); ++i) {
    const int obj_num = static_cast<int>(i + 1);
    offsets[obj_num] = static_cast<long>(out.size());
    out += std::to_string(obj_num) + " 0 obj\n";
    out += obj_bodies[i];
    if (!out.empty() && out.back() != '\n') out += "\n";
    out += "endobj\n";
  }

  const long xref_pos = static_cast<long>(out.size());
  out += "xref\n";
  out += "0 " + std::to_string(obj_bodies.size() + 1) + "\n";
  out += "0000000000 65535 f \n";

  auto fmt10 = [](long v) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld", v);
    return std::string(buf);
  };

  for (size_t obj_num = 1; obj_num <= obj_bodies.size(); ++obj_num) {
    out += fmt10(offsets[obj_num]) + " 00000 n \n";
  }

  out += "trailer\n";
  out += "<< /Size " + std::to_string(obj_bodies.size() + 1) + " /Root 1 0 R >>\n";
  out += "startxref\n";
  out += std::to_string(xref_pos) + "\n";
  out += "%%EOF\n";

  return out;
}

static std::string MakeSinglePagePdfWithField(const std::string& field_dict,
                                              const std::string& widget_dict,
                                              const std::string& acroform_dict) {
  // Object numbering:
  // 1: Catalog
  // 2: Pages
  // 3: Page
  // 4: Contents stream
  // 5: Font
  // 6: AcroForm
  // 7: Widget annotation
  // 8: Field dictionary

  const std::string contents_stream = "BT /Helv 12 Tf 72 200 Td (Hello) Tj ET";
  const std::string contents_obj =
      "<< /Length " + std::to_string(contents_stream.size()) + " >>\n"
      "stream\n" + contents_stream + "\nendstream";

  std::vector<std::string> objs;
  objs.reserve(8);

  objs.push_back("<< /Type /Catalog /Pages 2 0 R /AcroForm 6 0 R >>");  // 1
  objs.push_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");          // 2
  objs.push_back(
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 300 300]\n"
      "   /Resources << /Font << /Helv 5 0 R >> >>\n"
      "   /Contents 4 0 R\n"
      "   /Annots [7 0 R]\n"
      ">>");                                                             // 3
  objs.push_back(contents_obj);                                          // 4
  objs.push_back("<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>");  // 5
  objs.push_back(acroform_dict);                                         // 6
  objs.push_back(widget_dict);                                           // 7
  objs.push_back(field_dict);                                            // 8

  return BuildPdfFromObjects(objs);
}

struct LoadedField {
  ScopedGObject doc;
  ScopedGObject page;
  ScopedGObject field;
};

static LoadedField LoadFirstFormFieldFromPdfBytes(const std::string& pdf_bytes) {
  // Write to a temporary file and load via poppler_document_new_from_file().
  char tmpl[] = "/tmp/poppler_2336_XXXXXX.pdf";
  int fd = g_mkstemp(tmpl);
  EXPECT_NE(fd, -1);

  FILE* f = fdopen(fd, "wb");
  EXPECT_NE(f, nullptr);
  const size_t written = fwrite(pdf_bytes.data(), 1, pdf_bytes.size(), f);
  fclose(f);
  EXPECT_EQ(written, pdf_bytes.size());

  GError* error = nullptr;
  gchar* uri = g_filename_to_uri(tmpl, nullptr, &error);
  EXPECT_EQ(error, nullptr);
  EXPECT_NE(uri, nullptr);

  PopplerDocument* doc =
      poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
  g_free(uri);
  EXPECT_EQ(error, nullptr);
  EXPECT_NE(doc, nullptr);

  PopplerPage* page = poppler_document_get_page(doc, 0);
  EXPECT_NE(page, nullptr);

  GList* mappings = poppler_page_get_form_field_mapping(page);
  EXPECT_NE(mappings, nullptr);
  EXPECT_NE(mappings->data, nullptr);

  auto* mapping = static_cast<PopplerFormFieldMapping*>(mappings->data);
  EXPECT_NE(mapping->field, nullptr);

  // Keep the field alive independent of the mapping list.
  PopplerFormField* field = static_cast<PopplerFormField*>(g_object_ref(mapping->field));

  poppler_page_free_form_field_mapping(mappings);

  // Remove temp file; Poppler has already opened it.
  (void)g_remove(tmpl);

  LoadedField loaded;
  loaded.doc.reset(doc);
  loaded.page.reset(page);
  loaded.field.reset(field);
  return loaded;
}

class PopplerFormFieldTextDoSpellCheckTest_2336 : public ::testing::Test {};

TEST_F(PopplerFormFieldTextDoSpellCheckTest_2336, ReturnsTrueWhenSpellCheckAllowed_2336) {
  // Text field with no DoNotSpellCheck flag set.
  const std::string field_dict =
      "<< /FT /Tx /T (Text1) /Ff 0 /V (abc) /Kids [7 0 R] >>";
  const std::string widget_dict =
      "<< /Type /Annot /Subtype /Widget /Rect [50 50 250 80] /P 3 0 R /Parent 8 0 R >>";
  const std::string acroform_dict =
      "<< /Fields [8 0 R] /DA (/Helv 0 Tf 0 g) >>";

  LoadedField loaded = LoadFirstFormFieldFromPdfBytes(
      MakeSinglePagePdfWithField(field_dict, widget_dict, acroform_dict));

  auto* field = static_cast<PopplerFormField*>(loaded.field.get());
  ASSERT_NE(field, nullptr);

  // Observable behavior: for a text widget, it returns a gboolean.
  EXPECT_TRUE(poppler_form_field_text_do_spell_check(field));
}

TEST_F(PopplerFormFieldTextDoSpellCheckTest_2336, ReturnsFalseWhenSpellCheckDisabled_2336) {
  // Text field with DoNotSpellCheck set (commonly bit 23 => 0x400000).
  const std::string field_dict =
      "<< /FT /Tx /T (Text1) /Ff 4194304 /V (abc) /Kids [7 0 R] >>";
  const std::string widget_dict =
      "<< /Type /Annot /Subtype /Widget /Rect [50 50 250 80] /P 3 0 R /Parent 8 0 R >>";
  const std::string acroform_dict =
      "<< /Fields [8 0 R] /DA (/Helv 0 Tf 0 g) >>";

  LoadedField loaded = LoadFirstFormFieldFromPdfBytes(
      MakeSinglePagePdfWithField(field_dict, widget_dict, acroform_dict));

  auto* field = static_cast<PopplerFormField*>(loaded.field.get());
  ASSERT_NE(field, nullptr);

  EXPECT_FALSE(poppler_form_field_text_do_spell_check(field));
}

TEST_F(PopplerFormFieldTextDoSpellCheckTest_2336, ReturnsFalseForNonTextField_2336) {
  // Create a button field (/FT /Btn). The function is documented by its contract to
  // return FALSE when the widget type is not formText (via g_return_val_if_fail).
  const std::string field_dict =
      "<< /FT /Btn /T (Check1) /V /Off /Kids [7 0 R] >>";
  const std::string widget_dict =
      "<< /Type /Annot /Subtype /Widget /Rect [50 50 70 70] /P 3 0 R /Parent 8 0 R /AS /Off >>";
  const std::string acroform_dict =
      "<< /Fields [8 0 R] /DA (/Helv 0 Tf 0 g) >>";

  LoadedField loaded = LoadFirstFormFieldFromPdfBytes(
      MakeSinglePagePdfWithField(field_dict, widget_dict, acroform_dict));

  auto* field = static_cast<PopplerFormField*>(loaded.field.get());
  ASSERT_NE(field, nullptr);

  EXPECT_FALSE(poppler_form_field_text_do_spell_check(field));
}

}  // namespace