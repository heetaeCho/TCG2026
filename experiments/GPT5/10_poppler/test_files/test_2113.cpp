// File: poppler-annot-geometry-interior-color-test_2113.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib/gstdio.h>
#include <poppler.h>

#include <cmath>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace {

class PopplerAnnotGeometryInteriorColorTest_2113 : public ::testing::Test {
 protected:
  static std::string MakeMinimalPdfWithGeometryAnnot(const char* subtype,
                                                    bool with_interior_color,
                                                    double r = 1.0,
                                                    double g = 0.0,
                                                    double b = 0.0) {
    // Build a minimal, valid PDF with one page and one geometry annotation.
    // subtype should be "Square" or "Circle".
    //
    // Annotation dictionary includes /IC only when with_interior_color == true.
    // We also include /Rect so Poppler can place the annotation.

    auto dbl = [](double v) {
      // PDF accepts decimals; keep it compact.
      std::ostringstream os;
      os.setf(std::ios::fixed);
      os.precision(4);
      os << v;
      std::string s = os.str();
      // trim trailing zeros
      while (s.size() > 1 && s.find('.') != std::string::npos &&
             (s.back() == '0' || s.back() == '.')) {
        if (s.back() == '.') {
          s.pop_back();
          break;
        }
        s.pop_back();
      }
      return s;
    };

    std::vector<std::string> objs;
    objs.reserve(6);

    // 1: Catalog
    objs.push_back("<< /Type /Catalog /Pages 2 0 R >>");

    // 2: Pages
    objs.push_back("<< /Type /Pages /Kids [3 0 R] /Count 1 >>");

    // 3: Page
    objs.push_back("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
                   "   /Resources << >>\n"
                   "   /Contents 5 0 R\n"
                   "   /Annots [4 0 R]\n"
                   ">>");

    // 4: Annotation
    std::ostringstream a;
    a << "<< /Type /Annot /Subtype /" << subtype << "\n"
      << "   /Rect [10 10 100 100]\n";
    if (with_interior_color) {
      a << "   /IC [" << dbl(r) << " " << dbl(g) << " " << dbl(b) << "]\n";
    }
    a << ">>";
    objs.push_back(a.str());

    // 5: Empty contents stream
    objs.push_back("<< /Length 0 >>\nstream\nendstream");

    // Build final PDF with correct xref offsets.
    std::ostringstream pdf;
    pdf << "%PDF-1.4\n";
    std::vector<long> offsets;
    offsets.resize(objs.size() + 1);

    for (size_t i = 0; i < objs.size(); ++i) {
      offsets[i + 1] = static_cast<long>(pdf.tellp());
      pdf << (i + 1) << " 0 obj\n" << objs[i] << "\nendobj\n";
    }

    const long xref_pos = static_cast<long>(pdf.tellp());
    pdf << "xref\n0 " << (objs.size() + 1) << "\n";
    pdf << "0000000000 65535 f \n";
    for (size_t i = 1; i <= objs.size(); ++i) {
      char buf[32];
      std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
      pdf << buf;
    }

    pdf << "trailer\n<< /Size " << (objs.size() + 1) << " /Root 1 0 R >>\n";
    pdf << "startxref\n" << xref_pos << "\n%%EOF\n";
    return pdf.str();
  }

  static std::string WriteTempPdfAndGetUri(const std::string& pdf_bytes) {
    gchar* tmpl = g_strdup("/tmp/poppler_annot_2113_XXXXXX.pdf");
    int fd = g_mkstemp(tmpl);
    EXPECT_NE(fd, -1);
    if (fd == -1) {
      g_free(tmpl);
      return "";
    }

    {
      std::ofstream ofs(tmpl, std::ios::binary);
      ofs.write(pdf_bytes.data(), static_cast<std::streamsize>(pdf_bytes.size()));
      ofs.close();
    }

    close(fd);

    gchar* uri = g_filename_to_uri(tmpl, nullptr, nullptr);
    std::string out = uri ? uri : "";
    g_free(uri);
    g_free(tmpl);
    return out;
  }

  static PopplerDocument* LoadDocumentFromUriOrFail(const std::string& uri) {
    GError* error = nullptr;
    PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
    if (!doc) {
      std::string msg = error ? error->message : "unknown error";
      if (error) g_error_free(error);
      ADD_FAILURE() << "Failed to load PDF: " << msg;
      return nullptr;
    }
    if (error) g_error_free(error);
    return doc;
  }

