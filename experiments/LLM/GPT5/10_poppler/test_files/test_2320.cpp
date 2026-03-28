// poppler-form-field-get-alternate-ui-name-test_2320.cc
//
// Unit tests for:
//   gchar *poppler_form_field_get_alternate_ui_name(PopplerFormField *field)
//
// These tests treat the implementation as a black box and verify only observable behavior
// through the public Poppler GLib API by loading small in-memory PDFs that either contain
// or omit a field alternate UI name (/TU).

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace {

class PopplerFormFieldGetAlternateUiNameTest_2320 : public ::testing::Test {
protected:
  static std::string BuildPdfWithOptionalTUEntry(const std::string& tu_entry_or_empty) {
    // Minimal PDF with one page and one widget annotation that is also a field.
    // If tu_entry_or_empty is non-empty, it must already be a valid PDF dictionary entry,
    // e.g. "/TU (AltName)" or "/TU <FEFFC548>".
    //
    // Objects:
    //  1: Catalog
    //  2: Pages
    //  3: Page (Annots [5 0 R])
    //  4: AcroForm (Fields [5 0 R])
    //  5: Widget annotation / field dictionary (contains /TU optionally)
    //  7: Font (Helvetica)
    //
    // Note: We keep this as simple as possible while still allowing Poppler to expose a
    // PopplerFormField via poppler_page_get_form_field_mapping().

    std::vector<std::string> objs;
    objs.reserve(7);

    // 1 0 obj: Catalog
    objs.push_back(
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R /AcroForm 4 0 R >>\n"
        "endobj\n");

    // 2 0 obj: Pages
    objs.push_back(
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n");

    // 3 0 obj: Page
    objs.push_back(
        "3 0 obj\n"
        "<< /Type /Page\n"
        "   /Parent 2 0 R\n"
        "   /MediaBox [0 0 612 792]\n"
        "   /Resources << /Font << /Helv 7 0 R >> >>\n"
        "   /Annots [5 0 R]\n"
        ">>\n"
        "endobj\n");

    // 4 0 obj: AcroForm
    objs.push_back(
        "4 0 obj\n"
        "<< /Fields [5 0 R]\n"
        "   /DA (/Helv 0 Tf 0 g)\n"
        ">>\n"
        "endobj\n");

    // 5 0 obj: Widget annotation that also acts as the field (merged dict)
    // Include /TU only if requested.
    {
      std::ostringstream ann;
      ann << "5 0 obj\n"
          << "<< /Type /Annot\n"
          << "   /Subtype /Widget\n"
          << "   /Rect [50 700 250 730]\n"
          << "   /P 3 0 R\n"
          << "   /FT /Tx\n"
          << "   /T (FieldName)\n";
      if (!tu_entry_or_empty.empty()) {
        ann << "   " << tu_entry_or_empty << "\n";
      }
      ann << "   /V (Value)\n"
          << ">>\n"
          << "endobj\n";
      objs.push_back(ann.str());
    }

    // 6 is unused in this tiny file; we’ll just skip to 7 for the font.
    // 7 0 obj: Helvetica font
    objs.push_back(
        "7 0 obj\n"
        "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
        "endobj\n");

    // Build the full PDF while recording xref offsets.
    std::string pdf;
    pdf.reserve(4096);
    pdf += "%PDF-1.4\n";

    // Track offsets for object numbers 1,2,3,4,5,7.
    // We will emit an xref table sized up to 7.
    std::vector<long> offsets(8, -1);  // index by obj number

    auto append_obj = [&](int objno, const std::string& body) {
      offsets[objno] = static_cast<long>(pdf.size());
      pdf += body;
    };

    append_obj(1, objs[0]);
    append_obj(2, objs[1]);
    append_obj(3, objs[2]);
    append_obj(4, objs[3]);
    append_obj(5, objs[4]);
    append_obj(7, objs[5]);

    const long xref_offset = static_cast<long>(pdf.size());

    // xref for 0..7
    std::ostringstream xref;
    xref << "xref\n";
    xref << "0 8\n";
    xref << "0000000000 65535 f \n";
    for (int i = 1; i <= 7; ++i) {
      if (offsets[i] < 0) {
        // unused object slot
        xref << "0000000000 65535 f \n";
      } else {
        xref << std::setw(10) << std::setfill('0') << offsets[i] << " 00000 n \n";
      }
    }

    pdf += xref.str();

    std::ostringstream trailer;
    trailer << "trailer\n"
            << "<< /Size 8\n"
            << "   /Root 1 0 R\n"
            << ">>\n"
            << "startxref\n"
            << xref_offset << "\n"
            << "%%EOF\n";

    pdf += trailer.str();
    return pdf;
  }

  static PopplerDocument* NewDocumentFromPdfDataOrFail(const std::string& pdf_data) {
    GError* error = nullptr;
    PopplerDocument* doc =
        poppler_document_new_from_data(pdf_data.c_str(),
                                       static_cast<int>(pdf_data.size()),
                                       /*password=*/nullptr,
                                       &error);
    if (!doc) {
      std::string msg = "poppler_document_new_from_data failed";
      if (error && error->message) {
        msg += ": ";
        msg += error->message;
      }
      if (error) {
        g_error_free(error);
      }
      ADD_FAILURE() << msg;
      return nullptr;
    }
    if (error) {
      // Poppler usually sets doc==nullptr on error, but be defensive.
      g_error_free(error);
    }
    return doc;
  }

  static PopplerFormField* FirstFormFieldFromFirstPageOrFail(PopplerDocument* doc) {
    PopplerPage* page = poppler_document_get_page(doc, 0);
    if (!page) {
      ADD_FAILURE() << "Failed to get page 0";
      return nullptr;
    }

    GList* mappings = poppler_page_get_form_field_mapping(page);
    g_object_unref(page);

    if (!mappings) {
      ADD_FAILURE() << "No form field mappings returned";
      return nullptr;
    }

    auto* mapping = static_cast<PopplerFormFieldMapping*>(mappings->data);
    if (!mapping || !mapping->field) {
      poppler_page_free_form_field_mapping(mappings);
      ADD_FAILURE() << "Form field mapping missing field";
      return nullptr;
    }

    // Hold a ref to the field so it stays valid after freeing mappings.
    PopplerFormField* field = mapping->field;
    g_object_ref(field);

    poppler_page_free_form_field_mapping(mappings);
    return field;
  }
};

TEST_F(PopplerFormFieldGetAlternateUiNameTest_2320, NullFieldReturnsNull_2320) {
  // Observable error case via g_return_val_if_fail: should return NULL.
  gchar* s = poppler_form_field_get_alternate_ui_name(nullptr);
  EXPECT_EQ(nullptr, s);
}

TEST_F(PopplerFormFieldGetAlternateUiNameTest_2320, MissingTUEntryReturnsNull_2320) {
  // No /TU in field dict -> getAlternateUiName likely returns null -> API returns nullptr.
  const std::string pdf = BuildPdfWithOptionalTUEntry(/*tu_entry_or_empty=*/"");
  PopplerDocument* doc = NewDocumentFromPdfDataOrFail(pdf);
  ASSERT_NE(nullptr, doc);

  PopplerFormField* field = FirstFormFieldFromFirstPageOrFail(doc);
  ASSERT_NE(nullptr, field);

  gchar* alt = poppler_form_field_get_alternate_ui_name(field);
  EXPECT_EQ(nullptr, alt);

  g_object_unref(field);
  g_object_unref(doc);
}

TEST_F(PopplerFormFieldGetAlternateUiNameTest_2320, TUAsciiStringReturnsUtf8_2320) {
  const std::string pdf = BuildPdfWithOptionalTUEntry("/TU (Alternate UI Name)");
  PopplerDocument* doc = NewDocumentFromPdfDataOrFail(pdf);
  ASSERT_NE(nullptr, doc);

  PopplerFormField* field = FirstFormFieldFromFirstPageOrFail(doc);
  ASSERT_NE(nullptr, field);

  gchar* alt = poppler_form_field_get_alternate_ui_name(field);
  ASSERT_NE(nullptr, alt);
  EXPECT_STREQ("Alternate UI Name", alt);

  g_free(alt);
  g_object_unref(field);
  g_object_unref(doc);
}

TEST_F(PopplerFormFieldGetAlternateUiNameTest_2320, TUEmptyStringReturnsNonNullEmpty_2320) {
  // Boundary condition: empty TU string.
  const std::string pdf = BuildPdfWithOptionalTUEntry("/TU ()");
  PopplerDocument* doc = NewDocumentFromPdfDataOrFail(pdf);
  ASSERT_NE(nullptr, doc);

  PopplerFormField* field = FirstFormFieldFromFirstPageOrFail(doc);
  ASSERT_NE(nullptr, field);

  gchar* alt = poppler_form_field_get_alternate_ui_name(field);
  ASSERT_NE(nullptr, alt);
  EXPECT_STREQ("", alt);

  g_free(alt);
  g_object_unref(field);
  g_object_unref(doc);
}

TEST_F(PopplerFormFieldGetAlternateUiNameTest_2320, TUUtf16HexStringDecodesToUtf8_2320) {
  // Boundary/encoding case: UTF-16BE with BOM in a hex string.
  // U+C548 == "안", so <FE FF C5 48>
  const std::string pdf = BuildPdfWithOptionalTUEntry("/TU <FEFFC548>");
  PopplerDocument* doc = NewDocumentFromPdfDataOrFail(pdf);
  ASSERT_NE(nullptr, doc);

  PopplerFormField* field = FirstFormFieldFromFirstPageOrFail(doc);
  ASSERT_NE(nullptr, field);

  gchar* alt = poppler_form_field_get_alternate_ui_name(field);
  ASSERT_NE(nullptr, alt);
  EXPECT_STREQ(u8"안", alt);

  g_free(alt);
  g_object_unref(field);
  g_object_unref(doc);
}

}  // namespace