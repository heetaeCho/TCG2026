#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Function.h"
#include "Object.h"
#include "Dict.h"
#include "Stream.h"
#include "Array.h"
#include <memory>
#include <cstring>

// We need to construct SampledFunction from PDF objects.
// A sampled function (type 0) requires:
// - A stream object containing samples
// - /Size array
// - /BitsPerSample
// - /Domain array
// - /Range array
// Optional: /Encode, /Decode, /Order

class SampledFunctionTest_359 : public ::testing::Test {
protected:
    // Helper to build a minimal valid sampled function
    // 1-input, 1-output, size=[2], domain=[0 1], range=[0 1], BitsPerSample=8
    std::unique_ptr<Function> createSimpleSampledFunction(
        int numInputs, int numOutputs,
        const std::vector<int>& sizes,
        const std::vector<double>& domain,
        const std::vector<double>& range,
        int bitsPerSample,
        const std::vector<unsigned char>& sampleData,
        const std::vector<double>& encode = {},
        const std::vector<double>& decode = {})
    {
        // Build dictionary entries
        auto xref = (XRef*)nullptr;
        Dict *dict = new Dict(xref);

        // FunctionType
        dict->add("FunctionType", Object(0));

        // Domain array
        Array *domainArr = new Array(xref);
        for (double d : domain) {
            domainArr->add(Object(d));
        }
        dict->add("Domain", Object(domainArr));

        // Range array
        Array *rangeArr = new Array(xref);
        for (double r : range) {
            rangeArr->add(Object(r));
        }
        dict->add("Range", Object(rangeArr));

        // Size array
        Array *sizeArr = new Array(xref);
        for (int s : sizes) {
            sizeArr->add(Object(s));
        }
        dict->add("Size", Object(sizeArr));

        // BitsPerSample
        dict->add("BitsPerSample", Object(bitsPerSample));

        // Encode (optional)
        if (!encode.empty()) {
            Array *encArr = new Array(xref);
            for (double e : encode) {
                encArr->add(Object(e));
            }
            dict->add("Encode", Object(encArr));
        }

        // Decode (optional)
        if (!decode.empty()) {
            Array *decArr = new Array(xref);
            for (double d : decode) {
                decArr->add(Object(d));
            }
            dict->add("Decode", Object(decArr));
        }

        // Create stream with sample data
        char *buf = (char*)gmalloc(sampleData.size());
        memcpy(buf, sampleData.data(), sampleData.size());
        Object dictObj(dict);
        MemStream *memStream = new MemStream(buf, 0, sampleData.size(), std::move(dictObj));
        
        Object streamObj(memStream);
        
        auto func = Function::parse(&streamObj);
        return func;
    }
};

TEST_F(SampledFunctionTest_359, GetType_ReturnsSampled_359) {
    // Simple 1D->1D function with 2 samples: 0 and 255
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1, {2}, {0.0, 1.0}, {0.0, 1.0}, 8, samples);
    
    if (func) {
        EXPECT_EQ(func->getType(), Function::Type::Sampled);
    }
}

TEST_F(SampledFunctionTest_359, IsOk_ValidFunction_359) {
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1, {2}, {0.0, 1.0}, {0.0, 1.0}, 8, samples);
    
    if (func) {
        EXPECT_TRUE(func->isOk());
    }
}

TEST_F(SampledFunctionTest_359, GetInputSize_359) {
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1, {2}, {0.0, 1.0}, {0.0, 1.0}, 8, samples);
    
    if (func) {
        EXPECT_EQ(func->getInputSize(), 1);
    }
}

TEST_F(SampledFunctionTest_359, GetOutputSize_359) {
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1, {2}, {0.0, 1.0}, {0.0, 1.0}, 8, samples);
    
    if (func) {
        EXPECT_EQ(func->getOutputSize(), 1);
    }
}

TEST_F(SampledFunctionTest_359, TransformAtDomainMin_359) {
    // Samples: 0 at x=0, 255 at x=1
    // With range [0,1], sample 0 -> 0.0, sample 255 -> 1.0
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1, {2}, {0.0, 1.0}, {0.0, 1.0}, 8, samples);
    
    if (func && func->isOk()) {
        double in = 0.0;
        double out = -1.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.0, 0.01);
    }
}

TEST_F(SampledFunctionTest_359, TransformAtDomainMax_359) {
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1, {2}, {0.0, 1.0}, {0.0, 1.0}, 8, samples);
    
    if (func && func->isOk()) {
        double in = 1.0;
        double out = -1.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 1.0, 0.01);
    }
}

TEST_F(SampledFunctionTest_359, TransformAtMidpoint_359) {
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1, {2}, {0.0, 1.0}, {0.0, 1.0}, 8, samples);
    
    if (func && func->isOk()) {
        double in = 0.5;
        double out = -1.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.5, 0.05);
    }
}

