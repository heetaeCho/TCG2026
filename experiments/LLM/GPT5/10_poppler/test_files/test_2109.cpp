// poppler_annot_movie_get_title_test_2109.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

#include <cstdlib>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

namespace {

class ScopedGObject {
public:
  explicit ScopedGObject(gpointer obj = nullptr) : obj_(obj) {}
  ~ScopedGObject() {
    if (obj_) {
      g_object_unref(obj_);
    }
  }
  ScopedGObject(const ScopedGObject&) = delete;
  ScopedGObject& operator=(const ScopedGObject&) = delete;

  gpointer get() const { return obj_; }
  gpointer release() {
    gpointer tmp = obj_;
    obj_ = nullptr;
    return tmp;
  }

private:
  gpointer obj_;
};

class ScopedGError {
public:
  ScopedGError() = default;
  ~ScopedGError() {
    if (err_) {
      g_error_free(err_);
    }
  }
  ScopedGError(const ScopedGError&) = delete;
  ScopedGError& operator=(const ScopedGError&) = delete;

  GError** out() { return &err_; }
  GError* get() const { return err_; }

private:
  GError* err_ = nullptr;
};

class ScopedGChar {
public:
  explicit ScopedGChar(gchar* s = nullptr) : s_(s) {}
  ~ScopedGChar() {
    if (s_) {
      g_free(s_);
    }
  }
  ScopedGChar(const ScopedGChar&) = delete;
  ScopedGChar& operator=(const ScopedGChar&) = delete;

  gchar* get() const { return s_; }
  gchar* release() {
    gchar* tmp = s_;
    s_ = nullptr;
    return tmp;
  }

private:
  gchar* s_;
};

// Captures GLib log messages at CRITICAL level so we can verify g_return_val_if_fail behavior
// without relying on GLib's own test framework.
class ScopedGLogCapture {
public:
  ScopedGLogCapture() {
    handler_id_ = g_log_set_handler(
        /*log_domain=*/nullptr,
        static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL | G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION),
        &ScopedGLogCapture::LogHandler,
        this);
  }

  ~ScopedGLogCapture() {
    if (handler_id_ != 0) {
      g_log_remove_handler(/*log_domain=*/nullptr, handler_id_);
    }
  }

  ScopedGLogCapture(const ScopedGLogCapture&) = delete;
  ScopedGLogCapture& operator=(const ScopedGLogCapture&) = delete;

  int critical_count() const { return critical_count_; }

private:
  static void LogHandler(const gchar* /*log_domain*/,
                         GLogLevelFlags log_level,
                         const gchar* /*message*/,
                         gpointer user_data) {
    auto* self = static_cast<ScopedGLogCapture*>(user_data);
    if ((log_level & G_LOG_LEVEL_CRITICAL) != 0) {
      self->critical_count_++;
    }
  }

  guint handler_id_ = 0;
  int critical_count_ = 0;
};

static std::string GetTestDataDir() {
  const char* env = std::getenv("TESTDATADIR");
  if (env && *env) {
    return std::string(env);
  }
  // Common fallback used by many projects; if not present, tests that need PDFs will skip.
  return std::string("test-data");
}

static std::string JoinPath(const std::string& a, const std::string& b) {
  if (a.empty()) return b;
  if (b.empty()) return a;
  if (a.back() == G_DIR_SEPARATOR) return a + b;
  return a + G_DIR_SEPARATOR_S + b;
}

static std::string FilePathToUri(const std::string& path) {
  gchar* uri = g_filename_to_uri(path.c_str(), /*hostname=*/nullptr, /*error=*/nullptr);
  if (!uri) {
    return std::string();
  }
  std::string out(uri);
  g_free(uri);
  return out;
}

// Attempt to load a PopplerDocument from a set of candidate filenames.
// Returns a non-null document if any candidate exists and loads.
static ScopedGObject TryLoadDocumentFromCandidates(const std::vector<std::string>& filenames) {
  const std::string dir = GetTestDataDir();

  for (const auto& name : filenames) {
    const std::string path = JoinPath(dir, name);
    if (!g_file_test(path.c_str(), G_FILE_TEST_EXISTS)) {
      continue;
    }

    const std::string uri = FilePathToUri(path);
    if (uri.empty()) {
      continue;
    }

    ScopedGError err;
    PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, err.out());
    if (doc) {
      return ScopedGObject(doc);
    }
  }

  return ScopedGObject(nullptr);
}

