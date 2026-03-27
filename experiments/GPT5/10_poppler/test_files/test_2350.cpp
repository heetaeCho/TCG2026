// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for poppler_form_field_choice_toggle_item()
// File: ./TestProjects/poppler/glib/poppler-form-field.cc (function under test)
//
// TEST_ID: 2350

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <fstream>
#include <memory>
#include <string>

namespace {

class PopplerFormFieldChoiceToggleItemTest_2350 : public ::testing::Test {
protected:
  static std::string WriteTestPdfToTemp_2350() {
    // Minimal PDF with 1 page and 2 widget annotations:
    //  - Choice field (FT=Ch) with 3 options
    //  - Text field (FT=Tx)
    //
    // Includes AcroForm /DR and /DA so Poppler can parse fields reliably.
    static const char kPdf[] =
        "%PDF-1.5\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R /AcroForm 6 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Count 1 /Kids [3 0 R] >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792]\n"
        "   /Resources << /Font << /Helv 5 0 R >> >>\n"
        "   /Annots [7 0 R 8 0 R]\n"
        "   /Contents 4 0 R\n"
        ">>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Length 0 >>\n"
        "stream\n"
        "endstream\n"
        "endobj\n"
        "5 0 obj\n"
        "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
        "endobj\n"
        "6 0 obj\n"
        "<< /Fields [7 0 R 8 0 R]\n"
        "   /DR << /Font << /Helv 5 0 R >> >>\n"
        "   /DA (/Helv 12 Tf 0 g)\n"
        ">>\n"
        "endobj\n"
        "7 0 obj\n"
        "<< /Type /Annot /Subtype /Widget\n"
        "   /FT /Ch\n"
        "   /T (Choice1)\n"
        "   /Rect [72 700 240 730]\n"
        "   /P 3 0 R\n"
        "   /F 4\n"
        "   /DA (/Helv 12 Tf 0 g)\n"
        "   /Opt [(One) (Two) (Three)]\n"
        "   /V (One)\n"
        ">>\n"
        "endobj\n"
        "8 0 obj\n"
        "<< /Type /Annot /Subtype /Widget\n"
        "   /FT /Tx\n"
        "   /T (Text1)\n"
        "   /Rect [72 650 240 680]\n"
        "   /P 3 0 R\n"
        "   /F 4\n"
        "   /DA (/Helv 12 Tf 0 g)\n"
        "   /V (Hello)\n"
        ">>\n"
        "endobj\n"
        "xref\n"
        "0 9\n"
        "0000000000 65535 f \n"
        "0000000010 00000 n \n"
        "0000000076 00000 n \n"
        "0000000135 00000 n \n"
        "0000000282 00000 n \n"
        "0000000351 00000 n \n"
        "0000000421 00000 n \n"
        "0000000544 00000 n \n"
        "0000000740 00000 n \n"
        "trailer\n"
        "<< /Size 9 /Root 1 0 R >>\n"
        "startxref\n"
        "0919\n"
        "%%EOF\n";

    const gchar *tmp_dir = g_get_tmp_dir();
    gchar *path = g_build_filename(tmp_dir, "poppler_form_choice_toggle_2350.pdf", nullptr);

    // Best effort: overwrite if exists.
    std::ofstream ofs(path, std::ios::binary | std::ios::trunc);
    ofs.write(kPdf, static_cast<std::streamsize>(sizeof(kPdf) - 1));
    ofs.close();

    std::string out(path);
    g_free(path);
    return out;
  }

  static std::string FileUriForPath_2350(const std::string &path) {
    // Poppler GLib expects file:// URI.
    // NOTE: path from g_get_tmp_dir() should not need URI escaping here.
    return std::string("file://") + path;
  }

  static PopplerDocument *LoadDoc_2350(const std::string &file_uri) {
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file(file_uri.c_str(), /*password=*/nullptr, &error);
    if (!doc) {
      std::string msg = "Failed to load test PDF: ";
      if (error && error->message) {
        msg += error->message;
      } else {
        msg += "(no GError message)";
      }
      if (error) {
        g_error_free(error);
      }
      ADD_FAILURE() << msg;
      return nullptr;
    }
    if (error) {
      g_error_free(error);
    }
    return doc;
  }

  static PopplerFormField *FindFieldByTypeOnFirstPage_2350(PopplerDocument *doc,
                                                           PopplerFormFieldType wanted_type) {
    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
      ADD_FAILURE() << "poppler_document_get_page(0) returned NULL";
      return nullptr;
    }

    // Mapping list contains PopplerFormFieldMapping { PopplerFormField* field; PopplerRectangle area; }
    GList *mappings = poppler_page_get_form_field_mapping(page);
    PopplerFormField *found = nullptr;

    for (GList *l = mappings; l; l = l->next) {
      auto *mapping = static_cast<PopplerFormFieldMapping *>(l->data);
      if (!mapping || !mapping->field) {
        continue;
      }
      if (poppler_form_field_get_field_type(mapping->field) == wanted_type) {
        found = mapping->field;
        g_object_ref(found);
        break;
      }
    }

    poppler_page_free_form_field_mapping(mappings);
    g_object_unref(page);
    return found;
  }

  static std::unique_ptr<char, void (*)(void *)> DupTmpPdfPath_2350() {
    std::string path = WriteTestPdfToTemp_2350();
    return std::unique_ptr<char, void (*)(void *)>(g_strdup(path.c_str()), g_free);
  }
};

