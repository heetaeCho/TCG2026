// File: poppler-document-create-dests-tree-test_2162.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

#include <cstring>
#include <string>
#include <utility>
#include <vector>

namespace {

static std::string BuildPdfWithObjects_2162(const std::vector<std::pair<int, std::string>> &objs_2162) {
  // Build a minimal PDF with a correct xref table. Objects are provided as (objNum, bodyWithoutObjHeader).
  // This is test data construction and does not depend on Poppler internals.
  std::string pdf;
  pdf += "%PDF-1.4\n";
  pdf += "%\xE2\xE3\xCF\xD3\n"; // binary marker

  // Track offsets; PDF xref offsets are from beginning of file.
  // We'll build object numbers up to max for a simple contiguous xref table.
  int max_obj = 0;
  for (const auto &p : objs_2162) {
    if (p.first > max_obj)
      max_obj = p.first;
  }

  std::vector<long> offsets(max_obj + 1, -1);

  for (const auto &p : objs_2162) {
    const int obj_num = p.first;
    const std::string &body = p.second;

    offsets[obj_num] = static_cast<long>(pdf.size());
    pdf += std::to_string(obj_num) + " 0 obj\n";
    pdf += body;
    if (!body.empty() && body.back() != '\n')
      pdf += "\n";
    pdf += "endobj\n";
  }

  const long xref_offset = static_cast<long>(pdf.size());
  pdf += "xref\n";
  pdf += "0 " + std::to_string(max_obj + 1) + "\n";
  // Object 0: free entry
  pdf += "0000000000 65535 f \n";

  for (int i = 1; i <= max_obj; ++i) {
    long off = offsets[i];
    if (off < 0) {
      // Unused object number: mark as free.
      pdf += "0000000000 65535 f \n";
    } else {
      char buf[64];
      std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", off);
      pdf += buf;
    }
  }

  pdf += "trailer\n";
  pdf += "<< /Size " + std::to_string(max_obj + 1) + " /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_offset) + "\n";
  pdf += "%%EOF\n";
  return pdf;
}

static std::string MakePdf_NoNamedDests_2162() {
  // Catalog exists, but has no /Dests and no /Names destinations.
  // Should produce a non-null GTree with zero nodes.
  std::vector<std::pair<int, std::string>> objs;
  objs.emplace_back(1, "<< /Type /Catalog /Pages 2 0 R >>");
  objs.emplace_back(2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>");
  objs.emplace_back(3, "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 100 100] "
                      "/Contents 4 0 R /Resources <<>> >>");
  objs.emplace_back(4, "<< /Length 0 >>\nstream\n\nendstream");
  return BuildPdfWithObjects_2162(objs);
}

static std::string MakePdf_WithNamedDests_DestsAndNameTree_2162() {
  // Includes:
  // - /Dests: /DestA -> page 1, /Same -> page 2
  // - /Names /Dests name tree: (DestB) -> page 1, (Same) -> page 1 (duplicate key)
  //
  // The resulting GTree should contain keys: DestA, DestB, Same (3 unique names).
  std::vector<std::pair<int, std::string>> objs;

  // 1: Catalog with both /Dests and /Names destinations tree
  objs.emplace_back(
      1,
      "<< /Type /Catalog /Pages 2 0 R "
      "/Dests << /DestA 10 0 R /Same 11 0 R >> "
      "/Names << /Dests 12 0 R >> >>");

  // 2: Pages (2 pages)
  objs.emplace_back(2, "<< /Type /Pages /Kids [3 0 R 4 0 R] /Count 2 >>");

  // 3: Page 1
  objs.emplace_back(3, "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 100 100] "
                      "/Contents 5 0 R /Resources <<>> >>");
  // 4: Page 2
  objs.emplace_back(4, "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 100 100] "
                      "/Contents 6 0 R /Resources <<>> >>");

  // 5/6: empty content streams
  objs.emplace_back(5, "<< /Length 0 >>\nstream\n\nendstream");
  objs.emplace_back(6, "<< /Length 0 >>\nstream\n\nendstream");

  // 10: DestA => page 1 XYZ
  objs.emplace_back(10, "[ 3 0 R /XYZ 0 0 0 ]");
  // 11: Same => page 2 XYZ (will be duplicated by name tree entry)
  objs.emplace_back(11, "[ 4 0 R /XYZ 0 0 0 ]");

  // 12: Name tree for destinations
  objs.emplace_back(12, "<< /Names [ (DestB) 13 0 R (Same) 14 0 R ] >>");
  // 13: DestB => page 1 Fit
  objs.emplace_back(13, "[ 3 0 R /Fit ]");
  // 14: Same => page 1 XYZ
  objs.emplace_back(14, "[ 3 0 R /XYZ 0 0 0 ]");

  return BuildPdfWithObjects_2162(objs);
}

static PopplerDocument *NewDocFromData_2162(const std::string &pdf_bytes_2162) {
  GError *error = nullptr;
  PopplerDocument *doc =
      poppler_document_new_from_data(pdf_bytes_2162.c_str(),
                                     static_cast<int>(pdf_bytes_2162.size()),
                                     /*password=*/nullptr, &error);
  if (!doc) {
    if (error) {
      g_error_free(error);
    }
    return nullptr;
  }
  if (error) {
    g_error_free(error);
  }
  return doc;
}

class PopplerDocumentCreateDestsTreeTest_2162 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure GType system is initialized for safety with older GLib.
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif
  }
};

} // namespace

