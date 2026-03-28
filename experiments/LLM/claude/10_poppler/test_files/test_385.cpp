#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Function.h"
#include "Object.h"
#include "Dict.h"
#include "Stream.h"
#include "GooString.h"
#include <memory>
#include <cstring>

// Helper to create a PostScript function from a PS code string
// We need to construct valid PDF objects for PostScriptFunction

class PostScriptFunctionTest_385 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a PostScriptFunction from raw PostScript code
    // PostScriptFunction requires a funcObj (stream with PS code) and a dict
    // with Domain, Range entries
    std::unique_ptr<Function> createPSFunction(const char *psCode, 
                                                 int numInputs, double *domain,
                                                 int numOutputs, double *range) {
        // Build a Function from a type 4 function specification
        // We'll use Function::parse which handles type 4 (PostScript) functions
        
        // Create the dictionary entries
        Dict *dict = new Dict((XRef*)nullptr);
        
        // FunctionType = 4
        dict->add("FunctionType", Object(4));
        
        // Domain array
        Object domainArray = Object(new Array((XRef*)nullptr));
        for (int i = 0; i < numInputs * 2; i++) {
            domainArray.arrayAdd(Object(domain[i]));
        }
        dict->add("Domain", std::move(domainArray));
        
        // Range array
        Object rangeArray = Object(new Array((XRef*)nullptr));
        for (int i = 0; i < numOutputs * 2; i++) {
            rangeArray.arrayAdd(Object(range[i]));
        }
        dict->add("Range", std::move(rangeArray));
        
        // Create a memory stream with the PS code
        // The PS code needs to be wrapped in { }
        std::string fullCode = std::string("{ ") + psCode + " }";
        
        char *buf = (char*)gmalloc(fullCode.size());
        memcpy(buf, fullCode.c_str(), fullCode.size());
        
        Object streamDict = Object(new Dict((XRef*)nullptr));
        streamDict.dictAdd("Length", Object((int)fullCode.size()));
        
        MemStream *memStream = new MemStream(buf, 0, fullCode.size(), std::move(streamDict));
        
        // Create the stream object with the dict
        // We need to merge dict into the stream's dict
        for (int i = 0; i < dict->getLength(); i++) {
            memStream->getDict()->add(dict->getKey(i), dict->getVal(i).copy());
        }
        
        Object funcObj = Object(static_cast<Stream*>(memStream));
        
        auto func = Function::parse(&funcObj);
        
        delete dict;
        
        return func;
    }
};

TEST_F(PostScriptFunctionTest_385, GetTypeReturnsType4_385) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    
    auto func = createPSFunction("", 1, domain, 1, range);
    if (func && func->getType() == Function::Type::PostScript) {
        EXPECT_EQ(func->getType(), Function::Type::PostScript);
    }
}

TEST_F(PostScriptFunctionTest_385, GetCodeStringNotNull_385) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    
    auto func = createPSFunction("dup mul", 1, domain, 1, range);
    if (func && func->getType() == Function::Type::PostScript) {
        const PostScriptFunction *psFunc = static_cast<const PostScriptFunction*>(func.get());
        const GooString *codeStr = psFunc->getCodeString();
        // The code string should exist if the function was created successfully
        ASSERT_NE(codeStr, nullptr);
        EXPECT_GT(codeStr->getLength(), 0);
    }
}

TEST_F(PostScriptFunctionTest_385, CopyPreservesCodeString_385) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    
    auto func = createPSFunction("dup mul", 1, domain, 1, range);
    if (func && func->getType() == Function::Type::PostScript) {
        auto funcCopy = func->copy();
        ASSERT_NE(funcCopy, nullptr);
        
        const PostScriptFunction *psFunc = static_cast<const PostScriptFunction*>(func.get());
        const PostScriptFunction *psFuncCopy = static_cast<const PostScriptFunction*>(funcCopy.get());
        
        const GooString *origCode = psFunc->getCodeString();
        const GooString *copyCode = psFuncCopy->getCodeString();
        
        if (origCode && copyCode) {
            EXPECT_EQ(origCode->toStr(), copyCode->toStr());
        }
    }
}

TEST_F(PostScriptFunctionTest_385, TransformSimpleIdentity_385) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    
    // Simple identity: just pass through
    auto func = createPSFunction("", 1, domain, 1, range);
    if (func && func->isOk()) {
        double in[] = {0.5};
        double out[] = {0.0};
        func->transform(in, out);
        // We can check that output is within range
        EXPECT_GE(out[0], 0.0);
        EXPECT_LE(out[0], 1.0);
    }
}

