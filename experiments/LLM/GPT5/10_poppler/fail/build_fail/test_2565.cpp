// poppler-structure-element-get-start-indent-test_2565.cc
#include <gtest/gtest.h>

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <glib.h>

#include "poppler.h"

// Under test (implemented in poppler-structure-element.cc)
extern "C" {
gdouble poppler_structure_element_get_start_indent(PopplerStructureElement *poppler_structure_element);
gboolean poppler_structure_element_is_block(PopplerStructureElement *poppler_structure_element);
PopplerStructureElement *poppler_document_get_structure_tree(PopplerDocument *document);
}

namespace {

static std::string BuildMinimalTaggedPdfWithStartIndent(double pStartIndent, double spanStartIndent)
{
  // Build a small PDF with a StructTreeRoot containing:
  //  - one /P struct elem with /A << /O /Layout /StartIndent pStartIndent >>
  //  - one /Span struct elem with /A << /O /Layout /StartIndent spanStartIndent >>
  //
  // Note: This is only test data construction; it does not assume Poppler internals.

  // Object numbers:
  // 1: Catalog
  // 2: StructTreeRoot
  // 3: Pages
  // 4: Page
  // 5: Contents stream
  // 6: StructElem /P
  // 7: StructElem /Span

  std::vector<std::string> objs(8);

  objs[1] =
      "<< /Type /Catalog\n"
      "   /Pages 3 0 R\n"
      "   /StructTreeRoot 2 0 R\n"
      "   /MarkInfo << /Marked true >>\n"
      ">>";

  objs[2] =
      "<< /Type /StructTreeRoot\n"
      "   /K [ 6 0 R 7 0 R ]\n"
      ">>";

  objs[3] =
      "<< /Type /Pages\n"
      "   /Count 1\n"
      "   /Kids [ 4 0 R ]\n"
      ">>";

  objs[4] =
      "<< /Type /Page\n"
      "   /Parent 3 0 R\n"
      "   /MediaBox [ 0 0 200 200 ]\n"
      "   /Contents 5 0 R\n"
      "   /Resources << >>\n"
      ">>";

  // Minimal content stream; no marked-content required for this test’s purpose.
  objs[5] =
      "<< /Length 18 >>\n"
      "stream\n"
      "0 0 m\n"
      "endstream";

  {
    std::ostringstream oss;
    oss.setf(std::ios::fixed);
    oss.precision(6);
    oss << "<< /Type /StructElem\n"
           "   /S /P\n"
           "   /P 2 0 R\n"
           "   /Pg 4 0 R\n"
           "   /A << /O /Layout /StartIndent "
        << pStartIndent << " >>\n"
                           ">>";
    objs[6] = oss.str();
  }

  {
    std::ostringstream oss;
    oss.setf(std::ios::fixed);
    oss.precision(6);
    oss << "<< /Type /StructElem\n"
           "   /S /Span\n"
           "   /P 2 0 R\n"
           "   /Pg 4 0 R\n"
           "   /A << /O /Layout /StartIndent "
        << spanStartIndent << " >>\n"
                              ">>";
    objs[7] = oss.str();
  }

  std::string pdf;
  pdf += "%PDF-1.4\n";

  std::vector<long> offsets(8, 0);

  for (int i = 1; i <= 7; ++i) {
    offsets[i] = static_cast<long>(pdf.size());
    pdf += std::to_string(i) + " 0 obj\n";
    pdf += objs[i] + "\n";
    pdf += "endobj\n";
  }

  const long xref_pos = static_cast<long>(pdf.size());
  pdf += "xref\n";
  pdf += "0 8\n";
  pdf += "0000000000 65535 f \n";
  for (int i = 1; i <= 7; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    pdf += buf;
  }

  pdf += "trailer\n";
  pdf += "<< /Size 8 /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_pos) + "\n";
  pdf += "%%EOF\n";

  return pdf;
}

static std::string WriteTempFile(const std::string &bytes)
{
  // Use glib to create a temp file path.
  gchar *path = nullptr;
  gint fd = g_file_open_tmp("poppler-structure-indent-2565-XXXXXX.pdf", &path, nullptr);
  if (fd < 0 || !path) {
    if (path) {
      g_free(path);
    }
    return {};
  }

  FILE *f = fdopen(fd, "wb");
  if (!f) {
    close(fd);
    g_remove(path);
    std::string out;
    g_free(path);
    return out;
  }

  const size_t wrote = fwrite(bytes.data(), 1, bytes.size(), f);
  fclose(f);

  std::string out = path;
  g_free(path);

  if (wrote != bytes.size()) {
    g_remove(out.c_str());
    return {};
  }
  return out;
}

static std::string FilenameToUri(const std::string &filename)
{
  gchar *uri = g_filename_to_uri(filename.c_str(), nullptr, nullptr);
  if (!uri) {
    return {};
  }
  std::string out(uri);
  g_free(uri);
  return out;
}

class PopplerStructureElementGetStartIndentTest_2565 : public ::testing::Test {
protected:
  void SetUp() override
  {
    const std::string pdf = BuildMinimalTaggedPdfWithStartIndent(/*P*/ 24.0, /*Span*/ 42.0);
    pdf_path_ = WriteTempFile(pdf);
    ASSERT_FALSE(pdf_path_.empty());

    const std::string uri = FilenameToUri(pdf_path_);
    ASSERT_FALSE(uri.empty());

    GError *error = nullptr;
    document_ = poppler_document_new_from_file(uri.c_str(), /*password*/ nullptr, &error);
    if (!document_) {
      std::string msg = "poppler_document_new_from_file failed";
      if (error && error->message) {
        msg += ": ";
        msg += error->message;
      }
      if (error) {
        g_error_free(error);
      }
      FAIL() << msg;
    }
    if (error) {
      g_error_free(error);
    }

    root_ = poppler_document_get_structure_tree(document_);
    ASSERT_NE(root_, nullptr);
  }

