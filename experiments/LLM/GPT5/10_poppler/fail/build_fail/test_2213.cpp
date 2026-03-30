// File: poppler-index-iter-new-test_2213.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace {

std::string WritePdfToTempFile(const std::string &pdf_bytes) {
  // Use GLib temp file helpers for portability.
  gchar *tmp_name = nullptr;
  gint fd = g_file_open_tmp("poppler-index-iter-2213-XXXXXX.pdf", &tmp_name, nullptr);
  if (fd < 0 || tmp_name == nullptr) {
    if (tmp_name)
      g_free(tmp_name);
    return {};
  }

  // Write bytes
  FILE *f = fdopen(fd, "wb");
  if (!f) {
    close(fd);
    g_free(tmp_name);
    return {};
  }

  size_t written = fwrite(pdf_bytes.data(), 1, pdf_bytes.size(), f);
  fflush(f);
  fclose(f); // closes fd

  std::string path = tmp_name;
  g_free(tmp_name);

  if (written != pdf_bytes.size()) {
    // best-effort cleanup
    g_remove(path.c_str());
    return {};
  }
  return path;
}

static std::string BuildPdf_NoOutline() {
  // Minimal 1-page PDF with no /Outlines entry in the Catalog.
  std::vector<std::pair<int, std::string>> objs;
  objs.emplace_back(1, "<< /Type /Catalog /Pages 2 0 R >>");
  objs.emplace_back(2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>");
  objs.emplace_back(3,
                    "<< /Type /Page /Parent 2 0 R "
                    "/MediaBox [0 0 612 792] /Contents 4 0 R >>");
  // Simple content stream
  const char *stream = "BT /F1 12 Tf 72 720 Td (Hello) Tj ET\n";
  {
    std::ostringstream ss;
    ss << "<< /Length " << strlen(stream) << " >>\nstream\n" << stream << "endstream";
    objs.emplace_back(4, ss.str());
  }

  // Assemble with xref
  std::ostringstream out;
  out << "%PDF-1.4\n";
  std::vector<long> offsets;
  offsets.resize(5, 0); // 0..4
  for (auto &p : objs) {
    int num = p.first;
    offsets[num] = static_cast<long>(out.tellp());
    out << num << " 0 obj\n" << p.second << "\nendobj\n";
  }

  long xref_pos = static_cast<long>(out.tellp());
  out << "xref\n0 5\n";
  out << "0000000000 65535 f \n";
  for (int i = 1; i <= 4; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    out << buf;
  }
  out << "trailer\n<< /Size 5 /Root 1 0 R >>\n";
  out << "startxref\n" << xref_pos << "\n%%EOF\n";
  return out.str();
}

static std::string BuildPdf_TwoTopLevelOutlines() {
  // 2-page PDF with two top-level outline items: "First" and "Second".
  std::vector<std::pair<int, std::string>> objs;

  objs.emplace_back(1, "<< /Type /Catalog /Pages 2 0 R /Outlines 5 0 R >>");
  objs.emplace_back(2, "<< /Type /Pages /Kids [3 0 R 4 0 R] /Count 2 >>");
  objs.emplace_back(3,
                    "<< /Type /Page /Parent 2 0 R "
                    "/MediaBox [0 0 612 792] /Contents 6 0 R >>");
  objs.emplace_back(4,
                    "<< /Type /Page /Parent 2 0 R "
                    "/MediaBox [0 0 612 792] /Contents 7 0 R >>");

  // Outline root
  objs.emplace_back(5,
                    "<< /Type /Outlines "
                    "/First 8 0 R /Last 9 0 R /Count 2 >>");

  // Content streams
  const char *stream1 = "BT /F1 12 Tf 72 720 Td (Page 1) Tj ET\n";
  const char *stream2 = "BT /F1 12 Tf 72 720 Td (Page 2) Tj ET\n";
  {
    std::ostringstream ss;
    ss << "<< /Length " << strlen(stream1) << " >>\nstream\n" << stream1 << "endstream";
    objs.emplace_back(6, ss.str());
  }
  {
    std::ostringstream ss;
    ss << "<< /Length " << strlen(stream2) << " >>\nstream\n" << stream2 << "endstream";
    objs.emplace_back(7, ss.str());
  }

  // Outline items
  objs.emplace_back(8,
                    "<< /Title (First) /Parent 5 0 R "
                    "/Dest [3 0 R /Fit] /Next 9 0 R >>");
  objs.emplace_back(9,
                    "<< /Title (Second) /Parent 5 0 R "
                    "/Dest [4 0 R /Fit] /Prev 8 0 R >>");

  std::ostringstream out;
  out << "%PDF-1.4\n";
  std::vector<long> offsets;
  offsets.resize(10, 0); // 0..9
  for (auto &p : objs) {
    int num = p.first;
    offsets[num] = static_cast<long>(out.tellp());
    out << num << " 0 obj\n" << p.second << "\nendobj\n";
  }

  long xref_pos = static_cast<long>(out.tellp());
  out << "xref\n0 10\n";
  out << "0000000000 65535 f \n";
  for (int i = 1; i <= 9; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    out << buf;
  }
  out << "trailer\n<< /Size 10 /Root 1 0 R >>\n";
  out << "startxref\n" << xref_pos << "\n%%EOF\n";
  return out.str();
}

static std::string BuildPdf_NestedOutlineOneChild() {
  // 1-page PDF with one top-level outline "Chapter" having one child "Section".
  std::vector<std::pair<int, std::string>> objs;

  objs.emplace_back(1, "<< /Type /Catalog /Pages 2 0 R /Outlines 5 0 R >>");
  objs.emplace_back(2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>");
  objs.emplace_back(3,
                    "<< /Type /Page /Parent 2 0 R "
                    "/MediaBox [0 0 612 792] /Contents 4 0 R >>");

  const char *stream = "BT /F1 12 Tf 72 720 Td (Page 1) Tj ET\n";
  {
    std::ostringstream ss;
    ss << "<< /Length " << strlen(stream) << " >>\nstream\n" << stream << "endstream";
    objs.emplace_back(4, ss.str());
  }

  // Outlines root -> first/last is 8 (Chapter)
  objs.emplace_back(5,
                    "<< /Type /Outlines "
                    "/First 8 0 R /Last 8 0 R /Count 1 >>");

  // Chapter outline item has one child (Section)
  objs.emplace_back(8,
                    "<< /Title (Chapter) /Parent 5 0 R "
                    "/Dest [3 0 R /Fit] "
                    "/First 9 0 R /Last 9 0 R /Count 1 >>");

  // Child item
  objs.emplace_back(9,
                    "<< /Title (Section) /Parent 8 0 R "
                    "/Dest [3 0 R /Fit] >>");

  std::ostringstream out;
  out << "%PDF-1.4\n";
  std::vector<long> offsets;
  offsets.resize(10, 0); // 0..9
  for (auto &p : objs) {
    int num = p.first;
    offsets[num] = static_cast<long>(out.tellp());
    out << num << " 0 obj\n" << p.second << "\nendobj\n";
  }

  long xref_pos = static_cast<long>(out.tellp());
  out << "xref\n0 10\n";
  out << "0000000000 65535 f \n";
  for (int i = 1; i <= 9; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    out << buf;
  }
  out << "trailer\n<< /Size 10 /Root 1 0 R >>\n";
  out << "startxref\n" << xref_pos << "\n%%EOF\n";
  return out.str();
}

static PopplerDocument *OpenPopplerDocumentFromPath(const std::string &path) {
  GError *error = nullptr;

  gchar *uri = g_filename_to_uri(path.c_str(), /*hostname=*/nullptr, &error);
  if (!uri) {
    if (error)
      g_error_free(error);
    return nullptr;
  }

  PopplerDocument *doc = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
  g_free(uri);

  if (!doc) {
    if (error)
      g_error_free(error);
    return nullptr;
  }
  if (error)
    g_error_free(error);
  return doc;
}

class PopplerIndexIterNewTest_2213 : public ::testing::Test {
 protected:
  void TearDown() override {
    for (const auto &p : temp_paths_) {
      g_remove(p.c_str());
    }
    temp_paths_.clear();
  }

  std::string MakeTempPdf(const std::string &bytes) {
    std::string path = WritePdfToTempFile(bytes);
    if (!path.empty())
      temp_paths_.push_back(path);
    return path;
  }

 private:
    std::vector<std::string> temp_paths_;
};

} // namespace

TEST_F(PopplerIndexIterNewTest_2213, NoOutlineReturnsNull_2213) {
  const std::string pdf = BuildPdf_NoOutline();
  const std::string path = MakeTempPdf(pdf);
  ASSERT_FALSE(path.empty());

  PopplerDocument *doc = OpenPopplerDocumentFromPath(path);
  ASSERT_NE(doc, nullptr);

  PopplerIndexIter *iter = poppler_index_iter_new(doc);
  EXPECT_EQ(iter, nullptr) << "Expected nullptr when document has no outline.";

  g_object_unref(doc);
}

TEST_F(PopplerIndexIterNewTest_2213, TwoTopLevelOutlinesIteratesTitles_2213) {
  const std::string pdf = BuildPdf_TwoTopLevelOutlines();
  const std::string path = MakeTempPdf(pdf);
  ASSERT_FALSE(path.empty());

  PopplerDocument *doc = OpenPopplerDocumentFromPath(path);
  ASSERT_NE(doc, nullptr);

  PopplerIndexIter *iter = poppler_index_iter_new(doc);
  ASSERT_NE(iter, nullptr) << "Expected non-null iterator when outlines exist.";

  // Verify observable behavior via the public iterator API.
  gchar *title1 = poppler_index_iter_get_title(iter);
  ASSERT_NE(title1, nullptr);
  EXPECT_STREQ(title1, "First");
  g_free(title1);

  // Advance to next.
  EXPECT_TRUE(poppler_index_iter_next(iter));

  gchar *title2 = poppler_index_iter_get_title(iter);
  ASSERT_NE(title2, nullptr);
  EXPECT_STREQ(title2, "Second");
  g_free(title2);

  // Boundary: next past the last item should return false.
  EXPECT_FALSE(poppler_index_iter_next(iter));

  poppler_index_iter_free(iter);
  g_object_unref(doc);
}

TEST_F(PopplerIndexIterNewTest_2213, NestedOutlineChildIteratorProvidesChildTitle_2213) {
  const std::string pdf = BuildPdf_NestedOutlineOneChild();
  const std::string path = MakeTempPdf(pdf);
  ASSERT_FALSE(path.empty());

  PopplerDocument *doc = OpenPopplerDocumentFromPath(path);
  ASSERT_NE(doc, nullptr);

  PopplerIndexIter *iter = poppler_index_iter_new(doc);
  ASSERT_NE(iter, nullptr);

  gchar *parent_title = poppler_index_iter_get_title(iter);
  ASSERT_NE(parent_title, nullptr);
  EXPECT_STREQ(parent_title, "Chapter");
  g_free(parent_title);

  // Child iterator should exist and expose its own title.
  PopplerIndexIter *child = poppler_index_iter_get_child(iter);
  ASSERT_NE(child, nullptr);

  gchar *child_title = poppler_index_iter_get_title(child);
  ASSERT_NE(child_title, nullptr);
  EXPECT_STREQ(child_title, "Section");
  g_free(child_title);

  // Boundary: child has only one item; next should be false.
  EXPECT_FALSE(poppler_index_iter_next(child));

  poppler_index_iter_free(child);
  poppler_index_iter_free(iter);
  g_object_unref(doc);
}