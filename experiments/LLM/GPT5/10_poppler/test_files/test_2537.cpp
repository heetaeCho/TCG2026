// poppler-structure-element-iter-new-test-2537.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

extern "C" {

// Forward declarations (keep tests independent of private/internal state).
typedef struct _PopplerDocument PopplerDocument;
typedef struct _PopplerStructureElementIter PopplerStructureElementIter;

// Function under test (as given).
PopplerStructureElementIter *poppler_structure_element_iter_new(PopplerDocument *poppler_document);

// Public Poppler GLib API we rely on to create real documents.
PopplerDocument *poppler_document_new_from_file(const char *uri,
                                               const char *password,
                                               GError **error);

} // extern "C"

namespace {

class TempPdfFile {
public:
  explicit TempPdfFile(const std::string &pdf_bytes) {
    GError *err = nullptr;

    // Create a unique temp directory.
    gchar *dir = g_dir_make_tmp("poppler-iter-2537-XXXXXX", &err);
    if (!dir) {
      std::string msg = err ? err->message : "unknown error";
      if (err) g_error_free(err);
      throw std::runtime_error("g_dir_make_tmp failed: " + msg);
    }
    dir_.reset(dir);

    // Write file.
    gchar *path = g_build_filename(dir_.get(), "doc.pdf", nullptr);
    path_.reset(path);

    if (!g_file_set_contents(path_.get(), pdf_bytes.data(),
                             static_cast<gssize>(pdf_bytes.size()), &err)) {
      std::string msg = err ? err->message : "unknown error";
      if (err) g_error_free(err);
      throw std::runtime_error("g_file_set_contents failed: " + msg);
    }

    // Convert to file:// URI.
    gchar *uri = g_filename_to_uri(path_.get(), nullptr, &err);
    if (!uri) {
      std::string msg = err ? err->message : "unknown error";
      if (err) g_error_free(err);
      throw std::runtime_error("g_filename_to_uri failed: " + msg);
    }
    uri_.reset(uri);
  }

  const char *uri() const { return uri_.get(); }

private:
  struct GCharDeleter {
    void operator()(gchar *p) const { g_free(p); }
  };
  std::unique_ptr<gchar, GCharDeleter> dir_{nullptr};
  std::unique_ptr<gchar, GCharDeleter> path_{nullptr};
  std::unique_ptr<gchar, GCharDeleter> uri_{nullptr};
};

static std::string BuildMinimalPdf(bool include_struct_tree_root,
                                   bool root_has_child) {
  // Build a tiny, valid PDF with correct xref offsets.
  // Variants:
  //  - No StructTreeRoot in the catalog
  //  - StructTreeRoot present but /K [] (0 children)
  //  - StructTreeRoot present with one StructElem child
  //
  // The goal is ONLY to influence observable behavior of iter_new via Poppler's
  // parsing (black-box), not to re-implement Poppler internals.

  struct Obj {
    int num;
    std::string body;
  };

  std::vector<Obj> objs;

  // 1) Catalog
  {
    std::ostringstream cat;
    cat << "<< /Type /Catalog /Pages 2 0 R";
    if (include_struct_tree_root) {
      cat << " /StructTreeRoot 5 0 R /MarkInfo << /Marked true >>";
    }
    cat << " >>";
    objs.push_back({1, cat.str()});
  }

  // 2) Pages
  objs.push_back({2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>"});

  // 3) Page
  // Note: keep resources simple; Poppler should parse this fine.
  objs.push_back({3,
                  "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 300 300] "
                  "/Contents 4 0 R "
                  "/Resources << /Font << /F1 << /Type /Font /Subtype /Type1 "
                  "/BaseFont /Helvetica >> >> >> >>"});

  // 4) Contents stream (include some marked-content-ish syntax; should still be
  // a valid stream even if structure tree is absent).
  {
    std::string stream =
        "BT\n"
        "/F1 12 Tf\n"
        "72 200 Td\n"
        "(Hello) Tj\n"
        "ET\n";
    std::ostringstream body;
    body << "<< /Length " << stream.size() << " >>\n"
         << "stream\n"
         << stream
         << "endstream";
    objs.push_back({4, body.str()});
  }

  if (include_struct_tree_root) {
    // 5) StructTreeRoot
    {
      std::ostringstream root;
      root << "<< /Type /StructTreeRoot /K ";
      if (root_has_child) {
        root << "[6 0 R]";
      } else {
        root << "[]";
      }
      root << " >>";
      objs.push_back({5, root.str()});
    }

    if (root_has_child) {
      // 6) StructElem (one top-level element)
      // Keep it minimal; /P points back to StructTreeRoot; /Pg references page.
      objs.push_back({6,
                      "<< /Type /StructElem /S /Document /P 5 0 R "
                      "/Pg 3 0 R "
                      "/K 0 >>"});
    }
  }

  std::ostringstream pdf;
  pdf << "%PDF-1.4\n%âãÏÓ\n";

  std::vector<long> offsets;
  offsets.resize(static_cast<size_t>(objs.back().num) + 1, 0);

  for (const auto &o : objs) {
    offsets[static_cast<size_t>(o.num)] = static_cast<long>(pdf.tellp());
    pdf << o.num << " 0 obj\n" << o.body << "\nendobj\n";
  }

  long xref_off = static_cast<long>(pdf.tellp());
  int max_obj = objs.back().num;

  pdf << "xref\n";
  pdf << "0 " << (max_obj + 1) << "\n";
  pdf << "0000000000 65535 f \n";
  for (int i = 1; i <= max_obj; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[static_cast<size_t>(i)]);
    pdf << buf;
  }

  pdf << "trailer\n";
  pdf << "<< /Size " << (max_obj + 1) << " /Root 1 0 R >>\n";
  pdf << "startxref\n";
  pdf << xref_off << "\n";
  pdf << "%%EOF\n";

  return pdf.str();
}

struct GObjectUnref {
  void operator()(gpointer p) const {
    if (p) g_object_unref(p);
  }
};

static std::unique_ptr<PopplerDocument, GObjectUnref>
LoadPopplerDocumentFromPdfBytes(const std::string &bytes) {
  TempPdfFile tmp(bytes);
  GError *err = nullptr;
  PopplerDocument *doc = poppler_document_new_from_file(tmp.uri(), nullptr, &err);
  if (!doc) {
    std::string msg = err ? err->message : "unknown error";
    if (err) g_error_free(err);
    throw std::runtime_error("poppler_document_new_from_file failed: " + msg);
  }
  if (err) g_error_free(err);
  return std::unique_ptr<PopplerDocument, GObjectUnref>(doc);
}

} // namespace

class PopplerStructureElementIterNewTest_2537 : public ::testing::Test {};

TEST_F(PopplerStructureElementIterNewTest_2537, NullDocumentReturnsNull_2537) {
  // g_return_val_if_fail should emit a critical; expect it so tests are robust
  // under fatal-warnings configurations.
  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");
  PopplerStructureElementIter *iter = poppler_structure_element_iter_new(nullptr);
  g_test_assert_expected_messages();
  EXPECT_EQ(iter, nullptr);
}

TEST_F(PopplerStructureElementIterNewTest_2537, NonDocumentObjectReturnsNull_2537) {
  // Pass a plain GObject* casted to PopplerDocument* to exercise type check.
  GObject *not_a_doc = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_a_doc, nullptr);

  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");
  PopplerStructureElementIter *iter =
      poppler_structure_element_iter_new(reinterpret_cast<PopplerDocument *>(not_a_doc));
  g_test_assert_expected_messages();

