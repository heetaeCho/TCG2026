// File: poppler-structure-element-get-form-description-test-2590.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

namespace {

class ScopedGObject {
 public:
  explicit ScopedGObject(gpointer obj = nullptr) : obj_(obj) {}
  ~ScopedGObject() {
    if (obj_) g_object_unref(obj_);
  }
  ScopedGObject(const ScopedGObject&) = delete;
  ScopedGObject& operator=(const ScopedGObject&) = delete;

  ScopedGObject(ScopedGObject&& other) noexcept : obj_(other.obj_) { other.obj_ = nullptr; }
  ScopedGObject& operator=(ScopedGObject&& other) noexcept {
    if (this == &other) return *this;
    if (obj_) g_object_unref(obj_);
    obj_ = other.obj_;
    other.obj_ = nullptr;
    return *this;
  }

  gpointer get() const { return obj_; }
  gpointer release() {
    gpointer tmp = obj_;
    obj_ = nullptr;
    return tmp;
  }

 private:
  gpointer obj_;
};

class ScopedGError {
 public:
  ~ScopedGError() {
    if (err_) g_error_free(err_);
  }
  GError** out() { return &err_; }
  GError* get() const { return err_; }

 private:
  GError* err_ = nullptr;
};

class TempFile {
 public:
  TempFile() = default;
  explicit TempFile(std::string path) : path_(std::move(path)) {}
  ~TempFile() {
    if (!path_.empty()) {
      g_remove(path_.c_str());
    }
  }
  TempFile(const TempFile&) = delete;
  TempFile& operator=(const TempFile&) = delete;

  const std::string& path() const { return path_; }

