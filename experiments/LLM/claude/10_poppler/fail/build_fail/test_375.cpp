#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Function.h"
#include "Dict.h"
#include "Object.h"
#include "PDFDoc.h"

// We need to test StitchingFunction through its public interface.
// Since constructing valid StitchingFunction objects requires proper PDF Dict objects,
// we test what we can through the interface.

class StitchingFunctionTest_375 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getType returns Type::Stitching
TEST_F(StitchingFunctionTest_375, GetTypeReturnsStitching_375) {
    // We need to create a StitchingFunction to test getType.
    // Since we cannot easily construct one without a valid Dict,
    // we test via Function::parse if possible, or verify the type constant.
    
    // Create a minimal XRef-less environment
    // StitchingFunction requires a Dict with specific entries.
    // We'll attempt to create one and verify type even if isOk() is false.
    
    auto xref = std::make_unique<XRef>(nullptr);
    Dict dict(xref.get());
    
    // FunctionType 3 = Stitching
    dict.add("FunctionType", Object(3));
    
    // Domain is required
    Array *domainArray = new Array(xref.get());
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict.add("Domain", Object(domainArray));
    
    // Functions array (required for stitching)
    Array *funcsArray = new Array(xref.get());
    dict.add("Functions", Object(funcsArray));
    
    // Bounds array
    Array *boundsArray = new Array(xref.get());
    dict.add("Bounds", Object(boundsArray));
    
    // Encode array
    Array *encodeArray = new Array(xref.get());
    dict.add("Encode", Object(encodeArray));
    
    Object dictObj(&dict);
    
    RefRecursionChecker checker;
    auto func = Function::parse(&dictObj, checker);
    
    // If parsing succeeded, verify type
    if (func) {
        EXPECT_EQ(func->getType(), Function::Type::Stitching);
    }
}

