// File: poppler-document-get-print-duplex-test_2198.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace {

class PrintDuplexTest_2198 : public ::testing::Test {
protected:
  void SetUp() override {
    // Create a temporary file path
    char tmpl[] = "/tmp/poppler_print_duplex_XXXXXX.pdf";
    int fd = g_mkstemp(tmpl);
    ASSERT_NE(fd, -1);

    // Close immediately; we will write via std::ofstream
#ifdef _WIN32
    _close(fd);
#else
    close(fd);
#endif

    pdf_path_ = tmpl;

    // Convert to file:// URI
    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(pdf_path_.c_str(), nullptr, &error);
    ASSERT_EQ(error, nullptr);
    ASSERT_NE(uri, nullptr);
    pdf_uri_.assign(uri);
    g_free(uri);
  }

  void TearDown() override {
    if (!pdf_path_.empty()) {
      std::remove(pdf_path_.c_str());
    }
  }

  static std::string BuildMinimalPdfWithDuplex(const char *duplex_name_or_null) {
    // Creates a minimal valid PDF with an optional Catalog /ViewerPreferences /Duplex entry.
    // duplex_name_or_null examples: "Simplex", "DuplexFlipShortEdge", "DuplexFlipLongEdge", "WeirdValue"
    std::ostringstream out;
    out << "%PDF-1.7\n";
    out << "%\xE2\xE3\xCF\xD3\n"; // binary comment

    std::vector<long> offsets;
    offsets.resize(5, 0);

    auto write_obj = [&](int objnum, const std::string &body) {
      offsets[objnum] = static_cast<long>(out.tellp());
      out << objnum << " 0 obj\n" << body << "\nendobj\n";
    };

    // 1: Catalog
    {
      std::ostringstream cat;
      cat << "<< /Type /Catalog /Pages 2 0 R";
      if (duplex_name_or_null) {
        cat << " /ViewerPreferences << /Duplex /" << duplex_name_or_null << " >>";
      }
      cat << " >>";
      write_obj(1, cat.str());
    }

    // 2: Pages
    write_obj(2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>");

    // 4: Contents stream (empty)
    {
      std::ostringstream stream;
      stream << "<< /Length 0 >>\nstream\n\nendstream";
      write_obj(4, stream.str());
    }

    // 3: Page
    write_obj(3,
              "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] "
              "/Contents 4 0 R /Resources << >> >>");

    // xref
    long xref_pos = static_cast<long>(out.tellp());
    out << "xref\n";
    out << "0 5\n";
    out << "0000000000 65535 f \n";
    for (int i = 1; i <= 4; ++i) {
      char buf[32];
      std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
      out << buf;
    }

    // trailer
    out << "trailer\n";
    out << "<< /Size 5 /Root 1 0 R >>\n";
    out << "startxref\n";
    out << xref_pos << "\n";
    out << "%%EOF\n";
    return out.str();
  }

  void WritePdfToTempFile(const std::string &pdf_bytes) {
    std::ofstream f(pdf_path_, std::ios::binary | std::ios::trunc);
    ASSERT_TRUE(f.is_open());
    f.write(pdf_bytes.data(), static_cast<std::streamsize>(pdf_bytes.size()));
    f.close();
  }

  PopplerDocument *OpenTempPdfOrFail() {
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file(pdf_uri_.c_str(), nullptr, &error);
    if (!doc) {
      std::string msg = "Failed to open PDF via poppler_document_new_from_file: ";
      msg += (error && error->message) ? error->message : "(no error message)";
      if (error) {
        g_error_free(error);
      }
      ADD_FAILURE() << msg;
      return nullptr;
    }
    if (error) {
      // Some builds might set warnings in error even if doc is non-null; free defensively.
      g_error_free(error);
    }
    return doc;
  }

  std::string pdf_path_;
  std::string pdf_uri_;
};

TEST_F(PrintDuplexTest_2198, NullDocumentReturnsNone_2198) {
  // Exceptional/error case: NULL input should trigger g_return_val_if_fail and return NONE.
  EXPECT_EQ(poppler_document_get_print_duplex(nullptr), POPPLER_PRINT_DUPLEX_NONE);
}

TEST_F(PrintDuplexTest_2198, NonDocumentPointerReturnsNone_2198) {
  // Exceptional/error case: non-PopplerDocument instance should fail POPPLER_IS_DOCUMENT.
  GObject *obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  EXPECT_EQ(poppler_document_get_print_duplex(reinterpret_cast<PopplerDocument *>(obj)),
            POPPLER_PRINT_DUPLEX_NONE);

  g_object_unref(obj);
}

TEST_F(PrintDuplexTest_2198, NoViewerPreferencesReturnsNone_2198) {
  // Normal/boundary: valid document but no ViewerPreferences => default NONE.
  WritePdfToTempFile(BuildMinimalPdfWithDuplex(nullptr));
  PopplerDocument *doc = OpenTempPdfOrFail();
  ASSERT_NE(doc, nullptr);

  EXPECT_EQ(poppler_document_get_print_duplex(doc), POPPLER_PRINT_DUPLEX_NONE);

  g_object_unref(doc);
}

TEST_F(PrintDuplexTest_2198, SimplexReturnsSimplex_2198) {
  // Normal operation: /Duplex /Simplex => POPPLER_PRINT_DUPLEX_SIMPLEX.
  WritePdfToTempFile(BuildMinimalPdfWithDuplex("Simplex"));
  PopplerDocument *doc = OpenTempPdfOrFail();
  ASSERT_NE(doc, nullptr);

  EXPECT_EQ(poppler_document_get_print_duplex(doc), POPPLER_PRINT_DUPLEX_SIMPLEX);

  g_object_unref(doc);
}

TEST_F(PrintDuplexTest_2198, DuplexFlipShortEdgeReturnsShortEdge_2198) {
  // Normal operation: /Duplex /DuplexFlipShortEdge => POPPLER_PRINT_DUPLEX_DUPLEX_FLIP_SHORT_EDGE.
  WritePdfToTempFile(BuildMinimalPdfWithDuplex("DuplexFlipShortEdge"));
  PopplerDocument *doc = OpenTempPdfOrFail();
  ASSERT_NE(doc, nullptr);

  EXPECT_EQ(poppler_document_get_print_duplex(doc), POPPLER_PRINT_DUPLEX_DUPLEX_FLIP_SHORT_EDGE);

  g_object_unref(doc);
}

TEST_F(PrintDuplexTest_2198, DuplexFlipLongEdgeReturnsLongEdge_2198) {
  // Normal operation: /Duplex /DuplexFlipLongEdge => POPPLER_PRINT_DUPLEX_DUPLEX_FLIP_LONG_EDGE.
  WritePdfToTempFile(BuildMinimalPdfWithDuplex("DuplexFlipLongEdge"));
  PopplerDocument *doc = OpenTempPdfOrFail();
  ASSERT_NE(doc, nullptr);

  EXPECT_EQ(poppler_document_get_print_duplex(doc), POPPLER_PRINT_DUPLEX_DUPLEX_FLIP_LONG_EDGE);

  g_object_unref(doc);
}

TEST_F(PrintDuplexTest_2198, UnknownDuplexValueFallsBackToNone_2198) {
  // Boundary/robustness: unexpected /Duplex name should map to default NONE (switch default).
  WritePdfToTempFile(BuildMinimalPdfWithDuplex("WeirdValue"));
  PopplerDocument *doc = OpenTempPdfOrFail();
  ASSERT_NE(doc, nullptr);

  EXPECT_EQ(poppler_document_get_print_duplex(doc), POPPLER_PRINT_DUPLEX_NONE);

  g_object_unref(doc);
}

} // namespace