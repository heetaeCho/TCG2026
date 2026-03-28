// poppler-structure-element-attr-to-enum-test_2521.cc
//
// Unit tests exercising observable behavior that relies on the internal helper
//   template<typename EnumType> static EnumType attr_to_enum(PopplerStructureElement*)
// from poppler-structure-element.cc, via the public PopplerStructureElement API.
//
// Constraints respected:
// - No re-implementation/inference of Poppler internals.
// - Tests only use public GLib Poppler interfaces and observable behavior.
// - Boundary/error cases covered (missing structure tree, missing attribute).

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

// ---------------------------
// Minimal RAII helpers
// ---------------------------

namespace {

struct GErrorDeleter {
  void operator()(GError* e) const {
    if (e) g_error_free(e);
  }
};
using UniqueGError = std::unique_ptr<GError, GErrorDeleter>;

struct GObjectUnrefDeleter {
  void operator()(gpointer p) const {
    if (p) g_object_unref(p);
  }
};

using UniquePopplerDocument =
    std::unique_ptr<PopplerDocument, GObjectUnrefDeleter>;

struct StructureIterFreeDeleter {
  void operator()(PopplerStructureElementIter* it) const {
    if (it) poppler_structure_element_iter_free(it);
  }
};
using UniqueStructureIter =
    std::unique_ptr<PopplerStructureElementIter, StructureIterFreeDeleter>;

static std::string MakeTempPath_2521(const char* basename) {
  // Put in system temp dir.
  const char* tmp = g_get_tmp_dir();
  // Use PID + random-ish suffix to avoid collisions.
  guint32 r = g_random_int();
  char* p = g_strdup_printf("%s/%s_%d_%u.pdf", tmp, basename, (int)getpid(), r);
  std::string out(p);
  g_free(p);
  return out;
}

static std::string FilenameToUri_2521(const std::string& path) {
  UniqueGError err(nullptr);
  char* uri = g_filename_to_uri(path.c_str(), /*hostname=*/nullptr, &err.get());
  if (!uri) return {};
  std::string out(uri);
  g_free(uri);
  return out;
}

static bool WriteFile_2521(const std::string& path, const std::string& bytes) {
  UniqueGError err(nullptr);
  gboolean ok = g_file_set_contents(path.c_str(), bytes.data(),
                                   static_cast<gssize>(bytes.size()), &err.get());
  return ok == TRUE;
}

// ---------------------------
// Tiny PDF builder (test infra)
// ---------------------------

static std::string BuildPdfWithStructure_TextAlign_2521(
    const char* text_align_name_or_null /* e.g. "Center", or nullptr to omit /A */) {
  // Objects (1..9):
  // 1: Catalog with StructTreeRoot and Pages
  // 2: Pages
  // 3: Page with StructParents=0 and content stream
  // 4: Contents stream with a marked-content sequence MCID 0
  // 5: StructTreeRoot with K=[6 0 R] and ParentTree
  // 6: StructElem (/S /P) with optional /A << /TextAlign /X >>
  // 7: ParentTree
  // 8: (unused placeholder in case; keep numbering stable) -> empty dict
  // 9: MCR dict referencing page + MCID 0

  std::vector<std::string> obj(10);  // index = obj number
  obj[1] =
      "<< /Type /Catalog /Pages 2 0 R /MarkInfo << /Marked true >> /StructTreeRoot 5 0 R >>";
  obj[2] =
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>";
  obj[3] =
      "<< /Type /Page /Parent 2 0 R "
      "/MediaBox [0 0 200 200] "
      "/Resources << >> "
      "/Contents 4 0 R "
      "/StructParents 0 >>";

  // Marked content with MCID 0.
  // Use a minimal operators set; Poppler should still parse the tagged content.
  const char* stream_ops =
      "/P <</MCID 0>> BDC\n"
      "BT\n"
      "/F1 12 Tf\n"
      "10 100 Td\n"
      "(Hello) Tj\n"
      "ET\n"
      "EMC\n";
  {
    std::string s(stream_ops);
    obj[4] = std::string("<< /Length ") + std::to_string(s.size()) + " >>\nstream\n" + s +
             "endstream";
  }

  obj[5] =
      "<< /Type /StructTreeRoot /K [6 0 R] /ParentTree 7 0 R >>";

  {
    std::string a;
    if (text_align_name_or_null) {
      // PDF name object: /Center, /End, /Justify, /Start, etc.
      a = std::string(" /A << /TextAlign /") + text_align_name_or_null + " >>";
    }
    // /P is the parent in the structure hierarchy; for a top-level element, it is the tree root.
    obj[6] =
        std::string("<< /Type /StructElem /S /P /P 5 0 R") + a + " /K 9 0 R >>";
  }

  // ParentTree maps StructParents index 0 -> array containing the marked-content reference 9 0 R.
  obj[7] = "<< /Nums [ 0 [9 0 R] ] >>";

  obj[8] = "<< >>";  // placeholder, not referenced

  obj[9] = "<< /Type /MCR /Pg 3 0 R /MCID 0 >>";

  // Assemble PDF with correct xref offsets.
  std::string out;
  out += "%PDF-1.7\n";
  std::vector<long> offsets(10, 0);

  for (int i = 1; i <= 9; ++i) {
    offsets[i] = static_cast<long>(out.size());
    out += std::to_string(i) + " 0 obj\n";
    out += obj[i];
    out += "\nendobj\n";
  }

  const long xref_pos = static_cast<long>(out.size());
  out += "xref\n";
  out += "0 10\n";
  out += "0000000000 65535 f \n";
  for (int i = 1; i <= 9; ++i) {
    char line[32];
    std::snprintf(line, sizeof(line), "%010ld 00000 n \n", offsets[i]);
    out += line;
  }
  out += "trailer\n";
  out += "<< /Size 10 /Root 1 0 R >>\n";
  out += "startxref\n";
  out += std::to_string(xref_pos) + "\n";
  out += "%%EOF\n";
  return out;
}

static std::string BuildPdfWithoutStructureTree_2521() {
  // Minimal 1-page PDF without StructTreeRoot.
  // Objects: 1 Catalog, 2 Pages, 3 Page, 4 Contents.
  std::vector<std::string> obj(5);
  obj[1] = "<< /Type /Catalog /Pages 2 0 R >>";
  obj[2] = "<< /Type /Pages /Kids [3 0 R] /Count 1 >>";
  obj[3] = "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Resources << >> /Contents 4 0 R >>";
  const char* stream_ops =
      "BT\n"
      "/F1 12 Tf\n"
      "10 100 Td\n"
      "(Hello) Tj\n"
      "ET\n";
  std::string s(stream_ops);
  obj[4] = std::string("<< /Length ") + std::to_string(s.size()) + " >>\nstream\n" + s +
           "endstream";

  std::string out;
  out += "%PDF-1.7\n";
  std::vector<long> offsets(5, 0);
  for (int i = 1; i <= 4; ++i) {
    offsets[i] = static_cast<long>(out.size());
    out += std::to_string(i) + " 0 obj\n";
    out += obj[i];
    out += "\nendobj\n";
  }
  const long xref_pos = static_cast<long>(out.size());
  out += "xref\n";
  out += "0 5\n";
  out += "0000000000 65535 f \n";
  for (int i = 1; i <= 4; ++i) {
    char line[32];
    std::snprintf(line, sizeof(line), "%010ld 00000 n \n", offsets[i]);
    out += line;
  }
  out += "trailer\n";
  out += "<< /Size 5 /Root 1 0 R >>\n";
  out += "startxref\n";
  out += std::to_string(xref_pos) + "\n";
  out += "%%EOF\n";
  return out;
}

static UniquePopplerDocument LoadDocumentFromPdfBytes_2521(const std::string& pdf_bytes,
                                                          std::string* out_path_opt = nullptr) {
  const std::string path = MakeTempPath_2521("poppler_attr_to_enum_2521");
  if (!WriteFile_2521(path, pdf_bytes)) {
    return UniquePopplerDocument(nullptr);
  }
  if (out_path_opt) *out_path_opt = path;

  const std::string uri = FilenameToUri_2521(path);
  if (uri.empty()) return UniquePopplerDocument(nullptr);

  GError* err_raw = nullptr;
  PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &err_raw);
  UniqueGError err(err_raw);
  // If doc is null, caller will assert; keep it observable.
  return UniquePopplerDocument(doc);
}