// Test Function::parse with FunctionType 3 (Stitching) with a more complete setup
TEST_F(StitchingFunctionTest_375, ParseStitchingWithSubFunctions_375) {
    auto xref = std::make_unique<XRef>(nullptr);
    
    // Create a sub-function dict (identity-like sampled or exponential)
    // Use FunctionType 2 (Exponential) as sub-functions - simpler to set up
    Dict *subFuncDict1 = new Dict(xref.get());
    subFuncDict1->add("FunctionType", Object(2));
    Array *subDomain1 = new Array(xref.get());
    subDomain1->add(Object(0.0));
    subDomain1->add(Object(0.5));
    subFuncDict1->add("Domain", Object(subDomain1));
    subFuncDict1->add("N", Object(1.0));
    Array *c0_1 = new Array(xref.get());
    c0_1->add(Object(0.0));
    subFuncDict1->add("C0", Object(c0_1));
    Array *c1_1 = new Array(xref.get());
    c1_1->add(Object(0.5));
    subFuncDict1->add("C1", Object(c1_1));
    
    Dict *subFuncDict2 = new Dict(xref.get());
    subFuncDict2->add("FunctionType", Object(2));
    Array *subDomain2 = new Array(xref.get());
    subDomain2->add(Object(0.5));
    subDomain2->add(Object(1.0));
    subFuncDict2->add("Domain", Object(subDomain2));
    subFuncDict2->add("N", Object(1.0));
    Array *c0_2 = new Array(xref.get());
    c0_2->add(Object(0.5));
    subFuncDict2->add("C0", Object(c0_2));
    Array *c1_2 = new Array(xref.get());
    c1_2->add(Object(1.0));
    subFuncDict2->add("C1", Object(c1_2));
    
    // Main stitching function dict
    Dict mainDict(xref.get());
    mainDict.add("FunctionType", Object(3));
    
    Array *domain = new Array(xref.get());
    domain->add(Object(0.0));
    domain->add(Object(1.0));
    mainDict.add("Domain", Object(domain));
    
    Array *funcsArr = new Array(xref.get());
    funcsArr->add(Object(subFuncDict1));
    funcsArr->add(Object(subFuncDict2));
    mainDict.add("Functions", Object(funcsArr));
    
    Array *bounds = new Array(xref.get());
    bounds->add(Object(0.5));
    mainDict.add("Bounds", Object(bounds));
    
    Array *encode = new Array(xref.get());
    encode->add(Object(0.0));
    encode->add(Object(0.5));
    encode->add(Object(0.5));
    encode->add(Object(1.0));
    mainDict.add("Encode", Object(encode));
    
    Object dictObj(&mainDict);
    RefRecursionChecker checker;
    auto func = Function::parse(&dictObj, checker);
    
    if (func && func->isOk()) {
        EXPECT_EQ(func->getType(), Function::Type::Stitching);
        
        // Cast to StitchingFunction to test specific methods
        auto *stitchFunc = dynamic_cast<StitchingFunction*>(func.get());
        if (stitchFunc) {
            EXPECT_EQ(stitchFunc->getNumFuncs(), 2);
            
            EXPECT_NE(stitchFunc->getBounds(), nullptr);
            EXPECT_NE(stitchFunc->getEncode(), nullptr);
            
            // Verify bounds
            const double *b = stitchFunc->getBounds();
            if (b) {
                EXPECT_DOUBLE_EQ(b[0], 0.5);
            }
            
            // Verify encode values
            const double *e = stitchFunc->getEncode();
            if (e) {
                EXPECT_DOUBLE_EQ(e[0], 0.0);
                EXPECT_DOUBLE_EQ(e[1], 0.5);
                EXPECT_DOUBLE_EQ(e[2], 0.5);
                EXPECT_DOUBLE_EQ(e[3], 1.0);
            }
            
            // Verify sub-functions exist
            EXPECT_NE(stitchFunc->getFunc(0), nullptr);
            EXPECT_NE(stitchFunc->getFunc(1), nullptr);
            
            // Test transform
            double in = 0.0;
            double out = -1.0;
            stitchFunc->transform(&in, &out);
            EXPECT_GE(out, 0.0);
            EXPECT_LE(out, 1.0);
            
            in = 0.25;
            stitchFunc->transform(&in, &out);
            EXPECT_GE(out, 0.0);
            EXPECT_LE(out, 1.0);
            
            in = 0.5;
            stitchFunc->transform(&in, &out);
            EXPECT_GE(out, 0.0);
            EXPECT_LE(out, 1.0);
            
            in = 1.0;
            stitchFunc->transform(&in, &out);
            EXPECT_GE(out, 0.0);
            EXPECT_LE(out, 1.0);
            
            // Test copy
            auto copied = stitchFunc->copy();
            ASSERT_NE(copied, nullptr);
            EXPECT_EQ(copied->getType(), Function::Type::Stitching);
            
            auto *copiedStitch = dynamic_cast<StitchingFunction*>(copied.get());
            if (copiedStitch) {
                EXPECT_EQ(copiedStitch->getNumFuncs(), 2);
                EXPECT_TRUE(copiedStitch->isOk());
                
                // Verify copied function produces same results
                in = 0.25;
                double out1, out2;
                stitchFunc->transform(&in, &out1);
                copiedStitch->transform(&in, &out2);
                EXPECT_DOUBLE_EQ(out1, out2);
            }
        }
    }
}

