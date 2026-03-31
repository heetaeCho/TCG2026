#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"

// Since GfxUnivariateShading is abstract (inherits from GfxShading which has pure virtuals)
// and has complex construction requirements, we need to test through concrete subclasses.
// However, based on the constraints, we test the interface as provided.

// We'll use GfxAxialShading or GfxRadialShading as concrete subclasses if available,
// or we create a minimal testable wrapper.

// For testing getDomain0, getDomain1, getExtend0, getExtend1, we need concrete instances.
// GfxAxialShading and GfxRadialShading are concrete subclasses of GfxUnivariateShading.

class GfxUnivariateShadingTest_508 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getDomain0 returns the t0 value set during construction
TEST_F(GfxUnivariateShadingTest_508, GetDomain0_ReturnsT0_508) {
    // Create a GfxUnivariateShading via a concrete subclass
    // Using the constructor with int typeA, double t0A, double t1A, int&& funcsA, bool extend0A, bool extend1A
    // Since GfxUnivariateShading may not be directly instantiable, we test through
    // GfxAxialShading::parse if available, or use the copy constructor approach.
    
    // We'll attempt to construct using the simplest available path.
    // GfxAxialShading is a concrete subclass of GfxUnivariateShading.
    
    double t0 = 0.0;
    double t1 = 1.0;
    std::vector<std::unique_ptr<Function>> funcs;
    
    // Try creating via GfxAxialShading constructor if accessible
    // GfxAxialShading(double x0A, double y0A, double x1A, double y1A,
    //                 double t0A, double t1A, vector<unique_ptr<Function>>&& funcsA,
    //                 bool extend0A, bool extend1A)
    
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, t0, t1, std::move(funcs), false, false);
    EXPECT_DOUBLE_EQ(shading.getDomain0(), t0);
}

// Test getDomain0 with non-zero value
TEST_F(GfxUnivariateShadingTest_508, GetDomain0_NonZeroValue_508) {
    double t0 = 0.5;
    double t1 = 2.0;
    std::vector<std::unique_ptr<Function>> funcs;
    
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, t0, t1, std::move(funcs), false, false);
    EXPECT_DOUBLE_EQ(shading.getDomain0(), 0.5);
}

// Test getDomain1 returns the t1 value
TEST_F(GfxUnivariateShadingTest_508, GetDomain1_ReturnsT1_508) {
    double t0 = 0.0;
    double t1 = 1.0;
    std::vector<std::unique_ptr<Function>> funcs;
    
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, t0, t1, std::move(funcs), true, false);
    EXPECT_DOUBLE_EQ(shading.getDomain1(), t1);
}

// Test getDomain1 with custom value
TEST_F(GfxUnivariateShadingTest_508, GetDomain1_CustomValue_508) {
    double t0 = -1.0;
    double t1 = 3.5;
    std::vector<std::unique_ptr<Function>> funcs;
    
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, t0, t1, std::move(funcs), false, true);
    EXPECT_DOUBLE_EQ(shading.getDomain1(), 3.5);
}

// Test getExtend0 returns false
TEST_F(GfxUnivariateShadingTest_508, GetExtend0_ReturnsFalse_508) {
    std::vector<std::unique_ptr<Function>> funcs;
    
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, 0.0, 1.0, std::move(funcs), false, false);
    EXPECT_FALSE(shading.getExtend0());
}

// Test getExtend0 returns true
TEST_F(GfxUnivariateShadingTest_508, GetExtend0_ReturnsTrue_508) {
    std::vector<std::unique_ptr<Function>> funcs;
    
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, 0.0, 1.0, std::move(funcs), true, false);
    EXPECT_TRUE(shading.getExtend0());
}

// Test getExtend1 returns false
TEST_F(GfxUnivariateShadingTest_508, GetExtend1_ReturnsFalse_508) {
    std::vector<std::unique_ptr<Function>> funcs;
    
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, 0.0, 1.0, std::move(funcs), true, false);
    EXPECT_FALSE(shading.getExtend1());
}

// Test getExtend1 returns true
TEST_F(GfxUnivariateShadingTest_508, GetExtend1_ReturnsTrue_508) {
    std::vector<std::unique_ptr<Function>> funcs;
    
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, 0.0, 1.0, std::move(funcs), false, true);
    EXPECT_TRUE(shading.getExtend1());
}

