#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Function.h"

// Since SampledFunction requires complex PDF objects for construction,
// and we must treat the implementation as a black box, we test what we can
// through the public interface. We focus on getSampleNumber() as shown in
// the partial code, and other accessor methods from the known interface.

// Note: SampledFunction construction requires Object* and Dict* which are
// Poppler internal types. We need to include the necessary headers.
#include "Object.h"
#include "Dict.h"
#include "Stream.h"

#include <memory>
#include <vector>
#include <cstring>

class SampledFunctionTest_367 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a minimal sampled function from raw data
    // A sampled function (type 0) needs:
    // - /FunctionType 0
    // - /Domain array
    // - /Range array
    // - /Size array
    // - /BitsPerSample integer
    // - stream with sample data
    std::unique_ptr<Function> createSampledFunction(
        const std::vector<int>& size,
        const std::vector<double>& domain,
        const std::vector<double>& range,
        int bitsPerSample,
        const std::vector<unsigned char>& sampleData)
    {
        // Build dict entries for the function stream
        auto dict = Object(new Dict(nullptr));

        dict.dictAdd("FunctionType", Object(0));

        // Domain
        auto domainArr = Object(new Array(nullptr));
        for (double d : domain) {
            domainArr.arrayAdd(Object(d));
        }
        dict.dictAdd("Domain", std::move(domainArr));

        // Range
        auto rangeArr = Object(new Array(nullptr));
        for (double r : range) {
            rangeArr.arrayAdd(Object(r));
        }
        dict.dictAdd("Range", std::move(rangeArr));

        // Size
        auto sizeArr = Object(new Array(nullptr));
        for (int s : size) {
            sizeArr.arrayAdd(Object(s));
        }
        dict.dictAdd("Size", std::move(sizeArr));

        // BitsPerSample
        dict.dictAdd("BitsPerSample", Object(bitsPerSample));

        // Create a memory stream with sample data
        char* dataCopy = (char*)gmalloc(sampleData.size());
        memcpy(dataCopy, sampleData.data(), sampleData.size());

        Object streamDict = Object(new Dict(nullptr));
        streamDict.dictAdd("Length", Object((int)sampleData.size()));

        Stream* baseStream = new MemStream(dataCopy, 0, sampleData.size(), std::move(streamDict));
        Object streamObj = Object(baseStream);

        // Merge dict entries into the stream's dict
        for (int i = 0; i < dict.dictGetLength(); i++) {
            const char* key = dict.dictGetKey(i);
            streamObj.streamGetDict()->add(key, dict.dictGetVal(i).copy());
        }

        return Function::parse(&streamObj);
    }
};

// Test that getSampleNumber returns correct count for a simple 1D function
TEST_F(SampledFunctionTest_367, GetSampleNumber_Simple1D_367) {
    // 1 input, 1 output, size=[4], 8 bits per sample
    // 4 samples * 1 output = 4 bytes
    std::vector<unsigned char> data = {0, 85, 170, 255};
    auto func = createSampledFunction(
        {4},               // size
        {0.0, 1.0},       // domain (1 input)
        {0.0, 1.0},       // range (1 output)
        8,                  // bits per sample
        data
    );

    if (func) {
        ASSERT_EQ(func->getType(), Function::Type::Sampled);
        SampledFunction* sf = static_cast<SampledFunction*>(func.get());
        EXPECT_EQ(sf->getSampleNumber(), 4);
    }
}

// Test getSampleNumber for a 2D function
TEST_F(SampledFunctionTest_367, GetSampleNumber_2DFunction_367) {
    // 2 inputs, 1 output, size=[3,3], 8 bits per sample
    // 3*3 = 9 samples
    std::vector<unsigned char> data(9, 128);
    auto func = createSampledFunction(
        {3, 3},                      // size
        {0.0, 1.0, 0.0, 1.0},      // domain (2 inputs)
        {0.0, 1.0},                  // range (1 output)
        8,                            // bits per sample
        data
    );

    if (func) {
        ASSERT_EQ(func->getType(), Function::Type::Sampled);
        SampledFunction* sf = static_cast<SampledFunction*>(func.get());
        EXPECT_EQ(sf->getSampleNumber(), 9);
    }
}

