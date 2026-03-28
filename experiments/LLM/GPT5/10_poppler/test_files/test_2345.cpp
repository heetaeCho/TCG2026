// poppler-form-field-choice-get-n-items-test_2345.cc
//
// Unit tests for:
//   gint poppler_form_field_choice_get_n_items(PopplerFormField *field);
//
// Constraints honored:
// - Treat implementation as black box
// - Use only public/observable behavior
// - No private-state access
// - Exercise normal, boundary, and error cases (observable)
// - TEST_ID appended to every test name

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <string>
#include <vector>

// ---------------------------
// Small GLib helpers
// ---------------------------
namespace {

struct GObjectDeleter {
  void operator()(gpointer p) const {
    if (p) {
      g_object_unref(p);
    }
  }
};

template <typename T>
using GObjectPtr = std::unique_ptr<T, GObjectDeleter>;

static std::string JoinPath(const std::string &a, const std::string &b) {
  if (a.empty()) return b;
  if (a.back() == G_DIR_SEPARATOR) return a + b;
  return a + G_DIR_SEPARATOR_S + b;
}

static GObjectPtr<PopplerDocument> TryOpenDocFromCandidates(const std::vector<std::string> &candidates) {
  const char *srcdir = g_getenv("srcdir");
  const std::string base = (srcdir && *srcdir) ? std::string(srcdir) : std::string(".");

  for (const auto &name : candidates) {
    const std::string path = JoinPath(base, name);
    gchar *uri = g_filename_to_uri(path.c_str(), nullptr, nullptr);
    if (!uri) {
      continue;
    }

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file(uri, /*password*/ nullptr, &error);
    g_free(uri);

    if (doc) {
      if (error) g_error_free(error);
      return GObjectPtr<PopplerDocument>(doc);
    }

    if (error) g_error_free(error);
  }

  return GObjectPtr<PopplerDocument>(nullptr);
}

static GObjectPtr<PopplerPage> GetPage(PopplerDocument *doc, int index) {
  if (!doc) return GObjectPtr<PopplerPage>(nullptr);
  PopplerPage *page = poppler_document_get_page(doc, index);
  return GObjectPtr<PopplerPage>(page);
}

static PopplerFormField *FindFirstFieldOfType(PopplerPage *page, PopplerFormFieldType wanted_type) {
  if (!page) return nullptr;

  GList *mapping = poppler_page_get_form_field_mapping(page);
  for (GList *l = mapping; l; l = l->next) {
    auto *m = static_cast<PopplerFormFieldMapping *>(l->data);
    if (!m || !m->field) continue;
    if (poppler_form_field_get_field_type(m->field) == wanted_type) {
      // Keep ownership with mapping list; caller must not unref the field.
      poppler_page_free_form_field_mapping(mapping);
      return m->field;
    }
  }
  poppler_page_free_form_field_mapping(mapping);
  return nullptr;
}

// Captures *all* GLib log messages via the default handler.
// Useful to observe g_return_val_if_fail() criticals without relying on log domain.
class ScopedDefaultLogCapture {
 public:
  ScopedDefaultLogCapture() {
    prev_ = g_log_set_default_handler(&ScopedDefaultLogCapture::HandlerThunk, this);
  }

  ~ScopedDefaultLogCapture() {
    g_log_set_default_handler(prev_, nullptr);
  }

  bool saw_critical() const { return saw_critical_; }

 private:
  static void HandlerThunk(const gchar *log_domain,
                           GLogLevelFlags log_level,
                           const gchar *message,
                           gpointer user_data) {
    auto *self = static_cast<ScopedDefaultLogCapture *>(user_data);
    self->Handle(log_domain, log_level, message);
  }

  void Handle(const gchar * /*log_domain*/, GLogLevelFlags log_level, const gchar * /*message*/) {
    // GLib may OR flags (e.g., fatal), so test with bitmask.
    if ((log_level & G_LOG_LEVEL_CRITICAL) != 0) {
      saw_critical_ = true;
    }
    // Swallow output to keep tests clean.
  }

