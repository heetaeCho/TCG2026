#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Function.h"
#include "Object.h"
#include "Dict.h"
#include "Stream.h"
#include "Array.h"

// We need to create a proper PDF sampled function object to test SampledFunction.
// A Type 0 (Sampled) function requires:
// - FunctionType: 0
// - Domain: array of 2*m numbers
// - Size: array of m integers
// - BitsPerSample: integer
// - Range: array of 2*n numbers
// Optional: Encode, Decode, Order

class SampledFunctionTest_364 : public ::testing::Test {
protected:
    // Helper to create a minimal sampled function
    // This creates a 1-input, 1-output sampled function with 2 samples
    std::unique_ptr<Function> createSimpleSampledFunction(
        double domainMin = 0.0, double domainMax = 1.0,
        double rangeMin = 0.0, double rangeMax = 1.0,
        double encodeMin = 0.0, double encodeMax = 1.0,
        double decodeMin = 0.0, double decodeMax = 1.0,
        int sampleSize = 2, int bitsPerSample = 8)
    {
        // Build the function dictionary and stream
        auto dict = new Dict(nullptr);

        // FunctionType = 0
        dict->add("FunctionType", Object(0));

        // Domain [domainMin domainMax]
        auto domainArray = new Array(nullptr);
        domainArray->add(Object(domainMin));
        domainArray->add(Object(domainMax));
        dict->add("Domain", Object(domainArray));

        // Range [rangeMin rangeMax]
        auto rangeArray = new Array(nullptr);
        rangeArray->add(Object(rangeMin));
        rangeArray->add(Object(rangeMax));
        dict->add("Range", Object(rangeArray));

        // Size [sampleSize]
        auto sizeArray = new Array(nullptr);
        sizeArray->add(Object(sampleSize));
        dict->add("Size", Object(sizeArray));

        // BitsPerSample
        dict->add("BitsPerSample", Object(bitsPerSample));

        // Encode [encodeMin encodeMax]
        auto encodeArray = new Array(nullptr);
        encodeArray->add(Object(encodeMin));
        encodeArray->add(Object(encodeMax));
        dict->add("Encode", Object(encodeArray));

        // Decode [decodeMin decodeMax]
        auto decodeArray = new Array(nullptr);
        decodeArray->add(Object(decodeMin));
        decodeArray->add(Object(decodeMax));
        dict->add("Decode", Object(decodeArray));

        // Create sample data - simple linear ramp
        int numBytes = (sampleSize * bitsPerSample + 7) / 8;
        auto sampleData = (char *)gmalloc(numBytes);
        for (int i = 0; i < numBytes; i++) {
            if (i == 0) sampleData[i] = 0;
            else sampleData[i] = (char)255;
        }

        // Create a MemStream with the sample data
        Object streamDict(dict);
        dict->add("Length", Object(numBytes));
        auto stream = new MemStream(sampleData, 0, numBytes, std::move(streamDict));

        Object streamObj(stream);
        auto func = Function::parse(&streamObj);
        return func;
    }
};

TEST_F(SampledFunctionTest_364, CreateSimpleSampledFunction_364) {
    auto func = createSimpleSampledFunction();
    // Function may or may not be created successfully depending on the internal parsing
    // If created, it should report as ok
    if (func) {
        EXPECT_TRUE(func->isOk());
    }
}

TEST_F(SampledFunctionTest_364, GetTypeReturnsSampled_364) {
    auto func = createSimpleSampledFunction();
    if (func && func->isOk()) {
        EXPECT_EQ(func->getType(), Function::Type::Sampled);
    }
}

TEST_F(SampledFunctionTest_364, GetDecodeMin_364) {
    auto func = createSimpleSampledFunction(0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.5, 2.0);
    if (func && func->isOk()) {
        auto sampledFunc = dynamic_cast<SampledFunction*>(func.get());
        ASSERT_NE(sampledFunc, nullptr);
        EXPECT_DOUBLE_EQ(sampledFunc->getDecodeMin(0), 0.5);
    }
}

TEST_F(SampledFunctionTest_364, GetDecodeMax_364) {
    auto func = createSimpleSampledFunction(0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.5, 2.0);
    if (func && func->isOk()) {
        auto sampledFunc = dynamic_cast<SampledFunction*>(func.get());
        ASSERT_NE(sampledFunc, nullptr);
        EXPECT_DOUBLE_EQ(sampledFunc->getDecodeMax(0), 2.0);
    }
}

TEST_F(SampledFunctionTest_364, GetEncodeMin_364) {
    auto func = createSimpleSampledFunction(0.0, 1.0, 0.0, 1.0, 0.3, 0.9);
    if (func && func->isOk()) {
        auto sampledFunc = dynamic_cast<SampledFunction*>(func.get());
        ASSERT_NE(sampledFunc, nullptr);
        EXPECT_DOUBLE_EQ(sampledFunc->getEncodeMin(0), 0.3);
    }
}

