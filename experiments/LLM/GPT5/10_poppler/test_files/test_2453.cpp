// File: poppler-page-get-link-mapping-test-2453.cc
#include <gtest/gtest.h>

#include <poppler.h>
#include <glib.h>

#include <cmath>
#include <cstdint>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace {

struct PdfRect {
  double x1;
  double y1;
  double x2;
  double y2;
};

static std::string BuildPdfWithOptionalLinks(int rotate_degrees,
                                             const PdfRect* crop_box_or_null,
                                             const std::vector<PdfRect>& link_rects,
                                             const std::vector<std::string>& uris) {
  // Minimal, valid PDF with:
  // 1: Catalog
  // 2: Pages
  // 3: Page (MediaBox, optional CropBox, Rotate, optional Annots)
  // 4.. : Link annotations (one per link)
  // last: URI action objects (one per link)
  //
  // Note: For simplicity, we set MediaBox fixed and ensure provided rects lie within.
  const PdfRect media{0, 0, 200, 200};

  const bool has_links = !link_rects.empty();
  const int link_count = static_cast<int>(link_rects.size());
  const int base_annot_obj = 4;
  const int base_action_obj = base_annot_obj + link_count;
  const int last_obj = base_action_obj + link_count - 1;

  std::vector<std::string> objs;
  objs.reserve(static_cast<size_t>(last_obj));

  // 1 0 obj: Catalog
  {
    std::ostringstream o;
    o << "1 0 obj\n"
      << "<< /Type /Catalog /Pages 2 0 R >>\n"
      << "endobj\n";
    objs.push_back(o.str());
  }

  // 2 0 obj: Pages
  {
    std::ostringstream o;
    o << "2 0 obj\n"
      << "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      << "endobj\n";
    objs.push_back(o.str());
  }

  // 3 0 obj: Page
  {
    std::ostringstream o;
    o << "3 0 obj\n"
      << "<< /Type /Page /Parent 2 0 R\n"
      << "   /MediaBox [" << media.x1 << " " << media.y1 << " " << media.x2 << " " << media.y2
      << "]\n";

    if (crop_box_or_null) {
      const auto& c = *crop_box_or_null;
      o << "   /CropBox [" << c.x1 << " " << c.y1 << " " << c.x2 << " " << c.y2 << "]\n";
    }

    if (rotate_degrees != 0) {
      o << "   /Rotate " << rotate_degrees << "\n";
    }

    if (has_links) {
      o << "   /Annots [";
      for (int i = 0; i < link_count; ++i) {
        o << (base_annot_obj + i) << " 0 R";
        if (i + 1 < link_count) o << " ";
      }
      o << "]\n";
    }

    o << ">>\n"
      << "endobj\n";
    objs.push_back(o.str());
  }

  // Link annotations: 4..(4+link_count-1)
  for (int i = 0; i < link_count; ++i) {
    const auto& r = link_rects[static_cast<size_t>(i)];
    const int annot_obj_num = base_annot_obj + i;
    const int action_obj_num = base_action_obj + i;

    std::ostringstream o;
    o << annot_obj_num << " 0 obj\n"
      << "<< /Type /Annot /Subtype /Link\n"
      << "   /Rect [" << r.x1 << " " << r.y1 << " " << r.x2 << " " << r.y2 << "]\n"
      << "   /Border [0 0 0]\n"
      << "   /A " << action_obj_num << " 0 R\n"
      << ">>\n"
      << "endobj\n";
    objs.push_back(o.str());
  }

  // URI action objects
  for (int i = 0; i < link_count; ++i) {
    const int action_obj_num = base_action_obj + i;
    std::ostringstream o;
    // Escape parentheses minimally for our fixed test URIs (we keep them simple).
    o << action_obj_num << " 0 obj\n"
      << "<< /S /URI /URI (" << uris[static_cast<size_t>(i)] << ") >>\n"
      << "endobj\n";
    objs.push_back(o.str());
  }

  // Build full PDF and xref offsets.
  std::ostringstream pdf;
  pdf << "%PDF-1.4\n";
  std::vector<long> offsets(static_cast<size_t>(last_obj + 1), 0);
  offsets[0] = 0;

  // Objects are in order 1..last_obj
  for (int obj_num = 1; obj_num <= last_obj; ++obj_num) {
    offsets[static_cast<size_t>(obj_num)] = static_cast<long>(pdf.tellp());
    pdf << objs[static_cast<size_t>(obj_num - 1)];
  }

  const long xref_pos = static_cast<long>(pdf.tellp());
  pdf << "xref\n";
  pdf << "0 " << (last_obj + 1) << "\n";
  pdf << "0000000000 65535 f \n";
  for (int obj_num = 1; obj_num <= last_obj; ++obj_num) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld", offsets[static_cast<size_t>(obj_num)]);
    pdf << buf << " 00000 n \n";
  }

  pdf << "trailer\n";
  pdf << "<< /Size " << (last_obj + 1) << " /Root 1 0 R >>\n";
  pdf << "startxref\n";
  pdf << xref_pos << "\n";
  pdf << "%%EOF\n";

  return pdf.str();
}

