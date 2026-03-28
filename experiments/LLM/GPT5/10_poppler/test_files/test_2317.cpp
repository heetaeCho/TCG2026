// poppler-form-field-get-partial-name-test_2317.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <string>
#include <vector>

// The function under test is in poppler-form-field.cc:
//   gchar *poppler_form_field_get_partial_name(PopplerFormField *field);

namespace {

class PopplerFormFieldGetPartialNameTest_2317 : public ::testing::Test {
protected:
  static std::string GetTestDataDir() {
    // Prefer an explicit env var if the harness provides it.
    const char* env = g_getenv("POPPLER_TESTDATADIR");
    if (env && *env) {
      return std::string(env);
    }

#ifdef TESTDATADIR
    return std::string(TESTDATADIR);
#else
    // Conservative fallback for local runs.
    return std::string("./testdata");
#endif
  }

  static std::string FindFirstExistingPdfPathOrEmpty() {
    const std::string base = GetTestDataDir();

    // Try a few common filenames used in Poppler test suites.
    const std::vector<std::string> candidates = {
        "forms.pdf",
        "form.pdf",
        "acroform.pdf",
        "AcroForm.pdf",
        "test.pdf",
    };

    for (const auto& name : candidates) {
      gchar* full = g_build_filename(base.c_str(), name.c_str(), nullptr);
      const bool exists = g_file_test(full, G_FILE_TEST_IS_REGULAR);
      std::string out;
      if (exists) {
        out = full;
      }
      g_free(full);
      if (!out.empty()) {
        return out;
      }
    }
    return std::string();
  }

  static PopplerDocument* OpenAnyTestPdfOrSkip() {
    const std::string pdf_path = FindFirstExistingPdfPathOrEmpty();
    if (pdf_path.empty()) {
      GTEST_SKIP() << "No suitable PDF test file found in test data dir: " << GetTestDataDir();
    }

    GError* error = nullptr;
    gchar* uri = g_filename_to_uri(pdf_path.c_str(), nullptr, &error);
    if (!uri) {
      std::string msg = error ? error->message : "unknown error";
      if (error)
        g_error_free(error);
      GTEST_SKIP() << "Failed to build URI for test PDF: " << pdf_path << " (" << msg << ")";
    }

    PopplerDocument* doc = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
    g_free(uri);

    if (!doc) {
      std::string msg = error ? error->message : "unknown error";
      if (error)
        g_error_free(error);
      GTEST_SKIP() << "Failed to open test PDF: " << pdf_path << " (" << msg << ")";
    }
    return doc;
  }

  static PopplerFormField* FindAnyFormFieldOrNull(PopplerDocument* doc) {
    const int n_pages = poppler_document_get_n_pages(doc);
    for (int i = 0; i < n_pages; ++i) {
      PopplerPage* page = poppler_document_get_page(doc, i);
      if (!page)
        continue;

      GList* mappings = poppler_page_get_form_field_mapping(page);
      if (mappings) {
        auto* mapping = static_cast<PopplerFormFieldMapping*>(mappings->data);
        PopplerFormField* field = mapping ? mapping->field : nullptr;

        // Clean up mapping list and page before returning.
        poppler_page_free_form_field_mapping(mappings);
        g_object_unref(page);
        return field;
      }

      g_object_unref(page);
    }
    return nullptr;
  }

  static PopplerFormField* FindFirstFieldWithNonNullPartialNameOrNull(PopplerDocument* doc) {
    const int n_pages = poppler_document_get_n_pages(doc);
    for (int i = 0; i < n_pages; ++i) {
      PopplerPage* page = poppler_document_get_page(doc, i);
      if (!page)
        continue;

      GList* mappings = poppler_page_get_form_field_mapping(page);
      for (GList* l = mappings; l; l = l->next) {
        auto* mapping = static_cast<PopplerFormFieldMapping*>(l->data);
        PopplerFormField* field = mapping ? mapping->field : nullptr;
        if (!field)
          continue;

        gchar* name = poppler_form_field_get_partial_name(field);
        const bool ok = (name != nullptr);
        if (name)
          g_free(name);

        if (ok) {
          poppler_page_free_form_field_mapping(mappings);
          g_object_unref(page);
          return field;
        }
      }

      if (mappings)
        poppler_page_free_form_field_mapping(mappings);
      g_object_unref(page);
    }
    return nullptr;
  }

