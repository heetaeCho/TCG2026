#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cstring>

#include "GfxState.h"
#include "Function.h"

// We need a concrete Function implementation for testing purposes.
// This is a minimal mock/stub that provides the interface needed.
class StubFunction : public Function {
public:
    StubFunction(double domainMin, double domainMax) {
        m = 1; // one input
        domain[0][0] = domainMin;
        domain[0][1] = domainMax;
        hasRange = true;
        range[0][0] = 0.0;
        range[0][1] = 1.0;
    }

    const std::unique_ptr<Function> copy() const override {
        return std::make_unique<StubFunction>(domain[0][0], domain[0][1]);
    }

    const Function::Type getType() const override {
        return Function::Type::Sampled;
    }

    const void transform(const double *in, double *out) const override {
        out[0] = in[0];
    }

    const bool isOk() const override { return true; }
};

class GfxGouraudTriangleShadingTest_522 : public ::testing::Test {
protected:
    // Helper to create a parameterized GfxGouraudTriangleShading with given domain
    std::unique_ptr<GfxGouraudTriangleShading> createParameterizedShading(
        double domainMin, double domainMax, int type = 4) {
        
        // Create vertices - need at least 3 for one triangle
        int nVertices = 3;
        GfxGouraudVertex *vertices = (GfxGouraudVertex *)gmallocn(nVertices, sizeof(GfxGouraudVertex));
        memset(vertices, 0, nVertices * sizeof(GfxGouraudVertex));
        
        // Set up some basic vertex data
        vertices[0].x = 0.0; vertices[0].y = 0.0;
        vertices[1].x = 1.0; vertices[1].y = 0.0;
        vertices[2].x = 0.5; vertices[2].y = 1.0;
        
        // For parameterized shading, color values are parameters
        vertices[0].color.c[0] = 0;
        vertices[1].color.c[0] = 32768;
        vertices[2].color.c[0] = 65535;
        
        int nTriangles = 1;
        int (*triangles)[3] = (int (*)[3])gmallocn(nTriangles, 3 * sizeof(int));
        triangles[0][0] = 0;
        triangles[0][1] = 1;
        triangles[0][2] = 2;
        
        std::vector<std::unique_ptr<Function>> funcs;
        funcs.push_back(std::make_unique<StubFunction>(domainMin, domainMax));
        
        return std::make_unique<GfxGouraudTriangleShading>(
            type, vertices, nVertices, triangles, nTriangles, std::move(funcs));
    }
    
    // Helper to create a non-parameterized shading (no functions)
    std::unique_ptr<GfxGouraudTriangleShading> createNonParameterizedShading(int type = 4) {
        int nVertices = 3;
        GfxGouraudVertex *vertices = (GfxGouraudVertex *)gmallocn(nVertices, sizeof(GfxGouraudVertex));
        memset(vertices, 0, nVertices * sizeof(GfxGouraudVertex));
        
        vertices[0].x = 0.0; vertices[0].y = 0.0;
        vertices[1].x = 1.0; vertices[1].y = 0.0;
        vertices[2].x = 0.5; vertices[2].y = 1.0;
        
        int nTriangles = 1;
        int (*triangles)[3] = (int (*)[3])gmallocn(nTriangles, 3 * sizeof(int));
        triangles[0][0] = 0;
        triangles[0][1] = 1;
        triangles[0][2] = 2;
        
        std::vector<std::unique_ptr<Function>> funcs; // empty - no parameterization
        
        return std::make_unique<GfxGouraudTriangleShading>(
            type, vertices, nVertices, triangles, nTriangles, std::move(funcs));
    }
};

// Test that isParameterized returns true when functions are provided
TEST_F(GfxGouraudTriangleShadingTest_522, IsParameterized_WithFunctions_522) {
    auto shading = createParameterizedShading(0.0, 1.0);
    ASSERT_NE(shading, nullptr);
    EXPECT_TRUE(shading->isParameterized());
}

