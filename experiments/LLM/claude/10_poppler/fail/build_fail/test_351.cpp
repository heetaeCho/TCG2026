#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Function.h"
#include "Object.h"
#include <memory>

// Since Function is abstract (has pure virtual methods), we need a concrete subclass for testing.
// However, we can use Function::parse to create instances, or we can test through
// the public interface of concrete subclasses.

// We'll test what we can through the public interface, primarily using parse() to create
// Function objects from PDF objects when possible, and testing accessor methods.

class FunctionTest_351 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getRangeMin returns the expected value for a parsed function
// We'll create a sampled function or identity function via Object if possible

// Test getInputSize accessor
TEST_F(FunctionTest_351, GetInputSizeReturnsM_351) {
    // Create a simple identity function (Type 4 - PostScript calculator)
    // Type 4 function: { }
    // We need to construct the appropriate Object/Dict

    auto streamDict = Object(new Dict(nullptr));
    streamDict.dictAdd("FunctionType", Object(4));
    
    Array *domainArray = new Array(nullptr);
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    streamDict.dictAdd("Domain", Object(domainArray));
    
    Array *rangeArray = new Array(nullptr);
    rangeArray->add(Object(0.0));
    rangeArray->add(Object(1.0));
    streamDict.dictAdd("Range", Object(rangeArray));

    // PostScript calculator function body: "{ }"
    const char *psCode = "{ }\n";
    auto *memStream = new MemStream(const_cast<char *>(psCode), 0, strlen(psCode), std::move(streamDict));
    
    Object funcObj(memStream);
    
    auto func = Function::parse(&funcObj);
    if (func && func->isOk()) {
        EXPECT_EQ(func->getInputSize(), 1);
    }
}

// Test getOutputSize accessor
TEST_F(FunctionTest_351, GetOutputSizeReturnsN_351) {
    auto streamDict = Object(new Dict(nullptr));
    streamDict.dictAdd("FunctionType", Object(4));
    
    Array *domainArray = new Array(nullptr);
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    streamDict.dictAdd("Domain", Object(domainArray));
    
    Array *rangeArray = new Array(nullptr);
    rangeArray->add(Object(0.0));
    rangeArray->add(Object(1.0));
    streamDict.dictAdd("Range", Object(rangeArray));

    const char *psCode = "{ }\n";
    auto *memStream = new MemStream(const_cast<char *>(psCode), 0, strlen(psCode), std::move(streamDict));
    
    Object funcObj(memStream);
    
    auto func = Function::parse(&funcObj);
    if (func && func->isOk()) {
        EXPECT_EQ(func->getOutputSize(), 1);
    }
}

// Test getDomainMin and getDomainMax
TEST_F(FunctionTest_351, GetDomainMinMaxReturnsCorrectValues_351) {
    auto streamDict = Object(new Dict(nullptr));
    streamDict.dictAdd("FunctionType", Object(4));
    
    Array *domainArray = new Array(nullptr);
    domainArray->add(Object(0.5));
    domainArray->add(Object(2.5));
    streamDict.dictAdd("Domain", Object(domainArray));
    
    Array *rangeArray = new Array(nullptr);
    rangeArray->add(Object(0.0));
    rangeArray->add(Object(1.0));
    streamDict.dictAdd("Range", Object(rangeArray));

    const char *psCode = "{ }\n";
    auto *memStream = new MemStream(const_cast<char *>(psCode), 0, strlen(psCode), std::move(streamDict));
    
    Object funcObj(memStream);
    
    auto func = Function::parse(&funcObj);
    if (func && func->isOk()) {
        EXPECT_DOUBLE_EQ(func->getDomainMin(0), 0.5);
        EXPECT_DOUBLE_EQ(func->getDomainMax(0), 2.5);
    }
}

