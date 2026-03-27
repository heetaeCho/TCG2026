// File: poppler-document-get-print-scaling-test_2197.cc
//
// Unit tests for:
//   PopplerPrintScaling poppler_document_get_print_scaling(PopplerDocument *document)
//
// Constraints:
// - Treat implementation as black box
// - Only observable behavior via public API / return values
// - Include normal, boundary, and error cases
//
// TEST_ID: 2197

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h> // poppler-glib main header (PopplerDocument, poppler_document_new_from_file, etc.)

#include <cstdio>
#include <string>
#include <utility>

namespace {

class TempPdfFile {
public:
  explicit TempPdfFile(std::string contents)
  {
    // Create temp file path template
    gchar *tmpl = g_strdup("/tmp/poppler_print_scaling_XXXXXX.pdf");
    int fd = g_mkstemp(tmpl);
    path_.assign(tmpl);
    g_free(tmpl);

    if (fd < 0) {
      // If we can't create a temp file, fail fast.
      ADD_FAILURE() << "Failed to create temp file for PDF.";
      return;
    }

    // Write contents
    const gssize len = static_cast<gssize>(contents.size());
    const gssize written = write_all(fd, contents.data(), len);
    close_fd(fd);

    if (written != len) {
      ADD_FAILURE() << "Failed to write full PDF contents to temp file.";
    }
  }

  ~TempPdfFile()
  {
    if (!path_.empty()) {
      std::remove(path_.c_str());
    }
  }

  const std::string &path() const { return path_; }

  std::string file_uri() const
  {
    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(path_.c_str(), /*hostname=*/nullptr, &error);
    if (!uri) {
      std::string msg = "g_filename_to_uri failed";
      if (error) {
        msg += ": ";
        msg += error->message ? error->message : "(no message)";
        g_error_free(error);
      }
      ADD_FAILURE() << msg;
      return std::string();
    }
    std::string out(uri);
    g_free(uri);
    return out;
  }

private:
  static void close_fd(int fd)
  {
#if defined(G_OS_WIN32)
    _close(fd);
#else
    ::close(fd);
#endif
  }

  static gssize write_all(int fd, const char *buf, gssize len)
  {
    gssize total = 0;
    while (total < len) {
#if defined(G_OS_WIN32)
      const int n = _write(fd, buf + total, static_cast<unsigned int>(len - total));
      if (n <= 0) break;
      total += n;
#else
      const ssize_t n = ::write(fd, buf + total, static_cast<size_t>(len - total));
      if (n <= 0) break;
      total += static_cast<gssize>(n);
#endif
    }
    return total;
  }

  std::string path_;
};

struct GErrorDeleter {
  void operator()(GError *e) const
  {
    if (e) g_error_free(e);
  }
};

struct GObjectUnrefDeleter {
  void operator()(gpointer obj) const
  {
    if (obj) g_object_unref(obj);
  }
};

using UniqueGError = std::unique_ptr<GError, GErrorDeleter>;
using UniquePopplerDocument = std::unique_ptr<PopplerDocument, GObjectUnrefDeleter>;

// Minimal PDF helper:
// - Valid enough for Poppler to open
// - Allows optionally setting /ViewerPreferences with /PrintScaling
//
// Note: We do NOT test internal parsing; we only vary observable input PDFs and
// assert poppler_document_get_print_scaling() output.
static std::string MakeMinimalPdfWithOptionalViewerPreferences(const char *print_scaling_name_or_null)
{
  // Objects:
  // 1 0 obj: Catalog (optionally with /ViewerPreferences << /PrintScaling /None|/AppDefault >>)
  // 2 0 obj: Pages
  // 3 0 obj: Page
  // 4 0 obj: Contents (empty stream)
  //
  // Keep it simple; offsets are computed programmatically.
  std::string pdf;
  pdf += "%PDF-1.4\n";

  auto append_obj = [&](int obj_num, const std::string &body) -> size_t {
    const size_t offset = pdf.size();
    pdf += std::to_string(obj_num) + " 0 obj\n";
    pdf += body;
    if (!body.empty() && body.back() != '\n') pdf += "\n";
    pdf += "endobj\n";
    return offset;
  };

  std::string vp;
  if (print_scaling_name_or_null) {
    vp = " /ViewerPreferences << /PrintScaling /";
    vp += print_scaling_name_or_null;
    vp += " >>";
  }

  // 1: Catalog
  // /Type /Catalog /Pages 2 0 R [optional VP]
  size_t off1 = append_obj(1, "<< /Type /Catalog /Pages 2 0 R" + vp + " >>\n");

  // 2: Pages
  size_t off2 = append_obj(2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n");

  // 3: Page
  // Provide a minimal MediaBox and Contents
  size_t off3 = append_obj(3, "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 10 10] /Contents 4 0 R >>\n");

  // 4: Empty contents stream
  size_t off4 = pdf.size();
  pdf += "4 0 obj\n<< /Length 0 >>\nstream\nendstream\nendobj\n";

  // xref
  const size_t xref_offset = pdf.size();
  pdf += "xref\n0 5\n";
  pdf += "0000000000 65535 f \n";

  auto xref_line = [&](size_t off) {
    // 10-digit, zero-padded offset, then " 00000 n"
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010zu 00000 n \n", off);
    pdf += buf;
  };

  xref_line(off1);
  xref_line(off2);
  xref_line(off3);
  xref_line(off4);

  // trailer
  pdf += "trailer\n<< /Size 5 /Root 1 0 R >>\n";
  pdf += "startxref\n" + std::to_string(xref_offset) + "\n%%EOF\n";

  return pdf;
}

class PopplerDocumentPrintScalingTest_2197 : public ::testing::Test {
protected:
  UniquePopplerDocument OpenDocFromPdfString(const std::string &pdf_bytes)
  {
    TempPdfFile tmp(pdf_bytes);
    const std::string uri = tmp.file_uri();
    if (uri.empty()) return UniquePopplerDocument(nullptr);

    UniqueGError error(nullptr);
    GError *raw_error = nullptr;

    PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(),
                                                          /*password=*/nullptr,
                                                          &raw_error);
    error.reset(raw_error);

    if (!doc) {
      std::string msg = "poppler_document_new_from_file returned NULL";
      if (error) {
        msg += ": ";
        msg += error->message ? error->message : "(no message)";
      }
      ADD_FAILURE() << msg;
      return UniquePopplerDocument(nullptr);
    }

    return UniquePopplerDocument(doc);
  }
};

} // namespace

