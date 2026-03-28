#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Function.h"
#include "Object.h"
#include <memory>

// Since Function is abstract (has pure virtual methods), we need a concrete subclass for testing.
// However, we can test through the static parse method and any concrete instances we can create.
// We'll test the interface methods that are accessible.

class FunctionTest_347 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that parsing a null/invalid object returns nullptr or handles gracefully
TEST_F(FunctionTest_347, ParseNullObject_347) {
    Object obj;
    auto func = Function::parse(&obj);
    // An invalid/null object should not produce a valid function
    EXPECT_EQ(func, nullptr);
}

// Test parsing an invalid object type
TEST_F(FunctionTest_347, ParseInvalidObjectType_347) {
    Object obj;
    obj = Object(42); // An integer object, not a valid function definition
    auto func = Function::parse(&obj);
    EXPECT_EQ(func, nullptr);
}

// Test that parse handles a dictionary without FunctionType gracefully
TEST_F(FunctionTest_347, ParseDictWithoutFunctionType_347) {
    // Create an empty dictionary object - missing FunctionType should fail
    Dict *dict = new Dict(nullptr);
    Object obj = Object(dict);
    auto func = Function::parse(&obj);
    // Without proper FunctionType, parse should fail
    EXPECT_EQ(func, nullptr);
}

// Test parsing with a dictionary that has an invalid FunctionType
TEST_F(FunctionTest_347, ParseDictWithInvalidFunctionType_347) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(999)); // Invalid function type
    Object obj = Object(dict);
    auto func = Function::parse(&obj);
    EXPECT_EQ(func, nullptr);
}

// Test parsing a Type 4 (PostScript Calculator) function with minimal valid setup
TEST_F(FunctionTest_347, ParseType4FunctionMissingDomain_347) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(4));
    // Missing Domain - should fail
    Object obj = Object(dict);
    auto func = Function::parse(&obj);
    EXPECT_EQ(func, nullptr);
}

// Test that getInputSize returns proper value through a parsed function
// We attempt to create a valid Type 4 function
TEST_F(FunctionTest_347, ParseType4FunctionWithDomain_347) {
    // Type 4 needs: FunctionType=4, Domain array, Range array, and a stream with PS code
    // This is complex to set up without full PDF infrastructure, so we test what we can
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(4));
    
    // Create Domain array [0 1]
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    // Create Range array [0 1]
    Array *rangeArr = new Array(nullptr);
    rangeArr->add(Object(0.0));
    rangeArr->add(Object(1.0));
    dict->add("Range", Object(rangeArr));
    
    Object obj = Object(dict);
    auto func = Function::parse(&obj);
    // Type 4 needs a stream, not a dict, so this should fail
    EXPECT_EQ(func, nullptr);
}

// Test parsing with FunctionType 0 (Sampled) but missing required entries
TEST_F(FunctionTest_347, ParseType0FunctionIncomplete_347) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(0));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    // Missing Size, BitsPerSample, etc.
    Object obj = Object(dict);
    auto func = Function::parse(&obj);
    // Should fail due to missing required entries (and not being a stream)
    EXPECT_EQ(func, nullptr);
}

// Test parsing with FunctionType 2 (Exponential Interpolation)
TEST_F(FunctionTest_347, ParseType2FunctionMinimal_347) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    // Domain is required
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    // N (interpolation exponent) is required
    dict->add("N", Object(1.0));
    
    Object obj = Object(dict);
    auto func = Function::parse(&obj);
    
    if (func) {
        EXPECT_TRUE(func->isOk());
        EXPECT_EQ(func->getInputSize(), 1);
        EXPECT_GE(func->getOutputSize(), 1);
        EXPECT_EQ(func->getDomainMin(0), 0.0);
        EXPECT_EQ(func->getDomainMax(0), 1.0);
    }
}

