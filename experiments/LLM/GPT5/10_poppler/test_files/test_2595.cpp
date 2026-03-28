// poppler-structure-element-get-table-summary-test.cc
//
// Unit tests for poppler_structure_element_get_table_summary()
// TEST_ID: 2595

#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace {

// Minimal PDF builder that emits a single-page document with a structure tree
// containing one /Table StructElem. The /A dictionary includes /Summary <token>,
// where <token> is inserted verbatim (e.g. "(text)", "/MyName", "()", "123").
//
// This is test data generation (not Poppler logic), so it’s OK to implement here.
static std::string BuildPdfWithTableSummaryToken(const std::string &summary_token) {
  std::vector<std::string> objs;
  objs.reserve(6);

  // 1: Catalog with StructTreeRoot
  objs.push_back(
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R /StructTreeRoot 5 0 R >>\n"
      "endobj\n");

  // 2: Pages
  objs.push_back(
      "2 0 obj\n"
      "<< /Type /Pages /Count 1 /Kids [3 0 R] >>\n"
      "endobj\n");

  // 3: Page (blank)
  objs.push_back(
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
      "   /Contents 4 0 R /Resources << >> >>\n"
      "endobj\n");

  // 4: Empty content stream
  objs.push_back(
      "4 0 obj\n"
      "<< /Length 0 >>\n"
      "stream\n"
      "\n"
      "endstream\n"
      "endobj\n");

  // 5: StructTreeRoot
  objs.push_back(
      "5 0 obj\n"
      "<< /Type /StructTreeRoot /K [6 0 R] >>\n"
      "endobj\n");

  // 6: Table StructElem with Summary attribute
  // Keep /K empty array so Poppler sees it as a leaf element.
  std::string obj6 =
      "6 0 obj\n"
      "<< /Type /StructElem /S /Table /P 5 0 R\n"
      "   /A << /Summary " +
      summary_token +
      " >>\n"
      "   /K [] >>\n"
      "endobj\n";
  objs.push_back(std::move(obj6));

  std::string pdf;
  pdf.reserve(2048);
  pdf += "%PDF-1.5\n%\xE2\xE3\xCF\xD3\n";

  std::vector<long> offsets;
  offsets.resize(objs.size() + 1);
  offsets[0] = 0;

  // Write objects and track offsets.
  for (size_t i = 0; i < objs.size(); ++i) {
    offsets[i + 1] = static_cast<long>(pdf.size());
    pdf += objs[i];
  }

  const long xref_offset = static_cast<long>(pdf.size());
  pdf += "xref\n";
  pdf += "0 " + std::to_string(objs.size() + 1) + "\n";
  pdf += "0000000000 65535 f \n";
  for (size_t i = 1; i <= objs.size(); ++i) {
    char buf[64];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    pdf += buf;
  }

  pdf += "trailer\n";
  pdf += "<< /Size " + std::to_string(objs.size() + 1) + " /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_offset) + "\n";
  pdf += "%%EOF\n";

  return pdf;
}

static std::string WriteTempFile(const std::string &bytes) {
  gchar *tmpl = g_strdup("/tmp/poppler-struct-XXXXXX.pdf");
  int fd = g_mkstemp(tmpl);
  if (fd < 0) {
    std::string msg = "g_mkstemp failed: ";
    msg += g_strerror(errno);
    g_free(tmpl);
    throw std::runtime_error(msg);
  }

  FILE *f = fdopen(fd, "wb");
  if (!f) {
    close(fd);
    std::string msg = "fdopen failed: ";
    msg += g_strerror(errno);
    g_unlink(tmpl);
    g_free(tmpl);
    throw std::runtime_error(msg);
  }

  const size_t written = fwrite(bytes.data(), 1, bytes.size(), f);
  fclose(f);

  if (written != bytes.size()) {
    std::string msg = "fwrite failed (short write)";
    g_unlink(tmpl);
    g_free(tmpl);
    throw std::runtime_error(msg);
  }

  std::string path = tmpl;
  g_free(tmpl);
  return path;
}

static PopplerDocument *OpenDocFromPath(const std::string &path) {
  GError *error = nullptr;
  gchar *uri = g_filename_to_uri(path.c_str(), /*hostname=*/nullptr, &error);
  if (!uri) {
    if (error) g_error_free(error);
    return nullptr;
  }

  PopplerDocument *doc = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
  g_free(uri);

  if (!doc) {
    if (error) g_error_free(error);
    return nullptr;
  }
  return doc;
}

