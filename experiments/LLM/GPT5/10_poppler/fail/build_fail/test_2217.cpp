// poppler-index-iter-get-action-test_2217.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace {

class TempPdfFile {
public:
  TempPdfFile() = default;

  bool CreateWithContents(const std::string &bytes) {
    gchar *tmpl = g_strdup("poppler-gtest-XXXXXX.pdf");
    int fd = g_mkstemp(tmpl);
    if (fd == -1) {
      g_free(tmpl);
      return false;
    }
    // g_mkstemp returns an open fd; close after writing via std::ofstream.
    ::close(fd);

    path_ = tmpl;
    g_free(tmpl);

    std::ofstream ofs(path_, std::ios::binary);
    if (!ofs.is_open())
      return false;
    ofs.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
    ofs.close();
    return true;
  }

  const std::string &path() const { return path_; }

  std::string uri() const {
    GError *error = nullptr;
    gchar *u = g_filename_to_uri(path_.c_str(), nullptr, &error);
    if (!u) {
      if (error)
        g_error_free(error);
      return {};
    }
    std::string out = u;
    g_free(u);
    return out;
  }

  ~TempPdfFile() {
    if (!path_.empty()) {
      std::remove(path_.c_str());
    }
  }

private:
  std::string path_;
};

// Build a minimal valid PDF with 1 page and 2 outline items (bookmarks).
// Titles: "First" and "Second", both pointing to page 1 with /Fit destination.
std::string BuildPdfWithTwoOutlines() {
  // Objects (without xref/trailer yet).
  // We'll compute exact byte offsets at runtime.
  std::vector<std::string> objs;

  objs.push_back(
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R /Outlines 5 0 R >>\n"
      "endobj\n");

  objs.push_back(
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n");

  objs.push_back(
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Contents 4 0 R >>\n"
      "endobj\n");

  const char *streamBody = "BT /F1 12 Tf 72 720 Td (Hello) Tj ET\n";
  std::ostringstream obj4;
  obj4 << "4 0 obj\n"
       << "<< /Length " << std::strlen(streamBody) << " >>\n"
       << "stream\n"
       << streamBody
       << "endstream\n"
       << "endobj\n";
  objs.push_back(obj4.str());

  objs.push_back(
      "5 0 obj\n"
      "<< /Type /Outlines /First 6 0 R /Last 7 0 R /Count 2 >>\n"
      "endobj\n");

  objs.push_back(
      "6 0 obj\n"
      "<< /Title (First) /Parent 5 0 R /Next 7 0 R /Dest [3 0 R /Fit] >>\n"
      "endobj\n");

  objs.push_back(
      "7 0 obj\n"
      "<< /Title (Second) /Parent 5 0 R /Prev 6 0 R /Dest [3 0 R /Fit] >>\n"
      "endobj\n");

  std::ostringstream pdf;
  pdf << "%PDF-1.4\n";

  std::vector<long> offsets;
  offsets.reserve(objs.size() + 1);
  offsets.push_back(0); // object 0 (free) offset placeholder.

  for (const auto &o : objs) {
    offsets.push_back(static_cast<long>(pdf.tellp()));
    pdf << o;
  }

  const long xrefPos = static_cast<long>(pdf.tellp());
  pdf << "xref\n";
  pdf << "0 " << (objs.size() + 1) << "\n";
  pdf << "0000000000 65535 f \n";
  for (size_t i = 1; i < offsets.size(); ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld", offsets[i]);
    pdf << buf << " 00000 n \n";
  }

  pdf << "trailer\n"
      << "<< /Size " << (objs.size() + 1) << " /Root 1 0 R >>\n"
      << "startxref\n"
      << xrefPos << "\n"
      << "%%EOF\n";

  return pdf.str();
}

PopplerDocument *LoadDocumentFromUri(const std::string &uri) {
  GError *error = nullptr;
  PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
  if (!doc) {
    if (error)
      g_error_free(error);
    return nullptr;
  }
  if (error) {
    g_error_free(error);
  }
  return doc;
}

std::string ActionTitleIfAvailable(PopplerAction *action) {
  // PopplerAction is a public struct in poppler-glib; the "title" is typically
  // exposed as action->any.title. If not available in this build, return "".
  if (!action)
    return "";

  // Defensive: avoid compile errors if struct layout differs in some builds.
  // Most poppler-glib versions define:
  //   struct _PopplerActionAny { PopplerActionType type; gchar *title; };
  //   struct _PopplerAction { PopplerActionType type; union { ...; PopplerActionAny any; } };
#if defined(POPPLER_TYPE_ACTION) || defined(POPPLER_ACTION_NONE) || defined(POPPLER_ACTION_GOTO_DEST)
  // Try the common field name:
  return (action->any.title) ? std::string(action->any.title) : std::string();
#else
  (void)action;
  return "";
#endif
}

class PopplerIndexIterGetActionTest_2217 : public ::testing::Test {
protected:
  void SetUp() override {
    // No special init required; poppler-glib works without g_test_init here.
  }
};

} // namespace