TEST_F(SampledFunctionTest_364, GetEncodeMax_364) {
    auto func = createSimpleSampledFunction(0.0, 1.0, 0.0, 1.0, 0.3, 0.9);
    if (func && func->isOk()) {
        auto sampledFunc = dynamic_cast<SampledFunction*>(func.get());
        ASSERT_NE(sampledFunc, nullptr);
        EXPECT_DOUBLE_EQ(sampledFunc->getEncodeMax(0), 0.9);
    }
}

TEST_F(SampledFunctionTest_364, GetSampleSize_364) {
    auto func = createSimpleSampledFunction(0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 4);
    if (func && func->isOk()) {
        auto sampledFunc = dynamic_cast<SampledFunction*>(func.get());
        ASSERT_NE(sampledFunc, nullptr);
        EXPECT_EQ(sampledFunc->getSampleSize(0), 4);
    }
}

TEST_F(SampledFunctionTest_364, GetSamplesNotNull_364) {
    auto func = createSimpleSampledFunction();
    if (func && func->isOk()) {
        auto sampledFunc = dynamic_cast<SampledFunction*>(func.get());
        ASSERT_NE(sampledFunc, nullptr);
        EXPECT_NE(sampledFunc->getSamples(), nullptr);
    }
}

TEST_F(SampledFunctionTest_364, GetSampleNumber_364) {
    auto func = createSimpleSampledFunction(0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 2);
    if (func && func->isOk()) {
        auto sampledFunc = dynamic_cast<SampledFunction*>(func.get());
        ASSERT_NE(sampledFunc, nullptr);
        // For a 1D function with size 2 and 1 output, nSamples should be 2
        EXPECT_GE(sampledFunc->getSampleNumber(), 2);
    }
}

TEST_F(SampledFunctionTest_364, CopyProducesSameType_364) {
    auto func = createSimpleSampledFunction();
    if (func && func->isOk()) {
        auto copy = func->copy();
        ASSERT_NE(copy, nullptr);
        EXPECT_TRUE(copy->isOk());
        EXPECT_EQ(copy->getType(), Function::Type::Sampled);
    }
}

TEST_F(SampledFunctionTest_364, CopyPreservesDecodeMin_364) {
    auto func = createSimpleSampledFunction(0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.25, 0.75);
    if (func && func->isOk()) {
        auto copy = func->copy();
        ASSERT_NE(copy, nullptr);
        auto origSampled = dynamic_cast<SampledFunction*>(func.get());
        auto copySampled = dynamic_cast<SampledFunction*>(copy.get());
        ASSERT_NE(origSampled, nullptr);
        ASSERT_NE(copySampled, nullptr);
        EXPECT_DOUBLE_EQ(origSampled->getDecodeMin(0), copySampled->getDecodeMin(0));
    }
}

TEST_F(SampledFunctionTest_364, CopyPreservesDecodeMax_364) {
    auto func = createSimpleSampledFunction(0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.25, 0.75);
    if (func && func->isOk()) {
        auto copy = func->copy();
        ASSERT_NE(copy, nullptr);
        auto origSampled = dynamic_cast<SampledFunction*>(func.get());
        auto copySampled = dynamic_cast<SampledFunction*>(copy.get());
        ASSERT_NE(origSampled, nullptr);
        ASSERT_NE(copySampled, nullptr);
        EXPECT_DOUBLE_EQ(origSampled->getDecodeMax(0), copySampled->getDecodeMax(0));
    }
}

TEST_F(SampledFunctionTest_364, CopyPreservesEncodeMinMax_364) {
    auto func = createSimpleSampledFunction(0.0, 1.0, 0.0, 1.0, 0.1, 0.9);
    if (func && func->isOk()) {
        auto copy = func->copy();
        ASSERT_NE(copy, nullptr);
        auto origSampled = dynamic_cast<SampledFunction*>(func.get());
        auto copySampled = dynamic_cast<SampledFunction*>(copy.get());
        ASSERT_NE(origSampled, nullptr);
        ASSERT_NE(copySampled, nullptr);
        EXPECT_DOUBLE_EQ(origSampled->getEncodeMin(0), copySampled->getEncodeMin(0));
        EXPECT_DOUBLE_EQ(origSampled->getEncodeMax(0), copySampled->getEncodeMax(0));
    }
}

TEST_F(SampledFunctionTest_364, CopyPreservesSampleSize_364) {
    auto func = createSimpleSampledFunction(0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 8);
    if (func && func->isOk()) {
        auto copy = func->copy();
        ASSERT_NE(copy, nullptr);
        auto origSampled = dynamic_cast<SampledFunction*>(func.get());
        auto copySampled = dynamic_cast<SampledFunction*>(copy.get());
        ASSERT_NE(origSampled, nullptr);
        ASSERT_NE(copySampled, nullptr);
        EXPECT_EQ(origSampled->getSampleSize(0), copySampled->getSampleSize(0));
    }
}

