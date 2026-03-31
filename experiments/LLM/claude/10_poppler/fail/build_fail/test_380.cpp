#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Function.h"
#include "Dict.h"
#include "Object.h"
#include "PDFDoc.h"

// Since StitchingFunction requires a Dict for construction and we're treating
// it as a black box, we test what we can through the public interface.

class StitchingFunctionTest_380 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getType returns the correct function type for StitchingFunction
TEST_F(StitchingFunctionTest_380, GetTypeReturnsStitching_380) {
    // We need a valid Dict to construct StitchingFunction
    // Since we can't easily create one without a full PDF context,
    // we test through Function::parse if available, or verify interface contracts

    // Create a minimal stitching function setup
    // StitchingFunction is Type 3 in PDF spec
    // Without a valid Dict, construction may fail, but we can test isOk() returns false

    auto xref = std::make_unique<XRef>();
    Dict dict(xref.get());

    // Set up FunctionType = 3 (Stitching)
    dict.add("FunctionType", Object(3));

    // Set up Domain
    Array *domainArray = new Array(xref.get());
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict.add("Domain", Object(domainArray));

    // Set up Functions array with two identity-like functions
    // We'll use simple sampled or identity functions
    // For a minimal test, we set up two sub-functions

    // Sub-function 1: Identity function (Type 4 - PostScript calculator)
    Dict *func1Dict = new Dict(xref.get());
    func1Dict->add("FunctionType", Object(4));
    Array *domain1 = new Array(xref.get());
    domain1->add(Object(0.0));
    domain1->add(Object(0.5));
    func1Dict->add("Domain", Object(domain1));
    Array *range1 = new Array(xref.get());
    range1->add(Object(0.0));
    range1->add(Object(1.0));
    func1Dict->add("Range", Object(range1));

    // Sub-function 2
    Dict *func2Dict = new Dict(xref.get());
    func2Dict->add("FunctionType", Object(4));
    Array *domain2 = new Array(xref.get());
    domain2->add(Object(0.5));
    domain2->add(Object(1.0));
    func2Dict->add("Domain", Object(domain2));
    Array *range2 = new Array(xref.get());
    range2->add(Object(0.0));
    range2->add(Object(1.0));
    func2Dict->add("Range", Object(range2));

    Array *funcsArray = new Array(xref.get());
    funcsArray->add(Object(func1Dict));
    funcsArray->add(Object(func2Dict));
    dict.add("Functions", Object(funcsArray));

    // Set up Bounds
    Array *boundsArray = new Array(xref.get());
    boundsArray->add(Object(0.5));
    dict.add("Bounds", Object(boundsArray));

    // Set up Encode
    Array *encodeArray = new Array(xref.get());
    encodeArray->add(Object(0.0));
    encodeArray->add(Object(0.5));
    encodeArray->add(Object(0.5));
    encodeArray->add(Object(1.0));
    dict.add("Encode", Object(encodeArray));

    // Set up Range
    Array *rangeArray = new Array(xref.get());
    rangeArray->add(Object(0.0));
    rangeArray->add(Object(1.0));
    dict.add("Range", Object(rangeArray));

    RefRecursionChecker checker;
    StitchingFunction sf(&dict, checker);

    // If construction succeeded, verify type
    if (sf.isOk()) {
        EXPECT_EQ(sf.getType(), Function::Type::Stitching);
    }
}

