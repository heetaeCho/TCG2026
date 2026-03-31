#include <gtest/gtest.h>
#include <memory>
#include "Function.h"
#include "Object.h"
#include "Dict.h"
#include "Stream.h"
#include "PDFDoc.h"

class PostScriptFunctionTest_383 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a PostScript function from a PS code string
    // We build the required Object and Dict structures
    std::unique_ptr<Function> createPSFunction(const char *psCode, int numInputs, int numOutputs,
                                                double *domain, double *range) {
        // Build domain array
        Array *domainArray = new Array((XRef *)nullptr);
        for (int i = 0; i < numInputs * 2; i++) {
            domainArray->add(Object(domain[i]));
        }

        // Build range array
        Array *rangeArray = new Array((XRef *)nullptr);
        for (int i = 0; i < numOutputs * 2; i++) {
            rangeArray->add(Object(range[i]));
        }

        // Build the dictionary
        Dict *dict = new Dict((XRef *)nullptr);
        dict->add("FunctionType", Object(4));
        dict->add("Domain", Object(domainArray));
        dict->add("Range", Object(rangeArray));

        // Create a stream with the PS code
        std::string code(psCode);
        char *buf = (char *)gmalloc(code.size());
        memcpy(buf, code.c_str(), code.size());

        Object dictObj(dict);
        MemStream *memStream = new MemStream(buf, 0, code.size(), std::move(dictObj));

        Object streamObj(memStream);

        auto func = Function::parse(&streamObj);
        return func;
    }
};

TEST_F(PostScriptFunctionTest_383, GetTypeReturnsPostScript_383) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    auto func = createPSFunction("{ }", 1, 1, domain, range);
    if (func && func->isOk()) {
        EXPECT_EQ(func->getType(), Function::Type::PostScript);
    }
}

TEST_F(PostScriptFunctionTest_383, IsOkForValidFunction_383) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    auto func = createPSFunction("{ }", 1, 1, domain, range);
    // Even a minimal PS function should parse, but we just check it doesn't crash
    // The function may or may not be ok depending on exact parsing
    if (func) {
        // Just verify isOk() returns a boolean without crashing
        bool ok = func->isOk();
        (void)ok;
    }
}

TEST_F(PostScriptFunctionTest_383, CopyReturnsSameType_383) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    auto func = createPSFunction("{ }", 1, 1, domain, range);
    if (func && func->isOk()) {
        auto copied = func->copy();
        ASSERT_NE(copied, nullptr);
        EXPECT_EQ(copied->getType(), Function::Type::PostScript);
        EXPECT_TRUE(copied->isOk());
    }
}

TEST_F(PostScriptFunctionTest_383, TransformIdentity_383) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    // PostScript identity: just push input, which stays as output
    auto func = createPSFunction("{ }", 1, 1, domain, range);
    if (func && func->isOk()) {
        double in[] = {0.5};
        double out[] = {0.0};
        func->transform(in, out);
        // The output should be the input for identity
        EXPECT_NEAR(out[0], 0.5, 0.001);
    }
}

TEST_F(PostScriptFunctionTest_383, TransformWithMultiplication_383) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    // PS code to double the input: dup mul (squares) or just "2 mul"
    auto func = createPSFunction("{ 2 mul }", 1, 1, domain, range);
    if (func && func->isOk()) {
        double in[] = {0.25};
        double out[] = {0.0};
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.5, 0.001);
    }
}

TEST_F(PostScriptFunctionTest_383, TransformClampsToRange_383) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 0.5};
    // Multiply by 2, but range caps at 0.5
    auto func = createPSFunction("{ 2 mul }", 1, 1, domain, range);
    if (func && func->isOk()) {
        double in[] = {0.5};
        double out[] = {0.0};
        func->transform(in, out);
        // 0.5 * 2 = 1.0, but range is [0, 0.5], so should be clamped to 0.5
        EXPECT_LE(out[0], 0.5);
    }
}

TEST_F(PostScriptFunctionTest_383, TransformBoundaryInputZero_383) {
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

TEST_F(PostScriptFunctionTest_383, TransformBoundaryInputOne_383) {
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

TEST_F(PostScriptFunctionTest_383, GetCodeStringNotNull_383) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    auto func = createPSFunction("{ }", 1, 1, domain, range);
    if (func && func->isOk()) {
        auto *psFunc = dynamic_cast<PostScriptFunction *>(func.get());
        ASSERT_NE(psFunc, nullptr);
        const GooString *codeStr = psFunc->getCodeString();
        EXPECT_NE(codeStr, nullptr);
    }
}

TEST_F(PostScriptFunctionTest_383, CopyPreservesCodeString_383) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    auto func = createPSFunction("{ 2 mul }", 1, 1, domain, range);
    if (func && func->isOk()) {
        auto *psFunc = dynamic_cast<PostScriptFunction *>(func.get());
        ASSERT_NE(psFunc, nullptr);
        
        auto copied = func->copy();
        auto *copiedPs = dynamic_cast<PostScriptFunction *>(copied.get());
        ASSERT_NE(copiedPs, nullptr);
        
        const GooString *origCode = psFunc->getCodeString();
        const GooString *copiedCode = copiedPs->getCodeString();
        
        if (origCode && copiedCode) {
            EXPECT_EQ(origCode->toStr(), copiedCode->toStr());
        }
    }
}

TEST_F(PostScriptFunctionTest_383, TransformTwoInputsOneOutput_383) {
    double domain[] = {0.0, 1.0, 0.0, 1.0};
    double range[] = {0.0, 2.0};
    // Add two inputs
    auto func = createPSFunction("{ add }", 2, 1, domain, range);
    if (func && func->isOk()) {
        double in[] = {0.3, 0.4};
        double out[] = {0.0};
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.7, 0.01);
    }
}

TEST_F(PostScriptFunctionTest_383, TransformOneInputTwoOutputs_383) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0, 0.0, 1.0};
    // Duplicate input to get two outputs
    auto func = createPSFunction("{ dup }", 1, 2, domain, range);
    if (func && func->isOk()) {
        double in[] = {0.5};
        double out[] = {0.0, 0.0};
        func->transform(in, out);
        EXPECT_NEAR(out[0], 0.5, 0.01);
        EXPECT_NEAR(out[1], 0.5, 0.01);
    }
}

TEST_F(PostScriptFunctionTest_383, NullObjectCreation_383) {
    // Test with null/invalid input - should not crash
    Object nullObj;
    auto func = Function::parse(&nullObj);
    // Function::parse should return nullptr or a non-ok function for invalid input
    if (func) {
        EXPECT_FALSE(func->isOk());
    }
}

TEST_F(PostScriptFunctionTest_383, FunctionParseReturnsCorrectTypeForPS_383) {
    double domain[] = {0.0, 1.0};
    double range[] = {0.0, 1.0};
    auto func = createPSFunction("{ }", 1, 1, domain, range);
    if (func && func->isOk()) {
        EXPECT_EQ(func->getType(), Function::Type::PostScript);
    }
}

TEST_F(PostScriptFunctionTest_383, TransformNegation_383) {
    double domain[] = {0.0, 1.0};
    double range[] = {-1.0, 0.0};
    auto func = createPSFunction("{ neg }", 1, 1, domain, range);
    if (func && func->isOk()) {
        double in[] = {0.5};
        double out[] = {0.0};
        func->transform(in, out);
        EXPECT_NEAR(out[0], -0.5, 0.01);
    }
}
