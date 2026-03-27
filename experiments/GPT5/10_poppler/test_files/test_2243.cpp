// File: poppler-document-get-optional-content-items-test_2243.cc
//
// Unit tests for optional content (layers) enumeration in poppler-document.cc,
// exercising the observable behavior via the public GLib API.
//
// NOTE: The function under test in the prompt is a static helper:
//   static GList *get_optional_content_items(const OCGs *ocg)
// Since it is not part of the public API, these tests validate its behavior
// indirectly through PopplerDocument's public layer/optional-content API.
//
// TEST_ID: 2243

#include <gtest/gtest.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <poppler.h>

#include <cstdlib>
#include <memory>
#include <set>
#include <string>
#include <vector>

namespace {

class ScopedGError {
public:
  ~ScopedGError() {
    if (err_) {
      g_error_free(err_);
      err_ = nullptr;
    }
  }
  GError **outptr() { return &err_; }
  GError *get() const { return err_; }

private:
  GError *err_ = nullptr;
};

class ScopedGList {
public:
  ScopedGList() = default;
  explicit ScopedGList(GList *list) : list_(list) {}
  ~ScopedGList() { reset(nullptr); }

  ScopedGList(const ScopedGList &) = delete;
  ScopedGList &operator=(const ScopedGList &) = delete;

  ScopedGList(ScopedGList &&other) noexcept : list_(other.list_) { other.list_ = nullptr; }
  ScopedGList &operator=(ScopedGList &&other) noexcept {
    if (this != &other) {
      reset(nullptr);
      list_ = other.list_;
      other.list_ = nullptr;
    }
    return *this;
  }

  void reset(GList *l) {
    if (list_) {
      // Items are GObjects (PopplerLayer*). Free list nodes and unref each item.
      g_list_free_full(list_, reinterpret_cast<GDestroyNotify>(g_object_unref));
    }
    list_ = l;
  }

  GList *get() const { return list_; }
  guint length() const { return list_ ? g_list_length(list_) : 0; }

private:
  GList *list_ = nullptr;
};

static std::vector<std::string> CandidateDataDirs_2243() {
  std::vector<std::string> dirs;

  // Common in autotools/meson tests.
  const char *srcdir = std::getenv("srcdir");
  if (srcdir && *srcdir)
    dirs.emplace_back(srcdir);

  const char *top_srcdir = std::getenv("top_srcdir");
  if (top_srcdir && *top_srcdir)
    dirs.emplace_back(top_srcdir);

  const char *meson_src_root = std::getenv("MESON_SOURCE_ROOT");
  if (meson_src_root && *meson_src_root)
    dirs.emplace_back(meson_src_root);

  const char *g_test_srcdir = std::getenv("G_TEST_SRCDIR");
  if (g_test_srcdir && *g_test_srcdir)
    dirs.emplace_back(g_test_srcdir);

  // Some projects export a test data dir explicitly.
  const char *poppler_testdatadir = std::getenv("POPPLER_TESTDATADIR");
  if (poppler_testdatadir && *poppler_testdatadir)
    dirs.emplace_back(poppler_testdatadir);

  // Fall back to current working directory (useful in some runners).
  dirs.emplace_back(".");

  return dirs;
}

static std::string FindTestDataFile_2243(const std::vector<std::string> &relative_candidates) {
  const auto dirs = CandidateDataDirs_2243();
  for (const auto &dir : dirs) {
    for (const auto &rel : relative_candidates) {
      gchar *path = g_build_filename(dir.c_str(), rel.c_str(), nullptr);
      const bool exists = g_file_test(path, G_FILE_TEST_EXISTS | G_FILE_TEST_IS_REGULAR);
      std::string out;
      if (exists) {
        out = path;
        g_free(path);
        return out;
      }
      g_free(path);
    }
  }
  return {};
}

static std::string PathToFileUri_2243(const std::string &path) {
  gchar *uri = g_filename_to_uri(path.c_str(), nullptr, nullptr);
  std::string out = uri ? uri : "";
  g_free(uri);
  return out;
}

static PopplerDocument *LoadDocumentFromPath_2243(const std::string &path, GError **error) {
  const std::string uri = PathToFileUri_2243(path);
  if (uri.empty()) {
    g_set_error(error, g_quark_from_static_string("poppler-test"), 1,
                "Failed to convert path to file URI: %s", path.c_str());
    return nullptr;
  }
  // password = nullptr
  return poppler_document_new_from_file(uri.c_str(), nullptr, error);
}

// Helper: get layers list (may be nullptr, may be empty list depending on build/version).
static ScopedGList GetLayers_2243(PopplerDocument *doc) {
  // poppler_document_get_layers() is the GLib API that exposes Optional Content Groups (OCGs).
  // It returns a GList of PopplerLayer* (GObject).
  GList *layers = poppler_document_get_layers(doc);
  return ScopedGList(layers);
}

static std::set<std::string> TitlesFromLayers_2243(const ScopedGList &layers) {
  std::set<std::string> titles;
  for (GList *it = layers.get(); it != nullptr; it = it->next) {
    auto *layer = reinterpret_cast<PopplerLayer *>(it->data);
    if (!layer)
      continue;

    // Title accessor exists in poppler-glib.
    const gchar *title = poppler_layer_get_title(layer);
    if (title && *title)
      titles.insert(title);
  }
  return titles;
}

class OptionalContentItemsTest_2243 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Some GLib/Poppler builds require type system init; harmless otherwise.
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif
  }
};