// Test getSampleSize returns correct per-dimension size
TEST_F(SampledFunctionTest_367, GetSampleSize_367) {
    std::vector<unsigned char> data(12, 128); // 3*4=12 samples
    auto func = createSampledFunction(
        {3, 4},
        {0.0, 1.0, 0.0, 1.0},
        {0.0, 1.0},
        8,
        data
    );

    if (func) {
        SampledFunction* sf = static_cast<SampledFunction*>(func.get());
        EXPECT_EQ(sf->getSampleSize(0), 3);
        EXPECT_EQ(sf->getSampleSize(1), 4);
    }
}

// Test getEncodeMin and getEncodeMax defaults
TEST_F(SampledFunctionTest_367, GetEncodeDefaults_367) {
    // Default encode should be [0, Size[i]-1] for each dimension
    std::vector<unsigned char> data(4, 128);
    auto func = createSampledFunction(
        {4},
        {0.0, 1.0},
        {0.0, 1.0},
        8,
        data
    );

    if (func) {
        SampledFunction* sf = static_cast<SampledFunction*>(func.get());
        EXPECT_DOUBLE_EQ(sf->getEncodeMin(0), 0.0);
        EXPECT_DOUBLE_EQ(sf->getEncodeMax(0), 3.0); // Size[0]-1 = 3
    }
}

// Test getDecodeMin and getDecodeMax defaults
TEST_F(SampledFunctionTest_367, GetDecodeDefaults_367) {
    // Default decode should match Range
    std::vector<unsigned char> data(4, 128);
    auto func = createSampledFunction(
        {4},
        {0.0, 1.0},
        {0.0, 1.0},
        8,
        data
    );

    if (func) {
        SampledFunction* sf = static_cast<SampledFunction*>(func.get());
        EXPECT_DOUBLE_EQ(sf->getDecodeMin(0), 0.0);
        EXPECT_DOUBLE_EQ(sf->getDecodeMax(0), 1.0);
    }
}

// Test getSamples returns non-null pointer
TEST_F(SampledFunctionTest_367, GetSamplesNotNull_367) {
    std::vector<unsigned char> data = {0, 128, 255};
    auto func = createSampledFunction(
        {3},
        {0.0, 1.0},
        {0.0, 1.0},
        8,
        data
    );

    if (func) {
        SampledFunction* sf = static_cast<SampledFunction*>(func.get());
        EXPECT_NE(sf->getSamples(), nullptr);
    }
}

// Test isOk returns true for valid function
TEST_F(SampledFunctionTest_367, IsOkForValidFunction_367) {
    std::vector<unsigned char> data = {0, 255};
    auto func = createSampledFunction(
        {2},
        {0.0, 1.0},
        {0.0, 1.0},
        8,
        data
    );

    if (func) {
        EXPECT_TRUE(func->isOk());
    }
}

// Test getType returns Sampled
TEST_F(SampledFunctionTest_367, GetTypeReturnsSampled_367) {
    std::vector<unsigned char> data = {0, 255};
    auto func = createSampledFunction(
        {2},
        {0.0, 1.0},
        {0.0, 1.0},
        8,
        data
    );

    if (func) {
        EXPECT_EQ(func->getType(), Function::Type::Sampled);
    }
}

// Test copy creates a valid copy
TEST_F(SampledFunctionTest_367, CopyFunction_367) {
    std::vector<unsigned char> data = {0, 85, 170, 255};
    auto func = createSampledFunction(
        {4},
        {0.0, 1.0},
        {0.0, 1.0},
        8,
        data
    );

    if (func) {
        auto funcCopy = func->copy();
        ASSERT_NE(funcCopy, nullptr);
        EXPECT_TRUE(funcCopy->isOk());
        EXPECT_EQ(funcCopy->getType(), Function::Type::Sampled);

        SampledFunction* sfOrig = static_cast<SampledFunction*>(func.get());
        SampledFunction* sfCopy = static_cast<SampledFunction*>(funcCopy.get());
        EXPECT_EQ(sfCopy->getSampleNumber(), sfOrig->getSampleNumber());
        EXPECT_EQ(sfCopy->getSampleSize(0), sfOrig->getSampleSize(0));
    }
}

