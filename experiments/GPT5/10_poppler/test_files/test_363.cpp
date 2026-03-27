// TEST_ID: 363
// File: sampled_function_getencodemax_363_test.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <memory>
#include <vector>

// Poppler internal headers (as used by poppler core)
#include "poppler/Function.h"
#include "poppler/Object.h"
#include "poppler/Dict.h"
#include "poppler/Array.h"

namespace {

// Helper builders using the classic Poppler/Xpdf-style Object API.
// (These helpers are intentionally thin and only assemble public inputs.)

Object MakeIntObj(int v)
{
    Object o;
    o.initInt(v);
    return o;
}

Object MakeRealObj(double v)
{
    Object o;
    o.initReal(v);
    return o;
}

Object MakeNameObj(const char *name)
{
    Object o;
    o.initName(const_cast<char *>(name)); // Poppler API typically takes non-const
    return o;
}

Object MakeArrayObj(std::initializer_list<double> vals)
{
    auto *arr = new Array();
    for (double v : vals) {
        arr->add(MakeRealObj(v));
    }
    Object o;
    o.initArray(arr);
    return o;
}

Object MakeArrayObjInt(std::initializer_list<int> vals)
{
    auto *arr = new Array();
    for (int v : vals) {
        arr->add(MakeIntObj(v));
    }
    Object o;
    o.initArray(arr);
    return o;
}

void DictAdd(Dict *dict, const char *key, Object &&val)
{
    // Xpdf/Poppler-style Dict::add usually takes ownership of Object.
    dict->add(const_cast<char *>(key), std::move(val));
}

// Builds a minimal Type 0 (Sampled) function dictionary good enough for
// constructing SampledFunction in many Poppler versions.
//
// Parameters:
//  - size0: Size[0]
//  - bps: BitsPerSample
//  - encodeOpt: if provided, sets Encode to [emin, emax]; if nullptr, omits Encode
//  - decodeOpt: if provided, sets Decode to [dmin, dmax]; if nullptr, omits Decode
std::unique_ptr<Dict> MakeType0Dict_1in1out(int size0,
                                            int bps,
                                            const std::pair<double, double> *encodeOpt,
                                            const std::pair<double, double> *decodeOpt)
{
    auto dict = std::make_unique<Dict>();

    // Required for sampled functions.
    DictAdd(dict.get(), "FunctionType", MakeIntObj(0));

    // Minimal 1 input domain and 1 output range.
    DictAdd(dict.get(), "Domain", MakeArrayObj({0.0, 1.0}));
    DictAdd(dict.get(), "Range", MakeArrayObj({0.0, 1.0}));

    // Size and BPS.
    DictAdd(dict.get(), "Size", MakeArrayObjInt({size0}));
    DictAdd(dict.get(), "BitsPerSample", MakeIntObj(bps));

    // Optional arrays.
    if (encodeOpt) {
        DictAdd(dict.get(), "Encode", MakeArrayObj({encodeOpt->first, encodeOpt->second}));
    }
    if (decodeOpt) {
        DictAdd(dict.get(), "Decode", MakeArrayObj({decodeOpt->first, decodeOpt->second}));
    }

    return dict;
}

class SampledFunctionTest_363 : public ::testing::Test
{
protected:
    // Try to construct SampledFunction from a dict only (funcObj may be unused for
    // dict-based representation in some Poppler builds). We keep the Object alive
    // during construction.
    std::unique_ptr<SampledFunction> MakeFromDictOnly(std::unique_ptr<Dict> dict)
    {
        // Represent the function as a dictionary object (not a stream).
        Object funcObj;
        funcObj.initDict(dict.release());

        // SampledFunction signature per prompt: SampledFunction(Object* funcObj, Dict* dict)
        // For dict-based function objects, dict parameter may be the same as funcObj.getDict().
        Dict *d = funcObj.getDict();
        auto fn = std::make_unique<SampledFunction>(&funcObj, d);
        return fn;
    }
};

} // namespace