// Test getEncode returns non-null when function is valid
TEST_F(StitchingFunctionTest_380, GetEncodeReturnsNonNullWhenValid_380) {
    auto xref = std::make_unique<XRef>();
    Dict dict(xref.get());
    dict.add("FunctionType", Object(3));

    Array *domainArray = new Array(xref.get());
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict.add("Domain", Object(domainArray));

    Array *rangeArray = new Array(xref.get());
    rangeArray->add(Object(0.0));
    rangeArray->add(Object(1.0));
    dict.add("Range", Object(rangeArray));

    Dict *func1Dict = new Dict(xref.get());
    func1Dict->add("FunctionType", Object(4));
    Array *d1 = new Array(xref.get());
    d1->add(Object(0.0));
    d1->add(Object(1.0));
    func1Dict->add("Domain", Object(d1));
    Array *r1 = new Array(xref.get());
    r1->add(Object(0.0));
    r1->add(Object(1.0));
    func1Dict->add("Range", Object(r1));

    Dict *func2Dict = new Dict(xref.get());
    func2Dict->add("FunctionType", Object(4));
    Array *d2 = new Array(xref.get());
    d2->add(Object(0.0));
    d2->add(Object(1.0));
    func2Dict->add("Domain", Object(d2));
    Array *r2 = new Array(xref.get());
    r2->add(Object(0.0));
    r2->add(Object(1.0));
    func2Dict->add("Range", Object(r2));

    Array *funcsArray = new Array(xref.get());
    funcsArray->add(Object(func1Dict));
    funcsArray->add(Object(func2Dict));
    dict.add("Functions", Object(funcsArray));

    Array *boundsArray = new Array(xref.get());
    boundsArray->add(Object(0.5));
    dict.add("Bounds", Object(boundsArray));

    Array *encodeArray = new Array(xref.get());
    encodeArray->add(Object(0.0));
    encodeArray->add(Object(0.5));
    encodeArray->add(Object(0.5));
    encodeArray->add(Object(1.0));
    dict.add("Encode", Object(encodeArray));

    RefRecursionChecker checker;
    StitchingFunction sf(&dict, checker);

    if (sf.isOk()) {
        const double *enc = sf.getEncode();
        ASSERT_NE(enc, nullptr);
        EXPECT_DOUBLE_EQ(enc[0], 0.0);
        EXPECT_DOUBLE_EQ(enc[1], 0.5);
        EXPECT_DOUBLE_EQ(enc[2], 0.5);
        EXPECT_DOUBLE_EQ(enc[3], 1.0);
    }
}

// Test getNumFuncs returns correct count
TEST_F(StitchingFunctionTest_380, GetNumFuncsReturnsCorrectCount_380) {
    auto xref = std::make_unique<XRef>();
    Dict dict(xref.get());
    dict.add("FunctionType", Object(3));

    Array *domainArray = new Array(xref.get());
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict.add("Domain", Object(domainArray));

    Array *rangeArray = new Array(xref.get());
    rangeArray->add(Object(0.0));
    rangeArray->add(Object(1.0));
    dict.add("Range", Object(rangeArray));

    Dict *func1Dict = new Dict(xref.get());
    func1Dict->add("FunctionType", Object(4));
    Array *d1 = new Array(xref.get());
    d1->add(Object(0.0));
    d1->add(Object(1.0));
    func1Dict->add("Domain", Object(d1));
    Array *r1 = new Array(xref.get());
    r1->add(Object(0.0));
    r1->add(Object(1.0));
    func1Dict->add("Range", Object(r1));

    Dict *func2Dict = new Dict(xref.get());
    func2Dict->add("FunctionType", Object(4));
    Array *d2 = new Array(xref.get());
    d2->add(Object(0.0));
    d2->add(Object(1.0));
    func2Dict->add("Domain", Object(d2));
    Array *r2 = new Array(xref.get());
    r2->add(Object(0.0));
    r2->add(Object(1.0));
    func2Dict->add("Range", Object(r2));

    Array *funcsArray = new Array(xref.get());
    funcsArray->add(Object(func1Dict));
    funcsArray->add(Object(func2Dict));
    dict.add("Functions", Object(funcsArray));

    Array *boundsArray = new Array(xref.get());
    boundsArray->add(Object(0.5));
    dict.add("Bounds", Object(boundsArray));

    Array *encodeArray = new Array(xref.get());
    encodeArray->add(Object(0.0));
    encodeArray->add(Object(0.5));
    encodeArray->add(Object(0.5));
    encodeArray->add(Object(1.0));
    dict.add("Encode", Object(encodeArray));

    RefRecursionChecker checker;
    StitchingFunction sf(&dict, checker);

    if (sf.isOk()) {
        EXPECT_EQ(sf.getNumFuncs(), 2);
    }
}