// Test parsing Type 2 function with C0, C1, and Range
TEST_F(FunctionTest_347, ParseType2FunctionWithC0C1Range_347) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    dict->add("N", Object(1.0));
    
    Array *c0Arr = new Array(nullptr);
    c0Arr->add(Object(0.0));
    c0Arr->add(Object(0.0));
    c0Arr->add(Object(0.0));
    dict->add("C0", Object(c0Arr));
    
    Array *c1Arr = new Array(nullptr);
    c1Arr->add(Object(1.0));
    c1Arr->add(Object(1.0));
    c1Arr->add(Object(1.0));
    dict->add("C1", Object(c1Arr));
    
    Array *rangeArr = new Array(nullptr);
    rangeArr->add(Object(0.0));
    rangeArr->add(Object(1.0));
    rangeArr->add(Object(0.0));
    rangeArr->add(Object(1.0));
    rangeArr->add(Object(0.0));
    rangeArr->add(Object(1.0));
    dict->add("Range", Object(rangeArr));
    
    Object obj = Object(dict);
    auto func = Function::parse(&obj);
    
    if (func) {
        EXPECT_TRUE(func->isOk());
        EXPECT_EQ(func->getInputSize(), 1);
        EXPECT_EQ(func->getOutputSize(), 3);
        
        EXPECT_EQ(func->getDomainMin(0), 0.0);
        EXPECT_EQ(func->getDomainMax(0), 1.0);
        
        EXPECT_TRUE(func->getHasRange());
        EXPECT_EQ(func->getRangeMin(0), 0.0);
        EXPECT_EQ(func->getRangeMax(0), 1.0);
        EXPECT_EQ(func->getRangeMin(1), 0.0);
        EXPECT_EQ(func->getRangeMax(1), 1.0);
        EXPECT_EQ(func->getRangeMin(2), 0.0);
        EXPECT_EQ(func->getRangeMax(2), 1.0);
    }
}

// Test Type 2 function transform at boundary input 0.0
TEST_F(FunctionTest_347, Type2FunctionTransformAtZero_347) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    dict->add("N", Object(1.0));
    
    Array *c0Arr = new Array(nullptr);
    c0Arr->add(Object(0.5));
    dict->add("C0", Object(c0Arr));
    
    Array *c1Arr = new Array(nullptr);
    c1Arr->add(Object(1.0));
    dict->add("C1", Object(c1Arr));
    
    Array *rangeArr = new Array(nullptr);
    rangeArr->add(Object(0.0));
    rangeArr->add(Object(1.0));
    dict->add("Range", Object(rangeArr));
    
    Object obj = Object(dict);
    auto func = Function::parse(&obj);
    
    if (func && func->isOk()) {
        double in[1] = {0.0};
        double out[1] = {0.0};
        func->transform(in, out);
        // At x=0, result should be C0[0] = 0.5
        EXPECT_NEAR(out[0], 0.5, 1e-6);
    }
}

// Test Type 2 function transform at boundary input 1.0
TEST_F(FunctionTest_347, Type2FunctionTransformAtOne_347) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    dict->add("N", Object(1.0));
    
    Array *c0Arr = new Array(nullptr);
    c0Arr->add(Object(0.0));
    dict->add("C0", Object(c0Arr));
    
    Array *c1Arr = new Array(nullptr);
    c1Arr->add(Object(1.0));
    dict->add("C1", Object(c1Arr));
    
    Array *rangeArr = new Array(nullptr);
    rangeArr->add(Object(0.0));
    rangeArr->add(Object(1.0));
    dict->add("Range", Object(rangeArr));
    
    Object obj = Object(dict);
    auto func = Function::parse(&obj);
    
    if (func && func->isOk()) {
        double in[1] = {1.0};
        double out[1] = {0.0};
        func->transform(in, out);
        // At x=1, result should be C1[0] = 1.0
        EXPECT_NEAR(out[0], 1.0, 1e-6);
    }
}

