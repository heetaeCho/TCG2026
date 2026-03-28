// File: poppler-layer-show-test_2510.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>
#include <poppler.h>

#include <string>
#include <vector>

// These tests treat poppler_layer_show() as a black box and only validate
// observable behavior via the public Poppler GLib API (e.g. poppler_layer_is_visible()).

namespace {

class GLibLogCapture {
public:
  GLibLogCapture() {
    prev_ = g_log_set_default_handler(&GLibLogCapture::HandlerThunk, this);
  }

  ~GLibLogCapture() { g_log_set_default_handler(prev_, nullptr); }

  int critical_count() const { return critical_count_; }

private:
  static void HandlerThunk(const gchar *log_domain,
                           GLogLevelFlags log_level,
                           const gchar *message,
                           gpointer user_data) {
    static_cast<GLibLogCapture *>(user_data)->Handler(log_domain, log_level, message);
  }

  void Handler(const gchar * /*log_domain*/, GLogLevelFlags log_level, const gchar * /*message*/) {
    if (log_level & G_LOG_LEVEL_CRITICAL) {
      ++critical_count_;
    }
  }

  GLogFunc prev_{nullptr};
  int critical_count_{0};
};

static std::string ToFileUriIfExists(const std::string &path) {
  if (!g_file_test(path.c_str(), G_FILE_TEST_EXISTS)) {
    return {};
  }
  GError *error = nullptr;
  gchar *uri = g_filename_to_uri(path.c_str(), /*hostname=*/nullptr, &error);
  if (!uri) {
    if (error) {
      g_error_free(error);
    }
    return {};
  }
  std::string out(uri);
  g_free(uri);
  return out;
}

// Try to find a PDF with Optional Content Groups (layers) in common test locations.
// If none is found, tests that require a document will be skipped.
static std::string FindPdfWithLayersCandidatePath_2510() {
  // Common candidate filenames for OCG/layer test PDFs.
  const std::vector<std::string> names = {
      "ocg.pdf",
      "OCG.pdf",
      "layers.pdf",
      "layer.pdf",
      "optional-content.pdf",
      "optional_content.pdf",
  };

  // Common base directories in many Poppler test setups.
  const std::vector<std::string> dirs = {
      ".",                 // current working directory
      "test",              // ./test
      "tests",             // ./tests
      "testdata",          // ./testdata
      "test-data",         // ./test-data
      "data",              // ./data
      "testfiles",         // ./testfiles
      "test/files",        // ./test/files
      "glib/tests",        // ./glib/tests
      "glib/test",         // ./glib/test
      "poppler-glib/tests" // ./poppler-glib/tests
  };

  for (const auto &d : dirs) {
    for (const auto &n : names) {
      std::string p = d + G_DIR_SEPARATOR_S + n;
      if (g_file_test(p.c_str(), G_FILE_TEST_EXISTS)) {
        return p;
      }
    }
  }

  return {};
}

struct DocAndLayers {
  PopplerDocument *doc = nullptr; // owned
  GList *layers = nullptr;        // owned (list nodes; elements are owned by doc)
};

static DocAndLayers LoadDocAndLayers_2510() {
  DocAndLayers out;

  const std::string path = FindPdfWithLayersCandidatePath_2510();
  if (path.empty()) {
    return out;
  }

  const std::string uri = ToFileUriIfExists(path);
  if (uri.empty()) {
    return out;
  }

  GError *error = nullptr;
  out.doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &error);
  if (!out.doc) {
    if (error) {
      g_error_free(error);
    }
    return out;
  }

  out.layers = poppler_document_get_layers(out.doc);
  return out;
}

static void FreeDocAndLayers_2510(DocAndLayers *dl) {
  if (!dl) {
    return;
  }
  if (dl->layers) {
    g_list_free(dl->layers);
    dl->layers = nullptr;
  }
  if (dl->doc) {
    g_object_unref(dl->doc);
    dl->doc = nullptr;
  }
}

static std::vector<PopplerLayer *> LayersToVector_2510(GList *layers) {
  std::vector<PopplerLayer *> v;
  for (GList *l = layers; l != nullptr; l = l->next) {
    if (l->data && POPPLER_IS_LAYER(l->data)) {
      v.push_back(POPPLER_LAYER(l->data));
    }
  }
  return v;
}