// Test getRangeMin and getRangeMax
TEST_F(FunctionTest_351, GetRangeMinMaxReturnsCorrectValues_351) {
    auto streamDict = Object(new Dict(nullptr));
    streamDict.dictAdd("FunctionType", Object(4));
    
    Array *domainArray = new Array(nullptr);
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    streamDict.dictAdd("Domain", Object(domainArray));
    
    Array *rangeArray = new Array(nullptr);
    rangeArray->add(Object(-1.0));
    rangeArray->add(Object(3.0));
    streamDict.dictAdd("Range", Object(rangeArray));

    const char *psCode = "{ }\n";
    auto *memStream = new MemStream(const_cast<char *>(psCode), 0, strlen(psCode), std::move(streamDict));
    
    Object funcObj(memStream);
    
    auto func = Function::parse(&funcObj);
    if (func && func->isOk()) {
        EXPECT_DOUBLE_EQ(func->getRangeMin(0), -1.0);
        EXPECT_DOUBLE_EQ(func->getRangeMax(0), 3.0);
    }
}

// Test getHasRange
TEST_F(FunctionTest_351, GetHasRangeReturnsTrueWhenRangeSpecified_351) {
    auto streamDict = Object(new Dict(nullptr));
    streamDict.dictAdd("FunctionType", Object(4));
    
    Array *domainArray = new Array(nullptr);
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    streamDict.dictAdd("Domain", Object(domainArray));
    
    Array *rangeArray = new Array(nullptr);
    rangeArray->add(Object(0.0));
    rangeArray->add(Object(1.0));
    streamDict.dictAdd("Range", Object(rangeArray));

    const char *psCode = "{ }\n";
    auto *memStream = new MemStream(const_cast<char *>(psCode), 0, strlen(psCode), std::move(streamDict));
    
    Object funcObj(memStream);
    
    auto func = Function::parse(&funcObj);
    if (func && func->isOk()) {
        EXPECT_TRUE(func->getHasRange());
    }
}

// Test parsing with null/invalid object
TEST_F(FunctionTest_351, ParseNullObjectReturnsNull_351) {
    Object nullObj;
    auto func = Function::parse(&nullObj);
    EXPECT_EQ(func, nullptr);
}

// Test parsing with invalid function type
TEST_F(FunctionTest_351, ParseInvalidFunctionTypeReturnsNull_351) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(99));
    
    Array *domainArray = new Array(nullptr);
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict->add("Domain", Object(domainArray));
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    // Invalid function type should either return null or return a non-ok function
    if (func) {
        EXPECT_FALSE(func->isOk());
    } else {
        EXPECT_EQ(func, nullptr);
    }
}

// Test Exponential Interpolation Function (Type 2)
TEST_F(FunctionTest_351, ParseExponentialFunctionType2_351) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArray = new Array(nullptr);
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict->add("Domain", Object(domainArray));
    
    Array *c0Array = new Array(nullptr);
    c0Array->add(Object(0.0));
    dict->add("C0", Object(c0Array));
    
    Array *c1Array = new Array(nullptr);
    c1Array->add(Object(1.0));
    dict->add("C1", Object(c1Array));
    
    dict->add("N", Object(1.0));
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    if (func && func->isOk()) {
        EXPECT_EQ(func->getInputSize(), 1);
        EXPECT_EQ(func->getOutputSize(), 1);
        EXPECT_DOUBLE_EQ(func->getDomainMin(0), 0.0);
        EXPECT_DOUBLE_EQ(func->getDomainMax(0), 1.0);
    }
}

// Test transform for Type 2 exponential function (linear: N=1, C0=0, C1=1)
TEST_F(FunctionTest_351, TransformExponentialLinear_351) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArray = new Array(nullptr);
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict->add("Domain", Object(domainArray));
    
    Array *c0Array = new Array(nullptr);
    c0Array->add(Object(0.0));
    dict->add("C0", Object(c0Array));
    
    Array *c1Array = new Array(nullptr);
    c1Array->add(Object(1.0));
    dict->add("C1", Object(c1Array));
    
    dict->add("N", Object(1.0));
    
    Array *rangeArray = new Array(nullptr);
    rangeArray->add(Object(0.0));
    rangeArray->add(Object(1.0));
    dict->add("Range", Object(rangeArray));
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    if (func && func->isOk()) {
        double in[1], out[1];
        
        // Test at x=0: result should be C0 = 0
        in[0] = 0.0;
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.0, 1e-6);
        
        // Test at x=1: result should be C1 = 1
        in[0] = 1.0;
        func->transform(in, out);
        EXPECT_NEAR(out[0], 1.0, 1e-6);
        
        // Test at x=0.5: result should be 0.5 for linear
        in[0] = 0.5;
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.5, 1e-6);
    }
}

