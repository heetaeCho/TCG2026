// File: poppler-fonts-iter-is-embedded-test_2226.cc
#include <gtest/gtest.h>

#include <poppler.h>

#include <glib.h>
#include <glib-object.h>

#include <filesystem>
#include <string>
#include <vector>

namespace {

struct GCharDeleter {
  void operator()(gchar *p) const { g_free(p); }
};
using GCharPtr = std::unique_ptr<gchar, GCharDeleter>;

struct GErrorDeleter {
  void operator()(GError *e) const {
    if (e) g_error_free(e);
  }
};
using GErrorPtr = std::unique_ptr<GError, GErrorDeleter>;

struct GObjectUnrefDeleter {
  void operator()(gpointer p) const {
    if (p) g_object_unref(p);
  }
};
template <typename T>
using GObjPtr = std::unique_ptr<T, GObjectUnrefDeleter>;

static std::vector<std::filesystem::path> CandidateRoots() {
  std::vector<std::filesystem::path> roots;

  auto add_env = [&](const char *name) {
    const char *v = g_getenv(name);
    if (v && *v) roots.emplace_back(v);
  };

  // Common build/test env vars.
  add_env("srcdir");
  add_env("MESON_SOURCE_ROOT");
  add_env("MESON_BUILD_ROOT");
  add_env("TOP_SRCDIR");
  add_env("TOP_BUILDDIR");

  // Fallback: current working directory.
  roots.emplace_back(std::filesystem::current_path());

  // Add a few common subdirs where Poppler test PDFs often live.
  std::vector<std::filesystem::path> expanded;
  for (const auto &r : roots) {
    expanded.push_back(r);
    expanded.push_back(r / "testdata");
    expanded.push_back(r / "tests");
    expanded.push_back(r / "glib" / "tests");
    expanded.push_back(r / "glib" / "test");
    expanded.push_back(r / "poppler" / "test");
    expanded.push_back(r / "test");
  }
  return expanded;
}

static std::filesystem::path FindExistingFileByNames(const std::vector<std::string> &names) {
  for (const auto &root : CandidateRoots()) {
    for (const auto &name : names) {
      std::filesystem::path p = root / name;
      std::error_code ec;
      if (std::filesystem::exists(p, ec) && std::filesystem::is_regular_file(p, ec)) return p;
    }
  }
  return {};
}

// Limited-depth search for a PDF file matching a predicate on filename.
static std::filesystem::path FindPdfByFilenameHint(const std::vector<std::string> &hints,
                                                   int max_dirs_to_scan = 2000) {
  int scanned = 0;
  for (const auto &root : CandidateRoots()) {
    std::error_code ec;
    if (!std::filesystem::exists(root, ec) || !std::filesystem::is_directory(root, ec)) continue;

    for (auto it = std::filesystem::recursive_directory_iterator(
             root, std::filesystem::directory_options::skip_permission_denied, ec);
         it != std::filesystem::recursive_directory_iterator(); it.increment(ec)) {
      if (ec) break;
      if (++scanned > max_dirs_to_scan) break;

      const auto &entry = *it;
      if (!entry.is_regular_file(ec)) continue;

      auto path = entry.path();
      auto ext = path.extension().string();
      for (auto &c : ext) c = static_cast<char>(::tolower(c));
      if (ext != ".pdf") continue;

      std::string fname = path.filename().string();
      std::string lower = fname;
      for (auto &c : lower) c = static_cast<char>(::tolower(c));

      bool ok = true;
      for (const auto &h : hints) {
        std::string lh = h;
        for (auto &c : lh) c = static_cast<char>(::tolower(c));
        if (lower.find(lh) == std::string::npos) {
          ok = false;
          break;
        }
      }
      if (ok) return path;
    }
  }
  return {};
}

static std::string PathToFileUri(const std::filesystem::path &p) {
  GError *err_raw = nullptr;
  GCharPtr uri(g_filename_to_uri(p.string().c_str(), /*hostname=*/nullptr, &err_raw));
  GErrorPtr err(err_raw);
  if (!uri || err) return {};
  return std::string(uri.get());
}

static GObjPtr<PopplerDocument> LoadDocumentOrSkip(const std::filesystem::path &pdf_path) {
  if (pdf_path.empty()) {
    GTEST_SKIP() << "No suitable test PDF found in common testdata locations.";
  }

  std::string uri = PathToFileUri(pdf_path);
  if (uri.empty()) {
    GTEST_SKIP() << "Failed to convert PDF path to file:// URI: " << pdf_path.string();
  }

  GError *err_raw = nullptr;
  PopplerDocument *doc_raw = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &err_raw);
  GErrorPtr err(err_raw);

  if (!doc_raw || err) {
    GTEST_SKIP() << "Failed to open PDF via Poppler: " << pdf_path.string()
                 << (err ? std::string(" (") + err->message + ")" : "");
  }
  return GObjPtr<PopplerDocument>(doc_raw);
}

static GObjPtr<PopplerFontsIter> GetFontsIterOrSkip(PopplerDocument *doc) {
  if (!doc) GTEST_SKIP() << "Document is null.";
  PopplerFontsIter *iter_raw = poppler_document_get_fonts_iter(doc);
  if (!iter_raw) {
    GTEST_SKIP() << "poppler_document_get_fonts_iter() returned null (no fonts iterator available).";
  }
  return GObjPtr<PopplerFontsIter>(iter_raw);
}

}  // namespace

// ---- Tests for poppler_fonts_iter_is_embedded(PopplerFontsIter*) ----