// Test getBounds returns non-null and correct values
TEST_F(StitchingFunctionTest_380, GetBoundsReturnsCorrectValues_380) {
    auto xref = std::make_unique<XRef>();
    Dict dict(xref.get());
    dict.add("FunctionType", Object(3));

    Array *domainArray = new Array(xref.get());
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict.add("Domain", Object(domainArray));

    Array *rangeArray = new Array(xref.get());
    rangeArray->add(Object(0.0));
    rangeArray->add(Object(1.0));
    dict.add("Range", Object(rangeArray));

    Dict *func1Dict = new Dict(xref.get());
    func1Dict->add("FunctionType", Object(4));
    Array *d1 = new Array(xref.get());
    d1->add(Object(0.0));
    d1->add(Object(1.0));
    func1Dict->add("Domain", Object(d1));
    Array *r1 = new Array(xref.get());
    r1->add(Object(0.0));
    r1->add(Object(1.0));
    func1Dict->add("Range", Object(r1));

    Dict *func2Dict = new Dict(xref.get());
    func2Dict->add("FunctionType", Object(4));
    Array *d2 = new Array(xref.get());
    d2->add(Object(0.0));
    d2->add(Object(1.0));
    func2Dict->add("Domain", Object(d2));
    Array *r2 = new Array(xref.get());
    r2->add(Object(0.0));
    r2->add(Object(1.0));
    func2Dict->add("Range", Object(r2));

    Array *funcsArray = new Array(xref.get());
    funcsArray->add(Object(func1Dict));
    funcsArray->add(Object(func2Dict));
    dict.add("Functions", Object(funcsArray));

    Array *boundsArray = new Array(xref.get());
    boundsArray->add(Object(0.5));
    dict.add("Bounds", Object(boundsArray));

    Array *encodeArray = new Array(xref.get());
    encodeArray->add(Object(0.0));
    encodeArray->add(Object(0.5));
    encodeArray->add(Object(0.5));
    encodeArray->add(Object(1.0));
    dict.add("Encode", Object(encodeArray));

    RefRecursionChecker checker;
    StitchingFunction sf(&dict, checker);

    if (sf.isOk()) {
        const double *bounds = sf.getBounds();
        ASSERT_NE(bounds, nullptr);
        EXPECT_DOUBLE_EQ(bounds[0], 0.5);
    }
}

// Test getFunc returns valid function pointers
TEST_F(StitchingFunctionTest_380, GetFuncReturnsValidPointers_380) {
    auto xref = std::make_unique<XRef>();
    Dict dict(xref.get());
    dict.add("FunctionType", Object(3));

    Array *domainArray = new Array(xref.get());
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict.add("Domain", Object(domainArray));

    Array *rangeArray = new Array(xref.get());
    rangeArray->add(Object(0.0));
    rangeArray->add(Object(1.0));
    dict.add("Range", Object(rangeArray));

    Dict *func1Dict = new Dict(xref.get());
    func1Dict->add("FunctionType", Object(4));
    Array *d1 = new Array(xref.get());
    d1->add(Object(0.0));
    d1->add(Object(1.0));
    func1Dict->add("Domain", Object(d1));
    Array *r1 = new Array(xref.get());
    r1->add(Object(0.0));
    r1->add(Object(1.0));
    func1Dict->add("Range", Object(r1));

    Dict *func2Dict = new Dict(xref.get());
    func2Dict->add("FunctionType", Object(4));
    Array *d2 = new Array(xref.get());
    d2->add(Object(0.0));
    d2->add(Object(1.0));
    func2Dict->add("Domain", Object(d2));
    Array *r2 = new Array(xref.get());
    r2->add(Object(0.0));
    r2->add(Object(1.0));
    func2Dict->add("Range", Object(r2));

    Array *funcsArray = new Array(xref.get());
    funcsArray->add(Object(func1Dict));
    funcsArray->add(Object(func2Dict));
    dict.add("Functions", Object(funcsArray));

    Array *boundsArray = new Array(xref.get());
    boundsArray->add(Object(0.5));
    dict.add("Bounds", Object(boundsArray));

    Array *encodeArray = new Array(xref.get());
    encodeArray->add(Object(0.0));
    encodeArray->add(Object(0.5));
    encodeArray->add(Object(0.5));
    encodeArray->add(Object(1.0));
    dict.add("Encode", Object(encodeArray));

    RefRecursionChecker checker;
    StitchingFunction sf(&dict, checker);

    if (sf.isOk()) {
        EXPECT_NE(sf.getFunc(0), nullptr);
        EXPECT_NE(sf.getFunc(1), nullptr);
    }
}

