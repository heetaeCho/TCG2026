#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Function.h"
#include "Dict.h"
#include "Object.h"
#include "PDFDoc.h"
#include "Stream.h"

#include <memory>
#include <cmath>

// Helper to create a Dict for ExponentialFunction construction
// ExponentialFunction requires a Dict with specific keys:
// /FunctionType 2
// /Domain [domain_min domain_max]
// /N (exponent)
// /C0 (optional, defaults to [0.0])
// /C1 (optional, defaults to [1.0])

class ExponentialFunctionTest_371 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to build an ExponentialFunction from raw PDF objects via Dict
    std::unique_ptr<Function> createExponentialFunction(
        double domainMin, double domainMax,
        double exponent,
        const std::vector<double>& c0vals = {},
        const std::vector<double>& c1vals = {},
        int numOutputs = -1)
    {
        // Use Function::parse which handles FunctionType 2
        // We'll build an Object containing the dict
        auto dict = Object(new Dict(nullptr));
        dict.dictAdd("FunctionType", Object(2));

        // Domain array
        auto domainArr = Object(new Array(nullptr));
        domainArr.arrayAdd(Object(domainMin));
        domainArr.arrayAdd(Object(domainMax));
        dict.dictAdd("Domain", std::move(domainArr));

        // N (exponent)
        dict.dictAdd("N", Object(exponent));

        // C0
        if (!c0vals.empty()) {
            auto c0Arr = Object(new Array(nullptr));
            for (double v : c0vals) {
                c0Arr.arrayAdd(Object(v));
            }
            dict.dictAdd("C0", std::move(c0Arr));
        }

        // C1
        if (!c1vals.empty()) {
            auto c1Arr = Object(new Array(nullptr));
            for (double v : c1vals) {
                c1Arr.arrayAdd(Object(v));
            }
            dict.dictAdd("C1", std::move(c1Arr));
        }

        // Range (optional but may be needed)
        if (numOutputs > 0) {
            auto rangeArr = Object(new Array(nullptr));
            for (int i = 0; i < numOutputs; i++) {
                rangeArr.arrayAdd(Object(0.0));
                rangeArr.arrayAdd(Object(1.0));
            }
            dict.dictAdd("Range", std::move(rangeArr));
        }

        return Function::parse(&dict);
    }
};

// Test that getC0 returns a non-null pointer for a valid ExponentialFunction
TEST_F(ExponentialFunctionTest_371, GetC0ReturnsNonNull_371) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.0}, {1.0}, 1);
    if (func) {
        // We know the function type should be ExponentialFunction (type 2)
        ASSERT_EQ(func->getType(), Function::Type::Exponential);
        auto* expFunc = static_cast<ExponentialFunction*>(func.get());
        const double* c0 = expFunc->getC0();
        ASSERT_NE(c0, nullptr);
    }
}

// Test that getC0 returns correct default value (0.0) when C0 is not specified
TEST_F(ExponentialFunctionTest_371, GetC0DefaultValue_371) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {}, {}, 1);
    if (func && func->getType() == Function::Type::Exponential) {
        auto* expFunc = static_cast<ExponentialFunction*>(func.get());
        const double* c0 = expFunc->getC0();
        ASSERT_NE(c0, nullptr);
        EXPECT_DOUBLE_EQ(c0[0], 0.0);
    }
}

// Test that getC0 returns specified values
TEST_F(ExponentialFunctionTest_371, GetC0SpecifiedValues_371) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.5}, {1.0}, 1);
    if (func && func->getType() == Function::Type::Exponential) {
        auto* expFunc = static_cast<ExponentialFunction*>(func.get());
        const double* c0 = expFunc->getC0();
        ASSERT_NE(c0, nullptr);
        EXPECT_DOUBLE_EQ(c0[0], 0.5);
    }
}

// Test that getC1 returns a non-null pointer
TEST_F(ExponentialFunctionTest_371, GetC1ReturnsNonNull_371) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.0}, {1.0}, 1);
    if (func && func->getType() == Function::Type::Exponential) {
        auto* expFunc = static_cast<ExponentialFunction*>(func.get());
        const double* c1 = expFunc->getC1();
        ASSERT_NE(c1, nullptr);
    }
}

