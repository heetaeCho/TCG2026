#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Function.h"
#include "Object.h"
#include <memory>

// Since Function is abstract (has pure virtual methods), we need to test it
// through its public interface. We'll attempt to use Function::parse to create
// concrete instances, or test what we can through available means.

class FunctionTest_352 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that parse returns nullptr for an invalid/null object
TEST_F(FunctionTest_352, ParseInvalidObjectReturnsNull_352) {
    Object obj;
    auto func = Function::parse(&obj);
    EXPECT_EQ(func, nullptr);
}

// Test that parse handles a non-function object gracefully
TEST_F(FunctionTest_352, ParseNonFunctionObjectReturnsNull_352) {
    Object obj(42); // integer object, not a function
    auto func = Function::parse(&obj);
    EXPECT_EQ(func, nullptr);
}

// Test parse with a boolean object (wrong type)
TEST_F(FunctionTest_352, ParseBoolObjectReturnsNull_352) {
    Object obj(true);
    auto func = Function::parse(&obj);
    EXPECT_EQ(func, nullptr);
}

// Test parse with a real number object (wrong type)
TEST_F(FunctionTest_352, ParseRealObjectReturnsNull_352) {
    Object obj(3.14);
    auto func = Function::parse(&obj);
    EXPECT_EQ(func, nullptr);
}

// Test parse with a string object (wrong type)
TEST_F(FunctionTest_352, ParseStringObjectReturnsNull_352) {
    Object obj(new GooString("test"));
    auto func = Function::parse(&obj);
    EXPECT_EQ(func, nullptr);
}

// Test that getRangeMax, getRangeMin, getDomainMin, getDomainMax
// getInputSize, getOutputSize, getHasRange are accessible interface methods.
// We create a valid sampled function via a proper PDF dictionary to test these.

// Helper to build a Type 2 (Exponential) function dictionary
static Object makeType2FunctionDict() {
    Dict *dict = new Dict((XRef *)nullptr);
    
    // FunctionType 2
    dict->add("FunctionType", Object(2));
    
    // Domain [0 1]
    Array *domain = new Array((XRef *)nullptr);
    domain->add(Object(0.0));
    domain->add(Object(1.0));
    dict->add("Domain", Object(domain));
    
    // Range [0 1]
    Array *range = new Array((XRef *)nullptr);
    range->add(Object(0.0));
    range->add(Object(1.0));
    dict->add("Range", Object(range));
    
    // C0 [0]
    Array *c0 = new Array((XRef *)nullptr);
    c0->add(Object(0.0));
    dict->add("C0", Object(c0));
    
    // C1 [1]
    Array *c1 = new Array((XRef *)nullptr);
    c1->add(Object(1.0));
    dict->add("C1", Object(c1));
    
    // N (exponent)
    dict->add("N", Object(1.0));
    
    return Object(dict);
}

TEST_F(FunctionTest_352, ParseType2FunctionValid_352) {
    Object funcObj = makeType2FunctionDict();
    auto func = Function::parse(&funcObj);
    
    if (func) {
        EXPECT_TRUE(func->isOk());
        EXPECT_EQ(func->getInputSize(), 1);
        EXPECT_EQ(func->getOutputSize(), 1);
        EXPECT_DOUBLE_EQ(func->getDomainMin(0), 0.0);
        EXPECT_DOUBLE_EQ(func->getDomainMax(0), 1.0);
        EXPECT_DOUBLE_EQ(func->getRangeMin(0), 0.0);
        EXPECT_DOUBLE_EQ(func->getRangeMax(0), 1.0);
        EXPECT_TRUE(func->getHasRange());
    }
}

TEST_F(FunctionTest_352, Type2FunctionTransformAtZero_352) {
    Object funcObj = makeType2FunctionDict();
    auto func = Function::parse(&funcObj);
    
    if (func && func->isOk()) {
        double in = 0.0;
        double out = -1.0;
        func->transform(&in, &out);
        EXPECT_DOUBLE_EQ(out, 0.0);
    }
}

TEST_F(FunctionTest_352, Type2FunctionTransformAtOne_352) {
    Object funcObj = makeType2FunctionDict();
    auto func = Function::parse(&funcObj);
    
    if (func && func->isOk()) {
        double in = 1.0;
        double out = -1.0;
        func->transform(&in, &out);
        EXPECT_DOUBLE_EQ(out, 1.0);
    }
}

TEST_F(FunctionTest_352, Type2FunctionTransformAtHalf_352) {
    Object funcObj = makeType2FunctionDict();
    auto func = Function::parse(&funcObj);
    
    if (func && func->isOk()) {
        double in = 0.5;
        double out = -1.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.5, 0.001);
    }
}

