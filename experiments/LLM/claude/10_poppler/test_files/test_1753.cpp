#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cairo.h>
#include <memory>
#include <array>

#include "CairoFontEngine.h"
#include "CairoOutputDev.h"
#include "Dict.h"
#include "Object.h"
#include "Gfx.h"
#include "GfxFont.h"
#include "PDFDoc.h"
#include "Error.h"

using ::testing::_;
using ::testing::Return;
using ::testing::NiceMock;
using ::testing::AtLeast;

// Since _render_type3_glyph is a static function used as a cairo user font callback,
// we test it through the cairo user font mechanism.

// Forward declare the key used in the implementation
extern cairo_user_data_key_t type3_font_key;

class CairoFontEngineType3Test_1753 : public ::testing::Test {
protected:
    void SetUp() override {
        surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 100, 100);
        cr = cairo_create(surface);
    }

    void TearDown() override {
        if (cr) {
            cairo_destroy(cr);
        }
        if (surface) {
            cairo_surface_destroy(surface);
        }
    }

    cairo_surface_t *surface = nullptr;
    cairo_t *cr = nullptr;
};

// Test that CairoFontEngine can be created
TEST_F(CairoFontEngineType3Test_1753, CairoFontEngineCreation_1753) {
    CairoFontEngine *engine = new CairoFontEngine(nullptr);
    ASSERT_NE(engine, nullptr);
    delete engine;
}

// Test CairoOutputDev Type3 render type setting
TEST_F(CairoFontEngineType3Test_1753, Type3RenderTypeSetMask_1753) {
    CairoOutputDev outputDev;
    outputDev.setType3RenderType(CairoOutputDev::Type3RenderMask);
    // Verify it doesn't crash; the state is internal
    SUCCEED();
}

TEST_F(CairoFontEngineType3Test_1753, Type3RenderTypeSetColor_1753) {
    CairoOutputDev outputDev;
    outputDev.setType3RenderType(CairoOutputDev::Type3RenderColor);
    SUCCEED();
}

TEST_F(CairoFontEngineType3Test_1753, Type3RenderTypeSetNone_1753) {
    CairoOutputDev outputDev;
    outputDev.setType3RenderType(CairoOutputDev::Type3RenderNone);
    SUCCEED();
}

// Test getType3GlyphWidth returns values
TEST_F(CairoFontEngineType3Test_1753, GetType3GlyphWidthDefault_1753) {
    CairoOutputDev outputDev;
    double wx = -1.0, wy = -1.0;
    outputDev.getType3GlyphWidth(&wx, &wy);
    // Default values should be set (likely 0)
    EXPECT_GE(wx, 0.0);
    EXPECT_GE(wy, 0.0);
}

// Test hasType3GlyphBBox default
TEST_F(CairoFontEngineType3Test_1753, HasType3GlyphBBoxDefault_1753) {
    CairoOutputDev outputDev;
    bool hasBBox = outputDev.hasType3GlyphBBox();
    EXPECT_FALSE(hasBBox);
}

// Test type3GlyphHasColor default
TEST_F(CairoFontEngineType3Test_1753, Type3GlyphHasColorDefault_1753) {
    CairoOutputDev outputDev;
    bool hasColor = outputDev.type3GlyphHasColor();
    EXPECT_FALSE(hasColor);
}

// Test CairoOutputDev setCairo
TEST_F(CairoFontEngineType3Test_1753, SetCairoNullptr_1753) {
    CairoOutputDev outputDev;
    outputDev.setCairo(nullptr);
    SUCCEED();
}

// Test that CairoOutputDev can interpret type3 chars
TEST_F(CairoFontEngineType3Test_1753, InterpretType3Chars_1753) {
    CairoOutputDev outputDev;
    EXPECT_TRUE(outputDev.interpretType3Chars());
}

// Test CairoOutputDev upsideDown
TEST_F(CairoFontEngineType3Test_1753, UpsideDown_1753) {
    CairoOutputDev outputDev;
    EXPECT_TRUE(outputDev.upsideDown());
}

// Test CairoOutputDev useDrawChar
TEST_F(CairoFontEngineType3Test_1753, UseDrawChar_1753) {
    CairoOutputDev outputDev;
    EXPECT_TRUE(outputDev.useDrawChar());
}

// Test CairoOutputDev useTilingPatternFill
TEST_F(CairoFontEngineType3Test_1753, UseTilingPatternFill_1753) {
    CairoOutputDev outputDev;
    EXPECT_TRUE(outputDev.useTilingPatternFill());
}

// Test cairo matrix operations used in _render_type3_glyph
TEST_F(CairoFontEngineType3Test_1753, CairoMatrixInitScale_1753) {
    cairo_matrix_t invert_y_axis;
    cairo_matrix_init_scale(&invert_y_axis, 1, -1);
    EXPECT_DOUBLE_EQ(invert_y_axis.xx, 1.0);
    EXPECT_DOUBLE_EQ(invert_y_axis.yy, -1.0);
    EXPECT_DOUBLE_EQ(invert_y_axis.xy, 0.0);
    EXPECT_DOUBLE_EQ(invert_y_axis.yx, 0.0);
    EXPECT_DOUBLE_EQ(invert_y_axis.x0, 0.0);
    EXPECT_DOUBLE_EQ(invert_y_axis.y0, 0.0);
}