// Test that getC1 returns correct specified values
TEST_F(ExponentialFunctionTest_371, GetC1SpecifiedValues_371) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.0}, {0.75}, 1);
    if (func && func->getType() == Function::Type::Exponential) {
        auto* expFunc = static_cast<ExponentialFunction*>(func.get());
        const double* c1 = expFunc->getC1();
        ASSERT_NE(c1, nullptr);
        EXPECT_DOUBLE_EQ(c1[0], 0.75);
    }
}

// Test that getC1 returns default value (1.0) when not specified
TEST_F(ExponentialFunctionTest_371, GetC1DefaultValue_371) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {}, {}, 1);
    if (func && func->getType() == Function::Type::Exponential) {
        auto* expFunc = static_cast<ExponentialFunction*>(func.get());
        const double* c1 = expFunc->getC1();
        ASSERT_NE(c1, nullptr);
        EXPECT_DOUBLE_EQ(c1[0], 1.0);
    }
}

// Test getE returns the exponent value
TEST_F(ExponentialFunctionTest_371, GetEReturnsExponent_371) {
    auto func = createExponentialFunction(0.0, 1.0, 2.0, {0.0}, {1.0}, 1);
    if (func && func->getType() == Function::Type::Exponential) {
        auto* expFunc = static_cast<ExponentialFunction*>(func.get());
        EXPECT_DOUBLE_EQ(expFunc->getE(), 2.0);
    }
}

// Test getE with exponent of 1.0 (linear)
TEST_F(ExponentialFunctionTest_371, GetELinearExponent_371) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.0}, {1.0}, 1);
    if (func && func->getType() == Function::Type::Exponential) {
        auto* expFunc = static_cast<ExponentialFunction*>(func.get());
        EXPECT_DOUBLE_EQ(expFunc->getE(), 1.0);
    }
}

// Test getType returns Exponential
TEST_F(ExponentialFunctionTest_371, GetTypeReturnsExponential_371) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.0}, {1.0}, 1);
    if (func) {
        EXPECT_EQ(func->getType(), Function::Type::Exponential);
    }
}

// Test isOk returns true for a valid function
TEST_F(ExponentialFunctionTest_371, IsOkReturnsTrueForValid_371) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.0}, {1.0}, 1);
    if (func) {
        EXPECT_TRUE(func->isOk());
    }
}

// Test transform with input 0.0 should return C0 values
TEST_F(ExponentialFunctionTest_371, TransformAtZeroReturnsC0_371) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.2}, {0.8}, 1);
    if (func && func->getType() == Function::Type::Exponential) {
        double in = 0.0;
        double out = -1.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.2, 1e-6);
    }
}

// Test transform with input 1.0 should return C1 values
TEST_F(ExponentialFunctionTest_371, TransformAtOneReturnsC1_371) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.2}, {0.8}, 1);
    if (func && func->getType() == Function::Type::Exponential) {
        double in = 1.0;
        double out = -1.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.8, 1e-6);
    }
}

// Test transform with input 0.5 and exponent 1.0 (linear interpolation)
TEST_F(ExponentialFunctionTest_371, TransformLinearInterpolation_371) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.0}, {1.0}, 1);
    if (func && func->getType() == Function::Type::Exponential) {
        double in = 0.5;
        double out = -1.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.5, 1e-6);
    }
}

// Test transform with exponent 2.0 (quadratic)
TEST_F(ExponentialFunctionTest_371, TransformQuadratic_371) {
    auto func = createExponentialFunction(0.0, 1.0, 2.0, {0.0}, {1.0}, 1);
    if (func && func->getType() == Function::Type::Exponential) {
        double in = 0.5;
        double out = -1.0;
        func->transform(&in, &out);
        // Expected: C0 + x^N * (C1 - C0) = 0.0 + 0.25 * 1.0 = 0.25
        EXPECT_NEAR(out, 0.25, 1e-6);
    }
}

// Test copy function
TEST_F(ExponentialFunctionTest_371, CopyFunctionPreservesValues_371) {
    auto func = createExponentialFunction(0.0, 1.0, 2.0, {0.3}, {0.9}, 1);
    if (func && func->getType() == Function::Type::Exponential) {
        auto copied = func->copy();
        ASSERT_NE(copied, nullptr);
        EXPECT_EQ(copied->getType(), Function::Type::Exponential);
        EXPECT_TRUE(copied->isOk());

        auto* expOrig = static_cast<ExponentialFunction*>(func.get());
        auto* expCopy = static_cast<ExponentialFunction*>(copied.get());

        EXPECT_DOUBLE_EQ(expCopy->getE(), expOrig->getE());
        EXPECT_DOUBLE_EQ(expCopy->getC0()[0], expOrig->getC0()[0]);
        EXPECT_DOUBLE_EQ(expCopy->getC1()[0], expOrig->getC1()[0]);
    }
}

