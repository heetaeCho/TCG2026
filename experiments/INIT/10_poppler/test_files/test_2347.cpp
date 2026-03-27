// File: poppler-form-field-choice-is-item-selected-test-2347.cc

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

namespace {

// ---------------------------
// GLib critical log capture
// ---------------------------
class ScopedGlibCriticalCapture {
public:
  ScopedGlibCriticalCapture()
      : handler_id_(0), critical_count_(0) {
    handler_id_ = g_log_set_handler("GLib",
                                   static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL),
                                   &ScopedGlibCriticalCapture::LogHandler,
                                   this);
  }

  ~ScopedGlibCriticalCapture() {
    if (handler_id_ != 0) {
      g_log_remove_handler("GLib", handler_id_);
    }
  }

  int critical_count() const { return critical_count_; }

private:
  static void LogHandler(const gchar* /*log_domain*/,
                         GLogLevelFlags /*log_level*/,
                         const gchar* /*message*/,
                         gpointer user_data) {
    auto* self = static_cast<ScopedGlibCriticalCapture*>(user_data);
    self->critical_count_++;
  }

  guint handler_id_;
  int critical_count_;
};

// ---------------------------
// Minimal PDF builder
// ---------------------------
//
// Builds a very small PDF with one page and two AcroForm fields:
//  - a choice field (/FT /Ch) with /Opt [(A)(B)(C)] and /V (B)
//  - a text field (/FT /Tx)
//
// We compute xref offsets so Poppler can load it reliably.
//
static std::string BuildMinimalPdfWithChoiceAndText() {
  // Objects are 1-indexed. We'll generate objects 1..9.
  // 0 is the free object entry in xref.
  std::vector<std::string> obj(10);

  // 9: Helvetica font
  obj[9] =
      "9 0 obj\n"
      "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
      "endobj\n";

  // 4: Empty contents stream
  obj[4] =
      "4 0 obj\n"
      "<< /Length 0 >>\n"
      "stream\n"
      "endstream\n"
      "endobj\n";

  // 7: Widget annotation for choice field
  obj[7] =
      "7 0 obj\n"
      "<< /Type /Annot /Subtype /Widget\n"
      "   /Rect [50 700 200 730]\n"
      "   /FT /Ch\n"
      "   /Parent 5 0 R\n"
      "   /P 3 0 R\n"
      "   /F 4\n"
      ">>\n"
      "endobj\n";

  // 8: Widget annotation for text field
  obj[8] =
      "8 0 obj\n"
      "<< /Type /Annot /Subtype /Widget\n"
      "   /Rect [50 650 200 680]\n"
      "   /FT /Tx\n"
      "   /Parent 6 0 R\n"
      "   /P 3 0 R\n"
      "   /F 4\n"
      ">>\n"
      "endobj\n";

  // 5: Choice field dictionary
  obj[5] =
      "5 0 obj\n"
      "<< /FT /Ch\n"
      "   /T (Choice1)\n"
      "   /V (B)\n"
      "   /Opt [(A) (B) (C)]\n"
      "   /DA (/Helv 0 Tf 0 g)\n"
      "   /Kids [7 0 R]\n"
      ">>\n"
      "endobj\n";

  // 6: Text field dictionary
  obj[6] =
      "6 0 obj\n"
      "<< /FT /Tx\n"
      "   /T (Text1)\n"
      "   /V (Hello)\n"
      "   /DA (/Helv 0 Tf 0 g)\n"
      "   /Kids [8 0 R]\n"
      ">>\n"
      "endobj\n";

  // 3: Page
  obj[3] =
      "3 0 obj\n"
      "<< /Type /Page\n"
      "   /Parent 2 0 R\n"
      "   /MediaBox [0 0 612 792]\n"
      "   /Resources << >>\n"
      "   /Annots [7 0 R 8 0 R]\n"
      "   /Contents 4 0 R\n"
      ">>\n"
      "endobj\n";

  // 2: Pages
  obj[2] =
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n";

  // 1: Catalog with AcroForm (including DR font)
  obj[1] =
      "1 0 obj\n"
      "<< /Type /Catalog\n"
      "   /Pages 2 0 R\n"
      "   /AcroForm <<\n"
      "      /Fields [5 0 R 6 0 R]\n"
      "      /NeedAppearances true\n"
      "      /DR << /Font << /Helv 9 0 R >> >>\n"
      "   >>\n"
      ">>\n"
      "endobj\n";

  std::string pdf;
  pdf += "%PDF-1.4\n";

  std::vector<long> offsets(10, 0);
  offsets[0] = 0;

  for (int i = 1; i <= 9; ++i) {
    offsets[i] = static_cast<long>(pdf.size());
    pdf += obj[i];
  }

  const long xref_offset = static_cast<long>(pdf.size());

  pdf += "xref\n";
  pdf += "0 10\n";
  pdf += "0000000000 65535 f \n";

  // Each entry: 10-digit offset, space, 5-digit generation, space, n/f
  char buf[64];
  for (int i = 1; i <= 9; ++i) {
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    pdf += buf;
  }

  pdf += "trailer\n";
  pdf += "<< /Size 10 /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_offset);
  pdf += "\n%%EOF\n";

  return pdf;
}

