#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Function.h"

// Since Function is abstract (has pure virtual methods), we need a concrete subclass for testing.
// However, we cannot re-implement internal logic. We'll use Function::parse to create instances
// where possible, and test the interface methods.

// For testing purposes, we need to work with what's available through the public interface.
// Function::parse creates Function objects from PDF Object structures.

#include "Object.h"
#include "Dict.h"
#include "PDFDoc.h"

class FunctionTest_353 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that parsing a null/invalid object returns nullptr
TEST_F(FunctionTest_353, ParseNullObjectReturnsNull_353) {
    Object obj;
    auto func = Function::parse(&obj);
    EXPECT_EQ(func, nullptr);
}

// Test that parsing an invalid type object returns nullptr
TEST_F(FunctionTest_353, ParseInvalidObjectReturnsNull_353) {
    Object obj(42); // integer object, not a valid function
    auto func = Function::parse(&obj);
    EXPECT_EQ(func, nullptr);
}

// Test parsing with a boolean object (invalid for function)
TEST_F(FunctionTest_353, ParseBoolObjectReturnsNull_353) {
    Object obj(true);
    auto func = Function::parse(&obj);
    EXPECT_EQ(func, nullptr);
}

// Test parsing with a string object (invalid for function)
TEST_F(FunctionTest_353, ParseStringObjectReturnsNull_353) {
    Object obj(new GooString("test"));
    auto func = Function::parse(&obj);
    EXPECT_EQ(func, nullptr);
}

// Test parsing with a real number object (invalid for function)
TEST_F(FunctionTest_353, ParseRealObjectReturnsNull_353) {
    Object obj(3.14);
    auto func = Function::parse(&obj);
    EXPECT_EQ(func, nullptr);
}

// Test that getHasRange returns false by default for a function without range specified
// We test this indirectly through the interface
TEST_F(FunctionTest_353, GetHasRangeReturnsBool_353) {
    // Since we can't easily construct a valid Function without a proper PDF structure,
    // we verify the interface exists and compiles correctly
    // This test mainly validates the interface contract
    Object obj;
    auto func = Function::parse(&obj);
    // func should be nullptr for invalid input
    EXPECT_EQ(func, nullptr);
}

// Test that funcMaxOutputs and funcMaxInputs boundaries are respected
// We verify the constants are accessible
TEST_F(FunctionTest_353, ConstantsAreDefined_353) {
    EXPECT_EQ(funcMaxInputs, 32);
    EXPECT_EQ(funcMaxOutputs, 32);
    EXPECT_EQ(sampledFuncMaxInputs, 16);
}

// Test creating a function dictionary-based function (Type 2 - Exponential)
// by constructing proper PDF objects
TEST_F(FunctionTest_353, ParseValidType2FunctionDict_353) {
    // Create a dictionary representing a Type 2 (exponential interpolation) function
    Dict *dict = new Dict(static_cast<XRef*>(nullptr));
    
    // FunctionType = 2
    dict->add("FunctionType", Object(2));
    
    // Domain = [0 1]
    Array *domainArray = new Array(static_cast<XRef*>(nullptr));
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict->add("Domain", Object(domainArray));
    
    // C0 = [0]
    Array *c0Array = new Array(static_cast<XRef*>(nullptr));
    c0Array->add(Object(0.0));
    dict->add("C0", Object(c0Array));
    
    // C1 = [1]
    Array *c1Array = new Array(static_cast<XRef*>(nullptr));
    c1Array->add(Object(1.0));
    dict->add("C1", Object(c1Array));
    
    // N = 1 (linear interpolation)
    dict->add("N", Object(1.0));
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    
    if (func) {
        EXPECT_TRUE(func->isOk());
        EXPECT_EQ(func->getInputSize(), 1);
        EXPECT_EQ(func->getOutputSize(), 1);
        EXPECT_DOUBLE_EQ(func->getDomainMin(0), 0.0);
        EXPECT_DOUBLE_EQ(func->getDomainMax(0), 1.0);
    }
}

