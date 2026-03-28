// File: poppler-page-get-annot-mapping-test_2455.cc
//
// Unit tests for poppler_page_get_annot_mapping() from:
//   ./TestProjects/poppler/glib/poppler-page.cc
//
// These tests treat Poppler as a black box and validate only observable behavior
// through the public API and returned structures.
//
// Build assumptions: poppler-glib + glib + gtest are available.

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

namespace {

static std::string Pad10(gsize v) {
  char buf[32];
  std::snprintf(buf, sizeof(buf), "%010zu", static_cast<size_t>(v));
  return std::string(buf);
}

// Creates a minimal PDF with an xref table from a list of object bodies.
// Each object body should be the inside of "N 0 obj ... endobj" (i.e. not
// including the "N 0 obj" / "endobj" wrapper).
static std::string BuildPdfFromObjectBodies(const std::vector<std::string>& bodies) {
  // Objects are numbered 1..N
  std::string pdf;
  pdf += "%PDF-1.4\n";
  pdf += "%\xE2\xE3\xCF\xD3\n";  // binary comment

  std::vector<gsize> offsets;
  offsets.reserve(bodies.size() + 1);
  offsets.push_back(0);  // xref entry 0 (free object)

  for (size_t i = 0; i < bodies.size(); ++i) {
    offsets.push_back(pdf.size());
    pdf += std::to_string(i + 1);
    pdf += " 0 obj\n";
    pdf += bodies[i];
    if (!pdf.empty() && pdf.back() != '\n') pdf += "\n";
    pdf += "endobj\n";
  }

  const gsize xref_pos = pdf.size();
  pdf += "xref\n";
  pdf += "0 " + std::to_string(bodies.size() + 1) + "\n";
  // free object 0
  pdf += "0000000000 65535 f \n";
  for (size_t i = 1; i < offsets.size(); ++i) {
    pdf += Pad10(offsets[i]) + " 00000 n \n";
  }

  pdf += "trailer\n";
  pdf += "<< /Size " + std::to_string(bodies.size() + 1) + " /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(static_cast<size_t>(xref_pos)) + "\n";
  pdf += "%%EOF\n";

  return pdf;
}

static std::pair<std::string, std::string> WriteTempPdf(const std::string& pdf_bytes) {
  gchar* tmpl = g_strdup("/tmp/poppler_glib_annot_mapping_XXXXXX.pdf");
  int fd = g_mkstemp(tmpl);
  EXPECT_GE(fd, 0);

  gssize to_write = static_cast<gssize>(pdf_bytes.size());
  const char* p = pdf_bytes.data();
  while (to_write > 0) {
    gssize n = write(fd, p, static_cast<size_t>(to_write));
    EXPECT_GT(n, 0);
    to_write -= n;
    p += n;
  }
  close(fd);

  gchar* uri = g_filename_to_uri(tmpl, /*hostname=*/nullptr, /*error=*/nullptr);
  EXPECT_NE(uri, nullptr);

  std::string path(tmpl);
  std::string file_uri(uri);

  g_free(uri);
  g_free(tmpl);
  return {path, file_uri};
}

static PopplerDocument* OpenDocumentOrFail(const std::string& file_uri) {
  GError* error = nullptr;
  PopplerDocument* doc = poppler_document_new_from_file(file_uri.c_str(), /*password=*/nullptr, &error);
  if (!doc) {
    std::string msg = "Failed to open PDF via poppler_document_new_from_file";
    if (error && error->message) {
      msg += ": ";
      msg += error->message;
    }
    if (error) g_error_free(error);
    ADD_FAILURE() << msg;
    return nullptr;
  }
  if (error) g_error_free(error);
  return doc;
}

static PopplerPage* GetFirstPageOrFail(PopplerDocument* doc) {
  EXPECT_NE(doc, nullptr);
  if (!doc) return nullptr;
  PopplerPage* page = poppler_document_get_page(doc, 0);
  EXPECT_NE(page, nullptr);
  return page;
}

static void RemoveTempFile(const std::string& path) {
  if (!path.empty()) {
    std::remove(path.c_str());
  }
}

static void AssertAreaWithinPage(PopplerPage* page, const PopplerRectangle& area) {
  double w = 0.0, h = 0.0;
  poppler_page_get_size(page, &w, &h);

  // Only check basic sanity / bounds (observable, not re-deriving internal math).
  EXPECT_LE(area.x1, area.x2);
  EXPECT_LE(area.y1, area.y2);

  EXPECT_GE(area.x1, 0.0);
  EXPECT_GE(area.y1, 0.0);

  EXPECT_LE(area.x2, w + 1e-6);
  EXPECT_LE(area.y2, h + 1e-6);
}

class PopplerPageGetAnnotMappingTest_2455 : public ::testing::Test {
 protected:
  void TearDown() override {
    if (page_) {
      g_object_unref(page_);
      page_ = nullptr;
    }
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
    RemoveTempFile(tmp_path_);
    tmp_path_.clear();
  }

