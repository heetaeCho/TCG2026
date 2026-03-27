// File: poppler-document-reset-form-test.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <string>
#include <utility>
#include <vector>

namespace {

// Build a minimal, valid PDF containing two text form fields on page 1.
// Field dictionaries include both /V (initial) and /DV (default) values so that
// form reset has an observable effect via public Poppler GLib APIs.
static std::string BuildPdfTwoTextFields()
{
  struct Obj {
    int num;
    std::string body; // must include trailing newline(s) as appropriate
  };

  std::vector<Obj> objs;

  // 1: Catalog (references Pages and AcroForm)
  objs.push_back({1,
                  "<< /Type /Catalog /Pages 2 0 R /AcroForm 5 0 R >>\n"});

  // 2: Pages
  objs.push_back({2,
                  "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"});

  // 3: Page (annots are the widgets/fields)
  objs.push_back({3,
                  "<< /Type /Page /Parent 2 0 R\n"
                  "   /MediaBox [0 0 200 200]\n"
                  "   /Resources << /Font << /F1 4 0 R >> >>\n"
                  "   /Contents 6 0 R\n"
                  "   /Annots [7 0 R 8 0 R]\n"
                  ">>\n"});

  // 4: Font
  objs.push_back({4,
                  "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"});

  // 5: AcroForm
  // NeedAppearances helps viewers generate appearances without explicit /AP.
  objs.push_back({5,
                  "<< /Fields [7 0 R 8 0 R] /NeedAppearances true >>\n"});

  // 6: Contents stream (empty)
  objs.push_back({6,
                  "<< /Length 0 >>\n"
                  "stream\n"
                  "endstream\n"});

  // 7: Field+Widget #1
  objs.push_back({7,
                  "<< /FT /Tx /Subtype /Widget\n"
                  "   /T (field1)\n"
                  "   /V (INIT1)\n"
                  "   /DV (DEF1)\n"
                  "   /Rect [10 140 190 170]\n"
                  "   /P 3 0 R\n"
                  ">>\n"});

  // 8: Field+Widget #2
  objs.push_back({8,
                  "<< /FT /Tx /Subtype /Widget\n"
                  "   /T (field2)\n"
                  "   /V (INIT2)\n"
                  "   /DV (DEF2)\n"
                  "   /Rect [10 90 190 120]\n"
                  "   /P 3 0 R\n"
                  ">>\n"});

  // Assemble PDF and compute xref offsets.
  std::string out;
  out.reserve(4096);

  out += "%PDF-1.4\n";
  out += "%\xE2\xE3\xCF\xD3\n"; // binary comment

  // Offsets indexed by object number, 0..max
  const int max_obj = 8;
  std::vector<long> offsets(max_obj + 1, 0);

  for (const auto &o : objs) {
    offsets[o.num] = static_cast<long>(out.size());
    out += std::to_string(o.num) + " 0 obj\n";
    out += o.body;
    out += "endobj\n";
  }

  const long xref_offset = static_cast<long>(out.size());
  out += "xref\n";
  out += "0 " + std::to_string(max_obj + 1) + "\n";
  out += "0000000000 65535 f \n";
  for (int i = 1; i <= max_obj; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    out += buf;
  }

  out += "trailer\n";
  out += "<< /Size " + std::to_string(max_obj + 1) + " /Root 1 0 R >>\n";
  out += "startxref\n";
  out += std::to_string(xref_offset) + "\n";
  out += "%%EOF\n";
  return out;
}

static std::string WriteTempPdfAndGetUri(const std::string &pdf_bytes)
{
  // Create temp file.
  gchar *tmpl = g_strdup("poppler-reset-form-XXXXXX.pdf");
  int fd = g_mkstemp(tmpl);
  EXPECT_GE(fd, 0);

  // Write bytes.
  gsize written = 0;
  GError *err = nullptr;
  gboolean ok = g_file_set_contents(tmpl, pdf_bytes.data(),
                                   static_cast<gssize>(pdf_bytes.size()), &err);
  if (!ok) {
    std::string msg = err ? err->message : "unknown error";
    if (err)
      g_error_free(err);
    close(fd);
    g_free(tmpl);
    ADD_FAILURE() << "Failed to write temp PDF: " << msg;
    return "";
  }
  close(fd);

  // Convert to file:// URI.
  gchar *uri = g_filename_to_uri(tmpl, nullptr, &err);
  std::string uri_str = uri ? uri : "";
  if (!uri) {
    std::string msg = err ? err->message : "unknown error";
    if (err)
      g_error_free(err);
    g_free(tmpl);
    ADD_FAILURE() << "Failed to build URI: " << msg;
    return "";
  }

  g_free(uri);
  g_free(tmpl);
  return uri_str;
}

static PopplerDocument *OpenDocFromUriOrFail(const std::string &uri)
{
  GError *err = nullptr;
  PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &err);
  if (!doc) {
    std::string msg = err ? err->message : "unknown error";
    if (err)
      g_error_free(err);
    ADD_FAILURE() << "poppler_document_new_from_file failed: " << msg;
  }
  return doc;
}