 private:
  std::string path_;
};

static std::string BuildPdfWithStructElemDescObject(const std::string& struct_elem_object_body) {
  // Build a minimal valid PDF with:
  // 1) Catalog including /StructTreeRoot and /MarkInfo /Marked true
  // 2) One page
  // 3) StructTreeRoot -> one StructElem (provided body)
  //
  // We build xref offsets programmatically so Poppler can parse reliably.
  struct Obj {
    int num;
    std::string body;  // includes "<< >>" etc, without "n 0 obj" wrapper
    bool is_stream = false;
    std::string stream_data;
    std::string stream_dict;  // for streams, dict before "stream"
  };

  std::vector<Obj> objs;

  // 1 0 obj: Catalog
  objs.push_back(Obj{
      1,
      "<< /Type /Catalog /Pages 2 0 R /StructTreeRoot 5 0 R "
      "/MarkInfo << /Marked true >> >>",
      false});

  // 2 0 obj: Pages
  objs.push_back(Obj{2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>", false});

  // 3 0 obj: Page
  objs.push_back(Obj{
      3,
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 100 100] "
      "/Contents 4 0 R /Resources << >> /StructParents 0 >>",
      false});

  // 4 0 obj: empty content stream
  objs.push_back(Obj{
      4,
      "",
      true,
      "" /* stream_data */,
      "<< /Length 0 >>"});

  // 5 0 obj: StructTreeRoot
  objs.push_back(Obj{5, "<< /Type /StructTreeRoot /K [6 0 R] >>", false});

  // 6 0 obj: StructElem (provided)
  objs.push_back(Obj{6, struct_elem_object_body, false});

  std::string out;
  out += "%PDF-1.7\n";
  out += "%\xE2\xE3\xCF\xD3\n";

  // Offsets for xref (index 0 is free).
  std::vector<long> xref(7, 0);

  auto append_obj = [&](const Obj& o) {
    xref[o.num] = static_cast<long>(out.size());
    out += std::to_string(o.num);
    out += " 0 obj\n";
    if (!o.is_stream) {
      out += o.body;
      out += "\nendobj\n";
    } else {
      // Stream object
      out += o.stream_dict;
      out += "\nstream\n";
      out += o.stream_data;
      out += "\nendstream\nendobj\n";
    }
  };

  for (const auto& o : objs) append_obj(o);

  long xref_pos = static_cast<long>(out.size());
  out += "xref\n";
  out += "0 7\n";
  out += "0000000000 65535 f \n";
  for (int i = 1; i <= 6; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", xref[i]);
    out += buf;
  }

  out += "trailer\n";
  out += "<< /Size 7 /Root 1 0 R >>\n";
  out += "startxref\n";
  out += std::to_string(xref_pos);
  out += "\n%%EOF\n";

  return out;
}

static TempFile WriteTempPdf(const std::string& pdf_bytes) {
  gchar* tmp_path = nullptr;
  gint fd = g_file_open_tmp("poppler-structure-elem-2590-XXXXXX.pdf", &tmp_path, nullptr);
  EXPECT_GE(fd, 0);
  EXPECT_NE(tmp_path, nullptr);

  FILE* f = fdopen(fd, "wb");
  EXPECT_NE(f, nullptr);

  size_t written = fwrite(pdf_bytes.data(), 1, pdf_bytes.size(), f);
  EXPECT_EQ(written, pdf_bytes.size());
  fclose(f);  // also closes fd

  std::string path(tmp_path);
  g_free(tmp_path);
  return TempFile(std::move(path));
}

static ScopedGObject LoadDoc(const std::string& path) {
  ScopedGError err;
  gchar* uri = g_filename_to_uri(path.c_str(), nullptr, err.out());
  EXPECT_NE(uri, nullptr);
  EXPECT_EQ(err.get(), nullptr);

  ScopedGObject doc(poppler_document_new_from_file(uri, nullptr, err.out()));
  g_free(uri);

  EXPECT_NE(doc.get(), nullptr);
  EXPECT_EQ(err.get(), nullptr);
  return doc;
}

static PopplerStructureElement* GetFirstChild(PopplerStructureElement* root) {
  if (!root) return nullptr;
  int n = poppler_structure_element_get_n_children(root);
  if (n <= 0) return nullptr;
  return poppler_structure_element_get_child(root, 0);
}

class StructureElementFormDescriptionTest_2590 : public ::testing::Test {};

TEST_F(StructureElementFormDescriptionTest_2590, StringDescReturnsUtf8_2590) {
  // StructElem: /S /Form with /A << /Desc (Hello) >>
  const std::string struct_elem =
      "<< /Type /StructElem /S /Form /P 5 0 R /Pg 3 0 R /K 0 "
      "/A << /Desc (Hello) >> >>";
  const std::string pdf = BuildPdfWithStructElemDescObject(struct_elem);
  TempFile tf = WriteTempPdf(pdf);

  ScopedGObject doc = LoadDoc(tf.path());
  ASSERT_NE(doc.get(), nullptr);

  PopplerStructureElement* root =
      poppler_document_get_structure_root(POPPLER_DOCUMENT(doc.get()));
  ASSERT_NE(root, nullptr);

  PopplerStructureElement* form = GetFirstChild(root);
  ASSERT_NE(form, nullptr);
  ASSERT_EQ(poppler_structure_element_get_kind(form), POPPLER_STRUCTURE_ELEMENT_FORM);

  gchar* desc = poppler_structure_element_get_form_description(form);
  ASSERT_NE(desc, nullptr);
  EXPECT_STREQ(desc, "Hello");
  g_free(desc);
}

TEST_F(StructureElementFormDescriptionTest_2590, NameDescReturnsNameString_2590) {
  // StructElem: /S /Form with /A << /Desc /MyName >>
  const std::string struct_elem =
      "<< /Type /StructElem /S /Form /P 5 0 R /Pg 3 0 R /K 0 "
      "/A << /Desc /MyName >> >>";
  const std::string pdf = BuildPdfWithStructElemDescObject(struct_elem);
  TempFile tf = WriteTempPdf(pdf);

  ScopedGObject doc = LoadDoc(tf.path());
  ASSERT_NE(doc.get(), nullptr);

  PopplerStructureElement* root =
      poppler_document_get_structure_root(POPPLER_DOCUMENT(doc.get()));
  ASSERT_NE(root, nullptr);

  PopplerStructureElement* form = GetFirstChild(root);
  ASSERT_NE(form, nullptr);
  ASSERT_EQ(poppler_structure_element_get_kind(form), POPPLER_STRUCTURE_ELEMENT_FORM);

  gchar* desc = poppler_structure_element_get_form_description(form);
  ASSERT_NE(desc, nullptr);
  // Poppler's Object::getName() is expected to return the name without leading '/'.
  EXPECT_STREQ(desc, "MyName");
  g_free(desc);
}

TEST_F(StructureElementFormDescriptionTest_2590, MissingDescReturnsNull_2590) {
  // StructElem: /S /Form but no /Desc in /A
  const std::string struct_elem =
      "<< /Type /StructElem /S /Form /P 5 0 R /Pg 3 0 R /K 0 "
      "/A << >> >>";
  const std::string pdf = BuildPdfWithStructElemDescObject(struct_elem);
  TempFile tf = WriteTempPdf(pdf);

  ScopedGObject doc = LoadDoc(tf.path());
  ASSERT_NE(doc.get(), nullptr);

  PopplerStructureElement* root =
      poppler_document_get_structure_root(POPPLER_DOCUMENT(doc.get()));
  ASSERT_NE(root, nullptr);

  PopplerStructureElement* form = GetFirstChild(root);
  ASSERT_NE(form, nullptr);
  ASSERT_EQ(poppler_structure_element_get_kind(form), POPPLER_STRUCTURE_ELEMENT_FORM);

  gchar* desc = poppler_structure_element_get_form_description(form);
  EXPECT_EQ(desc, nullptr);
}

TEST_F(StructureElementFormDescriptionTest_2590, NonFormKindEmitsCriticalAndReturnsNull_2590) {
  // StructElem: /S /P (paragraph), so calling get_form_description should fail g_return_val_if_fail
  const std::string struct_elem =
      "<< /Type /StructElem /S /P /P 5 0 R /Pg 3 0 R /K 0 "
      "/A << /Desc (ShouldNotBeReturned) >> >>";
  const std::string pdf = BuildPdfWithStructElemDescObject(struct_elem);
  TempFile tf = WriteTempPdf(pdf);

  ScopedGObject doc = LoadDoc(tf.path());
  ASSERT_NE(doc.get(), nullptr);

  PopplerStructureElement* root =
      poppler_document_get_structure_root(POPPLER_DOCUMENT(doc.get()));
  ASSERT_NE(root, nullptr);

  PopplerStructureElement* elem = GetFirstChild(root);
  ASSERT_NE(elem, nullptr);
  ASSERT_NE(poppler_structure_element_get_kind(elem), POPPLER_STRUCTURE_ELEMENT_FORM);

  // g_return_val_if_fail logs a critical message and returns NULL.
  g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_STRUCTURE_ELEMENT_FORM*");
  gchar* desc = poppler_structure_element_get_form_description(elem);
  g_test_assert_expected_messages();
  EXPECT_EQ(desc, nullptr);
}

}  // namespace