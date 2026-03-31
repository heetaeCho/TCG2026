#include <gtest/gtest.h>
#include "Function.h"
#include <memory>
#include <cmath>
#include <vector>

// Test fixture for IdentityFunction
class IdentityFunctionTest_356 : public ::testing::Test {
protected:
    void SetUp() override {
        // IdentityFunction requires domain/range setup; we'll construct it directly
    }
};

// Test that getType returns Type::Identity
TEST_F(IdentityFunctionTest_356, GetTypeReturnsIdentity_356) {
    IdentityFunction func;
    EXPECT_EQ(func.getType(), Function::Type::Identity);
}

// Test that isOk returns true for a properly constructed IdentityFunction
TEST_F(IdentityFunctionTest_356, IsOkReturnsTrue_356) {
    IdentityFunction func;
    EXPECT_TRUE(func.isOk());
}

// Test that copy returns a non-null unique_ptr
TEST_F(IdentityFunctionTest_356, CopyReturnsNonNull_356) {
    IdentityFunction func;
    auto copied = func.copy();
    ASSERT_NE(copied, nullptr);
}

// Test that the copied function has the same type
TEST_F(IdentityFunctionTest_356, CopyPreservesType_356) {
    IdentityFunction func;
    auto copied = func.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getType(), Function::Type::Identity);
}

// Test that the copied function is also ok
TEST_F(IdentityFunctionTest_356, CopyIsOk_356) {
    IdentityFunction func;
    auto copied = func.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_TRUE(copied->isOk());
}

// Test transform with simple input - identity should pass through values
TEST_F(IdentityFunctionTest_356, TransformPassesThroughValues_356) {
    IdentityFunction func;
    double in[funcMaxInputs] = {};
    double out[funcMaxOutputs] = {};

    in[0] = 0.5;
    in[1] = 0.75;
    in[2] = 0.25;

    func.transform(in, out);

    // Identity function should copy input to output
    EXPECT_DOUBLE_EQ(out[0], 0.5);
    EXPECT_DOUBLE_EQ(out[1], 0.75);
    EXPECT_DOUBLE_EQ(out[2], 0.25);
}

// Test transform with zero values
TEST_F(IdentityFunctionTest_356, TransformWithZeroValues_356) {
    IdentityFunction func;
    double in[funcMaxInputs] = {};
    double out[funcMaxOutputs] = {};

    for (int i = 0; i < funcMaxInputs; i++) {
        in[i] = 0.0;
    }

    func.transform(in, out);

    for (int i = 0; i < funcMaxInputs; i++) {
        EXPECT_DOUBLE_EQ(out[i], 0.0);
    }
}

// Test transform with all ones
TEST_F(IdentityFunctionTest_356, TransformWithOnes_356) {
    IdentityFunction func;
    double in[funcMaxInputs] = {};
    double out[funcMaxOutputs] = {};

    for (int i = 0; i < funcMaxInputs; i++) {
        in[i] = 1.0;
    }

    func.transform(in, out);

    for (int i = 0; i < funcMaxInputs; i++) {
        EXPECT_DOUBLE_EQ(out[i], 1.0);
    }
}

// Test transform with boundary values (0 and 1)
TEST_F(IdentityFunctionTest_356, TransformBoundaryValues_356) {
    IdentityFunction func;
    double in[funcMaxInputs] = {};
    double out[funcMaxOutputs] = {};

    in[0] = 0.0;
    in[1] = 1.0;

    func.transform(in, out);

    EXPECT_DOUBLE_EQ(out[0], 0.0);
    EXPECT_DOUBLE_EQ(out[1], 1.0);
}

// Test transform with negative values (may be clamped by domain)
TEST_F(IdentityFunctionTest_356, TransformWithNegativeValues_356) {
    IdentityFunction func;
    double in[funcMaxInputs] = {};
    double out[funcMaxOutputs] = {};

    in[0] = -0.5;
    in[1] = -1.0;

    func.transform(in, out);

    // The output depends on domain clamping behavior; just ensure no crash
    // and the values are finite
    EXPECT_TRUE(std::isfinite(out[0]));
    EXPECT_TRUE(std::isfinite(out[1]));
}

// Test transform with values greater than 1 (may be clamped)
TEST_F(IdentityFunctionTest_356, TransformWithValuesGreaterThanOne_356) {
    IdentityFunction func;
    double in[funcMaxInputs] = {};
    double out[funcMaxOutputs] = {};

    in[0] = 2.0;
    in[1] = 100.0;

    func.transform(in, out);

    // The output depends on domain clamping behavior
    EXPECT_TRUE(std::isfinite(out[0]));
    EXPECT_TRUE(std::isfinite(out[1]));
}

// Test that copied function also transforms correctly
TEST_F(IdentityFunctionTest_356, CopiedFunctionTransformsCorrectly_356) {
    IdentityFunction func;
    auto copied = func.copy();
    ASSERT_NE(copied, nullptr);

    double in[funcMaxInputs] = {};
    double out1[funcMaxOutputs] = {};
    double out2[funcMaxOutputs] = {};

    in[0] = 0.3;
    in[1] = 0.7;

    func.transform(in, out1);
    copied->transform(in, out2);

    EXPECT_DOUBLE_EQ(out1[0], out2[0]);
    EXPECT_DOUBLE_EQ(out1[1], out2[1]);
}

// Test multiple successive transforms
TEST_F(IdentityFunctionTest_356, MultipleTransformsConsistent_356) {
    IdentityFunction func;
    double in[funcMaxInputs] = {};
    double out1[funcMaxOutputs] = {};
    double out2[funcMaxOutputs] = {};

    in[0] = 0.42;

    func.transform(in, out1);
    func.transform(in, out2);

    EXPECT_DOUBLE_EQ(out1[0], out2[0]);
}

// Test transform with very small values
TEST_F(IdentityFunctionTest_356, TransformWithVerySmallValues_356) {
    IdentityFunction func;
    double in[funcMaxInputs] = {};
    double out[funcMaxOutputs] = {};

    in[0] = 1e-15;
    in[1] = 1e-10;

    func.transform(in, out);

    EXPECT_TRUE(std::isfinite(out[0]));
    EXPECT_TRUE(std::isfinite(out[1]));
}

// Test transform with mid-range values
TEST_F(IdentityFunctionTest_356, TransformMidRangeValues_356) {
    IdentityFunction func;
    double in[funcMaxInputs] = {};
    double out[funcMaxOutputs] = {};

    in[0] = 0.5;

    func.transform(in, out);

    EXPECT_DOUBLE_EQ(out[0], 0.5);
}
