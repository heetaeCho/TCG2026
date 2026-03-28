// File: poppler-form-field-get-mapping-name-test_2318.cc
//
// Unit tests for:
//   gchar *poppler_form_field_get_mapping_name(PopplerFormField *field)
//
// These tests treat the implementation as a black box and validate only
// observable behavior through the public Poppler GLib API.

#include <gtest/gtest.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <poppler.h> // poppler-glib main header (often provides PopplerDocument/PopplerPage/etc.)

#include <string>
#include <vector>
#include <sstream>
#include <utility>

namespace {

static std::string BuildMinimalPdfWithTextField(bool include_tm, const std::string& tm_value_ascii) {
  // Minimal, single-page PDF with one AcroForm text field and one widget annotation.
  // If include_tm is true, adds /TM (mapping name) to the field dictionary.
  //
  // Objects:
  // 1 0: Catalog (/Root)
  // 2 0: Pages
  // 3 0: Page (with Annots [6 0 R])
  // 4 0: Contents (empty stream)
  // 5 0: AcroForm (Fields [7 0 R])
  // 6 0: Widget annotation (/Subtype /Widget /Parent 7 0 R)
  // 7 0: Field dictionary (/FT /Tx /T ... [/TM ...] /Kids [6 0 R])
  //
  // NOTE: This is test data generation, not re-implementing Poppler logic.

  struct Obj {
    int num;
    std::string body;
  };

  std::vector<Obj> objs;

  {
    std::ostringstream o;
    o << "<< /Type /Catalog /Pages 2 0 R /AcroForm 5 0 R >>";
    objs.push_back({1, o.str()});
  }
  {
    std::ostringstream o;
    o << "<< /Type /Pages /Kids [3 0 R] /Count 1 >>";
    objs.push_back({2, o.str()});
  }
  {
    std::ostringstream o;
    o << "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 300 300]\n"
      << "   /Resources << >>\n"
      << "   /Contents 4 0 R\n"
      << "   /Annots [6 0 R]\n"
      << ">>";
    objs.push_back({3, o.str()});
  }
  {
    // Empty contents stream.
    std::ostringstream o;
    o << "<< /Length 0 >>\n"
      << "stream\n"
      << "\n"
      << "endstream";
    objs.push_back({4, o.str()});
  }
  {
    std::ostringstream o;
    o << "<< /Fields [7 0 R] /NeedAppearances true >>";
    objs.push_back({5, o.str()});
  }
  {
    std::ostringstream o;
    o << "<< /Type /Annot /Subtype /Widget\n"
      << "   /Parent 7 0 R\n"
      << "   /Rect [50 50 150 70]\n"
      << "   /P 3 0 R\n"
      << "   /F 4\n"
      << ">>";
    objs.push_back({6, o.str()});
  }
  {
    std::ostringstream o;
    o << "<< /FT /Tx\n"
      << "   /T (Name)\n";
    if (include_tm) {
      // ASCII mapping name to avoid encoding ambiguity in a minimal PDF.
      o << "   /TM (" << tm_value_ascii << ")\n";
    }
    o << "   /V (abc)\n"
      << "   /Kids [6 0 R]\n"
      << ">>";
    objs.push_back({7, o.str()});
  }

  std::ostringstream pdf;
  pdf << "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n";

  // Track offsets for xref.
  // xref has entries from 0..max_obj inclusive.
  const int max_obj = 7;
  std::vector<long> offsets(static_cast<size_t>(max_obj + 1), 0);

  // Object 0 is the free object.
  offsets[0] = 0;

  for (const auto& obj : objs) {
    offsets[obj.num] = static_cast<long>(pdf.tellp());
    pdf << obj.num << " 0 obj\n" << obj.body << "\nendobj\n";
  }

  const long xref_pos = static_cast<long>(pdf.tellp());

  pdf << "xref\n";
  pdf << "0 " << (max_obj + 1) << "\n";
  pdf << "0000000000 65535 f \n";
  for (int i = 1; i <= max_obj; ++i) {
    // 10-digit, zero-padded offsets.
    char buf[32];
    g_snprintf(buf, sizeof(buf), "%010ld", offsets[i]);
    pdf << buf << " 00000 n \n";
  }

  pdf << "trailer\n";
  pdf << "<< /Size " << (max_obj + 1) << " /Root 1 0 R >>\n";
  pdf << "startxref\n";
  pdf << xref_pos << "\n";
  pdf << "%%EOF\n";

  return pdf.str();
}

static std::string WriteToTempFile(const std::string& bytes) {
  // Create a temp file and write bytes.
  gchar* filename = nullptr;
  gint fd = g_file_open_tmp("poppler_mapping_name_XXXXXX.pdf", &filename, nullptr);
  EXPECT_GE(fd, 0);
  EXPECT_NE(filename, nullptr);

  // Write all bytes.
  gssize to_write = static_cast<gssize>(bytes.size());
  const char* p = bytes.data();
  while (to_write > 0) {
    gssize n = write(fd, p, static_cast<size_t>(to_write));
    EXPECT_GT(n, 0);
    p += n;
    to_write -= n;
  }
  close(fd);

  std::string path(filename);
  g_free(filename);
  return path;
}

static std::string FilenameToFileUri(const std::string& filename) {
  GError* error = nullptr;
  gchar* uri = g_filename_to_uri(filename.c_str(), nullptr, &error);
  EXPECT_EQ(error, nullptr);
  EXPECT_NE(uri, nullptr);
  std::string s(uri);
  g_free(uri);
  return s;
}

static PopplerFormField* GetFirstFormFieldFromDoc(PopplerDocument* doc) {
  EXPECT_NE(doc, nullptr);

  PopplerPage* page = poppler_document_get_page(doc, 0);
  EXPECT_NE(page, nullptr);

  // Poppler GLib commonly exposes form fields per-page via a mapping list.
  // We only use public API to obtain a PopplerFormField instance.
  GList* mappings = poppler_page_get_form_field_mapping(page);
  EXPECT_NE(mappings, nullptr);

  // mapping struct is typically PopplerFormFieldMapping with "field" member.
  auto* mapping = static_cast<PopplerFormFieldMapping*>(mappings->data);
  EXPECT_NE(mapping, nullptr);
  EXPECT_NE(mapping->field, nullptr);

  PopplerFormField* field = mapping->field;
  // Keep field alive via doc/page references already held by Poppler; we just use it immediately.

  // Free mapping list using the public helper (preferred over manual free).
  poppler_page_free_form_field_mapping(mappings);

  g_object_unref(page);
  return field;
}

class PopplerFormFieldMappingNameTest_2318 : public ::testing::Test {
 protected:
  void TearDown() override {
    if (!temp_path_.empty()) {
      g_remove(temp_path_.c_str());
      temp_path_.clear();
    }
  }

