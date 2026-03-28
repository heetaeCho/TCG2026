// File: poppler-annot-square-get-interior-color-test_2117.cc

#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

namespace {

class FatalMaskGuard {
public:
  FatalMaskGuard(const char* domain, GLogLevelFlags new_mask)
      : domain_(domain ? g_strdup(domain) : nullptr), old_mask_(0) {
    // g_log_set_fatal_mask() returns the old fatal mask for the domain.
    old_mask_ = g_log_set_fatal_mask(domain_, new_mask);
  }

  ~FatalMaskGuard() {
    g_log_set_fatal_mask(domain_, old_mask_);
    g_free(domain_);
  }

  FatalMaskGuard(const FatalMaskGuard&) = delete;
  FatalMaskGuard& operator=(const FatalMaskGuard&) = delete;

private:
  char* domain_;
  GLogLevelFlags old_mask_;
};

static std::string WriteMinimalOnePagePdfToTempFile() {
  // A tiny, valid PDF with a single blank page.
  // Keep it simple; tests treat Poppler as a black box.
  static const char kPdf[] =
      "%PDF-1.1\n"
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R >>\n"
      "endobj\n"
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n"
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
      "endobj\n"
      "xref\n"
      "0 4\n"
      "0000000000 65535 f \n"
      "0000000009 00000 n \n"
      "0000000058 00000 n \n"
      "0000000115 00000 n \n"
      "trailer\n"
      "<< /Size 4 /Root 1 0 R >>\n"
      "startxref\n"
      "186\n"
      "%%EOF\n";

  gchar* tmp_name = nullptr;
  gint fd = g_file_open_tmp("poppler_annot_square_XXXXXX.pdf", &tmp_name, nullptr);
  EXPECT_GE(fd, 0);
  EXPECT_NE(tmp_name, nullptr);

  // Write content.
  gssize to_write = static_cast<gssize>(strlen(kPdf));
  gssize written = 0;
  while (written < to_write) {
    gssize w = write(fd, kPdf + written, static_cast<size_t>(to_write - written));
    if (w <= 0) break;
    written += w;
  }
  close(fd);

  EXPECT_EQ(written, to_write);

  std::string path(tmp_name);
  g_free(tmp_name);
  return path;
}

class PopplerAnnotSquareGetInteriorColorTest_2117 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure CRITICALs (from g_return_val_if_fail) won't be fatal even if the
    // environment is configured aggressively.
    fatal_mask_guard_ = std::make_unique<FatalMaskGuard>("Poppler", G_LOG_LEVEL_ERROR);

    pdf_path_ = WriteMinimalOnePagePdfToTempFile();

    GError* error = nullptr;
    gchar* uri = g_filename_to_uri(pdf_path_.c_str(), /*hostname=*/nullptr, &error);
    ASSERT_EQ(error, nullptr);
    ASSERT_NE(uri, nullptr);

    doc_ = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
    g_free(uri);

    ASSERT_EQ(error, nullptr);
    ASSERT_NE(doc_, nullptr);
  }

  void TearDown() override {
    if (doc_) g_object_unref(doc_);
    doc_ = nullptr;

    if (!pdf_path_.empty()) {
      g_remove(pdf_path_.c_str());
    }

    fatal_mask_guard_.reset();
  }

  PopplerDocument* doc_ = nullptr;
  std::string pdf_path_;
  std::unique_ptr<FatalMaskGuard> fatal_mask_guard_;
};

TEST_F(PopplerAnnotSquareGetInteriorColorTest_2117, NullInputReturnsNull_2117) {
  // Expect a critical message, but behavior should be "return NULL".
  g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*");
  PopplerColor* color = poppler_annot_square_get_interior_color(nullptr);
  g_test_assert_expected_messages();

  EXPECT_EQ(color, nullptr);
}

TEST_F(PopplerAnnotSquareGetInteriorColorTest_2117, WrongTypeReturnsNull_2117) {
  PopplerRectangle rect;
  rect.x1 = 10;
  rect.y1 = 10;
  rect.x2 = 100;
  rect.y2 = 100;

  // Create a different annot type and pass it where a Square is required.
  PopplerAnnot* circle_base = poppler_annot_circle_new(doc_, &rect);
  ASSERT_NE(circle_base, nullptr);

  g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*");
  PopplerColor* color =
      poppler_annot_square_get_interior_color(reinterpret_cast<PopplerAnnotSquare*>(circle_base));
  g_test_assert_expected_messages();

  EXPECT_EQ(color, nullptr);

  g_object_unref(circle_base);
}

