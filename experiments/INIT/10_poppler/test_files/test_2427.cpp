// poppler-page-get-index-test_2427.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

namespace {

constexpr unsigned char kTestPdfBytes[] =
    "%PDF-1.4\n"
    "1 0 obj\n"
    "<< /Type /Catalog /Pages 2 0 R >>\n"
    "endobj\n"
    "2 0 obj\n"
    "<< /Type /Pages /Count 3 /Kids [ 3 0 R 5 0 R 7 0 R ] >>\n"
    "endobj\n"
    "3 0 obj\n"
    "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>\n"
    "endobj\n"
    "4 0 obj\n"
    "<< /Length 4 >>\n"
    "stream\n"
    "q\n"
    "Q\n"
    "endstream\n"
    "endobj\n"
    "5 0 obj\n"
    "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 6 0 R >>\n"
    "endobj\n"
    "6 0 obj\n"
    "<< /Length 4 >>\n"
    "stream\n"
    "q\n"
    "Q\n"
    "endstream\n"
    "endobj\n"
    "7 0 obj\n"
    "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 8 0 R >>\n"
    "endobj\n"
    "8 0 obj\n"
    "<< /Length 4 >>\n"
    "stream\n"
    "q\n"
    "Q\n"
    "endstream\n"
    "endobj\n"
    "xref\n"
    "0 9\n"
    "0000000000 65535 f \n"
    "0000000009 00000 n \n"
    "0000000058 00000 n \n"
    "0000000136 00000 n \n"
    "0000000224 00000 n \n"
    "0000000278 00000 n \n"
    "0000000366 00000 n \n"
    "0000000420 00000 n \n"
    "0000000508 00000 n \n"
    "trailer\n"
    "<< /Size 9 /Root 1 0 R >>\n"
    "startxref\n"
    "596\n"
    "%%EOF\n";

PopplerDocument* CreateDocFromEmbeddedPdfOrFail() {
  GError* error = nullptr;
  PopplerDocument* doc = poppler_document_new_from_data(
      reinterpret_cast<const char*>(kTestPdfBytes),
      static_cast<int>(sizeof(kTestPdfBytes) - 1),
      /*password=*/nullptr,
      &error);

  if (!doc) {
    const char* msg = (error && error->message) ? error->message : "(no error message)";
    if (error) {
      g_error_free(error);
    }
    ADD_FAILURE() << "Failed to create PopplerDocument from embedded PDF data: " << msg;
    return nullptr;
  }

  if (error) {
    // If Poppler set a non-fatal error (unlikely), free it to avoid leaks.
    g_error_free(error);
  }
  return doc;
}

}  // namespace

class PopplerPageGetIndexTest_2427 : public ::testing::Test {
 protected:
  void SetUp() override {
    doc_ = CreateDocFromEmbeddedPdfOrFail();
    ASSERT_NE(doc_, nullptr);

    n_pages_ = poppler_document_get_n_pages(doc_);
    ASSERT_GE(n_pages_, 1);
  }

  void TearDown() override {
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
  }

  PopplerDocument* doc_ = nullptr;
  int n_pages_ = 0;
};

TEST_F(PopplerPageGetIndexTest_2427, ReturnsExpectedIndexForFirstPage_2427) {
  ASSERT_NE(doc_, nullptr);
  ASSERT_GE(n_pages_, 1);

  PopplerPage* page0 = poppler_document_get_page(doc_, 0);
  ASSERT_NE(page0, nullptr);

  EXPECT_EQ(poppler_page_get_index(page0), 0);

  g_object_unref(page0);
}

TEST_F(PopplerPageGetIndexTest_2427, ReturnsExpectedIndexForMiddlePage_2427) {
  ASSERT_NE(doc_, nullptr);
  ASSERT_GE(n_pages_, 3) << "Embedded test PDF is expected to have at least 3 pages.";

  const int mid = 1;
  PopplerPage* page = poppler_document_get_page(doc_, mid);
  ASSERT_NE(page, nullptr);

  EXPECT_EQ(poppler_page_get_index(page), mid);

  g_object_unref(page);
}

TEST_F(PopplerPageGetIndexTest_2427, ReturnsExpectedIndexForLastPage_2427) {
  ASSERT_NE(doc_, nullptr);
  ASSERT_GE(n_pages_, 1);

  const int last = n_pages_ - 1;
  PopplerPage* page = poppler_document_get_page(doc_, last);
  ASSERT_NE(page, nullptr);

  EXPECT_EQ(poppler_page_get_index(page), last);

  g_object_unref(page);
}

TEST_F(PopplerPageGetIndexTest_2427, NullPageReturnsZero_2427) {
  // Exceptional / error case (observable through return value).
  // poppler_page_get_index() uses g_return_val_if_fail(), which should return 0 for invalid input.
  EXPECT_EQ(poppler_page_get_index(nullptr), 0);
}

TEST_F(PopplerPageGetIndexTest_2427, RepeatedCallsAreConsistent_2427) {
  ASSERT_NE(doc_, nullptr);
  ASSERT_GE(n_pages_, 1);

  PopplerPage* page0 = poppler_document_get_page(doc_, 0);
  ASSERT_NE(page0, nullptr);

  const int v1 = poppler_page_get_index(page0);
  const int v2 = poppler_page_get_index(page0);
  const int v3 = poppler_page_get_index(page0);

  EXPECT_EQ(v1, v2);
  EXPECT_EQ(v2, v3);

  g_object_unref(page0);
}