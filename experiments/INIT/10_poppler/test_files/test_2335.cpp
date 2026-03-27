//===----------------------------------------------------------------------===//
// poppler_form_field_text_get_max_len unit tests
// File: poppler-form-field-text-get-max-len-test-2335.cc
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <string>
#include <vector>

// NOTE: We treat Poppler as a black box. These tests validate observable behavior
// via the public Poppler GLib API + the function under test.

namespace {

struct FieldSpec {
  enum class Type { kText, kButton };

  Type type;
  std::string name;
  // For text fields: if max_len < 0, omit /MaxLen entry.
  int max_len;
  // Widget rect
  double x1, y1, x2, y2;
};

static std::string BuildPdfOnePageWithFields(const std::vector<FieldSpec> &fields) {
  // Minimal PDF builder that emits valid xref offsets.
  // Objects:
  // 1 0 obj: Catalog
  // 2 0 obj: Pages
  // 3 0 obj: Page (Annots)
  // 4 0 obj: Contents (empty stream)
  // 5 0 obj: AcroForm (Fields)
  // N.. objs: each field/widget (combined field+widget dict)

  auto fmt = [](const char *s) { return std::string(s); };

  std::vector<std::string> objs;
  objs.reserve(6 + fields.size());

  // We'll fill Catalog and Page once we know AcroForm/Annots refs.
  // Object numbers:
  // 1: Catalog
  // 2: Pages
  // 3: Page
  // 4: Contents
  // 5: AcroForm
  // 6..: Fields
  const int catalog_obj = 1;
  const int pages_obj = 2;
  const int page_obj = 3;
  const int contents_obj = 4;
  const int acroform_obj = 5;
  const int first_field_obj = 6;

  // Placeholder for 1..5
  objs.push_back(""); // 1
  objs.push_back(""); // 2
  objs.push_back(""); // 3
  objs.push_back(""); // 4
  objs.push_back(""); // 5

  // Field objects
  for (size_t i = 0; i < fields.size(); ++i) {
    const int objnum = first_field_obj + static_cast<int>(i);
    (void)objnum;

    const FieldSpec &f = fields[i];

    std::string ft;
    if (f.type == FieldSpec::Type::kText) {
      ft = "/FT /Tx";
    } else {
      ft = "/FT /Btn";
    }

    std::string maxlen;
    if (f.type == FieldSpec::Type::kText && f.max_len >= 0) {
      maxlen = " /MaxLen " + std::to_string(f.max_len);
    }

    // Combined field+widget dictionary.
    // Put it directly in /AcroForm /Fields and also reference it from /Page /Annots.
    //
    // /P is the page reference; /Subtype /Widget; /T is field name; /Rect defines widget.
    std::string obj;
    obj += "<< /Type /Annot /Subtype /Widget ";
    obj += ft;
    obj += " /T (" + f.name + ")";
    obj += maxlen;
    obj += " /Rect [";
    obj += std::to_string(f.x1) + " " + std::to_string(f.y1) + " ";
    obj += std::to_string(f.x2) + " " + std::to_string(f.y2) + "]";
    obj += " /P 3 0 R";
    obj += " >>";

    objs.push_back(obj);
  }

  // Build /Annots array
  std::string annots = "[ ";
  for (size_t i = 0; i < fields.size(); ++i) {
    annots += std::to_string(first_field_obj + static_cast<int>(i));
    annots += " 0 R ";
  }
  annots += "]";

  // Build /Fields array
  std::string fields_arr = "[ ";
  for (size_t i = 0; i < fields.size(); ++i) {
    fields_arr += std::to_string(first_field_obj + static_cast<int>(i));
    fields_arr += " 0 R ";
  }
  fields_arr += "]";

  // Object 4: empty content stream
  objs[contents_obj - 1] = "<< /Length 0 >>\nstream\n\nendstream";

  // Object 2: Pages
  objs[pages_obj - 1] = "<< /Type /Pages /Kids [ 3 0 R ] /Count 1 >>";

  // Object 5: AcroForm
  objs[acroform_obj - 1] = "<< /Fields " + fields_arr + " >>";

  // Object 3: Page
  objs[page_obj - 1] =
      "<< /Type /Page /Parent 2 0 R "
      "/MediaBox [ 0 0 612 792 ] "
      "/Contents 4 0 R "
      "/Resources << >> "
      "/Annots " +
      annots + " >>";

  // Object 1: Catalog
  objs[catalog_obj - 1] =
      "<< /Type /Catalog /Pages 2 0 R /AcroForm 5 0 R >>";

  // Emit PDF with xref
  std::string out;
  out.reserve(4096);

  out += "%PDF-1.7\n";
  std::vector<long> offsets;
  offsets.reserve(objs.size() + 1);
  offsets.push_back(0); // object 0 (free)

  auto current_offset = [&]() -> long { return static_cast<long>(out.size()); };

  for (size_t i = 0; i < objs.size(); ++i) {
    const int objnum = static_cast<int>(i) + 1;
    offsets.push_back(current_offset());
    out += std::to_string(objnum) + " 0 obj\n";
    out += objs[i];
    out += "\nendobj\n";
  }

  const long xref_pos = current_offset();
  out += "xref\n";
  out += "0 " + std::to_string(objs.size() + 1) + "\n";
  out += "0000000000 65535 f \n";
  for (size_t i = 1; i < offsets.size(); ++i) {
    char buf[32];
    // 10-digit, zero-padded offset, gen 00000, in-use 'n'
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    out += buf;
  }

  out += "trailer\n";
  out += "<< /Size " + std::to_string(objs.size() + 1) + " /Root 1 0 R >>\n";
  out += "startxref\n";
  out += std::to_string(xref_pos) + "\n";
  out += "%%EOF\n";

  return out;
}

static std::string WriteTempPdfAndGetUri(const std::string &pdf_bytes) {
  // Create a temp file path
  gchar *path = nullptr;
  {
    GError *err = nullptr;
    int fd = g_file_open_tmp("poppler-maxlen-XXXXXX.pdf", &path, &err);
    if (fd >= 0) {
#ifdef G_OS_WIN32
      _close(fd);
#else
      close(fd);
#endif
    }
    if (err) {
      std::string msg = err->message ? err->message : "unknown";
      g_error_free(err);
      g_free(path);
      throw std::runtime_error("g_file_open_tmp failed: " + msg);
    }
  }

  // Write bytes
  {
    GError *err = nullptr;
    if (!g_file_set_contents(path, pdf_bytes.data(),
                             static_cast<gssize>(pdf_bytes.size()), &err)) {
      std::string msg = err && err->message ? err->message : "unknown";
      if (err) g_error_free(err);
      std::string p = path ? path : "";
      g_free(path);
      throw std::runtime_error("g_file_set_contents failed for " + p + ": " + msg);
    }
  }

  gchar *uri = g_filename_to_uri(path, nullptr, nullptr);
  std::string out_uri = uri ? uri : "";
  g_free(uri);
  g_free(path);
  return out_uri;
}

static PopplerFormField *GetFirstFieldOnFirstPage(PopplerDocument *doc) {
  PopplerPage *page = poppler_document_get_page(doc, 0);
  if (!page) return nullptr;

  GList *mappings = poppler_page_get_form_field_mapping(page);
  poppler_page_unref(page);

  if (!mappings) return nullptr;

  // Take first mapping
  auto *mapping = static_cast<PopplerFormFieldMapping *>(mappings->data);
  PopplerFormField *field = mapping ? mapping->field : nullptr;

  // Hold a reference to field object (it is a GObject)
  if (field) g_object_ref(field);

  poppler_page_free_form_field_mapping(mappings);
  return field;
}

} // namespace