  static PopplerAnnot* GetFirstAnnotFromFirstPageOrFail(PopplerDocument* doc) {
    if (!doc) return nullptr;
    PopplerPage* page = poppler_document_get_page(doc, 0);
    EXPECT_NE(page, nullptr);
    if (!page) return nullptr;

    GList* mapping_list = poppler_page_get_annot_mapping(page);
    EXPECT_NE(mapping_list, nullptr);
    if (!mapping_list) {
      g_object_unref(page);
      return nullptr;
    }

    auto* mapping = static_cast<PopplerAnnotMapping*>(mapping_list->data);
    EXPECT_NE(mapping, nullptr);
    EXPECT_NE(mapping ? mapping->annot : nullptr, nullptr);

    PopplerAnnot* annot = mapping ? mapping->annot : nullptr;

    // Keep annot alive by reffing it; mapping list will be freed.
    if (annot) g_object_ref(annot);

    poppler_page_free_annot_mapping(mapping_list);
    g_object_unref(page);
    return annot;
  }

  static void ExpectColorNear(const PopplerColor& c, guint16 r, guint16 g, guint16 b,
                              guint16 tol = 1) {
    auto near_u16 = [tol](guint16 a, guint16 e) {
      const int da = static_cast<int>(a);
      const int de = static_cast<int>(e);
      return std::abs(da - de) <= tol;
    };
    EXPECT_TRUE(near_u16(c.red, r)) << "red=" << c.red << " expected " << r;
    EXPECT_TRUE(near_u16(c.green, g)) << "green=" << c.green << " expected " << g;
    EXPECT_TRUE(near_u16(c.blue, b)) << "blue=" << c.blue << " expected " << b;
  }
};

TEST_F(PopplerAnnotGeometryInteriorColorTest_2113,
       SquareGetInteriorColor_FromParsedPdf_WithIC_2113) {
  const std::string pdf = MakeMinimalPdfWithGeometryAnnot("Square", /*with_interior_color=*/true,
                                                         /*r=*/1.0, /*g=*/0.0, /*b=*/0.0);
  const std::string uri = WriteTempPdfAndGetUri(pdf);

  PopplerDocument* doc = LoadDocumentFromUriOrFail(uri);
  ASSERT_NE(doc, nullptr);

  PopplerAnnot* annot = GetFirstAnnotFromFirstPageOrFail(doc);
  ASSERT_NE(annot, nullptr);
  ASSERT_TRUE(POPPLER_IS_ANNOT_SQUARE(annot));

  PopplerColor* c = poppler_annot_square_get_interior_color(POPPLER_ANNOT_SQUARE(annot));
  ASSERT_NE(c, nullptr);

  // PopplerColor components are 0..65535 (RGB).
  // /IC [1 0 0] should map to full red.
  ExpectColorNear(*c, /*r=*/65535, /*g=*/0, /*b=*/0, /*tol=*/1);

  g_free(c);
  g_object_unref(annot);
  g_object_unref(doc);
}

TEST_F(PopplerAnnotGeometryInteriorColorTest_2113,
       SquareGetInteriorColor_FromParsedPdf_WithoutIC_ReturnsNull_2113) {
  const std::string pdf =
      MakeMinimalPdfWithGeometryAnnot("Square", /*with_interior_color=*/false);
  const std::string uri = WriteTempPdfAndGetUri(pdf);

  PopplerDocument* doc = LoadDocumentFromUriOrFail(uri);
  ASSERT_NE(doc, nullptr);

  PopplerAnnot* annot = GetFirstAnnotFromFirstPageOrFail(doc);
  ASSERT_NE(annot, nullptr);
  ASSERT_TRUE(POPPLER_IS_ANNOT_SQUARE(annot));

  PopplerColor* c = poppler_annot_square_get_interior_color(POPPLER_ANNOT_SQUARE(annot));
  EXPECT_EQ(c, nullptr);

  g_object_unref(annot);
  g_object_unref(doc);
}

TEST_F(PopplerAnnotGeometryInteriorColorTest_2113,
       CircleGetInteriorColor_FromParsedPdf_WithIC_2113) {
  const std::string pdf = MakeMinimalPdfWithGeometryAnnot("Circle", /*with_interior_color=*/true,
                                                         /*r=*/0.0, /*g=*/1.0, /*b=*/0.0);
  const std::string uri = WriteTempPdfAndGetUri(pdf);

  PopplerDocument* doc = LoadDocumentFromUriOrFail(uri);
  ASSERT_NE(doc, nullptr);

  PopplerAnnot* annot = GetFirstAnnotFromFirstPageOrFail(doc);
  ASSERT_NE(annot, nullptr);
  ASSERT_TRUE(POPPLER_IS_ANNOT_CIRCLE(annot));

  PopplerColor* c = poppler_annot_circle_get_interior_color(POPPLER_ANNOT_CIRCLE(annot));
  ASSERT_NE(c, nullptr);

  // /IC [0 1 0] => full green
  ExpectColorNear(*c, /*r=*/0, /*g=*/65535, /*b=*/0, /*tol=*/1);

  g_free(c);
  g_object_unref(annot);
  g_object_unref(doc);
}

