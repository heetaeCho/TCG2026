#include <gtest/gtest.h>

#include <poppler.h>

#include <cmath>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace {

std::string BuildMinimalOnePagePdf(double width, double height, int rotate_degrees)
{
  // Minimal, self-contained PDF with one page and empty content stream.
  // MediaBox and CropBox are identical so Page::getCropWidth/Height should match width/height.
  //
  // Objects:
  // 1 0 obj: Catalog
  // 2 0 obj: Pages
  // 3 0 obj: Page (with /Rotate)
  // 4 0 obj: Contents (empty stream)

  std::ostringstream out;
  out << "%PDF-1.4\n";

  std::vector<long> offsets(5, 0);

  auto write_obj = [&](int objnum, const std::string &body) {
    offsets[objnum] = static_cast<long>(out.tellp());
    out << objnum << " 0 obj\n" << body << "\nendobj\n";
  };

  write_obj(1, "<< /Type /Catalog /Pages 2 0 R >>");

  write_obj(2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>");

  {
    std::ostringstream page;
    page << "<< /Type /Page /Parent 2 0 R "
         << "/MediaBox [0 0 " << std::fixed << std::setprecision(0) << width << " " << height << "] "
         << "/CropBox [0 0 " << std::fixed << std::setprecision(0) << width << " " << height << "] "
         << "/Rotate " << rotate_degrees << " "
         << "/Contents 4 0 R >>";
    write_obj(3, page.str());
  }

  // Empty content stream.
  write_obj(4, "<< /Length 0 >>\nstream\n\nendstream");

  const long xref_pos = static_cast<long>(out.tellp());
  out << "xref\n";
  out << "0 5\n";
  out << "0000000000 65535 f \n";
  for (int i = 1; i <= 4; ++i) {
    out << std::setw(10) << std::setfill('0') << offsets[i] << " 00000 n \n";
  }

  out << "trailer\n";
  out << "<< /Size 5 /Root 1 0 R >>\n";
  out << "startxref\n";
  out << xref_pos << "\n";
  out << "%%EOF\n";

  return out.str();
}

PopplerDocument *LoadDocFromDataOrFail(const std::string &pdf_bytes)
{
  GError *error = nullptr;
  PopplerDocument *doc =
      poppler_document_new_from_data(pdf_bytes.data(),
                                     static_cast<int>(pdf_bytes.size()),
                                     /*password=*/nullptr,
                                     &error);
  if (!doc) {
    std::string msg = "poppler_document_new_from_data failed";
    if (error && error->message) {
      msg += std::string(": ") + error->message;
    }
    if (error) {
      g_error_free(error);
    }
    ADD_FAILURE() << msg;
  }
  if (error) {
    // Some builds might still set a warning-like error; free defensively.
    g_error_free(error);
  }
  return doc;
}

}  // namespace

class PopplerPageGetSizeTest_2426 : public ::testing::Test {
protected:
  void TearDown() override
  {
    if (page_) {
      g_object_unref(page_);
      page_ = nullptr;
    }
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
  }

  void LoadOnePage(double w, double h, int rotate)
  {
    const std::string pdf = BuildMinimalOnePagePdf(w, h, rotate);
    doc_ = LoadDocFromDataOrFail(pdf);
    ASSERT_NE(doc_, nullptr);

    page_ = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page_, nullptr);
  }

  PopplerDocument *doc_ = nullptr;
  PopplerPage *page_ = nullptr;
};

TEST_F(PopplerPageGetSizeTest_2426, Rotate0ReturnsCropSize_2426)
{
  LoadOnePage(/*w=*/200, /*h=*/100, /*rotate=*/0);

  double w = 0.0, h = 0.0;
  poppler_page_get_size(page_, &w, &h);

  EXPECT_DOUBLE_EQ(w, 200.0);
  EXPECT_DOUBLE_EQ(h, 100.0);

  // Calling again should be stable/consistent.
  double w2 = 0.0, h2 = 0.0;
  poppler_page_get_size(page_, &w2, &h2);
  EXPECT_DOUBLE_EQ(w2, 200.0);
  EXPECT_DOUBLE_EQ(h2, 100.0);
}

TEST_F(PopplerPageGetSizeTest_2426, Rotate90SwapsWidthHeight_2426)
{
  LoadOnePage(/*w=*/200, /*h=*/100, /*rotate=*/90);

  double w = 0.0, h = 0.0;
  poppler_page_get_size(page_, &w, &h);

  // For 90 degrees, implementation swaps crop width/height into output.
  EXPECT_DOUBLE_EQ(w, 100.0);
  EXPECT_DOUBLE_EQ(h, 200.0);
}

TEST_F(PopplerPageGetSizeTest_2426, Rotate270SwapsWidthHeight_2426)
{
  LoadOnePage(/*w=*/300, /*h=*/120, /*rotate=*/270);

  double w = 0.0, h = 0.0;
  poppler_page_get_size(page_, &w, &h);

  EXPECT_DOUBLE_EQ(w, 120.0);
  EXPECT_DOUBLE_EQ(h, 300.0);
}

TEST_F(PopplerPageGetSizeTest_2426, NullOutParametersAreAllowed_2426)
{
  LoadOnePage(/*w=*/250, /*h=*/125, /*rotate=*/0);

  // width nullptr: height should still be written.
  double h = -1.0;
  poppler_page_get_size(page_, nullptr, &h);
  EXPECT_DOUBLE_EQ(h, 125.0);

  // height nullptr: width should still be written.
  double w = -1.0;
  poppler_page_get_size(page_, &w, nullptr);
  EXPECT_DOUBLE_EQ(w, 250.0);

  // both nullptr: should not crash.
  poppler_page_get_size(page_, nullptr, nullptr);
}

TEST_F(PopplerPageGetSizeTest_2426, NullPageReturnsWithoutWritingOutputs_2426)
{
  // g_return_if_fail(POPPLER_IS_PAGE(page)) => early return, no writes.
  double w = 123.0;
  double h = 456.0;

  poppler_page_get_size(nullptr, &w, &h);

  EXPECT_DOUBLE_EQ(w, 123.0);
  EXPECT_DOUBLE_EQ(h, 456.0);
}