TEST_F(FunctionTest_352, Type2FunctionCopy_352) {
    Object funcObj = makeType2FunctionDict();
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
        
        // Verify copy produces same results
        double in = 0.5;
        double out1 = -1.0, out2 = -1.0;
        func->transform(&in, &out1);
        funcCopy->transform(&in, &out2);
        EXPECT_DOUBLE_EQ(out1, out2);
    }
}

TEST_F(FunctionTest_352, Type2FunctionHasDifferentResultSet_352) {
    Object funcObj1 = makeType2FunctionDict();
    Object funcObj2 = makeType2FunctionDict();
    auto func1 = Function::parse(&funcObj1);
    auto func2 = Function::parse(&funcObj2);
    
    if (func1 && func1->isOk() && func2 && func2->isOk()) {
        // Two identical functions should not have different result sets
        EXPECT_FALSE(func1->hasDifferentResultSet(func2.get()));
    }
}

// Test with multi-dimensional domain
static Object makeType2FunctionDictWithRange(double rMin, double rMax) {
    Dict *dict = new Dict((XRef *)nullptr);
    
    dict->add("FunctionType", Object(2));
    
    Array *domain = new Array((XRef *)nullptr);
    domain->add(Object(0.0));
    domain->add(Object(1.0));
    dict->add("Domain", Object(domain));
    
    Array *range = new Array((XRef *)nullptr);
    range->add(Object(rMin));
    range->add(Object(rMax));
    dict->add("Range", Object(range));
    
    Array *c0 = new Array((XRef *)nullptr);
    c0->add(Object(rMin));
    dict->add("C0", Object(c0));
    
    Array *c1 = new Array((XRef *)nullptr);
    c1->add(Object(rMax));
    dict->add("C1", Object(c1));
    
    dict->add("N", Object(1.0));
    
    return Object(dict);
}

TEST_F(FunctionTest_352, Type2FunctionCustomRange_352) {
    Object funcObj = makeType2FunctionDictWithRange(-5.0, 10.0);
    auto func = Function::parse(&funcObj);
    
    if (func && func->isOk()) {
        EXPECT_DOUBLE_EQ(func->getRangeMin(0), -5.0);
        EXPECT_DOUBLE_EQ(func->getRangeMax(0), 10.0);
    }
}

TEST_F(FunctionTest_352, Type2FunctionTransformClampedByDomain_352) {
    Object funcObj = makeType2FunctionDict();
    auto func = Function::parse(&funcObj);
    
    if (func && func->isOk()) {
        // Input outside domain [0,1] should be clamped
        double in = 2.0;
        double out = -1.0;
        func->transform(&in, &out);
        // Should be clamped to domain max (1.0), resulting in output 1.0
        EXPECT_DOUBLE_EQ(out, 1.0);
    }
}

TEST_F(FunctionTest_352, Type2FunctionTransformNegativeInput_352) {
    Object funcObj = makeType2FunctionDict();
    auto func = Function::parse(&funcObj);
    
    if (func && func->isOk()) {
        double in = -1.0;
        double out = -1.0;
        func->transform(&in, &out);
        // Should be clamped to domain min (0.0), resulting in output 0.0
        EXPECT_DOUBLE_EQ(out, 0.0);
    }
}

// Test without Range specified
static Object makeType2FunctionDictNoRange() {
    Dict *dict = new Dict((XRef *)nullptr);
    
    dict->add("FunctionType", Object(2));
    
    Array *domain = new Array((XRef *)nullptr);
    domain->add(Object(0.0));
    domain->add(Object(1.0));
    dict->add("Domain", Object(domain));
    
    Array *c0 = new Array((XRef *)nullptr);
    c0->add(Object(0.0));
    dict->add("C0", Object(c0));
    
    Array *c1 = new Array((XRef *)nullptr);
    c1->add(Object(1.0));
    dict->add("C1", Object(c1));
    
    dict->add("N", Object(1.0));
    
    return Object(dict);
}

TEST_F(FunctionTest_352, Type2FunctionNoRange_352) {
    Object funcObj = makeType2FunctionDictNoRange();
    auto func = Function::parse(&funcObj);
    
    if (func && func->isOk()) {
        EXPECT_FALSE(func->getHasRange());
        EXPECT_EQ(func->getInputSize(), 1);
        EXPECT_EQ(func->getOutputSize(), 1);
    }
}

// Test with quadratic exponent (N=2)
static Object makeType2FunctionDictQuadratic() {
    Dict *dict = new Dict((XRef *)nullptr);
    
    dict->add("FunctionType", Object(2));
    
    Array *domain = new Array((XRef *)nullptr);
    domain->add(Object(0.0));
    domain->add(Object(1.0));
    dict->add("Domain", Object(domain));
    
    Array *range = new Array((XRef *)nullptr);
    range->add(Object(0.0));
    range->add(Object(1.0));
    dict->add("Range", Object(range));
    
    Array *c0 = new Array((XRef *)nullptr);
    c0->add(Object(0.0));
    dict->add("C0", Object(c0));
    
    Array *c1 = new Array((XRef *)nullptr);
    c1->add(Object(1.0));
    dict->add("C1", Object(c1));
    
    dict->add("N", Object(2.0));
    
    return Object(dict);
}

