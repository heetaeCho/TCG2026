// poppler-action-build-launch-ut_2293.cc
#include <gtest/gtest.h>

#include <glib.h>

#include "poppler.h"
#include "poppler-action.h"

#include <string>
#include <vector>

namespace {

struct TempPdf {
  std::string path;
  std::string uri;
};

static TempPdf WriteTempPdf(const std::string &pdf_bytes) {
  GError *error = nullptr;

  gchar *tmpl = g_strdup("poppler_build_launch_XXXXXX.pdf");
  // g_file_open_tmp creates a file in the system temp dir.
  gint fd = g_file_open_tmp(tmpl, &tmpl, &error);
  EXPECT_NE(fd, -1) << (error ? error->message : "g_file_open_tmp failed");

  if (fd != -1) {
    gssize total = 0;
    const char *data = pdf_bytes.data();
    gssize len = static_cast<gssize>(pdf_bytes.size());
    while (total < len) {
      gssize n = write(fd, data + total, static_cast<size_t>(len - total));
      EXPECT_GT(n, 0);
      if (n <= 0)
        break;
      total += n;
    }
    close(fd);
    EXPECT_EQ(total, len);
  }

  gchar *uri = g_filename_to_uri(tmpl, /*hostname=*/nullptr, &error);
  EXPECT_NE(uri, nullptr) << (error ? error->message : "g_filename_to_uri failed");

  TempPdf out;
  out.path = tmpl ? tmpl : "";
  out.uri = uri ? uri : "";

  g_free(uri);
  g_free(tmpl);
  if (error)
    g_error_free(error);
  return out;
}

static PopplerDocument *OpenDocOrFail(const std::string &uri) {
  GError *error = nullptr;
  PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &error);
  EXPECT_NE(doc, nullptr) << (error ? error->message : "poppler_document_new_from_file failed");
  if (error)
    g_error_free(error);
  return doc;
}

static std::vector<PopplerAction *> GetLaunchActionsFromFirstPage(PopplerDocument *doc) {
  std::vector<PopplerAction *> out;
  if (!doc)
    return out;

  PopplerPage *page = poppler_document_get_page(doc, 0);
  EXPECT_NE(page, nullptr);
  if (!page)
    return out;

  GList *mappings = poppler_page_get_link_mapping(page);
  for (GList *l = mappings; l; l = l->next) {
    auto *mapping = static_cast<PopplerLinkMapping *>(l->data);
    if (!mapping || !mapping->action)
      continue;
    if (mapping->action->type == POPPLER_ACTION_LAUNCH) {
      out.push_back(mapping->action);
    }
  }

  poppler_page_free_link_mapping(mappings);
  g_object_unref(page);
  return out;
}

// Minimal PDF with 1 page and 3 /Link annotations.
//  1) /Launch with /F (test.txt) and /Win << /P (param) >>
//  2) /Launch with /F (onlyfile.txt) and no params
//  3) /Launch with empty /F () and empty params /P ()
static std::string BuildPdfWithLaunchLinks() {
  // Note: This is a purposely small, hand-written PDF intended to be parseable by Poppler.
  // We avoid relying on any internal behavior beyond what Poppler exposes via the public GLib API.
  return std::string(
      "%PDF-1.4\n"
      "1 0 obj\n"
      "<< /Type /Catalog /Pages 2 0 R >>\n"
      "endobj\n"
      "2 0 obj\n"
      "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      "endobj\n"
      "3 0 obj\n"
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792]\n"
      "   /Annots [4 0 R 5 0 R 6 0 R]\n"
      "   /Contents 7 0 R\n"
      "   /Resources << >>\n"
      ">>\n"
      "endobj\n"
      "4 0 obj\n"
      "<< /Type /Annot /Subtype /Link /Rect [10 10 110 40] /Border [0 0 0]\n"
      "   /A << /S /Launch /F (test.txt) /Win << /P (param) >> >>\n"
      ">>\n"
      "endobj\n"
      "5 0 obj\n"
      "<< /Type /Annot /Subtype /Link /Rect [10 50 110 80] /Border [0 0 0]\n"
      "   /A << /S /Launch /F (onlyfile.txt) >>\n"
      ">>\n"
      "endobj\n"
      "6 0 obj\n"
      "<< /Type /Annot /Subtype /Link /Rect [10 90 110 120] /Border [0 0 0]\n"
      "   /A << /S /Launch /F () /Win << /P () >> >>\n"
      ">>\n"
      "endobj\n"
      "7 0 obj\n"
      "<< /Length 0 >>\n"
      "stream\n"
      "endstream\n"
      "endobj\n"
      "xref\n"
      "0 8\n"
      "0000000000 65535 f \n"
      "trailer\n"
      "<< /Size 8 /Root 1 0 R >>\n"
      "startxref\n"
      "0\n"
      "%%EOF\n");
}

