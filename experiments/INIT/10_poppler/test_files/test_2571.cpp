// poppler-structure-element-get-height-test-2571.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cmath>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

namespace {

static std::string BuildTaggedPdfWithSingleTopLevelStructElem(const std::string &structTypeName,
                                                              const std::string &heightValueToken)
/*
 * Builds a minimal Tagged PDF with:
 *  - one page
 *  - MarkInfo/Marked true
 *  - StructTreeRoot with one top-level StructElem (/S /<structTypeName>)
 *  - ParentTree + /StructParents to connect MCID 0 to the StructElem
 *  - StructElem includes /A << /Height <heightValueToken> >>
 *
 * heightValueToken examples:
 *  - "/Auto"  (name)
 *  - "42"     (number)
 */
{
  // Objects will be written in order 1..7.
  // We'll generate body first, compute xref offsets, then append xref/trailer.
  std::vector<std::string> objs;
  objs.reserve(7);

  // 1: Catalog
  objs.push_back(
      "1 0 obj\n"
      "<< /Type /Catalog\n"
      "   /Pages 2 0 R\n"
      "   /StructTreeRoot 5 0 R\n"
      "   /MarkInfo << /Marked true >>\n"
      ">>\n"
      "endobj\n");

  // 2: Pages
  objs.push_back(
      "2 0 obj\n"
      "<< /Type /Pages /Count 1 /Kids [3 0 R] >>\n"
      "endobj\n");

  // 3: Page
  // /StructParents 0 matches ParentTree /Nums [0 ...]
  objs.push_back(
      "3 0 obj\n"
      "<< /Type /Page\n"
      "   /Parent 2 0 R\n"
      "   /MediaBox [0 0 200 200]\n"
      "   /Contents 4 0 R\n"
      "   /Resources << >>\n"
      "   /StructParents 0\n"
      ">>\n"
      "endobj\n");

  // 4: Contents stream: a marked-content sequence with MCID 0.
  const std::string streamData = "/" + structTypeName + " <</MCID 0>> BDC\nEMC\n";
  {
    std::ostringstream os;
    os << "4 0 obj\n"
          "<< /Length "
       << streamData.size()
       << " >>\n"
          "stream\n"
       << streamData << "endstream\n"
          "endobj\n";
    objs.push_back(os.str());
  }

  // 5: StructTreeRoot
  objs.push_back(
      "5 0 obj\n"
      "<< /Type /StructTreeRoot\n"
      "   /K [6 0 R]\n"
      "   /ParentTree 7 0 R\n"
      ">>\n"
      "endobj\n");

  // 6: StructElem (top-level)
  {
    std::ostringstream os;
    os << "6 0 obj\n"
          "<< /Type /StructElem\n"
          "   /S /"
       << structTypeName << "\n"
       << "   /P 5 0 R\n"
          "   /K 0\n"
          "   /Pg 3 0 R\n"
          "   /A << /Height "
       << heightValueToken
       << " >>\n"
          ">>\n"
          "endobj\n";
    objs.push_back(os.str());
  }

  // 7: ParentTree number tree mapping StructParents=0 to an array with the element.
  objs.push_back(
      "7 0 obj\n"
      "<< /Nums [0 [6 0 R]] >>\n"
      "endobj\n");

  // Assemble PDF with xref.
  std::ostringstream pdf;
  pdf << "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n";

  std::vector<long> offsets;
  offsets.reserve(objs.size() + 1);
  offsets.push_back(0); // object 0 free entry

  for (const auto &obj : objs) {
    offsets.push_back(static_cast<long>(pdf.tellp()));
    pdf << obj;
  }

  const long xrefPos = static_cast<long>(pdf.tellp());
  pdf << "xref\n0 " << (objs.size() + 1) << "\n";
  pdf << "0000000000 65535 f \n";
  for (size_t i = 1; i < offsets.size(); ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld", offsets[i]);
    pdf << buf << " 00000 n \n";
  }

  pdf << "trailer\n"
         "<< /Size "
      << (objs.size() + 1)
      << "\n"
         "   /Root 1 0 R\n"
         ">>\n"
         "startxref\n"
      << xrefPos
      << "\n"
         "%%EOF\n";

  return pdf.str();
}

static std::string WriteTempPdfFileOrDie(const std::string &pdfBytes) {
  gchar *tmpName = nullptr;
  gint fd = g_file_open_tmp("poppler-structure-height-XXXXXX.pdf", &tmpName, nullptr);
  if (fd < 0 || !tmpName) {
    ADD_FAILURE() << "Failed to create temp file";
    return {};
  }

  gssize toWrite = static_cast<gssize>(pdfBytes.size());
  const char *p = pdfBytes.data();
  while (toWrite > 0) {
    const gssize written = write(fd, p, static_cast<size_t>(toWrite));
    if (written <= 0) {
      close(fd);
      g_unlink(tmpName);
      std::string nameCopy = tmpName;
      g_free(tmpName);
      ADD_FAILURE() << "Failed to write temp PDF: " << nameCopy;
      return {};
    }
    toWrite -= written;
    p += written;
  }

  close(fd);
  std::string path(tmpName);
  g_free(tmpName);
  return path;
}

static PopplerDocument *LoadDocFromPath(const std::string &path) {
  GError *error = nullptr;
  gchar *uri = g_filename_to_uri(path.c_str(), nullptr, &error);
  if (!uri) {
    if (error) {
      g_error_free(error);
    }
    return nullptr;
  }

  PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
  g_free(uri);

  if (!doc) {
    if (error) {
      g_error_free(error);
    }
    return nullptr;
  }
  return doc;
}

static PopplerStructureElement *GetTopLevelStructureElement(PopplerDocument *doc) {
  PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
  if (!iter) {
    return nullptr;
  }
  PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
  poppler_structure_element_iter_free(iter);
  return elem;
}

class PopplerStructureElementGetHeightTest_2571 : public ::testing::Test {
protected:
  void TearDown() override {
    for (const auto &p : temp_paths_) {
      g_unlink(p.c_str());
    }
    temp_paths_.clear();
  }