static std::string BuildPdfNoLinks(int rotate_degrees, const PdfRect* crop_box_or_null) {
  // Like above, but without Annots and action objects.
  const PdfRect media{0, 0, 200, 200};

  std::vector<std::string> objs;
  objs.reserve(3);

  {
    std::ostringstream o;
    o << "1 0 obj\n"
      << "<< /Type /Catalog /Pages 2 0 R >>\n"
      << "endobj\n";
    objs.push_back(o.str());
  }
  {
    std::ostringstream o;
    o << "2 0 obj\n"
      << "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
      << "endobj\n";
    objs.push_back(o.str());
  }
  {
    std::ostringstream o;
    o << "3 0 obj\n"
      << "<< /Type /Page /Parent 2 0 R\n"
      << "   /MediaBox [" << media.x1 << " " << media.y1 << " " << media.x2 << " " << media.y2
      << "]\n";
    if (crop_box_or_null) {
      const auto& c = *crop_box_or_null;
      o << "   /CropBox [" << c.x1 << " " << c.y1 << " " << c.x2 << " " << c.y2 << "]\n";
    }
    if (rotate_degrees != 0) {
      o << "   /Rotate " << rotate_degrees << "\n";
    }
    o << ">>\n"
      << "endobj\n";
    objs.push_back(o.str());
  }

  std::ostringstream pdf;
  pdf << "%PDF-1.4\n";
  std::vector<long> offsets(4, 0);
  for (int obj_num = 1; obj_num <= 3; ++obj_num) {
    offsets[static_cast<size_t>(obj_num)] = static_cast<long>(pdf.tellp());
    pdf << objs[static_cast<size_t>(obj_num - 1)];
  }

  const long xref_pos = static_cast<long>(pdf.tellp());
  pdf << "xref\n0 4\n";
  pdf << "0000000000 65535 f \n";
  for (int obj_num = 1; obj_num <= 3; ++obj_num) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld", offsets[static_cast<size_t>(obj_num)]);
    pdf << buf << " 00000 n \n";
  }
  pdf << "trailer\n<< /Size 4 /Root 1 0 R >>\n";
  pdf << "startxref\n" << xref_pos << "\n%%EOF\n";

  return pdf.str();
}

static std::string WriteTempPdfFile(const std::string& pdf_bytes) {
  gchar* path = nullptr;
  GError* error = nullptr;

  // Create a unique temp file name.
  gint fd = g_file_open_tmp("poppler_link_mapping_XXXXXX.pdf", &path, &error);
  if (fd < 0) {
    std::string msg = error ? error->message : "unknown error";
    if (error) g_error_free(error);
    if (path) g_free(path);
    ADD_FAILURE() << "g_file_open_tmp failed: " << msg;
    return {};
  }

  // Write content.
  const gssize to_write = static_cast<gssize>(pdf_bytes.size());
  gssize written = 0;
  while (written < to_write) {
    const gssize w = ::write(fd, pdf_bytes.data() + written, static_cast<size_t>(to_write - written));
    if (w <= 0) break;
    written += w;
  }
  ::close(fd);

  std::string out = path ? path : "";
  g_free(path);

  if (written != to_write) {
    ADD_FAILURE() << "Failed to write complete PDF to temp file";
    return {};
  }
  return out;
}

static std::string ToFileUri(const std::string& path) {
  gchar* uri = g_filename_to_uri(path.c_str(), nullptr, nullptr);
  std::string s = uri ? uri : "";
  g_free(uri);
  return s;
}

static PopplerDocument* LoadDocumentOrFail(const std::string& file_uri) {
  GError* error = nullptr;
  PopplerDocument* doc = poppler_document_new_from_file(file_uri.c_str(), /*password=*/nullptr, &error);
  if (!doc) {
    std::string msg = error ? error->message : "unknown error";
    if (error) g_error_free(error);
    ADD_FAILURE() << "Failed to load PDF: " << msg;
  }
  return doc;
}

static PopplerPage* GetFirstPageOrFail(PopplerDocument* doc) {
  PopplerPage* page = poppler_document_get_page(doc, 0);
  if (!page) {
    ADD_FAILURE() << "poppler_document_get_page returned NULL";
  }
  return page;
}

