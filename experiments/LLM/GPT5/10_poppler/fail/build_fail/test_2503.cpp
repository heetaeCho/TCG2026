// File: poppler-page-get-text-attributes-test_2503.cc
//
// Unit tests for poppler_page_get_text_attributes()
// Interface under test (from ./TestProjects/poppler/glib/poppler-page.cc):
//   GList *poppler_page_get_text_attributes(PopplerPage *page);
//
// Constraints respected:
// - Treat implementation as black box
// - Test only observable behavior via public API
// - No private state access
// - Include normal/boundary/error cases

#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>  // poppler-glib public API

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

// The function under test is provided by the codebase.
extern "C" {
GList *poppler_page_get_text_attributes(PopplerPage *page);
}

namespace {

struct GErrorDeleter {
  void operator()(GError* e) const {
    if (e) g_error_free(e);
  }
};
using GErrorPtr = std::unique_ptr<GError, GErrorDeleter>;

struct GObjectUnrefDeleter {
  void operator()(gpointer p) const {
    if (p) g_object_unref(p);
  }
};
template <typename T>
using GObjPtr = std::unique_ptr<T, GObjectUnrefDeleter>;

static std::string Pad10(uint32_t off) {
  std::ostringstream oss;
  oss << std::setw(10) << std::setfill('0') << off;
  return oss.str();
}

// Build a minimal PDF with one page. If text is empty, content stream is empty.
// MediaBox is [0 0 media_w media_h]
static std::string BuildMinimalPdfOnePage(const std::string& text, int media_w = 200, int media_h = 200) {
  // Content stream: draw text using Helvetica (Type1).
  std::string stream;
  if (!text.empty()) {
    // Keep it simple; escape only parentheses and backslash.
    std::string escaped;
    escaped.reserve(text.size());
    for (char c : text) {
      if (c == '(' || c == ')' || c == '\\') escaped.push_back('\\');
      escaped.push_back(c);
    }
    stream = "BT /F1 24 Tf 10 100 Td (" + escaped + ") Tj ET\n";
  }

  // Objects (1-based): Catalog, Pages, Page, Contents, Font
  std::vector<std::string> objs;
  objs.reserve(5);

  objs.push_back("1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");
  objs.push_back("2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n");

  {
    std::ostringstream page;
    page << "3 0 obj\n<< /Type /Page /Parent 2 0 R "
         << "/MediaBox [0 0 " << media_w << " " << media_h << "] "
         << "/Contents 4 0 R "
         << "/Resources << /Font << /F1 5 0 R >> >> "
         << ">>\nendobj\n";
    objs.push_back(page.str());
  }

  {
    std::ostringstream contents;
    contents << "4 0 obj\n<< /Length " << stream.size() << " >>\nstream\n"
             << stream
             << "endstream\nendobj\n";
    objs.push_back(contents.str());
  }

  objs.push_back("5 0 obj\n<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\nendobj\n");

  std::string pdf = "%PDF-1.4\n";
  std::vector<uint32_t> offsets;
  offsets.resize(objs.size() + 1);  // offsets[0] unused for obj 0 entry

  for (size_t i = 0; i < objs.size(); ++i) {
    offsets[i + 1] = static_cast<uint32_t>(pdf.size());
    pdf += objs[i];
  }

  const uint32_t xref_pos = static_cast<uint32_t>(pdf.size());
  pdf += "xref\n";
  pdf += "0 6\n";
  pdf += "0000000000 65535 f \n";
  for (int i = 1; i <= 5; ++i) {
    pdf += Pad10(offsets[i]) + " 00000 n \n";
  }

  pdf += "trailer\n";
  pdf += "<< /Size 6 /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_pos) + "\n";
  pdf += "%%EOF\n";
  return pdf;
}

static GObjPtr<PopplerDocument> LoadDocFromData(const std::string& pdf_bytes) {
  GError* err_raw = nullptr;
  PopplerDocument* doc =
      poppler_document_new_from_data(pdf_bytes.data(),
                                     static_cast<int>(pdf_bytes.size()),
                                     /*password=*/nullptr,
                                     &err_raw);
  GErrorPtr err(err_raw);
  if (!doc) {
    // If this fails in a given environment, make the failure obvious.
    ADD_FAILURE() << "poppler_document_new_from_data failed: "
                  << (err ? err->message : "unknown error");
    return GObjPtr<PopplerDocument>(nullptr);
  }
  return GObjPtr<PopplerDocument>(doc);
}

static GObjPtr<PopplerPage> GetFirstPage(PopplerDocument* doc) {
  if (!doc) return GObjPtr<PopplerPage>(nullptr);
  PopplerPage* page = poppler_document_get_page(doc, 0);
  if (!page) {
    ADD_FAILURE() << "poppler_document_get_page(doc, 0) returned NULL";
    return GObjPtr<PopplerPage>(nullptr);
  }
  return GObjPtr<PopplerPage>(page);
}

static void FreeTextAttributesList(GList* list) {
  if (!list) return;
  // poppler-glib provides poppler_text_attributes_free() for list items.
  g_list_free_full(list, reinterpret_cast<GDestroyNotify>(poppler_text_attributes_free));
}

static int ListLength(GList* list) {
  return list ? static_cast<int>(g_list_length(list)) : 0;
}

static void ExpectSameRanges(const GList* a, const GList* b) {
  // Compare start/end index ranges element-wise (most stable public fields).
  const GList* ia = a;
  const GList* ib = b;
  while (ia && ib) {
    const auto* ta = static_cast<const PopplerTextAttributes*>(ia->data);
    const auto* tb = static_cast<const PopplerTextAttributes*>(ib->data);
    ASSERT_NE(ta, nullptr);
    ASSERT_NE(tb, nullptr);

    EXPECT_EQ(ta->start_index, tb->start_index);
    EXPECT_EQ(ta->end_index, tb->end_index);

    // Basic invariants (observable via struct fields).
    EXPECT_LE(ta->start_index, ta->end_index);
    EXPECT_LE(tb->start_index, tb->end_index);

    ia = ia->next;
    ib = ib->next;
  }
  EXPECT_EQ(ia, nullptr);
  EXPECT_EQ(ib, nullptr);
}

class PopplerPageGetTextAttributesTest_2503 : public ::testing::Test {
 protected:
  void TearDown() override {
    // no global cleanup
  }
};

TEST_F(PopplerPageGetTextAttributesTest_2503, NullPageReturnsNull_2503) {
  // Error/exceptional case: g_return_val_if_fail should return NULL.
  EXPECT_EQ(poppler_page_get_text_attributes(nullptr), nullptr);
}

TEST_F(PopplerPageGetTextAttributesTest_2503, NonPageGObjectReturnsNull_2503) {
  // Boundary/error case: pointer is a valid GObject but not a PopplerPage.
  GObjPtr<GObject> not_a_page(G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr)));
  ASSERT_NE(not_a_page.get(), nullptr);

  EXPECT_EQ(poppler_page_get_text_attributes(reinterpret_cast<PopplerPage*>(not_a_page.get())), nullptr);
}

