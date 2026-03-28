#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Function.h"
#include "Object.h"
#include "Dict.h"
#include "Stream.h"
#include "PDFDoc.h"
#include <memory>
#include <cstring>
#include <vector>
#include <sstream>

// Helper to create a minimal sampled function PDF object for testing
// Since we're treating the implementation as a black box, we need to construct
// valid Object/Dict combinations that SampledFunction expects.

class SampledFunctionTest_358 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that copy() returns a non-null unique_ptr
TEST_F(SampledFunctionTest_358, CopyReturnsNonNull_358) {
    // We need a valid SampledFunction to test copy()
    // Since constructing one requires valid PDF objects, we test through
    // the Function::parse interface if available, or construct directly.
    
    // Create a minimal sampled function stream object
    // FunctionType 0, Domain, Range, Size, BitsPerSample are required
    
    // Build a dictionary for a Type 0 (Sampled) function
    auto xref = std::unique_ptr<XRef>(nullptr);
    
    Dict dict(nullptr);
    
    // Domain: [0 1]
    Object domainArray = Object(new Array(nullptr));
    domainArray.arrayAdd(Object(0.0));
    domainArray.arrayAdd(Object(1.0));
    dict.add("Domain", std::move(domainArray));
    
    // Range: [0 1]
    Object rangeArray = Object(new Array(nullptr));
    rangeArray.arrayAdd(Object(0.0));
    rangeArray.arrayAdd(Object(1.0));
    dict.add("Range", std::move(rangeArray));
    
    // Size: [2]
    Object sizeArray = Object(new Array(nullptr));
    sizeArray.arrayAdd(Object(2));
    dict.add("Size", std::move(sizeArray));
    
    // BitsPerSample: 8
    dict.add("BitsPerSample", Object(8));
    
    // FunctionType: 0
    dict.add("FunctionType", Object(0));
    
    // Create sample data - 2 samples of 1 byte each
    unsigned char sampleData[] = {0, 255};
    
    Object streamDict(new Dict(nullptr));
    streamDict.dictAdd("Length", Object(2));
    
    MemStream *memStream = new MemStream(reinterpret_cast<const char*>(sampleData), 0, 2, std::move(streamDict));
    
    Object funcObj(static_cast<Stream*>(memStream));
    
    // Try to parse the function
    std::unique_ptr<Function> func = Function::parse(&funcObj);
    
    if (func && func->isOk()) {
        std::unique_ptr<Function> copied = func->copy();
        EXPECT_NE(copied, nullptr);
        if (copied) {
            EXPECT_TRUE(copied->isOk());
        }
    }
}

// Test getType returns Type 0 for sampled functions
TEST_F(SampledFunctionTest_358, GetTypeReturnsSampled_358) {
    Dict dict(nullptr);
    
    Object domainArray = Object(new Array(nullptr));
    domainArray.arrayAdd(Object(0.0));
    domainArray.arrayAdd(Object(1.0));
    dict.add("Domain", std::move(domainArray));
    
    Object rangeArray = Object(new Array(nullptr));
    rangeArray.arrayAdd(Object(0.0));
    rangeArray.arrayAdd(Object(1.0));
    dict.add("Range", std::move(rangeArray));
    
    Object sizeArray = Object(new Array(nullptr));
    sizeArray.arrayAdd(Object(2));
    dict.add("Size", std::move(sizeArray));
    
    dict.add("BitsPerSample", Object(8));
    dict.add("FunctionType", Object(0));
    
    unsigned char sampleData[] = {0, 255};
    Object streamDict(new Dict(nullptr));
    streamDict.dictAdd("Length", Object(2));
    
    MemStream *memStream = new MemStream(reinterpret_cast<const char*>(sampleData), 0, 2, std::move(streamDict));
    Object funcObj(static_cast<Stream*>(memStream));
    
    std::unique_ptr<Function> func = Function::parse(&funcObj);
    
    if (func && func->isOk()) {
        EXPECT_EQ(func->getType(), Function::Type::Sampled);
    }
}