static std::pair<PopplerFormField *, PopplerFormField *>
GetTwoTextFieldsFromFirstPageOrFail(PopplerDocument *doc)
{
  PopplerPage *page = poppler_document_get_page(doc, 0);
  EXPECT_NE(page, nullptr);

  GList *mappings = poppler_page_get_form_field_mapping(page);
  EXPECT_NE(mappings, nullptr);

  PopplerFormField *f1 = nullptr;
  PopplerFormField *f2 = nullptr;

  for (GList *it = mappings; it != nullptr; it = it->next) {
    auto *m = static_cast<PopplerFormFieldMapping *>(it->data);
    if (!m || !m->field)
      continue;

    if (poppler_form_field_get_field_type(m->field) == POPPLER_FORM_FIELD_TEXT) {
      if (!f1) {
        f1 = static_cast<PopplerFormField *>(g_object_ref(m->field));
      } else if (!f2) {
        f2 = static_cast<PopplerFormField *>(g_object_ref(m->field));
      }
    }
    if (f1 && f2)
      break;
  }

  poppler_page_free_form_field_mapping(mappings);
  g_object_unref(page);

  EXPECT_NE(f1, nullptr);
  EXPECT_NE(f2, nullptr);
  return {f1, f2};
}

static std::string GetTextOrEmpty(PopplerFormField *field)
{
  gchar *txt = poppler_form_field_text_get_text(field);
  std::string s = txt ? txt : "";
  g_free(txt);
  return s;
}

static void SetText(PopplerFormField *field, const char *value)
{
  // PopplerFormFieldText API accepts UTF-8 string.
  poppler_form_field_text_set_text(field, value);
}

static GList *MakeNameListOne(PopplerFormField *field)
{
  gchar *name = poppler_form_field_get_name(field);
  EXPECT_NE(name, nullptr);

  // poppler_document_reset_form treats list data as char*; ensure lifetime
  // across the call by allocating (and freeing) our own.
  GList *l = nullptr;
  l = g_list_append(l, g_strdup(name));
  g_free(name);
  return l;
}

static void FreeNameList(GList *l)
{
  g_list_free_full(l, g_free);
}

} // namespace

// ---------- Tests (TEST_ID = 2207) ----------

