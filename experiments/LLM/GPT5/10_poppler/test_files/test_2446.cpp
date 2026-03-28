// poppler-page-find-text-with-options-test_2446.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstddef>
#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

extern "C" {
// Function under test (implemented in poppler-page.cc)
GList *poppler_page_find_text_with_options(PopplerPage *page,
                                          const char *text,
                                          PopplerFindFlags options);
}

// -------------------------
// Helpers
// -------------------------

namespace {

static void SwallowGlibCriticalLogs(const gchar * /*log_domain*/,
                                   GLogLevelFlags /*log_level*/,
                                   const gchar * /*message*/,
                                   gpointer /*user_data*/) {
  // Intentionally empty: we just want to keep g_return_val_if_fail() CRITICAL
  // from failing the test output with noisy logs.
}

class GlibCriticalLogSilencer {
 public:
  GlibCriticalLogSilencer() {
    handler_id_ = g_log_set_handler(nullptr,
                                   static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL),
                                   &SwallowGlibCriticalLogs,
                                   nullptr);
  }
  ~GlibCriticalLogSilencer() {
    if (handler_id_ != 0) {
      g_log_remove_handler(nullptr, handler_id_);
    }
  }

 private:
  guint handler_id_{0};
};

static std::string BuildSimpleSinglePagePdf_2446() {
  // Minimal PDF with predictable text strings:
  // Line1: "foo"
  // Line2: "foobar foo"
  // Line3: "Foo"
  //
  // We do not assert exact coordinates; we only assert basic invariants
  // (non-empty matches, within page bounds, monotonic reductions by flags).

  const std::string stream =
      "BT\n"
      "/F1 24 Tf\n"
      "50 700 Td\n"
      "(foo) Tj\n"
      "0 -30 Td\n"
      "(foobar foo) Tj\n"
      "0 -30 Td\n"
      "(Foo) Tj\n"
      "ET\n";

  auto append_obj = [](std::ostringstream &out,
                       std::vector<std::size_t> &offsets,
                       int obj_num,
                       const std::string &body) {
    offsets.push_back(static_cast<std::size_t>(out.tellp()));
    out << obj_num << " 0 obj\n" << body << "\nendobj\n";
  };

  std::ostringstream out;
  out << "%PDF-1.4\n";

  std::vector<std::size_t> offsets;
  offsets.reserve(6);
  offsets.push_back(0);  // xref entry 0 is the free object

  append_obj(out, offsets, 1, "<< /Type /Catalog /Pages 2 0 R >>");
  append_obj(out, offsets, 2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>");
  append_obj(out, offsets, 3,
             "<< /Type /Page /Parent 2 0 R\n"
             "   /MediaBox [0 0 612 792]\n"
             "   /Resources << /Font << /F1 4 0 R >> >>\n"
             "   /Contents 5 0 R\n"
             ">>");
  append_obj(out, offsets, 4,
             "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>");

  {
    std::ostringstream body;
    body << "<< /Length " << stream.size() << " >>\n"
         << "stream\n"
         << stream
         << "endstream";
    append_obj(out, offsets, 5, body.str());
  }

  const std::size_t xref_pos = static_cast<std::size_t>(out.tellp());
  out << "xref\n";
  out << "0 6\n";
  out << "0000000000 65535 f \n";
  for (int i = 1; i <= 5; ++i) {
    // 10-digit zero-padded offsets, generation 00000, in-use 'n'
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010zu 00000 n \n", offsets[i]);
    out << buf;
  }

  out << "trailer\n";
  out << "<< /Size 6 /Root 1 0 R >>\n";
  out << "startxref\n";
  out << xref_pos << "\n";
  out << "%%EOF\n";

  return out.str();
}

static int ListLength_2446(GList *list) {
  return static_cast<int>(g_list_length(list));
}

static void FreeMatches_2446(GList *list) {
  for (GList *l = list; l != nullptr; l = l->next) {
    // poppler_rectangle_extended_new() allocates; in typical Poppler GLib code
    // this is freed with g_free().
    g_free(l->data);
  }
  g_list_free(list);
}

}  // namespace

// -------------------------
// Test Fixture
// -------------------------

class PopplerPageFindTextWithOptionsTest_2446 : public ::testing::Test {
 protected:
  void SetUp() override {
    silencer_ = std::make_unique<GlibCriticalLogSilencer>();

    pdf_bytes_ = BuildSimpleSinglePagePdf_2446();

    GError *error = nullptr;
    document_ = poppler_document_new_from_data(pdf_bytes_.data(),
                                              static_cast<int>(pdf_bytes_.size()),
                                              /*password=*/nullptr,
                                              &error);
    ASSERT_NE(document_, nullptr) << (error ? error->message : "unknown error");
    if (error) g_error_free(error);

    page_ = poppler_document_get_page(document_, 0);
    ASSERT_NE(page_, nullptr);
  }

  void TearDown() override {
    if (page_) g_object_unref(page_);
    if (document_) g_object_unref(document_);
    silencer_.reset();
  }

  std::unique_ptr<GlibCriticalLogSilencer> silencer_;
  std::string pdf_bytes_;
  PopplerDocument *document_{nullptr};
  PopplerPage *page_{nullptr};
};

// -------------------------
// Tests
// -------------------------

