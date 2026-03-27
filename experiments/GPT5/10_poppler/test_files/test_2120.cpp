// poppler-annot-stamp-set-icon-test.cc
//
// Unit tests for poppler_annot_stamp_set_icon()
// TEST_ID: 2120
//
// Notes:
// - Treat implementation as black box.
// - Only verify observable behavior via public API (Poppler GLib).
// - Use a minimal on-disk PDF to obtain a valid PopplerDocument/PDFDoc context.

#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>
#include <poppler-document.h>
#include <poppler-page.h>
#include <poppler-annot.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>

namespace {

class PopplerAnnotStampSetIconTest_2120 : public ::testing::Test {
protected:
  void SetUp() override {
    tmp_pdf_path_ = MakeTempPath_("poppler_stamp_set_icon_2120_", ".pdf");
    WriteMinimalOnePagePdf_(tmp_pdf_path_);

    std::string uri = "file://" + tmp_pdf_path_;

    GError *error = nullptr;
    doc_ = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &error);
    ASSERT_NE(doc_, nullptr) << (error ? error->message : "poppler_document_new_from_file returned NULL");
    if (error) {
      g_error_free(error);
      error = nullptr;
    }

    page_ = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page_, nullptr);

    // Create a stamp annotation on the document.
    // This is the standard GLib API shape used by Poppler for annotation creation.
    PopplerRectangle rect;
    rect.x1 = 10;
    rect.y1 = 10;
    rect.x2 = 100;
    rect.y2 = 60;

    // Some Poppler versions return PopplerAnnot* for _new() functions; we cast to the specific type.
    PopplerAnnot *base = poppler_annot_stamp_new(doc_, &rect);
    ASSERT_NE(base, nullptr);
    stamp_ = POPPLER_ANNOT_STAMP(base);
    ASSERT_TRUE(POPPLER_IS_ANNOT_STAMP(stamp_));

    // We don't need to add it to the page to test setter/getter behavior, but doing so
    // can help ensure the object is fully integrated in typical usage.
    // If poppler_page_add_annot exists, use it; otherwise this is a no-op via ifdef.
#ifdef poppler_page_add_annot
    poppler_page_add_annot(page_, POPPLER_ANNOT(stamp_));
#endif
  }

  void TearDown() override {
    if (stamp_) {
      g_object_unref(stamp_);
      stamp_ = nullptr;
    }
    if (page_) {
      g_object_unref(page_);
      page_ = nullptr;
    }
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
    if (!tmp_pdf_path_.empty()) {
      std::remove(tmp_pdf_path_.c_str());
    }
  }

  static std::string MakeTempPath_(const char *prefix, const char *suffix) {
    // Use GLib temp dir to avoid platform quirks.
    const char *tmpdir = g_get_tmp_dir();
    std::string path = std::string(tmpdir) + G_DIR_SEPARATOR_S + prefix + std::to_string(g_random_int()) + suffix;
    return path;
  }

  static void WriteMinimalOnePagePdf_(const std::string &path) {
    // Very small valid PDF with a single blank page.
    // (Sufficient for Poppler to open and provide a PDFDoc context.)
    const char pdf[] =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Contents 4 0 R >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Length 0 >>\n"
        "stream\n"
        "endstream\n"
        "endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000202 00000 n \n"
        "trailer\n"
        "<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n"
        "250\n"
        "%%EOF\n";

    std::ofstream out(path, std::ios::binary);
    ASSERT_TRUE(out.good());
    out.write(pdf, sizeof(pdf) - 1);
    out.close();
    ASSERT_TRUE(out.good());
  }

  PopplerDocument *doc_ = nullptr;
  PopplerPage *page_ = nullptr;
  PopplerAnnotStamp *stamp_ = nullptr;
  std::string tmp_pdf_path_;
};

static const PopplerAnnotStampIcon kAllKnownIcons_2120[] = {
    POPPLER_ANNOT_STAMP_ICON_APPROVED,
    POPPLER_ANNOT_STAMP_ICON_AS_IS,
    POPPLER_ANNOT_STAMP_ICON_CONFIDENTIAL,
    POPPLER_ANNOT_STAMP_ICON_FINAL,
    POPPLER_ANNOT_STAMP_ICON_EXPERIMENTAL,
    POPPLER_ANNOT_STAMP_ICON_EXPIRED,
    POPPLER_ANNOT_STAMP_ICON_NOT_APPROVED,
    POPPLER_ANNOT_STAMP_ICON_NOT_FOR_PUBLIC_RELEASE,
    POPPLER_ANNOT_STAMP_ICON_SOLD,
    POPPLER_ANNOT_STAMP_ICON_DEPARTMENTAL,
    POPPLER_ANNOT_STAMP_ICON_FOR_COMMENT,
    POPPLER_ANNOT_STAMP_ICON_FOR_PUBLIC_RELEASE,
    POPPLER_ANNOT_STAMP_ICON_TOP_SECRET,
};

} // namespace

