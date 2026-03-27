// poppler_structure_element_get_line_height_test_2577.cc
#include <gtest/gtest.h>

#include <cmath>
#include <cstring>
#include <string>
#include <vector>

#include <glib.h>
#include <poppler.h>

namespace {

struct LogCapture {
  guint handler_id = 0;
  int critical_count = 0;

  static void Handler(const gchar* /*log_domain*/,
                      GLogLevelFlags log_level,
                      const gchar* /*message*/,
                      gpointer user_data) {
    auto* self = static_cast<LogCapture*>(user_data);
    if (log_level & G_LOG_LEVEL_CRITICAL) {
      self->critical_count++;
    }
  }

  void Install() {
    // Capture CRITICAL logs from any domain to avoid noisy stderr and to allow verification.
    handler_id = g_log_set_handler(nullptr, G_LOG_LEVEL_CRITICAL, &LogCapture::Handler, this);
  }

  void Uninstall() {
    if (handler_id != 0) {
      g_log_remove_handler(nullptr, handler_id);
      handler_id = 0;
    }
  }
};

static std::string BuildPdfWithXref(const std::vector<std::string>& objects,
                                   int root_obj_num,
                                   int info_obj_num = 0) {
  // objects is 1-based indexed conceptually: objects[i-1] is "i 0 obj ... endobj\n"
  std::string out;
  out += "%PDF-1.7\n";
  // Binary marker line (helps some parsers).
  out += "%\xE2\xE3\xCF\xD3\n";

  std::vector<long> offsets(objects.size() + 1, 0);  // offsets[0] is free entry

  for (size_t i = 0; i < objects.size(); ++i) {
    offsets[i + 1] = static_cast<long>(out.size());
    out += objects[i];
    if (out.empty() || out.back() != '\n') {
      out += "\n";
    }
  }

  const long xref_pos = static_cast<long>(out.size());
  out += "xref\n";
  out += "0 " + std::to_string(objects.size() + 1) + "\n";
  out += "0000000000 65535 f \n";
  for (size_t i = 1; i <= objects.size(); ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    out += buf;
  }

  out += "trailer\n";
  out += "<< /Size " + std::to_string(objects.size() + 1);
  out += " /Root " + std::to_string(root_obj_num) + " 0 R";
  if (info_obj_num > 0) {
    out += " /Info " + std::to_string(info_obj_num) + " 0 R";
  }
  out += " >>\n";
  out += "startxref\n";
  out += std::to_string(xref_pos) + "\n";
  out += "%%EOF\n";
  return out;
}

static std::string BuildTaggedPdf_LineHeights(double numeric_line_height, double boundary_line_height_zero) {
  // Creates a minimal tagged PDF with:
  // - 1 page
  // - StructTreeRoot with /K array containing:
  //     Span (LineHeight Normal)  -> MCID 0
  //     Span (LineHeight Auto)    -> MCID 1
  //     Span (LineHeight <numeric_line_height>) -> MCID 2
  //     Span (LineHeight 0)       -> MCID 3
  //     P (block-level paragraph) -> MCID 4  (used to test non-inline -> NaN)
  //
  // The content stream emits five marked-content sequences with those MCIDs.
  //
  // NOTE: The goal is to drive Poppler via public API only (black-box behavior).

  std::string content;
  content += "q\n";
  content += "BT\n";
  content += "/F1 12 Tf\n";
  content += "72 720 Td\n";

  auto emit_span = [&](int mcid, const char* text) {
    content += "/Span <</MCID " + std::to_string(mcid) + ">> BDC\n";
    content += "(";
    // Very small escaping: only escape \ and parens for our fixed literals.
    for (const char* p = text; *p; ++p) {
      if (*p == '\\' || *p == '(' || *p == ')') content += "\\";
      content += *p;
    }
    content += ") Tj\n";
    content += "T*\n";
    content += "EMC\n";
  };

  auto emit_p = [&](int mcid, const char* text) {
    content += "/P <</MCID " + std::to_string(mcid) + ">> BDC\n";
    content += "(";
    for (const char* p = text; *p; ++p) {
      if (*p == '\\' || *p == '(' || *p == ')') content += "\\";
      content += *p;
    }
    content += ") Tj\n";
    content += "T*\n";
    content += "EMC\n";
  };

  emit_span(0, "Hello-Normal");
  emit_span(1, "Hello-Auto");
  emit_span(2, "Hello-Numeric");
  emit_span(3, "Hello-Zero");
  emit_p(4, "Hello-Paragraph");

  content += "ET\n";
  content += "Q\n";

  const int content_len = static_cast<int>(content.size());

  std::vector<std::string> objs;
  objs.reserve(13);

  // 1 0 obj: Catalog
  objs.push_back(
      "1 0 obj\n"
      "<< /Type /Catalog\n"
      "   /Pages 2 0 R\n"
      "   /MarkInfo << /Marked true >>\n"
      "   /StructTreeRoot 3 0 R\n"
      ">>\n"
      "endobj\n");

  // 2 0 obj: Pages
  objs.push_back(
      "2 0 obj\n"
      "<< /Type /Pages\n"
      "   /Kids [4 0 R]\n"
      "   /Count 1\n"
      ">>\n"
      "endobj\n");

  // 3 0 obj: StructTreeRoot
  // ParentTree is 13 0 R
  // K array: [5 0 R 7 0 R 9 0 R 11 0 R 12 0 R]
  objs.push_back(
      "3 0 obj\n"
      "<< /Type /StructTreeRoot\n"
      "   /K [5 0 R 7 0 R 9 0 R 11 0 R 12 0 R]\n"
      "   /ParentTree 13 0 R\n"
      ">>\n"
      "endobj\n");

  // 4 0 obj: Page
  // StructParents 0 so ParentTree key is 0 and MCIDs map within that array.
  objs.push_back(
      "4 0 obj\n"
      "<< /Type /Page\n"
      "   /Parent 2 0 R\n"
      "   /MediaBox [0 0 612 792]\n"
      "   /Resources << /Font << /F1 6 0 R >> >>\n"
      "   /Contents 10 0 R\n"
      "   /StructParents 0\n"
      ">>\n"
      "endobj\n");

  // 5 0 obj: StructElem Span (LineHeight Normal) -> MCR 6
  objs.push_back(
      "5 0 obj\n"
      "<< /Type /StructElem\n"
      "   /S /Span\n"
      "   /P 3 0 R\n"
      "   /Pg 4 0 R\n"
      "   /A << /O /Layout /LineHeight /Normal >>\n"
      "   /K 6 0 R\n"
      ">>\n"
      "endobj\n");

  // 6 0 obj: Font
  objs.push_back(
      "6 0 obj\n"
      "<< /Type /Font\n"
      "   /Subtype /Type1\n"
      "   /BaseFont /Helvetica\n"
      ">>\n"
      "endobj\n");

  // 7 0 obj: StructElem Span (LineHeight Auto) -> MCR 8
  objs.push_back(
      "7 0 obj\n"
      "<< /Type /StructElem\n"
      "   /S /Span\n"
      "   /P 3 0 R\n"
      "   /Pg 4 0 R\n"
      "   /A << /O /Layout /LineHeight /Auto >>\n"
      "   /K 8 0 R\n"
      ">>\n"
      "endobj\n");

  // 8 0 obj: MCR for MCID 1
  objs.push_back(
      "8 0 obj\n"
      "<< /Type /MCR /Pg 4 0 R /MCID 1 >>\n"
      "endobj\n");

  // 9 0 obj: StructElem Span (LineHeight numeric) -> MCR 14 (we’ll use 9's /K as 14, but keep object numbers contiguous by placing MCRs now)
  // Instead, make MCR 9? We already used 9. We'll define Span numeric as obj 9 and MCR as obj 15 would complicate.
  // Keep contiguous: create numeric Span as obj 9 and its MCR as obj 16? Not needed; we can use MCR as obj 6? No.
  // We'll instead define MCRs for remaining in-place by allocating:
  //   obj 9: Span numeric uses /K 14 0 R (to be defined later)
  //   obj10: Contents
  //   obj11: Span zero uses /K 15 0 R
  //   obj12: P block uses /K 16 0 R
  //   obj13: ParentTree
  //   obj14: MCR for MCID 2
  //   obj15: MCR for MCID 3
  //   obj16: MCR for MCID 4
  //
  // That means we need 16 objects total; we'll append accordingly.

  {
    std::string o =
        "9 0 obj\n"
        "<< /Type /StructElem\n"
        "   /S /Span\n"
        "   /P 3 0 R\n"
        "   /Pg 4 0 R\n"
        "   /A << /O /Layout /LineHeight " +
        std::to_string(numeric_line_height) +
        " >>\n"
        "   /K 14 0 R\n"
        ">>\n"
        "endobj\n";
    objs.push_back(o);
  }

  // 10 0 obj: Contents stream
  {
    std::string o =
        "10 0 obj\n"
        "<< /Length " +
        std::to_string(content_len) +
        " >>\n"
        "stream\n" +
        content +
        "endstream\n"
        "endobj\n";
    objs.push_back(o);
  }

  // 11 0 obj: StructElem Span (LineHeight 0) -> MCR 15
  {
    std::string o =
        "11 0 obj\n"
        "<< /Type /StructElem\n"
        "   /S /Span\n"
        "   /P 3 0 R\n"
        "   /Pg 4 0 R\n"
        "   /A << /O /Layout /LineHeight " +
        std::to_string(boundary_line_height_zero) +
        " >>\n"
        "   /K 15 0 R\n"
        ">>\n"
        "endobj\n";
    objs.push_back(o);
  }

  // 12 0 obj: StructElem P (block-level) -> MCR 16
  objs.push_back(
      "12 0 obj\n"
      "<< /Type /StructElem\n"
      "   /S /P\n"
      "   /P 3 0 R\n"
      "   /Pg 4 0 R\n"
      "   /K 16 0 R\n"
      ">>\n"
      "endobj\n");

  // 13 0 obj: ParentTree (StructParents=0 -> this entry is an array indexed by MCID)
  // Nums: 0 [ (for MCID 0..4) 5 0 R, 7 0 R, 9 0 R, 11 0 R, 12 0 R ]
  objs.push_back(
      "13 0 obj\n"
      "<< /Nums [ 0 [ 5 0 R 7 0 R 9 0 R 11 0 R 12 0 R ] ] >>\n"
      "endobj\n");

  // 14 0 obj: MCR for MCID 2
  objs.push_back("14 0 obj\n<< /Type /MCR /Pg 4 0 R /MCID 2 >>\nendobj\n");
  // 15 0 obj: MCR for MCID 3
  objs.push_back("15 0 obj\n<< /Type /MCR /Pg 4 0 R /MCID 3 >>\nendobj\n");
  // 16 0 obj: MCR for MCID 4
  objs.push_back("16 0 obj\n<< /Type /MCR /Pg 4 0 R /MCID 4 >>\nendobj\n");

  // We forgot MCR for MCID 0. We can reuse obj 8? No, obj 8 is MCID 1. Add missing MCR by changing 5's /K.
  // Fix by making 5's /K point to a defined MCR object. We'll add MCR for MCID 0 as a new object 17,
  // but then we need to update earlier objects. Instead, simplest: repurpose obj 8 as MCID 0 and add obj 17 for MCID 1.
  // That would require re-numbering; avoid that by making 6 0 obj the MCR? But 6 is the font.
  //
  // Practical fix: swap roles:
  // - Use MCID 0's MCR as object 8 (update object 8 content)
  // - Use MCID 1's MCR as object 17 and update object 7 /K.
  //
  // Do that here by editing strings already added:
  // objs[7-1] is object 7; objs[8-1] is object 8.
  // But we already pushed object 8 as MCID 1. Replace it now.

  // Replace obj 8 (index 7) with MCID 0
  objs[7] =
      "8 0 obj\n"
      "<< /Type /MCR /Pg 4 0 R /MCID 0 >>\n"
      "endobj\n";

  // Update object 7 string to use /K 17 0 R instead of /K 8 0 R
  {
    std::string& span_auto = objs[6];  // obj 7 is index 6
    const std::string from = "   /K 8 0 R\n";
    const std::string to = "   /K 17 0 R\n";
    auto pos = span_auto.find(from);
    if (pos != std::string::npos) {
      span_auto.replace(pos, from.size(), to);
    }
  }

  // Add object 17: MCR for MCID 1
  objs.push_back("17 0 obj\n<< /Type /MCR /Pg 4 0 R /MCID 1 >>\nendobj\n");

  // Now the StructTreeRoot /K array references 5,7,9,11,12 (ok).
  // And each struct elem's /K references an MCR object:
  // 5->8 (MCID0), 7->17 (MCID1), 9->14 (MCID2), 11->15 (MCID3), 12->16 (MCID4)

  return BuildPdfWithXref(objs, /*root_obj_num=*/1);
}

static PopplerDocument* LoadDocFromDataOrFail(const std::string& pdf) {
  GError* error = nullptr;
  PopplerDocument* doc =
      poppler_document_new_from_data(pdf.data(), static_cast<int>(pdf.size()), /*password=*/nullptr, &error);
  if (!doc) {
    std::string msg = "Failed to load PDF: ";
    if (error && error->message) msg += error->message;
    if (error) g_error_free(error);
    ADD_FAILURE() << msg;
    return nullptr;
  }
  if (error) g_error_free(error);
  return doc;
}

static PopplerStructureElement* FindNthKind(PopplerDocument* doc,
                                           PopplerStructureElementKind kind,
                                           int n /*0-based*/) {
  PopplerStructureElementIter* iter = poppler_structure_element_iter_new(doc);
  if (!iter) return nullptr;

  int seen = 0;
  PopplerStructureElement* result = nullptr;

  // Depth-first traversal using the public iterator API.
  std::function<void(PopplerStructureElementIter*)> walk = [&](PopplerStructureElementIter* it) {
    if (!it || result) return;

    do {
      PopplerStructureElement* el = poppler_structure_element_iter_get_element(it);
      if (el) {
        if (poppler_structure_element_get_kind(el) == kind) {
          if (seen == n) {
            result = el;  // transfer full per API docs; keep it.
            return;
          }
          seen++;
        }
        g_object_unref(el);
      }

      PopplerStructureElementIter* child = poppler_structure_element_iter_get_child(it);
      if (child) {
        walk(child);
        poppler_structure_element_iter_free(child);
        if (result) return;
      }
    } while (poppler_structure_element_iter_next(it));
  };

  walk(iter);
  poppler_structure_element_iter_free(iter);

  return result;  // caller must g_object_unref if non-null
}

class PopplerStructureElementLineHeightTest_2577 : public ::testing::Test {
 protected:
  void SetUp() override { logs_.Install(); }
  void TearDown() override { logs_.Uninstall(); }

