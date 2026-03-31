#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"

// Since GfxUnivariateShading is abstract (inherits from GfxShading which has virtual methods)
// and has complex constructors, we need to find a way to instantiate it for testing.
// We'll use GfxAxialShading or GfxRadialShading as concrete subclasses if available,
// or attempt to construct GfxUnivariateShading through its copy constructor or factory methods.

// Based on the known dependencies, GfxAxialShading and GfxRadialShading are concrete subclasses
// of GfxUnivariateShading. We'll test through those if possible.

// However, since we're testing GfxUnivariateShading's interface (specifically getExtend0),
// we need concrete instances. Let's try to work with what's available.

class GfxUnivariateShadingTest_510 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test getExtend0 returns false when constructed with extend0=false
TEST_F(GfxUnivariateShadingTest_510, GetExtend0ReturnsFalseWhenSetFalse_510) {
    // Construct with extend0 = false
    std::vector<std::unique_ptr<Function>> funcs;
    // Type 2 = axial shading, type 3 = radial shading
    // We use a subclass since GfxUnivariateShading may be abstract
    // Using the constructor: GfxUnivariateShading(int typeA, double t0A, double t1A, 
    //   std::vector<std::unique_ptr<Function>>&& funcsA, bool extend0A, bool extend1A)
    // Since GfxUnivariateShading might not be directly instantiable, 
    // we try GfxAxialShading which inherits from it.
    
    // GfxAxialShading has: GfxAxialShading(double x0A, double y0A, double x1A, double y1A,
    //   double t0A, double t1A, std::vector<std::unique_ptr<Function>>&& funcsA,
    //   bool extend0A, bool extend1A)
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, 0.0, 1.0, std::move(funcs), false, true);
    EXPECT_FALSE(shading.getExtend0());
}

// Test getExtend0 returns true when constructed with extend0=true
TEST_F(GfxUnivariateShadingTest_510, GetExtend0ReturnsTrueWhenSetTrue_510) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, 0.0, 1.0, std::move(funcs), true, false);
    EXPECT_TRUE(shading.getExtend0());
}

// Test getExtend1 returns false when constructed with extend1=false
TEST_F(GfxUnivariateShadingTest_510, GetExtend1ReturnsFalseWhenSetFalse_510) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, 0.0, 1.0, std::move(funcs), true, false);
    EXPECT_FALSE(shading.getExtend1());
}

// Test getExtend1 returns true when constructed with extend1=true
TEST_F(GfxUnivariateShadingTest_510, GetExtend1ReturnsTrueWhenSetTrue_510) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, 0.0, 1.0, std::move(funcs), false, true);
    EXPECT_TRUE(shading.getExtend1());
}

// Test getDomain0 returns correct value
TEST_F(GfxUnivariateShadingTest_510, GetDomain0ReturnsCorrectValue_510) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, 0.5, 1.0, std::move(funcs), false, false);
    EXPECT_DOUBLE_EQ(0.5, shading.getDomain0());
}

// Test getDomain1 returns correct value
TEST_F(GfxUnivariateShadingTest_510, GetDomain1ReturnsCorrectValue_510) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, 0.0, 0.75, std::move(funcs), false, false);
    EXPECT_DOUBLE_EQ(0.75, shading.getDomain1());
}

// Test both extend flags set to true
TEST_F(GfxUnivariateShadingTest_510, BothExtendFlagsTrue_510) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, 0.0, 1.0, std::move(funcs), true, true);
    EXPECT_TRUE(shading.getExtend0());
    EXPECT_TRUE(shading.getExtend1());
}

// Test both extend flags set to false
TEST_F(GfxUnivariateShadingTest_510, BothExtendFlagsFalse_510) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, 0.0, 1.0, std::move(funcs), false, false);
    EXPECT_FALSE(shading.getExtend0());
    EXPECT_FALSE(shading.getExtend1());
}

// Test getNFuncs returns 0 when no functions provided
TEST_F(GfxUnivariateShadingTest_510, GetNFuncsReturnsZeroWhenEmpty_510) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, 0.0, 1.0, std::move(funcs), false, false);
    EXPECT_EQ(0, shading.getNFuncs());
}

// Test domain boundary values
TEST_F(GfxUnivariateShadingTest_510, DomainBoundaryValues_510) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, -1e10, 1e10, std::move(funcs), false, false);
    EXPECT_DOUBLE_EQ(-1e10, shading.getDomain0());
    EXPECT_DOUBLE_EQ(1e10, shading.getDomain1());
}

// Test domain with equal t0 and t1
TEST_F(GfxUnivariateShadingTest_510, DomainEqualValues_510) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, 0.5, 0.5, std::move(funcs), false, false);
    EXPECT_DOUBLE_EQ(0.5, shading.getDomain0());
    EXPECT_DOUBLE_EQ(0.5, shading.getDomain1());
}

// Test with negative domain values
TEST_F(GfxUnivariateShadingTest_510, NegativeDomainValues_510) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, -2.0, -1.0, std::move(funcs), true, true);
    EXPECT_DOUBLE_EQ(-2.0, shading.getDomain0());
    EXPECT_DOUBLE_EQ(-1.0, shading.getDomain1());
    EXPECT_TRUE(shading.getExtend0());
    EXPECT_TRUE(shading.getExtend1());
}

// Test using GfxRadialShading as another concrete subclass
TEST_F(GfxUnivariateShadingTest_510, RadialShadingGetExtend0_510) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxRadialShading shading(0.0, 0.0, 0.5, 1.0, 1.0, 1.5, 0.0, 1.0, std::move(funcs), true, false);
    EXPECT_TRUE(shading.getExtend0());
    EXPECT_FALSE(shading.getExtend1());
}

// Test copy constructor preserves extend0
TEST_F(GfxUnivariateShadingTest_510, CopyConstructorPreservesExtend0_510) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading original(0.0, 0.0, 1.0, 1.0, 0.0, 1.0, std::move(funcs), true, false);
    GfxAxialShading copy(&original);
    EXPECT_TRUE(copy.getExtend0());
    EXPECT_FALSE(copy.getExtend1());
    EXPECT_DOUBLE_EQ(original.getDomain0(), copy.getDomain0());
    EXPECT_DOUBLE_EQ(original.getDomain1(), copy.getDomain1());
}

// Test domain with zero values
TEST_F(GfxUnivariateShadingTest_510, DomainZeroValues_510) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, 0.0, 0.0, std::move(funcs), false, false);
    EXPECT_DOUBLE_EQ(0.0, shading.getDomain0());
    EXPECT_DOUBLE_EQ(0.0, shading.getDomain1());
}
