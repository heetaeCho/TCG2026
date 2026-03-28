// TEST_ID: 376
// File: stitchingfunction_unittest_376.cc

#include <gtest/gtest.h>

#include "poppler/Function.h"

// Poppler core types used to build Function dictionaries/objects.
#include "poppler/Object.h"
#include "poppler/Dict.h"
#include "poppler/Array.h"
#include "poppler/RefRecursionChecker.h"

namespace {

// Helper: make an Object holding a real number (Poppler commonly uses double for numeric entries).
static Object MakeReal(double v)
{
    Object o;
    o.initReal(v);
    return o;
}

static Object MakeInt(int v)
{
    Object o;
    o.initInt(v);
    return o;
}

static Object MakeName(const char *name)
{
    Object o;
    o.initName(const_cast<char *>(name));
    return o;
}

static Object MakeArray(std::initializer_list<Object> elems)
{
    Array *arr = new Array(nullptr);
    for (const auto &e : elems) {
        // Array::add takes ownership by value (Object is ref-counted/movable in Poppler).
        Object copy = e.copy();
        arr->add(std::move(copy));
    }
    Object o;
    o.initArray(arr);
    return o;
}

// Build a minimal Type 2 (Exponential Interpolation) sub-function dictionary.
// This is a reasonably small function type to embed inside a Stitching function.
static Object MakeType2FunctionDict_1in1out(double domain0, double domain1,
                                           double c0, double c1, double n)
{
    Dict *d = new Dict(nullptr);

    d->add("FunctionType", MakeInt(2));
    d->add("Domain", MakeArray({MakeReal(domain0), MakeReal(domain1)}));

    // For 1 output, C0/C1 are arrays of length 1.
    d->add("C0", MakeArray({MakeReal(c0)}));
    d->add("C1", MakeArray({MakeReal(c1)}));
    d->add("N", MakeReal(n));

    Object o;
    o.initDict(d);
    return o;
}

// Build a minimal Stitching (Type 3) function dictionary with 2 sub-functions.
static Object MakeType3StitchingFunctionDict_TwoFuncs()
{
    Dict *d = new Dict(nullptr);

    d->add("FunctionType", MakeInt(3));
    d->add("Domain", MakeArray({MakeReal(0.0), MakeReal(1.0)}));

    // Two subfunctions: both 1-in/1-out Type 2 functions.
    Object f0 = MakeType2FunctionDict_1in1out(0.0, 1.0, /*C0*/ 0.0, /*C1*/ 1.0, /*N*/ 1.0);
    Object f1 = MakeType2FunctionDict_1in1out(0.0, 1.0, /*C0*/ 1.0, /*C1*/ 0.0, /*N*/ 1.0);

    d->add("Functions", MakeArray({std::move(f0), std::move(f1)}));

    // Bounds has length = (#funcs - 1) = 1
    d->add("Bounds", MakeArray({MakeReal(0.5)}));

    // Encode has length = 2 * (#funcs) = 4
    d->add("Encode", MakeArray({MakeReal(0.0), MakeReal(1.0), MakeReal(0.0), MakeReal(1.0)}));

    Object o;
    o.initDict(d);
    return o;
}

} // namespace

TEST(StitchingFunctionTest_376, ConstructWithNullDictDoesNotCrash_376)
{
    RefRecursionChecker checker;

    // Observable requirement: construction should not crash; isOk() must be callable.
    EXPECT_NO_THROW({
        StitchingFunction f(nullptr, checker);
        (void)f.isOk();
    });
}

TEST(StitchingFunctionTest_376, WrongFunctionTypeYieldsNotOk_376)
{
    RefRecursionChecker checker;

    Dict *d = new Dict(nullptr);
    d->add("FunctionType", MakeInt(2)); // not a stitching function
    d->add("Domain", MakeArray({MakeReal(0.0), MakeReal(1.0)}));
    Object dictObj;
    dictObj.initDict(d);

    ASSERT_TRUE(dictObj.isDict());
    StitchingFunction f(dictObj.getDict(), checker);

    // Observable behavior: a StitchingFunction built from a non-Type3 dict should report not OK.
    EXPECT_FALSE(f.isOk());
}

TEST(StitchingFunctionTest_376, MissingRequiredKeysYieldsNotOk_376)
{
    RefRecursionChecker checker;

    Dict *d = new Dict(nullptr);
    d->add("FunctionType", MakeInt(3));
    d->add("Domain", MakeArray({MakeReal(0.0), MakeReal(1.0)}));
    // Intentionally omit: Functions / Bounds / Encode
    Object dictObj;
    dictObj.initDict(d);

    StitchingFunction f(dictObj.getDict(), checker);
    EXPECT_FALSE(f.isOk());
}

TEST(StitchingFunctionTest_376, ValidType3DictIsOkAndExposesSubFunctions_376)
{
    RefRecursionChecker checker;

    Object dictObj = MakeType3StitchingFunctionDict_TwoFuncs();
    ASSERT_TRUE(dictObj.isDict());

    StitchingFunction f(dictObj.getDict(), checker);

    ASSERT_TRUE(f.isOk());

    // Public accessors should behave consistently for a valid instance.
    EXPECT_EQ(f.getNumFuncs(), 2);

    const Function *sf0 = f.getFunc(0);
    const Function *sf1 = f.getFunc(1);
    EXPECT_NE(sf0, nullptr);
    EXPECT_NE(sf1, nullptr);

    // Out-of-range indices: must not crash; return value is observable.
    EXPECT_NO_THROW({
        const Function *neg = f.getFunc(-1);
        const Function *big = f.getFunc(2);
        // We don't assume the exact convention, but most interfaces return nullptr.
        // If Poppler chooses to clamp/return something else, this still remains safe.
        (void)neg;
        (void)big;
    });

    EXPECT_NE(f.getBounds(), nullptr);
    EXPECT_NE(f.getEncode(), nullptr);
    EXPECT_NE(f.getScale(), nullptr); // Exposed in interface; should be usable without crashing.
}

TEST(StitchingFunctionTest_376, TransformDoesNotCrashForDomainEndpoints_376)
{
    RefRecursionChecker checker;

    Object dictObj = MakeType3StitchingFunctionDict_TwoFuncs();
    ASSERT_TRUE(dictObj.isDict());

    StitchingFunction f(dictObj.getDict(), checker);
    ASSERT_TRUE(f.isOk());

    double out = 0.0;

    // Boundary conditions: domain endpoints.
    EXPECT_NO_THROW({
        const double in0 = 0.0;
        f.transform(&in0, &out);
    });

    EXPECT_NO_THROW({
        const double in1 = 1.0;
        f.transform(&in1, &out);
    });
}

TEST(StitchingFunctionTest_376, CopyProducesIndependentOkInstance_376)
{
    RefRecursionChecker checker;

    Object dictObj = MakeType3StitchingFunctionDict_TwoFuncs();
    ASSERT_TRUE(dictObj.isDict());

    StitchingFunction f(dictObj.getDict(), checker);
    ASSERT_TRUE(f.isOk());

    std::unique_ptr<Function> c;
    ASSERT_NO_THROW({ c = f.copy(); });
    ASSERT_NE(c, nullptr);

    // Observable behavior through base interface:
    EXPECT_TRUE(c->isOk());
    EXPECT_EQ(c->getType(), f.getType());

    // If it is a StitchingFunction copy, it should expose compatible stitching properties.
    // We avoid relying on RTTI/dynamic_cast availability; use only public methods if possible.
    // Here, we check that calling transform doesn't crash.
    double out = 0.0;
    const double in = 0.25;
    EXPECT_NO_THROW({ c->transform(&in, &out); });
}