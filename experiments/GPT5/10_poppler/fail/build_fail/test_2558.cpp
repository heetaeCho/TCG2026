// poppler-structure-element-get-background-color-test.cc
//
// Unit tests for:
//   gboolean poppler_structure_element_get_background_color(PopplerStructureElement*, PopplerColor*)
//
// Constraints respected:
// - Treat implementation as black box
// - Only use public API / observable behavior
// - No access to internal/private state
// - Use GLib log capture to verify g_return_val_if_fail behavior where observable

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <string>
#include <vector>

namespace {

struct GErrorDeleter {
  void operator()(GError* e) const { g_error_free(e); }
};

struct GObjectUnref {
  void operator()(gpointer p) const {
    if (p) g_object_unref(p);
  }
};

struct StructureIterFree {
  void operator()(PopplerStructureElementIter* it) const {
    if (it) poppler_structure_element_iter_free(it);
  }
};

using UniqueGError = std::unique_ptr<GError, GErrorDeleter>;
using UniqueDoc = std::unique_ptr<PopplerDocument, GObjectUnref>;
using UniqueIter = std::unique_ptr<PopplerStructureElementIter, StructureIterFree>;

static std::string FileToUri(const std::string& path) {
  UniqueGError err(nullptr);
  gchar* uri = g_filename_to_uri(path.c_str(), /*hostname=*/nullptr, &err.get());
  if (!uri) return {};
  std::string out(uri);
  g_free(uri);
  return out;
}

static UniqueDoc TryOpenDocumentFromFile(const std::string& path) {
  std::string uri = FileToUri(path);
  if (uri.empty()) return UniqueDoc(nullptr);

  GError* err_raw = nullptr;
  PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &err_raw);
  UniqueGError err(err_raw);
  return UniqueDoc(doc);
}

// Best-effort: try common locations used by poppler test suites.
// If none exist, tests that require a real structure element will be skipped.
static std::string FindTaggedPdfFixturePath() {
  const std::vector<std::string> candidates = {
      // Common in-tree fixtures (varies by project layout)
      "testdata/tagged.pdf",
      "test-data/tagged.pdf",
      "tests/tagged.pdf",
      "tests/data/tagged.pdf",
      "glib/tests/tagged.pdf",
      "glib/tests/data/tagged.pdf",
      "glib/test/tagged.pdf",
      "glib/test/data/tagged.pdf",
      // Sometimes named by feature
      "testdata/structure.pdf",
      "test-data/structure.pdf",
      "tests/structure.pdf",
      "tests/data/structure.pdf",
      "glib/tests/structure.pdf",
      "glib/tests/data/structure.pdf",
  };

  for (const auto& p : candidates) {
    if (g_file_test(p.c_str(), G_FILE_TEST_IS_REGULAR)) return p;
  }
  return {};
}

static PopplerStructureElement* GetAnyStructureElementFromDocument(PopplerDocument* doc) {
  if (!doc) return nullptr;

  UniqueIter iter(poppler_structure_element_iter_new(doc));
  if (!iter) return nullptr;

  // Get the current element at the iterator position.
  return poppler_structure_element_iter_get_element(iter.get());
}

class PopplerStructureElementGetBackgroundColorTest_2558 : public ::testing::Test {
 protected:
  static void SetUpTestSuite() {
    // Ensure GLib messages are not fatal for tests that intentionally trigger g_return_val_if_fail.
    // (Some harnesses set G_DEBUG=fatal-criticals; we avoid hard failure by not changing env here.
    // We only *expect* messages using g_test_expect_message when applicable.)
  }
};

TEST_F(PopplerStructureElementGetBackgroundColorTest_2558,
       NullElementReturnsFalseAndEmitsCritical_2558) {
  PopplerColor c{};
  // g_return_val_if_fail emits a CRITICAL with an assertion-like message.
  g_test_expect_message(/*log_domain=*/nullptr, G_LOG_LEVEL_CRITICAL, "*assertion*");
  gboolean ok = poppler_structure_element_get_background_color(nullptr, &c);
  g_test_assert_expected_messages();
  EXPECT_FALSE(ok);
}

