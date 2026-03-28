// poppler-form-field-get-field-type-test.cc
// Unit tests for poppler_form_field_get_field_type()
// TEST_ID: 2308

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <string>
#include <vector>

// ---- Helpers to build a minimal PDF with AcroForm widget annotations ----
// We generate a small PDF at runtime (no external test data dependency) that
// contains 4 terminal form fields on a single page:
//
//  - Button (/FT /Btn)
//  - Text   (/FT /Tx)
//  - Choice (/FT /Ch)
//  - Signature (/FT /Sig)
//
// Poppler should expose them as PopplerFormField objects via
// poppler_page_get_form_field_mapping(), and poppler_form_field_get_field_type()
// should map them to the corresponding PopplerFormFieldType.
static std::string BuildPdfWithAcroFormWidgets_2308() {
  struct Obj {
    int num;
    std::string body; // includes "obj ... endobj"
  };

  // Objects:
  // 1  Catalog
  // 2  Pages
  // 3  Page
  // 4  Contents
  // 5  Resources (Font dict)
  // 6  Font (Helvetica)
  // 7  AcroForm dict
  // 8  Button widget
  // 9  Text widget
  // 10 Choice widget
  // 11 Signature widget
  //
  // Notes:
  // - Widgets are included in Page /Annots and in AcroForm /Fields.
  // - Minimal /DA and /DR for text/choice fields.
  std::vector<Obj> objs;

  // 6: Font object
  objs.push_back({6,
                  "6 0 obj\n"
                  "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
                  "endobj\n"});

  // 5: Resources object referencing font 6
  objs.push_back({5,
                  "5 0 obj\n"
                  "<< /Font << /Helv 6 0 R >> >>\n"
                  "endobj\n"});

  // 4: Simple empty content stream (page will still load)
  objs.push_back({4,
                  "4 0 obj\n"
                  "<< /Length 0 >>\n"
                  "stream\n"
                  "\n"
                  "endstream\n"
                  "endobj\n"});

  // 8: Button widget annotation (terminal field)
  objs.push_back({8,
                  "8 0 obj\n"
                  "<< /Type /Annot /Subtype /Widget\n"
                  "   /FT /Btn\n"
                  "   /T (btn)\n"
                  "   /Rect [50 700 150 730]\n"
                  "   /F 4\n"
                  "   /P 3 0 R\n"
                  ">>\n"
                  "endobj\n"});

  // 9: Text widget annotation
  objs.push_back({9,
                  "9 0 obj\n"
                  "<< /Type /Annot /Subtype /Widget\n"
                  "   /FT /Tx\n"
                  "   /T (txt)\n"
                  "   /Rect [50 650 250 680]\n"
                  "   /F 4\n"
                  "   /P 3 0 R\n"
                  "   /DA (/Helv 10 Tf 0 g)\n"
                  ">>\n"
                  "endobj\n"});

  // 10: Choice widget annotation (combo/list)
  objs.push_back({10,
                  "10 0 obj\n"
                  "<< /Type /Annot /Subtype /Widget\n"
                  "   /FT /Ch\n"
                  "   /T (ch)\n"
                  "   /Rect [50 600 250 630]\n"
                  "   /F 4\n"
                  "   /P 3 0 R\n"
                  "   /DA (/Helv 10 Tf 0 g)\n"
                  "   /Opt [(One) (Two) (Three)]\n"
                  ">>\n"
                  "endobj\n"});

  // 11: Signature widget annotation
  objs.push_back({11,
                  "11 0 obj\n"
                  "<< /Type /Annot /Subtype /Widget\n"
                  "   /FT /Sig\n"
                  "   /T (sig)\n"
                  "   /Rect [50 550 250 580]\n"
                  "   /F 4\n"
                  "   /P 3 0 R\n"
                  ">>\n"
                  "endobj\n"});

  // 7: AcroForm dict
  objs.push_back({7,
                  "7 0 obj\n"
                  "<< /Fields [8 0 R 9 0 R 10 0 R 11 0 R]\n"
                  "   /DR 5 0 R\n"
                  "   /DA (/Helv 10 Tf 0 g)\n"
                  ">>\n"
                  "endobj\n"});

  // 3: Page
  objs.push_back({3,
                  "3 0 obj\n"
                  "<< /Type /Page\n"
                  "   /Parent 2 0 R\n"
                  "   /MediaBox [0 0 612 792]\n"
                  "   /Resources 5 0 R\n"
                  "   /Contents 4 0 R\n"
                  "   /Annots [8 0 R 9 0 R 10 0 R 11 0 R]\n"
                  ">>\n"
                  "endobj\n"});

  // 2: Pages
  objs.push_back({2,
                  "2 0 obj\n"
                  "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
                  "endobj\n"});

  // 1: Catalog
  objs.push_back({1,
                  "1 0 obj\n"
                  "<< /Type /Catalog /Pages 2 0 R /AcroForm 7 0 R >>\n"
                  "endobj\n"});

  // Sort by object number for a conventional layout (not strictly required)
  std::sort(objs.begin(), objs.end(),
            [](const Obj& a, const Obj& b) { return a.num < b.num; });

  std::string pdf;
  pdf += "%PDF-1.4\n";
  pdf += "%\xE2\xE3\xCF\xD3\n";

  // Track offsets (byte positions) for xref.
  // xref needs entry 0 plus up to max object number.
  int max_obj = 0;
  for (const auto& o : objs) max_obj = std::max(max_obj, o.num);

  std::vector<long> offsets(max_obj + 1, -1);
  offsets[0] = 0;

  for (const auto& o : objs) {
    offsets[o.num] = static_cast<long>(pdf.size());
    pdf += o.body;
  }

  long xref_pos = static_cast<long>(pdf.size());
  pdf += "xref\n";
  pdf += "0 " + std::to_string(max_obj + 1) + "\n";
  // Object 0: free
  pdf += "0000000000 65535 f \n";
  for (int i = 1; i <= max_obj; ++i) {
    long off = offsets[i];
    if (off < 0) {
      // Shouldn't happen with our constructed set, but keep the xref valid.
      pdf += "0000000000 65535 f \n";
      continue;
    }
    char buf[32];
    // 10-digit, zero-padded offset
    g_snprintf(buf, sizeof(buf), "%010ld", off);
    pdf += std::string(buf) + " 00000 n \n";
  }

  pdf += "trailer\n";
  pdf += "<< /Size " + std::to_string(max_obj + 1) + " /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_pos) + "\n";
  pdf += "%%EOF\n";
  return pdf;
}

