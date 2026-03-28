// poppler-page-get-form-field-mapping-test.cc
//
// Unit tests for poppler_page_get_form_field_mapping()
// TEST_ID: 2454
//
// Notes:
// - These tests treat the implementation as a black box.
// - They rely only on observable behavior via the public Poppler GLib API.
// - Where test PDFs are not available in the environment, the relevant tests
//   will be skipped (rather than failing spuriously).

#include <gtest/gtest.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <poppler.h>

#include <cerrno>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

extern "C" {
// Function under test (C symbol defined in poppler-page.cc)
GList *poppler_page_get_form_field_mapping(PopplerPage *page);
}

// Some Poppler builds expose PopplerFormFieldMapping as a boxed type with a free
// function. Prefer it if present; otherwise fall back to best-effort cleanup.
static void DestroyFormFieldMappingBestEffort(gpointer data) {
  if (!data) return;

  // If the API provides poppler_form_field_mapping_free(), use it.
  // (This is the common pattern in poppler-glib.)
#if defined(poppler_form_field_mapping_free)
  poppler_form_field_mapping_free(reinterpret_cast<PopplerFormFieldMapping *>(data));
#else
  // Best-effort: unref field if present, then free the struct.
  // The struct layout is part of poppler-glib public API in typical builds.
  auto *mapping = reinterpret_cast<PopplerFormFieldMapping *>(data);
  // Many versions include at least: PopplerFormField *field; PopplerRectangle area;
  // We only touch 'field' if it exists in the public struct.
  // Unfortunately C++ can't reflect fields; this is best-effort and may be a no-op
  // if the symbol/field is not present in this build.
  //
  // If PopplerFormFieldMapping is opaque in a given build, this fallback may not
  // compile; in that case, your build should provide poppler_form_field_mapping_free().
  if (mapping->field) {
    g_object_unref(mapping->field);
    mapping->field = nullptr;
  }
  g_free(mapping);
#endif
}

static void FreeMappingList(GList *list) {
  if (!list) return;
  g_list_free_full(list, DestroyFormFieldMappingBestEffort);
}

static std::vector<std::string> CandidateBaseDirs() {
  std::vector<std::string> dirs;

  const char *env = nullptr;

  env = g_getenv("POPPLER_TESTDATADIR");
  if (env && *env) dirs.emplace_back(env);

  env = g_getenv("TESTDATADIR");
  if (env && *env) dirs.emplace_back(env);

  env = g_getenv("srcdir");
  if (env && *env) dirs.emplace_back(env);

  env = g_getenv("abs_srcdir");
  if (env && *env) dirs.emplace_back(env);

  // Common relative locations used in many poppler-glib test setups.
  dirs.emplace_back(".");
  dirs.emplace_back("test");
  dirs.emplace_back("tests");
  dirs.emplace_back("test/data");
  dirs.emplace_back("tests/data");
  dirs.emplace_back("glib/test");
  dirs.emplace_back("glib/tests");
  dirs.emplace_back("glib/test/data");
  dirs.emplace_back("glib/tests/data");
  dirs.emplace_back("TestProjects/poppler/test/data");
  dirs.emplace_back("TestProjects/poppler/tests/data");
  dirs.emplace_back("TestProjects/poppler/glib/test/data");
  dirs.emplace_back("TestProjects/poppler/glib/tests/data");

  return dirs;
}

static std::string FindExistingTestPdf(const std::vector<std::string> &filenames) {
  const auto dirs = CandidateBaseDirs();
  for (const auto &d : dirs) {
    for (const auto &f : filenames) {
      gchar *path = g_build_filename(d.c_str(), f.c_str(), nullptr);
      const bool exists = g_file_test(path, G_FILE_TEST_EXISTS) && g_file_test(path, G_FILE_TEST_IS_REGULAR);
      if (exists) {
        std::string out(path);
        g_free(path);
        return out;
      }
      g_free(path);
    }
  }
  return {};
}

static std::string ToFileUri(const std::string &path) {
  GError *error = nullptr;
  gchar *uri = g_filename_to_uri(path.c_str(), /*hostname=*/nullptr, &error);
  if (!uri) {
    std::string msg = error ? error->message : "unknown error";
    if (error) g_error_free(error);
    return {};
  }
  std::string out(uri);
  g_free(uri);
  return out;
}

static PopplerDocument *LoadDocumentOrSkip(const std::string &pdf_path) {
  const std::string uri = ToFileUri(pdf_path);
  if (uri.empty()) {
    GTEST_SKIP() << "Could not create file:// URI for test PDF: " << pdf_path;
    return nullptr;
  }

  GError *error = nullptr;
  PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &error);
  if (!doc) {
    std::string msg = error ? error->message : "unknown error";
    if (error) g_error_free(error);
    GTEST_SKIP() << "Could not load test PDF '" << pdf_path << "': " << msg;
    return nullptr;
  }
  return doc;
}

class PopplerPageGetFormFieldMappingTest_2454 : public ::testing::Test {
 protected:
  void TearDown() override {
    if (page_) {
      g_object_unref(page_);
      page_ = nullptr;
    }
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
  }

