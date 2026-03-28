// File: poppler-annot-ink-set-draw-below-test_2133.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstring>
#include <string>
#include <vector>

namespace {

std::string BuildPdfWithTwoInkAnnots_2133() {
  // Build a minimal valid PDF with 1 page, empty contents, and 2 Ink annotations.
  // We compute xref offsets to keep the PDF well-formed for Poppler parsing.
  struct Obj_2133 {
    int num;
    std::string body;  // Must end with '\n' (we'll ensure).
  };

  std::vector<Obj_2133> objs;

  objs.push_back({1, "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"});
  objs.push_back({2, "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"});
  objs.push_back({6, "6 0 obj\n<< /Length 0 >>\nstream\n\nendstream\nendobj\n"});

  // Two Ink annots (objects 4 and 5)
  objs.push_back({4,
                  "4 0 obj\n"
                  "<< /Type /Annot\n"
                  "   /Subtype /Ink\n"
                  "   /Rect [10 10 100 100]\n"
                  "   /InkList [[10 10 90 90]]\n"
                  "   /Contents (ink1)\n"
                  ">>\n"
                  "endobj\n"});
  objs.push_back({5,
                  "5 0 obj\n"
                  "<< /Type /Annot\n"
                  "   /Subtype /Ink\n"
                  "   /Rect [20 20 110 110]\n"
                  "   /InkList [[20 20 100 100]]\n"
                  "   /Contents (ink2)\n"
                  ">>\n"
                  "endobj\n"});

  // Page object 3 references annots 4/5 and contents 6.
  objs.push_back({3,
                  "3 0 obj\n"
                  "<< /Type /Page\n"
                  "   /Parent 2 0 R\n"
                  "   /MediaBox [0 0 200 200]\n"
                  "   /Contents 6 0 R\n"
                  "   /Annots [4 0 R 5 0 R]\n"
                  ">>\n"
                  "endobj\n"});

  // Sort by object number (PDF readers don't require it, but xref building here assumes it).
  std::sort(objs.begin(), objs.end(), [](const Obj_2133& a, const Obj_2133& b) { return a.num < b.num; });

  std::string out;
  out += "%PDF-1.4\n";
  out += "%\xE2\xE3\xCF\xD3\n";

  // Record offsets for xref. PDF xref has entry 0 (free), then 1..maxobj.
  int max_obj = 0;
  for (const auto& o : objs) max_obj = std::max(max_obj, o.num);

  std::vector<long> offsets(static_cast<size_t>(max_obj + 1), -1);
  offsets[0] = 0;

  for (const auto& o : objs) {
    offsets[o.num] = static_cast<long>(out.size());
    out += o.body;
  }

  const long xref_pos = static_cast<long>(out.size());
  out += "xref\n";
  out += "0 " + std::to_string(max_obj + 1) + "\n";
  out += "0000000000 65535 f \n";
  for (int i = 1; i <= max_obj; ++i) {
    // All objects present in this test PDF.
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    out += buf;
  }

  out += "trailer\n";
  out += "<< /Size " + std::to_string(max_obj + 1) + " /Root 1 0 R >>\n";
  out += "startxref\n";
  out += std::to_string(xref_pos) + "\n";
  out += "%%EOF\n";
  return out;
}

struct InkAnnots_2133 {
  PopplerDocument* doc = nullptr;
  PopplerPage* page = nullptr;
  PopplerAnnotInk* ink1 = nullptr;
  PopplerAnnotInk* ink2 = nullptr;
};

InkAnnots_2133 LoadInkAnnotsFromPdf_2133() {
  InkAnnots_2133 r;

  std::string pdf = BuildPdfWithTwoInkAnnots_2133();
  GError* error = nullptr;

  r.doc = poppler_document_new_from_data(pdf.data(),
                                        static_cast<int>(pdf.size()),
                                        /*password=*/nullptr,
                                        &error);
  EXPECT_NE(r.doc, nullptr) << "Failed to create PopplerDocument: "
                            << (error ? error->message : "(no error)");
  if (!r.doc) {
    if (error) g_error_free(error);
    return r;
  }
  if (error) g_error_free(error);

  r.page = poppler_document_get_page(r.doc, 0);
  EXPECT_NE(r.page, nullptr);
  if (!r.page) return r;

  GList* mappings = poppler_page_get_annot_mapping(r.page);
  // Expect at least two annots from our PDF.
  EXPECT_NE(mappings, nullptr);

  // Find the first two ink annots.
  PopplerAnnotInk* found[2] = {nullptr, nullptr};
  int idx = 0;

  for (GList* it = mappings; it != nullptr; it = it->next) {
    auto* m = static_cast<PopplerAnnotMapping*>(it->data);
    if (!m || !m->annot) continue;
    if (POPPLER_IS_ANNOT_INK(m->annot)) {
      if (idx < 2) {
        found[idx] = POPPLER_ANNOT_INK(m->annot);
        // Hold refs beyond mapping lifetime.
        g_object_ref(found[idx]);
        ++idx;
      }
    }
  }

  poppler_page_free_annot_mapping(mappings);

  r.ink1 = found[0];
  r.ink2 = found[1];

  EXPECT_NE(r.ink1, nullptr);
  EXPECT_NE(r.ink2, nullptr);
  return r;
}

class PopplerAnnotInkSetDrawBelowTest_2133 : public ::testing::Test {
 protected:
  void TearDown() override {
    if (ink2_) g_object_unref(ink2_);
    if (ink1_) g_object_unref(ink1_);
    if (page_) g_object_unref(page_);
    if (doc_) g_object_unref(doc_);
  }