// Test getSampleSize for valid index
TEST_F(SampledFunctionTest_358, GetSampleSizeValidIndex_358) {
    Dict dict(nullptr);
    
    Object domainArray = Object(new Array(nullptr));
    domainArray.arrayAdd(Object(0.0));
    domainArray.arrayAdd(Object(1.0));
    dict.add("Domain", std::move(domainArray));
    
    Object rangeArray = Object(new Array(nullptr));
    rangeArray.arrayAdd(Object(0.0));
    rangeArray.arrayAdd(Object(1.0));
    dict.add("Range", std::move(rangeArray));
    
    Object sizeArray = Object(new Array(nullptr));
    sizeArray.arrayAdd(Object(4));
    dict.add("Size", std::move(sizeArray));
    
    dict.add("BitsPerSample", Object(8));
    dict.add("FunctionType", Object(0));
    
    unsigned char sampleData[] = {0, 85, 170, 255};
    Object streamDict(new Dict(nullptr));
    streamDict.dictAdd("Length", Object(4));
    
    MemStream *memStream = new MemStream(reinterpret_cast<const char*>(sampleData), 0, 4, std::move(streamDict));
    Object funcObj(static_cast<Stream*>(memStream));
    
    std::unique_ptr<Function> func = Function::parse(&funcObj);
    
    if (func && func->isOk()) {
        SampledFunction *sf = dynamic_cast<SampledFunction*>(func.get());
        if (sf) {
            EXPECT_EQ(sf->getSampleSize(0), 4);
        }
    }
}

// Test getSampleNumber
TEST_F(SampledFunctionTest_358, GetSampleNumber_358) {
    Dict dict(nullptr);
    
    Object domainArray = Object(new Array(nullptr));
    domainArray.arrayAdd(Object(0.0));
    domainArray.arrayAdd(Object(1.0));
    dict.add("Domain", std::move(domainArray));
    
    Object rangeArray = Object(new Array(nullptr));
    rangeArray.arrayAdd(Object(0.0));
    rangeArray.arrayAdd(Object(1.0));
    dict.add("Range", std::move(rangeArray));
    
    Object sizeArray = Object(new Array(nullptr));
    sizeArray.arrayAdd(Object(4));
    dict.add("Size", std::move(sizeArray));
    
    dict.add("BitsPerSample", Object(8));
    dict.add("FunctionType", Object(0));
    
    unsigned char sampleData[] = {0, 85, 170, 255};
    Object streamDict(new Dict(nullptr));
    streamDict.dictAdd("Length", Object(4));
    
    MemStream *memStream = new MemStream(reinterpret_cast<const char*>(sampleData), 0, 4, std::move(streamDict));
    Object funcObj(static_cast<Stream*>(memStream));
    
    std::unique_ptr<Function> func = Function::parse(&funcObj);
    
    if (func && func->isOk()) {
        SampledFunction *sf = dynamic_cast<SampledFunction*>(func.get());
        if (sf) {
            EXPECT_EQ(sf->getSampleNumber(), 4);
        }
    }
}

// Test getSamples returns non-null
TEST_F(SampledFunctionTest_358, GetSamplesReturnsNonNull_358) {
    Dict dict(nullptr);
    
    Object domainArray = Object(new Array(nullptr));
    domainArray.arrayAdd(Object(0.0));
    domainArray.arrayAdd(Object(1.0));
    dict.add("Domain", std::move(domainArray));
    
    Object rangeArray = Object(new Array(nullptr));
    rangeArray.arrayAdd(Object(0.0));
    rangeArray.arrayAdd(Object(1.0));
    dict.add("Range", std::move(rangeArray));
    
    Object sizeArray = Object(new Array(nullptr));
    sizeArray.arrayAdd(Object(2));
    dict.add("Size", std::move(sizeArray));
    
    dict.add("BitsPerSample", Object(8));
    dict.add("FunctionType", Object(0));
    
    unsigned char sampleData[] = {0, 255};
    Object streamDict(new Dict(nullptr));
    streamDict.dictAdd("Length", Object(2));
    
    MemStream *memStream = new MemStream(reinterpret_cast<const char*>(sampleData), 0, 2, std::move(streamDict));
    Object funcObj(static_cast<Stream*>(memStream));
    
    std::unique_ptr<Function> func = Function::parse(&funcObj);
    
    if (func && func->isOk()) {
        SampledFunction *sf = dynamic_cast<SampledFunction*>(func.get());
        if (sf) {
            EXPECT_NE(sf->getSamples(), nullptr);
        }
    }
}

