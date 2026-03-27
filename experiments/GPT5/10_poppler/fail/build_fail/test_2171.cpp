// poppler_document_get_pdf_version_test_2171.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <iomanip>
#include <sstream>
#include <string>

namespace {

std::string BuildMinimalPdf(const std::string& version /* e.g. "1.7" */)
{
  std::ostringstream oss;
  oss << "%PDF-" << version << "\n";

  // Track byte offsets for xref.
  // Offsets are from beginning of file (byte index).
  std::vector<size_t> offsets;
  offsets.resize(5, 0); // objects 0..4 (0 is the free entry)

  auto cur_pos = [&]() -> size_t {
    return static_cast<size_t>(oss.tellp());
  };

  auto write_obj = [&](int obj_num, const std::string& body) {
    offsets[obj_num] = cur_pos();
    oss << obj_num << " 0 obj\n" << body << "\nendobj\n";
  };

  write_obj(1, "<< /Type /Catalog /Pages 2 0 R >>");
  write_obj(2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>");
  write_obj(3, "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 1 1] /Contents 4 0 R >>");
  // Empty stream for contents.
  write_obj(4, "<< /Length 0 >>\nstream\nendstream");

  const size_t xref_offset = cur_pos();
  oss << "xref\n";
  oss << "0 5\n";
  oss << "0000000000 65535 f \n";

  for (int i = 1; i <= 4; ++i) {
    oss << std::setw(10) << std::setfill('0') << offsets[i]
        << " 00000 n \n";
  }

  oss << "trailer\n";
  oss << "<< /Size 5 /Root 1 0 R >>\n";
  oss << "startxref\n";
  oss << xref_offset << "\n";
  oss << "%%EOF\n";

  return oss.str();
}

PopplerDocument* NewDocumentFromPdfDataOrNull(const std::string& pdf_data, GError** out_error)
{
  if (out_error) *out_error = nullptr;
  // poppler_document_new_from_data expects (const char*, int, const char*, GError**)
  // but is declared with gchar* in some versions; const_cast is fine for read-only use.
  return poppler_document_new_from_data(const_cast<char*>(pdf_data.data()),
                                       static_cast<int>(pdf_data.size()),
                                       /*password=*/nullptr,
                                       out_error);
}

class PopplerDocumentGetPdfVersionTest_2171 : public ::testing::Test {
 protected:
  void SetUp() override
  {
    pdf_1_7_ = BuildMinimalPdf("1.7");
    GError* error = nullptr;
    doc_ = NewDocumentFromPdfDataOrNull(pdf_1_7_, &error);
    ASSERT_NE(doc_, nullptr) << "Failed to create PopplerDocument for PDF 1.7";
    ASSERT_EQ(error, nullptr);
  }

  void TearDown() override
  {
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
  }

  std::string pdf_1_7_;
  PopplerDocument* doc_ = nullptr;
};

TEST_F(PopplerDocumentGetPdfVersionTest_2171, ReturnsExpectedMajorMinor_2171)
{
  guint major = 0;
  guint minor = 0;

  poppler_document_get_pdf_version(doc_, &major, &minor);

  EXPECT_EQ(major, 1u);
  EXPECT_EQ(minor, 7u);
}

TEST_F(PopplerDocumentGetPdfVersionTest_2171, NullMajorPointerDoesNotCrashAndSetsMinor_2171)
{
  guint minor = 0;

  poppler_document_get_pdf_version(doc_, /*major_version=*/nullptr, &minor);

  EXPECT_EQ(minor, 7u);
}

TEST_F(PopplerDocumentGetPdfVersionTest_2171, NullMinorPointerDoesNotCrashAndSetsMajor_2171)
{
  guint major = 0;

  poppler_document_get_pdf_version(doc_, &major, /*minor_version=*/nullptr);

  EXPECT_EQ(major, 1u);
}

TEST_F(PopplerDocumentGetPdfVersionTest_2171, BothOutputPointersNullDoesNotCrash_2171)
{
  // Observable behavior here is simply that the call returns without crashing.
  poppler_document_get_pdf_version(doc_, /*major_version=*/nullptr, /*minor_version=*/nullptr);

  SUCCEED();
}

TEST_F(PopplerDocumentGetPdfVersionTest_2171, NullDocumentDoesNotWriteOutputs_2171)
{
  // g_return_if_fail should return early; outputs should remain unchanged.
  guint major = 123;
  guint minor = 45;

  poppler_document_get_pdf_version(/*document=*/nullptr, &major, &minor);

  EXPECT_EQ(major, 123u);
  EXPECT_EQ(minor, 45u);
}

TEST_F(PopplerDocumentGetPdfVersionTest_2171, DifferentPdfVersionIsReported_2171)
{
  const std::string pdf_1_4 = BuildMinimalPdf("1.4");
  GError* error = nullptr;
  PopplerDocument* doc_1_4 = NewDocumentFromPdfDataOrNull(pdf_1_4, &error);

  ASSERT_NE(doc_1_4, nullptr) << "Failed to create PopplerDocument for PDF 1.4";
  ASSERT_EQ(error, nullptr);

  guint major = 0;
  guint minor = 0;
  poppler_document_get_pdf_version(doc_1_4, &major, &minor);

  EXPECT_EQ(major, 1u);
  EXPECT_EQ(minor, 4u);

  g_object_unref(doc_1_4);
}

} // namespace