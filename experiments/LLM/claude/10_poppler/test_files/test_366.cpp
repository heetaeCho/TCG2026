#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Function.h"

// Since SampledFunction requires complex PDF objects for construction,
// and we must treat the implementation as a black box, we test what we can
// through the public interface. We focus on testing the getSamples() method
// which is the only method fully visible in the provided partial code,
// along with other public accessors where possible.

// Note: SampledFunction construction requires Object* and Dict* from Poppler's
// internal types. We need to include the necessary headers.
#include "Object.h"
#include "Dict.h"
#include "Stream.h"
#include "Array.h"

#include <memory>
#include <cstring>

class SampledFunctionTest_366 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a minimal sampled function stream object
    // A sampled function (type 0) needs:
    // - /FunctionType 0
    // - /Domain array
    // - /Range array
    // - /Size array
    // - /BitsPerSample integer
    // - stream data with samples
    std::unique_ptr<SampledFunction> createSimpleSampledFunction(
        int size, int bitsPerSample,
        double domainMin, double domainMax,
        double rangeMin, double rangeMax,
        const std::vector<unsigned char> &sampleData)
    {
        // We'll build the function object as a stream with the appropriate dictionary
        auto dict = new Dict(nullptr);

        // FunctionType
        dict->add("FunctionType", Object(0));

        // Domain: [domainMin domainMax]
        auto domainArray = new Array(nullptr);
        domainArray->add(Object(domainMin));
        domainArray->add(Object(domainMax));
        dict->add("Domain", Object(domainArray));

        // Range: [rangeMin rangeMax]
        auto rangeArray = new Array(nullptr);
        rangeArray->add(Object(rangeMin));
        rangeArray->add(Object(rangeMax));
        dict->add("Range", Object(rangeArray));

        // Size: [size]
        auto sizeArray = new Array(nullptr);
        sizeArray->add(Object(size));
        dict->add("Size", Object(sizeArray));

        // BitsPerSample
        dict->add("BitsPerSample", Object(bitsPerSample));

        // Create a memory stream with sample data
        char *dataCopy = (char *)gmalloc(sampleData.size());
        memcpy(dataCopy, sampleData.data(), sampleData.size());

        Object dictObj(dict);
        Stream *baseStream = new MemStream(dataCopy, 0, sampleData.size(), std::move(dictObj));

        Object streamObj(baseStream);

        auto func = std::make_unique<SampledFunction>(&streamObj, dict);
        return func;
    }
};

// Test that getSamples returns a non-null pointer for a valid sampled function
TEST_F(SampledFunctionTest_366, GetSamplesReturnsNonNull_366) {
    // Create a simple 1D sampled function with 2 samples, 8 bits per sample
    // Samples: 0, 255
    std::vector<unsigned char> data = {0, 255};
    auto func = createSimpleSampledFunction(2, 8, 0.0, 1.0, 0.0, 1.0, data);

    if (func && func->isOk()) {
        const double *samples = func->getSamples();
        EXPECT_NE(samples, nullptr);
    }
}

// Test that isOk returns true for a properly constructed function
TEST_F(SampledFunctionTest_366, IsOkForValidFunction_366) {
    std::vector<unsigned char> data = {0, 128, 255};
    auto func = createSimpleSampledFunction(3, 8, 0.0, 1.0, 0.0, 1.0, data);

    if (func) {
        EXPECT_TRUE(func->isOk());
    }
}

// Test getType returns Type 0 (Sampled)
TEST_F(SampledFunctionTest_366, GetTypeReturnsSampled_366) {
    std::vector<unsigned char> data = {0, 255};
    auto func = createSimpleSampledFunction(2, 8, 0.0, 1.0, 0.0, 1.0, data);

    if (func && func->isOk()) {
        EXPECT_EQ(func->getType(), Function::Type::Sampled);
    }
}

