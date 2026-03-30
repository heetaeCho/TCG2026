// TEST_ID: 368
//
// Unit tests for ExponentialFunction::copy()
// File under test: ./TestProjects/poppler/poppler/Function.h

#include <gtest/gtest.h>

#include "poppler/Function.h"
#include "poppler/Object.h"

namespace {

// Helper to build a minimal FunctionType 2 (Exponential) dictionary.
// This is constructed only via public Poppler types and the public ExponentialFunction(Dict*) ctor.
Dict *makeExpFuncDict(int nOutputs,
                      double domainMin,
                      double domainMax,
                      double c0Base,
                      double c1Base,
                      double exponentN,
                      bool includeAllRequiredKeys = true)
{
    // Dict/XRef ownership patterns vary across Poppler versions; the tests keep it simple and
    // rely only on heap allocation that Poppler objects typically manage via Object wrappers.
    auto *dict = new Dict(nullptr);

    if (!includeAllRequiredKeys) {
        // Intentionally under-specified dict to exercise "error/exceptional" construction paths.
        // (We do NOT assume what is required; we only assert observable behavior via isOk()/copy().)
        dict->add("FunctionType", Object(objInt, 2));
        return dict;
    }

    dict->add("FunctionType", Object(objInt, 2));

    // Domain: [domainMin domainMax]
    {
        auto *arr = new Array(nullptr);
        arr->add(Object(objReal, domainMin));
        arr->add(Object(objReal, domainMax));
        dict->add("Domain", Object(objArray, arr));
    }

    // C0: array of length nOutputs
    {
        auto *arr = new Array(nullptr);
        for (int i = 0; i < nOutputs; ++i) {
            arr->add(Object(objReal, c0Base + i));
        }
        dict->add("C0", Object(objArray, arr));
    }

    // C1: array of length nOutputs
    {
        auto *arr = new Array(nullptr);
        for (int i = 0; i < nOutputs; ++i) {
            arr->add(Object(objReal, c1Base + i));
        }
        dict->add("C1", Object(objArray, arr));
    }

    // N: exponent
    dict->add("N", Object(objReal, exponentN));

    return dict;
}

} // namespace

TEST(ExponentialFunctionTest_368, CopyReturnsNonNullUniquePtr_368)
{
    std::unique_ptr<Dict> dict(makeExpFuncDict(/*nOutputs=*/1,
                                               /*domainMin=*/0.0,
                                               /*domainMax=*/1.0,
                                               /*c0Base=*/0.0,
                                               /*c1Base=*/1.0,
                                               /*exponentN=*/1.0));

    ExponentialFunction func(dict.get());

    std::unique_ptr<Function> copied;
    EXPECT_NO_THROW(copied = func.copy());
    ASSERT_NE(copied, nullptr);
}

TEST(ExponentialFunctionTest_368, CopyProducesExponentialFunctionType_368)
{
    std::unique_ptr<Dict> dict(makeExpFuncDict(/*nOutputs=*/1,
                                               /*domainMin=*/-1.0,
                                               /*domainMax=*/2.0,
                                               /*c0Base=*/0.25,
                                               /*c1Base=*/0.75,
                                               /*exponentN=*/2.0));

    ExponentialFunction func(dict.get());

    std::unique_ptr<Function> copied = func.copy();
    ASSERT_NE(copied, nullptr);

    // Observable via RTTI: copy() should yield an ExponentialFunction instance.
    auto *copiedExp = dynamic_cast<ExponentialFunction *>(copied.get());
    ASSERT_NE(copiedExp, nullptr);

    // Observable via interface: reported type should match.
    EXPECT_EQ(copiedExp->getType(), func.getType());
}

TEST(ExponentialFunctionTest_368, CopyPreservesBasicParameters_368)
{
    std::unique_ptr<Dict> dict(makeExpFuncDict(/*nOutputs=*/2,
                                               /*domainMin=*/0.0,
                                               /*domainMax=*/10.0,
                                               /*c0Base=*/-3.0,
                                               /*c1Base=*/5.0,
                                               /*exponentN=*/3.5));

    ExponentialFunction func(dict.get());
    ASSERT_TRUE(func.isOk());

    std::unique_ptr<Function> copied = func.copy();
    ASSERT_NE(copied, nullptr);

    auto *copiedExp = dynamic_cast<ExponentialFunction *>(copied.get());
    ASSERT_NE(copiedExp, nullptr);

    // Observable behavior: the copied function should be "OK" if the original is.
    EXPECT_TRUE(copiedExp->isOk());

    // Observable via getters: scalar exponent should be preserved.
    EXPECT_DOUBLE_EQ(copiedExp->getE(), func.getE());

    // Observable via getters: coefficient arrays should preserve at least first few entries.
    // We do not assume how many outputs are used internally beyond what we provided.
    const double *origC0 = func.getC0();
    const double *origC1 = func.getC1();
    const double *copyC0 = copiedExp->getC0();
    const double *copyC1 = copiedExp->getC1();

    ASSERT_NE(origC0, nullptr);
    ASSERT_NE(origC1, nullptr);
    ASSERT_NE(copyC0, nullptr);
    ASSERT_NE(copyC1, nullptr);

    // Compare first two entries since we provided nOutputs=2.
    EXPECT_DOUBLE_EQ(copyC0[0], origC0[0]);
    EXPECT_DOUBLE_EQ(copyC0[1], origC0[1]);
    EXPECT_DOUBLE_EQ(copyC1[0], origC1[0]);
    EXPECT_DOUBLE_EQ(copyC1[1], origC1[1]);
}