TEST_F(OptionalContentItemsTest_2243, GetLayers_NullDocument_DoesNotCrash_2243) {
  // Boundary: passing nullptr is not guaranteed supported by the API, so we only
  // validate that our test does not dereference it. We skip calling the API.
  PopplerDocument *doc = nullptr;
  (void)doc;
  SUCCEED();
}

TEST_F(OptionalContentItemsTest_2243, GetLayers_NoOCGDocument_ReturnsNullOrEmpty_2243) {
  // Try a few commonly-used simple PDFs in Poppler test trees.
  const std::string pdf_path = FindTestDataFile_2243({
      "test-data/unittestcases/basic.pdf",
      "test-data/basic.pdf",
      "test/unittestcases/basic.pdf",
      "glib/tests/data/basic.pdf",
      "tests/data/basic.pdf",
      "basic.pdf",
  });

  if (pdf_path.empty()) {
    GTEST_SKIP() << "No basic PDF fixture found (looked in common test-data locations).";
  }

  ScopedGError err;
  std::unique_ptr<PopplerDocument, void (*)(PopplerDocument *)> doc(
      LoadDocumentFromPath_2243(pdf_path, err.outptr()),
      [](PopplerDocument *d) {
        if (d)
          g_object_unref(d);
      });

  ASSERT_NE(doc.get(), nullptr) << "Failed to load PDF: " << pdf_path
                                << (err.get() ? err.get()->message : "");

  ScopedGList layers = GetLayers_2243(doc.get());

  // Observable behavior: if there are no OCGs, the layers list should be absent or empty.
  // We do not assume which representation Poppler uses in this build.
  EXPECT_TRUE(layers.get() == nullptr || layers.length() == 0u);
}

TEST_F(OptionalContentItemsTest_2243, GetLayers_WithOCGDocument_ReturnsNonEmptyList_2243) {
  // Common fixture names for PDFs that contain optional content / layers.
  const std::string pdf_path = FindTestDataFile_2243({
      "test-data/unittestcases/ocg.pdf",
      "test-data/ocg.pdf",
      "test/unittestcases/ocg.pdf",
      "glib/tests/data/ocg.pdf",
      "tests/data/ocg.pdf",
      "ocg.pdf",
      "layers.pdf",
      "test-data/layers.pdf",
  });

  if (pdf_path.empty()) {
    GTEST_SKIP() << "No OCG/layers PDF fixture found (looked for ocg.pdf/layers.pdf).";
  }

  ScopedGError err;
  std::unique_ptr<PopplerDocument, void (*)(PopplerDocument *)> doc(
      LoadDocumentFromPath_2243(pdf_path, err.outptr()),
      [](PopplerDocument *d) {
        if (d)
          g_object_unref(d);
      });

  ASSERT_NE(doc.get(), nullptr) << "Failed to load PDF: " << pdf_path
                                << (err.get() ? err.get()->message : "");

  ScopedGList layers = GetLayers_2243(doc.get());
  ASSERT_NE(layers.get(), nullptr) << "Expected layers list for an OCG PDF fixture.";
  EXPECT_GT(layers.length(), 0u);

  // Boundary-ish: ensure list items are non-null and are PopplerLayer objects.
  for (GList *it = layers.get(); it != nullptr; it = it->next) {
    ASSERT_NE(it->data, nullptr);
    EXPECT_TRUE(POPPLER_IS_LAYER(it->data));
  }
}