// Test getSampleSize returns the correct size
TEST_F(SampledFunctionTest_366, GetSampleSizeReturnsCorrectValue_366) {
    std::vector<unsigned char> data = {0, 64, 128, 255};
    auto func = createSimpleSampledFunction(4, 8, 0.0, 1.0, 0.0, 1.0, data);

    if (func && func->isOk()) {
        EXPECT_EQ(func->getSampleSize(0), 4);
    }
}

// Test getSampleNumber returns the correct number of samples
TEST_F(SampledFunctionTest_366, GetSampleNumberReturnsCorrectValue_366) {
    std::vector<unsigned char> data = {0, 64, 128, 255};
    auto func = createSimpleSampledFunction(4, 8, 0.0, 1.0, 0.0, 1.0, data);

    if (func && func->isOk()) {
        EXPECT_EQ(func->getSampleNumber(), 4);
    }
}

// Test getEncodeMin and getEncodeMax defaults
TEST_F(SampledFunctionTest_366, GetEncodeDefaultValues_366) {
    std::vector<unsigned char> data = {0, 255};
    auto func = createSimpleSampledFunction(2, 8, 0.0, 1.0, 0.0, 1.0, data);

    if (func && func->isOk()) {
        // Default encode should be [0, Size-1] = [0, 1]
        EXPECT_DOUBLE_EQ(func->getEncodeMin(0), 0.0);
        EXPECT_DOUBLE_EQ(func->getEncodeMax(0), 1.0);
    }
}

// Test getDecodeMin and getDecodeMax defaults
TEST_F(SampledFunctionTest_366, GetDecodeDefaultValues_366) {
    std::vector<unsigned char> data = {0, 255};
    auto func = createSimpleSampledFunction(2, 8, 0.0, 1.0, 0.0, 1.0, data);

    if (func && func->isOk()) {
        // Default decode should be same as Range
        EXPECT_DOUBLE_EQ(func->getDecodeMin(0), 0.0);
        EXPECT_DOUBLE_EQ(func->getDecodeMax(0), 1.0);
    }
}

// Test transform at domain boundaries
TEST_F(SampledFunctionTest_366, TransformAtDomainMin_366) {
    // 2 samples: value 0 at x=0, value 255 at x=1
    std::vector<unsigned char> data = {0, 255};
    auto func = createSimpleSampledFunction(2, 8, 0.0, 1.0, 0.0, 1.0, data);

    if (func && func->isOk()) {
        double in[1] = {0.0};
        double out[1];
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.0, 0.01);
    }
}

TEST_F(SampledFunctionTest_366, TransformAtDomainMax_366) {
    std::vector<unsigned char> data = {0, 255};
    auto func = createSimpleSampledFunction(2, 8, 0.0, 1.0, 0.0, 1.0, data);

    if (func && func->isOk()) {
        double in[1] = {1.0};
        double out[1];
        func->transform(in, out);
        EXPECT_NEAR(out[0], 1.0, 0.01);
    }
}

// Test transform at midpoint (interpolation)
TEST_F(SampledFunctionTest_366, TransformAtMidpoint_366) {
    std::vector<unsigned char> data = {0, 255};
    auto func = createSimpleSampledFunction(2, 8, 0.0, 1.0, 0.0, 1.0, data);

    if (func && func->isOk()) {
        double in[1] = {0.5};
        double out[1];
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.5, 0.05);
    }
}

// Test transform with input outside domain (clamped)
TEST_F(SampledFunctionTest_366, TransformClampsBelowDomain_366) {
    std::vector<unsigned char> data = {0, 255};
    auto func = createSimpleSampledFunction(2, 8, 0.0, 1.0, 0.0, 1.0, data);

    if (func && func->isOk()) {
        double in[1] = {-1.0};
        double out[1];
        func->transform(in, out);
        // Should be clamped to domain min, so output should be ~0.0
        EXPECT_NEAR(out[0], 0.0, 0.01);
    }
}

TEST_F(SampledFunctionTest_366, TransformClampsAboveDomain_366) {
    std::vector<unsigned char> data = {0, 255};
    auto func = createSimpleSampledFunction(2, 8, 0.0, 1.0, 0.0, 1.0, data);

    if (func && func->isOk()) {
        double in[1] = {2.0};
        double out[1];
        func->transform(in, out);
        // Should be clamped to domain max, so output should be ~1.0
        EXPECT_NEAR(out[0], 1.0, 0.01);
    }
}

