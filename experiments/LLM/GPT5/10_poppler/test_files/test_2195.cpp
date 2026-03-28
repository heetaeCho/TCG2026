// poppler_document_get_page_layout_test_2195.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

extern "C" {
#include <poppler.h>
}

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace {

class ScopedGLogSilencer_2195 {
public:
  ScopedGLogSilencer_2195()
  {
    // Silence criticals that can be emitted by g_return_val_if_fail().
    addHandler(nullptr);
    addHandler("GLib");
    addHandler("GLib-GObject");
    addHandler("Poppler");
  }

  ~ScopedGLogSilencer_2195()
  {
    for (const auto &h : handlers_) {
      g_log_remove_handler(h.domain, h.id);
    }
  }

  ScopedGLogSilencer_2195(const ScopedGLogSilencer_2195 &) = delete;
  ScopedGLogSilencer_2195 &operator=(const ScopedGLogSilencer_2195 &) = delete;

private:
  struct Handler {
    const char *domain;
    guint id;
  };

  static void noopHandler(const gchar *, GLogLevelFlags, const gchar *, gpointer) {}

  void addHandler(const char *domain)
  {
    guint id = g_log_set_handler(domain,
                                 static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING),
                                 &ScopedGLogSilencer_2195::noopHandler, nullptr);
    handlers_.push_back({domain, id});
  }

  std::vector<Handler> handlers_;
};

static std::string BuildMinimalPdfWithOptionalPageLayout_2195(const char *pageLayoutNameOrNull)
{
  // Minimal valid PDF with 3 objects: Catalog, Pages, Page. Optional /PageLayout in Catalog.
  auto obj1 = std::string("1 0 obj\n<< /Type /Catalog /Pages 2 0 R");
  if (pageLayoutNameOrNull) {
    obj1 += " /PageLayout /";
    obj1 += pageLayoutNameOrNull;
  }
  obj1 += " >>\nendobj\n";

  const std::string obj2 =
      "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
  const std::string obj3 =
      "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";

  // Assemble with xref offsets.
  std::string pdf;
  pdf += "%PDF-1.4\n";
  pdf += "%\xE2\xE3\xCF\xD3\n"; // binary comment

  std::vector<long> offsets;
  offsets.reserve(4);
  offsets.push_back(0); // object 0 (free)

  auto appendWithOffset = [&](const std::string &s) {
    offsets.push_back(static_cast<long>(pdf.size()));
    pdf += s;
  };

  appendWithOffset(obj1);
  appendWithOffset(obj2);
  appendWithOffset(obj3);

  const long xrefPos = static_cast<long>(pdf.size());
  pdf += "xref\n0 4\n";
  pdf += "0000000000 65535 f \n";
  for (size_t i = 1; i < offsets.size(); ++i) {
    char line[32];
    std::snprintf(line, sizeof(line), "%010ld 00000 n \n", offsets[i]);
    pdf += line;
  }
  pdf += "trailer\n<< /Size 4 /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xrefPos);
  pdf += "\n%%EOF\n";
  return pdf;
}

static std::string WriteTempFile_2195(const std::string &contents)
{
  std::string templ = std::string(g_get_tmp_dir()) + G_DIR_SEPARATOR_S + "poppler-ut-2195-XXXXXX.pdf";
  std::vector<char> path(templ.begin(), templ.end());
  path.push_back('\0');

  int fd = g_mkstemp(path.data());
  EXPECT_GE(fd, 0);

  const gssize toWrite = static_cast<gssize>(contents.size());
  gssize written = 0;
  while (written < toWrite) {
    gssize w = write(fd, contents.data() + written, static_cast<size_t>(toWrite - written));
    EXPECT_GT(w, 0);
    written += w;
  }
  close(fd);
  return std::string(path.data());
}

static std::string PathToFileUri_2195(const std::string &path)
{
  // Use GLib helper to avoid manual escaping.
  gchar *uri = g_filename_to_uri(path.c_str(), nullptr, nullptr);
  EXPECT_NE(uri, nullptr);
  std::string out(uri);
  g_free(uri);
  return out;
}

class PopplerDocumentGetPageLayoutTest_2195 : public ::testing::Test {
protected:
  void TearDown() override
  {
    if (!tmpPath_.empty()) {
      g_remove(tmpPath_.c_str());
      tmpPath_.clear();
    }
  }

  PopplerDocument *LoadFromPdfString(const std::string &pdf)
  {
    tmpPath_ = WriteTempFile_2195(pdf);
    const std::string uri = PathToFileUri_2195(tmpPath_);

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &error);
    if (!doc && error) {
      g_error_free(error);
    }
    return doc;
  }

  std::string tmpPath_;
};

TEST_F(PopplerDocumentGetPageLayoutTest_2195, NullDocumentReturnsUnset_2195)
{
  ScopedGLogSilencer_2195 silencer;
  EXPECT_EQ(poppler_document_get_page_layout(nullptr), POPPLER_PAGE_LAYOUT_UNSET);
}