class PopplerBuildLaunchTest_2293 : public ::testing::Test {};

}  // namespace

TEST_F(PopplerBuildLaunchTest_2293, LaunchActionSetsFileNameAndParams_2293) {
  const TempPdf pdf = WriteTempPdf(BuildPdfWithLaunchLinks());
  ASSERT_FALSE(pdf.uri.empty());

  PopplerDocument *doc = OpenDocOrFail(pdf.uri);
  ASSERT_NE(doc, nullptr);

  const auto actions = GetLaunchActionsFromFirstPage(doc);
  ASSERT_GE(actions.size(), 1u);

  bool found = false;
  for (PopplerAction *a : actions) {
    if (!a || a->type != POPPLER_ACTION_LAUNCH)
      continue;

    // We expect at least one launch action with both file_name and params set.
    if (a->launch.file_name && a->launch.params &&
        std::string(a->launch.file_name) == "test.txt" &&
        std::string(a->launch.params) == "param") {
      found = true;
      break;
    }
  }

  EXPECT_TRUE(found);

  g_object_unref(doc);
  g_remove(pdf.path.c_str());
}

TEST_F(PopplerBuildLaunchTest_2293, LaunchActionWithOnlyFileNameLeavesParamsNull_2293) {
  const TempPdf pdf = WriteTempPdf(BuildPdfWithLaunchLinks());
  ASSERT_FALSE(pdf.uri.empty());

  PopplerDocument *doc = OpenDocOrFail(pdf.uri);
  ASSERT_NE(doc, nullptr);

  const auto actions = GetLaunchActionsFromFirstPage(doc);
  ASSERT_GE(actions.size(), 1u);

  bool found = false;
  for (PopplerAction *a : actions) {
    if (!a || a->type != POPPLER_ACTION_LAUNCH)
      continue;

    if (a->launch.file_name && std::string(a->launch.file_name) == "onlyfile.txt") {
      // build_launch only sets params if link->getParams() is non-null.
      EXPECT_TRUE(a->launch.params == nullptr || std::string(a->launch.params).empty());
      found = true;
      break;
    }
  }

  EXPECT_TRUE(found);

  g_object_unref(doc);
  g_remove(pdf.path.c_str());
}

TEST_F(PopplerBuildLaunchTest_2293, LaunchActionWithEmptyStringsProducesEmptyUtf8Strings_2293) {
  const TempPdf pdf = WriteTempPdf(BuildPdfWithLaunchLinks());
  ASSERT_FALSE(pdf.uri.empty());

  PopplerDocument *doc = OpenDocOrFail(pdf.uri);
  ASSERT_NE(doc, nullptr);

  const auto actions = GetLaunchActionsFromFirstPage(doc);
  ASSERT_GE(actions.size(), 1u);

  bool found = false;
  for (PopplerAction *a : actions) {
    if (!a || a->type != POPPLER_ACTION_LAUNCH)
      continue;

    // Third annotation uses /F () and /P () which should be observable as empty strings if parsed.
    if (a->launch.file_name && std::string(a->launch.file_name).empty()) {
      EXPECT_NE(a->launch.file_name, nullptr);
      if (a->launch.params) {
        EXPECT_TRUE(std::string(a->launch.params).empty());
      }
      found = true;
      break;
    }
  }

  EXPECT_TRUE(found);

  g_object_unref(doc);
  g_remove(pdf.path.c_str());
}

TEST_F(PopplerBuildLaunchTest_2293, OpenNonexistentFileReturnsNullAndSetsError_2293) {
  // Error case observable through public interface: opening a missing file should fail.
  GError *error = nullptr;
  PopplerDocument *doc =
      poppler_document_new_from_file("file:///this/path/should/not/exist_2293.pdf", nullptr, &error);

  EXPECT_EQ(doc, nullptr);
  EXPECT_NE(error, nullptr);
  if (error)
    g_error_free(error);
}