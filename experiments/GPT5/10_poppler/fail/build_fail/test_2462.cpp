// poppler-page-remove-annot-test_2462.cc
//
// Unit tests for:
//   void poppler_page_remove_annot(PopplerPage *page, PopplerAnnot *annot)
//
// Constraints honored:
// - Treat implementation as black box
// - Test only observable behavior through public API
// - Verify g_return_if_fail error cases via GLib log expectations
// - No access to private/internal state

#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

#include <cstddef>
#include <cstdio>
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace {

struct GObjectDeleter {
  void operator()(gpointer p) const {
    if (p) {
      g_object_unref(p);
    }
  }
};
template <typename T>
using GObjectPtr = std::unique_ptr<T, GObjectDeleter>;

struct GErrorDeleter {
  void operator()(GError *e) const {
    if (e) {
      g_error_free(e);
    }
  }
};
using GErrorPtr = std::unique_ptr<GError, GErrorDeleter>;

static std::string ToXrefLine(std::size_t off, bool in_use) {
  char buf[32];
  // PDF xref: 10-digit offset, 5-digit generation, 'n'/'f'
  // generation is 00000 for in-use, 65535 for free entry 0.
  std::snprintf(buf, sizeof(buf), "%010zu %05d %c \n", off, in_use ? 0 : 65535, in_use ? 'n' : 'f');
  return std::string(buf);
}

static std::string BuildMinimalPdfWithOptionalTextAnnot(bool with_annot) {
  // Build a small valid PDF with 1 page and optionally 1 /Text annotation.
  //
  // Objects:
  //  1 0 Catalog
  //  2 0 Pages
  //  3 0 Page (optionally /Annots [5 0 R])
  //  4 0 Contents (empty stream)
  //  5 0 Annot (if enabled)
  //
  // We compute object offsets and emit an xref table accordingly.

  std::ostringstream out;
  out << "%PDF-1.4\n";

  std::vector<std::size_t> offsets;  // offsets[0] corresponds to object 1.
  offsets.reserve(with_annot ? 5 : 4);

  auto emit_obj = [&](int obj_num, const std::string &body) {
    offsets.push_back(static_cast<std::size_t>(out.tellp()));
    out << obj_num << " 0 obj\n" << body << "\nendobj\n";
  };

  emit_obj(1, "<< /Type /Catalog /Pages 2 0 R >>");
  emit_obj(2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>");

  {
    std::ostringstream page;
    page << "<< /Type /Page /Parent 2 0 R "
         << "/MediaBox [0 0 200 200] "
         << "/Resources << >> "
         << "/Contents 4 0 R ";
    if (with_annot) {
      page << "/Annots [5 0 R] ";
    }
    page << ">>";
    emit_obj(3, page.str());
  }

  // Empty content stream
  emit_obj(4, "<< /Length 0 >>\nstream\n\nendstream");

  if (with_annot) {
    emit_obj(5, "<< /Type /Annot /Subtype /Text /Rect [20 20 40 40] /Contents (Note) >>");
  }

  const std::size_t xref_offset = static_cast<std::size_t>(out.tellp());

  const int num_objects = with_annot ? 5 : 4;
  out << "xref\n";
  out << "0 " << (num_objects + 1) << "\n";
  out << ToXrefLine(0, /*in_use=*/false);  // obj 0 free

  for (int i = 0; i < num_objects; ++i) {
    out << ToXrefLine(offsets[static_cast<std::size_t>(i)], /*in_use=*/true);
  }

  out << "trailer\n";
  out << "<< /Size " << (num_objects + 1) << " /Root 1 0 R >>\n";
  out << "startxref\n";
  out << xref_offset << "\n";
  out << "%%EOF\n";

  return out.str();
}

static GObjectPtr<PopplerDocument> LoadDocFromDataOrSkip(const std::string &pdf_data) {
  GError *err_raw = nullptr;
  PopplerDocument *doc =
      poppler_document_new_from_data(pdf_data.data(),
                                     static_cast<int>(pdf_data.size()),
                                     /*password=*/nullptr,
                                     &err_raw);
  GErrorPtr err(err_raw);

  if (!doc) {
    // If Poppler build options forbid new_from_data or parsing fails, skip.
    GTEST_SKIP() << "poppler_document_new_from_data failed: "
                 << (err ? err->message : "unknown error");
  }
  return GObjectPtr<PopplerDocument>(doc);
}

static GObjectPtr<PopplerPage> GetFirstPageOrSkip(PopplerDocument *doc) {
  if (!doc) {
    GTEST_SKIP() << "Document is null";
  }
  PopplerPage *page = poppler_document_get_page(doc, 0);
  if (!page) {
    GTEST_SKIP() << "Failed to load page 0 from document";
  }
  return GObjectPtr<PopplerPage>(page);
}

static std::vector<PopplerAnnotMapping *> GetAnnotMappings(PopplerPage *page) {
  std::vector<PopplerAnnotMapping *> mappings;

  // This API exists in Poppler GLib: returns a GList of PopplerAnnotMapping*.
  GList *list = poppler_page_get_annot_mapping(page);
  for (GList *l = list; l; l = l->next) {
    mappings.push_back(static_cast<PopplerAnnotMapping *>(l->data));
  }
  // Must free with poppler_page_free_annot_mapping (also frees list nodes).
  poppler_page_free_annot_mapping(list);
  return mappings;
}

static void ExpectCriticalMessageContaining(const char *substr) {
  // GLib usually logs something like:
  // "poppler_page_remove_annot: assertion 'POPPLER_IS_PAGE (page)' failed"
  g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*assertion*failed*");
  (void)substr;  // substring matching is fuzzy with wildcards; we still call as a semantic helper
}

class PopplerPageRemoveAnnotTest_2462 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Nothing required; tests use g_test_expect_message directly for log checking.
  }
};

}  // namespace