// Test that isParameterized returns false when no functions are provided
TEST_F(GfxGouraudTriangleShadingTest_522, IsNotParameterized_WithoutFunctions_522) {
    auto shading = createNonParameterizedShading();
    ASSERT_NE(shading, nullptr);
    EXPECT_FALSE(shading->isParameterized());
}

// Test getParameterDomainMin returns correct value
TEST_F(GfxGouraudTriangleShadingTest_522, GetParameterDomainMin_ReturnsCorrectValue_522) {
    auto shading = createParameterizedShading(0.0, 1.0);
    ASSERT_NE(shading, nullptr);
    ASSERT_TRUE(shading->isParameterized());
    EXPECT_DOUBLE_EQ(shading->getParameterDomainMin(), 0.0);
}

// Test getParameterDomainMax returns correct value
TEST_F(GfxGouraudTriangleShadingTest_522, GetParameterDomainMax_ReturnsCorrectValue_522) {
    auto shading = createParameterizedShading(0.0, 1.0);
    ASSERT_NE(shading, nullptr);
    ASSERT_TRUE(shading->isParameterized());
    EXPECT_DOUBLE_EQ(shading->getParameterDomainMax(), 1.0);
}

// Test domain with non-zero minimum
TEST_F(GfxGouraudTriangleShadingTest_522, GetParameterDomainMin_NonZero_522) {
    auto shading = createParameterizedShading(0.5, 2.5);
    ASSERT_NE(shading, nullptr);
    ASSERT_TRUE(shading->isParameterized());
    EXPECT_DOUBLE_EQ(shading->getParameterDomainMin(), 0.5);
}

// Test domain with non-standard maximum
TEST_F(GfxGouraudTriangleShadingTest_522, GetParameterDomainMax_NonStandard_522) {
    auto shading = createParameterizedShading(0.5, 2.5);
    ASSERT_NE(shading, nullptr);
    ASSERT_TRUE(shading->isParameterized());
    EXPECT_DOUBLE_EQ(shading->getParameterDomainMax(), 2.5);
}

// Test with negative domain values
TEST_F(GfxGouraudTriangleShadingTest_522, GetParameterDomain_NegativeValues_522) {
    auto shading = createParameterizedShading(-1.0, 1.0);
    ASSERT_NE(shading, nullptr);
    ASSERT_TRUE(shading->isParameterized());
    EXPECT_DOUBLE_EQ(shading->getParameterDomainMin(), -1.0);
    EXPECT_DOUBLE_EQ(shading->getParameterDomainMax(), 1.0);
}

// Test with very large domain values
TEST_F(GfxGouraudTriangleShadingTest_522, GetParameterDomain_LargeValues_522) {
    auto shading = createParameterizedShading(-1e10, 1e10);
    ASSERT_NE(shading, nullptr);
    ASSERT_TRUE(shading->isParameterized());
    EXPECT_DOUBLE_EQ(shading->getParameterDomainMin(), -1e10);
    EXPECT_DOUBLE_EQ(shading->getParameterDomainMax(), 1e10);
}

// Test with zero-width domain
TEST_F(GfxGouraudTriangleShadingTest_522, GetParameterDomain_ZeroWidth_522) {
    auto shading = createParameterizedShading(1.0, 1.0);
    ASSERT_NE(shading, nullptr);
    ASSERT_TRUE(shading->isParameterized());
    EXPECT_DOUBLE_EQ(shading->getParameterDomainMin(), 1.0);
    EXPECT_DOUBLE_EQ(shading->getParameterDomainMax(), 1.0);
}

// Test getNTriangles returns correct count
TEST_F(GfxGouraudTriangleShadingTest_522, GetNTriangles_ReturnsCorrectCount_522) {
    auto shading = createParameterizedShading(0.0, 1.0);
    ASSERT_NE(shading, nullptr);
    EXPECT_EQ(shading->getNTriangles(), 1);
}