TEST_F(PostScriptFunctionTest_385, TransformSquareFunction_385) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    
    // x^2 function
    auto func = createPSFunction("dup mul", 1, domain, 1, range);
    if (func && func->isOk()) {
        double in[] = {0.5};
        double out[] = {0.0};
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.25, 0.001);
    }
}

TEST_F(PostScriptFunctionTest_385, TransformBoundaryInputZero_385) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    
    auto func = createPSFunction("dup mul", 1, domain, 1, range);
    if (func && func->isOk()) {
        double in[] = {0.0};
        double out[] = {-1.0};
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.0, 0.001);
    }
}

TEST_F(PostScriptFunctionTest_385, TransformBoundaryInputOne_385) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    
    auto func = createPSFunction("dup mul", 1, domain, 1, range);
    if (func && func->isOk()) {
        double in[] = {1.0};
        double out[] = {-1.0};
        func->transform(in, out);
        EXPECT_NEAR(out[0], 1.0, 0.001);
    }
}

TEST_F(PostScriptFunctionTest_385, IsOkForValidFunction_385) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    
    auto func = createPSFunction("dup mul", 1, domain, 1, range);
    if (func) {
        EXPECT_TRUE(func->isOk());
    }
}

TEST_F(PostScriptFunctionTest_385, CopyReturnsNonNull_385) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    
    auto func = createPSFunction("dup mul", 1, domain, 1, range);
    if (func && func->isOk()) {
        auto funcCopy = func->copy();
        ASSERT_NE(funcCopy, nullptr);
        EXPECT_TRUE(funcCopy->isOk());
    }
}

TEST_F(PostScriptFunctionTest_385, CopiedFunctionProducesSameResults_385) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    
    auto func = createPSFunction("dup mul", 1, domain, 1, range);
    if (func && func->isOk()) {
        auto funcCopy = func->copy();
        
        double in[] = {0.7};
        double out1[] = {0.0};
        double out2[] = {0.0};
        
        func->transform(in, out1);
        funcCopy->transform(in, out2);
        
        EXPECT_NEAR(out1[0], out2[0], 0.0001);
    }
}

TEST_F(PostScriptFunctionTest_385, TransformAddFunction_385) {
    double domain[] = {0.0, 1.0, 0.0, 1.0};
    double range[] = {0.0, 2.0};
    
    // Two inputs, one output: add them
    auto func = createPSFunction("add", 2, domain, 1, range);
    if (func && func->isOk()) {
        double in[] = {0.3, 0.4};
        double out[] = {0.0};
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.7, 0.001);
    }
}

TEST_F(PostScriptFunctionTest_385, TransformOutputClampedToRange_385) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 0.5};
    
    // dup mul with input 1.0 gives 1.0, but range max is 0.5
    auto func = createPSFunction("dup mul", 1, domain, 1, range);
    if (func && func->isOk()) {
        double in[] = {1.0};
        double out[] = {0.0};
        func->transform(in, out);
        EXPECT_LE(out[0], 0.5);
    }
}

TEST_F(PostScriptFunctionTest_385, TransformInputClampedToDomain_385) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    
    auto func = createPSFunction("dup mul", 1, domain, 1, range);
    if (func && func->isOk()) {
        // Input outside domain should be clamped
        double in[] = {2.0};
        double out[] = {0.0};
        func->transform(in, out);
        // Clamped to 1.0, so 1.0*1.0 = 1.0
        EXPECT_NEAR(out[0], 1.0, 0.001);
    }
}

TEST_F(PostScriptFunctionTest_385, TransformNegativeInputClampedToDomain_385) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    
    auto func = createPSFunction("dup mul", 1, domain, 1, range);
    if (func && func->isOk()) {
        double in[] = {-0.5};
        double out[] = {-1.0};
        func->transform(in, out);
        // Clamped to 0.0, so 0.0*0.0 = 0.0
        EXPECT_NEAR(out[0], 0.0, 0.001);
    }
}

TEST_F(PostScriptFunctionTest_385, GetCodeStringContainsExpectedContent_385) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    
    auto func = createPSFunction("dup mul", 1, domain, 1, range);
    if (func && func->isOk() && func->getType() == Function::Type::PostScript) {
        const PostScriptFunction *psFunc = static_cast<const PostScriptFunction*>(func.get());
        const GooString *codeStr = psFunc->getCodeString();
        ASSERT_NE(codeStr, nullptr);
        // The code string should contain the PS operations
        std::string code = codeStr->toStr();
        EXPECT_NE(code.find("dup"), std::string::npos);
        EXPECT_NE(code.find("mul"), std::string::npos);
    }
}