  void SetUp() override {
    auto loaded = LoadInkAnnotsFromPdf_2133();
    doc_ = loaded.doc;
    page_ = loaded.page;
    ink1_ = loaded.ink1;
    ink2_ = loaded.ink2;
  }

  PopplerDocument* doc_ = nullptr;
  PopplerPage* page_ = nullptr;
  PopplerAnnotInk* ink1_ = nullptr;
  PopplerAnnotInk* ink2_ = nullptr;
};

}  // namespace

TEST_F(PopplerAnnotInkSetDrawBelowTest_2133, ToggleUpdatesGetterForSingleAnnot_2133) {
  ASSERT_NE(ink1_, nullptr);

  // Do not assume the default; just toggle and verify observable change.
  const gboolean initial = poppler_annot_ink_get_draw_below(ink1_);
  poppler_annot_ink_set_draw_below(ink1_, initial ? FALSE : TRUE);
  EXPECT_EQ(poppler_annot_ink_get_draw_below(ink1_), initial ? FALSE : TRUE);

  poppler_annot_ink_set_draw_below(ink1_, initial);
  EXPECT_EQ(poppler_annot_ink_get_draw_below(ink1_), initial);
}

TEST_F(PopplerAnnotInkSetDrawBelowTest_2133, SettingTrueThenFalseIsReflected_2133) {
  ASSERT_NE(ink1_, nullptr);

  poppler_annot_ink_set_draw_below(ink1_, TRUE);
  EXPECT_EQ(poppler_annot_ink_get_draw_below(ink1_), TRUE);

  poppler_annot_ink_set_draw_below(ink1_, FALSE);
  EXPECT_EQ(poppler_annot_ink_get_draw_below(ink1_), FALSE);
}

TEST_F(PopplerAnnotInkSetDrawBelowTest_2133, DoesNotAffectOtherInkAnnotations_2133) {
  ASSERT_NE(ink1_, nullptr);
  ASSERT_NE(ink2_, nullptr);

  const gboolean before1 = poppler_annot_ink_get_draw_below(ink1_);
  const gboolean before2 = poppler_annot_ink_get_draw_below(ink2_);

  poppler_annot_ink_set_draw_below(ink1_, before1 ? FALSE : TRUE);

  EXPECT_EQ(poppler_annot_ink_get_draw_below(ink1_), before1 ? FALSE : TRUE);
  EXPECT_EQ(poppler_annot_ink_get_draw_below(ink2_), before2) << "Changing ink1 should not change ink2";
}

#if GTEST_HAS_DEATH_TEST
TEST(PopplerAnnotInkSetDrawBelowDeathTest_2133, NullptrAnnotDies_2133) {
  // Observable error case: the function dereferences the passed pointer via macros and accessors.
  // This test documents that passing nullptr is not supported.
  EXPECT_DEATH({ poppler_annot_ink_set_draw_below(nullptr, TRUE); }, ".*");
}
#endif