  LogCapture logs_;
};

TEST_F(PopplerStructureElementLineHeightTest_2577, ReturnsMinusOneForNormal_2577) {
  const std::string pdf = BuildTaggedPdf_LineHeights(/*numeric=*/2.5, /*zero=*/0.0);
  PopplerDocument* doc = LoadDocFromDataOrFail(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerStructureElement* span0 = FindNthKind(doc, POPPLER_STRUCTURE_ELEMENT_SPAN, 0);
  ASSERT_NE(span0, nullptr);

  const double lh = poppler_structure_element_get_line_height(span0);
  EXPECT_DOUBLE_EQ(lh, -1.0);

  g_object_unref(span0);
  g_object_unref(doc);
}

TEST_F(PopplerStructureElementLineHeightTest_2577, ReturnsMinusOneForAuto_2577) {
  const std::string pdf = BuildTaggedPdf_LineHeights(/*numeric=*/2.5, /*zero=*/0.0);
  PopplerDocument* doc = LoadDocFromDataOrFail(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerStructureElement* span1 = FindNthKind(doc, POPPLER_STRUCTURE_ELEMENT_SPAN, 1);
  ASSERT_NE(span1, nullptr);

  const double lh = poppler_structure_element_get_line_height(span1);
  EXPECT_DOUBLE_EQ(lh, -1.0);

  g_object_unref(span1);
  g_object_unref(doc);
}

TEST_F(PopplerStructureElementLineHeightTest_2577, ReturnsNumericLineHeightWhenDefined_2577) {
  const std::string pdf = BuildTaggedPdf_LineHeights(/*numeric=*/2.5, /*zero=*/0.0);
  PopplerDocument* doc = LoadDocFromDataOrFail(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerStructureElement* span2 = FindNthKind(doc, POPPLER_STRUCTURE_ELEMENT_SPAN, 2);
  ASSERT_NE(span2, nullptr);

  const double lh = poppler_structure_element_get_line_height(span2);
  EXPECT_DOUBLE_EQ(lh, 2.5);

  g_object_unref(span2);
  g_object_unref(doc);
}

TEST_F(PopplerStructureElementLineHeightTest_2577, Boundary_AllowsZeroLineHeightValue_2577) {
  // Boundary: explicit /LineHeight 0 should be returned as-is (observable behavior).
  const std::string pdf = BuildTaggedPdf_LineHeights(/*numeric=*/2.5, /*zero=*/0.0);
  PopplerDocument* doc = LoadDocFromDataOrFail(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerStructureElement* span3 = FindNthKind(doc, POPPLER_STRUCTURE_ELEMENT_SPAN, 3);
  ASSERT_NE(span3, nullptr);

  const double lh = poppler_structure_element_get_line_height(span3);
  EXPECT_DOUBLE_EQ(lh, 0.0);

  g_object_unref(span3);
  g_object_unref(doc);
}

TEST_F(PopplerStructureElementLineHeightTest_2577, NonInlineElementReturnsNaNAndLogsCritical_2577) {
  const std::string pdf = BuildTaggedPdf_LineHeights(/*numeric=*/2.5, /*zero=*/0.0);
  PopplerDocument* doc = LoadDocFromDataOrFail(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerStructureElement* p = FindNthKind(doc, POPPLER_STRUCTURE_ELEMENT_P, 0);
  ASSERT_NE(p, nullptr);

  const int before = logs_.critical_count;
  const double lh = poppler_structure_element_get_line_height(p);

  EXPECT_TRUE(std::isnan(lh));
  EXPECT_GE(logs_.critical_count, before + 1);

  g_object_unref(p);
  g_object_unref(doc);
}

TEST_F(PopplerStructureElementLineHeightTest_2577, NullElementReturnsNaNAndLogsCritical_2577) {
  const int before = logs_.critical_count;
  const double lh = poppler_structure_element_get_line_height(nullptr);

  EXPECT_TRUE(std::isnan(lh));
  EXPECT_GE(logs_.critical_count, before + 1);
}

}  // namespace