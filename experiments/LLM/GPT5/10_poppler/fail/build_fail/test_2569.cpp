// poppler_structure_element_get_bounding_box_test_2569.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <sstream>
#include <string>
#include <vector>

namespace {

struct TempFile {
  std::string path;

  TempFile() {
    gchar *tmpl = g_strdup("/tmp/poppler-structure-bbox-XXXXXX.pdf");
    int fd = g_mkstemp(tmpl);
    if (fd >= 0) {
      close(fd);
      path = tmpl;
    }
    g_free(tmpl);
  }

  ~TempFile() {
    if (!path.empty()) {
      std::remove(path.c_str());
    }
  }

  TempFile(const TempFile &) = delete;
  TempFile &operator=(const TempFile &) = delete;
};

static std::string BuildPdfWithStructElemAndOptionalBBox(const char *struct_type_name,
                                                         bool include_bbox,
                                                         double x1,
                                                         double y1,
                                                         double x2,
                                                         double y2) {
  // Minimal PDF with:
  // - 1 page
  // - StructTreeRoot -> single StructElem
  // - StructElem includes /A << /O /Layout /BBox [x1 y1 x2 y2] >> (optional)
  //
  // This is intentionally tiny; Poppler should still parse it as a valid document.
  std::ostringstream out;
  out << "%PDF-1.7\n";

  auto emit_obj = [&](int objnum, const std::string &body, std::vector<long> &offs) {
    offs.resize(std::max<size_t>(offs.size(), static_cast<size_t>(objnum + 1)));
    offs[objnum] = static_cast<long>(out.tellp());
    out << objnum << " 0 obj\n" << body << "\nendobj\n";
  };

  std::vector<long> offsets(8, 0);

  // 1: Catalog
  emit_obj(1,
           "<< /Type /Catalog /Pages 2 0 R /StructTreeRoot 5 0 R >>",
           offsets);

  // 2: Pages
  emit_obj(2,
           "<< /Type /Pages /Kids [3 0 R] /Count 1 >>",
           offsets);

  // 4: Contents stream
  {
    std::string stream_data = "q\nQ\n";
    std::ostringstream body;
    body << "<< /Length " << stream_data.size() << " >>\nstream\n"
         << stream_data << "endstream";
    emit_obj(4, body.str(), offsets);
  }

  // 3: Page
  emit_obj(3,
           "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] "
           "/Contents 4 0 R /Resources << >> >>",
           offsets);

  // 5: StructTreeRoot
  emit_obj(5,
           "<< /Type /StructTreeRoot /K 6 0 R >>",
           offsets);

  // 6: StructElem
  {
    std::ostringstream body;
    body << "<< /Type /StructElem /S /" << struct_type_name << " /Pg 3 0 R";
    if (include_bbox) {
      body << " /A << /O /Layout /BBox [" << x1 << " " << y1 << " " << x2 << " " << y2
           << "] >>";
    }
    // Keep K minimal; empty array is typically acceptable for a leaf node in tests.
    body << " /K [] >>";
    emit_obj(6, body.str(), offsets);
  }

  // xref
  long xref_pos = static_cast<long>(out.tellp());
  out << "xref\n0 7\n";
  out << "0000000000 65535 f \n";
  for (int i = 1; i <= 6; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld", offsets[i]);
    out << buf << " 00000 n \n";
  }

  // trailer
  out << "trailer\n<< /Size 7 /Root 1 0 R >>\n";
  out << "startxref\n" << xref_pos << "\n%%EOF\n";
  return out.str();
}

static void WriteStringToFileOrFail(const std::string &path, const std::string &data) {
  FILE *f = std::fopen(path.c_str(), "wb");
  ASSERT_NE(f, nullptr);
  size_t wrote = std::fwrite(data.data(), 1, data.size(), f);
  std::fclose(f);
  ASSERT_EQ(wrote, data.size());
}

static PopplerDocument *LoadDocFromPathOrFail(const std::string &path) {
  GError *error = nullptr;

  gchar *uri = g_filename_to_uri(path.c_str(), nullptr, &error);
  EXPECT_EQ(error, nullptr);
  EXPECT_NE(uri, nullptr);

  PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
  g_free(uri);

  EXPECT_EQ(error, nullptr);
  EXPECT_NE(doc, nullptr);
  if (error) {
    g_error_free(error);
  }
  return doc;
}

static PopplerStructureElement *GetFirstStructureElementOrNull(PopplerDocument *doc) {
  PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
  if (!iter) {
    return nullptr;
  }
  PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
  poppler_structure_element_iter_free(iter);
  return elem;
}

}  // namespace

class PopplerStructureElementGetBoundingBoxTest_2569 : public ::testing::Test {
 protected:
  void TearDown() override {
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
  }

  PopplerDocument *doc_ = nullptr;
};

