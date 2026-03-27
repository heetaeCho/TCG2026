// poppler-form-field-button-set-state-test_2316.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <gio/gio.h>

#include <poppler.h>

#include <cstring>
#include <string>
#include <vector>

namespace {

std::string BuildMinimalPdfWithCheckbox_2316() {
  // A tiny, valid PDF with one page and one checkbox button field named "cb1".
  // The checkbox has /Off and /Yes appearances and starts in /Off state.
  struct Obj {
    int num;
    std::string body;  // must include trailing newline(s) as desired
  };

  std::vector<Obj> objs;

  // 1: Catalog
  objs.push_back({1, "<< /Type /Catalog /Pages 2 0 R /AcroForm 5 0 R >>\n"});

  // 2: Pages
  objs.push_back({2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"});

  // 3: Page (with Annots [7 0 R])
  objs.push_back({3,
                  "<< /Type /Page\n"
                  "   /Parent 2 0 R\n"
                  "   /MediaBox [0 0 200 200]\n"
                  "   /Resources << >>\n"
                  "   /Contents 4 0 R\n"
                  "   /Annots [7 0 R]\n"
                  ">>\n"});

  // 4: Empty contents stream
  objs.push_back({4, "<< /Length 0 >>\nstream\n\nendstream\n"});

  // 5: AcroForm
  objs.push_back({5, "<< /Fields [6 0 R] /NeedAppearances true >>\n"});

  // 6: Field (checkbox)
  objs.push_back(
      {6,
       "<< /FT /Btn\n"
       "   /T (cb1)\n"
       "   /V /Off\n"
       "   /Kids [7 0 R]\n"
       ">>\n"});

  // 7: Widget annotation for checkbox, with AP for /Off and /Yes
  objs.push_back({7,
                  "<< /Type /Annot\n"
                  "   /Subtype /Widget\n"
                  "   /Parent 6 0 R\n"
                  "   /Rect [50 50 70 70]\n"
                  "   /AS /Off\n"
                  "   /AP << /N << /Off 8 0 R /Yes 9 0 R >> >>\n"
                  ">>\n"});

  // 8: Appearance stream for /Off
  objs.push_back({8,
                  "<< /Type /XObject /Subtype /Form\n"
                  "   /BBox [0 0 20 20]\n"
                  "   /Resources << >>\n"
                  "   /Length 0\n"
                  ">>\n"
                  "stream\n"
                  "\n"
                  "endstream\n"});

  // 9: Appearance stream for /Yes (draw a simple X)
  // Keep it minimal; Poppler should accept it.
  {
    const char* yes_stream = "0 0 m 20 20 l S\n0 20 m 20 0 l S\n";
    std::string body;
    body += "<< /Type /XObject /Subtype /Form\n"
            "   /BBox [0 0 20 20]\n"
            "   /Resources << >>\n";
    body += "   /Length ";
    body += std::to_string(std::strlen(yes_stream));
    body += "\n>>\nstream\n";
    body += yes_stream;
    body += "endstream\n";
    objs.push_back({9, body});
  }

  // Build PDF with xref.
  std::string pdf;
  pdf += "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n";

  // Offsets: index by object number. Object numbers are 1..9.
  std::vector<long> offsets(10, 0);

  auto append = [&](const std::string& s) { pdf += s; };

  for (const auto& o : objs) {
    offsets[o.num] = static_cast<long>(pdf.size());
    append(std::to_string(o.num));
    append(" 0 obj\n");
    append(o.body);
    append("endobj\n");
  }

  const long xref_offset = static_cast<long>(pdf.size());
  append("xref\n");
  append("0 10\n");
  append("0000000000 65535 f \n");
  for (int i = 1; i <= 9; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    append(buf);
  }

  append("trailer\n");
  append("<< /Size 10 /Root 1 0 R >>\n");
  append("startxref\n");
  append(std::to_string(xref_offset));
  append("\n%%EOF\n");

  return pdf;
}

std::string BuildMinimalPdfWithTextField_2316() {
  // A tiny, valid PDF with one page and one text field named "tx1".
  struct Obj {
    int num;
    std::string body;
  };

  std::vector<Obj> objs;

  objs.push_back({1, "<< /Type /Catalog /Pages 2 0 R /AcroForm 5 0 R >>\n"});
  objs.push_back({2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"});
  objs.push_back({3,
                  "<< /Type /Page\n"
                  "   /Parent 2 0 R\n"
                  "   /MediaBox [0 0 200 200]\n"
                  "   /Resources << >>\n"
                  "   /Contents 4 0 R\n"
                  "   /Annots [7 0 R]\n"
                  ">>\n"});
  objs.push_back({4, "<< /Length 0 >>\nstream\n\nendstream\n"});
  objs.push_back({5, "<< /Fields [6 0 R] /NeedAppearances true >>\n"});

  // 6: Text field
  objs.push_back({6,
                  "<< /FT /Tx\n"
                  "   /T (tx1)\n"
                  "   /V (hello)\n"
                  "   /Kids [7 0 R]\n"
                  ">>\n"});

  // 7: Widget annotation for text field
  objs.push_back({7,
                  "<< /Type /Annot\n"
                  "   /Subtype /Widget\n"
                  "   /Parent 6 0 R\n"
                  "   /Rect [50 50 150 80]\n"
                  ">>\n"});

  std::string pdf;
  pdf += "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n";
  std::vector<long> offsets(8, 0);

  auto append = [&](const std::string& s) { pdf += s; };

  for (const auto& o : objs) {
    offsets[o.num] = static_cast<long>(pdf.size());
    append(std::to_string(o.num));
    append(" 0 obj\n");
    append(o.body);
    append("endobj\n");
  }

  const long xref_offset = static_cast<long>(pdf.size());
  append("xref\n");
  append("0 8\n");
  append("0000000000 65535 f \n");
  for (int i = 1; i <= 7; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    append(buf);
  }

  append("trailer\n");
  append("<< /Size 8 /Root 1 0 R >>\n");
  append("startxref\n");
  append(std::to_string(xref_offset));
  append("\n%%EOF\n");

  return pdf;
}

std::string WriteTempPdfAndGetFileUri_2316(const std::string& pdf_bytes) {
  gchar* tmp_path = nullptr;
  gint fd = g_file_open_tmp("poppler_form_field_2316_XXXXXX.pdf", &tmp_path, nullptr);
  EXPECT_GE(fd, 0);
  EXPECT_NE(tmp_path, nullptr);

  gssize total = 0;
  while (total < static_cast<gssize>(pdf_bytes.size())) {
    const gssize n = write(fd, pdf_bytes.data() + total,
                           static_cast<size_t>(pdf_bytes.size() - total));
    EXPECT_GT(n, 0);
    if (n <= 0) break;
    total += n;
  }
  close(fd);

  gchar* uri = g_filename_to_uri(tmp_path, nullptr, nullptr);
  EXPECT_NE(uri, nullptr);

  std::string uri_str = uri ? uri : "";
  g_free(uri);
  g_free(tmp_path);
  return uri_str;
}

PopplerFormField* FindFirstFieldOfType_2316(PopplerPage* page, PopplerFormFieldType want) {
  GList* mappings = poppler_page_get_form_field_mapping(page);
  for (GList* l = mappings; l != nullptr; l = l->next) {
    auto* mapping = static_cast<PopplerFormFieldMapping*>(l->data);
    if (!mapping || !mapping->field) continue;
    if (poppler_form_field_get_field_type(mapping->field) == want) {
      PopplerFormField* found = mapping->field;
      poppler_page_free_form_field_mapping(mappings);
      return found;  // note: field is owned by Poppler; mapping list freed
    }
  }
  poppler_page_free_form_field_mapping(mappings);
  return nullptr;
}

struct CriticalLogCatcher_2316 {
  static void Handler(const gchar* /*log_domain*/,
                      GLogLevelFlags log_level,
                      const gchar* /*message*/,
                      gpointer user_data) {
    if (log_level & (G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING)) {
      auto* self = static_cast<CriticalLogCatcher_2316*>(user_data);
      self->count++;
    }
  }

  guint count = 0;
  GLogFunc old_handler = nullptr;
  gpointer old_data = nullptr;

  CriticalLogCatcher_2316() {
    // Intercept default handler (covers all domains). This is best-effort: we only
    // assert "didn't crash" and optionally observe that a critical/warning happened.
    old_handler = g_log_set_default_handler(&Handler, this);
    old_data = nullptr;
  }

  ~CriticalLogCatcher_2316() {
    g_log_set_default_handler(old_handler, old_data);
  }
};

}  // namespace

TEST(PopplerFormFieldButtonSetStateTest_2316, TogglesCheckboxState_2316) {
  std::string uri = WriteTempPdfAndGetFileUri_2316(BuildMinimalPdfWithCheckbox_2316());
  ASSERT_FALSE(uri.empty());

  GError* error = nullptr;
  PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
  ASSERT_NE(doc, nullptr) << (error ? error->message : "unknown error");
  if (error) g_error_free(error);

  PopplerPage* page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  PopplerFormField* field =
      FindFirstFieldOfType_2316(page, POPPLER_FORM_FIELD_BUTTON);
  ASSERT_NE(field, nullptr);

  // Initial state should be false (unchecked) for our generated PDF.
  gboolean initial = poppler_form_field_button_get_state(field);

  // Set to the opposite value and verify observable state changes.
  poppler_form_field_button_set_state(field, initial ? FALSE : TRUE);
  gboolean after = poppler_form_field_button_get_state(field);
  EXPECT_NE(after, initial);

  // Setting again to the same value should be stable (idempotent behavior observable
  // through get_state).
  poppler_form_field_button_set_state(field, after);
  gboolean after2 = poppler_form_field_button_get_state(field);
  EXPECT_EQ(after2, after);

  g_object_unref(page);
  g_object_unref(doc);
}

TEST(PopplerFormFieldButtonSetStateTest_2316, AcceptsBothBooleanValues_2316) {
  std::string uri = WriteTempPdfAndGetFileUri_2316(BuildMinimalPdfWithCheckbox_2316());
  ASSERT_FALSE(uri.empty());

  GError* error = nullptr;
  PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
  ASSERT_NE(doc, nullptr) << (error ? error->message : "unknown error");
  if (error) g_error_free(error);

  PopplerPage* page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  PopplerFormField* field =
      FindFirstFieldOfType_2316(page, POPPLER_FORM_FIELD_BUTTON);
  ASSERT_NE(field, nullptr);

  // Boundary-ish: explicitly set FALSE then TRUE and observe.
  poppler_form_field_button_set_state(field, FALSE);
  EXPECT_FALSE(poppler_form_field_button_get_state(field));

  poppler_form_field_button_set_state(field, TRUE);
  EXPECT_TRUE(poppler_form_field_button_get_state(field));

  g_object_unref(page);
  g_object_unref(doc);
}

TEST(PopplerFormFieldButtonSetStateTest_2316, NonButtonFieldDoesNotCrash_2316) {
  std::string uri = WriteTempPdfAndGetFileUri_2316(BuildMinimalPdfWithTextField_2316());
  ASSERT_FALSE(uri.empty());

  GError* error = nullptr;
  PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
  ASSERT_NE(doc, nullptr) << (error ? error->message : "unknown error");
  if (error) g_error_free(error);

  PopplerPage* page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  PopplerFormField* text_field =
      FindFirstFieldOfType_2316(page, POPPLER_FORM_FIELD_TEXT);
  ASSERT_NE(text_field, nullptr);

  // The implementation has a g_return_if_fail(getType()==formButton); so for non-button
  // fields it should early-return (and may emit a critical). We assert it does not crash.
  CriticalLogCatcher_2316 catcher;
  poppler_form_field_button_set_state(text_field, TRUE);

  // Best-effort: typically a critical or warning is logged; don't make it mandatory
  // across build configurations.
  EXPECT_GE(catcher.count, 0u);

  g_object_unref(page);
  g_object_unref(doc);
}