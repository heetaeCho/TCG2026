// Copyright (C) 2026
// Unit tests for poppler_form_field_choice_get_item()
// File: poppler-form-field-choice-get-item-test.cc

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <string>
#include <vector>

namespace {

class PopplerFormFieldChoiceGetItemTest_2346 : public ::testing::Test {
protected:
  void SetUp() override {
    doc_ = LoadTestDocument();
    if (!doc_) {
      GTEST_SKIP() << "No suitable test PDF found (set TESTDATADIR/srcdir or provide known form PDFs).";
    }
  }

  void TearDown() override {
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
  }

  // Try to load a PDF that likely contains form fields (including a choice field).
  // This is intentionally tolerant: if a repo uses different filenames, tests will skip rather than fail.
  static PopplerDocument *LoadTestDocument() {
    const std::vector<std::string> candidates = BuildCandidatePaths();
    for (const auto &path : candidates) {
      if (!g_file_test(path.c_str(), G_FILE_TEST_EXISTS))
        continue;

      GError *error = nullptr;
      gchar *uri = g_filename_to_uri(path.c_str(), /*hostname=*/nullptr, &error);
      if (!uri) {
        if (error)
          g_error_free(error);
        continue;
      }

      PopplerDocument *doc = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
      g_free(uri);

      if (doc) {
        if (error)
          g_error_free(error);
        return doc;
      }

      if (error)
        g_error_free(error);
    }
    return nullptr;
  }

  static std::vector<std::string> BuildCandidatePaths() {
    std::vector<std::string> roots;

    if (const gchar *td = g_getenv("TESTDATADIR"); td && *td)
      roots.emplace_back(td);
    if (const gchar *sd = g_getenv("srcdir"); sd && *sd)
      roots.emplace_back(sd);

    // Common relative roots used in Poppler GLib tests / downstreams.
    roots.emplace_back(".");
    roots.emplace_back("..");
    roots.emplace_back("../test");
    roots.emplace_back("../test-data");
    roots.emplace_back("test");
    roots.emplace_back("test-data");

    // Candidate PDFs that often exist in Poppler test suites / forks.
    const std::vector<std::string> names = {
        "forms.pdf",
        "form.pdf",
        "forms/form.pdf",
        "forms/forms.pdf",
        "forms/choice.pdf",
        "forms/combobox.pdf",
        "forms/listbox.pdf",
        "acroform.pdf",
        "acroforms.pdf",
        "test.pdf",
        "pdfs/forms.pdf",
        "data/forms.pdf",
    };

    std::vector<std::string> out;
    out.reserve(roots.size() * names.size());
    for (const auto &r : roots) {
      for (const auto &n : names) {
        // Build a simple path join.
        if (r.empty() || r == ".") {
          out.push_back(n);
        } else if (r.back() == G_DIR_SEPARATOR) {
          out.push_back(r + n);
        } else {
          out.push_back(r + G_DIR_SEPARATOR_S + n);
        }
      }
    }
    return out;
  }

  struct FieldHit {
    PopplerFormField *field = nullptr; // borrowed from mapping; ref if returning
    PopplerPage *page = nullptr;       // owned (ref)
    PopplerFormFieldMapping *mapping = nullptr; // owned list element pointer (freed with list)
    GList *mappings = nullptr;         // owned list (free with poppler_page_free_form_field_mapping)
  };

  static bool IsFieldType(PopplerFormField *field, PopplerFormFieldType t) {
    return field && poppler_form_field_get_field_type(field) == t;
  }

  // Finds the first field matching predicate across all pages.
  // Returns with page ref'd and mappings list kept so the field pointer remains valid.
  static FieldHit FindFirstField(PopplerDocument *doc,
                                 const std::function<bool(PopplerFormField *)> &pred) {
    FieldHit hit;

    const int n_pages = poppler_document_get_n_pages(doc);
    for (int i = 0; i < n_pages; ++i) {
      PopplerPage *page = poppler_document_get_page(doc, i);
      if (!page)
        continue;

      GList *mappings = poppler_page_get_form_field_mapping(page);
      for (GList *l = mappings; l; l = l->next) {
        auto *m = static_cast<PopplerFormFieldMapping *>(l->data);
        if (!m || !m->field)
          continue;

        if (pred(m->field)) {
          hit.field = m->field;
          hit.page = page; // keep ref
          hit.mapping = m;
          hit.mappings = mappings;
          return hit;
        }
      }

      if (mappings)
        poppler_page_free_form_field_mapping(mappings);
      g_object_unref(page);
    }

    return hit;
  }

