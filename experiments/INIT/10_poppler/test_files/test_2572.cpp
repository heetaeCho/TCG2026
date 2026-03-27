// poppler-structure-element-get-block-align-test.cpp
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <string>

namespace {

static std::string WriteTempPdfAndGetUri(const std::string &pdf_bytes) {
  GError *error = nullptr;

  gchar *tmp_name = nullptr;
  gint fd = g_file_open_tmp("poppler-structure-block-align-XXXXXX.pdf", &tmp_name, &error);
  if (fd < 0) {
    std::string msg = error ? error->message : "g_file_open_tmp failed";
    if (error)
      g_error_free(error);
    ADD_FAILURE() << msg;
    return std::string();
  }
  close(fd);

  if (!g_file_set_contents(tmp_name, pdf_bytes.data(), static_cast<gssize>(pdf_bytes.size()), &error)) {
    std::string msg = error ? error->message : "g_file_set_contents failed";
    if (error)
      g_error_free(error);
    g_remove(tmp_name);
    g_free(tmp_name);
    ADD_FAILURE() << msg;
    return std::string();
  }

  gchar *uri = g_filename_to_uri(tmp_name, nullptr, &error);
  if (!uri) {
    std::string msg = error ? error->message : "g_filename_to_uri failed";
    if (error)
      g_error_free(error);
    g_remove(tmp_name);
    g_free(tmp_name);
    ADD_FAILURE() << msg;
    return std::string();
  }

  // Note: Keep the temp file around for the duration of the test process.
  // (Poppler may read lazily.)
  g_free(tmp_name);

  std::string uri_str(uri);
  g_free(uri);
  return uri_str;
}

static PopplerDocument *OpenDocumentFromUriOrFail(const std::string &uri) {
  GError *error = nullptr;
  PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
  if (!doc) {
    std::string msg = error ? error->message : "poppler_document_new_from_file failed";
    if (error)
      g_error_free(error);
    ADD_FAILURE() << msg;
  }
  return doc;
}

static PopplerStructureElement *GetRootElementOrSkip(PopplerDocument *doc) {
  PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
  if (!iter) {
    GTEST_SKIP() << "Document has no structure tree (PopplerStructureElementIter is NULL).";
  }

  PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
  poppler_structure_element_iter_free(iter);

  if (!elem) {
    GTEST_SKIP() << "Structure tree root element is NULL.";
  }
  return elem;
}

// A minimal (but valid) PDF with a structure tree root and a single /P (paragraph) element
// bound to marked content MCID 0 on page 1, with a Layout attribute /BlockAlign /Middle.
static std::string BuildTaggedPdf_BlockAlignMiddle_Paragraph() {
  // NOTE: This is intentionally small; Poppler is the system under test.
  // The structure dictionary uses /A << /O /Layout /BlockAlign /Middle >>.
  return
      "%PDF-1.7\n"
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R /MarkInfo << /Marked true >> /StructTreeRoot 6 0 R >>\n"
      "endobj\n"
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n"
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
      "   /Resources << /Font << /F1 5 0 R >> >>\n"
      "   /Contents 4 0 R\n"
      "   /StructParents 0\n"
      ">>\n"
      "endobj\n"
      "4 0 obj\n"
      "<< /Length 97 >>\n"
      "stream\n"
      "/P << /MCID 0 >> BDC\n"
      "BT /F1 12 Tf 50 150 Td (Hello) Tj ET\n"
      "EMC\n"
      "endstream\n"
      "endobj\n"
      "5 0 obj\n"
      "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
      "endobj\n"
      "6 0 obj\n"
      "<< /Type /StructTreeRoot /K [7 0 R] /ParentTree 8 0 R /ParentTreeNextKey 1 >>\n"
      "endobj\n"
      "7 0 obj\n"
      "<< /Type /StructElem /S /P /P 6 0 R /Pg 3 0 R /K 0\n"
      "   /A << /O /Layout /BlockAlign /Middle >>\n"
      ">>\n"
      "endobj\n"
      "8 0 obj\n"
      "<< /Nums [0 [7 0 R]] >>\n"
      "endobj\n"
      "xref\n"
      "0 9\n"
      "0000000000 65535 f \n"
      "0000000010 00000 n \n"
      "0000000100 00000 n \n"
      "0000000157 00000 n \n"
      "0000000295 00000 n \n"
      "0000000443 00000 n \n"
      "0000000522 00000 n \n"
      "0000000617 00000 n \n"
      "0000000738 00000 n \n"
      "trailer\n"
      "<< /Size 9 /Root 1 0 R >>\n"
      "startxref\n"
      "780\n"
      "%%EOF\n";
}

// Same as above, but the single structure element is /Span (inline-level typically),
// still carrying a Layout attribute /BlockAlign /After. poppler_structure_element_get_block_align()
// should reject non-block elements and return the default enum value.
static std::string BuildTaggedPdf_BlockAlignAfter_Span() {
  return
      "%PDF-1.7\n"
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R /MarkInfo << /Marked true >> /StructTreeRoot 6 0 R >>\n"
      "endobj\n"
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n"
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
      "   /Resources << /Font << /F1 5 0 R >> >>\n"
      "   /Contents 4 0 R\n"
      "   /StructParents 0\n"
      ">>\n"
      "endobj\n"
      "4 0 obj\n"
      "<< /Length 100 >>\n"
      "stream\n"
      "/Span << /MCID 0 >> BDC\n"
      "BT /F1 12 Tf 50 150 Td (Hello) Tj ET\n"
      "EMC\n"
      "endstream\n"
      "endobj\n"
      "5 0 obj\n"
      "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
      "endobj\n"
      "6 0 obj\n"
      "<< /Type /StructTreeRoot /K [7 0 R] /ParentTree 8 0 R /ParentTreeNextKey 1 >>\n"
      "endobj\n"
      "7 0 obj\n"
      "<< /Type /StructElem /S /Span /P 6 0 R /Pg 3 0 R /K 0\n"
      "   /A << /O /Layout /BlockAlign /After >>\n"
      ">>\n"
      "endobj\n"
      "8 0 obj\n"
      "<< /Nums [0 [7 0 R]] >>\n"
      "endobj\n"
      "xref\n"
      "0 9\n"
      "0000000000 65535 f \n"
      "0000000010 00000 n \n"
      "0000000100 00000 n \n"
      "0000000157 00000 n \n"
      "0000000295 00000 n \n"
      "0000000446 00000 n \n"
      "0000000525 00000 n \n"
      "0000000620 00000 n \n"
      "0000000744 00000 n \n"
      "trailer\n"
      "<< /Size 9 /Root 1 0 R >>\n"
      "startxref\n"
      "786\n"
      "%%EOF\n";
}

} // namespace