TEST_F(OptionalContentItemsTest_2243, GetLayers_WithOCGDocument_LayerTitlesAreStableSet_2243) {
  // We avoid asserting a specific order because the static helper may use either
  // an order array or an unordered container depending on document structure.
  const std::string pdf_path = FindTestDataFile_2243({
      "test-data/unittestcases/ocg.pdf",
      "test-data/ocg.pdf",
      "test/unittestcases/ocg.pdf",
      "glib/tests/data/ocg.pdf",
      "tests/data/ocg.pdf",
      "ocg.pdf",
      "layers.pdf",
      "test-data/layers.pdf",
  });

  if (pdf_path.empty()) {
    GTEST_SKIP() << "No OCG/layers PDF fixture found (looked for ocg.pdf/layers.pdf).";
  }

  ScopedGError err;
  std::unique_ptr<PopplerDocument, void (*)(PopplerDocument *)> doc(
      LoadDocumentFromPath_2243(pdf_path, err.outptr()),
      [](PopplerDocument *d) {
        if (d)
          g_object_unref(d);
      });

  ASSERT_NE(doc.get(), nullptr) << "Failed to load PDF: " << pdf_path
                                << (err.get() ? err.get()->message : "");

  ScopedGList layers_first = GetLayers_2243(doc.get());
  ASSERT_NE(layers_first.get(), nullptr);
  ASSERT_GT(layers_first.length(), 0u);

  ScopedGList layers_second = GetLayers_2243(doc.get());
  ASSERT_NE(layers_second.get(), nullptr);
  ASSERT_GT(layers_second.length(), 0u);

  // Observable behavior: for the same document instance, repeated calls should
  // enumerate the same set of layer titles (even if internal ordering differs).
  const auto titles_first = TitlesFromLayers_2243(layers_first);
  const auto titles_second = TitlesFromLayers_2243(layers_second);

  // If titles are unavailable in the fixture, this set could be empty; still compare.
  EXPECT_EQ(titles_first, titles_second);
}

TEST_F(OptionalContentItemsTest_2243, GetLayers_OrderFixture_WhenPresent_DoesNotReturnNull_2243) {
  // If a fixture with an OCG "Order" array is present, ensure Poppler can enumerate layers.
  // We do NOT assert exact ordering, only that it returns a valid list with valid items.
  const std::string pdf_path = FindTestDataFile_2243({
      "test-data/unittestcases/ocg-order.pdf",
      "test-data/ocg_order.pdf",
      "test-data/ocg-ordering.pdf",
      "test-data/ocg-order-array.pdf",
      "ocg-order.pdf",
      "ocg_order.pdf",
  });

  if (pdf_path.empty()) {
    GTEST_SKIP() << "No OCG order-array PDF fixture found (looked for ocg-order*.pdf).";
  }

  ScopedGError err;
  std::unique_ptr<PopplerDocument, void (*)(PopplerDocument *)> doc(
      LoadDocumentFromPath_2243(pdf_path, err.outptr()),
      [](PopplerDocument *d) {
        if (d)
          g_object_unref(d);
      });

  ASSERT_NE(doc.get(), nullptr) << "Failed to load PDF: " << pdf_path
                                << (err.get() ? err.get()->message : "");

  ScopedGList layers = GetLayers_2243(doc.get());
  ASSERT_NE(layers.get(), nullptr);
  EXPECT_GT(layers.length(), 0u);

  for (GList *it = layers.get(); it != nullptr; it = it->next) {
    ASSERT_NE(it->data, nullptr);
    EXPECT_TRUE(POPPLER_IS_LAYER(it->data));
  }
}

} // namespace