TEST_F(PopplerStructureElementGetBoundingBoxTest_2569, ReturnsTrueAndFillsRectangleForBlockWithBBox_2569) {
  TempFile tf;
  ASSERT_FALSE(tf.path.empty());

  const double kX1 = 10.0, kY1 = 20.0, kX2 = 30.0, kY2 = 40.0;
  const std::string pdf = BuildPdfWithStructElemAndOptionalBBox("P", /*include_bbox=*/true,
                                                                kX1, kY1, kX2, kY2);
  WriteStringToFileOrFail(tf.path, pdf);

  doc_ = LoadDocFromPathOrFail(tf.path);
  ASSERT_NE(doc_, nullptr);

  PopplerStructureElement *elem = GetFirstStructureElementOrNull(doc_);
  ASSERT_NE(elem, nullptr);

  ASSERT_TRUE(poppler_structure_element_is_block(elem));

  PopplerRectangle rect{};
  EXPECT_TRUE(poppler_structure_element_get_bounding_box(elem, &rect));
  EXPECT_DOUBLE_EQ(rect.x1, kX1);
  EXPECT_DOUBLE_EQ(rect.y1, kY1);
  EXPECT_DOUBLE_EQ(rect.x2, kX2);
  EXPECT_DOUBLE_EQ(rect.y2, kY2);
}

TEST_F(PopplerStructureElementGetBoundingBoxTest_2569, ReturnsFalseWhenBBoxAttributeMissing_2569) {
  TempFile tf;
  ASSERT_FALSE(tf.path.empty());

  const std::string pdf = BuildPdfWithStructElemAndOptionalBBox("P", /*include_bbox=*/false,
                                                                0, 0, 0, 0);
  WriteStringToFileOrFail(tf.path, pdf);

  doc_ = LoadDocFromPathOrFail(tf.path);
  ASSERT_NE(doc_, nullptr);

  PopplerStructureElement *elem = GetFirstStructureElementOrNull(doc_);
  ASSERT_NE(elem, nullptr);

  ASSERT_TRUE(poppler_structure_element_is_block(elem));

  PopplerRectangle rect{};
  EXPECT_FALSE(poppler_structure_element_get_bounding_box(elem, &rect));
}

TEST_F(PopplerStructureElementGetBoundingBoxTest_2569, ReturnsFalseAndLogsCriticalWhenBoundingBoxIsNull_2569) {
  TempFile tf;
  ASSERT_FALSE(tf.path.empty());

  const std::string pdf = BuildPdfWithStructElemAndOptionalBBox("P", /*include_bbox=*/true,
                                                                1, 2, 3, 4);
  WriteStringToFileOrFail(tf.path, pdf);

  doc_ = LoadDocFromPathOrFail(tf.path);
  ASSERT_NE(doc_, nullptr);

  PopplerStructureElement *elem = GetFirstStructureElementOrNull(doc_);
  ASSERT_NE(elem, nullptr);
  ASSERT_TRUE(poppler_structure_element_is_block(elem));

  // g_return_val_if_fail(bounding_box != nullptr, FALSE) should emit a CRITICAL log.
  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*bounding_box*");
  EXPECT_FALSE(poppler_structure_element_get_bounding_box(elem, nullptr));
  g_test_assert_expected_messages();
}

TEST_F(PopplerStructureElementGetBoundingBoxTest_2569, ReturnsFalseAndLogsCriticalWhenElementIsNotBlock_2569) {
  TempFile tf;
  ASSERT_FALSE(tf.path.empty());

  // /Span should be treated as inline (non-block) by poppler_structure_element_is_block().
  const std::string pdf = BuildPdfWithStructElemAndOptionalBBox("Span", /*include_bbox=*/true,
                                                                10, 20, 30, 40);
  WriteStringToFileOrFail(tf.path, pdf);

  doc_ = LoadDocFromPathOrFail(tf.path);
  ASSERT_NE(doc_, nullptr);

  PopplerStructureElement *elem = GetFirstStructureElementOrNull(doc_);
  ASSERT_NE(elem, nullptr);

  ASSERT_FALSE(poppler_structure_element_is_block(elem));

  PopplerRectangle rect{};
  // g_return_val_if_fail(poppler_structure_element_is_block(...), FALSE) should emit CRITICAL.
  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*is_block*");
  EXPECT_FALSE(poppler_structure_element_get_bounding_box(elem, &rect));
  g_test_assert_expected_messages();
}

TEST_F(PopplerStructureElementGetBoundingBoxTest_2569, HandlesZeroSizedBBox_2569) {
  TempFile tf;
  ASSERT_FALSE(tf.path.empty());

  const std::string pdf = BuildPdfWithStructElemAndOptionalBBox("P", /*include_bbox=*/true,
                                                                0.0, 0.0, 0.0, 0.0);
  WriteStringToFileOrFail(tf.path, pdf);

  doc_ = LoadDocFromPathOrFail(tf.path);
  ASSERT_NE(doc_, nullptr);

  PopplerStructureElement *elem = GetFirstStructureElementOrNull(doc_);
  ASSERT_NE(elem, nullptr);
  ASSERT_TRUE(poppler_structure_element_is_block(elem));

  PopplerRectangle rect{};
  EXPECT_TRUE(poppler_structure_element_get_bounding_box(elem, &rect));
  EXPECT_DOUBLE_EQ(rect.x1, 0.0);
  EXPECT_DOUBLE_EQ(rect.y1, 0.0);
  EXPECT_DOUBLE_EQ(rect.x2, 0.0);
  EXPECT_DOUBLE_EQ(rect.y2, 0.0);
}