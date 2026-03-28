#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/GfxState.h"

// Since we cannot easily construct GfxPatchMeshShading objects directly
// (they require complex dependencies), we test through the copy constructor
// and available public interface where possible.

class GfxPatchMeshShadingTest_525 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getNPatches returns correct count when constructed with patches
TEST_F(GfxPatchMeshShadingTest_525, GetNPatchesWithPatches_525) {
    const int nPatches = 3;
    GfxPatch *patches = new GfxPatch[nPatches];
    
    // Initialize patches with some data
    for (int i = 0; i < nPatches; i++) {
        for (int u = 0; u < 4; u++) {
            for (int v = 0; v < 4; v++) {
                patches[i].x[u][v] = static_cast<double>(i * 16 + u * 4 + v);
                patches[i].y[u][v] = static_cast<double>(i * 16 + u * 4 + v + 100);
            }
        }
    }

    std::vector<std::unique_ptr<Function>> funcs;
    GfxPatchMeshShading shading(6, patches, nPatches, std::move(funcs));
    
    EXPECT_EQ(shading.getNPatches(), nPatches);
}

// Test getPatch returns correct patch data
TEST_F(GfxPatchMeshShadingTest_525, GetPatchReturnsCorrectData_525) {
    const int nPatches = 2;
    GfxPatch *patches = new GfxPatch[nPatches];
    
    // Set distinctive values for each patch
    for (int u = 0; u < 4; u++) {
        for (int v = 0; v < 4; v++) {
            patches[0].x[u][v] = 1.0;
            patches[0].y[u][v] = 2.0;
            patches[1].x[u][v] = 3.0;
            patches[1].y[u][v] = 4.0;
        }
    }

    std::vector<std::unique_ptr<Function>> funcs;
    GfxPatchMeshShading shading(6, patches, nPatches, std::move(funcs));
    
    const GfxPatch *p0 = shading.getPatch(0);
    const GfxPatch *p1 = shading.getPatch(1);
    
    ASSERT_NE(p0, nullptr);
    ASSERT_NE(p1, nullptr);
    EXPECT_DOUBLE_EQ(p0->x[0][0], 1.0);
    EXPECT_DOUBLE_EQ(p0->y[0][0], 2.0);
    EXPECT_DOUBLE_EQ(p1->x[0][0], 3.0);
    EXPECT_DOUBLE_EQ(p1->y[0][0], 4.0);
}

// Test with single patch
TEST_F(GfxPatchMeshShadingTest_525, SinglePatch_525) {
    const int nPatches = 1;
    GfxPatch *patches = new GfxPatch[nPatches];
    
    for (int u = 0; u < 4; u++) {
        for (int v = 0; v < 4; v++) {
            patches[0].x[u][v] = static_cast<double>(u + v);
            patches[0].y[u][v] = static_cast<double>(u * v);
        }
    }

    std::vector<std::unique_ptr<Function>> funcs;
    GfxPatchMeshShading shading(6, patches, nPatches, std::move(funcs));
    
    EXPECT_EQ(shading.getNPatches(), 1);
    const GfxPatch *p = shading.getPatch(0);
    ASSERT_NE(p, nullptr);
    EXPECT_DOUBLE_EQ(p->x[2][3], 5.0);  // 2 + 3
    EXPECT_DOUBLE_EQ(p->y[2][3], 6.0);  // 2 * 3
}

// Test isParameterized with no functions (should not be parameterized)
TEST_F(GfxPatchMeshShadingTest_525, IsParameterizedNoFunctions_525) {
    const int nPatches = 1;
    GfxPatch *patches = new GfxPatch[nPatches];
    memset(patches, 0, sizeof(GfxPatch));

    std::vector<std::unique_ptr<Function>> funcs;
    GfxPatchMeshShading shading(6, patches, nPatches, std::move(funcs));
    
    // With no functions, it should not be parameterized
    EXPECT_FALSE(shading.isParameterized());
}

// Test copy constructor preserves patch data
TEST_F(GfxPatchMeshShadingTest_525, CopyPreservesPatches_525) {
    const int nPatches = 2;
    GfxPatch *patches = new GfxPatch[nPatches];
    
    for (int u = 0; u < 4; u++) {
        for (int v = 0; v < 4; v++) {
            patches[0].x[u][v] = 10.0;
            patches[0].y[u][v] = 20.0;
            patches[1].x[u][v] = 30.0;
            patches[1].y[u][v] = 40.0;
        }
    }

    std::vector<std::unique_ptr<Function>> funcs;
    GfxPatchMeshShading shading(6, patches, nPatches, std::move(funcs));
    
    auto shadingCopy = shading.copy();
    ASSERT_NE(shadingCopy, nullptr);
    
    GfxPatchMeshShading *copyPtr = static_cast<GfxPatchMeshShading *>(shadingCopy.get());
    EXPECT_EQ(copyPtr->getNPatches(), nPatches);
    
    const GfxPatch *cp0 = copyPtr->getPatch(0);
    const GfxPatch *cp1 = copyPtr->getPatch(1);
    
    ASSERT_NE(cp0, nullptr);
    ASSERT_NE(cp1, nullptr);
    EXPECT_DOUBLE_EQ(cp0->x[0][0], 10.0);
    EXPECT_DOUBLE_EQ(cp0->y[0][0], 20.0);
    EXPECT_DOUBLE_EQ(cp1->x[0][0], 30.0);
    EXPECT_DOUBLE_EQ(cp1->y[0][0], 40.0);
}

