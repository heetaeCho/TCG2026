// poppler-structure-element-get-column-gaps-test_2585.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <string>
#include <utility>
#include <vector>

namespace {

struct TempPdfFile {
  std::string path;
  std::string uri;

  ~TempPdfFile() {
    if (!path.empty()) {
      std::error_code ec;
      std::filesystem::remove(path, ec);
    }
  }
};

// Build a minimal tagged PDF with a simple structure tree.
// If add_column_gap_attr is true, the single StructElem has a /A << /O /Layout /ColumnGap [a b] >> entry.
static std::string BuildTaggedPdf(bool add_column_gap_attr, double a = 12.0, double b = 34.0) {
  // We'll construct objects and then compute xref offsets.
  // Objects:
  // 1 0 Catalog
  // 2 0 Pages
  // 3 0 Page (with /StructParents 0)
  // 4 0 Contents stream (with /MCID 0 marked content)
  // 5 0 StructTreeRoot
  // 6 0 StructElem (/S /P)
  // 7 0 Font
  // 8 0 ParentTree
  // 9 0 MCR

  auto fmt_double = [](double v) -> std::string {
    // Simple formatting: avoid scientific notation for typical values used in tests.
    char buf[64];
    // Keep enough precision for stable roundtrip within reasonable bounds.
    g_snprintf(buf, sizeof(buf), "%.6f", v);
    // Trim trailing zeros and dot.
    std::string s(buf);
    while (!s.empty() && s.back() == '0') s.pop_back();
    if (!s.empty() && s.back() == '.') s.pop_back();
    if (s.empty()) s = "0";
    return s;
  };

  const std::string a_s = fmt_double(a);
  const std::string b_s = fmt_double(b);

  std::vector<std::string> objs;
  objs.reserve(10);

  // 1 0 obj
  objs.push_back(
      "1 0 obj\n"
      "<< /Type /Catalog\n"
      "   /Pages 2 0 R\n"
      "   /StructTreeRoot 5 0 R\n"
      "   /MarkInfo << /Marked true >>\n"
      ">>\n"
      "endobj\n");

  // 2 0 obj
  objs.push_back(
      "2 0 obj\n"
      "<< /Type /Pages\n"
      "   /Kids [3 0 R]\n"
      "   /Count 1\n"
      ">>\n"
      "endobj\n");

  // 3 0 obj (Page)
  objs.push_back(
      "3 0 obj\n"
      "<< /Type /Page\n"
      "   /Parent 2 0 R\n"
      "   /MediaBox [0 0 200 200]\n"
      "   /Resources << /ProcSet [/PDF /Text]\n"
      "                 /Font << /F1 7 0 R >>\n"
      "              >>\n"
      "   /Contents 4 0 R\n"
      "   /StructParents 0\n"
      ">>\n"
      "endobj\n");

  // 4 0 obj (Contents) - include marked-content with /MCID 0.
  const std::string stream_data =
      "/P <</MCID 0>> BDC\n"
      "BT\n"
      "/F1 12 Tf\n"
      "50 150 Td\n"
      "(Hello) Tj\n"
      "ET\n"
      "EMC\n";
  objs.push_back("4 0 obj\n"
                 "<< /Length " +
                 std::to_string(stream_data.size()) +
                 " >>\n"
                 "stream\n" +
                 stream_data +
                 "endstream\n"
                 "endobj\n");

  // 5 0 obj (StructTreeRoot)
  objs.push_back(
      "5 0 obj\n"
      "<< /Type /StructTreeRoot\n"
      "   /K 6 0 R\n"
      "   /ParentTree 8 0 R\n"
      ">>\n"
      "endobj\n");

  // 6 0 obj (StructElem)
  std::string struct_elem =
      "6 0 obj\n"
      "<< /Type /StructElem\n"
      "   /S /P\n"
      "   /P 5 0 R\n"
      "   /K 9 0 R\n";
  if (add_column_gap_attr) {
    // Layout attribute owner with ColumnGap array.
    struct_elem +=
        "   /A << /O /Layout /ColumnGap [" + a_s + " " + b_s + "] >>\n";
  }
  struct_elem += ">>\nendobj\n";
  objs.push_back(std::move(struct_elem));

  // 7 0 obj (Font)
  objs.push_back(
      "7 0 obj\n"
      "<< /Type /Font\n"
      "   /Subtype /Type1\n"
      "   /BaseFont /Helvetica\n"
      ">>\n"
      "endobj\n");

  // 8 0 obj (ParentTree)
  objs.push_back(
      "8 0 obj\n"
      "<< /Nums [ 0 [ 9 0 R ] ] >>\n"
      "endobj\n");

  // 9 0 obj (MCR)
  objs.push_back(
      "9 0 obj\n"
      "<< /Type /MCR\n"
      "   /Pg 3 0 R\n"
      "   /MCID 0\n"
      ">>\n"
      "endobj\n");

  // Assemble PDF and compute offsets.
  std::string pdf;
  pdf.reserve(4096);
  pdf += "%PDF-1.5\n";
  pdf += "%\xE2\xE3\xCF\xD3\n";  // binary comment

  std::vector<std::size_t> offsets;
  offsets.reserve(objs.size() + 1);
  offsets.push_back(0);  // object 0 (free)

  for (const auto& obj : objs) {
    offsets.push_back(pdf.size());
    pdf += obj;
  }

  const std::size_t xref_pos = pdf.size();
  pdf += "xref\n";
  pdf += "0 " + std::to_string(objs.size() + 1) + "\n";
  pdf += "0000000000 65535 f \n";
  for (std::size_t i = 1; i < offsets.size(); ++i) {
    char line[32];
    g_snprintf(line, sizeof(line), "%010zu 00000 n \n", offsets[i]);
    pdf += line;
  }

  pdf += "trailer\n";
  pdf += "<< /Size " + std::to_string(objs.size() + 1) + "\n";
  pdf += "   /Root 1 0 R\n";
  pdf += ">>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_pos) + "\n";
  pdf += "%%EOF\n";

  return pdf;
}

static TempPdfFile WriteTempPdf(const std::string& pdf_bytes) {
  TempPdfFile out;

  // Create a predictable-ish unique temp filename.
  gchar* tmp_name = g_strdup_printf("poppler_structure_2585_%u.pdf", g_random_int());
  gchar* tmp_path = g_build_filename(g_get_tmp_dir(), tmp_name, nullptr);
  g_free(tmp_name);

  GError* error = nullptr;
  gboolean ok = g_file_set_contents(tmp_path, pdf_bytes.data(),
                                    static_cast<gssize>(pdf_bytes.size()), &error);
  if (!ok) {
    std::string msg = error ? error->message : "unknown error";
    if (error) g_error_free(error);
    g_free(tmp_path);
    throw std::runtime_error("Failed to write temp PDF: " + msg);
  }

  gchar* uri = g_filename_to_uri(tmp_path, nullptr, &error);
  if (!uri) {
    std::string msg = error ? error->message : "unknown error";
    if (error) g_error_free(error);
    std::filesystem::remove(tmp_path);
    g_free(tmp_path);
    throw std::runtime_error("Failed to make file URI: " + msg);
  }

  out.path = tmp_path;
  out.uri = uri;

  g_free(tmp_path);
  g_free(uri);
  return out;
}

static PopplerDocument* LoadDocumentFromUri(const std::string& uri) {
  GError* error = nullptr;
  PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &error);
  if (!doc) {
    std::string msg = error ? error->message : "unknown error";
    if (error) g_error_free(error);
    return nullptr;
  }
  if (error) g_error_free(error);
  return doc;
}