  void LoadPdf(const std::string& pdf_bytes) {
    auto [path, uri] = WriteTempPdf(pdf_bytes);
    tmp_path_ = path;

    doc_ = OpenDocumentOrFail(uri);
    ASSERT_NE(doc_, nullptr);

    page_ = GetFirstPageOrFail(doc_);
    ASSERT_NE(page_, nullptr);
  }

  PopplerDocument* doc_ = nullptr;
  PopplerPage* page_ = nullptr;
  std::string tmp_path_;
};

TEST_F(PopplerPageGetAnnotMappingTest_2455, NullPageReturnsNull_2455) {
  // Observable behavior: g_return_val_if_fail(POPPLER_IS_PAGE(page), NULL)
  GList* list = poppler_page_get_annot_mapping(nullptr);
  EXPECT_EQ(list, nullptr);
}

TEST_F(PopplerPageGetAnnotMappingTest_2455, NoAnnotsReturnsNull_2455) {
  // PDF with a single empty page, no /Annots entry.
  // Objects:
  // 1: Catalog
  // 2: Pages
  // 3: Page (no /Annots)
  // 4: Empty contents stream
  const std::vector<std::string> bodies = {
      "<< /Type /Catalog /Pages 2 0 R >>",
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>",
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Resources << >> /Contents 4 0 R >>",
      "<< /Length 0 >>\nstream\nendstream",
  };

  LoadPdf(BuildPdfFromObjectBodies(bodies));

  GList* list = poppler_page_get_annot_mapping(page_);
  EXPECT_EQ(list, nullptr);

  // Freeing nullptr should be safe; but only call if API exists at link time.
  // (If your build exports poppler_page_free_annot_mapping, keeping this is fine.)
  poppler_page_free_annot_mapping(list);
}

TEST_F(PopplerPageGetAnnotMappingTest_2455, EmptyAnnotsArrayReturnsNull_2455) {
  // /Annots [] present but empty -> mapping list should still be empty (NULL).
  const std::vector<std::string> bodies = {
      "<< /Type /Catalog /Pages 2 0 R >>",
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>",
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Resources << >> /Contents 4 0 R "
      "   /Annots [] >>",
      "<< /Length 0 >>\nstream\nendstream",
  };

  LoadPdf(BuildPdfFromObjectBodies(bodies));

  GList* list = poppler_page_get_annot_mapping(page_);
  EXPECT_EQ(list, nullptr);
  poppler_page_free_annot_mapping(list);
}

TEST_F(PopplerPageGetAnnotMappingTest_2455, TwoAnnotsReturnsTwoMappingsWithOrderAndTypes_2455) {
  // Two annotations with distinct /Contents so we can verify stable, observable order.
  // Use common, simple subtypes: /Text and /FreeText.
  //
  // Note: /DA is commonly required by FreeText for appearance; Poppler should still parse it.
  const std::vector<std::string> bodies = {
      // 1: Catalog
      "<< /Type /Catalog /Pages 2 0 R >>",
      // 2: Pages
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>",
      // 3: Page with Annots array in a defined order: [5,6]
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Resources << >> /Contents 4 0 R "
      "   /Annots [5 0 R 6 0 R] >>",
      // 4: Empty contents
      "<< /Length 0 >>\nstream\nendstream",
      // 5: Text annot
      "<< /Type /Annot /Subtype /Text /Rect [10 10 30 30] /Contents (First) >>",
      // 6: FreeText annot
      "<< /Type /Annot /Subtype /FreeText /Rect [50 50 150 80] /Contents (Second) "
      "   /DA (/Helv 12 Tf 0 g) >>",
  };

  LoadPdf(BuildPdfFromObjectBodies(bodies));

  GList* list = poppler_page_get_annot_mapping(page_);
  ASSERT_NE(list, nullptr);
  EXPECT_EQ(g_list_length(list), 2u);

  // First mapping in list should correspond to first annot in PDF /Annots array (observable order).
  auto* m0 = static_cast<PopplerAnnotMapping*>(list->data);
  ASSERT_NE(m0, nullptr);
  ASSERT_NE(m0->annot, nullptr);

  PopplerAnnotType t0 = poppler_annot_get_annot_type(m0->annot);
  EXPECT_EQ(t0, POPPLER_ANNOT_TEXT);

  gchar* c0 = poppler_annot_get_contents(m0->annot);
  ASSERT_NE(c0, nullptr);
  EXPECT_STREQ(c0, "First");
  g_free(c0);

  AssertAreaWithinPage(page_, m0->area);

  // Second mapping
  ASSERT_NE(list->next, nullptr);
  auto* m1 = static_cast<PopplerAnnotMapping*>(list->next->data);
  ASSERT_NE(m1, nullptr);
  ASSERT_NE(m1->annot, nullptr);

  PopplerAnnotType t1 = poppler_annot_get_annot_type(m1->annot);
  EXPECT_EQ(t1, POPPLER_ANNOT_FREE_TEXT);

  gchar* c1 = poppler_annot_get_contents(m1->annot);
  ASSERT_NE(c1, nullptr);
  EXPECT_STREQ(c1, "Second");
  g_free(c1);

  AssertAreaWithinPage(page_, m1->area);

  poppler_page_free_annot_mapping(list);
}

TEST_F(PopplerPageGetAnnotMappingTest_2455, RotatedPageReturnsMappingsWithinBounds_2455) {
  // Page rotated 90 degrees; we only assert basic sanity and within-page bounds.
  // This exercises the non-zero rotation path without re-deriving mapping math.
  const std::vector<std::string> bodies = {
      "<< /Type /Catalog /Pages 2 0 R >>",
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>",
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Rotate 90 "
      "   /Resources << >> /Contents 4 0 R /Annots [5 0 R] >>",
      "<< /Length 0 >>\nstream\nendstream",
      "<< /Type /Annot /Subtype /Text /Rect [20 40 60 70] /Contents (R90) >>",
  };

  LoadPdf(BuildPdfFromObjectBodies(bodies));

  GList* list = poppler_page_get_annot_mapping(page_);
  ASSERT_NE(list, nullptr);
  EXPECT_EQ(g_list_length(list), 1u);

  auto* mapping = static_cast<PopplerAnnotMapping*>(list->data);
  ASSERT_NE(mapping, nullptr);
  ASSERT_NE(mapping->annot, nullptr);

  gchar* contents = poppler_annot_get_contents(mapping->annot);
  ASSERT_NE(contents, nullptr);
  EXPECT_STREQ(contents, "R90");
  g_free(contents);

  AssertAreaWithinPage(page_, mapping->area);

  poppler_page_free_annot_mapping(list);
}

}  // namespace