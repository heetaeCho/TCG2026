// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for poppler_page_get_duration()
// File: ./TestProjects/poppler/glib/poppler-page.cc
//
// Function under test:
//   double poppler_page_get_duration(PopplerPage *page)
//
// Constraints respected:
// - Treat implementation as black box
// - Use only public/observable behavior
// - No access to private/internal state

#include <gtest/gtest.h>

#include <poppler.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <cmath>
#include <cstdint>
#include <fstream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

namespace {

class PopplerPageDurationTest_2429 : public ::testing::Test {
protected:
  void SetUp() override {
    // Create a temp directory for test PDFs.
    gchar *tmpdir_tpl = g_build_filename(g_get_tmp_dir(), "poppler-page-duration-XXXXXX", nullptr);
    temp_dir_ = g_mkdtemp(tmpdir_tpl);
    ASSERT_NE(temp_dir_, nullptr);
    // g_mkdtemp modifies buffer in-place; keep ownership to free later.
    temp_dir_buf_.reset(tmpdir_tpl);
  }

  void TearDown() override {
    // Best-effort cleanup of created files and directory.
    for (const auto &p : created_files_) {
      g_unlink(p.c_str());
    }
    if (temp_dir_) {
      g_rmdir(temp_dir_);
    }
  }

  struct GCharDeleter {
    void operator()(gchar *p) const { g_free(p); }
  };

  std::unique_ptr<gchar, GCharDeleter> temp_dir_buf_{nullptr};
  gchar *temp_dir_{nullptr};
  std::vector<std::string> created_files_;

  static std::string BuildMinimalPdfWithOptionalDur(std::optional<double> dur_seconds) {
    // Build a minimal valid PDF with 1 page.
    // Page dictionary includes /Dur <value> if dur_seconds has value.
    //
    // Objects:
    //  1 0 obj: Catalog
    //  2 0 obj: Pages
    //  3 0 obj: Page (optional /Dur)
    //  4 0 obj: Contents (empty stream)
    std::vector<std::string> objects;
    objects.reserve(4);

    objects.emplace_back(
        "<< /Type /Catalog /Pages 2 0 R >>");

    objects.emplace_back(
        "<< /Type /Pages /Count 1 /Kids [3 0 R] >>");

    {
      std::ostringstream page;
      page << "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Contents 4 0 R";
      if (dur_seconds.has_value()) {
        // Serialize with enough precision to round-trip.
        page.setf(std::ios::fixed);
        page.precision(10);
        page << " /Dur " << *dur_seconds;
      }
      page << " >>";
      objects.emplace_back(page.str());
    }

    // Empty content stream.
    objects.emplace_back(
        "<< /Length 0 >>\n"
        "stream\n"
        "\n"
        "endstream");

    std::ostringstream pdf;
    pdf << "%PDF-1.4\n";

    // Offsets for xref (object 0 is special).
    // xref needs 0..4 inclusive => 5 entries.
    std::vector<std::uint64_t> offsets(5, 0);

    for (int i = 0; i < 4; ++i) {
      const int obj_num = i + 1;
      offsets[obj_num] = static_cast<std::uint64_t>(pdf.tellp());
      pdf << obj_num << " 0 obj\n" << objects[i] << "\nendobj\n";
    }

    const std::uint64_t xref_pos = static_cast<std::uint64_t>(pdf.tellp());
    pdf << "xref\n";
    pdf << "0 5\n";
    // Object 0: free entry
    pdf << "0000000000 65535 f \n";
    // Objects 1..4: in-use entries
    for (int obj_num = 1; obj_num <= 4; ++obj_num) {
      // Each offset is 10 digits, leading zeros.
      char buf[32];
      std::snprintf(buf, sizeof(buf), "%010llu", static_cast<unsigned long long>(offsets[obj_num]));
      pdf << buf << " 00000 n \n";
    }

    pdf << "trailer\n";
    pdf << "<< /Size 5 /Root 1 0 R >>\n";
    pdf << "startxref\n";
    pdf << xref_pos << "\n";
    pdf << "%%EOF\n";

    return pdf.str();
  }