  static void FreeFieldHit(FieldHit *hit) {
    if (!hit)
      return;
    if (hit->mappings)
      poppler_page_free_form_field_mapping(hit->mappings);
    hit->mappings = nullptr;
    hit->mapping = nullptr;
    hit->field = nullptr;
    if (hit->page)
      g_object_unref(hit->page);
    hit->page = nullptr;
  }

  PopplerDocument *doc_ = nullptr;
};

TEST_F(PopplerFormFieldChoiceGetItemTest_2346, ReturnsNonNullUtf8ForValidIndex_2346) {
  FieldHit choice = FindFirstField(
      doc_, [](PopplerFormField *f) { return IsFieldType(f, POPPLER_FORM_FIELD_CHOICE); });

  if (!choice.field) {
    FreeFieldHit(&choice);
    GTEST_SKIP() << "No choice form field found in the available test PDF(s).";
  }

  const gint n_items = poppler_form_field_choice_get_n_items(choice.field);
  if (n_items <= 0) {
    FreeFieldHit(&choice);
    GTEST_SKIP() << "Choice field found, but it has no items; cannot test retrieval.";
  }

  gchar *item0 = poppler_form_field_choice_get_item(choice.field, 0);
  ASSERT_NE(item0, nullptr);

  // Observable behavior: returned string should be valid UTF-8 (function converts GooString to UTF-8).
  EXPECT_TRUE(g_utf8_validate(item0, -1, nullptr));

  // Also ensure it is a usable C string.
  EXPECT_GE(strlen(item0), 0u);

  g_free(item0);
  FreeFieldHit(&choice);
}

TEST_F(PopplerFormFieldChoiceGetItemTest_2346, NegativeIndexReturnsNullAndLogsCritical_2346) {
  FieldHit choice = FindFirstField(
      doc_, [](PopplerFormField *f) { return IsFieldType(f, POPPLER_FORM_FIELD_CHOICE); });

  if (!choice.field) {
    FreeFieldHit(&choice);
    GTEST_SKIP() << "No choice form field found in the available test PDF(s).";
  }

  // g_return_val_if_fail() should emit a CRITICAL log and return NULL.
  g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*assertion*index >= 0*failed*");
  gchar *item = poppler_form_field_choice_get_item(choice.field, -1);
  g_test_assert_expected_messages();

  EXPECT_EQ(item, nullptr);

  FreeFieldHit(&choice);
}

TEST_F(PopplerFormFieldChoiceGetItemTest_2346, IndexEqualToNItemsReturnsNullAndLogsCritical_2346) {
  FieldHit choice = FindFirstField(
      doc_, [](PopplerFormField *f) { return IsFieldType(f, POPPLER_FORM_FIELD_CHOICE); });

  if (!choice.field) {
    FreeFieldHit(&choice);
    GTEST_SKIP() << "No choice form field found in the available test PDF(s).";
  }

  const gint n_items = poppler_form_field_choice_get_n_items(choice.field);
  if (n_items < 0) {
    FreeFieldHit(&choice);
    GTEST_SKIP() << "Choice field returned a negative item count (unexpected); skipping.";
  }

  // Boundary: index == n_items is out of range.
  g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*assertion*index >= 0*index <*failed*");
  gchar *item = poppler_form_field_choice_get_item(choice.field, n_items);
  g_test_assert_expected_messages();

  EXPECT_EQ(item, nullptr);

  FreeFieldHit(&choice);
}

TEST_F(PopplerFormFieldChoiceGetItemTest_2346, WrongFieldTypeReturnsNullAndLogsCritical_2346) {
  // Find any non-choice field; most form PDFs contain text/button/signature too, but we keep it generic.
  FieldHit non_choice = FindFirstField(doc_, [](PopplerFormField *f) {
    return f && poppler_form_field_get_field_type(f) != POPPLER_FORM_FIELD_CHOICE;
  });

  if (!non_choice.field) {
    FreeFieldHit(&non_choice);
    GTEST_SKIP() << "No non-choice form field found in the available test PDF(s).";
  }

  // Precondition: field->widget->getType() == formChoice, so wrong type should CRITICAL and return NULL.
  g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*assertion*getType*formChoice*failed*");
  gchar *item = poppler_form_field_choice_get_item(non_choice.field, 0);
  g_test_assert_expected_messages();

  EXPECT_EQ(item, nullptr);

  FreeFieldHit(&non_choice);
}

} // namespace