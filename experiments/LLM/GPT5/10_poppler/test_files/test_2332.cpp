// poppler-form-field-text-get-text-type-test-2332.cc
#include <gtest/gtest.h>

#include <poppler.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

// This test suite treats Poppler as a black box and validates only observable
// behavior via the public GLib API.

namespace {

struct TempPdfFile {
  std::string path;   // filesystem path
  std::string uri;    // file:// URI

  TempPdfFile() = default;

  static TempPdfFile CreateWithContents(const std::string &pdf_bytes) {
    TempPdfFile f;

    // Create a temporary file.
    gchar *tmp_path = nullptr;
    GError *err = nullptr;

    // g_file_open_tmp creates a file and returns its fd.
    gint fd = g_file_open_tmp("poppler-form-field-2332-XXXXXX.pdf", &tmp_path, &err);
    if (fd == -1) {
      std::string msg = err ? err->message : "unknown error";
      if (err) g_error_free(err);
      ADD_FAILURE() << "Failed to create temp file: " << msg;
      return f;
    }

    // Write bytes.
    ssize_t total_written = 0;
    const char *data = pdf_bytes.data();
    const ssize_t len = static_cast<ssize_t>(pdf_bytes.size());
    while (total_written < len) {
      ssize_t w = write(fd, data + total_written, len - total_written);
      if (w <= 0) break;
      total_written += w;
    }
    close(fd);

    f.path = tmp_path ? tmp_path : "";
    g_free(tmp_path);

    if (total_written != len) {
      ADD_FAILURE() << "Failed to write all PDF bytes to temp file";
      return f;
    }

    // Build file:// URI (glib helper).
    gchar *uri_c = g_filename_to_uri(f.path.c_str(), /*hostname=*/nullptr, &err);
    if (!uri_c) {
      std::string msg = err ? err->message : "unknown error";
      if (err) g_error_free(err);
      ADD_FAILURE() << "g_filename_to_uri failed: " << msg;
      return f;
    }
    f.uri = uri_c;
    g_free(uri_c);

    return f;
  }

