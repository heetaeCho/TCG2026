#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Function.h"
#include "Dict.h"
#include "Object.h"
#include "PDFDoc.h"
#include "Stream.h"

#include <memory>
#include <cstring>

// Helper to create an ExponentialFunction via a Dict
// We need to build a proper PDF dictionary for the ExponentialFunction constructor

class ExponentialFunctionTest_372 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a Dict with required entries for ExponentialFunction
    // FunctionType = 2
    // Domain is required
    // N (exponent) is required
    // C0 and C1 are optional (default C0=[0], C1=[1])
    std::unique_ptr<Function> createExponentialFunction(
        double domainMin, double domainMax,
        double exponent,
        const std::vector<double>& c0 = {},
        const std::vector<double>& c1 = {},
        const std::vector<double>& range = {},
        int nOutputs = 1)
    {
        // Use Function::parse which accepts an Object
        // We need to build a dictionary Object
        
        // Build using raw Object/Dict API
        auto dictObj = Object(new Dict(nullptr));
        Dict *dict = dictObj.getDict();
        
        // FunctionType
        dict->add("FunctionType", Object(2));
        
        // Domain array
        Object domainArray = Object(new Array(nullptr));
        domainArray.arrayAdd(Object(domainMin));
        domainArray.arrayAdd(Object(domainMax));
        dict->add("Domain", std::move(domainArray));
        
        // N (exponent)
        dict->add("N", Object(exponent));
        
        // C0
        if (!c0.empty()) {
            Object c0Array = Object(new Array(nullptr));
            for (double v : c0) {
                c0Array.arrayAdd(Object(v));
            }
            dict->add("C0", std::move(c0Array));
        }
        
        // C1
        if (!c1.empty()) {
            Object c1Array = Object(new Array(nullptr));
            for (double v : c1) {
                c1Array.arrayAdd(Object(v));
            }
            dict->add("C1", std::move(c1Array));
        }
        
        // Range (optional)
        if (!range.empty()) {
            Object rangeArray = Object(new Array(nullptr));
            for (double v : range) {
                rangeArray.arrayAdd(Object(v));
            }
            dict->add("Range", std::move(rangeArray));
        }
        
        auto func = Function::parse(&dictObj);
        return func;
    }
};

// Test that a basic ExponentialFunction can be created and is valid
TEST_F(ExponentialFunctionTest_372, BasicCreation_372) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0);
    ASSERT_NE(func, nullptr);
    EXPECT_TRUE(func->isOk());
}

// Test getType returns the correct type for ExponentialFunction
TEST_F(ExponentialFunctionTest_372, GetTypeReturnsExponential_372) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0);
    ASSERT_NE(func, nullptr);
    ASSERT_TRUE(func->isOk());
    EXPECT_EQ(func->getType(), Function::Type::Exponential);
}

// Test getC1 returns non-null pointer
TEST_F(ExponentialFunctionTest_372, GetC1ReturnsNonNull_372) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.0}, {1.0});
    ASSERT_NE(func, nullptr);
    ASSERT_TRUE(func->isOk());
    
    auto* expFunc = dynamic_cast<ExponentialFunction*>(func.get());
    ASSERT_NE(expFunc, nullptr);
    
    const double* c1 = expFunc->getC1();
    ASSERT_NE(c1, nullptr);
    EXPECT_DOUBLE_EQ(c1[0], 1.0);
}

// Test getC0 returns expected values
TEST_F(ExponentialFunctionTest_372, GetC0ReturnsExpectedValues_372) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.5}, {0.8});
    ASSERT_NE(func, nullptr);
    ASSERT_TRUE(func->isOk());
    
    auto* expFunc = dynamic_cast<ExponentialFunction*>(func.get());
    ASSERT_NE(expFunc, nullptr);
    
    const double* c0 = expFunc->getC0();
    ASSERT_NE(c0, nullptr);
    EXPECT_DOUBLE_EQ(c0[0], 0.5);
}

// Test getC1 with custom values
TEST_F(ExponentialFunctionTest_372, GetC1WithCustomValues_372) {
    auto func = createExponentialFunction(0.0, 1.0, 2.0, {0.0}, {0.75});
    ASSERT_NE(func, nullptr);
    ASSERT_TRUE(func->isOk());
    
    auto* expFunc = dynamic_cast<ExponentialFunction*>(func.get());
    ASSERT_NE(expFunc, nullptr);
    
    const double* c1 = expFunc->getC1();
    ASSERT_NE(c1, nullptr);
    EXPECT_DOUBLE_EQ(c1[0], 0.75);
}