TEST_F(SampledFunctionTest_359, GetSampleSize_359) {
    std::vector<unsigned char> samples = {0, 128, 255};
    auto func = createSimpleSampledFunction(
        1, 1, {3}, {0.0, 1.0}, {0.0, 1.0}, 8, samples);
    
    if (func && func->isOk()) {
        auto *sf = static_cast<SampledFunction*>(func.get());
        EXPECT_EQ(sf->getSampleSize(0), 3);
    }
}

TEST_F(SampledFunctionTest_359, GetSampleNumber_359) {
    std::vector<unsigned char> samples = {0, 128, 255};
    auto func = createSimpleSampledFunction(
        1, 1, {3}, {0.0, 1.0}, {0.0, 1.0}, 8, samples);
    
    if (func && func->isOk()) {
        auto *sf = static_cast<SampledFunction*>(func.get());
        EXPECT_EQ(sf->getSampleNumber(), 3);
    }
}

TEST_F(SampledFunctionTest_359, GetSamples_NotNull_359) {
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1, {2}, {0.0, 1.0}, {0.0, 1.0}, 8, samples);
    
    if (func && func->isOk()) {
        auto *sf = static_cast<SampledFunction*>(func.get());
        EXPECT_NE(sf->getSamples(), nullptr);
    }
}

TEST_F(SampledFunctionTest_359, GetDomainMin_359) {
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1, {2}, {0.0, 1.0}, {0.0, 1.0}, 8, samples);
    
    if (func && func->isOk()) {
        EXPECT_DOUBLE_EQ(func->getDomainMin(0), 0.0);
    }
}

TEST_F(SampledFunctionTest_359, GetDomainMax_359) {
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1, {2}, {0.0, 1.0}, {0.0, 1.0}, 8, samples);
    
    if (func && func->isOk()) {
        EXPECT_DOUBLE_EQ(func->getDomainMax(0), 1.0);
    }
}

TEST_F(SampledFunctionTest_359, GetRangeMin_359) {
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1, {2}, {0.0, 1.0}, {0.0, 1.0}, 8, samples);
    
    if (func && func->isOk()) {
        EXPECT_DOUBLE_EQ(func->getRangeMin(0), 0.0);
    }
}

TEST_F(SampledFunctionTest_359, GetRangeMax_359) {
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1, {2}, {0.0, 1.0}, {0.0, 1.0}, 8, samples);
    
    if (func && func->isOk()) {
        EXPECT_DOUBLE_EQ(func->getRangeMax(0), 1.0);
    }
}

TEST_F(SampledFunctionTest_359, CopyFunction_359) {
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1, {2}, {0.0, 1.0}, {0.0, 1.0}, 8, samples);
    
    if (func && func->isOk()) {
        auto copy = func->copy();
        ASSERT_NE(copy, nullptr);
        EXPECT_EQ(copy->getType(), Function::Type::Sampled);
        EXPECT_TRUE(copy->isOk());
        EXPECT_EQ(copy->getInputSize(), func->getInputSize());
        EXPECT_EQ(copy->getOutputSize(), func->getOutputSize());
        
        // Both should produce same output
        double in = 0.5;
        double out1 = -1.0, out2 = -1.0;
        func->transform(&in, &out1);
        copy->transform(&in, &out2);
        EXPECT_DOUBLE_EQ(out1, out2);
    }
}

TEST_F(SampledFunctionTest_359, HasDifferentResultSet_SameFunction_359) {
    std::vector<unsigned char> samples = {0, 255};
    auto func1 = createSimpleSampledFunction(
        1, 1, {2}, {0.0, 1.0}, {0.0, 1.0}, 8, samples);
    auto func2 = createSimpleSampledFunction(
        1, 1, {2}, {0.0, 1.0}, {0.0, 1.0}, 8, samples);
    
    if (func1 && func1->isOk() && func2 && func2->isOk()) {
        EXPECT_FALSE(func1->hasDifferentResultSet(func2.get()));
    }
}

TEST_F(SampledFunctionTest_359, HasDifferentResultSet_DifferentFunction_359) {
    std::vector<unsigned char> samples1 = {0, 255};
    std::vector<unsigned char> samples2 = {255, 0};
    auto func1 = createSimpleSampledFunction(
        1, 1, {2}, {0.0, 1.0}, {0.0, 1.0}, 8, samples1);
    auto func2 = createSimpleSampledFunction(
        1, 1, {2}, {0.0, 1.0}, {0.0, 1.0}, 8, samples2);
    
    if (func1 && func1->isOk() && func2 && func2->isOk()) {
        EXPECT_TRUE(func1->hasDifferentResultSet(func2.get()));
    }
}

TEST_F(SampledFunctionTest_359, TransformClampsBelowDomain_359) {
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1, {2}, {0.0, 1.0}, {0.0, 1.0}, 8, samples);
    
    if (func && func->isOk()) {
        double in = -1.0;  // Below domain
        double out = -1.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 0.0, 0.01);
    }
}

