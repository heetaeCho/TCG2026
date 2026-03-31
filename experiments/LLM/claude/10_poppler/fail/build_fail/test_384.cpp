#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Function.h"
#include "Object.h"
#include "Dict.h"
#include "Stream.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>
#include <cmath>

class PostScriptFunctionTest_384 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a PostScriptFunction from a PostScript code string
    // We build an Object that represents a Type 4 function dictionary + stream
    std::unique_ptr<Function> createPSFunction(const char *psCode,
                                                int nInputs, int nOutputs,
                                                double *domainArr, double *rangeArr) {
        // Build domain array
        Array *domainArray = new Array((XRef*)nullptr);
        for (int i = 0; i < nInputs * 2; i++) {
            domainArray->add(Object(domainArr[i]));
        }

        // Build range array
        Array *rangeArray = new Array((XRef*)nullptr);
        for (int i = 0; i < nOutputs * 2; i++) {
            rangeArray->add(Object(rangeArr[i]));
        }

        // Build the dictionary
        Dict *dict = new Dict((XRef*)nullptr);
        dict->add("FunctionType", Object(4));
        dict->add("Domain", Object(domainArray));
        dict->add("Range", Object(rangeArray));

        // Create a memory stream with the PS code
        const int codeLen = strlen(psCode);
        char *codeBuf = (char *)gmalloc(codeLen + 1);
        memcpy(codeBuf, psCode, codeLen + 1);

        Object streamDictObj(new Dict((XRef*)nullptr));
        streamDictObj.getDict()->add("Length", Object(codeLen));

        Stream *baseStream = new AutoFreeMemStream(codeBuf, 0, codeLen, std::move(streamDictObj));

        Object streamObj(baseStream);
        // Copy dict entries into stream's dict
        baseStream->getDict()->add("FunctionType", Object(4));
        baseStream->getDict()->add("Domain", Object(domainArray->copy()));
        baseStream->getDict()->add("Range", Object(rangeArray->copy()));

        auto func = Function::parse(&streamObj);
        return func;
    }
};

// Test that a simple identity-like PostScript function is ok
TEST_F(PostScriptFunctionTest_384, SimpleIdentityFunction_IsOk_384) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    auto func = createPSFunction("{ }", 1, 1, domain, range);
    if (func) {
        EXPECT_TRUE(func->isOk());
    }
}

// Test getType returns PostScript type (Type 4)
TEST_F(PostScriptFunctionTest_384, GetType_ReturnsPostScript_384) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    auto func = createPSFunction("{ }", 1, 1, domain, range);
    if (func) {
        EXPECT_EQ(func->getType(), Function::Type::PostScript);
    }
}

// Test transform with a simple pass-through function
TEST_F(PostScriptFunctionTest_384, Transform_PassThrough_384) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    auto func = createPSFunction("{ }", 1, 1, domain, range);
    if (func && func->isOk()) {
        double in[] = {0.5};
        double out[] = {0.0};
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.5, 0.001);
    }
}

// Test transform with boundary input value 0
TEST_F(PostScriptFunctionTest_384, Transform_BoundaryZero_384) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    auto func = createPSFunction("{ }", 1, 1, domain, range);
    if (func && func->isOk()) {
        double in[] = {0.0};
        double out[] = {-1.0};
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.0, 0.001);
    }
}

// Test transform with boundary input value 1
TEST_F(PostScriptFunctionTest_384, Transform_BoundaryOne_384) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    auto func = createPSFunction("{ }", 1, 1, domain, range);
    if (func && func->isOk()) {
        double in[] = {1.0};
        double out[] = {-1.0};
        func->transform(in, out);
        EXPECT_NEAR(out[0], 1.0, 0.001);
    }
}

// Test transform with multiplication operation
TEST_F(PostScriptFunctionTest_384, Transform_Multiply_384) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    auto func = createPSFunction("{ 2 mul }", 1, 1, domain, range);
    if (func && func->isOk()) {
        double in[] = {0.25};
        double out[] = {0.0};
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.5, 0.001);
    }
}

// Test that output is clamped to range
TEST_F(PostScriptFunctionTest_384, Transform_OutputClampedToRange_384) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    auto func = createPSFunction("{ 3 mul }", 1, 1, domain, range);
    if (func && func->isOk()) {
        double in[] = {0.5};
        double out[] = {0.0};
        func->transform(in, out);
        // 0.5 * 3 = 1.5, should be clamped to 1.0
        EXPECT_LE(out[0], 1.0);
    }
}

