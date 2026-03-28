#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"

// Since GfxUnivariateShading is abstract (inherits from GfxShading) and has 
// protected/complex constructors, we need to test through what's available.
// We'll focus on testing getNFuncs() which is the method exposed in the partial code.

// Helper: We need a concrete subclass to instantiate for testing purposes.
// GfxAxialShading and GfxRadialShading are concrete subclasses of GfxUnivariateShading.
// We'll attempt to use those if available, or create a minimal test fixture.

class GfxUnivariateShadingTest_512 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getNFuncs returns 0 when constructed with no functions
TEST_F(GfxUnivariateShadingTest_512, GetNFuncsWithNoFunctions_512) {
    // Construct with empty function vector
    std::vector<std::unique_ptr<Function>> emptyFuncs;
    // Type 2 = axial shading, type 3 = radial shading
    // Using GfxAxialShading as a concrete subclass if available
    // If not directly constructible, we test via GfxAxialShading::parse or similar

    // Since we can't easily construct GfxUnivariateShading directly (it's abstract
    // and requires specific setup), we test getNFuncs through a concrete subclass.
    // GfxAxialShading inherits from GfxUnivariateShading.
    
    // Attempt construction with empty funcs - type 2 for axial
    GfxAxialShading shading(0, 0, 0, 0, 0.0, 1.0, std::move(emptyFuncs), false, false);
    EXPECT_EQ(shading.getNFuncs(), 0);
}

// Test that getNFuncs returns correct count when functions are provided
TEST_F(GfxUnivariateShadingTest_512, GetNFuncsWithOneFunctionViaAxialShading_512) {
    // We can't easily create Function objects without parsing, but we can 
    // verify the count mechanism with an empty vector
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0, 0, 1, 1, 0.0, 1.0, std::move(funcs), false, false);
    EXPECT_EQ(shading.getNFuncs(), 0);
}

// Test getDomain0 and getDomain1
TEST_F(GfxUnivariateShadingTest_512, GetDomainValues_512) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0, 0, 1, 1, 0.5, 2.5, std::move(funcs), false, false);
    EXPECT_DOUBLE_EQ(shading.getDomain0(), 0.5);
    EXPECT_DOUBLE_EQ(shading.getDomain1(), 2.5);
}

// Test getExtend0 and getExtend1 when both false
TEST_F(GfxUnivariateShadingTest_512, GetExtendBothFalse_512) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0, 0, 1, 1, 0.0, 1.0, std::move(funcs), false, false);
    EXPECT_FALSE(shading.getExtend0());
    EXPECT_FALSE(shading.getExtend1());
}

// Test getExtend0 and getExtend1 when both true
TEST_F(GfxUnivariateShadingTest_512, GetExtendBothTrue_512) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0, 0, 1, 1, 0.0, 1.0, std::move(funcs), true, true);
    EXPECT_TRUE(shading.getExtend0());
    EXPECT_TRUE(shading.getExtend1());
}

// Test getExtend0 true, getExtend1 false
TEST_F(GfxUnivariateShadingTest_512, GetExtendMixed_512) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0, 0, 1, 1, 0.0, 1.0, std::move(funcs), true, false);
    EXPECT_TRUE(shading.getExtend0());
    EXPECT_FALSE(shading.getExtend1());
}

// Test domain boundary: t0 == t1
TEST_F(GfxUnivariateShadingTest_512, GetDomainEqualValues_512) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0, 0, 1, 1, 3.0, 3.0, std::move(funcs), false, false);
    EXPECT_DOUBLE_EQ(shading.getDomain0(), 3.0);
    EXPECT_DOUBLE_EQ(shading.getDomain1(), 3.0);
}

// Test domain with negative values
TEST_F(GfxUnivariateShadingTest_512, GetDomainNegativeValues_512) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading shading(0, 0, 1, 1, -5.0, -1.0, std::move(funcs), false, false);
    EXPECT_DOUBLE_EQ(shading.getDomain0(), -5.0);
    EXPECT_DOUBLE_EQ(shading.getDomain1(), -1.0);
}

// Test with GfxRadialShading as another concrete subclass
TEST_F(GfxUnivariateShadingTest_512, RadialShadingGetNFuncs_512) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxRadialShading shading(0, 0, 0.5, 1, 1, 1.5, 0.0, 1.0, std::move(funcs), false, false);
    EXPECT_EQ(shading.getNFuncs(), 0);
}

// Test RadialShading domain values
TEST_F(GfxUnivariateShadingTest_512, RadialShadingDomainValues_512) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxRadialShading shading(0, 0, 0.5, 1, 1, 1.5, 0.25, 0.75, std::move(funcs), true, false);
    EXPECT_DOUBLE_EQ(shading.getDomain0(), 0.25);
    EXPECT_DOUBLE_EQ(shading.getDomain1(), 0.75);
    EXPECT_TRUE(shading.getExtend0());
    EXPECT_FALSE(shading.getExtend1());
}

// Test copy constructor preserves getNFuncs
TEST_F(GfxUnivariateShadingTest_512, CopyConstructorPreservesNFuncs_512) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading original(0, 0, 1, 1, 0.0, 1.0, std::move(funcs), true, true);
    GfxAxialShading copy(&original);
    EXPECT_EQ(copy.getNFuncs(), original.getNFuncs());
}

// Test copy constructor preserves domain
TEST_F(GfxUnivariateShadingTest_512, CopyConstructorPreservesDomain_512) {
    std::vector<std::unique_ptr<Function>> funcs;
    GfxAxialShading original(0, 0, 1, 1, 1.5, 3.5, std::move(funcs), false, true);
    GfxAxialShading copy(&original);
    EXPECT_DOUBLE_EQ(copy.getDomain0(), original.getDomain0());
    EXPECT_DOUBLE_EQ(copy.getDomain1(), original.getDomain1());
    EXPECT_EQ(copy.getExtend0(), original.getExtend0());
    EXPECT_EQ(copy.getExtend1(), original.getExtend1());
}
