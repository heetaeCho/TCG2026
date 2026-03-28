// poppler-page-get-text-for-area-test_2445.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstring>
#include <string>

namespace {

class PopplerPageGetTextForAreaTest_2445 : public ::testing::Test {
protected:
  void SetUp() override {
    // Minimal single-page PDF with the text "Hello" drawn near the top-left.
    // Uses built-in Helvetica.
    static const char kPdf[] =
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
        "   /Contents 5 0 R\n"
        ">>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
        "endobj\n"
        "5 0 obj\n"
        "<< /Length 44 >>\n"
        "stream\n"
        "BT\n"
        "/F1 24 Tf\n"
        "72 720 Td\n"
        "(Hello) Tj\n"
        "ET\n"
        "endstream\n"
        "endobj\n"
        "xref\n"
        "0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000245 00000 n \n"
        "0000000315 00000 n \n"
        "trailer\n"
        "<< /Size 6 /Root 1 0 R >>\n"
        "startxref\n"
        "409\n"
        "%%EOF\n";

    GError* error = nullptr;
    document_ = poppler_document_new_from_data(kPdf, static_cast<int>(std::strlen(kPdf)), nullptr, &error);
    ASSERT_NE(document_, nullptr) << (error ? error->message : "unknown error");
    if (error) g_error_free(error);

    page_ = poppler_document_get_page(document_, 0);
    ASSERT_NE(page_, nullptr);
  }

  void TearDown() override {
    if (page_) g_object_unref(page_);
    if (document_) g_object_unref(document_);
    page_ = nullptr;
    document_ = nullptr;
  }

  static std::string ToStringOrEmpty(const char* s) { return s ? std::string(s) : std::string(); }

  PopplerDocument* document_ = nullptr;
  PopplerPage* page_ = nullptr;
};

TEST_F(PopplerPageGetTextForAreaTest_2445, NullPageReturnsNull_2445) {
  PopplerRectangle area;
  area.x1 = 0;
  area.y1 = 0;
  area.x2 = 612;
  area.y2 = 792;

  char* text = poppler_page_get_text_for_area(nullptr, &area);
  EXPECT_EQ(text, nullptr);
}

TEST_F(PopplerPageGetTextForAreaTest_2445, NullAreaReturnsNull_2445) {
  char* text = poppler_page_get_text_for_area(page_, nullptr);
  EXPECT_EQ(text, nullptr);
}

TEST_F(PopplerPageGetTextForAreaTest_2445, InvalidPageTypeReturnsNull_2445) {
  // Use a real GObject instance (not a random pointer) to avoid undefined behavior
  // during GType checks inside POPPLER_IS_PAGE.
  GObject* not_a_page = g_object_new(G_TYPE_OBJECT, nullptr);
  ASSERT_NE(not_a_page, nullptr);

  PopplerRectangle area;
  area.x1 = 0;
  area.y1 = 0;
  area.x2 = 612;
  area.y2 = 792;

  char* text = poppler_page_get_text_for_area(reinterpret_cast<PopplerPage*>(not_a_page), &area);
  EXPECT_EQ(text, nullptr);

  g_object_unref(not_a_page);
}

TEST_F(PopplerPageGetTextForAreaTest_2445, ReturnsSameAsSelectedTextGlyph_2445) {
  // A large area covering the full page should deterministically compare against
  // poppler_page_get_selected_text(..., POPPLER_SELECTION_GLYPH, ...).
  PopplerRectangle area;
  area.x1 = 0;
  area.y1 = 0;
  area.x2 = 612;
  area.y2 = 792;

  char* via_area = poppler_page_get_text_for_area(page_, &area);
  char* via_selected = poppler_page_get_selected_text(page_, POPPLER_SELECTION_GLYPH, &area);

  // Observable behavior: wrapper should match the delegated call's returned text.
  EXPECT_EQ(ToStringOrEmpty(via_area), ToStringOrEmpty(via_selected));

  if (via_area) g_free(via_area);
  if (via_selected) g_free(via_selected);
}

TEST_F(PopplerPageGetTextForAreaTest_2445, BoundaryZeroSizedAreaMatchesSelectedText_2445) {
  // Boundary condition: degenerate rectangle (x1==x2 and y1==y2).
  // We don't assume what text is returned, only that the wrapper matches the delegated API.
  PopplerRectangle area;
  area.x1 = 100;
  area.y1 = 100;
  area.x2 = 100;
  area.y2 = 100;

  char* via_area = poppler_page_get_text_for_area(page_, &area);
  char* via_selected = poppler_page_get_selected_text(page_, POPPLER_SELECTION_GLYPH, &area);

  EXPECT_EQ(ToStringOrEmpty(via_area), ToStringOrEmpty(via_selected));

  if (via_area) g_free(via_area);
  if (via_selected) g_free(via_selected);
}

}  // namespace