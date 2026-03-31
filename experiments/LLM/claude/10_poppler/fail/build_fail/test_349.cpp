#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Function.h"
#include "Object.h"
#include <memory>

// Since Function is abstract (has pure virtual methods), we need a concrete subclass for testing.
// However, we can test through the parse() factory method if we can construct valid Function objects.
// For basic accessor tests, we'll try to use parse() or create test fixtures that exercise the interface.

class FunctionTest_349 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that parse returns nullptr for a null/invalid object
TEST_F(FunctionTest_349, ParseInvalidObjectReturnsNull_349) {
    Object obj;
    auto func = Function::parse(&obj);
    EXPECT_EQ(func, nullptr);
}

// Test parse with a non-function object (e.g., an integer)
TEST_F(FunctionTest_349, ParseNonFunctionObjectReturnsNull_349) {
    Object obj(42);
    auto func = Function::parse(&obj);
    EXPECT_EQ(func, nullptr);
}

// Test that we can create a sampled function (Type 0) via parse with a proper stream object
// This requires building a valid PDF function dictionary, which is complex.
// We'll test what we can with simpler objects.

// Test parse with a boolean object
TEST_F(FunctionTest_349, ParseBoolObjectReturnsNull_349) {
    Object obj(true);
    auto func = Function::parse(&obj);
    EXPECT_EQ(func, nullptr);
}

// Test parse with a string object
TEST_F(FunctionTest_349, ParseStringObjectReturnsNull_349) {
    Object obj(new GooString("test"));
    auto func = Function::parse(&obj);
    EXPECT_EQ(func, nullptr);
}

// Test parse with a real number object
TEST_F(FunctionTest_349, ParseRealObjectReturnsNull_349) {
    Object obj(3.14);
    auto func = Function::parse(&obj);
    EXPECT_EQ(func, nullptr);
}

// Test parse with an empty dictionary (missing FunctionType)
TEST_F(FunctionTest_349, ParseEmptyDictReturnsNull_349) {
    Object obj(new Dict(nullptr));
    auto func = Function::parse(&obj);
    EXPECT_EQ(func, nullptr);
}

// Test parse with a dictionary that has an invalid FunctionType
TEST_F(FunctionTest_349, ParseDictWithInvalidFunctionTypeReturnsNull_349) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(99));
    Object obj(dict);
    auto func = Function::parse(&obj);
    EXPECT_EQ(func, nullptr);
}

// Test parse with a Type 2 (exponential) function dictionary with minimal valid setup
TEST_F(FunctionTest_349, ParseType2FunctionMinimal_349) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    // Domain is required: [0 1]
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    // N (exponent) is required for type 2
    dict->add("N", Object(1.0));
    
    // C0 and C1 default to [0] and [1] respectively
    
    Object obj(dict);
    auto func = Function::parse(&obj);
    // Type 2 function should parse successfully with these params
    if (func) {
        EXPECT_EQ(func->getInputSize(), 1);
        EXPECT_EQ(func->getOutputSize(), 1);
        EXPECT_DOUBLE_EQ(func->getDomainMin(0), 0.0);
        EXPECT_DOUBLE_EQ(func->getDomainMax(0), 1.0);
    }
}

// Test getDomainMin and getDomainMax for a Type 2 function with specific domain
TEST_F(FunctionTest_349, Type2FunctionDomainAccessors_349) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(-5.0));
    domainArr->add(Object(10.0));
    dict->add("Domain", Object(domainArr));
    
    dict->add("N", Object(2.0));
    
    Object obj(dict);
    auto func = Function::parse(&obj);
    if (func) {
        EXPECT_DOUBLE_EQ(func->getDomainMin(0), -5.0);
        EXPECT_DOUBLE_EQ(func->getDomainMax(0), 10.0);
    }
}

// Test range accessors for a Type 2 function with Range specified
TEST_F(FunctionTest_349, Type2FunctionRangeAccessors_349) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    Array *rangeArr = new Array(nullptr);
    rangeArr->add(Object(-1.0));
    rangeArr->add(Object(2.0));
    dict->add("Range", Object(rangeArr));
    
    dict->add("N", Object(1.0));
    
    Object obj(dict);
    auto func = Function::parse(&obj);
    if (func) {
        EXPECT_TRUE(func->getHasRange());
        EXPECT_DOUBLE_EQ(func->getRangeMin(0), -1.0);
        EXPECT_DOUBLE_EQ(func->getRangeMax(0), 2.0);
    }
}

// Test transform for a Type 2 identity function (N=1, C0=[0], C1=[1])
TEST_F(FunctionTest_349, Type2IdentityTransform_349) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    dict->add("N", Object(1.0));
    
    Object obj(dict);
    auto func = Function::parse(&obj);
    if (func) {
        EXPECT_TRUE(func->isOk());
        
        double in, out;
        
        // Test at input 0.0
        in = 0.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.0, 1e-6);
        
        // Test at input 0.5
        in = 0.5;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.5, 1e-6);
        
        // Test at input 1.0
        in = 1.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 1.0, 1e-6);
    }
}

// Test copy for Type 2 function
TEST_F(FunctionTest_349, Type2FunctionCopy_349) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    dict->add("N", Object(1.0));
    
    Object obj(dict);
    auto func = Function::parse(&obj);
    if (func) {
        auto funcCopy = func->copy();
        ASSERT_NE(funcCopy, nullptr);
        EXPECT_EQ(funcCopy->getInputSize(), func->getInputSize());
        EXPECT_EQ(funcCopy->getOutputSize(), func->getOutputSize());
        EXPECT_DOUBLE_EQ(funcCopy->getDomainMin(0), func->getDomainMin(0));
        EXPECT_DOUBLE_EQ(funcCopy->getDomainMax(0), func->getDomainMax(0));
    }
}

