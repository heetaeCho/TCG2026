// Test file for poppler_form_field_choice_is_editable
// File: poppler-form-field-choice-is-editable-test.cc

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

extern "C" {
gboolean poppler_form_field_choice_is_editable(PopplerFormField *field);
}

namespace {

std::string BuildPdfWithChoiceAndTextWidgets() {
  // Minimal PDF containing 1 page with:
  //  - choice_edit   : choice field, combo+edit (/Ff = 393216)
  //  - choice_noedit : choice field, combo only (/Ff = 131072)
  //  - text1         : text field
  //
  // Poppler should be able to parse this without needing appearance streams.

  struct Obj {
    int num;
    std::string body;
  };

  // PDF form flags (AcroForm field flags for choice fields):
  // combo bit: 1<<17 = 131072
  // edit  bit: 1<<18 = 262144
  const int kFfCombo = 131072;
  const int kFfEdit = 262144;

  std::vector<Obj> objs;

  // 1: Catalog
  objs.push_back({1,
                  "<< /Type /Catalog\n"
                  "   /Pages 2 0 R\n"
                  "   /AcroForm 5 0 R\n"
                  ">>\n"});

  // 2: Pages
  objs.push_back({2,
                  "<< /Type /Pages\n"
                  "   /Kids [3 0 R]\n"
                  "   /Count 1\n"
                  ">>\n"});

  // 3: Page
  objs.push_back({3,
                  "<< /Type /Page\n"
                  "   /Parent 2 0 R\n"
                  "   /MediaBox [0 0 612 792]\n"
                  "   /Resources << >>\n"
                  "   /Contents 4 0 R\n"
                  "   /Annots [6 0 R 7 0 R 8 0 R]\n"
                  ">>\n"});

  // 4: Empty contents stream
  objs.push_back({4,
                  "<< /Length 0 >>\n"
                  "stream\n"
                  "\n"
                  "endstream\n"});

  // 5: AcroForm
  objs.push_back({5,
                  "<< /Fields [6 0 R 7 0 R 8 0 R]\n"
                  "   /NeedAppearances true\n"
                  ">>\n"});

  // 6: choice_edit widget (combo + edit)
  {
    std::ostringstream oss;
    oss << "<< /FT /Ch\n"
        << "   /Subtype /Widget\n"
        << "   /T (choice_edit)\n"
        << "   /Ff " << (kFfCombo + kFfEdit) << "\n"
        << "   /Opt [(A) (B) (C)]\n"
        << "   /V (A)\n"
        << "   /Rect [72 650 300 680]\n"
        << "   /P 3 0 R\n"
        << ">>\n";
    objs.push_back({6, oss.str()});
  }

  // 7: choice_noedit widget (combo only)
  {
    std::ostringstream oss;
    oss << "<< /FT /Ch\n"
        << "   /Subtype /Widget\n"
        << "   /T (choice_noedit)\n"
        << "   /Ff " << kFfCombo << "\n"
        << "   /Opt [(A) (B) (C)]\n"
        << "   /V (A)\n"
        << "   /Rect [72 600 300 630]\n"
        << "   /P 3 0 R\n"
        << ">>\n";
    objs.push_back({7, oss.str()});
  }

  // 8: text1 widget
  objs.push_back({8,
                  "<< /FT /Tx\n"
                  "   /Subtype /Widget\n"
                  "   /T (text1)\n"
                  "   /V (hello)\n"
                  "   /Rect [72 550 300 580]\n"
                  "   /P 3 0 R\n"
                  ">>\n"});

  std::ostringstream out;
  out << "%PDF-1.4\n";

  // Track byte offsets for xref.
  // xref entry 0 is the free object.
  std::vector<long> offsets(9, 0);

  for (const auto &o : objs) {
    offsets[o.num] = static_cast<long>(out.tellp());
    out << o.num << " 0 obj\n" << o.body << "endobj\n";
  }

  const long xref_offset = static_cast<long>(out.tellp());
  out << "xref\n";
  out << "0 9\n";
  out << "0000000000 65535 f \n";
  for (int i = 1; i <= 8; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld", offsets[i]);
    out << buf << " 00000 n \n";
  }

  out << "trailer\n";
  out << "<< /Size 9\n";
  out << "   /Root 1 0 R\n";
  out << ">>\n";
  out << "startxref\n";
  out << xref_offset << "\n";
  out << "%%EOF\n";

  return out.str();
}

std::string WriteTempPdfAndGetUriOrDie(const std::string &pdf_bytes) {
  // Create a temp file path.
  std::string tmpl = "/tmp/poppler_glib_choice_editable_XXXXXX";
  std::vector<char> path(tmpl.begin(), tmpl.end());
  path.push_back('\0');

  int fd = g_mkstemp(path.data());
  EXPECT_NE(fd, -1);

  // Write bytes
  ssize_t total = 0;
  const char *data = pdf_bytes.data();
  const ssize_t len = static_cast<ssize_t>(pdf_bytes.size());
  while (total < len) {
    ssize_t w = write(fd, data + total, len - total);
    if (w <= 0) break;
    total += w;
  }
  close(fd);
  EXPECT_EQ(total, len);

  GError *err = nullptr;
  gchar *uri = g_filename_to_uri(path.data(), nullptr, &err);
  EXPECT_EQ(err, nullptr);
  EXPECT_NE(uri, nullptr);

  std::string uri_str(uri);
  g_free(uri);

  return uri_str;
}

PopplerDocument *LoadDocOrDie(const std::string &uri) {
  GError *err = nullptr;
  PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &err);
  EXPECT_EQ(err, nullptr);
  EXPECT_NE(doc, nullptr);
  return doc;
}