  GLogFunc prev_{nullptr};
  bool saw_critical_{false};
};

static GObjectPtr<PopplerDocument> OpenAnyFormDocOrSkip() {
  // Common Poppler test filenames across repos; try a handful.
  // If none exist in this environment, we skip rather than fail.
  const std::vector<std::string> candidates = {
      "forms.pdf",
      "form.pdf",
      "test.pdf",
      "testdata/forms.pdf",
      "testdata/form.pdf",
      "testdata/test.pdf",
  };

  auto doc = TryOpenDocFromCandidates(candidates);
  if (!doc) {
    GTEST_SKIP() << "No suitable test PDF found (tried common candidates under $srcdir).";
  }
  return doc;
}

}  // namespace

// ---------------------------
// Tests (TEST_ID = 2345)
// ---------------------------

class PopplerFormFieldChoiceGetNItemsTest_2345 : public ::testing::Test {
 protected:
  void SetUp() override {
    doc_ = OpenAnyFormDocOrSkip();
    // Search first few pages; forms PDFs often keep fields early.
    for (int i = 0; i < 10 && i < poppler_document_get_n_pages(doc_.get()); ++i) {
      auto page = GetPage(doc_.get(), i);
      if (!page) continue;

      if (!choice_field_) {
        choice_field_ = FindFirstFieldOfType(page.get(), POPPLER_FORM_FIELD_CHOICE);
      }
      if (!non_choice_field_) {
        // Prefer a text field as a clear non-choice case; fallback to button/signature if needed.
        non_choice_field_ = FindFirstFieldOfType(page.get(), POPPLER_FORM_FIELD_TEXT);
        if (!non_choice_field_) non_choice_field_ = FindFirstFieldOfType(page.get(), POPPLER_FORM_FIELD_BUTTON);
        if (!non_choice_field_) non_choice_field_ = FindFirstFieldOfType(page.get(), POPPLER_FORM_FIELD_SIGNATURE);
      }

      if (choice_field_ && non_choice_field_) break;
    }
  }

  GObjectPtr<PopplerDocument> doc_{nullptr};
  PopplerFormField *choice_field_{nullptr};      // borrowed from mapping list
  PopplerFormField *non_choice_field_{nullptr};  // borrowed from mapping list
};

TEST_F(PopplerFormFieldChoiceGetNItemsTest_2345, ReturnsNonNegativeForChoiceField_2345) {
  if (!choice_field_) {
    GTEST_SKIP() << "No choice form field found in available test PDF.";
  }

  const gint n = poppler_form_field_choice_get_n_items(choice_field_);
  EXPECT_GE(n, 0) << "Expected non-negative item count for a choice field.";
}

TEST_F(PopplerFormFieldChoiceGetNItemsTest_2345, IsDeterministicAcrossCalls_2345) {
  if (!choice_field_) {
    GTEST_SKIP() << "No choice form field found in available test PDF.";
  }

  const gint n1 = poppler_form_field_choice_get_n_items(choice_field_);
  const gint n2 = poppler_form_field_choice_get_n_items(choice_field_);

  // Observable behavior: repeated calls should be stable absent other interactions.
  EXPECT_EQ(n1, n2);
  EXPECT_GE(n1, 0);
}

TEST_F(PopplerFormFieldChoiceGetNItemsTest_2345, BoundaryAllowsZeroItems_2345) {
  if (!choice_field_) {
    GTEST_SKIP() << "No choice form field found in available test PDF.";
  }

  const gint n = poppler_form_field_choice_get_n_items(choice_field_);

  // Boundary-focused assertion: zero is allowed (e.g., empty list/combo in malformed/minimal PDFs),
  // as well as positive values. This test ensures we don't incorrectly require >0.
  EXPECT_GE(n, 0);
}

TEST_F(PopplerFormFieldChoiceGetNItemsTest_2345, ReturnsMinusOneAndEmitsCriticalForNonChoiceField_2345) {
  if (!non_choice_field_) {
    GTEST_SKIP() << "No non-choice form field found in available test PDF.";
  }

  ScopedDefaultLogCapture capture;

  const gint n = poppler_form_field_choice_get_n_items(non_choice_field_);
  EXPECT_EQ(n, -1) << "Expected -1 for non-choice field input (g_return_val_if_fail contract).";
  EXPECT_TRUE(capture.saw_critical())
      << "Expected a GLib critical log due to g_return_val_if_fail when field is not formChoice.";
}