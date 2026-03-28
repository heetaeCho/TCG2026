// poppler-fonts-iter-copy-test_2229.cc
//
// Unit tests for poppler_fonts_iter_copy() (Poppler GLib)
//
// Constraints honored:
// - Treat implementation as a black box
// - Use only public/observable behavior via Poppler GLib API
// - No access to private/internal state

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cerrno>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

namespace {

class ScopedGLogHandler {
public:
  ScopedGLogHandler(const gchar *domain, GLogLevelFlags levels)
      : domain_(domain ? domain : ""), levels_(levels) {
    handler_id_ = g_log_set_handler(domain, levels, &ScopedGLogHandler::Handler, this);
  }

  ~ScopedGLogHandler() {
    if (handler_id_ != 0) {
      g_log_remove_handler(domain_.empty() ? nullptr : domain_.c_str(), handler_id_);
    }
  }

  int count() const { return count_; }

private:
  static void Handler(const gchar * /*log_domain*/,
                      GLogLevelFlags /*log_level*/,
                      const gchar * /*message*/,
                      gpointer user_data) {
    auto *self = static_cast<ScopedGLogHandler *>(user_data);
    self->count_++;
  }

  std::string domain_;
  GLogLevelFlags levels_;
  guint handler_id_{0};
  int count_{0};
};

class TempFile {
public:
  TempFile() {
    gchar *name = nullptr;
    GError *error = nullptr;

    // Creates a secure temp file and returns an fd.
    fd_ = g_file_open_tmp("poppler_fonts_iter_copy_XXXXXX.pdf", &name, &error);
    if (fd_ < 0) {
      std::string msg = "g_file_open_tmp failed: ";
      msg += (error && error->message) ? error->message : "unknown error";
      if (error) g_error_free(error);
      throw std::runtime_error(msg);
    }
    path_ = name ? name : "";
    g_free(name);
  }

  ~TempFile() {
    if (fd_ >= 0) {
      close(fd_);
    }
    if (!path_.empty()) {
      g_remove(path_.c_str());
    }
  }

  TempFile(const TempFile &) = delete;
  TempFile &operator=(const TempFile &) = delete;

  const std::string &path() const { return path_; }