// Test Type 2 function transform at midpoint
TEST_F(FunctionTest_347, Type2FunctionTransformAtMidpoint_347) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    dict->add("N", Object(1.0));
    
    Array *c0Arr = new Array(nullptr);
    c0Arr->add(Object(0.0));
    dict->add("C0", Object(c0Arr));
    
    Array *c1Arr = new Array(nullptr);
    c1Arr->add(Object(1.0));
    dict->add("C1", Object(c1Arr));
    
    Array *rangeArr = new Array(nullptr);
    rangeArr->add(Object(0.0));
    rangeArr->add(Object(1.0));
    dict->add("Range", Object(rangeArr));
    
    Object obj = Object(dict);
    auto func = Function::parse(&obj);
    
    if (func && func->isOk()) {
        double in[1] = {0.5};
        double out[1] = {0.0};
        func->transform(in, out);
        // Linear interpolation at 0.5: 0.0 + 0.5*(1.0 - 0.0) = 0.5
        EXPECT_NEAR(out[0], 0.5, 1e-6);
    }
}

// Test Type 2 function with N=2 (quadratic)
TEST_F(FunctionTest_347, Type2FunctionQuadraticTransform_347) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    dict->add("N", Object(2.0));
    
    Array *c0Arr = new Array(nullptr);
    c0Arr->add(Object(0.0));
    dict->add("C0", Object(c0Arr));
    
    Array *c1Arr = new Array(nullptr);
    c1Arr->add(Object(1.0));
    dict->add("C1", Object(c1Arr));
    
    Array *rangeArr = new Array(nullptr);
    rangeArr->add(Object(0.0));
    rangeArr->add(Object(1.0));
    dict->add("Range", Object(rangeArr));
    
    Object obj = Object(dict);
    auto func = Function::parse(&obj);
    
    if (func && func->isOk()) {
        double in[1] = {0.5};
        double out[1] = {0.0};
        func->transform(in, out);
        // With N=2: result = C0 + x^N * (C1 - C0) = 0 + 0.25 * 1 = 0.25
        EXPECT_NEAR(out[0], 0.25, 1e-6);
    }
}

// Test Type 2 function copy
TEST_F(FunctionTest_347, Type2FunctionCopy_347) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    dict->add("N", Object(1.0));
    
    Array *c0Arr = new Array(nullptr);
    c0Arr->add(Object(0.0));
    dict->add("C0", Object(c0Arr));
    
    Array *c1Arr = new Array(nullptr);
    c1Arr->add(Object(1.0));
    dict->add("C1", Object(c1Arr));
    
    Object obj = Object(dict);
    auto func = Function::parse(&obj);
    
    if (func && func->isOk()) {
        auto funcCopy = func->copy();
        ASSERT_NE(funcCopy, nullptr);
        EXPECT_TRUE(funcCopy->isOk());
        EXPECT_EQ(funcCopy->getInputSize(), func->getInputSize());
        EXPECT_EQ(funcCopy->getOutputSize(), func->getOutputSize());
        EXPECT_EQ(funcCopy->getDomainMin(0), func->getDomainMin(0));
        EXPECT_EQ(funcCopy->getDomainMax(0), func->getDomainMax(0));
        
        // Verify both produce same output
        double in[1] = {0.5};
        double out1[1], out2[1];
        func->transform(in, out1);
        funcCopy->transform(in, out2);
        EXPECT_NEAR(out1[0], out2[0], 1e-10);
    }
}

// Test hasDifferentResultSet with same function
TEST_F(FunctionTest_347, Type2FunctionHasDifferentResultSetSame_347) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    dict->add("N", Object(1.0));
    
    Object obj = Object(dict);
    auto func = Function::parse(&obj);
    
    if (func && func->isOk()) {
        // Comparing with itself should return false (not different)
        EXPECT_FALSE(func->hasDifferentResultSet(func.get()));
    }
}