TEST_F(PopplerIndexIterGetActionTest_2217, NullIterReturnsNull_2217) {
  EXPECT_EQ(poppler_index_iter_get_action(nullptr), nullptr);
}

TEST_F(PopplerIndexIterGetActionTest_2217, ReturnsNonNullActionForFirstOutlineItem_2217) {
  TempPdfFile pdf;
  ASSERT_TRUE(pdf.CreateWithContents(BuildPdfWithTwoOutlines()));
  const std::string uri = pdf.uri();
  ASSERT_FALSE(uri.empty());

  PopplerDocument *doc = LoadDocumentFromUri(uri);
  ASSERT_NE(doc, nullptr);

  PopplerIndexIter *iter = poppler_document_get_outline(doc);
  ASSERT_NE(iter, nullptr);

  PopplerAction *action = poppler_index_iter_get_action(iter);
  ASSERT_NE(action, nullptr);

  // Observable behavior: returned action should be usable and freeable.
  // (Also try to verify title if available in this poppler-glib build.)
  const std::string title = ActionTitleIfAvailable(action);
  if (!title.empty()) {
    EXPECT_EQ(title, "First");
  }

  poppler_action_free(action);
  poppler_index_iter_free(iter);
  g_object_unref(doc);
}

TEST_F(PopplerIndexIterGetActionTest_2217, AdvancesAndReturnsActionForSecondOutlineItem_2217) {
  TempPdfFile pdf;
  ASSERT_TRUE(pdf.CreateWithContents(BuildPdfWithTwoOutlines()));
  const std::string uri = pdf.uri();
  ASSERT_FALSE(uri.empty());

  PopplerDocument *doc = LoadDocumentFromUri(uri);
  ASSERT_NE(doc, nullptr);

  PopplerIndexIter *iter = poppler_document_get_outline(doc);
  ASSERT_NE(iter, nullptr);

  // Boundary/normal operation: move to next outline item (2nd of 2).
  ASSERT_TRUE(poppler_index_iter_next(iter));

  PopplerAction *action = poppler_index_iter_get_action(iter);
  ASSERT_NE(action, nullptr);

  const std::string title = ActionTitleIfAvailable(action);
  if (!title.empty()) {
    EXPECT_EQ(title, "Second");
  }

  poppler_action_free(action);
  poppler_index_iter_free(iter);
  g_object_unref(doc);
}

TEST_F(PopplerIndexIterGetActionTest_2217, ActionRemainsValidAfterMultipleGetActionCalls_2217) {
  TempPdfFile pdf;
  ASSERT_TRUE(pdf.CreateWithContents(BuildPdfWithTwoOutlines()));
  const std::string uri = pdf.uri();
  ASSERT_FALSE(uri.empty());

  PopplerDocument *doc = LoadDocumentFromUri(uri);
  ASSERT_NE(doc, nullptr);

  PopplerIndexIter *iter = poppler_document_get_outline(doc);
  ASSERT_NE(iter, nullptr);

  // Call twice; each returned action should be independently freeable.
  PopplerAction *a1 = poppler_index_iter_get_action(iter);
  PopplerAction *a2 = poppler_index_iter_get_action(iter);

  ASSERT_NE(a1, nullptr);
  ASSERT_NE(a2, nullptr);

  // If titles are exposed, both should match the same current item.
  const std::string t1 = ActionTitleIfAvailable(a1);
  const std::string t2 = ActionTitleIfAvailable(a2);
  if (!t1.empty() && !t2.empty()) {
    EXPECT_EQ(t1, t2);
    EXPECT_EQ(t1, "First");
  }

  poppler_action_free(a1);
  poppler_action_free(a2);
  poppler_index_iter_free(iter);
  g_object_unref(doc);
}