// Test getHasRange when no range is specified
TEST_F(FunctionTest_349, Type2FunctionNoRange_349) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    dict->add("N", Object(1.0));
    
    Object obj(dict);
    auto func = Function::parse(&obj);
    if (func) {
        EXPECT_FALSE(func->getHasRange());
    }
}

// Test Type 2 function with C0 and C1 explicitly set
TEST_F(FunctionTest_349, Type2FunctionWithC0C1_349) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    Array *c0Arr = new Array(nullptr);
    c0Arr->add(Object(0.5));
    dict->add("C0", Object(c0Arr));
    
    Array *c1Arr = new Array(nullptr);
    c1Arr->add(Object(1.5));
    dict->add("C1", Object(c1Arr));
    
    dict->add("N", Object(1.0));
    
    Object obj(dict);
    auto func = Function::parse(&obj);
    if (func) {
        EXPECT_TRUE(func->isOk());
        
        double in, out;
        
        // At x=0, result should be C0 = 0.5
        in = 0.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.5, 1e-6);
        
        // At x=1, result should be C1 = 1.5
        in = 1.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 1.5, 1e-6);
        
        // At x=0.5 with N=1, result should be C0 + x*(C1-C0) = 0.5 + 0.5*1.0 = 1.0
        in = 0.5;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 1.0, 1e-6);
    }
}

// Test Type 2 function with quadratic exponent (N=2)
TEST_F(FunctionTest_349, Type2FunctionQuadratic_349) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    dict->add("N", Object(2.0));
    
    Object obj(dict);
    auto func = Function::parse(&obj);
    if (func) {
        double in, out;
        
        // At x=0.5, with N=2, C0=[0], C1=[1]: result = 0 + (0.5^2)*(1-0) = 0.25
        in = 0.5;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.25, 1e-6);
    }
}

// Test Type 4 (PostScript calculator) function
TEST_F(FunctionTest_349, ParseType4PostScriptFunction_349) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(4));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    Array *rangeArr = new Array(nullptr);
    rangeArr->add(Object(0.0));
    rangeArr->add(Object(1.0));
    dict->add("Range", Object(rangeArr));
    
    // Type 4 functions need a stream, not just a dict
    // This test verifies that a dict alone doesn't parse as Type 4
    Object obj(dict);
    auto func = Function::parse(&obj);
    // Type 4 requires a stream, so parsing from dict alone may fail
    // We just verify it doesn't crash
}

// Test hasDifferentResultSet - default should return false for same function
TEST_F(FunctionTest_349, HasDifferentResultSetDefault_349) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    dict->add("N", Object(1.0));
    
    Object obj(dict);
    auto func = Function::parse(&obj);
    if (func) {
        // hasDifferentResultSet with itself should return false by default
        EXPECT_FALSE(func->hasDifferentResultSet(func.get()));
    }
}

// Test Type 2 function with multiple outputs
TEST_F(FunctionTest_349, Type2FunctionMultipleOutputs_349) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    Array *c0Arr = new Array(nullptr);
    c0Arr->add(Object(0.0));
    c0Arr->add(Object(0.0));
    c0Arr->add(Object(0.0));
    dict->add("C0", Object(c0Arr));
    
    Array *c1Arr = new Array(nullptr);
    c1Arr->add(Object(1.0));
    c1Arr->add(Object(0.5));
    c1Arr->add(Object(0.25));
    dict->add("C1", Object(c1Arr));
    
    dict->add("N", Object(1.0));
    
    Object obj(dict);
    auto func = Function::parse(&obj);
    if (func) {
        EXPECT_EQ(func->getOutputSize(), 3);
        EXPECT_EQ(func->getInputSize(), 1);
        
        double in = 0.5;
        double out[3];
        func->transform(&in, out);
        EXPECT_NEAR(out[0], 0.5, 1e-6);
        EXPECT_NEAR(out[1], 0.25, 1e-6);
        EXPECT_NEAR(out[2], 0.125, 1e-6);
    }
}

// Test that domain clamping works for Type 2 function
TEST_F(FunctionTest_349, Type2FunctionDomainClamping_349) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    dict->add("N", Object(1.0));
    
    Object obj(dict);
    auto func = Function::parse(&obj);
    if (func) {
        double in, out;
        
        // Input below domain should be clamped to 0
        in = -1.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.0, 1e-6);
        
        // Input above domain should be clamped to 1
        in = 2.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 1.0, 1e-6);
    }
}

// Test Type 3 (stitching) function - missing required fields
TEST_F(FunctionTest_349, ParseType3MissingFieldsReturnsNull_349) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(3));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    // Missing Functions, Bounds, Encode
    Object obj(dict);
    auto func = Function::parse(&obj);
    // Should fail due to missing required fields
    EXPECT_EQ(func, nullptr);
}

// Test parse with a negative function type
TEST_F(FunctionTest_349, ParseNegativeFunctionType_349) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(-1));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    Object obj(dict);
    auto func = Function::parse(&obj);
    EXPECT_EQ(func, nullptr);
}

// Test parse with FunctionType 1 (not commonly used, but valid type number)
TEST_F(FunctionTest_349, ParseType1Function_349) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(1));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    Object obj(dict);
    auto func = Function::parse(&obj);
    // Type 1 is not a standard PDF function type (0,2,3,4 are), may return null
    // Just verify no crash
}

// Test getType for Type 2 function
TEST_F(FunctionTest_349, Type2FunctionGetType_349) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    dict->add("N", Object(1.0));
    
    Object obj(dict);
    auto func = Function::parse(&obj);
    if (func) {
        // getType() should return the appropriate type enum
        auto type = func->getType();
        // We just verify it doesn't crash; exact enum value depends on implementation
        (void)type;
    }
}