// Test getE returns expected exponent
TEST_F(ExponentialFunctionTest_372, GetEReturnsExponent_372) {
    auto func = createExponentialFunction(0.0, 1.0, 3.5, {0.0}, {1.0});
    ASSERT_NE(func, nullptr);
    ASSERT_TRUE(func->isOk());
    
    auto* expFunc = dynamic_cast<ExponentialFunction*>(func.get());
    ASSERT_NE(expFunc, nullptr);
    
    EXPECT_DOUBLE_EQ(expFunc->getE(), 3.5);
}

// Test default C0 and C1 (when not specified)
TEST_F(ExponentialFunctionTest_372, DefaultC0AndC1_372) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0);
    ASSERT_NE(func, nullptr);
    ASSERT_TRUE(func->isOk());
    
    auto* expFunc = dynamic_cast<ExponentialFunction*>(func.get());
    ASSERT_NE(expFunc, nullptr);
    
    const double* c0 = expFunc->getC0();
    const double* c1 = expFunc->getC1();
    ASSERT_NE(c0, nullptr);
    ASSERT_NE(c1, nullptr);
    
    // Default C0 should be 0.0, C1 should be 1.0
    EXPECT_DOUBLE_EQ(c0[0], 0.0);
    EXPECT_DOUBLE_EQ(c1[0], 1.0);
}

// Test transform at input = 0 (should return C0)
TEST_F(ExponentialFunctionTest_372, TransformAtZero_372) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.2}, {0.8});
    ASSERT_NE(func, nullptr);
    ASSERT_TRUE(func->isOk());
    
    double in = 0.0;
    double out = -1.0;
    func->transform(&in, &out);
    
    // At x=0, result should be C0[0] = 0.2
    EXPECT_DOUBLE_EQ(out, 0.2);
}

// Test transform at input = 1 (should return C1)
TEST_F(ExponentialFunctionTest_372, TransformAtOne_372) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.2}, {0.8});
    ASSERT_NE(func, nullptr);
    ASSERT_TRUE(func->isOk());
    
    double in = 1.0;
    double out = -1.0;
    func->transform(&in, &out);
    
    // At x=1, result should be C1[0] = 0.8
    EXPECT_DOUBLE_EQ(out, 0.8);
}

// Test transform at midpoint with linear exponent
TEST_F(ExponentialFunctionTest_372, TransformAtMidpointLinear_372) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.0}, {1.0});
    ASSERT_NE(func, nullptr);
    ASSERT_TRUE(func->isOk());
    
    double in = 0.5;
    double out = -1.0;
    func->transform(&in, &out);
    
    // Linear: C0 + x^1 * (C1 - C0) = 0 + 0.5 * 1.0 = 0.5
    EXPECT_DOUBLE_EQ(out, 0.5);
}

// Test transform with exponent = 2 (quadratic)
TEST_F(ExponentialFunctionTest_372, TransformQuadratic_372) {
    auto func = createExponentialFunction(0.0, 1.0, 2.0, {0.0}, {1.0});
    ASSERT_NE(func, nullptr);
    ASSERT_TRUE(func->isOk());
    
    double in = 0.5;
    double out = -1.0;
    func->transform(&in, &out);
    
    // C0 + x^2 * (C1 - C0) = 0 + 0.25 * 1.0 = 0.25
    EXPECT_DOUBLE_EQ(out, 0.25);
}

// Test copy functionality
TEST_F(ExponentialFunctionTest_372, CopyFunction_372) {
    auto func = createExponentialFunction(0.0, 1.0, 2.0, {0.1}, {0.9});
    ASSERT_NE(func, nullptr);
    ASSERT_TRUE(func->isOk());
    
    auto copied = func->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_TRUE(copied->isOk());
    
    auto* expCopied = dynamic_cast<ExponentialFunction*>(copied.get());
    ASSERT_NE(expCopied, nullptr);
    
    EXPECT_DOUBLE_EQ(expCopied->getE(), 2.0);
    EXPECT_DOUBLE_EQ(expCopied->getC0()[0], 0.1);
    EXPECT_DOUBLE_EQ(expCopied->getC1()[0], 0.9);
}

// Test that copy produces same transform results
TEST_F(ExponentialFunctionTest_372, CopyProducesSameTransform_372) {
    auto func = createExponentialFunction(0.0, 1.0, 2.0, {0.1}, {0.9});
    ASSERT_NE(func, nullptr);
    ASSERT_TRUE(func->isOk());
    
    auto copied = func->copy();
    ASSERT_NE(copied, nullptr);
    
    double in = 0.7;
    double outOrig = -1.0, outCopy = -1.0;
    func->transform(&in, &outOrig);
    copied->transform(&in, &outCopy);
    
    EXPECT_DOUBLE_EQ(outOrig, outCopy);
}

