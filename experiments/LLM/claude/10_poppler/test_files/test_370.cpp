#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Function.h"
#include "Dict.h"
#include "Object.h"
#include "XRef.h"
#include "PDFDoc.h"

#include <memory>
#include <cmath>

// Helper to create a Dict for ExponentialFunction construction
// ExponentialFunction expects:
//   /FunctionType 2
//   /Domain [d0 d1]
//   /N (exponent)
//   /C0 [array] (optional, defaults to [0.0])
//   /C1 [array] (optional, defaults to [1.0])
//   /Range [r0 r1 ...] (optional)

class ExponentialFunctionTest_370 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper: build a Dict representing an ExponentialFunction spec
    // Returns an Object owning the dict
    Object buildExponentialDict(double domainMin, double domainMax,
                                double exponent,
                                const std::vector<double>& c0 = {},
                                const std::vector<double>& c1 = {},
                                const std::vector<double>& range = {}) {
        Object dictObj = Object(new Dict(nullptr));
        Dict *dict = dictObj.getDict();

        // FunctionType = 2
        dict->add("FunctionType", Object(2));

        // Domain
        Object domainArr = Object(new Array(nullptr));
        domainArr.arrayAdd(Object(domainMin));
        domainArr.arrayAdd(Object(domainMax));
        dict->add("Domain", std::move(domainArr));

        // N (exponent)
        dict->add("N", Object(exponent));

        // C0
        if (!c0.empty()) {
            Object c0Arr = Object(new Array(nullptr));
            for (double v : c0) {
                c0Arr.arrayAdd(Object(v));
            }
            dict->add("C0", std::move(c0Arr));
        }

        // C1
        if (!c1.empty()) {
            Object c1Arr = Object(new Array(nullptr));
            for (double v : c1) {
                c1Arr.arrayAdd(Object(v));
            }
            dict->add("C1", std::move(c1Arr));
        }

        // Range
        if (!range.empty()) {
            Object rangeArr = Object(new Array(nullptr));
            for (double v : range) {
                rangeArr.arrayAdd(Object(v));
            }
            dict->add("Range", std::move(rangeArr));
        }

        return dictObj;
    }

    std::unique_ptr<Function> createFunction(Object &obj) {
        return Function::parse(&obj);
    }
};

// Test that a valid ExponentialFunction with default C0/C1 is ok
TEST_F(ExponentialFunctionTest_370, ValidDefaultC0C1_IsOk_370) {
    Object dictObj = buildExponentialDict(0.0, 1.0, 1.0);
    auto func = createFunction(dictObj);
    if (func) {
        EXPECT_TRUE(func->isOk());
    }
}

// Test ExponentialFunction with exponent N=1 (linear interpolation)
TEST_F(ExponentialFunctionTest_370, LinearExponent_Transform_370) {
    // N=1, C0=[0], C1=[1], Domain=[0,1]
    Object dictObj = buildExponentialDict(0.0, 1.0, 1.0, {0.0}, {1.0}, {0.0, 1.0});
    auto func = createFunction(dictObj);
    if (func) {
        ASSERT_TRUE(func->isOk());

        double in, out;

        // At x=0, result should be C0 = 0.0
        in = 0.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.0, 1e-6);

        // At x=1, result should be C1 = 1.0
        in = 1.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 1.0, 1e-6);

        // At x=0.5, result should be 0.5 (linear)
        in = 0.5;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.5, 1e-6);
    }
}

// Test ExponentialFunction with exponent N=2 (quadratic)
TEST_F(ExponentialFunctionTest_370, QuadraticExponent_Transform_370) {
    // N=2, C0=[0], C1=[1], Domain=[0,1]
    // f(x) = C0 + x^N * (C1 - C0) = x^2
    Object dictObj = buildExponentialDict(0.0, 1.0, 2.0, {0.0}, {1.0}, {0.0, 1.0});
    auto func = createFunction(dictObj);
    if (func) {
        ASSERT_TRUE(func->isOk());

        double in, out;

        in = 0.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.0, 1e-6);

        in = 1.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 1.0, 1e-6);

        in = 0.5;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.25, 1e-6);
    }
}

// Test ExponentialFunction with non-trivial C0 and C1
TEST_F(ExponentialFunctionTest_370, NonTrivialC0C1_Transform_370) {
    // N=1, C0=[2], C1=[4], Domain=[0,1]
    // f(x) = 2 + x*(4-2) = 2 + 2x
    Object dictObj = buildExponentialDict(0.0, 1.0, 1.0, {2.0}, {4.0}, {0.0, 10.0});
    auto func = createFunction(dictObj);
    if (func) {
        ASSERT_TRUE(func->isOk());

        double in, out;

        in = 0.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 2.0, 1e-6);

        in = 1.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 4.0, 1e-6);

        in = 0.5;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 3.0, 1e-6);
    }
}

// Test that getType returns Type 2 (Exponential)
TEST_F(ExponentialFunctionTest_370, GetType_ReturnsExponential_370) {
    Object dictObj = buildExponentialDict(0.0, 1.0, 1.0, {0.0}, {1.0}, {0.0, 1.0});
    auto func = createFunction(dictObj);
    if (func) {
        ASSERT_TRUE(func->isOk());
        EXPECT_EQ(func->getType(), Function::Type::Exponential);
    }
}