TEST(PopplerDocumentResetFormTest_2207, ResetsOnlyListedFieldWhenExcludeFalse_2207)
{
  const std::string pdf = BuildPdfTwoTextFields();
  const std::string uri = WriteTempPdfAndGetUri(pdf);
  ASSERT_FALSE(uri.empty());

  PopplerDocument *doc = OpenDocFromUriOrFail(uri);
  ASSERT_NE(doc, nullptr);

  auto [field1, field2] = GetTwoTextFieldsFromFirstPageOrFail(doc);

  // Verify initial values are observable (from /V).
  EXPECT_EQ(GetTextOrEmpty(field1), "INIT1");
  EXPECT_EQ(GetTextOrEmpty(field2), "INIT2");

  // Change both values.
  SetText(field1, "CHANGED1");
  SetText(field2, "CHANGED2");
  EXPECT_EQ(GetTextOrEmpty(field1), "CHANGED1");
  EXPECT_EQ(GetTextOrEmpty(field2), "CHANGED2");

  // Reset only field1 (exclude_fields = FALSE).
  GList *names = MakeNameListOne(field1);
  poppler_document_reset_form(doc, names, FALSE);
  FreeNameList(names);

  // After reset, field1 should go back to its default (/DV), field2 should remain changed.
  EXPECT_EQ(GetTextOrEmpty(field1), "DEF1");
  EXPECT_EQ(GetTextOrEmpty(field2), "CHANGED2");

  g_object_unref(field1);
  g_object_unref(field2);
  g_object_unref(doc);
}

TEST(PopplerDocumentResetFormTest_2207, ResetsAllExceptListedFieldWhenExcludeTrue_2207)
{
  const std::string pdf = BuildPdfTwoTextFields();
  const std::string uri = WriteTempPdfAndGetUri(pdf);
  ASSERT_FALSE(uri.empty());

  PopplerDocument *doc = OpenDocFromUriOrFail(uri);
  ASSERT_NE(doc, nullptr);

  auto [field1, field2] = GetTwoTextFieldsFromFirstPageOrFail(doc);

  // Change both values.
  SetText(field1, "KEEP_ME");
  SetText(field2, "RESET_ME");
  ASSERT_EQ(GetTextOrEmpty(field1), "KEEP_ME");
  ASSERT_EQ(GetTextOrEmpty(field2), "RESET_ME");

  // Reset all except field1 (exclude_fields = TRUE).
  GList *names = MakeNameListOne(field1);
  poppler_document_reset_form(doc, names, TRUE);
  FreeNameList(names);

  // field1 remains as-is; field2 resets to default.
  EXPECT_EQ(GetTextOrEmpty(field1), "KEEP_ME");
  EXPECT_EQ(GetTextOrEmpty(field2), "DEF2");

  g_object_unref(field1);
  g_object_unref(field2);
  g_object_unref(doc);
}

TEST(PopplerDocumentResetFormTest_2207, NullDocumentDoesNotCrashAndLogsCritical_2207)
{
  // g_return_if_fail should emit a critical log and return.
  testing::internal::CaptureStderr();
  poppler_document_reset_form(nullptr, nullptr, FALSE);
  std::string err = testing::internal::GetCapturedStderr();

  // Be tolerant to log-domain formatting differences; check for the assertion text.
  EXPECT_NE(err.find("CRITICAL"), std::string::npos);
  EXPECT_NE(err.find("POPPLER_IS_DOCUMENT"), std::string::npos);
}

TEST(PopplerDocumentResetFormTest_2207, NullFieldsListDoesNotCrash_2207)
{
  const std::string pdf = BuildPdfTwoTextFields();
  const std::string uri = WriteTempPdfAndGetUri(pdf);
  ASSERT_FALSE(uri.empty());

  PopplerDocument *doc = OpenDocFromUriOrFail(uri);
  ASSERT_NE(doc, nullptr);

  auto [field1, field2] = GetTwoTextFieldsFromFirstPageOrFail(doc);

  // Make some changes.
  SetText(field1, "X1");
  SetText(field2, "X2");
  ASSERT_EQ(GetTextOrEmpty(field1), "X1");
  ASSERT_EQ(GetTextOrEmpty(field2), "X2");

  // Boundary: fields == nullptr. Observable requirement here is simply "no crash".
  // (Semantics of empty reset list are not asserted because they are not specified by the interface.)
  poppler_document_reset_form(doc, nullptr, FALSE);

  // Values should remain valid strings and calls should still succeed.
  (void)GetTextOrEmpty(field1);
  (void)GetTextOrEmpty(field2);

  g_object_unref(field1);
  g_object_unref(field2);
  g_object_unref(doc);
}