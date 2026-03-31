#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Function.h"
#include "Object.h"
#include "Dict.h"
#include "Stream.h"
#include "PDFDoc.h"

// Since SampledFunction requires complex PDF objects for construction,
// and we cannot access private state, we test through the public interface.
// We create minimal valid sampled function PDF objects where possible.

class SampledFunctionTest_365 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a minimal sampled function stream object
    // A sampled function (type 0) needs:
    // - FunctionType: 0
    // - Domain: array of 2*m numbers
    // - Size: array of m integers
    // - BitsPerSample: integer
    // Optional: Range, Encode, Decode, Order
    std::unique_ptr<SampledFunction> createSimpleSampledFunction(
        int m, int n,
        const std::vector<double>& domain,
        const std::vector<double>& range,
        const std::vector<int>& size,
        int bitsPerSample,
        const std::vector<double>& decode,
        const std::vector<unsigned char>& sampleData)
    {
        // Build the dictionary for the function stream
        auto dict = Object(new Dict(nullptr));

        // FunctionType
        dict.dictAdd("FunctionType", Object(0));

        // Domain
        auto domainArray = Object(new Array(nullptr));
        for (auto d : domain) {
            domainArray.arrayAdd(Object(d));
        }
        dict.dictAdd("Domain", std::move(domainArray));

        // Range
        auto rangeArray = Object(new Array(nullptr));
        for (auto r : range) {
            rangeArray.arrayAdd(Object(r));
        }
        dict.dictAdd("Range", std::move(rangeArray));

        // Size
        auto sizeArray = Object(new Array(nullptr));
        for (auto s : size) {
            sizeArray.arrayAdd(Object(s));
        }
        dict.dictAdd("Size", std::move(sizeArray));

        // BitsPerSample
        dict.dictAdd("BitsPerSample", Object(bitsPerSample));

        // Decode (if provided)
        if (!decode.empty()) {
            auto decodeArray = Object(new Array(nullptr));
            for (auto d : decode) {
                decodeArray.arrayAdd(Object(d));
            }
            dict.dictAdd("Decode", std::move(decodeArray));
        }

        // Create a memory stream with sample data
        char* buf = (char*)gmalloc(sampleData.size());
        memcpy(buf, sampleData.data(), sampleData.size());

        auto baseStr = new MemStream(buf, 0, sampleData.size(), std::move(dict));
        Object streamObj(baseStr);

        auto func = std::make_unique<SampledFunction>(&streamObj, streamObj.streamGetDict());
        return func;
    }
};

// Test getDecodeMax with explicit Decode values
TEST_F(SampledFunctionTest_365, GetDecodeMaxReturnsCorrectValue_365) {
    // 1 input, 1 output, domain [0 1], range [0 1], size [2], 8 bits
    // Decode [0.0 10.0]
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1,
        {0.0, 1.0},       // domain
        {0.0, 1.0},       // range
        {2},               // size
        8,                 // bitsPerSample
        {0.0, 10.0},      // decode
        samples
    );

    if (func && func->isOk()) {
        EXPECT_DOUBLE_EQ(func->getDecodeMax(0), 10.0);
    }
}

// Test getDecodeMax with default Decode (should default to Range values)
TEST_F(SampledFunctionTest_365, GetDecodeMaxDefaultsToRangeMax_365) {
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1,
        {0.0, 1.0},
        {0.0, 5.0},
        {2},
        8,
        {},              // no explicit decode -> defaults to range
        samples
    );

    if (func && func->isOk()) {
        EXPECT_DOUBLE_EQ(func->getDecodeMax(0), 5.0);
    }
}

// Test getDecodeMax with multiple outputs
TEST_F(SampledFunctionTest_365, GetDecodeMaxMultipleOutputs_365) {
    // 1 input, 2 outputs
    std::vector<unsigned char> samples = {0, 0, 255, 255};
    auto func = createSimpleSampledFunction(
        1, 2,
        {0.0, 1.0},
        {0.0, 1.0, 0.0, 2.0},
        {2},
        8,
        {0.0, 3.0, 0.0, 7.0},
        samples
    );

    if (func && func->isOk()) {
        EXPECT_DOUBLE_EQ(func->getDecodeMax(0), 3.0);
        EXPECT_DOUBLE_EQ(func->getDecodeMax(1), 7.0);
    }
}

// Test getDecodeMin alongside getDecodeMax
TEST_F(SampledFunctionTest_365, GetDecodeMinAndMaxConsistency_365) {
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1,
        {0.0, 1.0},
        {0.0, 1.0},
        {2},
        8,
        {-5.0, 15.0},
        samples
    );

    if (func && func->isOk()) {
        EXPECT_DOUBLE_EQ(func->getDecodeMin(0), -5.0);
        EXPECT_DOUBLE_EQ(func->getDecodeMax(0), 15.0);
    }
}