// Test input clamped to domain
TEST_F(PostScriptFunctionTest_384, Transform_InputClampedToDomain_384) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    auto func = createPSFunction("{ }", 1, 1, domain, range);
    if (func && func->isOk()) {
        double in[] = {2.0};
        double out[] = {0.0};
        func->transform(in, out);
        // Input 2.0 should be clamped to domain max 1.0
        EXPECT_NEAR(out[0], 1.0, 0.001);
    }
}

// Test input below domain minimum is clamped
TEST_F(PostScriptFunctionTest_384, Transform_InputBelowDomainClamped_384) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    auto func = createPSFunction("{ }", 1, 1, domain, range);
    if (func && func->isOk()) {
        double in[] = {-1.0};
        double out[] = {-1.0};
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.0, 0.001);
    }
}

// Test copy creates a working copy
TEST_F(PostScriptFunctionTest_384, Copy_CreatesWorkingCopy_384) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    auto func = createPSFunction("{ }", 1, 1, domain, range);
    if (func && func->isOk()) {
        auto funcCopy = func->copy();
        ASSERT_NE(funcCopy, nullptr);
        EXPECT_TRUE(funcCopy->isOk());

        double in[] = {0.5};
        double out1[] = {0.0};
        double out2[] = {0.0};
        func->transform(in, out1);
        funcCopy->transform(in, out2);
        EXPECT_NEAR(out1[0], out2[0], 0.001);
    }
}

// Test copy preserves type
TEST_F(PostScriptFunctionTest_384, Copy_PreservesType_384) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    auto func = createPSFunction("{ }", 1, 1, domain, range);
    if (func && func->isOk()) {
        auto funcCopy = func->copy();
        ASSERT_NE(funcCopy, nullptr);
        EXPECT_EQ(funcCopy->getType(), func->getType());
    }
}

// Test getCodeString returns non-null for valid function
TEST_F(PostScriptFunctionTest_384, GetCodeString_NonNull_384) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    auto func = createPSFunction("{ }", 1, 1, domain, range);
    if (func && func->isOk()) {
        auto *psFunc = dynamic_cast<PostScriptFunction*>(func.get());
        if (psFunc) {
            const GooString *codeStr = psFunc->getCodeString();
            EXPECT_NE(codeStr, nullptr);
        }
    }
}

// Test with addition operation
TEST_F(PostScriptFunctionTest_384, Transform_Addition_384) {
    double domain[] = {0.0, 1.0, 0.0, 1.0};
    double range[] = {0.0, 2.0};
    auto func = createPSFunction("{ add }", 2, 1, domain, range);
    if (func && func->isOk()) {
        double in[] = {0.3, 0.4};
        double out[] = {0.0};
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.7, 0.01);
    }
}

// Test with dup operation
TEST_F(PostScriptFunctionTest_384, Transform_DupMul_384) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    auto func = createPSFunction("{ dup mul }", 1, 1, domain, range);
    if (func && func->isOk()) {
        double in[] = {0.5};
        double out[] = {0.0};
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.25, 0.001);
    }
}

// Test with negative range
TEST_F(PostScriptFunctionTest_384, Transform_NegativeRange_384) {
    double domain[] = {0.0, 1.0};
    double range[] = {-1.0, 1.0};
    auto func = createPSFunction("{ 2 mul 1 sub }", 1, 1, domain, range);
    if (func && func->isOk()) {
        double in[] = {0.0};
        double out[] = {0.0};
        func->transform(in, out);
        EXPECT_NEAR(out[0], -1.0, 0.01);
    }
}

// Test multiple outputs
TEST_F(PostScriptFunctionTest_384, Transform_MultipleOutputs_384) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0, 0.0, 1.0};
    auto func = createPSFunction("{ dup }", 1, 2, domain, range);
    if (func && func->isOk()) {
        double in[] = {0.7};
        double out[] = {0.0, 0.0};
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.7, 0.001);
        EXPECT_NEAR(out[1], 0.7, 0.001);
    }
}

// Test getDomainSize
TEST_F(PostScriptFunctionTest_384, GetDomainSize_384) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    auto func = createPSFunction("{ }", 1, 1, domain, range);
    if (func && func->isOk()) {
        EXPECT_GE(func->getInputSize(), 1);
    }
}

// Test Function::parse returns nullptr for invalid object
TEST_F(PostScriptFunctionTest_384, Parse_InvalidObject_ReturnsNull_384) {
    Object nullObj;
    auto func = Function::parse(&nullObj);
    EXPECT_EQ(func, nullptr);
}