static PopplerStructureElement *FindFirstTableElement(PopplerStructureElementIter *iter) {
  // Depth-first traversal (similar to the docs sample).
  do {
    g_autoptr(PopplerStructureElement) element =
        poppler_structure_element_iter_get_element(iter);
    if (element) {
      if (poppler_structure_element_get_kind(element) == POPPLER_STRUCTURE_ELEMENT_TABLE) {
        // Transfer ownership to caller.
        return static_cast<PopplerStructureElement *>(g_object_ref(element));
      }
    }

    PopplerStructureElementIter *child = poppler_structure_element_iter_get_child(iter);
    if (child) {
      PopplerStructureElement *found = FindFirstTableElement(child);
      poppler_structure_element_iter_free(child);
      if (found) return found;
    }
  } while (poppler_structure_element_iter_next(iter));

  return nullptr;
}

}  // namespace

TEST(PopplerStructureElementGetTableSummaryTest_2595, NullElementReturnsNullAndLogs_2595) {
  // g_return_val_if_fail() should emit a critical and return NULL.
  g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_STRUCTURE_ELEMENT*");
  gchar *summary = poppler_structure_element_get_table_summary(nullptr);
  g_test_assert_expected_messages();

  EXPECT_EQ(summary, nullptr);
}

TEST(PopplerStructureElementGetTableSummaryTest_2595, SummaryStringIsReturnedUtf8_2595) {
  const std::string pdf = BuildPdfWithTableSummaryToken("(My table summary)");
  const std::string path = WriteTempFile(pdf);

  g_autoptr(PopplerDocument) doc = OpenDocFromPath(path);
  ASSERT_NE(doc, nullptr);

  g_autoptr(PopplerStructureElementIter) iter = poppler_structure_element_iter_new(doc);
  ASSERT_NE(iter, nullptr);

  g_autoptr(PopplerStructureElement) table = FindFirstTableElement(iter);
  ASSERT_NE(table, nullptr);

  g_autofree gchar *summary = poppler_structure_element_get_table_summary(table);
  ASSERT_NE(summary, nullptr);
  EXPECT_STREQ(summary, "My table summary");

  g_unlink(path.c_str());
}

TEST(PopplerStructureElementGetTableSummaryTest_2595, SummaryNameIsReturnedAsNameString_2595) {
  const std::string pdf = BuildPdfWithTableSummaryToken("/MySummaryName");
  const std::string path = WriteTempFile(pdf);

  g_autoptr(PopplerDocument) doc = OpenDocFromPath(path);
  ASSERT_NE(doc, nullptr);

  g_autoptr(PopplerStructureElementIter) iter = poppler_structure_element_iter_new(doc);
  ASSERT_NE(iter, nullptr);

  g_autoptr(PopplerStructureElement) table = FindFirstTableElement(iter);
  ASSERT_NE(table, nullptr);

  g_autofree gchar *summary = poppler_structure_element_get_table_summary(table);
  ASSERT_NE(summary, nullptr);
  // Name objects are returned without the leading '/' (per Object::getName()).
  EXPECT_STREQ(summary, "MySummaryName");

  g_unlink(path.c_str());
}

TEST(PopplerStructureElementGetTableSummaryTest_2595, EmptySummaryStringReturnsEmptyNonNull_2595) {
  const std::string pdf = BuildPdfWithTableSummaryToken("()");
  const std::string path = WriteTempFile(pdf);

  g_autoptr(PopplerDocument) doc = OpenDocFromPath(path);
  ASSERT_NE(doc, nullptr);

  g_autoptr(PopplerStructureElementIter) iter = poppler_structure_element_iter_new(doc);
  ASSERT_NE(iter, nullptr);

  g_autoptr(PopplerStructureElement) table = FindFirstTableElement(iter);
  ASSERT_NE(table, nullptr);

  g_autofree gchar *summary = poppler_structure_element_get_table_summary(table);
  ASSERT_NE(summary, nullptr);
  EXPECT_STREQ(summary, "");

  g_unlink(path.c_str());
}

TEST(PopplerStructureElementGetTableSummaryTest_2595, NonStringNonNameSummaryTriggersAssert_2595) {
  // The implementation calls g_assert_not_reached() for unexpected types.
  // Provide an integer token so Summary is neither string nor name.
  const std::string pdf = BuildPdfWithTableSummaryToken("123");
  const std::string path = WriteTempFile(pdf);

  g_autoptr(PopplerDocument) doc = OpenDocFromPath(path);
  ASSERT_NE(doc, nullptr);

  g_autoptr(PopplerStructureElementIter) iter = poppler_structure_element_iter_new(doc);
  ASSERT_NE(iter, nullptr);

  g_autoptr(PopplerStructureElement) table = FindFirstTableElement(iter);
  ASSERT_NE(table, nullptr);

  // Expect the process to die due to g_assert_not_reached().
  EXPECT_DEATH(
      {
        gchar *summary = poppler_structure_element_get_table_summary(table);
        (void)summary;
      },
      ".*");

  g_unlink(path.c_str());
}