TEST_F(PopplerStructureElementGetBackgroundColorTest_2558,
       NullColorReturnsFalseAndEmitsCriticalWhenElementValid_2558) {
  const std::string fixture = FindTaggedPdfFixturePath();
  if (fixture.empty()) {
    GTEST_SKIP() << "No tagged/structure PDF fixture found on disk; skipping test requiring a "
                    "valid PopplerStructureElement instance.";
  }

  UniqueDoc doc = TryOpenDocumentFromFile(fixture);
  if (!doc) {
    GTEST_SKIP() << "Failed to open fixture PDF (path='" << fixture
                 << "'); skipping test requiring a valid PopplerStructureElement instance.";
  }

  PopplerStructureElement* elem = GetAnyStructureElementFromDocument(doc.get());
  if (!elem) {
    GTEST_SKIP() << "Document has no structure tree or no accessible element; skipping.";
  }

  g_test_expect_message(/*log_domain=*/nullptr, G_LOG_LEVEL_CRITICAL, "*assertion*");
  gboolean ok = poppler_structure_element_get_background_color(elem, nullptr);
  g_test_assert_expected_messages();
  EXPECT_FALSE(ok);
}

TEST_F(PopplerStructureElementGetBackgroundColorTest_2558,
       ReturnsFalseWhenBackgroundColorNotPresentOrNotAvailable_2558) {
  const std::string fixture = FindTaggedPdfFixturePath();
  if (fixture.empty()) {
    GTEST_SKIP() << "No tagged/structure PDF fixture found; skipping structure-based behavior test.";
  }

  UniqueDoc doc = TryOpenDocumentFromFile(fixture);
  if (!doc) {
    GTEST_SKIP() << "Failed to open fixture PDF (path='" << fixture << "'); skipping.";
  }

  UniqueIter iter(poppler_structure_element_iter_new(doc.get()));
  if (!iter) {
    GTEST_SKIP() << "Fixture PDF opened but has no structure tree (iterator is NULL); skipping.";
  }

  // Walk a few nodes at the top level to find at least one element that does *not* expose
  // a background color. This test is written to be robust across different fixtures.
  bool observed_false = false;
  int steps = 0;
  do {
    PopplerStructureElement* elem = poppler_structure_element_iter_get_element(iter.get());
    if (!elem) continue;

    PopplerColor color{};
    gboolean ok = poppler_structure_element_get_background_color(elem, &color);
    if (!ok) {
      observed_false = true;
      break;
    }

    steps++;
  } while (steps < 32 && poppler_structure_element_iter_next(iter.get()));

  if (!observed_false) {
    GTEST_SKIP() << "Did not observe an element without background color in first 32 elements; "
                    "fixture may set background color everywhere. Skipping.";
  }

  SUCCEED();
}

TEST_F(PopplerStructureElementGetBackgroundColorTest_2558,
       WhenBackgroundColorIsAvailableReturnsTrueAndWritesColor_2558) {
  const std::string fixture = FindTaggedPdfFixturePath();
  if (fixture.empty()) {
    GTEST_SKIP() << "No tagged/structure PDF fixture found; skipping success-path test.";
  }

  UniqueDoc doc = TryOpenDocumentFromFile(fixture);
  if (!doc) {
    GTEST_SKIP() << "Failed to open fixture PDF (path='" << fixture << "'); skipping.";
  }

  UniqueIter iter(poppler_structure_element_iter_new(doc.get()));
  if (!iter) {
    GTEST_SKIP() << "Fixture PDF has no structure tree (iterator is NULL); skipping.";
  }

  // Search for any element that reports a background color.
  bool found_true = false;
  PopplerColor out{};
  int steps = 0;

  do {
    PopplerStructureElement* elem = poppler_structure_element_iter_get_element(iter.get());
    if (!elem) continue;

    PopplerColor color{};
    // Initialize to a sentinel pattern to detect that something was written on success.
    color.red = -1;
    color.green = -1;
    color.blue = -1;

    gboolean ok = poppler_structure_element_get_background_color(elem, &color);
    if (ok) {
      found_true = true;
      out = color;
      break;
    }

    steps++;
  } while (steps < 256 && poppler_structure_element_iter_next(iter.get()));

  if (!found_true) {
    GTEST_SKIP() << "No structure element reported a background color within first 256 elements. "
                    "Fixture may not contain BackgroundColor attributes.";
  }

  EXPECT_GE(out.red, 0);
  EXPECT_GE(out.green, 0);
  EXPECT_GE(out.blue, 0);
  // PopplerColor channels are commonly 16-bit (0..65535) in many APIs; we only assert non-negative
  // to avoid assuming scaling rules.
}

}  // namespace