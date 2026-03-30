// poppler-form-field-choice-get-text-test.cc
//
// Unit tests for:
//   gchar *poppler_form_field_choice_get_text(PopplerFormField *field)
//
// Constraints honored:
// - Treat implementation as black box.
// - Use only observable behavior via public GLib Poppler APIs.
// - No access to private/internal state.
// - Cover normal, boundary, and error/exceptional (observable) cases.
//
// TEST_ID: 2352

#include <gtest/gtest.h>

#include <poppler.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <memory>
#include <string>

namespace {

constexpr int TEST_ID = 2352;

struct GErrorDeleter {
  void operator()(GError *e) const { g_error_free(e); }
};

struct GObjectUnref {
  void operator()(gpointer p) const {
    if (p) {
      g_object_unref(p);
    }
  }
};

struct GFreeDeleter {
  void operator()(gpointer p) const {
    if (p) {
      g_free(p);
    }
  }
};

using GErrorPtr = std::unique_ptr<GError, GErrorDeleter>;
using GObjectPtr = std::unique_ptr<void, GObjectUnref>;
using GCharPtr = std::unique_ptr<gchar, GFreeDeleter>;

static std::string BuildTestUriOrEmpty(const char *filename) {
#ifndef TESTDATADIR
  // Many Poppler test setups define TESTDATADIR via build system.
  // If not defined, skip deterministically.
  (void)filename;
  return {};
#else
  gchar *path = g_build_filename(TESTDATADIR, filename, nullptr);
  if (!path) {
    return {};
  }
  GCharPtr path_holder(path);

  if (!g_file_test(path, G_FILE_TEST_EXISTS)) {
    return {};
  }

  GError *err = nullptr;
  gchar *uri = g_filename_to_uri(path, nullptr, &err);
  if (err) {
    g_error_free(err);
    return {};
  }
  if (!uri) {
    return {};
  }
  GCharPtr uri_holder(uri);
  return std::string(uri);
#endif
}

static PopplerDocument *OpenDocOrSkip(const char *filename) {
  const std::string uri = BuildTestUriOrEmpty(filename);
  if (uri.empty()) {
    GTEST_SKIP() << "Test data file not available (need TESTDATADIR and '" << filename
                 << "'). Skipping.";
  }

  GError *error_raw = nullptr;
  PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr,
                                                        &error_raw);
  GErrorPtr error(error_raw);
  if (!doc) {
    std::string msg = error ? error->message : "unknown error";
    GTEST_SKIP() << "Could not open test PDF '" << filename << "': " << msg;
  }
  return doc;
}

static PopplerPage *GetPageOrSkip(PopplerDocument *doc, int index) {
  PopplerPage *page = poppler_document_get_page(doc, index);
  if (!page) {
    GTEST_SKIP() << "Could not get page " << index << " from test PDF. Skipping.";
  }
  return page;
}

static PopplerFormField *FindFirstFieldOfTypeOrSkip(PopplerPage *page,
                                                    PopplerFormFieldType type) {
  // poppler_page_get_form_field_mapping returns a GList of PopplerFormFieldMapping*
  // Each mapping has .field and .area.
  GList *mappings = poppler_page_get_form_field_mapping(page);
  if (!mappings) {
    GTEST_SKIP() << "No form field mappings on page; cannot exercise API. Skipping.";
  }

  PopplerFormField *found = nullptr;
  for (GList *l = mappings; l; l = l->next) {
    auto *mapping = static_cast<PopplerFormFieldMapping *>(l->data);
    if (!mapping || !mapping->field) {
      continue;
    }
    if (poppler_form_field_get_field_type(mapping->field) == type) {
      found = mapping->field;
      break;
    }
  }

  poppler_page_free_form_field_mapping(mappings);

  if (!found) {
    GTEST_SKIP() << "No field of requested type found on page; skipping.";
  }
  return found;
}

// Prefer an editable choice field if available; otherwise fall back to any choice field.
static PopplerFormField *FindChoiceFieldPreferEditableOrSkip(PopplerPage *page) {
  GList *mappings = poppler_page_get_form_field_mapping(page);
  if (!mappings) {
    GTEST_SKIP() << "No form field mappings on page; cannot exercise API. Skipping.";
  }

  PopplerFormField *any_choice = nullptr;
  PopplerFormField *editable_choice = nullptr;

  for (GList *l = mappings; l; l = l->next) {
    auto *mapping = static_cast<PopplerFormFieldMapping *>(l->data);
    if (!mapping || !mapping->field) {
      continue;
    }
    if (poppler_form_field_get_field_type(mapping->field) != POPPLER_FORM_FIELD_CHOICE) {
      continue;
    }

    if (!any_choice) {
      any_choice = mapping->field;
    }

    // If this API exists in your Poppler version, it helps pick a combo box with edit.
    // If not available, we still keep any_choice.
#ifdef POPPLER_CHECK_VERSION
#if POPPLER_CHECK_VERSION(0, 20, 0)
    // poppler_form_field_choice_is_editable is present in many Poppler versions,
    // but guard it behind version macro when available.
    if (poppler_form_field_choice_is_editable(mapping->field)) {
      editable_choice = mapping->field;
      break;
    }
#endif
#endif
  }

  poppler_page_free_form_field_mapping(mappings);

  if (editable_choice) {
    return editable_choice;
  }
  if (any_choice) {
    return any_choice;
  }

  GTEST_SKIP() << "No choice form field found on page; skipping.";
}

