// File: poppler-annot-file-attachment-get-name-test_2105.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

namespace {

class ScopedCriticalLogCatcher {
public:
  ScopedCriticalLogCatcher() {
    // Catch criticals from common domains where g_return_* warnings may land.
    AddDomainHandler("GLib");
    AddDomainHandler("GLib-GObject");
    AddDomainHandler("Poppler");
    AddDomainHandler(nullptr); // default domain
  }

  ~ScopedCriticalLogCatcher() {
    for (auto &h : handlers_) {
      if (h.id != 0) {
        g_log_remove_handler(h.domain, h.id);
      }
      g_free(h.domain);
    }
  }

  int critical_count() const { return critical_count_; }

private:
  struct Handler {
    gchar *domain;
    guint id;
  };

  static void LogHandler(const gchar * /*log_domain*/,
                         GLogLevelFlags log_level,
                         const gchar * /*message*/,
                         gpointer user_data) {
    if (log_level & (G_LOG_LEVEL_CRITICAL)) {
      static_cast<ScopedCriticalLogCatcher *>(user_data)->critical_count_++;
    }
    // Swallow to avoid noisy test output.
  }

  void AddDomainHandler(const gchar *domain) {
    Handler h;
    h.domain = domain ? g_strdup(domain) : nullptr;
    h.id = g_log_set_handler(domain, G_LOG_LEVEL_CRITICAL,
                             &ScopedCriticalLogCatcher::LogHandler, this);
    handlers_.push_back(h);
  }