// ----------------------- Tests (TEST_ID: 2197) -----------------------

TEST_F(PopplerDocumentPrintScalingTest_2197, NullDocumentReturnsAppDefault_2197)
{
  // Error case: g_return_val_if_fail() should return APP_DEFAULT for invalid document.
  const PopplerPrintScaling scaling = poppler_document_get_print_scaling(nullptr);
  EXPECT_EQ(scaling, POPPLER_PRINT_SCALING_APP_DEFAULT);
}

TEST_F(PopplerDocumentPrintScalingTest_2197, PdfWithoutViewerPreferencesReturnsAppDefault_2197)
{
  // Boundary/normal: Catalog exists but has no /ViewerPreferences.
  const std::string pdf = MakeMinimalPdfWithOptionalViewerPreferences(nullptr);
  auto doc = OpenDocFromPdfString(pdf);
  ASSERT_NE(doc.get(), nullptr);

  const PopplerPrintScaling scaling = poppler_document_get_print_scaling(doc.get());
  EXPECT_EQ(scaling, POPPLER_PRINT_SCALING_APP_DEFAULT);
}

TEST_F(PopplerDocumentPrintScalingTest_2197, PdfWithPrintScalingNoneReturnsNone_2197)
{
  // Normal operation: /ViewerPreferences << /PrintScaling /None >>
  const std::string pdf = MakeMinimalPdfWithOptionalViewerPreferences("None");
  auto doc = OpenDocFromPdfString(pdf);
  ASSERT_NE(doc.get(), nullptr);

  const PopplerPrintScaling scaling = poppler_document_get_print_scaling(doc.get());
  EXPECT_EQ(scaling, POPPLER_PRINT_SCALING_NONE);
}

TEST_F(PopplerDocumentPrintScalingTest_2197, PdfWithPrintScalingAppDefaultReturnsAppDefault_2197)
{
  // Normal operation: /ViewerPreferences << /PrintScaling /AppDefault >>
  const std::string pdf = MakeMinimalPdfWithOptionalViewerPreferences("AppDefault");
  auto doc = OpenDocFromPdfString(pdf);
  ASSERT_NE(doc.get(), nullptr);

  const PopplerPrintScaling scaling = poppler_document_get_print_scaling(doc.get());
  EXPECT_EQ(scaling, POPPLER_PRINT_SCALING_APP_DEFAULT);
}

TEST_F(PopplerDocumentPrintScalingTest_2197, PdfWithUnknownPrintScalingFallsBackToAppDefault_2197)
{
  // Boundary: Provide an unrecognized name; observable behavior should fall back
  // to APP_DEFAULT (via default branch in switch or absence of recognized enum).
  // We don't assume internal mapping beyond "unknown should not become NONE".
  const std::string pdf = MakeMinimalPdfWithOptionalViewerPreferences("TotallyNotARealValue");
  auto doc = OpenDocFromPdfString(pdf);
  ASSERT_NE(doc.get(), nullptr);

  const PopplerPrintScaling scaling = poppler_document_get_print_scaling(doc.get());
  EXPECT_EQ(scaling, POPPLER_PRINT_SCALING_APP_DEFAULT);
}