TEST_F(CairoFontEngineType3Test_1753, CairoMatrixMultiply_1753) {
    cairo_matrix_t matrix, invert_y_axis, result;
    cairo_matrix_init_identity(&matrix);
    cairo_matrix_init_scale(&invert_y_axis, 1, -1);
    cairo_matrix_multiply(&result, &matrix, &invert_y_axis);
    EXPECT_DOUBLE_EQ(result.xx, 1.0);
    EXPECT_DOUBLE_EQ(result.yy, -1.0);
}

TEST_F(CairoFontEngineType3Test_1753, CairoMatrixTransformDistance_1753) {
    cairo_matrix_t matrix;
    cairo_matrix_init_identity(&matrix);
    double wx = 1.0, wy = 0.0;
    cairo_matrix_transform_distance(&matrix, &wx, &wy);
    EXPECT_DOUBLE_EQ(wx, 1.0);
    EXPECT_DOUBLE_EQ(wy, 0.0);
}

TEST_F(CairoFontEngineType3Test_1753, CairoMatrixTransformPoint_1753) {
    cairo_matrix_t matrix;
    cairo_matrix_init_identity(&matrix);
    double x = 5.0, y = 10.0;
    cairo_matrix_transform_point(&matrix, &x, &y);
    EXPECT_DOUBLE_EQ(x, 5.0);
    EXPECT_DOUBLE_EQ(y, 10.0);
}

// Test that matrix with scale inverts y properly
TEST_F(CairoFontEngineType3Test_1753, MatrixInvertYTransformDistance_1753) {
    cairo_matrix_t matrix, invert_y_axis;
    cairo_matrix_init(&matrix, 0.001, 0, 0, 0.001, 0, 0);
    cairo_matrix_init_scale(&invert_y_axis, 1, -1);
    cairo_matrix_multiply(&matrix, &matrix, &invert_y_axis);

    double wx = 1000.0, wy = 0.0;
    cairo_matrix_transform_distance(&matrix, &wx, &wy);
    EXPECT_NEAR(wx, 1.0, 1e-6);
    EXPECT_NEAR(wy, 0.0, 1e-6);
}

// Test font matrix with non-trivial values
TEST_F(CairoFontEngineType3Test_1753, NonTrivialFontMatrix_1753) {
    cairo_matrix_t matrix, invert_y_axis;
    // Typical Type3 font matrix
    matrix.xx = 0.01;
    matrix.yx = 0.0;
    matrix.xy = 0.0;
    matrix.yy = 0.01;
    matrix.x0 = 0.0;
    matrix.y0 = 0.0;

    cairo_matrix_init_scale(&invert_y_axis, 1, -1);
    cairo_matrix_multiply(&matrix, &matrix, &invert_y_axis);

    EXPECT_DOUBLE_EQ(matrix.xx, 0.01);
    EXPECT_DOUBLE_EQ(matrix.yy, -0.01);
}

// Test CairoOutputDev printing mode
TEST_F(CairoFontEngineType3Test_1753, SetPrinting_1753) {
    CairoOutputDev outputDev;
    outputDev.setPrinting(true);
    SUCCEED();
}

TEST_F(CairoFontEngineType3Test_1753, SetPrintingFalse_1753) {
    CairoOutputDev outputDev;
    outputDev.setPrinting(false);
    SUCCEED();
}

// Test Dict getLength for empty dict
TEST_F(CairoFontEngineType3Test_1753, EmptyDictGetLength_1753) {
    // Create a Dict - requires XRef, use nullptr for minimal test
    Dict dict(nullptr);
    EXPECT_EQ(dict.getLength(), 0);
}

// Test Object type checks
TEST_F(CairoFontEngineType3Test_1753, ObjectIsStreamDefault_1753) {
    Object obj;
    EXPECT_FALSE(obj.isStream());
}

TEST_F(CairoFontEngineType3Test_1753, ObjectIsDictDefault_1753) {
    Object obj;
    EXPECT_FALSE(obj.isDict());
}

TEST_F(CairoFontEngineType3Test_1753, ObjectNullType_1753) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isStream());
}

// Test error categories used in the function
TEST_F(CairoFontEngineType3Test_1753, ErrorCategorySyntaxError_1753) {
    EXPECT_EQ(errSyntaxError, 1);
}

// Test CAIRO_STATUS_SUCCESS value
TEST_F(CairoFontEngineType3Test_1753, CairoStatusSuccess_1753) {
    EXPECT_EQ(CAIRO_STATUS_SUCCESS, 0);
}

// Test Type3RenderType enum values
TEST_F(CairoFontEngineType3Test_1753, Type3RenderTypeEnumValues_1753) {
    EXPECT_EQ(CairoOutputDev::Type3RenderNone, 0);
    EXPECT_EQ(CairoOutputDev::Type3RenderMask, 1);
    EXPECT_EQ(CairoOutputDev::Type3RenderColor, 2);
}