TEST_F(PopplerDocumentGetPageLayoutTest_2195, NonDocumentPointerReturnsUnset_2195)
{
  ScopedGLogSilencer_2195 silencer;

  // Create a plain GObject instance (not a PopplerDocument) and cast it.
  GObject *obj = static_cast<GObject *>(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  auto *fakeDoc = reinterpret_cast<PopplerDocument *>(obj);
  EXPECT_EQ(poppler_document_get_page_layout(fakeDoc), POPPLER_PAGE_LAYOUT_UNSET);

  g_object_unref(obj);
}

TEST_F(PopplerDocumentGetPageLayoutTest_2195, MissingPageLayoutInPdfReturnsUnset_2195)
{
  PopplerDocument *doc = LoadFromPdfString(BuildMinimalPdfWithOptionalPageLayout_2195(nullptr));
  ASSERT_NE(doc, nullptr);

  EXPECT_EQ(poppler_document_get_page_layout(doc), POPPLER_PAGE_LAYOUT_UNSET);

  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetPageLayoutTest_2195, UnknownPageLayoutInPdfReturnsUnset_2195)
{
  PopplerDocument *doc = LoadFromPdfString(BuildMinimalPdfWithOptionalPageLayout_2195("DefinitelyNotARealLayout"));
  ASSERT_NE(doc, nullptr);

  // For an unrecognized catalog /PageLayout name, the observable behavior should be "unset".
  EXPECT_EQ(poppler_document_get_page_layout(doc), POPPLER_PAGE_LAYOUT_UNSET);

  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetPageLayoutTest_2195, SinglePageMapsToSinglePageEnum_2195)
{
  PopplerDocument *doc = LoadFromPdfString(BuildMinimalPdfWithOptionalPageLayout_2195("SinglePage"));
  ASSERT_NE(doc, nullptr);

  EXPECT_EQ(poppler_document_get_page_layout(doc), POPPLER_PAGE_LAYOUT_SINGLE_PAGE);

  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetPageLayoutTest_2195, OneColumnMapsToOneColumnEnum_2195)
{
  PopplerDocument *doc = LoadFromPdfString(BuildMinimalPdfWithOptionalPageLayout_2195("OneColumn"));
  ASSERT_NE(doc, nullptr);

  EXPECT_EQ(poppler_document_get_page_layout(doc), POPPLER_PAGE_LAYOUT_ONE_COLUMN);

  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetPageLayoutTest_2195, TwoColumnLeftMapsToTwoColumnLeftEnum_2195)
{
  PopplerDocument *doc = LoadFromPdfString(BuildMinimalPdfWithOptionalPageLayout_2195("TwoColumnLeft"));
  ASSERT_NE(doc, nullptr);

  EXPECT_EQ(poppler_document_get_page_layout(doc), POPPLER_PAGE_LAYOUT_TWO_COLUMN_LEFT);

  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetPageLayoutTest_2195, TwoColumnRightMapsToTwoColumnRightEnum_2195)
{
  PopplerDocument *doc = LoadFromPdfString(BuildMinimalPdfWithOptionalPageLayout_2195("TwoColumnRight"));
  ASSERT_NE(doc, nullptr);

  EXPECT_EQ(poppler_document_get_page_layout(doc), POPPLER_PAGE_LAYOUT_TWO_COLUMN_RIGHT);

  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetPageLayoutTest_2195, TwoPageLeftMapsToTwoPageLeftEnum_2195)
{
  PopplerDocument *doc = LoadFromPdfString(BuildMinimalPdfWithOptionalPageLayout_2195("TwoPageLeft"));
  ASSERT_NE(doc, nullptr);

  EXPECT_EQ(poppler_document_get_page_layout(doc), POPPLER_PAGE_LAYOUT_TWO_PAGE_LEFT);

  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetPageLayoutTest_2195, TwoPageRightMapsToTwoPageRightEnum_2195)
{
  PopplerDocument *doc = LoadFromPdfString(BuildMinimalPdfWithOptionalPageLayout_2195("TwoPageRight"));
  ASSERT_NE(doc, nullptr);

  EXPECT_EQ(poppler_document_get_page_layout(doc), POPPLER_PAGE_LAYOUT_TWO_PAGE_RIGHT);

  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetPageLayoutTest_2195, RepeatedCallsAreStableForSameDocument_2195)
{
  PopplerDocument *doc = LoadFromPdfString(BuildMinimalPdfWithOptionalPageLayout_2195("OneColumn"));
  ASSERT_NE(doc, nullptr);

  const PopplerPageLayout first = poppler_document_get_page_layout(doc);
  const PopplerPageLayout second = poppler_document_get_page_layout(doc);

  EXPECT_EQ(first, POPPLER_PAGE_LAYOUT_ONE_COLUMN);
  EXPECT_EQ(second, POPPLER_PAGE_LAYOUT_ONE_COLUMN);

  g_object_unref(doc);
}

} // namespace