// File: poppler-page-get-text-page-test-2431.cc
//
// Unit tests for static helper poppler_page_get_text_page(PopplerPage*).
// These tests treat the implementation as a black box and only verify
// observable behavior through the public/known struct fields and return values.

#include <gtest/gtest.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <poppler.h>

// We rely on PopplerPage's private struct layout for observing the cached TextPage.
// This header is part of the codebase per prompt.
#include "poppler-private.h"

// IMPORTANT:
// poppler_page_get_text_page is a static function in poppler-page.cc.
// To test it directly, we include the implementation file into this test TU.
// This is a common unit-testing pattern for internal helpers.
// Ensure your test target does NOT also link the compiled poppler-page.cc object,
// or you will get duplicate symbol errors.
#include "poppler-page.cc"

namespace {

class PopplerPageGetTextPageTest_2431 : public ::testing::Test {
protected:
  void SetUp() override {
    // Create a tiny 1-page PDF with a bit of text so TextOutputDev has something to extract.
    // (Any valid PDF should work; we avoid inferring internal text extraction logic.)
    const char kMinimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 300 300]\n"
        "   /Contents 4 0 R\n"
        "   /Resources << /Font << /F1 5 0 R >> >>\n"
        ">>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Length 44 >>\n"
        "stream\n"
        "BT\n"
        "/F1 24 Tf\n"
        "72 200 Td\n"
        "(Hello) Tj\n"
        "ET\n"
        "endstream\n"
        "endobj\n"
        "5 0 obj\n"
        "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
        "endobj\n"
        "xref\n"
        "0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000241 00000 n \n"
        "0000000335 00000 n \n"
        "trailer\n"
        "<< /Size 6 /Root 1 0 R >>\n"
        "startxref\n"
        "0411\n"
        "%%EOF\n";

    gchar *tmp_path = nullptr;
    {
      // Create a temp file path.
      gchar *tmpl = g_strdup("poppler_textpage_XXXXXX.pdf");
      int fd = g_mkstemp(tmpl);
      ASSERT_NE(fd, -1);

      // Write PDF bytes.
      gssize len = static_cast<gssize>(sizeof(kMinimalPdf) - 1);
      ASSERT_EQ(write(fd, kMinimalPdf, static_cast<size_t>(len)), len);
      close(fd);

      tmp_path = tmpl; // take ownership
    }

    tmp_path_ = tmp_path;

    gchar *uri = g_filename_to_uri(tmp_path_, nullptr, nullptr);
    ASSERT_NE(uri, nullptr);
    uri_.reset(uri, g_free);

    GError *error = nullptr;
    doc_ = poppler_document_new_from_file(uri_.get(), nullptr, &error);
    ASSERT_NE(doc_, nullptr);
    ASSERT_EQ(error, nullptr);

    page_ = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page_, nullptr);

    // Sanity: cache should start empty for a fresh page instance.
    // (If the underlying implementation pre-populates it, this will fail; but that would
    // be an observable behavior change we want to catch.)
    ASSERT_EQ(page_->text.get(), nullptr);
  }

  void TearDown() override {
    if (page_) {
      g_object_unref(page_);
      page_ = nullptr;
    }
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
    if (tmp_path_) {
      g_remove(tmp_path_);
      g_free(tmp_path_);
      tmp_path_ = nullptr;
    }
  }

  struct GFreeDeleter {
    void operator()(gchar *p) const { g_free(p); }
  };

  std::unique_ptr<gchar, GFreeDeleter> uri_{nullptr};

  PopplerDocument *doc_ = nullptr;
  PopplerPage *page_ = nullptr;
  gchar *tmp_path_ = nullptr;
};

TEST_F(PopplerPageGetTextPageTest_2431, FirstCallCreatesAndCachesTextPage_2431) {
  ASSERT_NE(page_, nullptr);
  ASSERT_EQ(page_->text.get(), nullptr);

  TextPage *tp = poppler_page_get_text_page(page_);
  EXPECT_NE(tp, nullptr);

  // Observable side effect: cache is populated.
  EXPECT_NE(page_->text.get(), nullptr);
  EXPECT_EQ(page_->text.get(), tp);
}

TEST_F(PopplerPageGetTextPageTest_2431, SecondCallReturnsSamePointerAndKeepsCache_2431) {
  ASSERT_NE(page_, nullptr);

  TextPage *tp1 = poppler_page_get_text_page(page_);
  ASSERT_NE(tp1, nullptr);

  auto cached1 = page_->text; // copy shared_ptr (observable via public field)
  ASSERT_NE(cached1.get(), nullptr);

  TextPage *tp2 = poppler_page_get_text_page(page_);
  ASSERT_NE(tp2, nullptr);

  // Should return the same cached TextPage (no re-creation observable).
  EXPECT_EQ(tp2, tp1);
  EXPECT_EQ(page_->text.get(), cached1.get());
}

TEST_F(PopplerPageGetTextPageTest_2431, CacheSurvivesRepeatedCalls_2431) {
  ASSERT_NE(page_, nullptr);

  TextPage *first = poppler_page_get_text_page(page_);
  ASSERT_NE(first, nullptr);

  for (int i = 0; i < 10; ++i) {
    TextPage *again = poppler_page_get_text_page(page_);
    ASSERT_NE(again, nullptr);
    EXPECT_EQ(again, first);
    EXPECT_EQ(page_->text.get(), first);
  }
}

TEST_F(PopplerPageGetTextPageTest_2431, DoesNotClearExistingCache_2431) {
  ASSERT_NE(page_, nullptr);

  TextPage *tp1 = poppler_page_get_text_page(page_);
  ASSERT_NE(tp1, nullptr);

  // Hold an extra ref to ensure the shared ownership stays valid.
  auto keep_alive = page_->text;
  ASSERT_EQ(keep_alive.get(), tp1);

  TextPage *tp2 = poppler_page_get_text_page(page_);
  ASSERT_NE(tp2, nullptr);

  EXPECT_EQ(tp2, tp1);
  EXPECT_EQ(page_->text.get(), keep_alive.get());
}

} // namespace