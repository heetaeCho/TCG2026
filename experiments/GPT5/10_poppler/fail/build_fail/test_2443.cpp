// File: poppler-page-get-selected-text-test_2443.cc
#include <gtest/gtest.h>

#include <poppler.h>
#include <glib.h>

#include <cstring>
#include <memory>
#include <string>

namespace {

struct GErrorDeleter {
  void operator()(GError *e) const {
    if (e) {
      g_error_free(e);
    }
  }
};

struct GObjectDeleter {
  void operator()(gpointer p) const {
    if (p) {
      g_object_unref(p);
    }
  }
};

struct GFreeDeleter {
  void operator()(gpointer p) const {
    if (p) {
      g_free(p);
    }
  }
};

using UniqueGError = std::unique_ptr<GError, GErrorDeleter>;
using UniqueGObject = std::unique_ptr<GObject, GObjectDeleter>;
using UniqueGChar = std::unique_ptr<gchar, GFreeDeleter>;

// A tiny single-page PDF containing the text "Hello World".
// Notes:
// - This is embedded to keep the test self-contained (no external files).
// - The tests only assert observable behavior through the public GLib API.
static const unsigned char kHelloWorldPdf[] =
    "%PDF-1.4\n"
    "1 0 obj\n"
    "<< /Type /Catalog /Pages 2 0 R >>\n"
    "endobj\n"
    "2 0 obj\n"
    "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
    "endobj\n"
    "3 0 obj\n"
    "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792]\n"
    "   /Resources << /Font << /F1 4 0 R >> >>\n"
    "   /Contents 5 0 R >>\n"
    "endobj\n"
    "4 0 obj\n"
    "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
    "endobj\n"
    "5 0 obj\n"
    "<< /Length 57 >>\n"
    "stream\n"
    "BT\n"
    "/F1 24 Tf\n"
    "72 720 Td\n"
    "(Hello World) Tj\n"
    "ET\n"
    "endstream\n"
    "endobj\n"
    "xref\n"
    "0 6\n"
    "0000000000 65535 f \n"
    "0000000009 00000 n \n"
    "0000000058 00000 n \n"
    "0000000115 00000 n \n"
    "0000000241 00000 n \n"
    "0000000311 00000 n \n"
    "trailer\n"
    "<< /Size 6 /Root 1 0 R >>\n"
    "startxref\n"
    "418\n"
    "%%EOF\n";

class PopplerPageGetSelectedTextTest_2443 : public ::testing::Test {
 protected:
  void SetUp() override {
    GError *err_raw = nullptr;

    // poppler_document_new_from_data copies/consumes the data depending on implementation;
    // we treat it as a black box and just pass a stable buffer.
    PopplerDocument *doc_raw = poppler_document_new_from_data(
        reinterpret_cast<const char *>(kHelloWorldPdf),
        static_cast<int>(sizeof(kHelloWorldPdf) - 1),
        /*password=*/nullptr,
        &err_raw);

    err_.reset(err_raw);
    ASSERT_NE(doc_raw, nullptr) << "Failed to create PopplerDocument from embedded PDF: "
                                << (err_ ? err_->message : "unknown error");
    doc_.reset(G_OBJECT(doc_raw));

    PopplerPage *page_raw = poppler_document_get_page(POPPLER_DOCUMENT(doc_.get()), 0);
    ASSERT_NE(page_raw, nullptr);
    page_.reset(G_OBJECT(page_raw));
  }

  PopplerPage *page() const { return POPPLER_PAGE(page_.get()); }