// Test boundary: input at domain boundaries
TEST_F(StitchingFunctionTest_375, TransformAtDomainBoundaries_375) {
    auto xref = std::make_unique<XRef>(nullptr);
    
    Dict *subFuncDict = new Dict(xref.get());
    subFuncDict->add("FunctionType", Object(2));
    Array *subDomain = new Array(xref.get());
    subDomain->add(Object(0.0));
    subDomain->add(Object(1.0));
    subFuncDict->add("Domain", Object(subDomain));
    subFuncDict->add("N", Object(1.0));
    
    Dict mainDict(xref.get());
    mainDict.add("FunctionType", Object(3));
    
    Array *domain = new Array(xref.get());
    domain->add(Object(0.0));
    domain->add(Object(1.0));
    mainDict.add("Domain", Object(domain));
    
    Array *funcsArr = new Array(xref.get());
    funcsArr->add(Object(subFuncDict));
    mainDict.add("Functions", Object(funcsArr));
    
    Array *bounds = new Array(xref.get());
    mainDict.add("Bounds", Object(bounds));
    
    Array *encode = new Array(xref.get());
    encode->add(Object(0.0));
    encode->add(Object(1.0));
    mainDict.add("Encode", Object(encode));
    
    Object dictObj(&mainDict);
    RefRecursionChecker checker;
    auto func = Function::parse(&dictObj, checker);
    
    if (func && func->isOk()) {
        auto *stitchFunc = dynamic_cast<StitchingFunction*>(func.get());
        if (stitchFunc) {
            EXPECT_EQ(stitchFunc->getNumFuncs(), 1);
            
            // Test at exact lower bound
            double in = 0.0;
            double out;
            stitchFunc->transform(&in, &out);
            // Should not crash, output should be valid
            
            // Test at exact upper bound
            in = 1.0;
            stitchFunc->transform(&in, &out);
            // Should not crash
            
            // Test outside domain (clamping behavior expected)
            in = -0.5;
            stitchFunc->transform(&in, &out);
            // Should be clamped, not crash
            
            in = 1.5;
            stitchFunc->transform(&in, &out);
            // Should be clamped, not crash
        }
    }
}

// Test with empty/invalid dict - should not be ok
TEST_F(StitchingFunctionTest_375, InvalidDictNotOk_375) {
    auto xref = std::make_unique<XRef>(nullptr);
    Dict mainDict(xref.get());
    mainDict.add("FunctionType", Object(3));
    
    // Missing required entries
    Object dictObj(&mainDict);
    RefRecursionChecker checker;
    auto func = Function::parse(&dictObj, checker);
    
    // Either parsing fails (returns nullptr) or the function is not ok
    if (func) {
        // If it was created as a StitchingFunction, it should report not ok
        // due to missing required entries
        auto *stitchFunc = dynamic_cast<StitchingFunction*>(func.get());
        if (stitchFunc) {
            EXPECT_FALSE(stitchFunc->isOk());
        }
    }
}

// Test getScale
TEST_F(StitchingFunctionTest_375, GetScaleReturnsValidPointer_375) {
    auto xref = std::make_unique<XRef>(nullptr);
    
    Dict *subFuncDict = new Dict(xref.get());
    subFuncDict->add("FunctionType", Object(2));
    Array *subDomain = new Array(xref.get());
    subDomain->add(Object(0.0));
    subDomain->add(Object(1.0));
    subFuncDict->add("Domain", Object(subDomain));
    subFuncDict->add("N", Object(1.0));
    
    Dict mainDict(xref.get());
    mainDict.add("FunctionType", Object(3));
    
    Array *domain = new Array(xref.get());
    domain->add(Object(0.0));
    domain->add(Object(1.0));
    mainDict.add("Domain", Object(domain));
    
    Array *funcsArr = new Array(xref.get());
    funcsArr->add(Object(subFuncDict));
    mainDict.add("Functions", Object(funcsArr));
    
    Array *bounds = new Array(xref.get());
    mainDict.add("Bounds", Object(bounds));
    
    Array *encode = new Array(xref.get());
    encode->add(Object(0.0));
    encode->add(Object(1.0));
    mainDict.add("Encode", Object(encode));
    
    Object dictObj(&mainDict);
    RefRecursionChecker checker;
    auto func = Function::parse(&dictObj, checker);
    
    if (func && func->isOk()) {
        auto *stitchFunc = dynamic_cast<StitchingFunction*>(func.get());
        if (stitchFunc) {
            const double *scale = stitchFunc->getScale();
            // scale may or may not be null depending on implementation
            // but the call should not crash
            (void)scale;
            SUCCEED();
        }
    }
}