// Test copy creates an equivalent function
TEST_F(SampledFunctionTest_366, CopyProducesFunctionalCopy_366) {
    std::vector<unsigned char> data = {0, 128, 255};
    auto func = createSimpleSampledFunction(3, 8, 0.0, 1.0, 0.0, 1.0, data);

    if (func && func->isOk()) {
        auto funcCopy = func->copy();
        ASSERT_NE(funcCopy, nullptr);

        double in[1] = {0.5};
        double out1[1], out2[1];
        func->transform(in, out1);
        funcCopy->transform(in, out2);
        EXPECT_DOUBLE_EQ(out1[0], out2[0]);
    }
}

// Test hasDifferentResultSet with same function
TEST_F(SampledFunctionTest_366, HasDifferentResultSetWithSelf_366) {
    std::vector<unsigned char> data = {0, 255};
    auto func = createSimpleSampledFunction(2, 8, 0.0, 1.0, 0.0, 1.0, data);

    if (func && func->isOk()) {
        EXPECT_FALSE(func->hasDifferentResultSet(func.get()));
    }
}

// Test with constant samples (all same value)
TEST_F(SampledFunctionTest_366, ConstantSamples_366) {
    std::vector<unsigned char> data = {128, 128, 128};
    auto func = createSimpleSampledFunction(3, 8, 0.0, 1.0, 0.0, 1.0, data);

    if (func && func->isOk()) {
        double in1[1] = {0.0};
        double in2[1] = {0.5};
        double in3[1] = {1.0};
        double out1[1], out2[1], out3[1];

        func->transform(in1, out1);
        func->transform(in2, out2);
        func->transform(in3, out3);

        // All outputs should be approximately equal
        EXPECT_NEAR(out1[0], out2[0], 0.01);
        EXPECT_NEAR(out2[0], out3[0], 0.01);
    }
}

// Test single sample
TEST_F(SampledFunctionTest_366, SingleSample_366) {
    std::vector<unsigned char> data = {255};
    auto func = createSimpleSampledFunction(1, 8, 0.0, 1.0, 0.0, 1.0, data);

    if (func && func->isOk()) {
        double in[1] = {0.5};
        double out[1];
        func->transform(in, out);
        EXPECT_NEAR(out[0], 1.0, 0.01);
    }
}

// Test with wider range
TEST_F(SampledFunctionTest_366, WiderRange_366) {
    std::vector<unsigned char> data = {0, 255};
    auto func = createSimpleSampledFunction(2, 8, 0.0, 1.0, 0.0, 10.0, data);

    if (func && func->isOk()) {
        double in[1] = {1.0};
        double out[1];
        func->transform(in, out);
        EXPECT_NEAR(out[0], 10.0, 0.1);
    }
}

// Test getSamples returns consistent pointer
TEST_F(SampledFunctionTest_366, GetSamplesConsistentPointer_366) {
    std::vector<unsigned char> data = {0, 128, 255};
    auto func = createSimpleSampledFunction(3, 8, 0.0, 1.0, 0.0, 1.0, data);

    if (func && func->isOk()) {
        const double *samples1 = func->getSamples();
        const double *samples2 = func->getSamples();
        EXPECT_EQ(samples1, samples2);
    }
}

// Test transform caching behavior (calling transform twice with same input)
TEST_F(SampledFunctionTest_366, TransformCachingConsistency_366) {
    std::vector<unsigned char> data = {0, 128, 255};
    auto func = createSimpleSampledFunction(3, 8, 0.0, 1.0, 0.0, 1.0, data);

    if (func && func->isOk()) {
        double in[1] = {0.3};
        double out1[1], out2[1];
        func->transform(in, out1);
        func->transform(in, out2);
        EXPECT_DOUBLE_EQ(out1[0], out2[0]);
    }
}