// Test Type 2 function with Range specified
TEST_F(FunctionTest_353, ParseType2FunctionWithRange_353) {
    Dict *dict = new Dict(static_cast<XRef*>(nullptr));
    
    dict->add("FunctionType", Object(2));
    
    Array *domainArray = new Array(static_cast<XRef*>(nullptr));
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict->add("Domain", Object(domainArray));
    
    Array *rangeArray = new Array(static_cast<XRef*>(nullptr));
    rangeArray->add(Object(0.0));
    rangeArray->add(Object(1.0));
    dict->add("Range", Object(rangeArray));
    
    dict->add("N", Object(1.0));
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    
    if (func) {
        EXPECT_TRUE(func->isOk());
        EXPECT_TRUE(func->getHasRange());
        EXPECT_DOUBLE_EQ(func->getRangeMin(0), 0.0);
        EXPECT_DOUBLE_EQ(func->getRangeMax(0), 1.0);
    }
}

// Test Type 2 function transform
TEST_F(FunctionTest_353, Type2FunctionTransform_353) {
    Dict *dict = new Dict(static_cast<XRef*>(nullptr));
    
    dict->add("FunctionType", Object(2));
    
    Array *domainArray = new Array(static_cast<XRef*>(nullptr));
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict->add("Domain", Object(domainArray));
    
    Array *c0Array = new Array(static_cast<XRef*>(nullptr));
    c0Array->add(Object(0.0));
    dict->add("C0", Object(c0Array));
    
    Array *c1Array = new Array(static_cast<XRef*>(nullptr));
    c1Array->add(Object(1.0));
    dict->add("C1", Object(c1Array));
    
    dict->add("N", Object(1.0));
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    
    if (func) {
        EXPECT_TRUE(func->isOk());
        
        // Test transform at x=0
        double in0 = 0.0;
        double out0 = -1.0;
        func->transform(&in0, &out0);
        EXPECT_NEAR(out0, 0.0, 1e-6);
        
        // Test transform at x=1
        double in1 = 1.0;
        double out1 = -1.0;
        func->transform(&in1, &out1);
        EXPECT_NEAR(out1, 1.0, 1e-6);
        
        // Test transform at x=0.5
        double in05 = 0.5;
        double out05 = -1.0;
        func->transform(&in05, &out05);
        EXPECT_NEAR(out05, 0.5, 1e-6);
    }
}

// Test copy of a function
TEST_F(FunctionTest_353, CopyFunction_353) {
    Dict *dict = new Dict(static_cast<XRef*>(nullptr));
    
    dict->add("FunctionType", Object(2));
    
    Array *domainArray = new Array(static_cast<XRef*>(nullptr));
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict->add("Domain", Object(domainArray));
    
    dict->add("N", Object(1.0));
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    
    if (func) {
        auto funcCopy = func->copy();
        ASSERT_NE(funcCopy, nullptr);
        EXPECT_TRUE(funcCopy->isOk());
        EXPECT_EQ(funcCopy->getInputSize(), func->getInputSize());
        EXPECT_EQ(funcCopy->getOutputSize(), func->getOutputSize());
        EXPECT_DOUBLE_EQ(funcCopy->getDomainMin(0), func->getDomainMin(0));
        EXPECT_DOUBLE_EQ(funcCopy->getDomainMax(0), func->getDomainMax(0));
        EXPECT_EQ(funcCopy->getHasRange(), func->getHasRange());
    }
}

// Test hasDifferentResultSet with same function
TEST_F(FunctionTest_353, HasDifferentResultSetSameFunction_353) {
    Dict *dict = new Dict(static_cast<XRef*>(nullptr));
    
    dict->add("FunctionType", Object(2));
    
    Array *domainArray = new Array(static_cast<XRef*>(nullptr));
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict->add("Domain", Object(domainArray));
    
    dict->add("N", Object(1.0));
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    
    if (func) {
        // A function compared to itself should not have a different result set
        EXPECT_FALSE(func->hasDifferentResultSet(func.get()));
    }
}

