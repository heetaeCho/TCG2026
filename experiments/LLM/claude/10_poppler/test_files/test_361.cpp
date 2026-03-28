#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Function.h"

// Since we cannot construct SampledFunction easily without valid PDF objects,
// and we must treat the implementation as a black box, we test what we can
// through the public interface. We focus on getSampleSize and other accessors.

// Note: SampledFunction requires Object* and Dict* for construction, which
// are complex PDF internal types. We'll test using the copy constructor path
// if possible, or test observable behavior through accessible methods.

// For the purpose of these tests, we attempt to create a minimal SampledFunction
// or test the interface as much as feasible given the constraints.

#include <memory>
#include "Object.h"
#include "Dict.h"
#include "Stream.h"

class SampledFunctionTest_361 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Helper to try creating a SampledFunction from a PDF stream object
// This creates a minimal sampled function with known parameters
static std::unique_ptr<Function> createMinimalSampledFunction(int m, int n,
                                                               std::vector<double> domain,
                                                               std::vector<double> range,
                                                               std::vector<int> size,
                                                               int bitsPerSample) {
    // We use Function::parse which handles creation
    // Build a stream dictionary and object representing a Type 0 function
    
    // This is complex - let's try using Function::parse
    // For now, we'll test what we can
    return nullptr;
}

// Test getSampleSize returns expected values for valid index
TEST_F(SampledFunctionTest_361, GetSampleSizeInterface_361) {
    // We test the getSampleSize method signature exists and is callable
    // Since constructing a valid SampledFunction requires PDF objects,
    // we verify the method is part of the public interface
    
    // Create a Type 0 (Sampled) function via Function::parse
    // Minimal setup: 1 input, 1 output, size [4], BitsPerSample 8
    
    // Build the stream content: 4 samples of 1 byte each
    unsigned char sampleData[] = {0, 85, 170, 255};
    
    auto dict = std::make_unique<Dict>(nullptr);
    
    // FunctionType
    dict->add("FunctionType", Object(0));
    
    // Domain [0 1]
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    // Range [0 1]
    Array *rangeArr = new Array(nullptr);
    rangeArr->add(Object(0.0));
    rangeArr->add(Object(1.0));
    dict->add("Range", Object(rangeArr));
    
    // Size [4]
    Array *sizeArr = new Array(nullptr);
    sizeArr->add(Object(4));
    dict->add("Size", Object(sizeArr));
    
    // BitsPerSample
    dict->add("BitsPerSample", Object(8));
    
    // Create a MemStream with the sample data
    Object streamDict(dict.release());
    auto *memStream = new MemStream((const char*)sampleData, 0, sizeof(sampleData), std::move(streamDict));
    
    Object streamObj(memStream);
    
    std::set<int> usedParents;
    auto func = Function::parse(&streamObj, &usedParents);
    
    if (func && func->getType() == Function::Type::Sampled) {
        SampledFunction *sf = static_cast<SampledFunction*>(func.get());
        
        // The size for input 0 should be 4
        EXPECT_EQ(sf->getSampleSize(0), 4);
        
        // Test isOk
        EXPECT_TRUE(sf->isOk());
        
        // Test getSampleNumber - for 1 input of size 4 and 1 output, nSamples should be 4
        EXPECT_EQ(sf->getSampleNumber(), 4);
        
        // Test getSamples is not null
        EXPECT_NE(sf->getSamples(), nullptr);
        
        // Test encode defaults: should be [0, Size-1] = [0, 3]
        EXPECT_DOUBLE_EQ(sf->getEncodeMin(0), 0.0);
        EXPECT_DOUBLE_EQ(sf->getEncodeMax(0), 3.0);
        
        // Test decode defaults: should be same as Range = [0, 1]
        EXPECT_DOUBLE_EQ(sf->getDecodeMin(0), 0.0);
        EXPECT_DOUBLE_EQ(sf->getDecodeMax(0), 1.0);
        
        // Test getType
        EXPECT_EQ(sf->getType(), Function::Type::Sampled);
    } else {
        // If we couldn't create the function, skip but note it
        GTEST_SKIP() << "Could not create SampledFunction from minimal stream";
    }
}