// ---------------------------
// Temp file helpers
// ---------------------------
static std::string WriteTempPdfAndGetUri(const std::string& pdf_bytes) {
  gchar* tmp_path = nullptr;
  gint fd = g_file_open_tmp("poppler-choice-2347-XXXXXX.pdf", &tmp_path, nullptr);
  EXPECT_NE(fd, -1);
  EXPECT_NE(tmp_path, nullptr);

  FILE* f = fdopen(fd, "wb");
  EXPECT_NE(f, nullptr);

  size_t written = fwrite(pdf_bytes.data(), 1, pdf_bytes.size(), f);
  EXPECT_EQ(written, pdf_bytes.size());
  fclose(f); // closes fd too

  gchar* uri = g_filename_to_uri(tmp_path, nullptr, nullptr);
  EXPECT_NE(uri, nullptr);

  std::string uri_str(uri);

  g_free(uri);
  g_free(tmp_path);

  return uri_str;
}

static PopplerDocument* LoadDocumentFromUri(const std::string& uri) {
  GError* error = nullptr;
  PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
  if (!doc) {
    if (error) {
      ADD_FAILURE() << "Failed to load PDF: " << (error->message ? error->message : "(no message)");
      g_error_free(error);
    } else {
      ADD_FAILURE() << "Failed to load PDF (no GError).";
    }
  }
  return doc;
}

static PopplerFormField* FindFirstFieldOfTypeOnPage(PopplerPage* page, PopplerFormFieldType want_type) {
  GList* mappings = poppler_page_get_form_field_mapping(page);
  for (GList* l = mappings; l != nullptr; l = l->next) {
    auto* m = static_cast<PopplerFormFieldMapping*>(l->data);
    if (m && m->field && poppler_form_field_get_field_type(m->field) == want_type) {
      PopplerFormField* field = static_cast<PopplerFormField*>(g_object_ref(m->field));
      poppler_page_free_form_field_mapping(mappings);
      return field;
    }
  }
  poppler_page_free_form_field_mapping(mappings);
  return nullptr;
}

// ---------------------------
// Test fixture
// ---------------------------
class PopplerFormFieldChoiceIsItemSelectedTest_2347 : public ::testing::Test {
protected:
  void SetUp() override {
    const std::string pdf = BuildMinimalPdfWithChoiceAndText();
    uri_ = WriteTempPdfAndGetUri(pdf);

    doc_ = LoadDocumentFromUri(uri_);
    ASSERT_NE(doc_, nullptr);

    page_ = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page_, nullptr);

    choice_ = FindFirstFieldOfTypeOnPage(page_, POPPLER_FORM_FIELD_CHOICE);
    ASSERT_NE(choice_, nullptr);

    text_ = FindFirstFieldOfTypeOnPage(page_, POPPLER_FORM_FIELD_TEXT);
    ASSERT_NE(text_, nullptr);
  }

  void TearDown() override {
    if (choice_) g_object_unref(choice_);
    if (text_) g_object_unref(text_);
    if (page_) g_object_unref(page_);
    if (doc_) g_object_unref(doc_);
  }

  std::string uri_;
  PopplerDocument* doc_ = nullptr;
  PopplerPage* page_ = nullptr;
  PopplerFormField* choice_ = nullptr;
  PopplerFormField* text_ = nullptr;
};

// ---------------------------
// Tests
// ---------------------------

TEST_F(PopplerFormFieldChoiceIsItemSelectedTest_2347, ReturnsTrueForSelectedItem_2347) {
  const gint n_items = poppler_form_field_choice_get_n_items(choice_);
  ASSERT_GE(n_items, 3);

  // Our generated PDF sets /V (B) with options (A)(B)(C).
  EXPECT_FALSE(poppler_form_field_choice_is_item_selected(choice_, 0));
  EXPECT_TRUE(poppler_form_field_choice_is_item_selected(choice_, 1));
  EXPECT_FALSE(poppler_form_field_choice_is_item_selected(choice_, 2));
}

TEST_F(PopplerFormFieldChoiceIsItemSelectedTest_2347, ReturnsFalseForValidButUnselectedItem_2347) {
  const gint n_items = poppler_form_field_choice_get_n_items(choice_);
  ASSERT_GT(n_items, 0);

  // Pick an index that is expected to be unselected in our sample: 0.
  EXPECT_FALSE(poppler_form_field_choice_is_item_selected(choice_, 0));
}

TEST_F(PopplerFormFieldChoiceIsItemSelectedTest_2347, NegativeIndexTriggersCriticalAndReturnsFalse_2347) {
  ScopedGlibCriticalCapture capture;

  EXPECT_FALSE(poppler_form_field_choice_is_item_selected(choice_, -1));
  EXPECT_GE(capture.critical_count(), 1);
}

TEST_F(PopplerFormFieldChoiceIsItemSelectedTest_2347, IndexEqualToNItemsTriggersCriticalAndReturnsFalse_2347) {
  const gint n_items = poppler_form_field_choice_get_n_items(choice_);
  ASSERT_GE(n_items, 0);

  ScopedGlibCriticalCapture capture;

  EXPECT_FALSE(poppler_form_field_choice_is_item_selected(choice_, n_items));
  EXPECT_GE(capture.critical_count(), 1);
}

TEST_F(PopplerFormFieldChoiceIsItemSelectedTest_2347, NonChoiceFieldTriggersCriticalAndReturnsFalse_2347) {
  ASSERT_EQ(poppler_form_field_get_field_type(text_), POPPLER_FORM_FIELD_TEXT);

  ScopedGlibCriticalCapture capture;

  // Precondition in implementation requires widget->getType() == formChoice.
  EXPECT_FALSE(poppler_form_field_choice_is_item_selected(text_, 0));
  EXPECT_GE(capture.critical_count(), 1);
}

} // namespace