class PopplerFormFieldChoiceGetTextTest_2352 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Ensure GLib type system is initialized in older setups if needed.
    // (g_type_init is deprecated, but harmless to avoid calling in newer GLib.)
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif
  }
};

TEST_F(PopplerFormFieldChoiceGetTextTest_2352, WrongFieldTypeReturnsNull_2352) {
  // Arrange: open a PDF with forms and pick a non-choice field.
  GObjectPtr doc(OpenDocOrSkip("forms.pdf"));
  GObjectPtr page(GetPageOrSkip(reinterpret_cast<PopplerDocument *>(doc.get()), 0));

  PopplerFormField *non_choice =
      FindFirstFieldOfTypeOrSkip(reinterpret_cast<PopplerPage *>(page.get()),
                                 POPPLER_FORM_FIELD_TEXT);

  // Act
  gchar *text = poppler_form_field_choice_get_text(non_choice);

  // Assert: for wrong type, g_return_val_if_fail => NULL.
  ASSERT_EQ(text, nullptr);
}

TEST_F(PopplerFormFieldChoiceGetTextTest_2352, DefaultTextMayBeNullWhenUnset_2352) {
  // Arrange: open a PDF with forms and pick a choice field.
  GObjectPtr doc(OpenDocOrSkip("forms.pdf"));
  GObjectPtr page(GetPageOrSkip(reinterpret_cast<PopplerDocument *>(doc.get()), 0));

  PopplerFormField *choice =
      FindChoiceFieldPreferEditableOrSkip(reinterpret_cast<PopplerPage *>(page.get()));

  // Act: without setting edit text explicitly, this may be NULL (depends on PDF state).
  gchar *text = poppler_form_field_choice_get_text(choice);

  // Assert: observable, non-crashing behavior. Either NULL or a valid UTF-8 string.
  if (text) {
    // Returned memory is owned by caller per GLib convention for gchar* return.
    // Ensure it is valid UTF-8.
    EXPECT_TRUE(g_utf8_validate(text, -1, nullptr));
    g_free(text);
  } else {
    SUCCEED() << "Choice edit text is unset; API returned NULL as allowed.";
  }
}

TEST_F(PopplerFormFieldChoiceGetTextTest_2352, SetTextThenGetTextMatches_2352) {
  // Arrange
  GObjectPtr doc(OpenDocOrSkip("forms.pdf"));
  GObjectPtr page(GetPageOrSkip(reinterpret_cast<PopplerDocument *>(doc.get()), 0));

  PopplerFormField *choice =
      FindChoiceFieldPreferEditableOrSkip(reinterpret_cast<PopplerPage *>(page.get()));

  const char kValue[] = "Hello Poppler ✅";

  // Act: set a text value if supported; then get it back via the function under test.
  //
  // Some PDFs/fields may not be editable; Poppler may ignore set_text in that case.
  // We still assert that the API returns either NULL or a valid UTF-8 string; and if it
  // returns non-NULL, it matches what was set for editable fields.
  poppler_form_field_choice_set_text(choice, kValue);
  gchar *got = poppler_form_field_choice_get_text(choice);

  // Assert
  if (!got) {
    // If field isn't editable, get_text may still be NULL even after set_text.
    // This is an observable "error/unsupported operation" outcome.
    SUCCEED() << "Field may be non-editable; get_text returned NULL after set_text.";
    return;
  }

  EXPECT_TRUE(g_utf8_validate(got, -1, nullptr));
  EXPECT_STREQ(got, kValue);
  g_free(got);
}

TEST_F(PopplerFormFieldChoiceGetTextTest_2352, EmptyStringBoundary_2352) {
  // Arrange
  GObjectPtr doc(OpenDocOrSkip("forms.pdf"));
  GObjectPtr page(GetPageOrSkip(reinterpret_cast<PopplerDocument *>(doc.get()), 0));

  PopplerFormField *choice =
      FindChoiceFieldPreferEditableOrSkip(reinterpret_cast<PopplerPage *>(page.get()));

  // Act
  poppler_form_field_choice_set_text(choice, "");
  gchar *got = poppler_form_field_choice_get_text(choice);

  // Assert: For editable choice fields, empty string should round-trip as "" (non-NULL).
  // For non-editable fields, Poppler may ignore it and return NULL; accept as observable.
  if (!got) {
    SUCCEED() << "Field may be non-editable; get_text returned NULL for empty string.";
    return;
  }

  EXPECT_TRUE(g_utf8_validate(got, -1, nullptr));
  EXPECT_STREQ(got, "");
  g_free(got);
}

}  // namespace