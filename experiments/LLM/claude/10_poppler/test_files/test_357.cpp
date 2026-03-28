#include <gtest/gtest.h>
#include <memory>
#include "Function.h"

class IdentityFunctionTest_357 : public ::testing::Test {
protected:
    void SetUp() override {
        func = std::make_unique<IdentityFunction>();
    }

    std::unique_ptr<IdentityFunction> func;
};

TEST_F(IdentityFunctionTest_357, IsOkReturnsTrue_357) {
    EXPECT_TRUE(func->isOk());
}

TEST_F(IdentityFunctionTest_357, TransformCopiesInputToOutput_357) {
    // IdentityFunction should copy input values to output values
    double in[funcMaxOutputs];
    double out[funcMaxOutputs];

    // Initialize input with known values
    for (int i = 0; i < funcMaxOutputs; i++) {
        in[i] = static_cast<double>(i) * 1.5;
        out[i] = 0.0;
    }

    func->transform(in, out);

    // For an identity function, we expect output to match input
    // (at least for the number of outputs the function produces)
    // Check the first several values
    for (int i = 0; i < func->getOutputSize(); i++) {
        EXPECT_DOUBLE_EQ(in[i], out[i]) << "Mismatch at index " << i;
    }
}

TEST_F(IdentityFunctionTest_357, TransformWithZeroValues_357) {
    double in[funcMaxOutputs] = {};
    double out[funcMaxOutputs];

    for (int i = 0; i < funcMaxOutputs; i++) {
        out[i] = 999.0; // sentinel value
    }

    func->transform(in, out);

    for (int i = 0; i < func->getOutputSize(); i++) {
        EXPECT_DOUBLE_EQ(0.0, out[i]) << "Mismatch at index " << i;
    }
}

TEST_F(IdentityFunctionTest_357, TransformWithNegativeValues_357) {
    double in[funcMaxOutputs];
    double out[funcMaxOutputs];

    for (int i = 0; i < funcMaxOutputs; i++) {
        in[i] = -static_cast<double>(i) * 2.5;
        out[i] = 0.0;
    }

    func->transform(in, out);

    for (int i = 0; i < func->getOutputSize(); i++) {
        EXPECT_DOUBLE_EQ(in[i], out[i]) << "Mismatch at index " << i;
    }
}

TEST_F(IdentityFunctionTest_357, TransformWithLargeValues_357) {
    double in[funcMaxOutputs];
    double out[funcMaxOutputs];

    for (int i = 0; i < funcMaxOutputs; i++) {
        in[i] = 1e15 + i;
        out[i] = 0.0;
    }

    func->transform(in, out);

    for (int i = 0; i < func->getOutputSize(); i++) {
        EXPECT_DOUBLE_EQ(in[i], out[i]) << "Mismatch at index " << i;
    }
}

TEST_F(IdentityFunctionTest_357, TransformWithFractionalValues_357) {
    double in[funcMaxOutputs];
    double out[funcMaxOutputs];

    for (int i = 0; i < funcMaxOutputs; i++) {
        in[i] = 0.001 * (i + 1);
        out[i] = 0.0;
    }

    func->transform(in, out);

    for (int i = 0; i < func->getOutputSize(); i++) {
        EXPECT_DOUBLE_EQ(in[i], out[i]) << "Mismatch at index " << i;
    }
}

TEST_F(IdentityFunctionTest_357, CopyReturnsValidFunction_357) {
    auto copied = func->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_TRUE(copied->isOk());
}

TEST_F(IdentityFunctionTest_357, CopyProducesSameBehavior_357) {
    auto copied = func->copy();
    ASSERT_NE(copied, nullptr);

    double in[funcMaxOutputs];
    double out1[funcMaxOutputs];
    double out2[funcMaxOutputs];

    for (int i = 0; i < funcMaxOutputs; i++) {
        in[i] = static_cast<double>(i) * 3.14;
        out1[i] = 0.0;
        out2[i] = 0.0;
    }

    func->transform(in, out1);
    copied->transform(in, out2);

    for (int i = 0; i < func->getOutputSize(); i++) {
        EXPECT_DOUBLE_EQ(out1[i], out2[i]) << "Mismatch at index " << i;
    }
}

TEST_F(IdentityFunctionTest_357, GetTypeReturnsIdentity_357) {
    Function::Type type = func->getType();
    EXPECT_EQ(type, Function::Type::Identity);
}

TEST_F(IdentityFunctionTest_357, MultipleTransformCallsAreConsistent_357) {
    double in[funcMaxOutputs];
    double out1[funcMaxOutputs];
    double out2[funcMaxOutputs];

    for (int i = 0; i < funcMaxOutputs; i++) {
        in[i] = static_cast<double>(i);
        out1[i] = 0.0;
        out2[i] = 0.0;
    }

    func->transform(in, out1);
    func->transform(in, out2);

    for (int i = 0; i < func->getOutputSize(); i++) {
        EXPECT_DOUBLE_EQ(out1[i], out2[i]) << "Mismatch at index " << i;
    }
}

TEST_F(IdentityFunctionTest_357, TransformWithBoundaryDoubleValues_357) {
    double in[funcMaxOutputs];
    double out[funcMaxOutputs];

    // Use some boundary-ish double values
    in[0] = std::numeric_limits<double>::min();
    in[1] = std::numeric_limits<double>::max();
    in[2] = std::numeric_limits<double>::epsilon();
    in[3] = -std::numeric_limits<double>::min();
    for (int i = 4; i < funcMaxOutputs; i++) {
        in[i] = 0.0;
    }

    for (int i = 0; i < funcMaxOutputs; i++) {
        out[i] = 42.0;
    }

    func->transform(in, out);

    for (int i = 0; i < func->getOutputSize(); i++) {
        EXPECT_DOUBLE_EQ(in[i], out[i]) << "Mismatch at index " << i;
    }
}
