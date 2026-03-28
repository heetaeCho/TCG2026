// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for poppler_document_get_pdf_subtype()
// File: ./TestProjects/poppler/glib/poppler-document-get-pdf-subtype-test.cc

#include <gtest/gtest.h>

#include <glib.h>
#include <glib/gstdio.h>
#include <poppler.h>

#include <cstdio>
#include <fstream>
#include <string>

namespace {

class PopplerDocumentGetPDFSubtypeTest_2203 : public ::testing::Test {
protected:
  void SetUp() override {
    // Create a temporary directory for test artifacts.
    GError *error = nullptr;
    tmp_dir_ = g_dir_make_tmp("poppler-gtest-2203-XXXXXX", &error);
    ASSERT_NE(tmp_dir_, nullptr) << (error ? error->message : "tmp dir creation failed");
    if (error) {
      g_error_free(error);
      error = nullptr;
    }

    pdf_path_ = std::string(tmp_dir_) + G_DIR_SEPARATOR_S + "minimal.pdf";
    ASSERT_TRUE(WriteMinimalPdf(pdf_path_));

    // Convert path to file:// URI for poppler_document_new_from_file().
    GFile *file = g_file_new_for_path(pdf_path_.c_str());
    ASSERT_NE(file, nullptr);
    char *uri = g_file_get_uri(file);
    g_object_unref(file);
    ASSERT_NE(uri, nullptr);
    pdf_uri_.assign(uri);
    g_free(uri);
  }

  void TearDown() override {
    if (!pdf_uri_.empty()) {
      pdf_uri_.clear();
    }
    if (!pdf_path_.empty()) {
      g_unlink(pdf_path_.c_str());
      pdf_path_.clear();
    }
    if (tmp_dir_) {
      g_rmdir(tmp_dir_);
      g_free(tmp_dir_);
      tmp_dir_ = nullptr;
    }
  }

  static bool WriteMinimalPdf(const std::string &path) {
    // A tiny, valid PDF with a single blank page.
    // (No explicit PDF/A, PDF/X, etc. conformance metadata is included.)
    static const char kPdf[] =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Contents 4 0 R >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Length 0 >>\n"
        "stream\n"
        "endstream\n"
        "endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000202 00000 n \n"
        "trailer\n"
        "<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n"
        "0261\n"
        "%%EOF\n";

    std::ofstream out(path, std::ios::binary);
    if (!out.is_open()) {
      return false;
    }
    out.write(kPdf, static_cast<std::streamsize>(sizeof(kPdf) - 1));
    out.close();
    return out.good();
  }

  PopplerDocument *OpenDocumentOrFail() const {
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file(pdf_uri_.c_str(), /*password=*/nullptr, &error);
    EXPECT_NE(doc, nullptr) << (error ? error->message : "poppler_document_new_from_file failed");
    if (error) {
      g_error_free(error);
    }
    return doc;
  }

  static bool IsKnownPopplerSubtype(PopplerPDFSubtype v) {
    switch (v) {
      case POPPLER_PDF_SUBTYPE_UNSET:
      case POPPLER_PDF_SUBTYPE_PDF_A:
      case POPPLER_PDF_SUBTYPE_PDF_E:
      case POPPLER_PDF_SUBTYPE_PDF_UA:
      case POPPLER_PDF_SUBTYPE_PDF_VT:
      case POPPLER_PDF_SUBTYPE_PDF_X:
      case POPPLER_PDF_SUBTYPE_NONE:
        return true;
      default:
        return false;
    }
  }

  char *tmp_dir_ = nullptr;
  std::string pdf_path_;
  std::string pdf_uri_;
};

TEST_F(PopplerDocumentGetPDFSubtypeTest_2203, NullDocumentReturnsNone_2203) {
  // Observable behavior from g_return_val_if_fail(): returns POPPLER_PDF_SUBTYPE_NONE on invalid input.
  PopplerPDFSubtype subtype = poppler_document_get_pdf_subtype(nullptr);
  EXPECT_EQ(subtype, POPPLER_PDF_SUBTYPE_NONE);
}

TEST_F(PopplerDocumentGetPDFSubtypeTest_2203, NonDocumentGObjectReturnsNone_2203) {
  // Pass a non-PopplerDocument instance; POPPLER_IS_DOCUMENT() should fail and return NONE.
  GObject *not_a_doc = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_a_doc, nullptr);

  PopplerPDFSubtype subtype =
      poppler_document_get_pdf_subtype(reinterpret_cast<PopplerDocument *>(not_a_doc));
  EXPECT_EQ(subtype, POPPLER_PDF_SUBTYPE_NONE);

  g_object_unref(not_a_doc);
}

TEST_F(PopplerDocumentGetPDFSubtypeTest_2203, ValidDocumentReturnsKnownEnumValue_2203) {
  PopplerDocument *doc = OpenDocumentOrFail();
  ASSERT_NE(doc, nullptr);

  PopplerPDFSubtype subtype = poppler_document_get_pdf_subtype(doc);
  EXPECT_TRUE(IsKnownPopplerSubtype(subtype));

  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetPDFSubtypeTest_2203, ValidDocumentIsDeterministicAcrossCalls_2203) {
  PopplerDocument *doc = OpenDocumentOrFail();
  ASSERT_NE(doc, nullptr);

  PopplerPDFSubtype a = poppler_document_get_pdf_subtype(doc);
  PopplerPDFSubtype b = poppler_document_get_pdf_subtype(doc);
  EXPECT_EQ(a, b);

  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetPDFSubtypeTest_2203, MinimalPdfDoesNotCrashAndReturnsKnownValue_2203) {
  // This test specifically exercises a minimal valid PDF created by the fixture.
  // We only assert that the return value is within the public enum and the call is safe.
  PopplerDocument *doc = OpenDocumentOrFail();
  ASSERT_NE(doc, nullptr);

  PopplerPDFSubtype subtype = poppler_document_get_pdf_subtype(doc);
  EXPECT_TRUE(IsKnownPopplerSubtype(subtype));

  g_object_unref(doc);
}

}  // namespace