static std::string WriteTempPdfAndGetUri_2308(const std::string& pdf_bytes) {
  GError* error = nullptr;

  // Create a temp file path
  gchar* tmpname = g_strdup_printf("poppler_form_field_type_2308_XXXXXX.pdf");
  gchar* tmpdir = g_dir_make_tmp("poppler_gtest_2308_XXXXXX", &error);
  if (!tmpdir) {
    std::string msg = error ? error->message : "unknown error";
    if (error) g_error_free(error);
    g_free(tmpname);
    throw std::runtime_error("Failed to create temp dir: " + msg);
  }

  gchar* path = g_build_filename(tmpdir, tmpname, nullptr);
  g_free(tmpname);

  if (!g_file_set_contents(path, pdf_bytes.data(),
                           static_cast<gssize>(pdf_bytes.size()), &error)) {
    std::string msg = error ? error->message : "unknown error";
    if (error) g_error_free(error);
    g_free(tmpdir);
    g_free(path);
    throw std::runtime_error("Failed to write temp PDF: " + msg);
  }

  gchar* uri = g_filename_to_uri(path, nullptr, &error);
  if (!uri) {
    std::string msg = error ? error->message : "unknown error";
    if (error) g_error_free(error);
    g_free(tmpdir);
    g_free(path);
    throw std::runtime_error("Failed to convert path to URI: " + msg);
  }

  // Keep directory around for the duration of the test run; the OS temp cleanup
  // is fine. We only need the URI string.
  std::string out(uri);
  g_free(uri);
  g_free(path);
  g_free(tmpdir);
  return out;
}

class PopplerFormFieldGetFieldTypeTest_2308 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Ensure GLib is initialized enough for Poppler usage in tests.
    // (No-op on many platforms; safe to call.)
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif
  }
};

