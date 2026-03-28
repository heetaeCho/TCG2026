// poppler_document_get_print_n_copies_test_2199.cc
//
// Unit tests for:
//   gint poppler_document_get_print_n_copies(PopplerDocument *document);
//
// Constraints honored:
// - Treat implementation as black box
// - Test only via public interface / observable behavior (return values)
// - No access to private/internal state
//
// TEST_ID: 2199

#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

#include <cstdio>
#include <cstring>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace {

class PopplerDocumentGetPrintNCopiesTest_2199 : public ::testing::Test {
protected:
  void TearDown() override {
    // Remove any temp files created by helpers.
    for (const auto &p : temp_paths_) {
      if (!p.empty()) {
        g_remove(p.c_str());
      }
    }
    temp_paths_.clear();
  }

  // Builds a minimal, valid PDF with optional ViewerPreferences/NumCopies.
  // Returns the PDF bytes.
  static std::string BuildMinimalPdfBytesWithNumCopies(std::optional<int> numCopies) {
    // Objects:
    // 1 0: Catalog, optionally includes /ViewerPreferences << /NumCopies N >>
    // 2 0: Pages
    // 3 0: Page
    // 4 0: Contents (empty stream)
    std::vector<std::string> objs;
    objs.reserve(4);

    {
      std::ostringstream cat;
      cat << "1 0 obj\n"
          << "<< /Type /Catalog\n"
          << "   /Pages 2 0 R\n";
      if (numCopies.has_value()) {
        cat << "   /ViewerPreferences << /NumCopies " << *numCopies << " >>\n";
      }
      cat << ">>\n"
          << "endobj\n";
      objs.push_back(cat.str());
    }

    objs.push_back(
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n");

    objs.push_back(
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 10 10]\n"
        "   /Resources << >>\n"
        "   /Contents 4 0 R\n"
        ">>\n"
        "endobj\n");

    objs.push_back(
        "4 0 obj\n"
        "<< /Length 0 >>\n"
        "stream\n"
        "\n"
        "endstream\n"
        "endobj\n");

    // Assemble PDF while recording byte offsets for xref.
    std::string pdf;
    pdf.reserve(2048);

    pdf += "%PDF-1.5\n";
    // Track offsets for objects 1..4 (xref also needs object 0).
    std::vector<size_t> offsets(5, 0);

    for (int i = 0; i < 4; ++i) {
      offsets[i + 1] = pdf.size();
      pdf += objs[i];
    }

    const size_t xref_offset = pdf.size();

    // xref table: 0..4
    // Each entry is "0000000000 65535 f \n" or "0000000000 00000 n \n"
    auto fmt_off = [](size_t off) {
      char buf[32];
      std::snprintf(buf, sizeof(buf), "%010zu", off);
      return std::string(buf);
    };

    pdf += "xref\n";
    pdf += "0 5\n";
    pdf += "0000000000 65535 f \n";
    for (int objNum = 1; objNum <= 4; ++objNum) {
      pdf += fmt_off(offsets[objNum]);
      pdf += " 00000 n \n";
    }

    pdf += "trailer\n";
    pdf += "<< /Size 5 /Root 1 0 R >>\n";
    pdf += "startxref\n";
    pdf += std::to_string(xref_offset);
    pdf += "\n%%EOF\n";

    return pdf;
  }

  // Writes bytes to a temp file and returns (path, file:// URI).
  std::pair<std::string, std::string> WriteTempPdfAndGetUri(const std::string &bytes) {
    gchar *tmp_path = nullptr;
    gint fd = g_file_open_tmp("poppler_gtest_2199_XXXXXX.pdf", &tmp_path, nullptr);
    EXPECT_GE(fd, 0);
    EXPECT_NE(tmp_path, nullptr);

    // Ensure fd is closed even if assertions fail later.
    struct FdCloser {
      int fd;
      ~FdCloser() {
        if (fd >= 0) {
          close(fd);
        }
      }
    } closer{fd};

    const gssize to_write = static_cast<gssize>(bytes.size());
    const gssize written = write(fd, bytes.data(), to_write);
    EXPECT_EQ(written, to_write);

    std::string path(tmp_path);
    g_free(tmp_path);

    // Track for cleanup.
    temp_paths_.push_back(path);

    gchar *uri = g_filename_to_uri(path.c_str(), nullptr, nullptr);
    EXPECT_NE(uri, nullptr);
    std::string uri_str(uri);
    g_free(uri);

    return {path, uri_str};
  }

  // Loads a PopplerDocument from a local file URI.
  PopplerDocument *LoadDocFromUri(const std::string &uri) {
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
    if (!doc) {
      std::string msg = error ? error->message : "unknown error";
      if (error) {
        g_error_free(error);
      }
      ADD_FAILURE() << "Failed to load PopplerDocument: " << msg;
      return nullptr;
    }
    if (error) {
      g_error_free(error);
    }
    return doc;
  }

private:
  std::vector<std::string> temp_paths_;
};

TEST_F(PopplerDocumentGetPrintNCopiesTest_2199, NullDocumentReturnsDefault_2199) {
  // Observable error behavior: g_return_val_if_fail(..., 1) => returns 1.
  EXPECT_EQ(poppler_document_get_print_n_copies(nullptr), 1);
}

TEST_F(PopplerDocumentGetPrintNCopiesTest_2199, NoViewerPreferencesReturnsDefaultOne_2199) {
  const std::string pdf = BuildMinimalPdfBytesWithNumCopies(std::nullopt);
  const auto [path, uri] = WriteTempPdfAndGetUri(pdf);

  PopplerDocument *doc = LoadDocFromUri(uri);
  ASSERT_NE(doc, nullptr);

  EXPECT_EQ(poppler_document_get_print_n_copies(doc), 1);

  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetPrintNCopiesTest_2199, ReturnsNumCopiesWhenPresent_2199) {
  const std::string pdf = BuildMinimalPdfBytesWithNumCopies(3);
  const auto [path, uri] = WriteTempPdfAndGetUri(pdf);

  PopplerDocument *doc = LoadDocFromUri(uri);
  ASSERT_NE(doc, nullptr);

  EXPECT_EQ(poppler_document_get_print_n_copies(doc), 3);

  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetPrintNCopiesTest_2199, ReturnsDifferentValidValues_2199) {
  // Boundary-ish coverage: exercise multiple distinct positive values.
  for (int v : {1, 2, 9}) {
    const std::string pdf = BuildMinimalPdfBytesWithNumCopies(v);
    const auto [path, uri] = WriteTempPdfAndGetUri(pdf);

    PopplerDocument *doc = LoadDocFromUri(uri);
    ASSERT_NE(doc, nullptr) << "Failed to load doc for NumCopies=" << v;

    EXPECT_EQ(poppler_document_get_print_n_copies(doc), v) << "NumCopies=" << v;

    g_object_unref(doc);
  }
}

}  // namespace