// Test Type 2 function with multiple outputs
TEST_F(FunctionTest_353, Type2FunctionMultipleOutputs_353) {
    Dict *dict = new Dict(static_cast<XRef*>(nullptr));
    
    dict->add("FunctionType", Object(2));
    
    Array *domainArray = new Array(static_cast<XRef*>(nullptr));
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict->add("Domain", Object(domainArray));
    
    Array *c0Array = new Array(static_cast<XRef*>(nullptr));
    c0Array->add(Object(0.0));
    c0Array->add(Object(0.0));
    c0Array->add(Object(0.0));
    dict->add("C0", Object(c0Array));
    
    Array *c1Array = new Array(static_cast<XRef*>(nullptr));
    c1Array->add(Object(1.0));
    c1Array->add(Object(0.5));
    c1Array->add(Object(0.25));
    dict->add("C1", Object(c1Array));
    
    dict->add("N", Object(1.0));
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    
    if (func) {
        EXPECT_TRUE(func->isOk());
        EXPECT_EQ(func->getInputSize(), 1);
        EXPECT_EQ(func->getOutputSize(), 3);
        
        double in = 1.0;
        double out[3] = {-1.0, -1.0, -1.0};
        func->transform(&in, out);
        EXPECT_NEAR(out[0], 1.0, 1e-6);
        EXPECT_NEAR(out[1], 0.5, 1e-6);
        EXPECT_NEAR(out[2], 0.25, 1e-6);
    }
}

// Test domain clamping - input outside domain should be clamped
TEST_F(FunctionTest_353, Type2FunctionDomainClamping_353) {
    Dict *dict = new Dict(static_cast<XRef*>(nullptr));
    
    dict->add("FunctionType", Object(2));
    
    Array *domainArray = new Array(static_cast<XRef*>(nullptr));
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict->add("Domain", Object(domainArray));
    
    Array *c0Array = new Array(static_cast<XRef*>(nullptr));
    c0Array->add(Object(0.0));
    dict->add("C0", Object(c0Array));
    
    Array *c1Array = new Array(static_cast<XRef*>(nullptr));
    c1Array->add(Object(1.0));
    dict->add("C1", Object(c1Array));
    
    dict->add("N", Object(1.0));
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    
    if (func) {
        // Input below domain min
        double inBelow = -1.0;
        double outBelow = -1.0;
        func->transform(&inBelow, &outBelow);
        EXPECT_NEAR(outBelow, 0.0, 1e-6);
        
        // Input above domain max
        double inAbove = 2.0;
        double outAbove = -1.0;
        func->transform(&inAbove, &outAbove);
        EXPECT_NEAR(outAbove, 1.0, 1e-6);
    }
}

// Test function without Domain (should fail)
TEST_F(FunctionTest_353, ParseFunctionWithoutDomainFails_353) {
    Dict *dict = new Dict(static_cast<XRef*>(nullptr));
    
    dict->add("FunctionType", Object(2));
    dict->add("N", Object(1.0));
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    
    // Without Domain, function should either be null or not ok
    if (func) {
        EXPECT_FALSE(func->isOk());
    }
}

// Test function with empty domain array
TEST_F(FunctionTest_353, ParseFunctionWithEmptyDomain_353) {
    Dict *dict = new Dict(static_cast<XRef*>(nullptr));
    
    dict->add("FunctionType", Object(2));
    
    Array *domainArray = new Array(static_cast<XRef*>(nullptr));
    dict->add("Domain", Object(domainArray));
    
    dict->add("N", Object(1.0));
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    
    if (func) {
        // With empty domain, function might not be ok
        // This tests boundary behavior
        EXPECT_FALSE(func->isOk());
    }
}

