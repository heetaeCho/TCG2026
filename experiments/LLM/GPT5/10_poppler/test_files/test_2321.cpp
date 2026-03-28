// poppler-form-field-signature-validate-test_2321.cc
//
// Unit tests for Poppler GLib signature validation behavior.
//
// These tests treat Poppler as a black box and only verify observable behavior
// via the public GLib API.
//
// NOTE: Some tests require a PDF containing a signature form field. If no such
// test PDF is available in the build/test environment, those tests will skip.

#include <gtest/gtest.h>

#include <poppler.h>

#include <glib.h>

#include <string>
#include <vector>

namespace {

class ScopedGError_2321 {
 public:
  ScopedGError_2321() = default;
  ~ScopedGError_2321() { reset(); }

  ScopedGError_2321(const ScopedGError_2321&) = delete;
  ScopedGError_2321& operator=(const ScopedGError_2321&) = delete;

  GError** out() { return &err_; }
  GError* get() const { return err_; }

  void reset() {
    if (err_) {
      g_error_free(err_);
      err_ = nullptr;
    }
  }

 private:
  GError* err_ = nullptr;
};

class ScopedGObject_2321 {
 public:
  explicit ScopedGObject_2321(gpointer obj = nullptr) : obj_(obj) {}
  ~ScopedGObject_2321() { reset(); }

  ScopedGObject_2321(const ScopedGObject_2321&) = delete;
  ScopedGObject_2321& operator=(const ScopedGObject_2321&) = delete;

  gpointer get() const { return obj_; }
  template <typename T>
  T* as() const {
    return reinterpret_cast<T*>(obj_);
  }

  void reset(gpointer obj = nullptr) {
    if (obj_) {
      g_object_unref(obj_);
    }
    obj_ = obj;
  }

 private:
  gpointer obj_ = nullptr;
};

static std::string JoinPath_2321(const std::string& a, const std::string& b) {
  if (a.empty()) return b;
  if (!a.empty() && a.back() == G_DIR_SEPARATOR) return a + b;
  return a + G_DIR_SEPARATOR_S + b;
}

static bool FileExists_2321(const std::string& path) {
  return g_file_test(path.c_str(), G_FILE_TEST_EXISTS) != FALSE;
}

// Try to locate a usable PDF from common Poppler test env vars and typical paths.
// Returns nullptr if not found.
static PopplerDocument* TryLoadAnyTestPdf_2321(std::string* out_uri_used) {
  // Candidate base directories (env-driven first).
  std::vector<std::string> base_dirs;

  const char* env_datadir = g_getenv("POPPLER_TEST_DATADIR");
  if (env_datadir && *env_datadir) base_dirs.emplace_back(env_datadir);

  const char* env_srcdir = g_getenv("srcdir");
  if (env_srcdir && *env_srcdir) base_dirs.emplace_back(env_srcdir);

  // Common relative fallbacks.
  base_dirs.emplace_back(".");
  base_dirs.emplace_back("test-data");
  base_dirs.emplace_back("tests");
  base_dirs.emplace_back("TestProjects/poppler/test-data");
  base_dirs.emplace_back("TestProjects/poppler/glib/test-data");

  // Candidate filenames: we try several, because different Poppler trees use
  // different names for form/signature PDFs.
  const std::vector<std::string> pdf_names = {
      "forms.pdf",
      "form.pdf",
      "signature.pdf",
      "signatures.pdf",
      "digital-signature.pdf",
      "digitalsignature.pdf",
      "acroforms.pdf",
      "acroform.pdf",
  };

  for (const auto& dir : base_dirs) {
    for (const auto& name : pdf_names) {
      const std::string path = JoinPath_2321(dir, name);
      if (!FileExists_2321(path)) continue;

      gchar* uri = g_filename_to_uri(path.c_str(), /*hostname=*/nullptr, /*error=*/nullptr);
      if (!uri) continue;

      ScopedGError_2321 err;
      PopplerDocument* doc = poppler_document_new_from_file(uri, /*password=*/nullptr, err.out());
      if (doc) {
        if (out_uri_used) *out_uri_used = uri;
        g_free(uri);
        return doc;
      }

      g_free(uri);
      // If open failed, keep searching; we don't assert here to avoid brittle tests.
    }
  }

  return nullptr;
}

static PopplerFormField* RefFirstFieldOfType_2321(PopplerDocument* doc, PopplerFormFieldType type) {
  if (!doc) return nullptr;

  const int n_pages = poppler_document_get_n_pages(doc);
  for (int i = 0; i < n_pages; ++i) {
    ScopedGObject_2321 page(poppler_document_get_page(doc, i));
    if (!page.get()) continue;

    GList* mappings = poppler_page_get_form_field_mapping(page.as<PopplerPage>());
    for (GList* it = mappings; it != nullptr; it = it->next) {
      auto* mapping = static_cast<PopplerFormFieldMapping*>(it->data);
      if (!mapping || !mapping->field) continue;

      if (poppler_form_field_get_field_type(mapping->field) == type) {
        // Ensure the returned PopplerFormField stays alive even after freeing mappings.
        PopplerFormField* field = mapping->field;
        g_object_ref(field);

        poppler_page_free_form_field_mapping(mappings);
        return field;
      }
    }
    poppler_page_free_form_field_mapping(mappings);
  }

  return nullptr;
}

// Attempts to find *any* non-signature field (text/choice/button) for negative tests.
static PopplerFormField* RefFirstNonSignatureField_2321(PopplerDocument* doc) {
  if (!doc) return nullptr;

  const PopplerFormFieldType candidates[] = {
      POPPLER_FORM_FIELD_TEXT,
      POPPLER_FORM_FIELD_CHOICE,
      POPPLER_FORM_FIELD_BUTTON,
  };

  for (PopplerFormFieldType t : candidates) {
    PopplerFormField* f = RefFirstFieldOfType_2321(doc, t);
    if (f) return f;
  }
  return nullptr;
}

static void FreeSignatureInfoIfPossible_2321(PopplerSignatureInfo* info) {
  // Newer Poppler GLib provides poppler_signature_info_free().
  // If it's not available in a given build, we avoid calling it to keep tests
  // linkable across versions. Use weak symbol style via preprocessor check.
#if defined(POPPLER_CHECK_VERSION)
#if POPPLER_CHECK_VERSION(23, 1, 0)
  poppler_signature_info_free(info);
  return;
#endif
#endif
  // Fallback: if no official free function is available, we still must avoid
  // re-implementing internal frees. Leak-avoidance is best-effort here.
  (void)info;
}

class PopplerFormFieldSignatureValidateTest_2321 : public ::testing::Test {
 protected:
  void SetUp() override {
    std::string uri_used;
    PopplerDocument* d = TryLoadAnyTestPdf_2321(&uri_used);
    doc_.reset(d);
    uri_used_ = uri_used;
  }

