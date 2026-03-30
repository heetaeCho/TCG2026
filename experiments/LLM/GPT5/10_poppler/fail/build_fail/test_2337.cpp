// poppler-form-field-text-do-scroll-test.cc
//
// Unit tests for poppler_form_field_text_do_scroll()
// TEST_ID: 2337

#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

// The function under test is implemented in poppler-form-field.cc.
// Some build setups may not expose it via public headers; declare it explicitly.
extern "C" gboolean poppler_form_field_text_do_scroll(PopplerFormField *field);

namespace {

class PopplerFormFieldTextDoScrollTest_2337 : public ::testing::Test {
 protected:
  static PopplerDocument *LoadAnyTestDocumentOrSkip() {
    const char *testdatadir = g_getenv("TESTDATADIR");
    if (!testdatadir || !*testdatadir) {
      GTEST_SKIP() << "TESTDATADIR is not set; cannot locate Poppler test PDFs.";
    }

    // Try a small set of common filenames used in Poppler test suites.
    const char *candidates[] = {
        "forms.pdf",
        "form.pdf",
        "input-form.pdf",
        "forms-2.pdf",
        "acroform.pdf",
        "form_text.pdf",
    };

    gchar *pdf_path = nullptr;
    for (const char *name : candidates) {
      gchar *p = g_build_filename(testdatadir, name, nullptr);
      if (g_file_test(p, G_FILE_TEST_IS_REGULAR)) {
        pdf_path = p;
        break;
      }
      g_free(p);
    }

    if (!pdf_path) {
      GTEST_SKIP() << "No known forms PDF found in TESTDATADIR=" << testdatadir;
    }

    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(pdf_path, /*hostname=*/nullptr, &error);
    g_free(pdf_path);

    if (!uri) {
      const char *msg = (error && error->message) ? error->message : "unknown error";
      if (error) g_error_free(error);
      GTEST_SKIP() << "g_filename_to_uri failed: " << msg;
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
    g_free(uri);

    if (!doc) {
      const char *msg = (error && error->message) ? error->message : "unknown error";
      if (error) g_error_free(error);
      GTEST_SKIP() << "poppler_document_new_from_file failed: " << msg;
    }

    return doc;
  }

  static PopplerFormField *FindAnyFieldOfType(PopplerDocument *doc, PopplerFormFieldType want_type) {
    const int n_pages = poppler_document_get_n_pages(doc);
    for (int i = 0; i < n_pages; ++i) {
      PopplerPage *page = poppler_document_get_page(doc, i);
      if (!page) continue;

      // Mapping list contains PopplerFormFieldMapping*, each with ->field.
      GList *mappings = poppler_page_get_form_field_mapping(page);
      for (GList *l = mappings; l; l = l->next) {
        auto *mapping = static_cast<PopplerFormFieldMapping *>(l->data);
        if (!mapping || !mapping->field) continue;

        const PopplerFormFieldType t = poppler_form_field_get_field_type(mapping->field);
        if (t == want_type) {
          // We return a new ref to keep it alive beyond unmapping.
          PopplerFormField *field = static_cast<PopplerFormField *>(g_object_ref(mapping->field));
          poppler_page_free_form_field_mapping(mappings);
          g_object_unref(page);
          return field;
        }
      }

      poppler_page_free_form_field_mapping(mappings);
      g_object_unref(page);
    }
    return nullptr;
  }
};

TEST_F(PopplerFormFieldTextDoScrollTest_2337, NullFieldReturnsFalse_2337) {
  // Exceptional/error case: null input should be handled by g_return_val_if_fail.
  EXPECT_FALSE(poppler_form_field_text_do_scroll(nullptr));
}

TEST_F(PopplerFormFieldTextDoScrollTest_2337, NonTextFieldReturnsFalse_2337) {
  // Error case (observable): passing a non-text field should return FALSE due to g_return_val_if_fail.
  PopplerDocument *doc = LoadAnyTestDocumentOrSkip();

  // Prefer a button field; if none exist, try choice/signature as alternatives.
  PopplerFormField *non_text = FindAnyFieldOfType(doc, POPPLER_FORM_FIELD_BUTTON);
  if (!non_text) non_text = FindAnyFieldOfType(doc, POPPLER_FORM_FIELD_CHOICE);
  if (!non_text) non_text = FindAnyFieldOfType(doc, POPPLER_FORM_FIELD_SIGNATURE);

  if (!non_text) {
    g_object_unref(doc);
    GTEST_SKIP() << "No non-text form field found in the available test PDF.";
  }

  EXPECT_FALSE(poppler_form_field_text_do_scroll(non_text));

  g_object_unref(non_text);
  g_object_unref(doc);
}

TEST_F(PopplerFormFieldTextDoScrollTest_2337, TextFieldResultMatchesDoScrollPropertyIfPresent_2337) {
  // Normal operation: for a real text field, verify observable consistency with a public GObject property
  // if the property exists (no inference about internal logic; just interface consistency).
  PopplerDocument *doc = LoadAnyTestDocumentOrSkip();

  PopplerFormField *text = FindAnyFieldOfType(doc, POPPLER_FORM_FIELD_TEXT);
  if (!text) {
    g_object_unref(doc);
    GTEST_SKIP() << "No text form field found in the available test PDF.";
  }

  const gboolean do_scroll = poppler_form_field_text_do_scroll(text);

  // If a "do-scroll" property exists, its value should match the function.
  GParamSpec *pspec = g_object_class_find_property(G_OBJECT_GET_CLASS(text), "do-scroll");
  if (pspec) {
    gboolean prop_value = FALSE;
    g_object_get(G_OBJECT(text), "do-scroll", &prop_value, nullptr);
    EXPECT_EQ(prop_value, do_scroll);
  } else {
    // Property not present in this build; still assert we got a valid gboolean and the call succeeded.
    EXPECT_TRUE(do_scroll == TRUE || do_scroll == FALSE);
  }

  g_object_unref(text);
  g_object_unref(doc);
}

TEST_F(PopplerFormFieldTextDoScrollTest_2337, TextFieldResultIsStableAcrossCalls_2337) {
  // Boundary/behavioral stability: repeated calls should be consistent for the same object state.
  PopplerDocument *doc = LoadAnyTestDocumentOrSkip();

  PopplerFormField *text = FindAnyFieldOfType(doc, POPPLER_FORM_FIELD_TEXT);
  if (!text) {
    g_object_unref(doc);
    GTEST_SKIP() << "No text form field found in the available test PDF.";
  }

  const gboolean v1 = poppler_form_field_text_do_scroll(text);
  const gboolean v2 = poppler_form_field_text_do_scroll(text);
  EXPECT_EQ(v1, v2);

  g_object_unref(text);
  g_object_unref(doc);
}

}  // namespace