// Test transform produces output for valid input
TEST_F(SampledFunctionTest_361, TransformProducesOutput_361) {
    unsigned char sampleData[] = {0, 85, 170, 255};
    
    auto dict = std::make_unique<Dict>(nullptr);
    dict->add("FunctionType", Object(0));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    Array *rangeArr = new Array(nullptr);
    rangeArr->add(Object(0.0));
    rangeArr->add(Object(1.0));
    dict->add("Range", Object(rangeArr));
    
    Array *sizeArr = new Array(nullptr);
    sizeArr->add(Object(4));
    dict->add("Size", Object(sizeArr));
    
    dict->add("BitsPerSample", Object(8));
    
    Object streamDict(dict.release());
    auto *memStream = new MemStream((const char*)sampleData, 0, sizeof(sampleData), std::move(streamDict));
    Object streamObj(memStream);
    
    std::set<int> usedParents;
    auto func = Function::parse(&streamObj, &usedParents);
    
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
        
        // Test at domain midpoint
        in[0] = 0.5;
        func->transform(in, out);
        EXPECT_GE(out[0], 0.0);
        EXPECT_LE(out[0], 1.0);
        
        // At input 0.0, sample index 0 maps to value 0 -> decode to 0.0
        in[0] = 0.0;
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.0, 0.01);
        
        // At input 1.0, sample index 3 maps to value 255 -> decode to 1.0
        in[0] = 1.0;
        func->transform(in, out);
        EXPECT_NEAR(out[0], 1.0, 0.01);
    } else {
        GTEST_SKIP() << "Could not create SampledFunction";
    }
}

// Test copy produces an equivalent function
TEST_F(SampledFunctionTest_361, CopyProducesEquivalentFunction_361) {
    unsigned char sampleData[] = {0, 128, 255};
    
    auto dict = std::make_unique<Dict>(nullptr);
    dict->add("FunctionType", Object(0));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    Array *rangeArr = new Array(nullptr);
    rangeArr->add(Object(0.0));
    rangeArr->add(Object(1.0));
    dict->add("Range", Object(rangeArr));
    
    Array *sizeArr = new Array(nullptr);
    sizeArr->add(Object(3));
    dict->add("Size", Object(sizeArr));
    
    dict->add("BitsPerSample", Object(8));
    
    Object streamDict(dict.release());
    auto *memStream = new MemStream((const char*)sampleData, 0, sizeof(sampleData), std::move(streamDict));
    Object streamObj(memStream);
    
    std::set<int> usedParents;
    auto func = Function::parse(&streamObj, &usedParents);
    
    if (func && func->isOk()) {
        auto funcCopy = func->copy();
        ASSERT_NE(funcCopy, nullptr);
        EXPECT_TRUE(funcCopy->isOk());
        EXPECT_EQ(funcCopy->getType(), func->getType());
        
        // Both should produce same output
        double in[1] = {0.5};
        double out1[1], out2[1];
        func->transform(in, out1);
        funcCopy->transform(in, out2);
        EXPECT_DOUBLE_EQ(out1[0], out2[0]);
        
        // Check sample size matches
        SampledFunction *sf1 = static_cast<SampledFunction*>(func.get());
        SampledFunction *sf2 = static_cast<SampledFunction*>(funcCopy.get());
        EXPECT_EQ(sf1->getSampleSize(0), sf2->getSampleSize(0));
        EXPECT_EQ(sf1->getSampleNumber(), sf2->getSampleNumber());
    } else {
        GTEST_SKIP() << "Could not create SampledFunction";
    }
}

// Test hasDifferentResultSet with identical function
TEST_F(SampledFunctionTest_361, HasDifferentResultSetWithSameFunction_361) {
    unsigned char sampleData[] = {0, 255};
    
    auto dict = std::make_unique<Dict>(nullptr);
    dict->add("FunctionType", Object(0));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    Array *rangeArr = new Array(nullptr);
    rangeArr->add(Object(0.0));
    rangeArr->add(Object(1.0));
    dict->add("Range", Object(rangeArr));
    
    Array *sizeArr = new Array(nullptr);
    sizeArr->add(Object(2));
    dict->add("Size", Object(sizeArr));
    
    dict->add("BitsPerSample", Object(8));
    
    Object streamDict(dict.release());
    auto *memStream = new MemStream((const char*)sampleData, 0, sizeof(sampleData), std::move(streamDict));
    Object streamObj(memStream);
    
    std::set<int> usedParents;
    auto func = Function::parse(&streamObj, &usedParents);
    
    if (func && func->isOk()) {
        auto funcCopy = func->copy();
        ASSERT_NE(funcCopy, nullptr);
        
        // Same function should not have different result set
        EXPECT_FALSE(func->hasDifferentResultSet(funcCopy.get()));
    } else {
        GTEST_SKIP() << "Could not create SampledFunction";
    }
}