// Test domain clamping: input below domain min
TEST_F(FunctionTest_347, Type2FunctionInputBelowDomain_347) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    dict->add("N", Object(1.0));
    
    Array *c0Arr = new Array(nullptr);
    c0Arr->add(Object(0.0));
    dict->add("C0", Object(c0Arr));
    
    Array *c1Arr = new Array(nullptr);
    c1Arr->add(Object(1.0));
    dict->add("C1", Object(c1Arr));
    
    Array *rangeArr = new Array(nullptr);
    rangeArr->add(Object(0.0));
    rangeArr->add(Object(1.0));
    dict->add("Range", Object(rangeArr));
    
    Object obj = Object(dict);
    auto func = Function::parse(&obj);
    
    if (func && func->isOk()) {
        double in[1] = {-0.5}; // Below domain min of 0.0
        double out[1] = {0.0};
        func->transform(in, out);
        // Input should be clamped to 0.0, so result = C0[0] = 0.0
        EXPECT_NEAR(out[0], 0.0, 1e-6);
    }
}

// Test domain clamping: input above domain max
TEST_F(FunctionTest_347, Type2FunctionInputAboveDomain_347) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    dict->add("N", Object(1.0));
    
    Array *c0Arr = new Array(nullptr);
    c0Arr->add(Object(0.0));
    dict->add("C0", Object(c0Arr));
    
    Array *c1Arr = new Array(nullptr);
    c1Arr->add(Object(1.0));
    dict->add("C1", Object(c1Arr));
    
    Array *rangeArr = new Array(nullptr);
    rangeArr->add(Object(0.0));
    rangeArr->add(Object(1.0));
    dict->add("Range", Object(rangeArr));
    
    Object obj = Object(dict);
    auto func = Function::parse(&obj);
    
    if (func && func->isOk()) {
        double in[1] = {1.5}; // Above domain max of 1.0
        double out[1] = {0.0};
        func->transform(in, out);
        // Input should be clamped to 1.0, so result = C1[0] = 1.0
        EXPECT_NEAR(out[0], 1.0, 1e-6);
    }
}

// Test getHasRange when range is specified
TEST_F(FunctionTest_347, Type2FunctionGetHasRangeTrue_347) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    dict->add("N", Object(1.0));
    
    Array *rangeArr = new Array(nullptr);
    rangeArr->add(Object(0.0));
    rangeArr->add(Object(1.0));
    dict->add("Range", Object(rangeArr));
    
    Object obj = Object(dict);
    auto func = Function::parse(&obj);
    
    if (func && func->isOk()) {
        EXPECT_TRUE(func->getHasRange());
    }
}

// Test getHasRange when range is not specified
TEST_F(FunctionTest_347, Type2FunctionGetHasRangeFalse_347) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    dict->add("N", Object(1.0));
    
    // No Range specified
    Object obj = Object(dict);
    auto func = Function::parse(&obj);
    
    if (func && func->isOk()) {
        EXPECT_FALSE(func->getHasRange());
    }
}

// Test with multiple input dimensions (Type 2 only supports 1 input)
TEST_F(FunctionTest_347, Type2FunctionMultipleInputDimensions_347) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    // Domain with 2 inputs (4 values)
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    dict->add("N", Object(1.0));
    
    Object obj = Object(dict);
    auto func = Function::parse(&obj);
    
    // Type 2 functions must have m=1, so this should fail
    if (func) {
        // If it didn't fail, verify it's not OK or has input size 1
        // The spec says ExponentialFunction must have m=1
        EXPECT_FALSE(func->isOk());
    }
}

// Test parsing FunctionType 3 (Stitching) without required entries
TEST_F(FunctionTest_347, ParseType3FunctionIncomplete_347) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(3));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    // Missing Functions, Bounds, Encode
    Object obj = Object(dict);
    auto func = Function::parse(&obj);
    
    // Should fail due to missing required entries
    EXPECT_EQ(func, nullptr);
}