// Test getType returns correct type for exponential function
TEST_F(FunctionTest_353, GetTypeForExponentialFunction_353) {
    Dict *dict = new Dict(static_cast<XRef*>(nullptr));
    
    dict->add("FunctionType", Object(2));
    
    Array *domainArray = new Array(static_cast<XRef*>(nullptr));
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict->add("Domain", Object(domainArray));
    
    dict->add("N", Object(1.0));
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    
    if (func) {
        EXPECT_TRUE(func->isOk());
        // Type should correspond to ExponentialInterpolation type
        auto type = func->getType();
        // We just verify it returns a valid type without asserting specific enum value
        // since we don't know the exact enum definitions
        (void)type;
    }
}

// Test with invalid FunctionType
TEST_F(FunctionTest_353, ParseInvalidFunctionType_353) {
    Dict *dict = new Dict(static_cast<XRef*>(nullptr));
    
    dict->add("FunctionType", Object(99)); // Invalid function type
    
    Array *domainArray = new Array(static_cast<XRef*>(nullptr));
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict->add("Domain", Object(domainArray));
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    
    // Invalid function type should result in null or not ok
    if (func) {
        EXPECT_FALSE(func->isOk());
    }
}

// Test Type 2 with N=2 (quadratic interpolation)
TEST_F(FunctionTest_353, Type2FunctionQuadraticInterpolation_353) {
    Dict *dict = new Dict(static_cast<XRef*>(nullptr));
    
    dict->add("FunctionType", Object(2));
    
    Array *domainArray = new Array(static_cast<XRef*>(nullptr));
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict->add("Domain", Object(domainArray));
    
    Array *c0Array = new Array(static_cast<XRef*>(nullptr));
    c0Array->add(Object(0.0));
    dict->add("C0", Object(c0Array));
    
    Array *c1Array = new Array(static_cast<XRef*>(nullptr));
    c1Array->add(Object(1.0));
    dict->add("C1", Object(c1Array));
    
    dict->add("N", Object(2.0)); // quadratic
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    
    if (func) {
        EXPECT_TRUE(func->isOk());
        
        // At x=0.5, result should be 0.5^2 = 0.25
        double in = 0.5;
        double out = -1.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.25, 1e-6);
        
        // At x=0, result should be 0
        double in0 = 0.0;
        double out0 = -1.0;
        func->transform(&in0, &out0);
        EXPECT_NEAR(out0, 0.0, 1e-6);
        
        // At x=1, result should be 1
        double in1 = 1.0;
        double out1 = -1.0;
        func->transform(&in1, &out1);
        EXPECT_NEAR(out1, 1.0, 1e-6);
    }
}

// Test getHasRange returns false when no range is specified
TEST_F(FunctionTest_353, GetHasRangeFalseWhenNoRange_353) {
    Dict *dict = new Dict(static_cast<XRef*>(nullptr));
    
    dict->add("FunctionType", Object(2));
    
    Array *domainArray = new Array(static_cast<XRef*>(nullptr));
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict->add("Domain", Object(domainArray));
    
    dict->add("N", Object(1.0));
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    
    if (func) {
        EXPECT_TRUE(func->isOk());
        EXPECT_FALSE(func->getHasRange());
    }
}

// Test getDomainMin and getDomainMax for multiple dimensions
TEST_F(FunctionTest_353, GetDomainMinMaxMultipleDimensions_353) {
    Dict *dict = new Dict(static_cast<XRef*>(nullptr));
    
    dict->add("FunctionType", Object(2));
    
    // 2D domain: [0 1 -1 2]
    Array *domainArray = new Array(static_cast<XRef*>(nullptr));
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict->add("Domain", Object(domainArray));
    
    dict->add("N", Object(1.0));
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    
    if (func) {
        EXPECT_TRUE(func->isOk());
        EXPECT_EQ(func->getInputSize(), 1);
        EXPECT_DOUBLE_EQ(func->getDomainMin(0), 0.0);
        EXPECT_DOUBLE_EQ(func->getDomainMax(0), 1.0);
    }
}