  bool HaveDoc() const { return doc_.get() != nullptr; }

  PopplerDocument* doc() const { return doc_.as<PopplerDocument>(); }

  std::string uri_used_;
  ScopedGObject_2321 doc_;
};

TEST_F(PopplerFormFieldSignatureValidateTest_2321, SkipIfNoPdfAvailable_2321) {
  if (!HaveDoc()) {
    GTEST_SKIP() << "No suitable test PDF found (tried common names/paths). "
                 << "Set POPPLER_TEST_DATADIR or provide a forms/signature PDF.";
  }
  SUCCEED();
}

TEST_F(PopplerFormFieldSignatureValidateTest_2321, WrongTypeSetsErrorAndReturnsNull_2321) {
  if (!HaveDoc()) {
    GTEST_SKIP() << "No test PDF available.";
  }

  ScopedGObject_2321 non_sig(RefFirstNonSignatureField_2321(doc()));
  if (!non_sig.get()) {
    GTEST_SKIP() << "No non-signature form field found in test PDF: " << uri_used_;
  }

  ScopedGError_2321 err;
  PopplerSignatureInfo* info =
      poppler_form_field_signature_validate(non_sig.as<PopplerFormField>(),
                                            static_cast<PopplerSignatureValidationFlags>(0),
                                            /*force_revalidation=*/FALSE,
                                            err.out());

  EXPECT_EQ(info, nullptr);
  ASSERT_NE(err.get(), nullptr);
  EXPECT_EQ(err.get()->domain, POPPLER_ERROR);
  EXPECT_EQ(err.get()->code, POPPLER_ERROR_INVALID);
  ASSERT_NE(err.get()->message, nullptr);
  EXPECT_NE(std::string(err.get()->message).find("Wrong FormField type"), std::string::npos);
}

TEST_F(PopplerFormFieldSignatureValidateTest_2321, WrongTypeWithNullErrorOutDoesNotCrashAndReturnsNull_2321) {
  if (!HaveDoc()) {
    GTEST_SKIP() << "No test PDF available.";
  }

  ScopedGObject_2321 non_sig(RefFirstNonSignatureField_2321(doc()));
  if (!non_sig.get()) {
    GTEST_SKIP() << "No non-signature form field found in test PDF: " << uri_used_;
  }

  // Passing nullptr for GError** must be safe and should still return nullptr.
  PopplerSignatureInfo* info =
      poppler_form_field_signature_validate(non_sig.as<PopplerFormField>(),
                                            static_cast<PopplerSignatureValidationFlags>(0),
                                            /*force_revalidation=*/FALSE,
                                            /*error=*/nullptr);

  EXPECT_EQ(info, nullptr);
}

TEST_F(PopplerFormFieldSignatureValidateTest_2321, SignatureValidateReturnsNonNullInfoWhenSignatureFieldExists_2321) {
  if (!HaveDoc()) {
    GTEST_SKIP() << "No test PDF available.";
  }

  ScopedGObject_2321 sig(RefFirstFieldOfType_2321(doc(), POPPLER_FORM_FIELD_SIGNATURE));
  if (!sig.get()) {
    GTEST_SKIP() << "No signature form field found in test PDF: " << uri_used_;
  }

  ScopedGError_2321 err;
  PopplerSignatureInfo* info =
      poppler_form_field_signature_validate(sig.as<PopplerFormField>(),
                                            static_cast<PopplerSignatureValidationFlags>(0),
                                            /*force_revalidation=*/FALSE,
                                            err.out());

  ASSERT_EQ(err.get(), nullptr) << (err.get() ? err.get()->message : "");
  ASSERT_NE(info, nullptr);

  // Observable/basic sanity checks (no assumptions about underlying crypto result).
  EXPECT_GE(info->sig_status, 0);
  EXPECT_LE(info->sig_status, 6);  // SignatureValidationStatus has 0..6 mapped.

  EXPECT_GE(info->cert_status, POPPLER_CERTIFICATE_TRUSTED);
  EXPECT_LE(info->cert_status, POPPLER_CERTIFICATE_NOT_VERIFIED);

  // signer_name should be a valid C string (may be empty depending on input PDF).
  ASSERT_NE(info->signer_name, nullptr);

  // local_signing_time is expected to be set (per implementation it is always created).
  ASSERT_NE(info->local_signing_time, nullptr);

  // certificate_info is optional; if present, key strings should be non-null.
  if (info->certificate_info) {
    // These are set via g_strdup of std::string, which should yield non-null pointers
    // (possibly empty strings). We only assert non-null, not content.
    EXPECT_NE(info->certificate_info->subject_common_name, nullptr);
    EXPECT_NE(info->certificate_info->subject_organization, nullptr);
    EXPECT_NE(info->certificate_info->subject_email, nullptr);

    EXPECT_NE(info->certificate_info->issuer_common_name, nullptr);
    EXPECT_NE(info->certificate_info->issuer_organization, nullptr);
    EXPECT_NE(info->certificate_info->issuer_email, nullptr);

    EXPECT_NE(info->certificate_info->issued, nullptr);
    EXPECT_NE(info->certificate_info->expires, nullptr);
  }

  FreeSignatureInfoIfPossible_2321(info);
}

TEST_F(PopplerFormFieldSignatureValidateTest_2321, SignatureValidateAcceptsAllFlagsAndForceRevalidation_2321) {
  if (!HaveDoc()) {
    GTEST_SKIP() << "No test PDF available.";
  }

  ScopedGObject_2321 sig(RefFirstFieldOfType_2321(doc(), POPPLER_FORM_FIELD_SIGNATURE));
  if (!sig.get()) {
    GTEST_SKIP() << "No signature form field found in test PDF: " << uri_used_;
  }

  const PopplerSignatureValidationFlags all_flags = static_cast<PopplerSignatureValidationFlags>(
      POPPLER_SIGNATURE_VALIDATION_FLAG_VALIDATE_CERTIFICATE |
      POPPLER_SIGNATURE_VALIDATION_FLAG_WITHOUT_OCSP_REVOCATION_CHECK |
      POPPLER_SIGNATURE_VALIDATION_FLAG_USE_AIA_CERTIFICATE_FETCH);

  ScopedGError_2321 err;
  PopplerSignatureInfo* info =
      poppler_form_field_signature_validate(sig.as<PopplerFormField>(),
                                            all_flags,
                                            /*force_revalidation=*/TRUE,
                                            err.out());

  // We don't assume the signature becomes valid; we only verify the call is accepted
  // and produces a result without surfacing a GLib error through the interface.
  ASSERT_EQ(err.get(), nullptr) << (err.get() ? err.get()->message : "");
  ASSERT_NE(info, nullptr);

  ASSERT_NE(info->signer_name, nullptr);
  ASSERT_NE(info->local_signing_time, nullptr);

  FreeSignatureInfoIfPossible_2321(info);
}

}  // namespace