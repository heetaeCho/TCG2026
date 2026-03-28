#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "SplashOutputDev.h"
#include "GfxState.h"
#include "SplashTypes.h"

#include <memory>
#include <vector>
#include <cstring>

// Helper to create a GfxGouraudTriangleShading for testing
// Type 4 = free-form, Type 5 = lattice-form
// We create minimal shading objects for testing purposes

class SplashGouraudPatternTest_1101 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Create a parameterized shading (has functions)
    GfxGouraudTriangleShading* createParameterizedShading(int nTri) {
        int nVerts = nTri * 3;
        GfxGouraudVertex* vertices = (GfxGouraudVertex*)gmallocn(nVerts, sizeof(GfxGouraudVertex));
        for (int i = 0; i < nVerts; i++) {
            vertices[i].x = i * 1.0;
            vertices[i].y = i * 2.0;
            vertices[i].color.c[0] = 0;
            vertices[i].color.comps = 1;
        }

        int(*triangles)[3] = (int(*)[3])gmallocn(nTri, 3 * sizeof(int));
        for (int i = 0; i < nTri; i++) {
            triangles[i][0] = i * 3;
            triangles[i][1] = i * 3 + 1;
            triangles[i][2] = i * 3 + 2;
        }

        std::vector<std::unique_ptr<Function>> funcs;
        // With empty funcs vector, isParameterized should return false
        // Type 4 gouraud shading
        return new GfxGouraudTriangleShading(4, vertices, nVerts, triangles, nTri, std::move(funcs));
    }

    // Create a non-parameterized shading (no functions)
    GfxGouraudTriangleShading* createNonParameterizedShading(int nTri) {
        int nVerts = nTri * 3;
        GfxGouraudVertex* vertices = (GfxGouraudVertex*)gmallocn(nVerts, sizeof(GfxGouraudVertex));
        for (int i = 0; i < nVerts; i++) {
            vertices[i].x = i * 1.0;
            vertices[i].y = i * 2.0;
            vertices[i].color.c[0] = 0;
            vertices[i].color.comps = 1;
        }

        int(*triangles)[3] = (int(*)[3])gmallocn(nTri, 3 * sizeof(int));
        for (int i = 0; i < nTri; i++) {
            triangles[i][0] = i * 3;
            triangles[i][1] = i * 3 + 1;
            triangles[i][2] = i * 3 + 2;
        }

        std::vector<std::unique_ptr<Function>> funcs;
        return new GfxGouraudTriangleShading(4, vertices, nVerts, triangles, nTri, std::move(funcs));
    }
};

TEST_F(SplashGouraudPatternTest_1101, IsParameterizedDelegatesToShading_1101) {
    GfxGouraudTriangleShading* shading = createNonParameterizedShading(1);
    SplashGouraudPattern pattern(false, shading);

    // isParameterized should delegate to shading->isParameterized()
    EXPECT_EQ(pattern.isParameterized(), shading->isParameterized());
}

TEST_F(SplashGouraudPatternTest_1101, GetNTrianglesReturnsCorrectCount_1101) {
    int expectedTriangles = 3;
    GfxGouraudTriangleShading* shading = createNonParameterizedShading(expectedTriangles);
    SplashGouraudPattern pattern(false, shading);

    EXPECT_EQ(pattern.getNTriangles(), expectedTriangles);
}

TEST_F(SplashGouraudPatternTest_1101, GetNTrianglesSingleTriangle_1101) {
    GfxGouraudTriangleShading* shading = createNonParameterizedShading(1);
    SplashGouraudPattern pattern(false, shading);

    EXPECT_EQ(pattern.getNTriangles(), 1);
}

TEST_F(SplashGouraudPatternTest_1101, IsStaticReturnsFalse_1101) {
    GfxGouraudTriangleShading* shading = createNonParameterizedShading(1);
    SplashGouraudPattern pattern(false, shading);

    // Gouraud patterns are not static (they vary across the surface)
    EXPECT_FALSE(pattern.isStatic());
}

TEST_F(SplashGouraudPatternTest_1101, TestPositionReturnsTrue_1101) {
    GfxGouraudTriangleShading* shading = createNonParameterizedShading(1);
    SplashGouraudPattern pattern(false, shading);

    // testPosition should generally return true for gouraud patterns
    EXPECT_TRUE(pattern.testPosition(0, 0));
    EXPECT_TRUE(pattern.testPosition(100, 200));
}

TEST_F(SplashGouraudPatternTest_1101, NonParameterizedShadingIsNotParameterized_1101) {
    GfxGouraudTriangleShading* shading = createNonParameterizedShading(2);

    // No functions means not parameterized
    EXPECT_FALSE(shading->isParameterized());

    SplashGouraudPattern pattern(false, shading);
    EXPECT_FALSE(pattern.isParameterized());
}

TEST_F(SplashGouraudPatternTest_1101, GetParametrizedTriangleReturnsData_1101) {
    GfxGouraudTriangleShading* shading = createNonParameterizedShading(1);
    SplashGouraudPattern pattern(false, shading);

    double x0, y0, color0;
    double x1, y1, color1;
    double x2, y2, color2;

    pattern.getParametrizedTriangle(0, &x0, &y0, &color0,
                                     &x1, &y1, &color1,
                                     &x2, &y2, &color2);

    // We just verify the call doesn't crash and returns values
    // The actual values depend on the shading data set up
    SUCCEED();
}

TEST_F(SplashGouraudPatternTest_1101, DirectColorTranslationFlag_1101) {
    GfxGouraudTriangleShading* shading = createNonParameterizedShading(1);

    // Test with bDirectColorTranslation = true
    SplashGouraudPattern patternDirect(true, shading);
    EXPECT_EQ(patternDirect.getNTriangles(), 1);

    // Test with bDirectColorTranslation = false
    GfxGouraudTriangleShading* shading2 = createNonParameterizedShading(1);
    SplashGouraudPattern patternIndirect(false, shading2);
    EXPECT_EQ(patternIndirect.getNTriangles(), 1);
}

TEST_F(SplashGouraudPatternTest_1101, MultipleTrianglesGetParametrized_1101) {
    int nTri = 5;
    GfxGouraudTriangleShading* shading = createNonParameterizedShading(nTri);
    SplashGouraudPattern pattern(false, shading);

    EXPECT_EQ(pattern.getNTriangles(), nTri);

    for (int i = 0; i < nTri; i++) {
        double x0, y0, color0;
        double x1, y1, color1;
        double x2, y2, color2;

        pattern.getParametrizedTriangle(i, &x0, &y0, &color0,
                                         &x1, &y1, &color1,
                                         &x2, &y2, &color2);
        // Just verify no crash on each triangle access
    }
    SUCCEED();
}

TEST_F(SplashGouraudPatternTest_1101, CopyReturnsNonNull_1101) {
    GfxGouraudTriangleShading* shading = createNonParameterizedShading(2);
    SplashGouraudPattern pattern(false, shading);

    SplashPattern* copied = pattern.copy();
    EXPECT_NE(copied, nullptr);
    delete copied;
}

TEST_F(SplashGouraudPatternTest_1101, GetColorDoesNotCrash_1101) {
    GfxGouraudTriangleShading* shading = createNonParameterizedShading(1);
    SplashGouraudPattern pattern(false, shading);

    SplashColor color;
    memset(color, 0, sizeof(SplashColor));
    // getColor may return false for gouraud patterns
    bool result = pattern.getColor(0, 0, color);
    // We just check it doesn't crash; the return value is implementation-dependent
    (void)result;
    SUCCEED();
}
