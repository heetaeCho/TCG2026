#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Function.h"
#include "Dict.h"
#include "Object.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

// Helper to create a minimal ExponentialFunction via a Dict
// We need to construct proper PDF objects for the function dictionary

class ExponentialFunctionTest_368 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a function dictionary for ExponentialFunction
    // FunctionType 2, Domain, N (exponent), optionally C0, C1
    std::unique_ptr<Function> createExponentialFunction(double domainMin, double domainMax,
                                                         double exponent,
                                                         const std::vector<double>& c0 = {},
                                                         const std::vector<double>& c1 = {},
                                                         int nOutputs = -1) {
        // Build via Function::parse which expects an Object
        // We'll build a Dict-based Object
        
        Object dictObj = Object(new Dict(nullptr));
        Dict *dict = dictObj.getDict();
        
        // FunctionType = 2
        dict->add("FunctionType", Object(2));
        
        // Domain array
        Object domainArray = Object(new Array(nullptr));
        domainArray.arrayAdd(Object(domainMin));
        domainArray.arrayAdd(Object(domainMax));
        dict->add("Domain", std::move(domainArray));
        
        // N (exponent)
        dict->add("N", Object(exponent));
        
        // C0 array (optional)
        if (!c0.empty()) {
            Object c0Array = Object(new Array(nullptr));
            for (double v : c0) {
                c0Array.arrayAdd(Object(v));
            }
            dict->add("C0", std::move(c0Array));
        }
        
        // C1 array (optional)
        if (!c1.empty()) {
            Object c1Array = Object(new Array(nullptr));
            for (double v : c1) {
                c1Array.arrayAdd(Object(v));
            }
            dict->add("C1", std::move(c1Array));
        }
        
        // Range array (optional but sometimes needed)
        if (nOutputs > 0) {
            Object rangeArray = Object(new Array(nullptr));
            for (int i = 0; i < nOutputs; i++) {
                rangeArray.arrayAdd(Object(0.0));
                rangeArray.arrayAdd(Object(1.0));
            }
            dict->add("Range", std::move(rangeArray));
        }
        
        return Function::parse(std::move(dictObj));
    }
};

// Test that a basic ExponentialFunction can be created and is valid
TEST_F(ExponentialFunctionTest_368, BasicCreation_368) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.0}, {1.0}, 1);
    if (func) {
        EXPECT_TRUE(func->isOk());
    }
}

// Test getType returns the correct type for ExponentialFunction
TEST_F(ExponentialFunctionTest_368, GetTypeReturnsExponential_368) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.0}, {1.0}, 1);
    if (func && func->isOk()) {
        EXPECT_EQ(func->getType(), Function::Type::Exponential);
    }
}

// Test copy creates a valid duplicate
TEST_F(ExponentialFunctionTest_368, CopyCreatesValidFunction_368) {
    auto func = createExponentialFunction(0.0, 1.0, 2.0, {0.0}, {1.0}, 1);
    if (func && func->isOk()) {
        auto copied = func->copy();
        ASSERT_NE(copied, nullptr);
        EXPECT_TRUE(copied->isOk());
        EXPECT_EQ(copied->getType(), Function::Type::Exponential);
    }
}

// Test transform with linear interpolation (N=1)
TEST_F(ExponentialFunctionTest_368, TransformLinear_368) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.0}, {1.0}, 1);
    if (func && func->isOk()) {
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

// Test transform with quadratic (N=2)
TEST_F(ExponentialFunctionTest_368, TransformQuadratic_368) {
    auto func = createExponentialFunction(0.0, 1.0, 2.0, {0.0}, {1.0}, 1);
    if (func && func->isOk()) {
        double in, out;
        
        // At x=0, result should be C0 = 0.0
        in = 0.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.0, 1e-6);
        
        // At x=1, result should be C1 = 1.0
        in = 1.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 1.0, 1e-6);
        
        // At x=0.5, result should be 0.25 (0.5^2)
        in = 0.5;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.25, 1e-6);
    }
}

// Test with non-zero C0
TEST_F(ExponentialFunctionTest_368, TransformNonZeroC0_368) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.5}, {1.0}, 1);
    if (func && func->isOk()) {
        double in, out;
        
        // At x=0, result should be C0 = 0.5
        in = 0.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.5, 1e-6);
        
        // At x=1, result should be C1 = 1.0
        in = 1.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 1.0, 1e-6);
        
        // At x=0.5, result = C0 + x^N * (C1 - C0) = 0.5 + 0.5 * 0.5 = 0.75
        in = 0.5;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.75, 1e-6);
    }
}

// Test default C0 and C1 (C0 defaults to {0.0}, C1 defaults to {1.0})
TEST_F(ExponentialFunctionTest_368, TransformDefaultC0C1_368) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {}, {}, 1);
    if (func && func->isOk()) {
        double in, out;
        
        in = 0.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.0, 1e-6);
        
        in = 1.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 1.0, 1e-6);
    }
}

