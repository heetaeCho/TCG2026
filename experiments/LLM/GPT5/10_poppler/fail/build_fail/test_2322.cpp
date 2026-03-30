// File: poppler-form-field-signature-validate-sync-test_2322.cc
#include <gtest/gtest.h>
#include <glib.h>
#include <gio/gio.h>

#include <poppler.h>

namespace {

constexpr const char* kCandidatePdfRelPaths[] = {
    // From poppler/test regression suite signature cases (see mailing list archive).
    "unittestcases/signature/valid/sha1.pdf",
    "unittestcases/signature/valid/detached.pdf",
    "unittestcases/signature/valid/etsi.pdf",
    "unittestcases/signature/valid/sha1_mixed_functions.pdf",
    // Fallbacks (in case the project vendors PDFs elsewhere):
    "testdata/unittestcases/signature/valid/sha1.pdf",
    "tests/unittestcases/signature/valid/sha1.pdf",
};

static std::string BuildPathFromSrcdirOrCwd(const char* rel) {
  const char* srcdir = g_getenv("srcdir");
  if (srcdir && *srcdir) {
    gchar* p = g_build_filename(srcdir, rel, nullptr);
    std::string out = p ? p : "";
    g_free(p);
    return out;
  }
  // current working directory
  gchar* cwd = g_get_current_dir();
  gchar* p = g_build_filename(cwd, rel, nullptr);
  std::string out = p ? p : "";
  g_free(p);
  g_free(cwd);
  return out;
}

static std::string FindExistingPdfPathOrEmpty() {
  for (const char* rel : kCandidatePdfRelPaths) {
    std::string abs = BuildPathFromSrcdirOrCwd(rel);
    if (!abs.empty() && g_file_test(abs.c_str(), G_FILE_TEST_IS_REGULAR)) {
      return abs;
    }
  }
  return {};
}

static PopplerDocument* LoadDocumentFromPdfOrSkip() {
  std::string pdf_path = FindExistingPdfPathOrEmpty();
  if (pdf_path.empty()) {
    GTEST_SKIP() << "No signature test PDF found in known locations.";
  }

  GError* error = nullptr;
  gchar* uri = g_filename_to_uri(pdf_path.c_str(), nullptr, &error);
  if (!uri) {
    std::string msg = error ? error->message : "unknown error";
    if (error) g_error_free(error);
    GTEST_SKIP() << "Failed to build file URI for test PDF: " << msg;
  }

  PopplerDocument* doc = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
  g_free(uri);

  if (!doc) {
    std::string msg = error ? error->message : "unknown error";
    if (error) g_error_free(error);
    GTEST_SKIP() << "Failed to load test PDF into PopplerDocument: " << msg;
  }

  return doc;
}

static PopplerFormField* FindSignatureFormFieldOrSkip(PopplerDocument* doc) {
  const int n_pages = poppler_document_get_n_pages(doc);
  for (int i = 0; i < n_pages; ++i) {
    PopplerPage* page = poppler_document_get_page(doc, i);
    if (!page) continue;

    GList* mappings = poppler_page_get_form_field_mapping(page);
    for (GList* it = mappings; it; it = it->next) {
      auto* mapping = static_cast<PopplerFormFieldMapping*>(it->data);
      if (!mapping || !mapping->field) continue;

      const PopplerFormFieldType type = poppler_form_field_get_field_type(mapping->field);
      if (type == POPPLER_FORM_FIELD_SIGNATURE) {
        // Keep a ref so it remains valid after freeing mappings/page.
        PopplerFormField* out = static_cast<PopplerFormField*>(g_object_ref(mapping->field));
        poppler_page_free_form_field_mapping(mappings);
        g_object_unref(page);
        return out;
      }
    }

    poppler_page_free_form_field_mapping(mappings);
    g_object_unref(page);
  }

  GTEST_SKIP() << "No signature form field found in the available test PDF.";
}

// Minimal log capture so g_return_val_if_fail() doesn't spew to stderr or abort under fatal criticals.
struct LogCapture {
  guint handler_id_null = 0;
  guint handler_id_poppler = 0;
  GLogLevelFlags old_fatal = (GLogLevelFlags)0;

  static void Handler(const gchar* /*log_domain*/,
                      GLogLevelFlags /*log_level*/,
                      const gchar* /*message*/,
                      gpointer /*user_data*/) {
    // Swallow.
  }

  void InstallForCriticals() {
    // Ensure CRITICAL isn't fatal for this test block.
    old_fatal = g_log_set_always_fatal((GLogLevelFlags)0);

    // Some builds may use NULL domain; others may use "Poppler" domain.
    handler_id_null = g_log_set_handler(nullptr, (GLogLevelFlags)G_LOG_LEVEL_CRITICAL, &Handler, nullptr);
    handler_id_poppler = g_log_set_handler("Poppler", (GLogLevelFlags)G_LOG_LEVEL_CRITICAL, &Handler, nullptr);
  }

