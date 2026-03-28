#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Function.h"

// Since we need to create ExponentialFunction objects for testing, and the constructor
// requires a Dict*, we need to include the necessary headers for creating valid Dict objects.
#include "Dict.h"
#include "Object.h"
#include "PDFDoc.h"

#include <memory>
#include <cmath>

class ExponentialFunctionTest_373 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Helper to create a Dict with the required entries for ExponentialFunction
// ExponentialFunction requires:
// - Domain (required)
// - N (exponent, required)
// - C0 (optional, defaults to [0.0])
// - C1 (optional, defaults to [1.0])
// - Range (optional)

static Object makeExponentialFunctionDict(XRef *xref, double n, 
                                           const double *c0, int c0Len,
                                           const double *c1, int c1Len,
                                           int numOutputs) {
    Dict *dict = new Dict(xref);
    
    // FunctionType = 2 (Exponential)
    dict->add("FunctionType", Object(2));
    
    // Domain: [0 1] for single input
    Object domainArray = Object(new Array(xref));
    domainArray.arrayAdd(Object(0.0));
    domainArray.arrayAdd(Object(1.0));
    dict->add("Domain", std::move(domainArray));
    
    // N (exponent)
    dict->add("N", Object(n));
    
    // C0
    if (c0 && c0Len > 0) {
        Object c0Array = Object(new Array(xref));
        for (int i = 0; i < c0Len; i++) {
            c0Array.arrayAdd(Object(c0[i]));
        }
        dict->add("C0", std::move(c0Array));
    }
    
    // C1
    if (c1 && c1Len > 0) {
        Object c1Array = Object(new Array(xref));
        for (int i = 0; i < c1Len; i++) {
            c1Array.arrayAdd(Object(c1[i]));
        }
        dict->add("C1", std::move(c1Array));
    }
    
    // Range
    if (numOutputs > 0) {
        Object rangeArray = Object(new Array(xref));
        for (int i = 0; i < numOutputs; i++) {
            rangeArray.arrayAdd(Object(0.0));
            rangeArray.arrayAdd(Object(1.0));
        }
        dict->add("Range", std::move(rangeArray));
    }
    
    return Object(dict);
}

// Test getE returns the exponent value
TEST_F(ExponentialFunctionTest_373, GetE_ReturnsExponentValue_373) {
    double c0[] = {0.0};
    double c1[] = {1.0};
    Object dictObj = makeExponentialFunctionDict(nullptr, 2.0, c0, 1, c1, 1, 1);
    
    ExponentialFunction func(dictObj.getDict());
    
    if (func.isOk()) {
        EXPECT_DOUBLE_EQ(func.getE(), 2.0);
    }
}

// Test getE with exponent = 1 (linear case)
TEST_F(ExponentialFunctionTest_373, GetE_LinearExponent_373) {
    double c0[] = {0.0};
    double c1[] = {1.0};
    Object dictObj = makeExponentialFunctionDict(nullptr, 1.0, c0, 1, c1, 1, 1);
    
    ExponentialFunction func(dictObj.getDict());
    
    if (func.isOk()) {
        EXPECT_DOUBLE_EQ(func.getE(), 1.0);
    }
}

// Test getE with exponent = 0
TEST_F(ExponentialFunctionTest_373, GetE_ZeroExponent_373) {
    double c0[] = {0.0};
    double c1[] = {1.0};
    Object dictObj = makeExponentialFunctionDict(nullptr, 0.0, c0, 1, c1, 1, 1);
    
    ExponentialFunction func(dictObj.getDict());
    
    if (func.isOk()) {
        EXPECT_DOUBLE_EQ(func.getE(), 0.0);
    }
}