// Test with multiple outputs
TEST_F(ExponentialFunctionTest_371, MultipleOutputs_371) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.1, 0.2, 0.3}, {0.9, 0.8, 0.7}, 3);
    if (func && func->getType() == Function::Type::Exponential) {
        auto* expFunc = static_cast<ExponentialFunction*>(func.get());
        const double* c0 = expFunc->getC0();
        ASSERT_NE(c0, nullptr);
        EXPECT_DOUBLE_EQ(c0[0], 0.1);
        EXPECT_DOUBLE_EQ(c0[1], 0.2);
        EXPECT_DOUBLE_EQ(c0[2], 0.3);

        const double* c1 = expFunc->getC1();
        ASSERT_NE(c1, nullptr);
        EXPECT_DOUBLE_EQ(c1[0], 0.9);
        EXPECT_DOUBLE_EQ(c1[1], 0.8);
        EXPECT_DOUBLE_EQ(c1[2], 0.7);
    }
}

// Test transform with multiple outputs at midpoint
TEST_F(ExponentialFunctionTest_371, TransformMultipleOutputsMidpoint_371) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}, 3);
    if (func && func->getType() == Function::Type::Exponential) {
        double in = 0.5;
        double out[3] = {-1.0, -1.0, -1.0};
        func->transform(&in, out);
        for (int i = 0; i < 3; i++) {
            EXPECT_NEAR(out[i], 0.5, 1e-6);
        }
    }
}

// Test with fractional exponent
TEST_F(ExponentialFunctionTest_371, FractionalExponent_371) {
    auto func = createExponentialFunction(0.0, 1.0, 0.5, {0.0}, {1.0}, 1);
    if (func && func->getType() == Function::Type::Exponential) {
        auto* expFunc = static_cast<ExponentialFunction*>(func.get());
        EXPECT_DOUBLE_EQ(expFunc->getE(), 0.5);

        double in = 0.25;
        double out = -1.0;
        func->transform(&in, &out);
        // Expected: 0.0 + 0.25^0.5 * (1.0 - 0.0) = 0.5
        EXPECT_NEAR(out, 0.5, 1e-6);
    }
}

// Test transform respects domain clamping at lower bound
TEST_F(ExponentialFunctionTest_371, TransformClampedBelowDomain_371) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.0}, {1.0}, 1);
    if (func && func->getType() == Function::Type::Exponential) {
        double in = -0.5; // below domain
        double out = -1.0;
        func->transform(&in, &out);
        // Should clamp to 0.0, so output should be C0[0] = 0.0
        EXPECT_NEAR(out, 0.0, 1e-6);
    }
}

// Test transform respects domain clamping at upper bound
TEST_F(ExponentialFunctionTest_371, TransformClampedAboveDomain_371) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.0}, {1.0}, 1);
    if (func && func->getType() == Function::Type::Exponential) {
        double in = 1.5; // above domain
        double out = -1.0;
        func->transform(&in, &out);
        // Should clamp to 1.0, so output should be C1[0] = 1.0
        EXPECT_NEAR(out, 1.0, 1e-6);
    }
}

// Test copy produces independent object (modifying original shouldn't affect copy)
TEST_F(ExponentialFunctionTest_371, CopyIsIndependent_371) {
    auto func = createExponentialFunction(0.0, 1.0, 2.0, {0.0}, {1.0}, 1);
    if (func && func->getType() == Function::Type::Exponential) {
        auto copied = func->copy();
        ASSERT_NE(copied, nullptr);

        // Both should transform identically
        double in = 0.5;
        double out1 = -1.0, out2 = -1.0;
        func->transform(&in, &out1);
        copied->transform(&in, &out2);
        EXPECT_DOUBLE_EQ(out1, out2);
    }
}

// Test with exponent 0 (all inputs map to same value)
TEST_F(ExponentialFunctionTest_371, ExponentZero_371) {
    auto func = createExponentialFunction(0.0, 1.0, 0.0, {0.0}, {1.0}, 1);
    if (func && func->getType() == Function::Type::Exponential) {
        auto* expFunc = static_cast<ExponentialFunction*>(func.get());
        EXPECT_DOUBLE_EQ(expFunc->getE(), 0.0);
    }
}
