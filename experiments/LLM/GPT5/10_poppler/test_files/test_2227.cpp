// File: poppler-fonts-iter-is-subset-test_2227.cc
//
// Unit tests for:
//   gboolean poppler_fonts_iter_is_subset(PopplerFontsIter *iter);
//
// Constraints note:
// - We treat Poppler as a black box and only use public/GLib API to obtain a
//   PopplerFontsIter from a real PopplerDocument.
// - We do NOT access internal struct fields (items/index/etc).

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdlib>
#include <string>
#include <vector>

namespace {

// Tries to find an existing file path among candidates using a few base dirs.
static std::string FindExistingTestPdfPath(const std::vector<std::string>& rel_candidates) {
  std::vector<std::string> bases;

  // 1) Env var override (common in CI setups).
  if (const char* env = std::getenv("POPPLER_TEST_DATA")) {
    if (env && *env) bases.emplace_back(env);
  }
  if (const char* env = std::getenv("TEST_DATA_DIR")) {
    if (env && *env) bases.emplace_back(env);
  }

  // 2) Build-time macro (sometimes provided by the project).
#ifdef TESTDATADIR
  bases.emplace_back(TESTDATADIR);
#endif

  // 3) Fallbacks: current directory and typical relative locations.
  bases.emplace_back(".");
  bases.emplace_back("testdata");
  bases.emplace_back("tests");
  bases.emplace_back("tests/data");
  bases.emplace_back("glib/tests");
  bases.emplace_back("glib/tests/data");

  for (const auto& base : bases) {
    for (const auto& rel : rel_candidates) {
      std::string path = base;
      if (!path.empty() && path.back() != '/' && rel.front() != '/') path += "/";
      path += rel;
      if (g_file_test(path.c_str(), G_FILE_TEST_IS_REGULAR)) return path;
    }
  }
  return {};
}

static PopplerDocument* OpenDocumentFromPath(const std::string& path) {
  GError* error = nullptr;

  // Convert local filesystem path -> file:// URI
  gchar* uri = g_filename_to_uri(path.c_str(), /*hostname=*/nullptr, &error);
  if (!uri) {
    if (error) g_error_free(error);
    return nullptr;
  }

  PopplerDocument* doc = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
  g_free(uri);

  if (!doc) {
    if (error) g_error_free(error);
    return nullptr;
  }
  if (error) g_error_free(error);
  return doc;
}

static PopplerDocument* OpenAnyFontsDocumentOrSkip() {
  // We don’t assume a specific repository layout; try a handful of plausible PDFs.
  const std::vector<std::string> candidates = {
      // common-ish names/locations in Poppler-related trees
      "fonts.pdf",
      "subset-fonts.pdf",
      "font-subset.pdf",
      "fonts/subset-fonts.pdf",
      "fonts/fonts.pdf",
      "data/fonts.pdf",
      "data/subset-fonts.pdf",
      "tests/fonts.pdf",
      "tests/data/fonts.pdf",
      "tests/data/subset-fonts.pdf",
  };

  const std::string path = FindExistingTestPdfPath(candidates);
  if (path.empty()) {
    GTEST_SKIP() << "No suitable test PDF found. "
                    "Set POPPLER_TEST_DATA or TEST_DATA_DIR to point to PDFs.";
  }

  PopplerDocument* doc = OpenDocumentFromPath(path);
  if (!doc) {
    GTEST_SKIP() << "Found a candidate PDF but Poppler failed to open it: " << path;
  }
  return doc;
}

class PopplerFontsIterIsSubsetTest_2227 : public ::testing::Test {
protected:
  void SetUp() override {
    doc_ = OpenAnyFontsDocumentOrSkip();
    ASSERT_NE(doc_, nullptr);

    iter_ = poppler_document_get_fonts_iter(doc_);
    if (!iter_) {
      g_object_unref(doc_);
      doc_ = nullptr;
      GTEST_SKIP() << "poppler_document_get_fonts_iter() returned NULL for the test PDF.";
    }
  }

  void TearDown() override {
    if (iter_) {
      poppler_fonts_iter_free(iter_);
      iter_ = nullptr;
    }
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
  }

  PopplerDocument* doc_ = nullptr;
  PopplerFontsIter* iter_ = nullptr;
};

}  // namespace

TEST_F(PopplerFontsIterIsSubsetTest_2227, ReturnsStableValueForCurrentFont_2227) {
  // Behavior under test:
  // - Calling poppler_fonts_iter_is_subset() should produce a gboolean.
  // - Repeated calls for the same iterator position should be stable/consistent.
  const gboolean first = poppler_fonts_iter_is_subset(iter_);
  const gboolean second = poppler_fonts_iter_is_subset(iter_);
  const gboolean third = poppler_fonts_iter_is_subset(iter_);

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);

  // Also ensure it is a valid gboolean value (GLib uses int; TRUE/FALSE are 1/0).
  EXPECT_TRUE(first == TRUE || first == FALSE);
}

TEST_F(PopplerFontsIterIsSubsetTest_2227, WorksAcrossMultipleFontsWhileIterating_2227) {
  // Boundary/normal operation:
  // - Iterate a limited number of fonts and ensure the call is safe and returns a gboolean each time.
  // - We do NOT assume any particular PDF has subset fonts; we only assert the API behaves.
  constexpr int kMaxToCheck = 32;

  int checked = 0;
  do {
    const gboolean v = poppler_fonts_iter_is_subset(iter_);
    EXPECT_TRUE(v == TRUE || v == FALSE);

    checked++;
    if (checked >= kMaxToCheck) break;
  } while (poppler_fonts_iter_next(iter_));

  EXPECT_GE(checked, 1) << "Expected at least one font entry to be iterable.";
}

TEST_F(PopplerFontsIterIsSubsetTest_2227, ObservesBothValuesIfDocumentContainsMixedFonts_2227) {
  // If the chosen PDF happens to contain both subset and non-subset fonts,
  // verify we can observe both TRUE and FALSE while iterating.
  // If not, we skip rather than making assumptions about the test PDF’s contents.
  bool saw_true = false;
  bool saw_false = false;

  constexpr int kMaxToScan = 128;
  int scanned = 0;

  do {
    const gboolean v = poppler_fonts_iter_is_subset(iter_);
    if (v == TRUE) saw_true = true;
    if (v == FALSE) saw_false = true;

    scanned++;
    if (scanned >= kMaxToScan) break;
  } while (poppler_fonts_iter_next(iter_));

  if (!(saw_true && saw_false)) {
    GTEST_SKIP() << "Test PDF did not expose both subset and non-subset fonts "
                    "(saw_true=" << saw_true << ", saw_false=" << saw_false << ").";
  }

  EXPECT_TRUE(saw_true);
  EXPECT_TRUE(saw_false);
}