TEST(PopplerFontsIterIsEmbeddedTest_2226, NullIterDies_2226) {
  // Observable error case: passing nullptr is invalid and should crash (or abort).
  // We use a death test to avoid relying on internal state.
  EXPECT_DEATH_IF_SUPPORTED({ (void)poppler_fonts_iter_is_embedded(nullptr); }, "");
}

TEST(PopplerFontsIterIsEmbeddedTest_2226, ReturnsStableValueForSameFont_2226) {
  // Normal operation: For a valid iterator positioned at a font, the result should be a gboolean
  // and should be stable across repeated calls without moving the iterator.
  const auto pdf = FindExistingFileByNames({
      // Common-ish names across Poppler test suites / downstream packs.
      "tests/test.pdf",
      "testdata/test.pdf",
      "test.pdf",
      "fonts.pdf",
      "test-fonts.pdf",
  });

  auto doc = LoadDocumentOrSkip(pdf);
  auto iter = GetFontsIterOrSkip(doc.get());

  // If there are no fonts, skip.
  // Some builds may still return an iter, but next() might be false immediately.
  // We only require that if at least one font exists, is_embedded is stable.
  if (!poppler_fonts_iter_next(iter.get())) {
    GTEST_SKIP() << "Fonts iterator appears empty for PDF: " << pdf.string();
  }

  const gboolean a = poppler_fonts_iter_is_embedded(iter.get());
  const gboolean b = poppler_fonts_iter_is_embedded(iter.get());
  EXPECT_EQ(a, b);
}

TEST(PopplerFontsIterIsEmbeddedTest_2226, FindsAtLeastOneEmbeddedFontWhenAvailable_2226) {
  // Normal operation (content-based): On a PDF likely to contain embedded fonts, ensure we can
  // observe at least one TRUE. If such a PDF isn't present, skip.
  std::filesystem::path pdf = FindExistingFileByNames({
      "font-embedded.pdf",
      "embedded-font.pdf",
      "embedded-fonts.pdf",
      "fonts-embedded.pdf",
      "testdata/embedded-font.pdf",
      "tests/embedded-font.pdf",
  });

  if (pdf.empty()) {
    // Heuristic fallback: scan for a PDF whose filename hints embedded fonts.
    pdf = FindPdfByFilenameHint({"font", "embed"});
  }

  auto doc = LoadDocumentOrSkip(pdf);
  auto iter = GetFontsIterOrSkip(doc.get());

  bool saw_any = false;
  bool saw_true = false;

  while (poppler_fonts_iter_next(iter.get())) {
    saw_any = true;
    if (poppler_fonts_iter_is_embedded(iter.get())) {
      saw_true = true;
      break;
    }
  }

  if (!saw_any) {
    GTEST_SKIP() << "No fonts found to evaluate embedded status in PDF: " << pdf.string();
  }

  EXPECT_TRUE(saw_true) << "Did not observe any embedded fonts in PDF: " << pdf.string();
}

TEST(PopplerFontsIterIsEmbeddedTest_2226, FindsAtLeastOneNonEmbeddedFontWhenAvailable_2226) {
  // Boundary/variation: On a PDF likely to contain non-embedded fonts, ensure we can observe FALSE.
  // If such a PDF isn't present, skip.
  std::filesystem::path pdf = FindExistingFileByNames({
      "font-not-embedded.pdf",
      "unembedded-font.pdf",
      "unembedded-fonts.pdf",
      "fonts-unembedded.pdf",
      "fonts-not-embedded.pdf",
      "testdata/unembedded-font.pdf",
      "tests/unembedded-font.pdf",
  });

  if (pdf.empty()) {
    // Heuristic fallback: scan for a PDF whose filename hints unembedded/nonembedded fonts.
    pdf = FindPdfByFilenameHint({"font", "unembed"});
    if (pdf.empty()) pdf = FindPdfByFilenameHint({"font", "nonembed"});
    if (pdf.empty()) pdf = FindPdfByFilenameHint({"font", "not-embed"});
  }

  auto doc = LoadDocumentOrSkip(pdf);
  auto iter = GetFontsIterOrSkip(doc.get());

  bool saw_any = false;
  bool saw_false = false;

  while (poppler_fonts_iter_next(iter.get())) {
    saw_any = true;
    if (!poppler_fonts_iter_is_embedded(iter.get())) {
      saw_false = true;
      break;
    }
  }

  if (!saw_any) {
    GTEST_SKIP() << "No fonts found to evaluate embedded status in PDF: " << pdf.string();
  }

  EXPECT_TRUE(saw_false) << "Did not observe any non-embedded fonts in PDF: " << pdf.string();
}

TEST(PopplerFontsIterIsEmbeddedTest_2226, CanCallIsEmbeddedForEachStepUntilEnd_2226) {
  // Boundary condition: iterate through all fonts (if any) and ensure is_embedded is callable
  // at each valid position, and that iteration terminates.
  const auto pdf = FindExistingFileByNames({
      "tests/test.pdf",
      "testdata/test.pdf",
      "test.pdf",
      "fonts.pdf",
      "test-fonts.pdf",
  });

  auto doc = LoadDocumentOrSkip(pdf);
  auto iter = GetFontsIterOrSkip(doc.get());

  int steps = 0;
  while (poppler_fonts_iter_next(iter.get())) {
    (void)poppler_fonts_iter_is_embedded(iter.get());
    ++steps;
    // Avoid pathological infinite loops if underlying implementation is broken.
    if (steps > 10000) {
      FAIL() << "Iterator did not terminate after 10000 steps for PDF: " << pdf.string();
    }
  }

  // If there are zero fonts, that's acceptable; test still validates termination.
  SUCCEED();
}