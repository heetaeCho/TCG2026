// poppler_structure_element_get_space_before_test_2563.cc
#include <gtest/gtest.h>

#include <poppler.h>

#include <glib.h>

#include <cmath>
#include <cstdint>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

namespace {

static std::string BuildMinimalTaggedPdfWithSpaceBefore(double space_before_value) {
  // Build a very small, valid PDF with a StructTreeRoot and two structure elements:
  //  - A block element (/S /P) with attribute /SpaceBefore = space_before_value
  //  - A non-block inline element (/S /Span) with no SpaceBefore attribute
  //
  // We keep /K empty arrays; Poppler should still parse the structure tree.
  std::vector<std::string> objs;
  objs.reserve(8);

  // 1: Catalog
  objs.push_back(
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R /StructTreeRoot 6 0 R >>\n"
      "endobj\n");

  // 2: Pages
  objs.push_back(
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n");

  // 3: Page
  objs.push_back(
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
      "   /Resources << >> /Contents 4 0 R >>\n"
      "endobj\n");

  // 4: Contents (minimal)
  objs.push_back(
      "4 0 obj\n"
      "<< /Length 6 >>\n"
      "stream\n"
      "q\n"
      "Q\n"
      "endstream\n"
      "endobj\n");

  // 5: StructElem P (block) with /A Layout attributes including /SpaceBefore
  {
    std::ostringstream oss;
    oss.setf(std::ios::fmtflags(0), std::ios::floatfield);
    oss.precision(17);
    oss << "5 0 obj\n"
           "<< /Type /StructElem /S /P /P 6 0 R /Pg 3 0 R /K []\n"
           "   /A << /O /Layout /SpaceBefore "
        << space_before_value << " >> >>\n"
           "endobj\n";
    objs.push_back(oss.str());
  }

  // 6: StructTreeRoot with children [5 0 R 7 0 R]
  objs.push_back(
      "6 0 obj\n"
      "<< /Type /StructTreeRoot /K [5 0 R 7 0 R] >>\n"
      "endobj\n");

  // 7: StructElem Span (inline, non-block)
  objs.push_back(
      "7 0 obj\n"
      "<< /Type /StructElem /S /Span /P 6 0 R /Pg 3 0 R /K [] >>\n"
      "endobj\n");

  // Assemble PDF and compute xref offsets.
  std::string pdf;
  pdf.reserve(4096);
  pdf += "%PDF-1.7\n";
  // Binary comment line recommended by spec (helps some parsers).
  pdf += "%\xE2\xE3\xCF\xD3\n";

  std::vector<long> offsets;
  offsets.resize(objs.size() + 1);
  offsets[0] = 0; // object 0 free entry

  for (size_t i = 0; i < objs.size(); ++i) {
    offsets[i + 1] = static_cast<long>(pdf.size());
    pdf += objs[i];
  }

  const long xref_pos = static_cast<long>(pdf.size());
  {
    std::ostringstream xref;
    xref << "xref\n";
    xref << "0 " << (objs.size() + 1) << "\n";
    // obj 0 free
    xref << "0000000000 65535 f \n";
    // obj 1..N
    for (size_t i = 1; i <= objs.size(); ++i) {
      char buf[32];
      std::snprintf(buf, sizeof(buf), "%010ld", offsets[i]);
      xref << buf << " 00000 n \n";
    }
    pdf += xref.str();
  }

  {
    std::ostringstream trailer;
    trailer << "trailer\n"
            << "<< /Size " << (objs.size() + 1) << " /Root 1 0 R >>\n"
            << "startxref\n"
            << xref_pos << "\n"
            << "%%EOF\n";
    pdf += trailer.str();
  }

  return pdf;
}

static std::string WriteTempPdfOrDie(const std::string &pdf_bytes) {
  gchar *tmp_name = nullptr;
  GError *error = nullptr;

  // Create a temp file.
  gint fd = g_file_open_tmp("poppler-structure-2563-XXXXXX.pdf", &tmp_name, &error);
  if (fd < 0) {
    std::string msg = "g_file_open_tmp failed: ";
    msg += (error && error->message) ? error->message : "unknown";
    if (error) g_error_free(error);
    GTEST_FAIL() << msg;
    return "";
  }

  // Write bytes.
  gsize total = 0;
  while (total < pdf_bytes.size()) {
    const gssize written =
        g_write(fd, pdf_bytes.data() + total, pdf_bytes.size() - total, &error);
    if (written <= 0) {
      std::string msg = "write failed: ";
      msg += (error && error->message) ? error->message : "unknown";
      if (error) g_error_free(error);
      g_close(fd, nullptr);
      g_unlink(tmp_name);
      g_free(tmp_name);
      GTEST_FAIL() << msg;
      return "";
    }
    total += static_cast<gsize>(written);
  }
  g_close(fd, nullptr);

  std::string path(tmp_name);
  g_free(tmp_name);
  return path;
}

static PopplerDocument *LoadDocumentFromPathOrDie(const std::string &path) {
  GError *error = nullptr;
  gchar *uri = g_filename_to_uri(path.c_str(), nullptr, &error);
  if (!uri) {
    std::string msg = "g_filename_to_uri failed: ";
    msg += (error && error->message) ? error->message : "unknown";
    if (error) g_error_free(error);
    GTEST_FAIL() << msg;
    return nullptr;
  }

  PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
  g_free(uri);

  if (!doc) {
    std::string msg = "poppler_document_new_from_file failed: ";
    msg += (error && error->message) ? error->message : "unknown";
    if (error) g_error_free(error);
    GTEST_FAIL() << msg;
    return nullptr;
  }

  return doc;
}

static PopplerStructureElement *FindFirstElementMatching(PopplerStructureElementIter *root_iter,
                                                        bool want_block) {
  // Walk the whole structure tree, return the first element where is_block == want_block.
  // We only use public traversal APIs.
  if (!root_iter) return nullptr;

  // Depth-first traversal.
  std::function<PopplerStructureElement *(PopplerStructureElementIter *)> walk =
      [&](PopplerStructureElementIter *iter) -> PopplerStructureElement * {
    if (!iter) return nullptr;

    do {
      PopplerStructureElement *el = poppler_structure_element_iter_get_element(iter);
      if (el) {
        const gboolean is_block = poppler_structure_element_is_block(el);
        if ((want_block && is_block) || (!want_block && !is_block)) {
          return el; // element is owned by caller? API says transfer full for get_element in some docs;
                     // but in practice Poppler returns a refcounted wrapper. We'll treat as full and free.
        }
      }

      PopplerStructureElementIter *child = poppler_structure_element_iter_get_child(iter);
      if (child) {
        PopplerStructureElement *found = walk(child);
        poppler_structure_element_iter_free(child);
        if (found) return found;
      }
    } while (poppler_structure_element_iter_next(iter));

    return nullptr;
  };

  return walk(root_iter);
}

} // namespace

// ---- Tests ----

TEST(PopplerStructureElementSpaceBeforeTest_2563, NullElementReturnsNaN_2563) {
  const gdouble v = poppler_structure_element_get_space_before(nullptr);
  EXPECT_TRUE(std::isnan(v));
}

TEST(PopplerStructureElementSpaceBeforeTest_2563, NonBlockElementReturnsNaN_2563) {
  // Create a Tagged PDF with an inline /Span element, then verify the API returns NaN on it.
  const std::string pdf = BuildMinimalTaggedPdfWithSpaceBefore(12.0);
  const std::string path = WriteTempPdfOrDie(pdf);
  ASSERT_FALSE(path.empty());

  PopplerDocument *doc = LoadDocumentFromPathOrDie(path);
  ASSERT_NE(doc, nullptr);

  PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
  ASSERT_NE(iter, nullptr);

  PopplerStructureElement *non_block = FindFirstElementMatching(iter, /*want_block=*/false);
  poppler_structure_element_iter_free(iter);

  ASSERT_NE(non_block, nullptr);
  EXPECT_FALSE(poppler_structure_element_is_block(non_block));

  const gdouble v = poppler_structure_element_get_space_before(non_block);
  EXPECT_TRUE(std::isnan(v));

  // Cleanup
  g_object_unref(doc);
  g_unlink(path.c_str());
  // Free element wrapper if Poppler returned transfer-full.
  // If Poppler returns a non-refcounted pointer, g_clear_object is harmless on NULL only,
  // so do a defensive unref via g_object_unref if it is a GObject.
  // PopplerStructureElement is not documented as GObject; free via g_object_unref is not correct.
  // Use g_free? Not correct either. The safest is to call poppler_structure_element_free if exists,
  // but it does not. Therefore, do not attempt to free it here; Poppler's iter element accessor
  // typically returns an internal wrapper managed by Poppler (or by the iter).
  (void)non_block;
}

TEST(PopplerStructureElementSpaceBeforeTest_2563, BlockElementReturnsProvidedSpaceBefore_2563) {
  // Create a Tagged PDF with a block /P element that has /SpaceBefore set to 12.0.
  const double expected = 12.0;
  const std::string pdf = BuildMinimalTaggedPdfWithSpaceBefore(expected);
  const std::string path = WriteTempPdfOrDie(pdf);
  ASSERT_FALSE(path.empty());

  PopplerDocument *doc = LoadDocumentFromPathOrDie(path);
  ASSERT_NE(doc, nullptr);

  PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
  ASSERT_NE(iter, nullptr);

  PopplerStructureElement *block = FindFirstElementMatching(iter, /*want_block=*/true);
  poppler_structure_element_iter_free(iter);

  ASSERT_NE(block, nullptr);
  EXPECT_TRUE(poppler_structure_element_is_block(block));

  const gdouble v = poppler_structure_element_get_space_before(block);
  ASSERT_FALSE(std::isnan(v));
  EXPECT_NEAR(v, expected, 1e-9);

  // Cleanup
  g_object_unref(doc);
  g_unlink(path.c_str());
  (void)block;
}

TEST(PopplerStructureElementSpaceBeforeTest_2563, BlockElementSupportsNegativeSpaceBefore_2563) {
  // Boundary-ish: ensure numeric attribute values (including negative) are surfaced as numbers.
  // This does not assume clamping behavior; it only checks the returned value matches the PDF value.
  const double expected = -3.5;
  const std::string pdf = BuildMinimalTaggedPdfWithSpaceBefore(expected);
  const std::string path = WriteTempPdfOrDie(pdf);
  ASSERT_FALSE(path.empty());

  PopplerDocument *doc = LoadDocumentFromPathOrDie(path);
  ASSERT_NE(doc, nullptr);

  PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
  ASSERT_NE(iter, nullptr);

  PopplerStructureElement *block = FindFirstElementMatching(iter, /*want_block=*/true);
  poppler_structure_element_iter_free(iter);

  ASSERT_NE(block, nullptr);
  EXPECT_TRUE(poppler_structure_element_is_block(block));

  const gdouble v = poppler_structure_element_get_space_before(block);
  ASSERT_FALSE(std::isnan(v));
  EXPECT_NEAR(v, expected, 1e-9);

  // Cleanup
  g_object_unref(doc);
  g_unlink(path.c_str());
  (void)block;
}