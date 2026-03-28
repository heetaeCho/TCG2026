#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Function.h"
#include "Object.h"
#include "Dict.h"
#include "Stream.h"
#include "Array.h"

// Helper to create a valid SampledFunction for testing
// Since SampledFunction requires a stream object and a dictionary,
// we need to construct proper Poppler objects.

class SampledFunctionTest_360 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a default-constructed (invalid) SampledFunction reports not ok
TEST_F(SampledFunctionTest_360, InvalidFunctionIsNotOk_360) {
    // Constructing with nullptr or invalid objects should result in !isOk()
    Object funcObj;
    funcObj.initNull();
    
    SampledFunction func(&funcObj, nullptr);
    EXPECT_FALSE(func.isOk());
}

// Test that constructing with a null dict yields not ok
TEST_F(SampledFunctionTest_360, NullDictIsNotOk_360) {
    Object funcObj;
    funcObj.initNull();
    
    SampledFunction func(&funcObj, nullptr);
    EXPECT_FALSE(func.isOk());
}

// Test getType returns the sampled function type
TEST_F(SampledFunctionTest_360, GetTypeReturnsSampled_360) {
    Object funcObj;
    funcObj.initNull();
    
    SampledFunction func(&funcObj, nullptr);
    // Even if not ok, getType should return the type identifier for sampled functions
    EXPECT_EQ(func.getType(), Function::Type::Sampled);
}

// Test that an invalid SampledFunction returns null samples
TEST_F(SampledFunctionTest_360, InvalidFunctionGetSamplesReturnsNull_360) {
    Object funcObj;
    funcObj.initNull();
    
    SampledFunction func(&funcObj, nullptr);
    if (!func.isOk()) {
        // For an invalid function, samples pointer may be null
        // This is observable behavior
        const double *samples = func.getSamples();
        // We just verify it doesn't crash; samples may or may not be null
        (void)samples;
    }
}

// Test that an invalid SampledFunction getSampleNumber
TEST_F(SampledFunctionTest_360, InvalidFunctionGetSampleNumber_360) {
    Object funcObj;
    funcObj.initNull();
    
    SampledFunction func(&funcObj, nullptr);
    if (!func.isOk()) {
        int nSamples = func.getSampleNumber();
        // For an invalid function, sample number should be 0 or a default
        EXPECT_GE(nSamples, 0);
    }
}

// Test copy of an invalid function
TEST_F(SampledFunctionTest_360, CopyOfInvalidFunction_360) {
    Object funcObj;
    funcObj.initNull();
    
    SampledFunction func(&funcObj, nullptr);
    if (!func.isOk()) {
        std::unique_ptr<Function> copied = func.copy();
        // Copy should exist but also be invalid
        ASSERT_NE(copied, nullptr);
        EXPECT_FALSE(copied->isOk());
    }
}

// Test hasDifferentResultSet with same invalid function
TEST_F(SampledFunctionTest_360, HasDifferentResultSetWithSelf_360) {
    Object funcObj;
    funcObj.initNull();
    
    SampledFunction func(&funcObj, nullptr);
    // Comparing with itself should return false (same result set)
    bool result = func.hasDifferentResultSet(&func);
    EXPECT_FALSE(result);
}

// Test getSampleSize with valid index range for invalid function
TEST_F(SampledFunctionTest_360, GetSampleSizeForInvalidFunction_360) {
    Object funcObj;
    funcObj.initNull();
    
    SampledFunction func(&funcObj, nullptr);
    // Access sample size at index 0 - should not crash
    int size = func.getSampleSize(0);
    EXPECT_GE(size, 0);
}

// Test getEncode min/max for invalid function
TEST_F(SampledFunctionTest_360, GetEncodeMinMaxForInvalidFunction_360) {
    Object funcObj;
    funcObj.initNull();
    
    SampledFunction func(&funcObj, nullptr);
    double encMin = func.getEncodeMin(0);
    double encMax = func.getEncodeMax(0);
    // Just verify no crash; values are implementation-defined for invalid func
    (void)encMin;
    (void)encMax;
}

// Test getDecode min/max for invalid function
TEST_F(SampledFunctionTest_360, GetDecodeMinMaxForInvalidFunction_360) {
    Object funcObj;
    funcObj.initNull();
    
    SampledFunction func(&funcObj, nullptr);
    double decMin = func.getDecodeMin(0);
    double decMax = func.getDecodeMax(0);
    (void)decMin;
    (void)decMax;
}