TEST_F(PopplerFormFieldChoiceToggleItemTest_2350, TogglesSelectionStateForValidIndex_2350) {
  const std::string pdf_path = WriteTestPdfToTemp_2350();
  const std::string uri = FileUriForPath_2350(pdf_path);

  PopplerDocument *doc = LoadDoc_2350(uri);
  ASSERT_NE(doc, nullptr);

  PopplerFormField *choice =
      FindFieldByTypeOnFirstPage_2350(doc, POPPLER_FORM_FIELD_CHOICE);
  ASSERT_NE(choice, nullptr);

  const gint n_items = poppler_form_field_choice_get_n_items(choice);
  ASSERT_GE(n_items, 2) << "Test PDF should have at least 2 choice items";

  const gint index = 1;
  const gboolean before = poppler_form_field_choice_is_item_selected(choice, index);

  // Function under test.
  poppler_form_field_choice_toggle_item(choice, index);

  const gboolean after = poppler_form_field_choice_is_item_selected(choice, index);
  EXPECT_NE(before, after) << "toggle_item() should flip the selected state of the target index";

  g_object_unref(choice);
  g_object_unref(doc);
}

TEST_F(PopplerFormFieldChoiceToggleItemTest_2350, BoundaryIndicesZeroAndLastDoNotCrash_2350) {
  const std::string pdf_path = WriteTestPdfToTemp_2350();
  const std::string uri = FileUriForPath_2350(pdf_path);

  PopplerDocument *doc = LoadDoc_2350(uri);
  ASSERT_NE(doc, nullptr);

  PopplerFormField *choice =
      FindFieldByTypeOnFirstPage_2350(doc, POPPLER_FORM_FIELD_CHOICE);
  ASSERT_NE(choice, nullptr);

  const gint n_items = poppler_form_field_choice_get_n_items(choice);
  ASSERT_GE(n_items, 1);

  // index 0
  {
    const gboolean before0 = poppler_form_field_choice_is_item_selected(choice, 0);
    poppler_form_field_choice_toggle_item(choice, 0);
    const gboolean after0 = poppler_form_field_choice_is_item_selected(choice, 0);
    EXPECT_NE(before0, after0);
  }

  // last index
  if (n_items > 1) {
    const gint last = n_items - 1;
    const gboolean before_last = poppler_form_field_choice_is_item_selected(choice, last);
    poppler_form_field_choice_toggle_item(choice, last);
    const gboolean after_last = poppler_form_field_choice_is_item_selected(choice, last);
    EXPECT_NE(before_last, after_last);
  }

  g_object_unref(choice);
  g_object_unref(doc);
}

TEST_F(PopplerFormFieldChoiceToggleItemTest_2350, DiesOnNegativeIndexWhenCriticalIsFatal_2350) {
  // Make GLib criticals abort so g_return_if_fail() becomes observable as a death.
  ASSERT_DEATH(
      {
        g_log_set_always_fatal(static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL));

        const std::string pdf_path = WriteTestPdfToTemp_2350();
        const std::string uri = FileUriForPath_2350(pdf_path);

        PopplerDocument *doc = LoadDoc_2350(uri);
        if (!doc) {
          // If doc can't be loaded, bail out; but that would fail the death test expectation.
          abort();
        }

        PopplerFormField *choice =
            FindFieldByTypeOnFirstPage_2350(doc, POPPLER_FORM_FIELD_CHOICE);
        if (!choice) {
          g_object_unref(doc);
          abort();
        }

        poppler_form_field_choice_toggle_item(choice, -1);

        g_object_unref(choice);
        g_object_unref(doc);
      },
      ".*");
}

TEST_F(PopplerFormFieldChoiceToggleItemTest_2350, DiesOnIndexEqualToItemCountWhenCriticalIsFatal_2350) {
  ASSERT_DEATH(
      {
        g_log_set_always_fatal(static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL));

        const std::string pdf_path = WriteTestPdfToTemp_2350();
        const std::string uri = FileUriForPath_2350(pdf_path);

        PopplerDocument *doc = LoadDoc_2350(uri);
        if (!doc) {
          abort();
        }

        PopplerFormField *choice =
            FindFieldByTypeOnFirstPage_2350(doc, POPPLER_FORM_FIELD_CHOICE);
        if (!choice) {
          g_object_unref(doc);
          abort();
        }

        const gint n_items = poppler_form_field_choice_get_n_items(choice);
        poppler_form_field_choice_toggle_item(choice, n_items); // out of range

        g_object_unref(choice);
        g_object_unref(doc);
      },
      ".*");
}

TEST_F(PopplerFormFieldChoiceToggleItemTest_2350, DiesWhenFieldIsNotChoiceTypeAndCriticalIsFatal_2350) {
  ASSERT_DEATH(
      {
        g_log_set_always_fatal(static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL));

        const std::string pdf_path = WriteTestPdfToTemp_2350();
        const std::string uri = FileUriForPath_2350(pdf_path);

        PopplerDocument *doc = LoadDoc_2350(uri);
        if (!doc) {
          abort();
        }

        // Grab the text field and call the choice-only function on it.
        PopplerFormField *text =
            FindFieldByTypeOnFirstPage_2350(doc, POPPLER_FORM_FIELD_TEXT);
        if (!text) {
          g_object_unref(doc);
          abort();
        }

        poppler_form_field_choice_toggle_item(text, 0);

        g_object_unref(text);
        g_object_unref(doc);
      },
      ".*");
}

} // namespace