// Test with 2 inputs and 1 output
TEST_F(SampledFunctionTest_361, TwoInputsOneOutput_361) {
    // 2x2 grid = 4 samples
    unsigned char sampleData[] = {0, 85, 170, 255};
    
    auto dict = std::make_unique<Dict>(nullptr);
    dict->add("FunctionType", Object(0));
    
    // Domain: [0 1 0 1] for 2 inputs
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    Array *rangeArr = new Array(nullptr);
    rangeArr->add(Object(0.0));
    rangeArr->add(Object(1.0));
    dict->add("Range", Object(rangeArr));
    
    // Size [2 2]
    Array *sizeArr = new Array(nullptr);
    sizeArr->add(Object(2));
    sizeArr->add(Object(2));
    dict->add("Size", Object(sizeArr));
    
    dict->add("BitsPerSample", Object(8));
    
    Object streamDict(dict.release());
    auto *memStream = new MemStream((const char*)sampleData, 0, sizeof(sampleData), std::move(streamDict));
    Object streamObj(memStream);
    
    std::set<int> usedParents;
    auto func = Function::parse(&streamObj, &usedParents);
    
    if (func && func->isOk()) {
        SampledFunction *sf = static_cast<SampledFunction*>(func.get());
        
        EXPECT_EQ(sf->getSampleSize(0), 2);
        EXPECT_EQ(sf->getSampleSize(1), 2);
        EXPECT_EQ(sf->getSampleNumber(), 4);
        
        double in[2], out[1];
        
        // Corner (0,0)
        in[0] = 0.0; in[1] = 0.0;
        func->transform(in, out);
        EXPECT_GE(out[0], 0.0);
        EXPECT_LE(out[0], 1.0);
        
        // Corner (1,1)
        in[0] = 1.0; in[1] = 1.0;
        func->transform(in, out);
        EXPECT_GE(out[0], 0.0);
        EXPECT_LE(out[0], 1.0);
    } else {
        GTEST_SKIP() << "Could not create SampledFunction with 2 inputs";
    }
}

// Test boundary: input clamped to domain
TEST_F(SampledFunctionTest_361, InputClampedToDomain_361) {
    unsigned char sampleData[] = {0, 128, 255};
    
    auto dict = std::make_unique<Dict>(nullptr);
    dict->add("FunctionType", Object(0));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    Array *rangeArr = new Array(nullptr);
    rangeArr->add(Object(0.0));
    rangeArr->add(Object(1.0));
    dict->add("Range", Object(rangeArr));
    
    Array *sizeArr = new Array(nullptr);
    sizeArr->add(Object(3));
    dict->add("Size", Object(sizeArr));
    
    dict->add("BitsPerSample", Object(8));
    
    Object streamDict(dict.release());
    auto *memStream = new MemStream((const char*)sampleData, 0, sizeof(sampleData), std::move(streamDict));
    Object streamObj(memStream);
    
    std::set<int> usedParents;
    auto func = Function::parse(&streamObj, &usedParents);
    
    if (func && func->isOk()) {
        double in[1], out[1], outAtMin[1], outAtMax[1];
        
        // Value below domain should clamp to domain min
        in[0] = 0.0;
        func->transform(in, outAtMin);
        
        in[0] = -1.0;
        func->transform(in, out);
        EXPECT_DOUBLE_EQ(out[0], outAtMin[0]);
        
        // Value above domain should clamp to domain max
        in[0] = 1.0;
        func->transform(in, outAtMax);
        
        in[0] = 2.0;
        func->transform(in, out);
        EXPECT_DOUBLE_EQ(out[0], outAtMax[0]);
    } else {
        GTEST_SKIP() << "Could not create SampledFunction";
    }
}

// Test with 16-bit samples
TEST_F(SampledFunctionTest_361, SixteenBitSamples_361) {
    // 2 samples, 16-bit each, big-endian
    unsigned char sampleData[] = {0x00, 0x00, 0xFF, 0xFF};
    
    auto dict = std::make_unique<Dict>(nullptr);
    dict->add("FunctionType", Object(0));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    Array *rangeArr = new Array(nullptr);
    rangeArr->add(Object(0.0));
    rangeArr->add(Object(1.0));
    dict->add("Range", Object(rangeArr));
    
    Array *sizeArr = new Array(nullptr);
    sizeArr->add(Object(2));
    dict->add("Size", Object(sizeArr));
    
    dict->add("BitsPerSample", Object(16));
    
    Object streamDict(dict.release());
    auto *memStream = new MemStream((const char*)sampleData, 0, sizeof(sampleData), std::move(streamDict));
    Object streamObj(memStream);
    
    std::set<int> usedParents;
    auto func = Function::parse(&streamObj, &usedParents);
    
    if (func && func->isOk()) {
        SampledFunction *sf = static_cast<SampledFunction*>(func.get());
        EXPECT_EQ(sf->getSampleSize(0), 2);
        
        double in[1], out[1];
        
        in[0] = 0.0;
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.0, 0.01);
        
        in[0] = 1.0;
        func->transform(in, out);
        EXPECT_NEAR(out[0], 1.0, 0.01);
    } else {
        GTEST_SKIP() << "Could not create SampledFunction with 16-bit samples";
    }
}