TEST_F(PopplerAnnotGeometryInteriorColorTest_2113,
       CircleGetInteriorColor_FromParsedPdf_WithoutIC_ReturnsNull_2113) {
  const std::string pdf =
      MakeMinimalPdfWithGeometryAnnot("Circle", /*with_interior_color=*/false);
  const std::string uri = WriteTempPdfAndGetUri(pdf);

  PopplerDocument* doc = LoadDocumentFromUriOrFail(uri);
  ASSERT_NE(doc, nullptr);

  PopplerAnnot* annot = GetFirstAnnotFromFirstPageOrFail(doc);
  ASSERT_NE(annot, nullptr);
  ASSERT_TRUE(POPPLER_IS_ANNOT_CIRCLE(annot));

  PopplerColor* c = poppler_annot_circle_get_interior_color(POPPLER_ANNOT_CIRCLE(annot));
  EXPECT_EQ(c, nullptr);

  g_object_unref(annot);
  g_object_unref(doc);
}

TEST_F(PopplerAnnotGeometryInteriorColorTest_2113,
       SquareSetInteriorColor_ThenGetInteriorColor_Matches_2113) {
  const std::string pdf =
      MakeMinimalPdfWithGeometryAnnot("Square", /*with_interior_color=*/false);
  const std::string uri = WriteTempPdfAndGetUri(pdf);

  PopplerDocument* doc = LoadDocumentFromUriOrFail(uri);
  ASSERT_NE(doc, nullptr);

  PopplerRectangle rect;
  rect.x1 = 10;
  rect.y1 = 10;
  rect.x2 = 100;
  rect.y2 = 100;

  PopplerAnnot* a = poppler_annot_square_new(doc, &rect);
  ASSERT_NE(a, nullptr);
  ASSERT_TRUE(POPPLER_IS_ANNOT_SQUARE(a));

  PopplerColor set_c;
  // Boundary-ish values: midpoints; rounding differences allowed by tolerance.
  set_c.red = 32768;
  set_c.green = 1;
  set_c.blue = 65535;

  poppler_annot_square_set_interior_color(POPPLER_ANNOT_SQUARE(a), &set_c);

  PopplerColor* got = poppler_annot_square_get_interior_color(POPPLER_ANNOT_SQUARE(a));
  ASSERT_NE(got, nullptr);

  ExpectColorNear(*got, set_c.red, set_c.green, set_c.blue, /*tol=*/2);

  g_free(got);
  g_object_unref(a);
  g_object_unref(doc);
}

TEST_F(PopplerAnnotGeometryInteriorColorTest_2113,
       SquareSetInteriorColor_NullClears_GetReturnsNull_2113) {
  const std::string pdf =
      MakeMinimalPdfWithGeometryAnnot("Square", /*with_interior_color=*/false);
  const std::string uri = WriteTempPdfAndGetUri(pdf);

  PopplerDocument* doc = LoadDocumentFromUriOrFail(uri);
  ASSERT_NE(doc, nullptr);

  PopplerRectangle rect;
  rect.x1 = 10;
  rect.y1 = 10;
  rect.x2 = 100;
  rect.y2 = 100;

  PopplerAnnot* a = poppler_annot_square_new(doc, &rect);
  ASSERT_NE(a, nullptr);
  ASSERT_TRUE(POPPLER_IS_ANNOT_SQUARE(a));

  // Set a color first
  PopplerColor set_c;
  set_c.red = 65535;
  set_c.green = 65535;
  set_c.blue = 0;
  poppler_annot_square_set_interior_color(POPPLER_ANNOT_SQUARE(a), &set_c);

  PopplerColor* got1 = poppler_annot_square_get_interior_color(POPPLER_ANNOT_SQUARE(a));
  ASSERT_NE(got1, nullptr);
  g_free(got1);

  // Now clear
  poppler_annot_square_set_interior_color(POPPLER_ANNOT_SQUARE(a), nullptr);

  PopplerColor* got2 = poppler_annot_square_get_interior_color(POPPLER_ANNOT_SQUARE(a));
  EXPECT_EQ(got2, nullptr);

  g_object_unref(a);
  g_object_unref(doc);
}

}  // namespace