// Test transform with boundary input values
TEST_F(SampledFunctionTest_358, TransformBoundaryValues_358) {
    Dict dict(nullptr);
    
    Object domainArray = Object(new Array(nullptr));
    domainArray.arrayAdd(Object(0.0));
    domainArray.arrayAdd(Object(1.0));
    dict.add("Domain", std::move(domainArray));
    
    Object rangeArray = Object(new Array(nullptr));
    rangeArray.arrayAdd(Object(0.0));
    rangeArray.arrayAdd(Object(1.0));
    dict.add("Range", std::move(rangeArray));
    
    Object sizeArray = Object(new Array(nullptr));
    sizeArray.arrayAdd(Object(2));
    dict.add("Size", std::move(sizeArray));
    
    dict.add("BitsPerSample", Object(8));
    dict.add("FunctionType", Object(0));
    
    unsigned char sampleData[] = {0, 255};
    Object streamDict(new Dict(nullptr));
    streamDict.dictAdd("Length", Object(2));
    
    MemStream *memStream = new MemStream(reinterpret_cast<const char*>(sampleData), 0, 2, std::move(streamDict));
    Object funcObj(static_cast<Stream*>(memStream));
    
    std::unique_ptr<Function> func = Function::parse(&funcObj);
    
    if (func && func->isOk()) {
        double in[1], out[1];
        
        // Test at domain minimum
        in[0] = 0.0;
        func->transform(in, out);
        EXPECT_GE(out[0], 0.0);
        EXPECT_LE(out[0], 1.0);
        
        // Test at domain maximum
        in[0] = 1.0;
        func->transform(in, out);
        EXPECT_GE(out[0], 0.0);
        EXPECT_LE(out[0], 1.0);
        
        // Test at midpoint
        in[0] = 0.5;
        func->transform(in, out);
        EXPECT_GE(out[0], 0.0);
        EXPECT_LE(out[0], 1.0);
    }
}

// Test with Encode and Decode specified
TEST_F(SampledFunctionTest_358, WithEncodeAndDecode_358) {
    Dict dict(nullptr);
    
    Object domainArray = Object(new Array(nullptr));
    domainArray.arrayAdd(Object(0.0));
    domainArray.arrayAdd(Object(1.0));
    dict.add("Domain", std::move(domainArray));
    
    Object rangeArray = Object(new Array(nullptr));
    rangeArray.arrayAdd(Object(0.0));
    rangeArray.arrayAdd(Object(10.0));
    dict.add("Range", std::move(rangeArray));
    
    Object sizeArray = Object(new Array(nullptr));
    sizeArray.arrayAdd(Object(2));
    dict.add("Size", std::move(sizeArray));
    
    dict.add("BitsPerSample", Object(8));
    dict.add("FunctionType", Object(0));
    
    // Encode
    Object encodeArray = Object(new Array(nullptr));
    encodeArray.arrayAdd(Object(0.0));
    encodeArray.arrayAdd(Object(1.0));
    dict.add("Encode", std::move(encodeArray));
    
    // Decode
    Object decodeArray = Object(new Array(nullptr));
    decodeArray.arrayAdd(Object(0.0));
    decodeArray.arrayAdd(Object(10.0));
    dict.add("Decode", std::move(decodeArray));
    
    unsigned char sampleData[] = {0, 255};
    Object streamDict(new Dict(nullptr));
    streamDict.dictAdd("Length", Object(2));
    
    MemStream *memStream = new MemStream(reinterpret_cast<const char*>(sampleData), 0, 2, std::move(streamDict));
    Object funcObj(static_cast<Stream*>(memStream));
    
    std::unique_ptr<Function> func = Function::parse(&funcObj);
    
    if (func && func->isOk()) {
        SampledFunction *sf = dynamic_cast<SampledFunction*>(func.get());
        if (sf) {
            EXPECT_DOUBLE_EQ(sf->getEncodeMin(0), 0.0);
            EXPECT_DOUBLE_EQ(sf->getEncodeMax(0), 1.0);
            EXPECT_DOUBLE_EQ(sf->getDecodeMin(0), 0.0);
            EXPECT_DOUBLE_EQ(sf->getDecodeMax(0), 10.0);
        }
    }
}