static int GListLength(GList* list) {
  int n = 0;
  for (GList* it = list; it != nullptr; it = it->next) ++n;
  return n;
}

static PopplerLinkMapping* FindMappingByUri(GList* list, const char* uri) {
  for (GList* it = list; it != nullptr; it = it->next) {
    auto* mapping = static_cast<PopplerLinkMapping*>(it->data);
    if (!mapping || !mapping->action) continue;
    if (mapping->action->type != POPPLER_ACTION_URI) continue;
    if (!mapping->action->uri.uri) continue;
    if (g_strcmp0(mapping->action->uri.uri, uri) == 0) return mapping;
  }
  return nullptr;
}

static void ExpectRectNear(const PopplerRectangle& got, const PdfRect& exp, double eps = 1e-6) {
  EXPECT_NEAR(got.x1, exp.x1, eps);
  EXPECT_NEAR(got.y1, exp.y1, eps);
  EXPECT_NEAR(got.x2, exp.x2, eps);
  EXPECT_NEAR(got.y2, exp.y2, eps);
}

// Compute the expected mapping rectangle using only public information that is observable:
// - crop offset
// - page size from poppler_page_get_size()
// - rotation (known from how the PDF was authored)
//
// This matches the externally visible coordinate results for link mapping.
static PdfRect ExpectedAreaForRotation(int rotate_degrees,
                                       const PdfRect& crop_box,
                                       const PdfRect& link_rect_in_pdf_space,
                                       double page_width,
                                       double page_height) {
  // Apply crop offset first (observable: crop affects coordinates).
  const double rx1 = link_rect_in_pdf_space.x1 - crop_box.x1;
  const double rx2 = link_rect_in_pdf_space.x2 - crop_box.x1;
  const double ry1 = link_rect_in_pdf_space.y1 - crop_box.y1;
  const double ry2 = link_rect_in_pdf_space.y2 - crop_box.y1;

  PdfRect out{};

  switch (rotate_degrees) {
    case 90:
      out.x1 = ry1;
      out.y1 = page_height - rx2;
      out.x2 = out.x1 + (ry2 - ry1);
      out.y2 = out.y1 + (rx2 - rx1);
      break;
    case 180:
      out.x1 = page_width - rx2;
      out.y1 = page_height - ry2;
      out.x2 = out.x1 + (rx2 - rx1);
      out.y2 = out.y1 + (ry2 - ry1);
      break;
    case 270:
      out.x1 = page_width - ry2;
      out.y1 = rx1;
      out.x2 = out.x1 + (ry2 - ry1);
      out.y2 = out.y1 + (rx2 - rx1);
      break;
    default:
      out.x1 = rx1;
      out.y1 = ry1;
      out.x2 = rx2;
      out.y2 = ry2;
      break;
  }
  return out;
}

class PopplerPageGetLinkMappingTest_2453 : public ::testing::Test {
 protected:
  void TearDown() override {
    for (const auto& p : temp_paths_) {
      if (!p.empty()) {
        g_remove(p.c_str());
      }
    }
  }

  std::string MakeTempPdf(const std::string& bytes) {
    std::string path = WriteTempPdfFile(bytes);
    temp_paths_.push_back(path);
    return path;
  }

 private:
  std::vector<std::string> temp_paths_;
};

}  // namespace

TEST_F(PopplerPageGetLinkMappingTest_2453, NullPageReturnsNull_2453) {
  // g_return_val_if_fail() typically logs a critical message; we only assert return value.
  GList* list = poppler_page_get_link_mapping(nullptr);
  EXPECT_EQ(list, nullptr);
}

