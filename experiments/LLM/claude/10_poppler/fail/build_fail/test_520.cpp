#include <gtest/gtest.h>
#include <memory>
#include <vector>

#include "GfxState.h"
#include "Object.h"
#include "Function.h"

class GfxGouraudTriangleShadingTest_520 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test getNTriangles with zero triangles
TEST_F(GfxGouraudTriangleShadingTest_520, GetNTrianglesZero_520) {
    // Create with 0 triangles
    std::vector<std::unique_ptr<Function>> funcs;
    GfxGouraudVertex *vertices = nullptr;
    int (*triangles)[3] = nullptr;

    GfxGouraudTriangleShading shading(4, vertices, 0, triangles, 0, std::move(funcs));
    EXPECT_EQ(shading.getNTriangles(), 0);
}

// Test getNTriangles with positive number of triangles
TEST_F(GfxGouraudTriangleShadingTest_520, GetNTrianglesPositive_520) {
    std::vector<std::unique_ptr<Function>> funcs;
    
    // Create some vertices
    GfxGouraudVertex vertices[3];
    memset(vertices, 0, sizeof(vertices));
    
    int triangles[1][3] = {{0, 1, 2}};
    
    // Note: we pass nullptr for vertices since the object takes ownership
    // We need to allocate on the heap since the destructor will free them
    GfxGouraudVertex *heapVertices = (GfxGouraudVertex *)gmallocn(3, sizeof(GfxGouraudVertex));
    memset(heapVertices, 0, 3 * sizeof(GfxGouraudVertex));
    
    int (*heapTriangles)[3] = (int (*)[3])gmallocn(1, 3 * sizeof(int));
    heapTriangles[0][0] = 0;
    heapTriangles[0][1] = 1;
    heapTriangles[0][2] = 2;
    
    GfxGouraudTriangleShading shading(4, heapVertices, 3, heapTriangles, 1, std::move(funcs));
    EXPECT_EQ(shading.getNTriangles(), 1);
}

// Test getNTriangles with multiple triangles
TEST_F(GfxGouraudTriangleShadingTest_520, GetNTrianglesMultiple_520) {
    std::vector<std::unique_ptr<Function>> funcs;
    
    int nVerts = 6;
    int nTris = 4;
    
    GfxGouraudVertex *heapVertices = (GfxGouraudVertex *)gmallocn(nVerts, sizeof(GfxGouraudVertex));
    memset(heapVertices, 0, nVerts * sizeof(GfxGouraudVertex));
    
    int (*heapTriangles)[3] = (int (*)[3])gmallocn(nTris, 3 * sizeof(int));
    for (int i = 0; i < nTris; i++) {
        heapTriangles[i][0] = 0;
        heapTriangles[i][1] = 1;
        heapTriangles[i][2] = 2;
    }
    
    GfxGouraudTriangleShading shading(4, heapVertices, nVerts, heapTriangles, nTris, std::move(funcs));
    EXPECT_EQ(shading.getNTriangles(), nTris);
}

// Test copy constructor preserves nTriangles
TEST_F(GfxGouraudTriangleShadingTest_520, CopyPreservesNTriangles_520) {
    std::vector<std::unique_ptr<Function>> funcs;
    
    int nVerts = 3;
    int nTris = 1;
    
    GfxGouraudVertex *heapVertices = (GfxGouraudVertex *)gmallocn(nVerts, sizeof(GfxGouraudVertex));
    memset(heapVertices, 0, nVerts * sizeof(GfxGouraudVertex));
    
    int (*heapTriangles)[3] = (int (*)[3])gmallocn(nTris, 3 * sizeof(int));
    heapTriangles[0][0] = 0;
    heapTriangles[0][1] = 1;
    heapTriangles[0][2] = 2;
    
    GfxGouraudTriangleShading original(4, heapVertices, nVerts, heapTriangles, nTris, std::move(funcs));
    
    GfxGouraudTriangleShading copied(&original);
    EXPECT_EQ(copied.getNTriangles(), original.getNTriangles());
}

// Test that getNTriangles is const-correct
TEST_F(GfxGouraudTriangleShadingTest_520, GetNTrianglesConst_520) {
    std::vector<std::unique_ptr<Function>> funcs;
    
    GfxGouraudTriangleShading shading(4, nullptr, 0, nullptr, 0, std::move(funcs));
    
    const GfxGouraudTriangleShading &constRef = shading;
    EXPECT_EQ(constRef.getNTriangles(), 0);
}