  void Uninstall() {
    if (handler_id_null) g_log_remove_handler(nullptr, handler_id_null);
    if (handler_id_poppler) g_log_remove_handler("Poppler", handler_id_poppler);
    g_log_set_always_fatal(old_fatal);
  }
};

class PopplerFormFieldSignatureValidateSyncTest_2322 : public ::testing::Test {
 protected:
  void TearDown() override {
    if (field_) g_object_unref(field_);
    if (doc_) g_object_unref(doc_);
    field_ = nullptr;
    doc_ = nullptr;
  }

  void EnsureSignatureFieldLoadedOrSkip() {
    if (field_) return;
    doc_ = LoadDocumentFromPdfOrSkip();
    field_ = FindSignatureFormFieldOrSkip(doc_);
  }

  PopplerDocument* doc_ = nullptr;
  PopplerFormField* field_ = nullptr;
};

TEST_F(PopplerFormFieldSignatureValidateSyncTest_2322, ReturnsNullIfErrorAlreadySet_2322) {
  // This exercises the observable g_return_val_if_fail() contract:
  // error == nullptr || *error == nullptr must hold, otherwise NULL is returned.
  LogCapture cap;
  cap.InstallForCriticals();

  GError* preset = g_error_new_literal(G_IO_ERROR, G_IO_ERROR_FAILED, "preset");
  ASSERT_NE(preset, nullptr);

  PopplerSignatureInfo* info =
      poppler_form_field_signature_validate_sync(/*field=*/nullptr,
                                                 (PopplerSignatureValidationFlags)0,
                                                 /*cancellable=*/nullptr,
                                                 /*error=*/&preset);

  EXPECT_EQ(info, nullptr);
  EXPECT_NE(preset, nullptr);  // Should remain set (function must not require clearing it).

  g_error_free(preset);
  cap.Uninstall();
}

TEST_F(PopplerFormFieldSignatureValidateSyncTest_2322, CancelledCancellableReturnsCancelledError_2322) {
  EnsureSignatureFieldLoadedOrSkip();

  GError* error = nullptr;
  GCancellable* cancellable = g_cancellable_new();
  ASSERT_NE(cancellable, nullptr);

  // Cancel before invocation to force the "return on cancel" behavior.
  g_cancellable_cancel(cancellable);

  PopplerSignatureInfo* info =
      poppler_form_field_signature_validate_sync(field_,
                                                 (PopplerSignatureValidationFlags)0,
                                                 cancellable,
                                                 &error);

  EXPECT_EQ(info, nullptr);
  ASSERT_NE(error, nullptr);
  EXPECT_TRUE(g_error_matches(error, G_IO_ERROR, G_IO_ERROR_CANCELLED));

  g_error_free(error);
  g_object_unref(cancellable);
}

TEST_F(PopplerFormFieldSignatureValidateSyncTest_2322, NonCancelledEitherReturnsInfoOrSetsError_2322) {
  EnsureSignatureFieldLoadedOrSkip();

  GError* error = nullptr;
  PopplerSignatureInfo* info =
      poppler_form_field_signature_validate_sync(field_,
                                                 (PopplerSignatureValidationFlags)0,
                                                 /*cancellable=*/nullptr,
                                                 &error);

  // Observable interface expectations:
  // - If info is returned, error must remain NULL.
  // - If info is NULL, an error may be provided (implementation-defined).
  if (info) {
    EXPECT_EQ(error, nullptr);
    poppler_signature_info_free(info);
  } else {
    // If it failed, we should at least not claim "cancelled" when no cancellable was supplied.
    ASSERT_NE(error, nullptr);
    EXPECT_FALSE(g_error_matches(error, G_IO_ERROR, G_IO_ERROR_CANCELLED));
    g_error_free(error);
  }
}

TEST_F(PopplerFormFieldSignatureValidateSyncTest_2322, WorksWithExplicitCancellableNotCancelled_2322) {
  EnsureSignatureFieldLoadedOrSkip();

  GCancellable* cancellable = g_cancellable_new();
  ASSERT_NE(cancellable, nullptr);

  GError* error = nullptr;
  PopplerSignatureInfo* info =
      poppler_form_field_signature_validate_sync(field_,
                                                 (PopplerSignatureValidationFlags)0,
                                                 cancellable,
                                                 &error);

  // Same observable contract as the non-cancellable case.
  if (info) {
    EXPECT_EQ(error, nullptr);
    poppler_signature_info_free(info);
  } else {
    ASSERT_NE(error, nullptr);
    EXPECT_FALSE(g_error_matches(error, G_IO_ERROR, G_IO_ERROR_CANCELLED));
    g_error_free(error);
  }

  g_object_unref(cancellable);
}

}  // namespace