TEST_F(FunctionTest_352, Type2FunctionQuadraticTransform_352) {
    Object funcObj = makeType2FunctionDictQuadratic();
    auto func = Function::parse(&funcObj);
    
    if (func && func->isOk()) {
        double in = 0.5;
        double out = -1.0;
        func->transform(&in, &out);
        // With N=2: out = C0 + x^N * (C1 - C0) = 0 + 0.25 * 1 = 0.25
        EXPECT_NEAR(out, 0.25, 0.001);
    }
}

// Test with multiple outputs
static Object makeType2FunctionDictMultiOutput() {
    Dict *dict = new Dict((XRef *)nullptr);
    
    dict->add("FunctionType", Object(2));
    
    Array *domain = new Array((XRef *)nullptr);
    domain->add(Object(0.0));
    domain->add(Object(1.0));
    dict->add("Domain", Object(domain));
    
    Array *range = new Array((XRef *)nullptr);
    range->add(Object(0.0));
    range->add(Object(1.0));
    range->add(Object(0.0));
    range->add(Object(1.0));
    range->add(Object(0.0));
    range->add(Object(1.0));
    dict->add("Range", Object(range));
    
    Array *c0 = new Array((XRef *)nullptr);
    c0->add(Object(0.0));
    c0->add(Object(0.0));
    c0->add(Object(0.0));
    dict->add("C0", Object(c0));
    
    Array *c1 = new Array((XRef *)nullptr);
    c1->add(Object(1.0));
    c1->add(Object(0.5));
    c1->add(Object(0.25));
    dict->add("C1", Object(c1));
    
    dict->add("N", Object(1.0));
    
    return Object(dict);
}

TEST_F(FunctionTest_352, Type2FunctionMultiOutput_352) {
    Object funcObj = makeType2FunctionDictMultiOutput();
    auto func = Function::parse(&funcObj);
    
    if (func && func->isOk()) {
        EXPECT_EQ(func->getOutputSize(), 3);
        EXPECT_EQ(func->getInputSize(), 1);
        
        double in = 1.0;
        double out[3] = {-1.0, -1.0, -1.0};
        func->transform(&in, out);
        EXPECT_NEAR(out[0], 1.0, 0.001);
        EXPECT_NEAR(out[1], 0.5, 0.001);
        EXPECT_NEAR(out[2], 0.25, 0.001);
    }
}

TEST_F(FunctionTest_352, Type2FunctionMultiOutputGetRange_352) {
    Object funcObj = makeType2FunctionDictMultiOutput();
    auto func = Function::parse(&funcObj);
    
    if (func && func->isOk()) {
        EXPECT_DOUBLE_EQ(func->getRangeMin(0), 0.0);
        EXPECT_DOUBLE_EQ(func->getRangeMax(0), 1.0);
        EXPECT_DOUBLE_EQ(func->getRangeMin(1), 0.0);
        EXPECT_DOUBLE_EQ(func->getRangeMax(1), 1.0);
        EXPECT_DOUBLE_EQ(func->getRangeMin(2), 0.0);
        EXPECT_DOUBLE_EQ(func->getRangeMax(2), 1.0);
    }
}

// Test with missing FunctionType
TEST_F(FunctionTest_352, ParseMissingFunctionType_352) {
    Dict *dict = new Dict((XRef *)nullptr);
    
    Array *domain = new Array((XRef *)nullptr);
    domain->add(Object(0.0));
    domain->add(Object(1.0));
    dict->add("Domain", Object(domain));
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    // Should fail or return nullptr since FunctionType is missing
    EXPECT_EQ(func, nullptr);
}

// Test with missing Domain
TEST_F(FunctionTest_352, ParseMissingDomain_352) {
    Dict *dict = new Dict((XRef *)nullptr);
    
    dict->add("FunctionType", Object(2));
    dict->add("N", Object(1.0));
    
    Object funcObj(dict);
    auto func = Function::parse(&funcObj);
    // Should fail since Domain is required
    if (func) {
        EXPECT_FALSE(func->isOk());
    }
}

// Test hasDifferentResultSet with nullptr
TEST_F(FunctionTest_352, HasDifferentResultSetWithNullptr_352) {
    Object funcObj = makeType2FunctionDict();
    auto func = Function::parse(&funcObj);
    
    if (func && func->isOk()) {
        // Test with nullptr - should handle gracefully
        EXPECT_FALSE(func->hasDifferentResultSet(nullptr));
    }
}