  UniqueGError err_;
  UniqueGObject doc_;
  UniqueGObject page_;
};

TEST_F(PopplerPageGetSelectedTextTest_2443, ReturnsNonNullForWholePageSelection_Glyph_2443) {
  gdouble width = 0, height = 0;
  poppler_page_get_size(page(), &width, &height);

  PopplerRectangle rect;
  rect.x1 = 0.0;
  rect.y1 = 0.0;
  rect.x2 = width;
  rect.y2 = height;

  UniqueGChar selected(poppler_page_get_selected_text(page(), POPPLER_SELECTION_GLYPH, &rect));
  ASSERT_NE(selected.get(), nullptr);

  // Observable behavior: whole-page selection should include known text.
  EXPECT_NE(std::string(selected.get()).find("Hello World"), std::string::npos);
}

TEST_F(PopplerPageGetSelectedTextTest_2443, ReturnsNonNullForWholePageSelection_Word_2443) {
  gdouble width = 0, height = 0;
  poppler_page_get_size(page(), &width, &height);

  PopplerRectangle rect;
  rect.x1 = 0.0;
  rect.y1 = 0.0;
  rect.x2 = width;
  rect.y2 = height;

  UniqueGChar selected(poppler_page_get_selected_text(page(), POPPLER_SELECTION_WORD, &rect));
  ASSERT_NE(selected.get(), nullptr);
  EXPECT_NE(std::string(selected.get()).find("Hello World"), std::string::npos);
}

TEST_F(PopplerPageGetSelectedTextTest_2443, ReturnsNonNullForWholePageSelection_Line_2443) {
  gdouble width = 0, height = 0;
  poppler_page_get_size(page(), &width, &height);

  PopplerRectangle rect;
  rect.x1 = 0.0;
  rect.y1 = 0.0;
  rect.x2 = width;
  rect.y2 = height;

  UniqueGChar selected(poppler_page_get_selected_text(page(), POPPLER_SELECTION_LINE, &rect));
  ASSERT_NE(selected.get(), nullptr);
  EXPECT_NE(std::string(selected.get()).find("Hello World"), std::string::npos);
}

TEST_F(PopplerPageGetSelectedTextTest_2443, NullSelectionReturnsNull_2443) {
  // Exceptional/error case observable via interface: returns NULL on invalid args.
  gchar *selected = poppler_page_get_selected_text(page(), POPPLER_SELECTION_GLYPH, nullptr);
  EXPECT_EQ(selected, nullptr);
}

TEST_F(PopplerPageGetSelectedTextTest_2443, InvalidPagePointerReturnsNull_2443) {
  PopplerRectangle rect;
  rect.x1 = 0.0;
  rect.y1 = 0.0;
  rect.x2 = 10.0;
  rect.y2 = 10.0;

  // Exceptional/error case: g_return_val_if_fail should return NULL.
  gchar *selected = poppler_page_get_selected_text(nullptr, POPPLER_SELECTION_GLYPH, &rect);
  EXPECT_EQ(selected, nullptr);
}

TEST_F(PopplerPageGetSelectedTextTest_2443, DegenerateRectangleDoesNotCrashAndReturnsNonNullString_2443) {
  // Boundary condition: zero-area selection.
  PopplerRectangle rect;
  rect.x1 = 100.0;
  rect.y1 = 100.0;
  rect.x2 = 100.0;
  rect.y2 = 100.0;

  UniqueGChar selected(poppler_page_get_selected_text(page(), POPPLER_SELECTION_GLYPH, &rect));

  // We avoid assuming whether Poppler returns empty vs. a character at a point.
  // Observable requirement: should return an allocated string (non-null) on valid inputs.
  ASSERT_NE(selected.get(), nullptr);
}

TEST_F(PopplerPageGetSelectedTextTest_2443, UnknownSelectionStyleBehavesLikeAValidCall_2443) {
  gdouble width = 0, height = 0;
  poppler_page_get_size(page(), &width, &height);

  PopplerRectangle rect;
  rect.x1 = 0.0;
  rect.y1 = 0.0;
  rect.x2 = width;
  rect.y2 = height;

  // Boundary/robustness: style outside enum range should not crash.
  auto bogus_style = static_cast<PopplerSelectionStyle>(999);

  UniqueGChar selected(poppler_page_get_selected_text(page(), bogus_style, &rect));
  ASSERT_NE(selected.get(), nullptr);
  EXPECT_NE(std::string(selected.get()).find("Hello World"), std::string::npos);
}

}  // namespace