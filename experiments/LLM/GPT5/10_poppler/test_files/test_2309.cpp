// Copyright (C) 2026
// Unit tests for poppler_form_field_get_id()
// File: ./TestProjects/poppler/glib/poppler-form-field-get-id-test.cc

#include <gtest/gtest.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <poppler.h>

namespace {

class PopplerFormFieldGetIdTest_2309 : public ::testing::Test {
protected:
  void SetUp() override { }

  void TearDown() override {
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
    if (page_) {
      g_object_unref(page_);
      page_ = nullptr;
    }
    if (tmp_uri_) {
      g_free(tmp_uri_);
      tmp_uri_ = nullptr;
    }
    if (tmp_path_) {
      g_unlink(tmp_path_);
      g_free(tmp_path_);
      tmp_path_ = nullptr;
    }
  }

  // Builds a minimal PDF with two AcroForm text fields (each with a widget).
  // Returns the PDF bytes as a std::string.
  static std::string BuildPdfWithTwoTextFields() {
    // We'll construct objects and compute xref offsets programmatically to avoid mistakes.
    struct Obj {
      int num;
      std::string body; // without "n 0 obj" / "endobj"
    };

    // Content stream for the page.
    const std::string pageStream =
        "BT\n"
        "/F1 12 Tf\n"
        "72 720 Td\n"
        "(Hello) Tj\n"
        "ET\n";

    std::vector<Obj> objs;

    // 1: Catalog
    objs.push_back(
        {1, "<< /Type /Catalog /Pages 2 0 R /AcroForm 6 0 R >>\n"});

    // 2: Pages
    objs.push_back(
        {2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"});

    // 3: Page
    objs.push_back({3,
                    "<< /Type /Page\n"
                    "   /Parent 2 0 R\n"
                    "   /MediaBox [0 0 612 792]\n"
                    "   /Resources << /Font << /F1 4 0 R >> >>\n"
                    "   /Contents 5 0 R\n"
                    "   /Annots [7 0 R 8 0 R]\n"
                    ">>\n"});

    // 4: Font
    objs.push_back(
        {4, "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"});

    // 5: Contents stream
    {
      std::string streamObj;
      streamObj += "<< /Length " + std::to_string(pageStream.size()) + " >>\n";
      streamObj += "stream\n";
      streamObj += pageStream;
      streamObj += "endstream\n";
      objs.push_back({5, streamObj});
    }

    // 6: AcroForm with Fields [9 0 R 10 0 R]
    objs.push_back({6,
                    "<< /Fields [9 0 R 10 0 R]\n"
                    "   /DA (/F1 12 Tf 0 g)\n"
                    ">>\n"});

    // 7: Widget annotation for field 9
    objs.push_back({7,
                    "<< /Type /Annot /Subtype /Widget\n"
                    "   /Rect [72 680 200 700]\n"
                    "   /P 3 0 R\n"
                    "   /Parent 9 0 R\n"
                    ">>\n"});

    // 8: Widget annotation for field 10
    objs.push_back({8,
                    "<< /Type /Annot /Subtype /Widget\n"
                    "   /Rect [72 640 200 660]\n"
                    "   /P 3 0 R\n"
                    "   /Parent 10 0 R\n"
                    ">>\n"});

    // 9: Field 1 (text)
    objs.push_back({9,
                    "<< /FT /Tx\n"
                    "   /T (field1)\n"
                    "   /V (A)\n"
                    "   /Kids [7 0 R]\n"
                    ">>\n"});

    // 10: Field 2 (text)
    objs.push_back({10,
                    "<< /FT /Tx\n"
                    "   /T (field2)\n"
                    "   /V (B)\n"
                    "   /Kids [8 0 R]\n"
                    ">>\n"});

    std::string pdf;
    pdf += "%PDF-1.4\n";
    pdf += "%\xE2\xE3\xCF\xD3\n"; // binary comment

    // Track offsets for xref.
    std::vector<long> offsets;
    offsets.resize(11, 0); // 0..10

    auto appendObj = [&](int num, const std::string& body) {
      offsets[num] = static_cast<long>(pdf.size());
      pdf += std::to_string(num) + " 0 obj\n";
      pdf += body;
      pdf += "endobj\n";
    };

    for (const auto& o : objs) {
      appendObj(o.num, o.body);
    }

    const long xrefOffset = static_cast<long>(pdf.size());
    pdf += "xref\n";
    pdf += "0 11\n";
    // Object 0: free
    pdf += "0000000000 65535 f \n";
    for (int i = 1; i <= 10; ++i) {
      char buf[32];
      // 10-digit, zero-padded byte offset
      g_snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
      pdf += buf;
    }

    pdf += "trailer\n";
    pdf += "<< /Size 11 /Root 1 0 R >>\n";
    pdf += "startxref\n";
    pdf += std::to_string(xrefOffset) + "\n";
    pdf += "%%EOF\n";

    return pdf;
  }

  void CreateTempPdfAndOpenOrFail() {
    GError* error = nullptr;

    // Create tmp file path
    gchar* tmpPath = nullptr;
    int fd = g_file_open_tmp("poppler_form_field_get_id_2309_XXXXXX.pdf", &tmpPath, &error);
    ASSERT_NE(fd, -1) << (error ? error->message : "g_file_open_tmp failed");
    if (error) {
      g_error_free(error);
      error = nullptr;
    }

    // Write PDF bytes
    const std::string pdfBytes = BuildPdfWithTwoTextFields();
    gssize written = write(fd, pdfBytes.data(), pdfBytes.size());
    close(fd);
    ASSERT_EQ(written, static_cast<gssize>(pdfBytes.size()));

    tmp_path_ = tmpPath;

    // Build file:// URI
    tmp_uri_ = g_filename_to_uri(tmp_path_, /*hostname=*/nullptr, &error);
    ASSERT_NE(tmp_uri_, nullptr) << (error ? error->message : "g_filename_to_uri failed");
    if (error) {
      g_error_free(error);
      error = nullptr;
    }

    doc_ = poppler_document_new_from_file(tmp_uri_, /*password=*/nullptr, &error);
    ASSERT_NE(doc_, nullptr) << (error ? error->message : "poppler_document_new_from_file failed");
    if (error) {
      g_error_free(error);
      error = nullptr;
    }

    page_ = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page_, nullptr);
  }

  PopplerDocument* doc_ = nullptr;
  PopplerPage* page_ = nullptr;
  gchar* tmp_path_ = nullptr;
  gchar* tmp_uri_ = nullptr;
};

TEST_F(PopplerFormFieldGetIdTest_2309, NullFieldReturnsMinusOne_2309) {
  // g_return_val_if_fail should log a critical and return -1.
  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_FORM_FIELD*");
  gint id = poppler_form_field_get_id(nullptr);
  g_test_assert_expected_messages();

  EXPECT_EQ(id, -1);
}

TEST_F(PopplerFormFieldGetIdTest_2309, NonFormGObjectReturnsMinusOne_2309) {
  // Pass an object that is definitely not a PopplerFormField instance.
  GObject* obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_FORM_FIELD*");
  gint id = poppler_form_field_get_id(reinterpret_cast<PopplerFormField*>(obj));
  g_test_assert_expected_messages();

  EXPECT_EQ(id, -1);

  g_object_unref(obj);
}

TEST_F(PopplerFormFieldGetIdTest_2309, ValidFieldReturnsStableNonNegativeId_2309) {
  CreateTempPdfAndOpenOrFail();

  // Obtain at least one form field via public API.
  GList* mappings = poppler_page_get_form_field_mapping(page_);
  ASSERT_NE(mappings, nullptr);

  PopplerFormFieldMapping* m = static_cast<PopplerFormFieldMapping*>(mappings->data);
  ASSERT_NE(m, nullptr);
  ASSERT_NE(m->field, nullptr);

  const gint id1 = poppler_form_field_get_id(m->field);
  const gint id2 = poppler_form_field_get_id(m->field);

  // Observable expectations:
  // - For a valid PopplerFormField, it should not be the failure sentinel (-1).
  // - Repeated calls should be stable for the same field instance.
  EXPECT_NE(id1, -1);
  EXPECT_EQ(id1, id2);

  poppler_page_free_form_field_mapping(mappings);
}

TEST_F(PopplerFormFieldGetIdTest_2309, TwoDifferentFieldsHaveDifferentIds_2309) {
  CreateTempPdfAndOpenOrFail();

  GList* mappings = poppler_page_get_form_field_mapping(page_);
  ASSERT_NE(mappings, nullptr);

  // Collect first two distinct fields (if any).
  PopplerFormField* f1 = nullptr;
  PopplerFormField* f2 = nullptr;

  for (GList* l = mappings; l != nullptr; l = l->next) {
    auto* m = static_cast<PopplerFormFieldMapping*>(l->data);
    if (!m || !m->field) {
      continue;
    }
    if (!f1) {
      f1 = m->field;
      continue;
    }
    if (m->field != f1) {
      f2 = m->field;
      break;
    }
  }

  ASSERT_NE(f1, nullptr);
  ASSERT_NE(f2, nullptr);

  const gint id1 = poppler_form_field_get_id(f1);
  const gint id2 = poppler_form_field_get_id(f2);

  EXPECT_NE(id1, -1);
  EXPECT_NE(id2, -1);

  // For two different form fields in the same document/page, IDs should differ.
  EXPECT_NE(id1, id2);

  poppler_page_free_form_field_mapping(mappings);
}

} // namespace