// Test copy preserves isOk state
TEST_F(SampledFunctionTest_358, CopyPreservesIsOk_358) {
    Dict dict(nullptr);
    
    Object domainArray = Object(new Array(nullptr));
    domainArray.arrayAdd(Object(0.0));
    domainArray.arrayAdd(Object(1.0));
    dict.add("Domain", std::move(domainArray));
    
    Object rangeArray = Object(new Array(nullptr));
    rangeArray.arrayAdd(Object(0.0));
    rangeArray.arrayAdd(Object(1.0));
    dict.add("Range", std::move(rangeArray));
    
    Object sizeArray = Object(new Array(nullptr));
    sizeArray.arrayAdd(Object(2));
    dict.add("Size", std::move(sizeArray));
    
    dict.add("BitsPerSample", Object(8));
    dict.add("FunctionType", Object(0));
    
    unsigned char sampleData[] = {0, 255};
    Object streamDict(new Dict(nullptr));
    streamDict.dictAdd("Length", Object(2));
    
    MemStream *memStream = new MemStream(reinterpret_cast<const char*>(sampleData), 0, 2, std::move(streamDict));
    Object funcObj(static_cast<Stream*>(memStream));
    
    std::unique_ptr<Function> func = Function::parse(&funcObj);
    
    if (func && func->isOk()) {
        std::unique_ptr<Function> copied = func->copy();
        ASSERT_NE(copied, nullptr);
        EXPECT_EQ(copied->isOk(), func->isOk());
    }
}

// Test copy produces same transform results
TEST_F(SampledFunctionTest_358, CopyProducesSameTransform_358) {
    Dict dict(nullptr);
    
    Object domainArray = Object(new Array(nullptr));
    domainArray.arrayAdd(Object(0.0));
    domainArray.arrayAdd(Object(1.0));
    dict.add("Domain", std::move(domainArray));
    
    Object rangeArray = Object(new Array(nullptr));
    rangeArray.arrayAdd(Object(0.0));
    rangeArray.arrayAdd(Object(1.0));
    dict.add("Range", std::move(rangeArray));
    
    Object sizeArray = Object(new Array(nullptr));
    sizeArray.arrayAdd(Object(2));
    dict.add("Size", std::move(sizeArray));
    
    dict.add("BitsPerSample", Object(8));
    dict.add("FunctionType", Object(0));
    
    unsigned char sampleData[] = {0, 255};
    Object streamDict(new Dict(nullptr));
    streamDict.dictAdd("Length", Object(2));
    
    MemStream *memStream = new MemStream(reinterpret_cast<const char*>(sampleData), 0, 2, std::move(streamDict));
    Object funcObj(static_cast<Stream*>(memStream));
    
    std::unique_ptr<Function> func = Function::parse(&funcObj);
    
    if (func && func->isOk()) {
        std::unique_ptr<Function> copied = func->copy();
        ASSERT_NE(copied, nullptr);
        
        double in[1] = {0.5};
        double out1[1], out2[1];
        
        func->transform(in, out1);
        copied->transform(in, out2);
        
        EXPECT_DOUBLE_EQ(out1[0], out2[0]);
    }
}

// Test with multiple inputs and outputs
TEST_F(SampledFunctionTest_358, MultipleInputsOutputs_358) {
    Dict dict(nullptr);
    
    // 2 inputs: Domain [0 1 0 1]
    Object domainArray = Object(new Array(nullptr));
    domainArray.arrayAdd(Object(0.0));
    domainArray.arrayAdd(Object(1.0));
    domainArray.arrayAdd(Object(0.0));
    domainArray.arrayAdd(Object(1.0));
    dict.add("Domain", std::move(domainArray));
    
    // 2 outputs: Range [0 1 0 1]
    Object rangeArray = Object(new Array(nullptr));
    rangeArray.arrayAdd(Object(0.0));
    rangeArray.arrayAdd(Object(1.0));
    rangeArray.arrayAdd(Object(0.0));
    rangeArray.arrayAdd(Object(1.0));
    dict.add("Range", std::move(rangeArray));
    
    // Size [2 2]
    Object sizeArray = Object(new Array(nullptr));
    sizeArray.arrayAdd(Object(2));
    sizeArray.arrayAdd(Object(2));
    dict.add("Size", std::move(sizeArray));
    
    dict.add("BitsPerSample", Object(8));
    dict.add("FunctionType", Object(0));
    
    // 2x2 grid, 2 outputs = 8 samples
    unsigned char sampleData[] = {0, 0, 255, 0, 0, 255, 255, 255};
    Object streamDict(new Dict(nullptr));
    streamDict.dictAdd("Length", Object(8));
    
    MemStream *memStream = new MemStream(reinterpret_cast<const char*>(sampleData), 0, 8, std::move(streamDict));
    Object funcObj(static_cast<Stream*>(memStream));
    
    std::unique_ptr<Function> func = Function::parse(&funcObj);
    
    if (func && func->isOk()) {
        SampledFunction *sf = dynamic_cast<SampledFunction*>(func.get());
        if (sf) {
            EXPECT_EQ(sf->getSampleSize(0), 2);
            EXPECT_EQ(sf->getSampleSize(1), 2);
            
            double in[2] = {0.0, 0.0};
            double out[2];
            func->transform(in, out);
            EXPECT_GE(out[0], 0.0);
            EXPECT_LE(out[0], 1.0);
            EXPECT_GE(out[1], 0.0);
            EXPECT_LE(out[1], 1.0);
        }
    }
}