PopplerFormField *FindFieldByNameOrNull(PopplerPage *page, const char *name) {
  GList *mappings = poppler_page_get_form_field_mapping(page);
  for (GList *l = mappings; l != nullptr; l = l->next) {
    auto *mapping = static_cast<PopplerFormFieldMapping *>(l->data);
    PopplerFormField *field = mapping->field;
    if (!field) continue;

    const gchar *field_name = poppler_form_field_get_name(field);
    if (field_name && std::strcmp(field_name, name) == 0) {
      // Free the list but keep the field object (owned by Poppler/GObject).
      poppler_page_free_form_field_mapping(mappings);
      return field;
    }
  }
  poppler_page_free_form_field_mapping(mappings);
  return nullptr;
}

class PopplerFormFieldChoiceIsEditableTest_2341 : public ::testing::Test {
 protected:
  void SetUp() override {
    const std::string pdf = BuildPdfWithChoiceAndTextWidgets();
    uri_ = WriteTempPdfAndGetUriOrDie(pdf);

    doc_ = LoadDocOrDie(uri_);
    ASSERT_NE(doc_, nullptr);

    page_ = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page_, nullptr);
  }

  void TearDown() override {
    if (page_) g_object_unref(page_);
    if (doc_) g_object_unref(doc_);
  }

  std::string uri_;
  PopplerDocument *doc_ = nullptr;
  PopplerPage *page_ = nullptr;
};

TEST_F(PopplerFormFieldChoiceIsEditableTest_2341, ReturnsTrueForEditableChoiceField_2341) {
  PopplerFormField *field = FindFieldByNameOrNull(page_, "choice_edit");
  ASSERT_NE(field, nullptr);

  // Sanity: ensure Poppler considers it a choice field via public API.
  EXPECT_EQ(poppler_form_field_get_field_type(field), POPPLER_FORM_FIELD_CHOICE);

  // Function under test.
  EXPECT_TRUE(poppler_form_field_choice_is_editable(field));

  // Repeat call: should remain stable and not crash.
  EXPECT_TRUE(poppler_form_field_choice_is_editable(field));
}

TEST_F(PopplerFormFieldChoiceIsEditableTest_2341, ReturnsFalseForNonEditableChoiceField_2341) {
  PopplerFormField *field = FindFieldByNameOrNull(page_, "choice_noedit");
  ASSERT_NE(field, nullptr);

  EXPECT_EQ(poppler_form_field_get_field_type(field), POPPLER_FORM_FIELD_CHOICE);

  EXPECT_FALSE(poppler_form_field_choice_is_editable(field));

  // Repeat call: stable.
  EXPECT_FALSE(poppler_form_field_choice_is_editable(field));
}

TEST_F(PopplerFormFieldChoiceIsEditableTest_2341, ReturnsFalseForNonChoiceField_2341) {
  PopplerFormField *field = FindFieldByNameOrNull(page_, "text1");
  ASSERT_NE(field, nullptr);

  // Sanity: ensure it's not a choice field through the public API.
  EXPECT_NE(poppler_form_field_get_field_type(field), POPPLER_FORM_FIELD_CHOICE);

  // Boundary/error case: function has a g_return_val_if_fail() requiring a choice widget type.
  // Observable behavior: should return FALSE.
  EXPECT_FALSE(poppler_form_field_choice_is_editable(field));
}

}  // namespace