  ~TempPdfFile() {
    if (!path.empty()) {
      g_unlink(path.c_str());
    }
  }
};

static std::string BuildMinimalPdfWithFormFields_2332() {
  // Build a minimal PDF containing 1 page and 4 widget annotations:
  // - /FT /Tx with /Ff 0           => normal text
  // - /FT /Tx with /Ff 4096        => multiline (bit 13)
  // - /FT /Tx with /Ff 1048576     => file select (bit 20)
  // - /FT /Ch (choice field)       => non-text type (should hit g_return_val_if_fail and return NORMAL)
  //
  // We generate xref offsets programmatically to avoid relying on any internal Poppler behavior.

  struct Obj {
    int num;
    std::string body; // without "n 0 obj" / "endobj"
  };

  std::vector<Obj> objs;

  objs.push_back({1, "<< /Type /Catalog /Pages 2 0 R /AcroForm 8 0 R >>"});
  objs.push_back({2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>"});

  // Page with 4 annotations.
  objs.push_back({3,
                  "<< /Type /Page /Parent 2 0 R "
                  "/MediaBox [0 0 300 300] "
                  "/Resources << >> "
                  "/Annots [4 0 R 5 0 R 6 0 R 7 0 R] >>"});

  // Widget annotations (also act as fields by including /FT and /T).
  // Normal text.
  objs.push_back({4,
                  "<< /Type /Annot /Subtype /Widget "
                  "/Rect [10 250 140 280] "
                  "/P 3 0 R "
                  "/T (normal_text) "
                  "/FT /Tx "
                  "/Ff 0 >>"});
  // Multiline text.
  objs.push_back({5,
                  "<< /Type /Annot /Subtype /Widget "
                  "/Rect [10 200 140 240] "
                  "/P 3 0 R "
                  "/T (multiline_text) "
                  "/FT /Tx "
                  "/Ff 4096 >>"});
  // File select text.
  objs.push_back({6,
                  "<< /Type /Annot /Subtype /Widget "
                  "/Rect [10 150 140 190] "
                  "/P 3 0 R "
                  "/T (file_select_text) "
                  "/FT /Tx "
                  "/Ff 1048576 >>"});
  // Non-text field (choice).
  objs.push_back({7,
                  "<< /Type /Annot /Subtype /Widget "
                  "/Rect [10 100 140 140] "
                  "/P 3 0 R "
                  "/T (choice_field) "
                  "/FT /Ch "
                  "/Ff 0 >>"});

  // AcroForm dictionary referencing fields.
  objs.push_back({8, "<< /Fields [4 0 R 5 0 R 6 0 R 7 0 R] /NeedAppearances true >>"});

  std::ostringstream out;
  out << "%PDF-1.4\n";
  out << "%\xE2\xE3\xCF\xD3\n"; // binary comment

  // Track offsets (byte positions) for xref.
  // xref includes object 0 plus objects 1..8.
  std::vector<long> offsets(9, 0);

  auto current_pos = [&]() -> long {
    return static_cast<long>(out.tellp());
  };

  for (const auto &o : objs) {
    offsets[o.num] = current_pos();
    out << o.num << " 0 obj\n";
    out << o.body << "\n";
    out << "endobj\n";
  }

  const long xref_pos = current_pos();
  out << "xref\n";
  out << "0 9\n";
  out << "0000000000 65535 f \n";
  for (int i = 1; i <= 8; ++i) {
    // 10-digit, zero-padded offsets.
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    out << buf;
  }

  out << "trailer\n";
  out << "<< /Size 9 /Root 1 0 R >>\n";
  out << "startxref\n";
  out << xref_pos << "\n";
  out << "%%EOF\n";

  return out.str();
}

static std::vector<PopplerFormField *> GetAllFormFieldsFromFirstPage_2332(PopplerDocument *doc) {
  std::vector<PopplerFormField *> fields;

  PopplerPage *page = poppler_document_get_page(doc, 0);
  if (!page) {
    ADD_FAILURE() << "Failed to get page 0";
    return fields;
  }

  // Returns a GList of PopplerFormFieldMapping*
  GList *mappings = poppler_page_get_form_field_mapping(page);
  for (GList *l = mappings; l != nullptr; l = l->next) {
    auto *mapping = static_cast<PopplerFormFieldMapping *>(l->data);
    if (mapping && mapping->field) {
      // mapping owns no reference; add a ref to keep stable while list is freed.
      fields.push_back(POPPLER_FORM_FIELD(g_object_ref(mapping->field)));
    }
  }

  poppler_page_free_form_field_mapping(mappings);
  g_object_unref(page);
  return fields;
}

} // namespace

class PopplerFormFieldTextGetTextTypeTest_2332 : public ::testing::Test {};

TEST_F(PopplerFormFieldTextGetTextTypeTest_2332, ReturnsExpectedTypesForTextWidgets_2332) {
  const std::string pdf = BuildMinimalPdfWithFormFields_2332();
  TempPdfFile tmp = TempPdfFile::CreateWithContents(pdf);
  ASSERT_FALSE(tmp.path.empty());
  ASSERT_FALSE(tmp.uri.empty());

  GError *error = nullptr;
  PopplerDocument *doc = poppler_document_new_from_file(tmp.uri.c_str(), /*password=*/nullptr, &error);
  ASSERT_NE(doc, nullptr) << "poppler_document_new_from_file failed: "
                          << (error ? error->message : "unknown error");
  if (error) g_error_free(error);

  std::vector<PopplerFormField *> fields = GetAllFormFieldsFromFirstPage_2332(doc);
  ASSERT_GE(fields.size(), 3u) << "Expected at least 3 form fields on the page";

  int normal_count = 0;
  int multiline_count = 0;
  int file_select_count = 0;

  for (PopplerFormField *f : fields) {
    // Only text fields are expected to return MULTILINE/FILE_SELECT.
    // We do not assume ordering; we assert presence of each type.
    PopplerFormTextType t = poppler_form_field_text_get_text_type(f);
    switch (t) {
      case POPPLER_FORM_TEXT_NORMAL:
        normal_count++;
        break;
      case POPPLER_FORM_TEXT_MULTILINE:
        multiline_count++;
        break;
      case POPPLER_FORM_TEXT_FILE_SELECT:
        file_select_count++;
        break;
      default:
        ADD_FAILURE() << "Unexpected PopplerFormTextType value: " << static_cast<int>(t);
        break;
    }
  }

  // Observable outcome: at least one field of each expected text subtype exists in the document.
  EXPECT_GE(normal_count, 1) << "Expected at least one NORMAL text type (also includes non-text fields)";
  EXPECT_EQ(multiline_count, 1) << "Expected exactly one MULTILINE text field";
  EXPECT_EQ(file_select_count, 1) << "Expected exactly one FILE_SELECT text field";

  for (PopplerFormField *f : fields) g_object_unref(f);
  g_object_unref(doc);
}

TEST_F(PopplerFormFieldTextGetTextTypeTest_2332, NonTextFieldReturnsNormal_2332) {
  const std::string pdf = BuildMinimalPdfWithFormFields_2332();
  TempPdfFile tmp = TempPdfFile::CreateWithContents(pdf);
  ASSERT_FALSE(tmp.uri.empty());

  GError *error = nullptr;
  PopplerDocument *doc = poppler_document_new_from_file(tmp.uri.c_str(), /*password=*/nullptr, &error);
  ASSERT_NE(doc, nullptr) << "poppler_document_new_from_file failed: "
                          << (error ? error->message : "unknown error");
  if (error) g_error_free(error);

  std::vector<PopplerFormField *> fields = GetAllFormFieldsFromFirstPage_2332(doc);
  ASSERT_GE(fields.size(), 4u) << "Expected 4 form fields (3 text + 1 choice)";

  // Identify a non-text field via the public type API and validate the function returns NORMAL.
  bool found_non_text = false;
  for (PopplerFormField *f : fields) {
    PopplerFormFieldType ty = poppler_form_field_get_field_type(f);
    if (ty != POPPLER_FORM_FIELD_TEXT) {
      found_non_text = true;
      EXPECT_EQ(poppler_form_field_text_get_text_type(f), POPPLER_FORM_TEXT_NORMAL)
          << "For non-text fields, g_return_val_if_fail should cause NORMAL to be returned";
      break;
    }
  }
  EXPECT_TRUE(found_non_text) << "Did not find any non-text field to test error path";

  for (PopplerFormField *f : fields) g_object_unref(f);
  g_object_unref(doc);
}

TEST_F(PopplerFormFieldTextGetTextTypeTest_2332, EmptyDocumentNoCrashOnLoadError_2332) {
  // Exceptional/error case observable via interface: loading invalid PDF should fail and
  // return nullptr with GError set; we do not call the target function in that case.
  const std::string not_a_pdf = "this is not a pdf";
  TempPdfFile tmp = TempPdfFile::CreateWithContents(not_a_pdf);
  ASSERT_FALSE(tmp.uri.empty());

  GError *error = nullptr;
  PopplerDocument *doc = poppler_document_new_from_file(tmp.uri.c_str(), /*password=*/nullptr, &error);
  EXPECT_EQ(doc, nullptr);
  EXPECT_NE(error, nullptr);
  if (error) g_error_free(error);
}