TEST_F(PopplerPageRemoveAnnotTest_2462, RemovesExistingAnnotFromPage_2462) {
  const std::string pdf = BuildMinimalPdfWithOptionalTextAnnot(/*with_annot=*/true);
  auto doc = LoadDocFromDataOrSkip(pdf);
  auto page = GetFirstPageOrSkip(doc.get());

  const auto before = GetAnnotMappings(page.get());
  ASSERT_EQ(before.size(), 1u) << "Test PDF should contain exactly one annotation";

  PopplerAnnot *annot = before[0]->annot;
  ASSERT_NE(annot, nullptr);

  // Remove and verify observable effect (annotation list changes).
  poppler_page_remove_annot(page.get(), annot);

  const auto after = GetAnnotMappings(page.get());
  EXPECT_EQ(after.size(), 0u) << "Annotation should be removed from the page";
}

TEST_F(PopplerPageRemoveAnnotTest_2462, RemovingSameAnnotTwiceDoesNotCrash_2462) {
  const std::string pdf = BuildMinimalPdfWithOptionalTextAnnot(/*with_annot=*/true);
  auto doc = LoadDocFromDataOrSkip(pdf);
  auto page = GetFirstPageOrSkip(doc.get());

  const auto mappings = GetAnnotMappings(page.get());
  ASSERT_EQ(mappings.size(), 1u);

  PopplerAnnot *annot = mappings[0]->annot;
  ASSERT_NE(annot, nullptr);

  // Hold a reference so the PopplerAnnot remains valid for the second call even if
  // the page drops its internal reference after removal.
  g_object_ref(annot);

  poppler_page_remove_annot(page.get(), annot);
  poppler_page_remove_annot(page.get(), annot);

  const auto after = GetAnnotMappings(page.get());
  EXPECT_EQ(after.size(), 0u);

  g_object_unref(annot);
}

TEST_F(PopplerPageRemoveAnnotTest_2462, NullPageTriggersCriticalAndReturns_2462) {
  const std::string pdf = BuildMinimalPdfWithOptionalTextAnnot(/*with_annot=*/true);
  auto doc = LoadDocFromDataOrSkip(pdf);
  auto page = GetFirstPageOrSkip(doc.get());

  const auto mappings = GetAnnotMappings(page.get());
  ASSERT_EQ(mappings.size(), 1u);
  PopplerAnnot *annot = mappings[0]->annot;
  ASSERT_NE(annot, nullptr);

  // Expect g_return_if_fail(POPPLER_IS_PAGE(page)) to log CRITICAL and return.
  g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_PAGE*");
  poppler_page_remove_annot(nullptr, annot);
  g_test_assert_expected_messages();
}