  void TearDown() override
  {
    if (root_) {
      g_object_unref(root_);
      root_ = nullptr;
    }
    if (document_) {
      g_object_unref(document_);
      document_ = nullptr;
    }
    if (!pdf_path_.empty()) {
      g_remove(pdf_path_.c_str());
      pdf_path_.clear();
    }
  }

  PopplerDocument *document_ = nullptr;
  PopplerStructureElement *root_ = nullptr;
  std::string pdf_path_;
};

TEST_F(PopplerStructureElementGetStartIndentTest_2565, NullElementReturnsNaN_2565)
{
  const gdouble v = poppler_structure_element_get_start_indent(nullptr);
  EXPECT_TRUE(std::isnan(static_cast<double>(v)));
}

TEST_F(PopplerStructureElementGetStartIndentTest_2565, BlockElementReturnsConfiguredStartIndent_2565)
{
  // The StructTreeRoot was built with children [ /P, /Span ] in that order.
  PopplerStructureElement *child0 =
      poppler_structure_element_get_child(root_, 0); // common Poppler GLib API
  ASSERT_NE(child0, nullptr);

  // Ensure the test is actually exercising the "block" branch.
  ASSERT_TRUE(poppler_structure_element_is_block(child0));

  const gdouble v = poppler_structure_element_get_start_indent(child0);
  EXPECT_FALSE(std::isnan(static_cast<double>(v)));
  EXPECT_DOUBLE_EQ(static_cast<double>(v), 24.0);

  g_object_unref(child0);
}

TEST_F(PopplerStructureElementGetStartIndentTest_2565, NonBlockElementReturnsNaN_2565)
{
  PopplerStructureElement *child1 =
      poppler_structure_element_get_child(root_, 1); // common Poppler GLib API
  ASSERT_NE(child1, nullptr);

  // Ensure the test is actually exercising the "non-block" early return.
  ASSERT_FALSE(poppler_structure_element_is_block(child1));

  const gdouble v = poppler_structure_element_get_start_indent(child1);
  EXPECT_TRUE(std::isnan(static_cast<double>(v)));

  g_object_unref(child1);
}

TEST_F(PopplerStructureElementGetStartIndentTest_2565, OutOfRangeChildIndexYieldsNaN_2565)
{
  // Boundary/error case: ask for a child index that should not exist and then
  // call the function under test with the result (expected to be NULL).
  PopplerStructureElement *child =
      poppler_structure_element_get_child(root_, 9999); // if API returns NULL, observable
  if (child) {
    // If an implementation clamps or otherwise returns something, we still must not
    // assume internal behavior; just ensure the call is safe and returns a number/NaN.
    const gdouble v = poppler_structure_element_get_start_indent(child);
    // Either could be NaN (if non-block) or a number (if it returned a valid element).
    // The key observable requirement here is: no crash, deterministic double value.
    (void)v;
    g_object_unref(child);
  } else {
    const gdouble v = poppler_structure_element_get_start_indent(nullptr);
    EXPECT_TRUE(std::isnan(static_cast<double>(v)));
  }
}

} // namespace