TEST_F(PopplerPageFindTextWithOptionsTest_2446, NullPageReturnsNull_2446) {
  GList *matches =
      poppler_page_find_text_with_options(nullptr, "foo", POPPLER_FIND_DEFAULT);
  EXPECT_EQ(matches, nullptr);
}

TEST_F(PopplerPageFindTextWithOptionsTest_2446, NullTextReturnsNull_2446) {
  GList *matches =
      poppler_page_find_text_with_options(page_, nullptr, POPPLER_FIND_DEFAULT);
  EXPECT_EQ(matches, nullptr);
}

TEST_F(PopplerPageFindTextWithOptionsTest_2446, FindDefaultFindsSomeMatches_2446) {
  GList *matches =
      poppler_page_find_text_with_options(page_, "foo", POPPLER_FIND_DEFAULT);
  ASSERT_NE(matches, nullptr);

  const int n = ListLength_2446(matches);
  EXPECT_GE(n, 1);

  FreeMatches_2446(matches);
}

TEST_F(PopplerPageFindTextWithOptionsTest_2446,
       WholeWordsOnlyDoesNotIncreaseMatchCount_2446) {
  GList *default_matches =
      poppler_page_find_text_with_options(page_, "foo", POPPLER_FIND_DEFAULT);
  ASSERT_NE(default_matches, nullptr);
  const int default_n = ListLength_2446(default_matches);

  GList *whole_matches = poppler_page_find_text_with_options(
      page_, "foo", static_cast<PopplerFindFlags>(POPPLER_FIND_WHOLE_WORDS_ONLY));
  // It is possible for whole-word searches to return NULL if nothing matches;
  // our PDF includes standalone "foo", so we expect at least one.
  ASSERT_NE(whole_matches, nullptr);
  const int whole_n = ListLength_2446(whole_matches);

  EXPECT_GE(default_n, whole_n);
  EXPECT_GE(whole_n, 1);

  FreeMatches_2446(default_matches);
  FreeMatches_2446(whole_matches);
}

TEST_F(PopplerPageFindTextWithOptionsTest_2446,
       CaseSensitiveReducesMatchesForFooVsfoo_2446) {
  // PDF contains "Foo" exactly once as its own token on line3.
  GList *insensitive = poppler_page_find_text_with_options(
      page_, "Foo", POPPLER_FIND_DEFAULT);
  ASSERT_NE(insensitive, nullptr);
  const int n_insensitive = ListLength_2446(insensitive);
  EXPECT_GE(n_insensitive, 1);

  GList *sensitive = poppler_page_find_text_with_options(
      page_, "Foo", static_cast<PopplerFindFlags>(POPPLER_FIND_CASE_SENSITIVE));
  ASSERT_NE(sensitive, nullptr);
  const int n_sensitive = ListLength_2446(sensitive);

  // Case-sensitive should not produce *more* matches than case-insensitive.
  EXPECT_LE(n_sensitive, n_insensitive);
  EXPECT_GE(n_sensitive, 1);

  FreeMatches_2446(insensitive);
  FreeMatches_2446(sensitive);
}

TEST_F(PopplerPageFindTextWithOptionsTest_2446,
       BackwardsFindsSameCountAsDefaultForSameNeedle_2446) {
  GList *forward =
      poppler_page_find_text_with_options(page_, "foo", POPPLER_FIND_DEFAULT);
  ASSERT_NE(forward, nullptr);
  const int n_forward = ListLength_2446(forward);

  GList *backward = poppler_page_find_text_with_options(
      page_, "foo", static_cast<PopplerFindFlags>(POPPLER_FIND_BACKWARDS));
  ASSERT_NE(backward, nullptr);
  const int n_backward = ListLength_2446(backward);

  // Observable expectation: backwards search should find the same *set* of
  // matches; ordering is implementation-dependent, so we only compare count.
  EXPECT_EQ(n_backward, n_forward);

  FreeMatches_2446(forward);
  FreeMatches_2446(backward);
}

TEST_F(PopplerPageFindTextWithOptionsTest_2446, ReturnedRectanglesAreWithinPageBounds_2446) {
  GList *matches =
      poppler_page_find_text_with_options(page_, "foo", POPPLER_FIND_DEFAULT);
  ASSERT_NE(matches, nullptr);

  double width = 0.0, height = 0.0;
  poppler_page_get_size(page_, &width, &height);
  ASSERT_GT(width, 0.0);
  ASSERT_GT(height, 0.0);

  for (GList *l = matches; l != nullptr; l = l->next) {
    ASSERT_NE(l->data, nullptr);

    // PopplerRectangleExtended is expected to be layout-compatible with
    // PopplerRectangle members plus extra fields; we only rely on the
    // documented public coordinate fields existing in the allocation.
    auto *rect = static_cast<PopplerRectangle *>(l->data);

    EXPECT_LE(rect->x1, rect->x2);
    EXPECT_LE(rect->y1, rect->y2);

    // Coordinates should be within the page box (allow tiny epsilon for float).
    const double eps = 1e-6;
    EXPECT_GE(rect->x1, -eps);
    EXPECT_GE(rect->y1, -eps);
    EXPECT_LE(rect->x2, width + eps);
    EXPECT_LE(rect->y2, height + eps);
  }

  FreeMatches_2446(matches);
}