static PopplerStructureElement* FindFirstGroupingElement(PopplerDocument* doc) {
  if (!doc) return nullptr;

  PopplerStructureElementIter* iter = poppler_structure_element_iter_new(doc);
  if (!iter) return nullptr;

  PopplerStructureElement* found = nullptr;

  // DFS using the iterator APIs.
  std::function<void(PopplerStructureElementIter*)> walk = [&](PopplerStructureElementIter* it) {
    if (!it || found) return;

    do {
      PopplerStructureElement* el = poppler_structure_element_iter_get_element(it);
      if (el && poppler_structure_element_is_grouping(el)) {
        found = static_cast<PopplerStructureElement*>(g_object_ref(el));
        return;
      }

      PopplerStructureElementIter* child = poppler_structure_element_iter_get_child(it);
      if (child) {
        walk(child);
        poppler_structure_element_iter_free(child);
        if (found) return;
      }
    } while (poppler_structure_element_iter_next(it));
  };

  walk(iter);
  poppler_structure_element_iter_free(iter);
  return found;
}

class PopplerStructureElementColumnGapsTest_2585 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure GLib type system is initialized (safe no-op on newer GLib).
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif
  }
};

}  // namespace

TEST_F(PopplerStructureElementColumnGapsTest_2585, ReturnsNullAndSetsMinusOneWhenAttributeNotDefined_2585) {
  TempPdfFile tmp = WriteTempPdf(BuildTaggedPdf(/*add_column_gap_attr=*/false));
  PopplerDocument* doc = LoadDocumentFromUri(tmp.uri);
  ASSERT_NE(doc, nullptr);

  PopplerStructureElement* grouping = FindFirstGroupingElement(doc);
  if (!grouping) {
    g_object_unref(doc);
    GTEST_SKIP() << "No grouping structure element found in test PDF (structure iteration not available).";
  }

  guint n_values = 123;  // sentinel
  gdouble* gaps = poppler_structure_element_get_column_gaps(grouping, &n_values);

  // Per implementation: if attribute is not present, returns NULL and sets n_values to (guint)-1.
  EXPECT_EQ(gaps, nullptr);
  EXPECT_EQ(n_values, static_cast<guint>(-1));

  g_object_unref(grouping);
  g_object_unref(doc);
}