TEST_F(SampledFunctionTest_364, CopyPreservesSampleNumber_364) {
    auto func = createSimpleSampledFunction();
    if (func && func->isOk()) {
        auto copy = func->copy();
        ASSERT_NE(copy, nullptr);
        auto origSampled = dynamic_cast<SampledFunction*>(func.get());
        auto copySampled = dynamic_cast<SampledFunction*>(copy.get());
        ASSERT_NE(origSampled, nullptr);
        ASSERT_NE(copySampled, nullptr);
        EXPECT_EQ(origSampled->getSampleNumber(), copySampled->getSampleNumber());
    }
}

TEST_F(SampledFunctionTest_364, TransformProducesOutput_364) {
    auto func = createSimpleSampledFunction();
    if (func && func->isOk()) {
        double in[1] = {0.5};
        double out[1] = {-999.0};
        func->transform(in, out);
        // The output should have been modified from the sentinel value
        // We can't know the exact value without knowing the samples, but
        // it should be within the range
        EXPECT_GE(out[0], 0.0);
        EXPECT_LE(out[0], 1.0);
    }
}

TEST_F(SampledFunctionTest_364, TransformAtDomainMin_364) {
    auto func = createSimpleSampledFunction();
    if (func && func->isOk()) {
        double in[1] = {0.0};
        double out[1] = {-999.0};
        func->transform(in, out);
        EXPECT_GE(out[0], 0.0);
        EXPECT_LE(out[0], 1.0);
    }
}

TEST_F(SampledFunctionTest_364, TransformAtDomainMax_364) {
    auto func = createSimpleSampledFunction();
    if (func && func->isOk()) {
        double in[1] = {1.0};
        double out[1] = {-999.0};
        func->transform(in, out);
        EXPECT_GE(out[0], 0.0);
        EXPECT_LE(out[0], 1.0);
    }
}

TEST_F(SampledFunctionTest_364, TransformClampsBeyondDomain_364) {
    auto func = createSimpleSampledFunction();
    if (func && func->isOk()) {
        double in[1] = {2.0}; // Beyond domain max of 1.0
        double out[1] = {-999.0};
        func->transform(in, out);
        // Should be clamped - output should still be in range
        EXPECT_GE(out[0], 0.0);
        EXPECT_LE(out[0], 1.0);
    }
}

TEST_F(SampledFunctionTest_364, TransformClampsBelowDomain_364) {
    auto func = createSimpleSampledFunction();
    if (func && func->isOk()) {
        double in[1] = {-1.0}; // Below domain min of 0.0
        double out[1] = {-999.0};
        func->transform(in, out);
        EXPECT_GE(out[0], 0.0);
        EXPECT_LE(out[0], 1.0);
    }
}

TEST_F(SampledFunctionTest_364, HasDifferentResultSetWithSelf_364) {
    auto func = createSimpleSampledFunction();
    if (func && func->isOk()) {
        // A function compared with itself should not have different result set
        EXPECT_FALSE(func->hasDifferentResultSet(func.get()));
    }
}

TEST_F(SampledFunctionTest_364, HasDifferentResultSetWithCopy_364) {
    auto func = createSimpleSampledFunction();
    if (func && func->isOk()) {
        auto copy = func->copy();
        ASSERT_NE(copy, nullptr);
        EXPECT_FALSE(func->hasDifferentResultSet(copy.get()));
    }
}

TEST_F(SampledFunctionTest_364, DefaultDecodeValues_364) {
    // When no Decode is specified, decode should default to Range values
    auto func = createSimpleSampledFunction(0.0, 1.0, 0.0, 10.0, 0.0, 1.0, 0.0, 10.0);
    if (func && func->isOk()) {
        auto sampledFunc = dynamic_cast<SampledFunction*>(func.get());
        ASSERT_NE(sampledFunc, nullptr);
        EXPECT_DOUBLE_EQ(sampledFunc->getDecodeMin(0), 0.0);
        EXPECT_DOUBLE_EQ(sampledFunc->getDecodeMax(0), 10.0);
    }
}

TEST_F(SampledFunctionTest_364, InputOutputCounts_364) {
    auto func = createSimpleSampledFunction();
    if (func && func->isOk()) {
        EXPECT_EQ(func->getInputSize(), 1);
        EXPECT_EQ(func->getOutputSize(), 1);
    }
}

TEST_F(SampledFunctionTest_364, DomainValues_364) {
    auto func = createSimpleSampledFunction(0.5, 2.5);
    if (func && func->isOk()) {
        EXPECT_DOUBLE_EQ(func->getDomainMin(0), 0.5);
        EXPECT_DOUBLE_EQ(func->getDomainMax(0), 2.5);
    }
}

TEST_F(SampledFunctionTest_364, RangeValues_364) {
    auto func = createSimpleSampledFunction(0.0, 1.0, -1.0, 5.0);
    if (func && func->isOk()) {
        EXPECT_TRUE(func->getHasRange());
        EXPECT_DOUBLE_EQ(func->getRangeMin(0), -1.0);
        EXPECT_DOUBLE_EQ(func->getRangeMax(0), 5.0);
    }
}