// Test with multiple outputs
TEST_F(ExponentialFunctionTest_372, MultipleOutputs_372) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, 
        {0.0, 0.0, 0.0}, {1.0, 0.5, 0.25},
        {0.0, 1.0, 0.0, 1.0, 0.0, 1.0});
    ASSERT_NE(func, nullptr);
    ASSERT_TRUE(func->isOk());
    
    auto* expFunc = dynamic_cast<ExponentialFunction*>(func.get());
    ASSERT_NE(expFunc, nullptr);
    
    const double* c1 = expFunc->getC1();
    EXPECT_DOUBLE_EQ(c1[0], 1.0);
    EXPECT_DOUBLE_EQ(c1[1], 0.5);
    EXPECT_DOUBLE_EQ(c1[2], 0.25);
}

// Test transform with multiple outputs
TEST_F(ExponentialFunctionTest_372, TransformMultipleOutputs_372) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0,
        {0.0, 0.0, 0.0}, {1.0, 0.5, 0.25},
        {0.0, 1.0, 0.0, 1.0, 0.0, 1.0});
    ASSERT_NE(func, nullptr);
    ASSERT_TRUE(func->isOk());
    
    double in = 1.0;
    double out[3] = {-1.0, -1.0, -1.0};
    func->transform(&in, out);
    
    EXPECT_DOUBLE_EQ(out[0], 1.0);
    EXPECT_DOUBLE_EQ(out[1], 0.5);
    EXPECT_DOUBLE_EQ(out[2], 0.25);
}

// Test domain clamping - input below domain minimum
TEST_F(ExponentialFunctionTest_372, DomainClampingBelowMin_372) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.0}, {1.0});
    ASSERT_NE(func, nullptr);
    ASSERT_TRUE(func->isOk());
    
    double in = -0.5;
    double out = -1.0;
    func->transform(&in, &out);
    
    // Input should be clamped to 0.0, result should be C0 = 0.0
    EXPECT_DOUBLE_EQ(out, 0.0);
}

// Test domain clamping - input above domain maximum
TEST_F(ExponentialFunctionTest_372, DomainClampingAboveMax_372) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0, {0.0}, {1.0});
    ASSERT_NE(func, nullptr);
    ASSERT_TRUE(func->isOk());
    
    double in = 1.5;
    double out = -1.0;
    func->transform(&in, &out);
    
    // Input should be clamped to 1.0, result should be C1 = 1.0
    EXPECT_DOUBLE_EQ(out, 1.0);
}

// Test with exponent = 0 (constant function)
TEST_F(ExponentialFunctionTest_372, ExponentZero_372) {
    // N=0 means x^0 = 1 for all x, so result = C0 + 1*(C1-C0) = C1
    // But N=0 might have special handling; we test observable behavior
    auto func = createExponentialFunction(0.0, 1.0, 0.0, {0.0}, {1.0});
    // Function may or may not be valid with N=0
    if (func && func->isOk()) {
        double in = 0.5;
        double out = -1.0;
        func->transform(&in, &out);
        // x^0 = 1, so result = C0 + 1*(C1-C0) = 1.0
        EXPECT_DOUBLE_EQ(out, 1.0);
    }
}

// Test getE with exponent = 1
TEST_F(ExponentialFunctionTest_372, GetEExponentOne_372) {
    auto func = createExponentialFunction(0.0, 1.0, 1.0);
    ASSERT_NE(func, nullptr);
    ASSERT_TRUE(func->isOk());
    
    auto* expFunc = dynamic_cast<ExponentialFunction*>(func.get());
    ASSERT_NE(expFunc, nullptr);
    EXPECT_DOUBLE_EQ(expFunc->getE(), 1.0);
}

// Test with non-unit domain
TEST_F(ExponentialFunctionTest_372, NonUnitDomain_372) {
    auto func = createExponentialFunction(0.0, 2.0, 1.0, {0.0}, {1.0});
    ASSERT_NE(func, nullptr);
    ASSERT_TRUE(func->isOk());
    
    // The function formula uses the input directly (clamped to domain)
    // f(x) = C0 + x^N * (C1 - C0)
    double in = 1.0;
    double out = -1.0;
    func->transform(&in, &out);
    // Domain clamps to [0,2], x=1.0 is within domain
    // Result depends on implementation - just verify it produces a result
    EXPECT_GE(out, 0.0);
    EXPECT_LE(out, 2.0);  // Might exceed 1.0 if domain is [0,2]
}