// Test copy creates valid copy
TEST_F(GfxGouraudTriangleShadingTest_522, Copy_CreatesValidCopy_522) {
    auto shading = createParameterizedShading(0.0, 1.0);
    ASSERT_NE(shading, nullptr);
    
    auto copied = shading->copy();
    ASSERT_NE(copied, nullptr);
    
    auto copiedGouraud = dynamic_cast<GfxGouraudTriangleShading*>(copied.get());
    ASSERT_NE(copiedGouraud, nullptr);
    EXPECT_EQ(copiedGouraud->getNTriangles(), shading->getNTriangles());
    EXPECT_EQ(copiedGouraud->isParameterized(), shading->isParameterized());
}

// Test copy preserves domain values
TEST_F(GfxGouraudTriangleShadingTest_522, Copy_PreservesDomain_522) {
    auto shading = createParameterizedShading(0.25, 0.75);
    ASSERT_NE(shading, nullptr);
    
    auto copied = shading->copy();
    ASSERT_NE(copied, nullptr);
    
    auto copiedGouraud = dynamic_cast<GfxGouraudTriangleShading*>(copied.get());
    ASSERT_NE(copiedGouraud, nullptr);
    ASSERT_TRUE(copiedGouraud->isParameterized());
    EXPECT_DOUBLE_EQ(copiedGouraud->getParameterDomainMin(), 0.25);
    EXPECT_DOUBLE_EQ(copiedGouraud->getParameterDomainMax(), 0.75);
}

// Test with multiple triangles (more vertices)
TEST_F(GfxGouraudTriangleShadingTest_522, MultipleTriangles_GetNTriangles_522) {
    int nVertices = 4;
    GfxGouraudVertex *vertices = (GfxGouraudVertex *)gmallocn(nVertices, sizeof(GfxGouraudVertex));
    memset(vertices, 0, nVertices * sizeof(GfxGouraudVertex));
    
    vertices[0].x = 0.0; vertices[0].y = 0.0;
    vertices[1].x = 1.0; vertices[1].y = 0.0;
    vertices[2].x = 1.0; vertices[2].y = 1.0;
    vertices[3].x = 0.0; vertices[3].y = 1.0;
    
    int nTriangles = 2;
    int (*triangles)[3] = (int (*)[3])gmallocn(nTriangles, 3 * sizeof(int));
    triangles[0][0] = 0; triangles[0][1] = 1; triangles[0][2] = 2;
    triangles[1][0] = 0; triangles[1][1] = 2; triangles[1][2] = 3;
    
    std::vector<std::unique_ptr<Function>> funcs;
    funcs.push_back(std::make_unique<StubFunction>(0.0, 1.0));
    
    auto shading = std::make_unique<GfxGouraudTriangleShading>(
        4, vertices, nVertices, triangles, nTriangles, std::move(funcs));
    
    ASSERT_NE(shading, nullptr);
    EXPECT_EQ(shading->getNTriangles(), 2);
}

// Test that DomainMin <= DomainMax for standard cases
TEST_F(GfxGouraudTriangleShadingTest_522, DomainMinLessThanOrEqualMax_522) {
    auto shading = createParameterizedShading(0.0, 1.0);
    ASSERT_NE(shading, nullptr);
    ASSERT_TRUE(shading->isParameterized());
    EXPECT_LE(shading->getParameterDomainMin(), shading->getParameterDomainMax());
}

// Test with very small domain range
TEST_F(GfxGouraudTriangleShadingTest_522, GetParameterDomain_VerySmallRange_522) {
    auto shading = createParameterizedShading(0.0, 1e-15);
    ASSERT_NE(shading, nullptr);
    ASSERT_TRUE(shading->isParameterized());
    EXPECT_DOUBLE_EQ(shading->getParameterDomainMin(), 0.0);
    EXPECT_DOUBLE_EQ(shading->getParameterDomainMax(), 1e-15);
}