TEST(ExponentialFunctionTest_368, CopyDoesNotAliasCoefficientStorage_368)
{
    std::unique_ptr<Dict> dict(makeExpFuncDict(/*nOutputs=*/3,
                                               /*domainMin=*/0.0,
                                               /*domainMax=*/1.0,
                                               /*c0Base=*/10.0,
                                               /*c1Base=*/20.0,
                                               /*exponentN=*/1.25));

    ExponentialFunction func(dict.get());
    ASSERT_TRUE(func.isOk());

    std::unique_ptr<Function> copied = func.copy();
    ASSERT_NE(copied, nullptr);

    auto *copiedExp = dynamic_cast<ExponentialFunction *>(copied.get());
    ASSERT_NE(copiedExp, nullptr);

    // Observable via public getters: coefficient pointers should not be the same addresses
    // if copy is a deep copy (as expected from a "copy()" API).
    // This does NOT access private state; it only compares pointers returned publicly.
    EXPECT_NE(copiedExp->getC0(), func.getC0());
    EXPECT_NE(copiedExp->getC1(), func.getC1());
}

TEST(ExponentialFunctionTest_368, CopyHandlesMaximumProvidedOutputsBoundary_368)
{
    // funcMaxOutputs is stated as 32 in the provided dependency snippet.
    // We treat this as a boundary target for inputs we provide to the public constructor.
    constexpr int kMaxOutputs = 32;

    std::unique_ptr<Dict> dict(makeExpFuncDict(/*nOutputs=*/kMaxOutputs,
                                               /*domainMin=*/0.0,
                                               /*domainMax=*/1.0,
                                               /*c0Base=*/-100.0,
                                               /*c1Base=*/100.0,
                                               /*exponentN=*/0.5));

    ExponentialFunction func(dict.get());

    // If construction is considered valid, the copy should also be valid and preserve values.
    // If construction is not valid in a given build/config, we still require copy() to be safe.
    std::unique_ptr<Function> copied;
    EXPECT_NO_THROW(copied = func.copy());
    ASSERT_NE(copied, nullptr);

    auto *copiedExp = dynamic_cast<ExponentialFunction *>(copied.get());
    ASSERT_NE(copiedExp, nullptr);

    if (func.isOk()) {
        EXPECT_TRUE(copiedExp->isOk());
        EXPECT_DOUBLE_EQ(copiedExp->getE(), func.getE());

        const double *origC0 = func.getC0();
        const double *origC1 = func.getC1();
        const double *copyC0 = copiedExp->getC0();
        const double *copyC1 = copiedExp->getC1();

        ASSERT_NE(origC0, nullptr);
        ASSERT_NE(origC1, nullptr);
        ASSERT_NE(copyC0, nullptr);
        ASSERT_NE(copyC1, nullptr);

        // Spot-check a few representative indices including boundaries.
        EXPECT_DOUBLE_EQ(copyC0[0], origC0[0]);
        EXPECT_DOUBLE_EQ(copyC0[1], origC0[1]);
        EXPECT_DOUBLE_EQ(copyC0[kMaxOutputs - 2], origC0[kMaxOutputs - 2]);
        EXPECT_DOUBLE_EQ(copyC0[kMaxOutputs - 1], origC0[kMaxOutputs - 1]);

        EXPECT_DOUBLE_EQ(copyC1[0], origC1[0]);
        EXPECT_DOUBLE_EQ(copyC1[1], origC1[1]);
        EXPECT_DOUBLE_EQ(copyC1[kMaxOutputs - 2], origC1[kMaxOutputs - 2]);
        EXPECT_DOUBLE_EQ(copyC1[kMaxOutputs - 1], origC1[kMaxOutputs - 1]);
    }
}

TEST(ExponentialFunctionTest_368, CopyIsSafeEvenWhenConstructionIsNotOk_368)
{
    // Build an intentionally under-specified dict. We do not assume what keys are mandatory;
    // we only assert that copy() is safe/observable through the interface.
    std::unique_ptr<Dict> dict(makeExpFuncDict(/*nOutputs=*/1,
                                               /*domainMin=*/0.0,
                                               /*domainMax=*/1.0,
                                               /*c0Base=*/0.0,
                                               /*c1Base=*/1.0,
                                               /*exponentN=*/1.0,
                                               /*includeAllRequiredKeys=*/false));

    ExponentialFunction func(dict.get());

    // Whether func.isOk() is true or false depends on Poppler's requirements; we do not infer.
    std::unique_ptr<Function> copied;
    EXPECT_NO_THROW(copied = func.copy());
    ASSERT_NE(copied, nullptr);

    // Still expected to be an ExponentialFunction instance by API contract of copy().
    EXPECT_NE(dynamic_cast<ExponentialFunction *>(copied.get()), nullptr);
}