// Test that getPatch returns different pointers for different indices
TEST_F(GfxPatchMeshShadingTest_525, GetPatchDifferentIndicesReturnDifferentPointers_525) {
    const int nPatches = 3;
    GfxPatch *patches = new GfxPatch[nPatches];
    memset(patches, 0, sizeof(GfxPatch) * nPatches);

    std::vector<std::unique_ptr<Function>> funcs;
    GfxPatchMeshShading shading(6, patches, nPatches, std::move(funcs));
    
    const GfxPatch *p0 = shading.getPatch(0);
    const GfxPatch *p1 = shading.getPatch(1);
    const GfxPatch *p2 = shading.getPatch(2);
    
    EXPECT_NE(p0, p1);
    EXPECT_NE(p1, p2);
    EXPECT_NE(p0, p2);
}

// Test type 7 shading (tensor-product patch meshes)
TEST_F(GfxPatchMeshShadingTest_525, Type7Shading_525) {
    const int nPatches = 1;
    GfxPatch *patches = new GfxPatch[nPatches];
    
    for (int u = 0; u < 4; u++) {
        for (int v = 0; v < 4; v++) {
            patches[0].x[u][v] = u * 10.0 + v;
            patches[0].y[u][v] = u + v * 10.0;
        }
    }

    std::vector<std::unique_ptr<Function>> funcs;
    GfxPatchMeshShading shading(7, patches, nPatches, std::move(funcs));
    
    EXPECT_EQ(shading.getNPatches(), 1);
    const GfxPatch *p = shading.getPatch(0);
    ASSERT_NE(p, nullptr);
    EXPECT_DOUBLE_EQ(p->x[3][3], 33.0);  // 3*10 + 3
    EXPECT_DOUBLE_EQ(p->y[3][3], 33.0);  // 3 + 3*10
}

// Test boundary - accessing first and last patch
TEST_F(GfxPatchMeshShadingTest_525, BoundaryFirstAndLastPatch_525) {
    const int nPatches = 5;
    GfxPatch *patches = new GfxPatch[nPatches];
    
    for (int i = 0; i < nPatches; i++) {
        for (int u = 0; u < 4; u++) {
            for (int v = 0; v < 4; v++) {
                patches[i].x[u][v] = static_cast<double>(i * 100);
                patches[i].y[u][v] = static_cast<double>(i * 200);
            }
        }
    }

    std::vector<std::unique_ptr<Function>> funcs;
    GfxPatchMeshShading shading(6, patches, nPatches, std::move(funcs));
    
    // First patch
    const GfxPatch *first = shading.getPatch(0);
    EXPECT_DOUBLE_EQ(first->x[0][0], 0.0);
    EXPECT_DOUBLE_EQ(first->y[0][0], 0.0);
    
    // Last patch
    const GfxPatch *last = shading.getPatch(nPatches - 1);
    EXPECT_DOUBLE_EQ(last->x[0][0], 400.0);
    EXPECT_DOUBLE_EQ(last->y[0][0], 800.0);
}

// Test getPatch with all control points at boundary of each patch cell
TEST_F(GfxPatchMeshShadingTest_525, PatchControlPointBoundaries_525) {
    const int nPatches = 1;
    GfxPatch *patches = new GfxPatch[nPatches];
    
    // Set corner control points
    patches[0].x[0][0] = 0.0;
    patches[0].y[0][0] = 0.0;
    patches[0].x[0][3] = 1.0;
    patches[0].y[0][3] = 0.0;
    patches[0].x[3][0] = 0.0;
    patches[0].y[3][0] = 1.0;
    patches[0].x[3][3] = 1.0;
    patches[0].y[3][3] = 1.0;
    
    // Fill remaining with zeros
    for (int u = 0; u < 4; u++) {
        for (int v = 0; v < 4; v++) {
            if (!((u == 0 || u == 3) && (v == 0 || v == 3))) {
                patches[0].x[u][v] = 0.5;
                patches[0].y[u][v] = 0.5;
            }
        }
    }

    std::vector<std::unique_ptr<Function>> funcs;
    GfxPatchMeshShading shading(6, patches, nPatches, std::move(funcs));
    
    const GfxPatch *p = shading.getPatch(0);
    EXPECT_DOUBLE_EQ(p->x[0][0], 0.0);
    EXPECT_DOUBLE_EQ(p->y[0][0], 0.0);
    EXPECT_DOUBLE_EQ(p->x[3][3], 1.0);
    EXPECT_DOUBLE_EQ(p->y[3][3], 1.0);
    EXPECT_DOUBLE_EQ(p->x[1][1], 0.5);
    EXPECT_DOUBLE_EQ(p->y[1][1], 0.5);
}
