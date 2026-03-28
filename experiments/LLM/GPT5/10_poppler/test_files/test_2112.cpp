// File: poppler-annot-line-set-vertices-test_2112.cc
#include <gtest/gtest.h>

#include <poppler.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <string>
#include <vector>

// -----------------------------
// Helpers (no Poppler logic re-implementation; only test scaffolding)
// -----------------------------

namespace {

static std::string BuildPdfWithSingleLineAnnot()
{
  // Build a tiny, valid PDF with 1 page and a single /Subtype /Line annotation.
  // We compute xref offsets to keep the PDF readable by Poppler.

  struct Obj {
    int num;
    std::string body; // without "n 0 obj" / "endobj"
  };

  std::vector<Obj> objs;

  // 1: Catalog
  objs.push_back(
      {1, "<< /Type /Catalog /Pages 2 0 R >>"});

  // 2: Pages
  objs.push_back(
      {2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>"});

  // 4: Contents stream (empty)
  const char *contentsStream =
      "<< /Length 0 >>\n"
      "stream\n"
      "\n"
      "endstream";
  objs.push_back({4, contentsStream});

  // 5: Line annotation
  // /L is the line vertices (x1 y1 x2 y2).
  // /Rect is required; we keep it covering the whole page.
  objs.push_back({5,
                  "<< /Type /Annot /Subtype /Line "
                  "/Rect [0 0 200 200] "
                  "/L [10 10 190 190] "
                  "/C [1 0 0] "
                  "/P 3 0 R >>"});

  // 3: Page (references contents and annotation)
  objs.push_back(
      {3, "<< /Type /Page /Parent 2 0 R "
          "/MediaBox [0 0 200 200] "
          "/Resources << >> "
          "/Contents 4 0 R "
          "/Annots [5 0 R] >>"});

  // PDF header
  std::string pdf;
  pdf += "%PDF-1.4\n";
  pdf += "%\xE2\xE3\xCF\xD3\n"; // binary comment

  // Record offsets: xref entry 0 is the free object
  std::vector<long> offsets;
  offsets.resize(6, 0); // objects 0..5 used

  // Write objects in numeric order: 1..5 (we already have all; sort by num)
  std::sort(objs.begin(), objs.end(), [](const Obj &a, const Obj &b) { return a.num < b.num; });

  for (const auto &o : objs) {
    offsets[o.num] = static_cast<long>(pdf.size());
    pdf += std::to_string(o.num) + " 0 obj\n";
    pdf += o.body;
    pdf += "\nendobj\n";
  }

  const long xrefOffset = static_cast<long>(pdf.size());

  // xref table: 0..5
  pdf += "xref\n";
  pdf += "0 6\n";
  pdf += "0000000000 65535 f \n";
  for (int i = 1; i <= 5; ++i) {
    char buf[32];
    // 10-digit offset, 5-digit generation
    g_snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    pdf += buf;
  }

  // trailer
  pdf += "trailer\n";
  pdf += "<< /Size 6 /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xrefOffset) + "\n";
  pdf += "%%EOF\n";

  return pdf;
}

class ScopedGLogCapture {
public:
  ScopedGLogCapture(const gchar *domain, GLogLevelFlags levels)
      : domain_(domain), levels_(levels)
  {
    // Ensure CRITICALs are not treated as fatal for this domain in this process.
    // (We only want to observe them.)
    old_fatal_mask_ = g_log_set_fatal_mask(domain_, (GLogLevelFlags)0);

    handler_id_ = g_log_set_handler(
        domain_, levels_,
        +[](const gchar *log_domain, GLogLevelFlags log_level, const gchar *message, gpointer user_data) {
          auto *self = static_cast<ScopedGLogCapture *>(user_data);
          self->count_++;
          self->messages_.push_back(
              std::string(log_domain ? log_domain : "") + " | " + std::to_string((unsigned)log_level) +
              " | " + (message ? message : ""));
        },
        this);
  }

  ~ScopedGLogCapture()
  {
    if (handler_id_ != 0) {
      g_log_remove_handler(domain_, handler_id_);
    }
    g_log_set_fatal_mask(domain_, old_fatal_mask_);
  }

  int count() const { return count_; }
  const std::vector<std::string> &messages() const { return messages_; }

private:
  const gchar *domain_;
  GLogLevelFlags levels_;
  guint handler_id_ = 0;
  GLogLevelFlags old_fatal_mask_{};
  int count_ = 0;
  std::vector<std::string> messages_;
};

class PopplerAnnotLineSetVerticesTest_2112 : public ::testing::Test {
protected:
  void SetUp() override
  {
    // Write temporary PDF
    gchar *tmpname = nullptr;
    GError *err = nullptr;

    // Create a unique temp file path
    int fd = g_file_open_tmp("poppler_annot_line_vertices_XXXXXX.pdf", &tmpname, &err);
    ASSERT_NE(fd, -1) << "g_file_open_tmp failed: " << (err ? err->message : "unknown");
    ASSERT_NE(tmpname, nullptr);

    const std::string pdf = BuildPdfWithSingleLineAnnot();
    const gssize w = write(fd, pdf.data(), pdf.size());
    close(fd);
    ASSERT_EQ(w, (gssize)pdf.size());

    tmp_path_ = tmpname;
    g_free(tmpname);

    // Load PopplerDocument
    gchar *uri = g_filename_to_uri(tmp_path_.c_str(), nullptr, &err);
    ASSERT_NE(uri, nullptr) << "g_filename_to_uri failed: " << (err ? err->message : "unknown");

    doc_ = poppler_document_new_from_file(uri, /*password=*/nullptr, &err);
    g_free(uri);
    ASSERT_NE(doc_, nullptr) << "poppler_document_new_from_file failed: " << (err ? err->message : "unknown");

    // Get first page
    page_ = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page_, nullptr);

    // Find the line annotation via mapping API
    GList *mappings = poppler_page_get_annot_mapping(page_);
    ASSERT_NE(mappings, nullptr);

    PopplerAnnotLine *found = nullptr;
    for (GList *l = mappings; l != nullptr; l = l->next) {
      auto *mapping = static_cast<PopplerAnnotMapping *>(l->data);
      if (mapping && mapping->annot && POPPLER_IS_ANNOT_LINE(mapping->annot)) {
        found = POPPLER_ANNOT_LINE(mapping->annot);
        break;
      }
    }

    poppler_page_free_annot_mapping(mappings);

    ASSERT_NE(found, nullptr) << "Did not find a PopplerAnnotLine in the test PDF.";
    line_ = found;
  }

  void TearDown() override
  {
    if (page_) {
      g_object_unref(page_);
      page_ = nullptr;
    }
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
    if (!tmp_path_.empty()) {
      g_remove(tmp_path_.c_str());
      tmp_path_.clear();
    }
    line_ = nullptr; // owned by Poppler; released with doc/page
  }

  std::string tmp_path_;
  PopplerDocument *doc_ = nullptr;
  PopplerPage *page_ = nullptr;
  PopplerAnnotLine *line_ = nullptr;
};

} // namespace

// -----------------------------
// Tests
// -----------------------------

TEST_F(PopplerAnnotLineSetVerticesTest_2112, ValidInputsDoNotEmitCritical_2112)
{
  ASSERT_NE(line_, nullptr);

  PopplerPoint start;
  start.x = 1.0;
  start.y = 2.0;

  PopplerPoint end;
  end.x = 3.0;
  end.y = 4.0;

  // g_return_if_fail logs CRITICAL under the "GLib" domain.
  ScopedGLogCapture glib_capture("GLib", (GLogLevelFlags)(G_LOG_LEVEL_CRITICAL));

  poppler_annot_line_set_vertices(line_, &start, &end);

  EXPECT_EQ(glib_capture.count(), 0) << "Unexpected GLib CRITICAL was emitted.";
}

TEST_F(PopplerAnnotLineSetVerticesTest_2112, NullStartTriggersReturnIfFail_2112)
{
  ASSERT_NE(line_, nullptr);

  PopplerPoint end;
  end.x = 3.0;
  end.y = 4.0;

  ScopedGLogCapture glib_capture("GLib", (GLogLevelFlags)(G_LOG_LEVEL_CRITICAL));

  poppler_annot_line_set_vertices(line_, /*start=*/nullptr, &end);

  EXPECT_GE(glib_capture.count(), 1) << "Expected at least one GLib CRITICAL for nullptr start.";
}

TEST_F(PopplerAnnotLineSetVerticesTest_2112, NullEndTriggersReturnIfFail_2112)
{
  ASSERT_NE(line_, nullptr);

  PopplerPoint start;
  start.x = 1.0;
  start.y = 2.0;

  ScopedGLogCapture glib_capture("GLib", (GLogLevelFlags)(G_LOG_LEVEL_CRITICAL));

  poppler_annot_line_set_vertices(line_, &start, /*end=*/nullptr);

  EXPECT_GE(glib_capture.count(), 1) << "Expected at least one GLib CRITICAL for nullptr end.";
}

TEST_F(PopplerAnnotLineSetVerticesTest_2112, NullAnnotTriggersTypeCheckFailure_2112)
{
  PopplerPoint start;
  start.x = 1.0;
  start.y = 2.0;

  PopplerPoint end;
  end.x = 3.0;
  end.y = 4.0;

  ScopedGLogCapture glib_capture("GLib", (GLogLevelFlags)(G_LOG_LEVEL_CRITICAL));

  poppler_annot_line_set_vertices(/*poppler_annot=*/nullptr, &start, &end);

  EXPECT_GE(glib_capture.count(), 1) << "Expected at least one GLib CRITICAL for nullptr annot.";
}

TEST_F(PopplerAnnotLineSetVerticesTest_2112, WrongTypeAnnotTriggersTypeCheckFailure_2112)
{
  // Create a different annot subtype instance (Text) and pass it as if it were a line.
  // This should fail POPPLER_IS_ANNOT_LINE() and return early (observable via GLib CRITICAL).
  PopplerAnnot *wrong = POPPLER_ANNOT(g_object_new(POPPLER_TYPE_ANNOT_TEXT, nullptr));
  ASSERT_NE(wrong, nullptr);

  PopplerPoint start;
  start.x = 1.0;
  start.y = 2.0;

  PopplerPoint end;
  end.x = 3.0;
  end.y = 4.0;

  ScopedGLogCapture glib_capture("GLib", (GLogLevelFlags)(G_LOG_LEVEL_CRITICAL));

  poppler_annot_line_set_vertices(reinterpret_cast<PopplerAnnotLine *>(wrong), &start, &end);

  EXPECT_GE(glib_capture.count(), 1) << "Expected at least one GLib CRITICAL for wrong annot type.";

  g_object_unref(wrong);
}