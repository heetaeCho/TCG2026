#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Function.h"

// Since we cannot directly construct SampledFunction without valid Object/Dict,
// and we need to treat the implementation as a black box, we test through
// the public interface using whatever construction mechanisms are available.

// Helper: We attempt to test getEncodeMax and other accessors.
// Since constructing a SampledFunction requires Object* and Dict*,
// we need to create valid PDF objects. We'll use Poppler's infrastructure.

#include "Object.h"
#include "Dict.h"
#include "Stream.h"
#include "Array.h"

// We need XRef for Dict construction in some Poppler versions
#include <cstring>

class SampledFunctionTest_363 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a minimal sampled function (Type 0)
    // Domain: [0, 1] for 1 input
    // Range: [0, 1] for 1 output
    // Size: [2]
    // BitsPerSample: 8
    // Encode: [0, 1]
    // Decode: [0, 1]
    std::unique_ptr<SampledFunction> createSimpleSampledFunction(
        int nInputs, int nOutputs,
        const std::vector<int>& sizes,
        int bitsPerSample,
        const std::vector<std::pair<double,double>>& domain,
        const std::vector<std::pair<double,double>>& range,
        const std::vector<std::pair<double,double>>& encode,
        const std::vector<std::pair<double,double>>& decode,
        const std::vector<unsigned char>& sampleData)
    {
        // Build the function dictionary as a stream
        Dict *dict = new Dict(nullptr);

        // FunctionType
        dict->add("FunctionType", Object(0));

        // Domain array
        Array *domainArr = new Array(nullptr);
        for (int i = 0; i < nInputs; i++) {
            domainArr->add(Object(domain[i].first));
            domainArr->add(Object(domain[i].second));
        }
        dict->add("Domain", Object(domainArr));

        // Range array
        Array *rangeArr = new Array(nullptr);
        for (int i = 0; i < nOutputs; i++) {
            rangeArr->add(Object(range[i].first));
            rangeArr->add(Object(range[i].second));
        }
        dict->add("Range", Object(rangeArr));

        // Size array
        Array *sizeArr = new Array(nullptr);
        for (int i = 0; i < nInputs; i++) {
            sizeArr->add(Object(sizes[i]));
        }
        dict->add("Size", Object(sizeArr));

        // BitsPerSample
        dict->add("BitsPerSample", Object(bitsPerSample));

        // Encode array (optional)
        if (!encode.empty()) {
            Array *encodeArr = new Array(nullptr);
            for (int i = 0; i < nInputs; i++) {
                encodeArr->add(Object(encode[i].first));
                encodeArr->add(Object(encode[i].second));
            }
            dict->add("Encode", Object(encodeArr));
        }

        // Decode array (optional)
        if (!decode.empty()) {
            Array *decodeArr = new Array(nullptr);
            for (int i = 0; i < nOutputs; i++) {
                decodeArr->add(Object(decode[i].first));
                decodeArr->add(Object(decode[i].second));
            }
            dict->add("Decode", Object(decodeArr));
        }

        // Create a memory stream with the sample data
        char *buf = (char *)gmalloc(sampleData.size());
        memcpy(buf, sampleData.data(), sampleData.size());

        Object dictObj(dict);
        Stream *baseStream = new MemStream(buf, 0, sampleData.size(), std::move(dictObj));
        baseStream->reset();

        Object streamObj(baseStream);

        auto func = std::unique_ptr<SampledFunction>(
            static_cast<SampledFunction*>(
                Function::parse(&streamObj).release()));

        return func;
    }
};

// Test basic construction and isOk for a simple 1-input, 1-output sampled function
TEST_F(SampledFunctionTest_363, BasicConstruction_363) {
    // 1 input, 1 output, size [2], 8 bits per sample
    // Samples: 0, 255 (maps to 0.0 and 1.0)
    std::vector<unsigned char> samples = {0, 255};

    auto func = createSimpleSampledFunction(
        1, 1,
        {2},
        8,
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        samples
    );

    if (func) {
        EXPECT_TRUE(func->isOk());
    }
}

// Test getType returns Type 0 (Sampled)
TEST_F(SampledFunctionTest_363, GetTypeReturnsSampled_363) {
    std::vector<unsigned char> samples = {0, 255};

    auto func = createSimpleSampledFunction(
        1, 1,
        {2},
        8,
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        samples
    );

    if (func && func->isOk()) {
        EXPECT_EQ(func->getType(), Function::Type::Sampled);
    }
}

// Test getEncodeMax returns correct values
TEST_F(SampledFunctionTest_363, GetEncodeMax_363) {
    std::vector<unsigned char> samples = {0, 255};

    auto func = createSimpleSampledFunction(
        1, 1,
        {2},
        8,
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        samples
    );

    if (func && func->isOk()) {
        EXPECT_DOUBLE_EQ(func->getEncodeMax(0), 1.0);
    }
}