TEST_F(PopplerDocumentCreateDestsTreeTest_2162, NullDocumentReturnsNull_2162) {
  // g_return_val_if_fail emits a GLib critical; expect it and verify return.
  g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*assertion*POPPLER_IS_DOCUMENT*failed*");
  GTree *tree = poppler_document_create_dests_tree(nullptr);
  EXPECT_EQ(tree, nullptr);
  g_test_assert_expected_messages();
}

TEST_F(PopplerDocumentCreateDestsTreeTest_2162, WrongGObjectTypeReturnsNull_2162) {
  // Pass a non-PopplerDocument instance casted to PopplerDocument*.
  GObject *obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*assertion*POPPLER_IS_DOCUMENT*failed*");
  GTree *tree = poppler_document_create_dests_tree(reinterpret_cast<PopplerDocument *>(obj));
  EXPECT_EQ(tree, nullptr);
  g_test_assert_expected_messages();

  g_object_unref(obj);
}

TEST_F(PopplerDocumentCreateDestsTreeTest_2162, NoDestinationsReturnsEmptyTree_2162) {
  std::string pdf = MakePdf_NoNamedDests_2162();
  PopplerDocument *doc = NewDocFromData_2162(pdf);
  ASSERT_NE(doc, nullptr);

  GTree *tree = poppler_document_create_dests_tree(doc);
  ASSERT_NE(tree, nullptr);

  EXPECT_EQ(g_tree_nnodes(tree), 0);

  g_tree_destroy(tree);
  g_object_unref(doc);
}

TEST_F(PopplerDocumentCreateDestsTreeTest_2162, CreatesTreeContainingDestsFromDestsAndNameTree_2162) {
  std::string pdf = MakePdf_WithNamedDests_DestsAndNameTree_2162();
  PopplerDocument *doc = NewDocFromData_2162(pdf);
  ASSERT_NE(doc, nullptr);

  GTree *tree = poppler_document_create_dests_tree(doc);
  ASSERT_NE(tree, nullptr);

  // Unique expected keys: DestA, DestB, Same
  EXPECT_EQ(g_tree_nnodes(tree), 3);

  // Verify lookups by name.
  PopplerDest *destA = static_cast<PopplerDest *>(g_tree_lookup(tree, "DestA"));
  PopplerDest *destB = static_cast<PopplerDest *>(g_tree_lookup(tree, "DestB"));
  PopplerDest *same  = static_cast<PopplerDest *>(g_tree_lookup(tree, "Same"));

  EXPECT_NE(destA, nullptr);
  EXPECT_NE(destB, nullptr);
  EXPECT_NE(same, nullptr);

  // Boundary: looking up a missing key should yield nullptr.
  EXPECT_EQ(g_tree_lookup(tree, "DoesNotExist"), nullptr);

  g_tree_destroy(tree);
  g_object_unref(doc);
}

TEST_F(PopplerDocumentCreateDestsTreeTest_2162, DuplicateNameDoesNotIncreaseNodeCount_2162) {
  // This PDF includes "Same" in both /Dests and /Names destinations;
  // observable behavior here: the key exists and the tree has only unique names.
  std::string pdf = MakePdf_WithNamedDests_DestsAndNameTree_2162();
  PopplerDocument *doc = NewDocFromData_2162(pdf);
  ASSERT_NE(doc, nullptr);

  GTree *tree = poppler_document_create_dests_tree(doc);
  ASSERT_NE(tree, nullptr);

  // Still only 3 unique entries.
  EXPECT_EQ(g_tree_nnodes(tree), 3);
  EXPECT_NE(g_tree_lookup(tree, "Same"), nullptr);

  g_tree_destroy(tree);
  g_object_unref(doc);
}