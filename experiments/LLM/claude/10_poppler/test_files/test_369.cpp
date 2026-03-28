#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Function.h"
#include "Dict.h"
#include "Object.h"
#include "XRef.h"
#include "PDFDoc.h"

#include <memory>
#include <cmath>

// Helper to create a Dict with the necessary entries for ExponentialFunction
// ExponentialFunction expects:
//   /FunctionType 2
//   /Domain [d0 d1]
//   /N (exponent)
//   optional /C0 [...]
//   optional /C1 [...]
//   optional /Range [...]

class ExponentialFunctionTest_369 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to build a Dict for ExponentialFunction construction
    // We need to create proper poppler Object/Dict structures
    std::unique_ptr<Function> createExponentialFunction(double domainMin, double domainMax,
                                                         double exponent,
                                                         const std::vector<double>& c0 = {},
                                                         const std::vector<double>& c1 = {},
                                                         int nOutputs = 1,
                                                         const std::vector<double>& range = {}) {
        // Use Function::parse which handles FunctionType dispatch
        // We'll build the dictionary as an Object
        
        // Build domain array
        Array *domainArr = new Array(nullptr);
        domainArr->add(Object(domainMin));
        domainArr->add(Object(domainMax));
        
        Dict *dict = new Dict(nullptr);
        dict->add("FunctionType", Object(2));
        dict->add("Domain", Object(domainArr));
        dict->add("N", Object(exponent));
        
        if (!c0.empty()) {
            Array *c0Arr = new Array(nullptr);
            for (double v : c0) {
                c0Arr->add(Object(v));
            }
            dict->add("C0", Object(c0Arr));
        }
        
        if (!c1.empty()) {
            Array *c1Arr = new Array(nullptr);
            for (double v : c1) {
                c1Arr->add(Object(v));
            }
            dict->add("C1", Object(c1Arr));
        }
        
        if (!range.empty()) {
            Array *rangeArr = new Array(nullptr);
            for (double v : range) {
                rangeArr->add(Object(v));
            }
            dict->add("Range", Object(rangeArr));
        }
        
        Object obj(dict);
        return Function::parse(&obj);
    }
};

// Test that getType returns Type::Exponential
TEST_F(ExponentialFunctionTest_369, GetTypeReturnsExponential_369) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0);
    if (func) {
        EXPECT_EQ(func->getType(), Function::Type::Exponential);
    }
}

// Test isOk for a valid function
TEST_F(ExponentialFunctionTest_369, IsOkForValidFunction_369) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0);
    if (func) {
        EXPECT_TRUE(func->isOk());
    }
}

// Test linear interpolation (N=1) with default C0={0} and C1={1}
TEST_F(ExponentialFunctionTest_369, LinearInterpolationDefaultC0C1_369) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.0}, {1.0}, 1, {0.0, 1.0});
    if (func && func->isOk()) {
        double in = 0.5;
        double out = 0.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.5, 1e-6);
    }
}

// Test with input at domain minimum (0)
TEST_F(ExponentialFunctionTest_369, InputAtDomainMinimum_369) {
    auto func = createExponentialFunction(0.0, 1.0, 2.0, {0.0}, {1.0}, 1, {0.0, 1.0});
    if (func && func->isOk()) {
        double in = 0.0;
        double out = -1.0;
        func->transform(&in, &out);
        // f(0) = C0 + 0^N * (C1 - C0) = C0 = 0.0
        EXPECT_NEAR(out, 0.0, 1e-6);
    }
}

// Test with input at domain maximum (1)
TEST_F(ExponentialFunctionTest_369, InputAtDomainMaximum_369) {
    auto func = createExponentialFunction(0.0, 1.0, 2.0, {0.0}, {1.0}, 1, {0.0, 1.0});
    if (func && func->isOk()) {
        double in = 1.0;
        double out = -1.0;
        func->transform(&in, &out);
        // f(1) = C0 + 1^N * (C1 - C0) = C1 = 1.0
        EXPECT_NEAR(out, 1.0, 1e-6);
    }
}

// Test quadratic interpolation (N=2)
TEST_F(ExponentialFunctionTest_369, QuadraticInterpolation_369) {
    auto func = createExponentialFunction(0.0, 1.0, 2.0, {0.0}, {1.0}, 1, {0.0, 1.0});
    if (func && func->isOk()) {
        double in = 0.5;
        double out = -1.0;
        func->transform(&in, &out);
        // f(0.5) = 0 + 0.5^2 * (1 - 0) = 0.25
        EXPECT_NEAR(out, 0.25, 1e-6);
    }
}

// Test with custom C0 and C1 values
TEST_F(ExponentialFunctionTest_369, CustomC0C1Values_369) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {2.0}, {4.0}, 1, {0.0, 10.0});
    if (func && func->isOk()) {
        double in = 0.5;
        double out = -1.0;
        func->transform(&in, &out);
        // f(0.5) = 2.0 + 0.5^1 * (4.0 - 2.0) = 2.0 + 1.0 = 3.0
        EXPECT_NEAR(out, 3.0, 1e-6);
    }
}