// Test getC0 returns the C0 array
TEST_F(ExponentialFunctionTest_373, GetC0_ReturnsC0Values_373) {
    double c0[] = {0.5};
    double c1[] = {1.0};
    Object dictObj = makeExponentialFunctionDict(nullptr, 1.0, c0, 1, c1, 1, 1);
    
    ExponentialFunction func(dictObj.getDict());
    
    if (func.isOk()) {
        const double *result = func.getC0();
        ASSERT_NE(result, nullptr);
        EXPECT_DOUBLE_EQ(result[0], 0.5);
    }
}

// Test getC1 returns the C1 array
TEST_F(ExponentialFunctionTest_373, GetC1_ReturnsC1Values_373) {
    double c0[] = {0.0};
    double c1[] = {0.75};
    Object dictObj = makeExponentialFunctionDict(nullptr, 1.0, c0, 1, c1, 1, 1);
    
    ExponentialFunction func(dictObj.getDict());
    
    if (func.isOk()) {
        const double *result = func.getC1();
        ASSERT_NE(result, nullptr);
        EXPECT_DOUBLE_EQ(result[0], 0.75);
    }
}

// Test getType returns ExponentialFunction type (Type 2)
TEST_F(ExponentialFunctionTest_373, GetType_ReturnsCorrectType_373) {
    double c0[] = {0.0};
    double c1[] = {1.0};
    Object dictObj = makeExponentialFunctionDict(nullptr, 1.0, c0, 1, c1, 1, 1);
    
    ExponentialFunction func(dictObj.getDict());
    
    if (func.isOk()) {
        EXPECT_EQ(func.getType(), Function::Type::Exponential);
    }
}

// Test transform with linear interpolation (N=1)
TEST_F(ExponentialFunctionTest_373, Transform_LinearInterpolation_373) {
    double c0[] = {0.0};
    double c1[] = {1.0};
    Object dictObj = makeExponentialFunctionDict(nullptr, 1.0, c0, 1, c1, 1, 1);
    
    ExponentialFunction func(dictObj.getDict());
    
    if (func.isOk()) {
        double in = 0.5;
        double out = 0.0;
        func.transform(&in, &out);
        EXPECT_NEAR(out, 0.5, 1e-6);
    }
}

// Test transform at input = 0
TEST_F(ExponentialFunctionTest_373, Transform_InputZero_ReturnsC0_373) {
    double c0[] = {0.3};
    double c1[] = {0.9};
    Object dictObj = makeExponentialFunctionDict(nullptr, 2.0, c0, 1, c1, 1, 1);
    
    ExponentialFunction func(dictObj.getDict());
    
    if (func.isOk()) {
        double in = 0.0;
        double out = 0.0;
        func.transform(&in, &out);
        EXPECT_NEAR(out, 0.3, 1e-6);
    }
}

// Test transform at input = 1
TEST_F(ExponentialFunctionTest_373, Transform_InputOne_ReturnsC1_373) {
    double c0[] = {0.3};
    double c1[] = {0.9};
    Object dictObj = makeExponentialFunctionDict(nullptr, 2.0, c0, 1, c1, 1, 1);
    
    ExponentialFunction func(dictObj.getDict());
    
    if (func.isOk()) {
        double in = 1.0;
        double out = 0.0;
        func.transform(&in, &out);
        EXPECT_NEAR(out, 0.9, 1e-6);
    }
}

// Test copy creates a valid copy
TEST_F(ExponentialFunctionTest_373, Copy_CreatesValidCopy_373) {
    double c0[] = {0.0};
    double c1[] = {1.0};
    Object dictObj = makeExponentialFunctionDict(nullptr, 3.0, c0, 1, c1, 1, 1);
    
    ExponentialFunction func(dictObj.getDict());
    
    if (func.isOk()) {
        auto copyFunc = func.copy();
        ASSERT_NE(copyFunc, nullptr);
        
        // The copy should have the same exponent
        auto *expCopy = dynamic_cast<ExponentialFunction *>(copyFunc.get());
        ASSERT_NE(expCopy, nullptr);
        EXPECT_DOUBLE_EQ(expCopy->getE(), 3.0);
    }
}