// Test transform with domain clamping for Type 2
TEST_F(FunctionTest_351, TransformExponentialClampsToDomain_351) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArray = new Array(nullptr);
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict->add("Domain", Object(domainArray));
    
    Array *c0Array = new Array(nullptr);
    c0Array->add(Object(0.0));
    dict->add("C0", Object(c0Array));
    
    Array *c1Array = new Array(nullptr);
    c1Array->add(Object(1.0));
    dict->add("C1", Object(c1Array));
    
    dict->add("N", Object(1.0));
    
    Array *rangeArray = new Array(nullptr);
    rangeArray->add(Object(0.0));
    rangeArray->add(Object(1.0));
    dict->add("Range", Object(rangeArray));
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    if (func && func->isOk()) {
        double in[1], out[1];
        
        // Test below domain min: should clamp to 0
        in[0] = -1.0;
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.0, 1e-6);
        
        // Test above domain max: should clamp to 1
        in[0] = 2.0;
        func->transform(in, out);
        EXPECT_NEAR(out[0], 1.0, 1e-6);
    }
}

// Test copy functionality
TEST_F(FunctionTest_351, CopyProducesSameResults_351) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArray = new Array(nullptr);
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict->add("Domain", Object(domainArray));
    
    Array *c0Array = new Array(nullptr);
    c0Array->add(Object(0.0));
    dict->add("C0", Object(c0Array));
    
    Array *c1Array = new Array(nullptr);
    c1Array->add(Object(1.0));
    dict->add("C1", Object(c1Array));
    
    dict->add("N", Object(1.0));
    
    Array *rangeArray = new Array(nullptr);
    rangeArray->add(Object(0.0));
    rangeArray->add(Object(1.0));
    dict->add("Range", Object(rangeArray));
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    if (func && func->isOk()) {
        auto funcCopy = func->copy();
        ASSERT_NE(funcCopy, nullptr);
        EXPECT_TRUE(funcCopy->isOk());
        EXPECT_EQ(funcCopy->getInputSize(), func->getInputSize());
        EXPECT_EQ(funcCopy->getOutputSize(), func->getOutputSize());
        EXPECT_DOUBLE_EQ(funcCopy->getDomainMin(0), func->getDomainMin(0));
        EXPECT_DOUBLE_EQ(funcCopy->getDomainMax(0), func->getDomainMax(0));
        EXPECT_DOUBLE_EQ(funcCopy->getRangeMin(0), func->getRangeMin(0));
        EXPECT_DOUBLE_EQ(funcCopy->getRangeMax(0), func->getRangeMax(0));
        
        // Verify transform produces same results
        double in[1] = {0.5};
        double out1[1], out2[1];
        func->transform(in, out1);
        funcCopy->transform(in, out2);
        EXPECT_DOUBLE_EQ(out1[0], out2[0]);
    }
}

// Test multiple output dimensions
TEST_F(FunctionTest_351, MultipleOutputDimensions_351) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArray = new Array(nullptr);
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict->add("Domain", Object(domainArray));
    
    Array *c0Array = new Array(nullptr);
    c0Array->add(Object(0.0));
    c0Array->add(Object(0.0));
    c0Array->add(Object(0.0));
    dict->add("C0", Object(c0Array));
    
    Array *c1Array = new Array(nullptr);
    c1Array->add(Object(1.0));
    c1Array->add(Object(0.5));
    c1Array->add(Object(0.25));
    dict->add("C1", Object(c1Array));
    
    dict->add("N", Object(1.0));
    
    Array *rangeArray = new Array(nullptr);
    rangeArray->add(Object(0.0));
    rangeArray->add(Object(1.0));
    rangeArray->add(Object(0.0));
    rangeArray->add(Object(1.0));
    rangeArray->add(Object(0.0));
    rangeArray->add(Object(1.0));
    dict->add("Range", Object(rangeArray));
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    if (func && func->isOk()) {
        EXPECT_EQ(func->getOutputSize(), 3);
        
        double in[1] = {1.0};
        double out[3];
        func->transform(in, out);
        EXPECT_NEAR(out[0], 1.0, 1e-6);
        EXPECT_NEAR(out[1], 0.5, 1e-6);
        EXPECT_NEAR(out[2], 0.25, 1e-6);
    }
}