  PopplerDocument* LoadDocFromPdfBytes(const std::string& pdf_bytes) {
    temp_path_ = WriteToTempFile(pdf_bytes);
    const std::string uri = FilenameToFileUri(temp_path_);

    GError* error = nullptr;
    PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
    EXPECT_EQ(error, nullptr);
    EXPECT_NE(doc, nullptr);
    return doc;
  }

  std::string temp_path_;
};

}  // namespace

TEST_F(PopplerFormFieldMappingNameTest_2318, NullFieldReturnsNull_2318) {
  // Error case: NULL argument should return NULL (g_return_val_if_fail).
  gchar* name = poppler_form_field_get_mapping_name(nullptr);
  EXPECT_EQ(name, nullptr);
}

TEST_F(PopplerFormFieldMappingNameTest_2318, WrongTypeReturnsNull_2318) {
  // Error case: pass a non-PopplerFormField GObject; must return NULL.
  GObject* obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  gchar* name = poppler_form_field_get_mapping_name(reinterpret_cast<PopplerFormField*>(obj));
  EXPECT_EQ(name, nullptr);

  g_object_unref(obj);
}

TEST_F(PopplerFormFieldMappingNameTest_2318, ReturnsMappingNameWhenPresent_2318) {
  const std::string pdf = BuildMinimalPdfWithTextField(/*include_tm=*/true, "MapName");
  PopplerDocument* doc = LoadDocFromPdfBytes(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerFormField* field = GetFirstFormFieldFromDoc(doc);
  ASSERT_NE(field, nullptr);

  gchar* name = poppler_form_field_get_mapping_name(field);
  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name, "MapName");

  g_free(name);
  g_object_unref(doc);
}

TEST_F(PopplerFormFieldMappingNameTest_2318, ReturnsNullWhenNoMappingName_2318) {
  const std::string pdf = BuildMinimalPdfWithTextField(/*include_tm=*/false, "");
  PopplerDocument* doc = LoadDocFromPdfBytes(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerFormField* field = GetFirstFormFieldFromDoc(doc);
  ASSERT_NE(field, nullptr);

  gchar* name = poppler_form_field_get_mapping_name(field);
  EXPECT_EQ(name, nullptr);

  g_object_unref(doc);
}

TEST_F(PopplerFormFieldMappingNameTest_2318, CanBeCalledRepeatedlyAfterFreeingResult_2318) {
  // Boundary/robustness: returned string is caller-owned; freeing it should not break future calls.
  const std::string pdf = BuildMinimalPdfWithTextField(/*include_tm=*/true, "MapName");
  PopplerDocument* doc = LoadDocFromPdfBytes(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerFormField* field = GetFirstFormFieldFromDoc(doc);
  ASSERT_NE(field, nullptr);

  gchar* name1 = poppler_form_field_get_mapping_name(field);
  ASSERT_NE(name1, nullptr);
  EXPECT_STREQ(name1, "MapName");
  g_free(name1);

  gchar* name2 = poppler_form_field_get_mapping_name(field);
  ASSERT_NE(name2, nullptr);
  EXPECT_STREQ(name2, "MapName");
  g_free(name2);

  g_object_unref(doc);
}