  std::string WritePdfToTempFile(const std::string &pdf_bytes, const char *basename) {
    ASSERT_NE(temp_dir_, nullptr);

    gchar *path = g_build_filename(temp_dir_, basename, nullptr);
    std::string out_path = path;
    g_free(path);

    std::ofstream ofs(out_path, std::ios::binary);
    EXPECT_TRUE(ofs.good());
    ofs.write(pdf_bytes.data(), static_cast<std::streamsize>(pdf_bytes.size()));
    ofs.close();
    EXPECT_TRUE(ofs.good());

    created_files_.push_back(out_path);
    return out_path;
  }

  static std::string PathToFileUri(const std::string &path) {
    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(path.c_str(), /*hostname=*/nullptr, &error);
    EXPECT_EQ(error, nullptr) << (error ? error->message : "");
    EXPECT_NE(uri, nullptr);
    std::string out = uri ? uri : "";
    g_free(uri);
    if (error) {
      g_error_free(error);
    }
    return out;
  }

  static PopplerDocument *OpenDocumentFromUri(const std::string &uri) {
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &error);
    EXPECT_EQ(error, nullptr) << (error ? error->message : "");
    if (error) {
      g_error_free(error);
    }
    return doc;
  }

  static PopplerPage *GetFirstPage(PopplerDocument *doc) {
    EXPECT_NE(doc, nullptr);
    if (!doc) {
      return nullptr;
    }
    PopplerPage *page = poppler_document_get_page(doc, 0);
    EXPECT_NE(page, nullptr);
    return page;
  }
};

TEST_F(PopplerPageDurationTest_2429, NullPageReturnsMinusOne_2429) {
  // Observable behavior: g_return_val_if_fail should return -1 for invalid input.
  EXPECT_EQ(poppler_page_get_duration(nullptr), -1);
}

TEST_F(PopplerPageDurationTest_2429, DurationPresentReturnsExactValue_2429) {
  const double expected = 5.5;
  const std::string pdf = BuildMinimalPdfWithOptionalDur(expected);
  const std::string path = WritePdfToTempFile(pdf, "dur_present.pdf");
  const std::string uri = PathToFileUri(path);

  PopplerDocument *doc = OpenDocumentFromUri(uri);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = GetFirstPage(doc);
  ASSERT_NE(page, nullptr);

  const double got = poppler_page_get_duration(page);
  EXPECT_NEAR(got, expected, 1e-9);

  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageDurationTest_2429, ZeroDurationBoundary_2429) {
  const double expected = 0.0;
  const std::string pdf = BuildMinimalPdfWithOptionalDur(expected);
  const std::string path = WritePdfToTempFile(pdf, "dur_zero.pdf");
  const std::string uri = PathToFileUri(path);

  PopplerDocument *doc = OpenDocumentFromUri(uri);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = GetFirstPage(doc);
  ASSERT_NE(page, nullptr);

  const double got = poppler_page_get_duration(page);
  EXPECT_NEAR(got, expected, 1e-12);

  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageDurationTest_2429, LargeDurationBoundary_2429) {
  const double expected = 12345.6789;
  const std::string pdf = BuildMinimalPdfWithOptionalDur(expected);
  const std::string path = WritePdfToTempFile(pdf, "dur_large.pdf");
  const std::string uri = PathToFileUri(path);

  PopplerDocument *doc = OpenDocumentFromUri(uri);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = GetFirstPage(doc);
  ASSERT_NE(page, nullptr);

  const double got = poppler_page_get_duration(page);
  EXPECT_NEAR(got, expected, 1e-7);

  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageDurationTest_2429, MissingDurationIsStableAndFinite_2429) {
  // When /Dur is absent, exact return value is implementation-defined.
  // We verify observable, implementation-agnostic properties:
  // - Call is stable across repeated invocations for the same PopplerPage
  // - Value is finite (not NaN/inf)
  const std::string pdf = BuildMinimalPdfWithOptionalDur(std::nullopt);
  const std::string path = WritePdfToTempFile(pdf, "dur_missing.pdf");
  const std::string uri = PathToFileUri(path);

  PopplerDocument *doc = OpenDocumentFromUri(uri);
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = GetFirstPage(doc);
  ASSERT_NE(page, nullptr);

  const double a = poppler_page_get_duration(page);
  const double b = poppler_page_get_duration(page);

  EXPECT_EQ(a, b);
  EXPECT_TRUE(std::isfinite(a));

  g_object_unref(page);
  g_object_unref(doc);
}

}  // namespace