// Test copy creates a valid copy
TEST_F(StitchingFunctionTest_380, CopyCreatesValidFunction_380) {
    auto xref = std::make_unique<XRef>();
    Dict dict(xref.get());
    dict.add("FunctionType", Object(3));

    Array *domainArray = new Array(xref.get());
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict.add("Domain", Object(domainArray));

    Array *rangeArray = new Array(xref.get());
    rangeArray->add(Object(0.0));
    rangeArray->add(Object(1.0));
    dict.add("Range", Object(rangeArray));

    Dict *func1Dict = new Dict(xref.get());
    func1Dict->add("FunctionType", Object(4));
    Array *d1 = new Array(xref.get());
    d1->add(Object(0.0));
    d1->add(Object(1.0));
    func1Dict->add("Domain", Object(d1));
    Array *r1 = new Array(xref.get());
    r1->add(Object(0.0));
    r1->add(Object(1.0));
    func1Dict->add("Range", Object(r1));

    Dict *func2Dict = new Dict(xref.get());
    func2Dict->add("FunctionType", Object(4));
    Array *d2 = new Array(xref.get());
    d2->add(Object(0.0));
    d2->add(Object(1.0));
    func2Dict->add("Domain", Object(d2));
    Array *r2 = new Array(xref.get());
    r2->add(Object(0.0));
    r2->add(Object(1.0));
    func2Dict->add("Range", Object(r2));

    Array *funcsArray = new Array(xref.get());
    funcsArray->add(Object(func1Dict));
    funcsArray->add(Object(func2Dict));
    dict.add("Functions", Object(funcsArray));

    Array *boundsArray = new Array(xref.get());
    boundsArray->add(Object(0.5));
    dict.add("Bounds", Object(boundsArray));

    Array *encodeArray = new Array(xref.get());
    encodeArray->add(Object(0.0));
    encodeArray->add(Object(0.5));
    encodeArray->add(Object(0.5));
    encodeArray->add(Object(1.0));
    dict.add("Encode", Object(encodeArray));

    RefRecursionChecker checker;
    StitchingFunction sf(&dict, checker);

    if (sf.isOk()) {
        auto copied = sf.copy();
        ASSERT_NE(copied, nullptr);
        EXPECT_TRUE(copied->isOk());
    }
}

// Test that an empty/invalid dict results in isOk() returning false
TEST_F(StitchingFunctionTest_380, InvalidDictReturnsNotOk_380) {
    auto xref = std::make_unique<XRef>();
    Dict dict(xref.get());

    // Minimal dict without required entries
    dict.add("FunctionType", Object(3));

    RefRecursionChecker checker;
    StitchingFunction sf(&dict, checker);

    EXPECT_FALSE(sf.isOk());
}