// Finds a pair of layers (A,B) such that:
// 1) Showing A makes A visible
// 2) Showing B afterwards makes A NOT visible (mutual exclusion observed)
//
// This relies only on observable behavior via poppler_layer_is_visible().
static bool FindMutuallyExclusivePair_2510(const std::vector<PopplerLayer *> &layers,
                                           PopplerLayer **out_a,
                                           PopplerLayer **out_b) {
  if (!out_a || !out_b) {
    return false;
  }
  *out_a = nullptr;
  *out_b = nullptr;

  if (layers.size() < 2) {
    return false;
  }

  for (size_t i = 0; i < layers.size(); ++i) {
    for (size_t j = 0; j < layers.size(); ++j) {
      if (i == j) {
        continue;
      }

      PopplerLayer *a = layers[i];
      PopplerLayer *b = layers[j];

      // Drive the state using public API calls only.
      poppler_layer_show(a);
      bool a_vis_after_a = poppler_layer_is_visible(a);
      if (!a_vis_after_a) {
        continue;
      }

      poppler_layer_show(b);
      bool b_vis_after_b = poppler_layer_is_visible(b);
      bool a_vis_after_b = poppler_layer_is_visible(a);

      if (b_vis_after_b && !a_vis_after_b) {
        *out_a = a;
        *out_b = b;
        return true;
      }
    }
  }

  return false;
}

} // namespace

class PopplerLayerShowTest_2510 : public ::testing::Test {
protected:
  void SetUp() override {
    dl_ = LoadDocAndLayers_2510();
    if (!dl_.doc || !dl_.layers) {
      return;
    }
    layers_vec_ = LayersToVector_2510(dl_.layers);
  }

  void TearDown() override { FreeDocAndLayers_2510(&dl_); }

  DocAndLayers dl_{};
  std::vector<PopplerLayer *> layers_vec_;
};

extern "C" {
// Function under test (defined in poppler-layer.cc)
void poppler_layer_show(PopplerLayer *poppler_layer);
}

TEST_F(PopplerLayerShowTest_2510, NullLayerDoesNotCrashAndEmitsCritical_2510) {
  GLibLogCapture capture;
  poppler_layer_show(nullptr);
  EXPECT_GE(capture.critical_count(), 1)
      << "Expected g_return_if_fail() to emit at least one CRITICAL log for nullptr.";
}

TEST_F(PopplerLayerShowTest_2510, WrongTypeDoesNotCrashAndEmitsCritical_2510) {
  GLibLogCapture capture;

  // Create a plain GObject that is not a PopplerLayer instance.
  GObject *obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  poppler_layer_show(reinterpret_cast<PopplerLayer *>(obj));
  EXPECT_GE(capture.critical_count(), 1)
      << "Expected g_return_if_fail() to emit at least one CRITICAL log for wrong type.";

  g_object_unref(obj);
}

TEST_F(PopplerLayerShowTest_2510, ShowMakesLayerVisibleWhenLayersExist_2510) {
  if (!dl_.doc || layers_vec_.empty()) {
    GTEST_SKIP() << "No layer-capable PDF found (or document has no layers).";
  }

  // Find a layer that is currently not visible, if possible; otherwise use the first one.
  PopplerLayer *target = nullptr;
  for (auto *layer : layers_vec_) {
    if (!poppler_layer_is_visible(layer)) {
      target = layer;
      break;
    }
  }
  if (!target) {
    target = layers_vec_.front();
  }
  ASSERT_NE(target, nullptr);

  poppler_layer_show(target);
  EXPECT_TRUE(poppler_layer_is_visible(target))
      << "After poppler_layer_show(), the target layer should be visible.";
}

TEST_F(PopplerLayerShowTest_2510, ShowOnVisibleLayerKeepsItVisible_2510) {
  if (!dl_.doc || layers_vec_.empty()) {
    GTEST_SKIP() << "No layer-capable PDF found (or document has no layers).";
  }

  PopplerLayer *target = layers_vec_.front();
  ASSERT_NE(target, nullptr);

  // Ensure visible first.
  poppler_layer_show(target);
  ASSERT_TRUE(poppler_layer_is_visible(target));

  // Calling show again should not make it invisible.
  poppler_layer_show(target);
  EXPECT_TRUE(poppler_layer_is_visible(target));
}

TEST_F(PopplerLayerShowTest_2510, RadioButtonGroupMutualExclusionObservable_2510) {
  if (!dl_.doc || layers_vec_.size() < 2) {
    GTEST_SKIP() << "Not enough layers to test mutual exclusion.";
  }

  PopplerLayer *a = nullptr;
  PopplerLayer *b = nullptr;
  if (!FindMutuallyExclusivePair_2510(layers_vec_, &a, &b)) {
    GTEST_SKIP() << "No mutually-exclusive (radio-button-like) layer pair observed in this document.";
  }

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  poppler_layer_show(a);
  ASSERT_TRUE(poppler_layer_is_visible(a));

  poppler_layer_show(b);
  EXPECT_TRUE(poppler_layer_is_visible(b));
  EXPECT_FALSE(poppler_layer_is_visible(a))
      << "Showing B should make A not visible if both are in the same mutual-exclusion group.";

  // And back again:
  poppler_layer_show(a);
  EXPECT_TRUE(poppler_layer_is_visible(a));
  EXPECT_FALSE(poppler_layer_is_visible(b))
      << "Showing A again should make B not visible if mutual exclusion is enforced.";
}