// poppler-form-field-button-get-button-type-test-2314.cc
#include <gtest/gtest.h>

#include <glib.h>

#include "poppler.h"
#include "poppler-form-field.h"

// NOTE:
// These tests treat Poppler as a black box. They only use the public GLib API to
// load a PDF, discover fields, and verify observable results from
// poppler_form_field_button_get_button_type().

namespace {

class PopplerFormFieldButtonGetButtonTypeTest_2314 : public ::testing::Test {
 protected:
  void SetUp() override {
    doc_ = LoadTestDocumentOrSkip();
  }

  void TearDown() override {
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
  }

  static PopplerDocument* LoadTestDocumentOrSkip() {
    // Try a few common filenames used in Poppler test suites.
    // We intentionally do not assume one fixed path; if none are found,
    // the tests are skipped rather than failing spuriously.
    const char* candidates[] = {
        "forms.pdf",
        "form.pdf",
        "FormTest.pdf",
        "test.forms.pdf",
    };

    auto try_load = [](const char* abs_path) -> PopplerDocument* {
      GError* error = nullptr;
      gchar* uri = g_filename_to_uri(abs_path, nullptr, &error);
      if (!uri) {
        if (error) g_error_free(error);
        return nullptr;
      }
      PopplerDocument* d = poppler_document_new_from_file(uri, nullptr, &error);
      g_free(uri);
      if (!d) {
        if (error) g_error_free(error);
        return nullptr;
      }
      return d;
    };

    // Prefer TESTDATADIR if provided by the build.
#ifdef TESTDATADIR
    for (const char* name : candidates) {
      gchar* path = g_build_filename(TESTDATADIR, name, nullptr);
      PopplerDocument* d = try_load(path);
      g_free(path);
      if (d) return d;
    }
#endif

    // Try relative "testdata" / "tests" / current dir fallback.
    const char* dirs[] = {"testdata", "tests", "."};
    for (const char* dir : dirs) {
      for (const char* name : candidates) {
        gchar* path = g_build_filename(dir, name, nullptr);
        PopplerDocument* d = try_load(path);
        g_free(path);
        if (d) return d;
      }
    }

    GTEST_SKIP() << "No suitable forms PDF fixture found (tried common names like forms.pdf).";
    return nullptr;
  }

  // Scans the document for the first PopplerFormField of type BUTTON that also
  // matches the requested PopplerFormButtonType (PUSH/CHECK/RADIO).
  PopplerFormField* FindButtonFieldByButtonType(PopplerFormButtonType want_button_type) {
    if (!doc_) return nullptr;

    const int n_pages = poppler_document_get_n_pages(doc_);
    for (int i = 0; i < n_pages; ++i) {
      PopplerPage* page = poppler_document_get_page(doc_, i);
      if (!page) continue;

      GList* mappings = poppler_page_get_form_field_mapping(page);
      for (GList* it = mappings; it; it = it->next) {
        auto* mapping = static_cast<PopplerFormFieldMapping*>(it->data);
        if (!mapping || !mapping->field) continue;

        PopplerFormField* field = mapping->field;
        if (poppler_form_field_get_field_type(field) != POPPLER_FORM_FIELD_BUTTON) continue;

        // Observable behavior under test:
        const PopplerFormButtonType got = poppler_form_field_button_get_button_type(field);
        if (got == want_button_type) {
          // Keep the field alive after freeing the mapping list.
          g_object_ref(field);
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

  // Finds any non-button form field (e.g., text/choice/signature) if present.
  PopplerFormField* FindNonButtonField() {
    if (!doc_) return nullptr;

    const int n_pages = poppler_document_get_n_pages(doc_);
    for (int i = 0; i < n_pages; ++i) {
      PopplerPage* page = poppler_document_get_page(doc_, i);
      if (!page) continue;

      GList* mappings = poppler_page_get_form_field_mapping(page);
      for (GList* it = mappings; it; it = it->next) {
        auto* mapping = static_cast<PopplerFormFieldMapping*>(it->data);
        if (!mapping || !mapping->field) continue;

        PopplerFormField* field = mapping->field;
        if (poppler_form_field_get_field_type(field) != POPPLER_FORM_FIELD_BUTTON) {
          g_object_ref(field);
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

  PopplerDocument* doc_ = nullptr;
};

TEST_F(PopplerFormFieldButtonGetButtonTypeTest_2314, PushButtonReturnsPush_2314) {
  if (!doc_) GTEST_SKIP();

  PopplerFormField* field = FindButtonFieldByButtonType(POPPLER_FORM_BUTTON_PUSH);
  if (!field) {
    GTEST_SKIP() << "No PUSH button field found in the PDF fixture.";
  }

  EXPECT_EQ(poppler_form_field_get_field_type(field), POPPLER_FORM_FIELD_BUTTON);
  EXPECT_EQ(poppler_form_field_button_get_button_type(field), POPPLER_FORM_BUTTON_PUSH);

  g_object_unref(field);
}

TEST_F(PopplerFormFieldButtonGetButtonTypeTest_2314, CheckButtonReturnsCheck_2314) {
  if (!doc_) GTEST_SKIP();

  PopplerFormField* field = FindButtonFieldByButtonType(POPPLER_FORM_BUTTON_CHECK);
  if (!field) {
    GTEST_SKIP() << "No CHECK button field found in the PDF fixture.";
  }

  EXPECT_EQ(poppler_form_field_get_field_type(field), POPPLER_FORM_FIELD_BUTTON);
  EXPECT_EQ(poppler_form_field_button_get_button_type(field), POPPLER_FORM_BUTTON_CHECK);

  g_object_unref(field);
}

TEST_F(PopplerFormFieldButtonGetButtonTypeTest_2314, RadioButtonReturnsRadio_2314) {
  if (!doc_) GTEST_SKIP();

  PopplerFormField* field = FindButtonFieldByButtonType(POPPLER_FORM_BUTTON_RADIO);
  if (!field) {
    GTEST_SKIP() << "No RADIO button field found in the PDF fixture.";
  }

  EXPECT_EQ(poppler_form_field_get_field_type(field), POPPLER_FORM_FIELD_BUTTON);
  EXPECT_EQ(poppler_form_field_button_get_button_type(field), POPPLER_FORM_BUTTON_RADIO);

  g_object_unref(field);
}

TEST_F(PopplerFormFieldButtonGetButtonTypeTest_2314,
       NonButtonFieldEmitsCriticalAndReturnsDefaultPush_2314) {
  if (!doc_) GTEST_SKIP();

  PopplerFormField* non_button = FindNonButtonField();
  if (!non_button) {
    GTEST_SKIP() << "No non-button form field found in the PDF fixture to exercise g_return path.";
  }

  // The implementation uses g_return_val_if_fail(field->widget->getType() == formButton, PUSH)
  // so we expect a CRITICAL log and a default return value of POPPLER_FORM_BUTTON_PUSH.
  //
  // We do not rely on exact message text or log domain (which may vary by build),
  // only that a CRITICAL is emitted.
  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*");
  const PopplerFormButtonType got = poppler_form_field_button_get_button_type(non_button);
  g_test_assert_expected_messages();

  EXPECT_EQ(got, POPPLER_FORM_BUTTON_PUSH);

  g_object_unref(non_button);
}

}  // namespace