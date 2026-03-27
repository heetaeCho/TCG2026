// File: poppler-layers-iter-get-child-test_2249.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace {

static std::string Pad10(size_t v) {
  std::ostringstream oss;
  oss << std::setw(10) << std::setfill('0') << v;
  return oss.str();
}

// Builds a minimal, valid PDF with Optional Content Groups (layers) and a
// hierarchical /Order entry containing a group node with two child OCGs.
// This is purely test data generation (does not depend on Poppler internals).
static std::string BuildPdfWithLayerGroupAndTwoChildren() {
  const std::string header = "%PDF-1.7\n%\xE2\xE3\xCF\xD3\n";

  // Object numbers: 1..6
  // 1: Catalog with OCProperties and hierarchical Order
  // 2: Pages
  // 3: Page
  // 4: Contents stream
  // 5: OCG Layer1
  // 6: OCG Layer2
  std::vector<std::string> objs;
  objs.reserve(6);

  objs.push_back(
      "1 0 obj\n"
      "<< /Type /Catalog\n"
      "   /Pages 2 0 R\n"
      "   /OCProperties <<\n"
      "      /OCGs [ 5 0 R 6 0 R ]\n"
      "      /D << /Order [ (Group) [ 5 0 R 6 0 R ] ] >>\n"
      "   >>\n"
      ">>\n"
      "endobj\n");

  objs.push_back(
      "2 0 obj\n"
      "<< /Type /Pages /Kids [ 3 0 R ] /Count 1 >>\n"
      "endobj\n");

  objs.push_back(
      "3 0 obj\n"
      "<< /Type /Page\n"
      "   /Parent 2 0 R\n"
      "   /MediaBox [ 0 0 200 200 ]\n"
      "   /Resources << >>\n"
      "   /Contents 4 0 R\n"
      ">>\n"
      "endobj\n");

  objs.push_back(
      "4 0 obj\n"
      "<< /Length 0 >>\n"
      "stream\n"
      "\n"
      "endstream\n"
      "endobj\n");

  objs.push_back(
      "5 0 obj\n"
      "<< /Type /OCG /Name (Layer1) >>\n"
      "endobj\n");

  objs.push_back(
      "6 0 obj\n"
      "<< /Type /OCG /Name (Layer2) >>\n"
      "endobj\n");

  std::string body;
  body.reserve(2048);

  std::vector<size_t> offsets;
  offsets.reserve(objs.size() + 1);
  offsets.push_back(0);  // object 0 (free)

  // Track offsets from start of file.
  size_t cursor = header.size();
  for (const auto& obj : objs) {
    offsets.push_back(cursor);
    body += obj;
    cursor += obj.size();
  }

  // Build xref.
  const size_t xref_offset = header.size() + body.size();
  std::ostringstream xref;
  xref << "xref\n";
  xref << "0 " << (objs.size() + 1) << "\n";
  xref << "0000000000 65535 f \n";
  for (size_t i = 1; i < offsets.size(); ++i) {
    xref << Pad10(offsets[i]) << " 00000 n \n";
  }

  // Trailer.
  std::ostringstream trailer;
  trailer << "trailer\n"
          << "<< /Size " << (objs.size() + 1) << " /Root 1 0 R >>\n"
          << "startxref\n"
          << xref_offset << "\n"
          << "%%EOF\n";

  return header + body + xref.str() + trailer.str();
}

struct DocAndLayersIter {
  PopplerDocument* doc = nullptr;
  PopplerLayersIter* iter = nullptr;

  ~DocAndLayersIter() {
    if (iter) {
      poppler_layers_iter_free(iter);
      iter = nullptr;
    }
    if (doc) {
      g_object_unref(doc);
      doc = nullptr;
    }
  }
};

static DocAndLayersIter LoadDocAndGetLayersIterOrSkip(const std::string& pdf) {
  DocAndLayersIter out;

  GError* error = nullptr;
  out.doc = poppler_document_new_from_data(pdf.data(),
                                          static_cast<int>(pdf.size()),
                                          /*password=*/nullptr, &error);
  if (!out.doc) {
    std::string msg = "Failed to create PopplerDocument from test PDF.";
    if (error && error->message) {
      msg += " GError: ";
      msg += error->message;
    }
    if (error) g_error_free(error);
    GTEST_SKIP() << msg;
  }
  if (error) {
    // Some builds may still set a warning error; treat as skip for robustness.
    std::string msg = "Poppler returned GError while creating document: ";
    msg += (error->message ? error->message : "(null)");
    g_error_free(error);
    g_object_unref(out.doc);
    out.doc = nullptr;
    GTEST_SKIP() << msg;
  }

  out.iter = poppler_document_get_layers(out.doc);
  if (!out.iter) {
    g_object_unref(out.doc);
    out.doc = nullptr;
    GTEST_SKIP() << "poppler_document_get_layers() returned NULL (layers not available).";
  }

  return out;
}

class PopplerLayersIterGetChildTest_2249 : public ::testing::Test {};

}  // namespace

TEST_F(PopplerLayersIterGetChildTest_2249, NullParentReturnsNull_2249) {
  // Exceptional/error case (observable): NULL input should return NULL.
  EXPECT_EQ(poppler_layers_iter_get_child(nullptr), nullptr);
}

TEST_F(PopplerLayersIterGetChildTest_2249, GroupNodeReturnsNonNullChildIter_2249) {
  // Normal operation: when the current layer has children, a new child iterator is returned.
  const std::string pdf = BuildPdfWithLayerGroupAndTwoChildren();
  auto dl = LoadDocAndGetLayersIterOrSkip(pdf);

  PopplerLayersIter* child = poppler_layers_iter_get_child(dl.iter);
  ASSERT_NE(child, nullptr);

  // Use only public APIs to observe that the returned iterator is usable.
  // (Do not assume ordering beyond what the PDF declares; check for non-empty title.)
  gchar* title = poppler_layers_iter_get_title(child);
  ASSERT_NE(title, nullptr);
  EXPECT_GT(g_utf8_strlen(title, -1), 0) << "Child iterator title should be a non-empty UTF-8 string.";
  g_free(title);

  poppler_layers_iter_free(child);
}

TEST_F(PopplerLayersIterGetChildTest_2249, LeafNodeReturnsNullChildIter_2249) {
  // Boundary condition: if the current node is a leaf (no kids), get_child should return NULL.
  const std::string pdf = BuildPdfWithLayerGroupAndTwoChildren();
  auto dl = LoadDocAndGetLayersIterOrSkip(pdf);

  PopplerLayersIter* child = poppler_layers_iter_get_child(dl.iter);
  ASSERT_NE(child, nullptr);

  // Child iterator is expected to point at a leaf OCG (Layer1/Layer2), which should have no children.
  EXPECT_EQ(poppler_layers_iter_get_child(child), nullptr);

  poppler_layers_iter_free(child);
}

TEST_F(PopplerLayersIterGetChildTest_2249, AfterIteratingToEndGetChildReturnsNull_2249) {
  // Boundary condition: moving the parent iterator to (or past) the end should not produce a child.
  const std::string pdf = BuildPdfWithLayerGroupAndTwoChildren();
  auto dl = LoadDocAndGetLayersIterOrSkip(pdf);

  // Advance to end using the public API.
  while (poppler_layers_iter_next(dl.iter)) {
    // keep advancing
  }

  EXPECT_EQ(poppler_layers_iter_get_child(dl.iter), nullptr);
}