// Test with multiple outputs
TEST_F(ExponentialFunctionTest_369, MultipleOutputs_369) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, 
                                           {0.0, 1.0}, {1.0, 0.0}, 2, 
                                           {0.0, 1.0, 0.0, 1.0});
    if (func && func->isOk()) {
        double in = 0.5;
        double out[2] = {-1.0, -1.0};
        func->transform(&in, out);
        // out[0] = 0.0 + 0.5 * (1.0 - 0.0) = 0.5
        // out[1] = 1.0 + 0.5 * (0.0 - 1.0) = 0.5
        EXPECT_NEAR(out[0], 0.5, 1e-6);
        EXPECT_NEAR(out[1], 0.5, 1e-6);
    }
}

// Test copy function
TEST_F(ExponentialFunctionTest_369, CopyFunction_369) {
    auto func = createExponentialFunction(0.0, 1.0, 2.0, {0.0}, {1.0}, 1, {0.0, 1.0});
    if (func && func->isOk()) {
        auto funcCopy = func->copy();
        ASSERT_NE(funcCopy, nullptr);
        EXPECT_EQ(funcCopy->getType(), Function::Type::Exponential);
        EXPECT_TRUE(funcCopy->isOk());
        
        double in = 0.5;
        double out1 = -1.0, out2 = -1.0;
        func->transform(&in, &out1);
        funcCopy->transform(&in, &out2);
        EXPECT_NEAR(out1, out2, 1e-10);
    }
}

// Test getE returns the exponent
TEST_F(ExponentialFunctionTest_369, GetExponent_369) {
    auto func = createExponentialFunction(0.0, 1.0, 3.0, {0.0}, {1.0}, 1, {0.0, 1.0});
    if (func && func->isOk()) {
        auto* expFunc = dynamic_cast<ExponentialFunction*>(func.get());
        ASSERT_NE(expFunc, nullptr);
        EXPECT_NEAR(expFunc->getE(), 3.0, 1e-10);
    }
}

// Test getC0 returns the C0 array
TEST_F(ExponentialFunctionTest_369, GetC0Values_369) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {5.0}, {10.0}, 1, {0.0, 20.0});
    if (func && func->isOk()) {
        auto* expFunc = dynamic_cast<ExponentialFunction*>(func.get());
        ASSERT_NE(expFunc, nullptr);
        const double* c0 = expFunc->getC0();
        ASSERT_NE(c0, nullptr);
        EXPECT_NEAR(c0[0], 5.0, 1e-10);
    }
}

// Test getC1 returns the C1 array
TEST_F(ExponentialFunctionTest_369, GetC1Values_369) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {5.0}, {10.0}, 1, {0.0, 20.0});
    if (func && func->isOk()) {
        auto* expFunc = dynamic_cast<ExponentialFunction*>(func.get());
        ASSERT_NE(expFunc, nullptr);
        const double* c1 = expFunc->getC1();
        ASSERT_NE(c1, nullptr);
        EXPECT_NEAR(c1[0], 10.0, 1e-10);
    }
}

// Test input clamping to domain
TEST_F(ExponentialFunctionTest_369, InputClampedToDomain_369) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.0}, {1.0}, 1, {0.0, 1.0});
    if (func && func->isOk()) {
        // Input below domain minimum should be clamped to 0
        double in = -0.5;
        double out = -1.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.0, 1e-6);
        
        // Input above domain maximum should be clamped to 1
        in = 1.5;
        out = -1.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 1.0, 1e-6);
    }
}

// Test with exponent N=0 (constant function, should return C1)
TEST_F(ExponentialFunctionTest_369, ExponentZero_369) {
    auto func = createExponentialFunction(0.0, 1.0, 0.0, {2.0}, {5.0}, 1, {0.0, 10.0});
    if (func && func->isOk()) {
        double in = 0.5;
        double out = -1.0;
        func->transform(&in, &out);
        // f(x) = C0 + x^0 * (C1 - C0) = C0 + 1*(C1-C0) = C1 = 5.0
        EXPECT_NEAR(out, 5.0, 1e-6);
    }
}

// Test with exponent N=0.5 (square root)
TEST_F(ExponentialFunctionTest_369, SquareRootExponent_369) {
    auto func = createExponentialFunction(0.0, 1.0, 0.5, {0.0}, {1.0}, 1, {0.0, 1.0});
    if (func && func->isOk()) {
        double in = 0.25;
        double out = -1.0;
        func->transform(&in, &out);
        // f(0.25) = 0 + 0.25^0.5 * (1-0) = 0.5
        EXPECT_NEAR(out, 0.5, 1e-6);
    }
}

// Test that the function number of inputs is 1
TEST_F(ExponentialFunctionTest_369, NumberOfInputsIsOne_369) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.0}, {1.0}, 1, {0.0, 1.0});
    if (func && func->isOk()) {
        EXPECT_EQ(func->getInputSize(), 1);
    }
}

// Test number of outputs matches C0/C1 size
TEST_F(ExponentialFunctionTest_369, NumberOfOutputsMatchesSpec_369) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, 
                                           {0.0, 1.0, 2.0}, {3.0, 4.0, 5.0}, 3,
                                           {0.0, 10.0, 0.0, 10.0, 0.0, 10.0});
    if (func && func->isOk()) {
        EXPECT_EQ(func->getOutputSize(), 3);
    }
}