// Normal operation: setting each known icon should be observable via the public getter.
TEST_F(PopplerAnnotStampSetIconTest_2120, SetsEachKnownIcon_2120) {
  ASSERT_TRUE(POPPLER_IS_ANNOT_STAMP(stamp_));

  for (auto icon : kAllKnownIcons_2120) {
    poppler_annot_stamp_set_icon(stamp_, icon);
    PopplerAnnotStampIcon got = poppler_annot_stamp_get_icon(stamp_);
    EXPECT_EQ(got, icon);
  }
}

// Boundary condition: setting NONE should be observable and should not crash.
TEST_F(PopplerAnnotStampSetIconTest_2120, SetNoneClearsIcon_2120) {
  ASSERT_TRUE(POPPLER_IS_ANNOT_STAMP(stamp_));

  poppler_annot_stamp_set_icon(stamp_, POPPLER_ANNOT_STAMP_ICON_APPROVED);
  ASSERT_EQ(poppler_annot_stamp_get_icon(stamp_), POPPLER_ANNOT_STAMP_ICON_APPROVED);

  poppler_annot_stamp_set_icon(stamp_, POPPLER_ANNOT_STAMP_ICON_NONE);
  EXPECT_EQ(poppler_annot_stamp_get_icon(stamp_), POPPLER_ANNOT_STAMP_ICON_NONE);
}

// Exceptional / error case: passing an invalid enum value should not crash and should not change
// the icon (observable via getter).
TEST_F(PopplerAnnotStampSetIconTest_2120, InvalidEnumDoesNotChangeIcon_2120) {
  ASSERT_TRUE(POPPLER_IS_ANNOT_STAMP(stamp_));

  poppler_annot_stamp_set_icon(stamp_, POPPLER_ANNOT_STAMP_ICON_FINAL);
  const PopplerAnnotStampIcon before = poppler_annot_stamp_get_icon(stamp_);
  ASSERT_EQ(before, POPPLER_ANNOT_STAMP_ICON_FINAL);

  // Value not in PopplerAnnotStampIcon.
  const PopplerAnnotStampIcon invalid = static_cast<PopplerAnnotStampIcon>(999);

  poppler_annot_stamp_set_icon(stamp_, invalid);

  const PopplerAnnotStampIcon after = poppler_annot_stamp_get_icon(stamp_);
  EXPECT_EQ(after, before);
}

// Exceptional / error case: UNKNOWN should be handled safely (no crash). Also verify it does not
// change the existing icon, since the function explicitly returns for UNKNOWN.
TEST_F(PopplerAnnotStampSetIconTest_2120, UnknownDoesNotChangeIcon_2120) {
  ASSERT_TRUE(POPPLER_IS_ANNOT_STAMP(stamp_));

  poppler_annot_stamp_set_icon(stamp_, POPPLER_ANNOT_STAMP_ICON_CONFIDENTIAL);
  const PopplerAnnotStampIcon before = poppler_annot_stamp_get_icon(stamp_);
  ASSERT_EQ(before, POPPLER_ANNOT_STAMP_ICON_CONFIDENTIAL);

  poppler_annot_stamp_set_icon(stamp_, POPPLER_ANNOT_STAMP_ICON_UNKNOWN);

  const PopplerAnnotStampIcon after = poppler_annot_stamp_get_icon(stamp_);
  EXPECT_EQ(after, before);
}

// Exceptional / error case: NULL input should not crash (g_return_if_fail).
TEST_F(PopplerAnnotStampSetIconTest_2120, NullAnnotDoesNotCrash_2120) {
  // No assertions other than "no crash".
  poppler_annot_stamp_set_icon(nullptr, POPPLER_ANNOT_STAMP_ICON_APPROVED);
  SUCCEED();
}

// Exceptional / error case: wrong GObject type should not crash (g_return_if_fail).
TEST_F(PopplerAnnotStampSetIconTest_2120, WrongTypeDoesNotCrash_2120) {
  PopplerRectangle rect;
  rect.x1 = 10;
  rect.y1 = 10;
  rect.x2 = 80;
  rect.y2 = 40;

  // Create a different annotation type and misuse-cast it to PopplerAnnotStamp*.
  PopplerAnnot *text_base = poppler_annot_text_new(doc_, &rect);
  ASSERT_NE(text_base, nullptr);
  ASSERT_TRUE(POPPLER_IS_ANNOT(text_base));
  ASSERT_FALSE(POPPLER_IS_ANNOT_STAMP(text_base));

  poppler_annot_stamp_set_icon(reinterpret_cast<PopplerAnnotStamp *>(text_base),
                              POPPLER_ANNOT_STAMP_ICON_APPROVED);

  g_object_unref(text_base);
  SUCCEED();
}