// Test transform produces output within range
TEST_F(SampledFunctionTest_367, TransformProducesOutputInRange_367) {
    // Linear ramp from 0 to 255 with 4 samples
    std::vector<unsigned char> data = {0, 85, 170, 255};
    auto func = createSampledFunction(
        {4},
        {0.0, 1.0},
        {0.0, 1.0},
        8,
        data
    );

    if (func) {
        double in[1] = {0.0};
        double out[1] = {-1.0};
        func->transform(in, out);
        EXPECT_GE(out[0], 0.0);
        EXPECT_LE(out[0], 1.0);

        in[0] = 1.0;
        func->transform(in, out);
        EXPECT_GE(out[0], 0.0);
        EXPECT_LE(out[0], 1.0);

        in[0] = 0.5;
        func->transform(in, out);
        EXPECT_GE(out[0], 0.0);
        EXPECT_LE(out[0], 1.0);
    }
}

// Test transform at boundaries of domain
TEST_F(SampledFunctionTest_367, TransformAtDomainBoundaries_367) {
    std::vector<unsigned char> data = {0, 255};
    auto func = createSampledFunction(
        {2},
        {0.0, 1.0},
        {0.0, 1.0},
        8,
        data
    );

    if (func) {
        double in[1], out[1];

        // At domain minimum
        in[0] = 0.0;
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.0, 0.01);

        // At domain maximum
        in[0] = 1.0;
        func->transform(in, out);
        EXPECT_NEAR(out[0], 1.0, 0.01);
    }
}

// Test transform with input outside domain (should be clamped)
TEST_F(SampledFunctionTest_367, TransformClampsBeyondDomain_367) {
    std::vector<unsigned char> data = {0, 255};
    auto func = createSampledFunction(
        {2},
        {0.0, 1.0},
        {0.0, 1.0},
        8,
        data
    );

    if (func) {
        double in[1], out[1];

        // Below domain minimum
        in[0] = -1.0;
        func->transform(in, out);
        EXPECT_GE(out[0], 0.0);
        EXPECT_LE(out[0], 1.0);

        // Above domain maximum
        in[0] = 2.0;
        func->transform(in, out);
        EXPECT_GE(out[0], 0.0);
        EXPECT_LE(out[0], 1.0);
    }
}

// Test with multiple outputs
TEST_F(SampledFunctionTest_367, MultipleOutputs_367) {
    // 1 input, 2 outputs, size=[2], 8 bits per sample
    // 2 samples * 2 outputs = 4 bytes
    // Sample 0: output0=0, output1=255
    // Sample 1: output0=255, output1=0
    std::vector<unsigned char> data = {0, 255, 255, 0};
    auto func = createSampledFunction(
        {2},
        {0.0, 1.0},
        {0.0, 1.0, 0.0, 1.0},
        8,
        data
    );

    if (func) {
        SampledFunction* sf = static_cast<SampledFunction*>(func.get());
        // Total samples = size[0] * nOutputs = 2 * 2 = 4
        EXPECT_EQ(sf->getSampleNumber(), 4);

        double in[1] = {0.0};
        double out[2] = {-1.0, -1.0};
        func->transform(in, out);
        EXPECT_GE(out[0], 0.0);
        EXPECT_LE(out[0], 1.0);
        EXPECT_GE(out[1], 0.0);
        EXPECT_LE(out[1], 1.0);
    }
}

// Test getSampleNumber with single sample
TEST_F(SampledFunctionTest_367, GetSampleNumberSingleSample_367) {
    std::vector<unsigned char> data = {128};
    auto func = createSampledFunction(
        {1},
        {0.0, 1.0},
        {0.0, 1.0},
        8,
        data
    );

    if (func) {
        SampledFunction* sf = static_cast<SampledFunction*>(func.get());
        EXPECT_EQ(sf->getSampleNumber(), 1);
    }
}

// Test hasDifferentResultSet between same and different functions
TEST_F(SampledFunctionTest_367, HasDifferentResultSet_367) {
    std::vector<unsigned char> data1 = {0, 255};
    auto func1 = createSampledFunction(
        {2}, {0.0, 1.0}, {0.0, 1.0}, 8, data1
    );

    std::vector<unsigned char> data2 = {0, 255};
    auto func2 = createSampledFunction(
        {2}, {0.0, 1.0}, {0.0, 1.0}, 8, data2
    );

    std::vector<unsigned char> data3 = {128, 128};
    auto func3 = createSampledFunction(
        {2}, {0.0, 1.0}, {0.0, 1.0}, 8, data3
    );

    if (func1 && func2) {
        // Same data should not have different result set
        EXPECT_FALSE(func1->hasDifferentResultSet(func2.get()));
    }

    if (func1 && func3) {
        // Different data should have different result set
        EXPECT_TRUE(func1->hasDifferentResultSet(func3.get()));
    }
}