static PopplerStructureElement* GetFirstStructureElement_2521(PopplerDocument* doc,
                                                              UniqueStructureIter* out_iter) {
  PopplerStructureElementIter* it_raw = poppler_structure_element_iter_new(doc);
  out_iter->reset(it_raw);
  if (!it_raw) return nullptr;
  return poppler_structure_element_iter_get_element(it_raw);
}

}  // namespace

// ---------------------------
// Tests (TEST_ID = 2521)
// ---------------------------

TEST(PopplerStructureElementAttrToEnumTest_2521, IterIsNullWhenNoStructureTree_2521) {
  UniquePopplerDocument doc = LoadDocumentFromPdfBytes_2521(BuildPdfWithoutStructureTree_2521());
  ASSERT_NE(doc.get(), nullptr);

  UniqueStructureIter iter(nullptr);
  PopplerStructureElement* elem = GetFirstStructureElement_2521(doc.get(), &iter);
  EXPECT_EQ(iter.get(), nullptr);
  EXPECT_EQ(elem, nullptr);
}

TEST(PopplerStructureElementAttrToEnumTest_2521, TextAlignCenterReturnedWhenAttributePresent_2521) {
  UniquePopplerDocument doc =
      LoadDocumentFromPdfBytes_2521(BuildPdfWithStructure_TextAlign_2521("Center"));
  ASSERT_NE(doc.get(), nullptr);

  UniqueStructureIter iter(nullptr);
  PopplerStructureElement* elem = GetFirstStructureElement_2521(doc.get(), &iter);
  ASSERT_NE(iter.get(), nullptr);
  ASSERT_NE(elem, nullptr);

  // Observable behavior: the public getter returns the enum value corresponding
  // to the attribute name, which is internally obtained via attr_to_enum<>.
  PopplerStructureTextAlign align = poppler_structure_element_get_text_align(elem);
  EXPECT_EQ(align, POPPLER_STRUCTURE_TEXT_ALIGN_CENTER);
}

