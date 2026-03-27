// File: poppler-document-get-page-by-label-test-2153.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

namespace {

static std::string BuildPdfTwoPagesWithDecimalPageLabels_2153()
{
  // Minimal PDF with:
  // - 2 pages
  // - /PageLabels using decimal style starting at 1 -> labels "1", "2"
  //
  // Objects:
  //  1 0: Catalog (with /Pages 2 0 R and /PageLabels 6 0 R)
  //  2 0: Pages
  //  3 0: Page 1 (Contents 5 0 R)
  //  4 0: Page 2 (Contents 7 0 R)
  //  5 0: Content stream 1
  //  6 0: PageLabels
  //  7 0: Content stream 2
  //
  // We compute xref offsets to keep it valid for strict parsers.

  struct Obj {
    int num;
    std::string body; // includes "n 0 obj ... endobj\n"
  };

  const char *s1 = "BT /F1 12 Tf 72 72 Td (Page1) Tj ET\n";
  const char *s2 = "BT /F1 12 Tf 72 72 Td (Page2) Tj ET\n";
  const int len1 = static_cast<int>(std::strlen(s1));
  const int len2 = static_cast<int>(std::strlen(s2));

  std::vector<Obj> objs;

  objs.push_back(
      {1,
       "1 0 obj\n"
       "<< /Type /Catalog /Pages 2 0 R /PageLabels 6 0 R >>\n"
       "endobj\n"});

  objs.push_back(
      {2,
       "2 0 obj\n"
       "<< /Type /Pages /Kids [3 0 R 4 0 R] /Count 2 >>\n"
       "endobj\n"});

  objs.push_back(
      {3,
       "3 0 obj\n"
       "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 5 0 R >>\n"
       "endobj\n"});

  objs.push_back(
      {4,
       "4 0 obj\n"
       "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 7 0 R >>\n"
       "endobj\n"});

  {
    std::string o5 = "5 0 obj\n<< /Length " + std::to_string(len1) +
                     " >>\nstream\n";
    o5.append(s1, s1 + len1);
    o5 += "endstream\nendobj\n";
    objs.push_back({5, std::move(o5)});
  }

  // Decimal labels starting at 1, so page 0 -> "1", page 1 -> "2"
  objs.push_back(
      {6,
       "6 0 obj\n"
       "<< /Nums [0 << /S /D /St 1 >>] >>\n"
       "endobj\n"});

  {
    std::string o7 = "7 0 obj\n<< /Length " + std::to_string(len2) +
                     " >>\nstream\n";
    o7.append(s2, s2 + len2);
    o7 += "endstream\nendobj\n";
    objs.push_back({7, std::move(o7)});
  }

  std::string pdf;
  pdf += "%PDF-1.4\n";
  pdf += "%\xE2\xE3\xCF\xD3\n"; // binary marker

  // Track offsets for xref. Index by object number (0..7).
  std::vector<std::size_t> offsets(8, 0);

  for (const auto &o : objs) {
    offsets[o.num] = pdf.size();
    pdf += o.body;
  }

  const std::size_t xref_pos = pdf.size();
  pdf += "xref\n";
  pdf += "0 8\n";
  pdf += "0000000000 65535 f \n";
  for (int i = 1; i <= 7; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010u 00000 n \n",
                  static_cast<unsigned>(offsets[i]));
    pdf += buf;
  }

  pdf += "trailer\n";
  pdf += "<< /Size 8 /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(static_cast<unsigned long long>(xref_pos));
  pdf += "\n%%EOF\n";

  return pdf;
}

class PopplerDocumentGetPageByLabelTest_2153 : public ::testing::Test {
protected:
  void SetUp() override
  {
    pdf_ = BuildPdfTwoPagesWithDecimalPageLabels_2153();

    GError *error = nullptr;
    document_ = poppler_document_new_from_data(pdf_.data(),
                                               static_cast<int>(pdf_.size()),
                                               /*password=*/nullptr, &error);
    ASSERT_NE(document_, nullptr);
    ASSERT_EQ(error, nullptr);
  }

  void TearDown() override
  {
    if (document_) {
      g_object_unref(document_);
      document_ = nullptr;
    }
  }

  std::string pdf_;
  PopplerDocument *document_ = nullptr;
};

TEST_F(PopplerDocumentGetPageByLabelTest_2153, ReturnsPageForLabelOne_2153)
{
  PopplerPage *page = poppler_document_get_page_by_label(document_, "1");
  ASSERT_NE(page, nullptr);

  // Observable behavior: returned page should correspond to index 0.
  EXPECT_EQ(poppler_page_get_index(page), 0);

  // If label API exists, it should match "1" for this document.
  gchar *label = poppler_page_get_label(page);
  ASSERT_NE(label, nullptr);
  EXPECT_STREQ(label, "1");
  g_free(label);

  g_object_unref(page);
}

TEST_F(PopplerDocumentGetPageByLabelTest_2153, ReturnsPageForLabelTwo_2153)
{
  PopplerPage *page = poppler_document_get_page_by_label(document_, "2");
  ASSERT_NE(page, nullptr);

  EXPECT_EQ(poppler_page_get_index(page), 1);

  gchar *label = poppler_page_get_label(page);
  ASSERT_NE(label, nullptr);
  EXPECT_STREQ(label, "2");
  g_free(label);

  g_object_unref(page);
}

TEST_F(PopplerDocumentGetPageByLabelTest_2153, ReturnsNullptrForUnknownLabel_2153)
{
  // There are only two pages labeled "1" and "2".
  PopplerPage *page = poppler_document_get_page_by_label(document_, "3");
  EXPECT_EQ(page, nullptr);
}

TEST_F(PopplerDocumentGetPageByLabelTest_2153, ReturnsNullptrForEmptyLabel_2153)
{
  PopplerPage *page = poppler_document_get_page_by_label(document_, "");
  EXPECT_EQ(page, nullptr);
}

TEST_F(PopplerDocumentGetPageByLabelTest_2153, ReturnsNullptrForNullLabel_2153)
{
  // Boundary: label is a const char* and may be passed as nullptr.
  // Observable expectation: function should not crash; it should return nullptr.
  PopplerPage *page = poppler_document_get_page_by_label(document_, nullptr);
  EXPECT_EQ(page, nullptr);
}

TEST_F(PopplerDocumentGetPageByLabelTest_2153, ReturnsNullptrForNonNumericLabel_2153)
{
  PopplerPage *page = poppler_document_get_page_by_label(document_, "A");
  EXPECT_EQ(page, nullptr);
}

} // namespace