  static PopplerFormField* FindFirstFieldWithNullPartialNameOrNull(PopplerDocument* doc) {
    const int n_pages = poppler_document_get_n_pages(doc);
    for (int i = 0; i < n_pages; ++i) {
      PopplerPage* page = poppler_document_get_page(doc, i);
      if (!page)
        continue;

      GList* mappings = poppler_page_get_form_field_mapping(page);
      for (GList* l = mappings; l; l = l->next) {
        auto* mapping = static_cast<PopplerFormFieldMapping*>(l->data);
        PopplerFormField* field = mapping ? mapping->field : nullptr;
        if (!field)
          continue;

        gchar* name = poppler_form_field_get_partial_name(field);
        const bool is_null = (name == nullptr);
        if (name)
          g_free(name);

        if (is_null) {
          poppler_page_free_form_field_mapping(mappings);
          g_object_unref(page);
          return field;
        }
      }

      if (mappings)
        poppler_page_free_form_field_mapping(mappings);
      g_object_unref(page);
    }
    return nullptr;
  }
};

TEST_F(PopplerFormFieldGetPartialNameTest_2317, NullFieldReturnsNull_2317) {
  // g_return_val_if_fail(POPPLER_IS_FORM_FIELD(field), NULL);
  EXPECT_EQ(poppler_form_field_get_partial_name(nullptr), nullptr);
}

TEST_F(PopplerFormFieldGetPartialNameTest_2317, WorksOnRealFormFieldAndReturnsUtf8_2317) {
  PopplerDocument* doc = OpenAnyTestPdfOrSkip();
  ASSERT_NE(doc, nullptr);

  PopplerFormField* field = FindFirstFieldWithNonNullPartialNameOrNull(doc);
  if (!field) {
    g_object_unref(doc);
    GTEST_SKIP() << "No form field with a non-NULL partial name found in available test PDFs.";
  }

  gchar* name = poppler_form_field_get_partial_name(field);
  ASSERT_NE(name, nullptr);

  // Observable properties: returned string should be valid UTF-8 (conversion helper suggests UTF-8).
  EXPECT_TRUE(g_utf8_validate(name, -1, nullptr));

  // Boundary-ish: allow empty string but ensure pointer is usable.
  // (We do not assume non-empty because that depends on the input PDF.)
  EXPECT_NE(name, nullptr);

  g_free(name);
  g_object_unref(doc);
}

TEST_F(PopplerFormFieldGetPartialNameTest_2317, ReturnsNullWhenUnderlyingPartialNameIsNull_2317) {
  PopplerDocument* doc = OpenAnyTestPdfOrSkip();
  ASSERT_NE(doc, nullptr);

  PopplerFormField* field = FindFirstFieldWithNullPartialNameOrNull(doc);
  if (!field) {
    g_object_unref(doc);
    GTEST_SKIP() << "No form field with a NULL partial name found in available test PDFs.";
  }

  // Error/exceptional observable case: function should return nullptr when no partial name exists.
  EXPECT_EQ(poppler_form_field_get_partial_name(field), nullptr);

  g_object_unref(doc);
}

TEST_F(PopplerFormFieldGetPartialNameTest_2317, MultipleCallsAreIndependentlyFreeable_2317) {
  PopplerDocument* doc = OpenAnyTestPdfOrSkip();
  ASSERT_NE(doc, nullptr);

  PopplerFormField* field = FindFirstFieldWithNonNullPartialNameOrNull(doc);
  if (!field) {
    g_object_unref(doc);
    GTEST_SKIP() << "No form field with a non-NULL partial name found in available test PDFs.";
  }

  gchar* a = poppler_form_field_get_partial_name(field);
  gchar* b = poppler_form_field_get_partial_name(field);

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  // Both returned values should be valid UTF-8.
  EXPECT_TRUE(g_utf8_validate(a, -1, nullptr));
  EXPECT_TRUE(g_utf8_validate(b, -1, nullptr));

  // We only require that both can be freed safely.
  g_free(a);
  g_free(b);

  g_object_unref(doc);
}

TEST_F(PopplerFormFieldGetPartialNameTest_2317, WorksWithAnyFormFieldMappingIfPresent_2317) {
  PopplerDocument* doc = OpenAnyTestPdfOrSkip();
  ASSERT_NE(doc, nullptr);

  PopplerFormField* field = FindAnyFormFieldOrNull(doc);
  if (!field) {
    g_object_unref(doc);
    GTEST_SKIP() << "No form fields found in available test PDFs.";
  }

  // The function should not crash and should return either NULL or a UTF-8 string.
  gchar* name = poppler_form_field_get_partial_name(field);
  if (name) {
    EXPECT_TRUE(g_utf8_validate(name, -1, nullptr));
    g_free(name);
  } else {
    SUCCEED();
  }

  g_object_unref(doc);
}

}  // namespace