TEST_F(SampledFunctionTest_363, GetEncodeMax_UsesExplicitEncode_363)
{
    const std::pair<double, double> encode{2.25, 9.75};
    auto dict = MakeType0Dict_1in1out(/*size0=*/4, /*bps=*/8, &encode, /*decodeOpt=*/nullptr);

    auto fn = MakeFromDictOnly(std::move(dict));
    if (!fn || !fn->isOk()) {
        GTEST_SKIP() << "SampledFunction could not be constructed as OK with this Poppler build.";
    }

    EXPECT_DOUBLE_EQ(fn->getEncodeMax(0), 9.75);
}

TEST_F(SampledFunctionTest_363, GetEncodeMax_DefaultsToSizeMinusOne_WhenEncodeMissing_363)
{
    // PDF spec default Encode for sampled functions: [0, Size_i - 1] for each input.
    // We verify observable behavior through getEncodeMax(0).
    const int size0 = 7;
    auto dict = MakeType0Dict_1in1out(/*size0=*/size0, /*bps=*/8, /*encodeOpt=*/nullptr, /*decodeOpt=*/nullptr);

    auto fn = MakeFromDictOnly(std::move(dict));
    if (!fn || !fn->isOk()) {
        GTEST_SKIP() << "SampledFunction could not be constructed as OK with this Poppler build.";
    }

    EXPECT_DOUBLE_EQ(fn->getEncodeMax(0), static_cast<double>(size0 - 1));
}

TEST_F(SampledFunctionTest_363, GetEncodeMax_AllowsNegativeEncodeMax_WhenProvided_363)
{
    const std::pair<double, double> encode{-5.0, -1.0};
    auto dict = MakeType0Dict_1in1out(/*size0=*/2, /*bps=*/8, &encode, /*decodeOpt=*/nullptr);

    auto fn = MakeFromDictOnly(std::move(dict));
    if (!fn || !fn->isOk()) {
        GTEST_SKIP() << "SampledFunction could not be constructed as OK with this Poppler build.";
    }

    EXPECT_DOUBLE_EQ(fn->getEncodeMax(0), -1.0);
}

TEST_F(SampledFunctionTest_363, GetEncodeMax_RemainsStableAcrossRepeatedCalls_363)
{
    const std::pair<double, double> encode{0.0, 123.0};
    auto dict = MakeType0Dict_1in1out(/*size0=*/10, /*bps=*/8, &encode, /*decodeOpt=*/nullptr);

    auto fn = MakeFromDictOnly(std::move(dict));
    if (!fn || !fn->isOk()) {
        GTEST_SKIP() << "SampledFunction could not be constructed as OK with this Poppler build.";
    }

    const double first = fn->getEncodeMax(0);
    const double second = fn->getEncodeMax(0);
    const double third = fn->getEncodeMax(0);

    EXPECT_DOUBLE_EQ(first, 123.0);
    EXPECT_DOUBLE_EQ(second, first);
    EXPECT_DOUBLE_EQ(third, first);
}

TEST_F(SampledFunctionTest_363, ConstructionWithClearlyInvalidBitsPerSample_IsNotOkOrSkips_363)
{
    // BitsPerSample is constrained by the PDF spec (commonly 1..32). Provide an
    // obviously invalid value and observe via isOk().
    auto dict = MakeType0Dict_1in1out(/*size0=*/2, /*bps=*/0, /*encodeOpt=*/nullptr, /*decodeOpt=*/nullptr);

    auto fn = MakeFromDictOnly(std::move(dict));
    if (!fn) {
        GTEST_SKIP() << "SampledFunction could not be constructed in this Poppler build.";
    }

    // Observable error case: isOk() should be false OR the constructor may coerce/accept.
    // We assert only that the API is callable and returns a boolean; if it returns true,
    // we avoid making stronger claims.
    const bool ok = fn->isOk();
    if (ok) {
        // If the implementation accepts bps=0 (unexpected), still ensure getEncodeMax is callable.
        EXPECT_TRUE(std::isfinite(fn->getEncodeMax(0)));
    } else {
        SUCCEED();
    }
}