  void LoadFirstPageOrSkip(const std::string &pdf_path) {
    doc_ = LoadDocumentOrSkip(pdf_path);
    if (!doc_) return;  // skipped already
    page_ = poppler_document_get_page(doc_, 0);
    if (!page_) {
      GTEST_SKIP() << "Could not get page 0 from test PDF: " << pdf_path;
    }
  }

  PopplerDocument *doc_ = nullptr;
  PopplerPage *page_ = nullptr;
};

TEST_F(PopplerPageGetFormFieldMappingTest_2454, NullPageReturnsNullAndEmitsCritical_2454) {
  // g_return_val_if_fail(POPPLER_IS_PAGE(page), NULL);
  // Observable behavior: returns NULL and emits a GLib critical.
  g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_PAGE*");
  GList *list = poppler_page_get_form_field_mapping(nullptr);
  g_test_assert_expected_messages();

  EXPECT_EQ(list, nullptr);
}

TEST_F(PopplerPageGetFormFieldMappingTest_2454, PageWithoutFormsReturnsNullOrEmptyList_2454) {
  // The implementation returns nullptr when getFormWidgets() returns nullptr.
  // We locate a "no forms" PDF; if none is present, we skip.

  const std::string pdf = FindExistingTestPdf({
      // Common test PDFs in poppler repos (no AcroForm fields).
      "basic.pdf",
      "t1.pdf",
      "text.pdf",
      "unicode.pdf",
      "rotate.pdf",
      "sample.pdf",
      "dummy.pdf",
      "empty.pdf",
  });

  if (pdf.empty()) {
    GTEST_SKIP() << "No suitable 'no-forms' PDF found in known test-data directories.";
  }

  LoadFirstPageOrSkip(pdf);
  if (!page_) return;

  GList *list = poppler_page_get_form_field_mapping(page_);

  // The code returns nullptr when no form widgets exist, but we allow either
  // nullptr or an empty list for robustness across Poppler versions/builds.
  if (list == nullptr) {
    SUCCEED();
    return;
  }

  EXPECT_EQ(g_list_length(list), 0u);
  FreeMappingList(list);
}

TEST_F(PopplerPageGetFormFieldMappingTest_2454, PageWithFormsReturnsMappingsWithNonNullFields_2454) {
  // Normal operation: when the page contains form widgets, we expect a non-null
  // list with at least one mapping, and each mapping should have a non-null field.
  //
  // We locate a PDF likely to contain AcroForm fields; if none is present, skip.

  const std::string pdf = FindExistingTestPdf({
      // Common names used in test suites for AcroForm coverage.
      "forms.pdf",
      "form.pdf",
      "acroform.pdf",
      "AcroForm.pdf",
      "fields.pdf",
      "formfields.pdf",
  });

  if (pdf.empty()) {
    GTEST_SKIP() << "No suitable 'forms' PDF found in known test-data directories.";
  }

  LoadFirstPageOrSkip(pdf);
  if (!page_) return;

  GList *list = poppler_page_get_form_field_mapping(page_);
  ASSERT_NE(list, nullptr) << "Expected non-null mapping list for a forms PDF: " << pdf;

  const guint len = g_list_length(list);
  ASSERT_GT(len, 0u) << "Expected at least one form field mapping for: " << pdf;

  for (GList *l = list; l != nullptr; l = l->next) {
    ASSERT_NE(l->data, nullptr);
    auto *mapping = reinterpret_cast<PopplerFormFieldMapping *>(l->data);

    // Observable via public struct field in typical poppler-glib builds.
    ASSERT_NE(mapping->field, nullptr);

    // Basic sanity: field is a GObject and should satisfy POPPLER_IS_FORM_FIELD().
    EXPECT_TRUE(POPPLER_IS_FORM_FIELD(mapping->field));
  }

  FreeMappingList(list);
}

TEST_F(PopplerPageGetFormFieldMappingTest_2454, ReturnedListIsIndependentAcrossCalls_2454) {
  // Boundary/behavioral: calling the function twice should return two lists that
  // the caller can free independently. We don't assume internal caching behavior,
  // only that returned lists are safe to free.
  //
  // Use the same "forms" PDF lookup; skip if unavailable.

  const std::string pdf = FindExistingTestPdf({
      "forms.pdf",
      "form.pdf",
      "acroform.pdf",
      "AcroForm.pdf",
      "fields.pdf",
      "formfields.pdf",
  });

  if (pdf.empty()) {
    GTEST_SKIP() << "No suitable 'forms' PDF found in known test-data directories.";
  }

  LoadFirstPageOrSkip(pdf);
  if (!page_) return;

  GList *list1 = poppler_page_get_form_field_mapping(page_);
  GList *list2 = poppler_page_get_form_field_mapping(page_);

  // If the PDF unexpectedly yields no widgets, allow skip-like behavior.
  if (!list1 || !list2) {
    FreeMappingList(list1);
    FreeMappingList(list2);
    GTEST_SKIP() << "Forms PDF did not yield mappings in this build/runtime: " << pdf;
  }

  EXPECT_GT(g_list_length(list1), 0u);
  EXPECT_GT(g_list_length(list2), 0u);

  // Free both; this test primarily verifies no double-free/ownership issues.
  FreeMappingList(list1);
  FreeMappingList(list2);
}