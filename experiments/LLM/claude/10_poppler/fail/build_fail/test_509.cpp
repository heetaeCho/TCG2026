#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"

// Since GfxUnivariateShading is abstract (inherits from GfxShading) and has
// complex dependencies, we need to test through concrete subclasses or
// by constructing instances where possible. We'll test getDomain1() and
// other public accessors through available concrete subclasses.

// GfxAxialShading and GfxRadialShading are concrete subclasses of GfxUnivariateShading
// We'll attempt to use the copy constructor or other available construction methods.

class GfxUnivariateShadingTest_509 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test getDomain0 and getDomain1 with GfxAxialShading parsed from a minimal setup
// Since we can't easily construct these objects without a full PDF parsing pipeline,
// we test what we can through the interface.

// We'll try to use GfxAxialShading as a concrete subclass
// GfxAxialShading is type 2 shading, GfxRadialShading is type 3

TEST_F(GfxUnivariateShadingTest_509, GetDomain1ReturnsT1Value_509) {
    // Create a GfxAxialShading with known domain values
    // GfxUnivariateShading(int typeA, double t0A, double t1A, std::vector<std::unique_ptr<Function>>&& funcsA, bool extend0A, bool extend1A)
    
    std::vector<std::unique_ptr<Function>> funcs;
    // Type 2 = axial shading, domain [0.0, 1.0]
    GfxAxialShading shading(0, 0, 0, 0, 0.0, 1.0, std::move(funcs), false, false);
    
    EXPECT_DOUBLE_EQ(shading.getDomain1(), 1.0);
}

TEST_F(GfxUnivariateShadingTest_509, GetDomain0ReturnsT0Value_509) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0, 0, 0, 0, 0.0, 1.0, std::move(funcs), false, false);
    
    EXPECT_DOUBLE_EQ(shading.getDomain0(), 0.0);
}

TEST_F(GfxUnivariateShadingTest_509, GetDomain1WithNonDefaultValue_509) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0, 0, 0, 0, -5.0, 10.5, std::move(funcs), false, false);
    
    EXPECT_DOUBLE_EQ(shading.getDomain1(), 10.5);
}

TEST_F(GfxUnivariateShadingTest_509, GetDomain0WithNegativeValue_509) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0, 0, 0, 0, -3.14, 2.71, std::move(funcs), false, false);
    
    EXPECT_DOUBLE_EQ(shading.getDomain0(), -3.14);
}

TEST_F(GfxUnivariateShadingTest_509, GetExtend0ReturnsFalse_509) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0, 0, 0, 0, 0.0, 1.0, std::move(funcs), false, true);
    
    EXPECT_FALSE(shading.getExtend0());
}

TEST_F(GfxUnivariateShadingTest_509, GetExtend0ReturnsTrue_509) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0, 0, 0, 0, 0.0, 1.0, std::move(funcs), true, false);
    
    EXPECT_TRUE(shading.getExtend0());
}

TEST_F(GfxUnivariateShadingTest_509, GetExtend1ReturnsFalse_509) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0, 0, 0, 0, 0.0, 1.0, std::move(funcs), true, false);
    
    EXPECT_FALSE(shading.getExtend1());
}

TEST_F(GfxUnivariateShadingTest_509, GetExtend1ReturnsTrue_509) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0, 0, 0, 0, 0.0, 1.0, std::move(funcs), false, true);
    
    EXPECT_TRUE(shading.getExtend1());
}

TEST_F(GfxUnivariateShadingTest_509, GetNFuncsReturnsZeroWhenEmpty_509) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0, 0, 0, 0, 0.0, 1.0, std::move(funcs), false, false);
    
    EXPECT_EQ(shading.getNFuncs(), 0);
}

TEST_F(GfxUnivariateShadingTest_509, DomainBoundaryZeroZero_509) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0, 0, 0, 0, 0.0, 0.0, std::move(funcs), false, false);
    
    EXPECT_DOUBLE_EQ(shading.getDomain0(), 0.0);
    EXPECT_DOUBLE_EQ(shading.getDomain1(), 0.0);
}

TEST_F(GfxUnivariateShadingTest_509, DomainLargeValues_509) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0, 0, 0, 0, -1e10, 1e10, std::move(funcs), false, false);
    
    EXPECT_DOUBLE_EQ(shading.getDomain0(), -1e10);
    EXPECT_DOUBLE_EQ(shading.getDomain1(), 1e10);
}

TEST_F(GfxUnivariateShadingTest_509, BothExtendsTrue_509) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0, 0, 0, 0, 0.0, 1.0, std::move(funcs), true, true);
    
    EXPECT_TRUE(shading.getExtend0());
    EXPECT_TRUE(shading.getExtend1());
}

TEST_F(GfxUnivariateShadingTest_509, BothExtendsFalse_509) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0, 0, 0, 0, 0.0, 1.0, std::move(funcs), false, false);
    
    EXPECT_FALSE(shading.getExtend0());
    EXPECT_FALSE(shading.getExtend1());
}

// Test with GfxRadialShading as another concrete subclass
TEST_F(GfxUnivariateShadingTest_509, RadialShadingGetDomain1_509) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxRadialShading shading(0, 0, 0, 0, 0, 0, 0.5, 2.5, std::move(funcs), false, false);
    
    EXPECT_DOUBLE_EQ(shading.getDomain1(), 2.5);
}

TEST_F(GfxUnivariateShadingTest_509, RadialShadingGetDomain0_509) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxRadialShading shading(0, 0, 0, 0, 0, 0, 0.5, 2.5, std::move(funcs), true, true);
    
    EXPECT_DOUBLE_EQ(shading.getDomain0(), 0.5);
}