TEST_F(PopplerAnnotSquareGetInteriorColorTest_2117, DefaultInteriorColorMayBeNull_2117) {
  PopplerRectangle rect;
  rect.x1 = 0;
  rect.y1 = 0;
  rect.x2 = 50;
  rect.y2 = 50;

  PopplerAnnot* square_base = poppler_annot_square_new(doc_, &rect);
  ASSERT_NE(square_base, nullptr);

  // If no interior color is set, API documents "NULL" is possible.
  PopplerColor* color =
      poppler_annot_square_get_interior_color(POPPLER_ANNOT_SQUARE(square_base));
  if (color) {
    // Ownership: must be freed with g_free().
    g_free(color);
  }

  g_object_unref(square_base);
}

TEST_F(PopplerAnnotSquareGetInteriorColorTest_2117, SetThenGetReturnsMatchingValues_2117) {
  PopplerRectangle rect;
  rect.x1 = 1;
  rect.y1 = 2;
  rect.x2 = 200;
  rect.y2 = 300;

  PopplerAnnot* square_base = poppler_annot_square_new(doc_, &rect);
  ASSERT_NE(square_base, nullptr);
  PopplerAnnotSquare* square = POPPLER_ANNOT_SQUARE(square_base);

  PopplerColor set_color;
  set_color.red = 0x1111;
  set_color.green = 0x2222;
  set_color.blue = 0x3333;

  poppler_annot_square_set_interior_color(square, &set_color);

  PopplerColor* got = poppler_annot_square_get_interior_color(square);
  ASSERT_NE(got, nullptr);

  EXPECT_EQ(got->red, set_color.red);
  EXPECT_EQ(got->green, set_color.green);
  EXPECT_EQ(got->blue, set_color.blue);

  g_free(got);
  g_object_unref(square_base);
}

TEST_F(PopplerAnnotSquareGetInteriorColorTest_2117, GetReturnsNewAllocationEachCall_2117) {
  PopplerRectangle rect;
  rect.x1 = 5;
  rect.y1 = 6;
  rect.x2 = 70;
  rect.y2 = 80;

  PopplerAnnot* square_base = poppler_annot_square_new(doc_, &rect);
  ASSERT_NE(square_base, nullptr);
  PopplerAnnotSquare* square = POPPLER_ANNOT_SQUARE(square_base);

  PopplerColor set_color;
  set_color.red = 0xAAAA;
  set_color.green = 0xBBBB;
  set_color.blue = 0xCCCC;

  poppler_annot_square_set_interior_color(square, &set_color);

  PopplerColor* c1 = poppler_annot_square_get_interior_color(square);
  PopplerColor* c2 = poppler_annot_square_get_interior_color(square);

  ASSERT_NE(c1, nullptr);
  ASSERT_NE(c2, nullptr);

  // API docs: "a new allocated PopplerColor" -> pointers should not be the same.
  EXPECT_NE(c1, c2);

  // Values should match the set color on both.
  EXPECT_EQ(c1->red, set_color.red);
  EXPECT_EQ(c1->green, set_color.green);
  EXPECT_EQ(c1->blue, set_color.blue);

  EXPECT_EQ(c2->red, set_color.red);
  EXPECT_EQ(c2->green, set_color.green);
  EXPECT_EQ(c2->blue, set_color.blue);

  g_free(c1);
  g_free(c2);
  g_object_unref(square_base);
}

TEST_F(PopplerAnnotSquareGetInteriorColorTest_2117, SetNullThenGetReturnsNullOrNoCrash_2117) {
  PopplerRectangle rect;
  rect.x1 = 0;
  rect.y1 = 0;
  rect.x2 = 10;
  rect.y2 = 10;

  PopplerAnnot* square_base = poppler_annot_square_new(doc_, &rect);
  ASSERT_NE(square_base, nullptr);
  PopplerAnnotSquare* square = POPPLER_ANNOT_SQUARE(square_base);

  // Boundary/error-ish case: passing NULL to setter. Observable expectation:
  // should not crash; getter may return NULL afterward.
  poppler_annot_square_set_interior_color(square, nullptr);

  PopplerColor* got = poppler_annot_square_get_interior_color(square);
  if (got) g_free(got);

  g_object_unref(square_base);
}

}  // namespace