TEST_F(PopplerFormFieldGetFieldTypeTest_2308, NullFieldReturnsUnknown_2308) {
  // Boundary/error case: g_return_val_if_fail should handle null input.
  EXPECT_EQ(poppler_form_field_get_field_type(nullptr),
            POPPLER_FORM_FIELD_UNKNOWN);
}

TEST_F(PopplerFormFieldGetFieldTypeTest_2308,
       MapsWidgetTypesFromPdf_2308) {
  const std::string pdf = BuildPdfWithAcroFormWidgets_2308();
  const std::string uri = WriteTempPdfAndGetUri_2308(pdf);

  GError* error = nullptr;
  PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
  ASSERT_NE(doc, nullptr) << (error ? error->message : "poppler_document_new_from_file failed");
  if (error) {
    g_error_free(error);
    error = nullptr;
  }

  PopplerPage* page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  // Retrieve form field mappings from the page.
  GList* mappings = poppler_page_get_form_field_mapping(page);
  ASSERT_NE(mappings, nullptr) << "Expected form field mappings for constructed PDF";

  // Collect observed types by field name (from PopplerFormField API).
  // We avoid assumptions about list ordering.
  bool saw_button = false;
  bool saw_text = false;
  bool saw_choice = false;
  bool saw_sig = false;

  for (GList* l = mappings; l != nullptr; l = l->next) {
    auto* m = static_cast<PopplerFormFieldMapping*>(l->data);
    ASSERT_NE(m, nullptr);
    ASSERT_NE(m->field, nullptr);

    gchar* name = poppler_form_field_get_name(m->field);
    ASSERT_NE(name, nullptr);

    PopplerFormFieldType t = poppler_form_field_get_field_type(m->field);

    if (g_strcmp0(name, "btn") == 0) {
      EXPECT_EQ(t, POPPLER_FORM_FIELD_BUTTON);
      saw_button = true;
    } else if (g_strcmp0(name, "txt") == 0) {
      EXPECT_EQ(t, POPPLER_FORM_FIELD_TEXT);
      saw_text = true;
    } else if (g_strcmp0(name, "ch") == 0) {
      EXPECT_EQ(t, POPPLER_FORM_FIELD_CHOICE);
      saw_choice = true;
    } else if (g_strcmp0(name, "sig") == 0) {
      EXPECT_EQ(t, POPPLER_FORM_FIELD_SIGNATURE);
      saw_sig = true;
    }

    g_free(name);
  }

  EXPECT_TRUE(saw_button);
  EXPECT_TRUE(saw_text);
  EXPECT_TRUE(saw_choice);
  EXPECT_TRUE(saw_sig);

  poppler_page_free_form_field_mapping(mappings);
  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerFormFieldGetFieldTypeTest_2308,
       RepeatedCallsAreStable_2308) {
  const std::string pdf = BuildPdfWithAcroFormWidgets_2308();
  const std::string uri = WriteTempPdfAndGetUri_2308(pdf);

  GError* error = nullptr;
  PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
  ASSERT_NE(doc, nullptr) << (error ? error->message : "poppler_document_new_from_file failed");
  if (error) {
    g_error_free(error);
    error = nullptr;
  }

  PopplerPage* page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  GList* mappings = poppler_page_get_form_field_mapping(page);
  ASSERT_NE(mappings, nullptr);

  // Pick one known field and call the function multiple times to ensure
  // observable stability (no side-effect assumptions).
  PopplerFormField* target = nullptr;
  PopplerFormFieldType expected = POPPLER_FORM_FIELD_UNKNOWN;

  for (GList* l = mappings; l != nullptr; l = l->next) {
    auto* m = static_cast<PopplerFormFieldMapping*>(l->data);
    if (!m || !m->field) continue;

    gchar* name = poppler_form_field_get_name(m->field);
    if (!name) continue;

    if (g_strcmp0(name, "txt") == 0) {
      target = m->field;
      expected = POPPLER_FORM_FIELD_TEXT;
      g_free(name);
      break;
    }
    g_free(name);
  }

  ASSERT_NE(target, nullptr);

  EXPECT_EQ(poppler_form_field_get_field_type(target), expected);
  EXPECT_EQ(poppler_form_field_get_field_type(target), expected);
  EXPECT_EQ(poppler_form_field_get_field_type(target), expected);

  poppler_page_free_form_field_mapping(mappings);
  g_object_unref(page);
  g_object_unref(doc);
}