TEST(PopplerStructureElementAttrToEnumTest_2521, TextAlignEndReturnedWhenAttributePresent_2521) {
  UniquePopplerDocument doc =
      LoadDocumentFromPdfBytes_2521(BuildPdfWithStructure_TextAlign_2521("End"));
  ASSERT_NE(doc.get(), nullptr);

  UniqueStructureIter iter(nullptr);
  PopplerStructureElement* elem = GetFirstStructureElement_2521(doc.get(), &iter);
  ASSERT_NE(iter.get(), nullptr);
  ASSERT_NE(elem, nullptr);

  PopplerStructureTextAlign align = poppler_structure_element_get_text_align(elem);
  EXPECT_EQ(align, POPPLER_STRUCTURE_TEXT_ALIGN_END);
}

TEST(PopplerStructureElementAttrToEnumTest_2521, TextAlignJustifyReturnedWhenAttributePresent_2521) {
  UniquePopplerDocument doc =
      LoadDocumentFromPdfBytes_2521(BuildPdfWithStructure_TextAlign_2521("Justify"));
  ASSERT_NE(doc.get(), nullptr);

  UniqueStructureIter iter(nullptr);
  PopplerStructureElement* elem = GetFirstStructureElement_2521(doc.get(), &iter);
  ASSERT_NE(iter.get(), nullptr);
  ASSERT_NE(elem, nullptr);

  PopplerStructureTextAlign align = poppler_structure_element_get_text_align(elem);
  EXPECT_EQ(align, POPPLER_STRUCTURE_TEXT_ALIGN_JUSTIFY);
}

TEST(PopplerStructureElementAttrToEnumTest_2521, TextAlignReturnsAValidEnumWhenAttributeOmitted_2521) {
  UniquePopplerDocument doc =
      LoadDocumentFromPdfBytes_2521(BuildPdfWithStructure_TextAlign_2521(/*omit /A*/ nullptr));
  ASSERT_NE(doc.get(), nullptr);

  UniqueStructureIter iter(nullptr);
  PopplerStructureElement* elem = GetFirstStructureElement_2521(doc.get(), &iter);
  ASSERT_NE(iter.get(), nullptr);
  ASSERT_NE(elem, nullptr);

  // Boundary case: attribute missing. The internal helper uses the attribute's default
  // value (Attribute::getDefaultValue(...)) when undefined. We do not assume what that
  // default is; we only assert it maps to a valid enum member.
  PopplerStructureTextAlign align = poppler_structure_element_get_text_align(elem);
  EXPECT_TRUE(align == POPPLER_STRUCTURE_TEXT_ALIGN_START ||
              align == POPPLER_STRUCTURE_TEXT_ALIGN_CENTER ||
              align == POPPLER_STRUCTURE_TEXT_ALIGN_END ||
              align == POPPLER_STRUCTURE_TEXT_ALIGN_JUSTIFY);
}

TEST(PopplerStructureElementAttrToEnumTest_2521, IterNextReturnsFalseAtEndForSingleTopLevelElement_2521) {
  UniquePopplerDocument doc =
      LoadDocumentFromPdfBytes_2521(BuildPdfWithStructure_TextAlign_2521("Center"));
  ASSERT_NE(doc.get(), nullptr);

  UniqueStructureIter iter(nullptr);
  PopplerStructureElement* elem = GetFirstStructureElement_2521(doc.get(), &iter);
  ASSERT_NE(elem, nullptr);

  // With a single top-level element in the structure tree, advancing should fail.
  EXPECT_FALSE(poppler_structure_element_iter_next(iter.get()));
}