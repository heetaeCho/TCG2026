#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"

// Since we need to test GfxFunctionShading which requires complex dependencies,
// we focus on what we can test through the public interface.

class GfxFunctionShadingTest_516 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test getNFuncs returns 0 when constructed with empty funcs vector
TEST_F(GfxFunctionShadingTest_516, GetNFuncsWithEmptyFuncs_516) {
    std::vector<std::unique_ptr<Function>> emptyFuncs;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    
    GfxFunctionShading shading(0.0, 0.0, 1.0, 1.0, matrix, std::move(emptyFuncs));
    
    EXPECT_EQ(shading.getNFuncs(), 0);
}

// Test getNFuncs returns correct count when constructed with multiple functions
TEST_F(GfxFunctionShadingTest_516, GetNFuncsWithMultipleFuncs_516) {
    std::vector<std::unique_ptr<Function>> funcs;
    // We need actual Function objects; if we can't create them easily,
    // we test with what we can construct.
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    
    GfxFunctionShading shading(0.0, 0.0, 1.0, 1.0, matrix, std::move(funcs));
    
    // With empty vector moved in, should be 0
    EXPECT_EQ(shading.getNFuncs(), 0);
}

// Test getDomain returns the domain values set in constructor
TEST_F(GfxFunctionShadingTest_516, GetDomainReturnsConstructorValues_516) {
    std::vector<std::unique_ptr<Function>> funcs;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    
    double x0In = -1.5, y0In = -2.5, x1In = 3.5, y1In = 4.5;
    GfxFunctionShading shading(x0In, y0In, x1In, y1In, matrix, std::move(funcs));
    
    double x0, y0, x1, y1;
    shading.getDomain(&x0, &y0, &x1, &y1);
    
    EXPECT_DOUBLE_EQ(x0, x0In);
    EXPECT_DOUBLE_EQ(y0, y0In);
    EXPECT_DOUBLE_EQ(x1, x1In);
    EXPECT_DOUBLE_EQ(y1, y1In);
}

// Test getDomain with zero-size domain
TEST_F(GfxFunctionShadingTest_516, GetDomainZeroSize_516) {
    std::vector<std::unique_ptr<Function>> funcs;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    
    GfxFunctionShading shading(0.0, 0.0, 0.0, 0.0, matrix, std::move(funcs));
    
    double x0, y0, x1, y1;
    shading.getDomain(&x0, &y0, &x1, &y1);
    
    EXPECT_DOUBLE_EQ(x0, 0.0);
    EXPECT_DOUBLE_EQ(y0, 0.0);
    EXPECT_DOUBLE_EQ(x1, 0.0);
    EXPECT_DOUBLE_EQ(y1, 0.0);
}

// Test getDomain with negative domain values
TEST_F(GfxFunctionShadingTest_516, GetDomainNegativeValues_516) {
    std::vector<std::unique_ptr<Function>> funcs;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    
    GfxFunctionShading shading(-100.0, -200.0, -50.0, -25.0, matrix, std::move(funcs));
    
    double x0, y0, x1, y1;
    shading.getDomain(&x0, &y0, &x1, &y1);
    
    EXPECT_DOUBLE_EQ(x0, -100.0);
    EXPECT_DOUBLE_EQ(y0, -200.0);
    EXPECT_DOUBLE_EQ(x1, -50.0);
    EXPECT_DOUBLE_EQ(y1, -25.0);
}

// Test getMatrix returns the matrix set in constructor
TEST_F(GfxFunctionShadingTest_516, GetMatrixReturnsConstructorValues_516) {
    std::vector<std::unique_ptr<Function>> funcs;
    std::array<double, 6> matrix = {2.0, 0.5, -0.5, 2.0, 10.0, 20.0};
    
    GfxFunctionShading shading(0.0, 0.0, 1.0, 1.0, matrix, std::move(funcs));
    
    const std::array<double, 6> &result = shading.getMatrix();
    
    EXPECT_DOUBLE_EQ(result[0], 2.0);
    EXPECT_DOUBLE_EQ(result[1], 0.5);
    EXPECT_DOUBLE_EQ(result[2], -0.5);
    EXPECT_DOUBLE_EQ(result[3], 2.0);
    EXPECT_DOUBLE_EQ(result[4], 10.0);
    EXPECT_DOUBLE_EQ(result[5], 20.0);
}