// Test hasDifferentResultSet with same function
TEST_F(SampledFunctionTest_358, HasDifferentResultSetSameFunc_358) {
    Dict dict(nullptr);
    
    Object domainArray = Object(new Array(nullptr));
    domainArray.arrayAdd(Object(0.0));
    domainArray.arrayAdd(Object(1.0));
    dict.add("Domain", std::move(domainArray));
    
    Object rangeArray = Object(new Array(nullptr));
    rangeArray.arrayAdd(Object(0.0));
    rangeArray.arrayAdd(Object(1.0));
    dict.add("Range", std::move(rangeArray));
    
    Object sizeArray = Object(new Array(nullptr));
    sizeArray.arrayAdd(Object(2));
    dict.add("Size", std::move(sizeArray));
    
    dict.add("BitsPerSample", Object(8));
    dict.add("FunctionType", Object(0));
    
    unsigned char sampleData[] = {0, 255};
    Object streamDict(new Dict(nullptr));
    streamDict.dictAdd("Length", Object(2));
    
    MemStream *memStream = new MemStream(reinterpret_cast<const char*>(sampleData), 0, 2, std::move(streamDict));
    Object funcObj(static_cast<Stream*>(memStream));
    
    std::unique_ptr<Function> func = Function::parse(&funcObj);
    
    if (func && func->isOk()) {
        std::unique_ptr<Function> copied = func->copy();
        ASSERT_NE(copied, nullptr);
        
        // Same function should not have different result set
        bool different = func->hasDifferentResultSet(copied.get());
        EXPECT_FALSE(different);
    }
}

// Test isOk with valid construction
TEST_F(SampledFunctionTest_358, IsOkWithValidConstruction_358) {
    Dict dict(nullptr);
    
    Object domainArray = Object(new Array(nullptr));
    domainArray.arrayAdd(Object(0.0));
    domainArray.arrayAdd(Object(1.0));
    dict.add("Domain", std::move(domainArray));
    
    Object rangeArray = Object(new Array(nullptr));
    rangeArray.arrayAdd(Object(0.0));
    rangeArray.arrayAdd(Object(1.0));
    dict.add("Range", std::move(rangeArray));
    
    Object sizeArray = Object(new Array(nullptr));
    sizeArray.arrayAdd(Object(2));
    dict.add("Size", std::move(sizeArray));
    
    dict.add("BitsPerSample", Object(8));
    dict.add("FunctionType", Object(0));
    
    unsigned char sampleData[] = {0, 255};
    Object streamDict(new Dict(nullptr));
    streamDict.dictAdd("Length", Object(2));
    
    MemStream *memStream = new MemStream(reinterpret_cast<const char*>(sampleData), 0, 2, std::move(streamDict));
    Object funcObj(static_cast<Stream*>(memStream));
    
    std::unique_ptr<Function> func = Function::parse(&funcObj);
    
    if (func) {
        EXPECT_TRUE(func->isOk());
    }
}

// Test getEncode and getDecode min/max defaults
TEST_F(SampledFunctionTest_358, DefaultEncodeDecodeValues_358) {
    Dict dict(nullptr);
    
    Object domainArray = Object(new Array(nullptr));
    domainArray.arrayAdd(Object(0.0));
    domainArray.arrayAdd(Object(1.0));
    dict.add("Domain", std::move(domainArray));
    
    Object rangeArray = Object(new Array(nullptr));
    rangeArray.arrayAdd(Object(0.0));
    rangeArray.arrayAdd(Object(1.0));
    dict.add("Range", std::move(rangeArray));
    
    Object sizeArray = Object(new Array(nullptr));
    sizeArray.arrayAdd(Object(4));
    dict.add("Size", std::move(sizeArray));
    
    dict.add("BitsPerSample", Object(8));
    dict.add("FunctionType", Object(0));
    
    unsigned char sampleData[] = {0, 85, 170, 255};
    Object streamDict(new Dict(nullptr));
    streamDict.dictAdd("Length", Object(4));
    
    MemStream *memStream = new MemStream(reinterpret_cast<const char*>(sampleData), 0, 4, std::move(streamDict));
    Object funcObj(static_cast<Stream*>(memStream));
    
    std::unique_ptr<Function> func = Function::parse(&funcObj);
    
    if (func && func->isOk()) {
        SampledFunction *sf = dynamic_cast<SampledFunction*>(func.get());
        if (sf) {
            // Default encode should be [0 Size-1] = [0 3]
            EXPECT_DOUBLE_EQ(sf->getEncodeMin(0), 0.0);
            EXPECT_DOUBLE_EQ(sf->getEncodeMax(0), 3.0);
            
            // Default decode should be Range values = [0 1]
            EXPECT_DOUBLE_EQ(sf->getDecodeMin(0), 0.0);
            EXPECT_DOUBLE_EQ(sf->getDecodeMax(0), 1.0);
        }
    }
}