// Test getDecodeMax with negative decode values
TEST_F(SampledFunctionTest_365, GetDecodeMaxNegativeValues_365) {
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1,
        {0.0, 1.0},
        {-10.0, -1.0},
        {2},
        8,
        {-20.0, -2.0},
        samples
    );

    if (func && func->isOk()) {
        EXPECT_DOUBLE_EQ(func->getDecodeMax(0), -2.0);
    }
}

// Test getDecodeMax where decode min > decode max (inverted)
TEST_F(SampledFunctionTest_365, GetDecodeMaxInvertedDecodeRange_365) {
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1,
        {0.0, 1.0},
        {0.0, 1.0},
        {2},
        8,
        {10.0, 0.0},   // inverted: min > max
        samples
    );

    if (func && func->isOk()) {
        EXPECT_DOUBLE_EQ(func->getDecodeMax(0), 0.0);
    }
}

// Test getDecodeMax with zero-width decode range
TEST_F(SampledFunctionTest_365, GetDecodeMaxZeroRange_365) {
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1,
        {0.0, 1.0},
        {0.0, 1.0},
        {2},
        8,
        {5.0, 5.0},
        samples
    );

    if (func && func->isOk()) {
        EXPECT_DOUBLE_EQ(func->getDecodeMax(0), 5.0);
    }
}

// Test copy constructor preserves decode max
TEST_F(SampledFunctionTest_365, CopyPreservesDecodeMax_365) {
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1,
        {0.0, 1.0},
        {0.0, 1.0},
        {2},
        8,
        {0.0, 42.0},
        samples
    );

    if (func && func->isOk()) {
        auto copied = func->copy();
        auto* copiedSampled = dynamic_cast<SampledFunction*>(copied.get());
        ASSERT_NE(copiedSampled, nullptr);
        EXPECT_DOUBLE_EQ(copiedSampled->getDecodeMax(0), 42.0);
    }
}

// Test getSampleSize
TEST_F(SampledFunctionTest_365, GetSampleSizeReturnsCorrectValue_365) {
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1,
        {0.0, 1.0},
        {0.0, 1.0},
        {2},
        8,
        {},
        samples
    );

    if (func && func->isOk()) {
        EXPECT_EQ(func->getSampleSize(0), 2);
    }
}

// Test getEncodeMin and getEncodeMax
TEST_F(SampledFunctionTest_365, GetEncodeDefaultValues_365) {
    // Default encode is [0, Size_i - 1]
    std::vector<unsigned char> samples = {0, 128, 255};
    auto func = createSimpleSampledFunction(
        1, 1,
        {0.0, 1.0},
        {0.0, 1.0},
        {3},
        8,
        {},
        samples
    );

    if (func && func->isOk()) {
        EXPECT_DOUBLE_EQ(func->getEncodeMin(0), 0.0);
        EXPECT_DOUBLE_EQ(func->getEncodeMax(0), 2.0);  // Size[0] - 1 = 2
    }
}

// Test getType returns Type 0 (sampled)
TEST_F(SampledFunctionTest_365, GetTypeReturnsSampled_365) {
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1,
        {0.0, 1.0},
        {0.0, 1.0},
        {2},
        8,
        {},
        samples
    );

    if (func && func->isOk()) {
        EXPECT_EQ(func->getType(), Function::Type::Sampled);
    }
}

// Test getSamples returns non-null for valid function
TEST_F(SampledFunctionTest_365, GetSamplesNonNull_365) {
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1,
        {0.0, 1.0},
        {0.0, 1.0},
        {2},
        8,
        {},
        samples
    );

    if (func && func->isOk()) {
        EXPECT_NE(func->getSamples(), nullptr);
    }
}

// Test getSampleNumber
TEST_F(SampledFunctionTest_365, GetSampleNumber_365) {
    std::vector<unsigned char> samples = {0, 128, 255};
    auto func = createSimpleSampledFunction(
        1, 1,
        {0.0, 1.0},
        {0.0, 1.0},
        {3},
        8,
        {},
        samples
    );

    if (func && func->isOk()) {
        EXPECT_EQ(func->getSampleNumber(), 3);
    }
}

// Test transform produces output within range
TEST_F(SampledFunctionTest_365, TransformProducesOutput_365) {
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1,
        {0.0, 1.0},
        {0.0, 1.0},
        {2},
        8,
        {},
        samples
    );

    if (func && func->isOk()) {
        double in = 0.0;
        double out = -1.0;
        func->transform(&in, &out);
        EXPECT_GE(out, 0.0);
        EXPECT_LE(out, 1.0);

        in = 1.0;
        func->transform(&in, &out);
        EXPECT_GE(out, 0.0);
        EXPECT_LE(out, 1.0);
    }
}

// Test getDecodeMax with large decode values
TEST_F(SampledFunctionTest_365, GetDecodeMaxLargeValues_365) {
    std::vector<unsigned char> samples = {0, 255};
    auto func = createSimpleSampledFunction(
        1, 1,
        {0.0, 1.0},
        {0.0, 1.0},
        {2},
        8,
        {0.0, 1e10},
        samples
    );

    if (func && func->isOk()) {
        EXPECT_DOUBLE_EQ(func->getDecodeMax(0), 1e10);
    }
}