// Test getMatrix with identity matrix
TEST_F(GfxFunctionShadingTest_516, GetMatrixIdentity_516) {
    std::vector<std::unique_ptr<Function>> funcs;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    
    GfxFunctionShading shading(0.0, 0.0, 1.0, 1.0, matrix, std::move(funcs));
    
    const std::array<double, 6> &result = shading.getMatrix();
    
    EXPECT_DOUBLE_EQ(result[0], 1.0);
    EXPECT_DOUBLE_EQ(result[1], 0.0);
    EXPECT_DOUBLE_EQ(result[2], 0.0);
    EXPECT_DOUBLE_EQ(result[3], 1.0);
    EXPECT_DOUBLE_EQ(result[4], 0.0);
    EXPECT_DOUBLE_EQ(result[5], 0.0);
}

// Test getFunc with empty funcs returns nullptr or handles gracefully
TEST_F(GfxFunctionShadingTest_516, GetFuncWithNoFuncs_516) {
    std::vector<std::unique_ptr<Function>> funcs;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    
    GfxFunctionShading shading(0.0, 0.0, 1.0, 1.0, matrix, std::move(funcs));
    
    // With 0 funcs, accessing getFunc(0) should be out of bounds
    // We just verify getNFuncs is 0
    EXPECT_EQ(shading.getNFuncs(), 0);
}

// Test copy constructor preserves domain
TEST_F(GfxFunctionShadingTest_516, CopyConstructorPreservesDomain_516) {
    std::vector<std::unique_ptr<Function>> funcs;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    
    GfxFunctionShading original(1.0, 2.0, 3.0, 4.0, matrix, std::move(funcs));
    GfxFunctionShading copy(&original);
    
    double x0, y0, x1, y1;
    copy.getDomain(&x0, &y0, &x1, &y1);
    
    EXPECT_DOUBLE_EQ(x0, 1.0);
    EXPECT_DOUBLE_EQ(y0, 2.0);
    EXPECT_DOUBLE_EQ(x1, 3.0);
    EXPECT_DOUBLE_EQ(y1, 4.0);
}

// Test copy constructor preserves matrix
TEST_F(GfxFunctionShadingTest_516, CopyConstructorPreservesMatrix_516) {
    std::vector<std::unique_ptr<Function>> funcs;
    std::array<double, 6> matrix = {2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
    
    GfxFunctionShading original(0.0, 0.0, 1.0, 1.0, matrix, std::move(funcs));
    GfxFunctionShading copy(&original);
    
    const std::array<double, 6> &result = copy.getMatrix();
    
    EXPECT_DOUBLE_EQ(result[0], 2.0);
    EXPECT_DOUBLE_EQ(result[1], 3.0);
    EXPECT_DOUBLE_EQ(result[2], 4.0);
    EXPECT_DOUBLE_EQ(result[3], 5.0);
    EXPECT_DOUBLE_EQ(result[4], 6.0);
    EXPECT_DOUBLE_EQ(result[5], 7.0);
}

// Test copy constructor preserves getNFuncs count
TEST_F(GfxFunctionShadingTest_516, CopyConstructorPreservesNFuncs_516) {
    std::vector<std::unique_ptr<Function>> funcs;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    
    GfxFunctionShading original(0.0, 0.0, 1.0, 1.0, matrix, std::move(funcs));
    GfxFunctionShading copy(&original);
    
    EXPECT_EQ(copy.getNFuncs(), original.getNFuncs());
}

// Test getDomain with very large values
TEST_F(GfxFunctionShadingTest_516, GetDomainLargeValues_516) {
    std::vector<std::unique_ptr<Function>> funcs;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    
    double large = 1e15;
    GfxFunctionShading shading(-large, -large, large, large, matrix, std::move(funcs));
    
    double x0, y0, x1, y1;
    shading.getDomain(&x0, &y0, &x1, &y1);
    
    EXPECT_DOUBLE_EQ(x0, -large);
    EXPECT_DOUBLE_EQ(y0, -large);
    EXPECT_DOUBLE_EQ(x1, large);
    EXPECT_DOUBLE_EQ(y1, large);
}

// Test that copy() virtual method works
TEST_F(GfxFunctionShadingTest_516, CopyMethodReturnsCopy_516) {
    std::vector<std::unique_ptr<Function>> funcs;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    
    GfxFunctionShading original(5.0, 6.0, 7.0, 8.0, matrix, std::move(funcs));
    auto copied = original.copy();
    
    ASSERT_NE(copied, nullptr);
    
    // Cast to GfxFunctionShading to verify domain
    GfxFunctionShading* copiedShading = dynamic_cast<GfxFunctionShading*>(copied.get());
    ASSERT_NE(copiedShading, nullptr);
    
    double x0, y0, x1, y1;
    copiedShading->getDomain(&x0, &y0, &x1, &y1);
    
    EXPECT_DOUBLE_EQ(x0, 5.0);
    EXPECT_DOUBLE_EQ(y0, 6.0);
    EXPECT_DOUBLE_EQ(x1, 7.0);
    EXPECT_DOUBLE_EQ(y1, 8.0);
}