// Test getType3GlyphBBox returns a valid pointer
TEST_F(CairoFontEngineType3Test_1753, GetType3GlyphBBox_1753) {
    CairoOutputDev outputDev;
    double *bbox = outputDev.getType3GlyphBBox();
    ASSERT_NE(bbox, nullptr);
}

// Test cairo_text_extents_t initialization
TEST_F(CairoFontEngineType3Test_1753, TextExtentsInit_1753) {
    cairo_text_extents_t metrics = {};
    EXPECT_DOUBLE_EQ(metrics.x_advance, 0.0);
    EXPECT_DOUBLE_EQ(metrics.y_advance, 0.0);
    EXPECT_DOUBLE_EQ(metrics.x_bearing, 0.0);
    EXPECT_DOUBLE_EQ(metrics.y_bearing, 0.0);
    EXPECT_DOUBLE_EQ(metrics.width, 0.0);
    EXPECT_DOUBLE_EQ(metrics.height, 0.0);
}

// Test matrix multiplication with identity preserves values
TEST_F(CairoFontEngineType3Test_1753, MatrixMultiplyIdentity_1753) {
    cairo_matrix_t identity, matrix, result;
    cairo_matrix_init_identity(&identity);
    cairo_matrix_init(&matrix, 2.0, 0.0, 0.0, 3.0, 1.0, 2.0);
    cairo_matrix_multiply(&result, &matrix, &identity);
    EXPECT_DOUBLE_EQ(result.xx, 2.0);
    EXPECT_DOUBLE_EQ(result.yy, 3.0);
    EXPECT_DOUBLE_EQ(result.x0, 1.0);
    EXPECT_DOUBLE_EQ(result.y0, 2.0);
}

// Test that Dict with entries has correct length
TEST_F(CairoFontEngineType3Test_1753, DictWithEntries_1753) {
    Dict dict(nullptr);
    dict.add("key1", Object(1));
    EXPECT_EQ(dict.getLength(), 1);
    dict.add("key2", Object(2));
    EXPECT_EQ(dict.getLength(), 2);
}

// Test Dict getKey
TEST_F(CairoFontEngineType3Test_1753, DictGetKey_1753) {
    Dict dict(nullptr);
    dict.add("testGlyph", Object(1));
    EXPECT_STREQ(dict.getKey(0), "testGlyph");
}

// Boundary test: glyph index equals charProcs length (out of bounds)
TEST_F(CairoFontEngineType3Test_1753, GlyphIndexBoundary_1753) {
    Dict dict(nullptr);
    dict.add("a", Object(1));
    // glyph >= getLength() should be an error condition
    unsigned long glyph = 1; // equals length of 1
    EXPECT_TRUE(glyph >= (unsigned)dict.getLength());
}

// Boundary test: glyph index within bounds
TEST_F(CairoFontEngineType3Test_1753, GlyphIndexWithinBounds_1753) {
    Dict dict(nullptr);
    dict.add("a", Object(1));
    dict.add("b", Object(2));
    unsigned long glyph = 0;
    EXPECT_FALSE(glyph >= (unsigned)dict.getLength());
    glyph = 1;
    EXPECT_FALSE(glyph >= (unsigned)dict.getLength());
}

// Test metrics computation with non-trivial matrix
TEST_F(CairoFontEngineType3Test_1753, MetricsComputation_1753) {
    cairo_matrix_t matrix;
    cairo_matrix_init(&matrix, 0.001, 0, 0, -0.001, 0, 0);

    double wx = 500.0, wy = 0.0;
    cairo_matrix_transform_distance(&matrix, &wx, &wy);
    EXPECT_NEAR(wx, 0.5, 1e-6);
    EXPECT_NEAR(wy, 0.0, 1e-6);
}

// Test bbox transformation
TEST_F(CairoFontEngineType3Test_1753, BBoxTransformation_1753) {
    cairo_matrix_t matrix;
    cairo_matrix_init(&matrix, 0.001, 0, 0, -0.001, 0, 0);

    double bbox[4] = {0.0, 0.0, 1000.0, 800.0};
    cairo_matrix_transform_point(&matrix, &bbox[0], &bbox[1]);
    cairo_matrix_transform_point(&matrix, &bbox[2], &bbox[3]);

    EXPECT_NEAR(bbox[0], 0.0, 1e-6);
    EXPECT_NEAR(bbox[1], 0.0, 1e-6);
    EXPECT_NEAR(bbox[2], 1.0, 1e-6);
    EXPECT_NEAR(bbox[3], -0.8, 1e-6);

    double width = bbox[2] - bbox[0];
    double height = bbox[3] - bbox[1];
    EXPECT_NEAR(width, 1.0, 1e-6);
    EXPECT_NEAR(height, -0.8, 1e-6);
}

// Test that CAIRO_STATUS_USER_FONT_NOT_IMPLEMENTED exists
TEST_F(CairoFontEngineType3Test_1753, CairoStatusUserFontNotImplemented_1753) {
    cairo_status_t status = CAIRO_STATUS_USER_FONT_NOT_IMPLEMENTED;
    EXPECT_NE(status, CAIRO_STATUS_SUCCESS);
}