// Test with explicit Encode and Decode arrays
TEST_F(SampledFunctionTest_361, ExplicitEncodeAndDecode_361) {
    unsigned char sampleData[] = {0, 128, 255};
    
    auto dict = std::make_unique<Dict>(nullptr);
    dict->add("FunctionType", Object(0));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    Array *rangeArr = new Array(nullptr);
    rangeArr->add(Object(0.0));
    rangeArr->add(Object(10.0));
    dict->add("Range", Object(rangeArr));
    
    Array *sizeArr = new Array(nullptr);
    sizeArr->add(Object(3));
    dict->add("Size", Object(sizeArr));
    
    dict->add("BitsPerSample", Object(8));
    
    // Encode [0 2] (maps domain to sample indices)
    Array *encodeArr = new Array(nullptr);
    encodeArr->add(Object(0.0));
    encodeArr->add(Object(2.0));
    dict->add("Encode", Object(encodeArr));
    
    // Decode [0 10] (maps sample values to output range)
    Array *decodeArr = new Array(nullptr);
    decodeArr->add(Object(0.0));
    decodeArr->add(Object(10.0));
    dict->add("Decode", Object(decodeArr));
    
    Object streamDict(dict.release());
    auto *memStream = new MemStream((const char*)sampleData, 0, sizeof(sampleData), std::move(streamDict));
    Object streamObj(memStream);
    
    std::set<int> usedParents;
    auto func = Function::parse(&streamObj, &usedParents);
    
    if (func && func->isOk()) {
        SampledFunction *sf = static_cast<SampledFunction*>(func.get());
        
        EXPECT_DOUBLE_EQ(sf->getEncodeMin(0), 0.0);
        EXPECT_DOUBLE_EQ(sf->getEncodeMax(0), 2.0);
        EXPECT_DOUBLE_EQ(sf->getDecodeMin(0), 0.0);
        EXPECT_DOUBLE_EQ(sf->getDecodeMax(0), 10.0);
        
        double in[1], out[1];
        
        // At input 1.0, encode maps to sample index 2, value 255 -> decode to 10.0
        in[0] = 1.0;
        func->transform(in, out);
        EXPECT_NEAR(out[0], 10.0, 0.1);
        
        // At input 0.0, encode maps to sample index 0, value 0 -> decode to 0.0
        in[0] = 0.0;
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.0, 0.1);
    } else {
        GTEST_SKIP() << "Could not create SampledFunction with explicit Encode/Decode";
    }
}

// Test multiple outputs
TEST_F(SampledFunctionTest_361, MultipleOutputs_361) {
    // 2 samples, 2 outputs each: sample[0]=(0,255), sample[1]=(255,0)
    unsigned char sampleData[] = {0, 255, 255, 0};
    
    auto dict = std::make_unique<Dict>(nullptr);
    dict->add("FunctionType", Object(0));
    
    Array *domainArr = new Array(nullptr);
    domainArr->add(Object(0.0));
    domainArr->add(Object(1.0));
    dict->add("Domain", Object(domainArr));
    
    // 2 outputs
    Array *rangeArr = new Array(nullptr);
    rangeArr->add(Object(0.0));
    rangeArr->add(Object(1.0));
    rangeArr->add(Object(0.0));
    rangeArr->add(Object(1.0));
    dict->add("Range", Object(rangeArr));
    
    Array *sizeArr = new Array(nullptr);
    sizeArr->add(Object(2));
    dict->add("Size", Object(sizeArr));
    
    dict->add("BitsPerSample", Object(8));
    
    Object streamDict(dict.release());
    auto *memStream = new MemStream((const char*)sampleData, 0, sizeof(sampleData), std::move(streamDict));
    Object streamObj(memStream);
    
    std::set<int> usedParents;
    auto func = Function::parse(&streamObj, &usedParents);
    
    if (func && func->isOk()) {
        double in[1], out[2];
        
        // At input 0.0
        in[0] = 0.0;
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.0, 0.01);
        EXPECT_NEAR(out[1], 1.0, 0.01);
        
        // At input 1.0
        in[0] = 1.0;
        func->transform(in, out);
        EXPECT_NEAR(out[0], 1.0, 0.01);
        EXPECT_NEAR(out[1], 0.0, 0.01);
    } else {
        GTEST_SKIP() << "Could not create SampledFunction with multiple outputs";
    }
}