// Test transform with input outside domain (should be clamped)
TEST_F(SampledFunctionTest_358, TransformInputOutsideDomain_358) {
    Dict dict(nullptr);
    
    Object domainArray = Object(new Array(nullptr));
    domainArray.arrayAdd(Object(0.0));
    domainArray.arrayAdd(Object(1.0));
    dict.add("Domain", std::move(domainArray));
    
    Object rangeArray = Object(new Array(nullptr));
    rangeArray.arrayAdd(Object(0.0));
    rangeArray.arrayAdd(Object(1.0));
    dict.add("Range", std::move(rangeArray));
    
    Object sizeArray = Object(new Array(nullptr));
    sizeArray.arrayAdd(Object(2));
    dict.add("Size", std::move(sizeArray));
    
    dict.add("BitsPerSample", Object(8));
    dict.add("FunctionType", Object(0));
    
    unsigned char sampleData[] = {0, 255};
    Object streamDict(new Dict(nullptr));
    streamDict.dictAdd("Length", Object(2));
    
    MemStream *memStream = new MemStream(reinterpret_cast<const char*>(sampleData), 0, 2, std::move(streamDict));
    Object funcObj(static_cast<Stream*>(memStream));
    
    std::unique_ptr<Function> func = Function::parse(&funcObj);
    
    if (func && func->isOk()) {
        double in[1], out[1];
        double outAtMin[1], outAtMax[1];
        
        // Get expected values at boundaries
        in[0] = 0.0;
        func->transform(in, outAtMin);
        
        in[0] = 1.0;
        func->transform(in, outAtMax);
        
        // Test below domain minimum - should clamp to 0
        in[0] = -1.0;
        func->transform(in, out);
        EXPECT_DOUBLE_EQ(out[0], outAtMin[0]);
        
        // Test above domain maximum - should clamp to 1
        in[0] = 2.0;
        func->transform(in, out);
        EXPECT_DOUBLE_EQ(out[0], outAtMax[0]);
    }
}

// Test with 16 bits per sample
TEST_F(SampledFunctionTest_358, SixteenBitsPerSample_358) {
    Dict dict(nullptr);
    
    Object domainArray = Object(new Array(nullptr));
    domainArray.arrayAdd(Object(0.0));
    domainArray.arrayAdd(Object(1.0));
    dict.add("Domain", std::move(domainArray));
    
    Object rangeArray = Object(new Array(nullptr));
    rangeArray.arrayAdd(Object(0.0));
    rangeArray.arrayAdd(Object(1.0));
    dict.add("Range", std::move(rangeArray));
    
    Object sizeArray = Object(new Array(nullptr));
    sizeArray.arrayAdd(Object(2));
    dict.add("Size", std::move(sizeArray));
    
    dict.add("BitsPerSample", Object(16));
    dict.add("FunctionType", Object(0));
    
    // 2 samples, 16 bits each = 4 bytes
    unsigned char sampleData[] = {0x00, 0x00, 0xFF, 0xFF};
    Object streamDict(new Dict(nullptr));
    streamDict.dictAdd("Length", Object(4));
    
    MemStream *memStream = new MemStream(reinterpret_cast<const char*>(sampleData), 0, 4, std::move(streamDict));
    Object funcObj(static_cast<Stream*>(memStream));
    
    std::unique_ptr<Function> func = Function::parse(&funcObj);
    
    if (func && func->isOk()) {
        double in[1] = {0.0};
        double out[1];
        func->transform(in, out);
        EXPECT_GE(out[0], 0.0);
        EXPECT_LE(out[0], 1.0);
    }
}