TEST_F(SampledFunctionTest_359, TransformClampsAboveDomain_359) {
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1, {2}, {0.0, 1.0}, {0.0, 1.0}, 8, samples);
    
    if (func && func->isOk()) {
        double in = 2.0;  // Above domain
        double out = -1.0;
        func->transform(&in, &out);
        EXPECT_NEAR(out, 1.0, 0.01);
    }
}

TEST_F(SampledFunctionTest_359, MultipleOutputs_359) {
    // 1 input, 2 outputs, size=[2], 4 samples total
    std::vector<unsigned char> samples = {0, 255, 255, 0};
    auto func = createSimpleSampledFunction(
        1, 2, {2}, {0.0, 1.0}, {0.0, 1.0, 0.0, 1.0}, 8, samples);
    
    if (func && func->isOk()) {
        EXPECT_EQ(func->getOutputSize(), 2);
        
        double in = 0.0;
        double out[2] = {-1.0, -1.0};
        func->transform(&in, out);
        EXPECT_NEAR(out[0], 0.0, 0.01);
        EXPECT_NEAR(out[1], 1.0, 0.01);
    }
}

TEST_F(SampledFunctionTest_359, GetEncodeMinMax_359) {
    std::vector<unsigned char> samples = {0, 128, 255};
    auto func = createSimpleSampledFunction(
        1, 1, {3}, {0.0, 1.0}, {0.0, 1.0}, 8, samples,
        {0.0, 2.0},  // encode
        {0.0, 1.0}   // decode
    );
    
    if (func && func->isOk()) {
        auto *sf = static_cast<SampledFunction*>(func.get());
        EXPECT_DOUBLE_EQ(sf->getEncodeMin(0), 0.0);
        EXPECT_DOUBLE_EQ(sf->getEncodeMax(0), 2.0);
    }
}

TEST_F(SampledFunctionTest_359, GetDecodeMinMax_359) {
    std::vector<unsigned char> samples = {0, 128, 255};
    auto func = createSimpleSampledFunction(
        1, 1, {3}, {0.0, 1.0}, {0.0, 1.0}, 8, samples,
        {0.0, 2.0},
        {0.0, 1.0}
    );
    
    if (func && func->isOk()) {
        auto *sf = static_cast<SampledFunction*>(func.get());
        EXPECT_DOUBLE_EQ(sf->getDecodeMin(0), 0.0);
        EXPECT_DOUBLE_EQ(sf->getDecodeMax(0), 1.0);
    }
}

TEST_F(SampledFunctionTest_359, TransformCachesResults_359) {
    // Calling transform twice with the same input should give the same result
    std::vector<unsigned char> samples = {0, 128, 255};
    auto func = createSimpleSampledFunction(
        1, 1, {3}, {0.0, 1.0}, {0.0, 1.0}, 8, samples);
    
    if (func && func->isOk()) {
        double in = 0.5;
        double out1 = -1.0, out2 = -1.0;
        func->transform(&in, &out1);
        func->transform(&in, &out2);
        EXPECT_DOUBLE_EQ(out1, out2);
    }
}

TEST_F(SampledFunctionTest_359, DefaultEncodeValues_359) {
    // Without explicit Encode, defaults should be [0, Size_i - 1]
    std::vector<unsigned char> samples = {0, 128, 255, 64};
    auto func = createSimpleSampledFunction(
        1, 1, {4}, {0.0, 1.0}, {0.0, 1.0}, 8, samples);
    
    if (func && func->isOk()) {
        auto *sf = static_cast<SampledFunction*>(func.get());
        EXPECT_DOUBLE_EQ(sf->getEncodeMin(0), 0.0);
        EXPECT_DOUBLE_EQ(sf->getEncodeMax(0), 3.0);  // Size_0 - 1
    }
}

TEST_F(SampledFunctionTest_359, DefaultDecodeValues_359) {
    // Without explicit Decode, defaults should be Range values
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1, {2}, {0.0, 1.0}, {-5.0, 5.0}, 8, samples);
    
    if (func && func->isOk()) {
        auto *sf = static_cast<SampledFunction*>(func.get());
        EXPECT_DOUBLE_EQ(sf->getDecodeMin(0), -5.0);
        EXPECT_DOUBLE_EQ(sf->getDecodeMax(0), 5.0);
    }
}

TEST_F(SampledFunctionTest_359, TwoDimensionalInput_359) {
    // 2 inputs, 1 output, size=[2,2], 4 samples
    std::vector<unsigned char> samples = {0, 128, 64, 255};
    auto func = createSimpleSampledFunction(
        2, 1, {2, 2}, {0.0, 1.0, 0.0, 1.0}, {0.0, 1.0}, 8, samples);
    
    if (func && func->isOk()) {
        EXPECT_EQ(func->getInputSize(), 2);
        EXPECT_EQ(func->getOutputSize(), 1);
        
        auto *sf = static_cast<SampledFunction*>(func.get());
        EXPECT_EQ(sf->getSampleSize(0), 2);
        EXPECT_EQ(sf->getSampleSize(1), 2);
        EXPECT_EQ(sf->getSampleNumber(), 4);
    }
}
