// File: poppler-structure-element-test-2522.cc
#include <gtest/gtest.h>

#include <poppler.h>
#include <glib.h>

#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace {

std::string Pad10(uint64_t v) {
  std::ostringstream oss;
  oss << std::setw(10) << std::setfill('0') << v;
  return oss.str();
}

struct PdfObj {
  int num;
  std::string body;  // must include trailing newline(s) as needed
};

std::string BuildPdfFromObjects(const std::vector<PdfObj>& objs, int size, int root_obj_num) {
  std::string pdf;
  pdf.reserve(4096);

  // PDF header + binary comment
  pdf += "%PDF-1.7\n";
  pdf += "%\xE2\xE3\xCF\xD3\n";

  // xref offsets (index 0 is the free object)
  std::vector<uint64_t> offsets(size, 0);

  for (const auto& o : objs) {
    if (o.num <= 0 || o.num >= size) continue;
    offsets[o.num] = static_cast<uint64_t>(pdf.size());
    pdf += std::to_string(o.num) + " 0 obj\n";
    pdf += o.body;
    if (!pdf.empty() && pdf.back() != '\n') pdf += "\n";
    pdf += "endobj\n";
  }

  const uint64_t xref_pos = static_cast<uint64_t>(pdf.size());
  pdf += "xref\n";
  pdf += "0 " + std::to_string(size) + "\n";
  pdf += "0000000000 65535 f \n";
  for (int i = 1; i < size; ++i) {
    pdf += Pad10(offsets[i]) + " 00000 n \n";
  }

  pdf += "trailer\n";
  pdf += "<< /Size " + std::to_string(size) + " /Root " + std::to_string(root_obj_num) + " 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_pos) + "\n";
  pdf += "%%EOF\n";

  return pdf;
}

// Builds a minimal Tagged PDF with:
// - StructTreeRoot and ParentTree
// - A /P structure element (MCID 0) optionally with /A << /TextAlign /Center >>
// - A /Span structure element (MCID 1) optionally with /A << /BaselineShift 10 >>
// - One page content stream containing marked-content sequences for MCID 0 and 1.
std::string BuildTaggedPdf(bool set_text_align_center, bool set_baseline_shift_10) {
  // Content stream with two marked-content sequences and some text.
  // Use tag names matching the structure element /S entries: /P and /Span.
  const std::string stream =
      "BT\n"
      "/F1 12 Tf\n"
      "72 720 Td\n"
      "/P <</MCID 0>> BDC\n"
      "(Hello) Tj\n"
      "EMC\n"
      "0 -14 Td\n"
      "/Span <</MCID 1>> BDC\n"
      "(World) Tj\n"
      "EMC\n"
      "ET\n";

  std::ostringstream contents_obj;
  contents_obj << "<< /Length " << stream.size() << " >>\n"
               << "stream\n"
               << stream
               << "endstream\n";

  std::ostringstream structroot_obj;
  // StructTreeRoot /K is an array of top-level structure elements (4 and 9).
  // ParentTree maps the page's /StructParents index (0) to an array of struct elems.
  structroot_obj
      << "<< /Type /StructTreeRoot\n"
      << "   /K [ 4 0 R 9 0 R ]\n"
      << "   /ParentTree 7 0 R\n"
      << ">>\n";

  std::ostringstream parenttree_obj;
  parenttree_obj << "<< /Nums [ 0 [ 4 0 R 9 0 R ] ] >>\n";

  std::ostringstream struct_p_obj;
  struct_p_obj << "<< /Type /StructElem\n"
               << "   /S /P\n"
               << "   /P 2 0 R\n"
               << "   /Pg 5 0 R\n"
               << "   /K 0\n";
  if (set_text_align_center) {
    struct_p_obj << "   /A << /TextAlign /Center >>\n";
  }
  struct_p_obj << ">>\n";

  std::ostringstream struct_span_obj;
  struct_span_obj << "<< /Type /StructElem\n"
                  << "   /S /Span\n"
                  << "   /P 2 0 R\n"
                  << "   /Pg 5 0 R\n"
                  << "   /K 1\n";
  if (set_baseline_shift_10) {
    struct_span_obj << "   /A << /BaselineShift 10 >>\n";
  }
  struct_span_obj << ">>\n";

  std::ostringstream catalog_obj;
  catalog_obj << "<< /Type /Catalog\n"
              << "   /Pages 3 0 R\n"
              << "   /StructTreeRoot 2 0 R\n"
              << ">>\n";

  std::ostringstream pages_obj;
  pages_obj << "<< /Type /Pages /Kids [ 5 0 R ] /Count 1 >>\n";

  std::ostringstream page_obj;
  page_obj << "<< /Type /Page\n"
           << "   /Parent 3 0 R\n"
           << "   /MediaBox [ 0 0 612 792 ]\n"
           << "   /Contents 6 0 R\n"
           << "   /Resources << /Font << /F1 8 0 R >> >>\n"
           << "   /StructParents 0\n"
           << ">>\n";

  std::ostringstream font_obj;
  font_obj << "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n";

  // Objects: 1..9 used, so /Size = 10.
  std::vector<PdfObj> objs = {
      {1, catalog_obj.str()},
      {2, structroot_obj.str()},
      {3, pages_obj.str()},
      {4, struct_p_obj.str()},
      {5, page_obj.str()},
      {6, contents_obj.str()},
      {7, parenttree_obj.str()},
      {8, font_obj.str()},
      {9, struct_span_obj.str()},
  };

  return BuildPdfFromObjects(objs, /*size=*/10, /*root_obj_num=*/1);
}