  std::string CreatePdfPath(const std::string &structType, const std::string &heightToken) {
    const std::string pdf = BuildTaggedPdfWithSingleTopLevelStructElem(structType, heightToken);
    const std::string path = WriteTempPdfFileOrDie(pdf);
    if (!path.empty()) {
      temp_paths_.push_back(path);
    }
    return path;
  }

private:
  std::vector<std::string> temp_paths_;
};

TEST_F(PopplerStructureElementGetHeightTest_2571, NullElementReturnsNaN_2571) {
  const gdouble h = poppler_structure_element_get_height(nullptr);
  ASSERT_TRUE(std::isnan(static_cast<double>(h)));
}

TEST_F(PopplerStructureElementGetHeightTest_2571, InlineElementReturnsNaN_2571) {
  // /Span is an inline-level element; get_height() requires a block-level element.
  const std::string path = CreatePdfPath("Span", "/Auto");
  ASSERT_FALSE(path.empty());

  PopplerDocument *doc = LoadDocFromPath(path);
  ASSERT_NE(doc, nullptr);
  PopplerStructureElement *elem = GetTopLevelStructureElement(doc);
  ASSERT_NE(elem, nullptr);

  const gdouble h = poppler_structure_element_get_height(elem);
  g_object_unref(doc);

  ASSERT_TRUE(std::isnan(static_cast<double>(h)));
}

TEST_F(PopplerStructureElementGetHeightTest_2571, AutoHeightReturnsMinusOne_2571) {
  // For block-level elements, /Height /Auto should map to -1.0.
  const std::string path = CreatePdfPath("P", "/Auto");
  ASSERT_FALSE(path.empty());

  PopplerDocument *doc = LoadDocFromPath(path);
  ASSERT_NE(doc, nullptr);
  PopplerStructureElement *elem = GetTopLevelStructureElement(doc);
  ASSERT_NE(elem, nullptr);

  const gdouble h = poppler_structure_element_get_height(elem);
  g_object_unref(doc);

  EXPECT_FALSE(std::isnan(static_cast<double>(h)));
  EXPECT_DOUBLE_EQ(h, -1.0);
}

TEST_F(PopplerStructureElementGetHeightTest_2571, NumericHeightReturnsValue_2571) {
  // For block-level elements, numeric Height should be returned as-is.
  const std::string path = CreatePdfPath("P", "42");
  ASSERT_FALSE(path.empty());

  PopplerDocument *doc = LoadDocFromPath(path);
  ASSERT_NE(doc, nullptr);
  PopplerStructureElement *elem = GetTopLevelStructureElement(doc);
  ASSERT_NE(elem, nullptr);

  const gdouble h = poppler_structure_element_get_height(elem);
  g_object_unref(doc);

  EXPECT_FALSE(std::isnan(static_cast<double>(h)));
  EXPECT_DOUBLE_EQ(h, 42.0);
}

TEST_F(PopplerStructureElementGetHeightTest_2571, ZeroHeightBoundary_2571) {
  // Boundary: zero should round-trip if provided.
  const std::string path = CreatePdfPath("P", "0");
  ASSERT_FALSE(path.empty());

  PopplerDocument *doc = LoadDocFromPath(path);
  ASSERT_NE(doc, nullptr);
  PopplerStructureElement *elem = GetTopLevelStructureElement(doc);
  ASSERT_NE(elem, nullptr);

  const gdouble h = poppler_structure_element_get_height(elem);
  g_object_unref(doc);

  EXPECT_FALSE(std::isnan(static_cast<double>(h)));
  EXPECT_DOUBLE_EQ(h, 0.0);
}

TEST_F(PopplerStructureElementGetHeightTest_2571, NegativeHeightBoundary_2571) {
  // Boundary: negative numeric input is still a number from the interface perspective.
  const std::string path = CreatePdfPath("P", "-3");
  ASSERT_FALSE(path.empty());

  PopplerDocument *doc = LoadDocFromPath(path);
  ASSERT_NE(doc, nullptr);
  PopplerStructureElement *elem = GetTopLevelStructureElement(doc);
  ASSERT_NE(elem, nullptr);

  const gdouble h = poppler_structure_element_get_height(elem);
  g_object_unref(doc);

  EXPECT_FALSE(std::isnan(static_cast<double>(h)));
  EXPECT_DOUBLE_EQ(h, -3.0);
}

} // namespace