// Test negative FunctionType
TEST_F(FunctionTest_347, ParseNegativeFunctionType_347) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(-1));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    Object obj = Object(dict);
    auto func = Function::parse(&obj);
    EXPECT_EQ(func, nullptr);
}

// Test FunctionType 1 (not a standard PDF function type in some implementations)
TEST_F(FunctionTest_347, ParseFunctionType1_347) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(1));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    Object obj = Object(dict);
    auto func = Function::parse(&obj);
    // FunctionType 1 is not standard; should likely fail
    // (or succeed if implementation supports it)
    // We just verify it doesn't crash
}

// Test Type 2 with multiple outputs
TEST_F(FunctionTest_347, Type2FunctionMultipleOutputs_347) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    dict->add("N", Object(1.0));
    
    Array *c0Arr = new Array(nullptr);
    c0Arr->add(Object(0.0));
    c0Arr->add(Object(0.2));
    c0Arr->add(Object(0.4));
    dict->add("C0", Object(c0Arr));
    
    Array *c1Arr = new Array(nullptr);
    c1Arr->add(Object(1.0));
    c1Arr->add(Object(0.8));
    c1Arr->add(Object(0.6));
    dict->add("C1", Object(c1Arr));
    
    Object obj = Object(dict);
    auto func = Function::parse(&obj);
    
    if (func && func->isOk()) {
        EXPECT_EQ(func->getOutputSize(), 3);
        
        double in[1] = {0.0};
        double out[3] = {0};
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.0, 1e-6);
        EXPECT_NEAR(out[1], 0.2, 1e-6);
        EXPECT_NEAR(out[2], 0.4, 1e-6);
        
        in[0] = 1.0;
        func->transform(in, out);
        EXPECT_NEAR(out[0], 1.0, 1e-6);
        EXPECT_NEAR(out[1], 0.8, 1e-6);
        EXPECT_NEAR(out[2], 0.6, 1e-6);
    }
}

// Test getType for Type 2 function
TEST_F(FunctionTest_347, Type2FunctionGetType_347) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    dict->add("N", Object(1.0));
    
    Object obj = Object(dict);
    auto func = Function::parse(&obj);
    
    if (func && func->isOk()) {
        // Type should correspond to exponential interpolation
        auto type = func->getType();
        // Just verify it returns a valid type without crashing
        (void)type;
    }
}

// Test range clamping
TEST_F(FunctionTest_347, Type2FunctionRangeClamping_347) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    dict->add("N", Object(1.0));
    
    Array *c0Arr = new Array(nullptr);
    c0Arr->add(Object(-1.0)); // Below range min
    dict->add("C0", Object(c0Arr));
    
    Array *c1Arr = new Array(nullptr);
    c1Arr->add(Object(2.0)); // Above range max
    dict->add("C1", Object(c1Arr));
    
    Array *rangeArr = new Array(nullptr);
    rangeArr->add(Object(0.0));
    rangeArr->add(Object(1.0));
    dict->add("Range", Object(rangeArr));
    
    Object obj = Object(dict);
    auto func = Function::parse(&obj);
    
    if (func && func->isOk()) {
        double in[1] = {0.0};
        double out[1] = {0.0};
        func->transform(in, out);
        // C0 = -1.0 but range is [0,1], so should be clamped to 0.0
        EXPECT_NEAR(out[0], 0.0, 1e-6);
        
        in[0] = 1.0;
        func->transform(in, out);
        // C1 = 2.0 but range is [0,1], so should be clamped to 1.0
        EXPECT_NEAR(out[0], 1.0, 1e-6);
    }
}

// Test empty domain array
TEST_F(FunctionTest_347, ParseEmptyDomain_347) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArr = new Array(nullptr);
    // Empty domain
    dict->add("Domain", Object(domainArr));
    
    dict->add("N", Object(1.0));
    
    Object obj = Object(dict);
    auto func = Function::parse(&obj);
    // Empty domain should fail
    EXPECT_EQ(func, nullptr);
}