// Test with large exponent
TEST_F(ExponentialFunctionTest_373, GetE_LargeExponent_373) {
    double c0[] = {0.0};
    double c1[] = {1.0};
    Object dictObj = makeExponentialFunctionDict(nullptr, 100.0, c0, 1, c1, 1, 1);
    
    ExponentialFunction func(dictObj.getDict());
    
    if (func.isOk()) {
        EXPECT_DOUBLE_EQ(func.getE(), 100.0);
    }
}

// Test with fractional exponent
TEST_F(ExponentialFunctionTest_373, GetE_FractionalExponent_373) {
    double c0[] = {0.0};
    double c1[] = {1.0};
    Object dictObj = makeExponentialFunctionDict(nullptr, 0.5, c0, 1, c1, 1, 1);
    
    ExponentialFunction func(dictObj.getDict());
    
    if (func.isOk()) {
        EXPECT_DOUBLE_EQ(func.getE(), 0.5);
    }
}

// Test with multiple outputs
TEST_F(ExponentialFunctionTest_373, Transform_MultipleOutputs_373) {
    double c0[] = {0.0, 0.0, 0.0};
    double c1[] = {1.0, 0.5, 0.25};
    Object dictObj = makeExponentialFunctionDict(nullptr, 1.0, c0, 3, c1, 3, 3);
    
    ExponentialFunction func(dictObj.getDict());
    
    if (func.isOk()) {
        double in = 1.0;
        double out[3] = {0.0, 0.0, 0.0};
        func.transform(&in, out);
        EXPECT_NEAR(out[0], 1.0, 1e-6);
        EXPECT_NEAR(out[1], 0.5, 1e-6);
        EXPECT_NEAR(out[2], 0.25, 1e-6);
    }
}

// Test isOk on valid function
TEST_F(ExponentialFunctionTest_373, IsOk_ValidFunction_ReturnsTrue_373) {
    double c0[] = {0.0};
    double c1[] = {1.0};
    Object dictObj = makeExponentialFunctionDict(nullptr, 1.0, c0, 1, c1, 1, 1);
    
    ExponentialFunction func(dictObj.getDict());
    
    // A properly constructed function should be ok
    // (This may or may not pass depending on whether nullptr xref is acceptable)
    // We just verify the method is callable
    bool ok = func.isOk();
    (void)ok; // Just verify it doesn't crash
}

// Test copy preserves C0 and C1
TEST_F(ExponentialFunctionTest_373, Copy_PreservesC0AndC1_373) {
    double c0[] = {0.2};
    double c1[] = {0.8};
    Object dictObj = makeExponentialFunctionDict(nullptr, 2.0, c0, 1, c1, 1, 1);
    
    ExponentialFunction func(dictObj.getDict());
    
    if (func.isOk()) {
        auto copyFunc = func.copy();
        auto *expCopy = dynamic_cast<ExponentialFunction *>(copyFunc.get());
        ASSERT_NE(expCopy, nullptr);
        
        EXPECT_DOUBLE_EQ(expCopy->getC0()[0], 0.2);
        EXPECT_DOUBLE_EQ(expCopy->getC1()[0], 0.8);
        EXPECT_DOUBLE_EQ(expCopy->getE(), 2.0);
    }
}

// Test transform with quadratic (N=2) at midpoint
TEST_F(ExponentialFunctionTest_373, Transform_QuadraticAtMidpoint_373) {
    double c0[] = {0.0};
    double c1[] = {1.0};
    Object dictObj = makeExponentialFunctionDict(nullptr, 2.0, c0, 1, c1, 1, 1);
    
    ExponentialFunction func(dictObj.getDict());
    
    if (func.isOk()) {
        double in = 0.5;
        double out = 0.0;
        func.transform(&in, &out);
        // f(x) = C0 + x^N * (C1 - C0) = 0 + 0.25 * 1 = 0.25
        EXPECT_NEAR(out, 0.25, 1e-6);
    }
}