// Find the first PopplerAnnotMovie in the first few pages of a document.
// Returns a borrowed pointer; caller owns the containing annotation list and must unref objects.
static PopplerAnnotMovie* FindFirstMovieAnnot(PopplerDocument* doc, int max_pages_to_scan) {
  if (!doc) return nullptr;

  const int n_pages = poppler_document_get_n_pages(doc);
  const int limit = std::min(n_pages, max_pages_to_scan);

  for (int i = 0; i < limit; ++i) {
    PopplerPage* page = poppler_document_get_page(doc, i);
    if (!page) continue;

    GList* annots = poppler_page_get_annot_mapping(page);
    // poppler_page_get_annot_mapping returns list of PopplerAnnotMapping*
    for (GList* l = annots; l != nullptr; l = l->next) {
      auto* mapping = static_cast<PopplerAnnotMapping*>(l->data);
      if (!mapping || !mapping->annot) continue;
      if (POPPLER_IS_ANNOT_MOVIE(mapping->annot)) {
        auto* movie = POPPLER_ANNOT_MOVIE(mapping->annot);
        poppler_page_free_annot_mapping(annots);
        g_object_unref(page);
        return movie; // borrowed (still owned by mapping->annot in list, but list is freed; object refcount remains)
      }
    }

    if (annots) {
      poppler_page_free_annot_mapping(annots);
    }
    g_object_unref(page);
  }

  return nullptr;
}

class PopplerAnnotMovieGetTitleTest_2109 : public ::testing::Test {};

TEST_F(PopplerAnnotMovieGetTitleTest_2109, NullInput_ReturnsNull_2109) {
  ScopedGLogCapture logs;

  gchar* title = poppler_annot_movie_get_title(nullptr);
  EXPECT_EQ(title, nullptr);

  // g_return_val_if_fail should emit a CRITICAL.
  EXPECT_GE(logs.critical_count(), 1);
}

TEST_F(PopplerAnnotMovieGetTitleTest_2109, WrongTypeInput_ReturnsNull_2109) {
  ScopedGLogCapture logs;

  ScopedGObject obj(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj.get(), nullptr);

  // Intentionally pass wrong type; must not crash, should return NULL and emit CRITICAL.
  gchar* title = poppler_annot_movie_get_title(reinterpret_cast<PopplerAnnotMovie*>(obj.get()));
  EXPECT_EQ(title, nullptr);
  EXPECT_GE(logs.critical_count(), 1);
}

TEST_F(PopplerAnnotMovieGetTitleTest_2109, ValidMovieAnnot_ReturnsStableUtf8OrNull_2109) {
  // Try a few likely filenames; if none exist in TESTDATADIR, skip gracefully.
  const std::vector<std::string> candidates = {
      "annots.pdf",
      "annotations.pdf",
      "movie.pdf",
      "movie-annotation.pdf",
      "test.pdf",
  };

  ScopedGObject doc_holder = TryLoadDocumentFromCandidates(candidates);
  if (!doc_holder.get()) {
    GTEST_SKIP() << "No suitable PDF found in TESTDATADIR to obtain a PopplerAnnotMovie instance.";
  }

  PopplerDocument* doc = POPPLER_DOCUMENT(doc_holder.get());
  PopplerAnnotMovie* movie = FindFirstMovieAnnot(doc, /*max_pages_to_scan=*/10);
  if (!movie) {
    GTEST_SKIP() << "Loaded a PDF but found no PopplerAnnotMovie annotation in the first pages.";
  }

  ScopedGChar t1(poppler_annot_movie_get_title(movie));
  ScopedGChar t2(poppler_annot_movie_get_title(movie));

  // Observable behavior: repeated calls should be consistent (both null or same string content).
  if (t1.get() == nullptr || t2.get() == nullptr) {
    EXPECT_EQ(t1.get(), t2.get());
    // If title is absent, this is still valid (boundary: no title).
    return;
  }

  EXPECT_STREQ(t1.get(), t2.get());
  EXPECT_GT(std::strlen(t1.get()), 0u);

  // The API returns UTF-8 (via _poppler_goo_string_to_utf8); validate it's well-formed.
  EXPECT_TRUE(g_utf8_validate(t1.get(), -1, nullptr));
}

} // namespace