// Test getEncodeMin returns correct values
TEST_F(SampledFunctionTest_363, GetEncodeMin_363) {
    std::vector<unsigned char> samples = {0, 255};

    auto func = createSimpleSampledFunction(
        1, 1,
        {2},
        8,
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        samples
    );

    if (func && func->isOk()) {
        EXPECT_DOUBLE_EQ(func->getEncodeMin(0), 0.0);
    }
}

// Test getDecodeMin and getDecodeMax
TEST_F(SampledFunctionTest_363, GetDecodeMinMax_363) {
    std::vector<unsigned char> samples = {0, 255};

    auto func = createSimpleSampledFunction(
        1, 1,
        {2},
        8,
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        samples
    );

    if (func && func->isOk()) {
        EXPECT_DOUBLE_EQ(func->getDecodeMin(0), 0.0);
        EXPECT_DOUBLE_EQ(func->getDecodeMax(0), 1.0);
    }
}

// Test getSampleSize
TEST_F(SampledFunctionTest_363, GetSampleSize_363) {
    std::vector<unsigned char> samples = {0, 255};

    auto func = createSimpleSampledFunction(
        1, 1,
        {2},
        8,
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        samples
    );

    if (func && func->isOk()) {
        EXPECT_EQ(func->getSampleSize(0), 2);
    }
}

// Test getSampleNumber
TEST_F(SampledFunctionTest_363, GetSampleNumber_363) {
    std::vector<unsigned char> samples = {0, 255};

    auto func = createSimpleSampledFunction(
        1, 1,
        {2},
        8,
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        samples
    );

    if (func && func->isOk()) {
        EXPECT_EQ(func->getSampleNumber(), 2);
    }
}

// Test getSamples is not null
TEST_F(SampledFunctionTest_363, GetSamplesNotNull_363) {
    std::vector<unsigned char> samples = {0, 255};

    auto func = createSimpleSampledFunction(
        1, 1,
        {2},
        8,
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        samples
    );

    if (func && func->isOk()) {
        EXPECT_NE(func->getSamples(), nullptr);
    }
}

// Test transform with boundary input values
TEST_F(SampledFunctionTest_363, TransformAtBoundaries_363) {
    // 2 samples: value 0 and value 255 (mapping to 0.0 and 1.0 with 8-bit)
    std::vector<unsigned char> samples = {0, 255};

    auto func = createSimpleSampledFunction(
        1, 1,
        {2},
        8,
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        samples
    );

    if (func && func->isOk()) {
        double in[1], out[1];

        // Test at input = 0.0
        in[0] = 0.0;
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.0, 0.01);

        // Test at input = 1.0
        in[0] = 1.0;
        func->transform(in, out);
        EXPECT_NEAR(out[0], 1.0, 0.01);
    }
}

// Test transform with midpoint input
TEST_F(SampledFunctionTest_363, TransformAtMidpoint_363) {
    std::vector<unsigned char> samples = {0, 255};

    auto func = createSimpleSampledFunction(
        1, 1,
        {2},
        8,
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        samples
    );

    if (func && func->isOk()) {
        double in[1] = {0.5};
        double out[1];
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.5, 0.05);
    }
}

// Test with custom encode range
TEST_F(SampledFunctionTest_363, CustomEncodeRange_363) {
    std::vector<unsigned char> samples = {0, 128, 255};

    auto func = createSimpleSampledFunction(
        1, 1,
        {3},
        8,
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 2.0}},
        {{0.0, 1.0}},
        samples
    );

    if (func && func->isOk()) {
        EXPECT_DOUBLE_EQ(func->getEncodeMin(0), 0.0);
        EXPECT_DOUBLE_EQ(func->getEncodeMax(0), 2.0);
    }
}

// Test with custom decode range
TEST_F(SampledFunctionTest_363, CustomDecodeRange_363) {
    std::vector<unsigned char> samples = {0, 255};

    auto func = createSimpleSampledFunction(
        1, 1,
        {2},
        8,
        {{0.0, 1.0}},
        {{0.0, 10.0}},
        {{0.0, 1.0}},
        {{0.0, 10.0}},
        samples
    );

    if (func && func->isOk()) {
        EXPECT_DOUBLE_EQ(func->getDecodeMin(0), 0.0);
        EXPECT_DOUBLE_EQ(func->getDecodeMax(0), 10.0);
    }
}