TEST_F(PopplerPageGetTextAttributesTest_2503, MatchesForAreaFullPageWhenTextExists_2503) {
  // Normal operation: for a page with text, the helper should behave like calling
  // poppler_page_get_text_attributes_for_area() with a selection covering the full page.
  const std::string pdf = BuildMinimalPdfOnePage("Hi", /*media_w=*/200, /*media_h=*/200);
  auto doc = LoadDocFromData(pdf);
  ASSERT_NE(doc.get(), nullptr);

  auto page = GetFirstPage(doc.get());
  ASSERT_NE(page.get(), nullptr);

  double w = 0.0, h = 0.0;
  poppler_page_get_size(page.get(), &w, &h);
  ASSERT_GT(w, 0.0);
  ASSERT_GT(h, 0.0);

  PopplerRectangle full = {};
  // Public PopplerRectangle uses doubles and has x1,y1,x2,y2 in poppler-glib.
  full.x1 = 0.0;
  full.y1 = 0.0;
  full.x2 = w;
  full.y2 = h;

  GList* attrs_whole = poppler_page_get_text_attributes(page.get());
  GList* attrs_area = poppler_page_get_text_attributes_for_area(page.get(), &full);

  // Observable equivalence checks:
  // - both either NULL or non-NULL
  // - same number of attributes
  // - same start/end ranges per attribute
  EXPECT_EQ(ListLength(attrs_whole), ListLength(attrs_area));
  if (attrs_whole && attrs_area) {
    ExpectSameRanges(attrs_whole, attrs_area);
  } else {
    EXPECT_EQ(attrs_whole, nullptr);
    EXPECT_EQ(attrs_area, nullptr);
  }

  FreeTextAttributesList(attrs_whole);
  FreeTextAttributesList(attrs_area);
}

TEST_F(PopplerPageGetTextAttributesTest_2503, BlankPageHasNoAttributesOrMatchesEmptyArea_2503) {
  // Boundary condition: page exists but has no text; result should be empty/NULL and
  // match the for-area call over full page.
  const std::string pdf = BuildMinimalPdfOnePage(/*text=*/"", /*media_w=*/200, /*media_h=*/200);
  auto doc = LoadDocFromData(pdf);
  ASSERT_NE(doc.get(), nullptr);

  auto page = GetFirstPage(doc.get());
  ASSERT_NE(page.get(), nullptr);

  double w = 0.0, h = 0.0;
  poppler_page_get_size(page.get(), &w, &h);
  ASSERT_GT(w, 0.0);
  ASSERT_GT(h, 0.0);

  PopplerRectangle full = {};
  full.x1 = 0.0;
  full.y1 = 0.0;
  full.x2 = w;
  full.y2 = h;

  GList* attrs_whole = poppler_page_get_text_attributes(page.get());
  GList* attrs_area = poppler_page_get_text_attributes_for_area(page.get(), &full);

  // Both should represent "no attributes" in the same way.
  EXPECT_EQ(ListLength(attrs_whole), ListLength(attrs_area));
  EXPECT_EQ(ListLength(attrs_whole), 0);

  FreeTextAttributesList(attrs_whole);
  FreeTextAttributesList(attrs_area);
}

}  // namespace