TEST_F(PopplerPageRemoveAnnotTest_2462, NullAnnotTriggersCriticalAndReturns_2462) {
  const std::string pdf = BuildMinimalPdfWithOptionalTextAnnot(/*with_annot=*/true);
  auto doc = LoadDocFromDataOrSkip(pdf);
  auto page = GetFirstPageOrSkip(doc.get());

  // Expect g_return_if_fail(POPPLER_IS_ANNOT(annot)) to log CRITICAL and return.
  g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT*");
  poppler_page_remove_annot(page.get(), nullptr);
  g_test_assert_expected_messages();
}

TEST_F(PopplerPageRemoveAnnotTest_2462, WrongTypeForPageTriggersCritical_2462) {
  const std::string pdf = BuildMinimalPdfWithOptionalTextAnnot(/*with_annot=*/true);
  auto doc = LoadDocFromDataOrSkip(pdf);
  auto page = GetFirstPageOrSkip(doc.get());

  const auto mappings = GetAnnotMappings(page.get());
  ASSERT_EQ(mappings.size(), 1u);
  PopplerAnnot *annot = mappings[0]->annot;
  ASSERT_NE(annot, nullptr);

  // Pass a plain GObject* as PopplerPage* to trigger POPPLER_IS_PAGE failure.
  GObject *not_a_page = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_a_page, nullptr);

  g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_PAGE*");
  poppler_page_remove_annot(reinterpret_cast<PopplerPage *>(not_a_page), annot);
  g_test_assert_expected_messages();

  g_object_unref(not_a_page);
}

TEST_F(PopplerPageRemoveAnnotTest_2462, WrongTypeForAnnotTriggersCritical_2462) {
  const std::string pdf = BuildMinimalPdfWithOptionalTextAnnot(/*with_annot=*/true);
  auto doc = LoadDocFromDataOrSkip(pdf);
  auto page = GetFirstPageOrSkip(doc.get());

  // Pass a plain GObject* as PopplerAnnot* to trigger POPPLER_IS_ANNOT failure.
  GObject *not_an_annot = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_an_annot, nullptr);

  g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT*");
  poppler_page_remove_annot(page.get(), reinterpret_cast<PopplerAnnot *>(not_an_annot));
  g_test_assert_expected_messages();

  g_object_unref(not_an_annot);
}

TEST_F(PopplerPageRemoveAnnotTest_2462, RemovingAnnotFromPageWithNoAnnotsIsNoOp_2462) {
  // Boundary: page has no /Annots array. We still need a valid PopplerAnnot to call
  // the function, so we load a second doc to obtain an annot object.
  const std::string pdf_no = BuildMinimalPdfWithOptionalTextAnnot(/*with_annot=*/false);
  auto doc_no = LoadDocFromDataOrSkip(pdf_no);
  auto page_no = GetFirstPageOrSkip(doc_no.get());

  const auto before_no = GetAnnotMappings(page_no.get());
  ASSERT_EQ(before_no.size(), 0u);

  const std::string pdf_yes = BuildMinimalPdfWithOptionalTextAnnot(/*with_annot=*/true);
  auto doc_yes = LoadDocFromDataOrSkip(pdf_yes);
  auto page_yes = GetFirstPageOrSkip(doc_yes.get());
  const auto mappings_yes = GetAnnotMappings(page_yes.get());
  ASSERT_EQ(mappings_yes.size(), 1u);
  PopplerAnnot *foreign_annot = mappings_yes[0]->annot;
  ASSERT_NE(foreign_annot, nullptr);

  // The observable requirement here is simply: does not crash, and page_no still has no annots.
  poppler_page_remove_annot(page_no.get(), foreign_annot);

  const auto after_no = GetAnnotMappings(page_no.get());
  EXPECT_EQ(after_no.size(), 0u);
}