class PopplerFormFieldTextGetMaxLenTest_2335 : public ::testing::Test {
protected:
  static PopplerDocument *LoadDocFromPdfBytes(const std::string &pdf_bytes) {
    std::string uri = WriteTempPdfAndGetUri(pdf_bytes);

    GError *err = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &err);

    if (err) {
      std::string msg = err->message ? err->message : "unknown";
      g_error_free(err);
      return nullptr;
    }
    return doc;
  }
};

TEST_F(PopplerFormFieldTextGetMaxLenTest_2335, ReturnsMaxLenWhenSet_2335) {
  const std::string pdf = BuildPdfOnePageWithFields({
      FieldSpec{FieldSpec::Type::kText, "txt", 17, 100, 600, 200, 620},
  });

  PopplerDocument *doc = LoadDocFromPdfBytes(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerFormField *field = GetFirstFieldOnFirstPage(doc);
  ASSERT_NE(field, nullptr);

  // Sanity: field type should be text
  EXPECT_EQ(poppler_form_field_get_field_type(field), POPPLER_FORM_FIELD_TEXT);

  // Function under test
  EXPECT_EQ(poppler_form_field_text_get_max_len(field), 17);

  g_object_unref(field);
  g_object_unref(doc);
}

TEST_F(PopplerFormFieldTextGetMaxLenTest_2335, ReturnsZeroWhenMaxLenNotPresent_2335) {
  const std::string pdf = BuildPdfOnePageWithFields({
      FieldSpec{FieldSpec::Type::kText, "txt", -1, 100, 600, 200, 620}, // no /MaxLen
  });

  PopplerDocument *doc = LoadDocFromPdfBytes(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerFormField *field = GetFirstFieldOnFirstPage(doc);
  ASSERT_NE(field, nullptr);

  EXPECT_EQ(poppler_form_field_get_field_type(field), POPPLER_FORM_FIELD_TEXT);

  // Observable expectation: when /MaxLen is not specified, Poppler reports 0.
  EXPECT_EQ(poppler_form_field_text_get_max_len(field), 0);

  g_object_unref(field);
  g_object_unref(doc);
}

TEST_F(PopplerFormFieldTextGetMaxLenTest_2335, ReturnsZeroForNonTextField_2335) {
  const std::string pdf = BuildPdfOnePageWithFields({
      FieldSpec{FieldSpec::Type::kButton, "btn", -1, 100, 600, 200, 620},
  });

  PopplerDocument *doc = LoadDocFromPdfBytes(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerFormField *field = GetFirstFieldOnFirstPage(doc);
  ASSERT_NE(field, nullptr);

  // Sanity: should not be text
  EXPECT_NE(poppler_form_field_get_field_type(field), POPPLER_FORM_FIELD_TEXT);

  // Function under test should return 0 due to g_return_val_if_fail().
  EXPECT_EQ(poppler_form_field_text_get_max_len(field), 0);

  g_object_unref(field);
  g_object_unref(doc);
}

TEST_F(PopplerFormFieldTextGetMaxLenTest_2335, BoundaryLargeMaxLenValue_2335) {
  // Boundary-ish: ensure large, but reasonable int value round-trips.
  const int kLarge = 100000;
  const std::string pdf = BuildPdfOnePageWithFields({
      FieldSpec{FieldSpec::Type::kText, "txt", kLarge, 100, 600, 200, 620},
  });

  PopplerDocument *doc = LoadDocFromPdfBytes(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerFormField *field = GetFirstFieldOnFirstPage(doc);
  ASSERT_NE(field, nullptr);

  EXPECT_EQ(poppler_form_field_get_field_type(field), POPPLER_FORM_FIELD_TEXT);
  EXPECT_EQ(poppler_form_field_text_get_max_len(field), kLarge);

  g_object_unref(field);
  g_object_unref(doc);
}