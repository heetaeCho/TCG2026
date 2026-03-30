// poppler_structure_element_get_page_test_2523.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <poppler.h>
#include <poppler-structure-element.h>

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

// Helper: write a minimal (tagged) PDF with one page and a simple StructTreeRoot.
// If include_pg_ref is true, the StructElem contains "/Pg 3 0 R" so Poppler can map it to page 0.
// If include_pg_ref is false, the StructElem has no /Pg entry, so get_page should return -1.
static bool WriteMinimalTaggedPdf_2523(const std::string &path, bool include_pg_ref) {
  // Objects:
  // 1 0: Catalog with /Pages 2 0 R, /StructTreeRoot 5 0 R, /MarkInfo << /Marked true >>
  // 2 0: Pages
  // 3 0: Page
  // 4 0: Contents (empty)
  // 5 0: StructTreeRoot with /K 6 0 R
  // 6 0: StructElem with /Pg (optional), /K [] (empty kids)
  const std::string contents_stream = "BT\nET\n";
  const std::string obj1 =
      "1 0 obj\n"
      "<< /Type /Catalog\n"
      "   /Pages 2 0 R\n"
      "   /StructTreeRoot 5 0 R\n"
      "   /MarkInfo << /Marked true >>\n"
      ">>\n"
      "endobj\n";
  const std::string obj2 =
      "2 0 obj\n"
      "<< /Type /Pages\n"
      "   /Kids [3 0 R]\n"
      "   /Count 1\n"
      ">>\n"
      "endobj\n";
  const std::string obj3 =
      "3 0 obj\n"
      "<< /Type /Page\n"
      "   /Parent 2 0 R\n"
      "   /MediaBox [0 0 612 792]\n"
      "   /Resources << >>\n"
      "   /Contents 4 0 R\n"
      ">>\n"
      "endobj\n";

  const std::string obj4 =
      "4 0 obj\n"
      "<< /Length " +
      std::to_string(contents_stream.size()) +
      " >>\n"
      "stream\n" +
      contents_stream +
      "endstream\n"
      "endobj\n";

  const std::string obj5 =
      "5 0 obj\n"
      "<< /Type /StructTreeRoot\n"
      "   /K 6 0 R\n"
      ">>\n"
      "endobj\n";

  std::string obj6 =
      "6 0 obj\n"
      "<< /Type /StructElem\n"
      "   /S /P\n"
      "   /P 5 0 R\n";
  if (include_pg_ref) {
    obj6 += "   /Pg 3 0 R\n";
  }
  obj6 +=
      "   /K []\n"
      ">>\n"
      "endobj\n";

  const std::string header = "%PDF-1.7\n%\xE2\xE3\xCF\xD3\n";

  std::vector<std::string> objects = {obj1, obj2, obj3, obj4, obj5, obj6};

  // Build file content while tracking xref offsets.
  std::string pdf;
  pdf.reserve(4096);
  pdf += header;

  std::vector<long> offsets;
  offsets.resize(objects.size() + 1);
  offsets[0] = 0;  // xref entry for object 0 (free)

  for (size_t i = 0; i < objects.size(); ++i) {
    offsets[i + 1] = static_cast<long>(pdf.size());
    pdf += objects[i];
  }

  const long xref_pos = static_cast<long>(pdf.size());

  // xref
  pdf += "xref\n";
  pdf += "0 7\n";
  pdf += "0000000000 65535 f \n";
  for (int i = 1; i <= 6; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    pdf += buf;
  }

  // trailer
  pdf += "trailer\n";
  pdf += "<< /Size 7\n";
  pdf += "   /Root 1 0 R\n";
  pdf += ">>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_pos);
  pdf += "\n%%EOF\n";

  GError *err = nullptr;
  if (!g_file_set_contents(path.c_str(), pdf.data(), static_cast<gssize>(pdf.size()), &err)) {
    if (err) {
      g_error_free(err);
    }
    return false;
  }
  return true;
}

