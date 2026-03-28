// File: poppler-annot-ink-new-test_2136.cc
//
// Unit tests for:
//   PopplerAnnot *_poppler_annot_ink_new(const std::shared_ptr<Annot> &annot);
//
// Notes:
// - We treat implementation as a black box.
// - Directly constructing a core poppler::Annot (C++ internal) is not practical from the GLib API,
//   so we exercise the behavior through observable GLib surfaces that necessarily create ink annots
//   (page annotation mapping) when an /Ink annotation is present in a PDF.

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace {

static std::string BuildMinimalPdfWithSinglePageAndAnnotObject(const std::string& annotObjectDict) {
  // Build a minimal PDF with:
  // 1 0 obj: Catalog
  // 2 0 obj: Pages
  // 3 0 obj: Page (with /Annots [4 0 R])
  // 4 0 obj: Annot (provided by caller)
  //
  // We compute xref offsets to keep parsers happy.
  struct Obj {
    int num;
    std::string body;
    std::string rendered;
    size_t offset = 0;
  };

  std::vector<Obj> objs;
  objs.push_back({1, "<< /Type /Catalog /Pages 2 0 R >>\n"});
  objs.push_back({2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"});
  objs.push_back({3,
                  "<< /Type /Page /Parent 2 0 R\n"
                  "   /MediaBox [0 0 612 792]\n"
                  "   /Contents 0 0 R\n"
                  "   /Annots [4 0 R]\n"
                  ">>\n"});
  objs.push_back({4, annotObjectDict + "\n"});

  for (auto& o : objs) {
    std::ostringstream os;
    os << o.num << " 0 obj\n" << o.body << "endobj\n";
    o.rendered = os.str();
  }

  std::ostringstream out;
  out << "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n";

  // Record offsets.
  for (auto& o : objs) {
    o.offset = static_cast<size_t>(out.tellp());
    out << o.rendered;
  }

  const size_t xref_offset = static_cast<size_t>(out.tellp());
  out << "xref\n";
  out << "0 " << (objs.size() + 1) << "\n";
  out << "0000000000 65535 f \n";
  for (const auto& o : objs) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010zu", o.offset);
    out << buf << " 00000 n \n";
  }

  out << "trailer\n";
  out << "<< /Size " << (objs.size() + 1) << " /Root 1 0 R >>\n";
  out << "startxref\n" << xref_offset << "\n";
  out << "%%EOF\n";

  return out.str();
}

static std::string WriteTempFile(const std::string& bytes) {
  // Create a temp file path.
  gchar* tmpl = g_strdup("/tmp/poppler_annot_ink_new_XXXXXX.pdf");
  int fd = g_mkstemp(tmpl);
  EXPECT_NE(fd, -1);
  if (fd == -1) {
    std::string empty;
    g_free(tmpl);
    return empty;
  }

  // Close fd; we'll write using std::ofstream for simplicity.
  close(fd);

  std::ofstream ofs(tmpl, std::ios::binary);
  ofs.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
  ofs.close();

  std::string path = tmpl;
  g_free(tmpl);
  return path;
}

static std::string FilePathToUri(const std::string& path) {
  gchar* uri = g_filename_to_uri(path.c_str(), /*hostname=*/nullptr, /*error=*/nullptr);
  if (!uri) return std::string();
  std::string out(uri);
  g_free(uri);
  return out;
}

static PopplerDocument* LoadDocOrFail(const std::string& uri) {
  GError* error = nullptr;
  PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &error);
  if (!doc) {
    if (error) {
      g_error_free(error);
    }
  }
  return doc;
}

class PopplerAnnotInkNewTest_2136 : public ::testing::Test {
 protected:
  void TearDown() override {
    for (const auto& p : temp_paths_) {
      std::remove(p.c_str());
    }
    temp_paths_.clear();
  }

  std::string MakeDocUriWithAnnotDict(const std::string& annotDict) {
    const std::string pdf = BuildMinimalPdfWithSinglePageAndAnnotObject(annotDict);
    const std::string path = WriteTempFile(pdf);
    EXPECT_FALSE(path.empty());
    temp_paths_.push_back(path);
    const std::string uri = FilePathToUri(path);
    EXPECT_FALSE(uri.empty());
    return uri;
  }

 private:
  std::vector<std::string> temp_paths_;
};

TEST_F(PopplerAnnotInkNewTest_2136, InkAnnotationProducesInkGObjectType_2136) {
  // /InkList contains one stroke with 3 points (x1 y1 x2 y2 x3 y3).
  const std::string annot =
      "<< /Type /Annot /Subtype /Ink\n"
      "   /Rect [0 0 200 200]\n"
      "   /InkList [ [10 10 20 20 30 30] ]\n"
      ">>";

  const std::string uri = MakeDocUriWithAnnotDict(annot);
  PopplerDocument* doc = LoadDocOrFail(uri);
  ASSERT_NE(doc, nullptr);

  PopplerPage* page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  GList* mappings = poppler_page_get_annot_mapping(page);
  ASSERT_NE(mappings, nullptr);

  bool found_ink = false;
  for (GList* l = mappings; l; l = l->next) {
    auto* mapping = static_cast<PopplerAnnotMapping*>(l->data);
    ASSERT_NE(mapping, nullptr);
    ASSERT_NE(mapping->annot, nullptr);

    if (POPPLER_IS_ANNOT_INK(mapping->annot)) {
      found_ink = true;

      // Observable behavior: the created annot is an Ink subtype.
      EXPECT_EQ(poppler_annot_get_annot_type(mapping->annot), POPPLER_ANNOT_INK);

      // Smoke-check that ink-specific API is callable and returns a list (may be empty or not).
      PopplerAnnotInk* ink = POPPLER_ANNOT_INK(mapping->annot);
      ASSERT_NE(ink, nullptr);

      GList* ink_list = poppler_annot_ink_get_ink_list(ink);
      // With a non-empty /InkList, we expect an observable non-null list.
      EXPECT_NE(ink_list, nullptr);

      if (ink_list) {
        // At least one stroke present.
        EXPECT_GE(g_list_length(ink_list), 1);
        poppler_annot_ink_free_ink_list(ink_list);
      }
      break;
    }
  }

  EXPECT_TRUE(found_ink);

  poppler_page_free_annot_mapping(mappings);
  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerAnnotInkNewTest_2136, EmptyInkListDoesNotCrashAndProducesInkAnnot_2136) {
  // Boundary condition: /InkList exists but is empty.
  const std::string annot =
      "<< /Type /Annot /Subtype /Ink\n"
      "   /Rect [0 0 200 200]\n"
      "   /InkList [ ]\n"
      ">>";

  const std::string uri = MakeDocUriWithAnnotDict(annot);
  PopplerDocument* doc = LoadDocOrFail(uri);
  ASSERT_NE(doc, nullptr);

  PopplerPage* page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  GList* mappings = poppler_page_get_annot_mapping(page);
  ASSERT_NE(mappings, nullptr);

  bool found_ink = false;
  for (GList* l = mappings; l; l = l->next) {
    auto* mapping = static_cast<PopplerAnnotMapping*>(l->data);
    ASSERT_NE(mapping, nullptr);
    ASSERT_NE(mapping->annot, nullptr);

    if (POPPLER_IS_ANNOT_INK(mapping->annot)) {
      found_ink = true;
      EXPECT_EQ(poppler_annot_get_annot_type(mapping->annot), POPPLER_ANNOT_INK);

      PopplerAnnotInk* ink = POPPLER_ANNOT_INK(mapping->annot);
      ASSERT_NE(ink, nullptr);

      // Observable: API call succeeds; list may be null or empty depending on implementation.
      GList* ink_list = poppler_annot_ink_get_ink_list(ink);
      if (ink_list) {
        EXPECT_EQ(g_list_length(ink_list), 0);
        poppler_annot_ink_free_ink_list(ink_list);
      }
      break;
    }
  }

  EXPECT_TRUE(found_ink);

  poppler_page_free_annot_mapping(mappings);
  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerAnnotInkNewTest_2136, NonInkAnnotationDoesNotAppearAsInkType_2136) {
  // Error/negative case (observable): if the PDF contains a non-ink annotation subtype,
  // the mapping should not expose it as POPPLER_ANNOT_INK / POPPLER_IS_ANNOT_INK.
  const std::string annot =
      "<< /Type /Annot /Subtype /Text\n"
      "   /Rect [0 0 200 200]\n"
      "   /Contents (hello)\n"
      ">>";

  const std::string uri = MakeDocUriWithAnnotDict(annot);
  PopplerDocument* doc = LoadDocOrFail(uri);
  ASSERT_NE(doc, nullptr);

  PopplerPage* page = poppler_document_get_page(doc, 0);
  ASSERT_NE(page, nullptr);

  GList* mappings = poppler_page_get_annot_mapping(page);
  ASSERT_NE(mappings, nullptr);

  bool any_ink = false;
  bool any_annot = false;

  for (GList* l = mappings; l; l = l->next) {
    auto* mapping = static_cast<PopplerAnnotMapping*>(l->data);
    ASSERT_NE(mapping, nullptr);
    ASSERT_NE(mapping->annot, nullptr);
    any_annot = true;

    if (POPPLER_IS_ANNOT_INK(mapping->annot)) {
      any_ink = true;
    }
  }

  EXPECT_TRUE(any_annot);
  EXPECT_FALSE(any_ink);

  poppler_page_free_annot_mapping(mappings);
  g_object_unref(page);
  g_object_unref(doc);
}

}  // namespace