// Test copy functionality
TEST_F(SampledFunctionTest_363, CopyFunction_363) {
    std::vector<unsigned char> samples = {0, 255};

    auto func = createSimpleSampledFunction(
        1, 1,
        {2},
        8,
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        samples
    );

    if (func && func->isOk()) {
        auto copied = func->copy();
        ASSERT_NE(copied, nullptr);

        SampledFunction *copiedSampled = static_cast<SampledFunction*>(copied.get());
        EXPECT_TRUE(copiedSampled->isOk());
        EXPECT_DOUBLE_EQ(copiedSampled->getEncodeMax(0), func->getEncodeMax(0));
        EXPECT_DOUBLE_EQ(copiedSampled->getEncodeMin(0), func->getEncodeMin(0));
        EXPECT_DOUBLE_EQ(copiedSampled->getDecodeMax(0), func->getDecodeMax(0));
        EXPECT_DOUBLE_EQ(copiedSampled->getDecodeMin(0), func->getDecodeMin(0));
        EXPECT_EQ(copiedSampled->getSampleSize(0), func->getSampleSize(0));
        EXPECT_EQ(copiedSampled->getSampleNumber(), func->getSampleNumber());

        // Verify transform produces same results
        double in[1] = {0.5};
        double out1[1], out2[1];
        func->transform(in, out1);
        copiedSampled->transform(in, out2);
        EXPECT_DOUBLE_EQ(out1[0], out2[0]);
    }
}

// Test with 2 inputs, 1 output
TEST_F(SampledFunctionTest_363, TwoInputOneOutput_363) {
    // Size [2, 2], so 4 samples total for 1 output
    std::vector<unsigned char> samples = {0, 128, 64, 255};

    auto func = createSimpleSampledFunction(
        2, 1,
        {2, 2},
        8,
        {{0.0, 1.0}, {0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}, {0.0, 1.0}},
        {{0.0, 1.0}},
        samples
    );

    if (func && func->isOk()) {
        EXPECT_EQ(func->getSampleSize(0), 2);
        EXPECT_EQ(func->getSampleSize(1), 2);
        EXPECT_DOUBLE_EQ(func->getEncodeMax(0), 1.0);
        EXPECT_DOUBLE_EQ(func->getEncodeMax(1), 1.0);
    }
}

// Test transform clamping for out-of-domain input
TEST_F(SampledFunctionTest_363, TransformOutOfDomainClamped_363) {
    std::vector<unsigned char> samples = {0, 255};

    auto func = createSimpleSampledFunction(
        1, 1,
        {2},
        8,
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        samples
    );

    if (func && func->isOk()) {
        double in[1], out[1];

        // Input below domain minimum
        in[0] = -1.0;
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.0, 0.01);

        // Input above domain maximum
        in[0] = 2.0;
        func->transform(in, out);
        EXPECT_NEAR(out[0], 1.0, 0.01);
    }
}

// Test hasDifferentResultSet with same function
TEST_F(SampledFunctionTest_363, HasDifferentResultSetSameFunction_363) {
    std::vector<unsigned char> samples = {0, 255};

    auto func = createSimpleSampledFunction(
        1, 1,
        {2},
        8,
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        samples
    );

    if (func && func->isOk()) {
        auto copied = func->copy();
        if (copied) {
            // Same function should not have different result set
            EXPECT_FALSE(func->hasDifferentResultSet(copied.get()));
        }
    }
}

// Test with multiple outputs
TEST_F(SampledFunctionTest_363, MultipleOutputs_363) {
    // 1 input, 2 outputs, size [2]
    // Samples interleaved: out0_s0, out1_s0, out0_s1, out1_s1
    std::vector<unsigned char> samples = {0, 255, 255, 0};

    auto func = createSimpleSampledFunction(
        1, 2,
        {2},
        8,
        {{0.0, 1.0}},
        {{0.0, 1.0}, {0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 1.0}, {0.0, 1.0}},
        samples
    );

    if (func && func->isOk()) {
        EXPECT_DOUBLE_EQ(func->getDecodeMax(0), 1.0);
        EXPECT_DOUBLE_EQ(func->getDecodeMax(1), 1.0);

        double in[1] = {0.0};
        double out[2];
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.0, 0.01);
        EXPECT_NEAR(out[1], 1.0, 0.01);
    }
}

// Test with larger sample size
TEST_F(SampledFunctionTest_363, LargerSampleSize_363) {
    // 1 input, 1 output, size [5]
    std::vector<unsigned char> samples = {0, 64, 128, 192, 255};

    auto func = createSimpleSampledFunction(
        1, 1,
        {5},
        8,
        {{0.0, 1.0}},
        {{0.0, 1.0}},
        {{0.0, 4.0}},
        {{0.0, 1.0}},
        samples
    );

    if (func && func->isOk()) {
        EXPECT_EQ(func->getSampleSize(0), 5);
        EXPECT_EQ(func->getSampleNumber(), 5);
        EXPECT_DOUBLE_EQ(func->getEncodeMax(0), 4.0);
    }
}