// Builds an untagged PDF (no /StructTreeRoot).
std::string BuildUntaggedPdf() {
  const std::string stream =
      "BT\n"
      "/F1 12 Tf\n"
      "72 720 Td\n"
      "(Hello) Tj\n"
      "ET\n";

  std::ostringstream contents_obj;
  contents_obj << "<< /Length " << stream.size() << " >>\n"
               << "stream\n"
               << stream
               << "endstream\n";

  std::ostringstream catalog_obj;
  catalog_obj << "<< /Type /Catalog /Pages 2 0 R >>\n";

  std::ostringstream pages_obj;
  pages_obj << "<< /Type /Pages /Kids [ 3 0 R ] /Count 1 >>\n";

  std::ostringstream page_obj;
  page_obj << "<< /Type /Page\n"
           << "   /Parent 2 0 R\n"
           << "   /MediaBox [ 0 0 612 792 ]\n"
           << "   /Contents 4 0 R\n"
           << "   /Resources << /Font << /F1 5 0 R >> >>\n"
           << ">>\n";

  std::ostringstream font_obj;
  font_obj << "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n";

  // Objects 1..5 used, so /Size = 6.
  std::vector<PdfObj> objs = {
      {1, catalog_obj.str()},
      {2, pages_obj.str()},
      {3, page_obj.str()},
      {4, contents_obj.str()},
      {5, font_obj.str()},
  };

  return BuildPdfFromObjects(objs, /*size=*/6, /*root_obj_num=*/1);
}

struct DocAndIter {
  PopplerDocument* doc = nullptr;
  PopplerStructureElementIter* iter = nullptr;
};

DocAndIter LoadDocAndRootIter(const std::string& pdf_bytes) {
  DocAndIter out;
  GError* error = nullptr;

  out.doc = poppler_document_new_from_data(pdf_bytes.data(),
                                           static_cast<int>(pdf_bytes.size()),
                                           /*password=*/nullptr,
                                           &error);
  EXPECT_EQ(error, nullptr) << (error ? error->message : "");
  EXPECT_NE(out.doc, nullptr);
  if (!out.doc) {
    if (error) g_error_free(error);
    return out;
  }

  out.iter = poppler_structure_element_iter_new(out.doc);
  return out;
}

PopplerStructureElement* FindFirstByKind(PopplerStructureElementIter* iter,
                                        PopplerStructureElementKind kind) {
  if (!iter) return nullptr;
  PopplerStructureElement* found = nullptr;

  // Iterate over siblings at this level.
  do {
    PopplerStructureElement* elem = poppler_structure_element_iter_get_element(iter);  // transfer full
    if (elem && poppler_structure_element_get_kind(elem) == kind) {
      found = elem;  // keep ownership
      break;
    }
    if (elem) g_object_unref(elem);
  } while (poppler_structure_element_iter_next(iter));

  return found;
}

class PopplerStructureElementTest_2522 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Ensure GLib warnings don't leak across tests.
  }
};

}  // namespace