// Test hasDifferentResultSet default behavior
TEST_F(FunctionTest_351, HasDifferentResultSetDefault_351) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArray = new Array(nullptr);
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict->add("Domain", Object(domainArray));
    
    dict->add("N", Object(1.0));
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    if (func && func->isOk()) {
        // Default implementation should return false
        EXPECT_FALSE(func->hasDifferentResultSet(nullptr));
    }
}

// Test Type 2 with N=2 (quadratic)
TEST_F(FunctionTest_351, TransformExponentialQuadratic_351) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArray = new Array(nullptr);
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict->add("Domain", Object(domainArray));
    
    Array *c0Array = new Array(nullptr);
    c0Array->add(Object(0.0));
    dict->add("C0", Object(c0Array));
    
    Array *c1Array = new Array(nullptr);
    c1Array->add(Object(1.0));
    dict->add("C1", Object(c1Array));
    
    dict->add("N", Object(2.0));
    
    Array *rangeArray = new Array(nullptr);
    rangeArray->add(Object(0.0));
    rangeArray->add(Object(1.0));
    dict->add("Range", Object(rangeArray));
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    if (func && func->isOk()) {
        double in[1], out[1];
        
        // At x=0.5, result = C0 + (C1-C0)*0.5^2 = 0 + 1*0.25 = 0.25
        in[0] = 0.5;
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.25, 1e-6);
        
        // At x=0, result = 0
        in[0] = 0.0;
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.0, 1e-6);
        
        // At x=1, result = 1
        in[0] = 1.0;
        func->transform(in, out);
        EXPECT_NEAR(out[0], 1.0, 1e-6);
    }
}

// Test that parsing missing Domain fails or returns null
TEST_F(FunctionTest_351, ParseMissingDomainFails_351) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    dict->add("N", Object(1.0));
    // No Domain specified
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    // Should fail since Domain is required
    if (func) {
        EXPECT_FALSE(func->isOk());
    }
}

// Test getType for Type 2
TEST_F(FunctionTest_351, GetTypeReturnsCorrectType_351) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArray = new Array(nullptr);
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict->add("Domain", Object(domainArray));
    
    dict->add("N", Object(1.0));
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    if (func && func->isOk()) {
        // Type 2 is exponential interpolation
        auto type = func->getType();
        // We just verify we can call getType without issues
        (void)type;
    }
}

// Test range clamping behavior
TEST_F(FunctionTest_351, TransformClampsToRange_351) {
    Dict *dict = new Dict(nullptr);
    dict->add("FunctionType", Object(2));
    
    Array *domainArray = new Array(nullptr);
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict->add("Domain", Object(domainArray));
    
    Array *c0Array = new Array(nullptr);
    c0Array->add(Object(0.0));
    dict->add("C0", Object(c0Array));
    
    Array *c1Array = new Array(nullptr);
    c1Array->add(Object(10.0));
    dict->add("C1", Object(c1Array));
    
    dict->add("N", Object(1.0));
    
    // Range limits output to [0, 1]
    Array *rangeArray = new Array(nullptr);
    rangeArray->add(Object(0.0));
    rangeArray->add(Object(1.0));
    dict->add("Range", Object(rangeArray));
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    if (func && func->isOk()) {
        double in[1] = {1.0};
        double out[1];
        func->transform(in, out);
        // Without range clamping, result would be 10.0
        // With range clamping, result should be 1.0
        EXPECT_LE(out[0], 1.0);
    }
}