TEST_F(PopplerStructureElementColumnGapsTest_2585, ReturnsArrayWhenAttributeDefined_2585) {
  TempPdfFile tmp = WriteTempPdf(BuildTaggedPdf(/*add_column_gap_attr=*/true, /*a=*/12.0, /*b=*/34.0));
  PopplerDocument* doc = LoadDocumentFromUri(tmp.uri);
  ASSERT_NE(doc, nullptr);

  PopplerStructureElement* grouping = FindFirstGroupingElement(doc);
  if (!grouping) {
    g_object_unref(doc);
    GTEST_SKIP() << "No grouping structure element found in test PDF (structure iteration not available).";
  }

  guint n_values = 0;
  gdouble* gaps = poppler_structure_element_get_column_gaps(grouping, &n_values);

  ASSERT_NE(gaps, nullptr);
  ASSERT_EQ(n_values, 2u);
  EXPECT_NEAR(gaps[0], 12.0, 1e-9);
  EXPECT_NEAR(gaps[1], 34.0, 1e-9);

  g_free(gaps);
  g_object_unref(grouping);
  g_object_unref(doc);
}

TEST_F(PopplerStructureElementColumnGapsTest_2585, ReturnsNullWhenNValuesIsNull_2585) {
  TempPdfFile tmp = WriteTempPdf(BuildTaggedPdf(/*add_column_gap_attr=*/true, /*a=*/1.0, /*b=*/2.0));
  PopplerDocument* doc = LoadDocumentFromUri(tmp.uri);
  ASSERT_NE(doc, nullptr);

  PopplerStructureElement* grouping = FindFirstGroupingElement(doc);
  if (!grouping) {
    g_object_unref(doc);
    GTEST_SKIP() << "No grouping structure element found in test PDF (structure iteration not available).";
  }

  // Avoid failing the test run if G_DEBUG=fatal-criticals is enabled:
  // expect the critical from g_return_val_if_fail().
  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*assertion*");
  gdouble* gaps = poppler_structure_element_get_column_gaps(grouping, nullptr);
  g_test_assert_expected_messages();

  EXPECT_EQ(gaps, nullptr);

  g_object_unref(grouping);
  g_object_unref(doc);
}