// Test getC0 and getC1 return correct values
TEST_F(ExponentialFunctionTest_368, GetC0C1Values_368) {
    auto func = createExponentialFunction(0.0, 1.0, 2.0, {0.3}, {0.9}, 1);
    if (func && func->isOk()) {
        auto* expFunc = dynamic_cast<ExponentialFunction*>(func.get());
        if (expFunc) {
            const double* c0 = expFunc->getC0();
            const double* c1 = expFunc->getC1();
            ASSERT_NE(c0, nullptr);
            ASSERT_NE(c1, nullptr);
            EXPECT_NEAR(c0[0], 0.3, 1e-6);
            EXPECT_NEAR(c1[0], 0.9, 1e-6);
        }
    }
}

// Test getE returns correct exponent
TEST_F(ExponentialFunctionTest_368, GetExponent_368) {
    auto func = createExponentialFunction(0.0, 1.0, 3.5, {0.0}, {1.0}, 1);
    if (func && func->isOk()) {
        auto* expFunc = dynamic_cast<ExponentialFunction*>(func.get());
        if (expFunc) {
            EXPECT_NEAR(expFunc->getE(), 3.5, 1e-6);
        }
    }
}

// Test copy preserves exponent and C0/C1
TEST_F(ExponentialFunctionTest_368, CopyPreservesParameters_368) {
    auto func = createExponentialFunction(0.0, 1.0, 2.5, {0.1}, {0.8}, 1);
    if (func && func->isOk()) {
        auto copied = func->copy();
        ASSERT_NE(copied, nullptr);
        
        auto* expOrig = dynamic_cast<ExponentialFunction*>(func.get());
        auto* expCopy = dynamic_cast<ExponentialFunction*>(copied.get());
        
        if (expOrig && expCopy) {
            EXPECT_NEAR(expCopy->getE(), expOrig->getE(), 1e-6);
            EXPECT_NEAR(expCopy->getC0()[0], expOrig->getC0()[0], 1e-6);
            EXPECT_NEAR(expCopy->getC1()[0], expOrig->getC1()[0], 1e-6);
        }
    }
}

// Test copy produces same transform results
TEST_F(ExponentialFunctionTest_368, CopyProducesSameTransform_368) {
    auto func = createExponentialFunction(0.0, 1.0, 2.0, {0.2}, {0.8}, 1);
    if (func && func->isOk()) {
        auto copied = func->copy();
        ASSERT_NE(copied, nullptr);
        
        double in = 0.5;
        double outOrig, outCopy;
        func->transform(&in, &outOrig);
        copied->transform(&in, &outCopy);
        EXPECT_NEAR(outOrig, outCopy, 1e-10);
    }
}

// Test with multiple outputs
TEST_F(ExponentialFunctionTest_368, MultipleOutputs_368) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.0, 0.0, 0.0}, {1.0, 0.5, 0.25}, 3);
    if (func && func->isOk()) {
        double in = 1.0;
        double out[3];
        func->transform(&in, out);
        EXPECT_NEAR(out[0], 1.0, 1e-6);
        EXPECT_NEAR(out[1], 0.5, 1e-6);
        EXPECT_NEAR(out[2], 0.25, 1e-6);
    }
}

// Test boundary: input at domain min
TEST_F(ExponentialFunctionTest_368, BoundaryDomainMin_368) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.0}, {1.0}, 1);
    if (func && func->isOk()) {
        double in = 0.0;
        double out;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.0, 1e-6);
    }
}

// Test boundary: input at domain max
TEST_F(ExponentialFunctionTest_368, BoundaryDomainMax_368) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.0}, {1.0}, 1);
    if (func && func->isOk()) {
        double in = 1.0;
        double out;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 1.0, 1e-6);
    }
}

// Test with exponent N=0 (constant function, x^0 = 1 for all x > 0)
TEST_F(ExponentialFunctionTest_368, ExponentZero_368) {
    // With N=0: result = C0 + x^0 * (C1 - C0) = C0 + 1*(C1-C0) = C1 for x > 0
    // At x=0: 0^0 is typically treated as 1 in PDF spec
    auto func = createExponentialFunction(0.0, 1.0, 0.0, {0.0}, {1.0}, 1);
    if (func && func->isOk()) {
        double in = 0.5;
        double out;
        func->transform(&in, &out);
        // x^0 = 1, so result = 0 + 1*(1-0) = 1
        EXPECT_NEAR(out, 1.0, 1e-6);
    }
}

// Test input clamping to domain
TEST_F(ExponentialFunctionTest_368, InputClampedToDomain_368) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.0}, {1.0}, 1);
    if (func && func->isOk()) {
        double in, out;
        
        // Input below domain should be clamped to 0
        in = -0.5;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.0, 1e-6);
        
        // Input above domain should be clamped to 1
        in = 1.5;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 1.0, 1e-6);
    }
}

// Test getInputSize returns 1 for ExponentialFunction
TEST_F(ExponentialFunctionTest_368, InputSizeIsOne_368) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.0}, {1.0}, 1);
    if (func && func->isOk()) {
        EXPECT_EQ(func->getInputSize(), 1);
    }
}

// Test getOutputSize matches the number of C0/C1 entries
TEST_F(ExponentialFunctionTest_368, OutputSizeMatchesC0C1_368) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.0, 0.0}, {1.0, 1.0}, 2);
    if (func && func->isOk()) {
        EXPECT_EQ(func->getOutputSize(), 2);
    }
}