// Test copy() produces an equivalent function
TEST_F(ExponentialFunctionTest_370, Copy_ProducesSameResults_370) {
    Object dictObj = buildExponentialDict(0.0, 1.0, 2.0, {1.0}, {3.0}, {0.0, 10.0});
    auto func = createFunction(dictObj);
    if (func) {
        ASSERT_TRUE(func->isOk());

        auto funcCopy = func->copy();
        ASSERT_NE(funcCopy, nullptr);
        EXPECT_TRUE(funcCopy->isOk());

        double in = 0.7;
        double out1, out2;
        func->transform(&in, &out1);
        funcCopy->transform(&in, &out2);
        EXPECT_NEAR(out1, out2, 1e-10);
    }
}

// Test getC0, getC1, getE accessors
TEST_F(ExponentialFunctionTest_370, Accessors_GetC0C1E_370) {
    Object dictObj = buildExponentialDict(0.0, 1.0, 3.0, {5.0}, {10.0}, {0.0, 20.0});
    auto func = createFunction(dictObj);
    if (func) {
        ASSERT_TRUE(func->isOk());
        // Downcast to ExponentialFunction
        auto* expFunc = dynamic_cast<ExponentialFunction*>(func.get());
        if (expFunc) {
            const double* c0 = expFunc->getC0();
            const double* c1 = expFunc->getC1();
            double e = expFunc->getE();

            ASSERT_NE(c0, nullptr);
            ASSERT_NE(c1, nullptr);
            EXPECT_NEAR(c0[0], 5.0, 1e-6);
            EXPECT_NEAR(c1[0], 10.0, 1e-6);
            EXPECT_NEAR(e, 3.0, 1e-6);
        }
    }
}

// Test multiple outputs
TEST_F(ExponentialFunctionTest_370, MultipleOutputs_Transform_370) {
    // N=1, C0=[0, 1], C1=[1, 0], Domain=[0,1], Range=[0,1, 0,1]
    // f(x) = [x, 1-x]
    Object dictObj = buildExponentialDict(0.0, 1.0, 1.0, {0.0, 1.0}, {1.0, 0.0}, {0.0, 1.0, 0.0, 1.0});
    auto func = createFunction(dictObj);
    if (func) {
        ASSERT_TRUE(func->isOk());

        double in = 0.5;
        double out[2];
        func->transform(&in, out);
        EXPECT_NEAR(out[0], 0.5, 1e-6);
        EXPECT_NEAR(out[1], 0.5, 1e-6);

        in = 0.0;
        func->transform(&in, out);
        EXPECT_NEAR(out[0], 0.0, 1e-6);
        EXPECT_NEAR(out[1], 1.0, 1e-6);

        in = 1.0;
        func->transform(&in, out);
        EXPECT_NEAR(out[0], 1.0, 1e-6);
        EXPECT_NEAR(out[1], 0.0, 1e-6);
    }
}

// Test boundary: input at domain boundaries
TEST_F(ExponentialFunctionTest_370, DomainBoundary_Clamping_370) {
    // Domain=[0.2, 0.8], N=1, C0=[0], C1=[1]
    Object dictObj = buildExponentialDict(0.2, 0.8, 1.0, {0.0}, {1.0}, {0.0, 1.0});
    auto func = createFunction(dictObj);
    if (func) {
        ASSERT_TRUE(func->isOk());

        double in, out;

        // Input below domain min should be clamped to 0.2
        // After normalization: (0.2-0.2)/(0.8-0.2) = 0
        in = 0.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.0, 1e-6);

        // Input above domain max should be clamped to 0.8
        // After normalization: (0.8-0.2)/(0.8-0.2) = 1
        in = 1.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 1.0, 1e-6);
    }
}

// Test with exponent N=0 (constant function: should return C1 for all x > 0, C0 for x = 0)
TEST_F(ExponentialFunctionTest_370, ZeroExponent_370) {
    // N=0, x^0 = 1 for x>0, so f(x) = C0 + 1*(C1-C0) = C1
    Object dictObj = buildExponentialDict(0.0, 1.0, 0.0, {2.0}, {5.0}, {0.0, 10.0});
    auto func = createFunction(dictObj);
    if (func) {
        ASSERT_TRUE(func->isOk());

        double in, out;
        in = 0.5;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 5.0, 1e-6);
    }
}

// Test with large exponent
TEST_F(ExponentialFunctionTest_370, LargeExponent_370) {
    // N=10, f(0.5) = 0.5^10 ≈ 0.0009765625
    Object dictObj = buildExponentialDict(0.0, 1.0, 10.0, {0.0}, {1.0}, {0.0, 1.0});
    auto func = createFunction(dictObj);
    if (func) {
        ASSERT_TRUE(func->isOk());

        double in = 0.5, out;
        func->transform(&in, &out);
        EXPECT_NEAR(out, std::pow(0.5, 10.0), 1e-6);
    }
}

// Test getInputSize and getOutputSize
TEST_F(ExponentialFunctionTest_370, InputOutputSize_370) {
    Object dictObj = buildExponentialDict(0.0, 1.0, 1.0, {0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}, {0.0, 1.0, 0.0, 1.0, 0.0, 1.0});
    auto func = createFunction(dictObj);
    if (func) {
        ASSERT_TRUE(func->isOk());
        // ExponentialFunction always has 1 input
        EXPECT_EQ(func->getInputSize(), 1);
        // Should have 3 outputs based on C0/C1 array size
        EXPECT_EQ(func->getOutputSize(), 3);
    }
}
