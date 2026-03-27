// File: poppler-document-get-pdf-part-test_2204.cc
#include <gtest/gtest.h>

#include <glib-object.h>
#include <glib.h>

#include <poppler.h>

namespace {

class PopplerDocumentPdfPartTest_2204 : public ::testing::Test {
protected:
  static std::string BuildMinimalPdf_2204() {
    // Build a tiny valid PDF (1 empty page) with correct xref offsets.
    // This is test data generation (not re-implementing Poppler logic).
    std::string pdf;
    auto append = [&](const std::string& s) { pdf += s; };

    append("%PDF-1.4\n");
    // Object 1: Catalog
    const size_t off1 = pdf.size();
    append("1 0 obj\n");
    append("<< /Type /Catalog /Pages 2 0 R >>\n");
    append("endobj\n");
    // Object 2: Pages
    const size_t off2 = pdf.size();
    append("2 0 obj\n");
    append("<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n");
    append("endobj\n");
    // Object 3: Page
    const size_t off3 = pdf.size();
    append("3 0 obj\n");
    append("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Contents 4 0 R >>\n");
    append("endobj\n");
    // Object 4: Contents (empty stream)
    const size_t off4 = pdf.size();
    append("4 0 obj\n");
    append("<< /Length 0 >>\n");
    append("stream\n");
    append("\n");
    append("endstream\n");
    append("endobj\n");

    // XRef table
    const size_t xref_off = pdf.size();
    append("xref\n");
    append("0 5\n");
    // Entry 0 (free object)
    append("0000000000 65535 f \n");

    auto xref_line = [&](size_t off) {
      char buf[32];
      // 10-digit offset, 5-digit generation, then 'n'
      g_snprintf(buf, sizeof(buf), "%010u 00000 n \n", static_cast<unsigned>(off));
      return std::string(buf);
    };
    append(xref_line(off1));
    append(xref_line(off2));
    append(xref_line(off3));
    append(xref_line(off4));

    // Trailer
    append("trailer\n");
    append("<< /Size 5 /Root 1 0 R >>\n");
    append("startxref\n");
    {
      char buf[32];
      g_snprintf(buf, sizeof(buf), "%u\n", static_cast<unsigned>(xref_off));
      append(buf);
    }
    append("%%EOF\n");

    return pdf;
  }

  static PopplerDocument* NewDocumentFromMinimalPdf_2204(GError** error) {
#if POPPLER_CHECK_VERSION(0, 18, 0)
    // poppler_document_new_from_data() exists in many Poppler GLib versions.
    const std::string pdf = BuildMinimalPdf_2204();
    return poppler_document_new_from_data(pdf.data(),
                                          static_cast<int>(pdf.size()),
                                          /*password=*/nullptr,
                                          error);
#else
    // Fallback: write to temp file and open via poppler_document_new_from_file().
    // (Keep this path for older builds if needed.)
    const std::string pdf = BuildMinimalPdf_2204();
    gchar* tmpname = nullptr;
    gint fd = g_file_open_tmp("poppler_pdf_part_2204_XXXXXX.pdf", &tmpname, error);
    if (fd < 0) {
      return nullptr;
    }
    const gssize wrote = write(fd, pdf.data(), pdf.size());
    close(fd);
    if (wrote < 0 || static_cast<size_t>(wrote) != pdf.size()) {
      if (tmpname) {
        g_unlink(tmpname);
        g_free(tmpname);
      }
      g_set_error(error, G_FILE_ERROR, G_FILE_ERROR_FAILED, "Failed to write temp PDF");
      return nullptr;
    }
    gchar* uri = g_filename_to_uri(tmpname, nullptr, error);
    PopplerDocument* doc = nullptr;
    if (uri) {
      doc = poppler_document_new_from_file(uri, /*password=*/nullptr, error);
      g_free(uri);
    }
    if (tmpname) {
      g_unlink(tmpname);
      g_free(tmpname);
    }
    return doc;
#endif
  }
};

TEST_F(PopplerDocumentPdfPartTest_2204, NullDocumentReturnsNone_2204) {
  // Observable error path: g_return_val_if_fail should return *_NONE for invalid instance.
  const PopplerPDFPart part = poppler_document_get_pdf_part(nullptr);
  EXPECT_EQ(part, POPPLER_PDF_SUBTYPE_PART_NONE);
}

TEST_F(PopplerDocumentPdfPartTest_2204, NonDocumentInstanceReturnsNone_2204) {
  // Pass a valid GObject instance that is not a PopplerDocument.
  GObject* not_doc = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_doc, nullptr);

  const PopplerPDFPart part =
      poppler_document_get_pdf_part(reinterpret_cast<PopplerDocument*>(not_doc));
  EXPECT_EQ(part, POPPLER_PDF_SUBTYPE_PART_NONE);

  g_object_unref(not_doc);
}

TEST_F(PopplerDocumentPdfPartTest_2204, ValidDocumentReturnsEnumAndIsDeterministic_2204) {
  GError* error = nullptr;
  PopplerDocument* doc = NewDocumentFromMinimalPdf_2204(&error);
  ASSERT_NE(doc, nullptr) << (error ? error->message : "Failed to create PopplerDocument");
  if (error) {
    g_error_free(error);
    error = nullptr;
  }

  const PopplerPDFPart p1 = poppler_document_get_pdf_part(doc);
  const PopplerPDFPart p2 = poppler_document_get_pdf_part(doc);

  // We don't assume any specific PDF subtype part for this document (black-box);
  // we only assert it is a valid enum value and stable across calls.
  EXPECT_GE(static_cast<int>(p1), static_cast<int>(POPPLER_PDF_SUBTYPE_PART_UNSET));
  EXPECT_LE(static_cast<int>(p1), static_cast<int>(POPPLER_PDF_SUBTYPE_PART_NONE));
  EXPECT_EQ(p1, p2);

  g_object_unref(doc);
}

TEST_F(PopplerDocumentPdfPartTest_2204, TwoValidDocumentsEachReturnValidEnum_2204) {
  GError* error1 = nullptr;
  PopplerDocument* doc1 = NewDocumentFromMinimalPdf_2204(&error1);
  ASSERT_NE(doc1, nullptr) << (error1 ? error1->message : "Failed to create first PopplerDocument");
  if (error1) {
    g_error_free(error1);
    error1 = nullptr;
  }

  GError* error2 = nullptr;
  PopplerDocument* doc2 = NewDocumentFromMinimalPdf_2204(&error2);
  ASSERT_NE(doc2, nullptr) << (error2 ? error2->message : "Failed to create second PopplerDocument");
  if (error2) {
    g_error_free(error2);
    error2 = nullptr;
  }

  const PopplerPDFPart p1 = poppler_document_get_pdf_part(doc1);
  const PopplerPDFPart p2 = poppler_document_get_pdf_part(doc2);

  EXPECT_GE(static_cast<int>(p1), static_cast<int>(POPPLER_PDF_SUBTYPE_PART_UNSET));
  EXPECT_LE(static_cast<int>(p1), static_cast<int>(POPPLER_PDF_SUBTYPE_PART_NONE));

  EXPECT_GE(static_cast<int>(p2), static_cast<int>(POPPLER_PDF_SUBTYPE_PART_UNSET));
  EXPECT_LE(static_cast<int>(p2), static_cast<int>(POPPLER_PDF_SUBTYPE_PART_NONE));

  g_object_unref(doc2);
  g_object_unref(doc1);
}

}  // namespace