static std::string MakeTempPdfPath_2523() {
  // Use glib temp file creation for portability.
  gchar *tmp_name = nullptr;
  gint fd = g_file_open_tmp("poppler-structure-get-page-XXXXXX.pdf", &tmp_name, nullptr);
  if (fd >= 0) {
    close(fd);
  }
  std::string path = tmp_name ? tmp_name : "";
  g_free(tmp_name);
  return path;
}

static PopplerDocument *OpenPopplerDocumentFromPath_2523(const std::string &path) {
  GError *err = nullptr;
  gchar *uri = g_filename_to_uri(path.c_str(), nullptr, &err);
  if (!uri) {
    if (err) g_error_free(err);
    return nullptr;
  }

  PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &err);
  g_free(uri);
  if (!doc) {
    if (err) g_error_free(err);
    return nullptr;
  }
  return doc;
}

class PopplerStructureElementGetPageTest_2523 : public ::testing::Test {
protected:
  void TearDown() override {
    // Cleanup temp files if created.
    if (!temp_paths_.empty()) {
      for (const auto &p : temp_paths_) {
        if (!p.empty()) {
          g_unlink(p.c_str());
        }
      }
    }
  }

  std::string CreatePdfFile_2523(bool include_pg_ref) {
    std::string path = MakeTempPdfPath_2523();
    if (path.empty()) return path;
    if (!WriteMinimalTaggedPdf_2523(path, include_pg_ref)) {
      g_unlink(path.c_str());
      return "";
    }
    temp_paths_.push_back(path);
    return path;
  }

private:
  std::vector<std::string> temp_paths_;
};

TEST_F(PopplerStructureElementGetPageTest_2523, NullInputReturnsMinusOne_2523) {
  // Exceptional/error case: NULL input should return -1 (and may log a critical warning).
  EXPECT_EQ(poppler_structure_element_get_page(nullptr), -1);
}

TEST_F(PopplerStructureElementGetPageTest_2523, FreshlyConstructedElementWithoutBackingElemReturnsMinusOne_2523) {
  // Boundary/error case: valid GObject instance but without an attached internal StructElement.
  // The implementation checks poppler_structure_element->elem != nullptr and returns -1.
  PopplerStructureElement *elem =
      POPPLER_STRUCTURE_ELEMENT(g_object_new(POPPLER_TYPE_STRUCTURE_ELEMENT, nullptr));
  ASSERT_NE(elem, nullptr);

  EXPECT_EQ(poppler_structure_element_get_page(elem), -1);

  g_object_unref(elem);
}

TEST_F(PopplerStructureElementGetPageTest_2523, TaggedPdfWithPageRefMapsToZeroBasedPageIndex_2523) {
  // Normal operation: a struct element that references the only page should map to index 0.
  const std::string path = CreatePdfFile_2523(true);
  ASSERT_FALSE(path.empty());

  PopplerDocument *doc = OpenPopplerDocumentFromPath_2523(path);
  ASSERT_NE(doc, nullptr);

  PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
  ASSERT_NE(iter, nullptr);

  PopplerStructureElement *element = poppler_structure_element_iter_get_element(iter);
  ASSERT_NE(element, nullptr);

  const gint page_index = poppler_structure_element_get_page(element);
  EXPECT_EQ(page_index, 0);

  poppler_structure_element_iter_free(iter);
  g_object_unref(doc);
}

TEST_F(PopplerStructureElementGetPageTest_2523, TaggedPdfWithoutPageRefReturnsMinusOne_2523) {
  // Boundary/error case: StructElem exists but has no /Pg entry, so page mapping should fail.
  const std::string path = CreatePdfFile_2523(false);
  ASSERT_FALSE(path.empty());

  PopplerDocument *doc = OpenPopplerDocumentFromPath_2523(path);
  ASSERT_NE(doc, nullptr);

  PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
  ASSERT_NE(iter, nullptr);

  PopplerStructureElement *element = poppler_structure_element_iter_get_element(iter);
  ASSERT_NE(element, nullptr);

  EXPECT_EQ(poppler_structure_element_get_page(element), -1);

  poppler_structure_element_iter_free(iter);
  g_object_unref(doc);
}