TEST_F(PopplerStructureElementTest_2522, DefaultValuesWhenAttributesMissing_2522) {
  // This test exercises the behavior driven by attr_value_or_default():
  // when an attribute isn't present on the underlying StructElement, Poppler should
  // behave as if the default value (Attribute::getDefaultValue) were used.
  const std::string pdf = BuildTaggedPdf(/*set_text_align_center=*/false,
                                         /*set_baseline_shift_10=*/false);
  DocAndIter di = LoadDocAndRootIter(pdf);
  ASSERT_NE(di.doc, nullptr);
  ASSERT_NE(di.iter, nullptr);

  // Find a block element (/P) and verify TextAlign defaults to Start.
  PopplerStructureElement* p = FindFirstByKind(di.iter, POPPLER_STRUCTURE_ELEMENT_P);
  ASSERT_NE(p, nullptr);

  // Default for TextAlign in Poppler's core mapping is "Start". :contentReference[oaicite:0]{index=0}
  EXPECT_EQ(poppler_structure_element_get_text_align(p), POPPLER_STRUCTURE_TEXT_ALIGN_START);

  g_object_unref(p);

  // Restart iteration to find /Span (since FindFirstByKind advanced iter).
  poppler_structure_element_iter_free(di.iter);
  di.iter = poppler_structure_element_iter_new(di.doc);
  ASSERT_NE(di.iter, nullptr);

  PopplerStructureElement* span = FindFirstByKind(di.iter, POPPLER_STRUCTURE_ELEMENT_SPAN);
  ASSERT_NE(span, nullptr);

  // Default for BaselineShift in Poppler's core mapping is "Zero" (numeric 0). :contentReference[oaicite:1]{index=1}
  EXPECT_DOUBLE_EQ(poppler_structure_element_get_baseline_shift(span), 0.0);

  g_object_unref(span);
  poppler_structure_element_iter_free(di.iter);
  g_object_unref(di.doc);
}

TEST_F(PopplerStructureElementTest_2522, UsesSpecifiedAttributeValues_2522) {
  // When the attribute is present, attr_value_or_default() should return that value
  // (via Attribute::getValue()), not the default.
  const std::string pdf = BuildTaggedPdf(/*set_text_align_center=*/true,
                                         /*set_baseline_shift_10=*/true);
  DocAndIter di = LoadDocAndRootIter(pdf);
  ASSERT_NE(di.doc, nullptr);
  ASSERT_NE(di.iter, nullptr);

  PopplerStructureElement* p = FindFirstByKind(di.iter, POPPLER_STRUCTURE_ELEMENT_P);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(poppler_structure_element_get_text_align(p), POPPLER_STRUCTURE_TEXT_ALIGN_CENTER);
  g_object_unref(p);

  // Restart iteration to find /Span
  poppler_structure_element_iter_free(di.iter);
  di.iter = poppler_structure_element_iter_new(di.doc);
  ASSERT_NE(di.iter, nullptr);

  PopplerStructureElement* span = FindFirstByKind(di.iter, POPPLER_STRUCTURE_ELEMENT_SPAN);
  ASSERT_NE(span, nullptr);
  EXPECT_DOUBLE_EQ(poppler_structure_element_get_baseline_shift(span), 10.0);
  g_object_unref(span);

  poppler_structure_element_iter_free(di.iter);
  g_object_unref(di.doc);
}

TEST_F(PopplerStructureElementTest_2522, IterNewReturnsNullWithoutStructureTree_2522) {
  // Observable error case: for documents without a structure tree, the root iterator is NULL. :contentReference[oaicite:2]{index=2}
  const std::string pdf = BuildUntaggedPdf();
  GError* error = nullptr;

  PopplerDocument* doc = poppler_document_new_from_data(pdf.data(),
                                                        static_cast<int>(pdf.size()),
                                                        /*password=*/nullptr,
                                                        &error);
  ASSERT_EQ(error, nullptr) << (error ? error->message : "");
  ASSERT_NE(doc, nullptr);

  PopplerStructureElementIter* iter = poppler_structure_element_iter_new(doc);
  EXPECT_EQ(iter, nullptr);

  if (iter) poppler_structure_element_iter_free(iter);
  g_object_unref(doc);
}