  EXPECT_EQ(iter, nullptr);
  g_object_unref(not_a_doc);
}

TEST_F(PopplerStructureElementIterNewTest_2537, DocumentWithoutStructTreeRootReturnsNull_2537) {
  auto doc = LoadPopplerDocumentFromPdfBytes(BuildMinimalPdf(/*include_struct_tree_root=*/false,
                                                             /*root_has_child=*/false));

  PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc.get());
  EXPECT_EQ(iter, nullptr);
}

TEST_F(PopplerStructureElementIterNewTest_2537, StructTreeRootWithZeroChildrenReturnsNull_2537) {
  auto doc = LoadPopplerDocumentFromPdfBytes(BuildMinimalPdf(/*include_struct_tree_root=*/true,
                                                             /*root_has_child=*/false));

  PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc.get());
  EXPECT_EQ(iter, nullptr);
}

TEST_F(PopplerStructureElementIterNewTest_2537, StructTreeRootWithChildReturnsNonNull_2537) {
  auto doc = LoadPopplerDocumentFromPdfBytes(BuildMinimalPdf(/*include_struct_tree_root=*/true,
                                                             /*root_has_child=*/true));

  PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc.get());
  ASSERT_NE(iter, nullptr);

  // We intentionally avoid inspecting internal fields of PopplerStructureElementIter.
  // Also, no public free function was provided in the prompt; avoid guessing cleanup.
}

TEST_F(PopplerStructureElementIterNewTest_2537, MultipleCallsProduceIndependentIters_2537) {
  auto doc = LoadPopplerDocumentFromPdfBytes(BuildMinimalPdf(/*include_struct_tree_root=*/true,
                                                             /*root_has_child=*/true));

  PopplerStructureElementIter *iter1 = poppler_structure_element_iter_new(doc.get());
  PopplerStructureElementIter *iter2 = poppler_structure_element_iter_new(doc.get());

  ASSERT_NE(iter1, nullptr);
  ASSERT_NE(iter2, nullptr);
  EXPECT_NE(iter1, iter2);

  // No further assumptions about internal ownership / lifecycle.
}

// Combine GLib test harness with GoogleTest so g_test_expect_message works.
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  g_test_init(&argc, &argv, nullptr);
  return RUN_ALL_TESTS();
}