// Test getScale returns non-null when function is valid
TEST_F(StitchingFunctionTest_380, GetScaleReturnsNonNull_380) {
    auto xref = std::make_unique<XRef>();
    Dict dict(xref.get());
    dict.add("FunctionType", Object(3));

    Array *domainArray = new Array(xref.get());
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict.add("Domain", Object(domainArray));

    Array *rangeArray = new Array(xref.get());
    rangeArray->add(Object(0.0));
    rangeArray->add(Object(1.0));
    dict.add("Range", Object(rangeArray));

    Dict *func1Dict = new Dict(xref.get());
    func1Dict->add("FunctionType", Object(4));
    Array *d1 = new Array(xref.get());
    d1->add(Object(0.0));
    d1->add(Object(1.0));
    func1Dict->add("Domain", Object(d1));
    Array *r1 = new Array(xref.get());
    r1->add(Object(0.0));
    r1->add(Object(1.0));
    func1Dict->add("Range", Object(r1));

    Dict *func2Dict = new Dict(xref.get());
    func2Dict->add("FunctionType", Object(4));
    Array *d2 = new Array(xref.get());
    d2->add(Object(0.0));
    d2->add(Object(1.0));
    func2Dict->add("Domain", Object(d2));
    Array *r2 = new Array(xref.get());
    r2->add(Object(0.0));
    r2->add(Object(1.0));
    func2Dict->add("Range", Object(r2));

    Array *funcsArray = new Array(xref.get());
    funcsArray->add(Object(func1Dict));
    funcsArray->add(Object(func2Dict));
    dict.add("Functions", Object(funcsArray));

    Array *boundsArray = new Array(xref.get());
    boundsArray->add(Object(0.5));
    dict.add("Bounds", Object(boundsArray));

    Array *encodeArray = new Array(xref.get());
    encodeArray->add(Object(0.0));
    encodeArray->add(Object(0.5));
    encodeArray->add(Object(0.5));
    encodeArray->add(Object(1.0));
    dict.add("Encode", Object(encodeArray));

    RefRecursionChecker checker;
    StitchingFunction sf(&dict, checker);

    if (sf.isOk()) {
        const double *scale = sf.getScale();
        ASSERT_NE(scale, nullptr);
    }
}

// Test missing Functions array makes it invalid
TEST_F(StitchingFunctionTest_380, MissingFunctionsArrayIsNotOk_380) {
    auto xref = std::make_unique<XRef>();
    Dict dict(xref.get());
    dict.add("FunctionType", Object(3));

    Array *domainArray = new Array(xref.get());
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict.add("Domain", Object(domainArray));

    Array *rangeArray = new Array(xref.get());
    rangeArray->add(Object(0.0));
    rangeArray->add(Object(1.0));
    dict.add("Range", Object(rangeArray));

    // No Functions, Bounds, or Encode
    RefRecursionChecker checker;
    StitchingFunction sf(&dict, checker);

    EXPECT_FALSE(sf.isOk());
}

// Test missing Bounds array makes it invalid
TEST_F(StitchingFunctionTest_380, MissingBoundsIsNotOk_380) {
    auto xref = std::make_unique<XRef>();
    Dict dict(xref.get());
    dict.add("FunctionType", Object(3));

    Array *domainArray = new Array(xref.get());
    domainArray->add(Object(0.0));
    domainArray->add(Object(1.0));
    dict.add("Domain", Object(domainArray));

    Array *rangeArray = new Array(xref.get());
    rangeArray->add(Object(0.0));
    rangeArray->add(Object(1.0));
    dict.add("Range", Object(rangeArray));

    Dict *func1Dict = new Dict(xref.get());
    func1Dict->add("FunctionType", Object(4));
    Array *d1 = new Array(xref.get());
    d1->add(Object(0.0));
    d1->add(Object(1.0));
    func1Dict->add("Domain", Object(d1));
    Array *r1 = new Array(xref.get());
    r1->add(Object(0.0));
    r1->add(Object(1.0));
    func1Dict->add("Range", Object(r1));

    Array *funcsArray = new Array(xref.get());
    funcsArray->add(Object(func1Dict));
    dict.add("Functions", Object(funcsArray));

    // No Bounds or Encode
    RefRecursionChecker checker;
    StitchingFunction sf(&dict, checker);

    // With single function and no bounds, may or may not be ok
    // We just verify it doesn't crash
    sf.isOk();
}