TEST(PopplerStructureElementGetBlockAlignTest_2572, NullPointerReturnsDefault_2572) {
  // Observable behavior: g_return_val_if_fail(...) returns the default enum value.
  PopplerStructureBlockAlign align = poppler_structure_element_get_block_align(nullptr);
  EXPECT_EQ(align, POPPLER_STRUCTURE_BLOCK_ALIGN_BEFORE);
}

TEST(PopplerStructureElementGetBlockAlignTest_2572, BlockElementReturnsAValidEnumValue_2572) {
  const std::string uri = WriteTempPdfAndGetUri(BuildTaggedPdf_BlockAlignMiddle_Paragraph());
  ASSERT_FALSE(uri.empty());

  PopplerDocument *doc = OpenDocumentFromUriOrFail(uri);
  ASSERT_NE(doc, nullptr);

  PopplerStructureElement *root = GetRootElementOrSkip(doc);

  // The document we generated should have a block element at the root.
  EXPECT_TRUE(poppler_structure_element_is_block(root));

  // Normal operation: should return a meaningful value (here, /Middle from the Layout attribute).
  PopplerStructureBlockAlign align = poppler_structure_element_get_block_align(root);
  EXPECT_EQ(align, POPPLER_STRUCTURE_BLOCK_ALIGN_MIDDLE);

  g_object_unref(doc);

  // Best-effort cleanup for boxed types (if Poppler exposes it as boxed).
  // If Poppler uses a different ownership model, this is still safe in typical GLib conventions.
  g_boxed_free(poppler_structure_element_get_type(), root);
}

TEST(PopplerStructureElementGetBlockAlignTest_2572, NonBlockElementReturnsDefault_2572) {
  const std::string uri = WriteTempPdfAndGetUri(BuildTaggedPdf_BlockAlignAfter_Span());
  ASSERT_FALSE(uri.empty());

  PopplerDocument *doc = OpenDocumentFromUriOrFail(uri);
  ASSERT_NE(doc, nullptr);

  PopplerStructureElement *root = GetRootElementOrSkip(doc);

  // The root element is /Span, expected to be non-block.
  EXPECT_FALSE(poppler_structure_element_is_block(root));

  // Boundary/error observable through API: non-block elements cause default return.
  PopplerStructureBlockAlign align = poppler_structure_element_get_block_align(root);
  EXPECT_EQ(align, POPPLER_STRUCTURE_BLOCK_ALIGN_BEFORE);

  g_object_unref(doc);
  g_boxed_free(poppler_structure_element_get_type(), root);
}