// Test getNFuncs with empty functions vector
TEST_F(GfxUnivariateShadingTest_508, GetNFuncs_EmptyFuncs_508) {
    std::vector<std::unique_ptr<Function>> funcs;
    
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, 0.0, 1.0, std::move(funcs), false, false);
    EXPECT_EQ(shading.getNFuncs(), 0);
}

// Test with negative domain values
TEST_F(GfxUnivariateShadingTest_508, GetDomain0_NegativeValue_508) {
    double t0 = -10.0;
    double t1 = -5.0;
    std::vector<std::unique_ptr<Function>> funcs;
    
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, t0, t1, std::move(funcs), false, false);
    EXPECT_DOUBLE_EQ(shading.getDomain0(), -10.0);
    EXPECT_DOUBLE_EQ(shading.getDomain1(), -5.0);
}

// Test with equal domain values (boundary)
TEST_F(GfxUnivariateShadingTest_508, GetDomain_EqualValues_508) {
    double t0 = 1.0;
    double t1 = 1.0;
    std::vector<std::unique_ptr<Function>> funcs;
    
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, t0, t1, std::move(funcs), false, false);
    EXPECT_DOUBLE_EQ(shading.getDomain0(), 1.0);
    EXPECT_DOUBLE_EQ(shading.getDomain1(), 1.0);
}

// Test with very large domain values
TEST_F(GfxUnivariateShadingTest_508, GetDomain_LargeValues_508) {
    double t0 = 1e10;
    double t1 = 1e15;
    std::vector<std::unique_ptr<Function>> funcs;
    
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, t0, t1, std::move(funcs), false, false);
    EXPECT_DOUBLE_EQ(shading.getDomain0(), 1e10);
    EXPECT_DOUBLE_EQ(shading.getDomain1(), 1e15);
}

// Test with very small domain values
TEST_F(GfxUnivariateShadingTest_508, GetDomain_VerySmallValues_508) {
    double t0 = 1e-15;
    double t1 = 1e-10;
    std::vector<std::unique_ptr<Function>> funcs;
    
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, t0, t1, std::move(funcs), false, false);
    EXPECT_DOUBLE_EQ(shading.getDomain0(), 1e-15);
    EXPECT_DOUBLE_EQ(shading.getDomain1(), 1e-10);
}

// Test both extend flags set to true
TEST_F(GfxUnivariateShadingTest_508, BothExtendTrue_508) {
    std::vector<std::unique_ptr<Function>> funcs;
    
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, 0.0, 1.0, std::move(funcs), true, true);
    EXPECT_TRUE(shading.getExtend0());
    EXPECT_TRUE(shading.getExtend1());
}

// Test copy constructor preserves domain values
TEST_F(GfxUnivariateShadingTest_508, CopyConstructor_PreservesDomain_508) {
    std::vector<std::unique_ptr<Function>> funcs;
    
    GfxAxialShading original(0.0, 0.0, 1.0, 1.0, 0.25, 0.75, std::move(funcs), true, false);
    GfxAxialShading copy(&original);
    
    EXPECT_DOUBLE_EQ(copy.getDomain0(), 0.25);
    EXPECT_DOUBLE_EQ(copy.getDomain1(), 0.75);
    EXPECT_TRUE(copy.getExtend0());
    EXPECT_FALSE(copy.getExtend1());
}

// Test with zero domain range
TEST_F(GfxUnivariateShadingTest_508, GetDomain_ZeroValues_508) {
    double t0 = 0.0;
    double t1 = 0.0;
    std::vector<std::unique_ptr<Function>> funcs;
    
    GfxAxialShading shading(0.0, 0.0, 1.0, 1.0, t0, t1, std::move(funcs), false, false);
    EXPECT_DOUBLE_EQ(shading.getDomain0(), 0.0);
    EXPECT_DOUBLE_EQ(shading.getDomain1(), 0.0);
}

// Test using GfxRadialShading as another concrete subclass
TEST_F(GfxUnivariateShadingTest_508, RadialShading_GetDomain0_508) {
    std::vector<std::unique_ptr<Function>> funcs;
    
    GfxRadialShading shading(0.0, 0.0, 0.5, 1.0, 1.0, 1.0, 0.0, 1.0, std::move(funcs), false, true);
    EXPECT_DOUBLE_EQ(shading.getDomain0(), 0.0);
    EXPECT_DOUBLE_EQ(shading.getDomain1(), 1.0);
    EXPECT_FALSE(shading.getExtend0());
    EXPECT_TRUE(shading.getExtend1());
}
