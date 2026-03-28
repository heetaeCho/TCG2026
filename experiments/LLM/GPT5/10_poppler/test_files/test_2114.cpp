// poppler_annot_geometry_set_interior_color_test_2114.cc
#include <gtest/gtest.h>

#include <glib-object.h>

extern "C" {
#include <poppler.h>  // poppler-glib umbrella header (adjust include path if your build requires <poppler/glib/poppler.h>)
}

namespace {

class PopplerAnnotGeometryInteriorColorTest_2114 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif
  }

  static PopplerDocument* NewMinimalDocOrNull() {
    // Minimal 1-page PDF. Poppler GLib supports loading from data.
    static const char kPdf[] =
        "%PDF-1.4\n"
        "1 0 obj << /Type /Catalog /Pages 2 0 R >> endobj\n"
        "2 0 obj << /Type /Pages /Kids [3 0 R] /Count 1 >> endobj\n"
        "3 0 obj << /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] "
        "          /Resources << >> /Contents 4 0 R >> endobj\n"
        "4 0 obj << /Length 0 >> stream\n"
        "endstream endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000010 00000 n \n"
        "0000000060 00000 n \n"
        "0000000120 00000 n \n"
        "0000000240 00000 n \n"
        "trailer << /Size 5 /Root 1 0 R >>\n"
        "startxref\n"
        "300\n"
        "%%EOF\n";

    GError* error = nullptr;
    PopplerDocument* doc =
        poppler_document_new_from_data(kPdf, static_cast<int>(sizeof(kPdf) - 1), /*password*/ nullptr, &error);
    if (!doc) {
      if (error) {
        g_error_free(error);
      }
      return nullptr;
    }
    return doc;
  }

  static PopplerAnnot* NewGeometryAnnotOrNull(PopplerDocument* doc) {
    // Create a geometry annotation. Square is a geometry annotation type.
    PopplerRectangle rect;
    rect.x1 = 10;
    rect.y1 = 10;
    rect.x2 = 50;
    rect.y2 = 50;

    // API is expected in poppler-glib: poppler_annot_square_new(PopplerDocument*, PopplerRectangle*)
    // If your build exposes a different constructor, adjust accordingly.
    PopplerAnnot* annot = POPPLER_ANNOT(poppler_annot_square_new(doc, &rect));
    return annot;
  }

  static bool HasInteriorColorProperty(PopplerAnnot* annot) {
    if (!annot) return false;
    GParamSpec* pspec =
        g_object_class_find_property(G_OBJECT_GET_CLASS(annot), "interior-color");
    return pspec != nullptr;
  }

  static PopplerColor* GetInteriorColorOrNull(PopplerAnnot* annot) {
    PopplerColor* out = nullptr;
    g_object_get(G_OBJECT(annot), "interior-color", &out, nullptr);
    return out;  // caller frees with g_free() if non-null (PopplerColor is a boxed/struct copy in poppler-glib)
  }
};

TEST_F(PopplerAnnotGeometryInteriorColorTest_2114, SetsInteriorColorViaGObjectProperty_2114) {
  PopplerDocument* doc = NewMinimalDocOrNull();
  ASSERT_NE(doc, nullptr);

  PopplerAnnot* annot = NewGeometryAnnotOrNull(doc);
  ASSERT_NE(annot, nullptr);

  // If the build doesn’t expose this property for this annot type, skip rather than failing spuriously.
  if (!HasInteriorColorProperty(annot)) {
    g_object_unref(annot);
    g_object_unref(doc);
    GTEST_SKIP() << "interior-color property not available on this Poppler geometry annot type/build.";
  }

  PopplerColor in;
  in.red = 100;
  in.green = 200;
  in.blue = 300;

  g_object_set(G_OBJECT(annot), "interior-color", &in, nullptr);

  PopplerColor* out = GetInteriorColorOrNull(annot);
  ASSERT_NE(out, nullptr);

  EXPECT_EQ(out->red, in.red);
  EXPECT_EQ(out->green, in.green);
  EXPECT_EQ(out->blue, in.blue);

  g_free(out);
  g_object_unref(annot);
  g_object_unref(doc);
}

TEST_F(PopplerAnnotGeometryInteriorColorTest_2114, OverwritesPreviousInteriorColor_2114) {
  PopplerDocument* doc = NewMinimalDocOrNull();
  ASSERT_NE(doc, nullptr);

  PopplerAnnot* annot = NewGeometryAnnotOrNull(doc);
  ASSERT_NE(annot, nullptr);

  if (!HasInteriorColorProperty(annot)) {
    g_object_unref(annot);
    g_object_unref(doc);
    GTEST_SKIP() << "interior-color property not available on this Poppler geometry annot type/build.";
  }

  PopplerColor first;
  first.red = 1;
  first.green = 2;
  first.blue = 3;

  PopplerColor second;
  second.red = 400;
  second.green = 500;
  second.blue = 600;

  g_object_set(G_OBJECT(annot), "interior-color", &first, nullptr);
  g_object_set(G_OBJECT(annot), "interior-color", &second, nullptr);

  PopplerColor* out = GetInteriorColorOrNull(annot);
  ASSERT_NE(out, nullptr);

  EXPECT_EQ(out->red, second.red);
  EXPECT_EQ(out->green, second.green);
  EXPECT_EQ(out->blue, second.blue);

  g_free(out);
  g_object_unref(annot);
  g_object_unref(doc);
}

TEST_F(PopplerAnnotGeometryInteriorColorTest_2114, BoundaryColorValuesDoNotCrash_2114) {
  PopplerDocument* doc = NewMinimalDocOrNull();
  ASSERT_NE(doc, nullptr);

  PopplerAnnot* annot = NewGeometryAnnotOrNull(doc);
  ASSERT_NE(annot, nullptr);

  if (!HasInteriorColorProperty(annot)) {
    g_object_unref(annot);
    g_object_unref(doc);
    GTEST_SKIP() << "interior-color property not available on this Poppler geometry annot type/build.";
  }

  // Boundary-ish values for the exposed int fields. We don’t assume clamping rules; we only
  // assert the call is accepted and a value can be read back.
  PopplerColor in;
  in.red = 0;
  in.green = 0;
  in.blue = 0;
  g_object_set(G_OBJECT(annot), "interior-color", &in, nullptr);

  PopplerColor* out0 = GetInteriorColorOrNull(annot);
  ASSERT_NE(out0, nullptr);
  g_free(out0);

  in.red = 65535;
  in.green = 65535;
  in.blue = 65535;
  g_object_set(G_OBJECT(annot), "interior-color", &in, nullptr);

  PopplerColor* outMax = GetInteriorColorOrNull(annot);
  ASSERT_NE(outMax, nullptr);
  g_free(outMax);

  g_object_unref(annot);
  g_object_unref(doc);
}

TEST_F(PopplerAnnotGeometryInteriorColorTest_2114, NullAnnotDoesNotSegfaultWhenChecked_2114) {
  // This test is intentionally minimal: it verifies our boundary handling in the test harness,
  // and avoids calling into Poppler with a null object (which would be undefined behavior).
  PopplerAnnot* annot = nullptr;
  EXPECT_FALSE(HasInteriorColorProperty(annot));
}

}  // namespace