  std::vector<Handler> handlers_;
  int critical_count_ = 0;
};

static std::string BuildMinimalPdfWithFileAttachmentAnnot(bool include_name_keys) {
  // Build a minimal PDF with one page and one /Subtype /FileAttachment annotation.
  // We intentionally keep expectations minimal: the test only checks whether
  // poppler_annot_file_attachment_get_name() returns NULL or non-NULL.
  struct Obj {
    int num;
    std::string body; // without "n 0 obj" / "endobj"
  };

  std::vector<Obj> objs;
  objs.push_back({1, "<< /Type /Catalog /Pages 2 0 R >>\n"});
  objs.push_back({2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"});
  objs.push_back({3,
                  "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
                  "   /Resources << >>\n"
                  "   /Contents 5 0 R\n"
                  "   /Annots [4 0 R]\n"
                  ">>\n"});

  std::string annot =
      "<< /Type /Annot /Subtype /FileAttachment /Rect [10 10 20 20]\n"
      "   /Contents (Attach)\n"
      "   /FS << /Type /Filespec /F (test.txt) >>\n";
  if (include_name_keys) {
    // Provide multiple plausible keys; whichever Poppler uses, this should
    // tend to produce a non-NULL name.
    annot += "   /Name /Paperclip\n";
    annot += "   /T (MyAttachmentName)\n";
  }
  annot += ">>\n";
  objs.push_back({4, annot});

  // Empty content stream
  objs.push_back({5, "<< /Length 0 >>\nstream\nendstream\n"});

  std::string out;
  out += "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n";

  // Track offsets (byte offsets from beginning of file).
  std::vector<long> offsets(6, 0); // 0..5
  for (const auto &o : objs) {
    offsets[o.num] = static_cast<long>(out.size());
    out += std::to_string(o.num) + " 0 obj\n";
    out += o.body;
    out += "endobj\n";
  }

  const long xref_pos = static_cast<long>(out.size());
  out += "xref\n";
  out += "0 6\n";
  out += "0000000000 65535 f \n";
  for (int i = 1; i <= 5; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    out += buf;
  }
  out += "trailer\n";
  out += "<< /Size 6 /Root 1 0 R >>\n";
  out += "startxref\n";
  out += std::to_string(xref_pos) + "\n";
  out += "%%EOF\n";
  return out;
}

static std::string WriteTempFile(const std::string &contents) {
  gchar *tmpl = g_strdup("/tmp/poppler_glib_test_XXXXXX.pdf");
  int fd = g_mkstemp(tmpl);
  if (fd == -1) {
    std::string err = "g_mkstemp failed";
    g_free(tmpl);
    throw std::runtime_error(err);
  }
  FILE *f = fdopen(fd, "wb");
  if (!f) {
    close(fd);
    std::string err = "fdopen failed";
    g_free(tmpl);
    throw std::runtime_error(err);
  }
  const size_t written = fwrite(contents.data(), 1, contents.size(), f);
  fclose(f);
  if (written != contents.size()) {
    std::string err = "fwrite failed";
    g_free(tmpl);
    throw std::runtime_error(err);
  }
  std::string path = tmpl;
  g_free(tmpl);
  return path;
}

static PopplerAnnotFileAttachment *FindFirstFileAttachmentAnnot(PopplerDocument *doc) {
  PopplerPage *page = poppler_document_get_page(doc, 0);
  if (!page) return nullptr;

  GList *mappings = poppler_page_get_annot_mapping(page);
  PopplerAnnotFileAttachment *found = nullptr;

  for (GList *l = mappings; l != nullptr; l = l->next) {
    auto *mapping = static_cast<PopplerAnnotMapping *>(l->data);
    if (mapping && mapping->annot && POPPLER_IS_ANNOT_FILE_ATTACHMENT(mapping->annot)) {
      found = POPPLER_ANNOT_FILE_ATTACHMENT(mapping->annot);
      break;
    }
  }

  poppler_page_free_annot_mapping(mappings);
  g_object_unref(page);
  return found;
}

class PopplerAnnotFileAttachmentGetNameTest_2105 : public ::testing::Test {
protected:
  void TearDown() override {
    for (const auto &p : temp_paths_) {
      (void)g_remove(p.c_str());
    }
    temp_paths_.clear();
  }

  PopplerDocument *LoadDocFromPdfString(const std::string &pdf) {
    const std::string path = WriteTempFile(pdf);
    temp_paths_.push_back(path);

    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(path.c_str(), nullptr, &error);
    if (!uri) {
      if (error) g_error_free(error);
      return nullptr;
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);
    if (!doc) {
      if (error) g_error_free(error);
      return nullptr;
    }
    return doc;
  }

  std::vector<std::string> temp_paths_;
};

} // namespace

// The function under test:
// gchar *poppler_annot_file_attachment_get_name(PopplerAnnotFileAttachment *poppler_annot);

TEST_F(PopplerAnnotFileAttachmentGetNameTest_2105, NullInputReturnsNull_2105) {
  ScopedCriticalLogCatcher catcher;
  gchar *name = poppler_annot_file_attachment_get_name(nullptr);
  EXPECT_EQ(name, nullptr);
  EXPECT_GE(catcher.critical_count(), 1);
}

TEST_F(PopplerAnnotFileAttachmentGetNameTest_2105, WrongTypeReturnsNull_2105) {
  // Pass a different PopplerAnnot subtype to verify type-checking behavior.
  ScopedCriticalLogCatcher catcher;

  PopplerAnnot *other = POPPLER_ANNOT(g_object_new(POPPLER_TYPE_ANNOT, nullptr));
  ASSERT_NE(other, nullptr);

  gchar *name = poppler_annot_file_attachment_get_name(
      reinterpret_cast<PopplerAnnotFileAttachment *>(other));
  EXPECT_EQ(name, nullptr);
  EXPECT_GE(catcher.critical_count(), 1);

  g_object_unref(other);
}

TEST_F(PopplerAnnotFileAttachmentGetNameTest_2105, ValidAnnotWithNameReturnsNonNullUtf8_2105) {
  const std::string pdf = BuildMinimalPdfWithFileAttachmentAnnot(/*include_name_keys=*/true);
  PopplerDocument *doc = LoadDocFromPdfString(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerAnnotFileAttachment *fa = FindFirstFileAttachmentAnnot(doc);
  ASSERT_NE(fa, nullptr);

  gchar *name = poppler_annot_file_attachment_get_name(fa);
  ASSERT_NE(name, nullptr);
  EXPECT_GT(std::strlen(name), 0u);

  g_free(name);
  g_object_unref(doc);
}

TEST_F(PopplerAnnotFileAttachmentGetNameTest_2105, ValidAnnotWithoutNameReturnsNull_2105) {
  const std::string pdf = BuildMinimalPdfWithFileAttachmentAnnot(/*include_name_keys=*/false);
  PopplerDocument *doc = LoadDocFromPdfString(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerAnnotFileAttachment *fa = FindFirstFileAttachmentAnnot(doc);
  ASSERT_NE(fa, nullptr);

  gchar *name = poppler_annot_file_attachment_get_name(fa);
  EXPECT_EQ(name, nullptr);

  g_object_unref(doc);
}

TEST_F(PopplerAnnotFileAttachmentGetNameTest_2105, RepeatedCallsProduceIndependentResults_2105) {
  const std::string pdf = BuildMinimalPdfWithFileAttachmentAnnot(/*include_name_keys=*/true);
  PopplerDocument *doc = LoadDocFromPdfString(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerAnnotFileAttachment *fa = FindFirstFileAttachmentAnnot(doc);
  ASSERT_NE(fa, nullptr);

  gchar *name1 = poppler_annot_file_attachment_get_name(fa);
  gchar *name2 = poppler_annot_file_attachment_get_name(fa);

  ASSERT_NE(name1, nullptr);
  ASSERT_NE(name2, nullptr);
  EXPECT_STREQ(name1, name2);

  g_free(name1);
  g_free(name2);
  g_object_unref(doc);
}