TEST_F(PopplerPageGetLinkMappingTest_2453, PageWithNoLinksReturnsNull_2453) {
  const PdfRect crop{10, 10, 190, 190};
  const std::string pdf = BuildPdfNoLinks(/*rotate_degrees=*/0, &crop);
  const std::string path = MakeTempPdf(pdf);
  ASSERT_FALSE(path.empty());

  const std::string uri = ToFileUri(path);
  ASSERT_FALSE(uri.empty());

  PopplerDocument* doc = LoadDocumentOrFail(uri);
  ASSERT_NE(doc, nullptr);
  PopplerPage* page = GetFirstPageOrFail(doc);
  ASSERT_NE(page, nullptr);

  GList* list = poppler_page_get_link_mapping(page);
  EXPECT_EQ(list, nullptr);

  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageGetLinkMappingTest_2453, SingleLinkRotate0AppliesCropOffsetAndHasUriAction_2453) {
  const PdfRect crop{10, 20, 190, 180};
  const PdfRect link_rect{30, 60, 80, 90};
  const std::string kUri = "http://example.com/a";

  const std::string pdf =
      BuildPdfWithOptionalLinks(/*rotate_degrees=*/0, &crop, {link_rect}, {kUri});
  const std::string path = MakeTempPdf(pdf);
  ASSERT_FALSE(path.empty());

  PopplerDocument* doc = LoadDocumentOrFail(ToFileUri(path));
  ASSERT_NE(doc, nullptr);
  PopplerPage* page = GetFirstPageOrFail(doc);
  ASSERT_NE(page, nullptr);

  double w = 0, h = 0;
  poppler_page_get_size(page, &w, &h);
  ASSERT_GT(w, 0);
  ASSERT_GT(h, 0);

  GList* list = poppler_page_get_link_mapping(page);
  ASSERT_NE(list, nullptr);
  EXPECT_EQ(GListLength(list), 1);

  PopplerLinkMapping* mapping = FindMappingByUri(list, kUri.c_str());
  ASSERT_NE(mapping, nullptr);
  ASSERT_NE(mapping->action, nullptr);
  EXPECT_EQ(mapping->action->type, POPPLER_ACTION_URI);
  EXPECT_STREQ(mapping->action->uri.uri, kUri.c_str());

  const PdfRect expected = ExpectedAreaForRotation(/*rotate_degrees=*/0, crop, link_rect, w, h);
  ExpectRectNear(mapping->area, expected);

  poppler_page_free_link_mapping(list);
  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageGetLinkMappingTest_2453, SingleLinkRotate90TransformsArea_2453) {
  const PdfRect crop{5, 5, 195, 195};
  const PdfRect link_rect{20, 30, 70, 80};
  const std::string kUri = "http://example.com/r90";

  const std::string pdf =
      BuildPdfWithOptionalLinks(/*rotate_degrees=*/90, &crop, {link_rect}, {kUri});
  const std::string path = MakeTempPdf(pdf);
  ASSERT_FALSE(path.empty());

  PopplerDocument* doc = LoadDocumentOrFail(ToFileUri(path));
  ASSERT_NE(doc, nullptr);
  PopplerPage* page = GetFirstPageOrFail(doc);
  ASSERT_NE(page, nullptr);

  double w = 0, h = 0;
  poppler_page_get_size(page, &w, &h);
  ASSERT_GT(w, 0);
  ASSERT_GT(h, 0);

  GList* list = poppler_page_get_link_mapping(page);
  ASSERT_NE(list, nullptr);
  EXPECT_EQ(GListLength(list), 1);

  PopplerLinkMapping* mapping = FindMappingByUri(list, kUri.c_str());
  ASSERT_NE(mapping, nullptr);

  const PdfRect expected = ExpectedAreaForRotation(/*rotate_degrees=*/90, crop, link_rect, w, h);
  ExpectRectNear(mapping->area, expected);

  poppler_page_free_link_mapping(list);
  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageGetLinkMappingTest_2453, SingleLinkRotate180TransformsArea_2453) {
  const PdfRect crop{12, 8, 188, 192};
  const PdfRect link_rect{40, 50, 90, 70};
  const std::string kUri = "http://example.com/r180";

  const std::string pdf =
      BuildPdfWithOptionalLinks(/*rotate_degrees=*/180, &crop, {link_rect}, {kUri});
  const std::string path = MakeTempPdf(pdf);
  ASSERT_FALSE(path.empty());

  PopplerDocument* doc = LoadDocumentOrFail(ToFileUri(path));
  ASSERT_NE(doc, nullptr);
  PopplerPage* page = GetFirstPageOrFail(doc);
  ASSERT_NE(page, nullptr);

  double w = 0, h = 0;
  poppler_page_get_size(page, &w, &h);
  ASSERT_GT(w, 0);
  ASSERT_GT(h, 0);

  GList* list = poppler_page_get_link_mapping(page);
  ASSERT_NE(list, nullptr);
  EXPECT_EQ(GListLength(list), 1);

  PopplerLinkMapping* mapping = FindMappingByUri(list, kUri.c_str());
  ASSERT_NE(mapping, nullptr);

  const PdfRect expected = ExpectedAreaForRotation(/*rotate_degrees=*/180, crop, link_rect, w, h);
  ExpectRectNear(mapping->area, expected);

  poppler_page_free_link_mapping(list);
  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageGetLinkMappingTest_2453, SingleLinkRotate270TransformsArea_2453) {
  const PdfRect crop{0, 0, 200, 200};
  const PdfRect link_rect{10, 20, 60, 40};
  const std::string kUri = "http://example.com/r270";

  const std::string pdf =
      BuildPdfWithOptionalLinks(/*rotate_degrees=*/270, &crop, {link_rect}, {kUri});
  const std::string path = MakeTempPdf(pdf);
  ASSERT_FALSE(path.empty());

  PopplerDocument* doc = LoadDocumentOrFail(ToFileUri(path));
  ASSERT_NE(doc, nullptr);
  PopplerPage* page = GetFirstPageOrFail(doc);
  ASSERT_NE(page, nullptr);

  double w = 0, h = 0;
  poppler_page_get_size(page, &w, &h);
  ASSERT_GT(w, 0);
  ASSERT_GT(h, 0);

  GList* list = poppler_page_get_link_mapping(page);
  ASSERT_NE(list, nullptr);
  EXPECT_EQ(GListLength(list), 1);

  PopplerLinkMapping* mapping = FindMappingByUri(list, kUri.c_str());
  ASSERT_NE(mapping, nullptr);

  const PdfRect expected = ExpectedAreaForRotation(/*rotate_degrees=*/270, crop, link_rect, w, h);
  ExpectRectNear(mapping->area, expected);

  poppler_page_free_link_mapping(list);
  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageGetLinkMappingTest_2453, MultipleLinksReturnsAllMappingsAndUris_2453) {
  const PdfRect crop{10, 10, 190, 190};
  const PdfRect r1{20, 20, 40, 40};
  const PdfRect r2{60, 70, 90, 110};

  const std::string u1 = "http://example.com/one";
  const std::string u2 = "http://example.com/two";

  const std::string pdf =
      BuildPdfWithOptionalLinks(/*rotate_degrees=*/0, &crop, {r1, r2}, {u1, u2});
  const std::string path = MakeTempPdf(pdf);
  ASSERT_FALSE(path.empty());

  PopplerDocument* doc = LoadDocumentOrFail(ToFileUri(path));
  ASSERT_NE(doc, nullptr);
  PopplerPage* page = GetFirstPageOrFail(doc);
  ASSERT_NE(page, nullptr);

  GList* list = poppler_page_get_link_mapping(page);
  ASSERT_NE(list, nullptr);
  EXPECT_EQ(GListLength(list), 2);

  PopplerLinkMapping* m1 = FindMappingByUri(list, u1.c_str());
  PopplerLinkMapping* m2 = FindMappingByUri(list, u2.c_str());
  EXPECT_NE(m1, nullptr);
  EXPECT_NE(m2, nullptr);

  // Boundary-ish sanity: areas should be non-degenerate.
  if (m1) {
    EXPECT_LT(m1->area.x1, m1->area.x2);
    EXPECT_LT(m1->area.y1, m1->area.y2);
  }
  if (m2) {
    EXPECT_LT(m2->area.x1, m2->area.x2);
    EXPECT_LT(m2->area.y1, m2->area.y2);
  }

  poppler_page_free_link_mapping(list);
  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageGetLinkMappingTest_2453, LinkRectOnCropBoundaryMapsToOriginAtRotate0_2453) {
  // Boundary condition: link rect exactly equals CropBox (in PDF user space).
  const PdfRect crop{15, 25, 115, 125};
  const PdfRect link_rect = crop;
  const std::string kUri = "http://example.com/boundary";

  const std::string pdf =
      BuildPdfWithOptionalLinks(/*rotate_degrees=*/0, &crop, {link_rect}, {kUri});
  const std::string path = MakeTempPdf(pdf);
  ASSERT_FALSE(path.empty());

  PopplerDocument* doc = LoadDocumentOrFail(ToFileUri(path));
  ASSERT_NE(doc, nullptr);
  PopplerPage* page = GetFirstPageOrFail(doc);
  ASSERT_NE(page, nullptr);

  GList* list = poppler_page_get_link_mapping(page);
  ASSERT_NE(list, nullptr);
  EXPECT_EQ(GListLength(list), 1);

  PopplerLinkMapping* mapping = FindMappingByUri(list, kUri.c_str());
  ASSERT_NE(mapping, nullptr);

  // For rotate 0, crop offset should bring the rectangle to start at (0,0).
  EXPECT_NEAR(mapping->area.x1, 0.0, 1e-6);
  EXPECT_NEAR(mapping->area.y1, 0.0, 1e-6);
  EXPECT_NEAR(mapping->area.x2, (crop.x2 - crop.x1), 1e-6);
  EXPECT_NEAR(mapping->area.y2, (crop.y2 - crop.y1), 1e-6);

  poppler_page_free_link_mapping(list);
  g_object_unref(page);
  g_object_unref(doc);
}