  void WriteAll(const std::string &data) {
    const char *p = data.data();
    size_t left = data.size();
    while (left > 0) {
      ssize_t n = ::write(fd_, p, left);
      if (n < 0) {
        if (errno == EINTR) continue;
        throw std::runtime_error(std::string("write failed: ") + std::strerror(errno));
      }
      p += static_cast<size_t>(n);
      left -= static_cast<size_t>(n);
    }
    ::fsync(fd_);
    ::lseek(fd_, 0, SEEK_SET);
  }

private:
  int fd_{-1};
  std::string path_;
};

// Builds a minimal, valid PDF with one page that references a Base14 font (/Helvetica).
// This is test input data generation (not reimplementation of Poppler internals).
static std::string BuildMinimalPdfOnePageHelvetica() {
  struct Obj {
    int num;
    std::string body;
  };

  std::vector<Obj> objs;

  // 1: Catalog
  objs.push_back({1, "<< /Type /Catalog /Pages 2 0 R >>"});

  // 2: Pages
  objs.push_back({2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>"});

  // 3: Page with font resource and content stream
  objs.push_back(
      {3,
       "<< /Type /Page /Parent 2 0 R "
       "/MediaBox [0 0 300 144] "
       "/Resources << /Font << /F1 5 0 R >> >> "
       "/Contents 4 0 R >>"});

  // 4: Content stream: draw text using F1
  const std::string stream =
      "BT\n"
      "/F1 24 Tf\n"
      "72 72 Td\n"
      "(Hello) Tj\n"
      "ET\n";
  objs.push_back({4, "<< /Length " + std::to_string(stream.size()) + " >>\nstream\n" + stream +
                         "endstream"});

  // 5: Font object (Base14 Helvetica)
  objs.push_back({5, "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>"});

  std::string pdf;
  pdf += "%PDF-1.4\n";

  // Record xref offsets (byte offsets from start of file)
  std::vector<long long> offsets;
  offsets.reserve(static_cast<size_t>(objs.size()) + 1);
  offsets.push_back(0); // object 0 (free)

  for (const auto &o : objs) {
    offsets.push_back(static_cast<long long>(pdf.size()));
    pdf += std::to_string(o.num) + " 0 obj\n";
    pdf += o.body + "\n";
    pdf += "endobj\n";
  }

  const long long xref_pos = static_cast<long long>(pdf.size());
  pdf += "xref\n";
  pdf += "0 " + std::to_string(objs.size() + 1) + "\n";
  pdf += "0000000000 65535 f \n";
  for (size_t i = 1; i < offsets.size(); i++) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010lld 00000 n \n", offsets[i]);
    pdf += buf;
  }

  pdf += "trailer\n";
  pdf += "<< /Size " + std::to_string(objs.size() + 1) + " /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_pos) + "\n";
  pdf += "%%EOF\n";

  return pdf;
}

static PopplerDocument *OpenDocumentFromPathOrFail(const std::string &path) {
  GError *error = nullptr;
  gchar *uri = g_filename_to_uri(path.c_str(), nullptr, &error);
  if (!uri) {
    std::string msg = "g_filename_to_uri failed: ";
    msg += (error && error->message) ? error->message : "unknown error";
    if (error) g_error_free(error);
    ADD_FAILURE() << msg;
    return nullptr;
  }

  PopplerDocument *doc = poppler_document_new_from_file(uri, /*password*/ nullptr, &error);
  g_free(uri);

  if (!doc) {
    std::string msg = "poppler_document_new_from_file failed: ";
    msg += (error && error->message) ? error->message : "unknown error";
    if (error) g_error_free(error);
    ADD_FAILURE() << msg;
    return nullptr;
  }

  return doc;
}

static PopplerFontsIter *ScanFontsOrFail(PopplerDocument *doc, PopplerFontInfo **out_info) {
  if (!doc) return nullptr;

  PopplerFontInfo *info = poppler_font_info_new(doc);
  if (!info) {
    ADD_FAILURE() << "poppler_font_info_new returned null";
    return nullptr;
  }

  const int n_pages = poppler_document_get_n_pages(doc);
  PopplerFontsIter *iter = nullptr;

  // Scan all pages; if none found, iter may remain nullptr.
  const gboolean found = poppler_font_info_scan(info, n_pages, &iter);

  *out_info = info;

  if (!found || !iter) {
    // Some PDFs could yield no fonts; for our generated PDF this should be observable as found==TRUE.
    ADD_FAILURE() << "poppler_font_info_scan did not return a fonts iterator";
    return nullptr;
  }

  return iter;
}

class PopplerFontsIterCopyTest_2229 : public ::testing::Test {};

TEST_F(PopplerFontsIterCopyTest_2229, NullIterReturnsNull_2229) {
  // g_return_val_if_fail should return NULL for nullptr input.
  // Also capture that a CRITICAL is emitted (observable external interaction via logging).
  ScopedGLogHandler glib_criticals("GLib", static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL));

  PopplerFontsIter *copied = poppler_fonts_iter_copy(nullptr);

  EXPECT_EQ(copied, nullptr);
  EXPECT_GE(glib_criticals.count(), 1) << "Expected at least one GLib CRITICAL for nullptr input";
}

TEST_F(PopplerFontsIterCopyTest_2229, CopyProducesDistinctNonNullIterator_2229) {
  TempFile tf;
  tf.WriteAll(BuildMinimalPdfOnePageHelvetica());

  PopplerDocument *doc = OpenDocumentFromPathOrFail(tf.path());
  ASSERT_NE(doc, nullptr);

  PopplerFontInfo *info = nullptr;
  PopplerFontsIter *iter = ScanFontsOrFail(doc, &info);
  ASSERT_NE(iter, nullptr);
  ASSERT_NE(info, nullptr);

  PopplerFontsIter *copy = poppler_fonts_iter_copy(iter);
  ASSERT_NE(copy, nullptr);
  EXPECT_NE(copy, iter);

  // Observable behavior: getters on both iterators should agree initially.
  const char *name_a = poppler_fonts_iter_get_name(iter);
  const char *name_b = poppler_fonts_iter_get_name(copy);

  ASSERT_NE(name_a, nullptr);
  ASSERT_NE(name_b, nullptr);
  EXPECT_STREQ(name_a, name_b);

  // Clean up
  poppler_fonts_iter_free(copy);
  poppler_fonts_iter_free(iter);
  poppler_font_info_free(info);
  g_object_unref(doc);
}

TEST_F(PopplerFontsIterCopyTest_2229, CopyRemainsUsableAfterOriginalFreed_2229) {
  TempFile tf;
  tf.WriteAll(BuildMinimalPdfOnePageHelvetica());

  PopplerDocument *doc = OpenDocumentFromPathOrFail(tf.path());
  ASSERT_NE(doc, nullptr);

  PopplerFontInfo *info = nullptr;
  PopplerFontsIter *iter = ScanFontsOrFail(doc, &info);
  ASSERT_NE(iter, nullptr);
  ASSERT_NE(info, nullptr);

  const std::string original_name =
      poppler_fonts_iter_get_name(iter) ? poppler_fonts_iter_get_name(iter) : "";
  ASSERT_FALSE(original_name.empty());

  PopplerFontsIter *copy = poppler_fonts_iter_copy(iter);
  ASSERT_NE(copy, nullptr);

  // Free the original; the copy should still provide the same observable font properties.
  poppler_fonts_iter_free(iter);

  const char *copy_name = poppler_fonts_iter_get_name(copy);
  ASSERT_NE(copy_name, nullptr);
  EXPECT_EQ(original_name, std::string(copy_name));

  poppler_fonts_iter_free(copy);
  poppler_font_info_free(info);
  g_object_unref(doc);
}

TEST_F(PopplerFontsIterCopyTest_2229, CopyPreservesCurrentPositionAfterAdvancing_2229) {
  TempFile tf;
  tf.WriteAll(BuildMinimalPdfOnePageHelvetica());

  PopplerDocument *doc = OpenDocumentFromPathOrFail(tf.path());
  ASSERT_NE(doc, nullptr);

  PopplerFontInfo *info = nullptr;
  PopplerFontsIter *iter = ScanFontsOrFail(doc, &info);
  ASSERT_NE(iter, nullptr);
  ASSERT_NE(info, nullptr);

  // Advance if possible; even if it can't advance (single font), behavior is still observable.
  const char *before = poppler_fonts_iter_get_name(iter);
  ASSERT_NE(before, nullptr);

  const gboolean advanced = poppler_fonts_iter_next(iter);

  // Copy at "current position" and verify getters match between original and copy.
  PopplerFontsIter *copy = poppler_fonts_iter_copy(iter);
  ASSERT_NE(copy, nullptr);

  const char *orig_now = poppler_fonts_iter_get_name(iter);
  const char *copy_now = poppler_fonts_iter_get_name(copy);
  ASSERT_NE(orig_now, nullptr);
  ASSERT_NE(copy_now, nullptr);
  EXPECT_STREQ(orig_now, copy_now);

  // Boundary/behavior note: if it did not advance (single item), orig_now should equal before.
  if (!advanced) {
    EXPECT_STREQ(orig_now, before);
  }

  poppler_fonts_iter_free(copy);
  poppler_fonts_iter_free(iter);
  poppler_font_info_free(info);
  g_object_unref(doc);
}

} // namespace